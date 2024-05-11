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
#include "../../../image/black_bg/prev_icon.h"
#include "../../../image/black_bg/next_icon.h"
#include "../../../image/white_bg/refresh_icon.h"
#include "../../../image/white_bg/shuffle_icon.h"

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
            .y = 65 + (EPD_HEIGHT - 65) / 2 - 70,
            .width = EPD_WIDTH - 100 - spotify_icon_width,
            .height =  140
        };

TaskHandle_t updateScreenSpotifyTaskHandle = NULL;
SpotifyArduino spotifyAgent = getSpotifyAgent();
uint8_t *spotifyFrameBuffer;
bool trackPlaying = false;
bool shuffle = false;

void spotifyTogglePlay() {
    Rect_t playIconArea = {
        .x = 400 - play_icon_width,
        .y = EPD_HEIGHT / 2 - play_icon_height / 2,
        .width = play_icon_width,
        .height =  play_icon_height
    };

    epd_clear_area_quick(playIconArea, true);

    if (trackPlaying) {
        spotifyAgent.pause();
        trackPlaying = false;
        epd_copy_to_framebuffer(playIconArea, (uint8_t *) play_icon_data, spotifyFrameBuffer);
    } else {
        spotifyAgent.play();
        trackPlaying = true;
        epd_copy_to_framebuffer(playIconArea, (uint8_t *) pause_icon_data, spotifyFrameBuffer);
    }

    epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);
}

void spotifyPrev() {
    spotifyAgent.previousTrack();
}

void spotifyNext() {
    spotifyAgent.nextTrack();
}

void spotifyToggleShuffle() {
    if (shuffle) {
        spotifyAgent.toggleShuffle(false);
    } else {
        spotifyAgent.toggleShuffle(true);
    }
}

void spotifyExit() {
    lastChangeIndex = 0;
    if (updateScreenSpotifyTaskHandle != NULL) {
        vTaskDelete(updateScreenSpotifyTaskHandle);
        updateScreenSpotifyTaskHandle = NULL;
    }
}

void printCurrentlyPlaying() {
    CleanFramebuffer(spotifyFrameBuffer, areaspotify);
    //vTaskDelay(pdMS_TO_TICKS(1000));
    epd_draw_status_bar(spotifyExit);
    //TODO add Spotify barcode

    Rect_t playIconArea = {
        .x = 400 - play_icon_width,
        .y = EPD_HEIGHT / 2 - play_icon_height / 2,
        .width = play_icon_width,
        .height =  play_icon_height
    };
    if (getIsPlaying()) {
        //epd_copy_to_framebuffer(playIconArea, (uint8_t *) pause_icon_data, spotifyFrameBuffer);
        trackPlaying = true;
    }
    else {
        //epd_copy_to_framebuffer(playIconArea, (uint8_t *) play_icon_data, spotifyFrameBuffer);
        trackPlaying = false;
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
    spotifyFrameBuffer = GetMainFramebuffer();
    ClearTouchPoints();
    CleanFramebuffer(spotifyFrameBuffer, epd_full_screen());
    epd_draw_status_bar(spotifyExit);

    Rect_t iconArea = {
        .x = 50,
        .y = 65 + (EPD_HEIGHT - 65) / 2 - spotify_icon_height / 2,
        .width = spotify_icon_width,
        .height =  spotify_icon_height
    };
    epd_copy_to_framebuffer(iconArea, (uint8_t *) spotify_icon_data, spotifyFrameBuffer);
    
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(prev_icon_data), // Add const qualifier
        prev_icon_width,
        prev_icon_height,
        EPD_WIDTH - 240, 
        EPD_HEIGHT - 60, 
        40, 
        0, 
        spotifyFrameBuffer,
        spotifyPrev
    );
    
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(pause_icon_data), // Add const qualifier
        pause_icon_width,
        pause_icon_height,
        EPD_WIDTH - 150, 
        EPD_HEIGHT - 60, 
        50, 
        0, 
        spotifyFrameBuffer,
        spotifyTogglePlay
    );
    
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(next_icon_data), // Add const qualifier
        next_icon_width,
        next_icon_height,
        EPD_WIDTH - 50, 
        EPD_HEIGHT - 60, 
        40, 
        0, 
        spotifyFrameBuffer,
        spotifyNext
    );
    //TODO draw refresh
    //TODO draw shuffle
    

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

/*
//TODO controls
manual refresh of the screen
//spin arrow icon
*/