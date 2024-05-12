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
#include "../include/components/card.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_horizontal_card(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char * primaryLabel, 
    const char * secondaryLabel, 
    GFXfont *primaryFont,
    GFXfont *secondaryFont,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        int text_width;
        int text_height;
        epd_get_text_dimensions(primaryFont, primaryLabel, &text_width, &text_height);

        AddTouchPoint(rectArea, function);

        if (bgColor == 15) {
            epd_draw_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                0, 
                framebuffer
            );
        } else {
            // Needs to convert color from range 0-15 to 0-255
            // as epd_fill_rounded_rect takes different color range
            uint8_t epdColor = epd_convert_font_color(bgColor);
            epd_fill_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epdColor, 
                framebuffer
            );
        }

        Rect_t iconArea = {
            .x = rectArea.x + 20,
            .y = rectArea.y + rectArea.height / 2 - image_height / 2,
            .width = image_width,
            .height =  image_height
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) image_data, framebuffer);


        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        int cursor_x = rectArea.x + image_width + 40;
        int cursor_y = rectArea.y + rectArea.height / 2 - 5;
        write_mode(
            primaryFont, 
            primaryLabel, 
            &cursor_x, 
            &cursor_y, 
            framebuffer, 
            drawMode,
            properties
        );
        
        cursor_x = rectArea.x + image_width + 40;
        cursor_y = rectArea.y + rectArea.height / 2 + text_height + 5;
        write_mode(
            secondaryFont, 
            secondaryLabel, 
            &cursor_x, 
            &cursor_y, 
            framebuffer, 
            drawMode,
            properties
        );
        
        delete properties;
}

void epd_draw_vertical_card(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    char* label, 
    GFXfont *font,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        int text_width;
        int text_height;
        epd_get_text_dimensions(font, label, &text_width, &text_height);

        AddTouchPoint(rectArea, function);

        if (bgColor == 15) {
            epd_draw_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                0, 
                framebuffer
            );
        } else {
            // Needs to convert color from range 0-15 to 0-255
            // as epd_fill_rounded_rect takes different color range
            uint8_t epdColor = epd_convert_font_color(bgColor);
            epd_fill_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epdColor, 
                framebuffer
            );
        }

        Rect_t iconArea = {
            .x = rectArea.x + rectArea.width / 2 - image_width / 2,
            .y = rectArea.y + rectArea.height / 2 - (image_height + text_height + 10) / 2,
            .width = image_width,
            .height =  image_height
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) image_data, framebuffer);


        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        int cursor_x = rectArea.x + rectArea.width / 2 - text_width / 2;
        int cursor_y = rectArea.y + rectArea.height / 2 + (image_height + text_height + 10) / 2;
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