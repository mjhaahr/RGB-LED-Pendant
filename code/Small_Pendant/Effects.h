/**
 * @file        Effects.h
 * @module      The Effects Module (FX)
 *
 * @brief       Contains Code for Running Effects on LED Matrix of the Small Pendant Project
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#ifndef __EFFECTS_H__
#define __EFFECTS_H__

#include "Config.h"

/**
 * Loads the color wheel into the frame buffer (needs to be actually drawn to the screen), given a wheel position
 * @param uint_fast16_t wheelPos - The wheel position in tenths of a degree
 */
void FX_ColorWheel(uint_fast16_t wheelPos);

#endif /* __EFFECTS_H__ */
