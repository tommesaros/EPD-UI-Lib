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
#include "../include/components/progress_bar.h"
#include "../include/components.h"
#include "../include/colors.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_progress_bar(
    int32_t x, 
    int32_t y, 
    int32_t width,
    int32_t progress,
    uint8_t bgColor,
    uint8_t progressColor,
    uint8_t *framebuffer) {
        epd_fill_rounded_rect(
            x, 
            y, 
            width, 
            PROGRESS_BAR_HEIGHT, 
            15, 
            epd_convert_font_color(bgColor), 
            framebuffer
        );

        int32_t progressWidth = (width / 100) * progress;
        // Make the progress rectangle a bit smaller so the background rectangle creates a border
        epd_fill_rounded_rect(
            x + BORDER_WIDTH, 
            y + BORDER_WIDTH, 
            progressWidth - BORDER_WIDTH * 2, 
            PROGRESS_BAR_HEIGHT - BORDER_WIDTH * 2, 
            12, 
            epd_convert_font_color(progressColor), 
            framebuffer
        );
}