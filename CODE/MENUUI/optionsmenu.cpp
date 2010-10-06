/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/OptionsMenu.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:41 $
 * $Author: Spearhawk $
 *
 * C module that contains functions to drive the Options user interface
 *
 * $Log: optionsmenu.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:46:24  Darkhill
 * no message
 *
 * Revision 2.4  2004/02/14 00:18:33  randomtiger
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
 * Revision 2.3  2003/10/16 17:36:29  randomtiger
 * D3D now has its own gamma system (stored in GammaD3D reg entry) that effects everything.
 * Put in Bobs specular fog fix.
 *
 * Revision 2.2  2003/03/18 10:07:03  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.1.2.1  2002/09/24 18:56:43  randomtiger
 * DX8 branch commit
 *
 * This is the scub of UP's previous code with the more up to date RT code.
 * For full details check previous dev e-mails
 *
 * Revision 2.1  2002/08/01 01:41:06  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.7  2002/05/17 03:05:08  mharris
 * more porting tweaks
 *
 * Revision 1.6  2002/05/16 06:06:23  mharris
 * ifndef NO_JOYSTICK
 *
 * Revision 1.5  2002/05/14 21:56:40  mharris
 * added more ifndef NO_SOUND
 *
 * Revision 1.4  2002/05/13 15:11:03  mharris
 * More NO_NETWORK ifndefs added
 *
 * Revision 1.3  2002/05/10 06:08:08  mharris
 * Porting... added ifndef NO_SOUND
 *
 * Revision 1.2  2002/05/07 02:58:44  mharris
 * make Buttons[] static
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 31    10/25/99 5:47p Jefff
 * reassigned some xstr ids
 * 
 * 30    10/14/99 2:50p Jefff
 * localization fixes
 * 
 * 29    9/13/99 6:07p Jefff
 * took out audiostream pausing to allow for correct volume adjustments
 * 
 * 28    9/09/99 2:28p Jefff
 * some detail slider #defines were switched around
 * 
 * 27    9/08/99 2:38p Jefff
 * sound pausing going to menu from game
 * 
 * 26    8/05/99 3:40p Jefff
 * hi-res text adjustments
 * 
 * 25    8/04/99 4:06p Jefff
 * fixed volume sliders blacking out at master volume of 1.0
 * 
 * 24    8/02/99 6:05p Jefff
 * failure sound on skill slider when disabled in game
 * 
 * 23    7/19/99 3:29p Dave
 * Fixed gamma bitmap in the options screen.
 * 
 * 22    7/19/99 2:13p Dave
 * Added some new strings for Heiko.
 * 
 * 21    7/18/99 9:54p Andsager
 * Demo build clean up
 * 
 * 20    7/15/99 7:15p Jefff
 * Added sounds for skill select
 * 
 * 19    7/15/99 4:10p Andsager
 * Disable control_config hud_config in FS2_DEMO
 * 
 * 18    7/15/99 9:20a Andsager
 * FS2_DEMO initial checkin
 * 
 * 17    7/13/99 1:15p Dave
 * 32 bit support. Whee!
 * 
 * 16    7/09/99 5:54p Dave
 * Seperated cruiser types into individual types. Added tons of new
 * briefing icons. Campaign screen.
 * 
 * 15    6/25/99 11:59a Dave
 * Multi options screen.
 * 
 * 14    6/24/99 12:34a Dave
 * Main options screen.
 * 
 * 13    6/22/99 7:03p Dave
 * New detail options screen.
 * 
 * 12    6/16/99 4:06p Dave
 * New pilot info popup. Added new draw-bitmap-as-poly function.
 * 
 * 11    5/24/99 5:45p Dave
 * Added detail levels to the nebula, with a decent speedup. Split nebula
 * lightning into its own section.
 * 
 * 10    4/02/99 4:44p Jasenw
 * 
 * 9     2/05/99 7:22p Neilk
 * Fixed gamma bitmap and converted coordinates for multiple resolutions
 * 
 * 8     1/30/99 5:08p Dave
 * More new hi-res stuff.Support for nice D3D textures.
 * 
 * 7     12/18/98 1:13a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 6     11/30/98 1:07p Dave
 * 16 bit conversion, first run.
 * 
 * 5     11/05/98 5:55p Dave
 * Big pass at reducing #includes
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
 * 123   6/12/98 7:13p Hoffoss
 * Fixed options screen problem where it wasn't showing tooltips.
 * 
 * 122   6/12/98 4:52p Hoffoss
 * Added support for special characters in in forgeign languages.
 * 
 * 121   6/09/98 10:31a Hoffoss
 * Created index numbers for all xstr() references.  Any new xstr() stuff
 * added from here on out should be added to the end if the list.  The
 * current list count can be found in FreeSpace.cpp (search for
 * XSTR_SIZE).
 * 
 * 120   6/05/98 9:50a Lawrance
 * OEM changes
 * 
 * 119   6/01/98 11:43a John
 * JAS & MK:  Classified all strings for localization.
 * 
 * 118   5/24/98 4:42p Dan
 * AL: Fix several bugs related to pausing and enabling/disabling event
 * music
 * 
 * 117   5/20/98 5:18p John
 * Made the gamma box draw as a bitmap, not a bunch of pixels.  Speeds up
 * the menu dramatically.
 * 
 * 116   5/19/98 1:21p Duncan
 * Use 'InterfacePalette' instad of 'OptionsMainPalette'
 * 
 * 115   5/18/98 9:14p Dave
 * Put in network config files support.
 * 
 * 114   5/18/98 5:16p Hoffoss
 * Changed code to use new palette Jasen told me to use.
 * 
 * 113   5/16/98 3:40p Lawrance
 * Don't restore the original details unless they've been stored!
 * 
 * 112   5/13/98 10:03a Mitri
 * AL: Fix some bugs as a result of recent rearranging of code
 * 
 * 111   5/13/98 12:24a Lawrance
 * Only load required bitmaps and masks for the options screen
 * 
 * 110   5/08/98 3:52p Hoffoss
 * Fixed placement of gamma graphic.
 * 
 * 109   5/07/98 12:41p Hoffoss
 * Added joystick deadzone slider support and mouse on/off support.
 * 
 * 108   5/06/98 8:06p Dave
 * Made standalone reset properly under weird conditions. Tweak
 * optionsmulti screen. Upped MAX_WEAPONS to 350. Put in new launch
 * countdown anim. Minro ui fixes/tweaks.
 * 
 * 107   5/05/98 8:38p Hoffoss
 * Added sensitivity adjustment to options menu and made it save to pilot
 * file.
 * 
 * 106   4/27/98 9:00a Jasen
 * Updated coords for button change.
 * 
 * 105   4/25/98 3:33p Allender
 * do exit confirmation
 * 
 * 104   4/22/98 12:34a Dave
 * Make sure hud config and control config buttons draw properly in all
 * tab modes. Make small tab buttons light up correctly in multi options
 * screen.
 * 
 * 103   4/21/98 12:14a Allender
 * disable skill level buttons for multiplayer games
 * 
 * 102   4/20/98 6:04p Dave
 * Implement multidata cache flushing and xferring mission files to
 * multidata. Make sure observers can't change hud config. Fix pilot image
 * viewing in popup. Put in game status field. Tweaked multi options. 
 * 
 * 101   4/18/98 12:45p Dave
 * Aesthetic changes to multi options screen. Put in missing exit button.
 * oops.
 * 
 * 100   4/17/98 5:27p Dave
 * More work on the multi options screen. Fixed many minor ui todo bugs.
 *  
 *
 * $NoKeywords: $
 *
*/

#include "graphics/grinternal.h"
#include "ui/ui.h"
#include "missionui/missionscreencommon.h"
#include "bmpman/bmpman.h"
#include "gamesequence/gamesequence.h"
#include "io/key.h"
#include "playerman/managepilot.h"
#include "freespace2/freespace.h"
#include "gamesnd/gamesnd.h"
#include "sound/sound.h"
#include "gamesnd/eventmusic.h"
#include "menuui/mainhallmenu.h"
#include "sound/audiostr.h"
#include "network/psnet.h"
#include "popup/popup.h"
#include "popup/popupdead.h"
#include "mission/missionbriefcommon.h"
#include "menuui/optionsmenu.h"
#include "io/joy.h"
#include "io/mouse.h"
#include "osapi/osregistry.h"
#include "globalincs/alphacolors.h"
#include "io/timer.h"
#include "nebula/neb.h"
#include "weapon/beam.h"
#include "debugconsole/dbugfile.h"

#ifndef NO_NETWORK
#include "network/multi.h"
#include "menuui/optionsmenumulti.h"
#endif

// hacky hack to make sure current tab is highlighted in red
int current_tab = 0;

// hotspot stuff.....
static UI_BUTTON Hotspot_region;

#define NUM_HOTSPOT_AREAS		6

#define HOTSPOT_MASK_X1			0
#define HOTSPOT_MASK_Y1			1
#define HOTSPOT_MASK_X2			2
#define HOTSPOT_MASK_Y2			3

static int Option_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		45,	375, 95, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Multi_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		100,375, 150, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Detail_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		155,375, 205, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Quit_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		485,375, 535, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Control_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		210,375, 260, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Hud_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		265,375, 315, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Accept_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		540,375, 590, 425
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

// will display a notification warning message
#define OPTIONS_NOTIFY_TIME			3500
#define OPTIONS_NOTIFY_Y            450

#define NUM_BUTTONS	24
#define NUM_ANIS		4
#define NUM_TABS		3
#define NUM_COMMONS	10

#define TABLESS							999

#define OPTIONS_TAB						0
#define MULTIPLAYER_TAB					1
#define DETAIL_LEVELS_TAB 				2
#define ABORT_GAME_BUTTON				3
#define CONTROL_CONFIG_BUTTON			4
#define HUD_CONFIG_BUTTON				5
#define ACCEPT_BUTTON					6

#define BRIEF_VOICE_OFF					7
#define BRIEF_VOICE_ON					8
#define MOUSE_OFF							9
#define MOUSE_ON							10
#define GAMMA_DOWN						11
#define GAMMA_UP							12

// detail level screen buttons
#define PLANETS_ON						13
#define PLANETS_OFF						14
#define HUD_TARGETVIEW_RENDER_ON		15
#define HUD_TARGETVIEW_RENDER_OFF	16
#define WEAPON_EXTRAS_ON				17
#define WEAPON_EXTRAS_OFF				18

#define LOW_DETAIL_N						19
#define MEDIUM_DETAIL_N					20
#define HIGH_DETAIL_N					21
#define VERY_HIGH_DETAIL_N				22
#define CUSTOM_DETAIL_N					23

#define REPEAT						(1<<0)
#define NO_MOUSE_OVER_SOUND	(1<<1)

// indicies for options coordinates
#define OPTIONS_X_COORD 0
#define OPTIONS_Y_COORD 1
#define OPTIONS_W_COORD 2
#define OPTIONS_H_COORD 3

struct options_buttons {
	char *filename;
	int x, y;
	int hotspot;
	int tab;
	int flags;
	UI_BUTTON button;  // because we have a class inside this struct, we need the constructor below..

	options_buttons(char *name, int x1, int y1, int h, int t, int f = 0) : filename(name), x(x1), y(y1), hotspot(h), tab(t), flags(f) {}
};

static options_buttons Buttons[GR_NUM_RESOLUTIONS][NUM_BUTTONS] = {
	{	// GR_640
		options_buttons("OPT_00",	45,		375,	0,		-1),							// options tab
		options_buttons("OPT_01",	100,	375,	1,		-1),							// multiplayer tab
		options_buttons("OPT_02",	155,	375,	2,		-1),							// detail levels tab
		options_buttons("OPT_03",	485,	375,	3,		-1),							// abort game button
		options_buttons("OPT_04",	210,	375,	4,		-1),							// control config button
		options_buttons("OPT_05",	265,	375,	5,		-1),							// hud config
		options_buttons("OPT_06",	540,	375,	6,		-1),							// accept button				

		options_buttons("OMB_07",	95,		65,		7,		OPTIONS_TAB, 2),			// Briefing / debriefing voice toggle off
		options_buttons("OMB_08",	157,	65,		8,		OPTIONS_TAB, 2),			// Briefing / debriefing voice toggle on
		options_buttons("OMB_18",	95,		257,	18,	OPTIONS_TAB, 2),			// Mouse off
		options_buttons("OMB_19",	157,	257,	19,	OPTIONS_TAB, 2),			// Mouse on
		options_buttons("OMB_26",	535,	139,	26,	OPTIONS_TAB, 1),			// Gamma Down
		options_buttons("OMB_27",	560,	139,	27,	OPTIONS_TAB, 1),			// Gamma Up
		
		options_buttons("ODB_21",	543,	248,	21,	DETAIL_LEVELS_TAB, 2),	// Planets On
		options_buttons("ODB_20",	485,	248,	20,	DETAIL_LEVELS_TAB, 2),	// Planets Off
		options_buttons("ODB_23",	543,	295,	23,	DETAIL_LEVELS_TAB, 2),	// Target View Rendering On
		options_buttons("ODB_22",	485,	295,	22,	DETAIL_LEVELS_TAB, 2),	// Target View Rendering Off
		options_buttons("ODB_25",	543,	342,	25,	DETAIL_LEVELS_TAB, 2),	// Weapon Extras On
		options_buttons("ODB_24",	485,	342,	24,	DETAIL_LEVELS_TAB, 2),	// Weapon Extras Off

		options_buttons("ODB_14",	566,	60,		14,	DETAIL_LEVELS_TAB, 2),	// Low Preset Detail
		options_buttons("ODB_15",	566,	81,		15,	DETAIL_LEVELS_TAB, 2),	// Medium Preset Detail
		options_buttons("ODB_16",	566,	102,	16,	DETAIL_LEVELS_TAB, 2),	// High Preset Detail
		options_buttons("ODB_17",	566,	123,	17,	DETAIL_LEVELS_TAB, 2),	// Highest Preset Detail
		options_buttons("ODB_18",	566,	144,	18,	DETAIL_LEVELS_TAB, 2),	// Custom Detail
	},
	{	// GR_1024
		options_buttons("2_OPT_00",	27,	4,		0,		-1),						// options tab
		options_buttons("2_OPT_01",	164,	4,		1,		-1),						// multiplayer tab
		options_buttons("2_OPT_02",	272,	4,		2,		-1),						// detail levels tab
		options_buttons("2_OPT_03",	16,	711,	3,		-1),						// abort game
		options_buttons("2_OPT_04",	657,	711,	4,		-1),						// control config button
		options_buttons("2_OPT_05",	809,	711,	5,		-1),						// hud config button
		options_buttons("2_OPT_06",	922,	694,	6,		-1),						// accept button		

		options_buttons("2_OMB_07",	81,	118,	7,		OPTIONS_TAB, 2),			// Briefing / debriefing voice toggle off
		options_buttons("2_OMB_08",	170,	118,	8,		OPTIONS_TAB, 2),			// Briefing / debriefing voice toggle on
		options_buttons("2_OMB_18",	81,	425,	18,	OPTIONS_TAB, 2),			// Mouse off
		options_buttons("2_OMB_19",	170,	425,	19,	OPTIONS_TAB, 2),			// Mouse on
		options_buttons("2_OMB_26",	925,	238,	26,	OPTIONS_TAB, 1),			// Gamma Down
		options_buttons("2_OMB_27",	971,	238,	27,	OPTIONS_TAB, 1),			// Gamma Up
		
		options_buttons("2_ODB_21",	956,	417,	21,	DETAIL_LEVELS_TAB, 2),	// Planets On
		options_buttons("2_ODB_20",	863,	417,	20,	DETAIL_LEVELS_TAB, 2),	// Planets Off
		options_buttons("2_ODB_23",	956,	492,	23,	DETAIL_LEVELS_TAB, 2),	// Target View Rendering On
		options_buttons("2_ODB_22",	863,	492,	22,	DETAIL_LEVELS_TAB, 2),	// Target View Rendering Off
		options_buttons("2_ODB_25",	956,	567,	25,	DETAIL_LEVELS_TAB, 2),	// Weapon Extras On
		options_buttons("2_ODB_24",	863,	567,	24,	DETAIL_LEVELS_TAB, 2),	// Weapon Extras Off

		options_buttons("2_ODB_14",	983,	122,	14,	DETAIL_LEVELS_TAB, 2),	// Low Preset Detail
		options_buttons("2_ODB_15",	983,	153,	15,	DETAIL_LEVELS_TAB, 2),	// Medium Preset Detail
		options_buttons("2_ODB_16",	983,	183,	16,	DETAIL_LEVELS_TAB, 2),	// High Preset Detail
		options_buttons("2_ODB_17",	983,	213,	17,	DETAIL_LEVELS_TAB, 2),	// Highest Preset Detail
		options_buttons("2_ODB_18",	983,	243,	18,	DETAIL_LEVELS_TAB, 2),	// Custom Detail
	}	
};

#define NUM_OPTIONS_SLIDERS			7
#define OPT_SOUND_VOLUME_SLIDER		0
#define OPT_MUSIC_VOLUME_SLIDER		1
#define OPT_VOICE_VOLUME_SLIDER		2
#define OPT_MOUSE_SENS_SLIDER			3
#define OPT_JOY_SENS_SLIDER			4
#define OPT_JOY_DEADZONE_SLIDER		5
#define OPT_SKILL_SLIDER				6

op_sliders Options_sliders[GR_NUM_RESOLUTIONS][NUM_OPTIONS_SLIDERS] = {
	{ // GR_640		
		op_sliders("OMB_10",		72,130,	-1,	-1,	10,	20,	10,
					  "OMB_11",		11, 272,131,
					  "OMB_09",		9, 45,131),								// sound fx volume slider
		op_sliders("OMB_13",		72,165,	-1,	-1,	13,	20,	10,
					  "OMB_14",		14, 272,166,
					  "OMB_12",		12, 45,166),								// music volume slider
		op_sliders("OMB_16",		72,200,	-1,	-1,	16,	20,	10,
					  "OMB_17",		17, 272,201,
					  "OMB_15",		15, 45,201),								// voice volume slider
		op_sliders("OMB_20",		47,307,	-1,	-1,	20,	20,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// mouse sensitivity	
		op_sliders("OMB_28",		397,244,	-1,	-1,	28,	20,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// joystick sensitivity
		op_sliders("OMB_29",		397,275,	-1,	-1,	29,	20,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// joystick deadzone
		op_sliders("OMB_21",		397, 60,	-1,	-1,	21,	36,	5,	NULL, -1, -1, -1, NULL, -1, -1, -1)
	},	
	{ // GR_1024		
		op_sliders("2_OMB_10",		50,	223,	-1,	-1,	10,	32,	10,
					  "2_OMB_11",		11,	361,	219,
					  "2_OMB_09",		9,		7,		219 ),								// sound fx volume slider
		op_sliders("2_OMB_13",		50,	281,	-1,	-1,	13,	32,	10,
					  "2_OMB_14",		14,	361,	275,
					  "2_OMB_12",		12,	7,		275 ),								// music volume slider
		op_sliders("2_OMB_16",		50,	335,	-1,	-1,	16,	32,	10,
					  "2_OMB_17",		17,	361,	330,
					  "2_OMB_15",		15,	7,		330 ),								// voice volume slider
		op_sliders("2_OMB_20",		9,		505,	-1,	-1,	20,	32,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// mouse sensitivity	
		op_sliders("2_OMB_28",		704,	414,	-1,	-1,	28,	32,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// joystick sensitivity
		op_sliders("2_OMB_29",		704,	464,	-1,	-1,	29,	32,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// joystick deadzone
		op_sliders("2_OMB_21",		704,	120,	-1,	-1,	21,	60,	5,	NULL, -1, -1, -1, NULL, -1, -1, -1)
	}
};

static struct {
	char *filename;
	char *mask_filename;
	int bitmap;
	int mask;
	
} Backgrounds[GR_NUM_RESOLUTIONS][NUM_TABS] = {
//XSTR:OFF
	{	// GR_640
		{ "OptionsMain", "OptionsMain-M"},
		{ "OptionsMulti", "OptionsMulti-M"},
		{ "OptionsDetail", "OptionsDetail-M"},
	},
	{	// GR_1024
		{ "2_OptionsMain", "2_OptionsMain-M"},
		{ "2_OptionsMulti", "2_OptionsMulti-M"},
		{ "2_OptionsDetail", "2_OptionsDetail-M"},
	}
//XSTR:ON
};

static int Tab = 0;
static int Options_menu_inited = 0;
#ifndef NO_NETWORK
static int Options_multi_inited = 0;
#endif
static int Options_detail_inited = 0;
static int Button_bms[NUM_COMMONS][MAX_BMAPS_PER_GADGET];

static UI_WINDOW Ui_window;
UI_GADGET Options_bogus;

static int Backup_skill_level;
#ifndef NO_SOUND
static float Backup_sound_volume;
static float Backup_music_volume;
static float Backup_voice_volume;
#endif

static int Backup_briefing_voice_enabled;
static int Backup_use_mouse_to_fly;

static int Sound_volume_int;
static int Music_volume_int;
static int Voice_volume_int;

static int Voice_vol_handle = -1;
int Options_notify_stamp = -1;
char Options_notify_string[200];

// called whenever accept is hit
// do any processing, etc in here.
void options_accept();
void options_force_button_frame(int n, int frame_num);

extern float Freespace_gamma;

void options_add_notify(char *str);
void options_notify_do_frame();

int Options_gamma_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		385,166,/*435, 179,*/ 195,	28	// GR_640
	},
	{
		692, 287, 308, 44		// GR_1024
	}
};

#define MAX_GAMMA_BITMAP_SIZE 17500

int Options_gamma_num_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		439,146, 65, 17//489, 159, 65, 17		// GR_640
	},
	{
		779, 254, 65, 17		// GR_1024
	}
};

int Options_skills_text_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		468, 92, 155, 10		// GR_640
	},
	{
		750, 169, 246, 21		// GR_1024
	}
};


// ---------------------------------------------------------------------------------------------------------
// DETAIL LEVEL OPTIONS definitions  BEGIN
//

#define NUM_DETAIL_SLIDERS			8

/*
#define DETAIL_DISTANCE_SLIDER	0
#define NEBULA_DETAIL_SLIDER		1
#define HARDWARE_TEXTURES_SLIDER	2
#define NUM_PARTICLES_SLIDER		6
#define SHARD_CULLING_SLIDER		3
#define SHIELD_DETAIL_SLIDER		4
#define NUM_STARS_SLIDER			5
#define LIGHTING_SLIDER				7
*/
#define DETAIL_DISTANCE_SLIDER	0
#define NEBULA_DETAIL_SLIDER		1
#define HARDWARE_TEXTURES_SLIDER	2
#define NUM_PARTICLES_SLIDER		3
#define SHARD_CULLING_SLIDER		4
#define SHIELD_DETAIL_SLIDER		5
#define NUM_STARS_SLIDER			6
#define LIGHTING_SLIDER				7
op_sliders Detail_sliders[GR_NUM_RESOLUTIONS][NUM_DETAIL_SLIDERS] = {
	{ // GR_640
		op_sliders("ODB_07",	45, 60,		-1,	-1,	7,		20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// model detail
		op_sliders("ODB_08",	45,	108,	-1,	-1,	8,		20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// nebula detail
		op_sliders("ODB_09",	45,	155,	-1,	-1,	9,		20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// textures
		op_sliders("ODB_10",	45,	201,	-1,	-1,	10,	20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// particles
		op_sliders("ODB_11",	45,249,	-1,	-1,	11,	20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// debris
		op_sliders("ODB_12",	45,296,	-1,	-1,	12,	20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// shield hit
		op_sliders("ODB_13",	45,343,	-1,	-1,	13,	20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// stars
		op_sliders("ODB_19",	464,199,	-1,	-1,	19,	20,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),			// lighting		
	},	
	{ // GR_1024
		op_sliders("2_ODB_07",	34,	114,	-1,	-1,	7,		32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// model detail
		op_sliders("2_ODB_08",	34,	190,	-1,	-1,	8,		32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// nebula detail
		op_sliders("2_ODB_09",	34,	265,	-1,	-1,	9,		32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// textures
		op_sliders("2_ODB_10",	34,	340,	-1,	-1,	10,	32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// particles
		op_sliders("2_ODB_11",	34,	416,	-1,	-1,	11,	32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// debris
		op_sliders("2_ODB_12",	34,	492,	-1,	-1,	12,	32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// shield hit
		op_sliders("2_ODB_13",	34,	567,	-1,	-1,	13,	32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// stars
		op_sliders("2_ODB_19",	829,	340,	-1,	-1,	19,	32,	5, NULL, -1, -1, -1, NULL, -1, -1, -1),		// lighting
	}
};
int Detail_slider_pos[NUM_DETAIL_SLIDERS];
detail_levels Detail_original;	// backup of Detail settings when screen is first entered
UI_GADGET Detail_bogus;
void options_detail_init();
void options_detail_hide_stuff();
void options_detail_unhide_stuff();
void options_detail_do_frame();
void options_detail_set_level(int level);

// text
#define OPTIONS_NUM_TEXT				47
UI_XSTR Options_text[GR_NUM_RESOLUTIONS][OPTIONS_NUM_TEXT] = {
	{ // GR_640
		// common text
		{ "Options",	1036,		44,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][OPTIONS_TAB].button },
		{ "Multi",		1042,		108,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][MULTIPLAYER_TAB].button },
		{ "Detail",		1351,		160,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][DETAIL_LEVELS_TAB].button },
		{ "Exit",		1059,		493,390,	UI_XSTR_COLOR_PINK,	-1, &Buttons[0][ABORT_GAME_BUTTON].button },
		{ "Game",		1412,		493,403,	UI_XSTR_COLOR_PINK,	-1, &Buttons[0][ABORT_GAME_BUTTON].button },
		{ "Control",	1352,		207,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][CONTROL_CONFIG_BUTTON].button },
		//{ "Config",		1353,		409,	430,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][CONTROL_CONFIG_BUTTON].button },
		{ "HUD",		1354,		280,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][HUD_CONFIG_BUTTON].button },
		//{ "Config",		1415,		504,	430,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][HUD_CONFIG_BUTTON].button },
		{ "Accept",		1035,		541,397,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][ACCEPT_BUTTON].button },
		
		// text for the detail level screen 
		{ "Preset Detail Levels",	1355,	410, 50,	UI_XSTR_COLOR_GREEN,	-1, &Detail_bogus },
		{ "Low",			1160,		529, 67,	UI_XSTR_COLOR_GREEN, -1, &Buttons[0][LOW_DETAIL_N].button },
		{ "Medium",		1161,		510, 88,	UI_XSTR_COLOR_GREEN, -1, &Buttons[0][MEDIUM_DETAIL_N].button },
		{ "High",		1162,		527,109,	UI_XSTR_COLOR_GREEN, -1, &Buttons[0][HIGH_DETAIL_N].button },
		{ "Very High",	1163,		489,130,	UI_XSTR_COLOR_GREEN, -1, &Buttons[0][VERY_HIGH_DETAIL_N].button },
		{ "Custom",		1356,		505,150,	UI_XSTR_COLOR_GREEN, -1, &Buttons[0][CUSTOM_DETAIL_N].button },		
		{ "Off",		1286,		451,254,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][PLANETS_OFF].button },
		{ "On",			1285,		515,254,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][PLANETS_ON].button },
		{ "Off",		1286,		451,301,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][HUD_TARGETVIEW_RENDER_OFF].button },
		{ "On",			1285,		515,301,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][HUD_TARGETVIEW_RENDER_ON].button },
		{ "Off",		1286,		451,348,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][WEAPON_EXTRAS_OFF].button },
		{ "On",			1285,		515,348,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][WEAPON_EXTRAS_ON].button },
		{ "Planets/Backgrounds",		1357,	397,231, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Target View Rendering",		1358,	388,278, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Weapon Extras",				1359,	439,325, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Model Detail",				1360,	45, 50,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Nebula Detail",				1361,	45, 97,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "3D Hardware Textures",		1362,	45,144,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Particles",					1363,	45,191,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Impact Effects",				1364,	45,238,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Shield Hit Effects",			1365,	45,285,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Stars",						1366,	45,332,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Lighting",					1367,	491,184,	UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },

		// main options screen text
		{ "Briefing Voice",	1368,	60, 50,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Off",					1286,	65, 72,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][BRIEF_VOICE_OFF].button },
		{ "On",					1285,	128, 72,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][BRIEF_VOICE_ON].button },
		{ "Volume",				1369,	60,102,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Effects",			1370,	65,121,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Music",				1371,	65,156,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Voice",				1372,	65,190,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Mouse",				1373,	60,240,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Off",				1286,	65,264,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][MOUSE_OFF].button },
		{ "On",					1285,	128,264,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[0][MOUSE_ON].button },
		{ "Sensitivity",		1529,	65,288,	UI_XSTR_COLOR_GREEN,	-1, &Options_sliders[0][OPT_MOUSE_SENS_SLIDER].slider },
		{ "Skill Level",		1509,	482, 50,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Brightness",			1375,	482,120,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Joystick",			1376,	524,216,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Sensitivity",		1374,	505,235,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Deadzone",			1377,	505,266,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
	},
	{ // GR_1024
			// common text
		{ "Options",	1036,		16,	57,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][OPTIONS_TAB].button },
		{ "Multi",		1042,		172,	57,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][MULTIPLAYER_TAB].button },
		{ "Detail",		1351,		283,	57,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][DETAIL_LEVELS_TAB].button },
		{ "Exit",		1059,		13,	685,	UI_XSTR_COLOR_PINK,	-1, &Buttons[1][ABORT_GAME_BUTTON].button },
		{ "Game",		1412,		13,	696,	UI_XSTR_COLOR_PINK,	-1, &Buttons[1][ABORT_GAME_BUTTON].button },
		{ "Control",	1352,		655,	685,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][CONTROL_CONFIG_BUTTON].button },
	//	{ "Config",		1353,		655,	696,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][CONTROL_CONFIG_BUTTON].button },
		{ "HUD",			1354,		806,	685,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][HUD_CONFIG_BUTTON].button },
	//	{ "Config",		1415,		806,	696,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][HUD_CONFIG_BUTTON].button },
		{ "Accept",		1035,		927,	672,	UI_XSTR_COLOR_PINK,	-1, &Buttons[1][ACCEPT_BUTTON].button },
		
		// text for the detail level screen 
		{ "Preset Detail Levels",	1355,	809,	90,	UI_XSTR_COLOR_GREEN,	-1, &Detail_bogus },
		{ "Low",			1160,		944,	131,	UI_XSTR_COLOR_GREEN, -1, &Buttons[1][LOW_DETAIL_N].button },
		{ "Medium",		1161,		924,	161,	UI_XSTR_COLOR_GREEN, -1, &Buttons[1][MEDIUM_DETAIL_N].button },
		{ "High",		1162,		942,	192,	UI_XSTR_COLOR_GREEN, -1, &Buttons[1][HIGH_DETAIL_N].button },
		{ "Very High",	1163,		903,	222,	UI_XSTR_COLOR_GREEN, -1, &Buttons[1][VERY_HIGH_DETAIL_N].button },
		{ "Custom",		1356,		922,	252,	UI_XSTR_COLOR_GREEN, -1, &Buttons[1][CUSTOM_DETAIL_N].button },		
		{ "Off",			1286,		835,	427,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][PLANETS_OFF].button },
		{ "On",			1285,		936,	427,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][PLANETS_ON].button },
		{ "Off",			1286,		835,	503,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][HUD_TARGETVIEW_RENDER_OFF].button },
		{ "On",			1285,		936,	503,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][HUD_TARGETVIEW_RENDER_ON].button },
		{ "Off",			1286,		835,	578,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][WEAPON_EXTRAS_OFF].button },
		{ "On",			1285,		936,	578,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][WEAPON_EXTRAS_ON].button },
		{ "Planets/Backgrounds",	1357,	808,	391, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Target View Rendering",	1358,	799,	466, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },
		{ "Weapon Extras",			1359,	850,	542, UI_XSTR_COLOR_GREEN, -1, &Detail_bogus },				
		{ "Model Detail",					1360,	44,	99,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][DETAIL_DISTANCE_SLIDER].slider },
		{ "Nebula Detail",				1361,	44,	175,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][NEBULA_DETAIL_SLIDER].slider },
		{ "3D Hardware Textures",		1362,	44,	250,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][HARDWARE_TEXTURES_SLIDER].slider },
		{ "Particles",						1363,	44,	325,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][NUM_PARTICLES_SLIDER].slider },
		{ "Impact Effects",				1364,	44,	401,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][SHARD_CULLING_SLIDER].slider },
		{ "Shield Hit Effects",			1365,	44,	476,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][SHIELD_DETAIL_SLIDER].slider },
		{ "Stars",							1366, 44,	552,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][NUM_STARS_SLIDER].slider },
		{ "Lighting",						1367, 903,	326,	UI_XSTR_COLOR_GREEN, -1, &Detail_sliders[1][LIGHTING_SLIDER].slider },

		// main options screen text
		{ "Briefing Voice",	1368,	23,	93,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Off",					1286,	32,	130,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][BRIEF_VOICE_OFF].button },
		{ "On",					1285,	134,	130,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][BRIEF_VOICE_ON].button },
		{ "Volume",				1369,	23,	178,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Effects",			1370,	33,	209,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Music",				1371,	33,	264,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Voice",				1372,	33,	319,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Mouse",				1373,	23,	399,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Off",					1286,	32,	437,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][MOUSE_OFF].button },
		{ "On",					1285,	134,	437,	UI_XSTR_COLOR_GREEN,	-1, &Buttons[1][MOUSE_ON].button },
		{ "Sensitivity",		1529,	34,	477,	UI_XSTR_COLOR_GREEN,	-1, &Options_sliders[1][OPT_MOUSE_SENS_SLIDER].slider },
		{ "Skill Level",		1509,	854,	93,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Brightness",		1375,	852,	214,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Joystick",			1376,	891,	370,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Sensitivity",		1374,	861,	400,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
		{ "Deadzone",			1377,	861,	451,	UI_XSTR_COLOR_GREEN,	-1, &Options_bogus },
	}
};


//
// DETAIL LEVEL tab definitions END
// ---------------------------------------------------------------------------------------------------------

void check_option_hotspot(int x, int y)
{
	// Options
	if ((x >= Option_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Option_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Option_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Option_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(44,397, "Options");
		}
	}
	
	// Multiplayer
	if ((x >= Multi_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Multi_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Multi_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Multi_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(108,397, "Multi");
		}
	}

	// Detail
	if ((x >= Detail_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Detail_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Detail_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Detail_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(160,397, "Detail");
		}
	}

	// Quit
	if ((x >= Quit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Quit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Quit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Quit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(498,390, "Exit");
			gr_string(493,403, "Game");
		}
	}

	// Control
	if ((x >= Control_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Control_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Control_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Control_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(207,397, "Control");
		}
	}

	// Hud
	if ((x >= Hud_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Hud_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Hud_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Hud_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(277,397, "Hud");
		}
	}

	// Accept
	if ((x >= Accept_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Accept_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Accept_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Accept_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			gr_set_color_fast(&Color_bright_white);
			gr_string(541,397, "Accept");
		}
	}
}

void options_play_voice_clip()
{
	int snd_id;

	if ( snd_is_playing(Voice_vol_handle) ) {
		snd_stop(Voice_vol_handle);
		Voice_vol_handle=-1;
	}

	snd_id = snd_load(&Snds_iface[SND_VOICE_SLIDER_CLIP], 0);
	Voice_vol_handle = snd_play_raw( snd_id, 0.0f, 1.0f, SND_PRIORITY_SINGLE_INSTANCE );
}

void options_add_notify(char *str)
{
	strcpy(Options_notify_string, str);
	Options_notify_stamp = timestamp(OPTIONS_NOTIFY_TIME);
}

void options_notify_do_frame()
{
	int w,h;

	if (Options_notify_stamp != -1) {
		if (timestamp_elapsed(Options_notify_stamp)) {
			Options_notify_stamp = -1;

		} else {
			gr_get_string_size(&w, &h, Options_notify_string);
			gr_printf((gr_screen.max_w - w) / 2, OPTIONS_NOTIFY_Y, Options_notify_string);
		}
	}
}

/*
void options_set_bmaps(int btn, int bm_index)
{
	int j;

	for (j=0; j<MAX_BMAPS_PER_GADGET; j++){
		Buttons[gr_screen.res][btn].button.bmap_ids[j] = Button_bms[bm_index][j];
	}
}
*/

void options_tab_setup(int set_palette)
{
	// char *pal;
	int i;
	int flags[256];

	if (Tab != MULTIPLAYER_TAB) {
		Assert(Backgrounds[gr_screen.res][Tab].mask >= 0);
		Ui_window.set_mask_bmap(Backgrounds[gr_screen.res][Tab].mask, Backgrounds[gr_screen.res][Tab].mask_filename);
	}

	for (i=0; i<256; i++){
		flags[i] = 0;
	}

	// activate, deactivate any necessary controls
	for (i=0; i<NUM_BUTTONS; i++) {
		if ( ((Buttons[gr_screen.res][i].tab == Tab) || (Buttons[gr_screen.res][i].tab == -1)) && !flags[Buttons[gr_screen.res][i].hotspot] ) {
			flags[Buttons[gr_screen.res][i].hotspot] = 1;
			Buttons[gr_screen.res][i].button.enable();
			if (Buttons[gr_screen.res][i].filename)
				Buttons[gr_screen.res][i].button.unhide();

		} else {
			Buttons[gr_screen.res][i].button.disable();
			Buttons[gr_screen.res][i].button.hide();
		}
	}

	// maybe enable/disable controls based upon current tab
	if (Tab == OPTIONS_TAB) {
		for(i=0; i<NUM_OPTIONS_SLIDERS; i++){
			Options_sliders[gr_screen.res][i].slider.enable();
			Options_sliders[gr_screen.res][i].slider.unhide();
		}		
	} else {
		for(i=0; i<NUM_OPTIONS_SLIDERS; i++){
			Options_sliders[gr_screen.res][i].slider.hide();
			Options_sliders[gr_screen.res][i].slider.disable();
		}		
	}	

	if( ((Game_mode & GM_IN_MISSION) && (!popupdead_is_active())) || (Game_mode & GM_MULTIPLAYER) ){
		Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.disable();
		Ui_window.use_hack_to_get_around_stupid_problem_flag = 0;
	}

	// do other special processing
	switch (Tab) {
		case MULTIPLAYER_TAB:
#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
#ifndef NO_NETWORK
			options_multi_select();
#endif			
			// need to hide the hud config and control config buttons
			// Buttons[gr_screen.res][CONTROL_CONFIG_BUTTON].button.hide();
			// Buttons[gr_screen.res][HUD_CONFIG_BUTTON].button.hide();
#endif // DEMO
			break;

		case DETAIL_LEVELS_TAB:
			options_detail_unhide_stuff();	
			break;
	}
}

// call this function to close down, do other processing of data in the tab that's being left
void options_tab_close()
{
	switch (Tab) {
		case MULTIPLAYER_TAB:
#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
#ifndef NO_NETWORK
			options_multi_unselect();		
#endif
#endif
			break;

		case DETAIL_LEVELS_TAB:
			options_detail_hide_stuff();
			break;
	}
}

void options_change_tab(int n)
{
	int idx;

#if defined(DEMO) || defined(OEM_BUILD) // not for FS2_DEMO
	if (n == MULTIPLAYER_TAB) {
		game_feature_not_in_demo_popup();
		return;
	}
#endif

	switch (n) {
#ifndef NO_NETWORK
		case MULTIPLAYER_TAB:
			if ( !Options_multi_inited ) {
				// init multiplayer
#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
				options_multi_init(&Ui_window);
				options_multi_unselect();
#endif
				Options_multi_inited = 1;
			}

			break;
#endif

		case DETAIL_LEVELS_TAB:
			if (!Options_detail_inited) {
				// init detail levels
				options_detail_init();
				options_detail_hide_stuff();
				Options_detail_inited = 1;
			}

			break;
	}

	// if we're going into the main screen
	if(n == OPTIONS_TAB){
		Options_bogus.enable();
		Options_bogus.unhide();
		for(idx=0; idx<NUM_OPTIONS_SLIDERS; idx++){
			Options_sliders[gr_screen.res][idx].slider.enable();
			Options_sliders[gr_screen.res][idx].slider.unhide();
		}
	} else {
		Options_bogus.hide();
		Options_bogus.disable();
		for(idx=0; idx<NUM_OPTIONS_SLIDERS; idx++){
			Options_sliders[gr_screen.res][idx].slider.hide();
			Options_sliders[gr_screen.res][idx].slider.disable();
		}
	}

	if (n != MULTIPLAYER_TAB) {
		if (Backgrounds[gr_screen.res][n].mask < 0) {
			gamesnd_play_iface(SND_GENERAL_FAIL);
			return;
		}
	}

	options_tab_close();

	Tab = n;
	options_tab_setup(1);
	gamesnd_play_iface(SND_SCREEN_MODE_PRESSED);
}

void set_sound_volume()
{
	main_hall_reset_ambient_vol();
}

void set_music_volume()
{
#ifndef NO_SOUND
	event_music_set_volume_all(Master_event_music_volume);
#endif
}

void set_voice_volume()
{
#ifndef NO_SOUND
	audiostream_set_volume_all(Master_voice_volume, ASF_VOICE);
#endif
}

void options_cancel_exit()
{
#ifndef NO_SOUND
	Master_sound_volume = Backup_sound_volume;
	set_sound_volume();
	Master_event_music_volume = Backup_music_volume;
	set_music_volume();
	Master_voice_volume = Backup_voice_volume;
	set_voice_volume();
#endif

	if(!(Game_mode & GM_MULTIPLAYER)){
		Game_skill_level = Backup_skill_level;
	}

	Briefing_voice_enabled = Backup_briefing_voice_enabled;
	Use_mouse_to_fly = Backup_use_mouse_to_fly;

	if ( Options_detail_inited ) {
		Detail = Detail_original;
	}

	gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
}

void options_change_gamma(float delta)
{
	char tmp_gamma_string[32];

	Freespace_gamma += delta;
	if (Freespace_gamma < 0.1f) {
		Freespace_gamma = 0.1f;
		gamesnd_play_iface(SND_GENERAL_FAIL);

	} else if (Freespace_gamma > 5.0f) {
		Freespace_gamma = 5.0f;
		gamesnd_play_iface(SND_GENERAL_FAIL);

	} else {
		gamesnd_play_iface(SND_USER_SELECT);
	}

	gr_set_gamma(Freespace_gamma);
	sprintf(tmp_gamma_string, NOX("%.2f"), Freespace_gamma);

	os_config_write_string(NULL, 
		(gr_screen.mode == GR_DIRECT3D) ? NOX("GammaD3D") : NOX("Gamma"), tmp_gamma_string);
}

void options_button_pressed(int n)
{
	int choice;	

	switch (n) {		
		case OPTIONS_TAB:
		
		case MULTIPLAYER_TAB:
		
		case DETAIL_LEVELS_TAB:	
			current_tab = n;
			if (Tab != n)
				options_change_tab(n);

			break;

		case ABORT_GAME_BUTTON:
			current_tab = 3;
			gamesnd_play_iface(SND_USER_SELECT);
			choice = popup( PF_NO_NETWORKING | PF_BODY_BIG, 2, POPUP_NO, POPUP_YES, XSTR( "Exit Game?", 374));
			if ( choice == 1 )
				gameseq_post_event(GS_EVENT_QUIT_GAME);
			break;

		case CONTROL_CONFIG_BUTTON:
			current_tab = 4;
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_CONTROL_CONFIG);
			current_tab = 0;
			break;				

		case HUD_CONFIG_BUTTON:
#ifdef FS2_DEMO
			game_feature_not_in_demo_popup();
#else

#ifndef NO_NETWORK
			// can't go to the hud config screen when a multiplayer observer
			if((Game_mode & GM_MULTIPLAYER) && (Net_player->flags & NETINFO_FLAG_OBSERVER)){
				gamesnd_play_iface(SND_GENERAL_FAIL);
				options_add_notify(XSTR( "Cannot use HUD config when an observer!", 375));
				break;
			}
#endif  // ifndef NO_NETWORK
			current_tab = 5;

			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_HUD_CONFIG);

			current_tab = 0;
#endif
			break;

		case ACCEPT_BUTTON:
			options_accept();
			break;		

			// BEGIN - detail level tab buttons

		case HUD_TARGETVIEW_RENDER_ON:
			Detail.targetview_model = 1;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case HUD_TARGETVIEW_RENDER_OFF:
			Detail.targetview_model = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case PLANETS_ON:
			Detail.planets_suns = 1;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case PLANETS_OFF:
			Detail.planets_suns = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case WEAPON_EXTRAS_ON:
			Detail.weapon_extras = 1;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case WEAPON_EXTRAS_OFF:
			Detail.weapon_extras = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			break;		

		case LOW_DETAIL_N:
			options_detail_set_level(0);
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case MEDIUM_DETAIL_N:
			options_detail_set_level(1);
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case HIGH_DETAIL_N:
			options_detail_set_level(2);
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case VERY_HIGH_DETAIL_N:
			options_detail_set_level(3);
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case CUSTOM_DETAIL_N:
			options_detail_set_level(-1);
			gamesnd_play_iface(SND_USER_SELECT);
			break;
			// END - detail level tab buttons

		case GAMMA_DOWN:
			options_change_gamma(-0.05f);
			break;

		case GAMMA_UP:
			options_change_gamma(0.05f);
			break;

		case BRIEF_VOICE_ON:
			Briefing_voice_enabled = 1;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case BRIEF_VOICE_OFF:
			Briefing_voice_enabled = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case MOUSE_ON:
			Use_mouse_to_fly = 1;
			gamesnd_play_iface(SND_USER_SELECT);
			break;

		case MOUSE_OFF:
			Use_mouse_to_fly = 0;
			gamesnd_play_iface(SND_USER_SELECT);
			break;
	}
}

void options_sliders_update()
{
#ifndef NO_SOUND
	// sound slider
	if (Options_sliders[gr_screen.res][OPT_SOUND_VOLUME_SLIDER].slider.pos != Sound_volume_int) {
		Sound_volume_int = Options_sliders[gr_screen.res][OPT_SOUND_VOLUME_SLIDER].slider.pos;
		Master_sound_volume = ((float) (Sound_volume_int) / 9.0f);
		set_sound_volume();
		gamesnd_play_iface(SND_USER_SELECT);
	}

	// music slider
	if (Options_sliders[gr_screen.res][OPT_MUSIC_VOLUME_SLIDER].slider.pos != Music_volume_int) {
		Music_volume_int = Options_sliders[gr_screen.res][OPT_MUSIC_VOLUME_SLIDER].slider.pos;
		Master_event_music_volume = ((float) (Music_volume_int) / 9.0f);
		if (Master_event_music_volume > 0.0f) {
			event_music_enable();
		}

		set_music_volume();
		gamesnd_play_iface(SND_USER_SELECT);
	}

	// voice slider
	if (Options_sliders[gr_screen.res][OPT_VOICE_VOLUME_SLIDER].slider.pos != Voice_volume_int) {
		Voice_volume_int = Options_sliders[gr_screen.res][OPT_VOICE_VOLUME_SLIDER].slider.pos;
		Master_voice_volume = ((float) (Voice_volume_int) / 9.0f);
		set_voice_volume();
		options_play_voice_clip();
	}
#endif

	if (Mouse_sensitivity != Options_sliders[gr_screen.res][OPT_MOUSE_SENS_SLIDER].slider.pos) {
		Mouse_sensitivity = Options_sliders[gr_screen.res][OPT_MOUSE_SENS_SLIDER].slider.pos;
		gamesnd_play_iface(SND_USER_SELECT);
	}

#ifndef NO_JOYSTICK
	if (Joy_sensitivity != Options_sliders[gr_screen.res][OPT_JOY_SENS_SLIDER].slider.pos) {
		Joy_sensitivity = Options_sliders[gr_screen.res][OPT_JOY_SENS_SLIDER].slider.pos;
		gamesnd_play_iface(SND_USER_SELECT);
	}

	if (Dead_zone_size != Options_sliders[gr_screen.res][OPT_JOY_DEADZONE_SLIDER].slider.pos * 5) {
		Dead_zone_size = Options_sliders[gr_screen.res][OPT_JOY_DEADZONE_SLIDER].slider.pos * 5;
		gamesnd_play_iface(SND_USER_SELECT);
	}
#endif

	if (Game_skill_level != Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.pos) {
		Game_skill_level = Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.pos;
		gamesnd_play_iface(SND_USER_SELECT);
	}
}

void options_accept()
{
#ifndef NO_NETWORK
	// apply the selected multiplayer options
	if ( Options_multi_inited ) {
		#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
		options_multi_accept();
		#endif
	}
#endif  // ifndef NO_NETWORK

#ifndef NO_SOUND
	// If music is zero volume, disable
	if ( Master_event_music_volume <= 0.0f ) {
//		event_music_disable();
		event_music_level_close();
	}
#endif

	// apply other options (display options, etc)
	// note: return in here (and play failed sound) if they can't accept yet for some reason

	gamesnd_play_iface(SND_COMMIT_PRESSED);
	gameseq_post_event(GS_EVENT_PREVIOUS_STATE);
}

void options_load_background_and_mask(int tab)
{
	Assert(tab == OPTIONS_TAB || tab == DETAIL_LEVELS_TAB );
	Backgrounds[gr_screen.res][tab].bitmap = bm_load(Backgrounds[gr_screen.res][tab].filename);
	Backgrounds[gr_screen.res][tab].mask = bm_load(Backgrounds[gr_screen.res][tab].mask_filename);
}

int Gamma_last_set = -1;
int Gamma_colors_inited = 0;

void options_menu_init()
{
	int i, j;
	options_buttons *b;

	Assert(!Options_menu_inited);

	// pause all sounds, since we could get here through the game
	beam_pause_sounds();
	//audiostream_pause_all();

	Tab = 0;
	Gamma_last_set = -1;

	common_set_interface_palette("InterfacePalette");  // set the interface palette
	Ui_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);

	// create window to track hotspots
	Hotspot_region.create(&Ui_window, "", 0, 0, gr_screen.max_w, gr_screen.max_h, 0, 1);
	Hotspot_region.hide();

	for (i=0; i<PLANETS_ON; i++) {
		b = &Buttons[gr_screen.res][i];

		b->button.create(&Ui_window, "", b->x, b->y, 60, 30, b->flags & REPEAT, 1);
		// set up callback for when a mouse first goes over a button
		if (b->filename) {
			b->button.set_bmaps(b->filename);
			if ( !(b->flags & NO_MOUSE_OVER_SOUND) ) {
				b->button.set_highlight_action(common_play_highlight_sound);
			}

		} else {
			b->button.hide();
		}

		b->button.link_hotspot(b->hotspot);
		if (i < NUM_COMMONS) {
			for (j=0; j<MAX_BMAPS_PER_GADGET; j++){
				Button_bms[i][j] = b->button.bmap_ids[j];
			}
		}
	}

	// add all xstr text
	for(i=8; i<OPTIONS_NUM_TEXT; i++){
		Ui_window.add_XSTR(&Options_text[gr_screen.res][i]);
	}

	// bogus controls
	Detail_bogus.base_create(&Ui_window, UI_KIND_ICON, 0, 0, 0, 0);
	Options_bogus.base_create(&Ui_window, UI_KIND_ICON, 0, 0, 0, 0);

	Buttons[gr_screen.res][GAMMA_DOWN].button.set_hotkey(KEY_COMMA);
	Buttons[gr_screen.res][GAMMA_UP].button.set_hotkey(KEY_PERIOD);

	/*
	Skill_control.first_frame = bm_load_animation("OPa_11", &Skill_control.total_frames);
	if (Skill_control.first_frame < 0) {
		Error(LOCATION, "Could not load OPa_11.ani\n");
		return;
	}
	*/

	for (i=0; i<NUM_TABS; i++) {
		Backgrounds[gr_screen.res][i].bitmap = -1;
		Backgrounds[gr_screen.res][i].mask = -1;
	}

	options_load_background_and_mask(OPTIONS_TAB);
	options_tab_setup(0);

	Backup_skill_level = Game_skill_level;
#ifndef NO_SOUND
	Backup_sound_volume = Master_sound_volume;
	Backup_music_volume = Master_event_music_volume;
	Backup_voice_volume = Master_voice_volume;
#endif
	Backup_briefing_voice_enabled = Briefing_voice_enabled;
	Backup_use_mouse_to_fly = Use_mouse_to_fly;
	
	// create slider	
	for ( i = 0; i < NUM_OPTIONS_SLIDERS; i++ ) {
		 Options_sliders[gr_screen.res][i].slider.create(&Ui_window, Options_sliders[gr_screen.res][i].x, Options_sliders[gr_screen.res][i].y,
																		Options_sliders[gr_screen.res][i].dots, Options_sliders[gr_screen.res][i].filename,
																		Options_sliders[gr_screen.res][i].hotspot, Options_sliders[gr_screen.res][i].right_filename, Options_sliders[gr_screen.res][i].right_mask, Options_sliders[gr_screen.res][i].right_x, Options_sliders[gr_screen.res][i].right_y,
																		Options_sliders[gr_screen.res][i].left_filename, Options_sliders[gr_screen.res][i].left_mask, Options_sliders[gr_screen.res][i].left_x, Options_sliders[gr_screen.res][i].left_y,
																		Options_sliders[gr_screen.res][i].dot_w);
	}	

	// maybe disable the skill slider
	if( ((Game_mode & GM_IN_MISSION) && (!popupdead_is_active())) || (Game_mode & GM_MULTIPLAYER) ) {
		Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.disable();
		Ui_window.use_hack_to_get_around_stupid_problem_flag = 0;
	}
	
	// setup slider values 
	// note slider scale is 0-9, while Master_ values calc with 1-10 scale (hence the -1)
#ifndef NO_SOUND
	Sound_volume_int = Options_sliders[gr_screen.res][OPT_SOUND_VOLUME_SLIDER].slider.pos = (int) (Master_sound_volume * 9.0f + 0.5f);
	Music_volume_int = Options_sliders[gr_screen.res][OPT_MUSIC_VOLUME_SLIDER].slider.pos = (int) (Master_event_music_volume * 9.0f + 0.5f);	
	Voice_volume_int = Options_sliders[gr_screen.res][OPT_VOICE_VOLUME_SLIDER].slider.pos = (int) (Master_voice_volume * 9.0f + 0.5f);
#else
	Sound_volume_int = Options_sliders[gr_screen.res][OPT_SOUND_VOLUME_SLIDER].slider.pos = 0;
	Music_volume_int = Options_sliders[gr_screen.res][OPT_MUSIC_VOLUME_SLIDER].slider.pos = 0;
	Voice_volume_int = Options_sliders[gr_screen.res][OPT_VOICE_VOLUME_SLIDER].slider.pos = 0;
#endif

#ifndef NO_JOYSTICK
	Options_sliders[gr_screen.res][OPT_JOY_SENS_SLIDER].slider.pos = Joy_sensitivity;	
	Options_sliders[gr_screen.res][OPT_JOY_DEADZONE_SLIDER].slider.pos = Dead_zone_size / 5;	
#else
	Options_sliders[gr_screen.res][OPT_JOY_SENS_SLIDER].slider.pos = 0;	
	Options_sliders[gr_screen.res][OPT_JOY_DEADZONE_SLIDER].slider.pos = 0;	
#endif
	Options_sliders[gr_screen.res][OPT_MOUSE_SENS_SLIDER].slider.pos = Mouse_sensitivity;
	Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.pos = Game_skill_level;

	Gamma_colors_inited = 0;

	// used to allow all keystrokes, even when called from a demo playback
	key_clear_filter();
	Options_menu_inited = 1;

	// hide options crap
	options_detail_hide_stuff();

}

void options_menu_close()
{
	int i;	

	Assert(Options_menu_inited);	

	for (i=0; i<NUM_TABS; i++) {
		if (Backgrounds[gr_screen.res][i].bitmap >= 0){
			bm_unload(Backgrounds[gr_screen.res][i].bitmap);
		}
		if ((Backgrounds[gr_screen.res][i].mask >= 0) && (i != Tab)){  // Ui_window.destroy() expects to release current tab's mask.
			bm_unload(Backgrounds[gr_screen.res][i].mask);
		}
	}

	if ( Voice_vol_handle >= 0 ) {
		snd_stop(Voice_vol_handle);
		Voice_vol_handle = -1;
	}

#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
#ifndef NO_NETWORK
	options_multi_close();
#endif
#endif

	Ui_window.destroy();
	common_free_interface_palette();		// restore game palette
	write_pilot_file();
	game_flush();
	
	// unpause all sounds, since we could be headed back to the game
	beam_unpause_sounds();
	//audiostream_unpause_all();
	
	Options_menu_inited = 0;
#ifndef NO_NETWORK
	Options_multi_inited = 0;
#endif
	Options_detail_inited = 0;


}


void draw_gamma_box()
{
	int x, y, v;

// NEILK: i had to change this declaration because the size is determined dynamically. I just picked an arbitrary large number to data size (although we should always be using less)
// TODO: change MAX size to maximum size for a 1024x768 bitmap
//	ushort Gamma_data[Options_gamma_coords[gr_screen.res][OPTIONS_W_COORD]*Options_gamma_coords[gr_screen.res][OPTIONS_H_COORD]*2];
	ushort Gamma_data[MAX_GAMMA_BITMAP_SIZE];

	v = fl2i( pow(0.5f, 1.0f / Freespace_gamma) * 255.0f );
	if (v > 255){
		v = 255;
	} else if (v < 0){
		v = 0;
	}

	int Gamma_changed = 0;
	if ( v != Gamma_last_set )	{
		Gamma_changed = 1;
	} else {
		Gamma_changed = 0;
	}
	Gamma_last_set = v;

	{
		ushort clr_full_white = 0;
		ushort clr_half_white = 0;
		ubyte r, g, b, a;

		BM_SELECT_TEX_FORMAT();

		// set full white
		r = g = b = a = 255;		
		bm_set_components((ubyte*)&clr_full_white, &r, &g, &b, &a);

		// set half white
		r = g = b = (ubyte)v;
		bm_set_components((ubyte*)&clr_half_white, &r, &g, &b, &a);

		ushort *dptr = Gamma_data;
		for (y=0; y<Options_gamma_coords[gr_screen.res][OPTIONS_H_COORD]; y++) {
			for (x=0; x<Options_gamma_coords[gr_screen.res][OPTIONS_W_COORD]; x++) {
				if ((x / 20) & 1) {
					*dptr = clr_half_white;
				} else {
					if ((x & 1) == (y & 1)) {
						*dptr = clr_full_white;
					} else {
						*dptr = 0;
					}
				}
				dptr++;
			}
		}

		// always go back to screen format
		BM_SELECT_SCREEN_FORMAT();

		// if we're in bitmap poly mode		
		int Gamma_bitmap = bm_create( 16, Options_gamma_coords[gr_screen.res][OPTIONS_W_COORD], Options_gamma_coords[gr_screen.res][OPTIONS_H_COORD], Gamma_data, 0 );
		gr_set_bitmap(Gamma_bitmap);
		gr_bitmap( Options_gamma_coords[gr_screen.res][OPTIONS_X_COORD], Options_gamma_coords[gr_screen.res][OPTIONS_Y_COORD] );

		bm_release( Gamma_bitmap );

	}
}


void options_menu_do_frame(float frametime)
{
	int i, k, x, y;	

	Assert(Options_menu_inited);
	k = Ui_window.process() & ~KEY_DEBUGGED;
	switch (k) {
		case KEY_SHIFTED | KEY_TAB:
		case KEY_LEFT:  // activate previous tab
			i = Tab - 1;
			if (i < 0)
				i = NUM_TABS - 1;

			options_change_tab(i);
			break;

		case KEY_TAB:
		case KEY_RIGHT:  // activate next tab
#ifndef NO_NETWORK
			// check to see if the multiplayer options screen wants to eat the tab kay
			if ((k == KEY_TAB) && (Tab == MULTIPLAYER_TAB)) {
				if (options_multi_eat_tab()) {
					break;
				}
			}
#endif

			i = Tab + 1;
			if (i >= NUM_TABS)
				i = 0;

			options_change_tab(i);
			break;

		case KEY_C:
			if (Tab == OPTIONS_TAB) {
				gamesnd_play_iface(SND_SWITCH_SCREENS);
				gameseq_post_event(GS_EVENT_CONTROL_CONFIG);
			}

			break;

		case KEY_H:
			if (Tab == OPTIONS_TAB) {
				gamesnd_play_iface(SND_SWITCH_SCREENS);
				gameseq_post_event(GS_EVENT_HUD_CONFIG);
			}

			break;

		case KEY_ESC:
			// if(Tab != MULTIPLAYER_TAB){
				options_cancel_exit();
			// }
			break;

		case KEY_CTRLED | KEY_ENTER:
			options_accept();
			break;

		case KEY_DELETE:
			break;

		case KEY_ENTER:			
			break;

		case DETAIL_LEVELS_TAB:
			Ui_window.add_XSTR(&Options_text[gr_screen.res][2]);
			
			break;
	}
	

	//	options_force_button_frame(OPTIONS_TAB, 1);
	//options_force_button_frame(DETAIL_LEVELS_TAB, 1);

	
						
	
	/**/

/*	#define 					7
#define BRIEF_VOICE_ON					8
#define MOUSE_OFF							9
#define MOUSE_ON							10
#define GAMMA_DOWN						11
#define GAMMA_UP							12

// detail level screen buttons
#define PLANETS_ON						13
#define PLANETS_OFF						14
#define HUD_TARGETVIEW_RENDER_ON		15
#define HUD_TARGETVIEW_RENDER_OFF	16
#define WEAPON_EXTRAS_ON				17
#define WEAPON_EXTRAS_OFF				18*/

	for (i=0; i<NUM_BUTTONS; i++) {
		if (Buttons[gr_screen.res][i].button.pressed())
		{
			//Ui_window.add_XSTR(&Options_text[gr_screen.res][i]);
			options_button_pressed(i);
		}
	}

	options_sliders_update();

	// if we're in the multiplayer options tab, get the background bitmap from the options multi module
#ifndef NO_NETWORK
	if(Tab == MULTIPLAYER_TAB){
		i = options_multi_background_bitmap();
	}
	else
#endif
	{
		i = Backgrounds[gr_screen.res][Tab].bitmap;
	}

	GR_MAYBE_CLEAR_RES(i);
	if (i >= 0) {
		gr_set_bitmap(i);
		gr_bitmap(0, 0);
	} 

	Ui_window.draw();

	// NOTE : this must be done here so that any special drawing crap we do is not overwritten by the UI_WINDOW::draw() call
	// do specific processing for the multiplayer tab
	switch (Tab) {
		case MULTIPLAYER_TAB:
#if !defined(DEMO) && !defined(OEM_BUILD) // not for FS2_DEMO
#ifndef NO_NETWORK
			options_multi_do(k);
#endif
#endif
			break;

		case DETAIL_LEVELS_TAB:
			options_detail_do_frame();
			break;

		default:
			Game_skill_level = Options_sliders[gr_screen.res][OPT_SKILL_SLIDER].slider.pos;
			break;
	}

	// handle the displaying of any notification messages
	options_notify_do_frame();

	for (i=0; i<NUM_TABS; i++){
		if (Buttons[gr_screen.res][i].button.button_down()){
			break;
		}
	}

	if ((i == NUM_TABS) /*&& (Tab != MULTIPLAYER_TAB)*/ ){
		Buttons[gr_screen.res][Tab].button.draw_forced(2);
	}

	if (Tab == OPTIONS_TAB) {
		// draw correct frame for briefing voice radio buttons
		if (Briefing_voice_enabled) {
			options_force_button_frame(BRIEF_VOICE_ON, 2);
			options_force_button_frame(BRIEF_VOICE_OFF, 1);

		} else {
			options_force_button_frame(BRIEF_VOICE_OFF, 2);
			options_force_button_frame(BRIEF_VOICE_ON, 1);
		}

		if (Use_mouse_to_fly) {
			options_force_button_frame(MOUSE_ON, 2);
			options_force_button_frame(MOUSE_OFF, 1);

		} else {
			options_force_button_frame(MOUSE_OFF, 2);
			options_force_button_frame(MOUSE_ON, 1);
		}		

		int w;
		gr_get_string_size(&w, NULL, Skill_level_names(Game_skill_level));
		x = Options_skills_text_coords[gr_screen.res][OPTIONS_X_COORD];
		y = Options_skills_text_coords[gr_screen.res][OPTIONS_Y_COORD];
		gr_set_color_fast(&Color_bright_white);
		gr_string(x + (Options_skills_text_coords[gr_screen.res][OPTIONS_W_COORD] / 2) - (w/2), y, Skill_level_names(Game_skill_level));
	}

	
	//==============================================================================
	// Draw the gamma adjustment grid.
	if (Tab == OPTIONS_TAB) {

		draw_gamma_box();
		
		gr_set_color_fast(&Color_white);
		x = Options_gamma_num_coords[gr_screen.res][OPTIONS_X_COORD]; //  + Options_gamma_num_coords[gr_screen.res][OPTIONS_W_COORD] / 2 - 12;
		y = Options_gamma_num_coords[gr_screen.res][OPTIONS_Y_COORD]; // + Options_gamma_num_coords[gr_screen.res][OPTIONS_H_COORD] / 2 - gr_get_font_height() / 2;

		gr_printf(x, y, NOX("%.2f"), Freespace_gamma);
	}
	//==============================================================================

#ifndef NO_NETWORK
	// maybe blit a waveform
	if(Tab == MULTIPLAYER_TAB){
		options_multi_vox_process_waveform();
	}
#endif
	
/*  Debug code: Graphs the joystick range scaling
{
int joy_get_scaled_reading(int raw, int axn);
	int x, y;

	gr_set_color_fast(&Color_white);
	for (x=0; x<256; x+=16) {
		gr_line(x + 15, 0, x + 15, 255);
		gr_line(0, x + 15, 255, x + 15);
	}

	gr_set_color_fast(&Color_bright_white);
	for (x=0; x<256; x++) {
		y = joy_get_scaled_reading(x * 256, 0) / 512;
		gr_line(x, 128, x, 128 + y);
	}
}*/	

	// hack, hack, hack
	// to make sure the game will display the mouse over and highlighted
	// graphics right we got this ugly thing.  when the user changes
	// the tab the value is changed and checked here so the clicked on
	// tab is highlighted.  the other tabs are forced to display their
	// mouse over graphic
	for (int u=0; u<6; u++)
	{
		if ( u == current_tab ) 
			options_force_button_frame(u, 2);
		else
			options_force_button_frame(u, 1);
		
	}

	x = y = 0;
	Hotspot_region.get_mouse_pos(&x, &y);
	check_option_hotspot(x, y);
	
	gr_flip();
}


// ---------------------------------------------------------------------------------------------------------
// DETAIL LEVEL OPTIONS definitions  BEGIN
//

void options_detail_synch_sliders()
{
	Detail_slider_pos[DETAIL_DISTANCE_SLIDER] = Detail_sliders[gr_screen.res][DETAIL_DISTANCE_SLIDER].slider.pos = Detail.detail_distance;
	Detail_slider_pos[NEBULA_DETAIL_SLIDER] = Detail_sliders[gr_screen.res][NEBULA_DETAIL_SLIDER].slider.pos = Detail.nebula_detail;
	Detail_slider_pos[HARDWARE_TEXTURES_SLIDER] = Detail_sliders[gr_screen.res][HARDWARE_TEXTURES_SLIDER].slider.pos = Detail.hardware_textures;	
	Detail_slider_pos[SHARD_CULLING_SLIDER] = Detail_sliders[gr_screen.res][SHARD_CULLING_SLIDER].slider.pos = Detail.num_small_debris;
	Detail_slider_pos[SHIELD_DETAIL_SLIDER] = Detail_sliders[gr_screen.res][SHIELD_DETAIL_SLIDER].slider.pos = Detail.shield_effects;
	Detail_slider_pos[NUM_STARS_SLIDER] = Detail_sliders[gr_screen.res][NUM_STARS_SLIDER].slider.pos = Detail.num_stars;
	Detail_slider_pos[NUM_PARTICLES_SLIDER] = Detail_sliders[gr_screen.res][NUM_PARTICLES_SLIDER].slider.pos = Detail.num_particles;
	Detail_slider_pos[LIGHTING_SLIDER] = Detail_sliders[gr_screen.res][LIGHTING_SLIDER].slider.pos = Detail.lighting;
}

void options_detail_init()
{
	int i;
	options_buttons *b;

	Detail_original = Detail;

	options_load_background_and_mask(DETAIL_LEVELS_TAB);

	for (i=PLANETS_ON; i<NUM_BUTTONS; i++) {
		b = &Buttons[gr_screen.res][i];

		b->button.create(&Ui_window, "", b->x, b->y, 60, 30, b->flags & REPEAT, 1);
		// set up callback for when a mouse first goes over a button
		if (b->filename) {
			b->button.set_bmaps(b->filename);
			if ( !(b->flags & NO_MOUSE_OVER_SOUND) ) {
				b->button.set_highlight_action(common_play_highlight_sound);
			}

		} else {
			b->button.hide();
		}

		b->button.link_hotspot(b->hotspot);
	}

	// create detail level sliders	
	for ( i = 0; i < NUM_DETAIL_SLIDERS; i++ ) {
		Detail_sliders[gr_screen.res][i].slider.create(&Ui_window, Detail_sliders[gr_screen.res][i].x, Detail_sliders[gr_screen.res][i].y,
																		Detail_sliders[gr_screen.res][i].dots, Detail_sliders[gr_screen.res][i].filename,
																		Detail_sliders[gr_screen.res][i].hotspot, Detail_sliders[gr_screen.res][i].right_filename, Detail_sliders[gr_screen.res][i].right_mask, Detail_sliders[gr_screen.res][i].right_x, Detail_sliders[gr_screen.res][i].right_y,
																		Detail_sliders[gr_screen.res][i].left_filename, Detail_sliders[gr_screen.res][i].left_mask, Detail_sliders[gr_screen.res][i].left_x, Detail_sliders[gr_screen.res][i].left_y,
																		Detail_sliders[gr_screen.res][i].dot_w);
	}

	// init the actual slider positions and our internal positions
	options_detail_synch_sliders();
}

void options_detail_sliders_update()
{
	int i;

	for ( i = 0; i < NUM_DETAIL_SLIDERS; i++ ) {
		if ( Detail_sliders[gr_screen.res][i].slider.pos != Detail_slider_pos[i] ) {
			Detail_slider_pos[i] = Detail_sliders[gr_screen.res][i].slider.pos;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	}

	// set Detail based on slider positions
	Detail.detail_distance = Detail_sliders[gr_screen.res][DETAIL_DISTANCE_SLIDER].slider.pos;

	// modify nebula stuff
	Detail.nebula_detail = Detail_sliders[gr_screen.res][NEBULA_DETAIL_SLIDER].slider.pos;
	neb2_set_detail_level(Detail.nebula_detail);

	Detail.hardware_textures = Detail_sliders[gr_screen.res][HARDWARE_TEXTURES_SLIDER].slider.pos;	
	Detail.num_small_debris = Detail_sliders[gr_screen.res][SHARD_CULLING_SLIDER].slider.pos;
	Detail.shield_effects = Detail_sliders[gr_screen.res][SHIELD_DETAIL_SLIDER].slider.pos;
	Detail.num_stars = Detail_sliders[gr_screen.res][NUM_STARS_SLIDER].slider.pos;
	Detail.num_particles = Detail_sliders[gr_screen.res][NUM_PARTICLES_SLIDER].slider.pos;
	Detail.lighting = Detail_sliders[gr_screen.res][LIGHTING_SLIDER].slider.pos;
}

void options_detail_hide_stuff()
{
	int i;

	for ( i = 0; i < NUM_DETAIL_SLIDERS; i++ ) {
		Detail_sliders[gr_screen.res][i].slider.disable();
		Detail_sliders[gr_screen.res][i].slider.hide();
	}

	// this will hide text unassociated with any real control
	Detail_bogus.hide();
}

void options_detail_unhide_stuff()
{
	int i;

	for ( i = 0; i < NUM_DETAIL_SLIDERS; i++ ) {
		Detail_sliders[gr_screen.res][i].slider.enable();
		Detail_sliders[gr_screen.res][i].slider.unhide();
	}

	// this will hide text unassociated with any real control
	Detail_bogus.unhide();
}

void options_force_button_frame(int n, int frame_num)
{
	if ( !Buttons[gr_screen.res][n].button.button_down() ) {
		Buttons[gr_screen.res][n].button.draw_forced(frame_num);
	}
}

// called once per frame to set lit buttons
void options_detail_do_frame()
{
	options_detail_sliders_update();	

	// force on/off buttons to draw their correct setting

	if ( Detail.targetview_model ) {
		options_force_button_frame(HUD_TARGETVIEW_RENDER_ON, 2);
		options_force_button_frame(HUD_TARGETVIEW_RENDER_OFF, 0);
	} else {
		options_force_button_frame(HUD_TARGETVIEW_RENDER_OFF, 2);
		options_force_button_frame(HUD_TARGETVIEW_RENDER_ON, 0);
	}

	if ( Detail.planets_suns == 1 ) {
		options_force_button_frame(PLANETS_ON, 2);
		options_force_button_frame(PLANETS_OFF, 0);
	} else {
		options_force_button_frame(PLANETS_OFF, 2);
		options_force_button_frame(PLANETS_ON, 0);
	}

	if ( Detail.weapon_extras) {
		options_force_button_frame(WEAPON_EXTRAS_ON, 2);
		options_force_button_frame(WEAPON_EXTRAS_OFF, 0);
	} else {
		options_force_button_frame(WEAPON_EXTRAS_OFF, 2);
		options_force_button_frame(WEAPON_EXTRAS_ON, 0);
	}	

	int current_detail;

	if ( Detail.setting >= 0 ) {
		current_detail = current_detail_level();
		Detail.setting = current_detail;
	} else {
		current_detail = -1;
	}

	options_force_button_frame(LOW_DETAIL_N, 1);
	options_force_button_frame(MEDIUM_DETAIL_N, 1);
	options_force_button_frame(HIGH_DETAIL_N, 1);
	options_force_button_frame(VERY_HIGH_DETAIL_N, 1);
	options_force_button_frame(CUSTOM_DETAIL_N, 1);

	switch ( current_detail ) {
	case -1:
		options_force_button_frame(CUSTOM_DETAIL_N, 2);
		break;
	case 0:
		options_force_button_frame(LOW_DETAIL_N, 2);
		break;
	case 1:
		options_force_button_frame(MEDIUM_DETAIL_N, 2);
		break;
	case 2:
		options_force_button_frame(HIGH_DETAIL_N, 2);
		break;
	case 3:
		options_force_button_frame(VERY_HIGH_DETAIL_N, 2);
		break;
	}
}

// Set all the detail settings to a predefined level
void options_detail_set_level(int level)
{
	detail_level_set(level);
	options_detail_synch_sliders();
}

//
// DETAIL LEVEL tab definitions END
// ---------------------------------------------------------------------------------------------------------


