/*******************************************************************
    Based on the OpenWeather API Example:
    My_OpenWeather_Test.ino
    https://github.com/Bodmer/OpenWeather/blob/main/examples/Onecall%20API%20(subscription%20required)/My_OpenWeather_Test/My_OpenWeather_Test.ino
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
#include "../../include/apps/weather/weather.h"

void ScreenWeather(uint8_t * framebuffer) {
    CleanFramebuffer(framebuffer, epd_full_screen());

    int cursor_x = 20; //TODO relative to mainbuffer
    int cursor_y = 140;

    writeln((GFXfont *)&OpenSans12, "Pocko ", &cursor_x, &cursor_y, framebuffer);
    CurrentWeather *current = getCurrentWeather();
    writeln((GFXfont *)&OpenSans12, current->temperature.c_str(), &cursor_x, &cursor_y, framebuffer);
    writeln((GFXfont *)&OpenSans12, current->description.c_str(), &cursor_x, &cursor_y, framebuffer);

    writeln((GFXfont *)&OpenSans12, "Zajtra: ", &cursor_x, &cursor_y, framebuffer);
    DailyWeather *daily = getDayWeather(4);
    writeln((GFXfont *)&OpenSans12, daily->temp_max.c_str(), &cursor_x, &cursor_y, framebuffer);
    writeln((GFXfont *)&OpenSans12, daily->description.c_str(), &cursor_x, &cursor_y, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // manual update button
}

