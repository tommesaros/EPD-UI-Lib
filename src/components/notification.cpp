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
#include "../include/components/status_bar.h"
#include "../include/components/notification.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

void epd_clear_notification(void *parameter) {
    vTaskSuspend(updateTimeStatusBarHandle);
    vTaskDelay(pdMS_TO_TICKS(NOTIFICATION_DURATION));
    Rect_t notificationArea = {
            .x = STATUS_BAR_PADDING,
            .y = STATUS_BAR_PADDING,
            .width = EPD_WIDTH - STATUS_BAR_PADDING * 2,
            .height = STATUS_BAR_HEIGHT
        };
    epd_clear_area_cycles(notificationArea, 2, 50);
    epd_draw_grayscale_image(epd_full_screen(), getMainFramebuffer());
    vTaskResume(updateTimeStatusBarHandle);
    vTaskDelete(NULL);
}

void epd_trigger_notification(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char * primaryLabel, 
    const char * secondaryLabel) {
        uint8_t *framebuffer = getNotificationFramebuffer();
        Rect_t notificationArea = {
            .x = STATUS_BAR_PADDING,
            .y = STATUS_BAR_PADDING,
            .width = EPD_WIDTH - STATUS_BAR_PADDING * 2,
            .height = STATUS_BAR_HEIGHT
        };

        cleanFramebufferAndEPD(framebuffer, notificationArea);

        // Background
        epd_fill_rounded_rect(
            notificationArea.x, 
            notificationArea.y, 
            notificationArea.width, 
            notificationArea.height, 
            20, 
            BLACK, 
            framebuffer
        );

        // Icon
        Rect_t notificationIconArea = {
            .x = STATUS_BAR_PADDING * 3,
            .y = STATUS_BAR_PADDING * 2,
            .width = imageWidth,
            .height = imageHeight
        };
        epd_copy_to_framebuffer(notificationIconArea, imageData, framebuffer);


        FontProperties *properties = new FontProperties();
        properties->fg_color = WHITE;
        properties->bg_color = BLACK;

        // Title
        int textX = STATUS_BAR_PADDING * 3 + imageWidth + STATUS_BAR_PADDING * 2;
        int textY = STATUS_BAR_HEIGHT - 5;
        write_mode(
            TITLE_FONT, 
            primaryLabel, 
            &textX, 
            &textY, 
            framebuffer, 
            WHITE_ON_BLACK, 
            properties
        );

        // Text
        textX += 20;
        write_mode(
            TEXT_FONT, 
            secondaryLabel, 
            &textX, 
            &textY, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties
        );
        
        epd_draw_grayscale_image(epd_full_screen(), framebuffer);

        xTaskCreatePinnedToCore(
            epd_clear_notification,     // Task function
            "epd_clear_notification",   // Task name
            5000,                       // Stack size (in words)
            NULL,                       // Task parameter
            1,                          // Task priority
            NULL,                       // Task handle
            tskNO_AFFINITY              // Core number (0 or 1)
        );          

        delete properties;
}
