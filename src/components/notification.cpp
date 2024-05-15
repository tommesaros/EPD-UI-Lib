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

void epd_clear_notification(void *parameter) {
    vTaskDelay(pdMS_TO_TICKS(NOTIFICATION_DURATION));
    epd_draw_grayscale_image(epd_full_screen(), getMainFramebuffer());
}

void epd_trigger_notification(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char * primaryLabel, 
    const char * secondaryLabel) {
        uint8_t *framebuffer = getNotificationFramebuffer();
        // Clear notification area

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
        int x = 30 + image_width + 20;
        int y = 45;
        write_mode(
            TITLE_FONT, 
            primaryLabel, 
            &x, 
            &y, 
            framebuffer, 
            WHITE_ON_BLACK, 
            properties
        );

        // Text
        x += 20;
        write_mode(
            TEXT_FONT_BOLD, 
            secondaryLabel, 
            &x, 
            &y, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties
        );
        
        epd_draw_grayscale_image(epd_full_screen(), framebuffer);

        xTaskCreatePinnedToCore(
            epd_clear_notification,    // Task function
            "epd_clear_notification",  // Task name
            5000,              // Stack size (in words)
            NULL,              // Task parameter
            1,                 // Task priority
            NULL,              // Task handle
            tskNO_AFFINITY     // Core number (0 or 1)
        );

        delete properties;
}
