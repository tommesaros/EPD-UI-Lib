#ifndef BUTTON_H
#define BUTTON_H

void epd_draw_circle_button_label(
    char* buttonText, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t color, 
    uint8_t textColor, 
    uint8_t *framebuffer
);

#endif // BUTTON_H