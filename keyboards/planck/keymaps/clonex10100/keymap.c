/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLEMAK,
  _LOWER,
  _RAISE,
  _UTIL,
  _NUMPAD, 
  _ADJUST,
  _GAMING
};

enum planck_keycodes {
  WS1 = SAFE_RANGE,
  WS2,
  WS3,
  WS4,
  WS5,
  FBTAB,
  BBTAB,
  CTAB,
  NTAB,
  COPY,
  CUT,
  PASTE
};

//tap dance
enum{
    RAISE_NUMLOCK
};

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for raise, twice for numberpad
    [RAISE_NUMLOCK] = ACTION_TAP_DANCE_DOUBLE(MO(_RAISE), TG(_ADJUST))
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define COLEMAK DF(_COLEMAK)
#define GAMING DF(_GAMING)
#define NUMPAD TG(_NUMPAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * 
 * This is the main, base layer
 *
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | GUI  | Alt  |Lower |    Space    | Raise|Numpad|Copy  | Cut  | Paste|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   NUMPAD,  COPY,    CUT,     PASTE
),

/* Lower
 * Symbol layer
 * TODO: Reorganize more efficiantly
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  Bksp|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  -   |  =   |  [   |  ]   |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM,  KC_AT,    KC_HASH,     KC_DLR,      KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_MINUS, KC_EQUAL, KC_LBRACKET, KC_RBRACKET, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______,  _______,  _______,     _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______,  _______,     _______,     _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise (Nav and numbers)
 * This is the easiest to access layer and should be used for things that are used all the time
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | BBTAB| CTAB | NTAB | FBTAB|      | Esc  | Left | Down |  Up  |Right |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Home | End  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 * Need to find a spot for -,=,[, and ]
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  BBTAB,   CTAB,    NTAB,    FBTAB,   _______, KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_BSLASH,
    _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Util (Lower + Raise)
 * For now it's an i3 nav.
 * ,-----------------------------------------------------------------------------------.
 * |Adjust| WS1  | WS2  | WS3  | WS4  | WS5  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Gaming|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | F1   | F2   | F3   | F4   | F5   | F6   | F7   | F8   | F9   | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_UTIL] = LAYOUT_planck_grid(
    TG(_ADJUST), WS1,     WS2,     WS3,     WS4,     WS5,     _______, _______, _______, _______, _______, _______,
    _______,     _______, _______, GAMING,  _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,
    _______,     _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______
),

/* Numpad. Yep. It's a numpad. Not much else to say
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   /  |  7   |  8   |  9   |BKSP  |
 * |------+------+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      |      |      |Exit  |   *  |  4   |  5   |  6   | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |  1   |  2   |  3   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |   +  |  0   |  .   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, KC_SLSH,  KC_7, KC_8,   KC_9,    KC_BSPC, 
        _______, _______, _______, _______, _______, _______, NUMPAD,  KC_ASTR,  KC_4, KC_5,   KC_6,    KC_ENT,
        _______, _______, _______, _______, _______, _______, _______, KC_MINUS, KC_1, KC_2,   KC_3,    _______,
        _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  KC_PLUS,  KC_0, KC_DOT, _______, _______
),
/* Adjust
 * Used for rarely used settings and toggles.
 * ,-----------------------------------------------------------------------------------.
 * |Un-Adj| Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    TG(_ADJUST), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,     _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
    _______,     MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF,_______, _______, _______,
    _______,     _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______
),

/*Gaming 
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  M   | Tab  |  Q   |  W   |  E   |  R   |  T   |COLMAK|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Ctrl |  A   |  S   |  D   |  F   |  G   |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Shift|  Z   |   X  |  C   |    space    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_ESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_M,   KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

};

//This runs everytime the layer state is changed
uint32_t layer_state_set_user(uint32_t state) {
  //Checks if _LOWER and _RAISE are both active, if so activates _UTIL
  return update_tri_layer_state(state, _LOWER, _RAISE, _UTIL);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WS1:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("1"));
      }
      return false;
      break;
    case WS2:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("2"));
      }
      return false;
      break;
    case WS3:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("3"));
      }
      return false;
      break;
    case WS4:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("4"));
      }
      return false;
      break;
    case WS5:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("5"));
      }
      return false;
      break;
    case BBTAB:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_TAB))));
      }
      return false;
      break;
    case NTAB:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("t"));
      }
      return false;
      break;
    case CTAB:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("w"));
      }
      return false;
      break;
    case FBTAB:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL(SS_TAP(X_TAB)));
      }
      return false;
      break;
    case COPY:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("c"));
      }
      return false;
      break;
    case CUT:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("x"));
      }
      return false;
      break;
    case PASTE:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("v"));
      }
      return false;
      break;
  }
  return true;
}


/* 
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
