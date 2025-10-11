/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
  _PC = 0,   //done
  _MAC,      //done
  _LOWER,    //done
  _MLOWER,   //done
  _RAISE,    //done
  _MRAISE,   //done
  _ADJUST,   //done
  _MADJUST,  //done
  _FNKEYS    //done
};

//need to double check if this works
enum keycodes {
  PC = SAFE_RANGE,
  MAC
};

//custom keycode aliases
#define P_SPC LT(_LOWER, KC_SPC)
#define M_SPC LT(_MLOWER, KC_SPC)
#define P_ENT LT(_RAISE, KC_ENT)
#define M_ENT LT(_MRAISE, KC_ENT)
#define P_NUM TG(_RAISE)
#define M_NUM TG(_MRAISE)
#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define MLOWER TT(_MLOWER)
#define MRAISE TT(_MRAISE)
#define FNKEYS MO(_FNKEYS)
#define K_CAPS LT(_FNKEYS, KC_CAPS)
#define K_SLCK LT(_FNKEYS, KC_SLCK)
/*  //pc modifier keys
#define P_A WIN_T(KC_A)
#define P_O ALT_T(KC_O)
#define P_E CTL_T(KC_E)
#define P_U SFT_T(KC_U)
#define P_H SFT_T(KC_H)
#define P_T CTL_T(KC_T)
#define P_N ALT_T(KC_N)
#define P_S WIN_T(KC_S)
  //mac modifier keys
#define M_A CTL_T(KC_A)
#define M_O OPT_T(KC_O)
#define M_E CMD_T(KC_E)
#define M_U SFT_T(KC_U)
#define M_H SFT_T(KC_H)
#define M_T CMD_T(KC_T)
#define M_N OPT_T(KC_N)
#define M_S CTL_T(KC_S)
*/
  //mod key combos
#define K_TAB SFT_T(KC_TAB)
#define K_ESC ALT_T(KC_ESC)
#define P_BSPC CTL_T(KC_BSPC)
#define M_BSPC GUI_T(KC_BSPC)
#define P_DEL GUI_T(KC_DEL)
#define M_DEL CTL_T(KC_DEL)
  //keyboard shortcuts, p = pc, m = mac
#define P_ALL LCTL(KC_A)
#define M_ALL LGUI(KC_A)
#define P_CUT LCTL(KC_X)
#define M_CUT LGUI(KC_X)
#define P_CPY LCTL(KC_C)
#define M_CPY LGUI(KC_C)
#define P_PSTE LCTL(KC_V)
#define M_PSTE LGUI(KC_V)
#define P_UNDO LCTL(KC_Z)
#define M_UNDO LGUI(KC_Z)
#define P_REDO LCTL(KC_Y)
#define M_REDO LGUI(LSFT(KC_Z))
#define P_FIND LCTL(KC_F)
#define M_FIND LGUI(KC_F)
#define M_HOME LGUI(KC_LEFT)
#define M_END LGUI(KC_RGHT)
#define M_PSCR LGUI(LSFT(KC_3))
#define P_NEWT LCTL(KC_T)
#define M_NEWT LGUI(KC_T)
#define P_FSCN LCA_T(KC_F11)
#define M_FSCN LCA_T(KC_F11)
#define P_RFSH MEH_T(KC_F5)
#define M_RFSH MEH_T(KC_F5)

//variables for encoders to alt tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Base Layer: QWERTY
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |   "  |   ,  |   .  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |   ;  |   Q  |   J  |   K  |   X  | Esc  | Mute |  | F11  | Del  |   B  |   M  |   W  |   V  |   Z  |        |
   * |        |      |      |      |      |      | Alt  |CtrAlt|  | Meh  | GUI  |      |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        | Mute | Caps | Tab  |Space |Raise |  |Lower |Enter | BkSp |SclLck|AllWin|
   *                        |  Vol |FNkeys|Shift |Lower |      |  |      |Raise | Ctrl |FNkeys|AltTab|
   *                        `----------------------------------'  `----------------------------------'
   */
      [_PC] = LAYOUT(
        _______,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,    KC_Y,                                     KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  _______,
        _______,   KC_A,     KC_O,     KC_E,     KC_U,    KC_I,                                     KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  _______,
        _______,   KC_SCLN,  KC_Q,     KC_J,     KC_K,    KC_X,   K_ESC,  KC_MUTE, P_FSCN,  P_DEL,  KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  _______,
                                       KC_MUTE,  K_CAPS,  K_TAB,  P_SPC,  RAISE,   LOWER,   P_ENT,  P_BSPC,  K_SLCK,  G(KC_TAB)
      ),

      [_MAC] = LAYOUT(
        _______,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,    KC_Y,                                      KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  _______,
        _______,   KC_A,     KC_O,     KC_E,     KC_U,    KC_I,                                      KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  _______,
        _______,   KC_SCLN,  KC_Q,     KC_J,     KC_K,    KC_X,   K_ESC,  KC_MUTE,  M_FSCN,  M_DEL,  KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  _______,
                                       KC_MUTE,  K_CAPS,  K_TAB,  M_SPC,  MRAISE,   MLOWER,  M_ENT,  M_BSPC,  K_SLCK,  G(KC_TAB)
      ),

  /*
   * Lower Layer: Symbols
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |PrtScr| Find | Undo | Redo |  _   |                              |   ~  |   [  |   ]  |   &  |   @  |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |SelAll| Cut  | Copy |Paste |  ^   |                              |   \  |   (  |   )  |   !  |   ?  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |Fullsc|NewTab| Back | Fwd  |Rfrsh |      |      |  |      |      |   $  |   {  |   }  |   |  |   #  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |NumLk |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_LOWER] = LAYOUT(
        _______, KC_PSCR, P_FIND,  P_UNDO,  P_REDO,  KC_UNDS,                                     KC_TILD, KC_LBRC, KC_RBRC, KC_AMPR, KC_AT,   _______,
        _______, P_ALL,   P_CUT,   P_CPY,   P_PSTE,  KC_CIRC,                                     KC_BSLS, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES, _______,
        _______, P_FSCN,  P_NEWT,  KC_WBAK, KC_WFWD, KC_WREF, _______, _______, _______, _______, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, KC_HASH, _______,
                                   _______, KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______
      ),

      [_MLOWER] = LAYOUT(
        _______, KC_PSCR, M_FIND,  M_UNDO,  M_REDO,  KC_UNDS,                                     KC_TILD, KC_LBRC, KC_RBRC, KC_AMPR, KC_AT,   _______,
        _______, M_ALL,   M_CUT,   M_CPY,   M_PSTE,  KC_CIRC,                                     KC_BSLS, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES, _______,
        _______, M_FSCN,  M_NEWT,  KC_WBAK, KC_WFWD, KC_WREF, _______, _______, _______, _______, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, KC_HASH, _______,
                                   _______, KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______
      ),

  /*
   * Raise Layer: Number keys, media, navigation
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |   -  |   7  |   8  |   9  |   /  |                              |  `   | Home | Up   | End  |Pg Up |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |   +  |   4  |   5  |   6  |   *  |                              |  %   | Left | Down |Right |Pg Dn |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |   0  |   1  |   2  |   3  |   =  |      |      |  |      |      |      | Play | Prev | Next |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      | Calc |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_RAISE] = LAYOUT(
        _______, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS,                                     KC_GRV,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
        _______, KC_PPLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,                                     KC_PERC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_EQL,  _______, _______, _______, _______, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, _______,
                                   _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______
      ),

      [_MRAISE] = LAYOUT(
        _______, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS,                                     KC_GRV,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
        _______, KC_PPLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,                                     KC_PERC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_EQL,  _______, _______, _______, _______, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, _______,
                                   _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______
      ),

  /*
   * Adjust Layer: Function keys, RGB
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        | Reset| Debug| mac  |      |      |                              |      |LftClk| M up |RgtClk|MW up |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              |      | M lft| M dwn| M rgt|MW dwn|        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |Voice-|Voice+| RGB  |      |      |      |      |  |      |      |      | M 4  | M mid|MW lft|MW rgt|        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |Power |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_ADJUST] = LAYOUT(
        _______, RESET,   DEBUG,   MAC,     XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, MUV_DE,  MUV_IN,  RGB_TOG, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_BTN4, KC_BTN3, KC_WH_L, KC_WH_R, _______,
                                   _______, KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______
      ),

      [_MADJUST] = LAYOUT(
        _______, RESET,   DEBUG,   PC,      XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
        _______, MUV_DE,  MUV_IN,  RGB_TOG, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_BTN4, KC_BTN3, KC_WH_L, KC_WH_R, _______,
                                   _______, KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______
      ),

  /*
   * Layer template
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_FNKEYS] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                                     XXXXXXX, KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                                     XXXXXXX, KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______,
                                   _______, KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______
      ),

  // /*
  //  * Layer template
  //  *
  //  * ,-------------------------------------------.                              ,-------------------------------------------.
  //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
  //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  //  *                        |      |      |      |      |      |  |      |      |      |      |      |
  //  *                        |      |      |      |      |      |  |      |      |      |      |      |
  //  *                        `----------------------------------'  `----------------------------------'
  //  */
  //     [_LAYERINDEX] = LAYOUT(
  //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  //     ),
};

//copied directly from planck
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PC:
      if (record->event.pressed) {
        //print("mode just switched to dvorak and this is a huge string\n");
        set_single_persistent_default_layer(_PC);
      }
      return false;
      break;
    case MAC:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MAC);
      }
      return false;
      break;
  }
  return true;
}

//OLED
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev2.1\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
          case _PC:
              oled_write_P(PSTR("Windows\n"), false);
              break;
          case _MAC:
              oled_write_P(PSTR("Apple\n"), false);
              break;
          case _LOWER:
              oled_write_P(PSTR("Util & Symbol\n"), false);
              break;
          case _MLOWER:
              oled_write_P(PSTR("Util & Symbol\n"), false);
              break;
          case _RAISE:
              oled_write_P(PSTR("NumPad & Nav\n"), false);
              break;
          case _MRAISE:
              oled_write_P(PSTR("NumPad & Nav\n"), false);
              break;
          case _ADJUST:
              oled_write_P(PSTR("Set & Mouse\n"), false);
              break;
          case _MADJUST:
              oled_write_P(PSTR("Set & Mouse\n"), false);
              break;
          case _FNKEYS:
              oled_write_P(PSTR("Function\n"), false);
              break;
          default:
              oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
          // 'Brent logo for kyria', 128x64px
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
          0x1c, 0x5c, 0xfc, 0xfc, 0xfc, 0xfe, 0xfc, 0xfc, 0xfc, 0xfe, 0xfa, 0xf8, 0xfa, 0xf8, 0xf8, 0xf8,
          0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
          0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf0, 0xfc, 0x70, 0x40, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x10, 0x10, 0x10, 0x10,
          0x10, 0x90, 0xd0, 0x70, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x07, 0x03, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x1f,
          0x0b, 0x17, 0x03, 0x0b, 0x03, 0x03, 0x03, 0x03, 0x03, 0x73, 0xf3, 0xfb, 0xfb, 0xfb, 0xf9, 0xf9,
          0xf1, 0x51, 0x21, 0x01, 0x01, 0x01, 0x81, 0x80, 0x81, 0xc0, 0xc0, 0xe0, 0xf0, 0xf0, 0xe0, 0xe0,
          0xe0, 0xe0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x1e,
          0x17, 0x11, 0x90, 0xf0, 0x00, 0x00, 0xe0, 0xc0, 0xc0, 0x60, 0x30, 0x10, 0x10, 0xc0, 0x60, 0x30,
          0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x60, 0x20, 0x30, 0x10, 0xf0, 0x30, 0x30, 0x30,
          0x10, 0xff, 0x10, 0x18, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xc0,
          0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
          0xff, 0xfe, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
          0x1f, 0x1f, 0x1f, 0x0e, 0x02, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x04,
          0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x0a, 0x09,
          0x0c, 0x04, 0x04, 0x04, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
          0x00, 0x07, 0x1e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0e, 0x1f, 0xff, 0xff, 0xff,
          0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x1f,
          0x1f, 0x1f, 0x0f, 0x8f, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x0f, 0x7f, 0xff,
          0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x38, 0xf8, 0x00, 0x00, 0xc0, 0x70,
          0xfc, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
          0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0,
          0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
          0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3c, 0x07, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x7f,
          0x03, 0x00, 0x00, 0x70, 0xfc, 0x86, 0xc2, 0x63, 0xe2, 0x00, 0x00, 0x00, 0xf8, 0xe0, 0x38, 0x08,
          0x04, 0x06, 0x02, 0x02, 0x00, 0xff, 0xf0, 0xf0, 0x98, 0x0c, 0x04, 0x00, 0xe0, 0xe0, 0x00, 0x00,
          0xf0, 0x20, 0x00, 0x00, 0x00, 0x30, 0x7c, 0x44, 0xc6, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
          0x7f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8,
          0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x00, 0x01, 0x03, 0x06, 0x00, 0x01, 0x07, 0x06, 0x06,
          0x07, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf4, 0xf8, 0x7a, 0x79,
          0x3f, 0xfe, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x8f, 0x4f, 0x3f, 0x1f, 0x0f, 0x07, 0x01, 0x01, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3f, 0x7f, 0xff,
          0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xf0, 0xf0, 0xe0,
          0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x08, 0x08, 0x00, 0x04, 0x06, 0x02, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x07, 0x0f, 0x0f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
          0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
      if (clockwise) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(KC_TAB);
      } else {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
      }
    }
    return true;
}

//releases alt when alt tabbing
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

#endif

//TD Actions
qk_tap_dance_action_t tap_dance_actions[] = {
};

//RGB layers
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 5, 24, 255, 255},       // Light 5 LEDs, starting with LED 4
    {13, 5, 40, 255, 255}       // Light 5 LEDs, starting with LED 14
);

const rgblight_segment_t PROGMEM my_pc_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 0, 96, 255}       // Light 9 LEDs, starting with LED 1, color is white
);

const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 220, 187, 255}       // Light 9 LEDs, starting with LED 1, color is white
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 184, 255, 255}     //blue
);

const rgblight_segment_t PROGMEM my_mlower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 136, 255, 255}     //cyanish blue
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 96, 255, 255}      //forest green
);

const rgblight_segment_t PROGMEM my_mraise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 64, 255, 255}      //lime green
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 0, 255, 255}       //red
);

const rgblight_segment_t PROGMEM my_madjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 240, 255, 255}       //rose
);

const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 0, 255, 0}       //off
);

//array of layers, layers further down the list override earlier layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_pc_layer,        // 0
    my_mac_layer,       // 1
    my_lower_layer,     // 2
    my_mlower_layer,    // 3
    my_raise_layer,     // 4
    my_mraise_layer,    // 5
    my_adjust_layer,    // 6
    my_madjust_layer,   // 7
    my_fn_layer,        // 8
    my_capslock_layer   // 9
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(9, led_state.caps_lock);
/*    #ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
      led_state.caps_lock ? PLAY_SONG(tone_caps_on) : PLAY_SONG(tone_caps_off);
      caps_state = led_state.caps_lock;
    }
    static uint8_t nums_state = 0;
    if (nums_state != led_state.num_lock) {
      led_state.num_lock ? PLAY_SONG(tone_nums_on) : PLAY_SONG(tone_nums_off);
      nums_state = led_state.num_lock;
    }
    #endif */
    return true;
}


layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _PC));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MAC));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    state = update_tri_layer_state(state, _MLOWER, _MRAISE, _MADJUST);
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MLOWER));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(5, layer_state_cmp(state, _MRAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(7, layer_state_cmp(state, _MADJUST));
    rgblight_set_layer_state(8, layer_state_cmp(state, _FNKEYS));
    return state;
    //return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
