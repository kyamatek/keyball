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
#define KC_A_BS LT(_BALL, KC_BSPC)    // adjust or back space
#define KC_A_DEL LT(_BALL, KC_DEL)    // adjust or delete
#define KC_AL_SP MT(MOD_LALT, KC_SPC)  // alt or space
#define KC_RAISE MO(_RAISE)
#define KC_BALL TO(_BALL)
#define KC_QWRT  TO(_QWERTY)

#define KC_WBACK LGUI(KC_LBRC) // browser back
#define KC_WFWRD LGUI(KC_RBRC) // browser forward


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
      TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,            LBRC ,  Y  ,  U  ,  I  ,  O  ,  P  ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     LCTL ,  A  ,  S  ,  D  ,  F  ,  G  ,            RBRC ,  H  ,  J  ,  K  ,  L  ,SCLN ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     LSFT ,  Z  ,  X  ,  C  ,  V  ,  B  ,                 ,  N  ,  M  , COMM, DOT , SLSH,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
     L_ESC,RAISE,RGUI , SPC ,LALT ,                 ,L_ENT,RSFT,RGUI,  MBTN1, BSPC ,RAISE 
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
      TAB ,  1  ,  2  ,  3  ,  4  ,  5  ,            WBACK,  6  ,  7  ,  8  ,  9  ,  0  ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     LCTL ,EXLM , AT  ,HASH , DLR ,PERC             ,WFWRD ,LEFT , DOWN, UP  ,RGHT ,MINS ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     LSFT ,CIRC , AMPR,ASTR ,LPRN ,RPRN             ,     , EQL , GRV ,QUOT ,MBTN2,BSLS ,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
      ESC ,     ,RGUI , SPC ,LALT ,                 ,L_ENT,RSFT ,RGUI ,MBTN1, DEL ,     
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----+-----+-----+-----+-----+-----.           ,-----+-----+-----+-----+-----+-----.
      F1  , F2  , F3  , F4  , F5  ,LPRN             , F6  , F7  , F8  , F9  , F10 , F11 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
     HASH ,EXLM ,AMPR ,PIPE , AT  ,RPRN             ,     ,MBTN1, PGUP,MBTN2,MBTN3, F12 ,
  //|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
      GRV , DQT ,QUOT ,CIRC ,TILD ,MBTN3            ,     ,VOLD ,VOLU ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----|           \-----+-----+-----+-----+-----+-----'
          ,PERC ,        ,A_DEL,     ,            ,    ,BALL ,     ,        ,     ,     
  //`-----+-----+  +-----+-----+-----+----'       `----+-----+-----+  +-----+-----+-----'
  ),

  [_BALL] = LAYOUT( \
  //,-----------------------------------------------------.          ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+          +--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_QWRT, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  //|--------+--------+    +-------+--------+--------+--------|  |-------+--------+--------+    +--------+--------+--------|
  ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};

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

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BALL:
        trackball_set_scroll_mode(true);
        trackball_set_divider(1);
        break;
    case _LOWER:
        trackball_set_scroll_mode(true);
        trackball_set_divider(1);
        break;
    case _RAISE:
        trackball_set_scroll_mode(false);
        trackball_set_divider(3);
        break;
    default:
        trackball_set_scroll_mode(false);
        trackball_set_divider(1);
        break;
    }
  return state;
}


#ifdef OLED_DRIVER_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Layer: Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Layer: Lower"), false);
            break;
        case _BALL:
            oled_write_ln_P(PSTR("Layer: Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        render_logo();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

#endif
