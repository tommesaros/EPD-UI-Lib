#ifndef FRAMEBUFFER_HANDLER_H
#define FRAMEBUFFER_HANDLER_H

/**
 * @brief Sets up all framebuffers for the UI components.
 * 
 * This function initializes the framebuffer and prepares it for use with the EPD UI library.
 * It should be called before any other functions from the library are used.
 */
void framebufferSetup();

/**
 * @brief Cleans the specified area of the framebuffer and refreshes the are on the EPD.
 *
 * This function clears the specified area of the framebuffer 
 * by setting all the pixels within the area to 0.
 *
 * @param framebuffer Pointer to the framebuffer.
 * @param area The area to be cleaned.
 */
void cleanFramebufferAndEPD(uint8_t *framebuffer, Rect_t area);

/**
 * @brief Retrieves the main framebuffer.
 *
 * This function returns a pointer to the main framebuffer, which is a uint8_t array, 
 * each number representing a color of a single pixel. The main framebuffer is used 
 * for storing a graphical representation of a display state.
 *
 * @return A pointer to the main framebuffer.
 */
uint8_t* getMainFramebuffer();

/**
 * @brief Retrieves the notification framebuffer.
 *
 * This function returns a pointer to the notification framebuffer, which is a uint8_t array,
 * each number representing a color of a single pixel. The notification framebuffer is used 
 * for storing a graphical representation of a notification toast.
 *
 * @return Pointer to the notification framebuffer.
 */
uint8_t* getNotificationFramebuffer();

/**
 * @brief Retrieves the framebuffer for the popup window.
 *
 * This function returns a pointer to the popup framebuffer, which is a uint8_t array,
 * each number representing a color of a single pixel. The popup framebuffer is used 
 * for storing a graphical representation of a popup, allowing the user to later,
 * after the popup closes, restore the contents of a main framebuffer.
 *
 * @return A pointer to the popup framebuffer.
 */
uint8_t* getOverlayFramebuffer();

#endif // FRAMEBUFFER_HANDLER_H
