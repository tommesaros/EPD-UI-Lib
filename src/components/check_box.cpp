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
#include "../include/colors.h"
#include "../include/components/check_box.h"
#include "../include/components.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

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
    void (*function)()) {
        int text_width;
        int text_height;
        epd_get_text_dimensions(font, label, &text_width, &text_height);
        Rect_t squareArea = {x, y, CHECK_BOX_SIZE, CHECK_BOX_SIZE};
        Rect_t touchArea = {x, y, squareArea.width + text_width + 10, squareArea.height};
        addTouchPoint(touchArea, function);

        // Background with a border
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_rounded_rect takes different color range
        epd_draw_rect(
            squareArea.x, 
            squareArea.y, 
            squareArea.width, 
            squareArea.height, 
            epd_convert_font_color(BLACK), 
            framebuffer
        );
        epd_fill_rect(
            squareArea.x + BORDER_WIDTH, 
            squareArea.y + BORDER_WIDTH, 
            squareArea.width - BORDER_WIDTH * 2, 
            squareArea.height - BORDER_WIDTH * 2, 
            epd_convert_font_color(WHITE), 
            framebuffer
        );

        // Check in the middle
        if (checked) {
            epd_fill_rect(
                squareArea.x + 5, 
                squareArea.y + 5, 
                squareArea.width - 10, 
                squareArea.height - 10, 
                epd_convert_font_color(BLACK), 
                framebuffer
            );
        }

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int cursor_x = x + squareArea.width + 10;
        int cursor_y = y + squareArea.height / 2 + text_height / 2;
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
