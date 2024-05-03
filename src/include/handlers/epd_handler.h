#ifndef EPD_HANDLER_H
#define EPD_HANDLER_H

void EPDSetup();
void epd_fill_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);
void epd_draw_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer);
void epd_sleep();

#endif // EPD_HANDLER_H