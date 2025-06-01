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

void DISP_NextColor(void);

void DISP_NextPattern(void);

void DISP_Off(void);

/**
 * Initializes the Display Module and sets up the LEDs
 */
void DISP_Init(void);

/**
 * Runs the Primary Display Task, responsible for controlling what's shown on the LEDs
 */
void DISP_Task(void);

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
void DISP_ColorWheel(uint_fast16_t wheelPos);

/**
 * Draws a Simple Smiley Face to the frame buffer
 * @param CRGB color - The color to draw
 */
void DISP_SmileyFace(CRGB color);

/**
 * Clears the frame buffer
 */
void DISP_Clear(void);

#endif /* __DISPLAY_H__ */
