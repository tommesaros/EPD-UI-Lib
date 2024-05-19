#ifndef CHECK_BOX_H
#define CHECK_BOX_H

/**
 * Draws a check box on the EPD display.
 *
 * @param label The label text to be displayed next to the check box.
 * @param font The font to be used for rendering the label text.
 * @param x The x-coordinate of the top-left corner of the check box.
 * @param y The y-coordinate of the top-left corner of the check box.
 * @param bgColor The background color of the check box.
 * @param textColor The text color of the label.
 * @param checked Indicates whether the check box is checked or not.
 * @param drawMode The drawing mode to be used for rendering the label.
 * @param framebuffer The framebuffer to be used for storing the check box.
 * @param function A function pointer to be called when the check box is clicked.
 */
void epd_draw_check_box(
    const char* label, 
    const GFXfont *font,
    int32_t x, 
    int32_t y, 
    uint8_t bgColor,
    uint8_t textColor,
    bool checked,  
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

#endif // CHECK_BOX_H