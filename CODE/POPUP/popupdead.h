/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Popup/PopupDead.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * Header for the death popup
 *
 * $Log: popupdead.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:11:36  Darkhill
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
 * 3     4/22/98 4:59p Allender
 * new multiplayer dead popup.  big changes to the comm menu system for
 * team vs. team.  Start of debriefing stuff for team vs. team  Make form
 * on my wing work with individual ships who have high priority orders
 * 
 * 2     2/10/98 11:20p Lawrance
 * Implement separate dead popup system
 * 
 * 1     2/10/98 6:02p Lawrance
 *
 * $NoKeywords: $
 */

#ifndef __POPUPDEAD_H__
#define __POPUPDEAD_H__

// return values for popup_do_frame for multiplayer
#define POPUPDEAD_DO_RESPAWN		0
#define POPUPDEAD_DO_OBSERVER		1
#define POPUPDEAD_DO_MAIN_HALL	2

void	popupdead_start();
void	popupdead_close();
int	popupdead_do_frame(float frametime);
int	popupdead_is_active();

#endif
