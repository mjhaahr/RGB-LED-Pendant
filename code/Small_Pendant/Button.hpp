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
} BTN_ButtonState;

class Button {
    private:
        // The GPIO Pin Number Associated with the Button
        uint8_t pin;

        // Button State doesn't get established until released (if pressed) or held
        BTN_ButtonState currentState;

        // Reflects the current state tracking for the pin itself
        int pinState;
        int lastPinState;

        // Debounce tick timer
        uint8_t debounceTicks;

    public:
        /**
         * Initializes a Button Object
         * @param uint8_t pin - The GPIO Pin for the Button
         */
        void init(uint8_t pin);

        /**
         * Performs the debounce handle and evaluates the button
         * @return BTN_ButtonState - The current state of the button
         */
        BTN_ButtonState task(void);

        /**
         * Gets and clears the current button state
         * @return BTN_ButtonState - The current state of the button
         */
        BTN_ButtonState getState(void);
};

#endif /* __BUTTON_H__ */
