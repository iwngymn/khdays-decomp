#!/usr/bin/env python3
"""vocab.py -- the canonical object vocabulary, and how a C file spells an object.

Shared by struct_lint.py, struct_apply.py and brief_structs.py. Three jobs:

  parse_doc(path)      the vocabulary doc (STRUCTS.md) -> {object name: Obj}
  file_structs(text)   every struct declared in one .c, laid out to byte offsets
  raw_casts(text)      every `*(T *)(BASE + 0xN)` / `((T *)(BASE + 0xN))->f` spelling

Nothing here reads the ROM; offset_census.py does that. This module only reads
text: the doc, and C files. Run it directly for the self-check, which lays out
every struct in the tree and compares the computed offsets against the
`/* 0x.... */` comments the files carry -- if this layout engine disagreed with
hundreds of hand-written comments, the engine would be the thing that is wrong.

    python tools/vocab.py --selfcheck

Doc format (strict on purpose, so a tool can read it):

    ## object NAME
    aliases: A, B, C              names local structs use for this object
    routes: R1 ; R2 ; ...         offset_census.py routes that reach it
    | offset | type | name | status | evidence |
    |---|---|---|---|---|
    | 0x009 | u8 | id | confirmed | ... |

type: u8 s8 u16 s16 u32 s32 u64 s64 word ptr fx32 bits8 bits16 bits32 VecFx32
status: confirmed | tentative | seen | excluded
  seen      the census shows the access, nobody has named it; name is field_XXX
  excluded  the offset is NOT this object's (belongs to another); a local struct
            that binds to this object and declares it is mixing two objects
"""
import os
import re
import sys
from collections import namedtuple

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
DOC = os.path.join(ROOT, "docs-local", "STRUCTS.md")

# type name -> (width, sign, align).  mwcc ARM (APCS): long long is 4-aligned,
# which is why the tree's u64 at 0x464 is followed by a field at 0x46c.
BASE_TYPES = {
    "u8": (1, "u", 1), "unsigned char": (1, "u", 1),
    "s8": (1, "s", 1), "signed char": (1, "s", 1), "char": (1, "s", 1),   # -char signed
    "u16": (2, "u", 2), "unsigned short": (2, "u", 2),
    "s16": (2, "s", 2), "short": (2, "s", 2), "signed short": (2, "s", 2),
    "u32": (4, "u", 4), "unsigned int": (4, "u", 4), "unsigned": (4, "u", 4), "unsigned long": (4, "u", 4),
    "s32": (4, "s", 4), "int": (4, "s", 4), "signed int": (4, "s", 4), "long": (4, "s", 4), "fx32": (4, "s", 4),
    "u64": (8, "u", 4), "unsigned long long": (8, "u", 4),
    "s64": (8, "s", 4), "long long": (8, "s", 4), "signed long long": (8, "s", 4),
    "BOOL": (4, "s", 4), "void": (0, "-", 1),
    "ptr": (4, "-", 4), "VecFx32": (12, "-", 4), "fx16": (2, "s", 2),
    "word": (4, "-", 4),      # a 4-byte field whose sign nobody has established (ldr cannot tell)
    "bits8": (1, "u", 1), "bits16": (2, "u", 2), "bits32": (4, "u", 4),
}

Field = namedtuple("Field", "off type width sign name status evidence")
Obj = namedtuple("Obj", "name aliases routes fields notes")
Member = namedtuple("Member", "off width sign name type comment_off bitfield")
Struct = namedtuple("Struct", "name members size complete align")
Cast = namedtuple("Cast", "base off width sign store line text")


# ------------------------------------------------------------------ the doc
def parse_doc(path=DOC):
    objs = {}
    cur = None
    for raw in open(path, encoding="utf-8"):
        line = raw.rstrip("\n")
        m = re.match(r"^## object\s+(\w+)", line)
        if m:
            cur = Obj(m.group(1), set([m.group(1)]), [], {}, [])
            objs[cur.name] = cur
            continue
        if cur is None:
            continue
        m = re.match(r"^aliases:\s*(.*)$", line)
        if m:
            cur.aliases.update(a.strip() for a in m.group(1).split(",") if a.strip())
            continue
        m = re.match(r"^routes:\s*(.*)$", line)
        if m:
            cur.routes.extend(r.strip() for r in m.group(1).split(";") if r.strip())
            continue
        m = re.match(r"^\|\s*(0x[0-9a-fA-F]+)\s*\|\s*([\w:]+)\s*\|\s*(\S+)\s*\|\s*(\w+)\s*\|(.*)\|\s*$", line)
        if m:
            off = int(m.group(1), 16)
            t = m.group(2)
            status = m.group(4)
            if status == "excluded":
                w, s = 0, "-"
            elif t in BASE_TYPES:
                w, s, _a = BASE_TYPES[t]
            else:
                raise SystemExit("%s: unknown type %r at offset 0x%x" % (path, t, off))
            if status not in ("confirmed", "tentative", "seen", "excluded"):
                raise SystemExit("%s: bad status %r at 0x%x" % (path, status, off))
            cur.fields[off] = Field(off, t, w, s, m.group(3), status, m.group(5).strip())
        elif line.startswith("note:"):
            cur.notes.append(line[5:].strip())
    return objs


def alias_index(objs):
    """struct name -> object, over every alias. Two objects claiming one alias is
    a doc error, and the lint would be unable to bind, so refuse early."""
    out = {}
    for o in objs.values():
        for a in o.aliases:
            if a in out and out[a] is not o:
                raise SystemExit("alias %r claimed by both %s and %s" % (a, out[a].name, o.name))
            out[a] = o
    return out


# ------------------------------------------------------------------ C text
def strip_comments(txt):
    txt = re.sub(r"/\*.*?\*/", lambda m: " " * len(m.group(0)), txt, flags=re.S)
    return re.sub(r"//[^\n]*", lambda m: " " * len(m.group(0)), txt)


STRUCT_RE = re.compile(r"\b(typedef\s+)?struct\s+(\w+)?\s*\{", re.S)
FN_TYPEDEF = re.compile(r"\btypedef\b[^;{]*\(\s*\*\s*(\w+)\s*\)\s*\([^;]*\)\s*;")
ALIAS_TYPEDEF = re.compile(r"\btypedef\s+((?:unsigned|signed|long|short|int|char)(?:\s+(?:unsigned|signed|long|short|int|char))*)\s+(\w+)\s*;")


def _match_brace(txt, i):
    """index just past the '}' matching the '{' at txt[i]."""
    depth = 0
    for k in range(i, len(txt)):
        if txt[k] == "{":
            depth += 1
        elif txt[k] == "}":
            depth -= 1
            if depth == 0:
                return k + 1
    return -1


def file_types(code):
    """The file's own scalar typedefs and function-pointer typedefs."""
    types = dict(BASE_TYPES)
    for m in FN_TYPEDEF.finditer(code):
        types[m.group(1)] = (4, "-", 4)
    for m in ALIAS_TYPEDEF.finditer(code):
        base = " ".join(m.group(1).split())
        if base in BASE_TYPES:
            types[m.group(2)] = BASE_TYPES[base]
    return types


def _split_members(body):
    """Top-level ';'-separated members, nested braces kept whole."""
    out, depth, cur = [], 0, []
    for ch in body:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        if ch == ";" and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    tail = "".join(cur).strip()
    if tail:
        out.append(tail)
    return [m for m in out if m]


def layout(body, types, structs, raw_lines=None):
    """Lay out one struct body. Returns (members, size, complete).

    complete=False when a member's type is unknown: offsets before it are
    right, nothing after it is claimed. A partial answer is honest; a guessed
    one would make the lint report offsets the file never stated.
    """
    members, off, maxalign = [], 0, 1
    bit_unit = None        # (unit_off, unit_width, bits_used, base_type)
    for mem in _split_members(body):
        mem_flat = " ".join(mem.split())
        if mem_flat.startswith("struct ") and "{" in mem_flat:
            return members, off, False, 1          # nested anonymous struct: out of scope
        # `T a, *b, c[4], d : 3;` -- split declarators at top-level commas first.
        # (`unsigned short lo : 8, hi : 8` is the tree's hw60 device, 658 files.)
        pieces, depth, cur = [], 0, []
        for ch in mem_flat:
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            if ch == "," and depth == 0:
                pieces.append("".join(cur).strip())
                cur = []
            else:
                cur.append(ch)
        pieces.append("".join(cur).strip())
        DECL = re.compile(r"^(.*?)\s*(\**)\s*(\w+)\s*((?:\[[^\]]*\])*)\s*(?::\s*(\d+))?$")
        m = DECL.match(pieces[0])
        if not m:
            # function pointer member: RET (*name)(args)
            fm = re.match(r"^.*\(\s*\*\s*(\w+)\s*\)\s*\(.*\)$", mem_flat)
            if fm:
                bit_unit = None
                off = (off + 3) & ~3
                members.append(Member(off, 4, "-", fm.group(1), "fnptr", None, False))
                off += 4
                maxalign = max(maxalign, 4)
                continue
            return members, off, False, 1
        tname = " ".join(m.group(1).replace("const", "").replace("volatile", "").split())
        decls = [(m.group(2), m.group(3), m.group(4), m.group(5))]
        for piece in pieces[1:]:
            pm = re.match(r"^(\**)\s*(\w+)\s*((?:\[[^\]]*\])*)\s*(?::\s*(\d+))?$", piece)
            if not pm:
                return members, off, False, 1
            decls.append(pm.groups())
        if tname in types:
            base_w, base_s, base_a = types[tname]
            tkey = tname
        elif tname.startswith("struct ") and tname[7:] in structs:
            base_w, base_s, base_a, tkey = structs[tname[7:]].size, "-", structs[tname[7:]].align, tname
        elif tname in structs:
            base_w, base_s, base_a, tkey = structs[tname].size, "-", structs[tname].align, "struct " + tname
        elif tname.startswith("enum "):
            base_w, base_s, base_a, tkey = 4, "s", 4, tname
        elif not all(d[0] for d in decls):
            return members, off, False, 1
        else:
            base_w, base_s, base_a, tkey = 0, "-", 1, tname    # only used through pointers
        for stars, nm, dims, bits in decls:
            width, sign, align, key = (4, "-", 4, "ptr") if stars else (base_w, base_s, base_a, tkey)
            if bits is not None:
                nb = int(bits)
                if nb == 0:
                    bit_unit = None
                    continue
                if bit_unit and bit_unit[3] == key and bit_unit[2] + nb <= width * 8:
                    uoff, uw, used, _t = bit_unit
                    bit_unit = (uoff, uw, used + nb, key)
                else:
                    off = (off + align - 1) & ~(align - 1)
                    uoff = off
                    bit_unit = (uoff, width, nb, key)
                    off += width
                    maxalign = max(maxalign, align)
                members.append(Member(uoff, width, sign, nm, key, None, True))
                continue
            bit_unit = None
            count = 1
            for d in re.findall(r"\[([^\]]*)\]", dims):
                d = d.strip()
                try:
                    count *= int(eval(d, {"__builtins__": {}}, {})) if d else 0   # `0x1c7 - 0x62` is common
                except Exception:
                    return members, off, False, 1
            off = (off + align - 1) & ~(align - 1)
            members.append(Member(off, width * count if count > 1 or dims else width, sign, nm, key, None, False))
            off += width * count
            maxalign = max(maxalign, align)
    size = (off + maxalign - 1) & ~(maxalign - 1)
    return members, size, True, maxalign


OFFCOMMENT = re.compile(r"/\*\s*(?:0x)?([0-9a-fA-F]{2,5})\b")


def file_structs(text):
    """{name: Struct} for every struct declared in a C file, in source order."""
    code = strip_comments(text)
    types = file_types(code)
    structs = {}
    pos = 0
    while True:
        m = STRUCT_RE.search(code, pos)
        if not m:
            break
        end = _match_brace(code, m.end() - 1)
        if end < 0:
            break
        body = code[m.end():end - 1]
        tail = code[end:end + 200]
        tm = re.match(r"\s*(\w+)\s*;", tail) if m.group(1) else None
        name = m.group(2) or (tm.group(1) if tm else None)
        pos = end
        if not name:
            continue
        members, size, complete, align = layout(body, types, structs)
        # attach the file's own `/* 0x.... */` comment offsets, when present
        annotated = []
        raw_body = text[m.end():end - 1] if len(text) == len(code) else None
        if raw_body:
            by_name = {}
            for ln in raw_body.splitlines():
                cm = OFFCOMMENT.search(ln)
                nm = re.search(r"(\w+)\s*(?:\[[^\]]*\])*\s*(?::\s*\d+)?\s*;", strip_comments(ln))
                if cm and nm:
                    by_name[nm.group(1)] = int(cm.group(1), 16)
            for mem in members:
                annotated.append(mem._replace(comment_off=by_name.get(mem.name)))
        else:
            annotated = members
        structs[name] = Struct(name, annotated, size, complete, align)
        if m.group(1) and tm and tm.group(1) != name:
            structs[tm.group(1)] = structs[name]
    return structs


# ------------------------------------------------------------------ raw casts
CAST_HEAD = re.compile(r"\*\s*\(\s*((?:const\s+)?(?:struct\s+\w+|unsigned\s+\w+|signed\s+\w+|\w+))\s*\*+\s*\)\s*\(")
ARROW_HEAD = re.compile(r"\(\s*\(\s*((?:struct\s+\w+|unsigned\s+\w+|signed\s+\w+|\w+))\s*\*\s*\)\s*\(")
NOISE_CASTS = re.compile(r"\(\s*(?:int|unsigned|unsigned int|u32|s32|char\s*\*|u8\s*\*|unsigned char\s*\*|signed char\s*\*)\s*\)")


def _balanced(code, i):
    depth = 0
    for k in range(i, len(code)):
        if code[k] == "(":
            depth += 1
        elif code[k] == ")":
            depth -= 1
            if depth == 0:
                return k
    return -1


def norm_base(expr):
    """`(int)owner` / `(char *)b[0]` / `( *ctx )` -> `owner` / `b[0]` / `*ctx`."""
    e = NOISE_CASTS.sub("", expr)
    e = re.sub(r"\s+", "", e)
    while e.startswith("(") and e.endswith(")") and _balanced(e, 0) == len(e) - 1:
        e = e[1:-1]
    return e


def _split_plus(inner):
    """`BASE + 0xN` at the top paren level -> (BASE, N); None otherwise."""
    depth = 0
    last = -1
    for k, ch in enumerate(inner):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "+" and depth == 0:
            last = k
    if last < 0:
        return None
    lhs, rhs = inner[:last].strip(), inner[last + 1:].strip()
    if not re.fullmatch(r"0x[0-9a-fA-F]+|\d+", rhs):
        return None
    return norm_base(lhs), int(rhs, 0)


def raw_casts(text, types=None):
    """Every `*(T *)(BASE + 0xN)` and `((T *)(BASE + 0xN))->f` in a file."""
    code = strip_comments(text)
    types = types or file_types(code)
    structs = file_structs(text)
    out = []
    for head, arrow in ((CAST_HEAD, False), (ARROW_HEAD, True)):
        for m in head.finditer(code):
            open_i = m.end() - 1
            close_i = _balanced(code, open_i)
            if close_i < 0:
                continue
            sp = _split_plus(code[open_i + 1:close_i])
            if not sp:
                continue
            base, off = sp
            t = " ".join(m.group(1).replace("const", "").split())
            if t in types:
                w, s, _a = types[t]
            elif t.startswith("struct ") and t[7:] in structs:
                w, s = structs[t[7:]].size, "-"
            elif t in structs:
                w, s = structs[t].size, "-"
            else:
                w, s = 0, "-"
            after = code[close_i + 1:close_i + 40]
            if arrow:
                am = re.match(r"\s*\)\s*->\s*(\w+)", after)
                if not am:
                    continue
                after = after[am.end():]
                if am.group(1) in ("lo", "hi", "f", "b", "lowByte", "highByte"):
                    pass   # codegen-device member; the width is the device's, already set
            store = bool(re.match(r"\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", after))
            line = code.count("\n", 0, m.start()) + 1
            out.append(Cast(base, off, w, s, store, line, code[m.start():close_i + 1]))
    return out


# ------------------------------------------------------------------ self-check
def _selfcheck():
    """Computed offsets vs. the files' own comments, tree-wide."""
    agree = disagree = 0
    shown = 0
    for base in ("src", "libs"):
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, base)):
            dirnames[:] = [d for d in dirnames if d not in ("asm_stubs", "nonmatching")]
            for fn in filenames:
                if not fn.endswith(".c"):
                    continue
                p = os.path.join(dirpath, fn)
                try:
                    text = open(p, encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                for st in file_structs(text).values():
                    for mem in st.members:
                        if mem.comment_off is None or mem.bitfield:
                            continue        # a bit-field's comment is usually its mask
                        if mem.comment_off == mem.off:
                            agree += 1
                        else:
                            disagree += 1
                            if shown < 15:
                                shown += 1
                                print("  %s: %s.%s computed 0x%x, comment says 0x%x"
                                      % (os.path.relpath(p, ROOT), st.name, mem.name, mem.off, mem.comment_off))
    print("selfcheck: %d member offsets agree with the file's comment, %d disagree" % (agree, disagree))
    return 0 if disagree * 20 < agree else 1


if __name__ == "__main__":
    if "--selfcheck" in sys.argv:
        sys.exit(_selfcheck())
    objs = parse_doc()
    for o in objs.values():
        print("%s: %d fields, aliases %s, routes %s" % (o.name, len(o.fields), sorted(o.aliases), o.routes))
