#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H

// ----------------------------
// External libraries
// ----------------------------
#include <touch.h>

/**
 * @brief Indicates whether an overlay is currently active.
 * 
 * An overlay is a graphical element that is displayed on top of the main UI.
 * This variable is typically used in conjunction with touch event handlers
 * to determine whether touch events should be processed by the overlay or by the
 * main UI. When an overlay is active, automatic updates within main framebuffer
 * should not be made.
 * 
 * @see SomeOtherRelatedFunction()
 */
extern bool overlayActive;

/**
 * @brief Sets up the touch functionality.
 * 
 * This function initializes the touch layer and returns an instance of the TouchClass
 * used to communicate with the touch layer.
 * 
 * @return An instance of the TouchClass used to communicate with the touch layer.
 */
TouchClass touchSetup();

/**
 * @brief Adds a touch point with the specified coordinates, size, and callback function.
 * 
 * This function adds a touch point to the touch layer with the specified area and callback function.
 * The callback function will be executed when the touch point is pressed.
 * 
 * @param area The area of the touch point.
 * @param function The callback function to be executed when the touch point is pressed.
 */
void addTouchPoint(Rect_t area, void (*function)());

/**
 * @brief Clears all stored touch points.
 * 
 * This function clears all the touch points that have been added to the touch layer.
 * It should be called each time before drawing new UI elements to the display.
 */
void clearTouchPoints();

/**
 * @brief Sets the state of the overlay.
 * 
 * This function sets the state of the overlay, indicating whether it is active or not.
 * 
 * @param state The state of the overlay (true for active, false for inactive).
 */
void setOverlayActive(bool state);

/**
 * @brief Adds a touch point to the overlay with the specified coordinates, size, and callback function.
 * 
 * This function adds a touch point to the overlay with the specified area and callback function.
 * The callback function will be executed when the touch point is pressed.
 * 
 * @param area The area of the touch point.
 * @param function The callback function to be executed when the touch point is pressed.
 */
void addOverlayTouchPoint(Rect_t area, void (*function)());

/**
 * @brief Clears all stored touch points in the overlay.
 * 
 * This function clears all the touch points that have been added to the overlay.
 * It should be called each time before drawing new UI elements to the overlay.
 */
void clearOverlayTouchPoints();

/**
 * @brief A dummy function.
 * 
 * This function does nothing and can be used as a placeholder or for testing purposes.
 */
void dummyFunction();

#endif // TOUCH_HANDLER_H
