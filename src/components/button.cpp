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
#include "../include/components.h"
#include "../include/colors.h"
#include "../include/components/button.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_circle_button(
    const char* label, 
    const GFXfont *font,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t bgColor, 
    uint8_t textColor, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};
        addTouchPoint(area, function);

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_circle takes different color range
        if (bgColor == WHITE) {
            // Drawing a border around the button
            epd_draw_circle(x, y, radius, epd_convert_font_color(BLACK), framebuffer);
            epd_draw_circle(x, y, radius - BORDER_WIDTH, epd_convert_font_color(WHITE), framebuffer);
        } else {
            epd_fill_circle(x, y, radius, epd_convert_font_color(bgColor), framebuffer);
        }

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int32_t width = 0;
        int32_t height = 0;
        epd_get_text_dimensions(font, label, &width, &height);
        int textX = x - (width / 2);
        int textY = y + (height / 2);
        write_mode(
            font, 
            label, 
            &textX, 
            &textY, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties
        );
        delete properties;
}

void epd_draw_circle_button_icon(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t bgColor, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};
        addTouchPoint(area, function);

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_circle takes different color range
        if (bgColor == WHITE) {
            // Drawing a border around the button
            epd_draw_circle(x, y, radius, epd_convert_font_color(BLACK), framebuffer);
            epd_draw_circle(x, y, radius - BORDER_WIDTH, epd_convert_font_color(WHITE), framebuffer);
        } else {
            epd_fill_circle(x, y, radius, epd_convert_font_color(bgColor), framebuffer);
        }

        // Icon
        Rect_t iconArea = {
            .x = x - imageWidth / 2,
            .y = y - imageHeight / 2,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);
}

void epd_draw_tertiary_button_icon(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char* label, 
    const GFXfont *font,
    int32_t x, 
    int32_t y, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        int textWidth;
        int textHeight;
        epd_get_text_dimensions(font, label, &textWidth, &textHeight);
        Rect_t area = {x, y - 5, imageWidth + textWidth + 10, imageHeight + 10};
        addTouchPoint(area, function);

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_circle takes different color range
        epd_fill_rect(
            area.x, 
            area.y, 
            area.width, 
            area.height, 
            epd_convert_font_color(bgColor), 
            framebuffer
        );

        // Icon
        Rect_t iconArea = {
            .x = x,
            .y = y,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int textX = x + imageWidth + 10;
        int textY = y + imageHeight / 2 + textHeight / 2 - 2;
        write_mode(
            font, 
            label, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        delete properties;
}

void epd_draw_button_icon(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char* label, 
    const GFXfont *font,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        int textWidth;
        int textHeight;
        epd_get_text_dimensions(font, label, &textWidth, &textHeight);
        addTouchPoint(rectArea, function);

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_circle takes different color range
        if (bgColor == WHITE) {
            // Drawing a border around the button
            epd_fill_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epd_convert_font_color(BLACK), 
                framebuffer
            );
            epd_fill_rounded_rect(
                rectArea.x + BORDER_WIDTH, 
                rectArea.y + BORDER_WIDTH, 
                rectArea.width - BORDER_WIDTH * 2, 
                rectArea.height - BORDER_WIDTH * 2, 
                radius, 
                epd_convert_font_color(WHITE), 
                framebuffer
            );
        } else {
            epd_fill_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epd_convert_font_color(bgColor), 
                framebuffer
            );
        }

        // Icon
        Rect_t iconArea = {
            .x = rectArea.x + rectArea.width / 2 - (imageWidth + textWidth + 20) / 2,
            .y = rectArea.y + rectArea.height / 2 - imageHeight / 2,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int textX = rectArea.x + rectArea.width / 2 - (imageWidth + textWidth + 20) / 2 + imageWidth + 20;
        int textY = rectArea.y + rectArea.height / 2 + textHeight / 2;
        write_mode(
            font, 
            label, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        delete properties;
}

void epd_draw_button(
    const char* label, 
    const GFXfont *font,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        addTouchPoint(rectArea, function);

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_circle takes different color range
        if (bgColor == WHITE) {
            // Drawing a border around the button
            epd_draw_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epd_convert_font_color(BLACK), 
                framebuffer
            );
            epd_fill_rounded_rect(
                rectArea.x + BORDER_WIDTH, 
                rectArea.y + BORDER_WIDTH, 
                rectArea.width - BORDER_WIDTH * 2, 
                rectArea.height - BORDER_WIDTH * 2, 
                radius, 
                epd_convert_font_color(WHITE), 
                framebuffer
            );
        } else {
            epd_fill_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epd_convert_font_color(bgColor), 
                framebuffer
            );
        }

        // Text
        int textWidth;
        int textHeight;
        epd_get_text_dimensions(font, label, &textWidth, &textHeight);
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int textX = rectArea.x + rectArea.width / 2 - textWidth / 2;
        int textY = rectArea.y + rectArea.height / 2 + textHeight / 2 - 2;
        write_mode(
            font, 
            label, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        delete properties;
}
