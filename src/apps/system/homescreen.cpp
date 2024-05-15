/*******************************************************************
    //TODO Description
    //Here you can place all your app shortcuts and widgets in 
    //form of interactive cards that show current information
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
#include "include/colors.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/black_bg/alarm_icon.h"
#include "../../../image/black_bg/spotify_line_icon.h"
#include "../../../image/black_bg/bus_icon.h"
#include "../../../image/black_bg/home_icon.h"

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
#include "../../include/apps/system/control_panel.h"
#include "../../include/apps/spotify/spotify.h"
#include "../../include/apps/weather/weather.h"

TaskHandle_t updateTimeHomeScreenHandle = NULL;

void homeExit() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    //TODO power off popup and then show image 
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
    displaySpotify();
}

void openWeather() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    displayWeather();
}

void openControlPanel() {
    vTaskDelete(updateTimeHomeScreenHandle);
    updateTimeHomeScreenHandle = NULL;
    displayControlPanel();
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

void triggerDoorLock() {
    epd_trigger_notification(
        const_cast<uint8_t*>(home_icon_data),
        home_icon_width,
        home_icon_height,
        "Door opened", 
        "Hallway door is open for 30 seconds." 
    );
}

void updateTimeHomeScreen(void *parameter) {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    
    Rect_t timeArea = {
        0, 
        SCREEN_MIDDLE_WITH_STATUS_BAR - 50, 
        EPD_WIDTH / 4, 
        100
    };
    char time[6];
    int hour;
    int minute;
    bool firstRun = true;

    int x;
    int y;
    int32_t width = 0;
    int32_t height = 0;
    
    while (true) {
        // Cover up the old time
        epd_fill_rect(
            0, 
            SCREEN_MIDDLE_WITH_STATUS_BAR - 50, 
            EPD_WIDTH / 4, 
            100, 
            epd_convert_font_color(WHITE),
            mainFramebuffer
        );

        hour = timeGetHour();
        minute = timeGetMinute();
        sprintf(time, "%02d:%02d", timeGetHour(), timeGetMinute());

        epd_get_text_dimensions(HEADLINE_FONT, time, &width, &height);
        x = EPD_WIDTH / 8 - width / 2;
        y = SCREEN_MIDDLE_WITH_STATUS_BAR + height / 2;
        write_mode(
            HEADLINE_FONT, 
            time, 
            &x, 
            &y, 
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

void displayHomeScreen() {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    clearTouchPoints();
    cleanFramebufferAndEPD(mainFramebuffer, epd_full_screen());

    if (updateTimeHomeScreenHandle == NULL) {
        xTaskCreatePinnedToCore(
            updateTimeHomeScreen,           // Task function
            "updateTimeHomeScreen",         // Task name
            5000,                           // Stack size (in words)
            NULL,                           // Task parameter
            1,                              // Task priority
            &updateTimeHomeScreenHandle,    // Task handle
            tskNO_AFFINITY                  // Core number (0 or 1)
        );
    }

    epd_draw_status_bar(homeExit);

    // Alarm card
    Rect_t cardArea = {
        EPD_WIDTH / 2 - SMALL_CARD_WIDTH / 2, 
        SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT * 1.5 - CARD_PADDING, 
        SMALL_CARD_WIDTH, 
        SMALL_CARD_HEIGHT
    };
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "Alarm",
        "tomorrow 7:20", // dummy data
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openAlarm
    );

    // Weather card
    CurrentWeather *current = getCurrentWeather();
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT / 2;
    epd_draw_horizontal_card(
        const_cast<uint8_t*>(getWeatherIcon(current->icon)), //icon of current weather
        alarm_icon_width,
        alarm_icon_height,
        "Weather",
        current->temperature.c_str(),
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openWeather
    );

    //Avoiding too long track names that would overflow the card
    char trackName[15];
    strncpy(trackName, getTrackName(), 14);

    // Spotify card
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR + SMALL_CARD_HEIGHT / 2 + CARD_PADDING;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(spotify_line_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "Spotify",
        trackName,
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openSpotify
    );

    // Bus departures card
    cardArea.x = EPD_WIDTH / 2 + SMALL_CARD_WIDTH / 2 + CARD_PADDING;
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT * 1.5 - CARD_PADDING;
    cardArea.width = SMALL_CARD_HEIGHT;
    epd_draw_vertical_card(
        const_cast<uint8_t *>(bus_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "",
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        openBusDepartures
    );

    // Doorlock card
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT / 2;
    cardArea.width = SMALL_CARD_HEIGHT;
    epd_draw_vertical_card(
        const_cast<uint8_t *>(bus_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "",
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        triggerDoorLock
    );

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer); 
}
