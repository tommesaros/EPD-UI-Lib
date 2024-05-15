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
#include "../include/components/notification.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"
/*
void epd_clear_notification() {
    epd_draw_grayscale_image();
}

void epd_trigger_notification(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char* label, 
    const GFXfont *font,
    Rect_t rectArea,
    int32_t radius, 
    DrawMode_t drawMode,
    uint8_t *framebuffer,
    int32_t duration ) {
        uint8_t *framebuffer = getNotificationFramebuffer();

        // Background
        epd_fill_rounded_rect(10, 10, EPD_WIDTH - 20, 50, 20, BLACK, framebuffer);

        // Icon
        Rect_t notificationIconArea = {
            .x = 30,
            .y = 20,
            .width = image_width,
            .height = image_height
        };
        epd_copy_to_framebuffer(notificationIconArea, image_data, framebuffer);


        FontProperties *properties = new FontProperties();
        properties->fg_color = WHITE;
        properties->bg_color = BLACK;

        // Title
        int32_t width;
        int32_t height;
        char time[6];
        sprintf(time, "%02d:%02d", timeGetHour(), timeGetMinute());
        epd_get_text_dimensions(TITLE_FONT, time, &width, &height);
        x = EPD_WIDTH / 2 - width / 2;
        write_mode(
            TITLE_FONT, 
            time, 
            &x, 
            &y, 
            framebuffer, 
            WHITE_ON_BLACK, 
            properties
        );

        // Text
        epd_get_text_dimensions(TEXT_FONT_BOLD, WIFI_SSID, &width, &height);
        x = EPD_WIDTH - 145 - width;
        y = 45;
        write_mode(
            TEXT_FONT_BOLD, 
            WIFI_SSID, 
            &x, 
            &y, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties
        );
        
        if (updateTimeStatusBarHandle == NULL) {
            xTaskCreatePinnedToCore(
                updateTimeStatusBar,    // Task function
                "updateTimeStatusBar",  // Task name
                5000,              // Stack size (in words)
                NULL,              // Task parameter
                1,                 // Task priority
                &updateTimeStatusBarHandle,              // Task handle
                tskNO_AFFINITY     // Core number (0 or 1)
            );
        }

        delete properties;
}
*/