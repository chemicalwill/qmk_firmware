//macro keycode declarations
enum custom_keycodes {
    BASE_QW = SAFE_RANGE,
    BASE_TD,
    CUTCOMM,
    DEFER,
    DUPE,
    EMAIL,
    ENTTGM,
    HMPROD,
    LABEL0,
    MNLOK,
    NOTSIG,
    FENTPACU,
    PROFILE,
    QUEUE,
    REHABDC,
    TPNTCOM,
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
            set_single_persistent_default_layer(_WORKTD);
        } else {
            // when keycode BASE_TD is released
        }
        break;

    case CUTCOMM:
        if (record->event.pressed) {
            // when keycode CUTCOMM is pressed
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code16(C(KC_A));
            tap_code16(C(KC_X));
            tap_code16(S(KC_TAB));
            tap_code16(S(KC_TAB));
            tap_code16(C(KC_V));
        } else {
            // when keycode CUTCOMM is released
        }
        break;

    case DEFER:
        if (record->event.pressed) {
            // when keycode DEFER is pressed
            tap_code16(S(KC_TAB));
            tap_code(KC_D);
            tap_code(KC_TAB);
        } else {
            // when keycode DEFER is released
        }
        break;

    case DUPE:
        if (record->event.pressed) {
            // when keycode DUPE is pressed
            tap_code(KC_TAB); //tab to Discontinue Reason
            tap_code(KC_TAB); //select "Duplicate"
            tap_code(KC_D);
            tap_code(KC_TAB); //tab to Label Copies
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_0);
            tap_code16(A(KC_0));
        } else {
            // when keycode DUPE is released
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

    case FENTPACU:
        if (record->event.pressed) {
            // when keycode FENTPACU is pressed
            tap_code(KC_DOWN);
            tap_code(KC_ENTER);
            tap_code(KC_TAB);
            SEND_STRING("prn pacu use only");
        } else {
            // when keycode FENTPACU is released
        }
        break;

    case HMPROD:
        if (record->event.pressed) {
            // when keycode HMPROD is pressed
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_DOWN);
            tap_code16(A(KC_M));
            tap_code16(A(KC_O));
        } else {
            // when keycode HMPROD is released
        }
        break;

    case LABEL0:
        if (record->event.pressed) {
            // when keycode LABEL0 is pressed
            tap_code16(A(KC_P));
            tap_code(KC_SPC);
            tap_code16(A(KC_O));
        } else {
            // when keycode LABEL0 is released
        }
        break;

    case MNLOK:
        if (record->event.pressed) {
            // when keycode MNLOK is pressed
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
            // when keycode MNLOK is released
        }
        break;

    case NOTSIG:
        if (record->event.pressed) {
            // when keycode NOTSIG is pressed
            tap_code16(S(KC_TAB));
            SEND_STRING("nnn\t");
        } else {
            // when keycode NOTSIG is released
        }
        break;

    case PROFILE:
        if (record->event.pressed) {
            // when keycode PROFILE is pressed
            tap_code(KC_V);
            tap_code(KC_V);
            tap_code16(A(KC_A));
        } else {
            // when keycode PROFILE is released
        }
        break;

    case QUEUE:
        if (record->event.pressed) {
            // when keycode QUEUE is pressed
            tap_code16(C(KC_P));
            wait_ms(250);
            tap_code16(A(KC_M));
            wait_ms(250);
            tap_code(KC_F5);
        } else {
            // when keycode QUEUE is released
        }
        break;

    case REHABDC:
        if (record->event.pressed) {
            // when keycode REHABDC is pressed
            tap_code(KC_TAB);   //tab to Discontinue Reason dropdown
            tap_code(KC_TAB);
            tap_code(KC_DOWN);  //select "Patient Discharged"
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_TAB);   //tab to Label Copies
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_0);
            tap_code16(A(KC_O));
        } else {
            // when keycode REHABDC is released
        }
        break;

    case TPNTCOM:
        if (record->event.pressed) {
            // when keycode TPNTCOM is pressed
            SEND_STRING("t\t1600\tt+\t1559");
            SEND_STRING("\t\t\t\t" SS_LCTL("ax") SS_LSFT("\t\t") SS_LCTL("v") "\t\t\t\t\tw\t");
        } else {
            // when keycode TPNTCOM is released
        }
        break;
    }
    return true;
};
