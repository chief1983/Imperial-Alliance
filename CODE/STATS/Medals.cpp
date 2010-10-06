/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/
 
/*
 * $Logfile: /Freespace2/code/Stats/Medals.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 * 
 * $Log: Medals.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:00:49  Darkhill
 * no message
 *
 * Revision 2.4  2003/03/18 10:07:06  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.3  2003/01/15 21:29:04  anonymous
 * fixed the demo compilation. Define FS2_DEMO globally to compile as a demo. Make sure warp.pof is in your data/models directory.
 *
 * Revision 2.2.2.1  2002/09/24 18:56:45  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.2  2002/08/01 01:41:10  penguin
 * The big include file move
 *
 * Revision 2.1  2002/07/07 19:56:00  penguin
 * Back-port to MSVC
 *
 * Revision 2.0  2002/06/03 04:02:29  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/15 15:06:11  mharris
 * TEMP PORT FIX: for non-Win32, ifdef out code to assign multiple
 * levels of a medal to remove _splitpath() reference.
 *
 * Revision 1.1  2002/05/02 18:03:13  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 12    10/29/99 10:40p Jefff
 * hack to make german medal names display without actually changing them
 * 
 * 11    9/02/99 3:41p Jefff
 * changed badge voice handling to be similar to promotion voice handling
 * 
 * 10    8/26/99 8:49p Jefff
 * Updated medals screen and about everything that ever touches medals in
 * one way or another.  Sheesh.
 * 
 * 9     7/16/99 1:50p Dave
 * 8 bit aabitmaps. yay.
 * 
 * 8     3/19/99 9:51a Dave
 * Checkin to repair massive source safe crash. Also added support for
 * pof-style nebulae, and some new weapons code.
 * 
 * 8     3/15/99 10:29a Neilk
 * 
 * 7     1/30/99 5:08p Dave
 * More new hi-res stuff.Support for nice D3D textures.
 * 
 * 6     12/18/98 1:13a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 5     11/30/98 1:07p Dave
 * 16 bit conversion, first run.
 * 
 * 4     10/23/98 3:51p Dave
 * Full support for tstrings.tbl and foreign languages. All that remains
 * is to make it active in Fred.
 * 
 * 3     10/13/98 9:29a Dave
 * Started neatening up freespace.h. Many variables renamed and
 * reorganized. Added AlphaColors.[h,cpp]
 * 
 * 2     10/07/98 10:54a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 26    6/13/98 3:18p Hoffoss
 * NOX()ed out a bunch of strings that shouldn't be translated.
 * 
 * 25    6/01/98 11:43a John
 * JAS & MK:  Classified all strings for localization.
 * 
 * 24    5/01/98 12:34p John
 * Added code to force FreeSpace to run in the same dir as exe and made
 * all the parse error messages a little nicer.
 * 
 * 23    4/27/98 3:13p Allender
 * make ctrl-enter work on medals screen
 * 
 * 22    4/23/98 8:27p Allender
 * basic support for cutscene playback.  Into movie code in place.  Tech
 * room can view cutscenes stored in CDROM_dir variable
 * 
 * 21    4/12/98 8:30p Allender
 * minor medal changes to show number of medals if > 1
 * 
 * 20    4/10/98 4:51p Hoffoss
 * Made several changes related to tooltips.
 * 
 * 19    3/18/98 12:03p John
 * Marked all the new strings as externalized or not.
 * 
 * 18    3/11/98 5:02p Dave
 * Put in code to support new medals artwork. Assorted multiplayer bug
 * fixes.
 * 
 * 17    3/07/98 5:44p Dave
 * Finished player info popup. Ironed out a few todo bugs.
 * 
 * 16    3/05/98 5:11p Allender
 * fix up medals screen (again).  Don't do state transition when viewing
 * medals from debriefing screen.
 * 
 * 15    3/05/98 2:32p Hoffoss
 * Renamed Rank_bitmap to Rank_bm so it isn't named the same as the
 * variable in the debrief screen which confuses the debugger.
 * 
 * 14    2/22/98 2:48p John
 * More String Externalization Classification
 * 
 * 13    2/09/98 5:21p Hoffoss
 * Made exit from medals screen to previous screen (instead of assuming
 * it's the barracks) work.
 * 
 * 12    1/27/98 4:23p Allender
 * enhanced internal scoring mechanisms.
 * 
 * 11    11/12/97 4:40p Dave
 * Put in multiplayer campaign support parsing, loading and saving. Made
 * command-line variables better named. Changed some things on the initial
 * pilot select screen.
 * 
 * 10    11/12/97 9:30a Dave
 * Fixed rank insignia tooltip not showing up.
 * 
 * 9     11/06/97 4:39p Allender
 * a ton of medal work.  Removed an uneeded elemen in the scoring
 * structure.  Fix up medals screen to apprioriate display medals (after
 * mask was changed).  Fix Fred to only display medals which may actually
 * be granted.  Added image_filename to player struct for Jason Hoffoss
 * 
 * 8     11/05/97 4:43p Allender
 * reworked medal/rank system to read all data from tables.  Made Fred
 * read medals.tbl.  Changed ai-warp to ai-warp-out which doesn't require
 * waypoint for activation
 *
 * $NoKeywords: $
 */


#include "stats/medals.h"
#include "graphics/2d.h"
#include "menuui/snazzyui.h"
#include "bmpman/bmpman.h"
#include "gamesequence/gamesequence.h"
#include "anim/animplay.h"
#include "io/mouse.h"
#include "freespace2/freespace.h"
#include "stats/scoring.h"
#include "playerman/player.h"
#include "palman/palman.h"
#include "ui/ui.h"
#include "io/key.h"
#include "cmdline/cmdline.h"
#include "gamesnd/gamesnd.h"
#include "globalincs/alphacolors.h"
#include "localization/localize.h"
#include "debugconsole/dbugfile.h"
#include "parse/parselo.h"

//#define MAX_MEDAL_TYPES 63 // the # of medals which exist so far

/*
#define CALLSIGN_X 198
#define CALLSIGN_Y 80
#define CALLSIGN_W (439-CALLSIGN_X)
#define CALLSIGN_H (116-CALLSIGN_Y)
*/

void medal_display_force_button_frame();
void medal_display_maybe_show_button_text();

// define for the medal information
medal_stuff Medals[NUM_MEDALS];
badge_stuff Badge_info[MAX_BADGES];

// holds indices into Medals array of the badges for # kills
int Badge_index[MAX_BADGES];

// the rank section of the screen
#define RANK_MEDAL_REGION		12			// region number of the rank medal
#define BADGE_REGION			14			// number of badge area
#define FCHG_REGION				17			// number for fchg area

// coords for indiv medal bitmaps
int Medal_coords[GR_NUM_RESOLUTIONS][NUM_MEDALS][2] = {
	{				// GR_640
		{ 257,214 },				// Distinguished Flying Cross
		{ 266,194 },				// Legion of Combat
		{ 248,194 },				// Iron Star
		{ 275,174 },				// Imperial Security Medal
		{ 257,174 },				// Palpatine Crescent
		{ 239,174 },				// Bronze Star of the Empire
		{ 284,154 },				// Silver Star of the Empire
		{ 266,154 },				// Gold Star of the Empire
		{ 165, 60 },				// Grand Order of the Emperor
		{ 248,154 },				// Order of the Renegade
		{ 165, 60 },				// Imperial Cross
		{ 230,154 },				// Medal of Honor
		{ 245, 105 },				// rank
		{ 99, 121 },				// wings
		{ 166, 45 },				// ace kills badge
		{ 166, 45 },				// top ace kills badge
		{ 166, 45 },				// jedi kills badge
	},
	{				// GR_1024
		{ 143, 75 },				
		{ 777, 75 },				
		{ 206, 208 },				
		{ 333, 212 },				
		{ 578, 210 },				
		{ 703, 208 },				
		{ 103, 374 },				
		{ 245, 374 },				
		{ 383, 386 },			
		{ 522, 384 },				
		{ 658, 374 },				
		{ 790, 374 },				
		{ 302, 128 },			
		{ 453, 146 },				
		{ 595, 121 },			
		{ 646, 121 },				
		{ 696, 121 },				
	}
};

// coords for the medal title
static int Medals_label_coords[GR_NUM_RESOLUTIONS][3] = {
	{ 241, 458, 300 },			// GR_640 x, y, w
	{ 386, 734, 480 }				// GR_1024 x, y, w
};

int Fchg_coords[GR_NUM_RESOLUTIONS][2] = {
	// GR_640
	{ 119, 141 },
	{ 480, 244 }
};

#define MEDALS_NUM_BUTTONS			1
#define MEDALS_EXIT					0	
ui_button_info Medals_buttons[GR_NUM_RESOLUTIONS][MEDALS_NUM_BUTTONS] = {
	{ // GR_640
		ui_button_info("MEB_18",	540,  425,	-1,	-1,	18),
	},
	{ // GR_1024
		ui_button_info("2_MEB_18",	919,	691,	-1,	-1,	18),
	}
};

#define MEDALS_NUM_TEXT				1
UI_XSTR Medals_text[GR_NUM_RESOLUTIONS][MEDALS_NUM_TEXT] = {
	{	// GR_640
		//***************fix!!!!!!!!!!!!!!!11***************
		{"Exit",		1059,		552,  446,	UI_XSTR_COLOR_PINK, -1,	&Medals_buttons[GR_640][MEDALS_EXIT].button },
	},
	{	// GR_1024
		{"Exit",		1059,		943,	673,	UI_XSTR_COLOR_PINK, -1,	&Medals_buttons[GR_1024][MEDALS_EXIT].button },
	},
};

static char* Medals_background_filename[GR_NUM_RESOLUTIONS] = {
	"MedalsDisplayEmpty",
	"2_MedalsDisplayEmpty"
};

static char* Medals_mask_filename[GR_NUM_RESOLUTIONS] = {
	"Medals-m",
	"2_Medals-m"
};

static int Medals_callsign_y[GR_NUM_RESOLUTIONS] = {
	54, 89
};

scoring_struct *Player_score=NULL;

int Medals_mode;
player *Medals_player;

// -----------------------------------------------------------------------------
// Main medals screen state
//
#define NUM_MEDAL_REGIONS			NUM_MEDALS + 2				// the extra one is for the rank medal
																// other one is for fchg rank
static bitmap *Medals_mask;
int Medals_mask_w, Medals_mask_h;
static int Medal_palette;              // Medal palette bitmap
static int Medals_bitmap_mask;         // the mask for the medal case
static int Medals_bitmap;              // the medal case itself
static int Medal_bitmaps[NUM_MEDALS];  // bitmaps for the individual medals
static int Rank_bm;							// bitmap for the rank medal
static int Fchg_bitmaps[NUM_FCHG_RANKS];

static MENU_REGION Medal_regions[NUM_MEDAL_REGIONS]; // a semi-hack for now because we only have 4 medals, but we also include the close button

static UI_WINDOW Medals_window;

//#define MAX_MEDALS_BUTTONS						1
//#define MEDAL_BUTTON_EXIT						0
//static UI_BUTTON Medal_buttons[MAX_MEDALS_BUTTONS];

/*static char *Medal_button_names[MAX_MEDALS_BUTTONS] = {
//XSTR:OFF
	"MX_17"
//XSTR:ON
};
*/
/*
static int Medal_button_coords[MAX_MEDALS_BUTTONS][2] = {
	{561,411}
};
static int Medal_button_masks[MAX_MEDALS_BUTTONS] = {
	17
};
*/


#define MEDAL_BITMAP_INIT (1<<0)
#define MASK_BITMAP_INIT  (1<<1)
int Init_flags;

void parse_medal_tbl()
{
	int rval, num_medals, i, bi;

	if ((rval = setjmp(parse_abort)) != 0) {
		Error(LOCATION, "Error parsing 'medals.tbl'\r\nError code = %i.\r\n", rval);
	} 

	// open localization
	lcl_ext_open();

	read_file_text("medals.tbl");

	reset_parse();

	// parse in all the rank names
	num_medals = 0;
	bi = 0;
	required_string("#Medals");
	//while (required_string("$Name:")) {
		while ( required_string_either("#End", "$Name:") ) {
		Assert ( num_medals < NUM_MEDALS);
		required_string("$Name:");
		stuff_string( Medals[num_medals].name, F_NAME, NULL );
		required_string("$Bitmap:");
		stuff_string( Medals[num_medals].bitmap, F_NAME, NULL );
		required_string("$Num mods:");
		stuff_int( &Medals[num_medals].num_versions);

		// some medals are based on kill counts.  When string +Num Kills: is present, we know that
		// this medal is a badge and should be treated specially
		Medals[num_medals].kills_needed = 0;
		if ( optional_string("+Num Kills:") ) {
			char buf[MULTITEXT_LENGTH + 1];

			Assert( bi < MAX_BADGES );
			stuff_int( &Medals[num_medals].kills_needed );
			Badge_index[bi] = num_medals;

			required_string("$Wavefile Base:");
			stuff_string(Badge_info[bi].voice_base, F_NAME, NULL, MAX_FILENAME_LEN);

			required_string("$Promotion Text:");
			stuff_string(buf, F_MULTITEXT, NULL);
			Badge_info[bi].promotion_text = strdup(buf);

			bi++;
		}

		num_medals++;
	}

	required_string("#End");
	//Assert( num_medals == NUM_MEDALS );

	// be sure that the badges kill numbers show up in order
	for (i = 0; i < MAX_BADGES-1; i++ ) {
		if ( Medals[Badge_index[i]].kills_needed >= Medals[Badge_index[i+1]].kills_needed ){
			Error(LOCATION, "Badges must appear sorted by lowest kill # first in medals.tbl\nFind Allender for most information.");
		}
	}

	// close localization
	lcl_ext_close();
}

void medal_main_init(player *pl, int mode)
{
	int idx;
	
	Assert(pl != NULL);
	Medals_player = pl;
    		
	Player_score = &Medals_player->stats;

	Medals_mode = mode;

	snazzy_menu_init();
	Medals_window.create( 0, 0, gr_screen.max_w, gr_screen.max_h, 0 );	

	// create the interface buttons
	for (idx=0; idx<MEDALS_NUM_BUTTONS; idx++) {
		// create the object
		Medals_buttons[gr_screen.res][idx].button.create(&Medals_window, "", Medals_buttons[gr_screen.res][idx].x, Medals_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);

		// set the sound to play when highlighted
		Medals_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Medals_buttons[gr_screen.res][idx].button.set_bmaps(Medals_buttons[gr_screen.res][idx].filename);

		// set the hotspot
		Medals_buttons[gr_screen.res][idx].button.link_hotspot(Medals_buttons[gr_screen.res][idx].hotspot);
	}	

	// add all xstrs
	//for (idx=0; idx<MEDALS_NUM_TEXT; idx++) {
	//	Medals_window.add_XSTR(&Medals_text[gr_screen.res][idx]);
	//}


	Init_flags = 0;	

	//init_medal_palette();
	
	Medals_bitmap = bm_load(Medals_background_filename[gr_screen.res]);
	if (Medals_bitmap < 0) {
	   Error(LOCATION, "Error loading medal background bitmap %s", Medals_background_filename[gr_screen.res]);
	} else {
		Init_flags |= MEDAL_BITMAP_INIT;
	}

	Medals_mask_w = -1;
	Medals_mask_h = -1;
      
	Medals_bitmap_mask = bm_load(Medals_mask_filename[gr_screen.res]);
	if(Medals_bitmap_mask < 0){
		Error(LOCATION, "Error loading medal mask file %s", Medals_mask_filename[gr_screen.res]);
	} else {
		Init_flags |= MASK_BITMAP_INIT;
		Medals_mask = bm_lock(Medals_bitmap_mask, 8, BMP_AABITMAP);
		bm_get_info(Medals_bitmap_mask, &Medals_mask_w, &Medals_mask_h);
	}
	init_medal_bitmaps();
	init_fchg_bitmaps();
	init_snazzy_regions();

	gr_set_color_fast(&Color_normal);

	Medals_window.set_mask_bmap(Medals_mask_filename[gr_screen.res]);
}


void blit_label(char *label, int *coords, int num)
{
	int x, y, sw;
	char text[256];

	gr_set_color_fast(&Color_bright);
	if (num >= 12)
		return;
	
	// set correct string
	if ( num > 1 ) {
		sprintf( text, NOX("%s (%d)"), label, num );
	} else {
		sprintf( text, "%s", label );
	}	
	
	// find correct coords
	gr_get_string_size(&sw, NULL, text);
	x = Medals_label_coords[gr_screen.res][0] + (Medals_label_coords[gr_screen.res][2] - sw) / 2;
	y = Medals_label_coords[gr_screen.res][1];

	// do it
	gr_string(x, y, text);
}

void blit_callsign()
{
	gr_set_color_fast(&Color_normal);

	// nothing special, just do it.
	gr_string(0x8000, Medals_callsign_y[gr_screen.res], Medals_player->callsign);
}

void blit_quote()
{
	gr_set_color_fast(&Color_bright_white);

//	gr_string(45, 395, Medals_player->quote);
}

int medal_main_do()
{
   int region,selected, k;
   int badge;
  
	k = Medals_window.process();	

	// process an exit command
	if ((k == KEY_ESC) && (Medals_mode == MM_NORMAL)) {
		gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
	}

	// draw the background medal display case
	gr_reset_clip();
	GR_MAYBE_CLEAR_RES(Medals_bitmap);
	if(Medals_bitmap != -1){
		gr_set_bitmap(Medals_bitmap);
		gr_bitmap(0,0);
	}

	// check to see if a button was pressed
	if( (k == (KEY_CTRLED|KEY_ENTER)) || (Medals_buttons[gr_screen.res][MEDALS_EXIT].button.pressed()) ) {	
		gamesnd_play_iface(SND_COMMIT_PRESSED);
		if(Medals_mode == MM_NORMAL){
			gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
		} else {
			// any calling popup function will know to close the screen down
			return 0;
		}		
	}

	// blit medals also takes care of blitting the rank insignia
	blit_medals(); 
	blit_fchg();
	//blit_callsign();
	//if (Medals_player->tc_pilot)
		blit_quote();
	
	region = snazzy_menu_do((ubyte*)Medals_mask->data, Medals_mask_w, Medals_mask_h, NUM_MEDAL_REGIONS, Medal_regions, &selected);
	switch (region) {
		case ESC_PRESSED:
			if (Medals_mode == MM_NORMAL) {
				gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
			} else {
				// any calling popup function will know to close the screen down
				return 0;
			}
			break;

		case RANK_MEDAL_REGION :
			blit_label(Ranks[Player_score->rank].name, &Medal_coords[gr_screen.res][region][0], 1);
			break;

		
		case BADGE_REGION:
			// go through section and see if the player has any of them
			for (badge=0; badge<=MAX_BADGES; badge++) {
				if (Medals_player->stats.medals[Badge_index[badge]] == 0) {
					// we don't have this badge so go back to the last one
					badge--;
					break;
				}
			}
			
			if (badge >= 0)
				blit_label(Medals[Badge_index[badge]].name, &Medal_coords[gr_screen.res][region][0], Player_score->medals[region]);
		
			break;

		case FCHG_REGION:
			if (Player_score->fchg > 0)
				blit_label(FCHG[Player_score->fchg].name, &Fchg_coords[gr_screen.res][0], 0);
			break;
		case -1:
			break;

		default :
      	if (Player_score->medals[region] > 0){
				blit_label(Medals[region].name, &Medal_coords[gr_screen.res][region][0], Player_score->medals[region] );
			}
			break;
	} // end switch

	Medals_window.draw();

	medal_display_force_button_frame();
	
	medal_display_maybe_show_button_text();

	
	gr_flip();

	return 1;
}

void medal_main_close()
{
	int idx;
	if (Init_flags & MEDAL_BITMAP_INIT)
		bm_unload(Medals_bitmap);

	if (Init_flags & MASK_BITMAP_INIT) {
		bm_unlock(Medals_bitmap_mask);
		bm_unload(Medals_bitmap_mask);
	}

   for (idx=0; idx < NUM_MEDALS; idx++) {
		if (Medal_bitmaps[idx] > -1){
			bm_unload(Medal_bitmaps[idx]);
		}
	}

   for (idx=0; idx<NUM_FCHG_RANKS; idx++) {
	   if (Fchg_bitmaps[idx] > -1)
		   bm_unload(Fchg_bitmaps[idx]);
   }

   Player_score = NULL;
	Medals_window.destroy();
	snazzy_menu_close();
	palette_restore_palette();
}

/*
void init_medal_palette()
{
	Medal_palette = bm_load("MedalsPalette.pcx");
	if(Medal_palette > -1){
#ifndef HARDWARE_ONLY
		palette_use_bm_palette(Medal_palette);
#endif
	}
}
*/

// function to load in the medals for this player.  It loads medals that the player has (known
// by whether or not a non-zero number is present in the player's medal array), then loads the
// rank bitmap

void init_medal_bitmaps()
{
	int idx;
	Assert(Player_score);

	for (idx=0; idx<NUM_MEDALS; idx++) {
		Medal_bitmaps[idx] = -1;
		if (Player_score->medals[idx] > 0) {
			int num_medals;
			char filename[NAME_LENGTH], base[NAME_LENGTH];
			
			// possibly load a different filename that is specified by the bitmap filename
			// for this medal.  if the player has > 1 of these types of medals, then determien
			// which of the possible version to use based on the player's count of this medal
			strcpy( filename, Medals[idx].bitmap );
#ifdef _WIN32
			_splitpath( filename, NULL, NULL, base, NULL );

			num_medals = Player_score->medals[idx];

			// can't display more than the maximum number of version for this medal
			if ( num_medals > Medals[idx].num_versions )
				num_medals = Medals[idx].num_versions;

			if ( num_medals > 1 ) {
				// append the proper character onto the end of the medal filename.  Base version
				// has no character. next version is a, then b, etc.
				sprintf( base, "%s%c", base, (num_medals-2)+'a');
			}
#else
			// mharris FIXME
			// quick hack for unix - no levels of medals
			strcpy(base, filename);
#endif

			// hi-res support
			if (gr_screen.res == GR_1024) {
				sprintf( filename, "2_%s", base );
			}

			// base now contains the actual medal bitmap filename needed to load
			// we don't need to pass extension to bm_load anymore, so just use the basename
			// as is.
         Medal_bitmaps[idx] = bm_load( filename );
			Assert( Medal_bitmaps[idx] != -1 );
		}
	}

	// load up rank insignia
	if (gr_screen.res == GR_1024) {
		char filename[NAME_LENGTH];
		sprintf(filename, "2_%s", Ranks[Player_score->rank].bitmap);
		Rank_bm = bm_load(filename);
	} else {
		
		Rank_bm = bm_load(Ranks[Player_score->rank].bitmap);
	}
}

void init_fchg_bitmaps()
{
	int idx;
	char filename[NAME_LENGTH];

	for (idx=0; idx<NUM_FCHG_RANKS; idx++) {
		Fchg_bitmaps[idx] = -1;
		
		if (gr_screen.res == GR_1024) {
			sprintf(filename, "%s", FCHG[idx].bitmap);
			Fchg_bitmaps[idx] = bm_load(filename);
		}
		
		Fchg_bitmaps[idx] = bm_load(FCHG[idx].bitmap);
	}
}

void init_snazzy_regions()
{
	int idx;

	// snazzy regions for the medals/ranks, etc.
	// add one since fchg hotspot isn't part of the medals
	for (idx=0; idx<NUM_MEDALS+1; idx++) {
		if (idx == RANK_MEDAL_REGION) 
			continue;

		snazzy_menu_add_region(&Medal_regions[idx], "", idx, 0);
	}

	// add the rank medal region
	snazzy_menu_add_region(&Medal_regions[RANK_MEDAL_REGION], "", RANK_MEDAL_REGION,0);
}


// blit the medals -- this includes the rank insignia
void blit_medals()
{
	int idx;

	for (idx=0; idx<NUM_MEDALS; idx++) {
		if (Player_score->medals[idx] > 0) {
			gr_set_bitmap(Medal_bitmaps[idx]);
			gr_bitmap(Medal_coords[gr_screen.res][idx][0], Medal_coords[gr_screen.res][idx][1]);
		}
	}

	// now blit rank, since that "medal" doesnt get loaded (or drawn) the normal way
	gr_set_bitmap(Rank_bm);
	gr_bitmap(Medal_coords[gr_screen.res][RANK_MEDAL_REGION][0], Medal_coords[gr_screen.res][RANK_MEDAL_REGION][1]);
}

// show whatever fchg rank pilot has
void blit_fchg()
{
	if (Player_score->fchg > 0) {
		gr_set_bitmap(Fchg_bitmaps[Player_score->fchg]);
	
		gr_bitmap(Fchg_coords[gr_screen.res][0], Fchg_coords[gr_screen.res][1]);
	}
}

void medal_display_force_button_frame()
{
	//for (int x=0; x<NUM_BUTTONS; x++) {
		if ( !Medals_buttons[gr_screen.res][0].button.button_down()) 
			Medals_buttons[gr_screen.res][0].button.draw_forced(1);
	//}
}

void medal_display_maybe_show_button_text()
{
	ui_button_info *b;
	
	for (int i=0; i<2; i++) {
		b = &Medals_buttons[gr_screen.res][i];

		if (b->button.button_hilighted()) {
			gr_set_color_fast(&Color_bright_white);
			gr_string(Medals_text[gr_screen.res][i].x, Medals_text[gr_screen.res][i].y, Medals_text[gr_screen.res][i].xstr);
		}
	}
}

