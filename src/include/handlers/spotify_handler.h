#ifndef SPOTIFY_HANDLER_H
#define SPOTIFY_HANDLER_H

#include <SpotifyArduino.h>


/**
 * @brief Sets up the Spotify API connection.
 * 
 * This function initializes the necessary components and configurations for 
 * integrating with Spotify. It should be called before any other 
 * Spotify-related operations are performed. It starts the automatic update of the
 * currently playing track.
 */
void spotifySetup();

/**
 * @brief Updates the currently playing information.
 *
 * This function is responsible for updating the information about the 
 * currently playing track in the Spotify handler. After SpotifySetup() is called,
 * it updates the track information every 10 seconds on its own.
 *
 * @param parameter Used only for RTOS tasks.
 */
void updateCurrentlyPlaying(void *parameter);

/**
 * This function returns the change index, which used to determine if the track has changed.
 *
 * @return The change index.
 */
int getChangeIndex();

/**
 * Checks if the Spotify player is currently playing a track.
 *
 * @return true if the player is playing a track, false otherwise.
 */
bool getIsPlaying();

/**
 * Retrieves all the track artists (comma-separated) from Spotify.
 *
 * @return A pointer to a character array containing the artists.
 */
char *getArtists();

/**
 * Retrieves the name of the track album.
 * 
 * @return A pointer to a character array representing the album name.
 */
char *getAlbumName();

/**
 * Retrieves the name of the current track.
 * 
 * @return A pointer to a character array containing the track name.
 */
char *getTrackName();

/**
 * Retrieves the SpotifyArduino agent.
 *
 * @return The SpotifyArduino agent.
 */
SpotifyArduino getSpotifyAgent();

#endif // SPOTIFY_HANDLER_H
