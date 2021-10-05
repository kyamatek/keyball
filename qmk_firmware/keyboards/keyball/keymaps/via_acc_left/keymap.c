/*
Copyright 2021 @Yowkees

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

#include "pointing_device.h"
#include "oledkit.h"
#include "stdlib.h"
#include "../../pmw/pmw.h"
#include "../../optical_sensor/optical_sensor.h"

enum keymap_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _BALL,
};

/////////////////////////////////////////////////////////////////////////////
// Special key codes for shorthand

// clang-format off

// layer
#define KC_L_SPC    LT(_LOWER, KC_SPC)
#define KC_R_ENT    LT(_RAISE, KC_ENT)

// shift_t
#define KC_S_EN     LSFT_T(KC_LANG2)

// original
#define KC_A_JA     LT(_BALL, KC_LANG1)     // cmd or adjust
#define KC_AL_CP    MT(MOD_LALT, KC_CAPS)   // alt or caps lock
#define KC_G_BS     MT(MOD_LGUI, KC_BSPC)   // command or back space
#define KC_G_DEL    MT(MOD_LGUI, KC_DEL)    // command or delete
#define KC_A_BS     LT(_BALL, KC_BSPC)      // adjust or back space
#define KC_A_DEL    LT(_BALL, KC_DEL)       // adjust or delete

// additional
#define KC_S_ENT MT(MOD_RSFT, KC_ENT)   // shift or enter
#define KC_RAISE MO(_RAISE)
#define KC_BALL TO(_BALL)
#define KC_QWRT  TO(_QWERTY)
#define KC_L_ENT    LT(_LOWER, KC_ENT)
#define KC_WBACK LGUI(KC_LBRC) // browser back
#define KC_WFWRD LGUI(KC_RBRC) // browser forward

enum custom_keycodes {
    KC_CPI_DEF = SAFE_RANGE,
    KC_CPI_UP,
    KC_CPI_DOWN,
};

// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                     KC_LBRC ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,                     KC_RBRC ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
     KC_LSFT ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,                                KC_N  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
     KC_ESC  ,KC_RAISE,KC_RGUI ,        KC_SPC ,KC_LALT ,               KC_L_ENT,KC_S_ENT,KC_RGUI ,     KC_BTN1,   KC_BSPC ,KC_RAISE 
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_RAISE] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                     KC_WBACK,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL ,KC_EXLM , KC_AT  ,KC_HASH ,KC_DLR  ,KC_PERC ,                     KC_WFWRD,KC_LEFT ,KC_DOWN , KC_UP  ,KC_RGHT ,KC_MINS ,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
     KC_LSFT ,KC_CIRC , KC_AMPR,KC_ASTR ,KC_LPRN ,KC_RPRN ,                               KC_EQL , KC_GRV ,KC_QUOT ,KC_BTN2,KC_BSLS ,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      KC_ESC ,_______ ,KC_RGUI ,        KC_SPC ,KC_LALT ,               KC_L_ENT,KC_S_ENT,KC_RGUI,      KC_BTN1,   KC_DEL  ,_______   
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_LOWER] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                     _______ ,KC_F6  , KC_F7  , KC_F8   , KC_F9  , KC_F10 ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_HASH ,KC_EXLM ,KC_AMPR ,KC_PIPE , KC_AT  ,KC_RPRN ,                     _______ ,KC_CPI_DEF,KC_CPI_DOWN,KC_CPI_UP, KC_F11 ,KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      KC_GRV , KC_DQT ,KC_QUOT ,KC_CIRC ,KC_TILD ,KC_BTN3,                              KC_VOLD ,KC_VOLU ,_______ ,_______ ,_______ ,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
     _______ ,KC_PERC ,_______ ,       _______ ,_______ ,               _______ ,KC_BALL ,_______,         _______ ,_______ ,_______   
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_BALL] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CPI_DEF, KC_CPI_DOWN, KC_CPI_UP, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_QWRT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX,                KC_QWRT, KC_QWRT,XXXXXXX,    XXXXXXX,    XXXXXXX, KC_RAISE
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

};

// clang-format on

static bool is_shift = false;
static bool is_ctrl = false;
static bool is_opt = false;
static bool regflag = false;
static bool is_scroll = false;
static int trackball_divider = 1;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BALL:
            keyball_set_scroll_mode(false);
            trackball_divider = 1;
            break;
        case _LOWER:
            keyball_set_scroll_mode(!is_scroll);
            trackball_divider = 1;
            break;
        case _RAISE:
            keyball_set_scroll_mode(is_scroll);
            trackball_divider = 4;
            break;
        default:
            keyball_set_scroll_mode(false);
            trackball_divider = 1;
            break;
    }
    return state;
}

#ifdef OLED_DRIVER_ENABLE

void oledkit_render_info_user(void) {
    const char *n;
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            n = PSTR("Default");
            break;
        case _RAISE:
            n = PSTR("Raise");
            break;
        case _LOWER:
            n = PSTR("Lower");
            break;
        case _BALL:
            n = PSTR("Adjust");
            break;
        default:
            n = PSTR("Undefined");
            break;
    }
    oled_write_P(PSTR("Layer: "), false);
    oled_write_ln_P(n, false);

    keyball_oled_render_ballinfo();
    keyball_oled_render_keyinfo();
}

#endif

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) { return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v; }

int8_t keyball_process_trackball_acceleration(const int16_t val) {
    //int step1 = 3;
    //float step1_acc = 3;

    //int step2 = 10;
    //float step2_acc = 13;

    int step1 = 2;
    float step1_acc = 2;

    int step2 = 2;
    float step2_acc = 2;

    int abs_val = abs(val);

    int8_t result = 0;

    if (abs_val > step2) {
        result = clip2int8(val * step2_acc);
    } else if (abs_val > step1){
        result = clip2int8(val * step1_acc);
    } else {
        result = clip2int8(val);
    }

    return result;
}

void keyball_process_trackball_user(const trackball_delta_t *primary, const trackball_delta_t *secondary) {
    bool is_scroll_mode = keyball_get_scroll_mode();
    report_mouse_t r = pointing_device_get_report();
    if (primary) {
        if (is_shift && (((primary->x) > 1 || (primary->x) < -1) || ((primary->y) > 1 || (primary->y) < -1))) {
            if ((primary->y) > 0 && (primary->y) > (primary->x) && (primary->y) > -(primary->x)) {
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                register_code(KC_DOWN);
                unregister_code(KC_DOWN);
            } else if ((primary->y) < 0 && (primary->y) < (primary->x) && (primary->y) < -(primary->x)) {
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                register_code(KC_UP);
                unregister_code(KC_UP);
            } else if ((primary->x) < 0 && (primary->x) < (primary->y) && (primary->x) < -(primary->y)) {
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            } else if ((primary->x) > 0 && (primary->x) > (primary->y) && (primary->x) > -(primary->y)) {
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                register_code(KC_RGHT);
                unregister_code(KC_RGHT);
            }
            return;
        }
        if (!regflag && is_ctrl && (((primary->x) > 2 || (primary->x) < -2) || ((primary->y) > 2 || (primary->y) < -2))) {
            if ((primary->y) > 0 && (primary->y) > (primary->x) && (primary->y) > -(primary->x)) {
                register_code(KC_DOWN);
                unregister_code(KC_DOWN);
            } else if ((primary->y) < 0 && (primary->y) < (primary->x) && (primary->y) < -(primary->x)) {
                register_code(KC_UP);
                unregister_code(KC_UP);
            } else if ((primary->x) < 0 && (primary->x) < (primary->y) && (primary->x) < -(primary->y)) {
                register_code(KC_RGHT);
                unregister_code(KC_RGHT);
            } else if ((primary->x) > 0 && (primary->x) > (primary->y) && (primary->x) > -(primary->y)) {
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            regflag = true;
        }
        if (regflag && (primary->x) < 2 && (primary->y) < 2 && (primary->x) > -2 && (primary->y) > -2) {
            regflag = false;
        }
        if (is_ctrl || is_shift) return;

        if (!is_scroll_mode) {
            r.x = keyball_process_trackball_acceleration((primary->x) / trackball_divider);
            r.y = keyball_process_trackball_acceleration((primary->y) / trackball_divider);
            //r.x += clip2int8((primary->x) / trackball_divider);
            //r.y += clip2int8((primary->y) / trackball_divider);
        } else {
            r.h += clip2int8(primary->x);
            r.v -= clip2int8(primary->y);
        }
    }
    if (secondary) {
        r.h += clip2int8(secondary->x);
        r.v -= clip2int8(secondary->y);
    }


    pointing_device_set_report(r);
    pointing_device_send();
}

void keyboard_post_init_user(void) {
    eeconfig_t kb_config;
    kb_config.raw = eeconfig_read_user();

    if (!kb_config.cpi) {
        kb_config.cpi = DEFAULT_CPI;
        eeconfig_update_user(kb_config.raw);
    }

    pmw_set_config((config_pmw_t){kb_config.cpi});
}

static void on_cpi_button(int cpi, keyrecord_t *record, bool absolute) {
    if (!record->event.pressed) return;

    eeconfig_t kb_config;

    if (absolute) {
        kb_config.cpi = (uint16_t)CLAMP_CPI(cpi);
    } else {
        kb_config.raw = eeconfig_read_user();
        int config_1;

        if (cpi < 0 && kb_config.cpi < abs(cpi)) {
            config_1 = MIN_CPI;
        } else {
            config_1 = (int)kb_config.cpi + cpi;
        }

        kb_config.cpi = (uint16_t)CLAMP_CPI(config_1);
    }

    eeconfig_update_user(kb_config.raw);
    pmw_set_config((config_pmw_t){kb_config.cpi});
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case KC_CPI_DEF:
            on_cpi_button(DEFAULT_CPI, record, true);
            return false;

        case KC_CPI_UP:
            on_cpi_button(2 * CPI_STEP, record, false);
            return false;

        case KC_CPI_DOWN:
            on_cpi_button(-2 * CPI_STEP, record, false);
            return false;
        case KC_LSFT:
            if (record->event.pressed) {
                is_shift = true;
            } else {
                is_shift = false;
            }
            return true;
        case KC_S_ENT:
            if (record->event.pressed) {
                is_shift = true;
            } else {
                is_shift = false;
            }
            return true;
        case KC_LCTL:
            if (record->event.pressed) {
                is_ctrl = true;
            } else {
                is_ctrl = false;
            }
            return true;
        case KC_LALT:
            if (record->event.pressed) {
                is_opt = true;
            } else {
                is_opt = false;
            }
            return true;
        case KC_RGUI:
            if (record->event.pressed) {
                keyball_set_scroll_mode(!is_scroll);
            } else {
                keyball_set_scroll_mode(is_scroll);
            }
            return true;
        default:
            return true;
    }
}
