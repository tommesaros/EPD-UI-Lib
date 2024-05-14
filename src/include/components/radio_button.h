#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

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