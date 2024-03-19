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

#include QMK_KEYBOARD_H
#include <keymap_french.h>

enum unicode_names {
    POOP,
    ROLF,
    SNEK
};  

const uint32_t PROGMEM unicode_map[] = {
[POOP]  = 0x1F4A9,  // 💩
[ROLF] = 0x1F923,  // 🤣
    [SNEK]  = 0x1F40D, // 🐍
};

// Tap Dance declarations
enum {
    TD_SPC_DOT,
  TD_C_CCDEIL,
  
  };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
KC_TAB,    FR_A,    FR_Z,    FR_E,    FR_R,    FR_T,                         FR_Y,    FR_U,    FR_I,    FR_O,   FR_P,  KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    FR_Q,    FR_S,    FR_D,    FR_F,    FR_G,                         FR_H,    FR_J,    FR_K,    FR_L, FR_M, KC_DEL,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT,    FR_W,    FR_X, FR_C,    FR_V,    FR_B,                         FR_N,    FR_COMM, FR_SCLN,  FR_COLN, FR_EXLM,  KC_ESC,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_LALT
//`--------------------------'  `--------------------------'

),

[1] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
KC_TAB,    FR_AMPR,    FR_EACU,    FR_DQUO,    FR_QUOT,    FR_LPRN,                         FR_MINS,    FR_EGRV,    FR_UNDS,    FR_CCED,    FR_AGRV, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, UM(1), XXXXXXX, XXXXXXX, KC_INS, KC_HOME,                      KC_END, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_DEL,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT, UC_NEXT, KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX,                      KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_MS_WH_UP,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
//`--------------------------'  `--------------------------'
),

[2] = LAYOUT_split_3x6_3(

//*, +, =, -, (,     ), >, <, &, X
// X, _, #, $, {,     }, \, |, /, X
// X, `, ", ', [,     ], ,, ;, :, !
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_BSLS,   FR_PLUS, FR_EQL,  FR_MINS,    FR_LPRN,                      FR_RPRN, FR_RABK, FR_LABK, FR_AMPR, XXXXXXX, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, FR_UNDS, FR_HASH, FR_DLR, FR_LCBR,                      FR_RCBR,  FR_BSLS, FR_PIPE, FR_SLSH, FR_CIRC,  KC_DEL,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT, XXXXXXX, FR_GRV, FR_DQUO, FR_QUOT, FR_LBRC,                      FR_RBRC, FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, KC_TILD,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
//`--------------------------'  `--------------------------'
),

[3] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                      KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      KC_KB_VOLUME_DOWN, KC_KB_MUTE, KC_KB_VOLUME_UP, XXXXXXX, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
//`--------------------------'  `--------------------------'
)
};
