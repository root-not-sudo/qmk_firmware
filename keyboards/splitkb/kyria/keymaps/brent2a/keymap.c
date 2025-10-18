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
  _LOWER,    //done
  _RAISE,    //done
  _ADJUST   //done
};

//need to double check if this works
enum keycodes {
  PC = SAFE_RANGE
};

//custom keycode aliases
#define P_SPC LT(_LOWER, KC_SPC)
#define P_ENT LT(_RAISE, KC_ENT)
#define RAISE TG(_RAISE)
#define LOWER TG(_LOWER)
#define CADEL LCA(KC_DEL)
#define WINT LGUI(KC_TAB)
#define BRCK LCTL(KC_C)
#define CLOSE LALT(KC_F4)

  //mod key combos
#define K_TAB SFT_T(KC_TAB)
#define P_BSPC CTL_T(KC_BSPC)
#define P_DEL GUI_T(KC_DEL)
#define XALT LALT_T(KC_X)
#define BGUI LGUI_T(KC_B)

  //keyboard shortcuts
#define P_ALL LCTL(KC_A)
#define P_CUT LCTL(KC_X)
#define P_CPY LCTL(KC_C)
#define P_PSTE LCTL(KC_V)
#define P_UNDO LCTL(KC_Z)
#define P_REDO LCTL(KC_Y)
#define P_FIND LCTL(KC_F)


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
   * |        |   ;  |   Q  |   J  |   K  |   X  | C+A  | F13  |  | Alt  | GUI  |   B  |   M  |   W  |   V  |   Z  |        |
   * |        |      |      |      |      |  Alt | Del  |      |  |      |      |  GUI |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      | Mute | Tab  |Space | F14  |  | Ctrl |Enter | BkSp |WinTab|      |
   *                        |      |      |Shift |Lower |      |  |      |Raise | Ctrl |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_PC] = LAYOUT(
        _______,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,     KC_Y,                                      KC_F,   KC_G,    KC_C,    KC_R,   KC_L,  _______,
        _______,   KC_A,     KC_O,     KC_E,     KC_U,     KC_I,                                      KC_D,   KC_H,    KC_T,    KC_N,   KC_S,  _______,
        _______,   KC_SCLN,  KC_Q,     KC_J,     KC_K,     XALT,   CADEL,  KC_F13, KC_RALT,  KC_RGUI, BGUI,   KC_M,    KC_W,    KC_V,   KC_Z,  _______,
                                       _______,  KC_MUTE,  K_TAB,  P_SPC,  KC_F14, KC_RCTL,  P_ENT,  P_BSPC,  WINT,  _______
      ),


  /*
   * Lower Layer: Symbols
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |PrtScr| Find | Undo | Redo |  _   |                              |   ~  |   [  |   ]  |   &  |   @  |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |SelAll| Cut  | Copy |Paste |  ^   |                              |   \  |   (  |   )  |   !  |   ?  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |CAPSL |NUMLCK|SCRLCK|Insert|Raise |      |      |  |      |      |   $  |   {  |   }  |   |  |   #  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      | Esc  |      |      |  |      |      | Del  |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_LOWER] = LAYOUT(
        _______, KC_PSCR, P_FIND,  P_UNDO,  P_REDO,  KC_UNDS,                                     KC_TILD, KC_LBRC, KC_RBRC, KC_AMPR, KC_AT,   _______,
        _______, P_ALL,   P_CUT,   P_CPY,   P_PSTE,  KC_CIRC,                                     KC_BSLS, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES, _______,
        _______, KC_CAPS, KC_NUM,  KC_SCRL, KC_INS,  RAISE,   _______, _______, _______, _______, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, KC_HASH, _______,
                                   _______, _______, KC_ESC,  _______, _______, _______, _______, KC_DEL,  _______, _______
      ),


  /*
   * Raise Layer: Number keys, media, navigation
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |   -  |   7  |   8  |   9  |   /  |                              |  `   | Home | Up   | End  |Pg Up |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |   +  |   4  |   5  |   6  |   *  |                              |  %   | Left | Down |Right |Pg Dn |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |   0  |   1  |   2  |   3  |   =  |      |      |  |      |      |Lower | F11  | Back |Refrsh| Fwd  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      | Calc |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_RAISE] = LAYOUT(
        _______, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS,                                     KC_GRV,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
        _______, KC_PPLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,                                     KC_PERC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_EQL,  _______, _______, _______, _______, LOWER,   KC_F11,  KC_WBAK, KC_F5,   KC_WFWD, _______,
                                   _______, _______, KC_ESC,  _______, _______, _______, _______, KC_DEL,  _______, _______
      ),


  /*
   * Adjust Layer: normal numbers, function keys, various functions
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |Reboot|   7  |   8  |   9  | Power|                              |VolUp | F2   | F3   | F4   |Reboot|        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        | Break|   4  |   5  |   6  | Close|                              |VolDwn| F5   | F6   | F7   | F8   |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |   0  |   1  |   2  |   3  | F1   |      |      |  |      |      | Mute | UGUp | UGDwn| UGTg |CtlGUI|        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
      [_ADJUST] = LAYOUT(
        _______, QK_BOOT, KC_7,   KC_8,    KC_9,    KC_PWR,                                      KC_VOLU, KC_F2,   KC_F3,   KC_F4,   QK_BOOT, _______,
        _______, BRCK,    KC_4,   KC_5,    KC_6,    CLOSE,                                       KC_VOLD, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
        _______, KC_0,    KC_1,   KC_2,    KC_3,    KC_F1,   _______, _______, _______, _______, KC_MUTE, UG_VALU, UG_VALD, UG_TOGG, CG_TOGG, _______,
                                  _______, _______, KC_ESC,  _______, _______, _______, _______, KC_DEL,  _______, _______
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
          case _LOWER:
              oled_write_P(PSTR("Util & Symbol\n"), false);
              break;
          case _RAISE:
              oled_write_P(PSTR("NumPad & Nav\n"), false);
              break;
          case _ADJUST:
              oled_write_P(PSTR("Set & Mouse\n"), false);
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

//ALT TAB Encoder Timer
void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
};

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
      register_code(KC_LALT);
      is_alt_tab_active = true;
      if (clockwise) {
          tap_code(KC_TAB);
      } else {
          register_code(KC_LSFT);
          tap_code(KC_TAB);
          unregister_code(KC_LSFT); // this fixes the getting stuck problem
      }
      alt_tab_timer = timer_read();
}
return false;
};

#endif


//RGB layers
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 5, 24, 255, 255},       // Light 5 LEDs, starting with LED 4
    {13, 5, 40, 255, 255}       // Light 5 LEDs, starting with LED 14
);

const rgblight_segment_t PROGMEM my_pc_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 0, 96, 255}       // Light 9 LEDs, starting with LED 1, color is white
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 184, 255, 255}     //blue
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 96, 255, 255}      //forest green
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, 0, 255, 255}       //red
);

//array of layers, layers further down the list override earlier layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_pc_layer,        // 0
    my_lower_layer,     // 1
    my_raise_layer,     // 2
    my_adjust_layer,    // 3
    my_capslock_layer   // 4
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
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
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
    //return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
