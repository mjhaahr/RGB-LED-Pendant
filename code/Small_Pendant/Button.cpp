/**
 * @file        Button.cpp
 * @module      The Button Class (BTN)
 *
 * @brief       Contains Code for Managing a Single Button Instance on the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Button.hpp"

#define BTN_DEBOUNCE_TIME_MS        25u
#define BTN_DEBOUNCE_TIME_TICKS     (BTN_DEBOUNCE_TIME_MS / SYSTICK_PERIOD_MS)

#define BTN_HELD_TIME_MS            500u
#define BTN_HELD_TIME_TICKS         (BTN_HELD_TIME_MS / SYSTICK_PERIOD_MS)

/**
 * Initializes a Button Object
 * @param uint8_t pin - The GPIO Pin for the Button
 */
void Button::init(uint8_t pin) {
    this->pin = pin;

    this->currentState = BTN_STATE_IDLE;

    this->pinState = GPIO_BUTTON_UNPRESSED;
    this->lastPinState = GPIO_BUTTON_UNPRESSED;

    this->debounceTicks = 0;
}

/**
 * Performs the debounce handle and evaluates the button
 * @return BTN_ButtonState - The current state of the button
 */
BTN_ButtonState Button::task(void) {
    // Increment tick timer (up to max val)
    if (this->debounceTicks < UINT8_MAX) {
        this->debounceTicks++;
    }

    int newPin = digitalRead(this->pin);

    if (newPin != this->lastPinState) {
        // If the state changes, reset the debounce timer
        this->debounceTicks = 0;
    } else if (this->debounceTicks >= BTN_HELD_TIME_TICKS) {
        // if state is the same AND the timer is greater than the held time, eval for hold
        if (newPin == GPIO_BUTTON_PRESSED) {
            this->currentState = BTN_STATE_HELD;
        }
    } else if (this->debounceTicks >= BTN_DEBOUNCE_TIME_TICKS) {
        // If state is the same AND the timer is greater than the debounce check, eval the button
        if (newPin == GPIO_BUTTON_UNPRESSED) {
            // Button Released
            if (this->currentState == BTN_STATE_IDLE) {
                // If Button was PRESSED, then released -> PRESSED
                this->currentState = BTN_STATE_PRESSED;
            }
        } else {
            // Button pressed, force to IDLE state
            this->currentState = BTN_STATE_IDLE;
        }
    }

    this->lastPinState = newPin;

    return this->currentState;
}

/**
 * Gets and clears the current button state
 * @return BTN_ButtonState - The current state of the button
 */
BTN_ButtonState Button::getState(void) {
    // Copy -> Clear -> Return
    BTN_ButtonState out = this->currentState;
    this->currentState = BTN_STATE_IDLE;
    return out;
}
