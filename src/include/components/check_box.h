#ifndef CHECK_BOX_H
#define CHECK_BOX_H

//TODO add description
void epd_draw_check_box(
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

#endif // CHECK_BOX_H