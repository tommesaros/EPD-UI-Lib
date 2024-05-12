/*******************************************************************
    
*******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <OpenWeather.h>

// ----------------------------
// Internal libraries
// ----------------------------
#include "include/fonts.h"
#include "include/components.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/black_bg/alarm_icon.h"
#include "../../../image/black_bg/spotify_line_icon.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../../include/handlers/epd_handler.h"
#include "../../include/handlers/touch_handler.h"
#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/handlers/weather_handler.h"
#include "../../include/handlers/time_handler.h"
#include "../../include/handlers/spotify_handler.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/system/homescreen.h"
#include "../../include/apps/spotify/spotify.h"
#include "../../include/apps/weather/weather.h"

TaskHandle_t updateTimeHomeScreenHandle = NULL;

void homeExit() {
    // epd_sleep();
}

void openAlarm() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    //TODO ScreenAlarm();
}

void openSpotify() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    ScreenSpotify();
}

void openWeather() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    ScreenWeather();
}

void openControlPanel() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    //TODO ScreenControlPanel();
}

void openBusDepartures() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    //TODO ScreenBusDepartures();
}

void toggleLights() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    //TODO toggle button;
}

void updateTimeHomeScreen(void *parameter) {
    int cursor_x;
    int cursor_y;
    uint8_t *mainFramebuffer = GetMainFramebuffer();
    char time[6];
    int32_t width = 0;
    int32_t height = 0;
    Rect_t timeArea = {
        0, 
        STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 50, 
        EPD_WIDTH / 4, 
        100
    };
    int hour;
    int minute;
    GFXfont *font = (GFXfont *)&OpenSans26B;
    bool firstRun = true;

    while (true) {
        epd_fill_rect(
            0, 
            STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 50, 
            EPD_WIDTH / 4, 
            100, 
            255, 
            mainFramebuffer
        );

        hour = TimeGetHour();
        minute = TimeGetMinute();
        sprintf(time, "%02d:%02d", TimeGetHour(), TimeGetMinute());
        epd_get_text_dimensions(font, time, &width, &height);
        cursor_x = EPD_WIDTH / 8 - width / 2;
        cursor_y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + height / 2;
        
        write_mode(
            font, 
            time, 
            &cursor_x, 
            &cursor_y, 
            mainFramebuffer, 
            BLACK_ON_WHITE, 
            NULL
        );
        
        if (firstRun) {
            firstRun = false;
        } else {
            epd_clear_area_cycles(timeArea, 2, 50);
            epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);
        }

        vTaskDelay(pdMS_TO_TICKS(60000)); // Delay for 1 minute
    }
}

void ScreenHome() {
    uint8_t *mainFramebuffer = GetMainFramebuffer();

    ClearTouchPoints();
    CleanFramebuffer(mainFramebuffer, epd_full_screen());

    if (updateTimeHomeScreenHandle == NULL) {
        xTaskCreatePinnedToCore(
            updateTimeHomeScreen,    // Task function
            "updateTimeHomeScreen",  // Task name
            5000,              // Stack size (in words)
            NULL,              // Task parameter
            1,                 // Task priority
            &updateTimeHomeScreenHandle,              // Task handle
            tskNO_AFFINITY     // Core number (0 or 1)
        );
    }

    epd_draw_status_bar(homeExit);

    
    // 1st column of information cards
    Rect_t cardArea = {
        EPD_WIDTH / 2 - 150, 
        STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 170, 
        300, 
        100
    };
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "Alarm",
        "tomorrow 7:20",
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openAlarm
    );

    CurrentWeather *current = getCurrentWeather();

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 50;
    epd_draw_horizontal_card(
        const_cast<uint8_t*>(getWeatherIcon(current->icon)),
        alarm_icon_width,
        alarm_icon_height,
        "Weather",
        current->temperature.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openWeather
    );

    char trackName[15];
    strncpy(trackName, getTrackName(), 14);

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 70;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(spotify_line_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "Spotify",
        trackName,
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openSpotify
    );

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer); 
}
