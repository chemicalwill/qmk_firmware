/*
make 1upkeyboards/1up60hte:chemicalwill:flash
*/

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _FN 1

#define FN_CAPS LT(_FN, KC_CAPS)

//Setting up Tap Dance for tap vs. hold
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2
};

//Tap dance enums
enum {
  FIVE_F5 = 0
};

int cur_dance (qk_tap_dance_state_t *state);

//for tap dance, put void statements here so they can be used in any keymap.
void five_finished (qk_tap_dance_state_t *state, void *user_data);
void five_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_tsangan(
		KC_GESC,  	KC_1,    KC_2,    KC_3,    KC_4,    TD(FIVE_F5), KC_6,    KC_7,    KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_DEL,
		KC_TAB,  	KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, 	KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
		KC_LCTL, 	KC_LGUI, KC_LALT, 							     KC_SPC,  					  		  KC_BTN1, KC_RGUI, KC_RCTL
		),

	[_FN] = LAYOUT_tsangan(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,  KC_F12,   RESET, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,  _______,  _______, _______, KC_BSLS,
		_______, _______, _______, _______, _______,  KC_END, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  _______,  _______, _______,
		_______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______,  KC_BSLS,  _______, _______,
		_______, _______, _______, 							  _______, 							   KC_MPRV, KC_MPLY, KC_MNXT
		),

	/*
	[_BLANK] = LAYOUT_tsangan(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, 							  _______, 							  _______, _______, _______
		),
	*/
	}
;

//TAP DANCE
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->interrupted || !state->pressed)  return SINGLE_TAP;
  //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
  else return SINGLE_HOLD;
};

//instanalize an instance of 'tap' for the '5/F5' tap dance.
static tap fivetap_state = {
  .is_press_action = true,
  .state = 0
};

void five_finished (qk_tap_dance_state_t *state, void *user_data) {
  fivetap_state.state = cur_dance(state);
  switch (fivetap_state.state) {
    case SINGLE_TAP: register_code(KC_5); break;
    case SINGLE_HOLD: register_code(KC_F5); break;
  }
};

void five_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (fivetap_state.state) {
    case SINGLE_TAP: unregister_code(KC_5); break;
    case SINGLE_HOLD: unregister_code(KC_F5); break;
  }
  fivetap_state.state = 0;
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [FIVE_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, five_finished, five_reset)
};
