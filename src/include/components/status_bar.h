#ifndef STATUS_BAR_H
#define STATUS_BAR_H

/**
 * Draws the status bar on the EPD display.
 *
 * @param function A function pointer to a callback function 
 * that will be executed when the button exiting the current 
 * screen is pressed.
 */
void epd_draw_status_bar(void (*function)());

#endif // STATUS_BAR_H