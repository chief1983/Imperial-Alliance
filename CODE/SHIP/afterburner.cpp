/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Ship/Afterburner.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * C file for managing the afterburners
 *
 * $Log: afterburner.cpp,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:12:10  Darkhill
 * no message
 *
 * Revision 2.8  2004/03/05 09:01:51  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.7  2004/01/31 03:56:46  phreak
 * changed "now" to unsigned int
 *
 * Revision 2.6  2003/11/23 00:59:01  Goober5000
 * fixed a bug introduced by Penguin for running with NO_NETWORK defined
 * --Goober5000
 *
 * Revision 2.5  2003/09/13 06:02:03  Goober5000
 * clean rollback of all of argv's stuff
 * --Goober5000
 *
 * Revision 2.3  2003/08/21 06:11:32  Goober5000
 * removed an extraneous thingy
 * --Goober5000
 *
 * Revision 2.2  2003/08/06 17:37:08  phreak
 * preliminary work on tertiary weapons. it doesn't really function yet, but i want to get something committed
 *
 * Revision 2.1  2002/08/01 01:41:09  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:28  penguin
 * Warpcore CVS sync
 *
 * Revision 1.2  2002/05/13 21:09:28  mharris
 * I think the last of the networking code has ifndef NO_NETWORK...
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 7     9/05/99 11:24p Jimb
 * changed recharge rate for afterburners based on skill setting.
 * 
 * 6     8/24/99 1:50a Dave
 * Fixed client-side afterburner stuttering. Added checkbox for no version
 * checking on PXO join. Made button info passing more friendly between
 * client and server.
 * 
 * 5     7/08/99 10:53a Dave
 * New multiplayer interpolation scheme. Not 100% done yet, but still
 * better than the old way.
 * 
 * 4     11/05/98 5:55p Dave
 * Big pass at reducing #includes
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
 * 25    5/23/98 2:41p Mike
 * Make Easy the default skill level and prevent old pilot's skill level
 * from carrying into new pilot.
 * 
 * 24    5/07/98 11:01a Lawrance
 * Play afterburner fail sound once energy runs out (and key is still
 * down)
 * 
 * 23    5/04/98 11:08p Hoffoss
 * Expanded on Force Feedback code, and moved it all into Joy_ff.cpp.
 * Updated references everywhere to it.
 * 
 * 22    4/18/98 9:12p Lawrance
 * Added Aureal support.
 * 
 * 21    4/13/98 2:11p Lawrance
 * Change afterburners so they can't be activated any faster than once
 * every 1.2 seconds
 * 
 * 20    4/07/98 1:53p Lawrance
 * Make energy system matter more.
 * 
 * 19    3/31/98 5:18p John
 * Removed demo/save/restore.  Made NDEBUG defined compile.  Removed a
 * bunch of debug stuff out of player file.  Made model code be able to
 * unload models and malloc out only however many models are needed.
 *  
 * 
 * 18    2/26/98 10:07p Hoffoss
 * Rewrote state saving and restoring to fix bugs and simplify the code.
 * 
 * 17    2/20/98 8:32p Lawrance
 * Add radius parm to sound_play_3d()
 * 
 * 16    12/28/97 5:52p Lawrance
 * fix volume discontinuity bug when afterburners ran out
 * 
 * 15    12/22/97 9:14p Allender
 * fix up some code relating to afterburners in multiplayer.  Clients now
 * control their own afterburners
 * 
 * 14    11/06/97 5:02p Dave
 * Finished reworking standalone multiplayer sequencing. Added
 * configurable observer-mode HUD
 * 
 * 13    10/17/97 9:49a Lawrance
 * remove debug output
 * 
 * 12    10/16/97 5:37p Lawrance
 * fix sound bug where AI afterburner was affecting player afterburner
 * sounds
 * 
 * 11    10/01/97 5:55p Lawrance
 * change call to snd_play_3d() to allow for arbitrary listening position
 * 
 * 10    9/16/97 2:27p Allender
 * Removed unused Assert that will cause problems in the future
 * 
 * 9     8/11/97 9:50a Allender
 * fixed afterburner snafu
 * 
 * 8     8/08/97 9:59a Allender
 * added afterburner code into multiplayer.  Required adding a new physics
 * info flag to indicate afterburners ready to fire. (needed for
 * multiplayer).  Removed some now unused variables in afterburner.cpp
 * 
 * 7     8/05/97 10:48a Lawrance
 * save afterburner data for the player
 * 
 * 6     7/27/97 5:14p Lawrance
 * add afterburners to the player control info
 * 
 * 5     7/25/97 5:02p Lawrance
 * fix bug with afterburner sound
 * 
 * 4     7/23/97 4:30p Lawrance
 * improve how disengage of afterburner works
 * 
 * 3     7/16/97 4:42p Mike
 * Make afterburner shake viewer, not ship.
 * Shake for limited time.
 * Add timestamp_until() function to timer library.
 * 
 * 2     7/11/97 8:57a Lawrance
 * make afterburner work same for player and AI ships
 * 
 * 1     7/10/97 2:24p Lawrance
 *
 * $NoKeywords: $
 */

#include "ship/afterburner.h"
#include "io/joy_ff.h"
#include "gamesnd/gamesnd.h"
#include "ship/ship.h"
#include "object/object.h"
#include "io/timer.h"
#include "render/3d.h"			// needed for View_position, which is used when playing a 3D sound
#include "hud/hudets.h"
#include "freespace2/freespace.h"
#include "network/multi.h"
#include "hud/hudmessage.h"
#include "weapon/weapon.h"


// The minimum required fuel to engage afterburners
#define MIN_AFTERBURNER_FUEL_TO_ENGAGE		10

float	Skill_level_afterburner_recharge_scale[NUM_SKILL_LEVELS] = {5.0f, 3.0f, 2.0f, 1.5f, 1.0f};

// ----------------------------------------------------------------------------
// afterburners_start() will be called when a ship engages the afterburners.
// This function should only be called once when afterburners first start.  This is
// to start an appropriate sound effect and do any one-time initializations.
//
// parameters:   *objp        ==> pointer to the object starting afterburners
//          
void afterburners_start(object *objp)
{
	ship_info	*sip;
	ship			*shipp;

	Assert( objp != NULL );

	shipp = &Ships[objp->instance];
	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < MAX_SHIP_TYPES );
	sip = &Ship_info[shipp->ship_info_index];

	if(objp->type == OBJ_OBSERVER)
		return;

	Assert( objp->type == OBJ_SHIP);
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );

	
	if (!(shipp->flags2 & SF2_POD_INSTALLED) && !(shipp->pod_weapon == TWT_SLAM))	{
		return;	
	}

	// Check if there is enough afterburner fuel
#ifndef NO_NETWORK
	if ( (shipp->afterburner_fuel < MIN_AFTERBURNER_FUEL_TO_ENGAGE) && !MULTIPLAYER_CLIENT ) {
#else
	if ( (shipp->afterburner_fuel < MIN_AFTERBURNER_FUEL_TO_ENGAGE) ) {
#endif
		if ( objp == Player_obj ) {
			snd_play( &Snds[SND_ABURN_FAIL] );
		}
		return;
	}

	
	objp->phys_info.flags |= PF_AFTERBURNER_ON;

	snd_play(&Snds[shipp->pod_sound_engage], 0.0f, 1.0f, SND_PRIORITY_MUST_PLAY);
	
}

// ----------------------------------------------------------------------------
// afterburners_update()
//
//	Update the state of the afterburner fuel remaining for an object using the
//	afterburner.  
//
// for the player ship, key_up_time() is called for the afterburner key to
// detect when afterburners disengage.
//
// input:		*objp				=> pointer to the object starting afterburners
//					fl_frametime	=> time in seconds of the last frame
//
void afterburners_update(object *objp, float fl_frametime)
{
	Assert( objp != NULL );
	Assert( objp->type == OBJ_SHIP );
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );
	
	ship_info *sip;
	ship *shipp;
	static int volume_chg_timer = 1;

	shipp = &Ships[objp->instance];

	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < MAX_SHIP_TYPES );
	sip = &Ship_info[shipp->ship_info_index];

	if ( (objp->flags & OF_PLAYER_SHIP ) && (Game_mode & GM_DEAD) ) {
		return;
	}

	if (!(shipp->flags2 & SF2_POD_INSTALLED) && !(shipp->pod_weapon == TWT_SLAM))	{
		return;	
	}


	// single player, multiplayer servers, and clients for their own ships
#ifndef NO_NETWORK
	if(!(Game_mode & GM_MULTIPLAYER) || MULTIPLAYER_MASTER || (objp == Player_obj)){
#else
	// changed from != to == by Goober5000... this seems to be a bug
	if (objp == Player_obj) {
#endif
		if ( !(objp->phys_info.flags & PF_AFTERBURNER_ON)) {
			// Recover afterburner fuel

//			float recover_rate=sip->afterburner_recover_rate;

			if ( shipp->afterburner_fuel < shipp->afterburner_fuel_capacity ) {
				float recharge_scale;
				recharge_scale = Energy_levels[shipp->engine_recharge_index] * 2.0f * Skill_level_afterburner_recharge_scale[Game_skill_level];
				shipp->afterburner_fuel += (shipp->afterburner_recover_rate * fl_frametime * recharge_scale);

				if ( shipp->afterburner_fuel >  shipp->afterburner_fuel_capacity){
					shipp->afterburner_fuel = shipp->afterburner_fuel_capacity;
				}
			}
			return;
		}
		else {
			// Check if there is enough afterburner fuel
			if ( shipp->afterburner_fuel <= 0 ) {
				shipp->afterburner_fuel = 0.0f;
				afterburners_stop(objp, 1);
				return;
			}
		}

		// afterburns are firing at this point

		// Reduce the afterburner fuel
		shipp->afterburner_fuel -= (shipp->afterburner_burn_rate * fl_frametime);
		if ( shipp->afterburner_fuel < 0.0f ) {
			shipp->afterburner_fuel = 0.0f;
		}
	}

	float top_speed;
	float desired_speed;

	top_speed = objp->phys_info.max_vel.xyz.z * 2.0f;

	float percent_throttle;
			
	if ( Ships[objp->instance].current_max_speed == 0 ) { 
		percent_throttle = objp->phys_info.fspeed / sip->max_speed;
	} else {
		percent_throttle = objp->phys_info.fspeed / shipp->current_max_speed;
	}
	
	desired_speed = top_speed * percent_throttle;
	
	if (desired_speed > top_speed)
		desired_speed = top_speed;

	objp->phys_info.afterburner_max_vel.xyz.z = desired_speed; //objp->phys_info.fspeed * 2;
	
}

// ----------------------------------------------------------------------------
// afterburners_stop() will be called when a ship disengages the afterburners.
//
// parameters:   *objp				=> pointer to the object starting afterburners
//						key_released	=>	OPTIONAL parameter (default value 0)
//												This is only used for the player object, to
//												manage starting/stopping
//
void afterburners_stop(object *objp, int key_released)
{
	Assert( objp != NULL );
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );
	
	ship_info *sip;
	ship *shipp;

	shipp = &Ships[objp->instance];

	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < MAX_SHIP_TYPES );
	sip = &Ship_info[shipp->ship_info_index];


	if ( !(objp->phys_info.flags & PF_AFTERBURNER_ON) ) {
		return;
	}

	objp->phys_info.flags &= ~PF_AFTERBURNER_ON;

	snd_play(&Snds[shipp->pod_sound_loop], 0.0f, 1.0f, SND_PRIORITY_MUST_PLAY);

	// if slam ran out of power make sure its turned off
	if (objp == Player_obj)
		ship_fire_tertiary(objp);
	
}

