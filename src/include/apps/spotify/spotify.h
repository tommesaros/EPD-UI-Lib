#ifndef SPOTIFY_H
#define SPOTIFY_H

/**
 * Toggles the play/pause state of the Spotify player.
 */
void spotifyTogglePlay();

/**
 * Skips to the previous track in the Spotify playlist.
 */
void spotifyPrev();

/**
 * Skips to the next track in the Spotify playlist.
 */
void spotifyNext();

/**
 * Toggles the shuffle mode of the Spotify playlist.
 */
void spotifyToggleShuffle();

/**
 * Toggles the repeat mode of the Spotify playlist.
 */
void spotifyToggleRepeat();

/**
 * Displays the Spotify UI on the screen.
 */
void displaySpotify();

/**
 * Prints the currently playing track information.
 */
void printCurrentlyPlaying();

/**
 * Clears task handle and exits the Spotify application.
 */
void spotifyExit();

#endif // SPOTIFY_H