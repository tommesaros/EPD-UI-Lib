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
#include "../include/components/toggle.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_toggle(
    int32_t x, 
    int32_t y, 
    bool checked, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t toggleArea = {x, y, TOGGLE_WIDTH, TOGGLE_HEIGHT};
        addTouchPoint(toggleArea, function);

        // Background
        epd_fill_rounded_rect(
            toggleArea.x, 
            toggleArea.y, 
            toggleArea.width,
            toggleArea.height,
            20,
            epd_convert_font_color(BLACK), 
            framebuffer
        );
        // Make the progress rectangle a bit smaller so the background rectangle creates a border
        epd_fill_rounded_rect(
            toggleArea.x + 2, 
            toggleArea.y + 2, 
            toggleArea.width - 4,
            toggleArea.height - 4,
            20,
            epd_convert_font_color(WHITE), 
            framebuffer
        );
        

        // Check in the middle
        if (checked) {
            epd_fill_circle(
            toggleArea.x + toggleArea.width - RADIO_BUTTON_RADIUS, 
            toggleArea.y + toggleArea.height / 2, 
            RADIO_BUTTON_RADIUS - 5, 
            epd_convert_font_color(BLACK), 
            framebuffer
        );
        } else {
            epd_fill_circle(
            toggleArea.x + RADIO_BUTTON_RADIUS, 
            toggleArea.y + toggleArea.height / 2, 
            RADIO_BUTTON_RADIUS - 5, 
            epd_convert_font_color(BLACK), 
            framebuffer
        );
        }
}