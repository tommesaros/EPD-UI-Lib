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
#include "../include/components/radio_button.h"
#include "../include/components.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

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
    void (*function)()) {
        int text_width;
        int text_height;
        epd_get_text_dimensions(font, label, &text_width, &text_height);
        Rect_t circleArea = {x, y, RADIO_BUTTON_RADIUS * 2, RADIO_BUTTON_RADIUS * 2};
        Rect_t touchArea = {x, y, circleArea.width + text_width + 10, circleArea.height};
        addTouchPoint(touchArea, function);

        // Background
        epd_fill_circle(
            circleArea.x + RADIO_BUTTON_RADIUS, 
            circleArea.y + RADIO_BUTTON_RADIUS, 
            RADIO_BUTTON_RADIUS, 
            255, 
            framebuffer
        );
        epd_draw_circle(
            circleArea.x + RADIO_BUTTON_RADIUS, 
            circleArea.y + RADIO_BUTTON_RADIUS, 
            RADIO_BUTTON_RADIUS, 
            0, 
            framebuffer
        );

        // Check in the middle
        if (checked) {
            epd_fill_circle(
            circleArea.x + RADIO_BUTTON_RADIUS, 
            circleArea.y + RADIO_BUTTON_RADIUS, 
            RADIO_BUTTON_RADIUS - 5, 
            0, 
            framebuffer
        );
        }

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int cursor_x = x + circleArea.width + 10;
        int cursor_y = y + circleArea.height / 2 + text_height / 2;
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