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
#include "../include/apps/system/app_menu.h"
#include "../include/apps/system/homescreen.h"

TaskHandle_t updateTimeTaskHandle = NULL;

void updateTimeTask(void *parameter) {
    //vacsi black border
    //touchable buttons
    int32_t cursor_x = EPD_WIDTH / 2;
    int32_t cursor_y = 45;
    uint8_t *mainFramebuffer = GetMainFramebuffer();
    char time[6];
    int32_t width = 0;
    int32_t height = 0;
    FontProperties *properties = new FontProperties();
    properties->fg_color = 15;
    properties->bg_color = 0;
    Rect_t dateArea = {150, 10, 200, 50};
    Rect_t timeArea = {EPD_WIDTH / 2 - 40, 10, 80, 50};
    int hour;
    int minute;
    GFXfont *font = (GFXfont *)&OpenSans12;
    int refreshCount = 0;

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(60000)); // Delay for 1 minute
        epd_poweron();

        if (refreshCount == 20) {
            epd_clear_area_cycles(epd_full_screen(), 4, 25);
            refreshCount = 0;
        } else {
            epd_clear_area_cycles(timeArea, 2, 50);
            refreshCount++;
        }
        
        hour = TimeGetHour();
        minute = TimeGetMinute();

        if (hour == 0 && minute == 0) {
            epd_clear_area_cycles(dateArea, 2, 50);
            epd_fill_rect(150, 11, 200, 49, 255, mainFramebuffer);
            epd_fill_rect(150, 11, 200, 49, 0, mainFramebuffer);

            cursor_x = 150;
            write_mode(
                font, 
                getTimeDate(), 
                &cursor_x, 
                &cursor_y, 
                mainFramebuffer, 
                WHITE_ON_BLACK,
                properties
            );
        }
        epd_fill_rect(EPD_WIDTH / 2 - 40, 11, 80, 49, 255, mainFramebuffer);
        epd_fill_rect(EPD_WIDTH / 2 - 40, 11, 80, 49, 0, mainFramebuffer);
        
        sprintf(time, "%02d:%02d", TimeGetHour(), TimeGetMinute());
        epd_get_text_dimensions(font, time, &width, &height);
        cursor_x = EPD_WIDTH / 2 - width / 2;
        
        write_mode(
            font, 
            time, 
            &cursor_x, 
            &cursor_y, 
            mainFramebuffer, 
            WHITE_ON_BLACK, 
            properties
        );
        
        epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);

        epd_poweroff();
    }
}

void epd_draw_status_bar() {
    uint8_t *mainFramebuffer = GetMainFramebuffer();
    epd_fill_rounded_rect(10, 10, EPD_WIDTH - 20, 50, 20, 0, mainFramebuffer);

    Rect_t statusBarIconArea = {
        .x = 30,
        .y = 20,
        .width = home_icon_width,
        .height = home_icon_height
    };
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) home_icon_data, mainFramebuffer);
    AddTouchPoint(
        statusBarIconArea.y, 
        statusBarIconArea.y, 
        statusBarIconArea.width, 
        statusBarIconArea.height, 
        ScreenHome
    );

    statusBarIconArea.x = 90;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) app_menu_icon_data, mainFramebuffer);
    AddTouchPoint(
        statusBarIconArea.y, 
        statusBarIconArea.y, 
        statusBarIconArea.width, 
        statusBarIconArea.height, 
        ScreenAppMenu
    );

    GFXfont *font = (GFXfont *)&OpenSans12;
    FontProperties *properties = new FontProperties();
    properties->fg_color = 15;
    properties->bg_color = 0;

    int cursor_x = 150;
    int cursor_y = 45;
    write_mode(
        font, 
        getTimeDate(), 
        &cursor_x, 
        &cursor_y, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    int32_t width = 0;
    int32_t height = 0;
    char time[6];
    sprintf(time, "%02d:%02d", TimeGetHour(), TimeGetMinute());
    epd_get_text_dimensions((GFXfont *)&OpenSans12, time, &width, &height);
    cursor_x = EPD_WIDTH / 2 - width / 2;
    
    write_mode(
        (GFXfont *)&OpenSans12, 
        time, 
        &cursor_x, 
        &cursor_y, 
        mainFramebuffer, 
        WHITE_ON_BLACK, 
        properties
    );

    epd_get_text_dimensions(font, WIFI_SSID, &width, &height);
    cursor_x = EPD_WIDTH - 145 - width;
    cursor_y = 45;
    write_mode(
        font, 
        WIFI_SSID, 
        &cursor_x, 
        &cursor_y, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    statusBarIconArea.x = EPD_WIDTH - 120;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) wifi_small_icon_data, mainFramebuffer);

    statusBarIconArea.x = EPD_WIDTH - 60;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) speaker_icon_data, mainFramebuffer);
    AddTouchPoint(
        EPD_WIDTH - 145 - width, 
        statusBarIconArea.y, 
        145 + width, 
        statusBarIconArea.height, 
        ScreenControlPanel
    );
    
    if (updateTimeTaskHandle == NULL) {
        xTaskCreatePinnedToCore(
            updateTimeTask,    // Task function
            "updateTimeTask",  // Task name
            5000,              // Stack size (in words)
            NULL,              // Task parameter
            1,                 // Task priority
            &updateTimeTaskHandle,              // Task handle
            tskNO_AFFINITY     // Core number (0 or 1)
        );
    }
}