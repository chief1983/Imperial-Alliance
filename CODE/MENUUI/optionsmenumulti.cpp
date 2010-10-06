/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/OptionsMenuMulti.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:41 $
 * $Author: Spearhawk $
 *
 * $Log: optionsmenumulti.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:46:39  Darkhill
 * no message
 *
 * Revision 2.2  2003/09/23 02:42:53  Kazan
 * ##KAZAN## - FS2NetD Support! (FS2 Open PXO) -- Game Server Listing, and mission validation completed - stats storing to come - needs fs2open_pxo.cfg file [VP-able]
 *
 * Revision 2.1  2002/08/01 01:41:06  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.3  2002/05/10 06:08:08  mharris
 * Porting... added ifndef NO_SOUND
 *
 * Revision 1.2  2002/05/04 04:52:22  mharris
 * 1st draft at porting
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 *  
 * 
 * 21    10/25/99 5:47p Jefff
 * reassigned some xstr ids
 * 
 * 20    8/02/99 2:44p Dave
 * Disable IPX for demo build.
 * 
 * 19    7/15/99 7:15p Jefff
 * Added various sound FX
 * 
 * 18    7/15/99 9:20a Andsager
 * FS2_DEMO initial checkin
 * 
 * 17    6/25/99 11:59a Dave
 * Multi options screen.
 * 
 * 16    6/22/99 7:03p Dave
 * New detail options screen.
 * 
 * 15    4/25/99 3:02p Dave
 * Build defines for the E3 build.
 * 
 * 14    2/25/99 4:19p Dave
 * Added multiplayer_beta defines. Added cd_check define. Fixed a few
 * release build warnings. Added more data to the squad war request and
 * response packets.
 * 
 * 13    2/19/99 2:55p Dave
 * Temporary checking to report the winner of a squad war match.
 * 
 * 12    2/17/99 2:10p Dave
 * First full run of squad war. All freespace and tracker side stuff
 * works.
 * 
 * 11    2/12/99 6:16p Dave
 * Pre-mission Squad War code is 95% done.
 * 
 * 10    2/05/99 7:22p Neilk
 * Fixed gamma bitmap and converted coordinates for multiple resolutions
 * 
 * 9     2/02/99 11:36a Dave
 * Removed obsolete data reference.
 * 
 * 8     12/18/98 1:13a Dave
 * Rough 1024x768 support for Direct3D. Proper detection and usage through
 * the launcher.
 * 
 * 7     11/20/98 11:16a Dave
 * Fixed up IPX support a bit. Making sure that switching modes and
 * loading/saving pilot files maintains proper state.
 * 
 * 6     11/19/98 4:19p Dave
 * Put IPX sockets back in psnet. Consolidated all multiplayer config
 * files into one.
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
 * 27    7/08/98 11:56a Dave
 * Changed mic problem error message.
 * 
 * 26    6/12/98 7:13p Hoffoss
 * Fixed options screen problem where it wasn't showing tooltips.
 * 
 * 25    6/09/98 10:31a Hoffoss
 * Created index numbers for all xstr() references.  Any new xstr() stuff
 * added from here on out should be added to the end if the list.  The
 * current list count can be found in FreeSpace.cpp (search for
 * XSTR_SIZE).
 * 
 * 24    6/01/98 11:43a John
 * JAS & MK:  Classified all strings for localization.
 * 
 * 23    5/21/98 9:45p Dave
 * Lengthened tracker polling times. Put in initial support for PXO
 * servers with channel filters. Fixed several small UI bugs.
 * 
 * 22    5/20/98 2:24a Dave
 * Fixed server side voice muting. Tweaked multi debrief/endgame
 * sequencing a bit. Much friendlier for stats tossing/accepting now.
 * 
 * 21    5/19/98 1:35a Dave
 * Tweaked pxo interface. Added rankings url to pxo.cfg. Make netplayer
 * local options update dynamically in netgames.
 * 
 * 20    5/18/98 12:03p Frank
 * Make sure network changes made in options screen are loaded into any
 * current Net_player as well as the Player.
 * 
 * 19    5/11/98 11:39p Dave
 * Stuff.
 * 
 * 18    5/10/98 7:05p Dave
 * Fix endgame sequencing ESC key. Changed how host options warning popups
 * are done. Fixed pause/message scrollback/options screen problems in mp.
 * Make sure observer HUD doesn't try to lock weapons.
 * 
 * 17    5/08/98 7:08p Dave
 * Lots of UI tweaking.
 * 
 * 16    5/08/98 5:04p Dave
 * Go to the join game screen when quitting multiplayer. Fixed mission
 * text chat bugs. Put mission type symbols on the create game list.
 * Started updating standalone gui controls.
 * 
 * 15    5/07/98 12:57a Dave
 * Fixed incorrect calls to free() from stats code. Put in new artwork for
 * debrief and host options screens. Another modification to scoring
 * system for secondary weapons.
 * 
 * 14    5/06/98 8:06p Dave
 * Made standalone reset properly under weird conditions. Tweak
 * optionsmulti screen. Upped MAX_WEAPONS to 350. Put in new launch
 * countdown anim. Minro ui fixes/tweaks.
 * 
 * 13    5/02/98 5:38p Dave
 * Put in new tracker API code. Put in ship information on mp team select
 * screen. Make standalone server name permanent. Fixed standalone server
 * text messages.
 * 
 * 12    4/30/98 5:24p Adam
 * JAS: Made multi config specify path.
 * 
 * 11    4/28/98 5:13p Dave
 * Remove references to old MT API
 * 
 * 10    4/25/98 2:00p Dave
 * Installed a bunch of multiplayer context help screens. Reworked ingame
 * join ship select screen. Fix places where network timestamps get hosed.
 * 
 * 9     4/22/98 4:09p John
 * String externalization
 * 
 * 8     4/22/98 12:34a Dave
 * Make sure hud config and control config buttons draw properly in all
 * tab modes. Make small tab buttons light up correctly in multi options
 * screen.
 * 
 * 7     4/21/98 4:44p Dave
 * Implement Vasudan ships in multiplayer. Added a debug function to bash
 * player rank. Fixed a few rtvoice buffer overrun problems. Fixed ui
 * problem in options screen. 
 * 
 * 6     4/20/98 6:04p Dave
 * Implement multidata cache flushing and xferring mission files to
 * multidata. Make sure observers can't change hud config. Fix pilot image
 * viewing in popup. Put in game status field. Tweaked multi options. 
 * 
 * 5     4/18/98 12:45p Dave
 * Aesthetic changes to multi options screen. Put in missing exit button.
 * oops.
 * 
 * 4     4/17/98 6:33p Dave
 * Finished first run of the screen. About time.
 * 
 * 3     4/17/98 5:27p Dave
 * More work on the multi options screen. Fixed many minor ui todo bugs.
 * 
 * 2     4/17/98 12:42a Dave
 * Worked on voice tab. Need to implement mic testing and player muting
 * list thingie.
 * 
 * 1     4/16/98 11:39p Dave
 *  
 * 
 * $NoKeywords: $
 */

#include "ui/ui.h"
#include "bmpman/bmpman.h"
#include "cfile/cfile.h"
#include "io/key.h"
#include "graphics/font.h"
#include "gamesnd/gamesnd.h"
#include "freespace2/freespace.h"
#include "playerman/player.h"
#include "network/multi.h"
#include "network/multi_voice.h"
#include "sound/rtvoice.h"
#include "io/mouse.h"
#include "menuui/optionsmenu.h"
#include "menuui/optionsmenumulti.h"
#include "popup/popup.h"
#include "osapi/osregistry.h"
#include "globalincs/alphacolors.h"
#include "io/timer.h"
#include "parse/parselo.h"

#ifndef NO_SOUND
 #include "sound/ds.h"
#endif


// general data section ------------------------------------------------
UI_WINDOW *Om_window = NULL;

static char* Om_background_0_fname[GR_NUM_RESOLUTIONS] = {
	"OptionsMultiGen",			// GR_640
	"2_OptionsMultiGen"			// GR_1024
};

static char* Om_background_0_mask_fname[GR_NUM_RESOLUTIONS] = {
	"OptionsMultiGen-M",			// GR_640
	"2_OptionsMultiGen-M"		// GR_1024
};

static char* Om_background_1_fname[GR_NUM_RESOLUTIONS] = {
	"OptionsMultiVox",			// GR_640
	"2_OptionsMultiVox"			// GR_1024
};

static char* Om_background_1_mask_fname[GR_NUM_RESOLUTIONS] = {
	"OptionsMultiVox-M",			// GR_640
	"2_OptionsMultiVox-M"		// GR_1024
};

int Om_background_0 = -1;
int Om_mask_0		  = -1;

int Om_background_1 = -1;
int Om_mask_1       = -1;

// screen modes
#define OM_MODE_NONE									-1		// no mode (unintialized)
#define OM_MODE_GENERAL								0		// general tab
#define OM_MODE_VOX									1		// voice tab
int Om_mode = OM_MODE_NONE;

// notification stuff
#define OM_NOTIFY_TIME								8000
#define OM_NOTIFY_Y									430
#define OM_NOTIFY_Y2									440
int Om_notify_stamp = -1;
char Om_notify_string[255];

// load all background bitmaps
void options_multi_load_bmaps();

// unload all the background bitmaps
void options_multi_unload_bmaps();

// add a notification message
void options_multi_add_notify(char *str);

// process and blit any notification messages
void options_multi_notify_process();


// protocol options section -------------------------------------------
#define OM_PRO_NUM_BUTTONS								10

#define OM_PRO_TCP										0
#define OM_PRO_IPX										1
#define OM_PRO_SCROLL_IP_UP							2
#define OM_PRO_SCROLL_IP_DOWN							3
#define OM_PRO_ADD_IP									4
#define OM_PRO_DELETE_IP								5
#define OM_PRO_LOCAL_BROADCAST						6
#define OM_PRO_VMT										7
#define OM_PRO_VOX_TAB									8
#define OM_PRO_GEN_TAB									9

ui_button_info Om_pro_buttons[GR_NUM_RESOLUTIONS][OM_PRO_NUM_BUTTONS] = {
	{ // GR_640
		ui_button_info("OMuB_07",	45, 42,	-1,	-1,	7),
		ui_button_info("OMuB_08",	45, 68,	-1,	-1,	8),
		ui_button_info("OMuB_09",	50,110,	-1,	-1,	9),
		ui_button_info("OMuB_10",	50,138,	-1,	-1,	10),
		ui_button_info("OMuB_11",	80,185,	-1,	-1,	11),
		ui_button_info("OMuB_12",	104,185,	-1,	-1,	12),
		ui_button_info("OMuB_13",	45,233,	-1,	-1,	13),
		ui_button_info("OMuB_14",	57,265,	-1,	-1,	14),
		ui_button_info("OMuB_15",	570, 42,	-1,	-1,	15),
		ui_button_info("OMuB_16",	570, 67,	-1,	-1,	16),
	},
	{ // GR_1024
		ui_button_info("2_OMuB_07",	12,	105,	-1,	-1,	7),
		ui_button_info("2_OMuB_08",	12,	134,	-1,	-1,	8),
		ui_button_info("2_OMuB_09",	2,		198,	-1,	-1,	9),
		ui_button_info("2_OMuB_10",	2,		252,	-1,	-1,	10),
		ui_button_info("2_OMuB_11",	32,	332,	-1,	-1,	11),
		ui_button_info("2_OMuB_12",	103,	332,	-1,	-1,	12),
		ui_button_info("2_OMuB_13",	14,	402,	-1,	-1,	13),
		ui_button_info("2_OMuB_14",	14,	452,	-1,	-1,	14),
		ui_button_info("2_OMuB_15",	976,	85,	-1,	-1,	15),
		ui_button_info("2_OMuB_16",	976,	114,	-1,	-1,	16),
	}
};

UI_GADGET Om_pro_bogus;

// test
#define OM_PRO_NUM_TEXT		6
UI_XSTR Om_pro_text[GR_NUM_RESOLUTIONS][OM_PRO_NUM_TEXT] = {
	{ // GR_640
		{ "TCP",				1378,	76, 49,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_TCP].button },
		{ "IPX",				1379,	76, 75,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_IPX].button },
		{ "IP Address",	1380,	81,111,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
		//{ "add",				1381,	22,	235,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_ADD_IP].button },
		//{ "rem.",			1382,	68,	235,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_DELETE_IP].button },
		{ "Broadcast Locally",	1397,	76,239,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_LOCAL_BROADCAST].button },	
//		{ "PXO",				1383,	88,272,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_VMT].button },
//		{ "Login",			1384,	222,281,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
//		{ "Password",		1385,	222,308,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
//		{ "Squadron",		1386,	222,335,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
		{ "Voice",			1528,	525, 49,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_VOX_TAB].button },
		{ "General",		1388,	508, 75,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[0][OM_PRO_GEN_TAB].button },	
	},
	{ // GR_1024
		{ "TCP",				1378,	61,	113,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_TCP].button },
		{ "IPX",				1379,	61,	141,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_IPX].button },
		{ "IP Address",	1380,	47,	206,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
		//{ "add",				1381,	36,	375,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_ADD_IP].button },
		//{ "rem.",			1382,	109,	375,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_DELETE_IP].button },
		{ "Broadcast Locally",	1397,	68,	417,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_LOCAL_BROADCAST].button },	
	//	{ "PXO",				1383,	68,	467,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_VMT].button },
	//	{ "Login",			1384,	23,	495,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
	//	{ "Password",		1385,	23,	538,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
	//	{ "Squadron",		1386,	23,	582,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_bogus },
		{ "Voice",			1528,	921,	96,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_VOX_TAB].button },
		{ "General",		1388,	902,	123,	UI_XSTR_COLOR_GREEN, -1, &Om_pro_buttons[1][OM_PRO_GEN_TAB].button },	
	}
};

// defines for the tracker input boxes
int Om_tracker_login_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		67,294, 226, -1//19, 322, 226, -1		// GR_640
	},
	{
		31, 518, 361, -1		// GR_1024
	}
};
int Om_tracker_passwd_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		67,321, 226, -1		// GR_640
	},
	{
		31, 562, 361, -1		// GR_1024
	}
};
int Om_tracker_squad_name_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		67,349, 226, -1		// GR_640
	},
	{
		31, 607, 361, -1		// GR_1024
	}
};

// protocol section tracker login input box
UI_INPUTBOX Om_tracker_login;

// protocol section tracker passwd input box
UI_INPUTBOX Om_tracker_passwd;

// pxo squad name/password
UI_INPUTBOX Om_tracker_squad_name;

#define TRACKER_FOCUS_NONE			0
#define TRACKER_FOCUS_LOGIN		1
#define TRACKER_FOCUS_PASSWORD	2
#define TRACKER_FOCUS_SQUADRON	3
static int Om_tracker_focus = 0;

// ip address list vars
#define IP_STRING_LEN								255
#define MAX_IP_ADDRS									100

#define IP_CONFIG_FNAME								NOX("Tcp.cfg")

#define IP_EMPTY_STRING								""

int Ip_list_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		81, 130, 227, 67		// GR_640
	},
	{
		46, 220, 364, 106		// GR_1024
	}
};


int Ip_list_max_display[GR_NUM_RESOLUTIONS] = {
	5,
	5
};

static int Ip_input_coords[GR_NUM_RESOLUTIONS][4] = {
	{
		81,120, 140, -1//109, 128, 140, -1		// GR_640
	},
	{
		132, 206, 261, -1		// GR_640
	}
};

int Om_input_mode = 0;
int Om_ip_start;												// index of the first element to be displayed in the list box
int Om_ip_selected;		                           // the selected default IP address
int Om_ip_disp_count;	                           // how many items are currently being displayed
int Om_num_ips;												// # of ip addresses we have
char Om_ip_addrs[MAX_IP_ADDRS][IP_STRING_LEN];		// the ip addresses themselves
UI_BUTTON Om_ip_button;										// button for detecting clicks on the ip address list
UI_INPUTBOX Om_ip_input;									// input box for adding new ip addresses

// setting vars
int Om_local_broadcast;										// whether the player has local broadcast selected or not
int Om_tracker_flag;											// if the guy has the tracker selected
int Om_protocol;												// protocol in use

// load all the controls for the protocol section
void options_multi_load_protocol_controls();

// disable/hide all the controls for the protocol section
void options_multi_disable_protocol_controls();

// enable/unhide all the controls for the protocol section
void options_multi_enable_protocol_controls();

// intialize the protocol section vars
void options_multi_init_protocol_vars();

// do frame for the protocol section
void options_multi_protocol_do(int key);

// if the accept button was hit
void options_multi_protocol_accept();

// check for button presses
void options_multi_protocol_check_buttons();

// if a button was pressed
void options_multi_protocol_button_pressed(int n);

// load the ip address file
void options_multi_protocol_load_ip_file();

// save the ip address file
void options_multi_protocol_save_ip_file();

// draw the list of ip addresses
void options_multi_protocol_display_ips();

// scroll the list of ip addresses down
void options_multi_protocol_scroll_ip_down();

// scroll the list of ip addresses up
void options_multi_protocol_scroll_ip_up();

// check the ip list to see if the user has selected a new item
void options_multi_protocol_check_ip_list();

// delete the currently selected ip if any
void options_multi_protocol_delete_ip();

// attempt to add the currently entered ip address
void options_multi_protocol_add_current_ip();


// general options tab section -------------------------------------------
#define OM_GEN_NUM_BUTTONS								10

#define OM_GEN_OBJ_LOW									0
#define OM_GEN_OBJ_MED									1
#define OM_GEN_OBJ_HIGH									2
#define OM_GEN_OBJ_LAN									3
#define OM_GEN_PIX_YES									4
#define OM_GEN_PIX_NO									5
#define OM_GEN_XFER_MULTIDATA_YES					6
#define OM_GEN_XFER_MULTIDATA_NO						7
#define OM_GEN_FLUSH_NO									8
#define OM_GEN_FLUSH_YES								9

ui_button_info Om_gen_buttons[GR_NUM_RESOLUTIONS][OM_GEN_NUM_BUTTONS] = {
	{ // GR_640
		ui_button_info("OGB_17",	570,114,	-1,	-1,	17),
		ui_button_info("OGB_18",	570,136,	-1,	-1,	18),
		ui_button_info("OGB_19",	570,158,	-1,	-1,	19),
		ui_button_info("OGB_20",	570,180,	-1,	-1,	20),
		ui_button_info("OGB_21",	307, 56,	-1,	-1,	21),
		ui_button_info("OGB_22",	352, 56,	-1,	-1,	22),
		ui_button_info("OGB_23",	570,222,	-1,	-1,	23),
		ui_button_info("OGB_24",	570,244,	-1,	-1,	24),
		ui_button_info("OGB_25",	570,283,	-1,	-1,	25),
		ui_button_info("OGB_26",	570,305,	-1,	-1,	26),
	},
	{ // GR_1024
		ui_button_info("2_OGB_17",	957,	188,	-1,	-1,	17),
		ui_button_info("2_OGB_18",	957,	223,	-1,	-1,	18),
		ui_button_info("2_OGB_19",	957,	258,	-1,	-1,	19),
		ui_button_info("2_OGB_20",	957,	293,	-1,	-1,	20),
		ui_button_info("2_OGB_21",	879,	366,	-1,	-1,	21),
		ui_button_info("2_OGB_22",	957,	366,	-1,	-1,	22),
		ui_button_info("2_OGB_23",	957,	457,	-1,	-1,	23),
		ui_button_info("2_OGB_24",	957,	491,	-1,	-1,	24),
		ui_button_info("2_OGB_25",	957,	555,	-1,	-1,	25),
		ui_button_info("2_OGB_26",	957,	589,	-1,	-1,	26),
	}
};

UI_GADGET Om_gen_bogus;

// text
#define OM_GEN_NUM_TEXT					14
UI_XSTR Om_gen_text[GR_NUM_RESOLUTIONS][OM_GEN_NUM_TEXT] = {
	{ // GR_640
		{ "Object Update",		1391,		487,100,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Low",				1160,		535,121,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_OBJ_LOW].button },
		{ "Medium",				1161,		516,143,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_OBJ_MED].button },		
		{ "High",				1162,		533,165,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_OBJ_HIGH].button },		
		{ "Lan",					1392,	538,187,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_OBJ_LAN].button },		
		{ "Pilot / Squad Images",	1393,	148, 63,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Yes",					1394,	305, 80,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_PIX_YES].button },		
		{ "No",					1395,		354, 80,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_PIX_NO].button },		
		{ "Transfer Missions",		1396,	464,208,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "/multidata",			1397,		490,229,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_XFER_MULTIDATA_YES].button },		
		{ "/missions",			1398,		501,251,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_XFER_MULTIDATA_NO].button },		
		{ "Flush Cache",		1399,		502,269,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Never",				1400,		523,290,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_FLUSH_NO].button },		
		{ "Before Game",		1401,		475,312,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[0][OM_GEN_FLUSH_YES].button },		
	},
	{ // GR_1024
		{ "Object Update",	1391,		818,	166,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Low",					1160,		913,	204,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_OBJ_LOW].button },
		{ "Medium",				1161,		892,	239,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_OBJ_MED].button },		
		{ "High",				1162,		909,	274,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_OBJ_HIGH].button },		
		{ "Lan",					1392,		916,	310,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_OBJ_LAN].button },		
		{ "Pilot / Squad Images",	1393,		821,	345,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Yes",					1394,		887,	411,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_PIX_YES].button },		
		{ "No",					1395,		966,	411,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_PIX_NO].button },		
		{ "Transfer Missions",		1396,		844,	435,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "/multidata",		1397,		858,	468,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_XFER_MULTIDATA_YES].button },		
		{ "/missions",			1398,		870,	503,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_XFER_MULTIDATA_NO].button },		
		{ "Flush Cache",		1399,		886,	533,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_bogus },		
		{ "Never",				1400,		897,	568,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_FLUSH_NO].button },		
		{ "Before Game",		1401,		849,	603,	UI_XSTR_COLOR_GREEN,	-1,	&Om_gen_buttons[1][OM_GEN_FLUSH_YES].button },		
	}
};

// setting vars
int Om_gen_obj_update;								// object update level
int Om_gen_pix;										// accept pilot pix or not
int Om_gen_xfer_multidata;							// xfer missions to multidata or not
int Om_gen_flush_cache;								// flush multidata directory before every game

// load all the general tab controls
void options_multi_load_gen_controls();

// disable/hide all the general tab controls
void options_multi_disable_gen_controls();

// enable/unhide all the general tab controls
void options_multi_enable_gen_controls();

// initialize the general tab vars
void options_multi_init_gen_vars();

// accept function for the general tab
void options_multi_gen_accept();

// do frame for the general tab
void options_multi_gen_do();

// check for button presses
void options_multi_gen_check_buttons();

// a button was pressed
void options_multi_gen_button_pressed(int n);


// voice options tab section -------------------------------------------
#define OM_VOX_NUM_BUTTONS								6

#define OM_VOX_VOICE_TEST								0
#define OM_VOX_VOICE_YES								1
#define OM_VOX_VOICE_NO									2
#define OM_VOX_PLIST_UP									3
#define OM_VOX_PLIST_DOWN								4
#define OM_VOX_VOICE_MUTE								5

UI_GADGET Om_vox_bogus;

ui_button_info Om_vox_buttons[GR_NUM_RESOLUTIONS][OM_VOX_NUM_BUTTONS] = {
	{ // GR_640
		ui_button_info("OVB_17",	556,	125,	-1,	-1,	17),
		ui_button_info("OVB_19",	307,	56,	-1,	-1,	19),
		ui_button_info("OVB_20",	352,	56,	-1,	-1,	20),
		ui_button_info("OVB_21",	564,	228,	-1,	-1,	21),
		ui_button_info("OVB_22",	564,	256,	-1,	-1,	22),
		ui_button_info("OVB_23",	564,	318,	-1,	-1,	23),
	},
	{ // GR_640
		ui_button_info("2_OVB_17",	900,	189,	-1,	-1,	17),
		ui_button_info("2_OVB_19",	882,	333,	-1,	-1,	19),
		ui_button_info("2_OVB_20",	959,	333,	-1,	-1,	20),
		ui_button_info("2_OVB_21",	983,	410,	-1,	-1,	21),
		ui_button_info("2_OVB_22",	983,	464,	-1,	-1,	22),
		ui_button_info("2_OVB_23",	959,	566,	-1,	-1,	23),
	}
};

// text
#define OM_VOX_NUM_TEXT					6
UI_XSTR Om_vox_text[GR_NUM_RESOLUTIONS][OM_VOX_NUM_TEXT] = {
	{ // GR_640
		{ "Mic test",			1389,		 494,132,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[0][OM_VOX_VOICE_TEST].button },
		{ "Voice Quality",		1531,		392,161,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_bogus },
		{ "Voice Transmission",	1530,		166,63,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_bogus },
		{ "On",					1285,		330,	63,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[0][OM_VOX_VOICE_YES].button },
		{ "Off",				1286,		375,	63,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[0][OM_VOX_VOICE_NO].button },
		{ "Mute",				1390,		525,324,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[0][OM_VOX_VOICE_MUTE].button },
	},
	{ // GR_1024
		{ "mic test",				1389,		908,	166,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[1][OM_VOX_VOICE_TEST].button },
		{ "Voice Quality",		1531,		703,	239,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_bogus },
		{ "Voice Transmission",	1530,		783,	310,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_bogus },
		{ "On",						1285,		890,	373,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[1][OM_VOX_VOICE_YES].button },
		{ "Off",						1286,		967,	373,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[1][OM_VOX_VOICE_NO].button },
		{ "Mute",					1390,		950,	609,	UI_XSTR_COLOR_GREEN,	-1, &Om_vox_buttons[1][OM_VOX_VOICE_MUTE].button },
	}
};

#define NUM_OM_VOX_SLIDERS				1
#define OM_VOX_QOS_SLIDER				0

op_sliders Om_vox_sliders[GR_NUM_RESOLUTIONS][NUM_OM_VOX_SLIDERS] = {
	{ // GR_640				
		op_sliders("OVB_18",	390,	175,	-1,	-1,	18,	20,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// voice QOS
	},	
	{ // GR_1024				
		op_sliders("2_OVB_18",	686,	259,	-1,	-1,	18,	20,	10, NULL, -1, -1, -1, NULL, -1, -1, -1),	// voice QOS
	}
};

// player list area
int Om_vox_plist_coords[GR_NUM_RESOLUTIONS][4] = {
	{	// GR_640
		339, 321, 216, 88
	},
	{	// GR_1024
		604, 432, 371, 127
	}
};
int Om_vox_plist_max_display[GR_NUM_RESOLUTIONS] = {
	6,
	6
};

int Om_vox_plist_start;
UI_BUTTON Om_vox_plist_button;

// voice test buffer
#define OM_VOX_BUF_SIZE				(1<<12)
#define OM_VOX_COMP_SIZE			((1<<15) + (1<<14))

#define OM_VOX_WAVE_Y				240
#define OM_VOX_WAVE_WIDTH			300

#define OM_VOX_DROP_ICON_X			100
#define OM_VOX_DROP_ICON_Y			100

#define OM_VOX_RECORD_INT			175

unsigned char Om_vox_voice_buffer[OM_VOX_BUF_SIZE];
int Om_vox_voice_buffer_size = -1;

unsigned char Om_vox_comp_buffer[OM_VOX_COMP_SIZE];
int Om_vox_voice_comp_size = -1;

int Om_vox_playback_handle;

// status of any test voice recording
#define OM_VOX_TEST_NONE					-1
#define OM_VOX_TEST_RECORDING				0
#define OM_VOX_TEST_PLAYBACK				1
int Om_vox_test_status = OM_VOX_TEST_NONE;

// setting vars
int Om_vox_accept_voice;

// simple list of players we are looking through
net_player *Om_vox_players[MAX_PLAYERS];

// selected player
net_player *Om_vox_player_select;

// mute or don't mute for each player
int Om_vox_player_flags[MAX_PLAYERS];

// the # of players
int Om_vox_num_players;

// load all the voice tab controls
void options_multi_load_vox_controls();

// disable/hide all the voice tab controls
void options_multi_disable_vox_controls();

// enable/unhide all the voice tab controls
void options_multi_enable_vox_controls();

// initialize the voice tab vars
void options_multi_init_vox_vars();

// accept function for the voice tab
void options_multi_vox_accept();

// do frame for the voice tab
void options_multi_vox_do();

// check for button presses
void options_multi_vox_check_buttons();

// a button was pressed
void options_multi_vox_button_pressed(int n);

// process/display the player list
void options_multi_vox_process_player_list();

// scroll the player list down
void options_multi_vox_plist_scroll_down();

// scroll the player list up
void options_multi_vox_plist_scroll_up();

// get the index into the player list of the passed netplayer
int options_multi_vox_plist_get(net_player *pl);


// general data section ------------------------------------------------

// load all background bitmaps
void options_multi_load_bmaps()
{
	// load both background bitmaps
	Om_background_0 = bm_load(Om_background_0_fname[gr_screen.res]);
	if(Om_background_0 == -1){
		nprintf(("Network","Error loading options background %s\n",Om_background_0_fname[gr_screen.res]));
	}

	Om_background_1 = bm_load(Om_background_1_fname[gr_screen.res]);
	if(Om_background_1 == -1){
		nprintf(("Network","Error loading options background %s\n",Om_background_1_fname[gr_screen.res]));
	}

	// load in both mask bitmaps
	Om_mask_0 = bm_load(Om_background_0_mask_fname[gr_screen.res]);
	if(Om_mask_0 == -1){
		nprintf(("Network","Error loading options background mask %s\n",Om_background_0_mask_fname[gr_screen.res]));
	}

	Om_mask_1 = bm_load(Om_background_1_mask_fname[gr_screen.res]);
	if(Om_mask_1 == -1){
		nprintf(("Network","Error loading options background mask %s\n",Om_background_1_mask_fname[gr_screen.res]));
	}
}

// unload all the background bitmaps
void options_multi_unload_bmaps()
{
	// unload all background bitmaps
	if(Om_background_0 != -1){
		bm_release(Om_background_0);
		Om_background_0 = -1;
	} 
	if(Om_background_1 != -1){
		bm_release(Om_background_1);
		Om_background_1 = -1;
	}

	// unload all mask bitmaps
	if(Om_mask_0 != -1){
		bm_release(Om_mask_0);
		Om_mask_0 = -1;
	}
	if(Om_mask_1 != -1){
		bm_release(Om_mask_1);
		Om_mask_1 = -1;
	}
}

// add a notification message
void options_multi_add_notify(char *str)
{
	// copy the string
	memset(Om_notify_string,0,255);
	if(str != NULL){		
		strcpy(Om_notify_string,str);
	} 		

	// set the timestamp
	Om_notify_stamp = timestamp(OM_NOTIFY_TIME);
}

// process and blit any notification messages
void options_multi_notify_process()
{
	int w;
	char *p_str[3];
	int n_chars[3];
	char line[255];
	int line_count;
	int y_start;
	int idx;
	
	// if there is no timestamp, do nothing
	if(Om_notify_stamp == -1){
		return;
	}

	// otherwise, if it has elapsed, unset it
	if(timestamp_elapsed(Om_notify_stamp)){
		Om_notify_stamp = -1;
		return;
	}

	// otherwise display the string
	line_count = split_str(Om_notify_string, 600, n_chars, p_str, 3);	
	y_start = OM_NOTIFY_Y;
	gr_set_color_fast(&Color_bright);
	for(idx=0;idx<line_count;idx++){
		memset(line, 0, 255);
		strncpy(line, p_str[idx], n_chars[idx]);
				
		gr_get_string_size(&w,NULL,line);
		gr_string((600 - w)/2,y_start,line);

		y_start += 10;
	}	
}


// protocol section --------------------------------------------------------

// load all the controls for the protocol section
void options_multi_load_protocol_controls()
{
	int idx;
	
	Assert(Om_window != NULL);

	// instantiate all the buttons
	for(idx=0; idx<OM_PRO_NUM_BUTTONS; idx++){
		// create the object
		Om_pro_buttons[gr_screen.res][idx].button.create(Om_window, "", Om_pro_buttons[gr_screen.res][idx].x, Om_pro_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);

		// set the sound to play when highlighted
		Om_pro_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Om_pro_buttons[gr_screen.res][idx].button.set_bmaps(Om_pro_buttons[gr_screen.res][idx].filename);

		// set the hotspot
		Om_pro_buttons[gr_screen.res][idx].button.link_hotspot(Om_pro_buttons[gr_screen.res][idx].hotspot);
	}

	// text
	for(idx=0; idx<OM_PRO_NUM_TEXT; idx++){
		Om_window->add_XSTR(&Om_pro_text[gr_screen.res][idx]);
	}

	// create the tracker input boxes	
	Om_tracker_login.create(Om_window, Om_tracker_login_coords[gr_screen.res][0], Om_tracker_login_coords[gr_screen.res][1], Om_tracker_login_coords[gr_screen.res][2], LOGIN_LEN - 1, Multi_tracker_login, UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_ESC_CLR | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_NO_BACK);
	Om_tracker_passwd.create(Om_window, Om_tracker_passwd_coords[gr_screen.res][0], Om_tracker_passwd_coords[gr_screen.res][1], Om_tracker_passwd_coords[gr_screen.res][2], LOGIN_LEN - 1, Multi_tracker_passwd, UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_ESC_CLR | UI_INPUTBOX_FLAG_PASSWD | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_NO_BACK);
	Om_tracker_squad_name.create(Om_window, Om_tracker_squad_name_coords[gr_screen.res][0], Om_tracker_squad_name_coords[gr_screen.res][1], Om_tracker_squad_name_coords[gr_screen.res][2], LOGIN_LEN - 1, Multi_tracker_squad_name, UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_ESC_CLR | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_NO_BACK);

	// create the invisible button for checking for clicks on the ip address list
	Om_ip_button.create(Om_window, "", Ip_list_coords[gr_screen.res][0], Ip_list_coords[gr_screen.res][1], Ip_list_coords[gr_screen.res][2], Ip_list_coords[gr_screen.res][3], 0, 1);
	Om_ip_button.hide();

	// create the new ip address input box	
	Om_ip_input.create(Om_window, Ip_input_coords[gr_screen.res][0], Ip_input_coords[gr_screen.res][1], Ip_input_coords[gr_screen.res][2], IP_STRING_LEN, IP_EMPTY_STRING, UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_ESC_CLR | UI_INPUTBOX_FLAG_KEYTHRU);
	Om_ip_input.hide();
	Om_ip_input.disable();
	
	// disable IPX button in demo
#ifdef FS2_DEMO
	Om_pro_buttons[gr_screen.res][OM_PRO_IPX].button.disable();
	Om_pro_buttons[gr_screen.res][OM_PRO_IPX].button.hide();
#endif

	// bogus control
	Om_pro_bogus.base_create(Om_window, UI_KIND_ICON, 0, 0, 0, 0);
}

// disable/hide all the controls for the protocol section
void options_multi_disable_protocol_controls()
{
	int idx;
	
	// hide and disable all the protocol buttons
	for(idx=0;idx<OM_PRO_NUM_BUTTONS;idx++){
		// hide the button
		Om_pro_buttons[gr_screen.res][idx].button.hide();

		// disable the button
		Om_pro_buttons[gr_screen.res][idx].button.disable();
	}

	// hide and disable the tracker input boxes
	Om_tracker_login.hide();
	Om_tracker_login.disable();
	Om_tracker_passwd.hide();
	Om_tracker_passwd.disable();
	Om_tracker_squad_name.hide();
	Om_tracker_squad_name.disable();

	// disable the click detection button
	Om_ip_button.disable();

	// disable and hide the ip address inputbox
	Om_ip_input.hide();
	Om_ip_input.disable();

	// undo input mode if necessary
	Om_input_mode = 0;

	// bogus control
	Om_pro_bogus.hide();
	Om_pro_bogus.disable();
}

// enable/unhide all the controls for the protocol section
void options_multi_enable_protocol_controls()
{
	int idx;
	
	// unhide and enable all the protocol buttons
	for(idx=0;idx<OM_PRO_NUM_BUTTONS;idx++){
		// enable the button
		Om_pro_buttons[gr_screen.res][idx].button.enable();
		
		// unhide the button
		Om_pro_buttons[gr_screen.res][idx].button.unhide();		
	}

	// unhide and enable the tracker input boxes
	if(Om_tracker_flag){
		Om_tracker_login.enable();	
		Om_tracker_passwd.enable();
		Om_tracker_squad_name.enable();
	}
	Om_tracker_login.unhide();
	Om_tracker_passwd.unhide();
	Om_tracker_squad_name.unhide();

	// enable the click detection button
	Om_ip_button.enable();	

	// bogus control
	Om_pro_bogus.enable();
	Om_pro_bogus.unhide();	
}

// intialize the protocol section vars
void options_multi_init_protocol_vars()
{
	// current protocol
	Om_protocol = Multi_options_g.protocol;

	// whether or not the user has the local broadcast button selected
	Om_local_broadcast = (Player->m_local_options.flags & MLO_FLAG_LOCAL_BROADCAST) ? 1 : 0;

	// whether or not we're playing on the tracker
	// ------------------- made to read the registry by Kazan -------------------
	Om_tracker_flag = os_config_read_uint( "PXO", "FS2OpenPXO" , 0 );
		 // (Multi_options_g.protocol == NET_TCP) && Multi_options_g.pxo ? 1 : 0;	

	// load the ip address list	
	Om_ip_disp_count = 0;
	options_multi_protocol_load_ip_file();
	Om_ip_selected = Om_num_ips - 1;	
	Om_ip_start = Om_num_ips - 1;			
}

// do frame for the protocol section
void options_multi_protocol_do(int key)
{
	// check for button presses
	options_multi_protocol_check_buttons();
	
	// force draw the correct "local broadcast" button	
	if(Om_local_broadcast){
		Om_pro_buttons[gr_screen.res][OM_PRO_LOCAL_BROADCAST].button.draw_forced(2);
	}

	// draw the "vmt" button if it is selected
	if(Om_tracker_flag){
//		Om_pro_buttons[gr_screen.res][OM_PRO_VMT].button.draw_forced(2);
	}

	// see if he hit any interesting key presses
	switch(key){
	case KEY_ENTER:
		// add a new ip string if we're in "input" mode
		if(Om_input_mode){			
			options_multi_protocol_add_current_ip();
			
			// clear the text control and input mode
			Om_ip_input.set_text("");
			Om_ip_input.clear_focus();
			Om_ip_input.disable();
			Om_input_mode = 0;
		}

		// if the tracker login inputbox has focus, lose it
		if(Om_tracker_login.has_focus()){
			Om_tracker_login.clear_focus();
			gamesnd_play_iface(SND_COMMIT_PRESSED);
		}
		// if the tracker password inputbox has focus, lose it
		if(Om_tracker_passwd.has_focus()){
			Om_tracker_passwd.clear_focus();
			gamesnd_play_iface(SND_COMMIT_PRESSED);
		}
		// if the tracker squad name inputbox has focus, lose it
		if(Om_tracker_squad_name.has_focus()){
			Om_tracker_squad_name.clear_focus();
			gamesnd_play_iface(SND_COMMIT_PRESSED);
		}
		break;

	case KEY_ESC:
		// if we're in input mode, cancel out
		if(Om_input_mode){
			// clear the text control and input mode
			Om_ip_input.set_text("");
			Om_ip_input.clear_focus();
			Om_ip_input.disable();
			Om_input_mode = 0;
		}
		// otherwise quit the options screen altogether
		else {
			options_cancel_exit();
		}
		break;

	case KEY_TAB:
		// tab through the tracker input controls
		if(Om_tracker_login.has_focus()){
			Om_tracker_passwd.set_focus();
		} else if(Om_tracker_passwd.has_focus()){
			Om_tracker_squad_name.set_focus();
		} else if(Om_tracker_squad_name.has_focus()){
			Om_tracker_login.set_focus();
		}
		break;
	}

	// force draw the proper protocol
	if (Om_protocol == NET_IPX) {
		Om_pro_buttons[gr_screen.res][OM_PRO_IPX].button.draw_forced(2);
	} else {
		Om_pro_buttons[gr_screen.res][OM_PRO_TCP].button.draw_forced(2);
	}

	// force draw the proper tab button
	switch (Om_mode) {
	case OM_MODE_GENERAL:
		Om_pro_buttons[gr_screen.res][OM_PRO_GEN_TAB].button.draw_forced(2);
		break;

	case OM_MODE_VOX:
		Om_pro_buttons[gr_screen.res][OM_PRO_VOX_TAB].button.draw_forced(2);
		break;
	}

	// check to see if the user has clicked on the ip list and selected a new item
	options_multi_protocol_check_ip_list();

	// draw the list of ip addresses
	options_multi_protocol_display_ips();	

	// hack to play sound when input boxes gain focus
	if (Om_tracker_login.has_focus()) {
		if (Om_tracker_focus != TRACKER_FOCUS_LOGIN) {
			Om_tracker_focus = TRACKER_FOCUS_LOGIN;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	} else if (Om_tracker_passwd.has_focus()) {
		if (Om_tracker_focus != TRACKER_FOCUS_PASSWORD) {
			Om_tracker_focus = TRACKER_FOCUS_PASSWORD;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	} else if (Om_tracker_squad_name.has_focus()) {
		if (Om_tracker_focus != TRACKER_FOCUS_SQUADRON) {
			Om_tracker_focus = TRACKER_FOCUS_SQUADRON;
			gamesnd_play_iface(SND_USER_SELECT);
		}
	} else {
		Om_tracker_focus = TRACKER_FOCUS_NONE;
	}
}

// if the accept button was hit
void options_multi_protocol_accept()
{
	// if the user has selected local broadcast write it into his options struct
	Player->m_local_options.flags &= ~(MLO_FLAG_LOCAL_BROADCAST);
	if(Om_local_broadcast){
		Player->m_local_options.flags |= MLO_FLAG_LOCAL_BROADCAST;
	}	

	// active protocol
	Multi_options_g.protocol = Om_protocol;

	// copy the VMT login and password data
	Om_tracker_login.get_text(Multi_tracker_login);
	Om_tracker_passwd.get_text(Multi_tracker_passwd);
	Om_tracker_squad_name.get_text(Multi_tracker_squad_name);

	// #KAZAN# --- Save FS2OpenPXO flag
//	os_config_write_uint( "PXO", "FS2OpenPXO" , Om_tracker_flag );

	// write out the tracker login and passwd values to the registry
//	os_config_write_string( "PXO", "Login", Multi_tracker_login );
//	os_config_write_string( "PXO", "Password", Multi_tracker_passwd );

	// write out the PXO squad name and passwd values to the registry
//	os_config_write_string( "PXO", "SquadName", Multi_tracker_squad_name );
	
	// save the ip address list
	options_multi_protocol_save_ip_file();
}

// check for button presses
void options_multi_protocol_check_buttons()
{
	int idx;

	// go through each button
	for(idx=0;idx<OM_PRO_NUM_BUTTONS;idx++){
		if(Om_pro_buttons[gr_screen.res][idx].button.pressed()){
			options_multi_protocol_button_pressed(idx);
			break;
		}
	}
}

// if a button was pressed
void options_multi_protocol_button_pressed(int n)
{
	switch(n){
	// add an ip address
	case OM_PRO_ADD_IP:
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		// setup the input mode
		Om_input_mode = 1;
		Om_ip_input.enable();
		Om_ip_input.unhide();
		Om_ip_input.set_text(IP_EMPTY_STRING);
		Om_ip_input.set_focus();
		gamesnd_play_iface(SND_USER_SELECT);
		break;

	// delete the currently selected ip
	case OM_PRO_DELETE_IP:
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		options_multi_protocol_delete_ip();
		gamesnd_play_iface(SND_USER_SELECT);
		break;

	// the "local" broadcast button - toggle
	case OM_PRO_LOCAL_BROADCAST:
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		if(!Om_local_broadcast){			
			Om_local_broadcast = 1;
		} else {
			Om_local_broadcast = 0;
		}

		gamesnd_play_iface(SND_USER_SELECT);
		break;

	// scroll ips down
	case OM_PRO_SCROLL_IP_DOWN:		
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		options_multi_protocol_scroll_ip_down();
		break;

	// scroll ips up
	case OM_PRO_SCROLL_IP_UP:		
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		options_multi_protocol_scroll_ip_up();
		break;

	// the vmt button
/*	case OM_PRO_VMT:
		// for the multiplayer beta, always force tracker mode
#ifdef MULTIPLAYER_BETA_BUILD // do we want this for FS2_DEMO
		Om_tracker_flag = 1;
#else
		// don't process if we're in input mode
		if(Om_input_mode){
			break;
		}

		// toggle the stupid thing
		Om_tracker_flag = !Om_tracker_flag;

		// if the thing is toggled on - enable the inputbox controls, else diable them
		if(Om_tracker_flag){
			Om_tracker_login.enable();
			Om_tracker_passwd.enable();
			Om_tracker_squad_name.enable();
		} else {
			Om_tracker_login.disable();
			Om_tracker_passwd.disable();
			Om_tracker_squad_name.disable();
		}

		// play a sound
		gamesnd_play_iface(SND_USER_SELECT);
#endif
		break;*/

	// general tab button 
	case OM_PRO_GEN_TAB:	
		if(Om_mode != OM_MODE_GENERAL){
			// set the general tab
			Om_mode = OM_MODE_GENERAL;		

			// disable the voice controls
			options_multi_disable_vox_controls();

			// enable the general controls
			options_multi_enable_gen_controls();

			// set the general screen mask	
			Assert(Om_mask_0 >= 0);
			Om_window->set_mask_bmap(Om_mask_0, Om_background_0_mask_fname[gr_screen.res]);
		}

		// play a sound
		gamesnd_play_iface(SND_USER_SELECT);

		break;

	// voice tab button
	case OM_PRO_VOX_TAB:
		if(Om_mode != OM_MODE_VOX){
			// set the voice tab
			Om_mode = OM_MODE_VOX;

			// disable the general controls
			options_multi_disable_gen_controls();

			// enable the voice controls
			options_multi_enable_vox_controls();

			// set the voice screen mask	
			Assert(Om_mask_1 >= 0);
			Om_window->set_mask_bmap(Om_mask_1, Om_background_1_mask_fname[gr_screen.res]);
		}
		// play a sound
		gamesnd_play_iface(SND_USER_SELECT);

		break;

	// tcp mode
	case OM_PRO_TCP:
		Om_protocol = NET_TCP;
		gamesnd_play_iface(SND_USER_SELECT);
		break;

	// ipx mode
	case OM_PRO_IPX:
#ifndef FS2_DEMO
		Om_protocol = NET_IPX;
		gamesnd_play_iface(SND_USER_SELECT);
#endif
		break;
	}
}

// load the ip address file
void options_multi_protocol_load_ip_file()
{
	char line[IP_STRING_LEN];
	CFILE *file = NULL;

	// reset the ip address count
	Om_num_ips = 0;

	// attempt to open the ip list file
	file = cfopen(IP_CONFIG_FNAME,"rt",CFILE_NORMAL,CF_TYPE_DATA);	
	if(file == NULL){
		nprintf(("Network","Error loading tcp.cfg file!\n"));
		return;
	}

	// read in all the strings in the file
	while(!cfeof(file)){
		line[0] = '\0';
		cfgets(line,IP_STRING_LEN,file);

		// strip off any newline character
		if(line[strlen(line) - 1] == '\n'){
			line[strlen(line) - 1] = '\0';
		}

		// 0 length lines don't get processed
		if((line[0] == '\0') || (line[0] == '\n') )
			continue;

		if ( !psnet_is_valid_ip_string(line) ) {
			nprintf(("Network","Invalid ip string (%s)\n",line));
		} else {
			if(Om_num_ips < MAX_IP_ADDRS-1){
				strcpy(Om_ip_addrs[Om_num_ips++],line);
			}
		}
	}

	cfclose(file);
}

// save the ip address file
void options_multi_protocol_save_ip_file()
{
	int idx;
	CFILE *file = NULL;

	// attempt to open the ip list file for writing
	file = cfopen(IP_CONFIG_FNAME,"wt",CFILE_NORMAL,CF_TYPE_DATA );
	if(file == NULL){
		nprintf(("Network","Error loading tcp.cfg file\n"));
		return;
	}

	// write out all the string we have
	for(idx=0;idx<Om_num_ips;idx++){
		// make _absolutely_ sure its a valid address
		// MWA -- commented out next line because name resolution might fail when
		// it was added.  We'll only grab games that we can actually get to.
		//Assert(psnet_is_valid_ip_string(Multi_ip_addrs[idx]));

		cfputs(Om_ip_addrs[idx],file);
				
	   // make sure to tack on a newline if necessary
		if(Om_ip_addrs[idx][strlen(&Om_ip_addrs[idx][0]) - 1] != '\n'){
			cfputs(NOX("\n"),file);
		}
	}

	cfclose(file);
}

// draw the list of ip addresses
void options_multi_protocol_display_ips()
{
	int idx;
	int y_start = Ip_list_coords[gr_screen.res][1];
		
	// get the # of items we should be displaying based upon the # of addresses and the starting display point
	if(Om_ip_start >= Ip_list_max_display[gr_screen.res]){
		Om_ip_disp_count = Ip_list_max_display[gr_screen.res];
	} else {
		Om_ip_disp_count = Om_ip_start + 1;
	}
	
	// display the addresses
	for(idx=Om_ip_start; idx >= Om_ip_start - Om_ip_disp_count + 1 ; idx--){	
		if(idx == Om_ip_selected){
			gr_set_color_fast(&Color_bright);
		} else {
			gr_set_color_fast(&Color_white);
		}

		gr_printf(Ip_list_coords[gr_screen.res][0], y_start, Om_ip_addrs[idx]);
		y_start += 10;
	}
}

// scroll the list of ip addresses down
void options_multi_protocol_scroll_ip_down()
{
	if(Om_ip_start >= Ip_list_max_display[gr_screen.res]){
		gamesnd_play_iface(SND_SCROLL);
		Om_ip_start--;
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}	
}

// scroll the list of ip addresses up
void options_multi_protocol_scroll_ip_up()
{
	if(Om_ip_start < Om_num_ips-1){
		gamesnd_play_iface(SND_SCROLL);
		Om_ip_start++;
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}

// check the ip list to see if the user has selected a new item
void options_multi_protocol_check_ip_list()
{
	int click_y;	
	int item;
	
	if(Om_ip_button.pressed()){
		// determine which item he clicked on	
		Om_ip_button.get_mouse_pos(NULL, &click_y);
		item = click_y / 10;
			
		// determine if there is an item in this location, and select it if so
		if(item < Om_ip_disp_count){
			Om_ip_selected = Om_ip_start - item;
		}
	}
}

// delete the currently selected ip if any
void options_multi_protocol_delete_ip()
{
	int idx;
	
	// attempt to delete the currently highlighted item
	if(Om_ip_selected != -1){		

		// move down all the other items				
		for(idx=Om_ip_selected; idx < Om_num_ips; idx++){
			strcpy(Om_ip_addrs[idx],Om_ip_addrs[idx+1]);
		}

		// make sure to decrement the starting index
		Om_ip_start--;			
			
		// check to make sure that the selected item is valid			
		Om_num_ips--;			
		if(Om_num_ips <= 0){
			Om_ip_selected = -1;
		} else {
			if(Om_ip_selected > 0){
				Om_ip_selected--;	
			} 
		}						
	}
}

// return 10, if successflu
char Ip_str[IP_STRING_LEN+1];
int Ip_validated_already = 0;
int options_multi_verify_ip()
{
	int result;

	if(!Ip_validated_already){
		// see if its a valid ip address
		result = psnet_is_valid_ip_string(Ip_str);
	
		// if the result is a valid ip string, return immediately
		if(result){
			return 10;
		}

		// otherwise, change the popup text to indicate that it is invalid and wait for the user to click ok
		popup_change_text(XSTR( "Ip string is invalid!", 386));
	} 	

	Ip_validated_already = 1;

	// always wait for the user to hit the "cancel" button
	return 0;
}

// attempt to add the currently entered ip address
void options_multi_protocol_add_current_ip()
{		
	// get the entered string
	Om_ip_input.get_text(Ip_str);

	// this popup wil do several things. 
	// 1.) It will display a popup so the user isn't left scratching his head
	// 2.) If the address
	Ip_validated_already = 0;
	if(popup_till_condition(options_multi_verify_ip, XSTR( "Cancel", 387), XSTR( "Verifying ip address", 388)) == 10){
		if(Om_num_ips < MAX_IP_ADDRS){
			strcpy(Om_ip_addrs[Om_num_ips],Ip_str);
			Om_ip_start = Om_num_ips;
			Om_num_ips++;
			
			// if this is the first item on the list, select it
			if(Om_num_ips == 1){
				Om_ip_selected = 0;
			}
		} else {
			options_multi_add_notify(XSTR( "Max # of IP addresses reached!", 389));
		}
	} 			
}

// general options tab section -------------------------------------------

// load all the general tab controls
void options_multi_load_gen_controls()
{
	int idx;
	
	Assert(Om_window != NULL);

	// instantiate all the buttons
	for(idx=0; idx<OM_GEN_NUM_BUTTONS; idx++){				
		// create the object
		Om_gen_buttons[gr_screen.res][idx].button.create(Om_window, "", Om_gen_buttons[gr_screen.res][idx].x, Om_gen_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);

		// set the sound to play when highlighted
		Om_gen_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Om_gen_buttons[gr_screen.res][idx].button.set_bmaps(Om_gen_buttons[gr_screen.res][idx].filename);

		// set the hotspot
		Om_gen_buttons[gr_screen.res][idx].button.link_hotspot(Om_gen_buttons[gr_screen.res][idx].hotspot);
	}

	// text
	for(idx=0; idx<OM_GEN_NUM_TEXT; idx++){
		Om_window->add_XSTR(&Om_gen_text[gr_screen.res][idx]);
	}

	// bogus control
	Om_gen_bogus.base_create(Om_window, UI_KIND_ICON, 0, 0, 0, 0);
}

// disable/hide all the general tab controls
void options_multi_disable_gen_controls()
{
	int idx;

	// go through all the controls
	for(idx=0;idx<OM_GEN_NUM_BUTTONS;idx++){
		Om_gen_buttons[gr_screen.res][idx].button.hide();
		Om_gen_buttons[gr_screen.res][idx].button.disable();
	}

	// bogus control
	Om_gen_bogus.hide();
	Om_gen_bogus.disable();
}

// enable/unhide all the general tab controls
void options_multi_enable_gen_controls()
{
	int idx;

	// go through all the controls
	for(idx=0;idx<OM_GEN_NUM_BUTTONS;idx++){		
		Om_gen_buttons[gr_screen.res][idx].button.enable();
		Om_gen_buttons[gr_screen.res][idx].button.unhide();
	}

	// bogus control
	Om_gen_bogus.enable();
	Om_gen_bogus.unhide();
}

// initialize the general tab vars
void options_multi_init_gen_vars()
{
	// initialize the object update
	Om_gen_obj_update = Player->m_local_options.obj_update_level;

	// initialize the accept pix var	
	if(Player->m_local_options.flags & MLO_FLAG_ACCEPT_PIX){
		Om_gen_pix = 1;
	} else {
		Om_gen_pix = 0;
	}

	// initialize the xfer_multidata var
	if(Player->m_local_options.flags & MLO_FLAG_XFER_MULTIDATA){
		Om_gen_xfer_multidata = 1;
	} else {
		Om_gen_xfer_multidata = 0;
	}

	// initialize the flush cache var
	if(Player->m_local_options.flags & MLO_FLAG_FLUSH_CACHE){
		Om_gen_flush_cache = 1;
	} else {
		Om_gen_flush_cache = 0;
	}
}

// accept function for the general tab
void options_multi_gen_accept()
{
	// apply the object update level
	Player->m_local_options.obj_update_level = Om_gen_obj_update;

	// apply the accept pix var
	Player->m_local_options.flags &= ~(MLO_FLAG_ACCEPT_PIX);
	if(Om_gen_pix){
		Player->m_local_options.flags |= MLO_FLAG_ACCEPT_PIX;
	}

	// apply the xfer multidata var
	Player->m_local_options.flags &= ~(MLO_FLAG_XFER_MULTIDATA);
	if(Om_gen_xfer_multidata){
		Player->m_local_options.flags |= MLO_FLAG_XFER_MULTIDATA;
	} 

	// apply the flush cache var
	Player->m_local_options.flags &= ~(MLO_FLAG_FLUSH_CACHE);
	if(Om_gen_flush_cache){
		Player->m_local_options.flags |= MLO_FLAG_FLUSH_CACHE;
	}
}

// do frame for the general tab
void options_multi_gen_do()
{
	// check for button presses
	options_multi_gen_check_buttons();

	// draw the proper object update button
	switch(Om_gen_obj_update){
	case OBJ_UPDATE_LOW:
		Om_gen_buttons[gr_screen.res][OM_GEN_OBJ_LOW].button.draw_forced(2);
		break;
	case OBJ_UPDATE_MEDIUM:
		Om_gen_buttons[gr_screen.res][OM_GEN_OBJ_MED].button.draw_forced(2);
		break;
	case OBJ_UPDATE_HIGH:
		Om_gen_buttons[gr_screen.res][OM_GEN_OBJ_HIGH].button.draw_forced(2);
		break;
	case OBJ_UPDATE_LAN:
		Om_gen_buttons[gr_screen.res][OM_GEN_OBJ_LAN].button.draw_forced(2);
		break;
	default :
		Int3();
	}

	// draw the proper pix button
	if(Om_gen_pix){
		Om_gen_buttons[gr_screen.res][OM_GEN_PIX_YES].button.draw_forced(2);
	} else {
		Om_gen_buttons[gr_screen.res][OM_GEN_PIX_NO].button.draw_forced(2);
	}

	// draw the proper xfer multidata button
	if(Om_gen_xfer_multidata){
		Om_gen_buttons[gr_screen.res][OM_GEN_XFER_MULTIDATA_YES].button.draw_forced(2);
	} else {
		Om_gen_buttons[gr_screen.res][OM_GEN_XFER_MULTIDATA_NO].button.draw_forced(2);
	}

	// draw the proper flush cache button
	if(Om_gen_flush_cache){
		Om_gen_buttons[gr_screen.res][OM_GEN_FLUSH_YES].button.draw_forced(2);
	} else {
		Om_gen_buttons[gr_screen.res][OM_GEN_FLUSH_NO].button.draw_forced(2);
	}
}

// check for button presses
void options_multi_gen_check_buttons()
{
	int idx;

	// go through all the buttons
	for(idx=0;idx<OM_GEN_NUM_BUTTONS;idx++){
		if(Om_gen_buttons[gr_screen.res][idx].button.pressed()){
			options_multi_gen_button_pressed(idx);
			break;
		}
	}
}

// a button was pressed
void options_multi_gen_button_pressed(int n)
{
	switch(n){
	// low object update level
	case OM_GEN_OBJ_LOW:
		if(Om_gen_obj_update != OBJ_UPDATE_LOW){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_obj_update = OBJ_UPDATE_LOW;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// medium object update level
	case OM_GEN_OBJ_MED:
		if(Om_gen_obj_update != OBJ_UPDATE_MEDIUM){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_obj_update = OBJ_UPDATE_MEDIUM;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// high object update level
	case OM_GEN_OBJ_HIGH:
		if(Om_gen_obj_update != OBJ_UPDATE_HIGH){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_obj_update = OBJ_UPDATE_HIGH;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;

	// lan object update level
	case OM_GEN_OBJ_LAN:
		if(Om_gen_obj_update != OBJ_UPDATE_LAN){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_obj_update = OBJ_UPDATE_LAN;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// accept pix
	case OM_GEN_PIX_YES:
		if(!Om_gen_pix){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_pix = 1;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// don't accept pix
	case OM_GEN_PIX_NO:
		if(Om_gen_pix){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_pix = 0;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// put missions in the multidate directory
	case OM_GEN_XFER_MULTIDATA_YES:
		if(!Om_gen_xfer_multidata){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_xfer_multidata = 1;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// dont put missions in the multidata directory
	case OM_GEN_XFER_MULTIDATA_NO:
		if(Om_gen_xfer_multidata){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_xfer_multidata = 0;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// flush the cache before each mission
	case OM_GEN_FLUSH_YES:
		if(!Om_gen_flush_cache){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_flush_cache = 1;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// don't flush the cache before each mission
	case OM_GEN_FLUSH_NO:
		if(Om_gen_flush_cache){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_gen_flush_cache = 0;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;	
	}
}

// voice options tab section -------------------------------------------

// load all the voice tab controls
void options_multi_load_vox_controls()
{
	int idx;
	
	Assert(Om_window != NULL);

	// instantiate all the buttons
	for(idx=0; idx<OM_VOX_NUM_BUTTONS; idx++){
		// create the object
		Om_vox_buttons[gr_screen.res][idx].button.create(Om_window, "", Om_vox_buttons[gr_screen.res][idx].x, Om_vox_buttons[gr_screen.res][idx].y, 1, 1, 0, 1);

		// set the sound to play when highlighted
		Om_vox_buttons[gr_screen.res][idx].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Om_vox_buttons[gr_screen.res][idx].button.set_bmaps(Om_vox_buttons[gr_screen.res][idx].filename);

		// set the hotspot
		Om_vox_buttons[gr_screen.res][idx].button.link_hotspot(Om_vox_buttons[gr_screen.res][idx].hotspot);
	}

	// text
	for(idx=0; idx<OM_VOX_NUM_TEXT; idx++){
		Om_window->add_XSTR(&Om_vox_text[gr_screen.res][idx]);
	}
	
	// sliders
	for ( idx = 0; idx < NUM_OM_VOX_SLIDERS; idx++ ) {
		 Om_vox_sliders[gr_screen.res][idx].slider.create(Om_window, Om_vox_sliders[gr_screen.res][idx].x, Om_vox_sliders[gr_screen.res][idx].y,
																		Om_vox_sliders[gr_screen.res][idx].dots, Om_vox_sliders[gr_screen.res][idx].filename,
																		Om_vox_sliders[gr_screen.res][idx].hotspot, Om_vox_sliders[gr_screen.res][idx].right_filename, Om_vox_sliders[gr_screen.res][idx].right_mask, Om_vox_sliders[gr_screen.res][idx].right_x, Om_vox_sliders[gr_screen.res][idx].right_y,
																		Om_vox_sliders[gr_screen.res][idx].left_filename, Om_vox_sliders[gr_screen.res][idx].left_mask, Om_vox_sliders[gr_screen.res][idx].left_x, Om_vox_sliders[gr_screen.res][idx].left_y,
																		Om_vox_sliders[gr_screen.res][idx].dot_w);
	}	

	// create the player list select button
	Om_vox_plist_button.create(Om_window, "", Om_vox_plist_coords[gr_screen.res][0], Om_vox_plist_coords[gr_screen.res][1], Om_vox_plist_coords[gr_screen.res][2], Om_vox_plist_coords[gr_screen.res][3], 0, 1);
	Om_vox_plist_button.hide();

	// build a list of net players
	Om_vox_num_players = 0;
	for(idx=0;idx<MAX_PLAYERS;idx++){
		Om_vox_players[idx] = NULL;

		// if i'm not connected, do nothing
		if((Net_player == NULL) || !(Net_player->flags & NETINFO_FLAG_CONNECTED)){
			continue;
		}

		// add all players I know about
		if(MULTI_CONNECTED(Net_players[idx]) && !MULTI_STANDALONE(Net_players[idx]) && (Net_player != &Net_players[idx])){
			// set the netplayer pointer
			Om_vox_players[Om_vox_num_players] = &Net_players[idx];

			// set his mute flag
			Om_vox_player_flags[Om_vox_num_players] = (Multi_voice_local_prefs & (1<<idx)) ? 1 : 0;

			// increment the count
			Om_vox_num_players++;
		}
	}	
	
	// bogus control
	Om_vox_bogus.base_create(Om_window, UI_KIND_ICON, 0, 0, 0, 0);
}

// disable/hide all the voice tab controls
void options_multi_disable_vox_controls()
{
	int idx;

	// go through all the controls
	for(idx=0; idx<OM_VOX_NUM_BUTTONS; idx++){
		Om_vox_buttons[gr_screen.res][idx].button.hide();
		Om_vox_buttons[gr_screen.res][idx].button.disable();
	}

	// hide the qos control
	Om_vox_sliders[gr_screen.res][OM_VOX_QOS_SLIDER].slider.hide();
	Om_vox_sliders[gr_screen.res][OM_VOX_QOS_SLIDER].slider.disable();	

	// unset the sound buffer size so we don't display any waveforms
	Om_vox_voice_buffer_size = -1;
	Om_vox_voice_comp_size = -1;
	Om_vox_playback_handle = -1;
	Om_vox_test_status = OM_VOX_TEST_NONE;	

	// disable the player list select button
	Om_vox_plist_button.disable();

	// bogus controls
	Om_vox_bogus.hide();
	Om_vox_bogus.disable();
}

// enable/unhide all the voice tab controls
void options_multi_enable_vox_controls()
{
	int idx;

	// go through all the controls
	for(idx=0; idx<OM_VOX_NUM_BUTTONS; idx++){		
		Om_vox_buttons[gr_screen.res][idx].button.enable();
		Om_vox_buttons[gr_screen.res][idx].button.unhide();
	}

	// unhide the qos control	
	Om_vox_sliders[gr_screen.res][OM_VOX_QOS_SLIDER].slider.enable();	
	Om_vox_sliders[gr_screen.res][OM_VOX_QOS_SLIDER].slider.unhide();	

	// unset the sound buffer size so we don't display any waveforms
	Om_vox_voice_buffer_size = -1;
	Om_vox_voice_comp_size = -1;
	Om_vox_playback_handle = -1;
	Om_vox_test_status = OM_VOX_TEST_NONE;	

	// select the first player on the list
	Om_vox_player_select = Om_vox_players[0];
	Om_vox_plist_start = 0;

	// enable the player list select button
	Om_vox_plist_button.enable();

	// bogus controls
	Om_vox_bogus.enable();
	Om_vox_bogus.unhide();
}

// initialize the voice tab vars
void options_multi_init_vox_vars()
{
	// intialize the accept voice var
	if(Player->m_local_options.flags & MLO_FLAG_NO_VOICE){
		Om_vox_accept_voice = 0;
	} else {
		Om_vox_accept_voice = 1;
	}
}

// accept function for the voice tab
void options_multi_vox_accept()
{
	int idx;
	int voice_pref_flags;
	
	// set the accept voice flag
	Player->m_local_options.flags &= ~(MLO_FLAG_NO_VOICE);
	if(!Om_vox_accept_voice){
		Player->m_local_options.flags |= MLO_FLAG_NO_VOICE;
	}

	// build the voice preferences stuff
	voice_pref_flags = 0xffffffff;
	for(idx=0;idx<Om_vox_num_players;idx++){
		// if this guy is muted
		if(!Om_vox_player_flags[idx]){
			voice_pref_flags &= ~(1 << NET_PLAYER_INDEX(Om_vox_players[idx]));
		}
	}
	multi_voice_set_prefs(voice_pref_flags);
}

// do frame for the voice tab
void options_multi_vox_do()
{
	int handle;
	
	// check for button presses
	options_multi_vox_check_buttons();

	// draw the proper accept voice button
	if(Om_vox_accept_voice){
		Om_vox_buttons[gr_screen.res][OM_VOX_VOICE_YES].button.draw_forced(2);
	} else {
		Om_vox_buttons[gr_screen.res][OM_VOX_VOICE_NO].button.draw_forced(2);
	}

	// if the currently selected player is muted
	if((Om_vox_player_select != NULL) && !Om_vox_player_flags[options_multi_vox_plist_get(Om_vox_player_select)]){
		Om_vox_buttons[gr_screen.res][OM_VOX_VOICE_MUTE].button.draw_forced(2);
	}

	// process and display the player list
	options_multi_vox_process_player_list();

	// if we're currently doing a voice test recording, process some stuff
	switch(Om_vox_test_status){
	case OM_VOX_TEST_RECORDING:	
		multi_voice_test_process();

		// force draw the mic test button
		Om_vox_buttons[gr_screen.res][OM_VOX_VOICE_TEST].button.draw_forced(2);

		// if we are no longer recording, switch to playback if possible
		if(!multi_voice_test_recording()){
			Om_vox_test_status = OM_VOX_TEST_PLAYBACK;
			
			if(Om_vox_voice_comp_size != -1){
				// stop any playing back sounds
				rtvoice_stop_playback_all();

				// attempt to get a playback handle
				handle = multi_voice_test_get_playback_buffer();
				if(handle != -1){
					Om_vox_playback_handle = rtvoice_play_uncompressed(handle, Om_vox_comp_buffer, Om_vox_voice_comp_size);

					// mark us as playing back
					Om_vox_test_status = OM_VOX_TEST_PLAYBACK;
				}
				// on error, notify the user something is wrong
				else {
					options_multi_add_notify(XSTR( "Error trying to playback recorded voice! Check your hardware", 390));

					// mark us as doing nothing
					Om_vox_test_status = OM_VOX_TEST_NONE;
				}
			} else {
				// mark us as doing nothing
				Om_vox_test_status = OM_VOX_TEST_NONE;
			}			
		}
		break;
	
	case OM_VOX_TEST_PLAYBACK:			
		#ifndef NO_SOUND
		// if we were playing a sound back, but now the sound is done
		if((Om_vox_playback_handle != -1) && (ds_get_play_position(ds_get_channel(Om_vox_playback_handle)) >= (DWORD)Om_vox_voice_comp_size)){
			// flush all playing sounds safely
			rtvoice_stop_playback_all();

			// null the sound handle
			Om_vox_playback_handle = -1;

			// set this so we know not to display any more waveforms
			Om_vox_voice_buffer_size = -1;
			Om_vox_voice_comp_size = -1;			

			// free the status up
			Om_vox_test_status = OM_VOX_TEST_NONE;
		}
		#else
		// shouln't be necessary, but...
		Om_vox_test_status = OM_VOX_TEST_NONE;
		#endif  // ifndef NO_SOUND
		break;
	}
}

// check for button presses
void options_multi_vox_check_buttons()
{
	int idx;

	// go through all the buttons
	for(idx=0; idx<OM_VOX_NUM_BUTTONS; idx++){
		if(Om_vox_buttons[gr_screen.res][idx].button.pressed()){
			options_multi_vox_button_pressed(idx);
			break;
		}
	}
}

// a button was pressed
void options_multi_vox_button_pressed(int n)
{
	switch(n){
	// accept voice button
	case OM_VOX_VOICE_YES:
		if(!Om_vox_accept_voice){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_vox_accept_voice = 1;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;
	
	// don't accept voice button
	case OM_VOX_VOICE_NO:
		if(Om_vox_accept_voice){
			gamesnd_play_iface(SND_USER_SELECT);
			Om_vox_accept_voice = 0;
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;

	// mute/unmute button
	case OM_VOX_VOICE_MUTE:
		if(Om_vox_player_select != NULL){
			Om_vox_player_flags[options_multi_vox_plist_get(Om_vox_player_select)] = !Om_vox_player_flags[options_multi_vox_plist_get(Om_vox_player_select)];
			gamesnd_play_iface(SND_USER_SELECT);
		} else {
			gamesnd_play_iface(SND_GENERAL_FAIL);
		}
		break;

	// scroll the player list up
	case OM_VOX_PLIST_UP:
		options_multi_vox_plist_scroll_up();
		break;

	// scroll the player list down
	case OM_VOX_PLIST_DOWN:
		options_multi_vox_plist_scroll_down();
		break;		

	// mic test button
	case OM_VOX_VOICE_TEST:
		#ifndef NO_SOUND
		// if in a multiplayer game, don't allow testing
		if((Net_player != NULL) && (Net_player->flags & NETINFO_FLAG_CONNECTED)){
			options_multi_add_notify(XSTR( "Cannot test mic while in a multiplayer game!", 391));
			break;
		}

		// if this machine is not capable of playing
		if(!Multi_voice_can_record){
			options_multi_add_notify(XSTR( "DirectSoundCapture could not be initialized. To initialize DirectSoundCapture your sound card must be full duplex and your sound card drivers must support DirectSoundCapture", 392));
		} else {
			// if we're not already doing a record test
			if(Om_vox_test_status == OM_VOX_TEST_NONE){
				// set the quality of sound
				rtvoice_set_qos(Om_vox_sliders[gr_screen.res][OM_VOX_QOS_SLIDER].slider.pos + 1);

				// clear the comp buffer
				memset(Om_vox_comp_buffer,128,OM_VOX_COMP_SIZE);

				Om_vox_test_status = OM_VOX_TEST_RECORDING;
				multi_voice_test_record_start();
			}
		}
		#endif  // ifndef NO_SOUND
		break;
	}
}

// screen shader
extern shader Grey_shader;

// process and blit any voice waveform if necessary
void options_multi_vox_process_waveform()
{
	int c_width = OM_VOX_WAVE_WIDTH;
	int avg_len;
	int buf_offset;
	int idx,a_idx,running_avg;	
	
	// if we're not in recording or playback mode
	if(Om_vox_test_status == OM_VOX_TEST_NONE){
		return;
	}

	// grey the screen
	gr_set_shader(&Grey_shader);
	gr_shade(0,0,gr_screen.clip_width, gr_screen.clip_height);

	switch(Om_vox_test_status){
	case OM_VOX_TEST_RECORDING:
		// if we have no sound buffer size, do nothing
		if(Om_vox_voice_buffer_size <= 0){
			return;
		}

		// if we are not recording, do nothing
		if(Om_vox_test_status != OM_VOX_TEST_RECORDING){
			return;
		}

		// get the # of samples we'll average for one line
		avg_len = Om_vox_voice_buffer_size / c_width;

		// blit the waveform
		gr_set_color_fast(&Color_green);
		buf_offset = 0;
		for(idx=0; idx < c_width; idx++){
			// reset the running average
			running_avg = 0;
			for(a_idx = 0; a_idx < avg_len; a_idx++){
				running_avg += (int)Om_vox_voice_buffer[buf_offset] - 128;			

				// increment the buffer offset
				buf_offset++;
			}

			running_avg /= avg_len;
			gr_line((gr_screen.max_w - OM_VOX_WAVE_WIDTH)/2 + idx, OM_VOX_WAVE_Y, (gr_screen.max_w - OM_VOX_WAVE_WIDTH)/2 + idx, OM_VOX_WAVE_Y + running_avg);
		}		

		// if this packet would have been dropped, notify the user
		if(multi_voice_test_packet_tossed()){
			gr_set_color_fast(&Color_bright);
			gr_string(OM_VOX_DROP_ICON_X,OM_VOX_DROP_ICON_Y, XSTR( "Packet Overflow", 393));
		}		
		break;

	case OM_VOX_TEST_PLAYBACK:
		#ifndef NO_SOUND
		// get the offset into the playing direct sound buffer
		buf_offset = ds_get_play_position(ds_get_channel(Om_vox_playback_handle));		

		// get the # of samples we'll average for one line
		avg_len = (int)((float)OM_VOX_RECORD_INT * ((1024.0f * 11.0f) / 1000.0f)) / c_width;				

		// blit the waveform
		gr_set_color_fast(&Color_red);		
		for(idx=0; idx < c_width; idx++){
			// reset the running average
			running_avg = 0;
			for(a_idx = 0; a_idx < avg_len; a_idx++){
				if(buf_offset < (OM_VOX_COMP_SIZE - 2)){
					running_avg += (int)Om_vox_comp_buffer[buf_offset] - 128;			

					// increment the buffer offset				
					buf_offset++;
				}
			}

			running_avg /= avg_len;			
			gr_line((gr_screen.max_w - OM_VOX_WAVE_WIDTH)/2 + idx, OM_VOX_WAVE_Y, (gr_screen.max_w - OM_VOX_WAVE_WIDTH)/2 + idx, OM_VOX_WAVE_Y + running_avg);
		}				
		#endif  // ifndef NO_SOUND
		break;
	}
}

// process/display the player list
void options_multi_vox_process_player_list()
{
	int idx;
	int y_start,p_count;
	int selected_index,click_y;
	char str[CALLSIGN_LEN+2];

	// check for mouse clicks
	if(Om_vox_plist_button.pressed()){
		Om_vox_plist_button.get_mouse_pos(NULL,&click_y);
		selected_index = (click_y / 10) + Om_vox_plist_start;

		// if he clicked on a valid player, select him
		if(Om_vox_players[selected_index] != NULL){
			Om_vox_player_select = Om_vox_players[selected_index];

			nprintf(("Network","Selecting player %s\n",Om_vox_player_select->player->callsign));
		}
	}

	// draw the list of players
	p_count = 0;
	y_start = Om_vox_plist_coords[gr_screen.res][1];
	for(idx = Om_vox_plist_start; idx < Om_vox_num_players; idx++){
		if(Om_vox_players[idx] != NULL){
			// if he's the selected player, highlight him
			if(Om_vox_players[idx] == Om_vox_player_select){
				gr_set_color_fast(&Color_bright);
			} else {
				gr_set_color_fast(&Color_normal);
			}

			// force fit his callsign
			strcpy(str,Om_vox_players[idx]->player->callsign);
			gr_force_fit_string(str, CALLSIGN_LEN+1, Om_vox_plist_coords[gr_screen.res][2]);

			// blit the callsign
			gr_string(Om_vox_plist_coords[gr_screen.res][0], y_start, str);

			// increment the y index
			y_start += 10;

			// increment the player count
			p_count++;
		}

		// if we've reached max display, break out
		if(p_count >= Om_vox_plist_max_display[gr_screen.res]){
			break;
		}
	}
}	

// get the index into the player list of the passed netplayer
int options_multi_vox_plist_get(net_player *pl)
{
	int idx;

	for(idx=0;idx<Om_vox_num_players;idx++){
		if(pl == Om_vox_players[idx]){
			return idx;
		}
	}

	// should neve get here. hmmm.
	Int3();
	return -1;
}

// scroll the player list down
void options_multi_vox_plist_scroll_down()
{
	if(Om_vox_num_players < Om_vox_plist_max_display[gr_screen.res]){
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	if((Om_vox_num_players - Om_vox_plist_start) >= Om_vox_plist_max_display[gr_screen.res]){
		Om_vox_plist_start++;
		gamesnd_play_iface(SND_USER_SELECT);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}

// scroll the player list up
void options_multi_vox_plist_scroll_up()
{
	if(Om_vox_plist_start > 0){
		Om_vox_plist_start--;
		gamesnd_play_iface(SND_USER_SELECT);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}


// extern functions -----------------------------------------------------

// called when the options screen is initialized, pass in the UI window
void options_multi_init(UI_WINDOW *options_window)
{
	// assign the options window
	Om_window = options_window;

	// load the background bitmaps
	options_multi_load_bmaps();	

	// load the controls for the protocol area
	options_multi_load_protocol_controls();

	// load the controls for the general tab
	options_multi_load_gen_controls();

	// load the controls for the voice tab
	options_multi_load_vox_controls();

	// disable all the protocol controls
	options_multi_disable_protocol_controls();

	// disable all the general tab controls
	options_multi_disable_gen_controls();

	// disable all the voice tab controls
	options_multi_disable_vox_controls();

	// intialize the protocol section vars
	options_multi_init_protocol_vars();

	// initialize the general tab vars
	options_multi_init_gen_vars();

	// initialize the voice tab vars
	options_multi_init_vox_vars();

	// intialize the multiplayer voice recording system
	if( !((Net_player != NULL) && (Net_player->flags & NETINFO_FLAG_CONNECTED)) ){
		multi_voice_init();
	}

	// set the default screen mode
	Om_mode = OM_MODE_NONE;
}

// do frame for the multi options screen
void options_multi_do(int key)
{		
	// do frame for the protocol section
	options_multi_protocol_do(key);

	// process and blit any notification messages
	options_multi_notify_process();

	// process the proper tab control
	switch(Om_mode){
	case OM_MODE_GENERAL:
		options_multi_gen_do();
		break;
	case OM_MODE_VOX:
		options_multi_vox_do();
		break;
	default :
		Int3();		
	}	
}

// called when the entire options screen is closed
void options_multi_close()
{
	// null out the window handle
	Om_window = NULL;

	// unload all background bitmaps
	options_multi_unload_bmaps();

	// stop any playing voice
	rtvoice_stop_playback_all();

	// unset the screen mode
	Om_mode = OM_MODE_NONE;
}

// called if the accept button on the main options screen was hit
void options_multi_accept()
{	
	// accept function for the protocol section
	options_multi_protocol_accept();

	// accept function for the general tab
	options_multi_gen_accept();

	// accept function for the voice tab
	options_multi_vox_accept();

	// if Net_player is not null, copy these new settings to him
	if(Net_player != NULL){
		multi_options_local_load(&Net_player->p_info.options, NULL);		
	}
	multi_options_local_load(&Player->m_local_options, NULL);

	// if we're connected to a game server, update our options on the server now
	if((Net_player != NULL) && !(Net_player->flags & NETINFO_FLAG_AM_MASTER) && MULTI_CONNECTED(Net_players[MY_NET_PLAYER_NUM]) ){
		multi_options_update_local();
	}
}

// called when the multiplayer tab is hit - initializes/switches all necessary data.
// NOTE : this is different from the initialization function, which is called only when the options menu is started
void options_multi_select()
{
	// set the windows mask bitmap
	Assert(Om_mask_0 >= 0);
	Om_window->set_mask_bmap(Om_mask_0, Om_background_0_mask_fname[gr_screen.res]);

	// set the default screen mode
	Om_mode = OM_MODE_GENERAL;

	// clear any notification messages
	Om_notify_stamp = -1;	

	// enable all the protocol controls
	options_multi_enable_protocol_controls();	

	// enable the general tab controls
	options_multi_enable_gen_controls();
}

// return the bitmap handle of the current background bitmap, or -1 if the multiplayer tab is not active
int options_multi_background_bitmap()
{
	// return the background bitmap mode based upon the current mode
	switch(Om_mode){
	case OM_MODE_GENERAL:
		return Om_background_0;

	case OM_MODE_VOX:
		return Om_background_1;
	}

	// unknown mode of some kind
	return -1;
}

// called when the multiplayer tab has been switched from
void options_multi_unselect()
{
	// unset the mode
	Om_mode = OM_MODE_NONE;

	// disable all the protocol controls
	options_multi_disable_protocol_controls();

	// disable all the general tab controls
	options_multi_disable_gen_controls();

	// disable all the vox tab controls
	options_multi_disable_vox_controls();

	// stop any test voice recording
	multi_voice_test_record_stop();
}

// set voice sound buffer for display 
void options_multi_set_voice_data(unsigned char *sound_buf,int buf_size,unsigned char *comp_buf, int comp_size, int uncomp_size, double gain)
{
	// copy the buffer to the vox tab data
	if(buf_size > OM_VOX_BUF_SIZE){
		memcpy(Om_vox_voice_buffer,sound_buf,OM_VOX_BUF_SIZE);
		Om_vox_voice_buffer_size = OM_VOX_BUF_SIZE;
	} else {
		memcpy(Om_vox_voice_buffer,sound_buf,buf_size);
		Om_vox_voice_buffer_size = buf_size;
	}

	// copy and uncompress the compressed buffer
	if(Om_vox_voice_comp_size == -1){
		Om_vox_voice_comp_size = 0;
	}
	// if we can fit it, decompress this data
	if((Om_vox_voice_comp_size + uncomp_size) < OM_VOX_COMP_SIZE){
		// uncompress the data
		rtvoice_uncompress(comp_buf, comp_size, gain, Om_vox_comp_buffer + Om_vox_voice_comp_size, uncomp_size);

		Om_vox_voice_comp_size += uncomp_size;
	}
}

// return whether we want to eat a tabbed keypress
int options_multi_eat_tab()
{
	// do we want to eat the tab key or not
	if(Om_tracker_passwd.has_focus() || Om_tracker_login.has_focus() || Om_tracker_squad_name.has_focus()){
		return 1;
	}

	return 0;
}
