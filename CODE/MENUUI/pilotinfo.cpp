#include "globalincs/pstypes.h"
#include "menuui/barracks.h"
#include "playerman/managepilot.h"
#include "ui/ui.h"
#include "graphics/font.h"
#include "io/key.h"
#include "gamesnd/gamesnd.h"
#include "osapi/osapi.h"
#include "popup/popup.h"
#include "menuui/playermenu.h"
#include "gamesequence/gamesequence.h"
#include "gamehelp/contexthelp.h"
#include "graphics/2d.h"
#include "ctype.h"
#include "freespace2/freespace.h"
#include "globalincs/systemvars.h"
#include "bmpman/bmpman.h"
#include "io/mouse.h"
#include "osapi/osregistry.h"
#include "globalincs/alphacolors.h"
#include "debugconsole/dbugfile.h"
#include "Playerman/Player.h"
#include "Ship/Ship.h"

#define PI_NUM_BUTTONS		3

#define PI_UP_BUTTON		0
#define PI_DOWN_BUTTON		1
#define PI_EXIT_BUTTON		2

// stats defines
#define NUM_STAT_LINES (21 + MAX_SHIP_TYPES)	// Goober5000
#define STAT_COLUMN1_W 40
#define STAT_COLUMN2_W 10

static int Stat_column1_w[GR_NUM_RESOLUTIONS] =
{
	40,		// GR_640
	40			// GR_1024
};

static int Stat_column2_w[GR_NUM_RESOLUTIONS] =
{
	10,		// GR_640
	10			// GR_1024
};

// constants for coordinate lookup
#define BARRACKS_X_COORD 0
#define BARRACKS_Y_COORD 1
#define BARRACKS_W_COORD 2
#define BARRACKS_H_COORD 3

//title info
static int Pilot_info_title_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		280, 30
	},
	{ // GR_1024
		100, 100
	}
};

// pilot stats field
static int Barracks_stats_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		170, 61, 200, 366  // 180//578, 366
	},
	{ // GR_1024
		42, 351, 240, 400
	}
};

static int Barracks_stats2_coords[GR_NUM_RESOLUTIONS][3] = {
	{ // GR_640
		386, 212, 81	//376	// X2, , W2
	},
	{ // GR_1024
		286, 351, 81		// X2, , W2
	}
};


static char *PilotStats_bitmap_fname[GR_NUM_RESOLUTIONS] = {
	"PilotStats",
	"2_PilotStats"
};

static char *PilotStats_bitmap_mask_fname[GR_NUM_RESOLUTIONS] = {
	"PilotStats-M",
	"2_PilotStats-M"
};

static int Num_stat_lines;
static char Stat_labels[NUM_STAT_LINES][STAT_COLUMN1_W];
static char Stats[NUM_STAT_LINES][STAT_COLUMN2_W];

//void pilot_info_init(void);
//void pilot_info_do(void);
static UI_WINDOW Ui_window;
static UI_BUTTON List_region;
static int Background_bitmap = -1;
extern player *Cur_pilot;
static int Stats_scroll_offset;

struct pilot_stats_buttons {
	char *filename;
	int x, y;
	int text_x, text_y;	// this is where the text label is
	int hotspot;
	int repeat;
	UI_BUTTON button;  // because we have a class inside this struct, we need the constructor below..

	pilot_stats_buttons(char *name, int x1, int y1, int x2, int y2, int h, int r = 0) : filename(name), x(x1), y(y1), text_x(x2), text_y(y2), hotspot(h), repeat(r) {}
};

static pilot_stats_buttons Buttons[GR_NUM_RESOLUTIONS][PI_NUM_BUTTONS] = {
	{
		pilot_stats_buttons("PSB_00", 380,	450,	11,		157,	0),		
		pilot_stats_buttons("PSB_01", 406,	450,	0,		0,		1),
		pilot_stats_buttons("PSB_02", 476,	450,	0,		0,		2),
	},
	{
		pilot_stats_buttons("PSB_00", 8,	122,	11,		157,	0),		
		pilot_stats_buttons("PSB_01", 323,	130,	0,		0,		1),
		pilot_stats_buttons("PSB_02", 350,	130,	0,		0,		2),
	}
};

#define STRCPY1(a, b) do {	\
	Assert(strlen(b) < STAT_COLUMN1_W); \
	strcpy(a, b); \
} while (0)

void init_pilot_stats(scoring_struct *stats)
{
	int i;
	float f;

	Num_stat_lines = 0;

	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "*All Time Stats", 50));
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;	

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Primary weapon shots:", 51));
	sprintf(Stats[Num_stat_lines], "%d", stats->p_shots_fired);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Primary weapon hits:", 52));
	sprintf(Stats[Num_stat_lines], "%d", stats->p_shots_hit);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Primary friendly hits:", 53));
	sprintf(Stats[Num_stat_lines], "%d", stats->p_bonehead_hits);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Primary hit %:", 54));
	if (stats->p_shots_fired > 0) {
		f = (float) stats->p_shots_hit * 100.0f / (float) stats->p_shots_fired;
	} else {
		f = 0.0f;
	}
	sprintf(Stats[Num_stat_lines], XSTR( "%.1f%%", 55), f);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Primary friendly hit %:", 56));
	if (stats->p_bonehead_hits > 0) {
		f = (float) stats->p_bonehead_hits * 100.0f / (float) stats->p_shots_fired;
	} else {
		f = 0.0f;
	}
	sprintf(Stats[Num_stat_lines], XSTR( "%.1f%%", 55), f);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Secondary weapon shots:", 57));
	sprintf(Stats[Num_stat_lines], "%d", stats->s_shots_fired);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Secondary weapon hits:", 58));
	sprintf(Stats[Num_stat_lines], "%d", stats->s_shots_hit);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Secondary friendly hits:", 59));
	sprintf(Stats[Num_stat_lines], "%d", stats->s_bonehead_hits);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Secondary hit %:", 60));
	if (stats->s_shots_fired > 0) {
		f = (float) stats->s_shots_hit * 100.0f / (float) stats->s_shots_fired;
	} else {
		f = 0.0f;
	}
	sprintf(Stats[Num_stat_lines], XSTR( "%.1f%%", 55), f);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Secondary friendly hit %:", 61));
	if (stats->s_bonehead_hits > 0) {
		f = (float) stats->s_bonehead_hits * 100.0f / (float) stats->s_shots_fired;
	} else {
		f = 0.0f;
	}
	sprintf(Stats[Num_stat_lines], XSTR( "%.1f%%", 55), f);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Total kills:", 62));
	sprintf(Stats[Num_stat_lines], "%d", stats->kill_count_ok);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "Assists:", 63));
	sprintf(Stats[Num_stat_lines], "%d", stats->assists);
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	STRCPY1(Stat_labels[Num_stat_lines], XSTR( "*Kills by Ship Type", 64));
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	Assert(Num_stat_lines < NUM_STAT_LINES);
	Stat_labels[Num_stat_lines][0] = 0;
	Stats[Num_stat_lines][0] = 0;
	Num_stat_lines++;

	// Goober5000 - make sure we have room for all ships
	Assert(Num_stat_lines + Num_ship_types < NUM_STAT_LINES);

	for (i=0; i<Num_ship_types; i++) {
		if (stats->kills[i]) {
			Assert(Num_stat_lines < NUM_STAT_LINES);

			// Goober5000 - in case above Assert isn't triggered (such as in non-debug builds)
			if (Num_stat_lines >= NUM_STAT_LINES)
			{
				break;
			}

			Assert(strlen(Ship_info[i].name) + 1 < STAT_COLUMN1_W);
			sprintf(Stat_labels[Num_stat_lines], NOX("%s:"), Ship_info[i].name);
			sprintf(Stats[Num_stat_lines], "%d", stats->kills[i]);
			Num_stat_lines++;
		}
	}

	for (i=0; i<Num_stat_lines; i++) {
		gr_force_fit_string(Stat_labels[i], Stat_column1_w[gr_screen.res], Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD]);
		gr_force_fit_string(Stats[i], Stat_column2_w[gr_screen.res], Barracks_stats2_coords[gr_screen.res][BARRACKS_W_COORD]);
	}
}

void display_pilot_stats()
{
	int y = 0;
	int z = Stats_scroll_offset;
	int font_height = gr_get_font_height();
	char *str;
	int i, w, h;
	while (y + font_height <= Barracks_stats_coords[gr_screen.res][BARRACKS_H_COORD]) {
		if (z >= Num_stat_lines) {
			break;
		}

		str = Stat_labels[z];
		if (*str == '*') {
			gr_set_color_fast(&Color_text_heading);
			str++;

			gr_get_string_size(&w, &h, str);
			i = Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y + h / 2 - 1;			
			gr_line(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD], i, Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] - w - 2, i,true);
			gr_line(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] + 1, i, Barracks_stats2_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats2_coords[gr_screen.res][BARRACKS_W_COORD], i,true);

		} else {
			gr_set_color_fast(&Color_text_normal);
		}

		gr_get_string_size(&w, NULL, str);
		gr_printf(Barracks_stats_coords[gr_screen.res][BARRACKS_X_COORD] + Barracks_stats_coords[gr_screen.res][BARRACKS_W_COORD] - w, Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y, "%s", str);
		str = Stats[z];
		if (*str) {
			gr_printf(Barracks_stats2_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_stats_coords[gr_screen.res][BARRACKS_Y_COORD] + y, "%s", str);
		}

		y += font_height;
		z++;
	}
}

void pilot_info_button_pressed(int n)
{
	switch (n) {
		case PI_EXIT_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_PREVIOUS_STATE);

			break;
	}
}

void pilot_info_init(void)
{
	// create interface
	Ui_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);
	Ui_window.set_mask_bmap(PilotStats_bitmap_mask_fname[gr_screen.res]);

	// load background bitmap
	Background_bitmap = bm_load(PilotStats_bitmap_fname[gr_screen.res]);
	if(Background_bitmap < 0){
		// we failed to load the bitmap - this is very bad
		Int3();
	}

	for (int i=0; i<PI_NUM_BUTTONS; i++) {
		// create the object
		Buttons[gr_screen.res][i].button.create(&Ui_window, "", Buttons[gr_screen.res][i].x, Buttons[gr_screen.res][i].y, 60, 30, Buttons[gr_screen.res][i].repeat, 1);

		// set the sound to play when highlighted
		Buttons[gr_screen.res][i].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Buttons[gr_screen.res][i].button.set_bmaps(Buttons[gr_screen.res][i].filename);

		// set the hotspot
		Buttons[gr_screen.res][i].button.link_hotspot(Buttons[gr_screen.res][i].hotspot);
	}

	init_pilot_stats(&Cur_pilot->stats);	
}

void pilot_info_do(float frametime)
{
	int k = Ui_window.process();

	switch (k)
	{
		case KEY_ESC:  // cancel
			gameseq_post_event(GS_EVENT_PREVIOUS_STATE);//GS_EVENT_PREVIOUS_STATE
			break;
	} // end switch
	
	for (int i=0; i<PI_NUM_BUTTONS; i++) {
			if (Buttons[gr_screen.res][i].button.pressed()) {
				pilot_info_button_pressed(i);
			}
	}

	gr_reset_clip();	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0);	
	}
	
	Ui_window.draw();
	// draw title
	char *str = NULL;
	int x, y = 16;
	int w,h;
	
	x = strlen(Player->callsign);

	str = (char *)malloc(x+y+1);
	strcpy(str, Player->callsign);
	strcat(str, "\'s Combat Record");

	gr_get_string_size(&w, &h, str);
	
	gr_set_color_fast(&Color_bright_white);
	gr_string((gr_screen.max_w - w)/2, //Pilot_info_title_coords[gr_screen.res][BARRACKS_X_COORD], 
		      Pilot_info_title_coords[gr_screen.res][BARRACKS_Y_COORD], 
			  str);

	display_pilot_stats();

	gr_flip();
}

void pilot_info_close(void)
{
	// destroy window
	Ui_window.destroy();

	// release background bitmap
	if (Background_bitmap >= 0) {
		bm_unload(Background_bitmap);
	}

	// unload the overlay bitmap
	//help_overlay_unload(BARRACKS_OVERLAY);

	game_flush();
}