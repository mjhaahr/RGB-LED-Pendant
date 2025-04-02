#include "Arduino.h"

extern "C" void initVariant(void) {
  // Stop LEDs floating
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
