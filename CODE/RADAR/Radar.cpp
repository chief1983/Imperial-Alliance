/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Radar/Radar.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * C module containg functions to display and manage the radar
 *
 * $Log: Radar.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:32:56  Darkhill
 * no message
 *
 * Revision 2.6  2004/07/18 15:37:41  Spearhawk
 * Added a option for using two radar screens (front and back) instead of one
 * set the extern bool useTwoRadarScreens to decide which mode is used
 *
 * Revision 2.5  2003/08/31 06:00:41  bobboau
 * an asortment of bugfixes, mostly with the specular code,
 * HUD flickering should be completly gone now
 *
 * Revision 2.4  2003/06/11 03:15:17  phreak
 * i hate to update again so soon, but i forgot to mark hostile local ssms that
 * were in stages 2 or 4 as warping so their blip color would then be blue
 *
 * Revision 2.3  2003/06/11 03:01:27  phreak
 * the radar will not show stage 3 local ssms
 *
 * Revision 2.2  2003/01/03 21:58:07  Goober5000
 * Fixed some minor bugs, and added a primitive-sensors flag, where if a ship
 * has primitive sensors it can't target anything and objects don't appear
 * on radar if they're outside a certain range.  This range can be modified
 * via the sexp primitive-sensors-set-range.
 * --Goober5000
 *
 * Revision 2.1  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:27  penguin
 * Warpcore CVS sync
 *
 * Revision 1.3  2002/05/13 21:09:28  mharris
 * I think the last of the networking code has ifndef NO_NETWORK...
 *
 * Revision 1.2  2002/05/04 04:52:22  mharris
 * 1st draft at porting
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 14    8/23/99 8:38p Andsager
 * Added see_all debug console command for turning radar range infinite in
 * nebula (but not targeting).
 * 
 * 13    6/10/99 3:43p Dave
 * Do a better job of syncing text colors to HUD gauges.
 * 
 * 12    6/07/99 4:21p Andsager
 * Add HUD color for tagged object.  Apply to target and radar.
 * 
 * 11    6/02/99 12:52p Andsager
 * Added team-wide ship visibility.  Implemented for player.
 * 
 * 10    1/25/99 5:03a Dave
 * First run of stealth, AWACS and TAG missile support. New mission type
 * :)
 * 
 * 9     1/12/99 5:45p Dave
 * Moved weapon pipeline in multiplayer to almost exclusively client side.
 * Very good results. Bandwidth goes down, playability goes up for crappy
 * connections. Fixed object update problem for ship subsystems.
 * 
 * 8     12/30/98 9:34a Jasen
 * updated coords for hi res
 * 
 * 7     12/29/98 7:29p Dave
 * Added some missing hi-res hud coord globalizations.
 * 
 * 6     12/29/98 2:30p Jasen
 * added some new coords for 1024 HUD stuff
 * 
 * 5     12/28/98 3:17p Dave
 * Support for multiple hud bitmap filenames for hi-res mode.
 * 
 * 4     11/05/98 4:18p Dave
 * First run nebula support. Beefed up localization a bit. Removed all
 * conditional compiles for foreign versions. Modified mission file
 * format.
 * 
 * 3     10/13/98 9:29a Dave
 * Started neatening up freespace.h. Many variables renamed and
 * reorganized. Added AlphaColors.[h,cpp]
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 90    8/28/98 3:29p Dave
 * EMP effect done. AI effects may need some tweaking as required.
 * 
 * 89    8/25/98 1:48p Dave
 * First rev of EMP effect. Player side stuff basically done. Next comes
 * AI code.
 * 
 * 88    6/12/98 4:52p Hoffoss
 * Added support for special characters in in forgeign languages.
 * 
 * 87    6/09/98 10:31a Hoffoss
 * Created index numbers for all xstr() references.  Any new xstr() stuff
 * added from here on out should be added to the end if the list.  The
 * current list count can be found in FreeSpace.cpp (search for
 * XSTR_SIZE).
 * 
 * 86    5/19/98 10:26a John
 * Fixed bug with radar blips not drawing in hardware.
 * 
 * 85    5/19/98 9:12a John
 * Made radar blips render as font characters 132 and 133.   Needs a new
 * font01.vf in the data tree.
 * 
 * 84    5/08/98 11:22a Allender
 * fix ingame join trouble.  Small messaging fix.  Enable collisions for
 * friendlies again
 * 
 * 83    5/01/98 12:24p Jim
 * don't process radar_plot_obj on the standalone server
 * 
 * 82    4/07/98 4:05p Lawrance
 * Only show hostile bombs on radar.
 * 
 * 81    3/26/98 5:26p John
 * added new paging code. nonfunctional.
 * 
 * 80    3/15/98 3:11p Lawrance
 * Always draw target radar blip bright.
 * 
 * 79    3/11/98 5:33p Lawrance
 * Support rendering and targeting of jump nodes
 * 
 * 78    3/03/98 8:12p Lawrance
 * Draw cargo as gray dots
 * 
 * 77    2/22/98 4:30p John
 * More string externalization classification
 * 
 * 76    2/22/98 2:48p John
 * More String Externalization Classification
 * 
 * 75    2/21/98 3:26p Lawrance
 * Improve how blips get drawn for ships immune to sensors.
 * 
 * 74    2/16/98 11:58p Lawrance
 * Add support for SF_HIDDEN_FROM_SENSORS flag.
 * 
 * 73    2/13/98 4:08p Lawrance
 * Use more accurate distance formula when plotting radar dots... fixes
 * "dead zone" black spot.
 * 
 * 72    2/12/98 4:58p Lawrance
 * Change to new flashing method.
 * 
 * 71    2/11/98 12:04a Lawrance
 * Only show bombs on radar, change code to use much less data.
 * 
 * 70    2/10/98 11:46a Lawrance
 * Ensure TEAM_TRAITOR views other TEAM_TRAITOR ships as hostile.
 * 
 *
 * $NoKeywords: $
 *
 */


#include "globalincs/pstypes.h"
#include "globalincs/alphacolors.h"
#include "graphics/font.h"
#include "math/floating.h"
#include "graphics/2d.h"
#include "render/3d.h"
#include "math/vecmat.h"
#include "palman/palman.h"
#include "bmpman/bmpman.h"
#include "object/object.h"
#include "ship/ship.h"
#include "playerman/player.h"
#include "weapon/weapon.h"
#include "io/timer.h"
#include "ship/ai.h"
#include "io/key.h"
#include "hud/hud.h"
#include "hud/hudtarget.h"
#include "hud/hudconfig.h"
#include "ship/subsysdamage.h"
#include "gamesnd/gamesnd.h"
#include "radar/radar.h"
#include "globalincs/linklist.h"
#include "network/multi.h"
#include "weapon/emp.h"
#include "freespace2/freespace.h"
#include "localization/localize.h"
#include "ship/awacs.h"
#include "Cmdline/cmdline.h"

//bool useTwoRadarScreens = false;

int Radar_radius[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		83,83 //120, 100
	},
	{ // GR_1024
		192, 160
	}
};

float Radar_center[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		62.0f, 46.0f //322.0f, 422.0f
	},
	{ // GR_1024
		515.0f, 675.0f
	}
};

float Radar_centerR[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		578.0f, 46.0f//574.0f, 54.0f
	},
	{ // GR_1024
		915.0f, 85.0f
	}
};

float Radar_centerL[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		62.0f, 46.0f //64.0f, 54.0f
	},
	{ // GR_1024
		101.0f, 85.0f
	}
};

int Radar_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		1,1 // 257, 369 
	}, 
	{ // GR_1024
		411, 590
	}
};

int Radar_coordsR[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		530, 1 // 510, 0
	}, 
	{ // GR_1024
		812, 0
	}
};

int Radar_coordsL[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		1, 1//0, 0
	}, 
	{ // GR_1024
		0, 0
	}
};

char RadarO_fname[GR_NUM_RESOLUTIONS][MAX_FILENAME_LEN] = {
	"RadarO",
	"2_RadarO"
};

char RadarL_fname[GR_NUM_RESOLUTIONS][MAX_FILENAME_LEN] = {
	"RadarL",
	"2_RadarL"
};

char RadarR_fname[GR_NUM_RESOLUTIONS][MAX_FILENAME_LEN] = {
	"RadarR",
	"2_RadarR"
};

int Radar_blip_radius_normal[GR_NUM_RESOLUTIONS] = {
	2,
	4
};
int Radar_blip_radius_target[GR_NUM_RESOLUTIONS] = {
	5,
	8
};

#define BLIP_MUTATE_TIME	100

float radx, rady;

#define MAX_RADAR_LEVELS	2		// bright and dim radar dots are allowed

#define BLIP_CURRENT_TARGET	(1<<0)
#define BLIP_DRAW_DIM			(1<<1)	// object is farther than Radar_dim_range units away
#define BLIP_DRAW_DISTORTED	(1<<2)	// object is resistant to sensors, so draw distorted

typedef struct blip	{
	blip	*prev, *next;
	int	x, y, rad;
	int	flags;	// BLIP_ flags defined above
} blip;

#define MAX_BLIPS 150
typedef struct rcol {
	ubyte	r, g, b;
} rcol;

#define	MAX_RADAR_COLORS		12

#define	RCOL_REBEL				0
#define	RCOL_IMPERIAL			1
#define	RCOL_BLUE				2
#define	RCOL_PURPLE				3
#define RCOL_YELLOW				4
#define RCOL_RED				5
#define RCOL_ORANGE				6
#define	RCOL_BOMB				7
#define	RCOL_NAVBUOYS			8
#define RCOL_WARPING_SHIP		9
#define	RCOL_JUMP_NODE			10
#define	RCOL_TAGGED				11

static float	Radar_dim_range;					// range at which we start dimming the radar blips
static int		Radar_calc_dim_dist_timer;		// timestamp at which we recalc Radar_dim_range

#define NUM_FLICKER_TIMERS	2
static int Radar_flicker_timer[NUM_FLICKER_TIMERS];					// timestamp used to flicker blips on and off
static int Radar_flicker_on[NUM_FLICKER_TIMERS];						// status of flickering

#define	RADAR_BLIP_BRIGHT		0				
#define	RADAR_BLIP_DIM			1

rcol Radar_color_rgb[MAX_RADAR_LEVELS][MAX_RADAR_COLORS] = {
	{{ 0x00, 0xff, 0x00},			// rebel				(green)
	{ 0xff, 0x00, 0x00},			// imperial				(red)
	{ 0x00, 0x00, 0xff},			// blue
	{ 0xff, 0x00, 0xff},			// purple
	{ 0xff, 0xff, 0x00},			// yellow
	{ 0xff, 0x00, 0x00},			// red
	{ 0xff, 0x80, 0x00},			// orange
	{ 0x7f, 0x7f, 0x00},			// homing missile (yellow)
	{ 0x7f, 0x7f, 0x7f},			// navbuoy or cargo	(gray)
	{ 0x64, 0x64, 0xc8},			// warp ship		(blueish)
	{ 0x7f, 0x7f, 0x7f},			// jump node		(gray)
	{ 0x95, 0x95, 0x00}},		// tagged	 		(yellow)

	// 1/3 intensity of above colors
	{{ 0x00, 0x7f, 0x00},			// rebel			(green)
	{ 0x7f, 0x00, 0x00},			// imperial			(red)
	{ 0x00, 0x00, 0x7f},			// 	blue
	{ 0x7f, 0x00, 0x7f},			// 	purple
	{ 0x7f, 0x7f, 0x00},			// 	yellow
	{ 0x7f, 0x00, 0x00},			// 	red
	{ 0x7f, 0x00, 0x00},			// 	orange
	{ 0x40, 0x40, 0x00},			// homing missile (yellow)
	{ 0x40, 0x40, 0x40},			// navbuoy or cargo	(gray)
	{ 0x00, 0x00, 0x7f},			// warp ship		(blue)
	{ 0x32, 0x32, 0x64},			// jump node		(gray)
	{ 0x4b, 0x4b, 0x00}},		// tagged			(yellow)
};

color Radar_colors[MAX_RADAR_LEVELS][MAX_RADAR_COLORS];

blip	Blip_bright_list[MAX_RADAR_COLORS];		// linked list of bright blips
blip	Blip_dim_list[MAX_RADAR_COLORS];			// linked list of dim blips
blip	Blips[MAX_BLIPS];								// blips pool
int	N_blips;											// next blip index to take from pool

float Radar_farthest_dist = 1000.0f;
static int Blip_mutate_id;

static int Radar_static_playing;			// is static currently playing on the radar?
static int Radar_static_next;				// next time to toggle static on radar
static int Radar_avail_prev_frame;		// was radar active last frame?
static int Radar_death_timer;				// timestamp used to play static on radar
int Radar_static_looping;					// id for looping radar static sound

static hud_frames RadarO_gauge;
static hud_frames RadarL_gauge;
static hud_frames RadarR_gauge;

int Radar_dist_coords[GR_NUM_RESOLUTIONS][RR_MAX_RANGES][2] = 
{
	{ // GR_640
		{8,81},//{367, 461},								// short
		{5,81}, //{364, 461},								// long
		{9,81}//{368, 461}								// infinity
	},
	{ // GR_1024
		{595, 740},								// short
		{592, 740},								// long
		{596, 741}								// infinity
	}
};

int Radar_dist_coordsL[GR_NUM_RESOLUTIONS][RR_MAX_RANGES][2] = 
{
	{ // GR_640
		{8,81},//{367, 461},								// short
		{5,81}, //{364, 461},								// long
		{9,81}//{368, 461}								// infinity
	},
	{ // GR_1024
		{184, 150},								// short
		{181, 150},								// long
		{185, 151}								// infinity
	}
};

int Radar_dist_coordsR[GR_NUM_RESOLUTIONS][RR_MAX_RANGES][2] = 
{
	{ // GR_640
		{615, 81},	//620, 617, 621							// short
		{612, 81},								// long
		{616, 81}								// infinity
	},
	{ // GR_1024
		{996, 150},								// short
		{993, 150},								// long
		{997, 151}								// infinity
	}
};

// forward declarations
void draw_radar_blips(int desired_color, int is_dim, int distort=0);

void radar_init()
{
	int i,j;

	RadarO_gauge.first_frame = bm_load_animation(RadarO_fname[gr_screen.res], &RadarO_gauge.num_frames);
	if ( RadarO_gauge.first_frame < 0 ) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", RadarO_fname[gr_screen.res]);
	}

	RadarL_gauge.first_frame = bm_load_animation(RadarL_fname[gr_screen.res], &RadarL_gauge.num_frames);
	if ( RadarL_gauge.first_frame < 0 ) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", RadarL_fname[gr_screen.res]);
	}
	
	RadarR_gauge.first_frame = bm_load_animation(RadarR_fname[gr_screen.res], &RadarR_gauge.num_frames);
	if ( RadarR_gauge.first_frame < 0 ) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", RadarR_fname[gr_screen.res]);
	}

	for (i=0; i<MAX_RADAR_LEVELS; i++ )	{
		for (j=0; j<MAX_RADAR_COLORS; j++ )	{
			gr_init_alphacolor( &Radar_colors[i][j], Radar_color_rgb[i][j].r, Radar_color_rgb[i][j].g, Radar_color_rgb[i][j].b, 255 );
		}
	}

	Blip_mutate_id	= 1;
}

// determine what color the object blip should be drawn as
int radar_blip_color(object *objp)
{
	int	color = 0;
	ship	*shipp = NULL;

	switch(objp->type) {
	case OBJ_SHIP:
		shipp = &Ships[objp->instance];
		if ( shipp->flags & SF_ARRIVING_STAGE_1 )	{
			color = RCOL_WARPING_SHIP;
		} else if ( ship_is_tagged(objp) ) {
			color = RCOL_TAGGED;
		} else if ( Ship_info[shipp->ship_info_index].flags & (SIF_NAVBUOY|SIF_CARGO) ) {
			color = RCOL_NAVBUOYS;
//		} else if ( shipp->team == TEAM_TRAITOR) {
//			color = RCOL_RED;
		} else {
			switch (shipp->iff)
				{
				case IFF_COLOR_REBEL:
					color = RCOL_REBEL;
					break;
				case IFF_COLOR_IMPERIAL:
					color = RCOL_IMPERIAL;
					break;
				case IFF_COLOR_BLUE:
					color = RCOL_BLUE;
					break;
				case IFF_COLOR_PURPLE:
					color = RCOL_PURPLE;
					break;
				case IFF_COLOR_YELLOW:
					color = RCOL_YELLOW;
					break;
				case IFF_COLOR_RED:
					color = RCOL_RED;
					break;
				case IFF_COLOR_ORANGE:
					color = RCOL_ORANGE;
					break;
				}
		}
		break;
	case OBJ_WEAPON:
		if ((Weapons[objp->instance].lssm_stage==2) || (Weapons[objp->instance].lssm_stage==4))
			color=RCOL_WARPING_SHIP;
		else
			color = RCOL_BOMB;
		break;
	case OBJ_JUMP_NODE:
		color = RCOL_JUMP_NODE;
		break;
	default:
		Error(LOCATION, "Illegal ship type in radar.");
		break;
	}

	return color;

	/*
	switch(objp->type) {
	case OBJ_SHIP:
		shipp = &Ships[objp->instance];
		if ( shipp->flags & SF_ARRIVING_STAGE_1 )	{
			color = RCOL_WARPING_SHIP;
		} else if ( ship_is_tagged(objp) ) {
			color = RCOL_TAGGED;
		} else if ( Ship_info[shipp->ship_info_index].flags & (SIF_NAVBUOY|SIF_CARGO) ) {
			color = RCOL_NAVBUOYS;
		} else {
			if ( (Player_ship->team == shipp->team) && (Player_ship->team != TEAM_TRAITOR) ) {
				color = RCOL_FRIENDLY;
			} else {
				switch (shipp->team) {
				case TEAM_FRIENDLY:
				case TEAM_HOSTILE:
				case TEAM_TRAITOR:
					color = RCOL_HOSTILE;
					break;
				case TEAM_NEUTRAL:
					color = RCOL_NEUTRAL;
					break;
				case TEAM_UNKNOWN:
					color = RCOL_UNKNOWN;
					break;
				default:
					color = RCOL_HOSTILE;
					Int3();	//	Bogus team id in shipp->team
					break;
				}
			}
		}*/
}

int See_all = FALSE;
DCF_BOOL(see_all, See_all)

void radar_plot_object( object *objp )	
{
	vector	pos, tempv;
	float		dist, rscale, zdist, max_radar_dist;
	int		xpos, ypos, color=0;
	vector	*world_pos = &objp->pos;	
	float		awacs_level;

#ifndef NO_NETWORK
	// don't process anything here.  Somehow, a jumpnode object caused this function
	// to get entered on server side.
	if( Game_mode & GM_STANDALONE_SERVER ){
		return;
	}

	// if ship is cloaked then don't plot on radar
	if (Ships[objp->instance].flags2 & SF2_CLOAK_ON)
		return;
	// if ship has decoy/jammer on don't plot on radar
	if (Ships[objp->instance].flags2 & SF2_NO_RADAR)
		return;

	// multiplayer clients ingame joining should skip this function
	if ( MULTIPLAYER_CLIENT && (Net_player->flags & NETINFO_FLAG_INGAME_JOIN) ){
		return;
	}
#endif

	// get team-wide awacs level for the object if not ship
	int ship_is_visible = 0;
	if (objp->type == OBJ_SHIP) {
		if (Player_ship != NULL) {
			if (ship_is_visible_by_team_new(objp, Player_ship)) {
				ship_is_visible = 1;
			}
		}
	}

	// only check awacs level if ship is not visible by team
	awacs_level = 1.5f;
	if (Player_ship != NULL && !ship_is_visible) {
		awacs_level = awacs_get_level(objp, Player_ship);
	}

	// if the awacs level is unviewable - bail
	if(awacs_level < 0.0f && !See_all){
		return;
	}

	// Apply object type filters	
	switch ( objp->type ) {
	case OBJ_SHIP:
		// Place to cull ships, such as NavBuoys		
		break;
		
	case OBJ_JUMP_NODE:
		// if buoy is not same iff as player then return
		if (Ships[Player_obj->instance].iff != Jump_nodes[objp->instance].iff)
			return;
		// filter jump nodes here if required
		break;

	case OBJ_WEAPON: {
		// if not a bomb, return
		if ( !(Weapon_info[Weapons[objp->instance].weapon_info_index].wi_flags & WIF_BOMB) ) {
			return;
		}

		// if bomb is on same team as player, return
		if ( (obj_team(objp) == Player_ship->team) && (Player_ship->team != TEAM_TRAITOR) ) {
			return;
		}

		//if a local ssm is in subspace, return
		if (Weapons[objp->instance].lssm_stage==3)
			return;
		break;
	}

	default:
		return;			// if any other kind of object, don't want to show on radar
		break;
	} // end switch

	
	// JAS -- new way of getting the rotated point that doesn't require this to be
	// in a g3_start_frame/end_frame block.
	vm_vec_sub(&tempv,world_pos,&Player_obj->pos);
	vm_vec_rotate( &pos, &tempv, &Player_obj->orient );

	// Calculate the distance betwen the radar object and the player
	dist = vm_vec_dist(world_pos, &Player_obj->pos);

	// Get the maximum distance of the radar
	max_radar_dist = Radar_ranges[HUD_config.rp_dist];

	// Check to see if the radar object is in radar range
	if ( dist > max_radar_dist ){
		return;
	}
	
	// Check which radar mode to use
	if(Cmdline_UseTwoRadar)
	{
		/* Two radar screen mode */

		// Calculate the distance betwen the radar object and the player
		zdist = fl_sqrt( (pos.xyz.x*pos.xyz.x)+(pos.xyz.y*pos.xyz.y)+(pos.xyz.z*pos.xyz.z));

		float new_x_dist, clipped_x_dist;
		float new_y_dist, clipped_y_dist;

		// If the distance is too small, make is apear dead cenetered
		if (zdist < 0.01f ) {
			new_x_dist = 0.0f;
			new_y_dist = 0.0f;
		}
		else {

			// Calculate the position of the radar blip
			new_x_dist = (pos.xyz.x/(zdist)) * radx;
			new_y_dist = (pos.xyz.y/(zdist)) * rady;

			/* force new_x_dist and new_y_dist to be inside the radar */

			float hypotenuse;
			float max_radius;

			// Calculate the distance form the center of the radar
			hypotenuse = (float)_hypot(new_x_dist, new_y_dist);

			// Get the max distance form the center of the radar
			max_radius = i2fl(Radar_radius[gr_screen.res][0] - 5);

			// If the distance form the center is more than the max fix it
			if (hypotenuse >= (max_radius) ) {
				clipped_x_dist = max_radius * (new_x_dist / hypotenuse);
				clipped_y_dist = max_radius * (new_y_dist / hypotenuse);
				new_x_dist = clipped_x_dist;
				new_y_dist = clipped_y_dist;
			}
		}

		// Is the radar object behind the player
		if(pos.xyz.z < 0.0f)
		{
			/* Object behind, blip on right radar */
			
			// Set the absolute screen position of the radar blip
			xpos = fl2i( Radar_centerR[gr_screen.res][0] + new_x_dist );
			ypos = fl2i( Radar_centerR[gr_screen.res][1] - new_y_dist );
		}
		else
		{
			/* Object infront, blip on left radar */

			// Set the absolute screen position of the radar blip
			xpos = fl2i( Radar_centerL[gr_screen.res][0] + new_x_dist );
			ypos = fl2i( Radar_centerL[gr_screen.res][1] - new_y_dist );
		}
	}
	else
	{
		/* Single radar screen mode */

		// This check should always go into the else clause (becasue
		// the distance formula is sqrt(x^2+y^2+z^2) = dist, it can
		// thus never bee less than the z axi) but check anyway just
		// to make sure no error passes through
		if ( dist < pos.xyz.z ) {
			rscale = 0.0f;
		} else {
			// The Freespace radar has two circles, the inner one which is
			// for ships infront of you, the outer ships behind you.
			// Here you calculate a radius scale, that'll put the blip
			// into the correct possition in the circles.
			// First the z position (z distance) is devided with the distance 
			// to the object this is to get a poestive or negative value betwen
			// -1 and 1. The arccos is applied, which will spit out a value
			// betwen PI and 0 (where PI is for -1 and 0 for 1). This value
			// is then devided by PI which gives us a value betwen 0 and 1.
			// This last value basicaly decides how far from the center the
			// randar blip will be ploted
			rscale = (float) acos( pos.xyz.z/dist ) / 3.14159f;		//2.0f;	 
		}

		// Calculate the distance betwen the radar object and the
		// player in the plane (x and y axies).
		zdist = fl_sqrt( (pos.xyz.x*pos.xyz.x)+(pos.xyz.y*pos.xyz.y) );

		float new_x_dist, clipped_x_dist;
		float new_y_dist, clipped_y_dist;

		// If the distance is too smale, make is apear dead cenetered
		if (zdist < 0.01f ) {
			new_x_dist = 0.0f;
			new_y_dist = 0.0f;
		}
		else {

			// Calculate the x position of the radar blip
			// by deviding the x position of the radar object
			// with the distance. Then apply the z "scale" that
			// we calculated above in order to make it apear the correct
			// distance from the center.
			new_x_dist = (pos.xyz.x/zdist) * rscale * radx;

			// Do the same thing fro the y position
			new_y_dist = (pos.xyz.y/zdist) * rscale * rady;

			// force new_x_dist and new_y_dist to be inside the radar
			// This code is really all about making sure the blip really
			// are in the radar screen
			float hypotenuse;
			float max_radius;

			// Calculate the distance form the center of the radar
			hypotenuse = (float)_hypot(new_x_dist, new_y_dist);

			// Get the max distance form the center of the radar
			max_radius = i2fl(Radar_radius[gr_screen.res][0] - 5);

			// If the distance form the center is more than the max fix it
			if (hypotenuse >= (max_radius) ) {
				clipped_x_dist = max_radius * (new_x_dist / hypotenuse);
				clipped_y_dist = max_radius * (new_y_dist / hypotenuse);
				new_x_dist = clipped_x_dist;
				new_y_dist = clipped_y_dist;
			}
		}

		// Set the absolute screen position of the radar blip
		xpos = fl2i( Radar_center[gr_screen.res][0] + new_x_dist );
		ypos = fl2i( Radar_center[gr_screen.res][1] - new_y_dist );
	}

	color = radar_blip_color(objp);

	// Determine the distance at which we will dim the radar blip
	if ( timestamp_elapsed(Radar_calc_dim_dist_timer) ) {
		Radar_calc_dim_dist_timer=timestamp(1000);
		Radar_dim_range = player_farthest_weapon_range();
		if ( Radar_dim_range <= 0 ) {
			Radar_dim_range=1500.0f;
		}
	}

	blip	*b;
	int blip_dim=0;

	if ( dist > Radar_dim_range ) {
		blip_dim=1;
	}

	if ( N_blips >= MAX_BLIPS ) {
		// out of blips, don't plot
		Int3();
		return;
	}

	b = &Blips[N_blips];
	b->flags=0;

	// flag the blip as a current target if it is
	if (OBJ_INDEX(objp) == Player_ai->target_objnum)	{
		b->flags |= BLIP_CURRENT_TARGET;
		blip_dim = 0;
	}

	if ( blip_dim ) {
		list_append( &Blip_dim_list[color], b );
	} else {
		list_append( &Blip_bright_list[color], b );
	}

	b->x = xpos;
	b->y = ypos;

	// see if blip should be drawn distorted
	if (objp->type == OBJ_SHIP)
	{
		// ships specifically hidden from sensors
		if ( Ships[objp->instance].flags & SF_HIDDEN_FROM_SENSORS ) {
			b->flags |= BLIP_DRAW_DISTORTED;
		}

		// determine if its AWACS distorted
		if ( awacs_level < 1.0f )
		{
			// check if it's 
			b->flags |= BLIP_DRAW_DISTORTED;
		}
	}				

	// don't distort the sensor blips if the player has primitive sensors and the nebula effect
	// is not active
	if (Player_ship->flags2 & SF2_PRIMITIVE_SENSORS)
	{
		if (!(The_mission.flags & MISSION_FLAG_FULLNEB))
		{
			b->flags &= ~BLIP_DRAW_DISTORTED;
		}
	}

	N_blips++;
}

// set N_blips for each color/brightness level to zero
void radar_null_nblips()
{
	int i;

	N_blips=0;

	for (i=0; i<MAX_RADAR_COLORS; i++) {
		list_init(&Blip_bright_list[i]);
		list_init(&Blip_dim_list[i]);
	}
}

// radar_mission_init() is called at the start of each mission.  
void radar_mission_init()
{
	int i;

	Blip_mutate_id				= 1;
	Radar_death_timer			= 0;
	Radar_static_playing		= 0;
	Radar_static_next			= 0;
	Radar_avail_prev_frame	= 1;
	Radar_calc_dim_dist_timer = timestamp(0);

	for ( i=0; i<NUM_FLICKER_TIMERS; i++ ) {
		Radar_flicker_timer[i]=timestamp(0);
		Radar_flicker_on[i]=0;
	}
}

#define SMALL_BLIP_CHAR (Lcl_special_chars + 5)
#define LARGE_BLIP_CHAR (Lcl_special_chars + 6)

int Small_blip_offset_x = 0;
int Small_blip_offset_y = 0;
int Large_blip_offset_x = 0;
int Large_blip_offset_y = 0;

char Small_blip_string[2];
char Large_blip_string[2];

void radar_frame_init()
{
	radar_null_nblips();
	radx = i2fl(Radar_radius[gr_screen.res][0]) / 2.0f;
	rady = i2fl(Radar_radius[gr_screen.res][1]) / 2.0f;

	int w,h;
	gr_set_font(FONT1);

	Small_blip_string[0] = '.';//ubyte(SMALL_BLIP_CHAR);
	Small_blip_string[1] = 0;
	gr_get_string_size( &w, &h, Small_blip_string );
	Small_blip_offset_x = -w/2;
	Small_blip_offset_y = -h/2;

	Large_blip_string[0] = ubyte(SMALL_BLIP_CHAR);//ubyte(LARGE_BLIP_CHAR);
	Large_blip_string[1] = 0;
	gr_get_string_size( &w, &h, Large_blip_string );
	Large_blip_offset_x = -w/2;
	Large_blip_offset_y = -h/2;
}

void radar_draw_circle( int x, int y, int rad, int brackets )
{
	if ( rad == Radar_blip_radius_target[gr_screen.res] )	{
		gr_string( Large_blip_offset_x+x, Large_blip_offset_y+y, Large_blip_string );
		if (brackets) {
			gr_set_color_fast(&Color_bright_yellow);
		//gr_line(Large_blip_offset_x+x-1, Large_blip_offset_y+y, Large_blip_offset_x+x-1, Large_blip_offset_y+y+4);
			// left bracket
			// top
			gr_line(Large_blip_offset_x+x-1, Large_blip_offset_y+y+2, Large_blip_offset_x+x+1, Large_blip_offset_y+y+2);
			// side
			gr_line(Large_blip_offset_x+x-1, Large_blip_offset_y+y+2, Large_blip_offset_x+x-1, Large_blip_offset_y+y+6);
			// bottom
			gr_line(Large_blip_offset_x+x-1, Large_blip_offset_y+y+6, Large_blip_offset_x+x+1, Large_blip_offset_y+y+6);
		
			// right bracket
			// top
			gr_line(Large_blip_offset_x+x+2, Large_blip_offset_y+y+2, Large_blip_offset_x+x+4, Large_blip_offset_y+y+2);
			// side
			gr_line(Large_blip_offset_x+x+3, Large_blip_offset_y+y+2, Large_blip_offset_x+x+3, Large_blip_offset_y+y+6);
			// bottom
			gr_line(Large_blip_offset_x+x+2, Large_blip_offset_y+y+6, Large_blip_offset_x+x+4, Large_blip_offset_y+y+6);
		}
	} else {
		// rad = RADAR_BLIP_RADIUS_NORMAL;
		gr_string( Large_blip_offset_x+x, Large_blip_offset_y+y, Large_blip_string );
		//gr_string( Small_blip_offset_x+x, Small_blip_offset_y+y, Small_blip_string );
	}
}

// radar is damaged, so make blips dance around
void radar_blip_draw_distorted(blip *b)
{
	int xdiff, ydiff;
	float scale;
	xdiff = -10 + rand()%20;
	ydiff = -10 + rand()%20;

	// maybe scale the effect if EMP is active
	if(emp_active_local()){
		scale = emp_current_intensity();

		xdiff = (int)((float)xdiff * scale);
		ydiff = (int)((float)ydiff * scale);
	}

	radar_draw_circle( b->x+xdiff, b->y+ydiff, b->rad, 0); 
}

// blip is for a target immune to sensors, so cause to flicker in/out with mild distortion
void radar_blip_draw_flicker(blip *b)
{
	int xdiff=0, ydiff=0, flicker_index;

	if ( (b-Blips) & 1 ) {
		flicker_index=0;
	} else {
		flicker_index=1;
	}

	if ( timestamp_elapsed(Radar_flicker_timer[flicker_index]) ) {
		Radar_flicker_timer[flicker_index] = timestamp_rand(50,1000);
		Radar_flicker_on[flicker_index] ^= 1;
	}

	if ( !Radar_flicker_on[flicker_index] ) {
		return;
	}

	if ( rand() & 1 ) {
		xdiff = -2 + rand()%4;
		ydiff = -2 + rand()%4;
	}

	radar_draw_circle( b->x+xdiff, b->y+ydiff, b->rad, 1);
}

// Draw all the active radar blips
void draw_radar_blips(int rcol, int is_dim, int distort)
{
	blip	*b=NULL;
	blip	*blip_head=NULL;

	// Need to set font.
	gr_set_font(FONT1);

	if ( is_dim ) {
		blip_head = &Blip_dim_list[rcol];
	} else {
		blip_head = &Blip_bright_list[rcol];
	}

	for ( b = GET_FIRST(blip_head); b !=END_OF_LIST(blip_head); b = GET_NEXT(b) )	{

		Assert((rcol >= 0) && (rcol < MAX_RADAR_COLORS));

		if ( is_dim ) {
			gr_set_color_fast( &Radar_colors[RADAR_BLIP_DIM][rcol] );
		} else {
			gr_set_color_fast( &Radar_colors[RADAR_BLIP_BRIGHT][rcol] );
		}

		if (b->flags & BLIP_CURRENT_TARGET) {
			// draw cool blip to indicate current target
			b->rad = Radar_blip_radius_target[gr_screen.res];				
		} else {
			b->rad = Radar_blip_radius_normal[gr_screen.res];
		}

		if ( distort ) { 
			radar_blip_draw_distorted(b);
		} else if ( b->flags & BLIP_DRAW_DISTORTED ) {
			radar_blip_draw_flicker(b);
		} else{
			radar_draw_circle( b->x, b->y, b->rad, 1);
		}
	}
}

// Draw the radar blips
// input:	distorted	=>		0 (default) to draw normal, 1 to draw distorted 
void radar_draw_blips_sorted(int distort)
{
	// draw dim blips first
	draw_radar_blips(RCOL_JUMP_NODE, 1, distort);
	draw_radar_blips(RCOL_WARPING_SHIP, 1, distort);
	draw_radar_blips(RCOL_NAVBUOYS, 1, distort);
	draw_radar_blips(RCOL_TAGGED, 1, distort);
	draw_radar_blips(RCOL_BOMB, 1, distort);
	draw_radar_blips(RCOL_REBEL, 1, distort);
	draw_radar_blips(RCOL_IMPERIAL, 1, distort);
	draw_radar_blips(RCOL_BLUE, 1, distort);
	draw_radar_blips(RCOL_PURPLE, 1, distort);
	draw_radar_blips(RCOL_YELLOW, 1, distort);
	draw_radar_blips(RCOL_RED, 1, distort);
	draw_radar_blips(RCOL_ORANGE, 1, distort);
	
	
	// draw bright blips
	draw_radar_blips(RCOL_JUMP_NODE, 0, distort);
	draw_radar_blips(RCOL_WARPING_SHIP, 0, distort);
	draw_radar_blips(RCOL_NAVBUOYS, 0, distort);
	draw_radar_blips(RCOL_TAGGED, 0, distort);
	draw_radar_blips(RCOL_BOMB, 0, distort);
	draw_radar_blips(RCOL_REBEL, 0, distort);
	draw_radar_blips(RCOL_IMPERIAL, 0, distort);
	draw_radar_blips(RCOL_BLUE, 0, distort);
	draw_radar_blips(RCOL_PURPLE, 0, distort);
	draw_radar_blips(RCOL_YELLOW, 0, distort);
	draw_radar_blips(RCOL_RED, 0, distort);
	draw_radar_blips(RCOL_ORANGE, 0, distort);
}

static int test_time = 1;
void radar_draw_range()
{
	char buf[32];

	// hud_set_bright_color();
	hud_set_gauge_color(HUD_RADAR, HUD_C_BRIGHT);

	if(Cmdline_UseTwoRadar)
	{
		switch ( HUD_config.rp_dist ) {

		case RR_SHORT:
			gr_printf(Radar_dist_coordsL[gr_screen.res][RR_SHORT][0], Radar_dist_coordsL[gr_screen.res][RR_SHORT][1], XSTR( "2k", 467));
			gr_printf(Radar_dist_coordsR[gr_screen.res][RR_SHORT][0], Radar_dist_coordsR[gr_screen.res][RR_SHORT][1], XSTR( "2k", 467));
			break;

		case RR_LONG:
			gr_printf(Radar_dist_coordsL[gr_screen.res][RR_LONG][0], Radar_dist_coordsL[gr_screen.res][RR_LONG][1], XSTR( "10k", 468));
			gr_printf(Radar_dist_coordsR[gr_screen.res][RR_LONG][0], Radar_dist_coordsR[gr_screen.res][RR_LONG][1], XSTR( "10k", 468));
			break;

		case RR_INFINITY:
			sprintf(buf, NOX("%c"), Lcl_special_chars);
			gr_printf(Radar_dist_coordsL[gr_screen.res][RR_INFINITY][0], Radar_dist_coordsL[gr_screen.res][RR_INFINITY][1], buf);
			gr_printf(Radar_dist_coordsR[gr_screen.res][RR_INFINITY][0], Radar_dist_coordsR[gr_screen.res][RR_INFINITY][1], buf);
			break;

		default:
			Int3();	// can't happen (get Alan if it does)
			break;
		}
	}
	else
	{
		switch ( HUD_config.rp_dist ) {

		case RR_SHORT:
			gr_printf(Radar_dist_coords[gr_screen.res][RR_SHORT][0], Radar_dist_coords[gr_screen.res][RR_SHORT][1], XSTR( "2k", 467));
			break;

		case RR_LONG:
			gr_printf(Radar_dist_coords[gr_screen.res][RR_LONG][0], Radar_dist_coords[gr_screen.res][RR_LONG][1], XSTR( "10k", 468));
			break;

		case RR_INFINITY:
			sprintf(buf, NOX("%c"), Lcl_special_chars);
			gr_printf(Radar_dist_coords[gr_screen.res][RR_INFINITY][0], Radar_dist_coords[gr_screen.res][RR_INFINITY][1], buf);
			break;

		default:
			Int3();	// can't happen (get Alan if it does)
			break;
		}
	}


	hud_set_default_color();
}

void radar_frame_render(float frametime)
{
	float	sensors_str;
	int ok_to_blit_radar;
	
	ok_to_blit_radar = 1;
	
	sensors_str = ship_get_subsystem_strength( Player_ship, SUBSYSTEM_SENSORS );

	if ( ship_subsys_disrupted(Player_ship, SUBSYSTEM_SENSORS) ) {
		sensors_str = MIN_SENSOR_STR_TO_RADAR-1;
	}

	// note that on lowest skill level, there is no radar effects due to sensors damage
	if ( (Game_skill_level == 0) || (sensors_str > SENSOR_STR_RADAR_NO_EFFECTS) ) {
		Radar_static_playing = 0;
		Radar_static_next = 0;
		Radar_death_timer = 0;
		Radar_avail_prev_frame = 1;
	} else if ( sensors_str < MIN_SENSOR_STR_TO_RADAR ) {
		if ( Radar_avail_prev_frame ) {
			Radar_death_timer = timestamp(2000);
			Radar_static_next = 1;
		}
		Radar_avail_prev_frame = 0;
	} else {
		Radar_death_timer = 0;
		if ( Radar_static_next == 0 )
			Radar_static_next = 1;
	}

	if ( timestamp_elapsed(Radar_death_timer) ) {
		ok_to_blit_radar = 0;
	}

	hud_set_gauge_color(HUD_RADAR);
	radar_blit_gauge();
	radar_draw_range();

	// if player craft is cloaked then no blips get rendered
	if (Player_ship->flags2 & SF2_CLOAK_ON)
	//if (Objects[Player_ship->objnum].phys_info.flags & PF_CLOAK_ON)
		return;

	if ( timestamp_elapsed(Radar_static_next) ) {
		Radar_static_playing ^= 1;
		Radar_static_next = timestamp_rand(50, 750);
	}

	// if the emp effect is active, always draw the radar wackily
	if(emp_active_local()){
		Radar_static_playing = 1;
	}

	if ( ok_to_blit_radar ) {
		if ( Radar_static_playing ) {
			radar_draw_blips_sorted(1);	// passing 1 means to draw distorted
			if ( Radar_static_looping == -1 ) {
				Radar_static_looping = snd_play_looping(&Snds[SND_STATIC]);
			}
		} else {
			radar_draw_blips_sorted();
			if ( Radar_static_looping != -1 ) {
				snd_stop(Radar_static_looping);
				Radar_static_looping = -1;
			}
		}
	} else {
		if ( Radar_static_looping != -1 ) {
			snd_stop(Radar_static_looping);
			Radar_static_looping = -1;
		}
	}
}

void radar_blit_gauge()
{
	SPECMAP = -1;
	GLOWMAP = -1;
	NORMMAP = -1;

	
	if(Cmdline_UseTwoRadar)
	{
		// Draw the left radar screen
		gr_set_bitmap(RadarL_gauge.first_frame+1);
		gr_aabitmap( Radar_coordsL[gr_screen.res][0], Radar_coordsL[gr_screen.res][1] );
		gr_printf(10,10, "F");
		// Draw the right radar screen
		gr_set_bitmap(RadarR_gauge.first_frame+1);
		gr_aabitmap( Radar_coordsR[gr_screen.res][0], Radar_coordsR[gr_screen.res][1] );
		gr_printf(623,10, "B");
	}
	else
	{
		// Draw the radar screen
		gr_set_bitmap(RadarO_gauge.first_frame+1);
		gr_aabitmap( Radar_coords[gr_screen.res][0], Radar_coords[gr_screen.res][1] );
	}

} 

void radar_page_in()
{
	bm_page_in_aabitmap( RadarO_gauge.first_frame, RadarO_gauge.num_frames );
	bm_page_in_aabitmap( RadarL_gauge.first_frame, RadarL_gauge.num_frames );
	bm_page_in_aabitmap( RadarR_gauge.first_frame, RadarR_gauge.num_frames );

}
