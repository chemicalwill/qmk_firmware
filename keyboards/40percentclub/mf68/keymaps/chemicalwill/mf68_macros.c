//Custom macro keycodes
enum custom_keycodes {
  BASE_QWER = SAFE_RANGE,
  BASE_GAME
};


//Macros
/* here's a cool-ass example:
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SWAGGER:
      if (record->event.pressed) {
        // when keycode SWAGGER is pressed
        SEND_STRING("I got the most swag on this corner of the street :sunglasses:!");
      } else {
        // when keycode SWAGGER is released
      }
      break;
  }
  return true;
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE_QWER:
      if (record->event.pressed) {
        // when keycode BASE_QWER is pressed
        set_single_persistent_default_layer(_QWER);
      } else {
        // when keycode BASE_QWER is released
      }
      break;

    case BASE_GAME:
      if (record->event.pressed) {
        // when keycode BASE_GAME is pressed
        set_single_persistent_default_layer(_GAME);
      } else {
        // when keycode BASE_GAME is released
      }
      break;
      
  }
  return true;
};

