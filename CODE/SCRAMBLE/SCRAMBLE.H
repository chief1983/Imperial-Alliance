/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /freespace2/code/Scramble/scramble.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:43 $
 * $Author: Spearhawk $
 *
 * Header file for file scrambler
 *
 * $Log: SCRAMBLE.H,v $
 * Revision 1.1.1.1  2004/08/13 22:47:43  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 21:11:13  Darkhill
 * no message
 *
 * Revision 2.0  2002/06/03 04:02:28  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:12  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/24/98 11:41p Dave
 * 
 * 1     10/24/98 11:31p Dave
 * 
 * 4     4/14/98 1:39p Lawrance
 * Add command line switches to preprocess ship and weapon tables
 * 
 * 3     3/31/98 1:14a Lawrance
 * Get .tbl and mission file encryption working.
 * 
 * 2     3/30/98 5:51p Lawrance
 * file encryption and decryption
 * 
 * 1     3/30/98 5:19p Lawrance
 *
 * $NoKeywords: $
 */

#ifndef __SCRAMBLE_H__
#define __SCRAMBLE_H__

#define PREPROCESS_SHIPS_TBL			0
#define PREPROCESS_WEAPONS_TBL		1

void scramble_file(char *src_filename, char *dest_filename = NULL, int preprocess = -1);
void unscramble_file(char *src_filename, char *dest_filename = NULL);

#endif
