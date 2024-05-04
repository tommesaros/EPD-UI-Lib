#ifndef EPD_HANDLER_H
#define EPD_HANDLER_H

void EPDSetup();
void epd_fill_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);
void epd_draw_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);
void epd_sleep();
void epd_get_text_dimensions(const GFXfont *font,
                             const char *string,
                             int32_t *width,    //needs to be a pointer
                             int32_t *height);  //needs to be a pointer

#endif // EPD_HANDLER_H