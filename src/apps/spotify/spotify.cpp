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
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
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

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../../include/credentials.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/spotify/spotify.h"

WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 5000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due

void printCurrentlyPlaying(CurrentlyPlaying currentlyPlaying);

void checkIfPlaying() {
    int cursor_x = 20;
    int cursor_y = 100;
    writeln((GFXfont *)&OpenSans12, "getting currently playing song:\n", &cursor_x, &cursor_y, NULL);
    // Market can be excluded if you want e.g. spotify.getCurrentlyPlaying()
    int status = spotify.getCurrentlyPlaying(printCurrentlyPlaying, SPOTIFY_MARKET);
    if (status == 200)
    {
        writeln((GFXfont *)&OpenSans12, "Successfully got currently playing\n", &cursor_x, &cursor_y, NULL);
    }
    else if (status == 204)
    {
        writeln((GFXfont *)&OpenSans12, "Doesn't seem to be anything playing\n", &cursor_x, &cursor_y, NULL);
    }
    else
    {
        writeln((GFXfont *)&OpenSans12, "Error: \n", &cursor_x, &cursor_y, NULL);
        // writeln((GFXfont *)&OpenSans12, status, &cursor_x, &cursor_y, NULL);
    }

    char heapSize[10];
    sprintf(heapSize, "%d", esp_get_free_heap_size());
    writeln((GFXfont *)&OpenSans12, heapSize, &cursor_x, &cursor_y, NULL);
}

void ScreenSpotify(void *parameter) {
    while (true) {
        Rect_t areaspotify = {
            .x = 10,
            .y = 20,
            .width = EPD_WIDTH - 20,
            .height =  EPD_HEIGHT / 2 + 80
        };
        epd_clear_area(areaspotify);
        // Handle HTTPS Verification
        client.setCACert(spotify_server_cert);

        // ... or don't!
        //client.setInsecure();

        int cursor_x = 20;
        int cursor_y = 60;
        char heapSize[10];
        sprintf(heapSize, "%d", esp_get_free_heap_size());
        writeln((GFXfont *)&OpenSans12, heapSize, &cursor_x, &cursor_y, NULL);

        if (!spotify.refreshAccessToken())
        {
            //TODO cross icon and framebuffer
            writeln((GFXfont *)&OpenSans12, "Failed to get Spotify access tokens", &cursor_x, &cursor_y, NULL);
        }
        
        checkIfPlaying();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Delay for 1 minute
    }
}

void printCurrentlyPlaying(CurrentlyPlaying currentlyPlaying) {
    // Use the details in this method or if you want to store them
    // make sure you copy them (using something like strncpy)
    // const char* artist =
    int cursor_x = 20;
    int cursor_y = 140;
    writeln((GFXfont *)&OpenSans12, "--------- Currently Playing ---------\n", &cursor_x, &cursor_y, NULL);
    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Is Playing: \n", &cursor_x, &cursor_y, NULL);
    if (currentlyPlaying.isPlaying)
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
    writeln((GFXfont *)&OpenSans12, currentlyPlaying.trackName, &cursor_x, &cursor_y, NULL);

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Artists: ", &cursor_x, &cursor_y, NULL);
    for (int i = 0; i < currentlyPlaying.numArtists; i++)
    {
        writeln((GFXfont *)&OpenSans12, currentlyPlaying.artists[i].artistName, &cursor_x, &cursor_y, NULL);
        writeln((GFXfont *)&OpenSans12, ", ", &cursor_x, &cursor_y, NULL);
    }

    cursor_x = 20;
    cursor_y += 40;
    writeln((GFXfont *)&OpenSans12, "Album: ", &cursor_x, &cursor_y, NULL);
    writeln((GFXfont *)&OpenSans12, currentlyPlaying.albumName, &cursor_x, &cursor_y, NULL);

    /*
    long progress = currentlyPlaying.progressMs; // duration passed in the song
    long duration = currentlyPlaying.durationMs; // Length of Song
    Serial.print("Elapsed time of song (ms): ");
    Serial.print(progress);
    Serial.print(" of ");
    Serial.println(duration);
    Serial.println();
    

    float percentage = ((float)progress / (float)duration) * 100;
    int clampedPercentage = (int)percentage;
    Serial.print("<");
    for (int j = 0; j < 50; j++)
    {
        if (clampedPercentage >= (j * 2))
        {
            Serial.print("=");
        }
        else
        {
            Serial.print("-");
        }
    }
    Serial.println(">");
    Serial.println();
    */
}