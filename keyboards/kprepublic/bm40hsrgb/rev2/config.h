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
// Use kinetic mouse mode for smooth acceleration
#define MK_KINETIC_SPEED

// Base cursor speed (modified by MS_SLOW / MS_FAST in process_record)
#define MOUSEKEY_BASE_SPEED       900
#define MOUSEKEY_DECELERATED_SPEED 200
#define MOUSEKEY_ACCELERATED_SPEED 3000

// How quickly the cursor accelerates from base to max
#define MOUSEKEY_MOVE_DELTA       8
// Time between cursor moves (lower = faster polling)
#define MOUSEKEY_INTERVAL         16  // ~60Hz
// Delay before acceleration starts (ms)
#define MOUSEKEY_TIME_TO_MAX      40

// Scroll speed
#define MOUSEKEY_WHEEL_BASE_SPEED     12
#define MOUSEKEY_WHEEL_INTERVAL       100
#define MOUSEKEY_WHEEL_TIME_TO_MAX    40
#define MOUSEKEY_WHEEL_DECELERATED_SPEED 3
#define MOUSEKEY_WHEEL_ACCELERATED_SPEED 50
#define MOUSEKEY_WHEEL_DELTA          1

// ── Combos (optional convenience pairs) ─────────────────────
// Uncomment to enable. Uses very tight timing to avoid false triggers.
// #define COMBO_ENABLE
// #define COMBO_TERM 30

// Debounce algorithm — sym_eager_pr is best for per-key mods
#define DEBOUNCE_TYPE sym_eager_pr
#define DEBOUNCE 5
