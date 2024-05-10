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

#include "include/components/status_bar.h"

uint8_t *mainFramebuffer;

// This is all the code that is run during the startup process.
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

    epd_draw_status_bar();

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer); 
}

// Has to be here because of the Arduino Core framework structure.
// In an ideal case, there should be no code.
// Can be used for testing.
void loop()
{
    delay(1000);
}

