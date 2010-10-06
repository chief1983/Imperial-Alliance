/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/pilotmanage.cpp $
 * $Revision: 1.2 $
 * $Date: 2004/09/07 22:56:14 $
 * $Author: Darkhill $
 *
 * C file for implementing pilot manage section
 *
 * $Log: pilotmanage.cpp,v $
 * Revision 1.2  2004/09/07 22:56:14  Darkhill
 * -Hopefully fixed a lot of the linker warnings.
 *
 * -Cleaned up some of the interface stuff.
 *
 * -Add a tag to the mission file so that up to three flight groups can be selected to have the player edit ships and weapons.  This gets rid of the old Alpha, Beta, and Gamma groups that were hard coded.
 *
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:47:42  Darkhill
 * no message
 *
 * Revision 2.6  2004/02/14 00:18:33  randomtiger
 * Please note that from now on OGL will only run with a registry set by Launcher v4. See forum for details.
 * OK, these changes effect a lot of file, I suggest everyone updates ASAP:
 * Removal of many files from project.
 * Removal of meanless Gr_bitmap_poly variable.
 * Removal of glide, directdraw, software modules all links to them, and all code specific to those paths.
 * Removal of redundant Fred paths that arent needed for Fred OGL.
 * Have seriously tidied the graphics initialisation code and added generic non standard mode functionality.
 * Fixed many D3D non standard mode bugs and brought OGL up to the same level.
 * Removed texture section support for D3D8, voodoo 2 and 3 cards will no longer run under fs2_open in D3D, same goes for any card with a maximum texture size less than 1024.
 *
 * Revision 2.5  2004/02/10 21:47:47  Goober5000
 * fixed the barracks crash bug
 * --Goober5000
 *
 * Revision 2.4  2003/08/20 08:11:00  wmcoolmon
 * Added error screens to the barracks and start screens when a pilot file can't be deleted
 *
 * Revision 2.3  2003/03/18 10:07:03  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.2.2.1  2002/09/24 18:56:43  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.2  2002/08/01 01:41:06  penguin
 * The big include file move
 *
 * Revision 2.1  2002/07/07 19:55:59  penguin
 * Back-port to MSVC
 *
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/04 04:52:22  mharris
 * 1st draft at porting
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 42    10/25/99 5:47p Jefff
 * reassigned some xstr ids
 * 
 * 41    9/14/99 11:01p Jefff
 * stats area coord fix
 * 
 * 40    9/09/99 11:24a Jefff
 * 
 * 39    9/02/99 11:26a Jefff
 * fixed incorrect pilot list dimensions
 * 
 * 38    8/17/99 2:24p Dave
 * Fixed wacky squad color stuff.
 * 
 * 37    8/16/99 4:27p Jefff
 * fix button position on squad change error popup
 * 
 * 36    8/11/99 3:58p Jefff
 * fixed player list box coord bug
 * 
 * 35    8/05/99 2:46p Jefff
 * added popup to the disabled squad selection buttons in single player
 * 
 * 34    8/02/99 11:02p Dave
 * Fixed up squad filename and squad name copying when converting a pilot
 * between single and multiplayer.
 * 
 * 33    7/27/99 7:17p Jefff
 * Replaced some art text with XSTR() text.
 * 
 * 32    7/15/99 9:20a Andsager
 * FS2_DEMO initial checkin
 * 
 * 31    6/29/99 7:39p Dave
 * Lots of small bug fixes.
 * 
 * 30    6/16/99 4:06p Dave
 * New pilot info popup. Added new draw-bitmap-as-poly function.
 * 
 * 29    6/11/99 11:13a Dave
 * last minute changes before press tour build.
 * 
 * 28    4/25/99 7:43p Dave
 * Misc small bug fixes. Made sun draw properly.
 * 
 * 27    4/25/99 3:02p Dave
 * Build defines for the E3 build.
 * 
 * 26    3/24/99 4:05p Dave
 * Put in support for assigning the player to a specific squadron with a
 * specific logo. Preliminary work for doing pos/orient checksumming in
 * multiplayer to reduce bandwidth.
 * 
 * 25    2/25/99 4:19p Dave
 * Added multiplayer_beta defines. Added cd_check define. Fixed a few
 * release build warnings. Added more data to the squad war request and
 * response packets.
 * 
 * 24    2/02/99 12:09p Neilk
 * Fixed text coords, centered pilot and squad pics in 1024x768, added vss
 * comment template
 *
 * $NoKeywords: $
 */
#include "globalincs/pstypes.h"
#include "menuui/barracks.h"
#include "playerman/managepilot.h"
#include "ui/ui.h"
#include "graphics/font.h"
#include "io/key.h"
#include "gamesnd/gamesnd.h"
#include "osapi/osapi.h"
#include "popup/popup.h"
#include "menuui/playermenu.h"
#include "gamesequence/gamesequence.h"
#include "gamehelp/contexthelp.h"
#include "graphics/2d.h"
#include "ctype.h"
#include "freespace2/freespace.h"
#include "globalincs/systemvars.h"
#include "bmpman/bmpman.h"
#include "io/mouse.h"
#include "osapi/osregistry.h"
#include "globalincs/alphacolors.h"
#include "debugconsole/dbugfile.h"
#include "menuui/snazzyui.h"
#include "Playerman/Player.h"
#include "parse/parselo.h"
#include "ship/ship.h"

#include "popup/popuptc.h"
#include "EH_Medals/idline.h"
#include "EH_Medals/convert.h"

static int prev_single_player = -1;
static int prev_multi_player = -1;

void pilot_manage_maybe_show_button_text();
void pilot_manage_force_button_frame();

//////////////////////////////////////////////////////////
// button defines
#define PM_NUM_BUTTONS					11

#define PM_UP_BUTTON					0
#define PM_DOWN_BUTTON					1
#define PM_SINGLE_MODE_BUTTON			2
#define PM_MULTI_MODE_BUTTON			3
#define PM_ACTIVE_BUTTON				4
#define PM_CREATE_BUTTON				5	
#define PM_CLONE_BUTTON					6		
#define PM_DELETE_BUTTON				7	
#define PM_CONVERT_BUTTON				8
#define PM_EXIT_BUTTON					9
#define PM_TC_BUTTON					10

static char *PilotManage_bitmap_fname[GR_NUM_RESOLUTIONS] = {
	"PilotMan",
	"2_PilotMan"
};

static char *PilotManage_bitmap_mask_fname[GR_NUM_RESOLUTIONS] = {
	"PilotMan-M",
	"2_PilotMan-M"
};

struct pilot_manage_buttons {
	char *filename;
	int x, y;
	int text_x, text_y;	// this is where the text label is
	int hotspot;
	int repeat;
	UI_BUTTON button;  // because we have a class inside this struct, we need the constructor below..

	pilot_manage_buttons(char *name, int x1, int y1, int x2, int y2, int h, int r = 0) : filename(name), x(x1), y(y1), text_x(x2), text_y(y2), hotspot(h), repeat(r) {}
};

static pilot_manage_buttons Buttons[GR_NUM_RESOLUTIONS][PM_NUM_BUTTONS] = {
	{
		pilot_manage_buttons("PMB_00", 565,  47,	11,		157,	0),		
		pilot_manage_buttons("PMB_01", 565, 345,	0,		0,		1),
		pilot_manage_buttons("PMB_02", 325, 375,	0,		0,		2),
		pilot_manage_buttons("PMB_03", 325, 405,	0,		0,		3),
		pilot_manage_buttons("PMB_04", 485, 375,	0,		0,		4),
		pilot_manage_buttons("PMB_05", 45,  375,	326,	441,		5),
		pilot_manage_buttons("PMB_06", 100, 375,	395,	441,		6),
		pilot_manage_buttons("PMB_07", 155, 375,	457,	441,		7),
		pilot_manage_buttons("PMB_08", 210, 375,	519,	441,		8),
		pilot_manage_buttons("PMB_09", 540, 375,	0,		0,		9),
		pilot_manage_buttons("PMB_10", 265, 375,	0,		0,		10),
	},
	{
		pilot_manage_buttons("PMB_00", 904,  76,	11,		157,	0),		
		pilot_manage_buttons("PMB_01", 904, 552,	0,		0,		1),
		pilot_manage_buttons("PMB_02", 520, 600,	0,		0,		2),
		pilot_manage_buttons("PMB_03", 520, 648,	0,		0,		3),
		pilot_manage_buttons("PMB_04", 776, 600,	0,		0,		4),
		pilot_manage_buttons("PMB_05", 72,  600,	0,		0,		5),
		pilot_manage_buttons("PMB_06", 160, 600,	0,		0,		6),
		pilot_manage_buttons("PMB_07", 248, 600,	0,		0,		7),
		pilot_manage_buttons("PMB_08", 336, 600,	0,		0,		8),
		pilot_manage_buttons("PMB_09", 864, 600,	0,		0,		9),
		pilot_manage_buttons("PMB_10", 424, 600,	0,		0,		10),
	}
};

#define PILOT_MANAGE_NUM_TEXT 11

UI_XSTR Pilot_manage_text[GR_NUM_RESOLUTIONS][PILOT_MANAGE_NUM_TEXT] = {
	{ // GR_640
		{ "",					-1,		350,	381,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		350,	381,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Single Player",		-1,		350,	381,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Multi Player",		-1,		350,	411,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Select",				-1,		487,	396,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Create",				-1,		47,		396,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Clone",				-1,		104,	396,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Remove",				-1,		155,	396,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Convert",			-1,		207,	396,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Accept",				-1,		541,	396,		UI_XSTR_COLOR_GREEN, -1, NULL },		
		{ "TC PIN",				-1,		265,	396,		UI_XSTR_COLOR_GREEN, -1, NULL},
	}, 
	{ // GR_1024
		{ "",					-1,		350,	381,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "",					-1,		350,	381,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Single Player",		-1,		560,	610,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Multi Player",		-1,		560,	658,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Select",				-1,		779,	634,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Create",				-1,		 75,    634,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Clone",				-1,		166,	634,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Remove",				-1,		248,	634,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Convert",			-1,		331,	634,		UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Accept",				-1,		866,	634,		UI_XSTR_COLOR_GREEN, -1, NULL },		
		{ "TC PIN",				-1,		424,	634,		UI_XSTR_COLOR_GREEN, -1, NULL},
	}
};

//Returns 0 on failure, 1 on success
int delete_pilot_file( char *pilot_name, int single );		// manage_pilot.cpp

// constants for coordinate lookup
#define PM_X_COORD 0
#define PM_Y_COORD 1
#define PM_W_COORD 2
#define PM_H_COORD 3

// pilot selection field
static int Pilot_manage_list_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		67, 47, 510, 318
	},
	{ // GR_1024
		80, 76,	816, 509
	}
};

static int Background_bitmap = -1;
static UI_WINDOW Ui_window;
static UI_BUTTON List_region;
static UI_INPUTBOX Inputbox;

extern int Player_sel_mode;

extern player *Cur_pilot;
static int Num_pilots;
static int Selected_line;
static char Pilots_arr[MAX_PILOTS][MAX_FILENAME_LEN];
static char *Pilots[MAX_PILOTS];
static int Pic_number;
static int Pic_squad_number;
static bool pilot_manage_callsign_enter_mode;
static int Pilot_ranks[MAX_PILOTS];
static int List_scroll_offset;
static int Clone_flag;
static int Pilot_images[MAX_PILOT_IMAGES];
static int Pilot_squad_images[MAX_PILOT_IMAGES];
static int Rank_pips_bitmaps;
static int Rank_pips_count;

// needs to go with new pilot management crap
// sets or clears hotkeys for pilot selection.
void pilot_manage_set_hotkeys(bool pilot_text_enter_mode)
{
	Buttons[gr_screen.res][PM_UP_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_UP : -1);
	Buttons[gr_screen.res][PM_DOWN_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_DOWN : -1);
	Buttons[gr_screen.res][PM_SINGLE_MODE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_LEFT : -1);

	
	Buttons[gr_screen.res][PM_ACTIVE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_ENTER : -1);
	Buttons[gr_screen.res][PM_DELETE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_DELETE : -1);

	Buttons[gr_screen.res][PM_MULTI_MODE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_RIGHT : -1);
	Buttons[gr_screen.res][PM_ACTIVE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_ENTER : -1);

	Buttons[gr_screen.res][PM_CREATE_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_CTRLED | KEY_ENTER : -1);

	Buttons[gr_screen.res][PM_TC_BUTTON].button.set_hotkey(pilot_text_enter_mode ? KEY_T : -1);
}


// new pilot name has focus, so update stats/pic to that pilot
int pilot_manage_new_pilot_selected()
{
	//char stripped[MAX_FILENAME_LEN+1] = "";

	// save the previous pilot first, so changes to it are kept
	if (strlen(Cur_pilot->callsign)) {
		write_pilot_file();
	}

	// check if we have a valid pilot hilighted.  If so, attempt to active it
	if ((Num_pilots < 1) || (Selected_line < 0) || (Selected_line >= Num_pilots)) {
		Cur_pilot->callsign[0] = 0;  // this indicates no pilot active
		return -1;
	}

	if (read_pilot_file(Pilots[Selected_line], !Player_sel_mode, Cur_pilot)) {
		Cur_pilot->callsign[0] = 0;  // this indicates no pilot active
		return -1;
	}

	return 0;
}

void pilot_manage_set_callsign_enter_mode(bool set_callsign_enter_mode)
{
	// set global mode variable
	pilot_manage_callsign_enter_mode = set_callsign_enter_mode;

	// disable/enable all buttons
	for (int idx=0; idx<PM_NUM_BUTTONS; idx++) {
		Buttons[gr_screen.res][idx].button.enable(!set_callsign_enter_mode);
	}

	// enable/disable hotkeys
	pilot_manage_set_hotkeys(!set_callsign_enter_mode);
	// disable/enable inputbox
	Inputbox.enable(set_callsign_enter_mode);
	// hide/unhide inputbox
	Inputbox.hide(!set_callsign_enter_mode);
}

// creates a new pilot file
void pilot_manage_create_new_pilot()//UI_INPUTBOX *Inputbox)
{
	// check if too many pilots
	if (Num_pilots >= MAX_PILOTS) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	// play sound for pilot creation
	gamesnd_play_iface(SND_SCROLL);
	
	// only write pilot file if there is an active pilot
	if (strlen(Player->callsign)) {
		write_pilot_file();
	}

	// move other pilot names and ranks down to make room for the new one
	int idx = Num_pilots;
	Assert(Num_pilots >= 0);
	while (idx--) {
		strcpy(Pilots[idx + 1], Pilots[idx]);
		Pilot_ranks[idx + 1] = Pilot_ranks[idx];
	}

	Selected_line = 0;
	Num_pilots++;
	Pilots[Selected_line][0] = 0;
	Pilot_ranks[Selected_line] = 0;
	List_scroll_offset = 0;

	// set mode to accept pilot name text
	pilot_manage_set_callsign_enter_mode(true);
	// set focus to input box
	Inputbox.set_focus();
	// set initial pilot name to ""
	Inputbox.set_text("");
	// reset size of input box to only 1 line
	Inputbox.update_dimensions(Pilot_manage_list_coords[gr_screen.res][PM_X_COORD], Pilot_manage_list_coords[gr_screen.res][PM_Y_COORD], Pilot_manage_list_coords[gr_screen.res][PM_W_COORD], gr_get_font_height());
	
  }

// exiting screen without canceling, so load in the new pilot selected here
int pilot_manage_pilot_accepted()
{
	char str[CALLSIGN_LEN + 1];

	// check if pilot active.  If not, don't allow accept.
	if (!Cur_pilot->callsign[0]){
		return -1;
	}

	// set his image 
	player_set_squad_bitmap(Cur_pilot, Cur_pilot->squad_filename);

//	Skill_level = get_default_skill_level();

	// MWA -- I think that we should be writing Cur_pilot here.
	//write_pilot_file(!is_pilot_multi(Cur_pilot));
	write_pilot_file( Cur_pilot );
	
	// when we store the LastPlayer key, we have to mark it as being single or multiplayer, so we know where to look for him
	// (since we could have a single and a multiplayer pilot with the same callsign)
	// we'll distinguish them by putting an M and the end of the multiplayer callsign and a P at the end of a single player
	strcpy(str, Cur_pilot->callsign);
	strcat(str, is_pilot_multi(Cur_pilot) ? NOX("M") : NOX("S"));
		
	os_config_write_string( NULL, "LastPlayer", str );
	return 0;
}

// scroll up pilot list one line
void pilot_manage_scroll_callsign_up()
{
	if (Selected_line > 0) {
		Selected_line--;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
	
	if ((Selected_line >= 0) && (Selected_line < List_scroll_offset)) {
		List_scroll_offset = Selected_line;
	}
}

// scroll down pilot list one line
void pilot_manage_scroll_callsign_down()
{
	if (Selected_line < Num_pilots - 1) {
		Selected_line++;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
	
	// num_pilots_to_fill_height is the number of pilots that can fit in given height
	int num_pilots_to_fill_height = Pilot_manage_list_coords[gr_screen.res][PM_H_COORD] / gr_get_font_height();
	if (Selected_line >= List_scroll_offset + num_pilots_to_fill_height) {
		List_scroll_offset++;
	}
}


void pilot_manage_delete_pilot()
{
	char buf[MAX_FILENAME_LEN];
	int active = 0;

	if (!Num_pilots) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	int popup_rval = popup(PF_TITLE_BIG | PF_TITLE_RED, 2, POPUP_NO, POPUP_YES, XSTR( "Warning!\n\nAre you sure you wish to delete this pilot?", 65));
	if (popup_rval != 1) {
		return;
	}

	if (!stricmp(Pilots[Selected_line], Cur_pilot->callsign)) {
		active = 1;
	}

	strcpy(buf, Pilots[Selected_line]);
	for (int i=Selected_line; i<Num_pilots-1; i++) {
		strcpy(Pilots[i], Pilots[i + 1]);
		Pilot_ranks[i] = Pilot_ranks[i + 1];
	}

	Num_pilots--;
	if (Selected_line >= Num_pilots) {
		Selected_line = Num_pilots - 1;
	}

	if (active) {
		if (Selected_line >= 0) {
			pilot_manage_new_pilot_selected();
		} else {
			Cur_pilot->callsign[0] = 0;
		}
	}

	delete_pilot_file(buf, Player_sel_mode == PLAYER_SELECT_MODE_SINGLE ? 1 : 0);
	gamesnd_play_iface(SND_USER_SELECT);
	
}

// Filter out pilots of wrong type (which shouldn't be in the directory we are checking, but just to be safe..)
int pilot_manage_pilot_filter(char *filename)
{
	int r, rank;

	r = verify_pilot_file(filename, Player_sel_mode == PLAYER_SELECT_MODE_SINGLE, &rank);
	if (rank >= Rank_pips_count)
		rank = Rank_pips_count - 1;

	if (!r) {
		Pilot_ranks[Num_pilots++] = rank;
	}

	return !r;
}


void pilot_manage_init_player_stuff(int mode)
{
	// determine if we should be looking for single or multiplayers at the outset
	Player_sel_mode = mode;
	
	// get the list of pilots based upon whether we're in single or multiplayer mode
	Num_pilots = 0;
	Get_file_list_filter = pilot_manage_pilot_filter;

	// single player specific stuff
	if (mode == PLAYER_SELECT_MODE_SINGLE) {
		Num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_SINGLE_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
	}
	// multiplayer specific stuff
	else {
		Num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_MULTI_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
	}

	int ranks[MAX_PILOTS];

	int i;
	for (i=0; i<Num_pilots; i++) {
		int j;
		for (j=0; j<Num_pilots; j++) {
			if (!strcmp(Pilots[i], Pilots_arr[j])) {
				ranks[i] = Pilot_ranks[j];
				break;
			}
		}
		Assert(j < Num_pilots);  // Pilot not found?  How is that possible?
	}

	for (i=0; i<Num_pilots; i++) {
		Pilot_ranks[i] = ranks[i];
	}

	 List_scroll_offset = 0;
	 
	Selected_line = 0;
	// select whatever pilot was highlighted before switching modes
	if (mode == PLAYER_SELECT_MODE_SINGLE && prev_single_player > -1) {
		Selected_line = prev_single_player;
	} else if (mode == PLAYER_SELECT_MODE_MULTI && prev_multi_player > -1) {
		Selected_line = prev_multi_player;
	} else {
	 // first time in select pilot from reg desk		
	for(int idx=0;idx<Num_pilots;idx++){
		if(strcmp(Player->callsign, Pilots_arr[idx])==0){
			Selected_line = idx;
			break;
		}
	} 
	}
	 
	pilot_manage_new_pilot_selected();

}

void pilot_manage_display_pilot_callsigns(int prospective_pilot)
{
	int y = 0;
	int cur_pilot_idx = List_scroll_offset;

	int multi = 0;
	if (Player_sel_mode == PLAYER_SELECT_MODE_MULTI) {
		multi = 1;
	}
	
	int font_height = gr_get_font_height();
	//cur_pilot_idx = 1;
	while (y + font_height <= Pilot_manage_list_coords[gr_screen.res][PM_H_COORD]) {
	if (cur_pilot_idx >= Num_pilots)
			break;
		
		if (!stricmp(Cur_pilot->callsign, Pilots[cur_pilot_idx]) && (is_pilot_multi(Cur_pilot) == multi)) {
			if ((cur_pilot_idx == Selected_line) || (cur_pilot_idx == prospective_pilot)) {
				gr_set_color_fast(&Color_text_active_hi);
			} else {
				gr_set_color_fast(&Color_text_active);
			}
		} else {
			if (cur_pilot_idx == Selected_line) {
				gr_set_color_fast(&Color_text_selected);
			} else if (cur_pilot_idx == prospective_pilot) {
				gr_set_color_fast(&Color_text_subselected);
			} else {
				gr_set_color_fast(&Color_text_normal);
			}
		}
		
		gr_printf(Pilot_manage_list_coords[gr_screen.res][PM_X_COORD], Pilot_manage_list_coords[gr_screen.res][PM_Y_COORD] + y, Pilots[cur_pilot_idx]);
		gr_set_bitmap(Rank_pips_bitmaps + Pilot_ranks[cur_pilot_idx]);
		gr_bitmap(Pilot_manage_list_coords[gr_screen.res][PM_X_COORD] - 34, Pilot_manage_list_coords[gr_screen.res][PM_Y_COORD] + y);
 
		y += font_height;
		cur_pilot_idx++;
	}
}

// process pilot callsign
void pilot_manage_accept_new_pilot_callsign()
{
	char buf[CALLSIGN_LEN + 1];
	char name[MAX_FILENAME_LEN];
	int i;

	int z = 0;
	Inputbox.get_text(buf);
	drop_white_space(buf);

	if (!isalpha(*buf)) {
		z = 1;
	} else {
		for (i=1; buf[i]; i++) {
			if (!isalpha(buf[i]) && !isdigit(buf[i]) && !strchr(VALID_PILOT_CHARS, buf[i])) {
				z = 1;
				return;
			}
		}
	}

	for (i=1; i<Num_pilots; i++) {
		if (!stricmp(buf, Pilots[i])) {
			z = 1;
			if (pilot_verify_overwrite() == 1) {
				strcpy(name, Pilots[Selected_line]);
				for (z=i; z<Num_pilots-1; z++) {
					strcpy(Pilots[z], Pilots[z + 1]);
					Pilot_ranks[z] = Pilot_ranks[z + 1];
				}

				Num_pilots--;
				delete_pilot_file(name, Player_sel_mode == PLAYER_SELECT_MODE_SINGLE ? 1 : 0);
				z = 0;
			}
			return;
		}
	}

	if (!*buf || (i < Num_pilots)) { // duplicate name, alert user
		z = 1;
	}

	if (z) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	strcpy(Pilots[0], buf);
	strcpy(Cur_pilot->callsign, buf);
	init_new_pilot(Cur_pilot, !Clone_flag);
	
	// again, make sure we set his flags correctly to ensure that he gets saved to the proper directory and gets
	// displayed correctly
	if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
		Cur_pilot->flags &= ~(PLAYER_FLAGS_IS_MULTI);
	} else {
		Cur_pilot->flags |= PLAYER_FLAGS_IS_MULTI;
		Cur_pilot->stats.flags |= STATS_FLAG_MULTIPLAYER;
	}

	if ( !(Game_mode & GM_STANDALONE_SERVER) ) {
		write_pilot_file(Cur_pilot);
	}

	Selected_line = 0;
	pilot_manage_new_pilot_selected();
	pilot_manage_set_callsign_enter_mode(false);
}


void pilot_manage_button_pressed(int n)
{
	switch (n) {
		//scroll pilot list up
		case PM_UP_BUTTON:
			pilot_manage_scroll_callsign_up();
			break;

		// scroll pilot list down
		case PM_DOWN_BUTTON:
			pilot_manage_scroll_callsign_down();
			break;
		
		// switch to single mode
		case PM_SINGLE_MODE_BUTTON:
			if (Player_sel_mode != PLAYER_SELECT_MODE_SINGLE) {
				gamesnd_play_iface(SND_USER_SELECT);
				// switching to multi so save multi player offset
				prev_multi_player = Selected_line;
				pilot_manage_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
			}						
			break;

		// switch to multi mode
		case PM_MULTI_MODE_BUTTON:
			if (Player_sel_mode != PLAYER_SELECT_MODE_MULTI) {
				gamesnd_play_iface(SND_USER_SELECT);
				// switching to multi so save single player offset
				prev_single_player = Selected_line;
				pilot_manage_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
			}
			break;
		
		//create new pilot
		case PM_CREATE_BUTTON:
			Clone_flag = 0;
			pilot_manage_create_new_pilot();
			break;
		
		// select pilot
		case PM_ACTIVE_BUTTON:			
			if (pilot_manage_new_pilot_selected()){
				gamesnd_play_iface(SND_GENERAL_FAIL);
				
				// throw up a popup telling the player that he should create a pilot first
				if(Player_sel_mode == PLAYER_SELECT_MODE_SINGLE){
					popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR( "You must create a single player pilot.", 66));
				} else {
					popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR( "You must create a multi player pilot.", 67));
				}
			} else {
				gamesnd_play_iface(SND_SCROLL);
			}
			break;	

		// clone pilot
		case PM_CLONE_BUTTON:
		//case B_PILOT_CLONE_BUTTON:
			if (Num_pilots < 1) {
				gamesnd_play_error_beep();
				break;
			}

			Clone_flag = 1;
			pilot_manage_create_new_pilot();
			break;

		// convert pilot single/multi
		case PM_CONVERT_BUTTON: 
		{
			char temp[256], *str;
			char old_pic[256] = "";
			char old_squad_pic[256] = "";
			char old_squad[256] = "";
			int z;

			if (!pilot_manage_new_pilot_selected()) {
				if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE)
					str = XSTR( "multiplayer", 68);
				else
					str = XSTR( "single player", 69);

				sprintf(temp, XSTR( "This will overwrite your %s pilot.  Proceed?", 70), str);
				if (!verify_pilot_file(Cur_pilot->callsign, Player_sel_mode == PLAYER_SELECT_MODE_MULTI)) {
					z = popup(0, 2, POPUP_CANCEL, POPUP_OK, temp);
					if (z != 1)
						break;
				}

				strcpy(old_pic, Cur_pilot->image_filename);
				strcpy(old_squad_pic, Cur_pilot->squad_filename);
				strcpy(old_squad, Cur_pilot->squad_name);
				init_new_pilot(Cur_pilot, 0);
				strcpy(Cur_pilot->image_filename, old_pic);
				strcpy(Cur_pilot->squad_filename, old_squad_pic);
				strcpy(Cur_pilot->squad_name, old_squad);
				if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
					Cur_pilot->flags |= PLAYER_FLAGS_IS_MULTI;
					write_pilot_file();
					pilot_manage_init_player_stuff(PLAYER_SELECT_MODE_MULTI);

				} else {
					write_pilot_file();
					pilot_manage_init_player_stuff(PLAYER_SELECT_MODE_SINGLE);
				}

				gamesnd_play_iface(SND_USER_SELECT);

			} else {
				gamesnd_play_iface(SND_GENERAL_FAIL);
			}

			break;
		}

		// delete pilot
		case PM_DELETE_BUTTON:
			pilot_manage_delete_pilot();
			break;

		// exit pilot selection
		case PM_EXIT_BUTTON:
		if (Num_pilots && !pilot_manage_pilot_accepted()) {
				gamesnd_play_iface(SND_COMMIT_PRESSED);
				gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
			} else {
				gamesnd_play_iface(SND_GENERAL_FAIL);

				// throw up a popup telling the player that he should create a pilot first
				if(Player_sel_mode == PLAYER_SELECT_MODE_SINGLE){
					popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR( "You must create a single player pilot.", 66));
				} else {
					popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR( "You must create a multi player pilot.", 67));
				}
			}
			break;
			
		case PM_TC_BUTTON:
			popup_tc();

			// want to switch it over to multiplayer pilots
			prev_single_player = Selected_line;
			pilot_manage_init_player_stuff(PLAYER_SELECT_MODE_MULTI);
		
			break;
		}

		
}

void pilot_manage_init(void)
{

	UI_WINDOW *w = &Ui_window;

	// create interface
	Ui_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);
	Ui_window.set_mask_bmap(PilotManage_bitmap_mask_fname[gr_screen.res]);

	// load background bitmap
	Background_bitmap = bm_load(PilotManage_bitmap_fname[gr_screen.res]);
	if(Background_bitmap < 0){
		// we failed to load the bitmap - this is very bad
		Int3();
	}

	for (int i=0; i<PM_NUM_BUTTONS; i++) {
		// create the object
		Buttons[gr_screen.res][i].button.create(&Ui_window, "", Buttons[gr_screen.res][i].x, Buttons[gr_screen.res][i].y, 60, 30, Buttons[gr_screen.res][i].repeat, 1);

		// set the sound to play when highlighted
		Buttons[gr_screen.res][i].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Buttons[gr_screen.res][i].button.set_bmaps(Buttons[gr_screen.res][i].filename);

		// set the hotspot
		Buttons[gr_screen.res][i].button.link_hotspot(Buttons[gr_screen.res][i].hotspot);
	}
	
	// load in help overlay bitmap	
	// needs to be fixed, taked out to get to compile
	//	help_overlay_load(PILOT_MANAGE_OVERLAY);
//	help_overlay_set_state(PILOT_MANAGE_OVERLAY,0);
	
	
	// button for selecting pilot
	List_region.create(&Ui_window, "", Pilot_manage_list_coords[gr_screen.res][PM_X_COORD], Pilot_manage_list_coords[gr_screen.res][PM_Y_COORD], Pilot_manage_list_coords[gr_screen.res][PM_W_COORD], Pilot_manage_list_coords[gr_screen.res][PM_H_COORD], 0, 1);
	List_region.hide();

	// create input box (for new pilot)
	Inputbox.create(&Ui_window, Pilot_manage_list_coords[gr_screen.res][PM_X_COORD], Pilot_manage_list_coords[gr_screen.res][PM_Y_COORD], Pilot_manage_list_coords[gr_screen.res][PM_W_COORD], CALLSIGN_LEN - 1, "", UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_LETTER_FIRST);
	Inputbox.set_valid_chars(VALID_PILOT_CHARS);
	Inputbox.disable();
	Inputbox.hide();

	Rank_pips_bitmaps = bm_load_animation("IconRankMini.ani", &Rank_pips_count);	

	pilot_manage_callsign_enter_mode = 0;
	List_scroll_offset = Pic_number = Pic_squad_number;// = Selected_line = 0;

	prev_single_player = -1;
	prev_multi_player = -1;
	
	pilot_manage_init_player_stuff(is_pilot_multi(Player));

	// enable hotkeys from start
	pilot_manage_set_callsign_enter_mode(false);
		
}

void pilot_manage_do(void)
{
	int k = Ui_window.process();
	int i;

	
	if ( k > 0 ) {
// put back in when overlay stuff is fixed
		//		if ( help_overlay_active(PILOT_MANAGE_OVERLAY) ) {
//			help_overlay_set_state(PILOT_MANAGE_OVERLAY,0);
//			k = 0;
//		}
	}

	
	switch (k)
	{
		case KEY_ESC:  // cancel only if not trying to enter a pilot name
			if (!pilot_manage_callsign_enter_mode)
				gameseq_post_event(GS_EVENT_BARRACKS_MENU);//GS_EVENT_PREVIOUS_STATE
			break;
	} // end switch
	
	int prospective_pilot = -1;
	// Entering pilot callsign
	if (pilot_manage_callsign_enter_mode) {
		// set focus to inputbox
		Inputbox.set_focus();

		switch (k) {
			case KEY_ESC:
				// cancel create pilot
				Num_pilots--;
				for (i=0; i<Num_pilots; i++) {
					strcpy(Pilots[i], Pilots[i + 1]);
					Pilot_ranks[i] = Pilot_ranks[i + 1];
				}

				pilot_manage_set_callsign_enter_mode(false);
				break;
			
					
			case KEY_ENTER: 
				pilot_manage_accept_new_pilot_callsign();
				break;
		} 
	} 

	// process buttons
		for (i=0; i<PM_NUM_BUTTONS; i++) {
			if (Buttons[gr_screen.res][i].button.pressed()) {
				pilot_manage_button_pressed(i);
			}
		}
	
	// pilot that mouse is over

// if mouse is over a pilot, find index into Pilots array
	if (List_region.is_mouse_on()) {
		int y;
		List_region.get_mouse_pos(NULL, &y);
		int pilot_index = List_scroll_offset + (y / gr_get_font_height());
		if ((pilot_index >= 0) && (pilot_index < Num_pilots)) {
			prospective_pilot = pilot_index;
		}
	}
		
	// if mouse clicked in list region, find index into Pilots array 
	if (List_region.pressed()) {
		if (prospective_pilot != -1) {
			Selected_line = prospective_pilot;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	}

	gr_reset_clip();	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0);	
	}
		
	Ui_window.draw();

	 //light up the correct mode button (single or multi)	
	if (Player_sel_mode == PLAYER_SELECT_MODE_SINGLE) {
		Buttons[gr_screen.res][PM_SINGLE_MODE_BUTTON].button.draw_forced(2);
	} else {
		Buttons[gr_screen.res][PM_MULTI_MODE_BUTTON].button.draw_forced(2);
	}	

	pilot_manage_display_pilot_callsigns(prospective_pilot);

	pilot_manage_force_button_frame();
	pilot_manage_maybe_show_button_text();

// needs to be fixed	help_overlay_maybe_blit(PILOT_MANAGE_OVERLAY);
	
	gr_flip();
}

void pilot_manage_close(void)
{
	// destroy window
	Ui_window.destroy();

	// release background bitmap
	if (Background_bitmap >= 0) {
		bm_unload(Background_bitmap);
	}

	// unload the overlay bitmap
// fix it	help_overlay_unload(PILOT_MANAGE_OVERLAY);

	game_flush();
}

void pilot_manage_force_button_frame()
{
	for (int x=0; x<PM_NUM_BUTTONS; x++) {
		if ( !Buttons[gr_screen.res][x].button.button_down()) 
			Buttons[gr_screen.res][x].button.draw_forced(1);
	}
}

void pilot_manage_maybe_show_button_text()
{
	pilot_manage_buttons *b;
	
	// skip the up/down arrows
	for (int i=0; i<PM_NUM_BUTTONS; i++) {
		b = &Buttons[gr_screen.res][i];

		if (b->button.button_hilighted()) {
			gr_set_color_fast(&Color_bright_white);
			gr_string(Pilot_manage_text[gr_screen.res][i].x, Pilot_manage_text[gr_screen.res][i].y, Pilot_manage_text[gr_screen.res][i].xstr);
		}
	}
}

// this will make a TC pilot based on his info from the database
void pilot_manage_make_tc_pilot(Idline id, char *name)
{	
	// play sound for pilot creation
	gamesnd_play_iface(SND_SCROLL);
	
	// only write pilot file if there is an active pilot
	if (strlen(Player->callsign)) {
		write_pilot_file();
	}

	int z = 0;

	for (int i=0; i<Num_pilots; i++) {
		if (!stricmp(name, Pilots[i])) {
			z = 1;
			if (pilot_verify_overwrite() == 1) {
				for (z=i; z<Num_pilots-1; z++) {
					strcpy(Pilots[z], Pilots[z + 1]);
					Pilot_ranks[z] = Pilot_ranks[z + 1];
				}

				Num_pilots--;
				delete_pilot_file(name, 0);
				z = 0;
			} else
				return;
		}
	}

	if (!*name || (i < Num_pilots)) { // duplicate name, alert user
		z = 1;
	}

	if (z) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	
		return;
	}

	// move other pilot names and ranks down to make room for the new one
	int idx = Num_pilots;
	Assert(Num_pilots >= 0);
	while (idx--) {
		strcpy(Pilots[idx + 1], Pilots[idx]);
		Pilot_ranks[idx + 1] = Pilot_ranks[idx];
	}

	Selected_line = 0;
	Num_pilots++;
	Pilots[Selected_line][0] = 0;
	Pilot_ranks[Selected_line] = 0;
	List_scroll_offset = 0;
	
	strcpy(Pilots[0], name);
	// make sure his rank pip matches his actual rank
	Pilot_ranks[0] = get_rank(id.rank);
	strcpy(Cur_pilot->callsign, name);
	init_new_pilot(Cur_pilot, !Clone_flag);

	Cur_pilot->flags |= PLAYER_FLAGS_IS_MULTI;
	Cur_pilot->stats.flags |= STATS_FLAG_MULTIPLAYER;

	Cur_pilot->stats.rank = get_rank(id.rank); 
	Cur_pilot->stats.fchg = get_fchg(id.fchg); 
	make_medals(&Cur_pilot->stats, id.medals);
	
	write_pilot_file(Cur_pilot);

	pilot_manage_new_pilot_selected();
}


