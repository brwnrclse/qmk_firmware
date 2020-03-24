#include QMK_KEYBOARD_H

#define SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

bool todage_numlck_on = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_all(
        KC_ESC,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_MINS, KC_PPLS,  KC_GRV, KC_NCLK,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        TG(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_BSPC, KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_SLSH, KC_PEQL,
        _______, KC_LGUI, KC_LALT,                   KC_LEFT, KC_SPC, KC_RIGHT,                  LT(1, KC_BTN1), KC_RGUI, KC_LALT, KC_LCTL, KC_APP
    ),

	[1] = LAYOUT_all(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
        _______, RGB_TOG, KC_UP,   RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
    ),

};

/**
 * On keypress show the 'Shifted' value and when pressed while Shift is held or
 *     NumLock is on then show the number.
 *
 */
void flip_num_key_shift(uint16_t keycode, bool pressed) {
  if (pressed) {
    if ((get_mods() && SHIFT_MASK) || todage_numlck_on) {
      register_code(keycode);
    } else {
      register_code(KC_LSFT);
      register_code(keycode);
    }
  } else {
    if ((get_mods() && SHIFT_MASK) || todage_numlck_on) {
      unregister_code(keycode);
    } else {
      register_code(KC_LSFT);
      register_code(keycode);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) { // Symbols first
    case (KC_0):
    case (KC_1):
    case (KC_2):
    case (KC_3):
    case (KC_4):
    case (KC_5):
    case (KC_6):
    case (KC_7):
    case (KC_8):
    case (KC_9): {
      flip_num_key_shift(keycode, record->event.pressed);
      return false; break;
    }
    case(KC_NLCK): { // Numlock controls the top row
      # TODO call register_lock_code here

      return false; break;
    }
    case(KC_BSPC): { // Backspace on press and Delete when pressed w/ Shift
        if ((get_mods() && SHIFT_MASK)) {
            register_code(KC_DEL);
        } else {
            register_code(KC_BSPC);
        }
    }
    default: return true;
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  writePin(F4, layer_state_is(1) ? 1 : 0); // Set numlock led when in layer 1

  return state;
}
