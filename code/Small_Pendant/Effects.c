/**
 * @file        Effects.c
 * @module      The Effects Module (FX)
 *
 * @brief       Contains Code for Running Effects on LED Matrix of the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Effects.h"
#include "Util.h"

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
void FX_ColorWheel(uint_fast16_t wheelPos) {
    // Pre-allocate pos data pointer
    uint_fast16_t* posData;
    // Loop over all pixels
    for (uint_fast8_t i = 0; i < NUM_LEDS; i++) {
        posData = UTIL_PolarCoords(i);

        if (posData[0] != CENTER) {
            // Sum angles, wrap to 3600
            uint_fast32_t angle = (wheelPos + posData[0]) % 3600;
            // Remap to 0-255
            uint_fast8_t colorPos = (uint_fast8_t) (angle * 255 / 3600);
            CRGB color = UTIL_Rainbow(colorPos);

            fract8 colorScale = (fract8) posData[2];

            CRGB newColor = blend(color, CRGB::White, colorScale);
            leds[i] = newColor;
        } else {
            leds[i] = CRGB::White;
        }
    }
}
