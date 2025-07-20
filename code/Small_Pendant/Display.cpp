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

#define SMILEY_FACE_NUM_PIXELS      61
// Active Pixels for smiley face (smile, left eye, right eye, outline)
const static uint_fast8_t smileyFacePixels[SMILEY_FACE_NUM_PIXELS] = {114, 135, 143, 144, 145, 146, 147, 129, 122, 47, 46, 55, 56, 76, 75, 42, 41, 60, 61, 71, 70, 0, 1, 2, 3, 4, 6, 5, 24, 25, 50, 51, 80, 81, 110, 111, 138, 139, 162, 163, 164, 176, 175, 174, 173, 172, 170, 171, 152, 151, 126, 125, 96, 95, 66, 65, 38, 37, 14, 13, 12};

#define DISP_WHEEL_TIME_S           3
#define DISP_WHEEL_MAX              3600
#define DISP_WHEEL_INT              (DISP_WHEEL_MAX / (UI_UPDATE_FREQ * DISP_WHEEL_TIME_S));

typedef enum {
    DISP_STATE_OFF      = 0u,
    DISP_STATE_WHEEL    = 1u,
    DISP_STATE_SMILEY   = 2u,
    DISP_STATE_CYLON    = 3u,
    DISP_STATE_MAX,
} DISP_State_e;

// Struct to hold the static context for the state info
typedef struct {
    uint_fast16_t index;
    bool dir;
    DISP_State_e state;
    bool redraw;
    CRGB currColor;
    bool alternate;
} DISP_DisplayContext_s;

/**
 * Local State Print helper
 */
static void printState(void);

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
static void DISP_ColorWheel(uint_fast16_t wheelPos);

/**
 * Draws a Simple Smiley Face to the frame buffer
 * @param CRGB color - The color to draw
 */
static void DISP_SmileyFace(CRGB color);

/**
 * Draws a the next frame of the Cylon image using the color
 * @param CRGB color - The color to draw
 */
static void DISP_Cylon(CRGB color);

/**
 * Clears the frame buffer
 */
static void DISP_Clear(void);

// Static Context
static DISP_DisplayContext_s dispContext;
// Static Reference to the LEDs to allow updates
static CRGB leds[NUM_LEDS];

/**
 * Initializes the Display Module and sets up the LEDs
 */
void DISP_Init(void) {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);
    // Disable dithering to remove flicker
    FastLED.setDither(DISABLE_DITHER);

    dispContext.index = 0u;
    dispContext.dir = false;
    dispContext.state = DISP_STATE_OFF;
    dispContext.redraw = false;
    dispContext.currColor = CRGB::Purple;
    dispContext.alternate = false;
    DISP_NextPattern();
}

/**
 * Runs the Primary Display Task, responsible for controlling what's shown on the LEDs
 */
void DISP_Task(void) {
    switch (dispContext.state) {
        case DISP_STATE_OFF:
            break;
            
        case DISP_STATE_WHEEL:
            dispContext.redraw = true;
            DISP_ColorWheel(dispContext.index);

            dispContext.index += DISP_WHEEL_INT;
            if (dispContext.index >= DISP_WHEEL_MAX) {
                dispContext.index = 0u;
            }
            
            break;
            
        case DISP_STATE_SMILEY:
            if (dispContext.redraw) {
                DISP_SmileyFace(dispContext.currColor);
            }
            break;
            
        case DISP_STATE_CYLON:
            dispContext.redraw = true;
            // Run every other frame
            if (!dispContext.alternate) {
                // Handle Wrap
                if (dispContext.index >= NUM_LEDS) {
                    dispContext.dir = true;
                    dispContext.index = NUM_LEDS;
                } else if (dispContext.index == 0u) {
                    dispContext.dir = false;
                }
    
                DISP_Cylon(dispContext.currColor);
      
                // Advance Index (false is incr, true is decr)
                dispContext.index += (dispContext.dir) ? (-1) : (1);

                dispContext.alternate = true;
            } else {
                dispContext.alternate = false;
            }
            break;
        
        default:
            dispContext.state = DISP_STATE_OFF;
            break;
    }
    
    if (dispContext.redraw) {
        dispContext.redraw = false;
        FastLED.show();
    }
}

/**
 * Advances the color of static color states
 */
void DISP_NextColor(void) {
    // Unless it's a solic color state, return
    switch(dispContext.state) {
        case DISP_STATE_SMILEY:
        case DISP_STATE_CYLON:
            break;
        default:
            return;
    }
    
    switch (dispContext.currColor.as_uint32_t()) {
        case 0xFF800080:
            dispContext.currColor = CRGB::Red;
            DebugPrintln("Color: RED");
            break;

        case 0xFFFF0000:
            dispContext.currColor = CRGB::Yellow;
            DebugPrintln("Color: YELLOW");
            break;

        case 0xFFFFFF00:
            dispContext.currColor = CRGB::Green;
            DebugPrintln("Color: GREEN");
            break;

        case 0xFF008000:
            dispContext.currColor = CRGB::Blue;
            DebugPrintln("Color: BLUE");
            break;

        case 0xFF0000FF:
            dispContext.currColor = CRGB::Purple;
            DebugPrintln("Color: PURPLE");
            break;

        default:
            break;
    }
    
    dispContext.redraw = true;
}

/**
 * Advances the pattern (of active patterns, cannot go to off
 */
void DISP_NextPattern(void) {
    // Cycle: Off -> Smiley -> Wheel (-> More) -> Smiley
    DISP_Clear();
    switch(dispContext.state) {
        case DISP_STATE_OFF:
            dispContext.state = DISP_STATE_WHEEL;
            break;
            
        case DISP_STATE_WHEEL:
            dispContext.state = DISP_STATE_SMILEY;
            break;
            
        case DISP_STATE_SMILEY:
            dispContext.state = DISP_STATE_CYLON;
            break;
            
        case DISP_STATE_CYLON:
            dispContext.state = DISP_STATE_WHEEL;
            break;
            
        default:
            dispContext.state = DISP_STATE_OFF;
            break;
    }
    // Set redraw when changing patterns
    dispContext.redraw = true;
    printState();
}

/**
 * Clears and Turns off the Display
 * Future HW TODO: Add FET to disable LED Power
 */
void DISP_Off(void) {
    DISP_Clear();
    dispContext.state = DISP_STATE_OFF;
    printState();
    dispContext.redraw = true;
}

/**
 * Local State Print helper
 */
static void printState(void) {
    const static String stateLabels[DISP_STATE_MAX] = {"OFF", "WHEEL", "SMILEY", "CYLON"};
    DebugPrint("State: ");
    DebugPrintln(stateLabels[dispContext.state]);
}

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
static void DISP_ColorWheel(uint_fast16_t wheelPos) {
    // Pre-allocate pos data pointer
    const uint_fast16_t* posData;
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
static void DISP_SmileyFace(CRGB color) {
    for (uint_fast8_t i = 0; i < SMILEY_FACE_NUM_PIXELS; i++) {
        leds[smileyFacePixels[i]] = color;
    }
}

/**
 * Clears the frame buffer
 */
static void DISP_Clear(void) {
    for (uint_fast8_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}

/**
 * Draws a the next frame of the Cylon image using the color
 * @param CRGB color - The color to draw
 */
static void DISP_Cylon(CRGB color) {
    // Scale current display
    for(uint8_t i = 0; i < NUM_LEDS; i++) { 
        leds[i].nscale8(200); 
    }
    
    // Set next pixel
    leds[dispContext.index] = color;
}
