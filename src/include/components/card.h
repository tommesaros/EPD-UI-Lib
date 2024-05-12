#ifndef CARD_H
#define CARD_H

void epd_draw_horizontal_card(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char *primaryLabel, 
    const char *secondaryLabel, 
    GFXfont *primaryFont,
    GFXfont *secondaryFont,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

void epd_draw_vertical_card(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    char* label, 
    GFXfont *font,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()
);

#endif // CARD_H