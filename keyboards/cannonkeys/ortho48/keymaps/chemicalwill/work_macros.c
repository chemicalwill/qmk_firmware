enum custom_keycodes {
    BASE_QW = SAFE_RANGE,
    BASE_TD,
    EMAIL,
    ENTTGM,
    MNL,
    TPN,
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
            // when keycode BASE_QW is pressed
            set_single_persistent_default_layer(_QWERTY);
        } else {
            // when keycode BASE_QW is released
        }
        break;

    case BASE_TD:
        if (record->event.pressed) {
            // when keycode BASE_TD is pressed
            set_single_persistent_default_layer(_WORK);
        } else {
            // when keycode BASE_TD is released
        }
        break;

    case EMAIL:
        if (record->event.pressed) {
            // when keycode EMAIL is pressed
            SEND_STRING("william.hedges@ascension.org");
        } else {
            // when keycode EMAIL is released
        }
        break;

    case ENTTGM:
        if (record->event.pressed) {
            // when keycode ENTTGM is pressed
            tap_code(KC_ENTER);
            layer_invert(_META);
        } else {
            // when keycode ENTTGM is released
        }
        break;

    case MNL:
        if (record->event.pressed) {
            // when keycode MNL is pressed
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
            // when keycode MNL is released
        }
        break;

    case TPN:
        if (record->event.pressed) {
            // when keycode TPN is pressed
            SEND_STRING("t\t1600\tt+\t1559");
            SEND_STRING("\t\t\t\t" SS_LCTL("ax") SS_LSFT("\t\t") SS_LCTL("v") "\t\t\t\t\tw\t");
        } else {
            // when keycode TPN is released
        }
        break;

    }
    return true;
};
