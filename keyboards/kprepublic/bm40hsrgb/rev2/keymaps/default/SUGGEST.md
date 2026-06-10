# BM40 keymap — niri gap audit

A review of `keymap.c` against the live niri config at
`~/.config/niri/cfg/keybinds.kdl`. Items are ordered high → low
priority. Each entry says **what**, **why**, and **how**.

---

## A. niri bindings NOT on the keymap — and whether they should be

### A1. `Mod+Escape` (toggle-keyboard-shortcuts-inhibit) — deliberately off
- **What:** the emergency escape from fullscreen apps that capture
  keyboard shortcuts (Steam, Proton, remote-desktop).
- **Why it's off:** it's a single chord the user will hit
  consciously, usually in panic. A dedicated layer slot hides it
  behind `Enter + something`, which defeats the purpose.
- **How to reach it:** raw from BASE — home-row `A` (Gui) + `Esc`
  pinky. Two keys, no layer.
- **If you insist on placing it:** `_NIRI [1][5]` currently holds
  `Chet` (hotkey-overlay); both are "meta-escape" actions, swap if
  Chet is less useful to you.

### A2. `Mod+Ctrl+C` (center-visible-columns) — composed
- **What:** niri's "balance all visible columns" command.
- **Why composed:** holding Ctrl (home-row `D` or `K`) while tapping
  `Ctr` on `_NIRI [3][8]` produces `Mod+Ctrl+C` already. No
  dedicated slot needed.

### A3. `Ctrl+Shift+1/2/3` (screenshot-region / screen / window) — from BASE
- **What:** niri's three screenshot variants have no Mod prefix, so
  they type directly from BASE: home-row `D` (Ctrl) + `F` (Shift)
  + NUM `1/2/3`.
- **Why not on `_NIRI`:** putting them on the layer means pressing
  Super+Shift+Ctrl+digit, which the binding doesn't match. The
  only screenshot variant that goes via Mod (`Mod+Shift+S`) is
  already `N_SHOT` on `_NIRI [1][4]`.

### A4. `Ctrl+Alt+Delete` (quit niri) — intentionally a raw chord
- **What:** niri's session-quit. Hard-to-hit by design.
- **Why not on layer:** single accidental tap = lose your session.
  The cost of the raw chord is a feature.

### A5. `Mod+WheelScrollUp/Down/Left/Right` — not reachable from QMK
- **What:** niri's wheel-based workspace/column nav from
  `keybinds.kdl:80-90`.
- **Why not on layer:** QMK mouse wheel + Mod modifier would work,
  but on a 47-key board without a scroll wheel, dedicating MOUSE
  slots to Mod-wheel combos is low-value. The `Mod+U/I` and
  `Mod+H/L` bindings cover the same semantic from NIRI.

---

## B. Potential refinements

### B1. `N_POWR` placement — "accidental blank" risk
- **What:** `_NIRI [3][7]` = `Mod+Shift+P` (power-off-monitors).
  It sits where BASE has `TH_ENT` + something — i.e. the right
  thumb's immediate neighborhood.
- **Why it could bite you:** fat-fingering blanks both screens.
  niri requires a key press or mouse wiggle to wake them.
- **Options:**
  1. Keep — it's behind the Enter layer, so triggering it during
     normal typing is physically hard.
  2. Move to `_NIRI [2][11]` (currently `_______`) so it's as far
     from the thumb as possible.
  3. Drop entirely and type the raw chord when needed.

### B2. `N_SESS` on `_NIRI [3][2]`
- **What:** session menu (`Mod+Shift+Q`). Useful but niche.
- **Alt idea:** if you never use it, swap for `N_CTRV`
  (center-visible-columns) to avoid the Ctrl-compose dance.

### B3. `N_FILES` on `_NIRI [1][0]` vs "terminal-first" workflow
- **What:** Opens nautilus via `Mod+E`. For someone who lives in a
  terminal + LazyVim, nautilus is rarely needed.
- **Alt idea:** replace with a bound like `Mod+Ctrl+C`
  (center-visible-columns) or a second terminal spawn shortcut.

### B4. `_NAV` right-hand arrows duplicate the right thumb arrows
- **What:** `_NAV [1][6..9]` are hjkl arrows and BASE [3][8..10]
  are also Left/Down/Right. On `_NAV` the thumb-row arrows don't
  fall through (they're BASE keys, not `_______`).
- **Why it's still worth it:** `_NAV` arrows are on the home row —
  no finger movement. BASE-row arrows work one-handed with the
  right thumb, which is faster for brief nudges. Keep both.

---

## C. LazyVim-specific considerations

### C1. `<Esc>` latency
- The left-pinky `CT_ESC` is `LCTL_T(KC_ESC)` — it's a tap-hold
  mod-tap. On fast vim `ijji` sequences the tap can register as a
  hold if you're right at the tapping-term boundary.
- **If you see ghost Ctrl-modifiers in insert mode:** raise
  `get_tapping_term` for `CT_ESC` in `keymap.c` by 20 ms.
- **Alternative escape:** `Ctrl+[` via home-row `D` + SYM `[`,
  but three keys is slower than raw Esc.

### C2. Leader key `<Space>`
- The 2u thumb is `TH_SPC` (LT to `_NAV`, tap = Space).
  `permissive_hold` is **on** for this key, so if you tap leader
  and immediately tap another key, leader fires correctly without
  waiting out the tapping-term. This matches LazyVim's rapid
  leader sequences (`<Space>ff`, `<Space>sg`, etc).

### C3. `<C-n>` / `<C-p>` in completion menus
- Home-row `D` (Ctrl) + `N` / `P` both work without issue — they're
  on opposite hands so there's no same-hand SFB.

### C4. Macro recording (`q` / `@`)
- `q` is a bare BASE letter with no tap-dance. `@` is SYM [0][2].
  Fine for occasional use; if you live in macros, consider moving
  `@` to a spot reachable with NIRI+something so you don't have
  to hold SYM.

---

## D. Hardware / firmware polish (lower priority)

### D1. Firmware size
- Current build: 15334 / 28672 bytes (53%). Plenty of room.
- If you enable `RGB_MATRIX_ENABLE = yes` in `rules.mk`, expect ~+6KB.
  Still comfortable.

### D2. `CONSOLE_ENABLE = no`
- If you're debugging a keymap issue, flip to `yes` and run
  `qmk console` to see real-time keypress logs. Flip back when done
  — it adds ~1-2KB.

### D3. `COMBO_ENABLE = no`
- niri has no "killer combo" bindings you're missing, but if you
  ever want `j+k = Esc` for pure-vim users, it's one flag flip.

---

## E. Applying the minimum set

The keymap is already aligned to niri. If you want to tighten it:

1. **Move `N_POWR`** from `[3][7]` to `[2][11]` to reduce
   accidental-blank risk. *(B1 option 2.)*
2. **Consider `N_CTRV` on `[3][2]`** in place of `N_SESS` if you
   rebalance columns more often than you open the session menu.
   *(B2.)*
3. **Raise `CT_ESC` tapping-term** to 190-200 ms if you see stray
   Ctrl modifiers in vim insert mode. *(C1.)*

Everything else is down to usage data — live with the keymap for a
week, then revisit.
