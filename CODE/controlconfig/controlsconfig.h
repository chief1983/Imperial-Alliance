/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/ControlConfig/ControlsConfig.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:40 $
 * $Author: Spearhawk $
 *
 * Header file for keyboard, joystick and mouse configuration
 *
 * $Log: controlsconfig.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:40  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 20:12:23  Darkhill
 * no message
 *
 * Revision 2.7  2004/05/03 21:22:19  Kazan
 * Abandon strdup() usage for mod list processing - it was acting odd and causing crashing on free()
 * Fix condition where alt_tab_pause() would flipout and trigger failed assert if game minimizes during startup (like it does a lot during debug)
 * Nav Point / Auto Pilot code (All disabled via #ifdefs)
 *
 * Revision 2.6  2004/04/06 03:09:01  phreak
 * added a control config option for the wireframe hud targetbox i enabled ages ago
 *
 * Revision 2.5  2003/11/11 02:15:43  Goober5000
 * ubercommit - basically spelling and language fixes with some additional
 * warnings disabled
 * --Goober5000
 *
 * Revision 2.4  2002/12/02 23:52:02  Goober5000
 * fixed misspelling
 *
 * Revision 2.3  2002/12/02 20:47:28  Goober5000
 * fixed misspelling of "category" as "catagory"
 *
 * Revision 2.2  2002/10/19 19:29:27  bobboau
 * inital commit, trying to get most of my stuff into FSO, there should be most of my fighter beam, beam rendering, beam shield hit, ABtrails, and ssm stuff. one thing you should be happy to know is the beam texture tileing is now set in the beam section section of the weapon table entry
 *
 * Revision 2.1  2002/10/17 20:40:50  randomtiger
 * Added ability to remove HUD ingame on keypress shift O
 * So I've added a new key to the bind list and made use of already existing hud removal code.
 *
 * Revision 2.0  2002/06/03 04:02:21  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:04  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 6     8/22/99 5:53p Dave
 * Scoring fixes. Added self destruct key. Put callsigns in the logfile
 * instead of ship designations for multiplayer players.
 * 
 * 5     8/19/99 10:59a Dave
 * Packet loss detection.
 * 
 * 4     8/01/99 12:39p Dave
 * Added HUD contrast control key (for nebula).
 * 
 * 3     11/05/98 4:18p Dave
 * First run nebula support. Beefed up localization a bit. Removed all
 * conditional compiles for foreign versions. Modified mission file
 * format.
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:48a Dave
 * 
 * 26    6/13/98 5:19p Hoffoss
 * externalized control config texts.
 * 
 * 25    5/15/98 8:37p Lawrance
 * Add 'equalize recharge rates' and 'target ship that sent last
 * transmission' key bindings
 * 
 * 24    5/14/98 5:32p Hoffoss
 * Improved axis binding code some more.
 * 
 * 23    5/13/98 7:15p Hoffoss
 * Fixed remaining bugs with axis binding.
 * 
 * 22    5/13/98 1:17a Hoffoss
 * Added joystick axes configurability.
 * 
 * 21    4/30/98 9:43p Hoffoss
 * Added new actions for free look movement which are default bounded to
 * the hat.
 * 
 * 20    4/25/98 1:59p Lawrance
 * fix merge typo
 * 
 * 19    4/25/98 1:24p Lawrance
 * Add time compression keys to key config
 * 
 * 18    4/25/98 12:43p Allender
 * added new shortcut key for attack my subsystem
 * 
 * 17    4/18/98 5:00p Dave
 * Put in observer zoom key. Made mission sync screen more informative.
 * 
 * 16    4/10/98 12:47p Allender
 * changed working on replay popup.  Don't reference repair in comm menu.
 * Added Shift-R for repair me
 * 
 * 15    4/08/98 11:11a Hoffoss
 * Fixed some bugs that showed up due to fixing other bugs the other day
 * with controls.
 * 
 * 14    3/31/98 4:15p Hoffoss
 * Disabled the show objectives action.
 * 
 * 13    3/23/98 12:27p Hoffoss
 * Whoops, changed order in list but forget to actually change the number.
 * 
 * 12    3/23/98 11:35a Hoffoss
 * Fixed #defines that were out of sync.
 * 
 * 11    3/19/98 5:04p Dave
 * Put in support for targeted multiplayer text and voice messaging (all,
 * friendly, hostile, individual).
 * 
 * 10    3/11/98 5:28p Hoffoss
 * Added control config debug display info to possibly aid in tracking
 * down a bug.
 * 
 * 9     2/28/98 7:02p Lawrance
 * overhaul on-line help
 * 
 * 8     2/26/98 12:33a Lawrance
 * Added back slew mode,  lots of changes to external and chase views.
 * 
 * 7     2/02/98 6:59p Lawrance
 * Adding new targeting keys (bomb, uninspected cargo, new ship, live
 * turrets).
 * 
 * 6     1/30/98 10:40a Lawrance
 * remove any binding references to hotkey screen
 * 
 * 5     1/28/98 6:19p Dave
 * Reduced standalone memory usage ~8 megs. Put in support for handling
 * multiplayer submenu handling for endgame, etc.
 * 
 * 4     1/22/98 4:53p Hoffoss
 * Made training messages/directives display a joystick button in place of
 * a keypress if there is no keypress bound to the action.
 * 
 * 3     1/02/98 4:42p Allender
 * removed unused key bindings from control config list
 * 
 * 2     12/30/97 4:47p Allender
 * work with ignore my target command.  Added new keyboard hotkey.  Made
 * it work globally
 * 
 * 1     12/24/97 11:59a Hoffoss
 * 
 * 41    11/24/97 10:20p Lawrance
 * Add key 'KEY_N' to target next ship on monitoring view
 * 
 * 40    11/21/97 5:57p Hoffoss
 * Fixed bug where timef type controls weren't checking joystick buttons.
 * 
 * 39    11/20/97 1:08a Lawrance
 * add support for 'R' key - target closest friendly repair ship
 * 
 * 38    11/17/97 6:40p Lawrance
 * Changed 'I' key to toggle of extended target info, moved target closest
 * locked missile to 'L'
 * 
 * 37    11/02/97 1:15p Hoffoss
 * Externed an array I need elsewhere.
 * 
 * 36    10/28/97 12:12a Lawrance
 * remove unused keys (Alt-H and Alt-F)
 * 
 * 35    10/24/97 11:00p Hoffoss
 * Controls config screen much improved.
 * 
 * 34    10/22/97 4:50p Hoffoss
 * Disabled throttle by default.
 * 
 * 33    10/21/97 7:05p Hoffoss
 * Overhauled the key/joystick control structure and usage throughout the
 * entire FreeSpace code.  The whole system is very different now.
 * 
 * 32    10/18/97 7:19p Hoffoss
 * Added timestamp recording when a key is pressed.
 * 
 * 31    9/14/97 10:24p Lawrance
 * add damage screen popup window
 * 
 * 30    9/10/97 6:02p Hoffoss
 * Added code to check for key-pressed sexp operator in FreeSpace as part
 * of training mission stuff.
 * 
 * 29    9/09/97 9:18a Hoffoss
 * Added message token translation (phase 1) to FreeSpace for training
 * missions support.
 * 
 * 28    8/31/97 6:38p Lawrance
 * pass in frametime to do_frame loop
 * 
 * 27    8/29/97 5:02p Sandeep
 * fixed joystick support for shield config
 * 
 * 26    8/25/97 12:24a Lawrance
 * added keys for shield management
 * 
 * 25    8/22/97 10:44p Sandeep
 * Added Configurable support for energy management keys, keyboard and
 * joystick
 * 
 * 24    8/21/97 5:03p Sandeep
 * Fixed joystick functions past "Target Closest Hostile Targeting Self"
 * bug.
 * 
 * 23    8/20/97 4:22p Sandeep
 * Add support for joystick mapping to all keyboard configurable commands.
 * Changed pilot file to allow support for new joystick, incompatible
 * version 33
 * 
 * 22    8/07/97 11:27p Lawrance
 * add support for 4th joystick axis (rudder), add new option to roll ship
 * 
 * 21    7/08/97 11:37a Lawrance
 * add joystick support for afterburners
 * 
 * 20    7/01/97 11:52a Lawrance
 * add targeting key, allow player to clear all bindings
 * 
 * 19    6/24/97 12:38a Lawrance
 * added in some new joystick bindings
 * 
 * 18    6/17/97 8:57p Lawrance
 * added target previous hostile/friendly
 * 
 * 17    6/03/97 1:39a Allender
 * made macros for joystick button id's
 * 
 * 16    5/28/97 9:53a Lawrance
 * move goals keys and squadmate message key from function keys to
 * assignable keys
 * 
 * 15    5/26/97 5:49p Lawrance
 * supporting max range on radar
 * 
 * 14    5/26/97 3:31p Lawrance
 * assign key bindings for view modes and view controls
 * 
 * 13    5/14/97 10:50a Mike
 * More countermeasure stuff.
 * 
 * 12    4/24/97 2:40p Lawrance
 * add key for targeting closest ship attacking self
 * 
 * 11    4/05/97 3:46p Allender
 * lots 'o messaging stuff.  Make shortcut keys for squadmate messaging
 * work.  Make menus a little more dynamic
 * 
 * 10    4/01/97 7:50p Lawrance
 * added many new keys, don't allow Shft or Alt as action keys, only allow
 * Ctrl as an action key
 * 
 * 9     3/10/97 8:30a Lawrance
 * changed -/+ 5% throttle keys to 1/3 2/3 throttle keys
 * 
 * 8     12/18/96 6:09p Lawrance
 * allowing shift+alt+ctrl modifiers on keyboard bindings
 * 
 * 7     12/18/96 10:18a Lawrance
 * integrating joystick axis configuration
 * 
 * 6     12/17/96 11:10a Lawrance
 * added targeting of subsystem in reticle
 * 
 * 5     12/06/96 12:27a Lawrance
 * adding support for joystick configuration
 * 
 * 4     12/05/96 2:47p Lawrance
 * changed how keyboard configuration was done to make code more easily
 * changeable
 * 
 * 3     12/03/96 10:11p Lawrance
 * Integrating keyboard configuration
 * 
 * 2     12/03/96 3:45p Lawrance
 *
 * $NoKeywords: $
 *
*/

#ifndef CONTROLS_CONFIG_H
#define CONTROLS_CONFIG_H

#define CONTROL_CONFIG_XSTR	507

#define JOY_X_AXIS	0
#define JOY_Y_AXIS	1
#define JOY_Z_AXIS	2
#define JOY_RX_AXIS	3
#define JOY_RY_AXIS	4
#define JOY_RZ_AXIS	5

#define NUM_JOY_AXIS_ACTIONS	5

#define JOY_HEADING_AXIS		0
#define JOY_PITCH_AXIS			1
#define JOY_BANK_AXIS			2
#define JOY_ABS_THROTTLE_AXIS	3
#define JOY_REL_THROTTLE_AXIS	4

// --------------------------------------------------
// different types of controls that can be assigned 
// --------------------------------------------------

#define CC_TYPE_TRIGGER		0
#define CC_TYPE_CONTINUOUS	1

typedef struct config_item {
	short key_default;  // default key bound to action
	short joy_default;  // default joystick button bound to action
	char tab;				// what tab (category) it belongs in
	char *text;				// describes the action in the config screen
	char type;				// manner control should be checked in
	short key_id;  // actual key bound to action
	short joy_id;  // joystick button bound to action
	int used;				// has control been used yet in mission?  If so, this is the timestamp
} config_item;

// --------------------------------------------------
// Keyboard #defines for the actions  
// This is the value of the id field in config_item
// --------------------------------------------------

// targeting a ship

#define TARGET_NEXT										0
#define TARGET_PREV										1
#define TARGET_NEXT_CLOSEST_HOSTILE						2
#define TARGET_PREV_CLOSEST_HOSTILE						3
#define TOGGLE_AUTO_TARGETING							4
#define TARGET_NEXT_CLOSEST_FRIENDLY					5
#define TARGET_PREV_CLOSEST_FRIENDLY					6
#define TARGET_SHIP_IN_RETICLE							7
#define TARGET_CLOSEST_SHIP_ATTACKING_TARGET			8
#define TARGET_LAST_TRANMISSION_SENDER					9
#define STOP_TARGETING_SHIP								10

// targeting a ship's subsystem
#define TARGET_SUBOBJECT_IN_RETICLE						11
#define TARGET_NEXT_SUBOBJECT							12
#define TARGET_PREV_SUBOBJECT							13	
#define STOP_TARGETING_SUBSYSTEM						14

// speed matching 
#define MATCH_TARGET_SPEED								15
#define TOGGLE_AUTO_MATCH_TARGET_SPEED					16

// weapons
#define FIRE_PRIMARY									17
#define FIRE_SECONDARY									18
#define CYCLE_NEXT_PRIMARY								19
#define CYCLE_PREV_PRIMARY								20
#define CYCLE_LINK_MODE_GUNS							21
#define CYCLE_SECONDARY									22
#define CYCLE_NUM_MISSLES								23
#define LAUNCH_COUNTERMEASURE							24
#define FIRE_POD										25

// controls
#define REVERSE_THRUST									26
#define BANK_LEFT										27
#define BANK_RIGHT										28
#define PITCH_FORWARD									29
#define PITCH_BACK										30
#define YAW_LEFT										31
#define YAW_RIGHT										32

// throttle control
#define ZERO_THROTTLE									33
#define MAX_THROTTLE									34
#define ONE_THIRD_THROTTLE								35
#define TWO_THIRDS_THROTTLE								36
#define PLUS_5_PERCENT_THROTTLE							37
#define MINUS_5_PERCENT_THROTTLE						38

// squadmate messaging keys
#define ATTACK_MESSAGE									39
#define DISARM_MESSAGE									40
#define DISABLE_MESSAGE									41
#define ATTACK_SUBSYSTEM_MESSAGE						42
#define CAPTURE_MESSAGE									43
#define ENGAGE_MESSAGE									44
#define FORM_MESSAGE									45
#define IGNORE_MESSAGE									46
#define PROTECT_MESSAGE									47
#define COVER_MESSAGE									48
#define WARP_MESSAGE									49
#define REARM_MESSAGE									50

#define TARGET_CLOSEST_SHIP_ATTACKING_SELF				51

// Views
#define VIEW_CHASE										52
#define VIEW_EXTERNAL									53
#define VIEW_EXTERNAL_TOGGLE_CAMERA_LOCK				54
#define VIEW_SLEW										55
#define VIEW_OTHER_SHIP									56
#define VIEW_DIST_INCREASE								57
#define VIEW_DIST_DECREASE								58
#define VIEW_CENTER										59
#define PADLOCK_UP										60
#define PADLOCK_DOWN									61
#define PADLOCK_LEFT									62
#define PADLOCK_RIGHT									63


#define RADAR_RANGE_CYCLE								64
#define SQUADMSG_MENU									65
#define SHOW_GOALS										66
#define END_MISSION										67
#define TARGET_TARGETS_TARGET							68
//#define AFTERBURNER										68
 
#define INCREASE_WEAPON									69//69
#define DECREASE_WEAPON									70//70
#define INCREASE_SHIELD									71//71
#define DECREASE_SHIELD									72//72
#define INCREASE_ENGINE									73//73
#define DECREASE_ENGINE									74//74
#define ETS_EQUALIZE									75//75
#define SHIELD_EQUALIZE									76//76
#define SHIELD_XFER_TOP									77//77
#define SHIELD_XFER_BOTTOM								78//78
#define SHIELD_XFER_LEFT								79//79
#define SHIELD_XFER_RIGHT								80//80

#define XFER_SHIELD										81
#define XFER_LASER										82
#define SHOW_DAMAGE_POPUP								83 // AL: this binding should be removing next time the controls are reorganized

#define BANK_WHEN_PRESSED								84
#define SHOW_NAVMAP										85
#define ADD_REMOVE_ESCORT								86
#define ESCORT_CLEAR									87
#define TARGET_NEXT_ESCORT_SHIP							88

#define TARGET_CLOSEST_REPAIR_SHIP						89
#define TARGET_NEXT_UNINSPECTED_CARGO					90
#define TARGET_PREV_UNINSPECTED_CARGO					91
#define TARGET_NEWEST_SHIP								92
#define TARGET_NEXT_LIVE_TURRET							93
#define TARGET_PREV_LIVE_TURRET							94

#define TARGET_NEXT_BOMB								95
#define TARGET_PREV_BOMB								96

// multiplayer messaging keys
#define MULTI_MESSAGE_ALL								97
#define MULTI_MESSAGE_FRIENDLY							98
#define MULTI_MESSAGE_HOSTILE							99
#define MULTI_MESSAGE_TARGET							100

// multiplayer misc keys
#define MULTI_OBSERVER_ZOOM_TO							101

#define TIME_SPEED_UP									102
#define TIME_SLOW_DOWN									103

#define TOGGLE_HUD_CONTRAST								104

#define MULTI_TOGGLE_NETINFO							105

#define MULTI_SELF_DESTRUCT								106

#define TOGGLE_HUD										107
#define RIGHT_SLIDE_THRUST								108
#define LEFT_SLIDE_THRUST								109
#define UP_SLIDE_THRUST									110
#define DOWN_SLIDE_THRUST								111
#define HUD_TARGETBOX_TOGGLE_WIREFRAME					112
#define ENTER_HANGAR									113
#define CYCLE_SFOILS									114

// this should be the total number of control action defines above (or last define + 1)
//#define CCFG_MAX 116
//#else
#define CCFG_MAX 115

//#endif

extern int Failed_key_index;
extern int Invert_heading;
extern int Invert_pitch;
extern int Invert_roll;
extern int Invert_thrust;
extern int Disable_axis2;
extern int Disable_axis3;

extern int Axis_map_to[];
extern int Invert_axis[];
extern int Invert_axis_defaults[];

extern config_item Control_config[];	// stores the keyboard configuration
extern char **Scan_code_text;
extern char **Joy_button_text;

// initialize common control config stuff - call at game startup after localization has been initialized
void control_config_common_init();

void control_config_init();
void control_config_do_frame(float frametime);
void control_config_close();

void control_config_cancel_exit();

void control_config_reset_defaults();
int translate_key_to_index(char *key);
char *translate_key(char *key);
char *textify_scancode(int code);
float check_control_timef(int id);
int check_control(int id, int key = -1);
void control_get_axes_readings(int *h, int *p, int *b, int *ta, int *tr);
void control_used(int id);
void control_config_clear();
void clear_key_binding(short key);
void control_check_indicate();
void control_config_clear_used_status();


#endif
