/*******************************************************************
 *Code based on ESP32 example library: SimpleTime.ino
*******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <WiFi.h>
#include "time.h"
#include "sntp.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/handlers/time_handler.h"


const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
struct tm timeinfo;

const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void timeAvailable(struct timeval *t)
{
    Serial.println("Got time adjustment from NTP!");
}

void timeSetup() {
    // set notification call-back function
    sntp_set_time_sync_notification_cb( timeAvailable );

    /**
     * NTP server address could be aquired via DHCP,
     *
     * NOTE: This call should be made BEFORE esp32 aquires IP address via DHCP,
     * otherwise SNTP option 42 would be rejected by default.
     * NOTE: configTime() function call if made AFTER DHCP-client run
     * will OVERRIDE aquired NTP server address
     */
    sntp_servermode_dhcp(1);    // (optional)

    /**
     * This will set configured ntp servers and constant TimeZone/daylightOffset
     * should be OK if your time zone does not need to adjust daylightOffset twice a year,
     * in such a case time adjustment won't be handled automagicaly.
     */
    // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

    /**
     * A more convenient approach to handle TimeZones with daylightOffset 
     * would be to specify a environmnet variable with TimeZone definition including daylight adjustmnet rules.
     * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
     */
    configTzTime(time_zone, ntpServer1, ntpServer2);
}

int timeGetHour() {
    while(!getLocalTime(&timeinfo)){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    return timeinfo.tm_hour;
}

int timeGetMinute() {
    while(!getLocalTime(&timeinfo)){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    return timeinfo.tm_min;
}

char* getTimeDate() {
    while(!getLocalTime(&timeinfo)){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    char* date = new char[11];
    sprintf(date, "%02d.%02d.%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
    return date;
}
