// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(static_white)
RGB_MATRIX_EFFECT(the_matrix)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define _BL 0
#define _FN 1
#define _VIM 2

extern bool repeat_use_register;
extern keyrecord_t repeat_last_record;
extern uint8_t user_red_key_index;
extern uint8_t g_vim_count;

// e.g: A simple effect, self-contained within a single method
static bool static_white(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  //VIM mode
  if (IS_LAYER_ON(_VIM)){
    for (uint8_t i = led_min; i < led_max; i++) {
      if (g_vim_count > 1 && i == g_led_config.matrix_co[1][g_vim_count]){ //VIM count highligh number in red
        rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
      }else{
        rgb_matrix_set_color(i, 0x00, 0xaa, 0x00);
      }
    }
    return led_max < DRIVER_LED_TOTAL;
  }

  uint8_t r = g_led_config.matrix_co[repeat_last_record.event.key.row][repeat_last_record.event.key.col];
  for (uint8_t i = led_min; i < led_max; i++) {
    if ( i == user_red_key_index && (g_rgb_timer & (0x1 << 9) ) ) { //Recording, blink @
      rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    } else if (i == r && repeat_use_register){ //Register value
      rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    } else if (g_vim_count > 1 && i == g_led_config.matrix_co[1][g_vim_count]){ //VIM count highligh number in green
      rgb_matrix_set_color(i, 0x00, 0xff, 0x00);
    }else{ //Set to white
      if (IS_LAYER_ON(_FN)){
        rgb_matrix_set_color(i, 0x33, 0x33, 0xff);
      }else{
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
      }
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

static bool the_matrix(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
#define THE_MATRIX_COL 0
#define THE_MATRIX_START 1
#define THE_MATRIX_END 2
  static uint8_t green_rows[3][3] = { 
    [0] = { 4, 8, 9 },
    [1] = { 0, -3, -5 },
    [2] = { 0, -3, -5 }
  };
  
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  //FillGreen
  for(uint8_t i = 0; i < 3; i++){
    uint8_t col = green_rows[i][THE_MATRIX_COL];
    for(uint8_t j = green_rows[i][THE_MATRIX_START]; j < green_rows[i][THE_MATRIX_END]; j++){
      if(j>=0){
        uint8_t led_i = g_led_config.matrix_co[j][col];
        rgb_matrix_set_color(led_i, 0x00, 0x33, 0x00);
      }
    }
    if ( (g_rgb_timer & (0x1 << 4) ) ) { 
      green_rows[i][THE_MATRIX_END]++;
      if(green_rows[i][THE_MATRIX_END] > MATRIX_ROWS){
        green_rows[i][THE_MATRIX_COL] = rand() % MATRIX_COLS; 
        green_rows[i][THE_MATRIX_START] = 0;
        green_rows[i][THE_MATRIX_END] = 0;
      }
    }
  }

  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
