/**
 * @file        Display.cpp
 * @module      The Display Module (DISP)
 *
 * @brief       Contains Code for Running Effects on LED Matrix of the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Display.hpp"
#include "Util.hpp"

// TODO: Make a class?
// TODO: Setup logic to change which effect is run (use the Buttons to call that?) (and I guess move the draw calls into here?)
// TODO: Implement actual state logic (iff off, do not change states)

// Static Reference to the LEDs to allow updates
static CRGB leds[NUM_LEDS];

#define SMILEY_FACE_NUM_PIXELS      61
// Active Pixels for smiley face (smile, left eye, right eye, outline)
static uint_fast8_t smileyFacePixels[SMILEY_FACE_NUM_PIXELS] = {114, 135, 143, 144, 145, 146, 147, 129, 122, 47, 46, 55, 56, 76, 75, 42, 41, 60, 61, 71, 70, 0, 1, 2, 3, 4, 6, 5, 24, 25, 50, 51, 80, 81, 110, 111, 138, 139, 162, 163, 164, 176, 175, 174, 173, 172, 170, 171, 152, 151, 126, 125, 96, 95, 66, 65, 38, 37, 14, 13, 12};


typedef enum {
    DISP_STATE_OFF      = 0u,
    DISP_STATE_SMILEY   = 1u,
    DISP_STATE_WHEEL    = 2u,
    DISP_STATE_MAX,
} DISP_State_e;

static String stateLabels[DISP_STATE_MAX] = {"OFF", "SMILEY", "WHEEL"};

static uint_fast16_t wheelPos = 0;
static DISP_State_e state;
static bool redraw;
static CRGB currColor;

static void printState(void);


void DISP_NextColor(void) {
    if (state != DISP_STATE_SMILEY) {
      return;
    }
    
    switch (currColor.as_uint32_t()) {
        case 0xFF800080:
            currColor = CRGB::Red;
            break;

        case 0xFFFF0000:
            currColor = CRGB::Yellow;
            break;

        case 0xFFFFFF00:
            currColor = CRGB::Green;
            break;

        case 0xFF008000:
            currColor = CRGB::Blue;
            break;

        case 0xFF0000FF:
            currColor = CRGB::Purple;
            break;

        default:
            break;
    }
    
    redraw = true;
}

void DISP_NextPattern(void) {
    // Cycle: Off -> Smiley -> Wheel (-> More) -> Smiley
    DISP_Clear();
    switch(state) {
        case DISP_STATE_OFF:
            state = DISP_STATE_SMILEY;
            break;
            
        case DISP_STATE_SMILEY:
            state = DISP_STATE_WHEEL;
            break;
            
        case DISP_STATE_WHEEL:
            state = DISP_STATE_SMILEY;
            break;
            
        default:
            state = DISP_STATE_OFF;
            break;
    }
    // Set redraw when changing patterns
    redraw = true;
    printState();
}

void DISP_Off(void) {
    DISP_Clear();
    state = DISP_STATE_OFF;
    printState();
    redraw = true;
}

/**
 * Initializes the Display Module and sets up the LEDs
 */
void DISP_Init(void) {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);
    
    currColor = CRGB::Yellow;
    DISP_NextPattern();
}

/**
 * Runs the Primary Display Task, responsible for controlling what's shown on the LEDs
 */
void DISP_Task(void) {
    switch (state) {
        case DISP_STATE_OFF:
            break;
            
        case DISP_STATE_SMILEY:
            if (redraw) {
                DISP_SmileyFace(currColor);
            }
            break;
            
        case DISP_STATE_WHEEL:
            redraw = true;
            DISP_ColorWheel(wheelPos);

            wheelPos += 12;
            if (wheelPos >= 3600 ) {
                wheelPos = 0;
            }
            
            break;
        
        default:
            state = DISP_STATE_OFF;
            break;
    }
    
    if (redraw) {
        redraw = false;
        FastLED.show();
    }
}

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
void DISP_ColorWheel(uint_fast16_t wheelPos) {
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

/**
 * Draws a Simple Smiley Face to the frame buffer
 * @param CRGB color - The color to draw
 */
void DISP_SmileyFace(CRGB color) {
    for (uint_fast8_t i = 0; i < SMILEY_FACE_NUM_PIXELS; i++) {
        leds[smileyFacePixels[i]] = color;
    }
}

/**
 * Clears the frame buffer
 */
void DISP_Clear(void) {
    for (uint_fast8_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}

static void printState(void) {
    DebugPrint("State: ");
    DebugPrintln(stateLabels[state]);
}
