/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
//default coloring
#    define RGBLIGHT_DEFAULT_SAT 96
//allow layer changes to change rgb
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_MAX_LAYERS 16
#endif

// Lets you roll mod-tap keys
//#define IGNORE_MOD_TAP_INTERRUPT

//necessary to ensure encoder is detected on each turn
#define TAP_CODE_DELAY 10

// time to detect tap dance action
#define TAPPING_TERM 150

//tapping toggle number of taps
#define TAPPING_TOGGLE 1
