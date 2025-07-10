/**
 * @file        Config.hpp
 * @module      The Configuration Module (CFG)
 *
 * @brief       Contains General Configuration Code for the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>
#include <FastLED.h>

// System Update
#define SYSTICK_PERIOD_MS           5u
#define SYSTICK_FREQ                (1000 / SYSTICK_PERIOD_MS)
// Update Display Every x Ticks
#define DISPLAY_UPDATE_INT          2u

// Pin Defines
#define LED_PIN                     8u
#define BOOT_COLOR_BUTTON_PIN       9u
#define USER_PATTERN_BUTTON_PIN     0u

#define GPIO_BUTTON_PRESSED         LOW
#define GPIO_BUTTON_UNPRESSED       HIGH

// LED Setup
#define NUM_LEDS                    177u
#define MAX_BRIGHTNESS              15u

// TODO: Setup Debug Enable for Printing

#endif /* __CONFIG_H__ */
