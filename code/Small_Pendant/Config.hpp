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

#define DEBUG

// System Update
#define SYSTICK_PERIOD_US           2000u
#define SYSTICK_FREQ                (1000000u / SYSTICK_PERIOD_US)

// Update UI (Buttons and Display) after a certain number of Sys Ticks
#define UI_UPDATE_PERIOD_MS         10u
#define UI_UPDATE_INT               (UI_UPDATE_PERIOD_MS * (1000u / SYSTICK_PERIOD_US))

// Pin Defines
#define LED_PIN                     8u
#define BOOT_COLOR_BUTTON_PIN       9u
#define USER_PATTERN_BUTTON_PIN     0u

#define GPIO_BUTTON_PRESSED         LOW
#define GPIO_BUTTON_UNPRESSED       HIGH

// LED Setup
#define NUM_LEDS                    177u
#define MAX_BRIGHTNESS              12u

#ifdef DEBUG
    #define DebugBegin(...) Serial.begin(__VA_ARGS__);
    #define DebugPrint(...) Serial.print(__VA_ARGS__);
    #define DebugPrintln(...) Serial.println(__VA_ARGS__);
    #define DebugWrite(...) Serial.write(__VA_ARGS__);
#else
    #define DebugBegin(...)
    #define DebugPrint(...)
    #define DebugPrintln(...)
    #define DebugWrite(...)
#endif

#endif /* __CONFIG_H__ */
