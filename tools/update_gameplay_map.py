#!/usr/bin/env python3
"""update_gameplay_map.py -- refresh docs/OVERLAY_GAMEPLAY_MAP.md's numeric columns from PROGRESS.md.

    python tools/update_gameplay_map.py [--check]

Per the map's own "Maintaining this map" section: copy each module's C% and
recompute Outside C (= Total - C matched) from PROGRESS.md, update the
snapshot date. The role/source-clue columns are hand-curated evidence and are
never touched here -- this only fixes arithmetic that PROGRESS.md already
knows, matching what tools/progress.py does for PROGRESS.md itself.

--check: exit 1 if the map is stale (would change), without writing. For a
pre-commit habit, not a build step.
"""
import datetime
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
PROGRESS = os.path.join(ROOT, "PROGRESS.md")
MAP = os.path.join(ROOT, "docs", "OVERLAY_GAMEPLAY_MAP.md")

PROGRESS_ROW = re.compile(
    r"^\| (?:DONE|PART) (\S+) \| (\d+) \| \d+ \| \d+ \| \d+ \| (\d+) \| ([\d.]+%) \|$"
)
MAP_ROW = re.compile(r"^\| (\S+) \| ([\d.]+%) \| (\d+) \| (.*) \|$")
SNAPSHOT_LINE = re.compile(r"^Snapshot taken \d{4}-\d{2}-\d{2} from .*$")


def load_progress():
    stats = {}
    for line in open(PROGRESS, encoding="utf-8"):
        m = PROGRESS_ROW.match(line.rstrip("\n"))
        if m:
            mod, c_matched, total, pct = m.groups()
            stats[mod] = (int(c_matched), int(total), pct)
    return stats


def refresh(check=False):
    stats = load_progress()
    lines = open(MAP, encoding="utf-8").read().split("\n")
    changed = False
    missing = []
    for i, line in enumerate(lines):
        if SNAPSHOT_LINE.match(line):
            today = datetime.date.today().isoformat()
            new = ("Snapshot taken %s from [PROGRESS.md](../PROGRESS.md). Treat every "
                   "percentage here as a dated snapshot and PROGRESS.md as authoritative. "
                   "All 298 listed modules are included. These percentages measure "
                   "functions reconstructed in matching C, not gameplay understood, code "
                   "size, or difficulty. This is a documentation snapshot, not a new ROM "
                   "verification; use PROGRESS.md for current counts.") % today
            if line != new:
                changed = True
                lines[i] = new
            continue
        m = MAP_ROW.match(line)
        if not m:
            continue
        mod, old_pct, old_outside, rest = m.groups()
        if mod not in stats:
            missing.append(mod)
            continue
        c_matched, total, pct = stats[mod]
        outside = total - c_matched
        new_line = "| %s | %s | %d | %s |" % (mod, pct, outside, rest)
        if new_line != line:
            changed = True
            lines[i] = new_line
    if missing:
        print("warning: %d map row(s) have no PROGRESS.md match, left as-is: %s"
              % (len(missing), ", ".join(missing[:10])), file=sys.stderr)
    if check:
        return 1 if changed else 0
    if changed:
        open(MAP, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
        print("updated" if changed else "already current")
    else:
        print("already current")
    return 0


if __name__ == "__main__":
    sys.exit(refresh(check="--check" in sys.argv[1:]))
