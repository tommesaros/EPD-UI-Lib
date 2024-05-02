#ifndef WEATHER_HANDLER_H
#define WEATHER_HANDLER_H

#include <OpenWeather.h>

void UpdateWeather(void *parameters);
void WeatherSetup();
OW_current *GetCurrentWeather();
OW_hourly *GetHourlyWeather();
OW_daily *GetDailyWeather();
String strTime(time_t unixTime);

#endif // WEATHER_HANDLER_H