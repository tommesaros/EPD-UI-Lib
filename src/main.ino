#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Arduino.h>
#include "epd_driver.h"
#include "libjpeg/libjpeg.h"
#include "../font/firasans.h"
#include "esp_adc_cal.h"
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include <FFat.h>
#include "../image/logo.h"
#include "pins.h"

#include "include/credentials.h"
#include "include/wifi_event.h"

#define DBG_OUTPUT_PORT Serial

uint8_t *framebuffer;

void setup()
{
    // Initializing serial port for debugging and monitorin purposes
    Serial.begin(115200);

    // Initializing the EPD display
    epd_init();
    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer) {
        Serial.println("Failed to allocate memory!");
        while (1) ;
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_poweron();
    epd_clear();

    // Initializing the WiFi connection
    WiFi.disconnect();
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.onEvent(WiFiEvent);
    delay(5000);
}


void loop()
{
    epd_poweron();
    epd_draw_hline(10, random(10, EPD_HEIGHT), EPD_WIDTH - 20, 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(1000);

    epd_draw_rect(10, random(10, EPD_HEIGHT), random(10, 60), random(10, 120), 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(1000);

    epd_draw_circle(random(10, EPD_WIDTH), random(10, EPD_HEIGHT), 120, 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(1000);

    epd_fill_rect(10, random(10, EPD_HEIGHT), random(10, 60), random(10, 120), 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(1000);

    epd_fill_circle(random(10, EPD_WIDTH), random(10, EPD_HEIGHT), random(10, 160), 0, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    delay(1000);


    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_clear();
    epd_poweroff();
    delay(1000);
}
