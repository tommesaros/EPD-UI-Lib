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
#include "include/dimensions.h"
#include "include/colors.h"

// ----------------------------
// Icons
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

SpotifyArduino spotifyAgent = getSpotifyAgent();
TaskHandle_t updateScreenSpotifyTaskHandle = NULL;
uint8_t *spotifyFrameBuffer;

int lastChangeIndex = 0;
bool trackPlaying = false;
bool shuffle = false;
bool repeat = false;

const int ICON_PADDING = 100;
const int LINE_HEIGHT = 40;

void spotifyTogglePlay() {
    Rect_t playIconArea = {
        .x = EPD_WIDTH - 160 - play_icon_width / 2,
        .y = EPD_HEIGHT - 70 - play_icon_height / 2,
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
    // The dot is signaling that the shuffle mode is on
    if (shuffle) {
        Rect_t shuffleDotArea = {
            .x = EPD_WIDTH - 160,
            .y = STATUS_BAR_HEIGHT + 30,
            .width = 15,
            .height = 12
        };
        CleanFramebuffer(spotifyFrameBuffer, shuffleDotArea);

        spotifyAgent.toggleShuffle(false);
        shuffle = false;
    } else {
        epd_fill_circle(EPD_WIDTH - 155, STATUS_BAR_HEIGHT + 36, 5, BLACK, spotifyFrameBuffer);
        epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);

        spotifyAgent.toggleShuffle(true);
        shuffle = true;
    }
}

void spotifyToggleRepeat() {
    // The dot is signaling that the repeat mode is on
    if (repeat) {
        Rect_t repeatDotArea = {
            .x = EPD_WIDTH - 318,
            .y = STATUS_BAR_HEIGHT + 30,
            .width = 15,
            .height =  12
        };
        CleanFramebuffer(spotifyFrameBuffer, repeatDotArea);

        spotifyAgent.setRepeatMode(repeat_off);
        repeat = false;
    } else {
        epd_fill_circle(EPD_WIDTH - 305, STATUS_BAR_HEIGHT + 36, 5, BLACK, spotifyFrameBuffer);
        epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);

        spotifyAgent.setRepeatMode(repeat_track);
        repeat = true;
    }
}

void spotifyExit() {
    // In order to trigger displaying the currently playing track 
    // immediately after reopening the Spotify app. 
    lastChangeIndex = 0;
    if (updateScreenSpotifyTaskHandle != NULL) {
        vTaskDelete(updateScreenSpotifyTaskHandle);
        updateScreenSpotifyTaskHandle = NULL;
    }
}

void printCurrentlyPlaying() {
    Rect_t areaspotify = {
        .x = 95 + spotify_icon_width,
        .y = SCREEN_MIDDLE_WITH_STATUS_BAR - 70,
        .width = EPD_WIDTH - 100 - spotify_icon_width,
        .height =  140
    };
    CleanFramebuffer(spotifyFrameBuffer, areaspotify);
    epd_draw_status_bar(spotifyExit);

    if (getIsPlaying()) {
        trackPlaying = true;
    }
    else {
        trackPlaying = false;
    }

    // Displaying the track information
    int cursor_x = ICON_PADDING + spotify_icon_width;
    int cursor_y = SCREEN_MIDDLE_WITH_STATUS_BAR - 20;
    writeln((GFXfont *)&OpenSans20B, getTrackName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = ICON_PADDING + spotify_icon_width;
    cursor_y += LINE_HEIGHT;
    writeln(TEXT_FONT_BOLD, getArtists(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    cursor_x = ICON_PADDING + spotify_icon_width;
    cursor_y += LINE_HEIGHT;
    writeln(TEXT_FONT, getAlbumName(), &cursor_x, &cursor_y, spotifyFrameBuffer);

    epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);
}

void updateScreenSpotify(void *parameter) {
    while (true) {
        if (lastChangeIndex != getChangeIndex()) {
            lastChangeIndex = getChangeIndex();
            printCurrentlyPlaying();
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void displaySpotify() {
    const int UPPER_BUTTON_ROW_Y = STATUS_BAR_HEIGHT + 20;
    const int LOWER_BUTTON_ROW_Y = EPD_HEIGHT - 70;
    const int SMALL_BUTTON_RADIUS = 40;
    const int BIG_BUTTON_RADIUS = 50;

    spotifyFrameBuffer = GetMainFramebuffer();
    ClearTouchPoints();
    CleanFramebuffer(spotifyFrameBuffer, epd_full_screen());
    epd_draw_status_bar(spotifyExit);

    // Big Spotify icon
    Rect_t iconArea = {
        .x = 50,
        .y = SCREEN_MIDDLE_WITH_STATUS_BAR - spotify_icon_height / 2,
        .width = spotify_icon_width,
        .height =  spotify_icon_height
    };
    epd_copy_to_framebuffer(iconArea, (uint8_t *) spotify_icon_data, spotifyFrameBuffer);

    // Repeat button
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(refresh_icon_data), 
        refresh_icon_width,
        refresh_icon_height,
        "Repeat",
        TEXT_FONT,
        EPD_WIDTH - 300,
        UPPER_BUTTON_ROW_Y, 
        WHITE, 
        BLACK,
        WHITE_ON_BLACK, 
        spotifyFrameBuffer,
        spotifyToggleRepeat
    );

    // Shuffle button
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(shuffle_icon_data), 
        shuffle_icon_width,
        shuffle_icon_height,
        "Shuffle",
        TEXT_FONT,
        EPD_WIDTH - 150, 
        UPPER_BUTTON_ROW_Y, 
        WHITE, 
        BLACK,
        WHITE_ON_BLACK, 
        spotifyFrameBuffer,
        spotifyToggleShuffle
    );
    
    // Previous track button
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(prev_icon_data), 
        prev_icon_width,
        prev_icon_height,
        EPD_WIDTH - 260, 
        LOWER_BUTTON_ROW_Y, 
        SMALL_BUTTON_RADIUS, 
        BLACK, 
        spotifyFrameBuffer,
        spotifyPrev
    );

    // Play/Pause button
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(pause_icon_data), 
        pause_icon_width,
        pause_icon_height,
        EPD_WIDTH - 160, 
        LOWER_BUTTON_ROW_Y, 
        BIG_BUTTON_RADIUS, 
        BLACK, 
        spotifyFrameBuffer,
        spotifyTogglePlay
    );
    
    // Next track button
    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(next_icon_data), 
        next_icon_width,
        next_icon_height,
        EPD_WIDTH - 60, 
        LOWER_BUTTON_ROW_Y, 
        SMALL_BUTTON_RADIUS, 
        BLACK, 
        spotifyFrameBuffer,
        spotifyNext
    );

    if (updateScreenSpotifyTaskHandle == NULL) {
        // Initial screen when the app is opened and not connected to Spotify yet
        int cursor_x = ICON_PADDING + spotify_icon_width;
        int cursor_y = SCREEN_MIDDLE_WITH_STATUS_BAR - 20;
        writeln(
            (GFXfont *)&OpenSans20B, 
            "Connecting to Spotify...", 
            &cursor_x, 
            &cursor_y, 
            spotifyFrameBuffer
        );

        cursor_x = ICON_PADDING + spotify_icon_width;
        cursor_y += LINE_HEIGHT;
        writeln(
            TEXT_FONT, 
            "Make sure you are playing Spotify music", 
            &cursor_x, 
            &cursor_y, 
            spotifyFrameBuffer
        );

        cursor_x = ICON_PADDING + spotify_icon_width;
        cursor_y += LINE_HEIGHT;
        writeln(
            TEXT_FONT, 
            "on some other device connected to your account.", 
            &cursor_x, 
            &cursor_y, 
            spotifyFrameBuffer
        );
        epd_draw_grayscale_image(epd_full_screen(), spotifyFrameBuffer);

        xTaskCreatePinnedToCore(
            updateScreenSpotify,                // Task function
            "updateScreenSpotify",              // Task name
            10000,                              // Stack size (in words)
            NULL,                               // Task parameter
            1,                                  // Task priority
            &updateScreenSpotifyTaskHandle,     // Task handle
            tskNO_AFFINITY                      // Core number
        );
    }
}

 //TODO dat to do premennych všetky súradnice a veľkosti