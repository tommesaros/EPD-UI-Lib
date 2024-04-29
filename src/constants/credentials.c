#include "../include/credentials.h"

// Do *NOT* share any of this information!
// Keep it stored localy on your machine and do not commit it to any public repository!

// WiFi credentials
const char* WIFI_SSID       = "";
const char* WIFI_PASSWORD   = "";

// Spotify credentials
/*
Sign into the Spotify Developer page https://developer.spotify.com/ and
create a new application (name it whatever you want). 
Copy the "client ID" and "client secret" from Spotify Developer page and paste it below.
In the Spotify Developer page, set your "redirect URI" to "http://localhost:8888/".
*/
#define CLIENT_ID  ""
#define CLIENT_SECRET "" 

// Country code, including this is advisable
#define SPOTIFY_MARKET "GB"

/*
To get the refresh token, you need to follow the instructions in the README of this repository:
https://github.com/arnvgh/get-spotify-refresh-token
*/
#define SPOTIFY_REFRESH_TOKEN ""
