bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void encoder_update_user(uint8_t index, bool clockwise) {

    switch(get_highest_layer(layer_state | default_layer_state)) {

        case _WORK:
            if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code(KC_TAB);
            } else { // if counterclockwise
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
            if (is_alt_tab_active) { // check the time elapsed
                if (timer_elapsed(alt_tab_timer) > 750) {
                    unregister_code(KC_LALT);
                    is_alt_tab_active = false;
                }
            }
            break;

        case _QWERTY:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;

        case _RAISE:
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(C(S(KC_TAB)));
            }
            break;

        case _FN:
            if (clockwise) {
                tap_code(KC_MS_WH_DOWN);
            } else {
                tap_code(KC_MS_WH_UP);
            }
            break;

    }
};

void matrix_scan_user(void) { // timer function
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 750) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
};
