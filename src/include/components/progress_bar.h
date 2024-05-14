#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

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