
// define what a 'tap' is
typedef struct {
    bool is_press_action;
    int state;
} tap;

// tap dance states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,         // key is tapped twice, but NOT interrupted
    DOUBLE_HOLD = 4,        // key is tapped twice and held
    DOUBLE_SINGLE_TAP = 5,  // key is tapped twice and interrupted right after
};

// tap dance keycodes
enum {
    GUI_META,
    MINS_SLSH,
    PLUS_ASTR,
};

// function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

// functions associated with each individual tap dance
void gui_finished (qk_tap_dance_state_t *state, void *user_data);
void gui_reset (qk_tap_dance_state_t *state, void *user_data);

void mins_finished (qk_tap_dance_state_t *state, void *user_data);
void mins_reset  (qk_tap_dance_state_t *state, void *user_data);

void plus_finished (qk_tap_dance_state_t *state, void *user_data);
void plus_reset (qk_tap_dance_state_t *state, void *user_data);

// setting up tap dance for tap vs. hold
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        // if count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
        if (state->interrupted) {
        // If the interrupting key is released before the tap-dance key, then it is a single HOLD
        //     However, if the tap-dance key is released first, then it is a single TAP
        return SINGLE_TAP;
    } else {
        if (!state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
        }
    }
    // If count = 2, and it has been interrupted - assume that user is trying to type the
    //     letter associated with single tap.
    else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;   // key is tapped twice, but interrupted right after
        else if (state->pressed)
            return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;                // key is tapped twice, but NOT interrupted
    }
    else
        return 3;                      // return n+1 where n is your number of tap dance states
};

// instance 'tap' for each tap dance
//     and define your tap dance functions
static tap guitap_state = {
    .is_press_action = true,
    .state = 0
};
void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
    guitap_state.state = cur_dance(state);
    switch (guitap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_LWIN);
            break;
        case SINGLE_HOLD:
            if (layer_state_is(_META)) {
                layer_off(_META);
            } else {
                layer_on(_META);
        }
        case DOUBLE_HOLD:
            layer_on(_META);
            break;
    }
};
void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (guitap_state.state==SINGLE_HOLD) {
        layer_off(_META);
    }
    guitap_state.state = 0;
};

static tap minstap_state = {
    .is_press_action = true,
    .state = 0
};
void mins_finished (qk_tap_dance_state_t *state, void *user_data) {
    minstap_state.state = cur_dance(state);
    switch (minstap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_MINS);
            break;
        case SINGLE_HOLD:
            tap_code(KC_SLSH);
            break;
    }
};
void mins_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (minstap_state.state) {
    }
    minstap_state.state = 0;
};

static tap plustap_state = {
    .is_press_action = true,
    .state = 0
};
void plus_finished (qk_tap_dance_state_t *state, void *user_data) {
    plustap_state.state = cur_dance(state);
    switch (plustap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_PLUS);
            break;
        case SINGLE_HOLD:
            tap_code16(KC_ASTR);
            break;
    }
};
void plus_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (plustap_state.state) {
        case SINGLE_TAP:
        unregister_code16(KC_PLUS);
        break;
    }
    plustap_state.state = 0;
};

// tap dance actions
qk_tap_dance_action_t tap_dance_actions[] = {
    [GUI_META] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_finished, gui_reset),
    [MINS_SLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mins_finished, mins_reset),
    [PLUS_ASTR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plus_finished, plus_reset),
};

// tap dance definitions
#define MINS_SLSH TD(MINS_SLSH)
#define PLUS_ASTR TD(PLUS_ASTR)
#define GUI_META TD(GUI_META)
