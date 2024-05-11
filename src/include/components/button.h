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
    uint8_t *framebuffer,
    void (*function)()
);

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

void epd_draw_tertiary_button_icon(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    char* label, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)());

#endif // BUTTON_H