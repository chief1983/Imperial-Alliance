#include "jukebox/fmod.h"
#include <windows.h>

#ifndef _JUKEBOX_H_
#define _JUKEBOX_H_

extern int jukebox_playing;

extern int volume;
extern int total_num_songs;
extern int current_song;

struct PlayListInfo{
	char SongTitle[256];
	char SongPath[MAX_PATH];
};

enum mode {CD, OGG};

extern FSOUND_STREAM *stream;

bool jukebox_init(void);
void jukebox_deinit(void);
void play_song(int);
int get_next_song_to_play();
int get_prev_song_to_play();
void maybe_pause_playback(bool);
void check_song_time(void);
void increase_volume(void);
void decrease_volume(void);

#endif