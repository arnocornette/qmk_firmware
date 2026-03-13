# ============================================================
#  rules.mk — BM40RGB v2
#  Enable only what's needed to keep firmware size reasonable
# ============================================================

# Core features
MOUSEKEY_ENABLE    = yes   # Mouse key emulation
TAP_DANCE_ENABLE   = yes   # Tap-dance ([ vs {, etc.)
EXTRAKEY_ENABLE    = yes   # Media keys + system keys
UNICODE_ENABLE     = no    # Not needed; saves space

# Mod-tap / layer-tap helpers
# (these are built-in; listed here for visibility)
# LT / MT are always available in QMK

# Combos — disable unless you add combo definitions
COMBO_ENABLE       = no

# Console (disable in production to save space)
CONSOLE_ENABLE     = no
COMMAND_ENABLE     = no

# Link-time optimisation — reduces firmware size
LTO_ENABLE         = yes
