#ifndef __POPUPTC_H__
#define __POPUPTC_H__

#include "EH_Medals/idline.h"

#define POPUP_TC_MAX_CHOICES 3

#define ERR_NONE	-1
#define ERR_OK		1
#define ERR_PIN		2
#define ERR_CONNECT 3
#define ERR_CFG		4

void popup_tc();
// defined in playermenu since its got all the stuff to make the pilot list box look right after creating pilot
void player_select_make_tc_pilot(Idline id, char *name);
// defined in playermanage since its got all the stuff to make the list box look right
void pilot_manage_make_tc_pilot(Idline id, char *name);

#endif
