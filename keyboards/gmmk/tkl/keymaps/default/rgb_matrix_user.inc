// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(static_white)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern bool repeat_use_register;
extern keyrecord_t repeat_last_record;
extern uint8_t user_red_key_index;

// e.g: A simple effect, self-contained within a single method
static bool static_white(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint8_t r = g_led_config.matrix_co[repeat_last_record.event.key.row][repeat_last_record.event.key.col];
  for (uint8_t i = led_min; i < led_max; i++) {
    if ( i == user_red_key_index && (g_rgb_timer & (0x1 << 9) ) ) { //Recording, blink @
      rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    } else if (i == r && repeat_use_register){ //Register value
      rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    }else if (i == r) { //Fade the last pressed key
      rgb_matrix_set_color(i, 0x77, 0x77, 0x77);
    }else{ //Set to white
      rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }

  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
