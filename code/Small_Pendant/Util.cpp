/**
 * @file        Util.cpp
 * @module      The Utility Module (UTIL)
 *
 * @brief       Contains Utily Methods and Defines for the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Util.hpp"

// Takes a pixel index and returns the angular offset from 0 (in tengths of a degree), unitless radius (in thousandths), and Percentage of White for ColorWheel
// UINT_FAST16_MAX for center value
const static uint_fast16_t angleLut[NUM_LEDS][3u] = {
   	{741, 7280, 0},
  	{819, 7071, 0},
  	{900, 7000, 0},
  	{981, 7071, 0},
  	{1060, 7280, 0},
  	{1237, 7211, 0},
  	{1166, 6708, 0},
  	{1084, 6325, 0},
  	{995, 6083, 2},
  	{900, 6000, 3},
  	{805, 6083, 2},
  	{716, 6325, 0},
  	{634, 6708, 0},
  	{563, 7211, 0},
  	{450, 7071, 0},
  	{513, 6403, 0},
  	{590, 5831, 5},
  	{682, 5385, 7},
  	{787, 5099, 9},
  	{900, 5000, 9},
  	{1013, 5099, 9},
  	{1118, 5385, 7},
  	{1210, 5831, 5},
  	{1287, 6403, 0},
  	{1350, 7071, 0},
  	{1463, 7211, 0},
  	{1413, 6403, 0},
  	{1350, 5657, 6},
  	{1269, 5000, 9},
  	{1166, 4472, 13},
  	{1040, 4123, 16},
  	{900, 4000, 20},
  	{760, 4123, 16},
  	{634, 4472, 13},
  	{531, 5000, 9},
  	{450, 5657, 6},
  	{387, 6403, 0},
  	{337, 7211, 0},
  	{266, 6708, 0},
  	{310, 5831, 5},
  	{369, 5000, 9},
  	{450, 4243, 15},
  	{563, 3606, 29},
  	{716, 3162, 39},
  	{900, 3000, 44},
  	{1084, 3162, 39},
  	{1237, 3606, 29},
  	{1350, 4243, 15},
  	{1431, 5000, 9},
  	{1490, 5831, 5},
  	{1534, 6708, 0},
  	{1641, 7280, 0},
  	{1616, 6325, 0},
  	{1582, 5385, 7},
  	{1534, 4472, 13},
  	{1463, 3606, 29},
  	{1350, 2828, 49},
  	{1166, 2236, 71},
  	{900, 2000, 84},
  	{634, 2236, 71},
  	{450, 2828, 49},
  	{337, 3606, 29},
  	{266, 4472, 13},
  	{218, 5385, 7},
  	{184, 6325, 0},
  	{160, 7280, 0},
  	{81, 7071, 0},
  	{95, 6083, 2},
  	{113, 5099, 9},
  	{140, 4123, 16},
  	{184, 3162, 39},
  	{266, 2236, 71},
  	{450, 1414, 122},
  	{900, 1000, 160},
  	{1350, 1414, 122},
  	{1534, 2236, 71},
  	{1616, 3162, 39},
  	{1660, 4123, 16},
  	{1687, 5099, 9},
  	{1705, 6083, 2},
  	{1719, 7071, 0},
  	{1800, 7000, 0},
  	{1800, 6000, 3},
  	{1800, 5000, 9},
  	{1800, 4000, 20},
  	{1800, 3000, 44},
  	{1800, 2000, 84},
  	{1800, 1000, 160},
      {CENTER, 0, 255},
  	{0, 1000, 160},
  	{0, 2000, 84},
  	{0, 3000, 44},
  	{0, 4000, 20},
  	{0, 5000, 9},
  	{0, 6000, 3},
  	{0, 7000, 0},
  	{3519, 7071, 0},
  	{3505, 6083, 2},
  	{3487, 5099, 9},
  	{3460, 4123, 16},
  	{3416, 3162, 39},
  	{3334, 2236, 71},
  	{3150, 1414, 122},
  	{2700, 1000, 160},
  	{2250, 1414, 122},
  	{2066, 2236, 71},
  	{1984, 3162, 39},
  	{1940, 4123, 16},
  	{1913, 5099, 9},
  	{1895, 6083, 2},
  	{1881, 7071, 0},
  	{1960, 7280, 0},
  	{1984, 6325, 0},
  	{2018, 5385, 7},
  	{2066, 4472, 13},
  	{2137, 3606, 29},
  	{2250, 2828, 49},
  	{2434, 2236, 71},
  	{2700, 2000, 84},
  	{2966, 2236, 71},
  	{3150, 2828, 49},
  	{3263, 3606, 29},
  	{3334, 4472, 13},
  	{3382, 5385, 7},
  	{3416, 6325, 0},
  	{3441, 7280, 0},
  	{3334, 6708, 0},
  	{3290, 5831, 5},
  	{3231, 5000, 9},
  	{3150, 4243, 15},
  	{3037, 3606, 29},
  	{2884, 3162, 39},
  	{2700, 3000, 44},
  	{2516, 3162, 39},
  	{2363, 3606, 29},
  	{2250, 4243, 15},
  	{2169, 5000, 9},
  	{2110, 5831, 5},
  	{2066, 6708, 0},
  	{2137, 7211, 0},
  	{2187, 6403, 0},
  	{2250, 5657, 6},
  	{2331, 5000, 9},
  	{2434, 4472, 13},
  	{2560, 4123, 16},
  	{2700, 4000, 20},
  	{2840, 4123, 16},
  	{2966, 4472, 13},
  	{3069, 5000, 9},
  	{3150, 5657, 6},
  	{3213, 6403, 0},
  	{3263, 7211, 0},
  	{3150, 7071, 0},
  	{3087, 6403, 0},
  	{3010, 5831, 5},
  	{2918, 5385, 7},
  	{2813, 5099, 9},
  	{2700, 5000, 9},
  	{2587, 5099, 9},
  	{2482, 5385, 7},
  	{2390, 5831, 5},
  	{2313, 6403, 0},
  	{2250, 7071, 0},
  	{2363, 7211, 0},
  	{2434, 6708, 0},
  	{2516, 6325, 0},
  	{2605, 6083, 2},
  	{2700, 6000, 3},
  	{2795, 6083, 2},
  	{2884, 6325, 0},
  	{2966, 6708, 0},
  	{3037, 7211, 0},
  	{2860, 7280, 0},
  	{2781, 7071, 0},
  	{2700, 7000, 0},
  	{2619, 7071, 0},
  	{2541, 7280, 0},
};

/**
 * Provides a rainbow given a position vlaue
 * The colours are a transition Red -> Green -> Blue -> Red
 * @param uint_fast8_t pos - The 'color wheel position', from 0 to 255
 * @return CRGB - The color data for the given position
 */
CRGB UTIL_Rainbow(uint_fast8_t pos) {
    CRGB outColor;
    if (pos < 85) {
        outColor.red = pos * 3;
        outColor.green = 255 - pos * 3;
        outColor.blue = 0;
    }
    else if (pos < 170) {
        pos -= 85;
        outColor.red = 255 - pos * 3;
        outColor.green = 0;
        outColor.blue = pos * 3;
    }
    else {
        pos -= 170;
        outColor.red = 0;
        outColor.green = pos * 3;
        outColor.blue = 255 - pos * 3;
    }

    return outColor;
}

/**
 * Gets the Polar Coords of the given LED address
 * @param uint_fast8_t led - The LED address
 * @return const uint_fast16_t* [3] - Polar Coordinates of the given LED (angle in tenths of a degree, unitless radius, visual weight percentage from center)
 */
const uint_fast16_t* UTIL_PolarCoords(uint_fast8_t led) {
    return angleLut[led];
}
