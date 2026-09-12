#!/usr/bin/env python3
"""map_structural_diff.py -- fold overlay_identity.json into docs/OVERLAY_GAMEPLAY_MAP.md.

    build/venv/Scripts/python.exe tools/map_structural_diff.py [--apply]

Sibling of tools/update_gameplay_map.py, same row regex, opposite contract: that tool
refreshes the numeric columns and never touches the hand-curated role/clue text; this
one touches ONLY the role text, and only in two ways:

  1. a placeholder role ("Exact in-game identity not established from this scan.",
     "Exact role not established.") is REPLACED by the structural fact;
  2. any other role gets the structural fact APPENDED as its own sentence, and the
     character rows' "exact use of this copy unconfirmed" clause is replaced by the
     group/slot fact it was standing in for.

The Source clue column is never edited. Default is a unified diff on stdout and a
count; --apply writes the file. It also cross-checks the map's own character names
against the group table (all overlays of one group must carry the same name) and
refuses to write if they disagree.
"""
import difflib
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
MAP = os.path.join(ROOT, "docs", "OVERLAY_GAMEPLAY_MAP.md")
IDENT = os.path.join(ROOT, "build", "overlay_identity.json")
MAP_ROW = re.compile(r"^\| (\S+) \| ([\d.]+%) \| (\d+) \| (.*?) \| (.*) \|$")
PLACEHOLDERS = ("Exact in-game identity not established from this scan.",
                "Exact role not established.")
COPY_CLAUSE = "; exact use of this copy unconfirmed."
NAME_RE = re.compile(r"^([A-Z][a-z]+)-specific character support")

STRUCT_NOTE = ("Structural facts (scene id, panel slot, character group/slot, enemy roster "
               "index/slot) come from four ROM tables read by "
               "`tools/overlay_identity.py`: `g_SceneTable` "
               "(`src/calls/func_0202099c.c`), the ov002 panel table "
               "(`src/overlays/ov002/calls/func_ov002_0207689c.c`), the ov029 group table "
               "(`src/overlays/ov029/calls/func_ov029_020b2ee0.c`) and the ov107 roster table "
               "(`src/overlays/ov107/calls/func_ov107_020c0680.c`). A structural fact says "
               "which table slot loads the overlay, not what the player sees. Character and "
               "enemy slots are memory slots (fixed load addresses, allocated first-free), "
               "not player numbers.")


def fact(rec):
    k = rec["kind"]
    if k == "scene":
        return "Scene id %d in g_SceneTable (class descriptor %s)." % (rec["key"], rec["class_desc"])
    if k == "panel":
        return "Panel slot %d of 14 in the ov002 panel table." % rec["key"]
    if k == "character":
        return "Character roster: group %d, memory slot %d of 4 (this group has %d slot%s)." % (
            rec["group"], rec["slot"], rec["slots_in_group"], "" if rec["slots_in_group"] == 1 else "s")
    if k == "enemy":
        s = "Enemy roster index %d (archive `%s`), memory slot %d of 6" % (
            rec["index"], rec["ms_archive"] or "Ms/%02X.p missing from ROM" % rec["index"], rec["slot"])
        if rec["slots_for_index"] > 1:
            s += ", one of %d slot copies" % rec["slots_for_index"]
        return s + "."
    if k == "slot_primer":
        return "Enemy memory-slot primer %d of 6, loaded once by func_ov107_020c0680." % rec["key"]
    return None


def new_role(role, rec):
    f = fact(rec)
    if f is None:
        return role
    if role in PLACEHOLDERS:
        return f
    if role.endswith(COPY_CLAUSE):
        return role[:-len(COPY_CLAUSE)] + ". " + f
    if f in role:
        return role
    return role + " " + f


def main(argv):
    ident = json.load(open(IDENT, encoding="utf-8"))
    recs = {"ov%03d" % r["overlay"]: r for r in ident["overlays"]}
    old = open(MAP, encoding="utf-8").read().split("\n")
    new = list(old)
    changed = 0
    replaced = 0
    group_names = {}
    for i, line in enumerate(old):
        m = MAP_ROW.match(line)
        if not m:
            if line.startswith("Character names below come from explicit strings") and STRUCT_NOTE not in line:
                new[i] = line + " " + STRUCT_NOTE
                changed += 1
            continue
        mod, pct, outside, role, clue = m.groups()
        rec = recs.get(mod)
        if not rec:
            continue
        if rec["kind"] == "character":
            nm = NAME_RE.match(role)
            group_names.setdefault(rec["group"], set()).add(nm.group(1) if nm else "?")
        role2 = new_role(role, rec)
        if role2 != role:
            changed += 1
            if role in PLACEHOLDERS:
                replaced += 1
            new[i] = "| %s | %s | %s | %s | %s |" % (mod, pct, outside, role2, clue)
    bad = {g: n for g, n in group_names.items() if len(n) != 1}
    if bad:
        sys.exit("map character names disagree inside a group table row: %r" % bad)
    missing = [m for m in recs if recs[m]["kind"] != "other"
               and not any(MAP_ROW.match(l) and MAP_ROW.match(l).group(1) == m for l in old)]
    diff = difflib.unified_diff(old, new, "docs/OVERLAY_GAMEPLAY_MAP.md", "docs/OVERLAY_GAMEPLAY_MAP.md (structural)", lineterm="")
    if "--apply" in argv:
        open(MAP, "w", encoding="utf-8", newline="\n").write("\n".join(new))
        print("applied")
    else:
        sys.stdout.write("\n".join(diff) + "\n")
    print("rows changed: %d (placeholder replaced: %d, fact appended: %d); "
          "group-name check: %d groups consistent" % (changed - 1 if changed else 0, replaced, changed - 1 - replaced, len(group_names)),
          file=sys.stderr)
    if missing:
        print("identified overlays with no map row (nothing to update): %s" % ", ".join(sorted(missing)), file=sys.stderr)


if __name__ == "__main__":
    main(sys.argv[1:])
