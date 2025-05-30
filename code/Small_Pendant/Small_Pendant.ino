/**
 * @file        Small_Pendant.ino
 * @module      The Main (Small_Pendant) Module
 *
 * @brief       Contains the Main code for the Small Pendant Project (Init and Task Dispatching)
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Config.hpp"
#include "Util.hpp"
#include "Buttons.hpp"
#include "Effects.hpp"

static CRGB leds[NUM_LEDS];

// TODO: move wheelPos to FX Module
static uint_fast16_t wheelPos = 0;

static unsigned long lastTime = 0;

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);

    FX_Init(leds);

    // Start with smiley face
    FX_SmileyFace();
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
