// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/handlers/framebuffer_handler.h"

uint8_t *mainFramebuffer;
uint8_t *notificationFramebuffer;
uint8_t *overlayFramebuffer;

uint8_t* createFramebuffer() {
    uint8_t *framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer) {
        Serial.println("Failed to allocate memory!");
        while (1) ;
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    return framebuffer;
}

void framebufferSetup() {
    mainFramebuffer = createFramebuffer();
    notificationFramebuffer = createFramebuffer();
    overlayFramebuffer = createFramebuffer();
}

void cleanFramebufferAndEPD(uint8_t *framebuffer, Rect_t area) {
    epd_fill_rect(area.x, area.y, area.width, area.height, 255, framebuffer);
    epd_clear_area_cycles(area, 2, 50);
}

uint8_t* getMainFramebuffer() {
    return mainFramebuffer;
}

uint8_t* getNotificationFramebuffer() {
    return notificationFramebuffer;
}

uint8_t* getOverlayFramebuffer() {
    return overlayFramebuffer;
}
