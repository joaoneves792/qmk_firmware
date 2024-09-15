#include QMK_KEYBOARD_H

#define _BL 0
#define _FN 1

enum custom_keycodes {
    QMKDOOM = SAFE_RANGE,
    KC_REP,
    KC_RREP,
};
static uint8_t  last_mods;
static uint16_t last_keycode = KC_TRNS;
keyrecord_t repeat_last_record;
bool repeat_use_register = false;
uint8_t user_red_key_index = NO_LED;


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed && keycode != MO(_FN) && keycode != KC_REP && keycode != KC_RREP && keycode != KC_TRNS && !repeat_use_register){
      last_mods         = (get_mods() | get_weak_mods());
      last_keycode      = keycode;
      repeat_last_record.event = record->event;
      repeat_last_record.tap   = record->tap;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case QMKDOOM:
          if (record->event.pressed) {
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
          return false;
      case KC_REP:
          if (record->event.pressed && last_keycode != KC_TRNS) {
              repeat_last_record.event.pressed = true;
              register_mods(last_mods);
              process_record(&repeat_last_record); 
          }else if (!record->event.pressed && last_keycode != KC_TRNS) {
              repeat_last_record.event.pressed = false;
              process_record(&repeat_last_record);
              unregister_mods(last_mods);
          }
          return false;
      case KC_RREP:
          if (record->event.pressed){
            repeat_use_register = !repeat_use_register;
          }
          return false;
    }
    return true;
};


void dynamic_macro_record_start_user() { user_red_key_index = g_led_config.matrix_co[1][2]; }

void dynamic_macro_play_user(int8_t direction) { }

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
                        KC_TRNS,    KC_TRNS,    DM_PLY1,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    DM_REC1,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    RGB_SPD,    RGB_MODE_FORWARD,   KC_TRNS,
                        KC_TRNS,    KC_TRNS,    RGB_TOG,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_RREP,    KC_TRNS,    RGB_HUD,    RGB_VAD,        RGB_VAI,        RGB_HUI,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,
                        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_MOD,    RGB_RMOD,       KC_TRNS,        KC_TRNS),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}
