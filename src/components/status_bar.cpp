// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/fonts.h"
#include "../include/components/status_bar.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

// ----------------------------
// Credentials
// ----------------------------
#include "../include/credentials.h"

// ----------------------------
// Icons
// ----------------------------
#include "../image/black_bg/home_icon.h"
#include "../image/black_bg/app_menu_icon.h"
#include "../image/black_bg/speaker_icon.h"
#include "../image/black_bg/wifi_small_icon.h"

void epd_draw_status_bar() {
    uint8_t *mainFramebuffer = GetMainFramebuffer();
    epd_fill_rounded_rect(10, 10, EPD_WIDTH - 20, 50, 20, 0, mainFramebuffer);

    Rect_t statusBarIconArea = {
        .x = 30,
        .y = 20,
        .width = home_icon_width,
        .height =  home_icon_height
    };
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) home_icon_data, mainFramebuffer);

    statusBarIconArea.x = 90;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) app_menu_icon_data, mainFramebuffer);

    GFXfont *font = (GFXfont *)&OpenSans12;
    int32_t width = 0;
    int32_t height = 0;
    epd_get_text_dimensions(font, WIFI_SSID, &width, &height);

    FontProperties *properties = new FontProperties();
    properties->fg_color = 15;
    properties->bg_color = 0;

    int cursor_x = EPD_WIDTH - 90 - width;
    int cursor_y = 45;
    write_mode(
        font, 
        WIFI_SSID, 
        &cursor_x, 
        &cursor_y, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties);

    statusBarIconArea.x = EPD_WIDTH - 130 - width;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) wifi_small_icon_data, mainFramebuffer);

    statusBarIconArea.x = EPD_WIDTH - 60;
    epd_copy_to_framebuffer(statusBarIconArea, (uint8_t *) speaker_icon_data, mainFramebuffer);

    
}