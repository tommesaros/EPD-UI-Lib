#ifndef EPD_HANDLER_H
#define EPD_HANDLER_H

/**
 * @brief The maximum number of quick refreshes supported by the EPD handler.
 *
 * This constant represents the maximum number of quick refreshes that can be performed
 * by the EPD handler. Quick refresh is a feature of the EPD (Electronic Paper Display)
 * technology that allows for faster screen updates by only refreshing the parts of the
 * screen that have changed. It is much less disturbing to the user than a full refresh, 
 * however it can cause ghosting if used too frequently.
 *
 * @note The value of this constant may vary depending on the specific EPD hardware being used.
 */
extern const int EPD_MAX_QUICK_REFRESHES;

/**
 * @brief Sets up the EPD (Electronic Paper Display).
 * 
 * This function initializes the communication with the Electronic Paper Display.
 */
void epdSetup();

/**
 * Draws a rounded rectangle with filled background.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rounded rectangle.
 * @param height The height of the rounded rectangle.
 * @param radius The radius of the rounded corners.
 * @param color The color to fill the rounded rectangle with. 
 *              (range 0-255, needs to be converted from 0-15 with epd_convert_font_color)
 * @param framebuffer The framebuffer to draw on. (NULL for instant drawing)
 */
void epd_fill_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);

/**
 * Draws a rounded rectangle with transparent background.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param radius The radius of the rounded corners.
 * @param color The color of the rectangle.
 *              (range 0-255, needs to be converted from 0-15 with epd_convert_font_color)
 * @param framebuffer The framebuffer to draw on. (NULL for instant drawing)
 */
void epd_draw_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);

/**
 * @brief Puts the EPD into sleep mode.
 * 
 * This function puts the EPD into sleep mode, when the EPD consumes no power
 * and is ready to be woken up by a button at the top of the device.
 * 
 * @note This function assumes that the EPD has been properly initialized before calling it.
 * @see epd_init
 */
void epd_sleep();

/**
 * @brief Clears the specified area on the EPD display quickly.
 *
 * This function clears the specified area on the EPD by setting all pixels within 
 * the area to white or black, depending on the value of the `white` parameter.
 * In order to prevent any damage to the display, this clearing method cannot be used
 * instead of proper epd_clear_area function. This serves as a quick way to change 
 * the contents of a small area of the display. After approximately 20 quick clears,
 * you should perform a full clear using the epd_clear_area function. Otherwise, 
 * a ghost image may remain on the display.
 *
 * @param area The rectangular area to be cleared on the EPD display.
 * @param white If `true`, the pixels will be set to white, false = black.
 */
void epd_clear_area_quick(Rect_t area, bool white);

/**
 * @brief Creates a new screen on the EPD display.
 *
 * This function sets up a cleam new screen by clearing the framebuffer
 * and all touch points. The `exitFunction` parameter is a callback function 
 * that will be called when the screen is exited.
 *
 * @param framebuffer Pointer to the framebuffer for the new screen.
 * @param exitFunction Callback function to be called when the screen is exited.
 */
void epd_new_screen(uint8_t *framebuffer, void (*exitFunction)());

/**
 * @brief Draws the main framebuffer on the EPD display.
 * 
 * This function draws contents of the main framebuffer on the EPD display. 
 * Use this function instead of epd_draw_grayscale_image from epd_driver.h 
 * to prevent pararell drawing two distinct framebuffers in the same time 
 * which results in ghosting.
 */
void epd_draw_main_framebuffer();

/**
 * @brief Draws the overlay framebuffer on the EPD display.
 * 
 * This function draws contents of the overlay framebuffer on the EPD display. 
 * Use this function instead of epd_draw_grayscale_image from epd_driver.h 
 * to prevent pararell drawing two distinct framebuffers in the same time 
 * which results in ghosting.
 */
void epd_draw_overlay_framebuffer();

#endif // EPD_HANDLER_H
