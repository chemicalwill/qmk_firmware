//Setting up Tap Dance for tap vs. hold
typedef struct {
    bool is_press_action;
    int state;
} tap;

//Tap Dance states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
};

//Tap dance enums
enum {
    GRV_ESC = 0,
    NO_INS = 1,
    PGUP_HOME = 2,
    PGDN_END = 3
};


int cur_dance (qk_tap_dance_state_t *state);

//for tap dance, put void statements here so they can be used in any keymap.
void grv_finished (qk_tap_dance_state_t *state, void *user_data);
void grv_reset (qk_tap_dance_state_t *state, void *user_data);

void noins_finished (qk_tap_dance_state_t *state, void *user_data);
void noins_reset (qk_tap_dance_state_t *state, void *user_data);

void pgup_finished (qk_tap_dance_state_t *state, void *user_data);
void pgup_reset (qk_tap_dance_state_t *state, void *user_data);

void pgdn_finished (qk_tap_dance_state_t *state, void *user_data);
void pgdn_reset (qk_tap_dance_state_t *state, void *user_data);


//Determine tap state
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->interrupted || !state->pressed) {
        return SINGLE_TAP;
    } else {
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'
        return SINGLE_HOLD;
    }
};

//instance 'tap' for the 'grv/ESC' tap dance
static tap grvtap_state = {
    .is_press_action = true,
    .state = 0
};
void grv_finished (qk_tap_dance_state_t *state, void *user_data) {
    grvtap_state.state = cur_dance(state);
    switch (grvtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_GRV);
            break;
        case SINGLE_HOLD:
            register_code(KC_ESC);
            break;
    }
};
void grv_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (grvtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_GRV);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_ESC);
            break;
    }
    grvtap_state.state = 0;
};

//instance 'tap' for the 'no/INS' tap dance
static tap noinstap_state = {
    .is_press_action = true,
    .state = 0
};
void noins_finished (qk_tap_dance_state_t *state, void *user_data) {
    noinstap_state.state = cur_dance(state);
    switch (noinstap_state.state) {
        case SINGLE_TAP:
            register_code(KC_NO);
            break;
        case SINGLE_HOLD:
            register_code(KC_INS);
            break;
    }
};
void noins_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (noinstap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_NO);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_INS);
            break;
    }
    noinstap_state.state = 0;
};

//instance 'tap' for the 'pgup' tap dance
static tap pguptap_state = {
    .is_press_action = true,
    .state = 0
};
void pgup_finished (qk_tap_dance_state_t *state, void *user_data) {
    pguptap_state.state = cur_dance(state);
    switch (pguptap_state.state) {
        case SINGLE_TAP:
            register_code(KC_PGUP);
            break;
        case SINGLE_HOLD:
            register_code(KC_HOME);
            break;
    }
};
void pgup_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (pguptap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_PGUP);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_HOME);
            break;
    }
    pguptap_state.state = 0;
};

//instance 'tap' for the 'pgdn' tap dance
static tap pgdntap_state = {
    .is_press_action = true,
    .state = 0
};
void pgdn_finished (qk_tap_dance_state_t *state, void *user_data) {
    pgdntap_state.state = cur_dance(state);
    switch (pgdntap_state.state) {
        case SINGLE_TAP:
            register_code(KC_PGDN);
            break;
        case SINGLE_HOLD:
            register_code(KC_END);
            break;
    }
};
void pgdn_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (pgdntap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_PGDN);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_END);
            break;
    }
    pgdntap_state.state = 0;
};

//Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [GRV_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, grv_finished, grv_reset),
    [NO_INS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, noins_finished, noins_reset),
    [PGUP_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgup_finished, pgup_reset),
    [PGDN_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgdn_finished, pgdn_reset)
};

//Tap dance declarations
#define GRV_ESC TD(GRV_ESC)
#define NO_INS TD(NO_INS)
#define PGUP_HOME TD(PGUP_HOME)
#define PGDN_END TD(PGDN_END)
