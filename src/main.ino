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

TouchClass touch;

const char overview[] = {
    "   ESP32 is a single 2.4 GHz Wi-Fi-and-Bluetooth\n"\
    "combo chip designed with the TSMC ultra-low-po\n"\
    "wer 40 nm technology. It is designed to achieve \n"\
    "the best power and RF performance, showing rob\n"\
    "ustness versatility and reliability in a wide variet\n"\
    "y of applications and power scenarios.\n"\
};

const char mcu_features[] = {
    "➸ Xtensa® dual-core 32-bit LX6 microprocessor\n"\
    "➸ 448 KB ROM & External 16MBytes falsh\n"\
    "➸ 520 KB SRAM & External 16MBytes PSRAM\n"\
    "➸ 16 KB SRAM in RTC\n"\
    "➸ Multi-connections in Classic BT and BLE\n"\
    "➸ 802.11 n (2.4 GHz), up to 150 Mbps\n"\
};

const char srceen_features[] = {
    "➸ 16 color grayscale\n"\
    "➸ Use with 4.7\" EPDs\n"\
    "➸ High-quality font rendering\n"\
    "➸ ~630ms for full frame draw\n"\
};


// const char *string_array[] = {overview, mcu_features, srceen_features};

int cursor_x = 20;
int cursor_y = 60;

Rect_t area1 = {
    .x = 10,
    .y = 20,
    .width = EPD_WIDTH - 20,
    .height =  EPD_HEIGHT / 2 + 80
};
uint8_t state = 1;
uint8_t buf[2] = {0xD1, 0X05};
uint8_t *mainFramebuffer;

void updateTimeTask(void *parameter) {
    // do handleru?
    //TODO theres no need to update the time everytime from the server
    //TODO do not print 99:99
    int32_t wifi_popup_cursor_x = 50;
    int32_t wifi_popup_cursor_y = 490;
    while (true) {
        // Update the time here
        epd_poweron();
        writeln((GFXfont *)&OpenSans12, "Current Time: ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
        char hour_str[2];
        sprintf(hour_str, "%02d", TimeGetHour());
        writeln((GFXfont *)&OpenSans12, hour_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

        char minute_str[2];
        sprintf(minute_str, "%02d", TimeGetMinute());
        writeln((GFXfont *)&OpenSans12, minute_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
        epd_poweron();

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
    // WeatherSetup();
    TimeSetup();
    touch = TouchSetup();
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
    }

    mainFramebuffer = GetMainFramebuffer();

    CleanFramebuffer(mainFramebuffer, epd_full_screen());

    //Draw Box
    epd_draw_rect(600, 450, 120, 60, 0, mainFramebuffer);
    cursor_x = 615;
    cursor_y = 490;
    writeln((GFXfont *)&OpenSans12, "Prev", &cursor_x, &cursor_y, mainFramebuffer);

    epd_draw_rect(740, 450, 120, 60, 0, mainFramebuffer);
    cursor_x = 755;
    cursor_y = 490;
    writeln((GFXfont *)&OpenSans12, "Next", &cursor_x, &cursor_y, mainFramebuffer);

    epd_draw_rounded_rect(10, 20, EPD_WIDTH - 20, EPD_HEIGHT / 2 + 80, 40, 0, mainFramebuffer);

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);

    delay(5000);

    epd_fill_rounded_rect(10, 20, EPD_WIDTH - 20, EPD_HEIGHT / 2 + 80, 40, 0, mainFramebuffer);

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);
    
    int32_t wifi_popup_cursor_x = 50;
    int32_t wifi_popup_cursor_y = 450;

    delay(1000);

    writeln((GFXfont *)&OpenSans12, "Connected to ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

    wifi_popup_cursor_x = 50;
    wifi_popup_cursor_y = 490;

    xTaskCreatePinnedToCore(
        updateTimeTask,    // Task function
        "UpdateTimeTask",  // Task name
        5000,              // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );
    //TODO task handle can be used to delete the task!!
}


void loop()
{
    uint16_t  x, y;
    if (digitalRead(TOUCH_INT)) {
        if (touch.scanPoint()) {
            touch.getPoint(x, y, 0);
            y = EPD_HEIGHT - y;
            if ((x > 600 && x < 720) && (y > 450 && y < 510)) {
                int32_t wifi_popup_cursor_x = 50;
                int32_t wifi_popup_cursor_y = 420;
                writeln((GFXfont *)&OpenSans12, "stlačené", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
                ScreenSpotify(mainFramebuffer);
            } else if ((x > 740 && x < 860) && (y > 450 && y < 510)) {
                ScreenWeather(mainFramebuffer);
            } else {
                
                return;
            }
            
            
            while (digitalRead(TOUCH_INT)) {
            }
        }
    }
    delay(10);
}

