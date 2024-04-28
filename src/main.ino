#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include "../image/logo.h"
#include "../font/firasans.h"
#include <Wire.h>
#include <touch.h>
#include "../image/lilygo.h"
#include "pins.h"
#include <WiFi.h>

#include "../font/opensans12.h"
#include "../font/opensans18.h"
#include "../font/opensans26b.h"


#include "include/wifi_event.h"
#include "include/credentials.h"
#include "include/time.h"
#include "include/epd_handler.h"
#include "include/touch_handler.h"
#include "include/wifi_init.h"

TouchClass touch;
uint8_t *framebuffer = NULL;

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

void setup()
{
    Serial.begin(115200);
    WiFiSetup();
    TimeSetup();
    framebuffer = EPDSetup();
    touch = TouchSetup();

    ScreenWiFiInit();

    while (WiFi.status() != WL_CONNECTED) {
        delay(10000);
    }

    epd_clear();

    //Draw Box
    epd_draw_rect(600, 450, 120, 60, 0, framebuffer);
    cursor_x = 615;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "Prev", &cursor_x, &cursor_y, framebuffer);

    epd_draw_rect(740, 450, 120, 60, 0, framebuffer);
    cursor_x = 755;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "Next", &cursor_x, &cursor_y, framebuffer);

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    
    int32_t wifi_popup_cursor_x = 50;
    int32_t wifi_popup_cursor_y = 450;

    delay(1000);

    writeln((GFXfont *)&OpenSans12, "Connected to ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

    wifi_popup_cursor_x = 50;
    wifi_popup_cursor_y = 490;

    writeln((GFXfont *)&OpenSans12, "Current Time: ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);
    char hour_str[2];
    sprintf(hour_str, "%02d", TimeGetHour());
    writeln((GFXfont *)&OpenSans12, hour_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

    char minute_str[2];
    sprintf(minute_str, "%02d", TimeGetMinute());
    writeln((GFXfont *)&OpenSans12, minute_str, &wifi_popup_cursor_x, &wifi_popup_cursor_y, NULL);

    epd_poweroff();
}


void loop()
{
    uint16_t  x, y;
    if (digitalRead(TOUCH_INT)) {
        if (touch.scanPoint()) {
            touch.getPoint(x, y, 0);
            y = EPD_HEIGHT - y;
            if ((x > 600 && x < 720) && (y > 450 && y < 510)) {
                state--;
            } else if ((x > 740 && x < 860) && (y > 450 && y < 510)) {
                state++;
            } else {
                return;
            }
            state %= 4;
            Serial.print(millis());
            Serial.print(":");
            Serial.println(state);
            epd_poweron();
            cursor_x = 20;
            cursor_y = 60;
            switch (state) {
            case 0:
                epd_clear_area(area1);
                write_string((GFXfont *)&FiraSans, (char *)overview, &cursor_x, &cursor_y, NULL);
                break;
            case 1:
                epd_clear_area(area1);
                write_string((GFXfont *)&FiraSans, (char *)srceen_features, &cursor_x, &cursor_y, NULL);
                break;
            case 2:
                epd_clear_area(area1);
                write_string((GFXfont *)&FiraSans, (char *)mcu_features, &cursor_x, &cursor_y, NULL);
                break;
            case 3:
                

#if defined(T5_47)
                // Set to wake up by GPIO39
                esp_sleep_enable_ext1_wakeup(GPIO_SEL_39, ESP_EXT1_WAKEUP_ALL_LOW);
#elif defined(T5_47_PLUS)
                esp_sleep_enable_ext1_wakeup(GPIO_SEL_21, ESP_EXT1_WAKEUP_ALL_LOW);
#endif
                esp_deep_sleep_start();
                break;
            case 4:
                break;
            default:
                break;
            }
            epd_poweroff();

            while (digitalRead(TOUCH_INT)) {
            }
            while (digitalRead(TOUCH_INT)) {
            }
        }
    }
    delay(10);
}
