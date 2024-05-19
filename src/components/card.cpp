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
#include "../include/components.h"
#include "../include/components/card.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_horizontal_card(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char * primaryLabel, 
    const char * secondaryLabel, 
    const GFXfont *primaryFont,
    const GFXfont *secondaryFont,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        addTouchPoint(rectArea, function);

        // Background with a border
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_rounded_rect takes different color range
        if (bgColor == WHITE) {
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
        } else {;
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
            .x = rectArea.x + CARD_PADDING,
            .y = rectArea.y + rectArea.height / 2 - imageHeight / 2,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);

        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        int primaryLabelWidth;
        int primaryLabelHeight;
        epd_get_text_dimensions(primaryFont, primaryLabel, &primaryLabelWidth, &primaryLabelHeight);
        int secondaryLabelWidth;
        int secondaryLabelHeight;
        epd_get_text_dimensions(primaryFont, primaryLabel, &secondaryLabelWidth, &secondaryLabelHeight);

        // Primary text
        int textX = rectArea.x + imageWidth + CARD_PADDING * 2;
        int textY;
        if (secondaryLabel == "") {
            textY = rectArea.y + rectArea.height / 2 + primaryLabelHeight / 2;
        } else {
            textY = rectArea.y + rectArea.height / 2 - (primaryLabelHeight + secondaryLabelHeight + 10) / 2 + primaryLabelHeight;
        }

        write_mode(
            primaryFont, 
            primaryLabel, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        
        // Secondary text
        textX = rectArea.x + imageWidth + CARD_PADDING * 2;
        textY = rectArea.y + rectArea.height / 2 + (primaryLabelHeight + secondaryLabelHeight + 10) / 2;
        write_mode(
            secondaryFont, 
            secondaryLabel, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        
        delete properties;
}

void epd_draw_vertical_card(
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

        // Background with a border
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_rounded_rect takes different color range
        if (bgColor == WHITE) {
            epd_draw_rounded_rect(
                rectArea.x, 
                rectArea.y, 
                rectArea.width, 
                rectArea.height, 
                radius, 
                epd_convert_font_color(BLACK), 
                framebuffer
            );
            epd_draw_rounded_rect(
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
            .x = rectArea.x + rectArea.width / 2 - imageWidth / 2,
            .y = rectArea.y + rectArea.height / 2 - (imageHeight + textHeight + 10) / 2,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);

        // Text
        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
        int textX = rectArea.x + rectArea.width / 2 - textWidth / 2;
        int textY = rectArea.y + rectArea.height / 2 + (imageHeight + textHeight + 10) / 2;
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

void epd_draw_multi_line_card(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char * primaryLabel, 
    const char * secondaryLabel, 
    const GFXfont *primaryFont,
    const GFXfont *secondaryFont,
    Rect_t rectArea,
    int32_t radius, 
    uint8_t bgColor,
    uint8_t textColor, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    void (*function)()) {
        addTouchPoint(rectArea, function);

        // Background with a border
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_rounded_rect takes different color range
        if (bgColor == WHITE) {
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
            .x = rectArea.x + CARD_PADDING,
            .y = rectArea.y + CARD_PADDING,
            .width = imageWidth,
            .height =  imageHeight
        };
        epd_copy_to_framebuffer(iconArea, (uint8_t *) imageData, framebuffer);

        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;

        // Primary text
        int textWidth;
        int textHeight;
        epd_get_text_dimensions(primaryFont, primaryLabel, &textWidth, &textHeight);
        int textX = rectArea.x + imageWidth + CARD_PADDING * 2;
        int textY = rectArea.y + CARD_PADDING + 30;
        write_mode(
            primaryFont, 
            primaryLabel, 
            &textX, 
            &textY, 
            framebuffer, 
            drawMode,
            properties
        );
        
        // Secondary text
        textX = rectArea.x + imageWidth + CARD_PADDING * 2;
        textY = rectArea.y + CARD_PADDING + 30 + textHeight + 10;
        write_string(
            secondaryFont, 
            secondaryLabel, 
            &textX, 
            &textY, 
            framebuffer
        );
        
        delete properties;
}