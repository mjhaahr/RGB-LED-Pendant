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

void ARDUINO_ISR_ATTR taskStart() {
	xSemaphoreGiveFromISR(taskSemaphore, NULL);
}

void setup() {
    BTN_Init();
    DISP_Init();

    // TODO: Setup IMU and add the calibration getter here
    // TODO: Do something with LED BUILTIN

    DebugBegin(57600);
    DebugPrintln("Start");

    // Create semaphore to flag when timer has fired
  	taskSemaphore = xSemaphoreCreateBinary();
  	
  	// Set timer frequency to 1Mhz
    taskTimer = timerBegin(1000000);
    
    // Attach taskStart ISR to task timer.
    timerAttachInterrupt(taskTimer, &taskStart);
    
    // Set task timer alarm to call taskStart ISR with the SysTick Period
    // Repeat the alarm (3rd param = true) with unlimited count (4th param = 0).
    timerAlarm(taskTimer, SYSTICK_PERIOD_US, true, 0);
}

void loop() {
    // Start UI Update Tracking at 0
    static uint8_t uiUpdateTicks = 0;
    
    // If Task Timer has fired
    if (xSemaphoreTake(taskSemaphore, 0) == pdTRUE) {
        // Increment display update check (runs every UI_UPDATE_INT ticks)
        if (++uiUpdateTicks >= UI_UPDATE_INT) {
            uiUpdateTicks = 0;
            // Check buttons
            BTN_Task();
            // Update display
            DISP_Task();
        } else {
          // Redraw the current display otherwise to update temporal dithering
          // DISP_Redraw();
        }
    }
}
