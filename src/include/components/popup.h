#ifndef POPUP_H
#define POPUP_H

/**
 * Clears the popup from the display.
 */
void epd_clear_popup();

/**
 * @brief Triggers the display of a popup with the specified parameters.
 * 
 * Before calling this function, the EPD screen and overlay touch points
 * should be cleared. Use theese functions:
 * // epd_clear();
 * // setOverlayActive(true);
 * // clearOverlayTouchPoints();
 * In a popup, there should be a button that will call epd_clear_popup() function
 * to exit the popup.
 * 
 * @param imageData The image data to be displayed in the popup.
 * @param imageWidth The width of the image.
 * @param imageHeight The height of the image.
 * @param title The title of the popup.
 * @param text The text content of the popup.
 * @param primaryButtonIconData The image data for the primary button icon.
 * @param primaryButtonIconWidth The width of the primary button icon.
 * @param primaryButtonIconHeight The height of the primary button icon.
 * @param primaryButtonLabel The label for the primary button.
 * @param primaryFunction The function to be called when the primary button is pressed.
 * @param secondaryButtonIconData The image data for the secondary button icon.
 * @param secondaryButtonIconWidth The width of the secondary button icon.
 * @param secondaryButtonIconHeight The height of the secondary button icon.
 * @param secondaryButtonLabel The label for the secondary button.
 * @param secondaryFunction The function to be called when the secondary button is pressed.
 */
void epd_trigger_popup(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char *title, 
    const char *text, 
    uint8_t *primaryButtonIconData,
    int32_t primaryButtonIconWidth,
    int32_t primaryButtonIconHeight,
    const char *primaryButtonLabel, 
    void (*primaryFunction)(),
    uint8_t *secondaryButtonIconData,
    int32_t secondaryButtonIconWidth,
    int32_t secondaryButtonIconHeight,
    const char *secondaryButtonLabel, 
    void (*secondaryFunction)()
);

#endif // POPUP_H