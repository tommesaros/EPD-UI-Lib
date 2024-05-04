#ifndef WEATHER_HANDLER_H
#define WEATHER_HANDLER_H

// more info https://openweathermap.org/api/one-call-3#list1

struct CurrentWeather {
    String sunrise;
    String sunset;
    String temperature;
    String feels_like;
    String humidity;
    String uvi;
    String clouds;
    String wind_speed;
    String rain;
    String description;
    String icon;
};

struct HourlyWeather {
    String time;
    String temperature;
    String wind_speed;
    String rain;
    String description;
    String icon;
};

struct DailyWeather {
    String time;
    String temp_min;
    String temp_max;
    String wind_speed;
    String rain;
    String description;
    String icon;
};

void updateWeather(void *parameters);
CurrentWeather* getCurrentWeather();
HourlyWeather* getHourWeather(int hourIndex);
DailyWeather* getDayWeather(int dayIndex);
void WeatherSetup();
String strTime(time_t unixTime);

#endif // WEATHER_HANDLER_H