
void encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(_FN)) {
        if (clockwise) {
            tap_code16(C(KC_TAB));
        } else {
            tap_code16(C(S(KC_TAB)));
        }
    } else {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    }
};
