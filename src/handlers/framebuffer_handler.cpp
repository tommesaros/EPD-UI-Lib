#include <Arduino.h>
#include "epd_driver.h"

#include "../include/handlers/framebuffer_handler.h"

uint8_t *main_framebuffer;
uint8_t *statusbar_framebuffer;
uint8_t *notification_framebuffer;
uint8_t *popup_framebuffer;

uint8_t* CreateFramebuffer() {
    uint8_t *framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer) {
        Serial.println("Failed to allocate memory!");
        while (1) ;
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    return framebuffer;
}

void FramebufferSetup() {
    main_framebuffer = CreateFramebuffer();
    statusbar_framebuffer = CreateFramebuffer();
    notification_framebuffer = CreateFramebuffer();
    popup_framebuffer = CreateFramebuffer();
}

void CleanFramebuffer(uint8_t *framebuffer, Rect_t area) {
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    epd_clear_area_cycles(area, 2, 50);
}

uint8_t* GetMainFramebuffer() {
    return main_framebuffer;
}

uint8_t* GetStatusbarFramebuffer() {
    return statusbar_framebuffer;
}

uint8_t* GetNotificationFramebuffer() {
    return notification_framebuffer;
}

uint8_t* GetPopupFramebuffer() {
    return popup_framebuffer;
}
