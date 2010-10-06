/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/JumpNode/JumpNode.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2004/08/13 22:47:41 $
 * $Author: Spearhawk $
 *
 * Header for everything to do with jump nodes
 *
 * $Log: JUMPNODE.H,v $
 * Revision 1.1.1.1  2004/08/13 22:47:41  Spearhawk
 * no message
 *
 * Revision 1.1.1.1  2004/08/13 22:03:35  Darkhill
 * no message
 *
 * Revision 2.3  2004/03/05 09:02:04  Goober5000
 * Uber pass at reducing #includes
 * --Goober5000
 *
 * Revision 2.2  2002/12/17 01:56:36  DTP
 * Bumped MAX JUMP-nodes to 50. if anybody wants a Jump-node forest
 *
 * Revision 2.1  2002/08/01 01:41:06  penguin
 * The big include file move
 *
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 2     10/07/98 10:53a Dave
 * Initial checkin.
 * 
 * 1     10/07/98 10:49a Dave
 * 
 * 2     3/21/98 7:36p Lawrance
 * Move jump nodes to own lib.
 * 
 * 1     3/21/98 3:53p Lawrance
 *
 * $NoKeywords: $
 */

#ifndef __JUMPNODE_H__
#define __JUMPNODE_H__

#include <stdlib.h>

#include "globalincs/globals.h"

struct vector;
struct object;

#define MAX_JUMP_NODES	50

#define JUMP_NODE_MODEL	"navbuoy.pof"

typedef struct {
	int	modelnum;
	int	objnum;						// objnum of this jump node
	char	name[NAME_LENGTH];
	int iff;				// iff for jump node, only used in ImpEd
} jump_node_struct;

extern int Num_jump_nodes;
extern jump_node_struct Jump_nodes[MAX_JUMP_NODES];

int	jumpnode_create(vector *pos);
void	jumpnode_render(object *jumpnode_objp, vector *pos, vector *view_pos = NULL);
void	jumpnode_render_all();	// called by FRED

#endif
