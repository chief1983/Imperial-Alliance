/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/PlayerMenu.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:41 $
 * $Author: Spearhawk $
 *
 * Code to drive the Player Select initial screen
 *
 * $Log: playermenu.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:47:52  Darkhill
 * no message
 *
 * Revision 2.7  2003/11/11 02:15:43  Goober5000
 * ubercommit - basically spelling and language fixes with some additional
 * warnings disabled
 * --Goober5000
 *
 * Revision 2.6  2003/10/27 23:04:22  randomtiger
 * Added -no_set_gamma flags
 * Fixed up some more non standard res stuff
 * Improved selection of device type, this includes using a pure device when allowed which means dev should not use Get* functions in D3D
 * Made fade in credits work
 * Stopped a call to gr_reser_lighting() in non htl mode when the pointer was NULL, was causing a crash loading a fogged level
 * Deleted directx8 directory content, has never been needed.
 *
 * Revision 2.5  2003/08/20 08:11:00  wmcoolmon
 * Added error screens to the barracks and start screens when a pilot file can't be deleted
 *
 * Revision 2.4  2003/03/18 10:07:03  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.3  2003/01/14 04:00:15  Goober5000
 * allowed for up to 256 main halls
 * --Goober5000
 *
 * Revision 2.2.2.1  2002/09/24 18:56:43  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.2  2002/08/04 05:12:42  penguin
 * Display fs2_open version instead of "Freespace 2"
 *
 * Revision 2.1  2002/08/01 01:41:06  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/10 20:42:44  mharris
 * use "ifndef NO_NETWORK" all over the place
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 * 
 * 
 * 43    11/02/99 11:42a Jefff
 * fixed copyright symbol in german fonts
 * 
 * 42    10/27/99 12:27a Jefff
 * localized tips correctly
 * 
 * 41    9/13/99 4:52p Dave
 * RESPAWN FIX
 * 
 * 40    9/02/99 11:10a Jefff
 * fixed 1024 list display bug - was only showing 8 pilots at a time
 * 
 * 39    8/26/99 8:51p Dave
 * Gave multiplayer TvT messaging a heavy dose of sanity. Cheat codes.
 * 
 * 38    8/26/99 9:45a Dave
 * First pass at easter eggs and cheats.
 * 
 * 37    8/16/99 6:39p Jefff
 * 
 * 36    8/16/99 6:37p Jefff
 * minor string alterations
 * 
 * 35    8/05/99 4:17p Dave
 * Tweaks to client interpolation.
 * 
 * 34    8/05/99 11:29a Mikek
 * Jacked up number of comments from 20 to 40, thereby doubling the
 * quality of our game.
 * 
 * 33    8/04/99 10:53a Dave
 * Added title to the user tips popup.
 * 
 * 32    8/03/99 3:21p Jefff
 * 
 * 31    8/03/99 10:32a Jefff
 * raised location of bottom_text to not interfere w/ logo.  changed
 * "please enter callsign" to "type callsign and press enter"
 * 
 * 30    8/02/99 9:13p Dave
 * Added popup tips.
 * 
 * 29    7/30/99 10:29a Jefff
 * fixed colors of bottom display texts
 * 
 * 28    7/27/99 7:17p Jefff
 * Replaced some art text with XSTR() text.
 * 
 * 27    7/19/99 2:06p Jasons
 * Remove all palette stuff from player select menu.
 * 
 * 26    7/15/99 9:20a Andsager
 * FS2_DEMO initial checkin
 * 
 * 25    7/09/99 9:51a Dave
 * Added thick polyline code.
 * 
 * 24    6/11/99 11:13a Dave
 * last minute changes before press tour build.
 * 
 * 23    5/21/99 6:45p Dave
 * Sped up ui loading a bit. Sped up localization disk access stuff. Multi
 * start game screen, multi password, and multi pxo-help screen.
 * 
 * 22    4/25/99 3:02p Dave
 * Build defines for the E3 build.
 * 
 * 21    3/25/99 2:31p Neilk
 * Coordinate changes to handle new artwork
 * 
 * 20    2/25/99 4:19p Dave
 * Added multiplayer_beta defines. Added cd_check define. Fixed a few
 * release build warnings. Added more data to the squad war request and
 * response packets.
 * 
 * 19    2/01/99 5:55p Dave
 * Removed the idea of explicit bitmaps for buttons. Fixed text
 * highlighting for disabled gadgets.
 * 
 * 18    1/30/99 5:08p Dave
 * More new hi-res stuff.Support for nice D3D textures.
 * 
 * 17    1/30/99 1:53a Dave
 * Fix some harcoded coords.
 * 
 * 16    1/30/99 1:28a Dave
 * 1024x768 full support.
 * 
 * 15    1/29/99 1:25p Dave
 * New code for choose pilot screen.
 * 
 * 14    1/29/99 12:47a Dave
 * Put in sounds for beam weapon. A bunch of interface screens (tech
 * database stuff).
 * 
 * 13    1/12/99 12:53a Dave
 * More work on beam weapons - made collision detection very efficient -
 * collide against all object types properly - made 3 movement types
 * smooth. Put in test code to check for possible non-darkening pixels on
 * object textures.
 * 
 * 12    12/18/98 1:13a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 11    12/06/98 2:36p Dave
 * Drastically improved nebula fogging.
 * 
 * 10    12/01/98 6:20p Dave
 * Removed tga test bitmap code.
 * 
 * 9     12/01/98 4:46p Dave
 * Put in targa bitmap support (16 bit).
 * 
 * 8     11/30/98 1:07p Dave
 * 16 bit conversion, first run.
 * 
 * 7     11/20/98 11:16a Dave
 * Fixed up IPX support a bit. Making sure that switching modes and
 * loading/saving pilot files maintains proper state.
 * 
 * 6     11/19/98 4:19p Dave
 * Put IPX sockets back in psnet. Consolidated all multiplayer config
 * files into one.
 * 
 * 5     11/05/98 4:18p Dave
 * First run nebula support. Beefed up localization a bit. Removed all
 * conditional compiles for foreign versions. Modified mission file
 * format.
 * 
 * 4     10/13/98 9:28a Dave
 * Started neatening up freespace.h. Many variables renamed and
 * reorganized. Added AlphaColors.[h,cpp]
 * 
 * 3     10/09/98 2:57p Dave
 * Starting splitting up OS stuff.
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:49a Dave
 * 
 *
 * $NoKeywords: $
 *
 */

#include <ctype.h>
#include <fstream>
#include <iostream>

#include "menuui/playermenu.h"
#include "graphics/2d.h"
#include "ui/ui.h"
#include "gamesnd/gamesnd.h"
#include "playerman/player.h"
#include "cfile/cfile.h"
#include "io/key.h"
#include "playerman/managepilot.h"
#include "missionui/missionscreencommon.h"
#include "bmpman/bmpman.h"
#include "freespace2/freespace.h"
#include "parse/parselo.h"
#include "gamesequence/gamesequence.h"
#include "io/timer.h"
#include "cmdline/cmdline.h"
#include "osapi/osregistry.h"
#include "palman/palman.h"
#include "menuui/mainhallmenu.h"
#include "popup/popup.h"
#include "io/mouse.h"
#include "globalincs/alphacolors.h"
#include "localization/localize.h"
#include "debugconsole/dbugfile.h"
#include "Mission/MissionCampaign.h"
#include "anim/animplay.h"
#include "Anim/PackUnpack.h"

#include "EH_Medals/idline.h"
#include "EH_Medals/convert.h"

#include "Popup/popuptc.h"

#ifndef NO_NETWORK
#include "network/multi.h"
#endif

// --------------------------------------------------------------------------------------------------------
// Demo title screen
#ifdef FS2_DEMO
static int Demo_title_active = 0;
static int Demo_title_bitmap = -1;
static int Demo_title_expire_timestamp = 0;
static int Demo_title_need_fade_in = 1;
static char *Demo_title_bitmap_filename = NOX("DemoTitle1");
#endif

// --------------------------------------------------------------------------------------------------------
// PLAYER SELECT defines
//

//#define MAX_PLAYER_SELECT_LINES		8							// max # of pilots displayed at once
int Player_select_max_lines[GR_NUM_RESOLUTIONS] = {			// max # of pilots displayed at once
	12,			// GR_640
	15			// GR_1024
};

// button control defines
#define NUM_PLAYER_SELECT_BUTTONS		9							// button control defines

#define CREATE_PILOT_BUTTON				0							//	
#define CLONE_BUTTON					1							//
#define DELETE_BUTTON					2							//
#define SCROLL_LIST_UP_BUTTON			3							//
#define SCROLL_LIST_DOWN_BUTTON			4							//
#define ACCEPT_BUTTON					5							//
#define SINGLE_BUTTON					6							//
#define MULTI_BUTTON					7
#define TC_BUTTON						8							//

// list text display area
int Choose_list_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		60, 245, 180, 180//170, 265, 400, 87     60 245
	},
	{ // GR_1024
		96,392, 288,288//183, 186, 640, 139
	}
};

char *Player_select_background_bitmap_name[GR_NUM_RESOLUTIONS] = {
	"ChoosePilot",
	"2_ChoosePilot"
};
char *Player_select_background_mask_bitmap[GR_NUM_RESOLUTIONS] = {
	"ChoosePilot-m",
	"2_ChoosePilot-m"
};
// #define PLAYER_SELECT_PALETTE							NOX("ChoosePilotPalette")	// palette for the screen	

#define PLAYER_SELECT_MAIN_HALL_OVERLAY         NOX("MainHall1")				// main hall help overlay

// convenient struct for handling all button controls
struct barracks_buttons {
	char *filename;
	int x, y, xt, yt;
	int hotspot;
	UI_BUTTON button;  // because we have a class inside this struct, we need the constructor below..

	barracks_buttons(char *name, int x1, int y1, int xt1, int yt1, int h) : filename(name), x(x1), y(y1), xt(xt1), yt(yt1), hotspot(h) {}
};

static barracks_buttons Player_select_buttons[GR_NUM_RESOLUTIONS][NUM_PLAYER_SELECT_BUTTONS] = {	
	{ // GR_640
		// create, clone and delete (respectively)
		barracks_buttons("CPB_00",		285,	245,	175,	500,	0), //114,	205,	117,	240,
		barracks_buttons("CPB_01",		285,	309,	175,	240,	1), //172,	205,	175,	240
		barracks_buttons("CPB_02",		285,	277,	229,	240,	2), //226,	205,	229,	240,

		// scroll up, scroll down,	and accept (respectively)
		barracks_buttons("CPB_03",		245,	245,	-1,	-1,	3), //429,	213,	-1,	-1
		barracks_buttons("CPB_04",		245,	405,	-1,	-1,	4), //456,	213,	-1,	-1
		barracks_buttons("CPB_05",		387,	147,	484,	246,	5),	//481,  207,	484,	246,
		
		// single player select and multiplayer select, create tc pilot, respectively
		barracks_buttons("CPB_06",		285,	341,	430,	108,	6), //428,	82,	430,	108,
		barracks_buttons("CPB_07",		285,	373,	481,	108,	7), //477,	82,	481,	108,
		barracks_buttons("CPB_08",		285,    405,    -1,     -1,     8)
	}, 
	{ // GR_1024
		// create, clone and delete (respectively)
		barracks_buttons("2_CPB_00",	460,	404,	199,	384,	0),
		barracks_buttons("2_CPB_01",	460,	504,	292,	384,	1),
		barracks_buttons("2_CPB_02",	460,	454,	379,	384,	2),

		// scroll up, scroll down, and accept (respectively)
		barracks_buttons("2_CPB_03",	396,	404,	-1,	-1,	3),
		barracks_buttons("2_CPB_04",	396,	654,	-1,	-1,	4),
		barracks_buttons("2_CPB_05",	614,	258,	787,	394,	5),	
		
		// single player select and multiplayer select, create tc pilot, respectively
		barracks_buttons("2_CPB_06",	460,	554,	700,	173,	6),
		barracks_buttons("2_CPB_07",	460,	604,	782,	173,	7),
		barracks_buttons("2_CPB_08",	460,	654,    -1,     -1,     8)
	}
};

// FIXME add to strings.tbl
#define PLAYER_SELECT_NUM_TEXT			9
UI_XSTR Player_select_text[GR_NUM_RESOLUTIONS][PLAYER_SELECT_NUM_TEXT] = {
	{ // GR_640
		{ "Add Pilot",			-1,		310,	251,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Clone Pilot",		-1,		310,	315,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Delete Pilot",		-1,		310,	283,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Single Player",		-1,		310,	347,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Multi Player",		-1,		310,	379,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Create TIE Corps Mutli Player", -1,  311, 411, UI_XSTR_COLOR_GREEN, -1, NULL},
	}, 
	{ // GR_1024
		{ "Add Pilot",			-1,		496,	415,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Clone Pilot",		-1,		496,	515,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Delete Pilot",		-1,		496,	465,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		0,		0,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Single Player",		-1,		496,	565,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Multi Player",		-1,		496,	615,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Create TIE Corps Mutli Player", -1,  496, 665, UI_XSTR_COLOR_GREEN, -1, NULL},
	}
};

UI_WINDOW Player_select_window;								// ui window for this screen
UI_BUTTON Player_select_list_region;						// button for detecting mouse clicks on this screen
UI_INPUTBOX Player_select_input_box;						// input box for adding new pilot names				

// #define PLAYER_SELECT_PALETTE_FNAME					NOX("InterfacePalette")
int Player_select_background_bitmap;						// bitmap for this screen
// int Player_select_palette;										// palette bitmap for this screen
int Player_select_autoaccept = 0;
// int Player_select_palette_set = 0;

// flag indicating if this is the absolute first pilot created and selected. Used to determine
// if the main hall should display the help overlay screen
int Player_select_very_first_pilot = 0;			
int Player_select_initial_count = 0;
char Player_select_very_first_pilot_callsign[CALLSIGN_LEN + 2];

extern int Main_hall_bitmap;									// bitmap handle to the main hall bitmap

int Player_select_mode;											// single or multiplayer - never set directly. use player_select_init_player_stuff()
int Player_select_num_pilots;									// # of pilots on the list
int Player_select_list_start;									// index of first list item to start displaying in the box
int Player_select_pilot;									    // index into the Pilot array of which is selected as the active pilot
int Player_select_input_mode;						   			// 0 if the player _isn't_ typing a callsign, 1 if he is
char Pilots_arr[MAX_PILOTS][MAX_FILENAME_LEN];		
char *Pilots[MAX_PILOTS];
int Player_select_clone_flag;									// clone the currently selected pilot
char Player_select_last_pilot[CALLSIGN_LEN + 10];		// callsign of the last used pilot, or none if there wasn't one
int Player_select_last_is_multi;

int Player_select_force_main_hall = 0;

// So the wave file can play a bit after the screen is loaded
int Reg_desk_sound_timestamp = -1;

int Reg_desk_intro_wave_id = -1;

// notification text areas

static int Player_select_bottom_text_y[GR_NUM_RESOLUTIONS] = {
	392,	// GR_640
	502	// GR_1024
};

static int Player_select_middle_text_y[GR_NUM_RESOLUTIONS] = {
	253,	// GR_640
	404	// GR_1024
};

char Player_select_bottom_text[150] = "";
char Player_select_middle_text[150] = "";
void player_select_set_bottom_text(char *txt);
void player_select_set_middle_text(char *txt);

// filenames of the door animations
char *door_anim_name[GR_NUM_RESOLUTIONS] = {
	"CPB_05.ani",
	"2_CPB_05.ani"
};

// first pair : coords of where to play a given door anim
// second pair : center of a given door anim in windowed mode
int door_anim_coords[GR_NUM_RESOLUTIONS][4] = {
	// GR_640
	{387, 147, 400, 200},
	// GR_1024
	{614,258, 400, 200}
};


// the door animations themselves
anim *reg_desk_door_anim;							

// the instance of a given door animation
anim_instance *reg_desk_door_anim_instance;

// handle to sound to play when door opens
int reg_desk_door_sound_handle = -1;

int on_door = 0;

void maybe_anim_door();
void reg_desk_render_door_anim(float frametime);
void reg_desk_handle_region_anim();


// FORWARD DECLARATIONS
void player_select_init_player_stuff(int mode);			// switch between single and multiplayer modes
void player_select_set_input_mode(int n);					
void player_select_button_pressed(int n);
void player_select_scroll_list_up();
void player_select_scroll_list_down();
int player_select_create_new_pilot();
void player_select_delete_pilot();
void player_select_display_all_text();
void player_select_display_copyright();
void player_select_set_bottom_text(char *txt);
void player_select_set_controls(int gray);
void player_select_draw_list();
void player_select_process_noninput(int k);
void player_select_process_input(int k);
int player_select_pilot_file_filter(char *filename);
int player_select_get_last_pilot_info();
void player_select_eval_very_first_pilot();
void player_select_commit();
void player_select_cancel_create();

void reg_desk_maybe_show_button_text();
void reg_desk_force_button_frame();

int test[4];
int door_timestamp = -1;
int door_moving = 0;

// basically, gray out all controls (gray == 1), or ungray the controls (gray == 0) 
void player_select_set_controls(int gray)
{
	int idx;
	
	for(idx=0;idx<NUM_PLAYER_SELECT_BUTTONS;idx++){
		if(gray){
			Player_select_buttons[gr_screen.res][idx].button.disable();
		} else {
			Player_select_buttons[gr_screen.res][idx].button.enable();
		}
	}
}
#include "graphics/font.h"

// functions for selecting single/multiplayer pilots at the very beginning of Freespace
void player_select_init()
{			
	int i;
	barracks_buttons *b;   
	UI_WINDOW *w;

	test[0] = bm_load("test0000");
	test[1] = bm_load("test0001");

	// start a looping ambient sound
	main_hall_start_ambient();

	Player_select_force_main_hall = 0;

	reg_desk_door_anim = NULL;
	reg_desk_door_anim = anim_load(door_anim_name[gr_screen.res]);
	
	if (reg_desk_door_anim == NULL) {
		Warning(LOCATION, "Could not load reg desk door anim\n");
	}

	// null out the animation instances
	reg_desk_door_anim_instance = NULL;

	// clear sound handle
	reg_desk_door_sound_handle = -1;

	
#ifdef FS2_DEMO
	/*
	Demo_title_bitmap = bm_load(Demo_title_bitmap_filename);
	if ( Demo_title_bitmap >= 0 ) {
#ifndef HARDWARE_ONLY
		palette_use_bm_palette(Demo_title_bitmap);
#endif
		Demo_title_active = 1;
		Demo_title_expire_timestamp = timestamp(5000);
	} else {
		Demo_title_active = 0;
	}
	*/
	Demo_title_active = 0;
#endif

	// create the UI window
	Player_select_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);
	Player_select_window.set_mask_bmap(Player_select_background_mask_bitmap[gr_screen.res]);
	
	// initialize the control buttons
	for (i=0; i<NUM_PLAYER_SELECT_BUTTONS; i++) {
		b = &Player_select_buttons[gr_screen.res][i];

		// create the button
		if ( (i == SCROLL_LIST_UP_BUTTON) || (i == SCROLL_LIST_DOWN_BUTTON) )
			b->button.create(&Player_select_window, NULL, b->x, b->y, 60, 30, 1, 1);
		else
			b->button.create(&Player_select_window, NULL, b->x, b->y, 60, 30, 1, 1);

		// set its highlight action
		if (i != ACCEPT_BUTTON)
			b->button.set_highlight_action(common_play_highlight_sound);

		// set its animation bitmaps
		b->button.set_bmaps(b->filename);

		// link the mask hotspot
		b->button.link_hotspot(b->hotspot);
	}		

	// add some text
	w = &Player_select_window;	
	//w->add_XSTR("Create", 1034, Player_select_buttons[gr_screen.res][CREATE_PILOT_BUTTON].xt, Player_select_buttons[gr_screen.res][CREATE_PILOT_BUTTON].yt, &Player_select_buttons[gr_screen.res][CREATE_PILOT_BUTTON].button, UI_XSTR_COLOR_GREEN);	
	//w->add_XSTR("Clone", 1040, Player_select_buttons[gr_screen.res][CLONE_BUTTON].xt, Player_select_buttons[gr_screen.res][CLONE_BUTTON].yt, &Player_select_buttons[gr_screen.res][CLONE_BUTTON].button, UI_XSTR_COLOR_GREEN);	
	//w->add_XSTR("Remove", 1038, Player_select_buttons[gr_screen.res][DELETE_BUTTON].xt, Player_select_buttons[gr_screen.res][DELETE_BUTTON].yt, &Player_select_buttons[gr_screen.res][DELETE_BUTTON].button, UI_XSTR_COLOR_GREEN);	
	
	//w->add_XSTR("Select", 1039, Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].xt, Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].yt, &Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button, UI_XSTR_COLOR_PINK);	
	//w->add_XSTR("Single", 1041, Player_select_buttons[gr_screen.res][SINGLE_BUTTON].xt, Player_select_buttons[gr_screen.res][SINGLE_BUTTON].yt, &Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button, UI_XSTR_COLOR_GREEN);	
	//w->add_XSTR("Multi", 1042, Player_select_buttons[gr_screen.res][MULTI_BUTTON].xt, Player_select_buttons[gr_screen.res][MULTI_BUTTON].yt, &Player_select_buttons[gr_screen.res][MULTI_BUTTON].button, UI_XSTR_COLOR_GREEN);	
//	for(i=0; i<PLAYER_SELECT_NUM_TEXT; i++) {
//		w->add_XSTR(&Player_select_text[gr_screen.res][i]);
//	}


	// create the list button text select region
	Player_select_list_region.create(&Player_select_window, "", Choose_list_coords[gr_screen.res][0], Choose_list_coords[gr_screen.res][1], Choose_list_coords[gr_screen.res][2], Choose_list_coords[gr_screen.res][3], 0, 1);
	Player_select_list_region.hide();

	// create the pilot callsign input box
	Player_select_input_box.create(&Player_select_window, Choose_list_coords[gr_screen.res][0], Choose_list_coords[gr_screen.res][1], Choose_list_coords[gr_screen.res][2] , CALLSIGN_LEN - 1, "", UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_LETTER_FIRST);
	Player_select_input_box.set_valid_chars(VALID_PILOT_CHARS);
	Player_select_input_box.hide();
	Player_select_input_box.disable();
	
	// not currently entering any text
	Player_select_input_mode = 0;	

	// set up hotkeys for buttons so we draw the correct animation frame when a key is pressed
	Player_select_buttons[gr_screen.res][SCROLL_LIST_UP_BUTTON].button.set_hotkey(KEY_UP);
	Player_select_buttons[gr_screen.res][SCROLL_LIST_DOWN_BUTTON].button.set_hotkey(KEY_DOWN);
	Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button.set_hotkey(KEY_ENTER);
	Player_select_buttons[gr_screen.res][CREATE_PILOT_BUTTON].button.set_hotkey(KEY_C);

	// disable the single player button in the multiplayer beta
#ifdef MULTIPLAYER_BETA_BUILD
	Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button.hide();
	Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button.disable();
#elif defined(E3_BUILD) || defined(PRESS_TOUR_BUILD)
	Player_select_buttons[gr_screen.res][MULTI_BUTTON].button.hide();
	Player_select_buttons[gr_screen.res][MULTI_BUTTON].button.disable();
#endif


	// attempt to load in the background bitmap
	Player_select_background_bitmap = bm_load(Player_select_background_bitmap_name[gr_screen.res]);				
	Assert(Player_select_background_bitmap >= 0);	

	// load in the palette for the screen
	// Player_select_palette = bm_load(PLAYER_SELECT_PALETTE);
	// Player_select_palette_set = 0;

	// unset the very first pilot data
	Player_select_very_first_pilot = 0;
	Player_select_initial_count = -1;
	memset(Player_select_very_first_pilot_callsign, 0, CALLSIGN_LEN + 2);	

	
//	if(Player_select_num_pilots == 0){
//		Player_select_autoaccept = 1;
//	}
		
	// if we found a pilot
//#if defined(DEMO) || defined(OEM_BUILD) || defined(E3_BUILD) || defined(PRESS_TOUR_BUILD) // not for FS2_DEMO
#if defined(MP_DEMO)
	player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
#else
	player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);	

	if (player_select_get_last_pilot_info()) {
		if (Player_select_last_is_multi) {
			player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
		} else {
			player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
		}
	} 
	// otherwise go to the single player mode by default
	else {
		player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
	}
#endif	

	if((Player_select_num_pilots == 1) && Player_select_input_mode){
		Player_select_autoaccept = 1;
	}

		
}

#ifdef FS2_DEMO
// Display the demo title screen
void demo_title_blit()
{
	int k;

	Mouse_hidden = 1;

	if ( timestamp_elapsed(Demo_title_expire_timestamp) ) {
		Demo_title_active = 0;
	}

	k = game_poll();
	if ( k > 0 ) {
		Demo_title_active = 0;
	}

	if ( Demo_title_need_fade_in ) {
		gr_fade_out(0);
	}
	
	gr_set_bitmap(Demo_title_bitmap);
	gr_bitmap(0,0);

	gr_flip();

	if ( Demo_title_need_fade_in ) {
		gr_fade_in(0);
		Demo_title_need_fade_in = 0;
	}

	if ( !Demo_title_active ) {
		gr_fade_out(0);
		Mouse_hidden = 0;
	}
}

#endif

void player_select_do(float frametime)
{
	int k = 0;

#ifdef FS2_DEMO
	if ( Demo_title_active ) {
		// demo_title_blit();
		return;
	}
#endif

	//if ( !Player_select_palette_set ) {
	//	Assert(Player_select_palette >= 0);
//#ifndef HARDWARE_ONLY
//		palette_use_bm_palette(Player_select_palette);
//#endif
//		Player_select_palette_set = 1;
//	}
		
	// set the input box at the "virtual" line 0 to be active so the player can enter a callsign
	if (Player_select_input_mode){
		Player_select_input_box.set_focus();
	}

	// process any ui window stuff
	k = Player_select_window.process();
	if(k){
		extern void game_process_cheats(int k);
		game_process_cheats(k);
	}
	switch(k){
	// switch between single and multiplayer modes
	case KEY_TAB : 
#if defined(DEMO) || defined(OEM_BUILD) // not for FS2_DEMO
		break;
#else

		if(Player_select_input_mode){
			gamesnd_play_iface(SND_GENERAL_FAIL);
			break;
		}
		// play a little sound
		gamesnd_play_iface(SND_USER_SELECT);
		if(Player_select_mode == PLAYER_SELECT_MODE_MULTI){					
			//player_select_set_middle_text(XSTR( "Single-Player Mode", 376));
				
			// reinitialize as single player mode
			player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
		} else if(Player_select_mode == PLAYER_SELECT_MODE_SINGLE){										
			//player_select_set_middle_text(XSTR( "Multiplayer Mode", 377));
				
			// reinitialize as multiplayer mode
			player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
		}
		break;	
#endif
	}	

	// draw the player select pseudo-dialog over it
	/*gr_reset_clip();
	gr_clear();
	gr_set_font(FONT2);
	gr_set_bitmap( Current_font->bitmap_id );
	static int r = 0;
	gr_aabitmap_ex(0, 0, 640, 480, 0, 0);

	//gr_print_screen("font");*/
	
	gr_set_bitmap(Player_select_background_bitmap);
	gr_bitmap(0,0);

	/*if (timestamp_elapsed(door_timestamp))
		gr_set_bitmap(test[1]);
	else
	if (door_moving) {
	door_timestamp = timestamp(2000);
	gr_set_bitmap(test[0]);
	
	gr_bitmap(10, 10);
	//}*/
	
	// press the accept button
	if (Player_select_autoaccept) {
		Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button.press_button();
	}
	
	// draw any ui window stuf
	Player_select_window.draw();

	// light up the correct mode button (single or multi)
	/*if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE){
		Player_select_buttons[gr_screen.res][SINGLE_BUTTON].button.draw_forced(2);
	} else {
		Player_select_buttons[gr_screen.res][MULTI_BUTTON].button.draw_forced(2);
	}*/

	// draw the pilot list text
	player_select_draw_list();	

	// draw copyright message on the bottom on the screen
	player_select_display_copyright();

	if (!Player_select_input_mode) {
		player_select_process_noninput(k);
	} else {
		player_select_process_input(k);
	}
	
	// draw any pending messages on the bottom or middle of the screen
	player_select_display_all_text();	

	reg_desk_handle_region_anim();

	maybe_anim_door();
	
	reg_desk_render_door_anim(frametime);
	
	reg_desk_force_button_frame();
	
	reg_desk_maybe_show_button_text();

	gr_flip();

	if (Reg_desk_sound_timestamp < 0)
	{
		// hot pickup line
		//gamesnd_play_iface(SND_REGDESK);
		Reg_desk_intro_wave_id = snd_play(&Snds_iface[SND_REGDESK], 0.0f, 1.0f, SND_PRIORITY_MUST_PLAY);
		Reg_desk_sound_timestamp = 1;
	}

	//player_select_scroll_list_up();
}

void player_select_close()
{
	// destroy the player select window
	Player_select_window.destroy();

	// if we're in input mode - we should undo the pilot create reqeust
	if(Player_select_input_mode){
		player_select_cancel_create();
	}
	
	// actually set up the Player struct here	
	if((Player_select_pilot == -1) || (Player_select_num_pilots == 0)){
		nprintf(("General","WARNING! No pilot selected! We should be exiting the game now!\n"));
		return;
	}

	// unload all bitmaps
	if(Player_select_background_bitmap >= 0){
		bm_release(Player_select_background_bitmap);
		Player_select_background_bitmap = -1;
	} 
	// if(Player_select_palette >= 0){
	// 	bm_release(Player_select_palette);
		//Player_select_palette = -1;
	// }

	// unload door animation handle
	if(reg_desk_door_anim_instance != NULL) {
		anim_stop_playing(reg_desk_door_anim_instance);
		reg_desk_door_anim_instance = NULL;
	}

	// free up door animations/instances
	if((reg_desk_door_anim_instance != NULL) && (anim_playing(reg_desk_door_anim_instance))) {
			reg_desk_door_anim_instance = NULL;			
		}
		if(reg_desk_door_anim != NULL){
			if(anim_free(reg_desk_door_anim) == -1) {
				nprintf(("General","WARNING!, Could not free up door anim %s\n",reg_desk_door_anim));
			}
		}		

	// stop any playing door sound
	if((reg_desk_door_sound_handle != -1) && snd_is_playing(reg_desk_door_sound_handle)) {
		snd_stop(reg_desk_door_sound_handle);
		reg_desk_door_sound_handle = -1;
	}

	// stop reg desk wave
	if (snd_is_playing(Reg_desk_intro_wave_id)) {
		snd_stop(Reg_desk_intro_wave_id);
	}
			
	// setup the player  struct
	Player_num = 0;
	Player = &Players[0];
	Player->flags |= PLAYER_FLAGS_STRUCTURE_IN_USE;
		
	// now read in a the pilot data
	if (read_pilot_file(Pilots[Player_select_pilot], !Player_select_mode, Player) != 0) {
		Error(LOCATION,"Couldn't load pilot file, bailing");
		Player = NULL;
	} 		

	if (Player_select_force_main_hall) {
		Player->main_hall = 1;
	}
}

void player_select_set_input_mode(int n)
{
	int i;

	// set the input mode
	Player_select_input_mode = n;	
	
	// enable all the player select buttons
	for (i=0; i<NUM_PLAYER_SELECT_BUTTONS; i++){
		Player_select_buttons[gr_screen.res][i].button.enable(!n);
	}

	Player_select_buttons[gr_screen.res][ACCEPT_BUTTON].button.set_hotkey(n ? -1 : KEY_ENTER);
	Player_select_buttons[gr_screen.res][CREATE_PILOT_BUTTON].button.set_hotkey(n ? -1 : KEY_C);

	// enable the player select input box
	if(Player_select_input_mode){
		Player_select_input_box.enable();
		Player_select_input_box.unhide();
	} else {
		Player_select_input_box.hide();
		Player_select_input_box.disable();
	}
}
extern int bg_mouse1;
void player_select_button_pressed(int n)
{
	int ret;
		
	int squad_index = -1;

	switch (n) {
	case SCROLL_LIST_UP_BUTTON:
		player_select_set_bottom_text("");

		player_select_scroll_list_up();
		break;

	case SCROLL_LIST_DOWN_BUTTON:
		player_select_set_bottom_text("");

		player_select_scroll_list_down();
		break;

	case ACCEPT_BUTTON:
		// make sure he has a valid pilot selected
		if (Player_select_pilot < 0) {								
			popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR( "You must select a valid pilot first", 378));
		} else {
			player_select_commit();				
		}
		break;

	case CLONE_BUTTON:
		// if we're at max-pilots, don't allow another to be added
		if (Player_select_num_pilots >= MAX_PILOTS) {
			player_select_set_bottom_text(XSTR( "You already have the maximum # of pilots!", 379));
			
			gamesnd_play_iface(SND_GENERAL_FAIL);
			break;
		}

		if (Player_select_pilot >= 0) {						
			// first we have to make sure this guy is actually loaded for when we create the clone
			if (Player == NULL) {
				Player = &Players[0];
				Player->flags |= PLAYER_FLAGS_STRUCTURE_IN_USE;
			}				

			// attempt to read in the pilot file of the guy to be cloned
			if (read_pilot_file(Pilots[Player_select_pilot], !Player_select_mode, Player) != 0) {
				Error(LOCATION,"Couldn't load pilot file, bailing");
				Player = NULL;
				Int3();
			}				

			// set the clone flag
			Player_select_clone_flag = 1;

			// create the new pilot (will be cloned with Player_select_clone_flag_set)
			if (!player_select_create_new_pilot()) {					
				player_select_set_bottom_text(XSTR( "Error creating new pilot file!", 380));
				Player_select_clone_flag = 0;
				memset(Player,0,sizeof(player));
				Player = NULL;
				break;
			}				

			// clear the player out
			// JH: How do you clone a pilot if you clear out the source you are copying
			// from?  These next 2 lines are pure stupidity, so I commented them out!
//			memset(Player,0,sizeof(player));
//			Player = NULL;
				
			// display some text on the bottom of the dialog
			player_select_set_bottom_text(XSTR( "Type Callsign and Press Enter", 381));				
			
			// gray out all controls in the dialog
			player_select_set_controls(1);					
		}
		break;

	case CREATE_PILOT_BUTTON:
		// if we're at max-pilots, don't allow another to be added
		if (Player_select_num_pilots >= MAX_PILOTS){
			player_select_set_bottom_text(XSTR( "You already have the maximum # of pilots!", 379));

			gamesnd_play_iface(SND_GENERAL_FAIL);
			break;
		}

		// create a new pilot
		if (!player_select_create_new_pilot()) {
			player_select_set_bottom_text(XSTR( "Type Callsign and Press Enter", 381));
		}

		// don't clone anyone
		Player_select_clone_flag = 0;
			
		// display some text on the bottom of the dialog			
		player_select_set_bottom_text(XSTR( "Type Callsign and Press Enter", 381));
			
		// gray out all controls
		player_select_set_controls(1);				
		break;

	case DELETE_BUTTON:
		player_select_set_bottom_text("");

		if (Player_select_pilot >= 0) {
			// display a popup requesting confirmation
			ret = popup(PF_TITLE_BIG | PF_TITLE_RED, 2, POPUP_NO, POPUP_YES, XSTR( "Warning!\n\nAre you sure you wish to delete this pilot?", 382));

			// delete the pilot
			if(ret == 1){
				player_select_delete_pilot();
			} 
		}
		break;

	case SINGLE_BUTTON:
#if defined(MP_DEMO)
		player_select_set_bottom_text("Single player unavailable in demo");
		break;
#else
		player_select_set_bottom_text("");

		Player_select_autoaccept = 0;
		// switch to single player mode
		if (Player_select_mode != PLAYER_SELECT_MODE_SINGLE) {
			// play a little sound
			gamesnd_play_iface(SND_USER_SELECT);
				
			//player_select_set_middle_text(XSTR( "Single Player Mode", 376));
				
			// reinitialize as single player mode
			player_select_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
#endif

	case MULTI_BUTTON:
		player_select_set_bottom_text("");

		Player_select_autoaccept = 0;
#if defined(DEMO) || defined(OEM_BUILD) // not for FS2_DEMO
		game_feature_not_in_demo_popup();
#else
		// switch to multiplayer mode
		if (Player_select_mode != PLAYER_SELECT_MODE_MULTI) {
			// play a little sound
			gamesnd_play_iface(SND_USER_SELECT);
			
			//player_select_set_middle_text(XSTR( "Multiplayer Mode", 377));
				
			// reinitialize as multiplayer mode
			player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
#endif
		break;

	case TC_BUTTON:
	
		popup_tc();
	
		break;
	}
}

int player_select_create_new_pilot()
{
	int idx;

	// make sure we haven't reached the max
	if (Player_select_num_pilots >= MAX_PILOTS) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return 0;
	}

	int play_scroll_sound = 1;

#ifdef FS2_DEMO
	if ( Demo_title_active ) {
		play_scroll_sound = 0;
	}
#endif

	if ( play_scroll_sound ) {
		gamesnd_play_iface(SND_SCROLL);
	}

	idx = Player_select_num_pilots;	
	
	// move all the pilots in the list up
	while (idx--) {
		strcpy(Pilots[idx + 1], Pilots[idx]);		
	}	

#ifndef NO_NETWORK
	// by default, set the default netgame protocol to be VMT
	Multi_options_g.protocol = NET_TCP;	
#endif

	// select the beginning of the list
	Player_select_pilot = 0;
	Player_select_num_pilots++;
	Pilots[Player_select_pilot][0] = 0;
	Player_select_list_start= 0;

	// set us to be in input mode
	player_select_set_input_mode(1);
	
	// set the input box to have focus
	Player_select_input_box.set_focus();
	Player_select_input_box.set_text("");
	Player_select_input_box.update_dimensions(Choose_list_coords[gr_screen.res][0], Choose_list_coords[gr_screen.res][1], Choose_list_coords[gr_screen.res][2], gr_get_font_height());	

	return 1;
}

void player_select_delete_pilot()
{
	char filename[MAX_PATH_LEN + 1];
	int i, deleted_cur_pilot;

	deleted_cur_pilot = 0;

	// tack on the full path and the pilot file extension
	// build up the path name length
	// make sure we do this based upon whether we're in single or multiplayer mode
	strcpy( filename, Pilots[Player_select_pilot] );
	strcat( filename, NOX(".plr") );

	int del_rval;
	int popup_rval = 0;
	do {
		// attempt to delete the pilot
		if (Player_select_mode == PLAYER_SELECT_MODE_SINGLE) {
			del_rval = cf_delete( filename, CF_TYPE_SINGLE_PLAYERS );
		} else {
			del_rval = cf_delete( filename, CF_TYPE_MULTI_PLAYERS );
		}

		if(!del_rval) {
			popup_rval = popup(PF_TITLE_BIG | PF_TITLE_RED, 2, XSTR( "&Retry", -1), XSTR("&Cancel",-1),
				XSTR("Error\nFailed to delete pilot file.  File may be read-only.\n", -1));
		}

		//Abort
		if(popup_rval)
		{
			return;
		}

		//Try again
	} while (!del_rval);

	// delete all the campaign save files for this pilot.
	mission_campaign_delete_all_savefiles( Pilots[Player_select_pilot], (Player_select_mode != PLAYER_SELECT_MODE_SINGLE) );

	// move all the players down
	for (i=Player_select_pilot; i<Player_select_num_pilots-1; i++){
		strcpy(Pilots[i], Pilots[i + 1]);		
	}		

	// correcly set the # of pilots and the currently selected pilot
	Player_select_num_pilots--;
	if (Player_select_pilot >= Player_select_num_pilots) {
		Player_select_pilot = Player_select_num_pilots - 1;		
	}		

}

// scroll the list of players up
void player_select_scroll_list_up()
{
	if (Player_select_pilot == -1)
		return;

	// change the pilot selected index and play the appropriate sound
	if (Player_select_pilot) {
		Player_select_pilot--;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
		
	if (Player_select_pilot < Player_select_list_start){
		Player_select_list_start = Player_select_pilot;
	}
}

// scroll the list of players down
void player_select_scroll_list_down()
{	
	// change the pilot selected index and play the appropriate sound
	if (Player_select_pilot < Player_select_num_pilots - 1) {
		Player_select_pilot++;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
		
	if (Player_select_pilot >= (Player_select_list_start + Player_select_max_lines[gr_screen.res])){
		Player_select_list_start++;
	}
}

// fill in the data on the last played pilot (callsign and is_multi or not)
int player_select_get_last_pilot_info()
{
	char *last_player;
 
	last_player = os_config_read_string( NULL, "LastPlayer", NULL);
	
	if(last_player == NULL){
		return 0;		
	} else {
		strcpy(Player_select_last_pilot,last_player);
	}
 
	// determine if he was a single or multi-player based upon the last character in his callsign
	Player_select_last_is_multi = Player_select_last_pilot[strlen(Player_select_last_pilot)-1] == 'M' ? 1 : 0;
	Player_select_last_pilot[strlen(Player_select_last_pilot)-1]='\0';

	return 1;	
}

int player_select_get_last_pilot()
{
	// if the player has the Cmdline_use_last_pilot command line option set, try and drop out quickly
	if(Cmdline_use_last_pilot){			
		int idx;
		

		if(!player_select_get_last_pilot_info()){
			return 0;
		}

		if(Player_select_last_is_multi){
			Player_select_num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_MULTI_PLAYERS, NOX("*.plr"), CF_SORT_TIME);				
		} else {
			Player_select_num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_SINGLE_PLAYERS, NOX("*.plr"), CF_SORT_TIME);						
		}

		Player_select_pilot = -1;
		idx = 0;
		// pick the last player		
		for(idx=0;idx<Player_select_num_pilots;idx++){
			if(strcmp(Player_select_last_pilot,Pilots_arr[idx])==0){
				Player_select_pilot = idx;
				break;
			}
		}		
		// set this so that we don't incorrectly create a "blank" pilot - .plr
		// in the player_select_close() function
		Player_select_num_pilots = 0;

		// if we've actually found a valid pilot, load him up		
		if(Player_select_pilot != -1){
			Player = &Players[0];			
			read_pilot_file(Pilots_arr[idx],!Player_select_last_is_multi,Player);
			Player->flags |= PLAYER_FLAGS_STRUCTURE_IN_USE;
			return 1;		
		}			
	} 

	return 0;
}

void player_select_init_player_stuff(int mode)
{			
	Player_select_list_start = 0;	

	// set the select mode to single player for default
	Player_select_mode = mode;

	// load up the list of players based upon the Player_select_mode (single or multiplayer)
	Get_file_list_filter = player_select_pilot_file_filter;
	if (mode == PLAYER_SELECT_MODE_SINGLE){
		Player_select_num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_SINGLE_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
	} else {
		Player_select_num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_MULTI_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
	}

	Player = NULL;	

	// if this value is -1, it means we should set it to the num pilots count
	if(Player_select_initial_count == -1){
		Player_select_initial_count = Player_select_num_pilots;
	}
		
	// select the first pilot if any exist, otherwise set to -1
	if (Player_select_num_pilots == 0) {		
		Player_select_pilot = -1;		
		player_select_set_bottom_text(XSTR( "Type Callsign and Press Enter", 381));
		player_select_set_controls(1);		// gray out the controls
		player_select_create_new_pilot();
	} else {
		Player_select_pilot = -1;
		int idx = 0;
		// pick the last player		
		for(idx=0;idx<Player_select_num_pilots;idx++){
			if(strcmp(Player_select_last_pilot,Pilots_arr[idx])==0){
				Player_select_pilot = idx;
				break;
			}
		}		
	}
}

void player_select_draw_list()
{
	int idx;

	for (idx=0; idx<Player_select_max_lines[gr_screen.res]; idx++) {
		// only draw as many pilots as we have
		if ((idx + Player_select_list_start) == Player_select_num_pilots)
			break;

		// if the currently selected pilot is this line, draw it highlighted
		if ( (idx + Player_select_list_start) == Player_select_pilot) {
			// if he's the active pilot and is also the current selection, super-highlight him									
			gr_set_color_fast(&Color_bright_white);
		}
		// otherwise draw him normally
		else {
			gr_set_color_fast(&Color_bright_blue);
		}
		
		// draw the actual callsign
		gr_printf(Choose_list_coords[gr_screen.res][0], Choose_list_coords[gr_screen.res][1] + (idx * gr_get_font_height()), Pilots[idx + Player_select_list_start]);
	}
}

void player_select_process_noninput(int k)
{
	int idx;
	
	// check for pressed buttons
	for (idx=0; idx<NUM_PLAYER_SELECT_BUTTONS; idx++) {
		if (Player_select_buttons[gr_screen.res][idx].button.pressed()) {
			player_select_button_pressed(idx);
		}
	}	

	// check for keypresses
	switch (k) {			
	// quit the game entirely
	case KEY_ESC:
		gameseq_post_event(GS_EVENT_QUIT_GAME);
		break;

	case KEY_ENTER | KEY_CTRLED:
		player_select_button_pressed(ACCEPT_BUTTON);
		break;

	// delete the currently highlighted pilot
	case KEY_DELETE:
		if (Player_select_pilot >= 0) {
			int ret;

			// display a popup requesting confirmation
			ret = popup(PF_USE_AFFIRMATIVE_ICON | PF_USE_NEGATIVE_ICON,2,POPUP_NO,POPUP_YES,XSTR( "Are you sure you want to delete this pilot?", 383));										

			// delete the pilot
			if(ret == 1){
				player_select_delete_pilot();
			} 
		}
		break;	
	}

	// check to see if the user has clicked on the "list region" button
	// and change the selected pilot appropriately
	if (Player_select_list_region.pressed()) {
		int click_y;
		// get the mouse position
		Player_select_list_region.get_mouse_pos(NULL, &click_y);
		
		// determine what index to select
		//idx = (click_y+5) / 10;
		idx = click_y / gr_get_font_height();


		// if he selected a valid item
		if(((idx + Player_select_list_start) < Player_select_num_pilots) && (idx >= 0)){
			Player_select_pilot = idx + Player_select_list_start;			
		}
	}

	// if the player has double clicked on a valid pilot, choose it and hit the accept button
	if (Player_select_list_region.double_clicked()) {
		if ((Player_select_pilot >= 0) && (Player_select_pilot < Player_select_num_pilots)) {
			player_select_button_pressed(ACCEPT_BUTTON);
		}
	}
}

void player_select_process_input(int k)
{
	char buf[CALLSIGN_LEN + 1];
	int idx,z;
	
	// if the player is in the process of typing in a new pilot name...
	switch (k) {
	// cancel create pilot
	case KEY_ESC:
		player_select_cancel_create();		
		break;

	// accept a new pilot name
	case KEY_ENTER:
		Player_select_input_box.get_text(buf);
		drop_white_space(buf);
		z = 0;
		if (!isalpha(*buf)) {
			z = 1;
		} else {
			for (idx=1; buf[idx]; idx++) {
				if (!isalpha(buf[idx]) && !isdigit(buf[idx]) && !strchr(VALID_PILOT_CHARS, buf[idx])) {
					z = 1;
					break;
				}
			}
		}

		for (idx=1; idx<Player_select_num_pilots; idx++) {
			if (!stricmp(buf, Pilots[idx])) {
				// verify if it is ok to overwrite the file
				if (pilot_verify_overwrite() == 1) {
					// delete the pilot and select the beginning of the list
					Player_select_pilot = idx;
					player_select_delete_pilot();
					Player_select_pilot = 0;
					idx = Player_select_num_pilots;
					z = 0;

				} else
					z = 1;

				break;
			}
		}

		if (!*buf || (idx < Player_select_num_pilots)) {
			z = 1;
		}

		if (z) {
			gamesnd_play_iface(SND_GENERAL_FAIL);
			break;
		}		

		// Create the new pilot, and write out his file
		strcpy(Pilots[0], buf);

		// if this is the first guy, we should set the Player struct
		if (Player == NULL) {
			Player = &Players[0];
			memset(Player, 0, sizeof(player));
			Player->flags |= PLAYER_FLAGS_STRUCTURE_IN_USE;
		}

		strcpy(Player->callsign, buf);
		init_new_pilot(Player, !Player_select_clone_flag);

		// set him as being a multiplayer pilot if we're in the correct mode
		if (Player_select_mode == PLAYER_SELECT_MODE_MULTI) {
			Player->flags |= PLAYER_FLAGS_IS_MULTI;
			Player->stats.flags |= STATS_FLAG_MULTIPLAYER;
		}

		// create his pilot file
		write_pilot_file(Player);

		// unset the player
		memset(Player, 0, sizeof(player));
		Player = NULL;

		// make this guy the selected pilot and put him first on the list
		Player_select_pilot = 0;
				
		// unset the input mode
		player_select_set_input_mode(0);

		// clear any pending bottom text
		player_select_set_bottom_text("");		

		// clear any pending middle text
		player_select_set_middle_text("");
				
		// ungray all the controls
		player_select_set_controls(0);

		// evaluate whether or not this is the very first pilot
		player_select_eval_very_first_pilot();
		break;

	case 0:
		break;

	// always kill middle text when a char is pressed in input mode
	default:
		player_select_set_middle_text("");
		break;
	}
}
    
// draw copyright message on the bottom on the screen
void player_select_display_copyright()
{
	// changed so I get credit - Den
	int	sx, sy, w;
	char Copyright_msg1[256];
	char Copyright_msg2[] = "Copyright (c) 1999, Volition, Inc. Copyright (c) 2004, FS2_Open Team.";
	char msg3[] = "Copyright (c) 2004, Emperor's Hammer. All rights reserved.";

	gr_set_color_fast(&Color_white);

	get_version_string(Copyright_msg1);
	
	gr_get_string_size(&w, NULL, Copyright_msg1);
	sx = fl2i((gr_screen.max_w / 2) - w/2.0f + 0.5f);
	sy = (gr_screen.max_h - 2) - 3*gr_get_font_height();
	
	//gr_string(sx, sy, Copyright_msg1);

	gr_get_string_size(&w, NULL, Copyright_msg2);
	sx = fl2i((gr_screen.max_w / 2) - w/2.0f + 0.5f);
	sy = (gr_screen.max_h - 2) - 2*gr_get_font_height();
 
	//gr_string(sx, sy, Copyright_msg2);

	gr_get_string_size(&w, NULL, msg3);
	sx = fl2i((gr_screen.max_w / 2) - w/2.0f + 0.5f);
	sy = (gr_screen.max_h - 2) - gr_get_font_height();

	//gr_string(sx, sy, msg3);
}

void player_select_display_all_text()
{
	int w, h;

	// only draw if we actually have a valid string
	if (strlen(Player_select_bottom_text)) {
		gr_get_string_size(&w, &h, Player_select_bottom_text);
		w = 178;	
		//w = (gr_screen.max_w - w) / 2;
		gr_set_color_fast(&Color_bright_white);
		gr_printf(w, Player_select_bottom_text_y[gr_screen.res], Player_select_bottom_text);
	}

	// only draw if we actually have a valid string
	if (strlen(Player_select_middle_text)) {
		gr_get_string_size(&w, &h, Player_select_middle_text);
		w = 300;
		//w = (gr_screen.max_w - w) / 2;
		gr_set_color_fast(&Color_bright_white);
		gr_printf(w, Player_select_middle_text_y[gr_screen.res], Player_select_middle_text);
	}
}

int player_select_pilot_file_filter(char *filename)
{
	return !verify_pilot_file(filename, Player_select_mode == PLAYER_SELECT_MODE_SINGLE);
}

void player_select_set_bottom_text(char *txt)
{
	if (txt) {
		strncpy(Player_select_bottom_text, txt, 149);
	}
}

void player_select_set_middle_text(char *txt)
{
	if (txt) {
		strncpy(Player_select_middle_text, txt, 149);
	}
}

void player_select_eval_very_first_pilot()
{	
	// never bring up the initial main hall help overlay
	// Player_select_very_first_pilot = 0;

	// if we already have this flag set, check to see if our callsigns match
	if(Player_select_very_first_pilot){
		// if the callsign has changed, unset the flag
		if(strcmp(Player_select_very_first_pilot_callsign,Pilots[Player_select_pilot])){
			Player_select_very_first_pilot = 0;
		}
	}
	// otherwise check to see if there is only 1 pilot
	else {
		if((Player_select_num_pilots == 1) && (Player_select_initial_count == 0)){
			// set up the data
			Player_select_very_first_pilot = 1;
			strcpy(Player_select_very_first_pilot_callsign,Pilots[Player_select_pilot]);
		}
	}
}

void player_select_commit()
{
	// if we've gotten to this point, we should have ensured this was the case
	Assert(Player_select_num_pilots > 0);
	
	 	
#if defined(MP_DEMO)
	// function does all the good stuff to get the game ready for MP, just use this instead of doing it
	// all over
	Game_mode = GM_MULTIPLAYER;
	main_hall_do_multi_ready();
#else
	gameseq_post_event(GS_EVENT_MAIN_MENU);
	player_select_eval_very_first_pilot();
#endif
	//gameseq_post_event(GS_EVENT_MAIN_MENU);
	
	//gamesnd_play_iface(SND_COMMIT_PRESSED);

	// evaluate if this is the _very_ first pilot
	//player_select_eval_very_first_pilot();
} 

void player_select_cancel_create()
{
	int idx;

	Player_select_num_pilots--;

	// make sure we correct the Selected_pilot index to account for the cancelled action
	if (Player_select_num_pilots == 0) {
		Player_select_pilot = -1;
	}

	// move all pilots down
	for (idx=0; idx<Player_select_num_pilots; idx++) {
		strcpy(Pilots[idx], Pilots[idx + 1]);
	}

	// unset the input mode
	player_select_set_input_mode(0);

	// clear any bottom text
	player_select_set_bottom_text("");

	// clear any middle text
	player_select_set_middle_text("");

	// ungray all controls
	player_select_set_controls(0);

	// disable the autoaccept
	Player_select_autoaccept = 0;
}

DCF(bastion,"Sets the player to be on the bastion")
{
	if(gameseq_get_state() == GS_STATE_INITIAL_PLAYER_SELECT){
		Player_select_force_main_hall = 1;
		dc_printf("Player is now in the Bastion\n");
	}
}

#define MAX_PLAYER_TIPS			40

char *Player_tips[MAX_PLAYER_TIPS];
int Num_player_tips;
int Player_tips_shown = 0;

// tooltips
void player_tips_init()
{
	Num_player_tips = 0;

	// begin external localization stuff
	lcl_ext_open();

	read_file_text("tips.tbl");
	reset_parse();

	while(!optional_string("#end")){
		required_string("+Tip:");

		if(Num_player_tips >= MAX_PLAYER_TIPS){
			break;
		}
		Player_tips[Num_player_tips++] = stuff_and_malloc_string(F_NAME, NULL, 1024);				
	}

	// stop externalizing, homey
	lcl_ext_close();
}
void player_tips_popup()
{
	int tip, ret;	
	
	// player has disabled tips
	if((Player != NULL) && !Player->tips){
		return;
	}
	// only show tips once per instance of Freespace
	if(Player_tips_shown == 1){
		return;
	}
	Player_tips_shown = 1;

	// randomly pick one
	tip = (int)frand_range(0.0f, (float)Num_player_tips - 1.0f);

	char all_txt[2048];	

	do {
		sprintf(all_txt, XSTR("NEW USER TIP\n\n%s", 1565), Player_tips[tip]);
		ret = popup(PF_NO_SPECIAL_BUTTONS | PF_TITLE | PF_TITLE_WHITE, 3, XSTR("&Ok", 669), XSTR("&Next", 1444), XSTR("Don't show me this again", 1443), all_txt);
		
		// now what?
		switch(ret){
		// next
		case 1:
			if(tip >= Num_player_tips - 1){
				tip = 0;
			} else {
				tip++;
			}
			break;

		// don't show me this again
		case 2:
			ret = 0;
			Player->tips = 0;
			write_pilot_file(Player);
			break;
		}
	} while(ret > 0);
}


void maybe_anim_door()
{
	barracks_buttons *b;

	// set flag so reg_desk_handle_region_anim() knows if cursor is over the door or not
	on_door = 0;
	
	b = &Player_select_buttons[gr_screen.res][ACCEPT_BUTTON];

	if (b->button.button_hilighted()) {
		on_door = 1;

		door_moving = 1;

		// if the animation is not playing, start it playing
		if (!reg_desk_door_anim_instance) {
			if (reg_desk_door_anim) {
				anim_play_struct aps;

				anim_play_init(&aps, reg_desk_door_anim, door_anim_coords[gr_screen.res][0], door_anim_coords[gr_screen.res][1]);
				aps.screen_id = GS_STATE_INITIAL_PLAYER_SELECT;
				aps.framerate_independent = 1;
											
				reg_desk_door_anim_instance = anim_play(&aps);

				if (reg_desk_door_sound_handle != -1) {			
					snd_stop(reg_desk_door_sound_handle);
				}
				
				//if (reg_desk_door_sound_handle == -1) {
				reg_desk_door_sound_handle = snd_play(&Snds_iface[SND_MAIN_HALL_DOOR_OPEN], 0.70f);  //&Snds_iface[Main_hall->door_sounds[region][0]],Main_hall->door_sound_pan[region]);				

				// start the sound playing at the right spot relative to the completion of the animation		
				if (reg_desk_door_anim_instance->frame_num != -1){
				
				//	float a = (float)reg_desk_door_anim_instance->frame_num / (float)reg_desk_door_anim_instance->parent->total_frames;
				//	if (reg_desk_door_anim_instance->parent->total_frames == 0)
				//		a = 0;
					snd_set_pos(reg_desk_door_sound_handle, &Snds_iface[SND_MAIN_HALL_DOOR_OPEN],// 0, 1);
							(float)reg_desk_door_anim_instance->frame_num / (float)reg_desk_door_anim_instance->parent->total_frames,1);
				}
	
		
	
			}
		} 
	}
	// otherwise if its playing in the reverse direction, change it to the forward direction
	if (reg_desk_door_anim_instance) { 
		if (reg_desk_door_anim_instance->frame_num > 15) { 
	//	anim_reverse_direction(reg_desk_door_anim_instance);
		if(reg_desk_door_sound_handle != -1){			
		//		snd_stop(reg_desk_door_sound_handle);	
			}
			
			reg_desk_door_sound_handle = snd_play(&Snds_iface[SND_MAIN_HALL_DOOR_CLOSE], 0.70f);  //&Snds_iface[Main_hall->door_sounds[region][0]],Main_hall->door_sound_pan[region]);				

			// start the sound playing at the right spot relative to the completion of the animation		
			if(reg_desk_door_anim_instance->frame_num != -1){			
				snd_set_pos(reg_desk_door_sound_handle, &Snds_iface[SND_MAIN_HALL_DOOR_CLOSE],
							(float)reg_desk_door_anim_instance->frame_num / (float)reg_desk_door_anim_instance->parent->total_frames,1);
			}
		}
	}
	
}

// render all playing door animations
void reg_desk_render_door_anim(float frametime)
{
	// render it
	if(reg_desk_door_anim_instance != NULL){
		anim_render_one(GS_STATE_INITIAL_PLAYER_SELECT, reg_desk_door_anim_instance, frametime);
	}
}

// handle starting, stopping, and reversing animation
void reg_desk_handle_region_anim()
{
	if((reg_desk_door_anim_instance != NULL) && !anim_playing(reg_desk_door_anim_instance)) {
		reg_desk_door_anim_instance = NULL;
	}
	
	// go through each region animation
	// if the instance is not null and the animation is playing
	if((reg_desk_door_anim_instance != NULL) && anim_playing(reg_desk_door_anim_instance)) {
			
	// check to see if we should hold a given door "open"
		if((on_door) && (reg_desk_door_anim_instance->frame_num == 15)) {//reg_desk_door_anim_instance->stop_at)) {
			anim_pause(reg_desk_door_anim_instance);
			reg_desk_door_anim_instance->stop_now = FALSE;
			snd_stop(reg_desk_door_sound_handle);
		}
			
		// check to see if we should close a door being held open
		if((!on_door) && (reg_desk_door_anim_instance->paused)){
			anim_unpause(reg_desk_door_anim_instance);
	
		}
	}
}	

void reg_desk_force_button_frame()
{
	for (int x=0; x<NUM_PLAYER_SELECT_BUTTONS; x++) {
		// don't want the exit door being drawn then can't see ani
		if (x != ACCEPT_BUTTON) {
			if ( !Player_select_buttons[gr_screen.res][x].button.button_down()) 
				Player_select_buttons[gr_screen.res][x].button.draw_forced(1);
		}
	}
}

void reg_desk_maybe_show_button_text()
{
	barracks_buttons *b;
	
	for (int i=0; i<NUM_PLAYER_SELECT_BUTTONS; i++) {
		b = &Player_select_buttons[gr_screen.res][i];

		if (b->button.button_hilighted()) {
			gr_set_color_fast(&Color_bright_white);
			gr_string(Player_select_text[gr_screen.res][i].x, Player_select_text[gr_screen.res][i].y, Player_select_text[gr_screen.res][i].xstr);
		}
	}
}


// this is for making a pilot based on their TC stats.  it is similar to the other function to create a pilot
// but there are enough differences that warrented making another function to create these guys
void player_select_make_tc_pilot(Idline id, char *name)
{
		char callsign[CALLSIGN_LEN + 1] = "";
		int idx = Player_select_num_pilots;
		int squad_index = -1;
		char squad[40];

		strcpy(callsign, name);
	
		Player_select_mode = PLAYER_SELECT_MODE_MULTI;
		player_select_init_player_stuff(PLAYER_SELECT_MODE_MULTI);

		int a = 0;
		for (idx=1; idx<Player_select_num_pilots; idx++) {
			if (!stricmp(callsign, Pilots[idx])) {
				// verify if it is ok to overwrite the file
				if (pilot_verify_overwrite() == 1) {
					// delete the pilot and select the beginning of the list
					Player_select_pilot = idx;
					player_select_delete_pilot();
					Player_select_pilot = 0;
					idx = Player_select_num_pilots;
				} else
					a = 1;
				
				break;
			}
		}
		// doesn't want to overwrite so we are bailing..............ugly, but its pretty on the inside
		if (a)
			return;
		
		// move all the pilots in the list up
		while (idx--) {
			strcpy(Pilots[idx + 1], Pilots[idx]);		
		}	

		Player_select_pilot = 0;
		Player_select_num_pilots++;
		Pilots[Player_select_pilot][0] = 0;
		Player_select_list_start= 0;
	
		// Create the new pilot, and write out his file
		strcpy(Pilots[0], callsign);

		// if this is the first guy, we should set the Player struct
		if (Player == NULL) {
			Player = &Players[0];
			memset(Player, 0, sizeof(player));
			Player->flags |= PLAYER_FLAGS_STRUCTURE_IN_USE;
		}

		strcpy(Player->callsign, callsign);
		init_new_pilot(Player, !Player_select_clone_flag);

		// set him as being a multiplayer pilot
		Player->flags |= PLAYER_FLAGS_IS_MULTI;
		Player->stats.flags |= STATS_FLAG_MULTIPLAYER;
		

		Player->stats.rank = get_rank(id.rank); 
		Player->stats.fchg = get_fchg(id.fchg); 
		make_medals(&Player->stats, id.medals);

		//strcpy(Player->quote, id.quote.c_str());

		//strcpy(squad, id.placement.squad.c_str());
		//squad[id.placement.squad.length()-1] = '\0';
		
		for (int x=0; x<Num_pilot_squad_images; x++) {
			//fprintf(fp, "%s\t%s\n", id.placement.squad.c_str(), Pilot_squad_image_names[x]);
			if ( !(stricmp(squad, Pilot_squad_image_names[x])) )
			//if ( !(stricmp("omega", Pilot_squad_image_names[x])) )
			{
				squad_index = x;
				//fprintf(fp, "%d\n", squad_index);
			}
			
		}
		
		if (squad_index >= 0)
			strcpy(Player->squad_filename, Pilot_squad_image_names[squad_index]);
		//28

		// special things come to those that are of the TC
		Player->flags |= PLAYER_FLAGS_IS_TC_PILOT;

		// create his pilot file
		write_pilot_file(Player);

		// unset the player
		memset(Player, 0, sizeof(player));
		Player = NULL;

		// make this guy the selected pilot and put him first on the list
		Player_select_pilot = 0;
				
		// evaluate whether or not this is the very first pilot
		player_select_eval_very_first_pilot();
}

