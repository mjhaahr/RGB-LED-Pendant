/**
 * @file        Button.cpp
 * @module      The Button Class (BTN)
 *
 * @brief       Contains Code for Managing a Single Button Instance on the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Button.hpp"

#define BTN_DEBOUNCE_TIME_MS        100u
#define BTN_DEBOUNCE_TIME_TICKS     (BTN_DEBOUNCE_TIME_MS / UI_UPDATE_PERIOD_MS)

#define BTN_HELD_TIME_MS            1000u
#define BTN_HELD_TIME_TICKS         (BTN_HELD_TIME_MS / UI_UPDATE_PERIOD_MS)

/**
 * Initializes a Button Object
 * @param uint8_t pin - The GPIO Pin for the Button
 * @param bool holdEn - True if HELD is a valid state
 */
void Button::init(uint8_t pin, bool holdEn) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);

    this->holdEn = holdEn;

    this->currentState = BTN_STATE_IDLE;
    this->newData = false;

    this->pinState = GPIO_BUTTON_UNPRESSED;
    this->lastPinState = GPIO_BUTTON_UNPRESSED;
    
    this->buttonState = GPIO_BUTTON_UNPRESSED;
    this->lastButton = GPIO_BUTTON_UNPRESSED;

    this->debounceTicks = 0;
}

/**
 * Performs the debounce handle and evaluates the button
 * @return BTN_ButtonState_e - The current state of the button
 */
BTN_ButtonState_e Button::task(void) {
    // Increment tick timer (up to max val)
    if (this->debounceTicks < UINT8_MAX) {
        this->debounceTicks++;
    }

    int newPin = digitalRead(this->pin);

    // Debounce the button
    if (newPin != this->lastPinState) {
        // If the state changes, reset the debounce timer
        this->debounceTicks = 0;
    } else if (this->debounceTicks >= BTN_DEBOUNCE_TIME_TICKS) {
        this->buttonState = newPin;
    }
    
    // Handle the Button Logic
    switch (this->currentState) {
        case BTN_STATE_IDLE:
            // Check if pressed
            if (this->buttonState == GPIO_BUTTON_PRESSED) {
                // Check if held for long enough to be "HELD" (and hold is allowed)
                if ((this->debounceTicks >= BTN_HELD_TIME_TICKS) && this->holdEn) {
                    this->newData = true;
                    this->currentState = BTN_STATE_HELD;
                }
            } else {
                // If released, switch to "PRESSED"
                if (this->lastButton == GPIO_BUTTON_PRESSED) {
                    this->newData = true;
                    this->currentState = BTN_STATE_PRESSED;
                }
            }
            break;
            
        case BTN_STATE_HELD:
            // Wait for it to be released (and switch to "IDLE")
            if (this->buttonState == GPIO_BUTTON_UNPRESSED) {
                this->newData = true;
                this->currentState = BTN_STATE_IDLE;
            }
            break;
            
        case BTN_STATE_PRESSED:
            // Once Pressed, clear to "IDLE"
            this->newData = true;
            this->currentState = BTN_STATE_IDLE;
            break;
    }

    this->lastPinState = newPin;
    this->lastButton = this->buttonState;
    return this->currentState;
}

/**
 * Gets the current button state
 * @return BTN_ButtonState_e - The current state of the button
 */
BTN_ButtonState_e Button::getState(void) {
    return this->currentState;
}

/**
 * Gets and clears if there is new data
 * @return bool - True if new state data is available
 */
bool Button::NewData(void) {
    bool out = this->newData;
    this->newData = false;
    return out;
}
