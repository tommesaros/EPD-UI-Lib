#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// All credentials, see credentials.c for more information

// WiFi
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Spotify
extern const char* SPOTIFY_CLIENT_ID;
extern const char* SPOTIFY_CLIENT_SECRET;
extern const char* SPOTIFY_MARKET;
extern const char* SPOTIFY_REFRESH_TOKEN;

// Weather
extern const char* WEATHER_URL;
extern const char* WEATHER_API_KEY;
extern const char* WEATHER_LAT;
extern const char* WEATHER_LON;
extern const char* WEATHER_UNITS;
extern const char* WEATHER_LANG;
extern const unsigned long WEATHER_TIME_OFFSET;

#endif // CREDENTIALS_H