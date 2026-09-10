# Progress policy

This project separates progress into several categories so contributors and
external trackers can see what has actually been decompiled into C.

## Real C decompilation

A function counts as real C decompilation only when it is implemented in C and
passes byte-exact verification against the original code.

## ASM stubs

ASM stubs, inline ASM, or placeholder assembly may be used temporarily while the
project is being bootstrapped.

These functions may match the original bytes, but they do not count as
C-decompiled progress.

## SDK identification

SDK/library functions identified through byte matching are useful for naming and
understanding the binary, but they are tracked separately from game-code
decompilation.

## Named-only functions

A function may have a known or provisional name before it has a real C
implementation. Names are useful for research, but they do not count as
C-decompiled progress.

## Initialized DATA

The public report inventories initialized `.rodata`, `.ctor`, and `.data`
section bytes from the checked-in module maps. BSS is excluded because it has
no stored ROM bytes. DATA begins at 0% and advances only after byte and
relocation verification; symbol names, extraction, `incbin`, embedded opcodes,
or preserving an original binary blob do not count as reconstruction.

`tools/index_data.py` builds the ground truth from the delinked objects and
`tools/verify_data.py` proves one reconstructed symbol against it, masking
relocated words and then comparing relocations by resolved target address so
that two spellings of one address agree and two addresses do not. A symbol whose
delinked objects disagree about their relocation targets is reported ambiguous
and refused rather than certified. Verified symbols leave a receipt, and the
report re-runs every receipt instead of trusting it, so an edited or deleted
source stops counting by itself. Bytes are attributed per module as well as per
address, because overlays are loaded over one another and share addresses.

Fully carved executable payloads use the narrower
`tools/verify_executable_data.py` gate. It refuses opaque directives and numeric
opcodes, requires one readable ARM mnemonic per instruction plus named/symbolic
embedded DATA, checks exact size/SHA-256, and proves that GAS and the project
MWLD preserve every byte. A separately tested semantic implementation is also
required; mechanical disassembly alone is not enough.

What the public report can see is the checked-in `delinks.txt`. A `.rodata` or
`.data` range appears in a FILE entry only because `gen_delinks.py` put it
there, and it only does that for a symbol `verify_data.py` proved and whose
source digest still matches, so the committed delinks are a record of
verification rather than a claim made by hand. That is the same standard the
code percentage already uses: a checkout has no ROM to compare against, so the
tree is the evidence. `data_progress.py --verify` re-runs the byte and
relocation proof wherever the delinked build and the compiler are present, and
reports any drift between what the delinks claim and what the bytes support.

Regions are split at the verified boundaries. The report counts a region only
when it is wholly matched, so leaving a module's whole section as one region
reported all-or-nothing and lost most of the proved bytes.

Verified DATA also enters the build. `gen_delinks.py` turns receipts into
`.rodata`/`.data` ranges on the owning source file, merging adjacent symbols
into one range and re-checking the source digest first, so an edited file drops
back out of the link instead of poisoning it. A source therefore has to own a
contiguous run and define its symbols in address order, because the linker
places one section image at the declared start.

Payloads stored in a data section but executed at runtime are classified
separately. ov024's `0x659c`-byte MobiClip decoder payload has now passed that
gate and is reported as `MobiClip executable payload` at 26012/26012 bytes.
Keeping the category separate makes clear that it is reconstructed executable
middleware rather than ordinary game DATA.

## Why this matters

The goal is to keep progress reporting honest and useful for contributors and
external project trackers such as decomp.dev. Byte-exact matching remains the
technical verification gate, but public C progress only counts real C
implementations.

## decomp.dev matching coverage

The primary `YKGP_report` artifact reports byte-exact matching coverage, not
pure-C completion. In addition to real C it includes only the sources listed in
`config/arm9/report_asm_matches.json`: the individually authorized CLZ exceptions
and the verified canonical SDK assembly completing ITCM. This is not permission
to count other game stubs, inline assembly, or SDK identifications as complete.

Each entry records its source hash, target hash, mode, and verified size. Source
hashes normalize line endings so Windows and CI agree. Changes invalidate the
attestation and stop report generation until `python tools/verify_report_asm.py`
passes byte and relocation verification again. Adding a game entry also requires
the explicit single-CLZ authorization in `config/arm9/asm_exceptions.json`.

ITCM can report 100% matching while the C audit reports 129/154 real-C functions,
because the remainder is canonical SDK assembly and not C. ov002 and ov003 now report
100% in both, following the single-instruction rule below. `PROGRESS.md` and
`build/report_c.json` continue to exclude every other ASM source from real C.
The workflow uploads `report_c.json` with `YKGP_progress_audit` for comparison.
Both reports use the same DATA inventory; their difference remains exclusively
the treatment of verified non-C code.

## The single-instruction rule

A source file that is C throughout apart from ONE instruction that no C form this
compiler accepts can emit counts as real C decompilation.

Scope, and it is deliberately narrow: exactly one instruction, the rest of the
implementation in C, and the instruction must be one the compiler cannot be coaxed
into producing from any C. Today that is `clz` alone, in
`src/overlays/ov002/calls/func_ov002_02077560.c` and
`src/overlays/ov003/calls/func_ov003_0204d74c.c`, both recorded in
`config/arm9/asm_exceptions.json`. Those two are the only functions holding ov002
and ov003 short of 100%, and under this rule both modules are complete.

This is not permission for inline assembly generally. A file with a second such
instruction, or with a hand-written block that C could have produced, is an ASM
stub and never counts. A whole function written as `asm` is not a decompilation at
all.

Why the rule exists rather than a per-file exception: the question was previously
answered both ways by two different counting tools, and the count was corrected
publicly twice as a result. `tools/audit_progress.py` now derives its verdict from
`tools/provenance.py`, which reads what the link actually used, so the two agree by
construction instead of by coincidence.

Recorded 2026-09-10 by the repository owner. An earlier entry in
`asm_exceptions.json` recorded the opposite, attributed to the owner and dated
2026-08-30/31; those dates precede their involvement in the project, so that
attribution is not reliable. The inherited text is preserved in that file rather
than deleted.
