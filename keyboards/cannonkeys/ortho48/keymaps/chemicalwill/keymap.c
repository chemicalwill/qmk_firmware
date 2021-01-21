
#include QMK_KEYBOARD_H

enum layers {
    _WORK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _FN,
    _META,
    _CODE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN MO(_FN)
#define META MO(_META)
#define CODE MO(_CODE)
#define FN_F5 LT(_FN, KC_F5)
#define OS_CODE OSL(_CODE)
#define TG_META TG(_META)

#define LS_CAPS LSFT_T(KC_CAPS)
#define RS_ENTER RSFT_T(KC_ENTER)

#include "work_macros.c"
#include "work_tap_dances.c"
#include "encoder.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* WORK
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |Q uvom|   W  |E AltE|R dcdc|T AltT|   Y  |U AltU|   I  |O AltO|P labl| Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Tab  |A AltA|S AltS| D TD |F fent|   G  |H prod|   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |S CAPS|   Z  |X cmnt|   C  |V prof|   B  |N AltN|M AltM|   ,  |   .  |  Up  |S Entr|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |WKMeta| LAlt |OSCode| Lower|    Space    | Raise| Fn F5 | Left | Down | Right|
    * `-----------------------------------------------------------------------------------'
    */
    [_WORK] = LAYOUT_ortho_4x12(
        KC_ESC,  Q_UVOM,  KC_W,    E_ALTE,   R_REHABDC, T_ALTT,  KC_Y,     U_ALTU,  KC_I,    O_ALTO,  P_0LABL, KC_BSPC,
        KC_TAB,  A_ALTA,  S_ALTS,  D_MACROS, F_FENT,    KC_G,    H_HMPROD, KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LS_CAPS, KC_Z,    X_COMMS, KC_C,     V_PROF,    KC_B,    N_NOTSIG, M_ALTM,  KC_COMM, KC_DOT,  KC_UP,   RS_ENTER,
        KC_LCTL, WK_META, KC_LALT, OS_CODE,  LOWER,     KC_SPC,  KC_SPC,   RAISE,   FN_F5,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* QWERTY
    * ,-----------------------------------------------------------------------------------.
    * | MPLY |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |S CAPS|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |S Entr|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |WKMeta| LAlt | Code |Lower |    Space    | Raise|  Fn  | Left | Down |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_MPLY, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LS_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_UP,   RS_ENTER,
        KC_LCTL, WK_META, KC_LALT, CODE,    LOWER,   KC_SPC,  KC_SPC,  RAISE,  FN,      KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /* LOWER
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Del  |   `  |      |      |      |      |      |   -  |   =  |   [  |   ]  |   \  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |   /  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  KC_GRV,  _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* RAISE
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Del  |   ~  |      |      |      |      |      |   _  |   +  |   {  |   }  |   |  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |   ?  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_TILD, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUES, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* FN
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Esc  |  F11 |  F12 |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      | PgUp |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |BASEQW|             |BASETD|      | Home | PgDn | End  |
    * `-----------------------------------------------------------------------------------'
    */
    [_FN] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        KC_ESC,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______, _______, _______, BASE_QW, _______, _______, BASE_TD, _______, KC_HOME, KC_PGDN, KC_END
    ),

    /* META
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |      |      |      |      |   7  |   8  |   9  |  - / |      |      | Tab  |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | Del  |      |      |      |      |   4  |   5  |   6  |  + * |      |      | Del  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |   1  |   2  |   3  | Enter|      |  Up  |ENTTGM|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |TGMETA|      |      |      |      0      |   .  | Enter| Left | Down | Right|
    * `-----------------------------------------------------------------------------------'
    */
    [_META] = LAYOUT_ortho_4x12(
        KC_TAB,  _______, _______, _______, _______, KC_7,   KC_8,   KC_9,   MINS_SLSH, _______, _______, KC_BSPC,
        KC_DEL,  _______, _______, _______, _______, KC_4,   KC_5,   KC_6,   PLUS_ASTR, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, KC_1,   KC_2,   KC_3,   KC_ENTER,  _______, KC_UP,   ENTTGM,
        _______, TG_META, _______, _______, _______, KC_0,   KC_0,   KC_DOT, KC_ENTER,  KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* CODE
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      | EMAIL|      | TPN  |      |      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      | MNL  |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_CODE] = LAYOUT_ortho_4x12(
        _______, _______, _______, EMAIL,   _______, TPN,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, MNL,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* BLANK
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    /*[_BLANK] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    */
};
