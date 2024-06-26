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
#include "../include/components/slider.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_slider(
    int32_t x, 
    int32_t y, 
    uint8_t *framebuffer,
    void (*upperFunction)(),
    void (*lowerFunction)()) {
        Rect_t sliderArea = {x, y, SLIDER_WIDTH, SLIDER_HEIGHT};

        // Background
        // Needs to convert color from range 0-15 to 0-255
        // as epd_fill_rounded_rect takes different color range
        epd_fill_rounded_rect(
            sliderArea.x, 
            sliderArea.y, 
            sliderArea.width, 
            sliderArea.height, 
            CORNER_RADIUS, 
            epd_convert_color_range(BLACK), 
            framebuffer
        );
        // Make the progress rectangle a bit smaller so the background rectangle creates a border
        epd_fill_rounded_rect(
            sliderArea.x + BORDER_WIDTH, 
            sliderArea.y + BORDER_WIDTH, 
            sliderArea.width - BORDER_WIDTH * 2, 
            sliderArea.height - BORDER_WIDTH * 2, 
            CORNER_RADIUS, 
            epd_convert_color_range(WHITE), 
            framebuffer
        );

        // Line in the middle
        epd_draw_line(
            sliderArea.x, 
            sliderArea.y + sliderArea.height / 2, 
            sliderArea.x + sliderArea.width, 
            sliderArea.y + sliderArea.height / 2, 
            epd_convert_color_range(BLACK), 
            framebuffer
        );

        // Upper text
        sliderArea.height = SLIDER_HEIGHT / 2;
        addTouchPoint(sliderArea, upperFunction);

        int textWidth;
        int textHeight;
        epd_get_text_dimensions(TITLE_FONT, SLIDER_UPPER_LABEL, &textWidth, &textHeight);
        int textX = sliderArea.x + sliderArea.width / 2 - textWidth / 2;
        int textY = sliderArea.y + sliderArea.height / 2 + textHeight / 2;
        writeln(
            TITLE_FONT,
            SLIDER_UPPER_LABEL,  
            &textX, 
            &textY, 
            framebuffer
        );

        // Lower text
        sliderArea.y = y + SLIDER_HEIGHT / 2;
        addTouchPoint(sliderArea, lowerFunction);

        epd_get_text_dimensions(TITLE_FONT, SLIDER_LOWER_LABEL, &textWidth, &textHeight);
        textX = sliderArea.x + sliderArea.width / 2 - textWidth / 2;
        textY = sliderArea.y + sliderArea.height / 2 + textHeight / 2;
        writeln(
            TITLE_FONT,
            SLIDER_LOWER_LABEL, 
            &textX, 
            &textY, 
            framebuffer
        );
}