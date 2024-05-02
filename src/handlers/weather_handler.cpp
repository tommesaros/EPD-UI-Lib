/*******************************************************************
    Based on the OpenWeather API Example:
    My_OpenWeather_Test.ino
    https://github.com/Bodmer/OpenWeather/blob/main/examples/Onecall%20API%20(subscription%20required)/My_OpenWeather_Test/My_OpenWeather_Test.ino
 *******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <OpenWeather.h>
#include <Time.h>

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/weather_handler.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../include/credentials.h"

#define TIME_OFFSET 1UL * 3600UL // UTC + 0 hour

OW_Weather ow; // Weather forecast library instance

OW_current *current = new OW_current;
OW_hourly *hourly = new OW_hourly;
OW_daily  *daily = new OW_daily;

void UpdateWeather(void *parameters) { 
    while (true) {
        delete current;
        delete hourly;
        delete daily;

        current = new OW_current;
        hourly = new OW_hourly;
        daily = new OW_daily;

        ow.getForecast(current, hourly, daily, WEATHER_API_KEY, WEATHER_LAT, WEATHER_LON, WEATHER_UNITS, WEATHER_LANG);

        vTaskDelay(3600000);
    }
}

void WeatherSetup() {
    xTaskCreatePinnedToCore(
        UpdateWeather,     // Task function
        "UpdateWeather",   // Task name
        10000,             // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );
}

OW_current *GetCurrentWeather() {
    return current;
}

OW_hourly *GetHourlyWeather() {
    return hourly;
}

OW_daily *GetDailyWeather() {
    return daily;
}

String strTime(time_t unixTime) {
  unixTime += TIME_OFFSET;
  return ctime(&unixTime);
}