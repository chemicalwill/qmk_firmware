/*
Copyright 2020 chemicalwill <https://github.com/chemicalwill>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

//layer enums, add as necessary in stack order
enum layers {
    _BASE,
    _FN1,
    _FN2,
};

//custom keycode enums, add as necessary. first one should be SAFE_RANGE, order doesn't matter (i tend to alphabetize them)
enum custom_keycodes {
    MACRO1 = SAFE_RANGE,
    MACRO2,
    MACRO3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_83_ansi(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_DEL,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        MO(_FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT_83_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_PGUP,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_FN2] = LAYOUT_83_ansi(
        _______, MACRO1,  MACRO2,  MACRO3,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),

/*
    [_BLANK] = LAYOUT_83_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),
*/
};


/* for macros you can follow this general format. each macro is it's own 'case' - i tried to give some examples of things you might see.

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HELLO:
            if (record->event.pressed) {
                // when keycode HELLO is pressed
                SEND_STRING("Hello, world!");
            } else {
                // when keycode HELLO is released
            }
            break;
    }
    return true;
};

*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO1:
            if (record->event.pressed) {
            // when keycode MACRO1 is pressed
                SEND_STRING("apple");
                tap_code(KC_TAB);
            } else {
            // when keycode MACRO1 is released
            }
            break;

        case MACRO2:
            if (record->event.pressed) {
            // when keycode MACRO2 is pressed
                SEND_STRING("pear");
                tap_code(KC_ENTER);
            } else {
            // when keycode MACRO2 is released
            }
            break;

        case MACRO3:
            if (record->event.pressed) {
            // when keycode MACRO3 is pressed
                tap_code16(C(KC_X));
                tap_code(KC_TAB);
                tap_code16(C(KC_V));
            } else {
            // when keycode MACRO3 is released
            }
            break;

    }
    return true;
};
