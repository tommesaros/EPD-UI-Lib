/*******************************************************************
 * Code based on Lilygo example library: touch.ino, 
 * https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/examples/touch/touch.ino
*******************************************************************/

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

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/handlers/touch_handler.h"

TouchClass touch;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    void (*function)();
} TouchPoint;

const int MAX_TOUCH_POINTS = 30;
TouchPoint touchPoints[MAX_TOUCH_POINTS];
int numTouchPoints = 0;

bool overlayActive = false;
TouchPoint overlayTouchPoints[MAX_TOUCH_POINTS];
int numOverlayTouchPoints = 0;

void touchLoop(void *parameters) {
    uint16_t  x, y;
    while (true) {
        
        if (digitalRead(TOUCH_INT)) {
            if (touch.scanPoint()) {
                touch.getPoint(x, y, 0);
                y = EPD_HEIGHT - y;

                if (overlayActive) {
                    for (int i = 0; i < numOverlayTouchPoints; i++) {
                        if ((x > overlayTouchPoints[i].x && x < (overlayTouchPoints[i].x + overlayTouchPoints[i].width)) 
                            && (y > overlayTouchPoints[i].y && y < (overlayTouchPoints[i].y + overlayTouchPoints[i].height))) {
                            overlayTouchPoints[i].function();
                        }
                    }
                } else {
                    for (int i = 0; i < numTouchPoints; i++) {
                        if ((x > touchPoints[i].x && x < (touchPoints[i].x + touchPoints[i].width)) 
                            && (y > touchPoints[i].y && y < (touchPoints[i].y + touchPoints[i].height))) {
                            touchPoints[i].function();
                        }
                    }
                }
                
                while (digitalRead(TOUCH_INT)) {
                }
                while (digitalRead(TOUCH_INT)) {
                }
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

TouchClass touchSetup() {
    pinMode(TOUCH_INT, INPUT_PULLUP);
    Wire.begin(TOUCH_SDA, TOUCH_SCL);

    if (!touch.begin()) {
        Serial.println("start touchscreen failed");
        while (1);
    }
    
    xTaskCreatePinnedToCore(
        touchLoop,    // Task function
        "touchLoop",  // Task name
        10000,              // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );

    return (touch);
}

void addTouchPoint(Rect_t area, void (*function)()) {
    if (numTouchPoints < MAX_TOUCH_POINTS) {
        touchPoints[numTouchPoints].x = area.x;
        touchPoints[numTouchPoints].y = area.y;
        touchPoints[numTouchPoints].width = area.width;
        touchPoints[numTouchPoints].height = area.height;
        touchPoints[numTouchPoints].function = function;
        numTouchPoints++;
    }
}

void clearTouchPoints() {
    memset(touchPoints, 0, sizeof(touchPoints));
    numTouchPoints = 0;
}

void setOverlayActive(bool state) {
    overlayActive = state;
}

void addOverlayTouchPoint(Rect_t area, void (*function)()) {
    if (numOverlayTouchPoints < MAX_TOUCH_POINTS) {
        overlayTouchPoints[numOverlayTouchPoints].x = area.x;
        overlayTouchPoints[numOverlayTouchPoints].y = area.y;
        overlayTouchPoints[numOverlayTouchPoints].width = area.width;
        overlayTouchPoints[numOverlayTouchPoints].height = area.height;
        overlayTouchPoints[numOverlayTouchPoints].function = function;
        numOverlayTouchPoints++;
    }
}

void clearOverlayTouchPoints() {
    memset(overlayTouchPoints, 0, sizeof(overlayTouchPoints));
    numOverlayTouchPoints = 0;
}

void dummyFunction() {
}