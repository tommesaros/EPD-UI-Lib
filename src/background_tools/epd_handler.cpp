// Code from Lilygo example library: wifi_sync.ino, 
// https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/tree/esp32s3/examples/wifi_sync
// TODO edit

#include <Arduino.h>
#include "epd_driver.h"

#include "../include/epd_handler.h"

uint8_t* EPDSetup() {
    epd_init();
    epd_poweron();
    epd_clear();

    uint8_t *main_framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!main_framebuffer) {
        Serial.println("Failed to allocate memory!");
        while (1) ;
    }
    memset(main_framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    
    return(main_framebuffer);
}