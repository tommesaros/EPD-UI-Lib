#include <Arduino.h>
#include "epd_driver.h"

#include "../include/handlers/framebuffer_handler.h"

uint8_t *main_framebuffer;
uint8_t *statusbar_framebuffer;
uint8_t *notification_framebuffer;
uint8_t *popup_framebuffer;

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
    main_framebuffer = createFramebuffer();
    statusbar_framebuffer = createFramebuffer();
    notification_framebuffer = createFramebuffer();
    popup_framebuffer = createFramebuffer();
}

void cleanFramebufferAndEPD(uint8_t *framebuffer, Rect_t area) {
    epd_fill_rect(area.x, area.y, area.width, area.height, 255, framebuffer);
    epd_clear_area_cycles(area, 2, 50);
}

uint8_t* getMainFramebuffer() {
    return main_framebuffer;
}

uint8_t* getNotificationFramebuffer() {
    return notification_framebuffer;
}

uint8_t* getPopupFramebuffer() {
    return popup_framebuffer;
}
