#ifndef TOGGLE_H
#define TOGGLE_H

/**
 * Draws an on/off toggle button on the EPD display.
 * 
 * @param x The x-coordinate of the top-left corner of the toggle button.
 * @param y The y-coordinate of the top-left corner of the toggle button.
 * @param checked The initial checked state of the toggle button.
 * @param framebuffer The framebuffer to be used for rendering the toggle button.
 * @param function The callback function to be called when the toggle button is clicked.
 */
void epd_draw_toggle(
    int32_t x, 
    int32_t y, 
    bool checked, 
    uint8_t *framebuffer,
    void (*function)()
);

#endif // TOGGLE_H