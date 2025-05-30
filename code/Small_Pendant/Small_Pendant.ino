/**
 * @file        Small_Pendant.ino
 * @module      The Main (Small_Pendant) Module
 *
 * @brief       Contains the Main code for the Small Pendant Project (Init and Task Dispatching)
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Config.h"
#include "Util.h"
#include "Buttons.h"
#include "Effects.h"


#define SMILEY_FACE_NUM_PIXELS      61
// Active Pixels for smiley face (smile, left eye, right eye, outline)
static uint_fast8_t smileyFacePixels[SMILEY_FACE_NUM_PIXELS] = {114, 135, 143, 144, 145, 146, 147, 129, 122, 47, 46, 55, 56, 76, 75, 42, 41, 60, 61, 71, 70, 0, 1, 2, 3, 4, 6, 5, 24, 25, 50, 51, 80, 81, 110, 111, 138, 139, 162, 163, 164, 176, 175, 174, 173, 172, 170, 171, 152, 151, 126, 125, 96, 95, 66, 65, 38, 37, 14, 13, 12};

CRGB leds[NUM_LEDS];


static uint_fast16_t wheelPos = 0;

static unsigned long lastTime = 0;

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);

    // Start with smiley face
    for (uint_fast8_t i = 0; i < SMILEY_FACE_NUM_PIXELS; i++) {
        leds[smileyFacePixels[i]] = CRGB::Green;
    }
    FastLED.show();
    // Hold for 2 seconds
    delay(2000);
}

void loop() {
    FX_ColorWheel(wheelPos);
    FastLED.show();
    wheelPos += 12;
    if (wheelPos >= 3600 ) {
        wheelPos = 0;
    }
    // TODO: implement manual systick generation (use a goddamn timer to implement it and add a callback to set a flag, maybe add delay(1)))
    // https://docs.espressif.com/projects/arduino-esp32/en/latest/api/timer.html
    delay(10);
}
