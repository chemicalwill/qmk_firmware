/*
make 40percentclub/mf68:chemicalwill
make 40percentclub/mf68:chemicalwill:flash
*/

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _FN 1

#define FN_CAPS LT(_FN, KC_CAPS)

//Custom keycodes
enum custom_keycodes {
  MKRSTF = SAFE_RANGE,
};

//Setting up Tap Dance for tap vs. hold
typedef struct {
  bool is_press_action;
  int state;
  } xtap;

//Tap Dance states
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  };

//Tap dance enums
enum {
  FIVE_F5 = 0,
  NO_INS = 1,
  PGUP_HOME = 2,
  PGDN_END = 3
  };

int cur_dance (qk_tap_dance_state_t *state);

//for tap dance, put void statements here so they can be used in any keymap.
void five_finished (qk_tap_dance_state_t *state, void *user_data);
void five_reset (qk_tap_dance_state_t *state, void *user_data);

void noins_finished (qk_tap_dance_state_t *state, void *user_data);
void noins_reset (qk_tap_dance_state_t *state, void *user_data);

void pgup_finished (qk_tap_dance_state_t *state, void *user_data);
void pgup_reset (qk_tap_dance_state_t *state, void *user_data);

void pgdn_finished (qk_tap_dance_state_t *state, void *user_data);
void pgdn_reset (qk_tap_dance_state_t *state, void *user_data);

//Actual keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_68_ansi(
    KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    TD(FIVE_F5), KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,          TD(NO_INS), TD(PGUP_HOME),
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,     TD(PGDN_END),
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,          KC_UP,
    KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                                 KC_RALT, MO(_FN), KC_RCTL,                   KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_FN] = LAYOUT_68_ansi(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_BSPC,          _______, KC_VOLU,
    _______, _______, _______, KC_END,  _______, _______, _______, _______, KC_UP,   _______,  _______, _______, _______, _______,          _______, KC_VOLD,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,                   _______,          KC_MUTE,
    _______, MKRSTF,  _______,                            _______,                             _______, _______, _______,          KC_MPRV, KC_MPLY, KC_MNXT
  )
};

//Macros
/* here's a cool-ass example:
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SWAGGER:
      if (record->event.pressed) {
        // when keycode SWAGGER is pressed
        SEND_STRING("I got the most swag on this corner of the street :sunglasses:!");
      } else {
        // when keycode SWAGGER is released
      }
      break;
  }
  return true;
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MKRSTF:
      if (record->event.pressed) {
        // when keycode MKRSTF is pressed
        if (host_keyboard_led_state().caps_lock == true) { //check to see if CAPS is on, and switch it off if so
          tap_code(KC_CAPS);
        } else {
          SEND_STRING("make 40percentclub/mf68:chemicalwill:flash");
          tap_code(KC_ENTER);
          reset_keyboard();
        }
      } else {
      // when keycode MKRSTF is released
    }
    break;
  }
  return true;
};


//TAP DANCE
//Determine tap state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->interrupted || !state->pressed) {
    return SINGLE_TAP;
  } else {
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'
    return SINGLE_HOLD;
  }
};

//instance 'tap' for the '5/F5' tap dance
static xtap fivetap_state = {
  .is_press_action = true,
  .state = 0
};
void five_finished (qk_tap_dance_state_t *state, void *user_data) {
  fivetap_state.state = cur_dance(state);
  switch (fivetap_state.state) {
    case SINGLE_TAP:
      register_code(KC_5);
      break;
    case SINGLE_HOLD:
      tap_code(KC_F5);
      break;
  }
}
void five_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (fivetap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_5);
      break;
  }
  fivetap_state.state = 0;
}

//instance 'tap' for the 'no/INS' tap dance
static xtap noinstap_state = {
  .is_press_action = true,
  .state = 0
};
void noins_finished (qk_tap_dance_state_t *state, void *user_data) {
  noinstap_state.state = cur_dance(state);
  switch (noinstap_state.state) {
    case SINGLE_TAP:
      register_code(KC_NO);
      break;
    case SINGLE_HOLD:
      register_code(KC_INS);
      break;
  }
}
void noins_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (noinstap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_NO);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_INS);
      break;
  }
  noinstap_state.state = 0;
}

//instance 'tap' for the 'pgup' tap dance
static xtap pguptap_state = {
  .is_press_action = true,
  .state = 0
};
void pgup_finished (qk_tap_dance_state_t *state, void *user_data) {
  pguptap_state.state = cur_dance(state);
  switch (pguptap_state.state) {
    case SINGLE_TAP:
      register_code(KC_PGUP);
      break;
    case SINGLE_HOLD:
      register_code(KC_HOME);
      break;
  }
}
void pgup_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (pguptap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_PGUP);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_HOME);
      break;
  }
  pguptap_state.state = 0;
}

//instance 'tap' for the 'pgdn' tap dance
static xtap pgdntap_state = {
  .is_press_action = true,
  .state = 0
};
void pgdn_finished (qk_tap_dance_state_t *state, void *user_data) {
  pgdntap_state.state = cur_dance(state);
  switch (pgdntap_state.state) {
    case SINGLE_TAP:
      register_code(KC_PGDN);
      break;
    case SINGLE_HOLD:
      register_code(KC_END);
      break;
  }
}
void pgdn_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (pgdntap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_PGDN);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_END);
      break;
  }
  pgdntap_state.state = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [FIVE_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, five_finished, five_reset),
  [NO_INS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, noins_finished, noins_reset),
  [PGUP_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgup_finished, pgup_reset),
  [PGDN_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgdn_finished, pgdn_reset)
};
