#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H

#include <touch.h>

/**
 * Sets up the touch functionality.
 * @return An instance of the TouchClass used to communicate with the touch layer.
 */
TouchClass TouchSetup();

/**
 * Adds a touch point with the specified coordinates, size, and callback function.
 * @param area The area of the touch point.
 * @param function The callback function to be executed when the touch point is pressed.
 */
void AddTouchPoint(Rect_t area, void (*function)());

/**
 * Clears all stored touch points. This function should be called each time
 * before drawing new UI elements to the display. 
 */
void ClearTouchPoints();

void dummyFunction();

#endif // TOUCH_HANDLER_H
