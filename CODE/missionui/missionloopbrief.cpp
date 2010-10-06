/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MissionUI/MissionLoopBrief.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:42 $
 * $Author: Spearhawk $
 *
 * Campaign Loop briefing screen
 *
 * $Log: missionloopbrief.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:42  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 22:00:54  Darkhill
 * no message
 *
 * Revision 2.3  2003/09/07 18:14:54  randomtiger
 * Checked in new speech code and calls from relevent modules to make it play.
 * Should all work now if setup properly with version 2.4 of the launcher.
 * FS2_SPEECH can be used to make the speech code compile if you have SAPI 5.1 SDK installed.
 * Otherwise the compile flag should not be set and it should all compile OK.
 *
 * - RT
 *
 * Revision 2.2  2003/03/18 10:07:04  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.1.2.1  2002/09/24 18:56:44  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.1  2002/08/01 01:41:07  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:25  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/09 23:02:59  mharris
 * Not using default values for audiostream functions, since they may
 * be macros (if NO_SOUND is defined)
 *
 * Revision 1.1  2002/05/02 18:03:10  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 4     9/06/99 9:44p Jefff
 * break out of loop support
 * 
 * 3     9/06/99 6:38p Dave
 * Improved CD detection code.
 * 
 * 2     8/27/99 12:04a Dave
 * Campaign loop screen.
 *  
 *
 * $NoKeywords: $
 */

#include "missionui/missionloopbrief.h"
#include "missionui/missionscreencommon.h"
#include "Mission/MissionBriefCommon.h"
#include "graphics/2d.h"
#include "bmpman/bmpman.h"
#include "gamesnd/gamesnd.h"
#include "gamesnd/eventmusic.h"
#include "sound/audiostr.h"
#include "io/key.h"
#include "gamesequence/gamesequence.h"
#include "mission/missioncampaign.h"
#include "anim/animplay.h"
#include "freespace2/freespace.h"
#include "sound/fsspeech.h"
#include "debugconsole/dbugfile.h"
#include "globalincs/alphacolors.h"

void loop_brief_force_button_frame();
void loop_brief_maybe_show_button_text();

// ---------------------------------------------------------------------------------------------------------------------------------------
// MISSION LOOP BRIEF DEFINES/VARS
//

char *Loop_brief_fname[GR_NUM_RESOLUTIONS] = {
	"LoopBrief",		// GR_640
	"2_LoopBrief",		// GR_1024
};

char *Loop_brief_mask[GR_NUM_RESOLUTIONS] = {
	"LoopBrief-m",		// GR_640
	"2_Loopbrief-m",	// GR_1024
};

#define NUM_LOOP_BRIEF_BUTTONS				2
#define LOOP_BRIEF_DECLINE						0
#define LOOP_BRIEF_ACCEPT						1
ui_button_info Loop_buttons[GR_NUM_RESOLUTIONS][NUM_LOOP_BRIEF_BUTTONS] = {
	{ // GR_640
		ui_button_info("LBB_00",		485,	375,	-1,	-1,	0),
		ui_button_info("LBB_01",		540,	375,	-1,	-1,	1),
	},
	{ // GR_1024
		ui_button_info("2_LBB_00",		846,	699,	-1,	-1,	0),
		ui_button_info("2_LBB_01",		920,	693,	-1,	-1,	1),
	}
};

#define NUM_LOOP_TEXT							2
UI_XSTR Loop_text[GR_NUM_RESOLUTIONS][NUM_LOOP_TEXT] = {
	{ // GR_640
		{ "Cancel",		-1,		487,	397,	UI_XSTR_COLOR_PINK,	-1,	&Loop_buttons[0][LOOP_BRIEF_DECLINE].button },
		{ "Launch",		-1,		542,	397,	UI_XSTR_COLOR_PINK,	-1,	&Loop_buttons[0][LOOP_BRIEF_ACCEPT].button },
	},	
	{ // GR_1024
		{ "Decline",		1467,	855,	670,	UI_XSTR_COLOR_PINK,	-1,	&Loop_buttons[1][LOOP_BRIEF_DECLINE].button },
		{ "Accept",			1035,	928,	670,	UI_XSTR_COLOR_PINK,	-1,	&Loop_buttons[1][LOOP_BRIEF_ACCEPT].button },
	}
};

// loop brief anim
int Loop_brief_anim_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		50,180//24, 267
	},
	{ // GR_640
		167, 491
	}
};

// text window coords
int Loop_brief_text_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		50,47,585,165//25,	107,	591,	143
	},
	{ // GR_1024
		40,	171,	945,	229
	}
};

UI_WINDOW Loop_brief_window;
int Loop_brief_bitmap;

anim *Loop_anim;
anim_instance *Loop_anim_instance;

int Loop_sound;

// ---------------------------------------------------------------------------------------------------------------------------------------
// MISSION LOOP BRIEF FUNCTIONS
//

// button press
void loop_brief_button_pressed(int i)
{	
	switch(i){
	case LOOP_BRIEF_DECLINE:		
		// CD CHECK
		if(game_do_cd_mission_check(Game_current_mission_filename)){
			gameseq_post_event(GS_EVENT_START_GAME);
			gamesnd_play_iface(SND_USER_SELECT);
		} else {
			gameseq_post_event(GS_EVENT_MAIN_MENU);
		}		
		break;

	case LOOP_BRIEF_ACCEPT:
		// select the loop mission		
		Campaign.loop_enabled = 1;
		Campaign.loop_reentry = Campaign.next_mission;			// save reentry pt, so we can break out of loop
		Campaign.next_mission = Campaign.loop_mission;		
		
		// CD CHECK
		if(game_do_cd_mission_check(Game_current_mission_filename)){
			gameseq_post_event(GS_EVENT_START_GAME);
			gamesnd_play_iface(SND_USER_SELECT);
		} else {
			gameseq_post_event(GS_EVENT_MAIN_MENU);
		}		
		break;
	}
}

// init
void loop_brief_init()
{
	int idx;
	ui_button_info *b;

	// load the background bitmap
	Loop_brief_bitmap = bm_load(Loop_brief_fname[gr_screen.res]);
	Assert(Loop_brief_bitmap != -1);

	// window
	Loop_brief_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);
	Loop_brief_window.set_mask_bmap(Loop_brief_mask[gr_screen.res]);	

	// add the buttons
	for (idx=0; idx<NUM_LOOP_BRIEF_BUTTONS; idx++) {
		b = &Loop_buttons[gr_screen.res][idx];

		b->button.create(&Loop_brief_window, "", b->x, b->y, 60, 30, 0, 1);		
		b->button.set_highlight_action(common_play_highlight_sound);
		b->button.set_bmaps(b->filename);
		b->button.link_hotspot(b->hotspot);
	}

	// add text
	for(idx=0; idx<NUM_LOOP_TEXT; idx++){
		Loop_brief_window.add_XSTR(&Loop_text[gr_screen.res][idx]);
	}

	// load animation if any
	Loop_anim = NULL;
	Loop_anim_instance = NULL;
	if(Campaign.missions[Campaign.current_mission].mission_loop_brief_anim != NULL){
		Loop_anim = anim_load(Campaign.missions[Campaign.current_mission].mission_loop_brief_anim);
	} else {
		Loop_anim = anim_load("CB_default");
	}

	// fire up an anim instance
	if(Loop_anim != NULL){
		anim_play_struct aps;

		anim_play_init(&aps, Loop_anim, Loop_brief_anim_coords[gr_screen.res][0], Loop_brief_anim_coords[gr_screen.res][1]);
		aps.framerate_independent = 1;
		aps.looped = 1;
		aps.screen_id = GS_STATE_LOOP_BRIEF;
		Loop_anim_instance = anim_play(&aps);
	}

	// init brief text
	if(Campaign.missions[Campaign.current_mission].mission_loop_desc != NULL){
		brief_color_text_init(Campaign.missions[Campaign.current_mission].mission_loop_desc, Loop_brief_text_coords[gr_screen.res][2]);
	}

	bool sound_played = false;


	// open sound
	if(Campaign.missions[Campaign.current_mission].mission_loop_brief_sound != NULL){
		Loop_sound = audiostream_open(Campaign.missions[Campaign.current_mission].mission_loop_brief_sound, ASF_VOICE);

		if(Loop_sound != -1){
			audiostream_play(Loop_sound, Master_voice_volume, 0);
			sound_played = true;
		}
	}

	if(sound_played == false) {
		fsspeech_play(FSSPEECH_FROM_BRIEFING, 
			Campaign.missions[Campaign.current_mission].mission_loop_desc);

	}

	// music
	common_music_init(SCORE_BRIEFING);
}

// do
void loop_brief_do()
{
	int k;
	int idx;

	// process keys
	k = Loop_brief_window.process();	

	switch (k) {
	case KEY_ESC:		
		gameseq_post_event(GS_EVENT_MAIN_MENU);
		break;
	}	

	// process button presses
	for (idx=0; idx<NUM_LOOP_BRIEF_BUTTONS; idx++){
		if (Loop_buttons[gr_screen.res][idx].button.pressed()){
			loop_brief_button_pressed(idx);
		}
	}
	
	common_music_do();

	// clear
	GR_MAYBE_CLEAR_RES(Loop_brief_bitmap);
	if (Loop_brief_bitmap >= 0) {
		gr_set_bitmap(Loop_brief_bitmap);
		gr_bitmap(0, 0);
	} 
	
	// draw the window
	Loop_brief_window.draw();		

	// render the briefing text
	brief_render_text(0, Loop_brief_text_coords[gr_screen.res][0], Loop_brief_text_coords[gr_screen.res][1], Loop_brief_text_coords[gr_screen.res][3], flFrametime);

	// render all anims
	anim_render_all(GS_STATE_LOOP_BRIEF, flFrametime);

	loop_brief_force_button_frame();
	loop_brief_maybe_show_button_text();

	gr_flip();
}

// close
void loop_brief_close()
{
	// this makes sure that we're all cool no matter how the user decides to exit
	mission_campaign_mission_over();

	// free the bitmap
	if (Loop_brief_bitmap >= 0){
		bm_unload(Loop_brief_bitmap);
	}		
	Loop_brief_bitmap = -1;

	// destroy the window
	Loop_brief_window.destroy();

	// free up anim stuff
	if(Loop_anim_instance != NULL){
		anim_release_render_instance(Loop_anim_instance);
		Loop_anim_instance = NULL;
	}
	if(Loop_anim != NULL){
		anim_free(Loop_anim);
		Loop_anim = NULL;
	}

	// stop voice
	if(Loop_sound != -1){
		audiostream_stop(Loop_sound, 1, 0);
		audiostream_close_file(Loop_sound, 1);
		Loop_sound = -1;
	}

	fsspeech_stop();

	// stop music
	common_music_close();
}

void loop_brief_force_button_frame()
{
	for (int x=0; x<NUM_LOOP_BRIEF_BUTTONS; x++) {
		if ( !Loop_buttons[gr_screen.res][x].button.button_down()) 
			Loop_buttons[gr_screen.res][x].button.draw_forced(1);
	}
}

void loop_brief_maybe_show_button_text()
{
	ui_button_info *b;
	
	for (int i=0; i<NUM_LOOP_TEXT; i++) {
		b = &Loop_buttons[gr_screen.res][i];

		if (b->button.button_hilighted()) {
			gr_set_color_fast(&Color_bright_white);
			gr_string(Loop_text[gr_screen.res][i].x, Loop_text[gr_screen.res][i].y, Loop_text[gr_screen.res][i].xstr);
		}
	}
}