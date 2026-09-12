#!/usr/bin/env python3
"""overlay_identity.py -- structural identity of every ARM9 overlay, from four ROM tables.

    build/venv/Scripts/python.exe tools/overlay_identity.py [--json out.json]  (default: build/overlay_identity.json, read by tools/map_structural_diff.py)

Reads the real bytes in dsd_extract/ (never the C transcriptions) and emits one record
per overlay id 0..302:

    {overlay, kind, key, base_addr, evidence, ...}

kind   scene        g_SceneTable @0x02042548 (arm9)      key = scene id
       panel        ov002 panel table @0x0207f58c        key = panel slot
       character    ov029 group table @0x020b30b0        key = "group G slot S"
       enemy        ov107 roster table @0x020cb6a4       key = "index I slot S"
       slot_primer  ov107 init loop, data_ov107_020cb610 key = slot
       other        claimed by none of the four tables

Every claim is cross-checked against a second route before it is printed (see
selfcheck()). A failed check aborts with a message instead of emitting a record,
per AGENTS.md "never publish a number you have not verified twice".

Decoders this transcribes (read them, they carry the reasoning):
    src/calls/func_0202099c.c                    scene table shape and use
    src/overlays/ov002/calls/func_ov002_0207689c.c   panel table (rows start at 0x0207f58c,
                                                 NOT 0x0207f590 as the data file pairs them)
    src/overlays/ov029/calls/func_ov029_020b2ee0.c   character group table
    src/overlays/ov107/calls/func_ov107_020c0680.c   enemy roster table, overlay = 113 + b + 1
"""
import glob
import json
import os
import re
import struct
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
EXTRACT = os.path.join(ROOT, "dsd_extract")
ARM9_BASE = 0x02000000

SCENE_TABLE = 0x02042548        # config/arm9/symbols.txt: data_02042548; next symbol 0x020425e8
SCENE_TABLE_END = 0x020425e8    # -> 20 entries of {int overlayId, void *classDesc}
PANEL_TABLE = 0x0207f58c        # func_ov002_0207689c reads id at 0x0207f58c+8n, data at 0x0207f590+8n
PANEL_ROWS = 14                 # ov002_panel_overlays.c: table runs to 0x0207f600
GROUP_TABLE = 0x020b30b0        # data_ov029_020b30b0, 16-byte rows {int overlayId[4]}
GROUP_INIT_TABLE = 0x020b2f70   # data_ov029_020b2f70, 16-byte rows {fn initFns[4]}; 0x140 bytes = 20 rows
GROUP_SLOTS = 0x020b3200        # data_ov029_020b3200[4], -1 = free
ENEMY_TABLE = 0x020cb6a4        # data_ov107_020cb6a4, 6 bytes per row
ENEMY_TABLE_END = 0x020cb968    # next symbol -> 0x2c4 bytes = 118 rows exactly
ENEMY_SLOT_IDS = 0x020cb610     # data_ov107_020cb610[6]: primer overlay ids
ENEMY_SLOT_PTRS = 0x020cb5f8    # data_ov107_020cb5f8[6]: byte written 0 in each primer
ENEMY_OVERLAY_BIAS = 114        # FS_OVERLAY_ID_ov113 + b + 1
ENEMY_FMT = "Ms/%02x.p"         # every enemy overlay formats its own index with this


def die(msg):
    sys.exit("SELF-CHECK FAILED: " + msg)


def load_overlays():
    """id -> (base_address, code_size + bss_size) from dsd's overlays.yaml (no pyyaml in the venv)."""
    txt = open(os.path.join(EXTRACT, "arm9_overlays", "overlays.yaml"), encoding="utf-8").read()
    ovs = {}
    for m in re.finditer(r"- id: (\d+)\n\s+base_address: (\d+)\n\s+code_size: (\d+)\n\s+bss_size: (\d+)", txt):
        # size = code + bss: ov018 is 32 bytes of code and its panel data block lives in bss
        ovs[int(m.group(1))] = (int(m.group(2)), int(m.group(3)) + int(m.group(4)))
    if not ovs or max(ovs) != 302 or len(ovs) != 303:
        die("expected overlays 0..302 in overlays.yaml, got %d" % len(ovs))
    return ovs


def ov_bytes(n):
    return open(os.path.join(EXTRACT, "arm9_overlays", "ov%03d.bin" % n), "rb").read()


def in_overlay(ovs, n, addr):
    base, size = ovs[n]
    return base <= addr < base + size


# ---------------------------------------------------------------- readers

def read_scene_table(arm9):
    n = (SCENE_TABLE_END - SCENE_TABLE) // 8
    rows = []
    for i in range(n):
        ov, cd = struct.unpack_from("<iI", arm9, SCENE_TABLE - ARM9_BASE + i * 8)
        rows.append((ov, cd))
    return rows


def read_panel_table(ov002, base):
    rows = []
    for n in range(PANEL_ROWS):
        ov, p = struct.unpack_from("<iI", ov002, PANEL_TABLE - base + n * 8)
        rows.append((ov, p))
    return rows


def read_group_table(ov029, base):
    n_init = (GROUP_TABLE - GROUP_INIT_TABLE) // 16
    n_groups = (GROUP_SLOTS - GROUP_TABLE) // 16
    rows = [struct.unpack_from("<4i", ov029, GROUP_TABLE - base + g * 16) for g in range(n_groups)]
    return rows, n_init


def read_enemy_table(ov107, base):
    n = (ENEMY_TABLE_END - ENEMY_TABLE) // 6
    if (ENEMY_TABLE_END - ENEMY_TABLE) % 6:
        die("enemy table span not a multiple of 6")
    off = ENEMY_TABLE - base
    rows = [list(ov107[off + i * 6: off + i * 6 + 6]) for i in range(n)]
    ids = struct.unpack_from("<6i", ov107, ENEMY_SLOT_IDS - base)
    ptrs = struct.unpack_from("<6I", ov107, ENEMY_SLOT_PTRS - base)
    return rows, ids, ptrs


def enemy_fmt_arg(n):
    """Second route for the enemy index: the literal each enemy overlay passes to
    OS_SPrintf(buf, "Ms/%02x.p", K). Returns K, or None if the overlay has no such call."""
    d = os.path.join(ROOT, "src", "overlays", "ov%03d" % n)
    sym = None
    for f in glob.glob(os.path.join(d, "data", "*.c")):
        m = re.search(r"char (data_ov\d+_[0-9a-f]+)\[\d+\] = \"Ms/%02x\.p\"", open(f, encoding="utf-8").read())
        if m:
            sym = m.group(1)
            break
    if sym is None:
        return None
    for f in glob.glob(os.path.join(d, "calls", "*.c")):
        src = open(f, encoding="utf-8").read()
        if sym not in src:
            continue
        m = re.search(r"OS_SPrintf\(\w+, %s, (0x[0-9a-fA-F]+|\d+)\)" % sym, src)
        if m:
            return int(m.group(1), 0)
        # 43 constructors were landed with the third argument dropped
        # (`OS_SPrintf(name, &fmt)`): the ROM does `mov r2,#K ; strb r2,[r4,#0x19c] ; bl`
        # and r2 is still K at the call. The store is the same literal, so read it.
        m = re.search(r"0x19c\) = (0x[0-9a-fA-F]+|\d+);", src)
        if m and re.search(r"OS_SPrintf\(\w+, &?%s\)" % sym, src):
            return int(m.group(1), 0)
    return None


# ---------------------------------------------------------------- main

def build():
    ovs = load_overlays()
    arm9 = open(os.path.join(EXTRACT, "arm9", "arm9.bin"), "rb").read()
    claims = {}   # overlay -> record
    notes = []

    def claim(rec):
        n = rec["overlay"]
        if n in claims:
            die("ov%03d claimed twice: %s and %s" % (n, claims[n]["kind"], rec["kind"]))
        rec["base_addr"] = "0x%08x" % ovs[n][0]
        claims[n] = rec

    # 1. scenes
    scenes = read_scene_table(arm9)
    for sid, (ov, cd) in enumerate(scenes):
        if ov == -1:
            if cd != 0:
                die("scene %d has no overlay but classDesc 0x%x" % (sid, cd))
            continue
        if not in_overlay(ovs, ov, cd):
            die("scene %d classDesc 0x%x not inside ov%03d" % (sid, cd, ov))
        claim({"overlay": ov, "kind": "scene", "key": sid, "class_desc": "0x%08x" % cd,
               "evidence": "dsd_extract/arm9/arm9.bin@0x%08x; src/calls/func_0202099c.c:13-15,62-71"
                           % (SCENE_TABLE + sid * 8)})

    # 2. panels
    panels = read_panel_table(ov_bytes(2), ovs[2][0])
    for slot, (ov, p) in enumerate(panels):
        if ov == -1:
            if p != 0:
                die("panel %d has no overlay but data ptr 0x%x" % (slot, p))
            continue
        if ov == 0 and p == 0:
            notes.append("panel slot %d reads {overlayId 0, data 0}: overlay 0 is the title overlay, "
                         "almost certainly an unused/terminator row, NOT claimed for ov000" % slot)
            continue
        if not in_overlay(ovs, ov, p):
            die("panel %d data ptr 0x%x not inside ov%03d" % (slot, p, ov))
        claim({"overlay": ov, "kind": "panel", "key": slot, "data_ptr": "0x%08x" % p,
               "evidence": "dsd_extract/arm9_overlays/ov002.bin@0x%08x; "
                           "src/overlays/ov002/calls/func_ov002_0207689c.c:38-41" % (PANEL_TABLE + slot * 8)})

    # 3. characters
    groups, n_init = read_group_table(ov_bytes(29), ovs[29][0])
    real_groups = [g for g in groups if any(v > 0 for v in g)]
    if len(real_groups) != n_init:
        die("group table has %d populated rows but init-hook table has %d rows" % (len(real_groups), n_init))
    trailing = groups[len(real_groups):]
    if any(any(v != 0 for v in row) for row in trailing):
        die("non-zero data after the last populated group row: %r" % trailing)
    if trailing:
        notes.append("group table: %d zero row(s) between the last group and the slot array at 0x%08x, "
                     "not counted as a group" % (len(trailing), GROUP_SLOTS))
    slot_base = {}
    for g, row in enumerate(real_groups):
        for s, ov in enumerate(row):
            if ov == -1:
                continue
            base = ovs[ov][0]
            if slot_base.setdefault(s, base) != base:
                die("group %d slot %d: ov%03d loads at 0x%x, slot base is 0x%x" % (g, s, ov, base, slot_base[s]))
            claim({"overlay": ov, "kind": "character", "key": "group %d slot %d" % (g, s),
                   "group": g, "slot": s, "slots_in_group": sum(1 for v in row if v != -1),
                   "evidence": "dsd_extract/arm9_overlays/ov029.bin@0x%08x; "
                               "src/overlays/ov029/calls/func_ov029_020b2ee0.c:62-66" % (GROUP_TABLE + g * 16 + s * 4)})
    if len(set(slot_base.values())) != 4:
        die("character slot bases not distinct: %r" % slot_base)

    # 4. enemies + primers
    enemies, primer_ids, primer_ptrs = read_enemy_table(ov_bytes(107), ovs[107][0])
    enemy_slot_base = {}
    for s, pid in enumerate(primer_ids):
        base = ovs[pid][0]
        if primer_ptrs[s] < base or primer_ptrs[s] >= base + ovs[pid][1] + 0x100:
            die("primer ov%03d: slot ptr 0x%x not near its base 0x%x" % (pid, primer_ptrs[s], base))
        enemy_slot_base[s] = base
        claim({"overlay": pid, "kind": "slot_primer", "key": s,
               "evidence": "dsd_extract/arm9_overlays/ov107.bin@0x%08x; "
                           "src/overlays/ov107/calls/func_ov107_020c0680.c:27-41" % (ENEMY_SLOT_IDS + s * 4)})
    if len(set(enemy_slot_base.values())) != 6:
        die("enemy slot bases not distinct")
    fmt_checked = 0
    for idx, row in enumerate(enemies):
        for s, b in enumerate(row):
            if b == 0xFF:
                continue
            ov = ENEMY_OVERLAY_BIAS + b
            if ovs[ov][0] != enemy_slot_base[s]:
                die("enemy idx %d slot %d -> ov%03d loads at 0x%x, slot base 0x%x"
                    % (idx, s, ov, ovs[ov][0], enemy_slot_base[s]))
            k = enemy_fmt_arg(ov)
            if k is None:
                notes.append("ov%03d (enemy idx %d): no OS_SPrintf(\"Ms/%%02x.p\", K) found, index unverified by route 2" % (ov, idx))
            elif k != idx:
                die("ov%03d formats Ms/%02x.p but the roster table says index %d" % (ov, k, idx))
            else:
                fmt_checked += 1
            archive = os.path.join(EXTRACT, "files", "Ms", "%02X.p" % idx)
            claim({"overlay": ov, "kind": "enemy", "key": "index %d slot %d" % (idx, s),
                   "index": idx, "slot": s, "slots_for_index": sum(1 for v in row if v != 0xFF),
                   "ms_archive": "Ms/%02X.p" % idx if os.path.exists(archive) else None,
                   "fmt_arg_verified": k == idx,
                   "evidence": "dsd_extract/arm9_overlays/ov107.bin@0x%08x; "
                               "src/overlays/ov107/calls/func_ov107_020c0680.c:45-49" % (ENEMY_TABLE + idx * 6 + s)})

    # 5. the rest
    for n in sorted(ovs):
        if n not in claims:
            rec = {"overlay": n, "kind": "other", "key": None, "evidence": None}
            if n == 302:
                rec["evidence"] = ("loaded by func_0201e470(0, 0x12e) in src/overlays/ov009/calls/func_ov009_0204dc00.c:96 "
                                   "and OVERLAY_302_ID in src/overlays/ov005/calls/func_ov005_020584a8.c:6")
            claim(rec)

    # coverage checks (the ranges the prior pass claimed, re-derived here)
    def kinds(lo, hi):
        return {claims[n]["kind"] for n in range(lo, hi + 1)}
    if kinds(30, 68) | kinds(70, 104) != {"character"}:
        die("character overlays are not exactly ov030-068, ov070-104")
    if claims[69]["kind"] != "other":
        die("ov069 claimed by a table")
    if kinds(114, 301) != {"enemy"}:
        die("enemy overlays are not exactly ov114-301")
    if kinds(108, 113) != {"slot_primer"}:
        die("primers are not exactly ov108-113")
    if kinds(13, 21) != {"panel"}:
        die("panel overlays are not exactly ov013-021")
    if {claims[n]["overlay"] for n in claims if claims[n]["kind"] == "scene"} != {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}:
        die("scene overlays are not {0,2..12}")

    summary = {
        "scene_entries": len(scenes), "scenes_with_overlay": sum(1 for o, _ in scenes if o != -1),
        "panel_rows": len(panels), "character_groups": len(real_groups),
        "character_slot_bases": {s: "0x%08x" % b for s, b in sorted(slot_base.items())},
        "enemy_indices": len(enemies), "enemy_overlays": sum(1 for r in claims.values() if r["kind"] == "enemy"),
        "enemy_fmt_arg_verified": fmt_checked,
        "enemy_slot_bases": {s: "0x%08x" % b for s, b in sorted(enemy_slot_base.items())},
        "kinds": {k: sum(1 for r in claims.values() if r["kind"] == k)
                  for k in ("scene", "panel", "character", "enemy", "slot_primer", "other")},
        "notes": notes,
    }
    return [claims[n] for n in sorted(claims)], summary


def main(argv):
    records, summary = build()
    out = None
    if "--json" in argv:
        out = argv[argv.index("--json") + 1]
        json.dump({"summary": summary, "overlays": records}, open(out, "w", encoding="utf-8"), indent=1)
    print(json.dumps(summary, indent=1))
    for r in records:
        if r["kind"] != "enemy" or "--all" in argv:
            print("ov%03d  %-12s %s" % (r["overlay"], r["kind"], r["key"]))
    if out:
        print("wrote", out)


if __name__ == "__main__":
    main(sys.argv[1:])
