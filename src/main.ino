#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <WiFi.h>
#include <ArduinoJson.h>

// ----------------------------
// Internal libraries
// ----------------------------
#include "include/credentials.h"
#include "include/fonts.h"
#include "include/components.h"

// ----------------------------
// Handlers
// ----------------------------
#include "include/handlers/wifi_handler.h"
#include "include/handlers/time_handler.h"
#include "include/handlers/epd_handler.h"
#include "include/handlers/touch_handler.h"
#include "include/handlers/framebuffer_handler.h"
#include "include/handlers/spotify_handler.h"
#include "include/handlers/weather_handler.h"

// ----------------------------
// Apps
// ----------------------------
#include "include/apps/system/wifi_init.h"
#include "include/apps/spotify/spotify.h"
#include "include/apps/weather/weather.h"

uint8_t *mainFramebuffer;

void updateTimeTask(void *parameter) {
    // do handleru?
    //TODO theres no need to update the time everytime from the server
    //TODO do not print 99:99
    int32_t wifi_popup_cursor_x;
    int32_t wifi_popup_cursor_y;
    while (true) {
        wifi_popup_cursor_x = 50;
        wifi_popup_cursor_y = 490;

        // Update the time here
        epd_poweron();
        writeln((GFXfont *)&OpenSans12, "Current Time: ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
        char hour_str[3];
        sprintf(hour_str, "%02d", TimeGetHour());
        writeln((GFXfont *)&OpenSans12, hour_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

        char minute_str[3];
        sprintf(minute_str, "%02d", TimeGetMinute());
        writeln((GFXfont *)&OpenSans12, minute_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

        vTaskDelay(pdMS_TO_TICKS(60000)); // Delay for 1 minute
    }
}

void setup()
{
    Serial.begin(115200);
    WiFiSetup();
    EPDSetup();
    FramebufferSetup();
    ScreenWiFiInit();
    SpotifySetup();
    WeatherSetup();
    TimeSetup();
    TouchClass touch = TouchSetup();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
    }

    mainFramebuffer = GetMainFramebuffer();

    CleanFramebuffer(mainFramebuffer, epd_full_screen());

    //Draw Box
    epd_draw_rect(600, 450, 120, 60, 0, mainFramebuffer);
    int cursor_x = 615;
    int cursor_y = 490;
    writeln((GFXfont *)&OpenSans12, "Prev", &cursor_x, &cursor_y, mainFramebuffer);

    epd_draw_rect(740, 450, 120, 60, 0, mainFramebuffer);
    cursor_x = 755;
    cursor_y = 490;
    writeln((GFXfont *)&OpenSans12, "Next", &cursor_x, &cursor_y, mainFramebuffer);
    
    int32_t wifi_popup_cursor_x = 50;
    int32_t wifi_popup_cursor_y = 450;

    writeln((GFXfont *)&OpenSans12, "Connected to ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, mainFramebuffer);
    writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_popup_cursor_x, &wifi_popup_cursor_y, mainFramebuffer);

    epd_draw_circle_button_label(
        "ahoj", 
        (GFXfont *)&OpenSans10B,
        100, 
        450, 
        40, 
        0, 
        15, 
        mainFramebuffer,
        ScreenSpotify
    );
    epd_draw_circle_button_label(
        "9", 
        (GFXfont *)&OpenSans16B,
        230, 
        450, 
        40, 
        15, 
        0, 
        mainFramebuffer,
        ScreenWeather
    );

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);

    delay(1000);

    xTaskCreatePinnedToCore(
        updateTimeTask,    // Task function
        "updateTimeTask",  // Task name
        5000,              // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );

    //ScreenWeather(mainFramebuffer);
    //ScreenSpotify(mainFramebuffer);

    //TODO task handle can be used to delete the task!!    
}


void loop()
{
    delay(1000);
}

