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
#include "../../include/apps/system/homescreen.h"
#include "../../include/apps/spotify/spotify.h"
#include "../../include/apps/weather/weather.h"

void homeExit() {
    //TODO
}

void ScreenHome() {
    uint8_t *mainFramebuffer = GetMainFramebuffer();

    ClearTouchPoints();
    CleanFramebuffer(mainFramebuffer, epd_full_screen());
    epd_draw_status_bar(homeExit);

    epd_draw_circle_button_label(
        "ahoj", 
        (GFXfont *)&OpenSans10B,
        100, 
        450, 
        40, 
        0, 
        15, 
        mainFramebuffer,
        ScreenSpotify
    );
    epd_draw_circle_button_label(
        "9", 
        (GFXfont *)&OpenSans16B,
        230, 
        450, 
        40, 
        15, 
        0, 
        mainFramebuffer,
        ScreenWeather
    );

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer); 
}
