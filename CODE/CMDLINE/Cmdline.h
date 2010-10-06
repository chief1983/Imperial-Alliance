/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *

*/ 

/*
 * $Logfile: /Freespace2/code/Cmdline/cmdline.h $

 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:40 $
 * $Author: Spearhawk $
 *
 * $Log: Cmdline.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:40  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 20:06:59  Darkhill
 * no message
 *
 * Revision 2.54  2004/04/26 18:23:47  Kazan
 * -no_fps_capping
 *
 * Revision 2.53  2004/04/26 00:23:26  taylor
 * novbo and snd_preload cmdline options, fix moddir getting appended space
 *
 * Revision 2.52  2004/04/18 19:39:12  randomtiger
 * Added -2d_poof command which allows access to 2D poof rendering
 * Added -radar_reduce to launcher flag description structure
 *
 * Revision 2.51  2004/04/03 18:11:20  Kazan
 * FRED fixes
 *
 * Revision 2.50  2004/03/20 14:47:12  randomtiger
 * Added base for a general dynamic batching solution.
 * Fixed NO_DSHOW_CODE code path bug.
 *
 * Revision 2.49  2004/03/19 14:51:54  randomtiger
 * New command line parameter: -d3d_lesstmem causes D3D to bypass V's secondry texture system.
 *
 * Revision 2.48  2004/03/19 11:44:04  randomtiger
 * Removed -d3d_notmanaged param.
 * Tided D3D texture code. Merged remaining section code into the rest of the system.
 * Prepared for removal of code causing waste of memory for secondry store of textures.
 *
 * Revision 2.47  2004/02/27 04:09:55  bobboau
 * fixed a Z buffer error in HTL submodel rendering,
 * and glow points,
 * and other stuff
 *
 * Revision 2.46  2004/02/16 11:47:31  randomtiger
 * Removed a lot of files that we dont need anymore.
 * Changed htl to be on by default, command now -nohtl
 * Changed D3D to use a 2D vertex for 2D operations which should cut down on redundant data having to go though the system.
 * Added small change to all -start_mission flag to take you to any mission by filename, very useful for testing.
 * Removed old dshow code and took away timerbar compile flag condition since it uses a runtime flag now.
 *
 * Revision 2.45  2004/01/29 01:34:00  randomtiger
 * Added malloc montoring system, use -show_mem_usage, debug exes only to get an ingame list of heap usage.
 * Also added -d3d_notmanaged flag to activate non managed D3D path, in experimental stage.
 *
 * Revision 2.44  2004/01/24 14:31:27  randomtiger
 * Added the D3D particle code, its not bugfree but works perfectly on my card and helps with the framerate.
 * Its optional and off by default, use -d3d_particle to activiate.
 * Also bumped up D3D ambient light setting, it was way too dark.
 * Its now set to something similar to the original game.
 *
 * Revision 2.43  2003/12/08 22:30:02  randomtiger
 * Put render state and other direct D3D calls repetition check back in, provides speed boost.
 * Fixed bug that caused fullscreen only crash with DXT textures
 * Put dithering back in for tgas and jpgs
 *
 * Revision 2.42  2003/12/04 20:39:09  randomtiger
 * Added DDS image support for D3D
 * Added new command flag '-ship_choice_3d' to activate 3D models instead of ani's in ship choice, feature now off by default
 * Hopefully have fixed D3D text batching bug that caused old values to appear
 * Added Hud_target_object_factor variable to control 3D object sizes of zoom in HUD target
 * Fixed jump nodes not showing
 *
 * Revision 2.41  2003/12/03 19:27:00  randomtiger
 * Changed -t32 flag to -jpgtga
 * Added -query_flag to identify builds with speech not compiled and other problems
 * Now loads up launcher if videocard reg entry not found
 * Now offers to go online to download launcher if its not present
 * Changed target view not to use lower res texture, hi res one is already chached so might as well use it
 *
 * Revision 2.40  2003/11/29 10:52:09  randomtiger
 * Turned off D3D file mapping, its using too much memory which may be hurting older systems and doesnt seem to be providing much of a speed benifit.
 * Added stats command for ingame stats on memory usage.
 * Trys to play intro.mve and intro.avi, just to be safe since its not set by table.
 * Added fix for fonts wrapping round in non standard hi res modes.
 * Changed D3D mipmapping to a good value to suit htl mode.
 * Added new fog colour method which makes use of the bitmap, making this htl feature backcompatible again.
 *
 * Revision 2.39  2003/11/19 20:37:23  randomtiger
 * Almost fully working 32 bit pcx, use -pcx32 flag to activate.
 * Made some commandline variables fit the naming standard.
 * Changed timerbar system not to run pushes and pops if its not in use.
 * Put in a note about not uncommenting asserts.
 * Fixed up a lot of missing POP's on early returns?
 * Perhaps the motivation for Assert functionality getting commented out?
 * Fixed up some bad asserts.
 * Changed nebula poofs to render in 2D in htl, it makes it look how it used to in non htl. (neb.cpp,1248)
 * Before the poofs were creating a nasty stripe effect where they intersected with ships hulls.
 * Put in a special check for the signs of that D3D init bug I need to lock down.
 *
 * Revision 2.38  2003/11/15 18:09:33  randomtiger
 * Put TGA and JPG stuff on -t32 flag
 * Put 32 bit PCX stuff on -pcx32 (still has bugs)
 * Added multisample checking on device initialisation
 * Changed unrecognised parameter message (as requested) to be more user friendly
 * Speech now chooses voice based on reg value set by launcher v3.1
 *
 * Revision 2.37  2003/11/09 06:31:38  Kazan
 * a couple of htl functions being called in nonhtl (ie NULL functions) problems fixed
 * conflicts in cmdline and timerbar.h log entries
 * cvs stopped acting like it was on crack obviously
 *
 * Revision 2.36  2003/11/09 04:09:18  Goober5000
 * edited for language
 * --Goober5000
 *
 * Revision 2.35  2003/11/08 22:25:47  Kazan
 * Timerbar was enabled in both release and debug - so i made it a command line option "-timerbar"
 * DONT MESS WITH OTHER PEOPLES INCLUDE PATHS
 * DONT MESS WITH EXEC NAMES (leave it fs2_open_r and fs2_open_d) or paths!
 *
 * Revision 2.34  2003/11/03 18:07:26  randomtiger
 * Added -d3d_no_vsync command to make turning off vsync optional.
 * Removed 32bit command, it doesnt do anything.
 * Made aa multisample reg check safe.
 *
 * Revision 2.33  2003/10/27 23:04:20  randomtiger
 * Added -no_set_gamma flags
 * Fixed up some more non standard res stuff
 * Improved selection of device type, this includes using a pure device when allowed which means dev should not use Get* functions in D3D
 * Made fade in credits work
 * Stopped a call to gr_reser_lighting() in non htl mode when the pointer was NULL, was causing a crash loading a fogged level
 * Deleted directx8 directory content, has never been needed.
 *
 * Revision 2.32  2003/10/24 17:35:04  randomtiger
 * Implemented support for 32bit TGA and JPG for D3D
 * Also 32 bit PCX, but it still has some bugs to be worked out
 * Moved convert_24_to_16 out of the bitmap pfunction structures and into packunpack.cpp because thats the only place that uses it.
 *
 * Revision 2.31  2003/10/17 17:18:42  randomtiger
 * Big restructure for D3D and new modules grd3dlight and grd3dsetup
 *
 * Revision 2.30  2003/10/12 03:41:37  Kazan
 * #Kazan# FS2NetD client code gone multithreaded, some Fred2 Open -mod stuff [obvious code.lib] including a change in cmdline.cpp, changed Stick's "-nohtl" to "-htl" - HTL is _OFF_ by default here (Bobboau and I decided this was a better idea for now)
 *
 * Revision 2.29  2003/09/25 21:12:22  Kazan
 * ##Kazan## FS2NetD Completed!  Just needs some thorough bug checking (i don't think there are any serious bugs)
 * Also D3D8 Screenshots work now.
 *
 * Revision 2.28  2003/09/23 02:42:52  Kazan
 * ##KAZAN## - FS2NetD Support! (FS2 Open PXO) -- Game Server Listing, and mission validation completed - stats storing to come - needs fs2open_pxo.cfg file [VP-able]
 *
 * Revision 2.27  2003/09/14 19:00:02  wmcoolmon
 * Changed "nospec" and "cell" to "Cmdline_nospec" and "Cmdline_cell"
 *
 * Revision 2.26  2003/09/14 18:32:24  wmcoolmon
 * Added "-safeloading" command line parameter, which uses old fs2_retail-style loading code -C
 *
 * Revision 2.25  2003/09/13 06:02:05  Goober5000
 * clean rollback of all of argv's stuff
 * --Goober5000
 *
 * Revision 2.23  2003/08/22 07:35:08  bobboau
 * specular code should be bugless now,
 * cell shadeing has been added activated via the comand line '-cell',
 * 3D shockwave models, and a transparency method I'm calling edge and center alpha that could be usefull for other things, ask for details
 *
 * Revision 2.22  2003/08/21 20:54:37  randomtiger
 * Fixed switching - RT
 *
 * Revision 2.21  2003/08/12 03:18:33  bobboau
 * Specular 'shine' mapping;
 * useing a phong lighting model I have made specular highlights
 * that are mapped to the model,
 * rendering them is still slow, but they look real purdy
 *
 * also 4 new (untested) comand lines, the XX is a floating point value
 * -spec_exp XX
 * the n value, you can set this from 0 to 200 (actualy more than that, but this is the recomended range), it will make the highlights bigger or smaller, defalt is 16.0 so start playing around there
 * -spec_point XX
 * -spec_static XX
 * -spec_tube XX
 * these are factors for the three diferent types of lights that FS uses, defalt is 1.0,
 * static is the local stars,
 * point is weapons/explosions/warp in/outs,
 * tube is beam weapons,
 * for thouse of you who think any of these lights are too bright you can configure them you're self for personal satisfaction
 *
 * Revision 2.20  2003/08/09 06:07:23  bobboau
 * slightly better implementation of the new zbuffer thing, it now checks only three diferent formats defalting to the 16 bit if neither the 24 or 32 bit versions are suported
 *
 * Revision 2.19  2003/03/29 09:42:05  Goober5000
 * made beams default shield piercing again
 * also added a beam no pierce command line flag
 * and fixed something else which I forgot :P
 * --Goober5000
 *
 * Revision 2.18  2003/03/18 10:07:00  unknownplayer
 * The big DX/main line merge. This has been uploaded to the main CVS since I can't manage to get it to upload to the DX branch. Apologies to all who may be affected adversely, but I'll work to debug it as fast as I can.
 *
 * Revision 2.17  2003/02/22 04:13:17  wmcoolmon
 * Added "-dshowvid" command-line option, which must be set in order for movies to play.
 *
 * Revision 2.16  2002/12/21 13:39:25  DTP
 * did bit more house keeping. modfied Phreaks fps cmdline a bit, so that we dont have to specific build code.libs for fred, but can use the same code.lib for both fs2_open.exe and fred2_open.exe
 *
 * Revision 2.15  2002/12/17 03:08:18  DTP
 * fix to Show_framerate. seems it will call an unresolved external error during fred builds. modified my ifndefs a bit, dsw modified to include preprocessor tag FRED.
 *
 * Revision 2.14  2002/12/17 02:22:34  DTP
 * wrong name :)
 *
 * Revision 2.13  2002/12/17 02:21:06  DTP
 * cleaned up after phreak :). it will make a mess in debug builds. added a couple of ifndef _debugs.
 *
 * Revision 2.12  2002/11/10 16:30:53  DTP
 * -DTP reworked mod support,
 *
 * Revision 2.11  2002/10/31 21:14:16  DTP
 * DTP Quickly added something needed to cmdline.h, since otherwise we can not compile the code as it misses some externals. Thought a rollback rolled all back.
 *
 * Revision 2.10  2002/10/30 20:22:30  inquisitor
 * Bad Committ, Rolling back
 *
 * Revision 2.7  2002/10/22 23:02:39  randomtiger
 * Made Phreaks alternative scanning style optional under the command line tag "-phreak"
 * Fixed bug that changes HUD colour when targetting debris in a full nebula. - RT
 *
 * Revision 2.6  2002/10/19 03:50:28  randomtiger
 * Added special pause mode for easier action screenshots.
 * Added new command line parameter for accessing all single missions in tech room. - RT
 *
 * Revision 2.5  2002/08/27 13:38:57  penguin
 * Moved DirectX8 stuff to directx8 branch; reverted to previous
 *
 * Revision 2.3.2.4  2002/11/10 11:32:29  randomtiger
 *
 * Made D3D8 mipmapping optional on command line flag -d3dmipmip, off by default.
 * When on is now less blury. - RT
 *
 * Revision 2.3.2.3  2002/11/04 23:53:24  randomtiger
 *
 * Added new command line parameter -d3dlauncher which brings up the launcher.
 * This is needed since FS2 DX8 now stores the last successful details in the registry and
 * uses them to choose the adapter and mode to run in unless its windowed or they are not set.
 * Added some code for Antialiasing but it messes up the font but hopefully that can be fixed later. - RT
 *
 * Revision 2.3.2.2  2002/11/04 21:24:59  randomtiger
 *
 * When running in D3D all ani's are memory mapped for speed, this takes up more memory but stops gametime locking of textures which D3D8 hates.
 * Added new command line tag Cmdline_d3dlowmem for people who dont want to make use of this because they have no memory.
 * Cleaned up some more texture stuff enabled console debug for D3D.
 *
 * Revision 2.3.2.1  2002/08/27 13:19:02  penguin
 * Moved to directx8 branch
 *
 * Revision 2.4  2002/08/18 19:48:28  randomtiger
 * Added new lib files: strmiids and ddraw to get dshow working
 * Added new command line parameter to active direct show movie play: -dshowvid
 * Uncommented movie_play calls and includes
 *
 * Revision 2.3  2002/08/07 00:44:13  DTP
 * Implented -GF4FIX commandline switch
 *
 * Revision 2.2  2002/07/29 06:35:15  DTP
 * added -almission commandline arguement, will autoload mission i.e fs2_open.exe -almission kickass will autoload kickass.fs2 which should be a multiplayer mission.
 *
 * Revision 2.1  2002/07/07 19:55:58  penguin
 * Back-port to MSVC
 *
 * Revision 2.0  2002/06/03 04:02:21  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/08 17:29:17  mharris
 * more port tweaks
 *
 * Revision 1.1  2002/05/02 18:03:04  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 8     8/26/99 8:51p Dave
 * Gave multiplayer TvT messaging a heavy dose of sanity. Cheat codes.
 * 
 * 7     7/15/99 3:07p Dave
 * 32 bit detection support. Mouse coord commandline.
 * 
 * 6     7/13/99 1:15p Dave
 * 32 bit support. Whee!
 * 
 * 5     6/22/99 9:37p Dave
 * Put in pof spewing.
 * 
 * 4     1/12/99 5:45p Dave
 * Moved weapon pipeline in multiplayer to almost exclusively client side.
 * Very good results. Bandwidth goes down, playability goes up for crappy
 * connections. Fixed object update problem for ship subsystems.
 * 
 * 3     11/17/98 11:12a Dave
 * Removed player identification by address. Now assign explicit id #'s.
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:48a Dave
 * 
 * 27    9/15/98 4:04p Allender
 * added back in the -ip_addr command line switch because it needs to be
 * in the standalone server only executable
 * 
 * 26    9/14/98 11:28a Allender
 * support for server bashing of address when received from client.  Added
 * a cmdline.cfg file to process command line arguments from a file
 * 
 * 25    9/08/98 2:20p Allender
 * temporary code to force IP address to a specific value.
 * 
 * 24    8/20/98 5:30p Dave
 * Put in handy multiplayer logfile system. Now need to put in useful
 * applications of it all over the code.
 * 
 * 23    8/07/98 10:40a Allender
 * new command line flags for starting netgames.  Only starting currently
 * works, and PXO isn't implemented yet
 * 
 * 22    7/24/98 11:14a Allender
 * start of new command line options for version 1.04
 * 
 * 21    5/21/98 1:50a Dave
 * Remove obsolete command line functions. Reduce shield explosion packets
 * drastically. Tweak PXO screen even more. Fix file xfer system so that
 * we can guarantee file uniqueness.
 * 
 * 20    5/18/98 9:10p Dave
 * Put in many new PXO features. Fixed skill level bashing in multiplayer.
 * Removed several old command line options. Put in network config files.
 * 
 * 19    5/09/98 7:16p Dave
 * Put in CD checking. Put in standalone host password. Made pilot into
 * popup scrollable.
 * 
 * 18    4/23/98 8:27p Allender
 * basic support for cutscene playback.  Into movie code in place.  Tech
 * room can view cutscenes stored in CDROM_dir variable
 * 
 * 17    3/14/98 2:48p Dave
 * Cleaned up observer joining code. Put in support for file xfers to
 * ingame joiners (observers or not). Revamped and reinstalled pseudo
 * lag/loss system.
 * 
 * 16    1/31/98 4:32p Dave
 * Put in new support for VMT player validation, game logging in and game
 * logging out.
 * 
 * 15    12/10/97 4:45p Dave
 * Added in more detailed support for multiplayer packet lag/loss. Fixed
 * some multiplayer stuff. Added some controls to the standalone.
 * 
 * 14    12/09/97 6:14p Lawrance
 * add -nomusic flag
 * 
 * 13    11/28/97 7:04p Dave
 * Emergency checkin due to big system crash.
 * 
 * 12    11/28/97 5:06p Dave
 * Put in facilities for simulating multiplayer lag.
 * 
 * 11    11/24/97 5:42p Dave
 * Fixed a file xfer buffer free/malloc problem. Lengthened command line
 * switch string parse length.
 * 
 * 10    11/12/97 4:39p Dave
 * Put in multiplayer campaign support parsing, loading and saving. Made
 * command-line variables better named. Changed some things on the initial
 * pilot select screen.
 * 
 * 9     11/11/97 4:54p Dave
 * Put in support for single vs. multiplayer pilots. Put in initial player
 * selection screen (no command line option yet). Started work on
 * multiplayer campaign file save gaming.
 * 
 * 8     9/18/97 10:13p Dave
 * Added -gimmemedals, which gives the current pilot all the medals in the
 * game (debug)
 * 
 * 7     9/18/97 9:20a Dave
 * Minor modifications
 * 
 * 6     9/15/97 11:40p Lawrance
 * remove demo granularity switch
 * 
 * 5     9/03/97 5:03p Lawrance
 * add support for -nosound command line parm
 * 
 * 4     8/21/97 4:55p Dave
 * Added a switch for multiplayer chat streaming. Added a section for
 * global command line vars.
 * 
 * 3     8/06/97 2:26p Dave
 * Made the command line parse more robust. Made it easier to add and
 * process new command-line switches.
 * 
 * 2     8/04/97 3:13p Dave
 * Added command line functions. See cmdline.cpp for directions on adding
 * new switches
 * 
 * 1     8/04/97 9:58a Dave
 * 
 * $NoKeywords: $
 */

#ifndef FS_CMDLINE_HEADER_FILE
#define FS_CMDLINE_HEADER_FILE

#ifdef _WIN32
int parse_cmdline(char *cmdline);
#else
int parse_cmdline(int argc, char *argv[]);
#endif

int fred2_parse_cmdline(int argc, char *argv[]);
// COMMAND LINE SETTINGS
// This section is for reference by all the *_init() functions. For example, the multiplayer init function
// could check to see if (int Cmdline_multi_stream_chat_to_file) has been set by the command line parser.
//
// Add any extern definitions here and put the actual variables inside of cmdline.cpp for ease of use
// Also, check to make sure anything you add doesn't break Fred or TestCode

extern int Cmdline_multi_stream_chat_to_file;
extern int Cmdline_freespace_no_sound;
extern int Cmdline_freespace_no_music;
extern int Cmdline_use_last_pilot;
extern int Cmdline_cd_check;
extern int Cmdline_start_netgame;
extern int Cmdline_closed_game;
extern int Cmdline_restricted_game;
extern int Cmdline_network_port;
extern char *Cmdline_game_name;
extern char *Cmdline_game_password;
extern char *Cmdline_rank_above;
extern char *Cmdline_rank_below;
extern char *Cmdline_connect_addr;
extern int Cmdline_multi_log;
extern int Cmdline_server_firing;
extern int Cmdline_client_dodamage;
extern int Cmdline_spew_pof_info;
extern int Cmdline_mouse_coords;
extern int Cmdline_timeout;
extern int Cmdline_SpewMission_CRCs;
extern int Cmdline_SpewTable_CRCs;

extern int Cmdline_window;
extern char *Cmdline_almission;	//DTP for autoload mission
extern int Cmdline_gf4fix;	//DTP for Random tigers GF4fix.
extern int Cmdline_allslev;
extern int Cmdline_phreak;
extern int Cmdline_dnoshowvid;	//WMC Toggles movie playing support
extern char *Cmdline_mod; //DTP for mod support
extern int Cmdline_show_fps;//DTP moved here because it is the correct place for it to be.
extern int Cmdline_show_stats;
extern int Cmdline_safeloading;
extern int Cmdline_nospec;

extern int Cmdline_cache_ani;
extern int Cmdline_d3dmipmap;

extern int Cmdline_beams_no_pierce_shields;	// Goober5000
extern float Cmdline_fov;

extern float static_light_factor;
extern float static_tube_factor;
extern float static_point_factor;
extern double specular_exponent_value;

extern int Cmdline_cell;
extern int Cmdline_nohtl;
extern int Cmdline_dxt;
extern int Cmdline_jpgtga;
extern int Cmdline_no_set_gamma;
extern int Cmdline_d3d_no_vsync;
extern int Cmdline_pcx32;

extern int Cmdline_noglow;
extern int Cmdline_timerbar;
extern int Cmdline_query_speech;
extern int Cmdline_ship_choice_3d;
extern int Cmdline_d3d_particle;

extern int Cmdline_ambient_factor;
extern int Cmdline_show_mem_usage;
extern int Cmdline_rt;
extern char *Cmdline_start_mission;

extern int Cmdline_d3d_lesstmem;
extern int Cmdline_batch_3dunlit;

extern int Cmdline_2d_poof;

extern int Cmdline_FRED2_htl;
extern int CmdLine_FRED2_NoWarn;

extern int Cmdline_novbo;
extern int Cmdline_snd_preload;
extern int Cmdline_NoFPSCap;

extern int Cmdline_UseJukebox;
extern int Cmdline_UseTwoRadar;

extern int Cmdline_gimme_all_medals;
extern int Cmdline_make_me_admiral;

extern int Cmdline_debug_hud;

//extern char FreeSpace_Directory[]; // allievating a cfilesystem problem caused by fred -- Kazan
#endif
