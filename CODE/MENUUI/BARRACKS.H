/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

/*
 * $Logfile: /Freespace2/code/MenuUI/Barracks.h $
 * $Revision: 2.0 $
 * $Date: 2002/06/03 04:02:24 $
 * $Author: penguin $
 *
 * C source file for implementing barracks
 *
 * $Log: barracks.h,v $
 * Revision 2.0  2002/06/03 04:02:24  penguin
 * Warpcore CVS sync
 *
 * Revision 1.1  2002/05/02 18:03:09  mharris
 * Initial checkin - converted filenames and includes to lower case
 *
 * 
 * 3     2/02/99 11:58a Neilk
 * added vss revision/log comments
 *
 * $NoKeywords: $
 */
#ifndef _BARRACKS_H
#define _BARRACKS_H

// initialize the barracks 
void barracks_init();

// do a frame for the barrracks
void barracks_do_frame(float frametime);

// close the barracks
void barracks_close();

// pilot info crap
void pilot_info_init(void);
void pilot_info_do(float frametime);
void pilot_info_close(void);

// pilot management crap
void pilot_manage_init(void);
void pilot_manage_do(void);
void pilot_manage_close(void);


#endif // _BARRACKS_H

#define STRCPY1(a, b) do {	\
	Assert(strlen(b) < STAT_COLUMN1_W); \
	strcpy(a, b); \
} while (0)

//static player *Cur_pilot;

/*void barracks_init_stats(scoring_struct *stats);
void barracks_set_hotkeys(bool pilot_text_enter_mode);
void barracks_strip_pcx(char *str);
int barracks_new_pilot_selected(void);
void barracks_set_callsign_enter_mode(bool set_callsign_enter_mode);
void barracks_create_new_pilot(void);
int barracks_pilot_accepted(void);
void barracks_scroll_callsign_up(void);
void barracks_scroll_callsign_down(void);
void barracks_scroll_stats_up(void);
void barracks_scroll_stats_down(void);
void barracks_prev_pic(void);
void barracks_next_pic(void);
void barracks_prev_squad_pic(void);
void barracks_next_squad_pic(void);
void barracks_delete_pilot(void);
int barracks_pilot_filter(char *filename);
void barracks_squad_change_popup(void);*/





