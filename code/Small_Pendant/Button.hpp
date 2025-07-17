/**
 * @file        Button.hpp
 * @module      The Button Class (BTN)
 *
 * @brief       Contains Code for Managing a Single Button Instance on the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Config.hpp"

// enum used to hold the state of a button, whether it's currently pressed, held, or idle
typedef enum {
    BTN_STATE_IDLE,
    BTN_STATE_PRESSED,
    BTN_STATE_HELD,
} BTN_ButtonState_e;

class Button {
    private:
        // The GPIO Pin Number Associated with the Button
        uint8_t pin;
        // True if holding is a separate option
        bool holdEn;

        // Button State doesn't get established until released (if pressed) or held
        BTN_ButtonState_e currentState;
        // New Data Flag
        bool newData;

        // Reflects the current state tracking for the pin itself
        int pinState;
        int lastPinState;
        
        // Debounced state of the button (pressed or unpressed)
        int buttonState;
        int lastButton;

        // Debounce tick timer
        uint8_t debounceTicks;

    public:
        /**
         * Initializes a Button Object
         * @param uint8_t pin - The GPIO Pin for the Button
         * @param bool holdEn - True if HELD is a valid state
         */
        void init(uint8_t pin, bool holdEn);

        /**
         * Performs the debounce handle and evaluates the button
         * @return BTN_ButtonState_e - The current state of the button
         */
        BTN_ButtonState_e task(void);

        /**
         * Gets the current button state
         * @return BTN_ButtonState_e - The current state of the button
         */
        BTN_ButtonState_e getState(void);
        
        /**
         * Gets and clears if there is new data
         * @return bool - True if new state data is available
         */
        bool NewData(void);
};

#endif /* __BUTTON_H__ */
