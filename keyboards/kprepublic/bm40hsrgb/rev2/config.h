// ============================================================
//  config.h — BM40RGB v2 user config
//  Tune QMK behaviour for home-row mods + fast programming use
// ============================================================

#pragma once

// ── Tapping ──────────────────────────────────────────────────
// Base tapping term (per-key overrides in keymap.c)
#define TAPPING_TERM 150

// Prevent accidental mod-tap triggers when rolling keys quickly
// IMPORTANT: do NOT enable PERMISSIVE_HOLD globally — only for thumb keys
// (handled per-key in get_permissive_hold)
#undef PERMISSIVE_HOLD

// Ignore key presses that happen very quickly after a tap
// Helps distinguish tap-then-type from hold-then-type
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Required for get_tapping_term to work
// (already implied by TAPPING_TERM_PER_KEY but explicit for clarity)

// ── Tap-dance ────────────────────────────────────────────────
// Slightly faster tap-dance window than tapping term
#define TAPPING_TERM_TAP_DANCE 180

// ── Mouse keys ───────────────────────────────────────────────
// Default accelerated mode (no MK_KINETIC_SPEED / MOUSEKEY_INERTIA):
// those modes ignore MS_ACL0/MS_ACL2 or use a different set of knobs.
//   tap        → 4 px nudge
//   hold       → ramps 4 → 32 px/frame over ~0.8 s  (≈2000 px/s top)
//   + MS_ACL0  → fixed  8 px/frame (≈500 px/s)  precise UI targeting
//   + MS_ACL2  → fixed 32 px/frame (≈2000 px/s) skip the ramp
// Speed in px/s = MOVE_DELTA * MAX_SPEED * 1000 / INTERVAL.

// Cursor
#define MOUSEKEY_DELAY            10  // x10 ms → 100 ms before repeat (taps stay single nudges)
#define MOUSEKEY_INTERVAL         16  // ~60 Hz reports
#define MOUSEKEY_MOVE_DELTA        4  // px per step at start of ramp
#define MOUSEKEY_MAX_SPEED         8  // top = MOVE_DELTA * 8 = 32 px/step
#define MOUSEKEY_TIME_TO_MAX      50  // steps to reach top (~0.8 s)

// Scroll wheel (one unit = one wheel notch)
//   hold → ~16 notches/s ramping to ~50/s over ~3 s; ACL2 = top instantly
#define MOUSEKEY_WHEEL_DELAY      10  // x10 ms → 100 ms before repeat
#define MOUSEKEY_WHEEL_INTERVAL   60  // ms between notches
#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   3  // top = 3 notches per interval
#define MOUSEKEY_WHEEL_TIME_TO_MAX 50

// ── Combos (optional convenience pairs) ─────────────────────
// Uncomment to enable. Uses very tight timing to avoid false triggers.
// #define COMBO_ENABLE
// #define COMBO_TERM 30

// Debounce algorithm — sym_eager_pr is best for per-key mods
#define DEBOUNCE_TYPE sym_eager_pr
#define DEBOUNCE 5
