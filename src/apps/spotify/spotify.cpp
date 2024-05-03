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
#include "../../../font/opensans20b.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/white_bg/spotify_icon.h"

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

uint8_t * spotifyFrameBuffer;

void printCurrentlyPlaying() {
    CleanFramebuffer(spotifyFrameBuffer, areaspotify);
    //TODO add Spotify barcode
    int cursor_x = 20; //TODO relative to mainbuffer
    int cursor_y = 140;
    writeln((GFXfont *)&OpenSans12, "Is Playing: \n", &cursor_x, &cursor_y, spotifyFrameBuffer);
    if (getIsPlaying())
    {
        writeln((GFXfont *)&OpenSans12, "Yes", &cursor_x, &cursor_y, spotifyFrameBuffer);
        // display play icon
    }
    else
    {
        writeln((GFXfont *)&OpenSans12, "No", &cursor_x, &cursor_y, spotifyFrameBuffer);
        // display pause icon
    }
    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans20B, getTrackName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, getArtists(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, getAlbumName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    Rect_t iconArea = {
        .x = EPD_WIDTH - 100 - spotify_icon_width,
        .y = EPD_HEIGHT / 2 - spotify_icon_height / 2,
        .width = spotify_icon_width,
        .height =  spotify_icon_height
    };
    epd_copy_to_framebuffer(iconArea, (uint8_t *) spotify_icon_data, spotifyFrameBuffer);

    epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);
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

void ScreenSpotify(uint8_t * framebuffer) {
    int cursor_x = 20; //TODO relative to mainbuffer
    int cursor_y = 140;
    writeln((GFXfont *)&OpenSans12, "Make sure you are playing Spotify music on some other device.", &cursor_x, &cursor_y, spotifyFrameBuffer);
    spotifyFrameBuffer = framebuffer;

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

/*
//TODO controls

spotify.previousTrack();
updateCurrentlyPlaying()
printCurrentlyPlaying()


spotify.nextTrack();
updateCurrentlyPlaying()
printCurrentlyPlaying()


spotify.pause();
isPlaying = false;
prevIsPlaying = false;
//show play icon

spotify.play();
isPlaying = true;
prevIsPlaying = true;
//show pause icon

spotify.toggleShuffle(true);
// icon and bold the text

spotify.toggleShuffle(false);
// icon and unbold the text

manual refresh of the screen
//spin arrow icon
*/