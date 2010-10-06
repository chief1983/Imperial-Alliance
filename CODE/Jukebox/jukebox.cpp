#include <stdio.h>
#include "osapi/osapi.h"
#include "jukebox/jukebox.h"
#include "jukebox/fmod.h"

int jukebox_playing;
FSOUND_STREAM *stream;
int volume;
int total_num_songs;
int current_song;

DWORD randomize = 0;
DWORD play_mode = OGG;

bool jukebox_init(void)
{
	FILE *fp;
	
	total_num_songs = 0;
	current_song = 0;
	jukebox_playing = 0;
	volume = 100;
	stream = NULL;
	char *temp, *drive;

	FSOUND_SetBufferSize(100);
	temp = (char *)malloc(4);
	drive = (char *)malloc(3);

	if (FSOUND_Init(44100, 32, 0) == false)
		return false;
	else
	{
		play_mode = os_config_read_uint(NULL, "Play Mode", 1);

		FSOUND_SetVolume(FSOUND_ALL, volume);

		randomize = os_config_read_uint(NULL, "Random Playback", 0);

		temp = os_config_read_string(NULL, "Drive Letter", "D:\\");
		// we just want the drive letter and the colon
		for (int x=0; x<2; x++)
			drive[x] = temp[x];
		drive[2] = 0;
	
		switch (play_mode)
		{
		case CD:

			stream = FSOUND_Stream_Open(drive, 0, 0, 0);

			total_num_songs = FSOUND_Stream_GetNumSubStreams(stream);

			
			break;

		case OGG:		
			fp = fopen("playlist.mrp", "r");
			if (fp == NULL)
				return false;
			else
			{
				fscanf(fp, "%d", &total_num_songs);
		
				fcloseall();
			}

			break;
		}
						
		FSOUND_Stream_Stop(stream);
		
		return true;
	}
}

void jukebox_deinit(void)
{
	FSOUND_Close();
}

void play_song(int song)
{
	char filename[MAX_PATH] = "";
	char song_path[MAX_PATH] = "";
	int length;
	int x;
	FILE *fp;

	FSOUND_Stream_Stop(stream);

	switch (play_mode)
	{
	case CD:
		

		if (stream != NULL)
			FSOUND_Stream_SetSubStream(stream, song);
		
		break;

	case OGG:
		fp = fopen("playlist.mrp", "r");
		
		if (fp != NULL)
		{
			for (x=0; x<=song+1; x++)
			{
			
				fgets(song_path, MAX_PATH, fp);
			}

			fclose(fp);
				
			// this little evil thing is to strip the \n from the end of the
			// string.  FMOD has a real problem if the \n is left.  so here
			// we are taking it away
			length = strlen(song_path);
			for (x=0; x<length-1; x++)
				filename[x] = song_path[x];
	
		stream = FSOUND_Stream_Open(filename, FSOUND_NORMAL | FSOUND_2D, 0, 0); 
	
		break;
		}
	}
	if (stream != NULL) {
		FSOUND_Stream_Play(FSOUND_FREE, stream);
		jukebox_playing = 1;
	} else
		jukebox_playing = 0;
	
}

void check_song_time(void)
{
	int current_time;
		
	if (jukebox_playing) {
		current_time = FSOUND_Stream_GetTime(stream);

		if (current_time == FSOUND_Stream_GetLengthMs(stream))
			play_song(get_next_song_to_play());
	}
}

int get_next_song_to_play()
{
	if (jukebox_playing) {
		if (randomize)
			current_song = (rand() % total_num_songs) + 1;
		else
			current_song++;

		if (current_song > total_num_songs-1)
			current_song = 0;
	} else {
		if (randomize)
			current_song = (rand() % total_num_songs) + 1;
		else
			current_song = 0;
	}

	return current_song;
}

int get_prev_song_to_play()
{
	if (jukebox_playing) {
		if (randomize)
			current_song = (rand() % total_num_songs) + 1;
		else
			current_song--;

		if (current_song < 0)
			current_song = total_num_songs-1;
	}  else {
		if (randomize)
			current_song = (rand() % total_num_songs) + 1;
		else
			current_song = 0;
	}

	return current_song;
}

void maybe_pause_playback(bool pause)
{
	if (pause)
		FSOUND_SetPaused(FSOUND_ALL, TRUE);
	else
		FSOUND_SetPaused(FSOUND_ALL, FALSE);
}

void increase_volume(void)
{
	volume += 5;

	if (volume > 255)
		volume = 255;

	FSOUND_SetVolume(FSOUND_ALL, volume);
}

void decrease_volume(void)
{
	volume -= 5;

	if (volume < 0)
		volume = 0;

	FSOUND_SetVolume(FSOUND_ALL, volume);
}





