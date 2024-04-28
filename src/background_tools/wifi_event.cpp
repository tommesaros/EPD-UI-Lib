// Code from Lilygo example library: wifi_sync.ino, 
// https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/tree/esp32s3/examples/wifi_sync

#include <WiFi.h>

#include "../include/wifi_event.h"
#include "../include/credentials.h"



void WiFiSetup() {
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.onEvent(WiFiEvent);
}

void WiFiEvent(WiFiEvent_t event) {
    /*
    const Rect_t line1Area = {
        .x = 0,
        .y = 387,
        .width = 960,
        .height = 51,
    };
    */

    int32_t wifi_cursor_x = 0;
    int32_t wifi_cursor_y = 0;

    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) {
        case ARDUINO_EVENT_WIFI_READY:
            Serial.println("WiFi interface ready");
            /*
            wifi_cursor_x = line1Area.x;
            wifi_cursor_y = line1Area.y + OpenSans12.advance_y + OpenSans12.descender;
            epd_clear_area(line1Area);
            writeln((GFXfont *)&OpenSans12, "Connecting to ", &wifi_cursor_x, &wifi_cursor_y, NULL);
            writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_cursor_x, &wifi_cursor_y, NULL);
            */
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            Serial.println("Completed scan for access points");
            break;
        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("WiFi client started");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            Serial.println("WiFi clients stopped");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("Connected to access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            /*
            Serial.println("Disconnected from WiFi access point");
            wifi_cursor_x = line1Area.x;
            wifi_cursor_y = line1Area.y + OpenSans12.advance_y + OpenSans12.descender;
            epd_clear_area(line1Area);
            writeln((GFXfont *)&OpenSans12, "WiFi Disconnected", &wifi_cursor_x, &wifi_cursor_y, NULL);
            */
            break;
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            Serial.println("Authentication mode of access point has changed");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            /*
            wifi_cursor_x = line1Area.x;
            wifi_cursor_y = line1Area.y + OpenSans12.advance_y + OpenSans12.descender;
            epd_clear_area(line1Area);
            writeln((GFXfont *)&OpenSans12, "WiFI Connected to ", &wifi_cursor_x, &wifi_cursor_y, NULL);
            writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_cursor_x, &wifi_cursor_y, NULL);
            */
            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            Serial.println("Lost IP address and IP address is reset to 0");
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("WiFi access point started");
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            Serial.println("WiFi access point stopped");
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            Serial.println("Client connected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            Serial.println("Client disconnected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            Serial.println("Assigned IP address to client");
            break;
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
            Serial.println("Received probe request");
            break;
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
            Serial.println("AP IPv6 is preferred");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            Serial.println("STA IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP6:
            Serial.println("Ethernet IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_START:
            Serial.println("Ethernet started");
            break;
        case ARDUINO_EVENT_ETH_STOP:
            Serial.println("Ethernet stopped");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            Serial.println("Ethernet connected");
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("Ethernet disconnected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.println("Obtained IP address");
            break;
        default: break;
    }
}