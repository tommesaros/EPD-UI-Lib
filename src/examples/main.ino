#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include "../../temp/image/logo.h"
#include "../../font/firasans.h"
#include "../../font/opensans24b.h"
#include "../../font/opensans9.h"
#include <Wire.h>
#include <touch.h>
#include "../../temp/image/lilygo.h"
#include "../pins.h"

TouchClass touch;
uint8_t *framebuffer = NULL;
uint8_t *framebuffer2 = NULL;

const char overview[] = {
    "Frame 1 +ľščťžýáíéúäô§-.\n"\
    "➸ 448 KB ROM & External 16MBytes falsh\n"\
    "➸ 520 KB SRAM & External 16MBytes PSRAM\n"\
};

const char mcu_features[] = {
    "Frame 2 +ľščťžýáíéúäô§-.\n"\
    "➸ 448 KB ROM & External 16MBytes falsh\n"\
    "➸ 520 KB SRAM & External 16MBytes PSRAM\n"\
};

const char srceen_features[] = {
    "Frame 3 +ľščťžýáíéúäô§-.\n"\
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

const FontProperties props = {
    .fg_color = 15,
    .bg_color = 0,
    .fallback_glyph = 0,
    .flags = 0
};

void setup()
{
    Serial.begin(115200);
    epd_init();

    pinMode(TOUCH_INT, INPUT_PULLUP);

    Wire.begin(TOUCH_SDA, TOUCH_SCL);

    if (!touch.begin()) {
        Serial.println("start touchscreen failed");
        while (1);
    }
    Serial.println("Started Touchscreen poll...");

    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer) {
        Serial.println("alloc memory failed !!!");
        while (1);
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_poweron();
    epd_clear();

    write_string((GFXfont *)&FiraSans, "Initial frame", &cursor_x, &cursor_y, framebuffer);

    //Draw Box
    epd_draw_rect(600, 450, 120, 60, 0, framebuffer);
    cursor_x = 615;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "Prev", &cursor_x, &cursor_y, framebuffer);

    epd_draw_rect(740, 450, 120, 60, 0, framebuffer);
    cursor_x = 755;
    cursor_y = 490;
    writeln((GFXfont *)&FiraSans, "Next", &cursor_x, &cursor_y, framebuffer);
    

    Rect_t area = {
        .x = 160,
        .y = 420,
        .width = lilygo_width,
        .height =  lilygo_height
    };
    // epd_copy_to_framebuffer(area, (uint8_t *) lilygo_data, framebuffer);

    epd_draw_rect(10, 20, EPD_WIDTH - 20, EPD_HEIGHT / 2 + 80, 0, framebuffer);
    
    epd_draw_rect(340, 450, 120, 60, 0, framebuffer);
    cursor_x = 345;
    cursor_y = 490;
    writeln((GFXfont *)&OpenSans9, "Ahoj", &cursor_x, &cursor_y, framebuffer);
    epd_draw_rect(80, 80, 50, 50, 0, framebuffer);
    epd_fill_rect(0, EPD_HEIGHT - 50, 50, 50, 0, framebuffer);
    epd_fill_rect(50, EPD_HEIGHT - 50, 50, 50, 50, framebuffer);
    epd_fill_rect(100, EPD_HEIGHT - 50, 50, 50, 100, framebuffer);
    epd_fill_rect(150, EPD_HEIGHT - 50, 50, 50, 150, framebuffer);
    epd_fill_rect(200, EPD_HEIGHT - 50, 50, 50, 200, framebuffer);
    epd_fill_rect(250, EPD_HEIGHT - 50, 50, 50, 250, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);

    epd_poweroff();

    framebuffer2 = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer2) {
        Serial.println("alloc memory failed !!!");
        while (1);
    }
    memset(framebuffer2, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

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
                // epd_clear_area(area1);
                epd_fill_rect(10, 20, EPD_WIDTH - 20, EPD_HEIGHT / 2 + 80, 150, framebuffer2);
                // write_string((GFXfont *)&OpenSans9, (char *)overview, &cursor_x, &cursor_y, framebuffer2);
                write_mode((GFXfont *)&OpenSans9, (char *)overview, &cursor_x, &cursor_y, framebuffer2, WHITE_ON_WHITE, &props);
                epd_draw_grayscale_image(epd_full_screen(), framebuffer2);
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
                epd_clear_area(area1);
                write_string((GFXfont *)&OpenSans24B, "DeepSleep", &cursor_x, &cursor_y, NULL);
                break;

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
