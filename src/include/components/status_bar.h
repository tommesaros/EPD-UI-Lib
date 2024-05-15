#ifndef STATUS_BAR_H
#define STATUS_BAR_H

/**
 * @brief A handle to a FreeRTOS task.
 *
 * The `TaskHandle_t` type is used to represent a handle to a FreeRTOS task.
 * It is used to reference and manipulate tasks in the FreeRTOS operating system.
 * This handle can be used to perform operations such as suspending, resuming,
 * deleting, or querying the state of a task.
 */
extern TaskHandle_t updateTimeStatusBarHandle;

/**
 * Draws the status bar on the EPD display.
 *
 * @param function A function pointer to a callback function 
 * that will be executed when the button exiting the current 
 * screen is pressed.
 */
void epd_draw_status_bar(void (*function)());

#endif // STATUS_BAR_H