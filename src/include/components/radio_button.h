#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

/**
 * Draws a radio button on the EPD display.
 *
 * @param label The label text to be displayed next to the radio button.
 * @param font The font to be used for rendering the label text.
 * @param x The x-coordinate of the top-left corner of the radio button.
 * @param y The y-coordinate of the top-left corner of the radio button.
 * @param bgColor The background color of the radio button.
 * @param textColor The text color of the label.
 * @param checked Specifies whether the radio button is checked or not.
 * @param drawMode The drawing mode to be used for rendering the label.
 * @param framebuffer The framebuffer to be used for storing the radio button.
 * @param function A function pointer to be called when the radio button is clicked.
 */
void epd_draw_radio_button(
    const char* label, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    uint8_t bgColor,
    uint8_t textColor,
    bool checked, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

#endif // RADIO_BUTTON_H