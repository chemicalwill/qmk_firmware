void encoder_update_user(bool clockwise) {
    if (clockwise) {
        tap_code(KC_TAB);
    } else {
        tap_code16(S(KC_TAB));
    }
}
