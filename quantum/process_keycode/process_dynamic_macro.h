/* Copyright 2016 Jack Humbert
 * Copyright 2019 Drashna Jael're (@drashna, aka Christopher Courtney)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Author: Wojciech Siewierski < wojciech dot siewierski at onet dot pl > */
#pragma once

#include "quantum.h"

/* May be overridden with a custom value. Be aware that the effective
 * macro length is half of this value: each keypress is recorded twice
 * because of the down-event and up-event. This is not a bug, it's the
 * intended behavior.
 *
 * Usually it should be fine to set the macro size to at least 256 but
 * there have been reports of it being too much in some users' cases,
 * so 128 is considered a safe default.
 */
#ifndef DYNAMIC_MACRO_SIZE
#    define DYNAMIC_MACRO_SIZE 128
#endif


//#define SET_TINY_KEY_COL(e, c) (e = ( (c << 4) | (e & 0x0f) ) )
//#define GET_TINY_KEY_COL(e) (e >> 4)
//
//#define SET_TINY_KEY_ROW(e, r) (e = ( ((r & 0x07) << 1) | (e & 0xf1) ) )
//#define GET_TINY_KEY_COL(e) ((e & 0x0f) >> 1)
//
//#define SET_TINY_KEY_PRESSED(e, p)

typedef struct {
  uint8_t row : 3;
  uint8_t col : 4;
  uint8_t pressed : 1;
} tinykeyevent_t;


//typedef struct {
//  keypos_t key;
//  bool pressed;
//} tinykeyevent_t;

void dynamic_macro_led_blink(void);
bool process_dynamic_macro(uint16_t keycode, keyrecord_t *record);
void dynamic_macro_record_start_user(void);
void dynamic_macro_play_user(int8_t direction);
//void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record);
void dynamic_macro_record_end_user(int8_t direction);
