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
#include "../include/dimensions.h"

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
        AddTouchPoint(touchArea, function);

        epd_fill_rect(squareArea.x, squareArea.y, squareArea.width, squareArea.height, 255, framebuffer);
        epd_draw_rect(squareArea.x, squareArea.y, squareArea.width, squareArea.height, 0, framebuffer);

        if (checked) {
            epd_fill_rect(squareArea.x + 10, squareArea.y + 10, squareArea.width - 20, squareArea.height - 20, 0, framebuffer);
        }

        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        int cursor_x = x + squareArea.width + 10;
        int cursor_y = y + squareArea.height / 2 + text_height / 2 - 5;
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
