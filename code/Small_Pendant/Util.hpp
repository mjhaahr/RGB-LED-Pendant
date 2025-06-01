/**
 * @file        Util.hpp
 * @module      The Utility Module (UTIL)
 *
 * @brief       Contains Utily Methods and Defines for the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __UTIL_H__
#define __UTIL_H__

#include "Config.hpp"

#define UTIL_MAX(x, y)  (((x) > (y)) ? (x) : (y))
#define UTIL_MIN(x, y)  (((x) < (y)) ? (x) : (y))

#define CENTER              UINT_FAST16_MAX

/**
 * Provides a rainbow given a position vlaue
 * The colours are a transition Red -> Green -> Blue -> Red
 * @param uint_fast8_t pos - The 'color wheel position', from 0 to 255
 * @return CRGB - The color data for the given position
 */
CRGB UTIL_Rainbow(uint_fast8_t pos);

/**
 * Gets the Polar Coords of the given LED address
 * @param uint_fast8_t led - The LED address
 * @return uint_fast16_t* [3] - Polar Coordinates of the given LED (angle in tenths of a degree, unitless radius, visual weight percentage from center)
 */
uint_fast16_t* UTIL_PolarCoords(uint_fast8_t led);

#endif /* __UTIL_H__ */
