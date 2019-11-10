/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   //#define RGBLIGHT_EFFECT_BREATHING
   //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
   //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   //#define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
   #define RGBLIGHT_EFFECT_RGB_TEST   // led_test keymap need only this.
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif


#undef RGBLED_NUM
#define RGBLED_NUM 64

/* RGB LED Conversion macro from physical array to electric array */
#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,            L32, L33, L34, L35, L36, L37, \
    L06, L07, L08, L09, L10, L11,            L38, L39, L40, L41, L42, L43, \
    L12, L13, L14, L15, L16, L17,            L44, L45, L46, L47, L48, L49, \
    L18, L19, L20, L21, L22, L23, L24,  L50, L51, L52, L53, L54, L55, L56, \
    L25, L26, L27, L28, L29, L30, L31,  L57, L58, L59, L60, L61, L62, L63  \
  ) \
  { \
    L00, L01, L02, L03, L04, L05,            L32, L33, L34, L35, L36, L37, \
    L06, L07, L08, L09, L10, L11,            L38, L39, L40, L41, L42, L43, \
    L12, L13, L14, L15, L16, L17,            L44, L45, L46, L47, L48, L49, \
    L18, L19, L20, L21, L22, L23, L24,  L50, L51, L52, L53, L54, L55, L56, \
    L25, L26, L27, L28, L29, L30, L31,  L57, L58, L59, L60, L61, L62, L63  \
  }

/* RGB LED logical order map */
/* Top->Bottom, Right->Left */
#define  RGBLIGHT_LED_MAP  LED_LAYOUT( \
     0,  1,  2,  3,  4,  5,          32, 33, 34, 35, 36, 37, \
     6,  7,  8,  9, 10, 11,          38, 39, 40, 41, 42, 43, \
    12, 13, 14, 15, 16, 17,          44, 45, 46, 47, 48, 49, \
    18, 19, 20, 21, 22, 23, 24,  50, 51, 52, 53, 54, 55, 56, \
    25, 26, 27, 28, 29, 30, 31,  57, 58, 59, 60, 61, 62, 63  \
 )

#endif /* CONFIG_USER_H */
