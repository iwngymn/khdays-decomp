#!/usr/bin/env python3
"""brief_structs.py -- the vocabulary section a worker brief gets for one target.

    python tools/brief_structs.py <func_name>

Prints nothing when the target touches no known object, so brief.py can append
the output unconditionally. Decides "touches" from the ROM, not from any C:
the target's own instructions (offset_census.py, cached) give every field
access as ROUTE + OFFSET + WIDTH, and an object is reported when

  * the route is one of the object's `routes:` lines in STRUCTS.md, and at least
    one access lands on a doc field with the right width, or
  * the accesses on one route shape-bind to the object (struct_lint.py's rule).

For each object the worker gets: which of its accesses are doc fields (name,
status, type), a partial `struct` to paste that holds exactly those fields
with pads (hermetic, no #include; the doc's names, so the file agrees with
the tree without the worker knowing the tree), and the accesses on that route
the doc does not know, which the worker declares as `field_XXX` and lists
under `struct-proposals:` in its report.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import vocab
import struct_lint
import offset_census
import struct_apply

try:
    sys.stdout.reconfigure(errors="replace")
except Exception:
    pass


def section(name, objs=None):
    objs = objs or vocab.parse_doc()
    rows = offset_census.census().get(name)
    if not rows:
        return ""
    by_route = {}
    for _o, route, off, w, s, rw in rows:
        if route == "?":
            continue
        by_route.setdefault(route, {}).setdefault((off, w), set()).add(rw)
    out = []
    for route, accs in by_route.items():
        keys = sorted(accs)
        for obj in objs.values():
            named = [(off, w) for off, w in keys if off in obj.fields and obj.fields[off].status != "excluded" and obj.fields[off].width == w]
            if route in obj.routes and named:
                pass
            elif struct_lint.best_object({obj.name: obj}, keys) is not obj:
                continue
            excluded = [off for off, w in keys if off in obj.fields and obj.fields[off].status == "excluded"]
            unknown = sorted({(off, w) for off, w in keys if (off, w) not in named and off not in obj.fields})
            out.append("%s via %s  (%d of %d accesses on this route are doc fields)" % (obj.name, route, len(named), len(keys)))
            for off, w in named:
                f = obj.fields[off]
                out.append("  +0x%-4x %-6s %-18s %s  %s" % (off, f.type, f.name, f.status, "/".join(sorted(accs[(off, w)]))))
            if excluded:
                out.append("  NOTE: +%s reached on this route but the doc marks them NOT %s -- the route may be a different object here; say so in the report"
                           % (", +".join("0x%x" % o for o in excluded), obj.name))
            out.append("  paste this partial struct as-is (names from STRUCTS.md; do not rename):")
            out += ["    " + ln for ln in struct_apply.struct_text(obj, {off for off, _w in named}).rstrip().splitlines()]
            if unknown:
                out.append("  on this route but NOT in the doc: " + ", ".join("+0x%x (%s%d)" % (off, "/".join(sorted(accs[(off, w)])), w) for off, w in unknown))
                out.append("  declare those as field_XXX in your struct; if you learn what one is, put it under struct-proposals: in your report")
    if not out:
        return ""
    return "\n## canonical objects this function touches (STRUCTS.md)\n" + "\n".join(out) + "\n"


if __name__ == "__main__":
    sys.stdout.write(section(sys.argv[1]) or "(no known object)\n")
