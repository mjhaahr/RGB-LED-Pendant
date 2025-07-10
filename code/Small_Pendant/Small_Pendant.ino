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

hw_timer_t *taskTimer = NULL;
volatile SemaphoreHandle_t taskSemaphore;
static uint8_t dispayUpdateTicks;

void ARDUINO_ISR_ATTR taskStart() {
	xSemaphoreGiveFromISR(taskSemaphore, NULL);
}

void setup() {
    BTN_Init();
    DISP_Init();

    DebugBegin(57600);
    DebugPrintln("Start");

    // Create semaphore to flag when timer has fired
  	taskSemaphore = xSemaphoreCreateBinary();
  	
  	// Set timer frequency to 1Mhz
    taskTimer = timerBegin(1000000);
    
    // Attach taskStart ISR to task timer.
    timerAttachInterrupt(taskTimer, &taskStart);
    
    // Set timer alarm to call taskStart ISR every 5 milliseconds.
    // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
    timerAlarm(taskTimer, SYSTICK_PERIOD_US, true, 0);
    
    // Start Display Update Tracking at 0
    dispayUpdateTicks = 0;
}

void loop() {
    // If Task Timer has fired
    if (xSemaphoreTake(taskSemaphore, 0) == pdTRUE) {
        // Increment display update check (runs every DISPLAY_UPDATE_INT ticks)
        if (++dispayUpdateTicks <= DISPLAY_UPDATE_INT) {
            dispayUpdateTicks = 0;
            // Check buttons
            BTN_Task();
            // Update display
            DISP_Task();
        }
    }
}
