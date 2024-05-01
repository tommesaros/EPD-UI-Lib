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
#include <WiFiClientSecure.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
#include <ArduinoJson.h>
#include <string.h>

#include "epd_driver.h"
#include "../font/opensans12.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/spotify_handler.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../include/credentials.h"

WiFiClientSecure client;
SpotifyArduino spotify(client, SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);
unsigned long delayBetweenRequests = 5000; // Time between requests (1 minute)

int changeIndex = 0;
bool isPlaying = false;
char artists[100] = "";
char albumName[100] = "";
char trackName[100] = "";

char trackUri[100] = "";
char prevTrackUri[100] = "";

void saveCurrentlyPlaying(CurrentlyPlaying currentlyPlaying) {
    isPlaying = currentlyPlaying.isPlaying;
    strcpy(artists, "");

    for (int i = 0; i < currentlyPlaying.numArtists; i++) {
        if (i != 0) {
            strcat(artists, ", ");
        } 
        strcat(artists, currentlyPlaying.artists[i].artistName);
    }

    strcpy(albumName, currentlyPlaying.albumName);
    strcpy(trackName, currentlyPlaying.trackName);
    strcpy(trackUri, currentlyPlaying.trackUri);
}

int spotifycursor_x = 20;
int spotifycursor_y = 60;

void updateCurrentlyPlaying(void *parameter) {
    while (true) {
        int status = spotify.getCurrentlyPlaying(saveCurrentlyPlaying, SPOTIFY_MARKET);

        if (status == 200) {
            isPlaying = true;
        }
        else if (status == 204){
            isPlaying = false;
        }
        else{
            isPlaying = false;
            //TODO cross icon and notification toast
            // writeln((GFXfont *)&OpenSans12, status, &cursor_x, &cursor_y, NULL);
        }

        if (strcmp(prevTrackUri, trackUri) != 0) {
            changeIndex++;
            strcpy(prevTrackUri, trackUri);
        }
        
        vTaskDelay(pdMS_TO_TICKS(10000)); // Delay for 1 minute
    }
    
}

void SpotifySetup() {
    client.setCACert(spotify_server_cert);  // Handle HTTPS Verification

     if (!spotify.refreshAccessToken())
    {
        //TODO cross icon and notification toast
        //writeln((GFXfont *)&OpenSans12, "Failed to get Spotify access tokens", &cursor_x, &cursor_y, NULL);
    }
    
    xTaskCreatePinnedToCore(
        updateCurrentlyPlaying,     // Task function
        "updateCurrentlyPlaying",   // Task name
        10000,              // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );
}

int getChangeIndex() {
    return changeIndex;
}

bool getIsPlaying() {
    return isPlaying;
}

char *getArtists() {
    return artists;
}

char *getAlbumName() {
    return albumName;
}

char *getTrackName() {
    return trackName;
}
