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
#include "../include/components/status_bar.h"
#include "../include/components.h"
#include "../include/colors.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"
#include "../include/handlers/time_handler.h"

// ----------------------------
// Credentials
// ----------------------------
#include "../include/credentials.h"

// ----------------------------
// Icons
// ----------------------------
#include "../image/black_bg/home_icon.h"
#include "../image/black_bg/app_menu_icon.h"
#include "../image/black_bg/speaker_icon.h"
#include "../image/black_bg/wifi_small_icon.h"

// ----------------------------
// Apps
// ----------------------------
#include "../include/apps/system/control_panel.h"
#include "../include/apps/system/homescreen.h"

TaskHandle_t updateTimeStatusBarHandle = NULL;
void (*exitFunction)();

void exitAppAndGoToHomescreen() {
    exitFunction();
    displayHomeScreen();
}

void exitAppAndGoToAppMenu() {
    exitFunction();
    // Show screen with all apps when there are 
    // more apps than can fit on the homescreen
}


void updateTimeStatusBar(void *parameter) {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    
    int32_t x = EPD_WIDTH / 2;
    int32_t y = 45;
    int32_t width = 0;
    int32_t height = 0;
    Rect_t dateArea = {150, 10, 200, 50};
    Rect_t timeArea = {EPD_WIDTH / 2 - 40, 10, 80, 50};
    
    char time[6];
    FontProperties *properties = new FontProperties();
    properties->fg_color = WHITE;
    properties->bg_color = BLACK;

    int hour;
    int minute;
    int refreshCount = 0;

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(60000)); // Delay for 1 minute

        // Do a full refresh every 20 minutes
        if (refreshCount == EPD_MAX_QUICK_REFRESHES) {
            epd_clear();
            refreshCount = 0;
        } else {
            epd_clear_area_cycles(timeArea, 2, 50);
            refreshCount++;
        }
        
        hour = timeGetHour();
        minute = timeGetMinute();

        // Update date at midnight
        if (hour == 0 && minute == 0) {
            epd_clear_area_cycles(dateArea, 2, 50);
            epd_fill_rect(150, 11, 200, 49, 0, mainFramebuffer);

            x = 150;
            write_mode(
                TEXT_FONT_BOLD, 
                getTimeDate(), 
                &x, 
                &y, 
                mainFramebuffer, 
                WHITE_ON_BLACK,
                properties
            );
        }

        // Background
        epd_fill_rect(EPD_WIDTH / 2 - 40, 11, 80, 49, 0, mainFramebuffer);
        
        // Updated time
        sprintf(time, "%02d:%02d", timeGetHour(), timeGetMinute());
        epd_get_text_dimensions(TITLE_FONT, time, &width, &height);
        x = EPD_WIDTH / 2 - width / 2;
        write_mode(
            TITLE_FONT, 
            time, 
            &x, 
            &y, 
            mainFramebuffer, 
            WHITE_ON_BLACK, 
            properties
        );
        epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);
    }

    delete properties;
}

void epd_draw_status_bar(void (*function)()) {
    exitFunction = function;
    uint8_t *mainFramebuffer = getMainFramebuffer();

    // Background
    epd_fill_rounded_rect(10, 10, EPD_WIDTH - 20, 50, 20, BLACK, mainFramebuffer);

    // Homescreen and menu icons
    Rect_t statusBarIconArea = {
        .x = 30,
        .y = 20,
        .width = home_icon_width,
        .height = home_icon_height
    };
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) home_icon_data, mainFramebuffer);
    addTouchPoint(statusBarIconArea, exitAppAndGoToHomescreen);

    statusBarIconArea.x = 90;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) app_menu_icon_data, mainFramebuffer);
    addTouchPoint(statusBarIconArea, exitAppAndGoToAppMenu);

    FontProperties *properties = new FontProperties();
    properties->fg_color = WHITE;
    properties->bg_color = BLACK;

    // Date
    int x = 150;
    int y = 45;
    write_mode(
        TEXT_FONT_BOLD, 
        getTimeDate(), 
        &x, 
        &y, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    // Time
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
        mainFramebuffer, 
        WHITE_ON_BLACK, 
        properties
    );

    // Wifi SSID
    epd_get_text_dimensions(TEXT_FONT_BOLD, WIFI_SSID, &width, &height);
    x = EPD_WIDTH - 145 - width;
    y = 45;
    write_mode(
        TEXT_FONT_BOLD, 
        WIFI_SSID, 
        &x, 
        &y, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    // Wifi and speaker icons
    statusBarIconArea.x = EPD_WIDTH - 120;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) wifi_small_icon_data, mainFramebuffer);
    statusBarIconArea.x = EPD_WIDTH - 60;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) speaker_icon_data, mainFramebuffer);

    statusBarIconArea.x = EPD_WIDTH - 145 - width;
    statusBarIconArea.width = 145 + width;
    addTouchPoint(statusBarIconArea, displayControlPanel);
    
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