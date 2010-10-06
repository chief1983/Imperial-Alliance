#include "ship/pod.h"
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
#include "Weapon/Weapon.h"
#include "ship/ShipFX.h"
#include "object/object.h"
#include "globalincs/linklist.h"
#include "ship/afterburner.h"

// ----------------------------------------------------------
// Global to file
// ----------------------------------------------------------
static int		Player_pod_loop_id;		// identifies the looping afterburner sound of the player ship
static int		Player_pod_loop_delay;	// timestamp used to time the start of the looping afterburner sound
static int		Player_disengage_timer;
static float	Player_pod_vol;
static int		Player_pod_start_time;


// ----------------------------------------------------------
// local constants
// ----------------------------------------------------------

// The minimum required fuel to engage afterburners
#define MIN_POD_FUEL_TO_ENGAGE		1

#define POD_DEFAULT_VOL					0.5f	// default starting volume (0.0f -> 1.0f)
#define POD_PERCENT_VOL_ATTENUATE		0.30f	// % at which afterburner volume is reduced
#define POD_PERCENT_FOR_LOOP_SND		0.33f
#define POD_VOLUME_UPDATE				250	// consider changing afterburner volume every 100 ms
#define POD_LOOP_DELAY					200	// ms after engage, to start looping sound

#define DISENGAGE_TIME								1500	// time in ms to play faded loop sound when afterburner disengages


float	Skill_level_pod_recharge_scale[NUM_SKILL_LEVELS] = {5.0f, 3.0f, 2.0f, 1.5f, 1.0f};

// ----------------------------------------------------------------------------
// pod_level_init()
//          
//	call at the start of a mission
//
void pod_level_init()
{
	Player_disengage_timer = 1;
	Player_pod_vol = POD_DEFAULT_VOL;
	Player_pod_loop_id = -1;
	Player_pod_start_time = 0;
}

// ----------------------------------------------------------------------------
// afterburners_start() will be called when a ship engages the afterburners.
// This function should only be called once when afterburners first start.  This is
// to start an appropriate sound effect and do any one-time initializations.
//
// parameters:   *objp        ==> pointer to the object starting afterburners
//          
int pod_start(object *objp)
{
	ship_info	*sip;
	ship			*shipp;

	Assert( objp != NULL );

	shipp = &Ships[objp->instance];
	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < MAX_SHIP_TYPES );
	sip = &Ship_info[shipp->ship_info_index];

	if(objp->type == OBJ_OBSERVER)
		return 1;

	Assert( objp->type == OBJ_SHIP);
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );

		
	if ( !(shipp->flags2 & SF2_POD_INSTALLED) )	{
		return 1;
	}

	// S.L.A.M. is handled elsewhere
	if (shipp->pod_weapon == TWT_SLAM)
		return 1;
	
	// Check if there is enough pod energy
#ifndef NO_NETWORK
	if ( (shipp->pod_energy < MIN_POD_FUEL_TO_ENGAGE) && !MULTIPLAYER_CLIENT ) {
#else
	if ( (shipp->pod_energy < MIN_POD_FUEL_TO_ENGAGE) ) {
#endif
		if ( objp == Player_obj ) {
			snd_play( &Snds[SND_ABURN_FAIL] );
		}
		return 1;
	}

	if (objp == Player_obj) {
		snd_play(&Snds[shipp->pod_sound_engage], 0.0f, 1.0f, SND_PRIORITY_MUST_PLAY);
		joy_ff_afterburn_on();
	}
	else {
		// hear other craft engaging booster
		if (shipp->pod_weapon == TWT_BOOST_POD)
			snd_play_3d( &Snds[shipp->pod_sound_engage], &objp->pos, &View_position, objp->radius );
	}
	
	return 0;
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
void pod_update(object *objp, float fl_frametime)
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

	if ( !(shipp->flags2 & SF2_POD_INSTALLED) )	{
		return;	
	}

	if (shipp->pod_weapon == TWT_BOOST_POD) {
		if (!(objp->phys_info.flags & PF_BOOSTER_ON)) {
			return;
		}
	}

	// S.L.A.M. is handled elsewhere
	if (shipp->pod_weapon == TWT_SLAM)
		return;
	
	// single player, multiplayer servers, and clients for their own ships
#ifndef NO_NETWORK
	if(!(Game_mode & GM_MULTIPLAYER) || MULTIPLAYER_MASTER || (objp == Player_obj)){
#else
	// changed from != to == by Goober5000... this seems to be a bug
	if (objp == Player_obj) {
#endif
	    // if any of the energy draining pod weapons AREN'T on and the pod weapon isn't the 
		// booster then refill the gauge
		if ( !(shipp->flags2 & SF2_DRAINS_ENERGY) && !(shipp->pod_weapon == TWT_BOOST_POD)) {
			// Recover pod energy
			
			if ( shipp->pod_energy < shipp->pod_energy_capacity ) {
				float recharge_scale;
				recharge_scale = Energy_levels[shipp->engine_recharge_index] * 2.0f * Skill_level_pod_recharge_scale[Game_skill_level];
				shipp->pod_energy += (shipp->pod_recover_rate * fl_frametime * recharge_scale);

				if ( shipp->pod_energy >  shipp->pod_energy_capacity){
					shipp->pod_energy = shipp->pod_energy_capacity;
				}
			}
			return;
		}
		else {
			// Check if there is enough pod energy
			if ( shipp->pod_energy <= 0 ) {
				shipp->pod_energy = 0.0f;
				pod_stop(objp);
				return;
			}
		}

		// pod in use at this point

		// Reduce the pod energy
		shipp->pod_energy -= (shipp->pod_burn_rate * fl_frametime);
		if ( shipp->pod_energy < 0.0f ) {
			shipp->pod_energy = 0.0f;
		}
	}
			Player_pod_vol = POD_DEFAULT_VOL;
			//Player_pod_loop_delay = 0;
			if ( Player_pod_loop_id == -1 && objp == Player_obj) {
				Player_pod_loop_id = snd_play_looping( &Snds[shipp->pod_sound_loop], 0.0f , -1, -1);
				snd_set_volume(Player_pod_loop_id, Player_pod_vol);
//				nprintf(("Alan","PLAY LOOPING SOUND\n"));
			}

}



// ----------------------------------------------------------------------------
// afterburners_stop() will be called when a ship disengages the afterburners.
//
// parameters:   *objp				=> pointer to the object starting afterburners
//						key_released	=>	OPTIONAL parameter (default value 0)
//												This is only used for the player object, to
//												manage starting/stopping
//
void pod_stop(object *objp)
{
	//tertiary_weapon_info* twip = &Tertiary_weapon_info;

	Assert( objp != NULL );
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );
	
	ship_info *sip;
	ship *shipp;

	shipp = &Ships[objp->instance];

	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < MAX_SHIP_TYPES );
	sip = &Ship_info[shipp->ship_info_index];
	

	if ( !(shipp->flags2 & SF2_DRAINS_ENERGY) || (shipp->pod_weapon == TWT_BOOST_POD))	{
		nprintf(("Warning","Ship type %s does not have pod capability\n", sip->name));
		return;
	}
	
	// if the pod weapon stopped because it ran out of juice then we'll just have to turn it off
	if (objp == Player_obj)
		ship_fire_tertiary(objp);

	pod_stop_sounds();
	
}

// ----------------------------------------------------------------------------
// pod_stop_sounds() 
//
// Terminates any looping afterburner sounds.
// This should only be called when the game decides to stop all looping sounds.
//
void pod_stop_sounds()
{
	if ( Player_pod_loop_id != -1 ) {
		snd_stop(Player_pod_loop_id);
//		nprintf(("Alan","STOP LOOPING SOUND\n"));
	}

	Player_pod_loop_id = -1;
//	Player_pod_timer = 1;
	Player_pod_loop_delay = 0;

	joy_ff_afterburn_off();
}

//	Return true if objp is in jammer field of other craft.
int maybe_jam_weapons(object *objp)
{
	object	*objp2;
	vector	cur_pos, goal_pos;
	ship_info	*sip;
	float	radius;
	mc_info mc;
	float distance;
	tertiary_weapon_info* twip;

	sip = &Ship_info[Ships[objp->instance].ship_info_index];
	twip=&Tertiary_weapon_info;
	
	if (objp->type != OBJ_SHIP) 
		return 0;
	
	cur_pos = objp->pos;

	// if cap ship has a jammer installed it gets a special field distance
	if ((sip->flags & SIF_BIG_SHIP) || (sip->flags & SIF_HUGE_SHIP))
		distance = CAP_SHIP_JAMMER_RANGE;
	else
		distance = twip->jammer_range;

	vm_vec_scale_add(&goal_pos, &cur_pos, &objp->orient.vec.fvec, distance);

	for ( objp2 = GET_FIRST(&obj_used_list); objp2 != END_OF_LIST(&obj_used_list); objp2 = GET_NEXT(objp2) ) {
		if ((objp != objp2) && (objp2->type == OBJ_SHIP)) {
			if (Ships[objp2->instance].flags2 & SF2_JAMMER_ON) {
					radius = objp->radius;
					
					if (1.5f * radius < 70.0f)
						radius *= 1.5f;
					else
						radius = 70.0f;

					ship_model_start(objp2);

					mc.model_num = Ships[objp2->instance].modelnum;			// Fill in the model to check
					mc.orient = &objp2->orient;	// The object's orient
					mc.pos = &objp2->pos;			// The object's position
					mc.p0 = &cur_pos;					// Point 1 of ray to check
					mc.p1 = &goal_pos;					// Point 2 of ray to check
					mc.flags = MC_CHECK_MODEL | MC_ONLY_SPHERE;//MC_CHECK_SPHERELINE;
					mc.radius = radius;

					model_collide(&mc);

					ship_model_stop(objp2);

					return mc.num_hits;
			}
		}
	}
	
	return 0;
}

// go through list of ships and see if they are within the tractor beam
// range.  if ship is in the box then disable its flight controls
int is_in_front_in_box(object *objp)
{
	object *objp2;
	vector	pos, tempv;
	float box_width, box_depth;
	tertiary_weapon_info* twip;
	
	if (objp->type != OBJ_SHIP) 
		return 0;

	if (!(Ships[objp->instance].flags2 & SF2_TRACTOR_ON)) 
		return 0;
	
	twip=&Tertiary_weapon_info;

	box_width = objp->radius;
	box_depth = twip->tractor_range;
	
	for ( objp2 = GET_FIRST(&obj_used_list); objp2 != END_OF_LIST(&obj_used_list); objp2 = GET_NEXT(objp2) ) {
		if ((objp != objp2) && (objp2->type == OBJ_SHIP)) {
			// Rotate the cordinate system to have origo at the center of the obj
			// and looking down the posetive z-axi
			vm_vec_sub(&tempv,&objp2->pos,&objp->pos);
			vm_vec_rotate(&pos, &tempv, &objp->orient);
						
			// Check to is if the target is inside the box
			if((pos.xyz.x > -box_width) && (pos.xyz.x < box_width) && 
				(pos.xyz.y > -box_width) && (pos.xyz.y < box_width) && 
				(pos.xyz.z > 0) && (pos.xyz.z < box_depth)) 
			{
				objp2->phys_info.flags |= PF_IN_TRACTOR_BEAM;
							
			}
			
		}
	}

	return 0;
}

// check to see if pod subsystem strength is below 20%.  if it is 
// below 20% then turn off whatever pod weapon is on the craft
void maybe_disable_pod(object *objp)
{
	ship *shipp;

	shipp = &Ships[objp->instance];

	if (ship_get_subsystem_strength(shipp, SUBSYSTEM_POD) < 0.2) {
		
		switch (shipp->pod_weapon)
		{
			case TWT_TURBOCHARGER:
				objp->phys_info.flags &= ~(PF_TURBO_ON);

				break;
	
			case TWT_CLOAK:
				objp->flags &= ~(OF_PROTECTED);
				shipfx_stop_cloak(shipp, Tertiary_weapon_info.cloak_cooldown);
				//shipp->flags2 &= ~(SF2_CLOAK_ON);
				//shipp->cloak_stage = CLOAK_OFF;
		
				break;		
	
			case TWT_BOOST_POD:
				objp->phys_info.flags &= ~(PF_BOOSTER_ON);

				break;
	
			case TWT_DECOY:
				shipp->flags2 &= ~(SF2_DECOY_ON);
				shipp->pod_engaged = 0;

				break;

			case TWT_TRACTOR:
				shipp->pod_engaged = 0;
				shipp->flags2 &= ~(SF2_TRACTOR_ON);
		
				break;

			case TWT_JAMMER:
				shipp->pod_engaged = 0;
				shipp->flags2 &= ~(SF2_JAMMER_ON);

				break;

			case TWT_SLAM:
				afterburners_stop(objp, 1);
				shipp->pod_engaged = 0;
		
				break;
		}
	}
	// turbo charger is the only pod that is on all of the time.  so
	// if subsytem strength is above 20% make sure that it is kept on
	else {
		if (shipp->pod_weapon == TWT_TURBOCHARGER)
			objp->phys_info.flags |= PF_TURBO_ON;
	}
}

		

