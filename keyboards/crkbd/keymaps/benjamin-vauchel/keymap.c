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
#include <keymap_french_mac_iso.h>
#include <sendstring_french_mac_iso.h>

// custom macros
enum custom_keycodes { PHP_OBJ = SAFE_RANGE, PHP_MAP, PHP_THIS, PHP_DD, PHP_CONS, PHP_DBCOL, PHP_EQ_STRICT, PHP_NEQ_STRICT, CL_COMP, CL_CMIT, DC_UP, DC_DOWN, DC_EXEC };

// Tap Dance declarations
enum {
    TD_SPC_DOT,
    TD_C_CCDEIL,

};

// Overrides
const key_override_t home_key_override   = ko_make_basic(MOD_BIT(KC_RALT), KC_LEFT, KC_HOME);
const key_override_t end_key_override    = ko_make_basic(MOD_BIT(KC_RALT), KC_RIGHT, KC_END);
const key_override_t pageup_key_override = ko_make_basic(MOD_BIT(KC_RALT), KC_UP, KC_PGUP);
const key_override_t pagedn_key_override = ko_make_basic(MOD_BIT(KC_RALT), KC_DOWN, KC_PGDN);
const key_override_t mwup_key_override   = ko_make_basic(MOD_BIT(KC_RALT), KC_MS_UP, KC_MS_WH_UP);
const key_override_t mwdn_key_override   = ko_make_basic(MOD_BIT(KC_RALT), KC_MS_DOWN, KC_MS_WH_DOWN);
const key_override_t mbtn1_key_override  = ko_make_basic(MOD_BIT(KC_RALT), KC_MS_LEFT, KC_MS_BTN1);
const key_override_t mbtn2_key_override  = ko_make_basic(MOD_BIT(KC_RALT), KC_MS_RIGHT, KC_MS_BTN2);
const key_override_t euro_key_override   = ko_make_basic(MOD_MASK_ALT | MOD_MASK_SHIFT, KC_NUBS, FR_EURO);

bool trema_override_action(bool activated, void *context) {
    if (activated) {
        tap_code16(FR_DIAE);
    }
    return false;
}

const key_override_t trema_key_override = {.trigger_mods = MOD_BIT(KC_LALT), .layers = ~0, .suppressed_mods = MOD_BIT(KC_LALT), .options = ko_options_default, .negative_mod_mask = 0, .custom_action = trema_override_action, .context = NULL, .trigger = FR_CIRC, .replacement = KC_NO, .enabled = NULL};

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &home_key_override,
    &end_key_override,
    &pageup_key_override,
    &pagedn_key_override,
    &mwup_key_override,
    &mwdn_key_override,
    &mbtn1_key_override,
    &mbtn2_key_override,
    &euro_key_override,
    &trema_key_override,
    NULL // Null terminate the array of overrides!
};

// Layer indicator
void keyboard_post_init_user(void) {
    // Call the post init code.
    rgblight_enable_noeeprom();        // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(0, 0, 0); // sets the color to teal/cyan without saving

    //  debug_enable=true;
    // debug_matrix=true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (matrix_is_on(7, 4) || matrix_is_on(3, 4)) {
        return false;
    }

    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) {
                    if (layer == 1 && (keymap_key_to_keycode(layer, (keypos_t){col, row}) == FR_LPRN || keymap_key_to_keycode(layer, (keypos_t){col, row}) == FR_MINS)) {
                        rgb_matrix_set_color(index, RGB_WHITE);
                    } else if (layer == 2 && (keymap_key_to_keycode(layer, (keypos_t){col, row}) == FR_LCBR || keymap_key_to_keycode(layer, (keypos_t){col, row}) == FR_RCBR)) {
                        rgb_matrix_set_color(index, RGB_WHITE);
                    } else if (layer == 3 && (row == 2 && (col == 5 || col == 6))) {
                        rgb_matrix_set_color(index, RGB_WHITE);
                    } else {
                        rgb_matrix_set_color(index, RGB_BLACK);
                    }
                }
            }
        }
    } else {
        rgb_matrix_set_color_all(0, 0, 0);
    }
    return false;
}

// Process Record User pour les Macros PHP
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PHP_OBJ:
            if (record->event.pressed) {
                tap_code16(FR_MINS);
                tap_code16(FR_HASH); // Renvoie > sur Mac
            }
            return false;
        case PHP_MAP:
            if (record->event.pressed) {
                tap_code16(FR_EQL);
                tap_code16(FR_HASH); // Renvoie > sur Mac
            }
            return false;
        case PHP_THIS:
            if (record->event.pressed) {
                tap_code16(FR_DLR);
                tap_code16(FR_T);
                tap_code16(FR_H);
                tap_code16(FR_I);
                tap_code16(FR_S);
                tap_code16(FR_MINS);
                tap_code16(FR_HASH); // Renvoie > sur Mac
            }
            return false;
        case PHP_DD:
            if (record->event.pressed) {
                SEND_STRING("dd();");
                tap_code16(KC_LEFT); // Place le curseur entre les parenthèses
            }
            return false;
        case PHP_CONS:
            if (record->event.pressed) {
                SEND_STRING("php bin/console ");
            }
            return false;
        case PHP_DBCOL:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
        case PHP_EQ_STRICT:
            if (record->event.pressed) {
                SEND_STRING("===");
            }
            return false;
        case PHP_NEQ_STRICT:
            if (record->event.pressed) {
                SEND_STRING("!==");
            }
            return false;
        case CL_COMP:
            if (record->event.pressed) {
                SEND_STRING("/compact\n");
            }
            return false;
        case CL_CMIT:
            if (record->event.pressed) {
                SEND_STRING("/commit\n");
            }
            return false;
        case DC_UP:
            if (record->event.pressed) {
                SEND_STRING("docker compose up -d\n");
            }
            return false;
        case DC_DOWN:
            if (record->event.pressed) {
                SEND_STRING("docker compose down\n");
            }
            return false;
        case DC_EXEC:
            if (record->event.pressed) {
                SEND_STRING("docker compose exec ");
            }
            return false;
    }
    return true;
}

// Layers

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_split_3x6_3(
                                                                  // azertyuiop
                                                                  // qsdfghjklm
                                                                  // wxcvbn,;:!
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, FR_A, FR_Z, FR_E, FR_R, FR_T, FR_Y, FR_U, FR_I, FR_O, FR_P, KC_BSPC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  MT(MOD_LSFT, KC_CAPS_LOCK), FR_Q, FR_S, FR_D, FR_F, FR_G, FR_H, FR_J, FR_K, FR_L, FR_M, KC_DEL,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, FR_W, FR_X, FR_C, FR_V, FR_B, FR_N, FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, MT(MOD_LCTL, KC_ESC),
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  LCMD(LCTL(KC_SPC)), TT(1), MT(MOD_LALT, KC_SPC), MT(MOD_RALT, KC_ENT), TT(2), KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  ),

                                                              [1] = LAYOUT_split_3x6_3(
                                                                  // &é"'(-è_çà
                                                                  // 12345
                                                                  // 67890
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, FR_AMPR, FR_LEAC, FR_DQUO, FR_QUOT, FR_LPRN, FR_MINS, FR_LEGR, FR_UNDS, FR_LCCE, FR_LAGR, KC_BSPC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  MT(MOD_LSFT, KC_CAPS_LOCK), FR_1, FR_2, FR_3, FR_4, FR_5, KC_INS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DEL,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, FR_6, FR_7, FR_8, FR_9, FR_0, XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, MT(MOD_LCTL, KC_ESC),
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  LCMD(LCTL(KC_SPC)), TO(0), MT(MOD_LALT, KC_SPC), MT(MOD_RALT, KC_ENT), TT(3), KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  ),

                                                              [2] = LAYOUT_split_3x6_3(
                                                                  // *, +, =, -, (,     ), <, >, &, ^
                                                                  // @, _, #, $, {,     }, \, |, /, %
                                                                  // ù, `, ", ', [,     ], ,, ;, :, !
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, FR_ASTR, FR_PLUS, FR_EQL, FR_MINS, FR_LPRN, FR_RPRN, FR_AT, FR_HASH, FR_AMPR, FR_CIRC, KC_BSPC,
                                                                  //|--------+--------+--------+-------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  MT(MOD_LSFT, KC_CAPS_LOCK), FR_LABK, FR_UNDS, FR_RABK, FR_DLR, FR_LCBR, FR_RCBR, FR_BSLS, FR_PIPE, FR_SLSH, FR_PERC, KC_DEL,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, FR_LUGR, FR_GRV, FR_DQUO, FR_QUOT, FR_LBRC, FR_RBRC, FR_COMM, FR_SCLN, FR_COLN, FR_EXLM, KC_TILD,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  LCMD(LCTL(KC_SPC)), TT(3), MT(MOD_LALT, KC_SPC), MT(MOD_RALT, KC_ENT), TO(0), KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  ),

                                                              [3] = LAYOUT_split_3x6_3(
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  PHP_DD, PHP_CONS, PHP_MAP, PHP_OBJ, PHP_THIS, PHP_DBCOL, KC_KB_VOLUME_DOWN, KC_KB_MUTE, KC_KB_VOLUME_UP, DC_UP, DC_DOWN, DC_EXEC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  PHP_EQ_STRICT, PHP_NEQ_STRICT, XXXXXXX, XXXXXXX, CL_COMP, CL_CMIT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  LCMD(LCTL(KC_SPC)), TO(0), MT(MOD_LALT, KC_SPC), MT(MOD_RALT, KC_ENT), TO(0), KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  )};
