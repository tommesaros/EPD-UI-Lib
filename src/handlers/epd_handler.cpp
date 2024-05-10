#include <Arduino.h>
#include "epd_driver.h"

#include "../include/handlers/epd_handler.h"

void EPDSetup() {
    epd_init();
    epd_poweron();
    epd_clear();
    
    return;
}

void epd_fill_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer) {
    // Draw the four corners
    epd_fill_circle(x + radius, y + radius, radius, color, framebuffer);
    epd_fill_circle(x + width - radius, y + radius, radius, color, framebuffer);
    epd_fill_circle(x + radius, y + height - radius, radius, color, framebuffer);
    epd_fill_circle(x + width - radius, y + height - radius, radius, color, framebuffer);

    // Draw the four sides
    epd_fill_rect(x + radius, y, width - 2 * radius, height + 1, color, framebuffer);
    epd_fill_rect(x, y + radius, radius, height - 2 * radius, color, framebuffer);
    epd_fill_rect(x + width - radius, y + radius, radius + 1, height - 2 * radius, color, framebuffer);
    epd_fill_rect(x + radius, y + height - radius, width - 2 * radius + 1, radius, color, framebuffer);
}

void epd_draw_rounded_rect(int x, int y, int width, int height, int radius, int color, uint8_t *framebuffer) {
    // draw white rectangle inside that is a pixel smaller
    // Draw the four corners
    epd_draw_circle(x + radius, y + radius, radius, color, framebuffer);
    epd_draw_circle(x + width - radius, y + radius, radius, color, framebuffer);
    epd_draw_circle(x + radius, y + height - radius, radius, color, framebuffer);
    epd_draw_circle(x + width - radius, y + height - radius, radius, color, framebuffer);

    // Draw the four sides
    epd_draw_rect(x + radius, y, width - 2 * radius, height, color, framebuffer);
    epd_draw_rect(x, y + radius, radius, height - 2 * radius, color, framebuffer);
    epd_draw_rect(x + width - radius, y + radius, radius, height - 2 * radius, color, framebuffer);
    epd_draw_rect(x + radius, y + height - radius, width - 2 * radius, radius, color, framebuffer);
}

void epd_sleep() {
    epd_poweroff();
    // epd_deinit();
    esp_sleep_enable_ext1_wakeup(GPIO_SEL_13, ESP_EXT1_WAKEUP_ANY_HIGH);
    esp_deep_sleep_start();
    // void epd_powerdown_lilygo_t5_47();
}

void epd_get_text_dimensions(const GFXfont *font,
                             const char *string,
                             int32_t *p_width,
                             int32_t *p_height) {
    int32_t x1 = 0; 
    int32_t y1 = 0; 
    int32_t x2 = 0; 
    int32_t y2 = 0; 

    FontProperties *properties = new FontProperties();
    properties->fg_color = 15;
    properties->bg_color = 0;

    get_text_bounds(font,
                    string,
                    &x1,
                    &y1,
                    &x2,
                    &y2,
                    p_width,
                    p_height,
                    properties);

    delete properties;
}
void epd_clear_area_quick(Rect_t area, bool white) {
    epd_push_pixels(area, 100, white ? 1 : 0);
}

uint8_t epd_convert_font_color(uint8_t color) {
    return map(color, 0, 15, 0, 255);
}
