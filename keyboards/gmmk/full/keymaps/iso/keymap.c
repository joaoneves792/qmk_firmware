#include QMK_KEYBOARD_H

#define _BL 0
#define _FN 1
#define _VIM 2

enum custom_keycodes {
    QMKDOOM = SAFE_RANGE,
    KC_REP,
    KC_RREP,
    KC_VIMC0,
    KC_VIMC1,
    KC_VIMC2,
    KC_VIMC3,
    KC_VIMC4,
    KC_VIMC5,
    KC_VIMC6,
    KC_VIMC7,
    KC_VIMC8,
    KC_VIMC9,
};

static uint8_t  last_mods;
static uint16_t last_keycode = KC_TRNS;
static uint8_t  last_layer = 0;
keyrecord_t repeat_last_record;
bool repeat_use_register = false;
uint8_t user_red_key_index = NO_LED;
uint8_t g_vim_count = 0;
static bool ignore = false;


#define QK_IS_BASIC(kc) (kc > QK_BASIC && kc <= QK_BASIC_MAX)

bool post_process_intercept_user(uint16_t keycode, keyrecord_t *record) {
    if(ignore){ return true; }

    if(!record->event.pressed && (QK_IS_BASIC(keycode) || keycode == KC_REP || keycode == DM_PLY1)){
      if ( g_vim_count > 1 ){ 


        layer_state_t saved_layer_state = layer_state;
        uint8_t saved_mods = (get_mods() | get_weak_mods());
        ignore = true;
        for(;g_vim_count > 1; g_vim_count--){
            clear_keyboard();
            layer_clear();

            register_mods(saved_mods);
            record->event.pressed = true;
            action_t a;
            if (keycode == DM_PLY1){ 
              a.code = ACTION_LAYER_ON_OFF(_FN);
              process_action(record, a);
            }
            process_record(record); 
            wait_ms(50);
            record->event.pressed = false;
            process_record(record);
            wait_ms(50);

            clear_keyboard();
            layer_state = saved_layer_state;
        }


        ignore = false;
        return true;
      }
    }

    if(record->event.pressed && !repeat_use_register){
      if(keycode != KC_REP  && \
           keycode != KC_RREP && \
           keycode != MO(_FN)){
        last_layer        = get_highest_layer(layer_state);
        last_mods         = (get_mods() | get_weak_mods());
        last_keycode      = keycode;
        repeat_last_record.event = record->event;
        repeat_last_record.tap   = record->tap;
      }
    }
    return true;
}

void process_doom(void){
    //SEND_STRING_DELAY("The code you write makes you a programmer. The code you delete makes you a good one. The code you don't have to write makes you a great one.", 50);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" Wake up, Neo...", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" The Matrix has you...", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" Follow the white rabbit.", 50);
    SEND_STRING_DELAY(" \b \b \b", 200);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY(" 671tch iN Th3 M4trix.", 0);
    SEND_STRING_DELAY("  ", 244);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY("       671tch iN Th3 M4trix.", 0);
    SEND_STRING_DELAY("  ", 244);
    SEND_STRING_DELAY("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 0);
    SEND_STRING_DELAY("    671tch iN Th3 M4trix.", 0);
}


void process_repeat_key(bool pressed){
    static layer_state_t current_layer_state;
    if (pressed && last_keycode != KC_TRNS) {
        current_layer_state = get_highest_layer(layer_state);
        repeat_last_record.event.pressed = true;
        register_mods(last_mods);
        action_t a;
        a.code = ACTION_LAYER_ON_OFF(last_layer);
        process_action(&repeat_last_record, a);
        process_record(&repeat_last_record); 
    }else if (!pressed && last_keycode != KC_TRNS) {
        repeat_last_record.event.pressed = false;
        process_record(&repeat_last_record);
        unregister_mods(last_mods);
        layer_state = current_layer_state;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case QMKDOOM:
          if (record->event.pressed) {
            process_doom();
          }
          return false;
      case KC_REP:
          process_repeat_key(record->event.pressed);
          return false;
      case KC_RREP:
          if (record->event.pressed){
            repeat_use_register = !repeat_use_register;
          }
          return false;
      case KC_VIMC0:
      case KC_VIMC1:
      case KC_VIMC2:
      case KC_VIMC3:
      case KC_VIMC4:
      case KC_VIMC5:
      case KC_VIMC6:
      case KC_VIMC7:
      case KC_VIMC8:
      case KC_VIMC9:
        g_vim_count = keycode - KC_VIMC0;
        layer_off(_VIM);
        return false;
    }
    return true;
};


void dynamic_macro_record_start_user() { user_red_key_index = g_led_config.matrix_co[1][2]; }

void dynamic_macro_play_user(int8_t direction) { ignore = true; }

void dynamic_macro_play_user_end(int8_t direction) { ignore = false; }

void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {  }

void dynamic_macro_record_end_user(int8_t direction) { user_red_key_index = NO_LED; } 


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* The GMMK uses a 7x16 matrix. Some keys are not wired in the matrix at their physical location */

    [_BL] = KEYMAP(     QMKDOOM,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,          KC_F10,         KC_F11,     KC_F12, 
                        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,           KC_0,           KC_MINS,    KC_EQL,    KC_NUMLOCK, KC_KP_SLASH,         KC_KP_ASTERISK,
                        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,           KC_P,           KC_LBRC,    KC_RBRC,   KC_KP_7,    KC_KP_8,             KC_KP_9, 
                        KC_ESC,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,           KC_SCLN,        KC_QUOT,    KC_BSLS,   KC_KP_4,    KC_KP_5,             KC_KP_6, 
                        KC_LSPO,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,         KC_SLSH,        KC_RSPC,    KC_ENT,    KC_KP_1,    KC_KP_2,             KC_KP_3, 
                        KC_LCPO,    KC_LGUI,    KC_LALT,    KC_SPC,     KC_RALT,    MO(_FN),    KC_REP,     KC_RCPC,    KC_LEFT,    KC_DOWN,        KC_UP,          KC_RGHT,    KC_BSPC,   KC_KP_0,    KC_KP_DOT,           KC_KP_ENTER,
                        KC_NUBS,    KC_PSCR,    KC_SLCK,    KC_PAUS,    KC_INS,     KC_HOME,    KC_PGUP,    KC_DEL,     KC_END,     KC_PGDN,        KC_KP_MINUS,    KC_KP_PLUS), 

    [_FN] = KEYMAP(     RESET,      KC_MYCM,    KC_MAIL,    KC_LANG1,   KC_LANG2,   KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_MSTP,    KC_MUTE,        KC_VOLD,        KC_VOLU,    KC_TRNS,
                        KC_TRNS,    KC_1,       DM_PLY1,    KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,           KC_0,           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    DM_REC1,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    RGB_SPD,    RGB_MODE_FORWARD,   KC_TRNS,
                        KC_TRNS,    KC_TRNS,    RGB_TOG,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    TG(_VIM),   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_RREP,    KC_TRNS,    RGB_HUD,    RGB_VAD,        RGB_VAI,        RGB_HUI,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_MOD,    RGB_RMOD,       KC_TRNS,        KC_TRNS),

    [_VIM] = KEYMAP(    RESET,      KC_MYCM,    KC_MAIL,    KC_LANG1,   KC_LANG2,   KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_MSTP,    KC_MUTE,        KC_VOLD,        KC_VOLU,    KC_TRNS,
                        KC_TRNS,    KC_VIMC1,   KC_VIMC2,   KC_VIMC3,   KC_VIMC4,   KC_VIMC5,   KC_VIMC6,   KC_VIMC7,   KC_VIMC8,   KC_VIMC9,       KC_VIMC0,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    DM_REC1,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    C(KC_C),    KC_TRNS,    KC_TRNS,    KC_TRNS,        C(KC_V),        KC_TRNS,    KC_TRNS,    RGB_SPD,    RGB_MODE_FORWARD,   KC_TRNS,
                        TG(_VIM),   KC_TRNS,    RGB_TOG,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,       KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_REP,     KC_TRNS,    RGB_HUD,    RGB_VAD,        RGB_VAI,        RGB_HUI,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_MOD,    RGB_RMOD,       KC_TRNS,        KC_TRNS),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}
