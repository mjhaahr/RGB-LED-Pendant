/**
 * @file        Config.h
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
#define UPDATE_RATE                 100u
#define UPDATE_PERIOD               (1000u / UPDATE_RATE)

// Pin Defines
#define LED_PIN                     8u
#define BOOT_COLOR_BUTTON_PIN       9u
#define USER_PATTERN_BUTTON_PIN     0u

// LED Setup
#define NUM_LEDS                    177u
#define MAX_BRIGHTNESS              15u

#endif /* __CONFIG_H__ */
