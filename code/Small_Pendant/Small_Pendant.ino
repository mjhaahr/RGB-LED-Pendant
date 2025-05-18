#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS        177u
#define LED_PIN         8u
#define MAX_BRIGHTNESS  15u

#define CENTER              UINT_FAST16_MAX

// Takes a pixel index and returns the angular offset from 0 (in tengths of a degree) and a unitless radius (in thousandths)
// UINT_FAST16_MAX for center value
uint_fast16_t angleLut[NUM_LEDS][2u] = {
   	{741, 7280},
	{819, 7071},
	{900, 7000},
	{981, 7071},
	{1060, 7280},
	{1237, 7211},
	{1166, 6708},
	{1084, 6325},
	{995, 6083},
	{900, 6000},
	{805, 6083},
	{716, 6325},
	{634, 6708},
	{563, 7211},
	{450, 7071},
	{513, 6403},
	{590, 5831},
	{682, 5385},
	{787, 5099},
	{900, 5000},
	{1013, 5099},
	{1118, 5385},
	{1210, 5831},
	{1287, 6403},
	{1350, 7071},
	{1463, 7211},
	{1413, 6403},
	{1350, 5657},
	{1269, 5000},
	{1166, 4472},
	{1040, 4123},
	{900, 4000},
	{760, 4123},
	{634, 4472},
	{531, 5000},
	{450, 5657},
	{387, 6403},
	{337, 7211},
	{266, 6708},
	{310, 5831},
	{369, 5000},
	{450, 4243},
	{563, 3606},
	{716, 3162},
	{900, 3000},
	{1084, 3162},
	{1237, 3606},
	{1350, 4243},
	{1431, 5000},
	{1490, 5831},
	{1534, 6708},
	{1641, 7280},
	{1616, 6325},
	{1582, 5385},
	{1534, 4472},
	{1463, 3606},
	{1350, 2828},
	{1166, 2236},
	{900, 2000},
	{634, 2236},
	{450, 2828},
	{337, 3606},
	{266, 4472},
	{218, 5385},
	{184, 6325},
	{160, 7280},
	{81, 7071},
	{95, 6083},
	{113, 5099},
	{140, 4123},
	{184, 3162},
	{266, 2236},
	{450, 1414},
	{900, 1000},
	{1350, 1414},
	{1534, 2236},
	{1616, 3162},
	{1660, 4123},
	{1687, 5099},
	{1705, 6083},
	{1719, 7071},
	{1800, 7000},
	{1800, 6000},
	{1800, 5000},
	{1800, 4000},
	{1800, 3000},
	{1800, 2000},
	{1800, 1000},
    {CENTER, 0},
	{0, 1000},
	{0, 2000},
	{0, 3000},
	{0, 4000},
	{0, 5000},
	{0, 6000},
	{0, 7000},
	{3519, 7071},
	{3505, 6083},
	{3487, 5099},
	{3460, 4123},
	{3416, 3162},
	{3334, 2236},
	{3150, 1414},
	{2700, 1000},
	{2250, 1414},
	{2066, 2236},
	{1984, 3162},
	{1940, 4123},
	{1913, 5099},
	{1895, 6083},
	{1881, 7071},
	{1960, 7280},
	{1984, 6325},
	{2018, 5385},
	{2066, 4472},
	{2137, 3606},
	{2250, 2828},
	{2434, 2236},
	{2700, 2000},
	{2966, 2236},
	{3150, 2828},
	{3263, 3606},
	{3334, 4472},
	{3382, 5385},
	{3416, 6325},
	{3441, 7280},
	{3334, 6708},
	{3290, 5831},
	{3231, 5000},
	{3150, 4243},
	{3037, 3606},
	{2884, 3162},
	{2700, 3000},
	{2516, 3162},
	{2363, 3606},
	{2250, 4243},
	{2169, 5000},
	{2110, 5831},
	{2066, 6708},
	{2137, 7211},
	{2187, 6403},
	{2250, 5657},
	{2331, 5000},
	{2434, 4472},
	{2560, 4123},
	{2700, 4000},
	{2840, 4123},
	{2966, 4472},
	{3069, 5000},
	{3150, 5657},
	{3213, 6403},
	{3263, 7211},
	{3150, 7071},
	{3087, 6403},
	{3010, 5831},
	{2918, 5385},
	{2813, 5099},
	{2700, 5000},
	{2587, 5099},
	{2482, 5385},
	{2390, 5831},
	{2313, 6403},
	{2250, 7071},
	{2363, 7211},
	{2434, 6708},
	{2516, 6325},
	{2605, 6083},
	{2700, 6000},
	{2795, 6083},
	{2884, 6325},
	{2966, 6708},
	{3037, 7211},
	{2860, 7280},
	{2781, 7071},
	{2700, 7000},
	{2619, 7071},
	{2541, 7280},
};

CRGB leds[NUM_LEDS];


static uint16_t wheelPos = 0;

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);
}

void loop() {
    colorWheel(wheelPos);
    wheelPos += 12;
    delay(10);
}

// Draws a colorwheel onto the display, taking in the wheel position from zero in tenths of a degree
void colorWheel(uint16_t wheelPos) {
    // Pre-allocate pos data pointer
    uint_fast16_t *posData;
    // Loop over all pixels
    for (uint_fast8_t i = 0; i < NUM_LEDS; i++) {
        posData = angleLut[i];

        if (posData[0] != CENTER) {
            // Sum angles, wrap to 3600
            uint_fast32_t angle = (wheelPos + posData[0]) % 3600;
            // Remap to 0-255
            uint_fast8_t colorPos = (uint_fast8_t) (angle * 255 / 3600);
            CRGB color = rainbow(colorPos);

            fract8 colorScale;

            // Distance fraction
            if (posData[1] < 2000) {
                uint16_t scaledDist = (posData[1] * 9 / 100);
                colorScale = (fract8) (268 - scaledDist);
            } else if (posData[1] < 3000) {
                uint16_t scaledDist = (posData[1] * 6 / 100);
                colorScale = (fract8) (204 - scaledDist);
            } else if (posData[1] < 4000) {
                uint16_t scaledDist = (posData[1] * 6 / 1000);
                colorScale = (fract8) (75 - scaledDist);
            } else if (posData[1] < 6000) {
                uint16_t scaledDist = (posData[1] * 15 / 2000);
                colorScale = (fract8) (45 - scaledDist);
            } else {
                colorScale = 0;
            }

            CRGB newColor = blend(color, CRGB::White, colorScale);
            leds[i] = newColor;
        } else {
            leds[i] = CRGB::White;
        }
    }

    FastLED.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB rainbow(uint_fast8_t pos) {
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
