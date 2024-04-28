#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

// TODO add description to all includes

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Arduino.h>
#include "epd_driver.h"
#include "libjpeg/libjpeg.h"
#include "../font/firasans.h"
#include "../font/opensans12.h"
#include "esp_adc_cal.h"
// #include <FS.h>
// #include <SPI.h>
// #include <SD.h>
// #include <FFat.h>
#include "../image/logo.h" // TODO delete
#include "pins.h"
#include "pins.h"
#include <Wire.h>
#include <touch.h>

#include "time.h"
#include "esp_sntp.h"

#include "include/credentials.h"
#include "include/wifi_event.h"
#include "include/time.h"
#include "include/epd_handler.h"
#include "include/touch_handler.h"

#define DBG_OUTPUT_PORT Serial

uint8_t *main_framebuffer;
TouchClass touch;

void setup() {
    int32_t wifi_cursor_x = 50;
    int32_t wifi_cursor_y = 50;
    
    // Initializing serial port for debugging and monitorin purposes
    Serial.begin(115200);

    // Initializing the screen framebuffer and EPD display
    main_framebuffer = EPDSetup();
    writeln((GFXfont *)&OpenSans12, "edp set up ", &wifi_cursor_x, &wifi_cursor_y, NULL);

    // Initializing the WiFi connection
    
    WiFiSetup();
    writeln((GFXfont *)&OpenSans12, "wifi set up ", &wifi_cursor_x, &wifi_cursor_y, NULL);

    // Initializing the time
    TimeSetup();
    //TODO rename to timesetup, see naming conventions

    // Intializing the touch
    touch = TouchSetup();
    writeln((GFXfont *)&OpenSans12, "touch set up ", &wifi_cursor_x, &wifi_cursor_y, NULL);

    // Initializing the main screen
    int cursor_x;
    int cursor_y;

    epd_draw_rect(600, 450, 120, 60, 0, main_framebuffer);
    cursor_x = 615;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "WiFI", &cursor_x, &cursor_y, main_framebuffer);

    epd_draw_rect(740, 450, 120, 60, 0, main_framebuffer);
    cursor_x = 755;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "Time", &cursor_x, &cursor_y, main_framebuffer);

    epd_draw_grayscale_image(epd_full_screen(), main_framebuffer);

    epd_poweroff();
}


void loop() {
    uint16_t  x, y;

    bool wifi_touched = false;
    bool time_touched = false;

    if (digitalRead(TOUCH_INT)) {
        if (touch.scanPoint()) {
            touch.getPoint(x, y, 0);
            y = EPD_HEIGHT - y;
            
            if ((x > 600 && x < 720) && (y > 450 && y < 510)) {         // WiFI button
                wifi_touched = true;
            } else if ((x > 740 && x < 860) && (y > 450 && y < 510)) {  // Time button
                time_touched = true;
            } else {
                return;
            }

            epd_poweron();
            int32_t wifi_cursor_x = 50;
            int32_t wifi_cursor_y = 150;
            writeln((GFXfont *)&OpenSans12, "Current Time: ", &wifi_cursor_x, &wifi_cursor_y, NULL);
            writeln((GFXfont *)&OpenSans12, getLocalTimeString(), &wifi_cursor_x, &wifi_cursor_y, NULL);
            delay(1000);

            epd_clear();
            epd_poweroff();
            delay(1000);
        }
    }    
}
