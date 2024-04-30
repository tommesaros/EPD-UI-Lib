// Code based on SpotifyDisplayLILYFO repository and ArduinoSpotify example
// https://github.com/Acorn221/SpotifyDisplayLILYGO/blob/master/src/HelperFunctions.cpp


// ----------------------------
// Internal Helper Functions
// ----------------------------
#if 0
#include "HelperFunctions.h"
#include "../../include/credentials.h"
#include "../../../image/spotify.h"

#include <Arduino.h>
#include "epd_driver.h"
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduinoCert.h>

#include "../../../font/opensans12.h"
#include "../../../font/opensans26b.h"

#include "../../../image/spotify.h"

#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/apps/wifi_init/wifi_init.h"



#define TIME_TO_SLEEP 300 // Time between checking if songs are playing (in deepsleep)

// used to decide whether or not to update the display
RTC_DATA_ATTR String oldSongURI = "";
RTC_DATA_ATTR bool wasPlaying = false;
RTC_DATA_ATTR bool hasResetDisplay = false;
RTC_DATA_ATTR unsigned long int lastSleepDuration = 0;

WiFiClientSecure client;
SpotifyArduino spotify(client, CLIENT_ID, CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

void getSpotifyScanCode(String URI, int lengths[25]){
    
    HTTPClient http;
    String url = String(scannablesURL);
    url.concat(URI);
    http.begin(url.c_str(), scannables_root_ca); // Specify the URL and certificate
    int httpCode = http.GET();                   // Make the request
    if (httpCode > 0)
    { // Check for the returning code
        String payload = http.getString();
        
        int location = 0;
        for (int i = 0; i < 3; i++)
        {
            location = payload.indexOf("height=\"", location + 8);
        }
        for (int i = 0; i < 23; i++)
        {
            int length = payload.substring(location + 8, payload.indexOf(".", location)).toInt();
            lengths[i] = map(length, 0, 60, 0, 46);
            location = payload.indexOf("height=\"", location + 8);
        }
    }
    else
    {
        if (DEBUG)
            Serial.println("Error on HTTP request");
    }
    http.end(); // Free the resources
}

void setDisplayNotListening(uint8_t *framebuffer){
    CleanFramebuffer(framebuffer);
    int32_t cursor_x = 100;
    int32_t cursor_y = 100;
    writeln((GFXfont *)&OpenSans12, "Not playing right now. :(", &cursor_x, &cursor_y, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}

void drawSpotifyScan(int lengths[24], uint8_t *framebuffer)
{ // the function to show the spotify scan code
    Rect_t area = {
        .x = EPD_WIDTH - 100 - spotify_icon_width,
        .y = EPD_HEIGHT / 2 - spotify_icon_height / 2,
        .width = spotify_icon_width,
        .height =  spotify_icon_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) spotify_icon_data, framebuffer);
    // drawRoundedLines(3, 5, lengths, 23, x + 58, y + 23, display);
}
/*
void drawRoundedLines(int distanceBetween, int width, int lengths[25], int count, int x, int y, GxEPD_Class* display)
{ // for drawing rounded lines next to eachother
  for (int i = 0; i < count; i++)
  {
    drawRoundedLine(lengths[i], width, x + ((distanceBetween + width) * i), y, display);
  }
}

void drawRoundedLine(int height, int width, int x, int y, GxEPD_Class* display)
{ // for drawing a singular rounded line, y is parsed in the middle of the line
  y = y - (height / 2);
  display->fillRoundRect(x, y, width, height, width, GxEPD_BLACK);
}
*/

void ScreenSpotify()
{
    // Setting the Spotify SSL key
    client.setCACert(spotify_server_cert);

    // Market can be excluded if you want e.g. spotify.getCurrentlyPlaying()
    int status = spotify.getCurrentlyPlaying(handleCurrentlyPlayingCallback, SPOTIFY_MARKET);

    if (status == 200)
    {
        if (DEBUG)
        Serial.println("Successfully got currently playing");
    }
    else if (status == 204)
    {
        // sometimes spotify returns 204 when there is no song playing, sometimes it returns 200
        if (DEBUG)
        Serial.println("Doesn't seem to be anything playing");
        if (wasPlaying || !hasResetDisplay)
        {
        wasPlaying = false;
        if (!hasResetDisplay)
            hasResetDisplay = true;
        }
    }
    else
    {
        if (DEBUG)
        Serial.printf("Error: %d\n", status);
    }
}

/**
 * @brief This function is called when the Spotify API returns a currently playing song
 *
 * @param currentlyPlaying This is passed through the callback and is an instance of the CurrentlyPlaying Class
 */
void handleCurrentlyPlayingCallback(CurrentlyPlaying currentlyPlaying)
{
  // if the playing status has changed or the song has changed
  if (currentlyPlaying.isPlaying != wasPlaying || strcmp(currentlyPlaying.trackUri, oldSongURI.c_str()) != 0)
  {
    oldSongURI = String(currentlyPlaying.trackUri);
    printCurrentlyPlayingToDisplay(currentlyPlaying);
    wasPlaying = currentlyPlaying.isPlaying;
  }
}

/**
 * @brief This prints the currently playing song to the display
 *
 * @param currentlyPlaying
 */
void printCurrentlyPlayingToDisplay(CurrentlyPlaying currentlyPlaying)
{
  if (currentlyPlaying.isPlaying)
  {
    uint8_t *framebuffer = GetMainFramebuffer();
    CleanFramebuffer(framebuffer);

    String Artists = String(currentlyPlaying.trackName);
    Artists.concat(" By ");
    for (int i = 0; i < currentlyPlaying.numArtists; i++)
    {
      // add the artist name to the string
      Artists.concat(currentlyPlaying.artists[i].artistName);
      // if it's the last artist, don't add a comma, otherwise do
      if (i < currentlyPlaying.numArtists - 1)
        Artists.concat(", ");
    }
    
    int32_t wifi_popup_cursor_x = 100;
    int32_t wifi_popup_cursor_y = 240;
    writeln((GFXfont *)&OpenSans26B, Artists, &wifi_popup_cursor_x, &wifi_popup_cursor_y, framebuffer);

    // Setting the lengths to 2 incase the HTTP request fails so it doesn't break the whole display
    int lengths[25] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    getSpotifyScanCode(currentlyPlaying.trackUri, lengths);

    // drawSpotifyScan(0, 76, lengths, &display);

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);

    hasResetDisplay = true;
  }
  else if (wasPlaying || !hasResetDisplay)
  {
    setDisplayNotListening(framebuffer);
    wasPlaying = false;
    hasResetDisplay = true;
  }
}
#endif