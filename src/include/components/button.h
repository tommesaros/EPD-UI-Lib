#ifndef BUTTON_H
#define BUTTON_H

/**
 * Draws a circular button with a label.
 * When bgColor = white, a black border is drawn around the button.
 * 
 * @param buttonText The text to be displayed on the button.
 * @param font The font to be used for the label.
 * @param x The x position of the center of the circle.
 * @param y The y position of the center of the circle.
 * @param radius The radius of the circle.
 * @param color The color of the circle (15 is white, 0 is black).
 * @param textColor The color of the label (15 is white, 0 is black).
 * @param framebuffer The framebuffer to draw on.
 * @param function The function to be called when the button is pressed.
 */
void epd_draw_circle_button(
    char* buttonText, 
    const GFXfont *font,
    int32_t x,
    int32_t y,
    int32_t radius,
    uint8_t color,
    uint8_t textColor,
    uint8_t *framebuffer,
    void (*function)()
);

/**
 * Draws a circular button with an icon.
 * When bgColor = white, a black border is drawn around the button.
 * 
 * @param image_data The image data of the icon.
 * @param image_width The width of the icon.
 * @param image_height The height of the icon.
 * @param x The x position of the center of the circle.
 * @param y The y position of the center of the circle.
 * @param radius The radius of the circle.
 * @param bgColor The background color of the button.
 * @param framebuffer The framebuffer to draw on.
 * @param function The function to be called when the button is pressed.
 */
void epd_draw_circle_button_icon(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    int32_t x,
    int32_t y,
    int32_t radius,
    uint8_t bgColor,
    uint8_t *framebuffer,
    void (*function)()
);

/**
 * Draws a tertiary button with an icon.
 * 
 * @param image_data The image data of the icon.
 * @param image_width The width of the icon.
 * @param image_height The height of the icon.
 * @param label The label to be displayed on the button.
 * @param font The font to be used for the label.
 * @param x The x position of the button.
 * @param y The y position of the button.
 * @param bgColor The background color of the button.
 * @param textColor The color of the label (15 is white, 0 is black).
 * @param drawMode The draw mode of the button.
 * @param framebuffer The framebuffer to draw on.
 * @param function The function to be called when the button is pressed.
 */
void epd_draw_tertiary_button_icon(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char* label,
    const GFXfont *font,
    int32_t x,
    int32_t y,
    uint8_t bgColor,
    uint8_t textColor,
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

/**
 * Draws a button with an icon.
 * When bgColor = white, a black border is drawn around the button.
 * 
 * @param image_data The image data of the icon.
 * @param image_width The width of the icon.
 * @param image_height The height of the icon.
 * @param label The label to be displayed on the button.
 * @param font The font to be used for the label.
 * @param rectArea The rectangular area of the button.
 * @param radius The radius of the button.
 * @param bgColor The background color of the button.
 * @param textColor The color of the label (15 is white, 0 is black).
 * @param drawMode The draw mode of the button.
 * @param framebuffer The framebuffer to draw on.
 * @param function The function to be called when the button is pressed.
 */
void epd_draw_button_icon(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    char* label,
    const GFXfont *font,
    Rect_t rectArea,
    int32_t radius,
    uint8_t bgColor,
    uint8_t textColor,
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

/**
 * Draws a button with a label.
 * When bgColor = white, a black border is drawn around the button.
 * 
 * @param label The label to be displayed on the button.
 * @param font The font to be used for the label.
 * @param rectArea The rectangular area of the button.
 * @param radius The radius of the button.
 * @param bgColor The background color of the button.
 * @param textColor The color of the label (15 is white, 0 is black).
 * @param drawMode The draw mode of the button.
 * @param framebuffer The framebuffer to draw on.
 * @param function The function to be called when the button is pressed.
 */
void epd_draw_button(
    char* label,
    const GFXfont *font,
    Rect_t rectArea,
    int32_t radius,
    uint8_t bgColor,
    uint8_t textColor,
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

#endif // BUTTON_H