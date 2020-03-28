#include "bear_face.h"

void keyboard_pre_init_kb(void) {
    //Calls the keyboard pre init code
    //Sets LED pin as output
setPinOutput(F7);
}

bool led_update_kb(led_t led_state) {
    // Caps Lock LED indicator toggling code here
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F7, led_state.caps_lock);
    }
    return res;
}
