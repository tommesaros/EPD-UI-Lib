// Code from Lilygo example library: wifi_sync.ino, 
// https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/tree/esp32s3/examples/wifi_sync
// TODO edit

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"

#include "../include/touch_handler.h"

TouchClass TouchSetup() {
    TouchClass touch;

    pinMode(TOUCH_INT, INPUT_PULLUP);
    Wire.begin(TOUCH_SDA, TOUCH_SCL);

    if (!touch.begin()) {
        Serial.println("start touchscreen failed");
        while (1);
    }

    return (touch);
}