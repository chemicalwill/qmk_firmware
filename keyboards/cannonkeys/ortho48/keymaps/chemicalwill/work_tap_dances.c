//Setting up tap dance for tap vs. hold
typedef struct {
    bool is_press_action;
    int state;
} xtap;

//Tap dance states enum
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,         //key is tapped twice, but NOT interrupted
    DOUBLE_HOLD = 4,        //key is tapped twice and held
    DOUBLE_SINGLE_TAP = 5,  //key is tapped twice and interrupted right after
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7,
    TRIPLE_SINGLE_TAP = 8,
    QUAD_TAP = 9,
    QUAD_HOLD = 10,
    QUAD_SINGLE_TAP = 11
};

//Tap dance declarations
enum {
    A_ALTA,
    D_MACROS,
    E_ALTE,
    ESC_UVOM,
    F_FENT,
    M_ALTM,
    MINS_SLSH,
    N_NOTSIG,
    O_ALTO,
    P_0LABL,
    PLUS_ASTR,
    R_REHABDC,
    S_ALTS,
    T_ALTT,
    U_ALTU,
    V_MACROS,
    WK_META,
    X_COMMS
};

//Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void a_finished (qk_tap_dance_state_t *state, void *user_data);
void a_reset (qk_tap_dance_state_t *state, void *user_data);

void c_finished (qk_tap_dance_state_t *state, void *user_data);
void c_reset (qk_tap_dance_state_t *state, void *user_data);

void d_finished (qk_tap_dance_state_t *state, void *user_data);
void d_reset (qk_tap_dance_state_t *state, void *user_data);

void e_finished (qk_tap_dance_state_t *state, void *user_data);
void e_reset (qk_tap_dance_state_t *state, void *user_data);

void esc_finished (qk_tap_dance_state_t *state, void *user_data);
void esc_reset (qk_tap_dance_state_t *state, void *user_data);

void f_finished (qk_tap_dance_state_t *state, void *user_data);
void f_reset (qk_tap_dance_state_t *state, void *user_data);

void m_finished (qk_tap_dance_state_t *state, void *user_data);
void m_reset (qk_tap_dance_state_t *state, void *user_data);

void mins_finished (qk_tap_dance_state_t *state, void *user_data);
void mins_reset  (qk_tap_dance_state_t *state, void *user_data);

void n_finished (qk_tap_dance_state_t *state, void *user_data);
void n_reset (qk_tap_dance_state_t *state, void *user_data);

void o_finished (qk_tap_dance_state_t *state, void *user_data);
void o_reset (qk_tap_dance_state_t *state, void *user_data);

void p_finished (qk_tap_dance_state_t *state, void *user_data);
void p_reset (qk_tap_dance_state_t *state, void *user_data);

void plus_finished (qk_tap_dance_state_t *state, void *user_data);
void plus_reset (qk_tap_dance_state_t *state, void *user_data);

void r_finished (qk_tap_dance_state_t *state, void *user_data);
void r_reset (qk_tap_dance_state_t *state, void *user_data);

void s_finished (qk_tap_dance_state_t *state, void *user_data);
void s_reset (qk_tap_dance_state_t *state, void *user_data);

void t_finished (qk_tap_dance_state_t *state, void *user_data);
void t_reset (qk_tap_dance_state_t *state, void *user_data);

void u_finished (qk_tap_dance_state_t *state, void *user_data);
void u_reset (qk_tap_dance_state_t *state, void *user_data);

void v_finished (qk_tap_dance_state_t *state, void *user_data);
void v_reset (qk_tap_dance_state_t *state, void *user_data);

void wk_finished (qk_tap_dance_state_t *state, void *user_data);
void wk_reset (qk_tap_dance_state_t *state, void *user_data);

void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

//Determine tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
        if (state->interrupted) {
        //     if (!state->pressed) return SINGLE_TAP;
        //need "permissive hold" here.
        //     else return SINGLE_HOLD;
        //If the interrupting key is released before the tap-dance key, then it is a single HOLD
        //      However, if the tap-dance key is released first, then it is a single TAP
        //      But how to get access to the state of the interrupting key????
        return SINGLE_TAP;
    } else {
        if (!state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
        }
    }
    //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
    //  with single tap.
    else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;   //key is tapped twice, but interrupted right after
        else if (state->pressed)
            return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;          //key is tapped twice, but is NOT interrupted
    }
    //Again for count = 3
    else if (state->count == 3) {   //really included for 'p' for choosing order protocols
        if (state->interrupted)
            return TRIPLE_SINGLE_TAP;
        else if (state->pressed)
            return TRIPLE_HOLD;
    else
        return TRIPLE_TAP;
    }
  //And again for count = 4
    else if (state->count == 4) {
        if (state->interrupted)
            return QUAD_SINGLE_TAP;
        else if (state->pressed)
            return QUAD_HOLD;
    else
        return QUAD_HOLD;
    }
    else
        return 12; //return n+1 where n is your number of tap dance states
};

//Instance 'xtap' for the A/Alt+A tap dance
static xtap atap_state = {
    .is_press_action = true,
    .state = 0
};
void a_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case SINGLE_TAP:
            register_code(KC_A);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_A));
            break;
        case DOUBLE_TAP:
            tap_code(KC_A);
            tap_code(KC_A);
            break;
        case DOUBLE_HOLD:
            tap_code(KC_A);
            tap_code16(A(KC_A));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_A);
            register_code(KC_A);
            break;
    }
}
void a_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (atap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_A);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_A);
            break;
    }
    atap_state.state = 0;
}

//Instance 'xtap' for the C/CUTCOMM tap dance
static xtap ctap_state = {
    .is_press_action = true,
    .state = 0
};
void c_finished (qk_tap_dance_state_t *state, void *user_data) {
    ctap_state.state = cur_dance(state);
    switch (ctap_state.state) {
        case SINGLE_TAP:
            register_code(KC_C);
            break;
    case SINGLE_HOLD:
        //COMMENT macro
        tap_code(KC_TAB);
        tap_code(KC_TAB);
        tap_code16(C(KC_A));
        tap_code16(C(KC_X));
        tap_code16(S(KC_TAB));
        tap_code16(S(KC_TAB));
        tap_code16(C(KC_V));
        break;
    case DOUBLE_TAP:
        tap_code(KC_C);
        register_code(KC_C);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_C);
        register_code(KC_C);
        break;
    }
}
void c_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ctap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_C);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_C);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_C);
            break;
    }
    ctap_state.state = 0;
}

//Instance 'xtap' for the D tap dance
static xtap dtap_state = {
    .is_press_action = true,
    .state = 0
};
void d_finished (qk_tap_dance_state_t *state, void *user_data) {
    dtap_state.state = cur_dance(state);
    switch (dtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_D);
            break;
        case SINGLE_HOLD:
            //DEFER macro
            tap_code16(S(KC_TAB));
            tap_code(KC_D);
            tap_code(KC_TAB);
            break;
        case DOUBLE_TAP:
            tap_code(KC_D);
            register_code(KC_D);
            break;
        case DOUBLE_HOLD:
            //DUPE macro
            tap_code(KC_TAB); //tab to Discontinue Reason
            tap_code(KC_TAB); //select "Duplicate"
            tap_code(KC_D);
            tap_code(KC_TAB); //tab to Label Copies
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code(KC_0);
            tap_code16(A(KC_O));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_D);
            register_code(KC_D);
            break;
    }
}
void d_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (dtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_D);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_D);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_D);
            break;
    }
    dtap_state.state = 0;
}

//Instance 'xtap' for the E/Alt+E tap dance
static xtap etap_state = {
    .is_press_action = true,
    .state = 0
};
void e_finished (qk_tap_dance_state_t *state, void *user_data) {
    etap_state.state = cur_dance(state);
    switch (etap_state.state) {
        case SINGLE_TAP:
            register_code(KC_E);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_E));
            break;
        case DOUBLE_TAP:
            tap_code(KC_E);
            register_code(KC_E);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_E);
            register_code(KC_E);
            break;
    }
}
void e_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (etap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_E);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_E);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_E);
            break;
    }
    etap_state.state = 0;
}

//Instance 'xtap' for the ESC/UVOM tap dance
static xtap esctap_state = {
    .is_press_action = true,
    .state = 0
};
void esc_finished (qk_tap_dance_state_t *state, void *user_data) {
    esctap_state.state = cur_dance(state);
    switch (esctap_state.state) {
        case SINGLE_TAP:
            register_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            //UVOM macro
            tap_code16(C(KC_P));
            wait_ms(250);
            tap_code16(A(KC_M));
            wait_ms(250);
            tap_code(KC_F5);
            break;
    }
}
void esc_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (esctap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
    }
    esctap_state.state = 0;
}

//Instance 'xtap' for the F/FENTPACU tap dance
static xtap ftap_state = {
    .is_press_action = true,
    .state = 0
};
void f_finished (qk_tap_dance_state_t *state, void *user_data) {
    ftap_state.state = cur_dance(state);
    switch (ftap_state.state) {
        case SINGLE_TAP:
            register_code(KC_F);
            break;
        case SINGLE_HOLD:
            //FENTPACU macro
            tap_code(KC_DOWN);
            tap_code(KC_ENTER);
            tap_code(KC_TAB);
            SEND_STRING("prn pacu use only");
            break;
        case DOUBLE_TAP:
            tap_code(KC_F);
            register_code(KC_F);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_F);
            register_code(KC_F);
            break;
    }
}
void f_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ftap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_F);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_F);
            break;
    }
    ftap_state.state = 0;
}

//Instance 'xtap' for the M/Alt+M tap dance
static xtap mtap_state = {
    .is_press_action = true,
    .state = 0
};
void m_finished (qk_tap_dance_state_t *state, void *user_data) {
    mtap_state.state = cur_dance(state);
    switch (mtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_M);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_M));
            break;
        case DOUBLE_TAP:
            tap_code(KC_M);
            register_code(KC_M);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_M);
            register_code(KC_M);
            break;
    }
}
void m_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (mtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_M);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_M);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_M);
            break;
    }
    mtap_state.state = 0;
}

//Instance 'xtap' for the MINS/SLSH tap dance
static xtap minstap_state = {
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
}
void mins_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (minstap_state.state) {
    }
    minstap_state.state = 0;
}

//Instance 'xtap' for the N/NOTSIG tap dance
static xtap ntap_state = {
    .is_press_action = true,
    .state = 0
};
void n_finished (qk_tap_dance_state_t *state, void *user_data) {
    ntap_state.state = cur_dance(state);
    switch (ntap_state.state) {
        case SINGLE_TAP:
            register_code(KC_N);
            break;
        case SINGLE_HOLD:
            //NOTSIG macro
            tap_code16(S(KC_TAB));
            SEND_STRING("nnn\t");
            break;
        case DOUBLE_TAP:
            tap_code(KC_N);
            register_code(KC_N);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_N);
            register_code(KC_N);
            break;
    }
}
void n_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ntap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_N);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_N);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_N);
            break;
    }
    ntap_state.state = 0;
}

//Instance 'xtap' for the O/Alt+O tap dance
static xtap otap_state = {
    .is_press_action = true,
    .state = 0
};
void o_finished (qk_tap_dance_state_t *state, void *user_data) {
    otap_state.state = cur_dance(state);
    switch (otap_state.state) {
        case SINGLE_TAP:
            register_code(KC_O);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_O));
            break;
        case DOUBLE_TAP:
            tap_code(KC_O);
            register_code(KC_O);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_O);
            register_code(KC_O);
            break;
    }
}
void o_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (otap_state.state) {
        case SINGLE_TAP:
        unregister_code(KC_O);
        break;
        case DOUBLE_TAP:
            unregister_code(KC_O);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_O);
            break;
    }
    otap_state.state = 0;
}

//Instance 'xtap' for the P/0LABEL tap dance
static xtap ptap_state = {
    .is_press_action = true,
    .state = 0
};
void p_finished (qk_tap_dance_state_t *state, void *user_data) {
    ptap_state.state = cur_dance(state);
    switch (ptap_state.state) {
        case SINGLE_TAP:
            register_code(KC_P);
            break;
        case SINGLE_HOLD:
            //0LABEL macro
            tap_code16(A(KC_P));
            tap_code(KC_SPC);
            tap_code16(A(KC_O));
            break;
        case DOUBLE_TAP:
            tap_code(KC_P);
            register_code(KC_P);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_P);
            register_code(KC_P);
            break;
        case TRIPLE_TAP:        //keep triple, quad dances for rapidly choosing dropdowns
            tap_code(KC_P);
            tap_code(KC_P);
            register_code(KC_P);
            break;
        case TRIPLE_SINGLE_TAP:
            tap_code(KC_P);
            tap_code(KC_P);
            register_code(KC_P);
            break;
        case QUAD_TAP:
            tap_code(KC_P);
            tap_code(KC_P);
            tap_code(KC_P);
            register_code(KC_P);
            break;
        case QUAD_SINGLE_TAP:
            tap_code(KC_P);
            tap_code(KC_P);
            tap_code(KC_P);
            register_code(KC_P);
            break;
    }
}
void p_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ptap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_P);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_P);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_P);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_P);
            break;
        case TRIPLE_SINGLE_TAP:
            unregister_code(KC_P);
            break;
        case QUAD_TAP:
            unregister_code(KC_P);
            break;
        case QUAD_SINGLE_TAP:
            unregister_code(KC_P);
            break;
    }
    ptap_state.state = 0;
}

//Instance 'xtap' for the PLUS/ASTR tap dance
static xtap plustap_state = {
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
}
void plus_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (plustap_state.state) {
        case SINGLE_TAP:
        unregister_code16(KC_PLUS);
        break;
    }
    plustap_state.state = 0;
}

//Instance 'xtap' for the R/REHABDC tap dance
static xtap rtap_state = {
    .is_press_action = true,
    .state = 0
};
void r_finished (qk_tap_dance_state_t *state, void *user_data) {
    rtap_state.state = cur_dance(state);
    switch (rtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_R);
            break;
        case SINGLE_HOLD:
            //REHABDC macro
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
            break;
        case DOUBLE_TAP:
            tap_code(KC_R);
            register_code(KC_R);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_R);
            register_code(KC_R);
            break;
    }
}
void r_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (rtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_R);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_R);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_R);
            break;
    }
    rtap_state.state = 0;
}

//Instance 'xtap' for the S/Alt+S tap dance
static xtap stap_state = {
    .is_press_action = true,
    .state = 0
};
void s_finished (qk_tap_dance_state_t *state, void *user_data) {
    stap_state.state = cur_dance(state);
    switch (stap_state.state) {
        case SINGLE_TAP:
            register_code(KC_S);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_S));
            break;
        case DOUBLE_TAP:
            tap_code(KC_S);
            register_code(KC_S);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_S);
            register_code(KC_S);
            break;
    }
}
void s_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (stap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_S);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_S);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_S);
            break;
    }
    stap_state.state = 0;
}

//Instance 'xtap' for the T/Alt+T tap dance
static xtap ttap_state = {
    .is_press_action = true,
    .state = 0
};
void t_finished (qk_tap_dance_state_t *state, void *user_data) {
    ttap_state.state = cur_dance(state);
    switch (ttap_state.state) {
        case SINGLE_TAP:
            register_code(KC_T);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_T));
            break;
        case DOUBLE_TAP:
            tap_code(KC_T);
            register_code(KC_T);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_T);
            register_code(KC_T);
            break;
    }
}
void t_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ttap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_T);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_T);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_T);
            break;
    }
    ttap_state.state = 0;
}

//Instance 'xtap' for the U/Alt+U tap dance
static xtap utap_state = {
    .is_press_action = true,
    .state = 0
};
void u_finished (qk_tap_dance_state_t *state, void *user_data) {
    utap_state.state = cur_dance(state);
    switch (utap_state.state) {
        case SINGLE_TAP:
            register_code(KC_U);
            break;
        case SINGLE_HOLD:
            tap_code16(A(KC_U));
            break;
        case DOUBLE_TAP:
            tap_code(KC_U);
            register_code(KC_U);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_U);
            register_code(KC_U);
            break;
    }
}
void u_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (utap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_U);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_U);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_U);
            break;
    }
    utap_state.state = 0;
}

//Instance 'xtap' for the V tap dance
static xtap vtap_state = {
    .is_press_action = true,
    .state = 0
};
void v_finished (qk_tap_dance_state_t *state, void *user_data) {
    vtap_state.state = cur_dance(state);
    switch (vtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_V);
            break;
        case SINGLE_HOLD:
            //PROFILE macro
            tap_code(KC_V);
            tap_code(KC_V);
            tap_code16(A(KC_A));
            break;
        case DOUBLE_TAP:
            tap_code(KC_V);
            register_code(KC_V);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_V);
            register_code(KC_V);
            break;
        case TRIPLE_TAP:    //Leave triple, quad taps in, in case I hit 'v' on several different orders I'm verifying
            tap_code(KC_V);
            tap_code(KC_V);
            register_code(KC_V);
            break;
        case TRIPLE_SINGLE_TAP:
            tap_code(KC_V);
            tap_code(KC_V);
            register_code(KC_V);
            break;
        case QUAD_TAP:
            tap_code(KC_V);
            tap_code(KC_V);
            tap_code(KC_V);
            register_code(KC_V);
            break;
        case QUAD_SINGLE_TAP:
            tap_code(KC_V);
            tap_code(KC_V);
            tap_code(KC_V);
            register_code(KC_V);
            break;
    }
}
void v_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (vtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_V);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_V);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_V);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_V);
            break;
        case TRIPLE_SINGLE_TAP:
            unregister_code(KC_V);
            break;
        case QUAD_TAP:
            unregister_code(KC_V);
            break;
        case QUAD_SINGLE_TAP:
            unregister_code(KC_V);
            break;
    }
    vtap_state.state = 0;
}

//Instance 'xtap' for the WK_META tap dance
static xtap wktap_state = {
    .is_press_action = true,
    .state = 0
};
void wk_finished (qk_tap_dance_state_t *state, void *user_data) {
    wktap_state.state = cur_dance(state);
    switch (wktap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_LWIN);
            break;
        case SINGLE_HOLD:
            if (layer_state_is(_META)) {
                layer_off(_META);
            } else {
                layer_on(_META);
        case DOUBLE_HOLD:
            layer_on(_META);
            break;
        }
        break;
    }
}
void wk_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (wktap_state.state==SINGLE_HOLD) {
        layer_off(_META);
    }
    wktap_state.state = 0;
}

//Instance 'xtap' for the X/CUTCOMM tap dance
static xtap xtap_state = {
    .is_press_action = true,
    .state = 0
};
void x_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_X);
            break;
        case SINGLE_HOLD:
            //CUTCOMM macro
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            tap_code16(C(KC_A));
            tap_code16(C(KC_X));
            tap_code16(S(KC_TAB));
            tap_code16(S(KC_TAB));
            tap_code16(C(KC_V));
            break;
        case DOUBLE_TAP:
            tap_code(KC_X);
            register_code(KC_X);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_X);
            register_code(KC_X);
            break;
    }
}
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_X);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_X);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_X);
            break;
    }
    xtap_state.state = 0;
}


//Tap dance defintions
qk_tap_dance_action_t tap_dance_actions[] = {
    [A_ALTA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_finished, a_reset),
    [D_MACROS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_finished, d_reset),
    [E_ALTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_finished, e_reset),
    [ESC_UVOM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished, esc_reset),
    [F_FENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset),
    [M_ALTM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, m_finished, m_reset),
    [MINS_SLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mins_finished, mins_reset),
    [N_NOTSIG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_finished, n_reset),
    [O_ALTO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o_finished, o_reset),
    [P_0LABL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, p_finished, p_reset),
    [PLUS_ASTR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plus_finished, plus_reset),
    [R_REHABDC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_finished, r_reset),
    [S_ALTS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),
    [T_ALTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, t_finished, t_reset),
    [U_ALTU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u_finished, u_reset),
    [V_MACROS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_finished, v_reset),
    [WK_META] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wk_finished, wk_reset),
    [X_COMMS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
};

//Define tap dances as keycodes to fit in the keymap better
#define A_ALTA TD(A_ALTA)
#define D_MACROS TD(D_MACROS)
#define E_ALTE TD(E_ALTE)
#define F_FENT TD(F_FENT)
#define ESC_UVOM TD(ESC_UVOM)
#define M_ALTM TD(M_ALTM)
#define MINS_SLSH TD(MINS_SLSH)
#define N_NOTSIG TD(N_NOTSIG)
#define O_ALTO TD(O_ALTO)
#define P_0LABL TD(P_0LABL)
#define PLUS_ASTR TD(PLUS_ASTR)
#define R_REHABDC TD(R_REHABDC)
#define S_ALTS TD(S_ALTS)
#define T_ALTT TD(T_ALTT)
#define U_ALTU TD(U_ALTU)
#define V_MACROS TD(V_MACROS)
#define WK_META TD(WK_META)
#define X_COMMS TD(X_COMMS)
