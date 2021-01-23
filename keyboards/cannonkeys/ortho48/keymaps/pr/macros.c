
enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    ENTTGM,
    //MACRO3,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case EMAIL:
            if (record->event.pressed) {
                // when keycode EMAIL is pressed
                SEND_STRING("chemicalwill92@gmail.com");
            } else {
                // when keycode EMAIL is released
            }
            break;

        case ENTTGM: // sends ENTER and toggles off the _META numpad layer
            if (record->event.pressed) {
                // when keycode ENTTGM is pressed
                tap_code(KC_ENTER);
                layer_invert(_META);
            } else {
                // when keycode ENTTGM is released
            }
            break;

        /*
        case MACRO3:
            if (record->event.pressed) {
                // when keycode MACRO3 is pressed
                SEND_STRING("And here's where I'd put another macro... if I had one!");
            } else {
                // when keycode MACRO3 is released
            }
            break;
        */

        }
    return true;
};
