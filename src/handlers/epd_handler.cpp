#include <Arduino.h>
#include "epd_driver.h"

#include "../include/handlers/epd_handler.h"
#include "../include/handlers/framebuffer_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/components/status_bar.h"
#include "../include/fonts.h"

const int EPD_MAX_QUICK_REFRESHES = 20;
bool epdCurrentlyRefreshing = false;

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
    epd_fill_rect(area.x, area.y, area.width, area.height, white ? 255 : 0, GetMainFramebuffer());
    epd_push_pixels(area, 130, white ? 1 : 0);
}

uint8_t epd_convert_font_color(uint8_t color) {
    return map(color, 0, 15, 0, 255);
}

void epd_new_screen(uint8_t *framebuffer, void (*exitFunction)()) {
    ClearTouchPoints();
    CleanFramebuffer(framebuffer, epd_full_screen());
    epd_draw_status_bar(exitFunction);
}

GFXfont* epd_get_font(int size, bool bold) {
    switch (size) {
        case 8:
            return bold ? (GFXfont *)&OpenSans8B : (GFXfont *)&OpenSans8;
        case 9:
            return bold ? (GFXfont *)&OpenSans9B : (GFXfont *)&OpenSans9;
        case 10:
            return bold ? (GFXfont *)&OpenSans10B : (GFXfont *)&OpenSans10;
        case 11:
            return bold ? (GFXfont *)&OpenSans11B : (GFXfont *)&OpenSans11;
        case 12:
            return bold ? (GFXfont *)&OpenSans12B : (GFXfont *)&OpenSans12;
        case 13:
            return bold ? (GFXfont *)&OpenSans13B : (GFXfont *)&OpenSans13;
        case 14:
            return bold ? (GFXfont *)&OpenSans14B : (GFXfont *)&OpenSans14;
        case 15:
            return bold ? (GFXfont *)&OpenSans16B : (GFXfont *)&OpenSans15;
        case 16:
            return bold ? (GFXfont *)&OpenSans16B : (GFXfont *)&OpenSans16;
        case 18:
            return bold ? (GFXfont *)&OpenSans18B : (GFXfont *)&OpenSans18;
        case 20:
            return bold ? (GFXfont *)&OpenSans20B : (GFXfont *)&OpenSans20;
        case 24:
            return bold ? (GFXfont *)&OpenSans24B : (GFXfont *)&OpenSans24;
        case 26:
            return bold ? (GFXfont *)&OpenSans26B : (GFXfont *)&OpenSans26;
        default:
            return (GFXfont *)&OpenSans12;
    }
}

void epd_draw_framebuffer(uint8_t *framebuffer) {
    while (epdCurrentlyRefreshing) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    epdCurrentlyRefreshing = true;
    epd_poweron();
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    epd_poweroff();
    epdCurrentlyRefreshing = false;
}