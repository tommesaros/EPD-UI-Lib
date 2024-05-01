/*******************************************************************
    Based on the Spotify Arduino Library Example: 
    getCurrentlyPlaying.ino and playerControls.ino
    https://github.com/witnessmenow/spotify-api-arduino/blob/main/examples/getCurrentlyPlaying/getCurrentlyPlaying.ino
    https://github.com/witnessmenow/spotify-api-arduino/tree/main/examples/playerControls

    Message from the original author:
    Written by Brian Lough
    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduino.h>
#include <ArduinoJson.h>

// ----------------------------
// Fonts
// ----------------------------
#include "../../../font/opensans12.h"
#include "../../../font/opensans18.h"
#include "../../../font/opensans26b.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../../include/handlers/epd_handler.h"
#include "../../include/handlers/touch_handler.h"
#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/handlers/spotify_handler.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../../include/credentials.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/spotify/spotify.h"

int lastChangeIndex = 0;
Rect_t areaspotify = {
            .x = 10,
            .y = 20,
            .width = EPD_WIDTH - 20,
            .height =  EPD_HEIGHT / 2 + 80
        };

void printCurrentlyPlaying() {
    epd_clear_area(areaspotify);
    int cursor_x = 20;
    int cursor_y = 140;
    writeln((GFXfont *)&OpenSans12, "Is Playing: \n", &cursor_x, &cursor_y, NULL);
    if (getIsPlaying())
    {
        writeln((GFXfont *)&OpenSans12, "Yes", &cursor_x, &cursor_y, NULL);
        // display play icon
    }
    else
    {
        writeln((GFXfont *)&OpenSans12, "No", &cursor_x, &cursor_y, NULL);
        // display pause icon
    }
    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Track: ", &cursor_x, &cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, getTrackName(), &cursor_x, &cursor_y, NULL);

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Artists: ", &cursor_x, &cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, getArtists(), &cursor_x, &cursor_y, NULL);

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Album: ", &cursor_x, &cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, getAlbumName(), &cursor_x, &cursor_y, NULL);
}

void updateScreenSpotify(void *parameter) {
    while (true) {
        

        if (lastChangeIndex != getChangeIndex()) {
            lastChangeIndex = getChangeIndex();
            printCurrentlyPlaying();
        }

        vTaskDelay(pdMS_TO_TICKS(10000)); // Delay for 1 minute
    }
}

void ScreenSpotify() {
    xTaskCreatePinnedToCore(
        updateScreenSpotify,    // Task function
        "updateScreenSpotify",  // Task name
        10000,              // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );
}