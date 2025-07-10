/**
 * @file        Small_Pendant.ino
 * @module      The Main (Small_Pendant) Module
 *
 * @brief       Contains the Main code for the Small Pendant Project (Init and Task Dispatching)
 *
 * @author      Matthew Haahr (mjhaahr)
 */
#include "Config.hpp"
#include "Util.hpp"
#include "Buttons.hpp"
#include "Display.hpp"

void setup() {
    BTN_Init();
    DISP_Init();

    Serial.begin(57600);
    Serial.println("Start");
}

void loop() {
    BTN_Task();
    DISP_Task();
    // TODO: implement manual systick generation (use a goddamn timer to implement it and add a callback to set a flag, maybe add delay(1)))
    // https://docs.espressif.com/projects/arduino-esp32/en/latest/api/timer.html
    delay(10);
}
