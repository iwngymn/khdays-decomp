#!/usr/bin/env python3
"""offset_census.py -- who touches a struct offset, decided from the ROM's instructions.

    python tools/offset_census.py --offset 0x1c7 [--module 'ov2*'] [--route R]
    python tools/offset_census.py --route '[[a0+0x4]]' [--module ov245]
    python tools/offset_census.py --func func_ov245_020ccfa8
    python tools/offset_census.py --rebuild        # drop the cache

Reads build/func_index.json (bytes + relocs of every function, solved or not) and
decodes each function with capstone. A linear pass tracks where each register's
value came from, so an access is reported as ROUTE + OFFSET + WIDTH + SIGN + R/W:

    a0..a3             the parameter registers at entry
    ret:SYM            r0 after `bl SYM`
    sym:NAME           a literal-pool word that relocates to NAME (a global)
    lit:0x....         a literal-pool word with no relocation (raw address)
    [ROUTE+0xN]        a word loaded through ROUTE at N   ([ROUTE] when N == 0)
    ?                  the pass lost track (register written by something else)

Two accesses to the same offset are the same FIELD only when the route agrees.
`[[a0+0x4]]+0x1c7` in an AI-overlay think callback and `ret:func_01fffde0+0x1c7`
in ov022 are two claims about two different pointers; this tool keeps them apart,
which the C casts cannot (every file spells its own base expression).

Sign is only observable on loads (ldrsb/ldrsh vs ldrb/ldrh). A store says the
width and nothing else. The bytes already police load width and sign -- a wrong
`*(unsigned char *)` on a load does not match -- so what the census adds is
STORE-side width, the route, and the cross-file histogram.

ponytail: linear pass, no CFG. A register redefined on one branch arm is read as
whatever the fall-through arm left; conditional execution is treated as taken.
Measured wrong-route noise shows up as small counts on odd routes; read the
big buckets. Upgrade path: per-basic-block state merge, if a real question
ever needs it.
"""
import fnmatch
import json
import os
import sys
import time
from collections import Counter, defaultdict

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
IDX_PATH = os.path.join(ROOT, "build", "func_index.json")
CACHE = os.path.join(ROOT, "build", "struct_census_cache.json")

try:
    sys.stdout.reconfigure(errors="replace")
except Exception:
    pass


# ------------------------------------------------------------------ decoding
def _decoders():
    from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
    out = {}
    for mode, cm in (("arm", CS_MODE_ARM), ("thumb", CS_MODE_THUMB)):
        md = Cs(CS_ARCH_ARM, cm)
        md.detail = True
        md.skipdata = True
        out[mode] = md
    return out


def match(pattern, text):
    """Exact match, or a glob when the pattern carries * or ?. Routes contain
    '[' and ']', which fnmatch would read as a character class -- the first run of
    this tool answered 'no access' to every bracketed route for that reason."""
    if "*" in pattern or "?" in pattern:
        return fnmatch.fnmatchcase(text, pattern.replace("[", "[[]"))
    return pattern == text


def _fmt(base, disp):
    if disp == 0:
        return "[%s]" % base
    return "[%s%s0x%x]" % (base, "+" if disp > 0 else "-", abs(disp))


def census_function(name, e, md):
    """[(insn_off, route, offset, width, sign, rw)] for one function."""
    from capstone.arm import (ARM_OP_REG, ARM_OP_MEM, ARM_OP_IMM, ARM_INS_LDR, ARM_INS_LDRB,
                              ARM_INS_LDRH, ARM_INS_LDRSB, ARM_INS_LDRSH, ARM_INS_LDRD,
                              ARM_INS_STR, ARM_INS_STRB, ARM_INS_STRH, ARM_INS_STRD,
                              ARM_INS_MOV, ARM_INS_ADD, ARM_INS_SUB, ARM_INS_BL, ARM_INS_BLX,
                              ARM_INS_LDM, ARM_INS_STM, ARM_INS_LDMDB, ARM_INS_STMDB,
                              ARM_INS_PUSH, ARM_INS_POP, ARM_INS_BX, ARM_INS_MVN)
    # ldrd/strd are recorded as two word accesses: that is how mwcc reads a u64
    # here too (two ldr), so the doc's u64 shows up as r4 at +0 and +4 either way.
    LOADS = {ARM_INS_LDR: (4, "-"), ARM_INS_LDRB: (1, "u"), ARM_INS_LDRH: (2, "u"),
             ARM_INS_LDRSB: (1, "s"), ARM_INS_LDRSH: (2, "s"), ARM_INS_LDRD: (4, "-")}
    STORES = {ARM_INS_STR: 4, ARM_INS_STRB: 1, ARM_INS_STRH: 2, ARM_INS_STRD: 4}
    thumb = e["mode"] == "thumb"
    code = bytes.fromhex(e["hex"])
    relocs = {int(o): s for o, s in e.get("relocs", [])}
    # register -> (base, disp) or None
    regs = {"r0": ("a0", 0), "r1": ("a1", 0), "r2": ("a2", 0), "r3": ("a3", 0)}
    slots = {}     # stack slot key (sp disp) -> provenance, so spills survive a call
    out = []

    def prov(r):
        return regs.get(r)

    def pool_word(addr):
        if addr + 4 > len(code):
            return None
        if addr in relocs:
            return ("sym:" + relocs[addr], 0)
        return ("lit:0x%x" % int.from_bytes(code[addr:addr + 4], "little"), 0)

    for i in md.disasm(code, 0):
        if i.id == 0:          # skipdata placeholder: a pool word or a jump table
            continue
        ops = i.operands
        oid = i.id

        if oid in LOADS or oid in STORES:
            memop = next((o for o in ops if o.type == ARM_OP_MEM), None)
            if memop is None:
                continue
            mem = memop.mem
            base = i.reg_name(mem.base)
            if mem.index != 0:
                # register-offset addressing: an array walk, not a field. The
                # destination register's provenance is unknown afterwards.
                if oid in LOADS:
                    regs[i.reg_name(ops[0].reg)] = None
                continue
            disp = mem.disp
            if base == "pc":
                # literal pool: ARM pc = insn+8, thumb pc = (insn+4) word-aligned
                addr = (i.address + 8 + disp) if not thumb else (((i.address + 4) & ~3) + disp)
                if oid == ARM_INS_LDR:
                    regs[i.reg_name(ops[0].reg)] = pool_word(addr)
                continue
            if base == "sp":
                key = disp
                if oid == ARM_INS_LDR:
                    regs[i.reg_name(ops[0].reg)] = slots.get(key)
                elif oid == ARM_INS_STR:
                    slots[key] = regs.get(i.reg_name(ops[0].reg))
                continue
            p = prov(base)
            route, off = (p[0], p[1] + disp) if p else ("?", disp)
            if oid in LOADS:
                w, s = LOADS[oid]
                out.append((i.address, route, off, w, s, "r"))
                if oid == ARM_INS_LDRD:
                    out.append((i.address, route, off + 4, 4, "-", "r"))
                dst = i.reg_name(ops[0].reg)
                regs[dst] = (_fmt(route, off), 0) if oid == ARM_INS_LDR and route != "?" else None
                if oid == ARM_INS_LDRD:
                    regs[i.reg_name(ops[1].reg)] = None
            else:
                w = STORES[oid]
                out.append((i.address, route, off, w, "-", "w"))
                if oid == ARM_INS_STRD:
                    out.append((i.address, route, off + 4, 4, "-", "w"))
            if i.writeback:
                regs[base] = None
            continue

        if oid in (ARM_INS_LDM, ARM_INS_STM, ARM_INS_LDMDB, ARM_INS_STMDB) and ops and ops[0].type == ARM_OP_REG:
            base = i.reg_name(ops[0].reg)
            if base == "sp":
                continue
            p = prov(base)
            route, off0 = (p[0], p[1]) if p else ("?", 0)
            rw = "r" if oid in (ARM_INS_LDM, ARM_INS_LDMDB) else "w"
            rlist = [o for o in ops[1:] if o.type == ARM_OP_REG]
            for k, o in enumerate(rlist):
                out.append((i.address, route, off0 + 4 * k, 4, "-", rw))
                if rw == "r":
                    regs[i.reg_name(o.reg)] = None
            if i.writeback:
                regs[base] = None
            continue

        if oid in (ARM_INS_BL, ARM_INS_BLX):
            sym = relocs.get(i.address, "?")
            regs.update(r0=("ret:" + sym, 0), r1=None, r2=None, r3=None, r12=None, lr=None)
            continue

        if oid == ARM_INS_MOV and len(ops) == 2 and ops[0].type == ARM_OP_REG:
            dst = i.reg_name(ops[0].reg)
            regs[dst] = prov(i.reg_name(ops[1].reg)) if ops[1].type == ARM_OP_REG and not ops[1].shift.type else None
            continue

        if oid in (ARM_INS_ADD, ARM_INS_SUB) and len(ops) == 3 and ops[0].type == ARM_OP_REG \
                and ops[1].type == ARM_OP_REG and ops[2].type == ARM_OP_IMM:
            dst, src = i.reg_name(ops[0].reg), i.reg_name(ops[1].reg)
            if src == "sp" or src == "pc":
                regs[dst] = None
                continue
            p = prov(src)
            k = ops[2].imm if oid == ARM_INS_ADD else -ops[2].imm
            regs[dst] = (p[0], p[1] + k) if p else None
            continue

        if oid in (ARM_INS_PUSH, ARM_INS_POP, ARM_INS_BX, ARM_INS_MVN):
            if oid == ARM_INS_MVN and ops and ops[0].type == ARM_OP_REG:
                regs[i.reg_name(ops[0].reg)] = None
            continue

        # anything else that writes a register: unknown from here
        if ops and ops[0].type == ARM_OP_REG:
            dst = i.reg_name(ops[0].reg)
            if dst not in ("sp", "pc"):
                regs[dst] = None
    return out


# ------------------------------------------------------------------ cache
def load_index():
    with open(IDX_PATH, encoding="utf-8") as fh:
        return json.load(fh)


def build(idx):
    md = _decoders()
    rows = {}
    t0 = time.time()
    for n, (name, e) in enumerate(idx.items()):
        try:
            rows[name] = census_function(name, e, md[e["mode"]])
        except Exception as exc:  # a broken hex entry must not kill the census
            rows[name] = []
            print("skip %s: %s" % (name, exc), file=sys.stderr)
    print("census: %d functions decoded in %.1fs" % (len(rows), time.time() - t0), file=sys.stderr)
    return rows


def census(rebuild=False):
    """{func: [(insn_off, route, offset, width, sign, rw)]}, cached against func_index mtime."""
    stamp = os.stat(IDX_PATH).st_mtime
    if not rebuild and os.path.isfile(CACHE):
        try:
            with open(CACHE, encoding="utf-8") as fh:
                c = json.load(fh)
            if c.get("stamp") == stamp:
                return c["rows"]
        except Exception:
            pass
    idx = load_index()
    rows = build(idx)
    with open(CACHE, "w", encoding="utf-8") as fh:
        json.dump({"stamp": stamp, "rows": rows}, fh)
    return rows


def solved_files():
    """func name -> repo-relative path, for functions that have real C in the tree."""
    out = {}
    for base in ("src", "libs"):
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, base)):
            dirnames[:] = [d for d in dirnames if d not in ("asm_stubs", "nonmatching")]
            for fn in filenames:
                if fn.endswith(".c"):
                    out[fn[:-2]] = os.path.relpath(os.path.join(dirpath, fn), ROOT).replace("\\", "/")
    return out


# ------------------------------------------------------------------ reports
def _acc(width, sign, rw):
    return "%s%d%s" % (rw, width, "" if sign == "-" else sign)


def report_offset(rows, idx, offset, module, route, top, have):
    hits = defaultdict(list)     # route -> [(func, acc)]
    for f, accs in rows.items():
        if module and not fnmatch.fnmatch(idx[f]["module"], module):
            continue
        for _o, r, off, w, s, rw in accs:
            if off == offset and (not route or match(route, r)):
                hits[r].append((f, _acc(w, s, rw)))
    if not hits:
        print("no access to +0x%x%s" % (offset, " in " + module if module else ""))
        return
    total = sum(len(v) for v in hits.values())
    nf = len({f for v in hits.values() for f, _ in v})
    print("+0x%x: %d accesses in %d functions%s" % (offset, total, nf, ", module " + module if module else ""))
    print("%-34s %5s %5s %6s  %s" % ("route", "acc", "funcs", "solved", "width/sign/rw histogram"))
    for r, v in sorted(hits.items(), key=lambda kv: -len(kv[1]))[:top]:
        funcs = {f for f, _ in v}
        h = Counter(a for _, a in v)
        print("%-34s %5d %5d %6d  %s" % (r, len(v), len(funcs), sum(1 for f in funcs if f in have),
                                        " ".join("%s=%d" % kv for kv in h.most_common())))
    mods = Counter(idx[f]["module"] for v in hits.values() for f, _ in v)
    print("modules: " + " ".join("%s=%d" % kv for kv in mods.most_common(12)))
    if route:
        fl = sorted({f for v in hits.values() for f, _ in v})
        print("functions (%d, %d solved):" % (len(fl), sum(1 for f in fl if f in have)))
        for f in fl[:top]:
            print("  %s  %s" % (f, have.get(f, "(unsolved)")))


def report_route(rows, idx, route, module, top, have, min_funcs):
    byoff = defaultdict(list)
    nfun = 0
    for f, accs in rows.items():
        if module and not fnmatch.fnmatch(idx[f]["module"], module):
            continue
        mine = [(off, w, s, rw) for _o, r, off, w, s, rw in accs if match(route, r)]
        if mine:
            nfun += 1
        for off, w, s, rw in mine:
            byoff[off].append((f, _acc(w, s, rw)))
    print("route %s%s: %d functions, %d distinct offsets" % (route, " in " + module if module else "", nfun, len(byoff)))
    print("%-8s %5s %5s %6s  %s" % ("offset", "acc", "funcs", "solved", "width/sign/rw histogram  [modules]"))
    for off in sorted(byoff):
        v = byoff[off]
        funcs = {f for f, _ in v}
        if len(funcs) < min_funcs:
            continue
        h = Counter(a for _, a in v)
        mods = Counter(idx[f]["module"] for f in funcs)
        print("+0x%-5x %5d %5d %6d  %-28s [%s]" % (
            off, len(v), len(funcs), sum(1 for f in funcs if f in have),
            " ".join("%s=%d" % kv for kv in h.most_common(4)),
            " ".join("%s=%d" % kv for kv in mods.most_common(4))))


def report_func(rows, name):
    accs = rows.get(name)
    if accs is None:
        print("not in func_index: " + name)
        return
    print("%s: %d field accesses" % (name, len(accs)))
    for o, r, off, w, s, rw in accs:
        print("  +%04x  %-30s +0x%-4x %s" % (o, r, off, _acc(w, s, rw)))


def main(argv):
    if "--help" in argv or not argv:
        print(__doc__)
        return 0
    args = list(argv)

    def opt(flag, default=None):
        if flag in args:
            k = args.index(flag)
            v = args[k + 1]
            del args[k:k + 2]
            return v
        return default
    rebuild = "--rebuild" in args
    if rebuild:
        args.remove("--rebuild")
    offset = opt("--offset")
    route = opt("--route")
    module = opt("--module")
    func = opt("--func")
    top = int(opt("--top", "20"))
    min_funcs = int(opt("--min", "1"))
    if args:
        print("unknown args: %s" % args)
        return 2
    rows = census(rebuild)
    idx = load_index()
    have = solved_files()
    if func:
        report_func(rows, func)
    elif offset is not None:
        report_offset(rows, idx, int(offset, 0), module, route, top, have)
    elif route:
        report_route(rows, idx, route, module, top, have, min_funcs)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
