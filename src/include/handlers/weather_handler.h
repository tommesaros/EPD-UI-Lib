#ifndef WEATHER_HANDLER_H
#define WEATHER_HANDLER_H

/**
 * Structure representing the current weather conditions with units.
 */
struct CurrentWeather {
    String sunrise; /**< The time of sunrise. */
    String sunset; /**< The time of sunset. */
    String temperature; /**< The current temperature. */
    String feels_like; /**< The perceived temperature. */
    String humidity; /**< The humidity percentage. */
    String uvi; /**< The UV index. */
    String clouds; /**< The cloudiness percentage. */
    String wind_speed; /**< The wind speed. */
    String rain; /**< The precipitation volume. */
    String description; /**< The weather description. */
    String icon; /**< The weather icon. */
};

/**
 * Structure representing the hourly weather forecast with units.
 */
struct HourlyWeather {
    String time; /**< The time of the forecast. */
    String temperature; /**< The forecasted temperature. */
    String wind_speed; /**< The forecasted wind speed. */
    String rain; /**< The forecasted precipitation volume. */
    String description; /**< The weather description. */
    String icon; /**< The weather icon. */
};

/**
 * Structure representing the daily weather forecast with units.
 */
struct DailyWeather {
    String day; /**< The time of the forecast. */
    String temp_min; /**< The minimum forecasted temperature. */
    String temp_max; /**< The maximum forecasted temperature. */
    String wind_speed; /**< The forecasted wind speed. */
    String rain; /**< The forecasted precipitation volume. */
    String description; /**< The weather description. */
    String icon; /**< The weather icon. */
};

/**
 * Updates the weather data.
 * @param parameters Used only for RTOS tasks.
 */
void updateWeather(void *parameters);

/**
 * Gets the current weather data.
 * @return A pointer to the CurrentWeather structure.
 */
CurrentWeather* getCurrentWeather();

/**
 * Gets the hourly weather data for a specific hour.
 * @param hourIndex The index of the hour, has to be lower then MAX_HOURS.
 * @return A pointer to the HourlyWeather structure.
 */
HourlyWeather* getHourWeather(int hourIndex);

/**
 * Gets the daily weather data for a specific day.
 * @param dayIndex The index of the day, has to be lower then MAX_DAYS.
 * @return A pointer to the DailyWeather structure.
 */
DailyWeather* getDayWeather(int dayIndex);

/**
 * Performs the setup for weather handling.
 */
void weatherSetup();

/**
 * Converts a Unix timestamp to a string representation of time.
 * @param unixTime The Unix timestamp.
 * @return The string representation of time.
 */
String getTimeString(time_t unixTime);

//TODO: add description
String getDateString(time_t unixTime);

//TODO: add description
const uint8_t* getWeatherIcon(String iconName);

#endif // WEATHER_HANDLER_H
