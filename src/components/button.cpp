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
    char* buttonText, 
    GFXfont *font,
    int32_t x, 
    int32_t y, 
    int32_t radius, 
    uint8_t color, 
    uint8_t textColor, 
    uint8_t *framebuffer) {
        Rect_t area = {x - radius, y - radius, radius * 2, radius * 2};

        epd_push_pixels(area, 100, 1);
        epd_fill_circle(x, y, radius, color, framebuffer);
        
        int32_t width = 0;
        int32_t height = 0;

        FontProperties *properties = new FontProperties();
        properties->fg_color = 15;
        properties->bg_color = 0;

       

        epd_get_text_dimensions(font, buttonText, &width, &height);

        int cursor_x = x - (width / 2);
        int cursor_y = y + (height / 2);

        write_mode(font, buttonText, &cursor_x, &cursor_y, framebuffer, 
                    WHITE_ON_BLACK,
                    properties);
}

// with icons / without
// primary, secondary, tertiary, circle

