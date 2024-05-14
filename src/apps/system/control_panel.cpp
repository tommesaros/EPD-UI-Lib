/*******************************************************************
    
*******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <OpenWeather.h>

// ----------------------------
// Internal libraries
// ----------------------------
#include "include/fonts.h"
#include "include/components.h"

// ----------------------------
// Images
// ----------------------------
//TODO: Add images

// ----------------------------
// Handlers
// ----------------------------
#include "../../include/handlers/epd_handler.h"
#include "../../include/handlers/touch_handler.h"
#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/handlers/weather_handler.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../../include/credentials.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/system/control_panel.h"

bool firstCheckBox = true;
bool secondCheckBox = false;

void toggle() {
    //draw opposite of what it is
}

void ScreenControlPanel() {
    //TODO black background
    //TODO popup framebuffer
    uint8_t *mainFramebuffer = GetMainFramebuffer();
    epd_draw_check_box(
        "Ahoj", 
        (GFXfont *)&OpenSans12B,
        20, 
        100, 
        0,
        15, 
        firstCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_check_box(
        "Caaau", 
        (GFXfont *)&OpenSans12B,
        20, 
        150, 
        0,
        15, 
        secondCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Ahoj", 
        (GFXfont *)&OpenSans12B,
        20, 
        200, 
        0,
        15, 
        firstCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Caaau", 
        (GFXfont *)&OpenSans12B,
        20, 
        250, 
        0,
        15, 
        secondCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_progress_bar(
        20, 
        300, 
        300, 
        15, 
        15, 
        3, 
        mainFramebuffer
    );

    epd_fill_rect(20, 380, 100, 20, 100, mainFramebuffer);
    epd_fill_rect(20, 400, 100, 20, 200, mainFramebuffer);
    epd_fill_rect(20, 420, 100, 20, 220, mainFramebuffer);
    epd_fill_rect(20, 440, 100, 20, 240, mainFramebuffer);
    epd_fill_rect(20, 440, 100, 20, 150, mainFramebuffer);

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);
}