#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

/**
 * @brief Draws a progress bar on the EPD display.
 * 
 * The progress bar represents the progress value provided as an argument.
 * 
 * @param x The x-coordinate of the top-left corner of the progress bar.
 * @param y The y-coordinate of the top-left corner of the progress bar.
 * @param width The width of the progress bar.
 * @param progress The progress value (%) to be represented by the progress bar.
 * @param bgColor The background color of the progress bar.
 * @param progressColor The color of the progress bar.
 * @param framebuffer The framebuffer on which the progress bar will be storing.
 */
void epd_draw_progress_bar(
    int32_t x, 
    int32_t y, 
    int32_t width,
    int32_t progress,
    uint8_t bgColor,
    uint8_t progressColor,
    uint8_t *framebuffer
);

#endif // PROGRESS_BAR_H