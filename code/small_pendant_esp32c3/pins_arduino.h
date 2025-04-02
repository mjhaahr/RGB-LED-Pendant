#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

static const uint8_t LED_BUILTIN = 1;
#define BUILTIN_LED LED_BUILTIN  // backward compatibility
#define LED_BUILTIN LED_BUILTIN  // allow testing #ifdef LED_BUILTIN

static const uint8_t TX = 21;
static const uint8_t RX = 20;

static const uint8_t SDA = 2;
static const uint8_t SCL = 3;

#endif /* Pins_Arduino_h */
