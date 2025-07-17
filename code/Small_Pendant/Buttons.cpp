/**
 * @file        Buttons.cpp
 * @module      The Buttons Module (BTN)
 *
 * @brief       Contains Code for Interacting with the Buttons on the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Buttons.hpp"
#include "Display.hpp"

static Button colorButton;
static Button patternButton;

/**
 * Initializes the Buttons Module
 */
void BTN_Init(void) {
    colorButton.init(BOOT_COLOR_BUTTON_PIN, false);
    patternButton.init(USER_PATTERN_BUTTON_PIN, true);
}

/**
 * Handles Running the two buttons and updating the display with the result
 */
void BTN_Task(void) {
    colorButton.task();
    patternButton.task();

    if (colorButton.NewData()) {
        switch(colorButton.getState()) {
            case BTN_STATE_PRESSED:
                DISP_NextColor();
                break;

            default:
                // Do Nothing Under otherwise
                break;
        }
    }

    if (patternButton.NewData()) {
        switch(patternButton.getState()) {
            case BTN_STATE_PRESSED:
                DISP_NextPattern();
                break;

            case BTN_STATE_HELD:
                DISP_Off();
                break;

            default:
                // Do Nothing Under otherwise
                break;
        }
    }
}
