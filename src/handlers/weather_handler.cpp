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

        String temptemp = String(current->temp) + "°C";
        const char *temp = temptemp.c_str();
        
        if (current)
        {
            Serial.println("############### Current weather ###############\n");
            Serial.print("dt (time)        : "); Serial.println(strTime(current->dt));
            Serial.print("sunrise          : "); Serial.println(strTime(current->sunrise));
            Serial.print("sunset           : "); Serial.println(strTime(current->sunset));
            Serial.print("temp             : "); Serial.println(current->temp);
            Serial.print("feels_like       : "); Serial.println(current->feels_like);
            Serial.print("pressure         : "); Serial.println(current->pressure);
            Serial.print("humidity         : "); Serial.println(current->humidity);
            Serial.print("uvi              : "); Serial.println(current->uvi);
            Serial.print("clouds           : "); Serial.println(current->clouds);
            Serial.print("wind_speed       : "); Serial.println(current->wind_speed);
            Serial.print("rain             : "); Serial.println(current->rain);
            Serial.print("description      : "); Serial.println(current->description);
            Serial.print("icon             : "); Serial.println(current->icon);

            Serial.println();
        }

        if (hourly)
        {
            Serial.println("############### Hourly weather  ###############\n");
            for (int i = 0; i < MAX_HOURS; i++)
            {
                Serial.print("Hourly summary  "); if (i < 10) Serial.print(" "); Serial.print(i);
                Serial.println();
                Serial.print("dt (time)        : "); Serial.println(strTime(hourly->dt[i]));
                Serial.print("temp             : "); Serial.println(hourly->temp[i]);
                Serial.print("feels_like       : "); Serial.println(hourly->feels_like[i]);
                Serial.print("pressure         : "); Serial.println(hourly->pressure[i]);
                Serial.print("humidity         : "); Serial.println(hourly->humidity[i]);
                Serial.print("dew_point        : "); Serial.println(hourly->dew_point[i]);
                Serial.print("clouds           : "); Serial.println(hourly->clouds[i]);
                Serial.print("wind_speed       : "); Serial.println(hourly->wind_speed[i]);
                Serial.print("wind_gust        : "); Serial.println(hourly->wind_gust[i]);
                Serial.print("wind_deg         : "); Serial.println(hourly->wind_deg[i]);
                Serial.print("rain             : "); Serial.println(hourly->rain[i]);
                Serial.print("snow             : "); Serial.println(hourly->snow[i]);
                Serial.println();
                Serial.print("id               : "); Serial.println(hourly->id[i]);
                Serial.print("main             : "); Serial.println(hourly->main[i]);
                Serial.print("description      : "); Serial.println(hourly->description[i]);
                Serial.print("icon             : "); Serial.println(hourly->icon[i]);
                Serial.print("pop              : "); Serial.println(hourly->pop[i]);

                Serial.println();
            }
        }

        if (daily)
        {
            Serial.println("###############  Daily weather  ###############\n");
            for (int i = 0; i < MAX_DAYS; i++)
            {
                Serial.print("Daily summary   "); if (i < 10) Serial.print(" "); Serial.print(i);
                Serial.println();
                Serial.print("dt (time)        : "); Serial.println(strTime(daily->dt[i]));
                Serial.print("sunrise          : "); Serial.println(strTime(daily->sunrise[i]));
                Serial.print("sunset           : "); Serial.println(strTime(daily->sunset[i]));

                Serial.print("temp.morn        : "); Serial.println(daily->temp_morn[i]);
                Serial.print("temp.day         : "); Serial.println(daily->temp_day[i]);
                Serial.print("temp.eve         : "); Serial.println(daily->temp_eve[i]);
                Serial.print("temp.night       : "); Serial.println(daily->temp_night[i]);
                Serial.print("temp.min         : "); Serial.println(daily->temp_min[i]);
                Serial.print("temp.max         : "); Serial.println(daily->temp_max[i]);

                Serial.print("feels_like.morn  : "); Serial.println(daily->feels_like_morn[i]);
                Serial.print("feels_like.day   : "); Serial.println(daily->feels_like_day[i]);
                Serial.print("feels_like.eve   : "); Serial.println(daily->feels_like_eve[i]);
                Serial.print("feels_like.night : "); Serial.println(daily->feels_like_night[i]);

                Serial.print("pressure         : "); Serial.println(daily->pressure[i]);
                Serial.print("humidity         : "); Serial.println(daily->humidity[i]);
                Serial.print("dew_point        : "); Serial.println(daily->dew_point[i]);
                Serial.print("uvi              : "); Serial.println(daily->uvi[i]);
                Serial.print("clouds           : "); Serial.println(daily->clouds[i]);
                Serial.print("visibility       : "); Serial.println(daily->visibility[i]);
                Serial.print("wind_speed       : "); Serial.println(daily->wind_speed[i]);
                Serial.print("wind_gust        : "); Serial.println(daily->wind_gust[i]);
                Serial.print("wind_deg         : "); Serial.println(daily->wind_deg[i]);
                Serial.print("rain             : "); Serial.println(daily->rain[i]);
                Serial.print("snow             : "); Serial.println(daily->snow[i]);
                Serial.println();
                Serial.print("id               : "); Serial.println(daily->id[i]);
                Serial.print("main             : "); Serial.println(daily->main[i]);
                Serial.print("description      : "); Serial.println(daily->description[i]);
                Serial.print("icon             : "); Serial.println(daily->icon[i]);
                Serial.print("pop              : "); Serial.println(daily->pop[i]);

                Serial.println();
            }
        }

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