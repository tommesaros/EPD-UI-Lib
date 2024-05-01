#ifndef SPOTIFY_HANDLER_H
#define SPOTIFY_HANDLER_H

#include <SpotifyArduino.h>

void SpotifySetup();
void updateCurrentlyPlaying(void *parameter);
int getChangeIndex();
bool getIsPlaying();
char *getArtists();
char *getAlbumName();
char *getTrackName();

#endif // SPOTIFY_HANDLER_H