#ifndef CARD_H
#define CARD_H

/**
 * Draws a horizontal card on the EPD display.
 *
 * @param image_data The pointer to the image data.
 * @param image_width The width of the image.
 * @param image_height The height of the image.
 * @param primaryLabel The primary label text to be displayed on the card.
 * @param secondaryLabel The secondary label text to be displayed on the card.
 * @param primaryFont The font to be used for the primary label.
 * @param secondaryFont The font to be used for the secondary label.
 * @param rectArea The rectangular area where the card will be drawn.
 * @param radius The radius of the card's corners.
 * @param bgColor The background color of the card.
 * @param textColor The text color of the labels.
 * @param drawMode The drawing mode for the card.
 * @param framebuffer The pointer to the framebuffer.
 * @param function The function to be called when the card is interacted with.
 */
void epd_draw_horizontal_card(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char *primaryLabel, 
    const char *secondaryLabel, 
    const GFXfont *primaryFont,
    const GFXfont *secondaryFont,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

/**
 * Draws a vertical card on the EPD display.
 *
 * @param image_data Pointer to the image data.
 * @param image_width Width of the image.
 * @param image_height Height of the image.
 * @param label The label to be displayed on the card.
 * @param font The font to be used for the label.
 * @param rectArea The rectangular area where the card will be drawn.
 * @param radius The radius of the card's corners.
 * @param bgColor The background color of the card.
 * @param textColor The text color of the label.
 * @param drawMode The draw mode for the card.
 * @param framebuffer Pointer to the framebuffer.
 * @param function Pointer to a function to be executed when the card is interacted with.
 */
void epd_draw_vertical_card(
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

#endif // CARD_H