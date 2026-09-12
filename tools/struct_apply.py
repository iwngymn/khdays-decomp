#!/usr/bin/env python3
"""struct_apply.py -- turn `*(T *)(BASE + 0xN)` into a named field, bytes unchanged.

    python tools/struct_apply.py --object AiState --scratch DIR <file.c> ...
    python tools/struct_apply.py --object AiState --dry-run <file.c> ...
    python tools/struct_apply.py --object AiState --write <file.c> ...
    options: --doc PATH   --skip @list.txt

For each file that has a raw-cast base BOUND to the object (same rule as
struct_lint.py), every `*(T *)(BASE + 0xN)` whose N is a doc field of the same
width and signedness becomes `((struct OBJ *)(BASE))->name`, and a partial
`struct OBJ { ... }` holding exactly the fields this file uses (with pads) is
inserted above the first extern / function. The file's own base-type typedefs
are not relied on: fields are spelled `unsigned char`, `short`, `int`, ...

Nothing is written to the tree until tools/verify_idx.py has graded the
rewritten text byte-exact against build/func_index.json, in a scratch copy.
--scratch keeps every copy (`<stem>.c` rewritten, `<stem>.orig.c`) for review;
--write copies a verified rewrite over the real file, and only then. A file
that does not verify BEFORE the rewrite is refused: that is the one signal
that it is not landed, matched C (an in-flight target, a nonmatching draft),
and this tool must never touch those.

Left alone, and reported as such:
  * `((struct hw60 *)(BASE + 0x60))->hi`  -- already a named access via a
    codegen device; rewriting it needs the device inside the object struct
  * a cast whose width or sign disagrees with the doc (struct_lint.py's job)
  * a cast at an offset the doc has not got
  * a `ptr` field read as `*(int *)` -- retyping it to a pointer changes the
    meaning of the arithmetic around it, not just the spelling
  * files that already declare a struct for this object (merge by hand)
  * files whose function is not in func_index, or not under src/ or libs/

ponytail: text substitution, one object per run, no retyping of the base
variable. Upgrade path: retype `int *ctx` to `struct AiState **` when the
whole file is on one object -- that is a readability pass, not a mechanical one.
"""
import os
import re
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import vocab
import struct_lint

ROOT = vocab.ROOT
sys.path.insert(0, os.path.join(ROOT, "tools"))
import verify_idx      # noqa: E402  (tools/verify_idx.py, the project's strict per-function check)

C_TYPE = {"u8": "unsigned char", "s8": "signed char", "u16": "unsigned short", "s16": "short",
          "u32": "unsigned int", "s32": "int", "fx32": "int", "u64": "unsigned long long",
          "s64": "long long", "bits8": "unsigned char", "bits16": "unsigned short",
          "bits32": "unsigned int", "ptr": "void *", "word": "int"}
CAST_SIGN = {"char": "s", "signed char": "s", "s8": "s", "unsigned char": "u", "u8": "u",
             "short": "s", "signed short": "s", "s16": "s", "unsigned short": "u", "u16": "u",
             "int": "s", "signed int": "s", "s32": "s", "long": "s", "fx32": "s",
             "unsigned int": "u", "unsigned": "u", "u32": "u", "unsigned long": "u",
             "long long": "s", "s64": "s", "unsigned long long": "u", "u64": "u"}


def compatible(cast, field):
    if field.status == "excluded" or field.type == "ptr" or field.type == "VecFx32":
        return False
    if cast.width != field.width:
        return False
    if field.sign in "us" and cast.sign in "us" and cast.sign != field.sign:
        return False
    return True


def struct_text(obj, offs):
    lines = ["/* Partial %s, fields from STRUCTS.md; pads are not claims about the object. */" % obj.name,
             "struct %s {" % obj.name]
    cur = 0
    for off in sorted(offs):
        f = obj.fields[off]
        if off > cur:
            lines.append("    unsigned char pad%03x[0x%x];" % (cur, off - cur))
        lines.append("    %s %s;%s/* 0x%03x */" % (C_TYPE[f.type], f.name, " " * max(1, 28 - len(C_TYPE[f.type]) - len(f.name)), off))
        cur = off + f.width
    lines.append("};")
    return "\n".join(lines) + "\n\n"


def insertion_point(text):
    """Line index of the first extern or function definition at column 0."""
    lines = text.splitlines(keepends=True)
    for i, ln in enumerate(lines):
        if re.match(r"^(extern\b|static\b|[A-Za-z_][\w \*]*\b\w+\s*\([^;]*$)", ln) and not ln.startswith(("typedef", "struct", "#")):
            return i
    return len(lines)


def rewrite(text, obj, aliases):
    """(new_text, done, left) or (None, reason, [])."""
    structs = vocab.file_structs(text)
    for name, st in structs.items():
        if name in aliases and aliases[name] is obj:
            return None, "already declares struct %s; merge by hand" % name, []
        flat = [(off, m) for off, m, _c, _d in struct_lint.flatten(st, structs) if not struct_lint.PAD.match(m.name)]
        if struct_lint.best_object({obj.name: obj}, [(o, m.width) for o, m in flat]) is obj:
            return None, "already declares %s (shape-bound) for this object; merge by hand" % name, []
    casts = vocab.raw_casts(text)
    by_base = {}
    for c in casts:
        if c.width:
            by_base.setdefault(c.base, []).append(c)
    todo, left = [], []
    for base, cs in by_base.items():
        if struct_lint.best_object({obj.name: obj}, [(c.off, c.width) for c in cs]) is not obj:
            continue
        for c in cs:
            f = obj.fields.get(c.off)
            if f is None:
                left.append((c, "offset not in doc"))
            elif not c.text.startswith("*"):
                left.append((c, "device access (->%s), needs the device in the struct" % f.name))
            elif not compatible(c, f):
                left.append((c, "disagrees with doc (%s %s) -- struct_lint.py" % (f.type, f.name)))
            else:
                todo.append((c, f))
    if not todo:
        return None, "no raw cast on a base bound to %s" % obj.name if not left else "nothing rewritable (%d left)" % len(left), left
    code = vocab.strip_comments(text)
    # replace from the end so earlier spans keep their positions
    spans = []
    for c, f in todo:
        for m in re.finditer(re.escape(c.text), code):
            spans.append((m.start(), m.end(), c, f))
    spans = sorted(set(spans), reverse=True)
    out = text
    seen = set()
    for a, b, c, f in spans:
        if (a, b) in seen:
            continue
        seen.add((a, b))
        inner = c.text[c.text.index("(", c.text.index("*)") + 2) + 1:-1]     # `BASE + 0xN`
        base_src = inner[:inner.rfind("+")].strip()
        out = out[:a] + "((struct %s *)(%s))->%s" % (obj.name, base_src, f.name) + out[b:]
    lines = out.splitlines(keepends=True)
    k = insertion_point(out)
    lines.insert(k, struct_text(obj, {f.off for _c, f in todo}))
    return "".join(lines), len(seen), left


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
    objname = opt("--object")
    scratch = opt("--scratch")
    skip = opt("--skip")
    dry = "--dry-run" in args
    write = "--write" in args
    for f in ("--dry-run", "--write"):
        while f in args:
            args.remove(f)
    if not objname or not (dry or write or scratch):
        print("need --object NAME and one of --dry-run / --scratch DIR / --write")
        return 2
    objs = vocab.parse_doc(doc)
    aliases = vocab.alias_index(objs)
    obj = objs[objname]
    files = [os.path.abspath(a) for a in args]
    if skip:
        skipset = {os.path.abspath(l.strip()) for l in open(skip[1:] if skip.startswith("@") else skip) if l.strip()}
        files = [f for f in files if f not in skipset]
    if scratch:
        os.makedirs(scratch, exist_ok=True)
    idx = verify_idx._index()

    tally = {"rewritten": 0, "reverted": 0, "skipped": 0}
    for p in files:
        rel = os.path.relpath(p, ROOT).replace("\\", "/")
        stem = os.path.splitext(os.path.basename(p))[0]
        if not rel.startswith(("src/", "libs/")) or "/nonmatching/" in rel or "/asm_stubs/" in rel:
            print("SKIP  %s: not landed C" % rel); tally["skipped"] += 1; continue
        if stem not in idx:
            print("SKIP  %s: not in func_index" % rel); tally["skipped"] += 1; continue
        text = open(p, encoding="utf-8", errors="replace").read()
        new, done, left = rewrite(text, obj, aliases)
        if new is None:
            print("SKIP  %s: %s" % (rel, done)); tally["skipped"] += 1
            for c, why in left[:4]:
                print("        left %s: %s" % (c.text, why))
            continue
        if dry:
            import difflib
            print("---- %s: %d cast(s) rewritten, %d left" % (rel, done, len(left)))
            sys.stdout.writelines(difflib.unified_diff(text.splitlines(True), new.splitlines(True), "a/" + rel, "b/" + rel, n=1))
            continue
        thumb = idx[stem]["mode"] == "thumb"
        work = scratch or os.path.join(os.environ.get("TEMP", "/tmp"), "struct_apply")
        os.makedirs(work, exist_ok=True)
        orig_copy = os.path.join(work, stem + ".orig.c")
        new_copy = os.path.join(work, stem + ".c")
        shutil.copy(p, orig_copy)
        try:
            rc0, _v0 = verify_idx.check(orig_copy, stem, thumb)
        except SystemExit as exc:
            rc0, _v0 = 2, str(exc.code)
        if rc0 != 0:
            print("SKIP  %s: does not verify BEFORE the rewrite -- not touching it" % rel); tally["skipped"] += 1
            continue
        open(new_copy, "w", encoding="utf-8").write(new)
        try:
            rc, verdict = verify_idx.check(new_copy, stem, thumb)
        except SystemExit as exc:
            rc, verdict = 2, str(exc.code)
        if rc == 0:
            tally["rewritten"] += 1
            print("OK    %s: %d cast(s) -> fields, %d left, bytes identical%s" % (rel, done, len(left), "; WRITTEN" if write else ""))
            if write:
                shutil.copy(new_copy, p)
        else:
            tally["reverted"] += 1
            print("REVERT %s: %d cast(s) rewritten but %s" % (rel, done, verdict.splitlines()[0]))
            if scratch:
                os.replace(new_copy, os.path.join(work, stem + ".FAILED.c"))
        for c, why in left[:4]:
            print("        left %s: %s" % (c.text, why))
    print("\n%s" % "  ".join("%s=%d" % kv for kv in tally.items()))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
