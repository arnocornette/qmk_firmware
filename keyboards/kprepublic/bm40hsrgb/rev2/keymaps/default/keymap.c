// ============================================================
//  BM40RGB v2 — QMK keymap for niri + LazyVim
//  Layout: LAYOUT_ortho_4x12_1x2uC (47 keys)
//
//  DESIGN RULE: All layers are momentary (MO / LT only).
//  There are NO toggle layers and NO tri-layers. Every layer is
//  active only while its activating key is held. Every layer is
//  reachable directly from BASE — no layer-from-layer hops.
// ============================================================
//
//  LAYER OVERVIEW
//  ┌─────┬────────────────────────────────────────────────────┐
//  │  0  │ BASE   — QWERTY + home-row mods                    │
//  │  1  │ NAV    — Vim hjkl, arrows, PgUp/Dn, clipboard      │
//  │  2  │ NUM    — Number row, F1–F12, math symbols          │
//  │  3  │ SYM    — Shifted symbols, brackets, quotes         │
//  │  4  │ MOUSE  — Cursor, wheel, buttons, speed (ACL0/2)    │
//  │  5  │ NIRI   — niri WM: workspaces, windows, apps, mons  │
//  │  6  │ MEDIA  — Volume, brightness, transport             │
//  │  7  │ LSP    — LazyVim LSP / DAP / Telescope / Trouble   │
//  └─────┴────────────────────────────────────────────────────┘
//
//  HOME-ROW MODS (BASE layer, tap/hold):
//    A → LGUI   S → LALT   D → LCTL   F → LSFT
//    J → RSFT   K → RCTL   L → RALT   ; → RGUI
//    Esc → LCTL (CT_ESC)  — tap Esc, hold Ctrl
//
//  LAYER ACTIVATION — all momentary, all from BASE:
//    NUM:    hold left-inner thumb   (TH_TAB, tap = Tab)
//    NAV:    hold left-outer thumb   (TH_SPC, tap = Space, 2u)
//    SYM:    hold right-outer thumb  (TH_BSP, tap = Backspace)
//    NIRI:   hold right-inner thumb  (TH_ENT, tap = Enter)
//    MOUSE:  hold bottom-left pinky  (MO_MSE)
//    LSP:    hold top-left pinky     (MO_LSP, row 0 col 0)
//    MEDIA:  hold top-right pinky    (MO_MED, row 0 col 11)
//
//  Tab and Backspace remain available via their thumb LT keys
//  (TH_TAB / TH_BSP) — the top-row pinky slots are repurposed.
//
//  MODIFIER COMPOSITION ON _NIRI (tap_code16-style passthrough):
//    Tap N_WSn             → Mod+n        (focus workspace)
//    Shift + tap N_WSn     → Mod+Shift+n  (move-window-to-ws)  [1..5 only in niri]
//    Ctrl  + tap N_WSn     → Mod+Ctrl+n   (move-column-to-ws)
//
//    Tap N_FOCL/D/U/R      → focus (col left/right, win up/down)
//    Shift + N_FOCL/R      → move-column-left/right           (== N_MVL/R)
//    Shift + N_FOCD/U      → move-window-up/down              (== N_MVD/U)
//    Ctrl  + N_FOCL/R      → focus-monitor-left/right         (== N_SCRP/N)
//    Ctrl  + N_FOCD/U      → focus-monitor-down/up
//    Shift+Ctrl + N_FOCL/R → move-column-to-monitor-left/right
//    Shift+Ctrl + N_FOCD/U → move-column-to-monitor-down/up
//
//  So monitor u/d need no dedicated keys — compose with Ctrl on
//  N_FOCU / N_FOCD. This keeps the _NIRI layer uncrowded.
//
//  LAZYVIM MACROS ON _LSP (SEND_STRING passthrough):
//    LV_xx         → leader sequence " xx"   (e.g. " ff" for find files)
//    LV_GD/GI/...  → bare motion "gd" / "gi" (LSP goto)
//    LV_PDI/NDI... → "[d" / "]d"             (diagnostic nav)
//  These expect normal mode; holding stray modifiers may break the
//  sequence, so activate _LSP with the pinky and type with the
//  other hand — home-row mods are off while on _LSP.
//
//  TAP-DANCE (BASE/SYM): [[→{  ]]→}  //→?  ``→~
// ============================================================

#include QMK_KEYBOARD_H

// ── Layer indices ────────────────────────────────────────────
enum layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _MOUSE,
    _MOUSE_FAST,
    _NIRI,
    _MEDIA,
    _LSP,
};

// ── Custom keycodes ──────────────────────────────────────────
//
//  N_WSn focuses workspace n (Super+n). Hold Shift while tapping
//  for move-window-to-workspace (niri: Mod+Shift+n); hold Ctrl
//  for move-column-to-workspace (niri: Mod+Ctrl+n). tap_code16
//  preserves modifiers the user is already holding.
//
//  LV_* keycodes emit LazyVim key sequences via SEND_STRING. They
//  clear modifiers first so a stray Shift from a resting finger
//  can't corrupt the sequence (e.g. "ff" -> "FF").
enum custom_keycodes {
    N_WS1 = SAFE_RANGE,
    N_WS2, N_WS3, N_WS4, N_WS5, N_WS6, N_WS7, N_WS8, N_WS9,

    // LazyVim <leader> sequences
    LV_FF,  LV_SG,  LV_FR,  LV_FB,                  // Telescope
    LV_CA,  LV_CR,  LV_CF,  LV_CD,  LV_CL,  LV_CS,  // LSP code actions
    LV_XX,  LV_XL,                                  // Trouble
    LV_GG,  LV_EE,  LV_BD,  LV_WW,                  // git / explorer / buffer / window
    LV_DB,  LV_DC,  LV_DU,  LV_DT,                  // DAP control
    LV_DI,  LV_DO,  LV_DP,                          // DAP step (in / over / out)

    // LazyVim bare normal-mode sequences
    LV_GD,  LV_GDL, LV_GI,  LV_GY,  LV_GR,          // LSP goto
    LV_PDI, LV_NDI, LV_PER, LV_NER,                 // diagnostic nav
};

// ── Tap-dance ────────────────────────────────────────────────
enum tap_dance {
    TD_LBRC,
    TD_RBRC,
    TD_SLSH,
    TD_GRV,
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
    [TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_GRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV,  KC_TILD),
};

// ── Home-row mod aliases ─────────────────────────────────────
#define HM_A  LGUI_T(KC_A)
#define HM_S  LALT_T(KC_S)
#define HM_D  LCTL_T(KC_D)
#define HM_F  LSFT_T(KC_F)
#define HM_J  RSFT_T(KC_J)
#define HM_K  RCTL_T(KC_K)
#define HM_L  RALT_T(KC_L)
#define HM_SC RGUI_T(KC_SCLN)

// ── Layer-access aliases (all momentary) ──────────────────────
#define TH_SPC  LT(_NAV,  KC_SPC)        // hold = NAV,   tap = Space
#define TH_BSP  LT(_SYM,  KC_BSPC)       // hold = SYM,   tap = Backspace
#define TH_TAB  LT(_NUM,  KC_TAB)        // hold = NUM,   tap = Tab
#define TH_ENT  LT(_NIRI, KC_ENT)        // hold = NIRI,  tap = Enter
#define MO_MSE  MO(_MOUSE)               // hold = MOUSE
#define MO_LSP  LT(_LSP, KC_LSFT)                 // hold = LSP    (top-left pinky)
#define MO_MED  MO(_MEDIA)               // hold = MEDIA  (top-right pinky)

#define CT_ESC  LCTL_T(KC_ESC)

// Hyper+Tab — niri-bound to spawn pkm-capture. Lives on _NAV [0][0]
// (top-left while the Space thumb is held).
#define HYPR_TAB LGUI(LCTL(LALT(LSFT(KC_TAB))))

// ── niri hotkey aliases ───────────────────────────────────────
//  Plain key-combo macros. Holding Shift/Ctrl at BASE-level adds
//  to whatever these emit (see "modifier composition" above).

// Focus / move (hjkl)
#define N_FOCL  LGUI(KC_H)               // focus-column-left
#define N_FOCR  LGUI(KC_L)               // focus-column-right
#define N_FOCU  LGUI(KC_K)               // focus-window-up
#define N_FOCD  LGUI(KC_J)               // focus-window-down
#define N_MVL   LGUI(LSFT(KC_H))         // move-column-left
#define N_MVR   LGUI(LSFT(KC_L))         // move-column-right
#define N_MVU   LGUI(LSFT(KC_K))         // move-window-up
#define N_MVD   LGUI(LSFT(KC_J))         // move-window-down

// Monitor focus (left/right only; up/down via Ctrl + N_FOCU/D)
#define N_SCRP  LGUI(LCTL(KC_H))         // focus-monitor-left
#define N_SCRN  LGUI(LCTL(KC_L))         // focus-monitor-right
#define N_SCRSP LGUI(LSFT(LCTL(KC_H)))   // move-column-to-monitor-left
#define N_SCRSN LGUI(LSFT(LCTL(KC_L)))   // move-column-to-monitor-right

// Workspaces
#define N_WSPREV LGUI(KC_I)              // focus-workspace-up   (Mod+I)
#define N_WSNEXT LGUI(KC_U)              // focus-workspace-down (Mod+U)
#define N_WSLAST LGUI(KC_TAB)            // focus-workspace-previous

// Window state
#define N_KILL  LGUI(KC_Q)               // close-window
#define N_FULL  LGUI(KC_F)               // fullscreen-window
#define N_FLT   LGUI(KC_T)               // toggle-window-floating
#define N_TAB   LGUI(KC_W)               // toggle-column-tabbed-display

// Column layout (niri's scrollable tiling sweet spot)
#define N_CTR   LGUI(KC_C)               // center-column
#define N_CTRV  LGUI(LCTL(KC_C))         // center-visible-columns
#define N_CMAX  LGUI(LSFT(KC_C))         // maximize-column
#define N_CEXP  LGUI(LCTL(KC_F))         // expand-column-to-available-width

// Resize column / window
#define N_RSZS  LGUI(KC_MINS)            // column width -10%
#define N_RSZG  LGUI(KC_EQL)             // column width +10%
#define N_RSZSH LGUI(LSFT(KC_MINS))      // window height -10%
#define N_RSZGH LGUI(LSFT(KC_EQL))       // window height +10%

// Applications (from ~/.config/niri/cfg/keybinds.kdl)
#define N_LAUNCH LGUI(KC_D)              // launcher (noctalia)
#define N_TERM   LGUI(KC_ENT)            // alacritty
#define N_BROWSE LGUI(KC_B)              // brave
#define N_FILES  LGUI(KC_E)              // nautilus

// Session / system
#define N_LOCK   LGUI(LALT(KC_L))        // noctalia lock
#define N_SESS   LGUI(LSFT(KC_Q))        // noctalia session menu
#define N_SHOT   LGUI(LSFT(KC_S))        // screenshot
#define N_CHEAT  LGUI(LSFT(KC_ESC))      // hotkey overlay
#define N_POWR   LGUI(LSFT(KC_P))        // power-off-monitors
#define N_ESCI   LGUI(KC_ESC)            // emergency: toggle shortcut inhibit

// ── Keymap ────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_4x12_1x2uC(
    MO_LSP,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    MO_MED,
    CT_ESC,     HM_A,    HM_S,    HM_D,    HM_F,    KC_G,    KC_H,    HM_J,    HM_K,    HM_L,    HM_SC,   KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SLSH), KC_RSFT,
    MO_MSE,     KC_LGUI, KC_LALT, KC_LCTL, TH_TAB,  TH_SPC,           TH_BSP,  TH_ENT,  KC_LEFT, KC_DOWN, KC_RGHT
),

// ── NAV ───────────────────────────────────────────────────────
//  Right hand = arrows (hjkl). Left hand = page/line nav.
//  Row 2 left = clipboard (Undo/Cut/Copy/Paste) — works in most
//  X11/GTK/Wayland apps via XK_Undo / XF86Cut / etc.
[_NAV] = LAYOUT_ortho_4x12_1x2uC(
    HYPR_TAB,KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, XXXXXXX, KC_WBAK, XXXXXXX, KC_WFWD, XXXXXXX, KC_DEL,
    KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

// ── NUM ───────────────────────────────────────────────────────
//  Row 0 digits; row 1 F1–F12; row 2 math ops; 2u thumb = Space
//  so "42 items" types without releasing the layer thumb.
[_NUM] = LAYOUT_ortho_4x12_1x2uC(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_SLSH, KC_EQL,  KC_ASTR, KC_PLUS, KC_MINS, KC_LPRN, KC_0,    KC_COMM, KC_DOT,  XXXXXXX, _______, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_SPC,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

// ── SYM ───────────────────────────────────────────────────────
[_SYM] = LAYOUT_ortho_4x12_1x2uC(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_EQL,
    KC_BSLS, KC_PIPE, KC_LCBR, KC_RCBR, KC_PLUS, KC_EQL,  TD(TD_LBRC), TD(TD_RBRC), KC_LT,   KC_GT,   KC_DQUO, _______,
    KC_TILD, KC_GRV,  KC_TILD, KC_LPRN, KC_RPRN, KC_MINS, KC_UNDS, KC_SLSH, KC_QUES, KC_COLN, KC_SCLN, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

// ── MOUSE ─────────────────────────────────────────────────────
//  Right hand cursor (hjkl), left hand wheel, thumbs for clicks.
//  ACL0 / ACL2 are held-to-slow / held-to-fast.
[_MOUSE] = LAYOUT_ortho_4x12_1x2uC(
    XXXXXXX, XXXXXXX, XXXXXXX, MS_UP,   XXXXXXX, MS_WHLU, XXXXXXX, MS_BTN4, MS_BTN5, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, MS_WHLL, XXXXXXX, MS_WHLR, XXXXXXX, MS_BTN3, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_BTN3, MS_BTN1,          MS_BTN2, MS_ACL0, MS_ACL2, XXXXXXX, XXXXXXX
),

// ── NIRI ──────────────────────────────────────────────────────
//  Row 0: workspaces 1-9 + last; column resize -/+
//  Row 1: apps/meta (left) · focus win + monitor (right)
//  Row 2: lock/send-to-mon + window-height -/+ · move win + col-max
//  Row 3: layout modes + launchers
//
//  Layout pairing for right hand:
//    [1][6..9]  = N_FOCL / N_FOCD / N_FOCU / N_FOCR  (focus)
//    [2][6..9]  = N_MVL  / N_MVD  / N_MVU  / N_MVR   (move, matches focus)
//    [1][10-11] = N_SCRP / N_SCRN                    (monitor L/R)
//    [2][10]    = N_CMAX
//
//  Column-management cluster (niri's strength):
//    Row 0 [10-11] = shrink / grow column     (Mod+- / Mod+=)
//    Row 2 [4-5]   = shrink / grow height     (Mod+Shift+- / Mod+Shift+=)
//    Row 3 [8]     = center column            (Mod+C)
//    Row 3 [2]     = expand column            (Mod+Ctrl+F)
//    Row 2 [10]    = maximize column          (Mod+Shift+C)
//    Row 3 [9]     = tabbed                   (Mod+W)
//    Row 3 [10]    = fullscreen               (Mod+F)
//
//  NOT bound (composable or niri-destructive):
//    - monitor up/down        → Ctrl + N_FOCU / N_FOCD
//    - move-col-to-monitor ud → Shift+Ctrl + N_FOCU / N_FOCD
//    - Mod+Escape (inhibit)   → too global; use from BASE if needed
//    - Ctrl+Alt+Delete (quit niri) → deliberate raw chord only
[_NIRI] = LAYOUT_ortho_4x12_1x2uC(
    N_WS1,   N_WS2,   N_WS3,   N_WS4,   N_WS5,   N_WS6,   N_WS7,   N_WS8,   N_WS9,   N_WSLAST, N_RSZS,  N_RSZG,
    N_FILES, N_CEXP,  N_WSPREV,N_WSNEXT,N_SHOT,  N_CHEAT, N_FOCL,  N_FOCD,  N_FOCU,  N_FOCR,   N_SCRP,  N_SCRN,
    _______, N_LOCK,  N_SCRSP, N_SCRSN, N_RSZSH, N_RSZGH, N_MVL,   N_MVD,   N_MVU,   N_MVR,    N_CMAX,  _______,
    N_KILL,  N_FLT,   N_SESS,  N_TERM,  N_LAUNCH,N_BROWSE,         _______,  _______,  N_CTR,    N_TAB,   N_FULL
),

// ── MEDIA ─────────────────────────────────────────────────────
//  Active while MO_MED (top-right pinky, BASE row 0 col 11) is held.
//  niri forwards XF86Audio* / XF86MonBrightness* to noctalia IPC.
[_MEDIA] = LAYOUT_ortho_4x12_1x2uC(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, XXXXXXX, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE
),

// ── LSP ───────────────────────────────────────────────────────
//  Active while MO_LSP (top-left pinky, BASE row 0 col 0) is held.
//  Right hand = LSP goto + hover + diagnostics (most-used).
//  Left  hand = Telescope, Trouble, Git, DAP control.
//
//  Layout summary:
//    Row 0 left : F5 / F9 / F10 / F11 / F12   (DAP function keys)
//    Row 0 right: [e ]e [d ]d  +  cs          (diag nav + symbols)
//    Row 1 left : ff sg fr fb  +  xx          (Telescope + Trouble)
//    Row 1 right: gd gD gi gy gr  K(hover)    (LSP goto + hover)
//    Row 2 left : gg  e  bd  ww  xL           (git/explorer/buffer/win)
//    Row 2 right: ca cr cf cd cl              (code actions)
//    Row 3 left : db dc du dt di              (DAP breakpoint/flow)
//    Row 3 right:       do dO                 (DAP step over / out)
//
//  All LV_* keycodes emit LazyVim key sequences via SEND_STRING —
//  you must be in normal mode for them to take effect.
[_LSP] = LAYOUT_ortho_4x12_1x2uC(
    KC_F5,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LV_PER,  LV_NER,  LV_PDI,  LV_NDI,  LV_CS,   _______,_______,
    LV_FF,   LV_SG,   LV_FR,   LV_FB,   LV_XX,   LV_GD,   LV_GDL,  LV_GI,   LV_GY,   LV_GR,   S(KC_K),_______,
    LV_GG,   LV_EE,   LV_BD,   LV_WW,   LV_XL,   LV_CA,   LV_CR,   LV_CF,   LV_CD,   LV_CL,   _______,_______,
    LV_DB,   LV_DC,   LV_DU,   LV_DT,   LV_DI,            LV_DO,   LV_DP,   XXXXXXX, XXXXXXX, XXXXXXX,_______
),

};

// ── Custom keycode handling ───────────────────────────────────
//
//  N_WS* : tap_code16(LGUI(n)) preserves externally-held Shift/Ctrl,
//          so compose move-window / move-column on the fly.
//  LV_*  : SEND_STRING-based LazyVim macros. Modifiers are cleared
//          before emitting so a resting Shift or Ctrl on the other
//          hand can't corrupt the sequence.

static void lv_send(const char *str) {
    uint8_t mods = get_mods();
    clear_mods();
    send_string(str);
    set_mods(mods);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        // niri workspaces (modifier-composable)
        case N_WS1: tap_code16(LGUI(KC_1)); return false;
        case N_WS2: tap_code16(LGUI(KC_2)); return false;
        case N_WS3: tap_code16(LGUI(KC_3)); return false;
        case N_WS4: tap_code16(LGUI(KC_4)); return false;
        case N_WS5: tap_code16(LGUI(KC_5)); return false;
        case N_WS6: tap_code16(LGUI(KC_6)); return false;
        case N_WS7: tap_code16(LGUI(KC_7)); return false;
        case N_WS8: tap_code16(LGUI(KC_8)); return false;
        case N_WS9: tap_code16(LGUI(KC_9)); return false;

        // LazyVim <leader> sequences (leader = Space)
        case LV_FF: lv_send(" ff"); return false;  // find files
        case LV_SG: lv_send(" sg"); return false;  // live grep
        case LV_FR: lv_send(" fr"); return false;  // recent files
        case LV_FB: lv_send(" fb"); return false;  // buffers
        case LV_CA: lv_send(" ca"); return false;  // code action
        case LV_CR: lv_send(" cr"); return false;  // rename
        case LV_CF: lv_send(" cf"); return false;  // format
        case LV_CD: lv_send(" cd"); return false;  // line diagnostics
        case LV_CL: lv_send(" cl"); return false;  // LSP info
        case LV_CS: lv_send(" cs"); return false;  // symbols outline
        case LV_XX: lv_send(" xx"); return false;  // trouble
        case LV_XL: lv_send(" xL"); return false;  // loclist
        case LV_GG: lv_send(" gg"); return false;  // lazygit
        case LV_EE: lv_send(" e");  return false;  // file explorer
        case LV_BD: lv_send(" bd"); return false;  // buffer delete
        case LV_WW: lv_send(" ww"); return false;  // window pick
        case LV_DB: lv_send(" db"); return false;  // toggle breakpoint
        case LV_DC: lv_send(" dc"); return false;  // continue
        case LV_DU: lv_send(" du"); return false;  // DAP UI toggle
        case LV_DT: lv_send(" dt"); return false;  // terminate
        case LV_DI: lv_send(" di"); return false;  // step into
        case LV_DO: lv_send(" do"); return false;  // step over
        case LV_DP: lv_send(" dO"); return false;  // step out (capital O)

        // LazyVim bare normal-mode sequences
        case LV_GD:  lv_send("gd"); return false;  // goto definition
        case LV_GDL: lv_send("gD"); return false;  // goto declaration
        case LV_GI:  lv_send("gi"); return false;  // goto implementation
        case LV_GY:  lv_send("gy"); return false;  // goto type definition
        case LV_GR:  lv_send("gr"); return false;  // references
        case LV_PDI: lv_send("[d"); return false;  // prev diagnostic
        case LV_NDI: lv_send("]d"); return false;  // next diagnostic
        case LV_PER: lv_send("[e"); return false;  // prev error
        case LV_NER: lv_send("]e"); return false;  // next error

        default:
            return true;
    }
}

// ── Tapping-term per-key (home-row mods) ──────────────────────
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HM_A: case HM_SC: return 220;
        case HM_S: case HM_L:  return 200;
        case HM_D: case HM_K:  return 185;
        case HM_F: case HM_J:  return 170;
        case TH_SPC: case TH_BSP: case TH_TAB: case TH_ENT: return 180;
        default: return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_SPC: case TH_BSP: case TH_TAB: case TH_ENT: return true;
        default: return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return false;
}
