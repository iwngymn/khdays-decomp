# Overlay gameplay map

Snapshot taken 2026-09-08 from [PROGRESS.md](../PROGRESS.md), except the ov014 row, which reflects later work. Treat every percentage here as a dated snapshot and PROGRESS.md as authoritative. All 298 listed modules are included. These percentages measure functions reconstructed in matching C, not gameplay understood, code size, or difficulty. This is a documentation snapshot, not a new ROM verification; use PROGRESS.md for current counts.

“Outside C” = total functions minus C-matched functions. This includes assembly and library identifications; it is not a promise that all remaining functions should become C. A 100% row can still have unknown names and unrecovered data.

Character names below come from explicit strings in the local source. Repeated copies of a character are not assigned to a player slot or game mode: that relationship has not been verified. For unidentified objects, resource labels are evidence to investigate, not an invented enemy name. This is a full inventory with partial identification, not a fully solved game map.

## Suggested targets

- Shared combat understanding: ov107 (42.5%, 111 outside C) and ov022 (87.1%, 98 outside C).
- Repeated named-character work: Xigbar ov032/052/072 (35.3%, 22 each); Xemnas ov043/062 (26.1%, 34 each).
- Story events: ov023 (57.6%, 95 outside C).
- Xion-related complex work: ov235 (35.1%), ov255 (39.3%), ov257 (34.7%). Resources establish association, not precise phases.
- Menus: ov008 (78.5%, 266 outside C), ov025 (71.1%, 290), ov026 (72.7%, 70).

These are investigation priorities, not measured difficulty rankings. Check live claims and exact remaining functions before assigning work. Each candidate needs individual verification.

## Maintaining this map

Keep role descriptions evidence-based: link source code or resource declarations, and mark inferred screen names, character forms, and unknown identities explicitly. A resource name establishes an association, not ownership of every related behavior. Do not infer game modes or player slots from repeated copies.

When refreshing the numeric snapshot, copy all module rows from PROGRESS.md, recompute Outside C as Total minus C matched, and update the snapshot date and revision. Keep this map separate from the generated progress report. No extracted ROM data is needed in this document.

## All modules

| Module | C complete | Outside C | Plain-English role | Source clue |
|---|---:|---:|---|---|
| itcm | 83.8% | 25 | Fast-access support code; a memory placement, not an in-game feature. | No identifying text recovered in the scanned string files. |
| main | 76.8% | 455 | Shared game and Nintendo DS support code; not a single gameplay system. | No identifying text recovered in the scanned string files. |
| ov000 | 100.0% | 0 | Title, new-game, load and save support. | `UI/load/lrd_&.s.z`, `text/font_eu_10all.nftr`, `/ttl/ttl.p2`, `ttl/ttl_&.p2` ([source data](../src/overlays/ov000/data/)) |
| ov001 | 100.0% | 0 | Exact role not established. | No identifying text recovered in the scanned string files. |
| ov002 | 99.9% | 1 | Shared gameplay, character/world handling and battle displays. | `ba/tr/%s.z`, `refresh_wnd`, `ba/ch/xo/w_mot.p.z`, `ba/ch/%s/wp.b.z` ([source data](../src/overlays/ov002/data/)) |
| ov003 | 96.4% | 1 | Display/camera setup and character-related display resources. | `ba/ch/ax/def.p.z`, `ba/ch/xo/def.p.z`, `ba/ch/go/def.p.z`, `ba/ch/do/def.p.z` ([source data](../src/overlays/ov003/data/)) |
| ov004 | 100.0% | 0 | Mission-related counting/results display; exact screen identity uncertain. | `UI/cm/str/world_id_&.s.z`, `UI/cm/msl_&.msi.z`, `/UI/cal/7_a.pak.z`, `/UI/cal/8_a.pak.z` ([source data](../src/overlays/ov004/data/)) |
| ov005 | 100.0% | 0 | Mission results screens and panel-related resources. | `UI/cm/str/world_id_&.s.z`, `ui/pnl/3d_&.pak.z`, `UI/srslt/res_&.s.z`, `UI/srslt/res.p2` ([source data](../src/overlays/ov005/data/)) |
| ov006 | 100.0% | 0 | Mission Mode member selection and its screen. | `UI/mlt/mlt_&.s.z`, `/text/font_eu_10all.NFTR`, `/text/font_eu_10all.NFTR`, `UI/mlt/res.p2` ([source data](../src/overlays/ov006/data/)) |
| ov007 | 100.0% | 0 | Likely help/manual screen, based on ui/mnl resources. | `ui/mnl/m`, `ui/mnl/mnl_&.s.z`, `/text/font_eu_10all.nftr` ([source data](../src/overlays/ov007/data/)) |
| ov008 | 78.5% | 266 | Large menu collection: camp menu, panels, shop and mission progress. | `Dummy09`, `Dummy01`, `Dummy08`, `Dummy03` ([source data](../src/overlays/ov008/data/)) |
| ov009 | 100.0% | 0 | Camp menu and save interface. | `text/font_eu_08.nftr`, `text/font_eu_10.nftr`, `text/font_eu_08s.nftr`, `text/font_eu_10s.nftr` ([source data](../src/overlays/ov009/data/)) |
| ov010 | 100.0% | 0 | Likely system messages, based on UI/sys resources. | `/UI/sys/sys_&.s.z`, `text/font_eu_10.nftr` ([source data](../src/overlays/ov010/data/)) |
| ov011 | 60.0% | 16 | Screen using UI/sf resources; exact screen not identified. | `UI/sf/m.p2`, `843.z`, `UI/sf/sf.p2`, `UI/sf/sffont_10.nftr` ([source data](../src/overlays/ov011/data/)) |
| ov012 | 100.0% | 0 | Opening-related resources (op); exact sequence not established. | `/text/font_eu_10all.nftr`, `/op/op.p2`, `op/scr.z` ([source data](../src/overlays/ov012/data/)) |
| ov013 | 100.0% | 0 | References col_btl; exact gameplay object not identified. | `col_btl` ([source data](../src/overlays/ov013/data/)) |
| ov014 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. |
| ov015 | 37.1% | 44 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. |
| ov016 | 50.0% | 41 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. |
| ov017 | 64.4% | 16 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. |
| ov019 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov019/data/)) |
| ov020 | 100.0% | 0 | References wall boundaries and up/down labels; exact object unknown. | `col_wall`, `col_wall10`, `col_wall09`, `up` ([source data](../src/overlays/ov020/data/)) |
| ov021 | 48.4% | 16 | Object timer and scale updates observed; exact object unknown. | No identifying text recovered in the scanned string files. |
| ov022 | 87.1% | 98 | Shared battle/character machinery, pause handling and combat effects. | `ef_wind_B01\0`, `\0`, `Please Entry ScriptName`, `ba/ef/ta.p.z` ([source data](../src/overlays/ov022/data/)) |
| ov023 | 57.6% | 95 | Story-event/staged-scene resources and cameras; likely event handling. | `AW`, `NM`, `PI`, `TT` ([source data](../src/overlays/ov023/data/)) |
| ov024 | 95.8% | 5 | MobiClip video playback/decoding. | `/text/font_eu_10all.nftr`, `mobiclip_intr` ([source data](../src/overlays/ov024/data/)) |
| ov025 | 71.1% | 290 | Large camp-menu/panel/save collection; exact distinction from ov008 unknown. | `ro_w_tg_R`, `Dummy09`, `Dummy01`, `Dummy08` ([source data](../src/overlays/ov025/data/)) |
| ov026 | 72.7% | 70 | Shop interface. | `UI/cm/str/world_id_&.s.z`, `mi/ch/70.z`, `ui/shop/res.p2`, `ui/shop/res_i18n.p2` ([source data](../src/overlays/ov026/data/)) |
| ov027 | 37.2% | 27 | Multiple character appearance resources; exact feature unknown. | `jp_unused`, `ba/ch/go/def.p.z`, `ba/ch/do/def.p.z`, `ba/ch/so/def.p.z` ([source data](../src/overlays/ov027/data/)) |
| ov028 | 100.0% | 0 | Anti-tamper code according to README.md; not independently traced for this map. | No identifying text recovered in the scanned string files. |
| ov029 | 100.0% | 0 | Exact role not established. | No identifying text recovered in the scanned string files. |
| ov030 | 100.0% | 0 | Roxas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `ro_w_tg_L`, `roxas_R`, `roxas_tg`, `ro_w_tg_R` ([source data](../src/overlays/ov030/data/)) |
| ov031 | 100.0% | 0 | Axel-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `axel_R`, `ax_h_L`, `axel_tg`, `ax_h_R` ([source data](../src/overlays/ov031/data/)) |
| ov032 | 35.3% | 22 | Xigbar-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `ef_b_03`, `ef_b_02`, `ef_b_00`, `ef_b_01` ([source data](../src/overlays/ov032/data/)) |
| ov033 | 63.0% | 10 | Saix-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `saix_tg`, `sa_h_L`, `sa_h_R`, `saix_R` ([source data](../src/overlays/ov033/data/)) |
| ov034 | 57.6% | 14 | Xaldin-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xaldin_R`, `xaldin_tg`, `ba/ch/xa/def.p.z`, `ba/ch/xa/def_h.p.z` ([source data](../src/overlays/ov034/data/)) |
| ov035 | 67.7% | 10 | Sora-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `sora_R`, `so_left_dummy`, `sora_tg`, `so_w_tg00` ([source data](../src/overlays/ov035/data/)) |
| ov036 | 75.0% | 10 | Demyx-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `demyx_tg`, `demyx_R`, `ba/ch/de/def.p.z`, `ba/ch/de/def_h.p.z` ([source data](../src/overlays/ov036/data/)) |
| ov037 | 67.7% | 10 | Larxene-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `la_h_L`, `larxene_R`, `larxene_tg`, `la_h_R` ([source data](../src/overlays/ov037/data/)) |
| ov038 | 100.0% | 0 | Lexaeus-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `lexaeus_R`, `le_h_R`, `lexaeus_tg`, `ba/ch/le/li_e3.p.z` ([source data](../src/overlays/ov038/data/)) |
| ov039 | 56.8% | 16 | Luxord-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `luxord_R`, `luxord_tg`, `ba/ch/lu/li_e1.p.z`, `ba/ch/lu/def.p.z` ([source data](../src/overlays/ov039/data/)) |
| ov040 | 71.9% | 9 | Marluxia-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `marluxia_R`, `ma_h_R`, `marluxia_tg`, `ba/ch/ma/li_e2.p.z` ([source data](../src/overlays/ov040/data/)) |
| ov041 | 75.8% | 8 | Riku-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `riku_tg`, `riku_R`, `ri_h_R`, `ba/ch/ri/def.p.z` ([source data](../src/overlays/ov041/data/)) |
| ov042 | 67.9% | 9 | Vexen-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `vexen_R`, `ve_w_tg`, `vexen_tg`, `ba/ch/ve/def.p.z` ([source data](../src/overlays/ov042/data/)) |
| ov043 | 26.1% | 34 | Xemnas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xe_h_R`, `xemnas_R`, `xe_h_L`, `xemnas_tg` ([source data](../src/overlays/ov043/data/)) |
| ov044 | 100.0% | 0 | Xion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xion_tg`, `_R`, `xo_h_R`, `ba/ch/xo/etc.p.z` ([source data](../src/overlays/ov044/data/)) |
| ov045 | 63.0% | 10 | Zexion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `zexion_R`, `zexion_tg`, `ba/ch/ze/def.p.z`, `ba/ch/ze/def_h.p.z` ([source data](../src/overlays/ov045/data/)) |
| ov046 | 75.0% | 9 | Mickey-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `mi_w_tg_R`, `mickey_tg`, `mickey_R`, `ba/ch/mi/def.p.z` ([source data](../src/overlays/ov046/data/)) |
| ov047 | 100.0% | 0 | Donald-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `donald_R`, `do_h_R`, `donald_tg`, `ba/ch/do/def.p.z` ([source data](../src/overlays/ov047/data/)) |
| ov048 | 69.7% | 10 | Goofy-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `goofy_R`, `go_h_R`, `goofy_tg`, `ba/ch/go/li_e2.p.z` ([source data](../src/overlays/ov048/data/)) |
| ov049 | 69.0% | 9 | Roxas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `roxas_tg`, `roxas_R`, `ro_h_L`, `ro_h_R` ([source data](../src/overlays/ov049/data/)) |
| ov050 | 100.0% | 0 | Axel-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `axel_R`, `ax_h_L`, `axel_tg`, `ax_h_R` ([source data](../src/overlays/ov050/data/)) |
| ov051 | 63.0% | 10 | Saix-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `saix_tg`, `sa_h_L`, `sa_h_R`, `saix_R` ([source data](../src/overlays/ov051/data/)) |
| ov052 | 35.3% | 22 | Xigbar-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `ef_b_03`, `ef_b_02`, `ef_b_00`, `ef_b_01` ([source data](../src/overlays/ov052/data/)) |
| ov053 | 57.6% | 14 | Xaldin-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xaldin_R`, `xaldin_tg`, `ba/ch/xa/def.p.z`, `ba/ch/xa/def_h.p.z` ([source data](../src/overlays/ov053/data/)) |
| ov054 | 67.7% | 10 | Sora-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `sora_R`, `so_left_dummy`, `sora_tg`, `so_w_tg00` ([source data](../src/overlays/ov054/data/)) |
| ov055 | 75.0% | 10 | Demyx-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `demyx_tg`, `demyx_R`, `ba/ch/de/def.p.z`, `ba/ch/de/def_h.p.z` ([source data](../src/overlays/ov055/data/)) |
| ov056 | 67.7% | 10 | Larxene-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `la_h_L`, `larxene_R`, `larxene_tg`, `la_h_R` ([source data](../src/overlays/ov056/data/)) |
| ov057 | 100.0% | 0 | Lexaeus-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `lexaeus_R`, `le_h_R`, `lexaeus_tg`, `ba/ch/le/li_e3.p.z` ([source data](../src/overlays/ov057/data/)) |
| ov058 | 56.8% | 16 | Luxord-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `luxord_R`, `luxord_tg`, `ba/ch/lu/li_e1.p.z`, `ba/ch/lu/def.p.z` ([source data](../src/overlays/ov058/data/)) |
| ov059 | 71.9% | 9 | Marluxia-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `marluxia_R`, `ma_h_R`, `marluxia_tg`, `ba/ch/ma/li_e2.p.z` ([source data](../src/overlays/ov059/data/)) |
| ov060 | 75.8% | 8 | Riku-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `riku_tg`, `riku_R`, `ri_h_R`, `ba/ch/ri/def.p.z` ([source data](../src/overlays/ov060/data/)) |
| ov061 | 67.9% | 9 | Vexen-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `vexen_R`, `ve_w_tg`, `vexen_tg`, `ba/ch/ve/def.p.z` ([source data](../src/overlays/ov061/data/)) |
| ov062 | 26.1% | 34 | Xemnas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xe_h_R`, `xemnas_R`, `xe_h_L`, `xemnas_tg` ([source data](../src/overlays/ov062/data/)) |
| ov063 | 100.0% | 0 | Xion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xion_tg`, `xion_R`, `xo_h_R`, `ba/ch/xo/etc.p.z` ([source data](../src/overlays/ov063/data/)) |
| ov064 | 63.0% | 10 | Zexion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `zexion_R`, `zexion_tg`, `ba/ch/ze/def.p.z`, `ba/ch/ze/def_h.p.z` ([source data](../src/overlays/ov064/data/)) |
| ov065 | 75.0% | 9 | Mickey-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `mi_w_tg_R`, `mickey_tg`, `mickey_R`, `ba/ch/mi/def.p.z` ([source data](../src/overlays/ov065/data/)) |
| ov066 | 100.0% | 0 | Donald-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `donald_R`, `do_h_R`, `donald_tg`, `ba/ch/do/def.p.z` ([source data](../src/overlays/ov066/data/)) |
| ov067 | 69.7% | 10 | Goofy-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `goofy_R`, `go_h_R`, `goofy_tg`, `ba/ch/go/li_e2.p.z` ([source data](../src/overlays/ov067/data/)) |
| ov068 | 69.0% | 9 | Roxas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `roxas_tg`, `roxas_R`, `ro_h_L`, `ro_h_R` ([source data](../src/overlays/ov068/data/)) |
| ov069 | 75.5% | 12 | Mission-list resources; exact screen not identified. | `UI/cm/msl_&.msi.z`, `UI/cm/msl_&.msi.z` ([source data](../src/overlays/ov069/data/)) |
| ov070 | 100.0% | 0 | Axel-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `axel_R`, `ax_h_L`, `axel_tg`, `ax_h_R` ([source data](../src/overlays/ov070/data/)) |
| ov071 | 63.0% | 10 | Saix-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `saix_tg`, `sa_h_L`, `sa_h_R`, `saix_R` ([source data](../src/overlays/ov071/data/)) |
| ov072 | 35.3% | 22 | Xigbar-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `ef_b_03`, `ef_b_02`, `ef_b_00`, `ef_b_01` ([source data](../src/overlays/ov072/data/)) |
| ov073 | 57.6% | 14 | Xaldin-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xaldin_R`, `xaldin_tg`, `ba/ch/xa/def.p.z`, `ba/ch/xa/def_h.p.z` ([source data](../src/overlays/ov073/data/)) |
| ov074 | 67.7% | 10 | Sora-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `sora_R`, `so_left_dummy`, `sora_tg`, `so_w_tg00` ([source data](../src/overlays/ov074/data/)) |
| ov075 | 75.0% | 10 | Demyx-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `demyx_tg`, `demyx_R`, `ba/ch/de/def.p.z`, `ba/ch/de/def_h.p.z` ([source data](../src/overlays/ov075/data/)) |
| ov076 | 67.7% | 10 | Larxene-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `la_h_L`, `larxene_R`, `larxene_tg`, `la_h_R` ([source data](../src/overlays/ov076/data/)) |
| ov077 | 100.0% | 0 | Lexaeus-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `lexaeus_R`, `le_h_R`, `lexaeus_tg`, `ba/ch/le/li_e3.p.z` ([source data](../src/overlays/ov077/data/)) |
| ov078 | 56.8% | 16 | Luxord-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `luxord_R`, `luxord_tg`, `ba/ch/lu/li_e1.p.z`, `ba/ch/lu/def.p.z` ([source data](../src/overlays/ov078/data/)) |
| ov079 | 71.9% | 9 | Marluxia-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `marluxia_R`, `ma_h_R`, `marluxia_tg`, `ba/ch/ma/li_e2.p.z` ([source data](../src/overlays/ov079/data/)) |
| ov080 | 75.8% | 8 | Riku-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `riku_tg`, `riku_R`, `ri_h_R`, `ba/ch/ri/def.p.z` ([source data](../src/overlays/ov080/data/)) |
| ov081 | 67.9% | 9 | Vexen-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `vexen_R`, `ve_w_tg`, `vexen_tg`, `ba/ch/ve/def.p.z` ([source data](../src/overlays/ov081/data/)) |
| ov082 | 100.0% | 0 | Xion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xion_tg`, `xion_R`, `xo_h_R`, `ba/ch/xo/etc.p.z` ([source data](../src/overlays/ov082/data/)) |
| ov083 | 63.0% | 10 | Zexion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `zexion_R`, `zexion_tg`, `ba/ch/ze/def.p.z`, `ba/ch/ze/def_h.p.z` ([source data](../src/overlays/ov083/data/)) |
| ov084 | 75.0% | 9 | Mickey-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `mi_w_tg_R`, `mickey_tg`, `mickey_R`, `ba/ch/mi/def.p.z` ([source data](../src/overlays/ov084/data/)) |
| ov085 | 100.0% | 0 | Donald-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `donald_R`, `do_h_R`, `donald_tg`, `ba/ch/do/def.p.z` ([source data](../src/overlays/ov085/data/)) |
| ov086 | 69.7% | 10 | Goofy-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `goofy_R`, `go_h_R`, `goofy_tg`, `ba/ch/go/li_e2.p.z` ([source data](../src/overlays/ov086/data/)) |
| ov087 | 69.0% | 9 | Roxas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `roxas_tg`, `roxas_R`, `ro_h_L`, `ro_h_R` ([source data](../src/overlays/ov087/data/)) |
| ov088 | 100.0% | 0 | Axel-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `axel_R`, `ax_h_L`, `axel_tg`, `ax_h_R` ([source data](../src/overlays/ov088/data/)) |
| ov089 | 63.0% | 10 | Saix-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `saix_tg`, `sa_h_L`, `sa_h_R`, `saix_R` ([source data](../src/overlays/ov089/data/)) |
| ov090 | 57.6% | 14 | Xaldin-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xaldin_R`, `xaldin_tg`, `ba/ch/xa/def.p.z`, `ba/ch/xa/def_h.p.z` ([source data](../src/overlays/ov090/data/)) |
| ov091 | 67.7% | 10 | Sora-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `sora_R`, `so_left_dummy`, `sora_tg`, `so_w_tg00` ([source data](../src/overlays/ov091/data/)) |
| ov092 | 75.0% | 10 | Demyx-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `demyx_tg`, `demyx_R`, `ba/ch/de/def.p.z`, `ba/ch/de/def_h.p.z` ([source data](../src/overlays/ov092/data/)) |
| ov093 | 67.7% | 10 | Larxene-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `la_h_L`, `larxene_R`, `larxene_tg`, `la_h_R` ([source data](../src/overlays/ov093/data/)) |
| ov094 | 92.3% | 3 | Lexaeus-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `lexaeus_R`, `le_h_R`, `lexaeus_tg`, `ba/ch/le/li_e3.p.z` ([source data](../src/overlays/ov094/data/)) |
| ov095 | 56.8% | 16 | Luxord-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `luxord_R`, `luxord_tg`, `ba/ch/lu/li_e1.p.z`, `ba/ch/lu/def.p.z` ([source data](../src/overlays/ov095/data/)) |
| ov096 | 71.9% | 9 | Marluxia-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `marluxia_R`, `ma_h_R`, `marluxia_tg`, `ba/ch/ma/li_e2.p.z` ([source data](../src/overlays/ov096/data/)) |
| ov097 | 75.8% | 8 | Riku-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `riku_tg`, `riku_R`, `ri_h_R`, `ba/ch/ri/def.p.z` ([source data](../src/overlays/ov097/data/)) |
| ov098 | 67.9% | 9 | Vexen-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `vexen_R`, `ve_w_tg`, `vexen_tg`, `ba/ch/ve/def.p.z` ([source data](../src/overlays/ov098/data/)) |
| ov099 | 100.0% | 0 | Xion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `xion_tg`, `xion_R`, `xo_h_R`, `ba/ch/xo/etc.p.z` ([source data](../src/overlays/ov099/data/)) |
| ov100 | 63.0% | 10 | Zexion-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `zexion_R`, `zexion_tg`, `ba/ch/ze/def.p.z`, `ba/ch/ze/def_h.p.z` ([source data](../src/overlays/ov100/data/)) |
| ov101 | 75.0% | 9 | Mickey-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `mi_w_tg_R`, `mickey_tg`, `mickey_R`, `ba/ch/mi/def.p.z` ([source data](../src/overlays/ov101/data/)) |
| ov102 | 100.0% | 0 | Donald-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `donald_R`, `do_h_R`, `donald_tg`, `ba/ch/do/def.p.z` ([source data](../src/overlays/ov102/data/)) |
| ov103 | 69.7% | 10 | Goofy-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `goofy_R`, `go_h_R`, `goofy_tg`, `ba/ch/go/li_e2.p.z` ([source data](../src/overlays/ov103/data/)) |
| ov104 | 69.0% | 9 | Roxas-specific character support: animation/weapon/effect resources; exact use of this copy unconfirmed. | `roxas_tg`, `roxas_R`, `ro_h_L`, `ro_h_R` ([source data](../src/overlays/ov104/data/)) |
| ov105 | 46.2% | 57 | Exact role not established. | No identifying text recovered in the scanned string files. |
| ov106 | 36.0% | 32 | Participates in multiplayer-session handling; also has event/display resources. | `dual3d_update`, `ev/EV_DP.p2`, `/UI/hcnt/arc_&`, `ba/ef/mi_&.p.z` ([source data](../src/overlays/ov106/data/)) |
| ov107 | 42.5% | 111 | Shared creature/combat support, called for damage, targeting and reactions. | `Ms/BL.bin`, `Ms/UP.bin`, `ba/ef/s_burn.p.z`, `ba/ef/s_frost.p.z` ([source data](../src/overlays/ov107/data/)) |
| ov114 | 76.7% | 10 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov114/data/)) |
| ov115 | 72.3% | 13 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov115/data/)) |
| ov116 | 72.3% | 13 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov116/data/)) |
| ov117 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov117/data/)) |
| ov118 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov118/data/)) |
| ov119 | 58.9% | 23 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov119/data/)) |
| ov120 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov120/data/)) |
| ov121 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov121/data/)) |
| ov122 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov122/data/)) |
| ov123 | 74.5% | 12 | Exact in-game identity not established from this scan. | `headcon` ([source data](../src/overlays/ov123/data/)) |
| ov124 | 74.5% | 12 | Exact in-game identity not established from this scan. | `headcon` ([source data](../src/overlays/ov124/data/)) |
| ov125 | 56.1% | 29 | Exact in-game identity not established from this scan. | `tag_L`, `tag_R` ([source data](../src/overlays/ov125/data/)) |
| ov126 | 56.1% | 29 | Exact in-game identity not established from this scan. | `tag_L`, `tag_R` ([source data](../src/overlays/ov126/data/)) |
| ov127 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov127/data/)) |
| ov128 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov128/data/)) |
| ov129 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov129/data/)) |
| ov130 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov130/data/)) |
| ov131 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov131/data/)) |
| ov132 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov132/data/)) |
| ov133 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov133/data/)) |
| ov134 | 79.5% | 8 | Exact in-game identity not established from this scan. | `move`, `guru0` ([source data](../src/overlays/ov134/data/)) |
| ov135 | 79.5% | 8 | Exact in-game identity not established from this scan. | `move`, `guru0` ([source data](../src/overlays/ov135/data/)) |
| ov136 | 79.5% | 8 | Exact in-game identity not established from this scan. | `move`, `guru0` ([source data](../src/overlays/ov136/data/)) |
| ov137 | 70.3% | 19 | Exact in-game identity not established from this scan. | `eff_tag`, `017`, `move` ([source data](../src/overlays/ov137/data/)) |
| ov138 | 70.3% | 19 | Exact in-game identity not established from this scan. | `eff_tag`, `017`, `move` ([source data](../src/overlays/ov138/data/)) |
| ov139 | 77.8% | 10 | Exact in-game identity not established from this scan. | `I_move` ([source data](../src/overlays/ov139/data/)) |
| ov140 | 77.8% | 10 | Exact in-game identity not established from this scan. | `I_move` ([source data](../src/overlays/ov140/data/)) |
| ov141 | 100.0% | 0 | Exact in-game identity not established from this scan. | `root`, `M_Loudness` ([source data](../src/overlays/ov141/data/)) |
| ov142 | 100.0% | 0 | Exact in-game identity not established from this scan. | `root`, `M_Loudness` ([source data](../src/overlays/ov142/data/)) |
| ov143 | 100.0% | 0 | Exact in-game identity not established from this scan. | `root`, `M_Loudness` ([source data](../src/overlays/ov143/data/)) |
| ov144 | 55.3% | 17 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov144/data/)) |
| ov145 | 55.3% | 17 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov145/data/)) |
| ov146 | 56.8% | 38 | Exact in-game identity not established from this scan. | `Broot` ([source data](../src/overlays/ov146/data/)) |
| ov147 | 100.0% | 0 | Exact in-game identity not established from this scan. | `S_fire`, `S_move` ([source data](../src/overlays/ov147/data/)) |
| ov148 | 100.0% | 0 | Exact in-game identity not established from this scan. | `S_fire`, `S_move` ([source data](../src/overlays/ov148/data/)) |
| ov149 | 100.0% | 0 | Exact in-game identity not established from this scan. | `root`, `MF_Loudness` ([source data](../src/overlays/ov149/data/)) |
| ov150 | 100.0% | 0 | Exact in-game identity not established from this scan. | `root`, `MF_Loudness` ([source data](../src/overlays/ov150/data/)) |
| ov151 | 76.8% | 13 | Exact in-game identity not established from this scan. | `root`, `MW_Loudness` ([source data](../src/overlays/ov151/data/)) |
| ov152 | 76.8% | 13 | Exact in-game identity not established from this scan. | `root`, `MW_Loudness` ([source data](../src/overlays/ov152/data/)) |
| ov153 | 77.8% | 10 | Exact in-game identity not established from this scan. | `headcon` ([source data](../src/overlays/ov153/data/)) |
| ov154 | 77.8% | 10 | Exact in-game identity not established from this scan. | `headcon` ([source data](../src/overlays/ov154/data/)) |
| ov155 | 77.8% | 10 | Exact in-game identity not established from this scan. | `headcon` ([source data](../src/overlays/ov155/data/)) |
| ov156 | 76.0% | 12 | Exact in-game identity not established from this scan. | `head02`, `headcon` ([source data](../src/overlays/ov156/data/)) |
| ov157 | 76.0% | 12 | Exact in-game identity not established from this scan. | `head02`, `headcon` ([source data](../src/overlays/ov157/data/)) |
| ov158 | 73.4% | 17 | Exact in-game identity not established from this scan. | `eff_tag`, `036`, `move` ([source data](../src/overlays/ov158/data/)) |
| ov159 | 73.4% | 17 | Exact in-game identity not established from this scan. | `eff_tag`, `036`, `move` ([source data](../src/overlays/ov159/data/)) |
| ov160 | 68.3% | 20 | Exact in-game identity not established from this scan. | `eff_tag`, `037`, `move` ([source data](../src/overlays/ov160/data/)) |
| ov161 | 85.0% | 9 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov161/data/)) |
| ov162 | 85.0% | 9 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov162/data/)) |
| ov163 | 82.1% | 10 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov163/data/)) |
| ov164 | 82.1% | 10 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov164/data/)) |
| ov165 | 82.1% | 10 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov165/data/)) |
| ov166 | 80.0% | 11 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov166/data/)) |
| ov167 | 80.0% | 11 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov167/data/)) |
| ov168 | 80.0% | 11 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov168/data/)) |
| ov169 | 80.7% | 11 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov169/data/)) |
| ov170 | 80.7% | 11 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov170/data/)) |
| ov171 | 76.8% | 13 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov171/data/)) |
| ov172 | 76.8% | 13 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov172/data/)) |
| ov173 | 68.6% | 16 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov173/data/)) |
| ov174 | 68.6% | 16 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov174/data/)) |
| ov175 | 85.5% | 8 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov175/data/)) |
| ov176 | 85.5% | 8 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov176/data/)) |
| ov177 | 85.5% | 8 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov177/data/)) |
| ov178 | 75.8% | 15 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov178/data/)) |
| ov179 | 75.8% | 15 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov179/data/)) |
| ov180 | 75.8% | 15 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov180/data/)) |
| ov181 | 82.7% | 9 | Exact in-game identity not established from this scan. | `B_Move` ([source data](../src/overlays/ov181/data/)) |
| ov182 | 82.7% | 9 | Exact in-game identity not established from this scan. | `B_Move` ([source data](../src/overlays/ov182/data/)) |
| ov183 | 82.7% | 9 | Exact in-game identity not established from this scan. | `B_Move` ([source data](../src/overlays/ov183/data/)) |
| ov184 | 82.7% | 9 | Exact in-game identity not established from this scan. | `B_Move` ([source data](../src/overlays/ov184/data/)) |
| ov185 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov185/data/)) |
| ov186 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov186/data/)) |
| ov187 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov187/data/)) |
| ov188 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov188/data/)) |
| ov189 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov189/data/)) |
| ov190 | 100.0% | 0 | Individual creature/character: health, hit reactions, targeting and timed actions; identity unknown. | `move` ([source data](../src/overlays/ov190/data/)) |
| ov191 | 72.2% | 15 | Exact in-game identity not established from this scan. | `head02`, `headcon` ([source data](../src/overlays/ov191/data/)) |
| ov192 | 72.2% | 15 | Exact in-game identity not established from this scan. | `head02`, `headcon` ([source data](../src/overlays/ov192/data/)) |
| ov193 | 72.2% | 15 | Exact in-game identity not established from this scan. | `head02`, `headcon` ([source data](../src/overlays/ov193/data/)) |
| ov194 | 78.0% | 11 | Exact in-game identity not established from this scan. | `tag_00`, `move`, `guru0` ([source data](../src/overlays/ov194/data/)) |
| ov195 | 78.0% | 11 | Exact in-game identity not established from this scan. | `tag_00`, `move`, `guru0` ([source data](../src/overlays/ov195/data/)) |
| ov196 | 78.0% | 11 | Exact in-game identity not established from this scan. | `tag_00`, `move`, `guru0` ([source data](../src/overlays/ov196/data/)) |
| ov197 | 100.0% | 0 | Exact in-game identity not established from this scan. | `S_fire`, `BS_move` ([source data](../src/overlays/ov197/data/)) |
| ov198 | 100.0% | 0 | Exact in-game identity not established from this scan. | `S_fire`, `BS_move` ([source data](../src/overlays/ov198/data/)) |
| ov199 | 100.0% | 0 | Exact in-game identity not established from this scan. | `S_fire`, `BS_move` ([source data](../src/overlays/ov199/data/)) |
| ov200 | 83.3% | 10 | Exact in-game identity not established from this scan. | `tag_L`, `tag_R` ([source data](../src/overlays/ov200/data/)) |
| ov201 | 83.3% | 10 | Exact in-game identity not established from this scan. | `tag_L`, `tag_R` ([source data](../src/overlays/ov201/data/)) |
| ov202 | 76.8% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov202/data/)) |
| ov203 | 76.8% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov203/data/)) |
| ov204 | 66.7% | 18 | Exact in-game identity not established from this scan. | `B_Imove` ([source data](../src/overlays/ov204/data/)) |
| ov205 | 66.7% | 18 | Exact in-game identity not established from this scan. | `B_Imove` ([source data](../src/overlays/ov205/data/)) |
| ov206 | 76.2% | 15 | Exact in-game identity not established from this scan. | `Target01`, `large_move` ([source data](../src/overlays/ov206/data/)) |
| ov207 | 76.2% | 15 | Exact in-game identity not established from this scan. | `Target01`, `large_move` ([source data](../src/overlays/ov207/data/)) |
| ov208 | 80.2% | 16 | Exact in-game identity not established from this scan. | `Rock_move` ([source data](../src/overlays/ov208/data/)) |
| ov209 | 81.5% | 15 | Exact in-game identity not established from this scan. | `Rock_move` ([source data](../src/overlays/ov209/data/)) |
| ov210 | 77.1% | 19 | Exact in-game identity not established from this scan. | `n_shadow`, `ns_move` ([source data](../src/overlays/ov210/data/)) |
| ov211 | 77.1% | 19 | Exact in-game identity not established from this scan. | `n_shadow`, `ns_move` ([source data](../src/overlays/ov211/data/)) |
| ov212 | 79.0% | 25 | Exact in-game identity not established from this scan. | `tag_bero`, `tagE01`, `move` ([source data](../src/overlays/ov212/data/)) |
| ov213 | 44.0% | 65 | Exact in-game identity not established from this scan. | `sword` ([source data](../src/overlays/ov213/data/)) |
| ov214 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov214/data/)) |
| ov215 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov215/data/)) |
| ov216 | 84.0% | 8 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov216/data/)) |
| ov217 | 84.0% | 8 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov217/data/)) |
| ov218 | 50.7% | 36 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov218/data/)) |
| ov219 | 54.8% | 19 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov219/data/)) |
| ov220 | 62.0% | 19 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov220/data/)) |
| ov221 | 78.6% | 18 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov221/data/)) |
| ov222 | 78.6% | 18 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov222/data/)) |
| ov223 | 67.0% | 30 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov223/data/)) |
| ov224 | 76.2% | 20 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov224/data/)) |
| ov225 | 73.6% | 23 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov225/data/)) |
| ov226 | 71.2% | 23 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov226/data/)) |
| ov227 | 64.3% | 30 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov227/data/)) |
| ov228 | 82.7% | 14 | Exact in-game identity not established from this scan. | `A_move` ([source data](../src/overlays/ov228/data/)) |
| ov229 | 82.7% | 14 | Exact in-game identity not established from this scan. | `A_move` ([source data](../src/overlays/ov229/data/)) |
| ov230 | 74.3% | 19 | Exact in-game identity not established from this scan. | `AE_move` ([source data](../src/overlays/ov230/data/)) |
| ov231 | 80.0% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov231/data/)) |
| ov232 | 80.0% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov232/data/)) |
| ov233 | 82.7% | 14 | Exact in-game identity not established from this scan. | `A_move` ([source data](../src/overlays/ov233/data/)) |
| ov234 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov234/data/)) |
| ov235 | 35.1% | 63 | Xion-related object/form; XionShare and B50A resources. Exact fight phase unconfirmed. | `Ms/XionShare.p`, `B50A_01body`, `B_spine01`, `1_1_sword` ([source data](../src/overlays/ov235/data/)) |
| ov236 | 55.6% | 68 | Exact in-game identity not established from this scan. | `B_body`, `B_head02`, `GA_move`, `B_LArm01` ([source data](../src/overlays/ov236/data/)) |
| ov237 | 46.5% | 46 | Exact in-game identity not established from this scan. | `R_yubi`, `L_hand`, `L_yubi`, `R_hand` ([source data](../src/overlays/ov237/data/)) |
| ov238 | 45.8% | 39 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov238/data/)) |
| ov239 | 59.5% | 17 | Exact in-game identity not established from this scan. | `Ms/NBShare.p`, `move` ([source data](../src/overlays/ov239/data/)) |
| ov240 | 64.3% | 15 | Exact in-game identity not established from this scan. | `Ms/NBShare.p`, `move` ([source data](../src/overlays/ov240/data/)) |
| ov241 | 61.5% | 10 | Exact in-game identity not established from this scan. | `tag_02`, `tag_01`, `tag_00`, `move` ([source data](../src/overlays/ov241/data/)) |
| ov242 | 61.5% | 10 | Exact in-game identity not established from this scan. | `tag_02`, `tag_01`, `tag_00`, `move` ([source data](../src/overlays/ov242/data/)) |
| ov243 | 59.3% | 11 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov243/data/)) |
| ov244 | 58.0% | 60 | Exact in-game identity not established from this scan. | `DS01`, `DM002` ([source data](../src/overlays/ov244/data/)) |
| ov245 | 59.1% | 108 | Exact in-game identity not established from this scan. | `tag_00`, `tag_item`, `tag_tire_F`, `tag_tire_R` ([source data](../src/overlays/ov245/data/)) |
| ov246 | 75.0% | 16 | Exact in-game identity not established from this scan. | `eff_tag`, `038`, `move` ([source data](../src/overlays/ov246/data/)) |
| ov247 | 75.0% | 16 | Exact in-game identity not established from this scan. | `eff_tag`, `038`, `move` ([source data](../src/overlays/ov247/data/)) |
| ov248 | 75.6% | 19 | Exact in-game identity not established from this scan. | `AI_move` ([source data](../src/overlays/ov248/data/)) |
| ov249 | 78.2% | 17 | Exact in-game identity not established from this scan. | `AF_move` ([source data](../src/overlays/ov249/data/)) |
| ov250 | 73.1% | 14 | Exact in-game identity not established from this scan. | `B2_Move` ([source data](../src/overlays/ov250/data/)) |
| ov251 | 73.1% | 14 | Exact in-game identity not established from this scan. | `B2_Move` ([source data](../src/overlays/ov251/data/)) |
| ov252 | 19.1% | 76 | Exact in-game identity not established from this scan. | `01_B_head01`, `01_B_body02`, `core`, `B3_01body` ([source data](../src/overlays/ov252/data/)) |
| ov253 | 47.3% | 87 | Exact in-game identity not established from this scan. | `tag01`, `tag00`, `tag02`, `tag03` ([source data](../src/overlays/ov253/data/)) |
| ov254 | 55.7% | 81 | Exact in-game identity not established from this scan. | `SL`, `SR`, `core`, `head01` ([source data](../src/overlays/ov254/data/)) |
| ov255 | 39.3% | 68 | Xion-related object/form; XionShare and B50B resources. Exact fight phase unconfirmed. | `Ms/XionShare.p`, `B50B_01body`, `B_spine01`, `T2` ([source data](../src/overlays/ov255/data/)) |
| ov256 | 41.6% | 66 | Exact in-game identity not established from this scan. | `tag00`, `tag01`, `tag02`, `tag03` ([source data](../src/overlays/ov256/data/)) |
| ov257 | 34.7% | 62 | Xion-related object/form; XionShare and B50C resources. Exact fight phase unconfirmed. | `tag02_FL`, `tag02_BR`, `tag02_BL`, `tag02_FR` ([source data](../src/overlays/ov257/data/)) |
| ov258 | 39.5% | 49 | Exact in-game identity not established from this scan. | `tag_buki_L`, `tag_buki_R`, `tagB_L`, `tagB_R` ([source data](../src/overlays/ov258/data/)) |
| ov259 | 37.2% | 76 | Exact in-game identity not established from this scan. | `sa_h_R`, `move`, `tag00_1` ([source data](../src/overlays/ov259/data/)) |
| ov260 | 38.2% | 68 | Exact in-game identity not established from this scan. | `wA`, `B013move` ([source data](../src/overlays/ov260/data/)) |
| ov261 | 51.4% | 17 | Exact in-game identity not established from this scan. | `zero_ef_dummy` ([source data](../src/overlays/ov261/data/)) |
| ov262 | 51.4% | 17 | Exact in-game identity not established from this scan. | `zero_ef_dummy` ([source data](../src/overlays/ov262/data/)) |
| ov263 | 80.0% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov263/data/)) |
| ov264 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov264/data/)) |
| ov265 | 80.0% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov265/data/)) |
| ov266 | 78.2% | 26 | Exact in-game identity not established from this scan. | `tag_bero`, `tagE01`, `move` ([source data](../src/overlays/ov266/data/)) |
| ov267 | 78.2% | 26 | Exact in-game identity not established from this scan. | `tag_bero`, `tagE01`, `move` ([source data](../src/overlays/ov267/data/)) |
| ov268 | 79.0% | 17 | Exact in-game identity not established from this scan. | `SRock_move` ([source data](../src/overlays/ov268/data/)) |
| ov269 | 78.0% | 11 | Exact in-game identity not established from this scan. | `tag_00`, `move`, `guru0` ([source data](../src/overlays/ov269/data/)) |
| ov270 | 78.0% | 11 | Exact in-game identity not established from this scan. | `tag_00`, `move`, `guru0` ([source data](../src/overlays/ov270/data/)) |
| ov271 | 83.3% | 10 | Exact in-game identity not established from this scan. | `tag_L`, `tag_R` ([source data](../src/overlays/ov271/data/)) |
| ov272 | 58.9% | 23 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov272/data/)) |
| ov273 | 44.8% | 64 | Exact in-game identity not established from this scan. | `sword` ([source data](../src/overlays/ov273/data/)) |
| ov274 | 76.2% | 15 | Exact in-game identity not established from this scan. | `Target01`, `Slarge_move` ([source data](../src/overlays/ov274/data/)) |
| ov275 | 76.2% | 15 | Exact in-game identity not established from this scan. | `Target01`, `Slarge_move` ([source data](../src/overlays/ov275/data/)) |
| ov276 | 62.0% | 19 | Exact in-game identity not established from this scan. | `SA_move` ([source data](../src/overlays/ov276/data/)) |
| ov277 | 58.0% | 60 | Exact in-game identity not established from this scan. | `DS01`, `UpperArm`, `DM002` ([source data](../src/overlays/ov277/data/)) |
| ov278 | 54.9% | 69 | Exact in-game identity not established from this scan. | `B_body`, `B_head02`, `GA_move`, `B_LArm01` ([source data](../src/overlays/ov278/data/)) |
| ov279 | 58.9% | 23 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov279/data/)) |
| ov280 | 80.0% | 13 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov280/data/)) |
| ov281 | 100.0% | 0 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov281/data/)) |
| ov282 | 78.3% | 18 | Multi-part creature/character with movement and attacks; exact identity unknown. | `Sns_move` ([source data](../src/overlays/ov282/data/)) |
| ov283 | 48.1% | 42 | Object with Xigbar-style hand labels; identity/role not confirmed. | `xig_h_L`, `xig_h_R` ([source data](../src/overlays/ov283/data/)) |
| ov284 | 57.6% | 14 | Exact in-game identity not established from this scan. | `tag03` ([source data](../src/overlays/ov284/data/)) |
| ov285 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov285/data/)) |
| ov286 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov286/data/)) |
| ov287 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov287/data/)) |
| ov288 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov288/data/)) |
| ov289 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov289/data/)) |
| ov290 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov290/data/)) |
| ov291 | 65.6% | 11 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov291/data/)) |
| ov292 | 100.0% | 0 | Exact in-game identity not established from this scan. | `body` ([source data](../src/overlays/ov292/data/)) |
| ov293 | 67.6% | 12 | Exact in-game identity not established from this scan. | `move` ([source data](../src/overlays/ov293/data/)) |
| ov294 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov294/data/)) |
| ov295 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov295/data/)) |
| ov296 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov296/data/)) |
| ov297 | 59.0% | 16 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov297/data/)) |
| ov298 | 54.1% | 17 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov298/data/)) |
| ov299 | 64.5% | 11 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov299/data/)) |
| ov300 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov300/data/)) |
| ov301 | 100.0% | 0 | Exact in-game identity not established from this scan. | No identifying text recovered in the scanned string files. ([source data](../src/overlays/ov301/data/)) |
| ov302 | 100.0% | 0 | World-name text resources; exact screen/role not identified. | `UI/cm/str/world_id_&.s.z` ([source data](../src/overlays/ov302/data/)) |

Numbers missing from the progress snapshot, including ov018 and ov108–ov113, have not been silently assigned a role or percentage.
