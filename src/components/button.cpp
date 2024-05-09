/*******************************************************************
    Based on the OpenWeather API Example:
    My_OpenWeather_Test.ino
    https://github.com/Bodmer/OpenWeather/blob/main/examples/Onecall%20API%20(subscription%20required)/My_OpenWeather_Test/My_OpenWeather_Test.ino
*******************************************************************/

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
#include "../include/components/button.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_draw_circle_button_label(
    char* label, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t bgColor, 
    uint8_t textColor, 
    uint8_t *framebuffer,
    void (*function)()) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};
        AddTouchPoint(x - radius, y - radius, radius * 2, radius * 2, function);
        epd_clear_area_quick(area); 

        if (bgColor == 15) {
            epd_draw_circle(x, y, radius, 0, framebuffer);
        } else {
            // Convert color from range 0-15 to 0-255
            // Fill circle takes different range
            uint8_t epdColor = epd_convert_font_color(bgColor);
            epd_fill_circle(x, y, radius, epdColor, framebuffer);
        }

        FontProperties *properties = new FontProperties();
        properties->fg_color = textColor;
        properties->bg_color = bgColor;
       
        int32_t width = 0;
        int32_t height = 0;
        epd_get_text_dimensions(font, label, &width, &height);

        int cursor_x = x - (width / 2);
        int cursor_y = y + (height / 2);
        write_mode(
            font, 
            label, 
            &cursor_x, 
            &cursor_y, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties);
        
        delete properties;
}

// with icons / without
// primary, secondary, tertiary, circle

