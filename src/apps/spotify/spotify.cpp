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
// Internal libraries
// ----------------------------
#include "include/fonts.h"
#include "include/components.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/white_bg/spotify_icon.h"
#include "../../../image/black_bg/pause_icon.h"
#include "../../../image/black_bg/play_icon.h"

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
            .x = 95 + spotify_icon_width,
            .y = 65 + (EPD_HEIGHT - 65) / 2 - 60,
            .width = EPD_WIDTH - 100 - spotify_icon_width,
            .height =  120
        };

TaskHandle_t updateScreenSpotifyTaskHandle = NULL;

void printCurrentlyPlaying() {
    uint8_t *spotifyFrameBuffer = GetMainFramebuffer();
    CleanFramebuffer(spotifyFrameBuffer, areaspotify);
    vTaskDelay(pdMS_TO_TICKS(1000));
    epd_draw_status_bar();
    //TODO add Spotify barcode

    Rect_t playIconArea = {
        .x = 400 - play_icon_width,
        .y = EPD_HEIGHT / 2 - play_icon_height / 2,
        .width = play_icon_width,
        .height =  play_icon_height
    };
    if (getIsPlaying()) {
        epd_copy_to_framebuffer(playIconArea, (uint8_t *) pause_icon_data, spotifyFrameBuffer);
    }
    else {
        epd_copy_to_framebuffer(playIconArea, (uint8_t *) play_icon_data, spotifyFrameBuffer);
    }

    int cursor_x = 100 + spotify_icon_width; //TODO relative to mainbuffer
    int cursor_y = 65 + (EPD_HEIGHT - 65) / 2 - 20;
    writeln((GFXfont *)&OpenSans20B, getTrackName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = 100 + spotify_icon_width;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, getArtists(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = 100 + spotify_icon_width;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, getAlbumName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);
}

void updateScreenSpotify(void *parameter) {
    while (true) {
        if (lastChangeIndex != getChangeIndex()) {
            lastChangeIndex = getChangeIndex();
            printCurrentlyPlaying();
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void ScreenSpotify() {
    //ClearTouchPoints();
    uint8_t *spotifyFrameBuffer = GetMainFramebuffer();
    CleanFramebuffer(spotifyFrameBuffer, epd_full_screen());
    epd_draw_status_bar();

    Rect_t iconArea = {
        .x = 50,
        .y = 65 + (EPD_HEIGHT - 65) / 2 - spotify_icon_height / 2,
        .width = spotify_icon_width,
        .height =  spotify_icon_height
    };
    epd_copy_to_framebuffer(iconArea, (uint8_t *) spotify_icon_data, spotifyFrameBuffer);
    epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);

    if (updateScreenSpotifyTaskHandle == NULL) {
        int cursor_x = 100 + spotify_icon_width; //TODO relative to mainbuffer
        int cursor_y = 65 + (EPD_HEIGHT - 65) / 2 - 20;
        writeln((GFXfont *)&OpenSans20B, "Connecting to Spotify...", &cursor_x, &cursor_y, spotifyFrameBuffer);

        cursor_x = 100 + spotify_icon_width;
        cursor_y += 40;
        writeln((GFXfont *)&OpenSans12, "Make sure you are playing Spotify music", &cursor_x, &cursor_y, spotifyFrameBuffer);

        cursor_x = 100 + spotify_icon_width;
        cursor_y += 40;
        writeln((GFXfont *)&OpenSans12, "on some other device connected to your account.", &cursor_x, &cursor_y, spotifyFrameBuffer);
        epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);

        xTaskCreatePinnedToCore(
            updateScreenSpotify,    // Task function
            "updateScreenSpotify",  // Task name
            10000,              // Stack size (in words)
            NULL,              // Task parameter
            1,                 // Task priority
            &updateScreenSpotifyTaskHandle,              // Task handle
            tskNO_AFFINITY     // Core number (0 or 1)
        );
    }
}

void spotifyExit() {
    if (updateScreenSpotifyTaskHandle != NULL) {
        vTaskDelete(updateScreenSpotifyTaskHandle);
        updateScreenSpotifyTaskHandle = NULL;
    }
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