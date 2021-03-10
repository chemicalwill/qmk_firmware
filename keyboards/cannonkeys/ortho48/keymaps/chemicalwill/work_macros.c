enum custom_keycodes {
    BASE_QW = SAFE_RANGE,
    BASE_TD,
    EMAIL,
    ENTTGM,
    MNL,
    OTHER,
    RESCUE,
    TROUGH
};

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

        case BASE_QW:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            } else {
            }
            break;

        case BASE_TD:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORK);
            } else {
            }
            break;

        case EMAIL:
            if (record->event.pressed) {
                SEND_STRING("william.hedges@ascension.org");
            } else {
            }
            break;

        case ENTTGM:
            if (record->event.pressed) {
                tap_code(KC_ENTER);
                layer_invert(_META);
            } else {
            }
            break;

        case MNL:
            if (record->event.pressed) {
                tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB);
                tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB);
                tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB);
                tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB);
                tap_code(KC_TAB); // total of 21 tabs as of 11/16
                tap_code(KC_P);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code(KC_DOWN);
                tap_code16(A(KC_O));
            } else {
            }
            break;

        case OTHER:
            if (record->event.pressed) {
                tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB); tap_code(KC_TAB);
                SEND_STRING("other");
                tap_code(KC_TAB);
            } else {
            }
            break;

        case RESCUE:
            if (record->event.pressed) {
                SEND_STRING("po5004");
                tap_code(KC_ENTER);
            } else {
            }
            break;

        case TROUGH:
            if (record->event.pressed) {
                SEND_STRING("Please draw prior to TIME dose and hold dose until trough results and addressed by pharmacy. Thank you!");
            } else {
            }
            break;

        }
    return true;
};
