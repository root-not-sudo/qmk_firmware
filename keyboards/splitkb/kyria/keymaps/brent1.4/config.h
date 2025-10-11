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

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  //#define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
  //need to check these (my additions to the default coming from my planck) RGB default saturation to make it look white (default hue is red)
  #define RGBLIGHT_DEFAULT_SAT 96
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 16
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK

/*
// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
// Encoder pad positions
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
*/
#define ENCODER_DIRECTION_FLIP


//necessary to ensure encoder is detected on each turn
#define TAP_CODE_DELAY 10



// time to detect tap dance action
#define TAPPING_TERM 150

//tapping toggle number of taps
#define TAPPING_TOGGLE 1

//maximum power in mA
//#define USB_MAX_POWER_CONSUMPTION 100

//5000 for master, 1000 for slave
//#define SPLIT_USB_TIMEOUT 5000
#define SPLIT_USB_TIMEOUT 1000
