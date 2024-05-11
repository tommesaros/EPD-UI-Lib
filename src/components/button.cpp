// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/fonts.h"
#include "../include/components/button.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

#include "../../image/black_bg/play_icon.h"

void epd_draw_circle_button_label(
    char* label, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t bgColor, 
    uint8_t textColor, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};
        AddTouchPoint(x - radius, y - radius, radius * 2, radius * 2, function);
        // epd_clear_area_quick(area, true); 

        if (bgColor == 15) {
            epd_draw_circle(x, y, radius, 0, framebuffer);
        } else {
            // Convert color from range 0-15 to 0-255
            // Fill circle takes different range
            uint8_t epdColor = epd_convert_font_color(bgColor);
            epd_fill_circle(x, y, radius, epdColor, framebuffer);
        }

        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
       
        int32_t width = 0;
        int32_t height = 0;
        epd_get_text_dimensions(font, label, &width, &height);

        int cursor_x = x - (width / 2);
        int cursor_y = y + (height / 2);
        write_mode(
            font, 
            label, 
            &cursor_x, 
            &cursor_y, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties);
        
        delete properties;
}

void epd_draw_circle_button_icon(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t bgColor, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};
        AddTouchPoint(x - radius, y - radius, radius * 2, radius * 2, function);
        // epd_clear_area_quick(area, true); 

        if (bgColor == 15) {
            epd_draw_circle(x, y, radius, 0, framebuffer);
        } else {
            // Convert color from range 0-15 to 0-255
            // Fill circle takes different range
            uint8_t epdColor = epd_convert_font_color(bgColor);
            epd_fill_circle(x, y, radius, epdColor, framebuffer);
        }

        Rect_t iconArea = {
            .x = x - image_width / 2,
            .y = y - image_height / 2,
            .width = image_width,
            .height =  image_height
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) image_data, framebuffer);
}

// with icons / without
// primary, secondary, tertiary, circle

