# BM40 — Daily driver guide (niri + LazyVim)

Everything you need to actually *use* this keymap without reopening
`keymap.c`. Assumes the layout is as defined in `keymap.c` in this
directory, paired with niri at `~/.config/niri/`.

---

## 1. Mental model in 60 seconds

- **8 layers, all momentary.** Hold a key → layer active. Let go →
  gone. No sticky state, no tri-layers, no "oh wait which layer am I on".
- **Base is QWERTY**, but the home row doubles as mods (A/S/D/F +
  J/K/L/;). Tap the letter, hold it to get Super/Alt/Ctrl/Shift.
- **Four thumb keys** activate NUM, NAV, SYM, NIRI. **Three pinky
  keys** activate MOUSE (bottom-left), LSP (top-left), and MEDIA
  (top-right). Every layer has its own one-key hold.
- **The board talks to niri** via a dedicated `_NIRI` layer whose
  keys emit the exact `Super+…` chords niri already listens for.
- **The board talks to LazyVim** via a dedicated `_LSP` layer whose
  keys emit LazyVim `<leader>…` sequences and bare LSP motions.

---

## 2. Home-row mods (base layer)

```
  Left hand              Right hand
┌───┬───┬───┬───┐     ┌───┬───┬───┬───┐
│ A │ S │ D │ F │     │ J │ K │ L │ ; │
│GUI│ALT│CTL│SFT│     │SFT│CTL│ALT│GUI│
└───┴───┴───┴───┘     └───┴───┴───┴───┘
  220 200 185 170       170 185 200 220   ms tapping-term
```

- **Tap** a letter → normal character.
- **Hold** → that modifier (GUI = Super on Wayland).
- Timing is tuned so index fingers fire mods fastest (170 ms) and
  pinkies slowest (220 ms) — matches the natural speed of each digit.
- `permissive_hold` is **off** for home-row mods and **on** for the
  thumb LT keys. In practice: rolling typing stays letters,
  deliberate holds give mods.

**Common chords you'll use constantly in LazyVim:**

| Chord | Fingers | What |
|---|---|---|
| `Ctrl+W` | hold `D`, tap `W` | LazyVim window chord prefix |
| `Ctrl+C` | hold `D`, tap `C` | abort / normal-mode escape |
| `Ctrl+D`/`Ctrl+U` | hold `D`, tap `D`/`U` | half-page jumps |
| `Ctrl+O`/`Ctrl+I` | hold `D`, tap `O`/`I` | jumplist back/forward |
| `Ctrl+]` | hold `D`, tap `]` (SYM) | jump to definition |
| `Shift+V` | hold `J`, tap `V` | visual-line |
| Leader `<Space>` | tap the 2u thumb | LazyVim leader — tap is Space |

---

## 3. Layer activation

```
  ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
  │LSP │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │MED │  ← pinky corners
  ├────┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼────┤
  │Esc │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ '  │
  ├────┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼────┤
  │LSft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSft│
  ├────┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼────┤
  │MSE │GUI│ALT│CTL│TAB│  SPC  │BSP│ENT│ ← │ ↓ │ →  │  ← thumb row
  └────┴───┴───┴───┴───┴───────┴───┴───┴───┴───┴────┘
                     NUM   NAV  SYM NIRI
```

**Thumb layers** (all LT — tap the letter, hold for layer):

| Thumb        | Hold | Tap       |
|--------------|------|-----------|
| left-inner   | NUM  | Tab       |
| left-outer 2u| NAV  | Space     |
| right-outer  | SYM  | Backspace |
| right-inner  | NIRI | Enter     |

**Pinky layers** (pure MO — no tap action):

| Pinky        | Hold  |
|--------------|-------|
| bottom-left  | MOUSE |
| top-left     | LSP   |
| top-right    | MEDIA |

Mnemonic: **thumbs left→right = NUM, NAV, SYM, NIRI** for text-shaping
layers; **pinkies** handle the "tool" layers (mouse / code / media).

---

## 4. Layer cheat-sheets

### 4.1 `_NAV` — hold left-outer thumb (Space)

Right hand = arrows. Left hand = page/line nav. Bottom = clipboard.

```
  ┌───┬────┬────┬───┬────┬────┐┌───┬────┬───┬────┬──┬───┐
  │Esc│PgUp│BkSp│ ↑ │Del │PgDn││   │WBk │   │WFwd│  │Del│
  ├───┼────┼────┼───┼────┼────┤├───┼────┼───┼────┼──┼───┤
  │Hom│ ←  │ ↓  │ → │End │    ││ ← │ ↓  │ ↑ │ →  │  │   │
  ├───┼────┼────┼───┼────┼────┤├───┼────┼───┼────┼──┼───┤
  │ _ │Und │Cut │Cpy│Pst │    ││   │    │   │    │  │ _ │
  └───┴────┴────┴───┴────┴────┘└───┴────┴───┴────┴──┴───┘
```

- **Hold Space, right hand `hjkl`** = arrows. Drill this first —
  it's your most-used layer after BASE.
- `WBk`/`WFwd` = browser back/forward. Useful in Brave, file
  managers with history, IDE navigation.
- Left-hand clipboard row works in most GTK/Qt/Wayland apps without
  rebinding.
- **LazyVim tip:** you rarely need NAV inside vim — vim's own
  motions are better. NAV shines in the terminal, browser,
  Slack, etc.

### 4.2 `_NUM` — hold left-inner thumb (Tab)

```
  ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
  │1 │2 │3 │4 │5 │6 │7 │8 │9 │0 │- │= │
  ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
  │F1│F2│F3│F4│F5│F6│F7│F8│F9│10│11│12│
  ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
  │/ │= │* │+ │- │( │0 │, │. │  │  │  │
  └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
  2u thumb centre = Space.
```

- Top row = digits. Second row = F1-F12 (rename F2, debug F5, etc.).
- Third row = calculator ops.
- 2u centre = Space, so `42 items` types without releasing the
  layer thumb.

### 4.3 `_SYM` — hold right-outer thumb (Backspace)

```
  ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
  │~ │! │@ │# │$ │% │^ │& │* │( │) │_ │
  ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
  │\ │| │{ │} │+ │= │[ │] │< │> │" │  │
  ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
  │  │` │~ │( │) │- │_ │/ │? │: │; │  │
  └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
```

- Tap-dance on `[` and `]`: single tap `[`/`]`, double tap `{`/`}`.
- Tap-dance on `` ` `` (BASE): single tap `` ` ``, double tap `~`.
- Shell staples — `|`, `&`, `$`, `~` — all home-row-reachable.
- LazyVim: `[d` / `]d` (diagnostics), `[c` / `]c` (hunks), `<C-]>`
  (go-to-definition) all live here.

### 4.4 `_MOUSE` — hold bottom-left key (pinky)

```
  ┌───┬───┬───┬────┬───┬────┬───┬────┬───┬────┬───┬───┐
  │   │   │   │M ↑ │   │Wh↑ │   │MB4 │MB5│    │   │   │
  ├───┼───┼───┼────┼───┼────┼───┼────┼───┼────┼───┼───┤
  │   │   │M← │M ↓ │M→ │Wh↓ │M← │M ↓ │M ↑│M → │   │   │
  ├───┼───┼───┼────┼───┼────┼───┼────┼───┼────┼───┼───┤
  │   │   │Wh←│    │Wh→│    │MB3│MB1 │MB2│    │   │   │
  ├───┼───┼───┼────┼───┼────┼───┼────┼───┼────┼───┼───┤
  │   │   │   │    │MB3│MB1 │MB2│ACL0│AL2│    │   │   │
  └───┴───┴───┴────┴───┴────┴───┴────┴───┴────┴───┴───┘
```

- Right hand = cursor + primary buttons (MB1 = left, MB2 = right,
  MB3 = middle).
- Left hand = wheel in four directions.
- Row 0 right hand: **MB4/MB5** = browser back/forward side buttons.
- Thumb-row `ACL0`/`ACL2` = hold-to-slow / hold-to-fast cursor.

### 4.5 `_NIRI` — hold right-inner thumb (Enter)

This is the layer that makes this keyboard a niri remote control.

```
  ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
  │WS1 │WS2 │WS3 │WS4 │WS5 │WS6 │WS7 │WS8 │WS9 │WSl │Rsz-│Rsz+│  ← focus ws 1-9 + prev; resize col
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │Fils│CEx │WPv │WNx │Shot│Chet│F←  │F↓  │F↑  │F→  │Mo← │Mo→ │  ← apps, ws cycle, focus win, focus monitor
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │    │Lock│MM← │MM→ │Ht- │Ht+ │M←  │M↓  │M↑  │M→  │CMax│    │  ← lock, send-to-monitor, height, move win, col-max
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │    │Flt │Sess│Trm │Lch │   Brw   │Kil │Pwr │Ctr │Tab │Full│  ← modes, session, launchers, center col
  └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
```

**Workspace row** uses modifier composition (no dedicated move keys):

| Want | How |
|---|---|
| focus workspace N | tap `WSn` |
| move window to ws N + follow | hold **Shift** (F/J), tap `WSn`  *(niri 1-5 only)* |
| move column to ws N (stay) | hold **Ctrl** (D/K), tap `WSn` |

**hjkl** uses the same trick — one set of keys, all 12 variants:

| Want | How |
|---|---|
| focus column/window | tap `F←/F↓/F↑/F→` |
| move column/window | hold **Shift**, tap same keys (== `M←/M↓/M↑/M→`) |
| focus monitor L/R | hold **Ctrl**, tap `F←/F→` (== `Mo←/Mo→`) |
| focus monitor U/D | hold **Ctrl**, tap `F↑/F↓` *(no dedicated key)* |
| move col to monitor | hold **Shift+Ctrl**, tap any `F` direction |

Shift/Ctrl can come from the pinky column (`LShift` row 2 col 0,
`LCtrl` row 3 col 3) or from home-row mods (`F`/`D` / `J`/`K`).

**The daily flow** (keycaps named by their base-layer letter):

| Goal | Keys |
|---|---|
| Jump to workspace 3 | hold `Enter`, tap `E` position (WS3) |
| Move window to ws 3 (follow) | hold `Enter`+`F` (Shift), tap `E` |
| Move column to ws 3 (stay) | hold `Enter`+`D` (Ctrl), tap `E` |
| Focus column left / right | hold `Enter`, tap `H` / `;`  (FocL/FocR) |
| Focus window up / down | hold `Enter`, tap `K` / `J` (FocU/FocD) |
| Move window one column left | hold `Enter`, tap `N` (M←) |
| Focus prev / next monitor | hold `Enter`, tap `P` / `BSp` (Mo←/Mo→) |
| Focus monitor up / down | hold `Enter`+`D` (Ctrl), tap `K` / `J` |
| Send window to next monitor | hold `Enter`, tap `C` (MM→) |
| Resize column shrink / grow | hold `Enter`, tap `P` / `BSp` row 0 (Rsz-/+) |
| Expand current column | hold `Enter`, tap `W` (CEx) |
| Center column | hold `Enter`, tap `,` (Ctr) |
| Maximize in column | hold `Enter`, tap `P` row 2 (CMax) |
| Fullscreen | hold `Enter`, tap `/` (Full) |
| Toggle tabbed layout | hold `Enter`, tap `.` (Tab) |
| Toggle floating | hold `Enter`, tap `Gui` pos (Flt) |
| Kill current window | hold `Enter`, tap `N` row 3 (Kil) |
| Launch terminal | hold `Enter`, tap `Ctrl` pos (Trm) |
| Launch rofi / noctalia | hold `Enter`, tap `Tab` pos row 3 (Lch) |
| Launch browser | hold `Enter`, tap the 2u thumb (Brw) |
| Screenshot region | hold `Enter`, tap `T` (Shot) |
| Open nautilus | hold `Enter`, tap `Esc` pos (Fils) |
| Hotkey overlay | hold `Enter`, tap `Y` (Chet) |
| Lock screen | hold `Enter`, tap `Z` (Lock) |
| Session menu | hold `Enter`, tap `X` row 3 (Sess) |
| Power off monitors | hold `Enter`, tap `M` row 3 (Pwr) |
| Previous / next workspace | hold `Enter`, tap `S` / `D` (WPv/WNx) |
| Last workspace | hold `Enter`, tap `O` (WSl) |

**What's intentionally *not* on the layer:**

- `Mod+Escape` (toggle-keyboard-shortcuts-inhibit) — emergency
  escape from shortcut-capturing fullscreen apps. Type the raw
  Mod+Esc from BASE when you need it.
- `Mod+Ctrl+C` (center-visible-columns) — compose Ctrl + `Ctr`.
- `Ctrl+Alt+Delete` (quit niri) — deliberately a raw chord.

### 4.6 `_MEDIA` — hold top-right pinky (BSpc position)

```
  │    │    │    │    │Br- │    │Br+ │    │    │    │    │ ▽  │
  (row 1 empty)
  │    │    │    │    │Vol-│    │Vol+│    │    │    │    │    │
  │    │    │    │Prev│Play│Next│    │    │    │    │Mute│
```

- Row 0 = brightness: `R` (Br-) and `Y` (Br+), mirroring volume.
- Right thumb area controls playback (Prev/Play/Next).
- Volume on `V` (down) and `N` (up). Mute on the bottom-right.
- niri forwards `XF86Audio*`/`XF86MonBrightness*` to noctalia's IPC
  calls — QMK's standard keycodes work unmodified.

### 4.6b `_GAME` — Warframe (toggle: MEDIA + G)

The one toggled layer. Hold the top-right pinky and tap `G` to turn
it on; do the same again to turn it off. Plain keys only — no
home-row mods, no Super — so WASD can be held freely and niri
shortcuts can't fire mid-mission.

```
  │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │MED │
  │Esc │ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │Bspc│
  │Sft │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │Ent │
  │Ctl │Alt │    │    │Ctl │  Space  │ 1  │ 2  │ 3  │ 4  │ '  │
```

- Movement: WASD, Shift (sprint/roll), Ctrl (pinky or left thumb),
  C, Space (jump).
- Abilities 1-4 on the bottom-right.
- Chat: all letters, Shift, Bspc and Enter work as normal.

### 4.7 `_LSP` — hold top-left pinky (Tab position)

LazyVim's command surface on one layer. Every key emits a LazyVim
`<leader>…` sequence or a bare normal-mode motion — **you must be
in normal mode** for them to do what they say.

```
  ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
  │    │ F5 │ F9 │F10 │F11 │F12 │[e  │]e  │[d  │]d  │ cs │    │  DAP · diag nav · symbols
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │    │ ff │ sg │ fr │ fb │ xx │ gd │ gD │ gi │ gy │ gr │ K  │  Telescope+Trouble · LSP goto + hover
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │    │ gg │ e  │ bd │ ww │ xL │ ca │ cr │ cf │ cd │ cl │    │  Git/Exp/Buf/Win · Code actions
  ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
  │    │ db │ dc │ du │ dt │ di │  do (2u)│ dO │    │    │    │  DAP (leader)
  └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
```

**One-handed right-hand moves (most frequent):** `gd`, `gr`, `K`
(hover), `ca`, `cr`, `cf` all live on the right hand — hold LSP
with the left pinky, execute with the right hand without leaving
home row.

**Daily flow:**

| Goal                         | Keys                                           |
|------------------------------|------------------------------------------------|
| Jump to definition           | hold LSP, tap `T` (gd)                         |
| Find references              | hold LSP, tap `P` (gr)                         |
| Hover docs                   | hold LSP, tap `BSp`-position (K)               |
| Code action                  | hold LSP, tap `H` (ca)                         |
| Rename                       | hold LSP, tap `J` (cr)                         |
| Format                       | hold LSP, tap `K` (cf)                         |
| Next / prev diagnostic       | hold LSP, tap `I` / `O` (]d / [d)              |
| Find files                   | hold LSP, tap `A` (ff)                         |
| Live grep                    | hold LSP, tap `S` (sg)                         |
| Open Trouble                 | hold LSP, tap `G` (xx)                         |
| lazygit                      | hold LSP, tap `Z` (gg)                         |
| Toggle explorer              | hold LSP, tap `X` (e)                          |
| Delete buffer                | hold LSP, tap `C` (bd)                         |
| Toggle breakpoint            | hold LSP, tap `LGui`-pos (db) **or** F9        |
| DAP continue                 | hold LSP, tap `LAlt`-pos (dc) **or** F5        |
| DAP UI toggle                | hold LSP, tap `LCtl`-pos (du)                  |
| Step into / over / out       | F11 / F10 / F12  **or** leader `di` / `do` / `dO` |

**Why two ways for DAP?** F-keys are the muscle-memory path most
DAP-UI docs show; the `<leader>d*` row mirrors them for when you're
already in a leader cadence.

---

## 5. niri workflow — end-to-end examples

### 5.1 "Open browser on workspace 2, then code on workspace 1"

1. Hold Enter, tap `S` (Brw) → brave launches on current workspace.
2. Hold Enter + `F` (Shift via home-row), tap `2` (WS2) → window
   moves to ws 2 and you follow.
3. Hold Enter, tap `1` (WS1) → back to ws 1.
4. Hold Enter, tap `D` row 3 (Trm) → alacritty.

### 5.2 "Scroll through a wide column layout in niri"

niri's killer feature is horizontal scrolling columns.

1. Open three terminals: Enter + `D` row 3, three times.
2. Move one to its own column: Enter + `F` (Shift), tap `N` (M←).
3. Focus columns with Enter + `H` / `;` (FocL / FocR).
4. Make the focused column wider: Enter + `W` (CEx — expand to
   available width). Narrow it again with Enter + `,` (Ctr) or
   Enter + `P`/`BSp` row 0 (Rsz-/+).

### 5.3 "I need to see the keybind overlay"

Hold `Enter`, tap `Y` (Chet) → niri's built-in hotkey overlay pops
up (shows every binding with its `hotkey-overlay-title`).

### 5.4 "I plugged in a second monitor"

niri auto-places workspaces across monitors. To move between:

- Focus the other monitor L/R: hold Enter, tap `P` / `BSp` row 1
  (Mo←/Mo→).
- Focus monitor above/below: hold Enter + `D` (Ctrl), tap `K` / `J`.
- Send current window to monitor: hold Enter, tap `X` / `C`
  (MM←/MM→) — or compose Shift+Ctrl + any F-direction.

### 5.5 "A Steam/Proton game is eating my keybinds"

Hit `Mod+Escape` directly from BASE (raw chord, no layer). niri's
`toggle-keyboard-shortcuts-inhibit` gets you back control. Mod+Esc
again to return the shortcuts to the app.

---

## 6. LazyVim tips on this keymap

- **Leader `<Space>`** = the 2u thumb. Tap-release to fire leader,
  hold to enter NAV — the LT timing is tuned so short taps never
  hit NAV by accident.
- **`<Esc>` vs home-row `Esc`:** the left-pinky `Esc` key
  (`CT_ESC`) doubles as Ctrl when held. Normal-mode return is just
  a tap.
- **`Ctrl+[` as escape alternative:** LazyVim maps it; `D` held +
  SYM `[` works, but it's slower than raw `Esc`.
- **LSP chords live on `_LSP`.** `gd`, `gr`, `K`, `<leader>ca`,
  `<leader>cr`, `<leader>cf`, `[d`/`]d` and the DAP F-keys are all
  one key away while the top-left pinky is held. You can still
  type them by hand from BASE; the layer is the fast path, not the
  only path.
- **Window management in Neovim:** `Ctrl+W` + hjkl. The right-hand
  hjkl is home-row, so this is fluid.
- **Avoid home-row-mod cramp in long files:** for multi-line visual
  selections with hold-Shift-hjkl, prefer `V`/`v` motions (`V}`,
  `vap`, etc.) over hammering Shift.
- **`_LSP` requires normal mode.** The macros send literal key
  sequences — if you're in insert mode, `gd` types "gd" into the
  buffer. Tap Esc first if unsure.

---

## 7. Flashing & iteration

From the qmk_firmware root:

```bash
qmk compile -kb kprepublic/bm40hsrgb/rev2 -km default
qmk flash   -kb kprepublic/bm40hsrgb/rev2 -km default
```

- Put the BM40 into bootloader first: physical reset button on the
  back, or temporarily map `QK_BOOT` to a corner key.
- After flashing, test each layer with `wev` (Wayland equivalent of
  evtest) or the QMK keymap viewer — catches wiring mistakes
  before you're mid-flow.

---

## 8. Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| Caps getting stuck | permissive hold + home-row mod misfire | raise tapping-term for the offending key |
| `Mod+N` doesn't switch workspaces | niri lost focus / another window captured it | hit `Mod+Escape` to toggle shortcut-inhibit |
| Mouse layer won't release | pinky resting on `MO_MSE` | retrain, or remap to a less-resting key |
| No screenshot appears | `grim`/`slurp` not installed or noctalia IPC down | check `niri msg version`, install `grim slurp` |
| Volume/brightness does nothing | noctalia-shell IPC not running | `qs -c noctalia-shell` should be in autostart |
| "Weird" characters when typing fast | pressed a thumb LT during a roll and hit its layer | shorten tapping-term for thumb keys, or retrain the roll |
| `Mod+Shift+P` blanks monitors and you can't un-blank | niri power-off-monitors — wiggle mouse or press any key | intentional |

---

## 9. See also

- `keymap.c` — the source of truth.
- `LEGEND.md` — compact reference tables for every layer.
- `SUGGEST.md` — niri-vs-keymap gap audit and tweak ideas.
- `~/.config/niri/cfg/keybinds.kdl` — the WM side of the contract.
