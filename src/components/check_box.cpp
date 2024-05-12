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
#include "../include/components/check_box.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_selected_check_box(
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
    void (*function)()) {
        int text_width;
        int text_height;
        epd_get_text_dimensions(font, label, &text_width, &text_height);

        Rect_t area = {x, y - 5, image_width + text_width + 10, image_height + 10};
        AddTouchPoint(area, function);

        uint8_t epdColor = epd_convert_font_color(bgColor);
        epd_fill_rect(area.x, area.y, area.width, area.height, epdColor, framebuffer);

        Rect_t iconArea = {
            .x = x,
            .y = y,
            .width = image_width,
            .height =  image_height
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) image_data, framebuffer);


        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        int cursor_x = x + image_width + 10;
        int cursor_y = y + image_height / 2 + text_height / 2 - 5;
        write_mode(
            font, 
            label, 
            &cursor_x, 
            &cursor_y, 
            framebuffer, 
            drawMode,
            properties
        );
        
        delete properties;
}