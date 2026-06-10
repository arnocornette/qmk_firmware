# ============================================================
#  rules.mk — BM40RGB v2
# ============================================================
#
#  Per-keymap feature flags. Board defaults come from the
#  keyboard's own rules.mk — this file enables/disables only
#  what this keymap specifically needs.
#
#  Key principle for 40% keyboards: firmware space is tight
#  (~28KB usable on atmega32u4). Enable only what you use.
# ============================================================

# ── Required by the keymap ──────────────────────────────────

# Tap-dance: for TD_LBRC, TD_RBRC, TD_SLSH, TD_GRV
TAP_DANCE_ENABLE = yes

# Mousekeys: the entire _MOUSE layer depends on these
MOUSEKEY_ENABLE = yes

# Extra keycodes: needed for MS_* mouse keys, XF86 media keys,
# and LGUI/LSFT/LCTL modifier combos in the _QTILE layer
EXTRAKEY_ENABLE = yes

# NKRO: full n-key rollover. Required by FORCE_NKRO in config.h.
# Improves reliability for home row mods + rolling presses.
NKRO_ENABLE = yes


# ── Recommended but optional ────────────────────────────────

# Tri-layer support is built into QMK core (no rules.mk flag
# needed). update_tri_layer_state() is always available.

# RGB matrix — BM40RGB ships with per-key RGB. Enable if you
# want the _MEDIA layer RGB_* keys to work. Disable to save
# ~6KB of firmware if you don't care about lighting.
RGB_MATRIX_ENABLE = no


# ── Explicitly disabled (save firmware space) ───────────────

# Console/command access — useful for debugging, but costs space
# and requires hid_listen running. Enable temporarily if you need
# to debug a keymap issue.
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

# Bootmagic lite — lets you hold a key on plug-in to reset.
# Useful safety net. Costs ~500 bytes. Disable if tight on space.
BOOTMAGIC_ENABLE = yes

# Audio — this keyboard has no speaker, and audio code is large.
AUDIO_ENABLE = no

# Unicode — not used in this keymap. Saves ~2KB.
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = no
UCIS_ENABLE = no

# Key lock (KC_LOCK) — not used. Saves a little space.
KEY_LOCK_ENABLE = no

# Leader key — not used in this keymap. Saves ~1KB.
LEADER_ENABLE = no

# Combos — not used. If you later want keys like "j+k = Esc",
# flip this to yes and add a combo table.
COMBO_ENABLE = no

# Dynamic macros — not used.
DYNAMIC_MACRO_ENABLE = no

# Auto shift — disabled; we use home row mods for shift instead.
AUTO_SHIFT_ENABLE = no


# ── Bootloader ──────────────────────────────────────────────
#
#  The BM40RGBH v2 uses the atmel-dfu bootloader. This is
#  usually set in the keyboard's own rules.mk — only override
#  here if yours isn't the standard v2 board. If you get
#  "avrdude: error" during flash, your board might need:
#    BOOTLOADER = caterina
#    BOOTLOADER = qmk-dfu
# BOOTLOADER = atmel-dfu


# ── Link-Time Optimization ──────────────────────────────────
#
#  Significantly reduces firmware size (often 20-30%). Safe
#  with modern QMK. Enable if you're running out of space.
LTO_ENABLE = yes
