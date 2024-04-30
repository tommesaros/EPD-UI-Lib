// Code based on SpotifyDisplayLILYFO repository: HelperFunctions.cpp
// https://github.com/Acorn221/SpotifyDisplayLILYGO/blob/master/src/HelperFunctions.cpp

#if 0
#include "HelperFunctions.h"

#include <Arduino.h>
#include "epd_driver.h"
#include <Arduino.h>
#include "epd_driver.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <SpotifyArduinoCert.h>

#include "../../../font/opensans12.h"
#include "../../../font/opensans26b.h"

#include "../../../image/spotify.h"

#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/apps/wifi_init/wifi_init.h"

const char *scannables_root_ca = // this certificate is for scannables.scdn.co to get the scan link
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
    "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
    "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
    "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
    "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
    "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
    "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
    "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
    "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
    "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
    "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
    "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
    "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
    "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
    "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
    "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
    "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
    "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
    "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
    "-----END CERTIFICATE-----";

const char *scannablesURL = "https://scannables.scdn.co/uri/plain/svg/ffffff/black/256/";

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
#endif