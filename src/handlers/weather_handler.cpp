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

// ----------------------------
// Weather icons
// ----------------------------
#include "../../image/black_bg/sunny_icon.h"
#include "../../image/black_bg/cloudy_icon.h"
#include "../../image/black_bg/semi_cloudy_icon.h"
#include "../../image/black_bg/rainy_icon.h"
#include "../../image/black_bg/storm_icon.h"
#include "../../image/black_bg/snow_icon.h"
#include "../../image/black_bg/mist_icon.h"

OW_Weather ow; // Weather forecast library instance

struct CurrentWeather;
struct HourlyWeather;
struct DailyWeather;

CurrentWeather currentWeather;
HourlyWeather hourlyWeather[MAX_HOURS];
DailyWeather dailyWeather[MAX_DAYS];

OW_current *current;
OW_hourly *hourly;
OW_daily *daily;

void updateWeather(void *parameters) {
    while (true) {
        current = new OW_current;
        hourly = new OW_hourly;
        daily = new OW_daily;

        ow.getForecast(current, hourly, daily, WEATHER_API_KEY, WEATHER_LAT, WEATHER_LON, WEATHER_UNITS, WEATHER_LANG);

        currentWeather.sunrise = strTime(current->sunrise);
        currentWeather.sunset = strTime(current->sunset);
        currentWeather.temperature = String(current->temp) + "°C";
        currentWeather.feels_like = String(current->feels_like) + "°C";
        currentWeather.humidity = String(current->humidity) + "%";
        currentWeather.uvi = String(current->uvi);
        currentWeather.clouds = String(current->clouds) + "%";
        currentWeather.wind_speed = String(current->wind_speed) + "m/s";
        currentWeather.rain = String(current->rain) + "mm/h";
        currentWeather.description = String(current->description);
        currentWeather.icon = String(current->icon);

        for (int i = 0; i < MAX_HOURS; i++) {
            hourlyWeather[i].time = strTime(hourly->dt[i]);
            hourlyWeather[i].temperature = String(hourly->temp[i]) + "°C";
            hourlyWeather[i].wind_speed = String(hourly->wind_speed[i]) + "m/s";
            hourlyWeather[i].rain = String(hourly->rain[i]) + "mm/h";
            hourlyWeather[i].description = String(hourly->description[i]);
            hourlyWeather[i].icon = String(hourly->icon[i]);
        }

        for (int i = 0; i < MAX_DAYS; i++) {
            dailyWeather[i].day = strDate(daily->dt[i]);
            dailyWeather[i].temp_min = String(daily->temp_min[i]) + "°C";
            dailyWeather[i].temp_max = String(daily->temp_max[i]) + "°C";
            dailyWeather[i].wind_speed = String(daily->wind_speed[i]) + "m/s";
            dailyWeather[i].rain = String(daily->rain[i]) + "mm/h";
            dailyWeather[i].description = String(daily->description[i]);
            dailyWeather[i].icon = String(daily->icon[i]);
        }

        delete current;
        delete hourly;
        delete daily;

        //TODO check data if temp==0, then retry

        vTaskDelay(3600000);
    }
}

CurrentWeather* getCurrentWeather() {
    return &currentWeather;
}

HourlyWeather* getHourWeather(int hourIndex) {
    if (hourIndex >= 0 && hourIndex < MAX_HOURS) {
        return &hourlyWeather[hourIndex];
    } else { 
        return nullptr;
    }
}

DailyWeather* getDayWeather(int dayIndex) {
    if (dayIndex >= 0 && dayIndex < MAX_DAYS) {
        return &dailyWeather[dayIndex];
    } else { 
        return nullptr;
    }
}

void WeatherSetup() {
    xTaskCreatePinnedToCore(
        updateWeather,     // Task function
        "updateWeather",   // Task name
        10000,             // Stack size (in words)
        NULL,              // Task parameter
        1,                 // Task priority
        NULL,              // Task handle
        tskNO_AFFINITY     // Core number (0 or 1)
    );
}

String strTime(time_t unixTime) {
    unixTime += WEATHER_TIME_OFFSET;
    struct tm *timeinfo;
    timeinfo = localtime(&unixTime);
    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    return String(buffer);
}

String strDate(time_t unixTime) {
    unixTime += WEATHER_TIME_OFFSET;
    struct tm *timeinfo;
    timeinfo = localtime(&unixTime);
    char buffer[20]; 
    strftime(buffer, sizeof(buffer), "%a %d.%m.", timeinfo);
    return String(buffer);
}

//TODO get current weather icon
const uint8_t* getWeatherIcon(String iconName) {
    if (iconName == "01d" || iconName == "01n") {
        return sunny_icon_data;
    } else if (iconName == "02d" || iconName == "02n") {
        return semi_cloudy_icon_data;
    } else if (iconName == "03d" || iconName == "03n" || iconName == "04d" || iconName == "04n") {
        return cloudy_icon_data;
    } else if (iconName == "09d" || iconName == "09n" || iconName == "10d" || iconName == "10n") {
        return rainy_icon_data;
    } else if (iconName == "11d" || iconName == "11n") {
        return storm_icon_data;
    } else if (iconName == "13d" || iconName == "13n") {
        return snow_icon_data;
    } else if (iconName == "50d" || iconName == "50n") {
        return mist_icon_data;
    } else {
        return sunny_icon_data;
    }
}
