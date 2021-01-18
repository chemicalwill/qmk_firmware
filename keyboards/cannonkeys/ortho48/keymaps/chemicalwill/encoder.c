
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_TAB);
    } else {
        tap_code16(S(KC_TAB));
    }
};
