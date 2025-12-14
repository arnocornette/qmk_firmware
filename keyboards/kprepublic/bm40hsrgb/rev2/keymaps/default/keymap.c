#include QMK_KEYBOARD_H



enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BLTog| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12_1x2uC(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
    KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_NO, KC_SPC,KC_TILD, KC_BSLS, KC_LBRC, KC_RBRC,  KC_QUOT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    KC_1,   KC_2,   KC_3,    KC_4,   KC_5,    KC_6,   KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS,  KC_EQUAL,
    KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,  LGUI(KC_DOWN),  LGUI(KC_UP),
    _______,  KC_NO,  KC_NO,  KC_NO,  KC_MEDIA_PREV_TRACK,  KC_VOLD,  KC_VOLU,  KC_MEDIA_NEXT_TRACK, KC_NO,  KC_NO,  LGUI(KC_LEFT),  LGUI(KC_RIGHT),
    _______,  _______,  _______,  _______,  _______,  KC_MEDIA_PLAY_PAUSE,  _______,  KC_NO,  KC_NO,  KC_NO,  KC_KB_MUTE
),
};

