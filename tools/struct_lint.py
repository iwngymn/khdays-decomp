#!/usr/bin/env python3
"""struct_lint.py -- does the landed C agree with the object vocabulary?

    python tools/struct_lint.py <file.c> ...        the wave's files
    python tools/struct_lint.py --module ov245       one module
    python tools/struct_lint.py --all [--summary]    the tree (~10 s)
    options: --doc PATH   --strict   --skip @list.txt   --info

Exit 1 when any FAIL is printed, else 0. WARN and INFO never fail.

What it checks, per file, against STRUCTS.md:

  1. Every local struct, laid out to byte offsets (vocab.file_structs). A
     struct is BOUND to an object when its name is one of the object's aliases
     (name-bound) or when enough of its members sit at the object's known
     offsets with the same width (shape-bound: 2 confirmed/tentative fields, or
     1 plus 2 `seen`). For a bound struct, each member at a canonical offset:
       FAIL  width differs                (u32 where the doc says u64)
       FAIL  signedness differs           (u8 where the doc says s8; bytes and
             halfwords only -- ldr cannot show a word's sign, so that is WARN)
       FAIL  offset is `excluded`         (the struct mixes two objects)
       FAIL  a canonical NAME used at a different offset (`pNode` at 0x4)
       WARN  name differs from the doc's confirmed/tentative name
       INFO  a `seen` field carries a real name in this file (a proposal
             candidate for the doc; a worker reports it, see workflow_integration.md)
     Sub-struct members are flattened, so `struct Charge charge` at 0x2770 is
     judged by Charge's own members at 0x2770+.
  2. Every raw `*(T *)(BASE + 0xN)` / `((T *)(BASE + 0xN))->f`, grouped by BASE
     expression and bound by the same shape rule. Same FAILs for width and
     excluded; a store's signedness mismatch is only WARN (the bytes cannot
     see it; a load's would not match at all).
  3. --summary: per alias, how many structs are consistent vs conflicting --
     the audit_structs.py "84 bodies" number, split by whether each body
     disagrees with the doc or is merely partial.

What it does NOT prove: bytes. Only resolvecheck/verify_idx/gate do. This is a
vocabulary check on already-matched files; it never touches a worker's
candidate (those live under scratchpad/, this scans src/ and libs/).

ponytail: binding is by offset+width coincidence with a threshold, not by
route. Two unrelated objects that share two field widths at two offsets will
bind falsely; when that shows up, add the offset as `excluded` on the wrong
object or raise the threshold. The census (offset_census.py) is the route-level
truth if a binding is disputed.
"""
import os
import re
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import vocab

ROOT = vocab.ROOT
PAD = re.compile(r"^(?:_*pad|_pad|unk|reserved|_)\w*$|^_[0-9a-f]+$", re.I)


def tree_files(module=None):
    out = []
    for base in ("src", "libs"):
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, base)):
            dirnames[:] = [d for d in dirnames if d not in ("asm_stubs", "nonmatching")]
            if module and ("/%s/" % module) not in (dirpath.replace("\\", "/") + "/"):
                continue
            for fn in filenames:
                if fn.endswith(".c"):
                    out.append(os.path.join(dirpath, fn))
    return sorted(out)


def flatten(st, structs, base=0, depth=0):
    """(abs_off, Member, is_composite) for every member, sub-structs expanded.

    The composite itself is yielded first, then its children: a `VecFx32 vecPos`
    at 0x48c must be judged as 12 bytes against the doc's VecFx32, not as three
    ints against it (that produced 32 false FAILs in ov022 on the first run),
    while a `struct Charge charge` at 0x2770 whose size the doc does not know is
    judged by its first member.
    """
    out = []
    for m in st.members:
        sub = None
        if m.type.startswith("struct ") and m.type[7:] in structs:
            sub = structs[m.type[7:]]
        elif m.type in structs:
            sub = structs[m.type]
        if sub is not None and sub is not st and depth < 4 and sub.complete and not m.bitfield and m.width == sub.size:
            out.append((base + m.off, m, True, depth))
            out += flatten(sub, structs, base + m.off, depth + 1)
            continue
        if sub is not None and not sub.complete:
            continue           # a member whose type we could not lay out claims nothing
        out.append((base + m.off, m, False, depth))
    return out


def matches(fields, accesses):
    """(confirmed/tentative hits, seen hits, highest matched offset) for (off, width) pairs."""
    ct = seen = 0
    hi = -1
    for off, w in accesses:
        f = fields.get(off)
        if f is None or f.status == "excluded" or f.width != w:
            continue
        if f.status == "confirmed" or (f.status == "tentative" and off >= 0x40):
            ct += 1          # a tentative byte at 0x8 is where unrelated objects coincide
        else:
            seen += 1
        hi = max(hi, off)
    return ct, seen, hi


def bound(ct, seen, hi):
    """Two named fields with one past 0x40, or three named fields.
    Small offsets are where unrelated objects coincide (a u64 at 0, a byte at 9):
    the first run bound a 0x30-byte packet struct to Actor on exactly that."""
    return (ct >= 2 and hi >= 0x40) or ct >= 3 or (ct >= 1 and seen >= 2 and hi >= 0x40)


def confirmed_conflict(fields, accesses):
    """A width that contradicts a CONFIRMED (ROM-proven) field: a struct with a
    4-byte word at 0x0 is not an Actor, whatever else it shares."""
    return any(off in fields and fields[off].status == "confirmed" and fields[off].width != w
               for off, w in accesses)


def best_object(objs, accesses):
    best, score = None, (0, 0)
    for o in objs.values():
        ct, seen, hi = matches(o.fields, accesses)
        if bound(ct, seen, hi) and (ct, seen) > score and not confirmed_conflict(o.fields, accesses):
            best, score = o, (ct, seen)
    return best


def lint_file(path, objs, aliases, strict, want_info):
    rel = os.path.relpath(path, ROOT).replace("\\", "/")
    try:
        text = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return []
    findings = []          # (level, line, message)
    structs = vocab.file_structs(text)
    canon_names = {o.name: {f.name: off for off, f in o.fields.items()
                            if f.status in ("confirmed", "tentative")} for o in objs.values()}
    bindings = {}

    for name, st in structs.items():
        if not st.members:
            continue
        flat = [(off, m, comp, d) for off, m, comp, d in flatten(st, structs) if not PAD.match(m.name)]
        obj = aliases.get(name)
        how = "name"
        if obj is None:
            obj = best_object(objs, [(off, m.width) for off, m, _c, _d in flat])
            how = "shape"
        if obj is None:
            continue
        bindings[name] = (obj, how)
        names = canon_names[obj.name]
        mine = []
        covered = []           # (start, end) of composites that matched a doc field
        for off, m, comp, depth in flat:
            if any(a <= off < b for a, b in covered):
                continue       # inside a composite the doc already accepted whole
            f = obj.fields.get(off)
            if comp:
                if f is not None and f.status != "excluded" and f.width == m.width:
                    covered.append((off, off + m.width))
                    if m.name != f.name and f.status in ("confirmed", "tentative"):
                        mine.append(("WARN", 0, "struct %s.%s at 0x%x: %s calls it %s (%s)|%s" %
                                     (name, m.name, off, obj.name, f.name, f.status, m.name)))
                continue       # otherwise judge the children
            if f is None:
                # a canonical name at the wrong offset is a lie, whatever sits there --
                # for a DIRECT member; a sub-struct's own `nId` is its own business
                if depth == 0 and m.name in names and names[m.name] != off:
                    mine.append(("FAIL", 0, "struct %s.%s at 0x%x: %s.%s is 0x%x" %
                                     (name, m.name, off, obj.name, m.name, names[m.name])))
                continue
            if f.status == "excluded":
                mine.append(("FAIL", 0, "struct %s.%s at 0x%x: not a %s field (%s) -- this struct mixes two objects" %
                                 (name, m.name, off, obj.name, f.name)))
                continue
            if m.bitfield and f.type.startswith("bits"):
                pass
            elif m.width != f.width:
                # a `seen` word is "something 4 bytes wide was read here", so a
                # VecFx32 or a byte there is a WARN; a named field's width is a FAIL
                mine.append(("FAIL" if f.status != "seen" else "WARN", 0, "struct %s.%s at 0x%x: width %d, %s.%s is %s (%d)" %
                                 (name, m.name, off, m.width, obj.name, f.name, f.type, f.width)))
                continue
            if f.sign in "us" and m.sign in "us" and m.sign != f.sign and not m.bitfield:
                # ldrsb/ldrb and ldrsh/ldrh differ in the ROM; ldr is ldr. A word's
                # sign is a claim about meaning, so it only warns.
                mine.append(("FAIL" if f.width <= 2 else "WARN", 0, "struct %s.%s at 0x%x: %s, %s.%s is %s" %
                                 (name, m.name, off, m.type, obj.name, f.name, f.type)))
                continue
            if f.status == "seen":
                if want_info and not re.match(r"^field_?[0-9a-fA-F]+$", m.name) and not m.bitfield:
                    mine.append(("INFO", 0, "struct %s.%s at 0x%x: %s.%s is unnamed in the doc -- proposal candidate" %
                                     (name, m.name, off, obj.name, f.name)))
            elif m.name != f.name and not m.bitfield and not f.name.startswith("("):
                lvl = "FAIL" if strict and f.status == "confirmed" else "WARN"
                mine.append((lvl, 0, "struct %s.%s at 0x%x: %s calls it %s (%s)|%s" %
                                 (name, m.name, off, obj.name, f.name, f.status, m.name)))
        nfail = sum(1 for l, _l, _m in mine if l == "FAIL")
        ct, seen, _hi = matches(obj.fields, [(off, m.width) for off, m, _c, _d in flat])
        if how == "shape" and nfail > ct + seen:
            # more disagreement than agreement: the resemblance is the coincidence,
            # not the conflicts. One line, not a FAIL per member.
            findings.append(("WARN", 0, "struct %s: resembles %s at %d offset(s) but conflicts at %d -- probably a different object" %
                             (name, obj.name, ct + seen, nfail)))
            del bindings[name]
        else:
            findings += mine
            if how == "name" and ct + seen == 0 and nfail:
                findings.append(("FAIL", 0, "struct %s: named like %s but shares no field with it" % (name, obj.name)))

    # raw casts, per base expression
    casts = vocab.raw_casts(text)
    by_base = defaultdict(list)
    for c in casts:
        if c.width:
            by_base[c.base].append(c)
    for base, cs in by_base.items():
        obj = best_object(objs, [(c.off, c.width) for c in cs])
        if obj is None:
            continue
        bindings["<%s>" % base] = (obj, "cast")
        n_named = 0
        for c in cs:
            f = obj.fields.get(c.off)
            if f is None:
                continue
            if f.status == "excluded":
                findings.append(("FAIL", c.line, "%s: not a %s field (%s)" % (c.text, obj.name, f.name)))
            elif c.width != f.width:
                findings.append(("FAIL" if f.status != "seen" else "WARN", c.line, "%s: width %d, %s.%s is %s" % (c.text, c.width, obj.name, f.name, f.type)))
            elif f.sign in "us" and c.sign in "us" and c.sign != f.sign:
                lvl = "WARN" if (c.store or f.width > 2) else "FAIL"
                findings.append((lvl, c.line, "%s: %s store, %s.%s is %s" % (c.text, "unsigned" if c.sign == "u" else "signed", obj.name, f.name, f.type)
                                 if c.store else "%s: sign differs from %s.%s (%s)" % (c.text, obj.name, f.name, f.type)))
            else:
                n_named += 1
        if want_info and n_named:
            findings.append(("INFO", 0, "base `%s` is %s: %d raw cast(s) could be named fields (struct_apply.py)" % (base, obj.name, n_named)))
    return [(lvl, rel, line, msg) for lvl, line, msg in findings], bindings


def main(argv):
    args = list(argv)
    if not args or "--help" in args:
        print(__doc__)
        return 2

    def opt(flag, default=None):
        if flag in args:
            k = args.index(flag)
            v = args[k + 1]
            del args[k:k + 2]
            return v
        return default
    doc = opt("--doc", vocab.DOC)
    module = opt("--module")
    skip = opt("--skip")
    strict = "--strict" in args
    summary = "--summary" in args
    want_info = "--info" in args
    all_files = "--all" in args
    for f in ("--strict", "--summary", "--info", "--all"):
        while f in args:
            args.remove(f)
    objs = vocab.parse_doc(doc)
    aliases = vocab.alias_index(objs)

    if all_files or module:
        files = tree_files(module)
    else:
        files = [os.path.abspath(a) for a in args]
    if skip:
        skipset = {os.path.abspath(l.strip()) for l in open(skip[1:] if skip.startswith("@") else skip) if l.strip()}
        files = [f for f in files if os.path.abspath(f) not in skipset]
    for f in files:
        if "scratchpad" in f.replace("\\", "/").split("/"):
            print("refusing %s: candidate files are not landed C" % f)
            return 2

    counts = Counter()
    per_alias = defaultdict(Counter)
    kinds = Counter()
    other_names = defaultdict(Counter)     # "Obj.field" -> names files use instead
    for p in files:
        res = lint_file(p, objs, aliases, strict, want_info)
        if not res:
            continue
        findings, bindings = res
        failed_structs = {re.match(r"struct (\w+)", m).group(1) for l, _r, _ln, m in findings if l == "FAIL" and m.startswith("struct ")}
        for name, (obj, how) in bindings.items():
            key = "%s->%s" % (name, obj.name)
            per_alias[key]["conflict" if name in failed_structs else "consistent"] += 1
        for lvl, rel, line, msg in findings:
            if "|" in msg:
                msg, alt = msg.rsplit("|", 1)
                cm = re.search(r"(\w+) calls it (\w+)", msg)
                if cm:
                    other_names["%s.%s" % (cm.group(1), cm.group(2))][alt] += 1
            counts[lvl] += 1
            kinds[(lvl, msg.split(":")[-1].strip()[:40] if lvl != "INFO" else "info")] += 1
            if not summary:
                print("%-4s %s%s  %s" % (lvl, rel, ":%d" % line if line else "", msg))

    print()
    print("files scanned: %d   FAIL=%d WARN=%d INFO=%d" % (len(files), counts["FAIL"], counts["WARN"], counts["INFO"]))
    if summary or all_files or module:
        print("\nbindings (local struct or <cast base> -> object): consistent / conflicting")
        for key, c in sorted(per_alias.items(), key=lambda kv: -sum(kv[1].values()))[:25]:
            print("  %-40s %5d / %d" % (key, c["consistent"], c["conflict"]))
        print("\nmost common findings:")
        for (lvl, k), n in kinds.most_common(12):
            print("  %-4s %4d  %s" % (lvl, n, k))
        if other_names:
            print("\nother names the tree uses for a doc field (evidence for renames, or for the doc):")
            for key, c in sorted(other_names.items(), key=lambda kv: -sum(kv[1].values()))[:15]:
                print("  %-24s %s" % (key, " ".join("%s=%d" % kv for kv in c.most_common(5))))
    return 1 if counts["FAIL"] else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
