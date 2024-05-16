#ifndef SLIDER_H
#define SLIDER_H


/**
 * Draws a slider component on the EPD display.
 * 
 * @param x The x-coordinate of the top-left corner of the slider.
 * @param y The y-coordinate of the top-left corner of the slider.
 * @param framebuffer Pointer to the framebuffer where the slider will be drawn.
 * @param upperFunction Pointer to the function that will be called when the upper half is touched.
 * @param lowerFunction Pointer to the function that will be called when the lower half is touched.
 */
void epd_draw_slider(
    int32_t x, 
    int32_t y, 
    uint8_t *framebuffer,
    void (*upperFunction)(),
    void (*lowerFunction)()
);

#endif // SLIDER_H