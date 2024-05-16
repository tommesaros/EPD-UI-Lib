#include "../include/credentials.h"
// ------------------------------------------------------------------------------------
// Do *NOT* share any of this information!
// Keep it stored localy on your machine and do not commit it to any public repository!
// ------------------------------------------------------------------------------------


// ----------------------------
// WiFi credentials
// ----------------------------

const char* WIFI_SSID       = "";
const char* WIFI_PASSWORD   = "";

// ----------------------------
// Spotify credentials
// ----------------------------
/*
Sign into the Spotify Developer page https://developer.spotify.com/ and
create a new application (name it whatever you want). 
Copy the "client ID" and "client secret" from Spotify Developer page and paste it below.
In the Spotify Developer page, set your "redirect URI" to "http://localhost:8888/".
*/
const char* SPOTIFY_CLIENT_ID       = "";
const char* SPOTIFY_CLIENT_SECRET   = "";

// Country code, including this is advisable
const char* SPOTIFY_MARKET          = "GB";

/*
Follow the instructions in the README file of this repository:
https://github.com/arnvgh/get-spotify-refresh-token
In main.py file, change spotipy.SpotifyOAuth scope on line 12 from
scope="playlist-modify-private" to
scope="playlist-modify-private user-read-playback-state user-read-currently-playing user-read-playback-position user-modify-playback-state app-remote-control"
Then copy the "refresh_token" from .cache file and paste it below.
*/
const char* SPOTIFY_REFRESH_TOKEN   = "";


// ----------------------------
// Weather credentials
// ----------------------------
const char* WEATHER_URL = "https://api.openweathermap.org/data/3.0/onecall?";

/*
Sign into the OpenWeatherMap page and paste below your API key from:
https://home.openweathermap.org/api_keys
Subscribe to the "One Call API 3.0" services (1000 calls a day are free):
https://openweathermap.org/price#onecall
Optionally, set a call limit to avoid getting charged for overuse:
https://home.openweathermap.org/subscriptions (set "Call per day" to 999)
*/ 
const char* WEATHER_API_KEY = "";

/*
To get the latitude and longitude, you can use Google Maps.
Just right-click on the location you want and copy the numbers.
*/
const char* WEATHER_LAT = "49.209895085987185";
const char* WEATHER_LON = "16.599009032596893";

const char* WEATHER_UNITS = "metric";           // or "imperial"
const char* WEATHER_LANG = "en";                // see OpenWeather API notes
const unsigned long WEATHER_TIME_OFFSET = 1UL * 3600UL; // UTC + 0 hour
