/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*  REF LAYOUT_split_3x6_3_ex2
    ,--------------------------------------------------------------.  ,--------------------------------------------------------------.
     [0, 0]18,[0, 1]17,[0, 2]12,[0, 3]11, [0, 4]4, [0, 5]3,[0, 6]21,   [4, 6]44,[4, 5]26,[4, 4]27,[4, 3]34,[4, 2]35,[4, 1]40,[4, 0]41,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     [1, 0]19,[1, 1]16,[1, 2]13,[1, 3]10, [1, 4]5, [1, 5]2,[1, 6]22,   [5, 6]45,[5, 5]25,[5, 4]28,[5, 3]33,[5, 2]36,[5, 1]39,[5, 0]42,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     [2, 0]20,[2, 1]15,[2, 2]14, [2, 3]9, [2, 4]6, [2, 5]1,                     [6, 5]24,[6, 4]29,[6, 3]32,[6, 2]37,[6, 1]38,[6, 0]43,
    |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                 [3, 3]8, [3, 4]7, [3, 5]0,                     [7, 5]23,[7, 4]30,[7, 3]31
                             //`--------------------------'                    `--------------------------'

*/

#include QMK_KEYBOARD_H
#include <stdarg.h>
#include "rgb_matrix.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [qwt] = LAYOUT_split_3x6_3_ex2(
    ,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_T,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_T,       KC_T,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
    |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI,   MO(1),  KC_SPC,                       KC_ENT,   MO(2), KC_RALT
                             //`--------------------------'                    `--------------------------'

  ),

    [cmk] = LAYOUT_split_3x6_3_ex2(
    ,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_T,       KC_T,    KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, KC_BSPC,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_T,       KC_T,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_SCLN,
    |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
    |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI,   MO(1),  KC_SPC,                       KC_ENT,   MO(2), KC_RALT
                             //`--------------------------'                    `--------------------------'
  ),



};

//This function takes the row and column of one key and lights it.
void light_one(uint8_t row, uint8_t column, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t led_index = g_led_config.matrix_co[row][column];

    if (led_index != NO_LED) {
        rgb_matrix_set_color(led_index, r, g, b);
    }
}
//This function lights takes multiple key matrices and lights them.

typedef struct {
    uint8_t row;
    uint8_t col;
} matrix_pos_t;
/*
void light_many(matrix_pos_t positions[], uint8_t count, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < count; i++) {
        uint8_t led = g_led_config.matrix_co[positions[i].row][positions[i].col];
        if (led != NO_LED) {
            rgb_matrix_set_color(led, r, g, b);
        }
    }
}
*/
//example
/*void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    matrix_pos_t
        {1, 2}, 
        {2, 3}, 
        {2, 4}  
    };
    
    // Light all specified keys in red
    light_many(keys, sizeof(keys)/sizeof(keys[0]), 255, 0, 0);  va_end(args);
}
*/
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    RGB pressed_color = {255, 0, 0};  // Red for pressed state
    
    // Loop through all tracked keypresses
    for (uint8_t i = 0; i < g_last_hit_tracker.count; i++) {
        // Get the LED index for this keypress
        uint8_t led_index = g_last_hit_tracker.index[i];
        
        // Only process if the LED =/between first and last LED
        if (led_index >= led_min && led_index <= led_max) {
            rgb_matrix_set_color(led_index, 
                pressed_color.r, pressed_color.g, pressed_color.b);
        }
    }
    
    return false;  // Don't need parent processing
}