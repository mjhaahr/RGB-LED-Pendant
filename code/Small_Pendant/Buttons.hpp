/**
 * @file        Buttons.hpp
 * @module      The Buttons Module (BTN)
 *
 * @brief       Contains Code for Interacting with the Buttons on the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "Config.hpp"
#include "Button.hpp"

/**
 * Initializes the Buttons Module
 */
void BTN_Init(void);

/**
 * Handles Running the two buttons and updating the display with the result
 */
void BTN_Task(void);

#endif /* __BUTTONS_H__ */
