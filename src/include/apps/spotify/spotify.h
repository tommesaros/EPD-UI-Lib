#ifndef SPOTIFY_H
#define SPOTIFY_H

/**
 * @brief Toggles the play/pause state of the Spotify player.
 */
void spotifyTogglePlay();

/**
 * @brief Skips to the previous track in the Spotify playlist.
 */
void spotifyPrev();

/**
 * @brief Skips to the next track in the Spotify playlist.
 */
void spotifyNext();

/**
 * @brief Toggles the shuffle mode of the Spotify playlist.
 */
void spotifyToggleShuffle();

/**
 * @brief Toggles the repeat mode of the Spotify playlist.
 */
void spotifyToggleRepeat();

/**
 * @brief Displays the Spotify UI on the screen.
 */
void displaySpotify();

/**
 * @brief Prints the currently playing track information.
 */
void printCurrentlyPlaying();

/**
 * @brief Clears task handle and exits the Spotify application.
 */
void spotifyExit();

#endif // SPOTIFY_H