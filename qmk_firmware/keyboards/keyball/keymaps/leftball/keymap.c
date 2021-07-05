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
#include "trackball.h"

bool isScrollMode;

enum keymap_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _BALL,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  KC_MBTN1,
  KC_MBTN2,
  KC_MBTN3
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VD KC__VOLDOWN
#define KC_VU KC__VOLUP

// layer
#define KC_L_SPC LT(_LOWER, KC_SPC)
//#define KC_R_ENT LT(_RAISE, KC_ENT)
#define KC_L_ENT LT(_LOWER, KC_ENT)
#define KC_L_ESC LT(_LOWER, KC_ESC)

// shift_t
#define KC_S_EN LSFT_T(KC_LANG2)

// original
#define KC_A_JA LT(_BALL, KC_LANG1)   // cmd or adjust 
#define KC_AL_CP MT(MOD_LALT, KC_CAPS)  // alt or caps lock
#define KC_G_BS MT(MOD_LGUI, KC_BSPC)   // command or back space
#define KC_G_DEL MT(MOD_LGUI, KC_DEL)   // command or delete
#define KC_S_ENT MT(MOD_RSFT, KC_ENT)   // shift or enter
#define KC_A_BS LT(_BALL, KC_BSPC)    // adjust or back space
#define KC_A_DEL LT(_BALL, KC_DEL)    // adjust or delete
#define KC_AL_SP MT(MOD_LALT, KC_SPC)  // alt or space
#define KC_RAISE MO(_RAISE)
#define KC_BALL TO(_BALL)
#define KC_QWRT  TO(_QWERTY)

#define KC_WBACK LGUI(KC_LBRC) // browser back
#define KC_WFWRD LGUI(KC_RBRC) // browser forward


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                     KC_LBRC ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,                     KC_RBRC ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
     KC_LSFT ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,                                KC_N  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
     KC_L_ESC,KC_RAISE,KC_RGUI ,        KC_SPC ,KC_LALT ,               KC_L_ENT,KC_S_ENT,KC_RGUI ,     KC_MBTN1,   KC_BSPC ,KC_RAISE 
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_RAISE] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                     KC_WBACK,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL ,KC_EXLM , KC_AT  ,KC_HASH , KC_DLR ,KC_PERC ,                     KC_WFWRD,KC_LEFT ,KC_DOWN , KC_UP  ,KC_RGHT ,KC_MINS ,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
     KC_LSFT ,KC_CIRC , KC_AMPR,KC_ASTR ,KC_LPRN ,KC_RPRN ,                               KC_EQL , KC_GRV ,KC_QUOT ,KC_MBTN2,KC_BSLS ,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
      KC_ESC ,_______ ,KC_RGUI ,        KC_SPC ,KC_LALT ,               KC_L_ENT,KC_S_ENT,KC_RGUI,      KC_MBTN1,   KC_DEL  ,_______   
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_LOWER] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,KC_LPRN ,                     KC_F6  , KC_F7  , KC_F8   , KC_F9  , KC_F10 , KC_F11 ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_HASH ,KC_EXLM ,KC_AMPR ,KC_PIPE , KC_AT  ,KC_RPRN ,                     _______ , KC_PGUP,_______ ,_______ , KC_F12 ,_______,
  //|--------+--------+--------+--------+--------+--------|                    `--------+--------+--------+--------+--------+--------|
      KC_GRV , KC_DQT ,KC_QUOT ,KC_CIRC ,KC_TILD ,KC_MBTN3,                              KC_VOLD ,KC_VOLU ,_______ ,_______ ,_______ ,
  //|--------+--------+--------+--------+--------+--------'            ,--------+-------+--------+--------+--------+--------+--------|
     _______ ,KC_PERC ,_______ ,       _______ ,_______ ,               _______ ,KC_BALL ,_______ ,     _______ ,_______    ,_______   
  //`--------+--------+--------'      `--------+--------'              `--------+--------' `--------'  `--------'  `--------+--------'
  ),

  [_BALL] = LAYOUT_left_ball( \
  //,-----------------------------------------------------.          ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+          +--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,                          KC_QWRT, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  //|--------+--------+    +-------+--------+--------+--------|  |-------+--------+--------+    +--------+--------+--------|
  ),

};

//uint8_t posx = 0;
//uint8_t posy = 11;
//bool on = true;
//uint8_t rmx = 0;
//uint8_t rmy = 11;
const char integers[10] = "0123456789";
uint8_t count = 0;
uint8_t ten = 0;
uint8_t hundred = 0;
uint8_t thousand = 0;
uint8_t ten_thousand = 0;
static int trackball_divider = 1;

static bool is_shift = false;
static bool is_ctrl = false;
static bool is_opt = false;
static bool regflag = false;


void countup(void) {
    if (count == 9) {
        count = 0;
        if (ten == 9) {
            ten = 0;
            if (hundred == 9) {
                hundred = 0;
                if (thousand == 9) {
                    thousand = 0;
                    if (ten_thousand == 9) {
                        ten_thousand = 0;
                    } else {
                        ten_thousand++;
                    }
                } else {
                    thousand++;
                }
            } else {
                hundred++;
            }
        } else {
            ten++;
        }
    } else {
        count++;
    }
    /*
    rmx = posx;
    rmy = posy;
    if (posx == 127) {
        posx = 0;
        if (posy == 31) {
            posy = 11;
            on = !on;
        } else {
            posy++;
        }
    } else {
        posx++;
    }
    */
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};
  if (record->event.pressed) {
      countup();
  }

  switch (keycode) {
    case KC_MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
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
        trackball_set_scroll_mode(true);
      } else {
        trackball_set_scroll_mode(false);
      }
      return true;
  }
  return true;
}
	
/*#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif
    return true;
}*/

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse = true;
}

void trackball_process_user(int8_t dx, int8_t dy) {
    report_mouse_t r = pointing_device_get_report();
    if (is_shift && ((dx > 1 || dx < -1) || (dy > 1 || dy < -1))) {
        if (dy > 0 && dy > dx && dy > -dx) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            register_code(KC_DOWN);
            unregister_code(KC_DOWN);
        } else if (dy < 0 && dy < dx && dy < -dx) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            register_code(KC_UP);
            unregister_code(KC_UP);
        } else if (dx < 0 && dx < dy && dx < -dy) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            register_code(KC_LEFT);
            unregister_code(KC_LEFT);
        } else if (dx > 0 && dx > dy && dx > -dy) {
            unregister_code(KC_LSFT);
            unregister_code(KC_RSFT);
            register_code(KC_RGHT);
            unregister_code(KC_RGHT);
        }
        return;
    }
    if (!regflag && is_ctrl && ((dx > 2 || dx < -2) || (dy > 2 || dy < -2))) {
        if (dy > 0 && dy > dx && dy > -dx) {
            register_code(KC_DOWN);
            unregister_code(KC_DOWN);
        } else if (dy < 0 && dy < dx && dy < -dx) {
            register_code(KC_UP);
            unregister_code(KC_UP);
        } else if (dx < 0 && dx < dy && dx < -dy) {
            register_code(KC_RGHT);
            unregister_code(KC_RGHT);
        } else if (dx > 0 && dx > dy && dx > -dy) {
            register_code(KC_LEFT);
            unregister_code(KC_LEFT);
        }
        regflag = true;

    }
    if (regflag && dx < 2 && dy < 2 && dx > -2 && dy > -2) {
        regflag = false;
    }
    if (is_ctrl || is_shift) return;
    if (trackball_get_scroll_mode()) {
        r.h = dx;
        r.v = -dy;
    } else {
        r.x = dx / trackball_divider;
        r.y = dy / trackball_divider;
    }
    pointing_device_set_report(r);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BALL:
        trackball_set_scroll_mode(true);
        trackball_divider = 1;
        break;
    case _LOWER:
        trackball_set_scroll_mode(true);
        trackball_divider = 1;
        break;
    case _RAISE:
        trackball_set_scroll_mode(false);
        trackball_divider = 4;
        break;
    default:
        trackball_set_scroll_mode(false);
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
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Count: "), false);
    oled_write_char(integers[ten_thousand], false);
    oled_write_char(integers[thousand], false);
    oled_write_char(integers[hundred], false);
    oled_write_char(integers[ten], false);
    oled_write_char(integers[count], false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("SubLr: "), false);
    if (is_shift) {
        oled_write_ln_P(PSTR("Shift"), false);
    } else if (is_ctrl) {
        oled_write_ln_P(PSTR("Ctrl"), false);
    } else if (is_opt) {
        oled_write_ln_P(PSTR("Option"), false);
    } else {
        oled_write_ln_P(PSTR("Normal"), false);
    }

    
    //oled_write_pixel(posx, posy, on);
    //oled_write_pixel(rmx, rmy, false);
}

#endif
