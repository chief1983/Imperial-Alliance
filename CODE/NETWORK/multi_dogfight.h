/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Network/multi_dogfight.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:42 $
 * $Author: Spearhawk $
 * 
 * $Log: multi_dogfight.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:42  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:21:48  Darkhill
 * no message
 *
 * Revision 2.0  2002/06/03 04:02:26  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:11  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     2/23/99 2:29p Dave
 * First run of oldschool dogfight mode. 
 *   
 * $NoKeywords: $
 */

#ifndef __FS2_MULTIPLAYER_DOGFIGHT_HEADER_FILE
#define __FS2_MULTIPLAYER_DOGFIGHT_HEADER_FILE

// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT DEFINES/VARS
//

struct net_player;
struct object;


// ----------------------------------------------------------------------------------------------------
// MULTI DOGFIGHT FUNCTIONS
//

// call once per level just before entering the mission
void multi_df_level_pre_enter();

// evaluate a kill in dogfight by a netplayer
void multi_df_eval_kill(net_player *killer, object *dead_obj);

// debrief
void multi_df_debrief_init();

// do frame
void multi_df_debrief_do();

// close
void multi_df_debrief_close();

#endif
