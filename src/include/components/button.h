#ifndef BUTTON_H
#define BUTTON_H

void epd_draw_circle_button_label(
    char* buttonText, 
    GFXfont *font,
    int32_t x,                      // x position of the center of the circle
    int32_t y,                      // y position of the center of the circle
    int32_t radius, 
    uint8_t color,                  // 15 is white, 0 is black
    uint8_t textColor,              // 15 is white, 0 is black
    uint8_t *framebuffer
);

#endif // BUTTON_H