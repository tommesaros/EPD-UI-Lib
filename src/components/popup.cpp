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
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char * title, 
    const char * text, 
    uint8_t *primaryButtonIconData,
    int32_t primaryButtonIconWidth,
    int32_t primaryButtonIconHeight,
    const char * primaryButtonLabel, 
    uint8_t *secondaryButtonIconData,
    int32_t secondaryButtonIconWidth,
    int32_t secondaryButtonIconHeight,
    const char * secondaryButtonLabel, 
    void (*function)()) {
        uint8_t *framebuffer = getNotificationFramebuffer();
        Rect_t notificationArea = {
            .x = 10,
            .y = 10,
            .width = EPD_WIDTH - 20,
            .height = 50
        };

        cleanFramebufferAndEPD(framebuffer, notificationArea);
/*
        epd_draw_multi_line_card(
        (uint8_t*)power_big_icon_data,
        power_big_icon_width,
        power_big_icon_height,
        "Power off the device?",
        "Are you sure you want to power off the device?\nThis will close all running apps and turn off the\ndisplay. You can turn it back on by pressing the \nmost right button above the screen.",
        TITLE_FONT,
        TEXT_FONT,
        popupArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        getMainFramebuffer(),
        dummyFunction
    );*/
}