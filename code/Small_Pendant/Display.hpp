/**
 * @file        Display.hpp
 * @module      The Display Module (DISP)
 *
 * @brief       Contains Code for Running Effects on LED Matrix of the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Config.hpp"

/**
 * Initializes the Display Module and sets up the LEDs
 */
void DISP_Init(void);

/**
 * Runs the Primary Display Task, responsible for controlling what's shown on the LEDs
 */
void DISP_Task(void);

/**
 * Advances the color of static color states
 */
void DISP_NextColor(void);

/**
 * Advances the pattern (of active patterns, cannot go to off
 */
void DISP_NextPattern(void);

/**
 * Clears and Turns off the Display
 * Futur HW TODO: Add FET to disable LED Power
 */
void DISP_Off(void);

#endif /* __DISPLAY_H__ */
