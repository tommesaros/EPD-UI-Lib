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
#include "../../include/apps/alarm/alarm.h"

//tertiary button to add new alarm, card for each alarm

void displayAlarm() {
    
}

/*
epd_draw_circle_button(
        "ahoj", 
        (GFXfont *)&OpenSans10B,
        100, 
        450, 
        40, 
        0, 
        15, 
        mainFramebuffer,
        openSpotify
    );
    
    epd_draw_circle_button(
        "9", 
        (GFXfont *)&OpenSans16B,
        230, 
        450, 
        40, 
        15, 
        0, 
        mainFramebuffer,
        openWeather
    );

*/