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
#include "../include/dimensions.h"

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
        epd_fill_rounded_rect(x, y, width, PROGRESS_BAR_HEIGHT, 10, bgColor, framebuffer);
        int32_t progressWidth = (width / 100) * progress;
        epd_fill_rounded_rect(x, y, progressWidth, PROGRESS_BAR_HEIGHT, 10, progressColor, framebuffer);
}