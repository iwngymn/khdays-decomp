<!-- Keep PRs focused: one function, a related family, or a reviewable module.
See docs/CONTRIBUTION_STYLE.md for scope and commit-message examples.
For tooling/docs, replace the function inventory with the problem and result;
mark function verification not applicable and describe the relevant checks.
Fill placeholders with actual evidence; leave unperformed checks unchecked. -->

## What this PR decompiles

<!-- State the behavior and contribution category: real C matched, non-matching
C, assembly exception, SDK identification, or name-only change. Link the claim.
Explain required supporting changes. A sentence can replace a one-row table. -->

| Function | Address | ARM/Thumb | Bytes | Relocations | Behavior |
| --- | --- | --- | --- | --- | --- |
| `<func_...>` | `<0x...>` | `<mode>` | `<full length>` | `<count>` | `<what it does>` |

## Verification

<!-- Give exact commands, compiler version/flags or their pinned configuration,
reference inputs, exit codes and actual results for every function. Confirm
full bytes/length and relocation offsets/types/targets/addends, not just a count
or MATCH marker. Explain any non-obvious C forms needed to match. -->

Per-function checks: `<commands and results>`

Fresh link and module checks: `<commands/results, or not run/pending and reason>`

<!-- Module completion requires a fresh successful ninja build/arm9.elf followed
by tools/dsd.exe check modules --config-path config/arm9/config.yaml -f.
Do not claim completion from stale outputs. ROM repacking is separate.
Include refreshed real-C progress only when it describes this PR's changes. -->

## Checklist

- [ ] Every function claimed as matching C has been independently checked for exact bytes, full length, relocations and source meaning.
- [ ] The change contains only the stated source and necessary supporting edits; no ROM, assets, compiler, binaries or private notes.
- [ ] The module claim is linked, or coordination is explained as not applicable.
- [ ] Verification and progress claims describe the submitted changes; pending checks and limitations are stated.
