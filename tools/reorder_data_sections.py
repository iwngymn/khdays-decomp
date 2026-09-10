#!/usr/bin/env python3
"""Put a compiled object's initialized-data sections in ROM address order.

    python tools/reorder_data_sections.py <object.o> [more.o ...]

Why this exists
---------------
mwccarm emits every global data definition as its own `.rodata`/`.data` section
(or pools same-typed globals into one section) and orders them by size, stable,
over the sequence [n-1, ..., 2, 1, n] of source order -- so three or more globals
never come out in source order, whatever the source order is. Measured on this
compiler (3.0 build 139): no flag changes it (-O0, -str pool/nopool, -ipa, -lang
c/c++, bare `-c` all agree; `-str pool` merges the sections and keeps the
scramble). And 244 of the 447 multi-symbol files here are not size-ascending in
address order, so no source order can produce the ROM layout either.

dsd's linker script names the object once per section, `foo.o(.rodata)`, and
mwld then lays down every input section of that name in section-header order.
delinks.txt cannot select individual sections, so a file that defines several
globals lands scrambled inside the range it claims (65 bytes of the ov035
module; 369 of 704 receipted data sources). This is why gen_delinks.py's
gen_data_block can assume "a source owns a contiguous run and defines its
symbols in address order": _run_mwcc.py calls reorder() after every compile,
which makes that assumption true by construction.

What it does
------------
The address a symbol was verified at is read from build/data_receipts/<sym>.json.
Section headers of the same name are permuted so their order follows that
address; inside a section holding several verified symbols the symbol chunks
are moved so each sits at (its address - the section's lowest address). The
file keeps its size: headers, st_shndx/st_value and r_offset/r_addend are
patched in place. A section whose symbols are not all verified is left alone
(it cannot be placed correctly anyway) and reported on stderr. An object that
needs no change is not rewritten.
"""
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RECEIPTS = ROOT / "build" / "data_receipts"
DATA_SECTIONS = {".rodata", ".data", ".ctor"}

SHT_PROGBITS, SHT_SYMTAB, SHT_RELA, SHT_REL = 1, 2, 4, 9
STT_SECTION, STT_FILE = 3, 4
SHN_LORESERVE = 0xFF00
SHDR = struct.Struct("<IIIIIIIIII")   # name type flags addr offset size link info align entsize
SYM = struct.Struct("<IIIBBH")        # name value size info other shndx


def receipt_addr(name):
    p = RECEIPTS / (name + ".json")
    if not p.is_file():
        return None
    try:
        return json.loads(p.read_text(encoding="utf-8")).get("start")
    except (OSError, ValueError):
        return None


def reorder(path, log=sys.stderr):
    """Rewrite `path` in place. Returns the number of sections changed."""
    path = Path(path)
    buf = bytearray(path.read_bytes())
    if buf[:5] != b"\x7fELF\x01" or buf[5] != 1:
        return 0                                    # not ELF32 little-endian
    e_shoff, = struct.unpack_from("<I", buf, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", buf, 0x2E)
    if e_shentsize != SHDR.size or not e_shnum:
        return 0
    shdrs = [list(SHDR.unpack_from(buf, e_shoff + i * SHDR.size)) for i in range(e_shnum)]
    shstr = shdrs[e_shstrndx]

    def cstr(tab, off):
        end = buf.index(b"\0", tab[4] + off)
        return buf[tab[4] + off:end].decode("ascii", "replace")

    names = [cstr(shstr, h[0]) for h in shdrs]
    symtab_idx = next((i for i, h in enumerate(shdrs) if h[1] == SHT_SYMTAB), None)
    if symtab_idx is None:
        return 0
    symtab = shdrs[symtab_idx]
    strtab = shdrs[symtab[6]]
    nsyms = symtab[5] // SYM.size
    syms = [list(SYM.unpack_from(buf, symtab[4] + i * SYM.size)) for i in range(nsyms)]

    # Verified address of every named data symbol, grouped by section.
    by_sec = {}
    for s in syms:
        stype = s[3] & 0xF
        if stype in (STT_SECTION, STT_FILE) or s[5] == 0 or s[5] >= SHN_LORESERVE:
            continue
        if names[s[5]] not in DATA_SECTIONS or shdrs[s[5]][1] != SHT_PROGBITS:
            continue
        by_sec.setdefault(s[5], []).append((s, receipt_addr(cstr(strtab, s[0]))))

    changed = 0

    # 1. Symbol order inside a section that holds several verified symbols.
    #    old offset -> new offset per byte range, applied to symbols and relocs.
    moves = {}                                      # sec index -> [(old, new, size)]
    for idx, entries in by_sec.items():
        if len(entries) < 2:
            continue
        if any(addr is None for _, addr in entries):
            print(f"reorder_data_sections: {path.name}: section {idx} {names[idx]} has "
                  f"unverified symbols; left as emitted", file=log)
            continue
        base = min(addr for _, addr in entries)
        size = shdrs[idx][5]
        chunks = sorted((addr - base, s[1], s[2]) for s, addr in entries)
        ok = all(new + sz <= size for new, _, sz in chunks) and all(
            chunks[i][0] + chunks[i][2] <= chunks[i + 1][0] for i in range(len(chunks) - 1))
        if not ok:
            print(f"reorder_data_sections: {path.name}: section {idx} {names[idx]} verified "
                  f"addresses do not fit the section; left as emitted", file=log)
            continue
        if all(new == old for new, old, _ in chunks):
            continue
        off = shdrs[idx][4]
        old_data = bytes(buf[off:off + size])
        new_data = bytearray(size)
        for new, old, sz in chunks:
            new_data[new:new + sz] = old_data[old:old + sz]
        buf[off:off + size] = new_data
        moves[idx] = [(old, new, sz) for new, old, sz in chunks]
        changed += 1

    def remap_off(idx, o):
        for old, new, sz in moves.get(idx, ()):
            if old <= o < old + sz:
                return o - old + new
        raise ValueError(f"{path.name}: offset 0x{o:x} of section {idx} is outside every symbol")

    for s in syms:
        if s[5] in moves:
            s[1] = remap_off(s[5], s[1])

    # 2. Header order of same-named sections: verified ones sorted by address,
    #    keeping their slots; unverified ones stay where they are.
    perm = list(range(e_shnum))                     # new index -> old index
    for name in DATA_SECTIONS:
        slots = [i for i in range(e_shnum) if names[i] == name
                 and i in by_sec and all(a is not None for _, a in by_sec[i])]
        order = sorted(slots, key=lambda i: min(a for _, a in by_sec[i]))
        for slot, old in zip(slots, order):
            perm[slot] = old
    old_to_new = {old: new for new, old in enumerate(perm)}
    if any(new != old for new, old in enumerate(perm)):
        changed += sum(1 for new, old in enumerate(perm) if new != old)

    # 3. Relocations: offsets follow their moved symbol chunk; a relocation
    #    against a section symbol carries the offset in its addend instead.
    for i, h in enumerate(shdrs):
        if h[1] not in (SHT_REL, SHT_RELA):
            continue
        target, ent = h[7], (12 if h[1] == SHT_RELA else 8)
        for off in range(h[4], h[4] + h[5], ent):
            r_offset, r_info = struct.unpack_from("<II", buf, off)
            if target in moves:
                r_offset = remap_off(target, r_offset)
            if h[1] == SHT_RELA:
                r_addend, = struct.unpack_from("<i", buf, off + 8)
                sym = syms[r_info >> 8]
                if (sym[3] & 0xF) == STT_SECTION and sym[5] in moves:
                    r_addend = remap_off(sym[5], r_addend)
                struct.pack_into("<i", buf, off + 8, r_addend)
            struct.pack_into("<I", buf, off, r_offset)

    if not changed:
        return 0

    # 4. Write back: symbols (with section indices renumbered), headers in the
    #    new order with link/info renumbered, and the string-table index.
    def renum(i):
        return old_to_new.get(i, i) if 0 < i < SHN_LORESERVE else i

    for n, s in enumerate(syms):
        s[5] = renum(s[5])
        SYM.pack_into(buf, symtab[4] + n * SYM.size, *s)
    for new, old in enumerate(perm):
        h = list(shdrs[old])
        if h[1] in (SHT_REL, SHT_RELA):
            h[7] = renum(h[7])
        if h[1] in (SHT_REL, SHT_RELA, SHT_SYMTAB) or h[6]:
            h[6] = renum(h[6])
        SHDR.pack_into(buf, e_shoff + new * SHDR.size, *h)
    struct.pack_into("<H", buf, 0x32, renum(e_shstrndx))
    path.write_bytes(bytes(buf))
    return changed


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    total = 0
    for arg in sys.argv[1:]:
        n = reorder(arg)
        total += n
        if n:
            print(f"{arg}: {n} section(s) reordered")
    print(f"{len(sys.argv) - 1} object(s), {total} section(s) reordered")
    return 0


if __name__ == "__main__":
    sys.exit(main())
