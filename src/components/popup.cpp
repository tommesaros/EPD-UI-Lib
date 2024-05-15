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
#include "../include/components/popup.h"
#include "../include/components/status_bar.h"
#include "../include/components.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

//full black screen
//then status bac
//then big whote card with write_string 
//and button at the end
//secondary touchpoints
// IF provided aditional text (desc), make space for it

void epd_clear_popup(void *parameter) {
    vTaskSuspend(updateTimeStatusBarHandle);
    vTaskDelay(pdMS_TO_TICKS(NOTIFICATION_DURATION));
    Rect_t notificationArea = {
            .x = 10,
            .y = 10,
            .width = EPD_WIDTH - 20,
            .height = 50
        };
    epd_clear_area_cycles(notificationArea, 2, 50);
    epd_draw_grayscale_image(epd_full_screen(), getMainFramebuffer());
    vTaskResume(updateTimeStatusBarHandle);
    vTaskDelete(NULL);
}

void epd_trigger_popup(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char * primaryLabel, 
    const char * secondaryLabel) {
        uint8_t *framebuffer = getNotificationFramebuffer();
        Rect_t notificationArea = {
            .x = 10,
            .y = 10,
            .width = EPD_WIDTH - 20,
            .height = 50
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
            TEXT_FONT, 
            secondaryLabel, 
            &x, 
            &y, 
            framebuffer, 
            WHITE_ON_BLACK,
            properties
        );
        
        epd_draw_grayscale_image(epd_full_screen(), framebuffer);

        xTaskCreatePinnedToCore(
            epd_clear_popup,     // Task function
            "epd_clear_popup",   // Task name
            5000,                       // Stack size (in words)
            NULL,                       // Task parameter
            1,                          // Task priority
            NULL,                       // Task handle
            tskNO_AFFINITY              // Core number (0 or 1)
        );          

        delete properties;
}