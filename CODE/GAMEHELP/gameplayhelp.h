/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/GameHelp/GameplayHelp.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:40 $
 * $Author: Spearhawk $
 *
 * Header for displaying in-game help
 *
 * $Log: gameplayhelp.h,v $
 * Revision 1.1.1.1  2004/08/13 22:47:40  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 20:45:05  Darkhill
 * no message
 *
 * Revision 2.0  2002/06/03 04:02:22  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:07  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/07/98 10:52a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:48a Dave
 * 
 * 2     3/09/98 9:54p Lawrance
 * integrate new art for gameplay help
 * 
 * 1     3/09/98 5:05p Lawrance
 *
 * $NoKeywords: $
 */

#ifndef __GAMEPLAY_HELP_H__
#define __GAMEPLAY_HELP_H__

void gameplay_help_init();
void gameplay_help_close();
void gameplay_help_do_frame(float frametime);

#endif
