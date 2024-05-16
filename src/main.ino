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
#include "include/apps/system/homescreen.h"

// This is all the code that is run during the startup process.
void setup()
{
    Serial.begin(115200);
    wifiSetup();
    epdSetup();
    framebufferSetup();
    displayWiFiInitMessage();
    spotifySetup();
    weatherSetup();
    timeSetup();
    TouchClass touch = touchSetup();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
    }

    displayHomeScreen();
}

// Has to be here because of the Arduino Core framework structure.
// In an ideal case, there should be no code.
// Can be used for testing.
void loop()
{
    delay(1000);
}

