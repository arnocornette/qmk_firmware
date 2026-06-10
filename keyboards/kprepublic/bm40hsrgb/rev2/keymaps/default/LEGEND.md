# BM40RGB v2 — Keymap Legend (niri)

QMK keymap for **kprepublic BM40RGBH v2** — 40% 47-key ortho
(`LAYOUT_ortho_4x12_1x2uC`). Rows 0-2 are full 12-wide; bottom row
has 11 keys with a single **2u** key at centre (col 5-6).

**Target:** niri (Wayland scrollable tiling) + LazyVim.
**Design rule:** all layers are momentary (`MO` / `LT` only). No
toggles, no tri-layers. Every layer reachable directly from BASE —
no layer-from-layer hops.

---

## Layer Overview

| # | Layer | Purpose                                            |
|---|-------|----------------------------------------------------|
| 0 | BASE  | QWERTY + home-row mods                             |
| 1 | NAV   | Vim hjkl, arrows, PgUp/Dn, clipboard               |
| 2 | NUM   | Number row, F1-F12, math symbols                   |
| 3 | SYM   | Shifted symbols, brackets, quotes                  |
| 4 | MOUSE | Cursor, wheel, buttons, speed (ACL0/2)             |
| 5 | NIRI  | niri WM: workspaces, windows, apps, monitors       |
| 6 | MEDIA | Volume, brightness, transport                      |
| 7 | LSP   | LazyVim LSP / DAP / Telescope / Trouble / Git      |

---

## Layer Activation

All momentary, all from BASE:

| Layer  | Activator                                 | Tap action |
|--------|-------------------------------------------|------------|
| NUM    | hold left-inner thumb (`TH_TAB`)          | Tab        |
| NAV    | hold left-outer thumb (`TH_SPC`, 2u)      | Space      |
| SYM    | hold right-outer thumb (`TH_BSP`)         | Backspace  |
| NIRI   | hold right-inner thumb (`TH_ENT`)         | Enter      |
| MOUSE  | hold bottom-left pinky (`MO_MSE`)         | —          |
| LSP    | hold top-left pinky (`MO_LSP`, row 0 [0]) | —          |
| MEDIA  | hold top-right pinky (`MO_MED`, row 0 [11])| —         |

`Tab` and `Backspace` stay on the thumb LT keys (`TH_TAB` / `TH_BSP`);
the top-row pinky corners are repurposed as layer keys.

---

## Home-Row Mods (BASE, tap/hold)

| Key | Hold         | Tap |
|-----|--------------|-----|
| A   | LGUI (Super) | a   |
| S   | LALT         | s   |
| D   | LCTL         | d   |
| F   | LSFT         | f   |
| J   | RSFT         | j   |
| K   | RCTL         | k   |
| L   | RALT         | l   |
| ;   | RGUI         | ;   |
| Esc | LCTL         | Esc |

Tapping terms are staggered per finger (170-220 ms) — see
`get_tapping_term` in `keymap.c`.

---

## Tap-Dance

| Keys      | Single | Double |
|-----------|--------|--------|
| `TD_LBRC` | `[`    | `{`    |
| `TD_RBRC` | `]`    | `}`    |
| `TD_SLSH` | `/`    | `?`    |
| `TD_GRV`  | `` ` `` | `~`   |

---

## Layer 0 — BASE

| LSP   | Q | W | E | R | T | Y | U | I | O | P | MED |
|-------|---|---|---|---|---|---|---|---|---|---|-----|
| CtEsc | **A**/Gui | **S**/Alt | **D**/Ctl | **F**/Sft | G | H | **J**/Sft | **K**/Ctl | **L**/Alt | **;**/Gui | `'` |
| LSft  | Z | X | C | V | B | N | M | , | . | /→? | RSft |
| MOUSE | LGui | LAlt | LCtl | NUM·Tab | NAV·Space (2u) | SYM·BSpc | NIRI·Ent | ← | ↓ | → |

Bold keys = home-row mods (hold = modifier, tap = letter).
`/→?` is tap-dance. Top corners `LSP`/`MED` are `MO()` layer keys.

---

## Layer 1 — NAV

| Esc  | PgUp | BSpc | ↑ | Del | PgDn | ✕ | WBak | ✕ | WFwd | ✕ | Del |
|------|------|------|---|-----|------|---|------|---|------|---|-----|
| Home | ← | ↓ | → | End | ✕ | ← | ↓ | ↑ | → | ✕ | ✕ |
| ▽ | Undo | Cut | Copy | Paste | ✕ | ✕ | ✕ | ✕ | ✕ | ✕ | ▽ |
| ▽ | ✕ | ✕ | ✕ | ✕ | ▽ (2u) | ✕ | ✕ | ✕ | ✕ | ✕ |

`▽` = transparent (falls through to BASE). `✕` = no-op.
`WBak`/`WFwd` = browser back/forward.

---

## Layer 2 — NUM

| 1  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |
|----|---|---|---|---|---|---|---|---|---|---|---|
| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10 | F11 | F12 |
| /  | = | * | + | - | ( | 0 | , | . | ✕ | ▽ | ✕ |
| ▽  | ✕ | ✕ | ✕ | ▽ | Space (2u) | ✕ | ✕ | ✕ | ✕ | ✕ |

2u thumb is Space so `42 items` types without releasing the layer.

---

## Layer 3 — SYM

| ~  | ! | @ | # | $ | % | ^ | & | * | ( | ) | _ |
|----|---|---|---|---|---|---|---|---|---|---|---|
| \\ | \| | { | } | + | = | `[`/`{` | `]`/`}` | < | > | " | ▽ |
| ✕  | `` ` `` | ~ | ( | ) | - | _ | / | ? | : | ; | ▽ |
| ✕  | ✕ | ✕ | ✕ | ✕ | ✕ | ▽ (2u) | ✕ | ✕ | ✕ | ✕ |

Row 1 cols 6-7 are tap-dance (`TD_LBRC` / `TD_RBRC`).

---

## Layer 4 — MOUSE

| ✕ | ✕ | ✕ | MsUp | ✕ | WhUp | ✕ | BTN4 | BTN5 | ✕ | ✕ | ✕ |
|---|---|---|------|---|------|---|------|------|---|---|---|
| ✕ | ✕ | MsLft | MsDn | MsRt | WhDn | MsLft | MsDn | MsUp | MsRt | ✕ | ✕ |
| ▽ | ✕ | WhLft | ✕ | WhRt | ✕ | BTN3 | BTN1 | BTN2 | ✕ | ✕ | ▽ |
| ▽ | ✕ | ✕ | ✕ | BTN3 | BTN1 (2u) | BTN2 | ACL0 | ACL2 | ✕ | ✕ |

- Right hjkl = cursor movement. Left col 2-4 = wheel.
- `BTN1/2/3` on thumbs and right-hand row 2.
- `BTN4/5` = browser back/forward.
- `ACL0` = slow, `ACL2` = fast (held, not sticky).

---

## Layer 5 — NIRI (Mod = Super/LGUI)

| WS1    | WS2  | WS3   | WS4   | WS5  | WS6  | WS7  | WS8  | WS9  | WSlast | Col- | Col+ |
|--------|------|-------|-------|------|------|------|------|------|--------|------|------|
| Files  | CEx  | WSPrv | WSNxt | Shot | Chet | FocL | FocD | FocU | FocR   | MonL | MonR |
| ▽      | Lock | MvML  | MvMR  | Ht-  | Ht+  | MvL  | MvD  | MvU  | MvR    | CMax | ▽    |
| ▽      | Flt  | Sess  | Term  | Lch  | Brw (2u) | Kil | Pwr | Ctr  | Tab   | Full |

**Workspace row** (WS1-9, WSlast) — modifier composition via `tap_code16`:

- Tap = focus workspace (`Mod+N`)
- **Shift + tap** = move-window-to-workspace (`Mod+Shift+N`)  *[niri binds 1-5]*
- **Ctrl + tap** = move-column-to-workspace (`Mod+Ctrl+N`)

**Monitor-up/down are not on dedicated keys** — compose instead:

- `Ctrl + FocU/FocD` → focus-monitor-up/down (`Mod+Ctrl+K/J`)
- `Shift+Ctrl + FocU/FocD` → move-column-to-monitor-up/down

Ctrl on home-row = `D` / `K`; Shift = `F` / `J`.

**Command reference:**

| Binding | Action                          | niri shortcut |
|---------|---------------------------------|---------------|
| Lch     | launcher (noctalia)             | Mod+D         |
| Term    | alacritty                       | Mod+Enter     |
| Brw     | brave                           | Mod+B         |
| Files   | nautilus                        | Mod+E         |
| Shot    | screenshot                      | Mod+Shift+S   |
| Chet    | hotkey-overlay                  | Mod+Shift+Esc |
| Lock    | noctalia lock                   | Mod+Alt+L     |
| Sess    | noctalia session menu           | Mod+Shift+Q   |
| Pwr     | power-off-monitors              | Mod+Shift+P   |
| Kil     | close-window                    | Mod+Q         |
| Full    | fullscreen-window               | Mod+F         |
| Flt     | toggle-window-floating          | Mod+T         |
| Tab     | toggle-column-tabbed-display    | Mod+W         |
| Ctr     | center-column                   | Mod+C         |
| CMax    | maximize-column                 | Mod+Shift+C   |
| CEx     | expand-column-to-available-width | Mod+Ctrl+F    |
| WSPrv   | focus-workspace-up              | Mod+I         |
| WSNxt   | focus-workspace-down            | Mod+U         |
| WSlast  | focus-workspace-previous        | Mod+Tab       |
| FocL/R  | focus-column-left/right         | Mod+H/L       |
| FocU/D  | focus-window-up/down            | Mod+K/J       |
| MvL/R   | move-column-left/right          | Mod+Shift+H/L |
| MvU/D   | move-window-up/down             | Mod+Shift+K/J |
| MonL/R  | focus-monitor-left/right        | Mod+Ctrl+H/L  |
| MvML/R  | move-column-to-monitor-left/right | Mod+Shift+Ctrl+H/L |
| Col-/+  | column width ±10%               | Mod+-/+       |
| Ht-/+   | window height ±10%              | Mod+Shift+-/+ |

**Intentionally not placed** (reachable other ways or too global):

- `Mod+Escape` (toggle-keyboard-shortcuts-inhibit) — emergency
  escape from fullscreen shortcut-capturing apps. Type raw from
  BASE if needed.
- `Mod+Ctrl+C` (center-visible-columns) — compose `Ctrl + Ctr`
  from home-row-mod D + the `N_CTR` key.
- `Ctrl+Alt+Delete` (quit niri) — deliberate raw chord only.
- `Ctrl+Shift+1/2/3` (native screenshot variants) — no Mod needed,
  type from BASE.
- `XF86Audio*` / `XF86MonBrightness*` — live on MEDIA (tri-layer).

---

## Layer 6 — MEDIA (hold `MO_MED`, top-right pinky)

| ✕ | ✕ | ✕ | ✕ | Bri- | ✕ | Bri+ | ✕ | ✕ | ✕ | ✕ | ▽ |
|---|---|---|---|------|---|------|---|---|---|---|---|
| ✕ | ✕ | ✕ | ✕ | ✕    | ✕ | ✕    | ✕ | ✕ | ✕ | ✕ | ✕ |
| ▽ | ✕ | ✕ | ✕ | Vol- | ✕ | Vol+ | ✕ | ✕ | ✕ | ✕ | ▽ |
| ✕ | ✕ | ✕ | Prev | Play | Next (2u) | ✕ | ✕ | ✕ | ✕ | Mute |

Active while the top-right pinky (row 0 col 11) is held — no
tri-layer, no toggle. Release to drop back.

niri forwards `XF86Audio*` / `XF86MonBrightness*` to the noctalia
IPC calls configured in `~/.config/niri/cfg/keybinds.kdl`, so the
standard QMK keycodes (`KC_VOLU`/`KC_BRIU`/etc.) Just Work.

---

## Layer 7 — LSP (hold `MO_LSP`, top-left pinky)

LazyVim command surface — LSP goto, code actions, diagnostics,
Telescope, Trouble, Git, DAP. Every entry emits a LazyVim key
sequence via `SEND_STRING` (you must be in normal mode).

| ▽ | F5 | F9 | F10 | F11 | F12 | [e | ]e | [d | ]d | cs | ▽ |
|---|----|----|-----|-----|-----|----|----|----|----|----|---|
| ▽ | ff | sg | fr  | fb  | xx  | gd | gD | gi | gy | gr | K |
| ▽ | gg | e  | bd  | ww  | xL  | ca | cr | cf | cd | cl | ▽ |
| ▽ | db | dc | du  | dt  | di  | do (2u) | dO | ✕ | ✕ | ✕ |

**Row 0 — DAP F-keys + diagnostic nav + symbols outline:**

| Key | Sends | LazyVim action           |
|-----|-------|--------------------------|
| F5  | F5    | DAP continue             |
| F9  | F9    | DAP toggle breakpoint    |
| F10 | F10   | DAP step over            |
| F11 | F11   | DAP step into            |
| F12 | F12   | DAP step out             |
| [e  | `[e`  | previous error           |
| ]e  | `]e`  | next error               |
| [d  | `[d`  | previous diagnostic      |
| ]d  | `]d`  | next diagnostic          |
| cs  | ` cs` | `<leader>cs` — symbols   |

**Row 1 — Telescope + Trouble · LSP goto + hover:**

| Key | Sends  | LazyVim action                |
|-----|--------|-------------------------------|
| ff  | ` ff`  | `<leader>ff` — find files     |
| sg  | ` sg`  | `<leader>sg` — live grep      |
| fr  | ` fr`  | `<leader>fr` — recent files   |
| fb  | ` fb`  | `<leader>fb` — buffers        |
| xx  | ` xx`  | `<leader>xx` — Trouble        |
| gd  | `gd`   | goto definition               |
| gD  | `gD`   | goto declaration              |
| gi  | `gi`   | goto implementation           |
| gy  | `gy`   | goto type definition          |
| gr  | `gr`   | references                    |
| K   | Shift+K| hover doc                     |

**Row 2 — Git / Explorer / Buffer / Window · Code actions:**

| Key | Sends  | LazyVim action                |
|-----|--------|-------------------------------|
| gg  | ` gg`  | `<leader>gg` — lazygit        |
| e   | ` e`   | `<leader>e`  — explorer       |
| bd  | ` bd`  | `<leader>bd` — buffer delete  |
| ww  | ` ww`  | `<leader>ww` — window pick    |
| xL  | ` xL`  | `<leader>xL` — location list  |
| ca  | ` ca`  | `<leader>ca` — code action    |
| cr  | ` cr`  | `<leader>cr` — rename         |
| cf  | ` cf`  | `<leader>cf` — format         |
| cd  | ` cd`  | `<leader>cd` — line diag      |
| cl  | ` cl`  | `<leader>cl` — LSP info       |

**Row 3 — DAP leader variants (mirror F-keys for discoverability):**

| Key | Sends | LazyVim action                   |
|-----|-------|----------------------------------|
| db  | ` db` | toggle breakpoint                |
| dc  | ` dc` | continue                         |
| du  | ` du` | DAP UI toggle                    |
| dt  | ` dt` | terminate                        |
| di  | ` di` | step into                        |
| do  | ` do` | step over                        |
| dO  | ` dO` | step out (capital `O`)           |

All `LV_*` handlers call `clear_mods()` before emitting the string,
so a resting Shift on the other hand won't turn `ff` into `FF`.

---

## Custom Keycodes

**`N_WS1` … `N_WS9`** use `tap_code16`, which preserves modifiers
the user is already holding. So:

- tap `N_WS3` alone             → `Mod+3`         (focus workspace 3)
- Shift + tap `N_WS3`           → `Mod+Shift+3`   (move-window-to-ws 3)
- Ctrl + tap `N_WS3`            → `Mod+Ctrl+3`    (move-column-to-ws 3)

Same trick extends to hjkl: holding Shift/Ctrl/both while tapping
`N_FOCL/D/U/R` produces move, monitor-focus, and move-to-monitor.

**`LV_*`** use `SEND_STRING` via `lv_send()`, which clears
modifiers first. Holding Shift during `LV_FF` would otherwise turn
`ff` into `FF`.

---

## Why Separate MO Keys?

**MOUSE**, **LSP**, and **MEDIA** each own a dedicated pinky key.
Frequent layers (MOUSE, LSP) are on bottom-left and top-left, so
you can activate them without moving off home row. MEDIA is rare
(volume, brightness) and lives on top-right where accidental
activation is least likely during typing.

The previous tri-layer for MEDIA (NUM + NIRI thumbs together) has
been removed — every layer is now a single one-key hold.
