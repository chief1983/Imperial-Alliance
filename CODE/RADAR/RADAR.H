/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Radar/Radar.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * Prototypes for radar code
 *
 * $Log: RADAR.H,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:32:57  Darkhill
 * no message
 *
 * Revision 2.0  2002/06/03 04:02:27  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:51a Dave
 * 
 * 10    12/29/97 4:22p Lawrance
 * Draw NEUTRAL radar dots after FRIENDLY.. clean up some radar code.
 * 
 * 9     11/06/97 5:02p Dave
 * Finished reworking standalone multiplayer sequencing. Added
 * configurable observer-mode HUD
 * 
 * 8     11/05/97 11:21p Lawrance
 * implement new radar gauge
 * 
 * 7     10/11/97 6:38p Lawrance
 * implementing damage effects to radar
 * 
 * 6     3/25/97 3:55p Lawrance
 * allowing debris to be targeted and shown on radar
 * 
 * 5     2/17/97 5:18p John
 * Added a bunch of RCS headers to a bunch of old files that don't have
 * them.
 *
 * $NoKeywords: $
 */

#ifndef _RADAR_H
#define _RADAR_H

extern int Radar_static_looping;

extern bool useTwoRadarScreens;

extern void radar_init();
extern void radar_plot_object( object *objp );
extern void radar_frame_init();
extern void radar_mission_init();
extern void radar_frame_render(float frametime);

// observer hud rendering code uses this function
void radar_draw_blips_sorted(int distort=0);
void radar_draw_range();
void radar_blit_gauge();

#endif

