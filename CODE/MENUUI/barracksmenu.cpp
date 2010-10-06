#include "globalincs/pstypes.h"
#include "menuui/barracks.h"
#include "playerman/managepilot.h"
#include "playerman/player.h"
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
#include "menuui/snazzyui.h"

#define NUM_BARRACKS_BUTTONS	8

#define PILOT_MANAGE			0
#define EXIT_BUTTON				1
#define PILOT_STATS				2
#define LAST_PILOT_PIC			3
#define NEXT_PILOT_PIC			4
#define VIEW_UNIFORM			5
#define LAST_SQUAD_PIC			6
#define NEXT_SQUAD_PIC			7

#define BARRACKS_IMAGE_NOT_LOADED	-2

// hotspot stuff.....
#define NUM_HOTSPOT_AREAS		4

#define HOTSPOT_MASK_X1			0
#define HOTSPOT_MASK_Y1			1
#define HOTSPOT_MASK_X2			2
#define HOTSPOT_MASK_Y2			3

// num pixels shader is above/below tooltip text
static int Tooltip_padding[GR_NUM_RESOLUTIONS] = {
	4,		// GR_640
	7,		// GR_1024
};

// y location for start of tooltip shader
static int Tooltip_y_coord[GR_NUM_RESOLUTIONS] = {
	469,	// GR_640
	469,	// GR_1024
};

static int Pilot_manage_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		122, 33, 190, 112
	},
	{ // GR_1024   x1, y1, x2, y2
		122, 33, 190, 112
	}
};

static int Pilot_info_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		58, 197, 198, 237
	},
	{ // GR_1024   x1, y1, x2, y2
		58, 197, 198, 237
	}
};

static int Uniform_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		58, 241, 218, 479
	},
	{ // GR_1024   x1, y1, x2, y2
		58, 241, 218, 479
	}
};

static int Exit_hotspot_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640   x1, y1, x2, y2
		506, 0, 639, 479
	},
	{ // GR_640   x1, y1, x2, y2
		506, 0, 639, 479
	}
};


// constants for coordinate lookup
#define BARRACKS_X_COORD 0
#define BARRACKS_Y_COORD 1
#define BARRACKS_W_COORD 2
#define BARRACKS_H_COORD 3

void strip_pcx(char *str);

// pilot picture field
static int Barracks_image_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		292,76, 160, 120 //461, 23, 160, 120
	},
	{ // GR_1024
		782, 58, 160, 120
	}
};

// pilot picture # of # location
static int Barracks_image_number_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		345, 216 //122
	},
	{ // GR_1024
		732, 239
	}
};

// pilot squad logo field
int Barracks_squad_coords[GR_NUM_RESOLUTIONS][4] = {
	{ // GR_640
		308,272, 128,128 //495, 177, 128, 128
	},
	{ // GR_1024
		829, 323, 128, 128
	}
};

// pilot squad # of # location
int Barracks_squad_number_coords[GR_NUM_RESOLUTIONS][2] = {
	{ // GR_640
		345, 420 //130
	},
	{ // GR_1024
		794, 500
	}
};

static char *Barracks_bitmap_fname[GR_NUM_RESOLUTIONS] = {
	"Barracks",		// GR_640
	"2_Barracks"		// GR_1024
};

static char *Barracks_bitmap_mask_fname[GR_NUM_RESOLUTIONS] = {
	"Barracks-M",		// GR_640
	"2_Barracks-M"		// GR_1024
};

struct barracks_buttons {
	char *filename;
	int x, y;
	int text_x, text_y;	// this is where the text label is
	int hotspot;
	int repeat;
	UI_BUTTON button;  // because we have a class inside this struct, we need the constructor below..

	barracks_buttons(char *name, int x1, int y1, int x2, int y2, int h, int r = 0) : filename(name), x(x1), y(y1), text_x(x2), text_y(y2), hotspot(h), repeat(r) {}
};

static int Background_bitmap = -1;
static UI_WINDOW Ui_window, Ui_window1;
static UI_BUTTON List_region;
static UI_INPUTBOX Inputbox;

extern int Player_sel_mode;

static int x1 = 0;
player *Cur_pilot;
static int Num_pilots;
static int Selected_line;
static char Pilots_arr[MAX_PILOTS][MAX_FILENAME_LEN];
static char *Pilots[MAX_PILOTS];
static int Pic_number;
static int Pic_squad_number;
static bool Barracks_callsign_enter_mode;
static int Pilot_ranks[MAX_PILOTS];
static int List_scroll_offset;
static int Stats_scroll_offset;
static int Clone_flag;
static int Pilot_images[MAX_PILOT_IMAGES];
static int Pilot_squad_images[MAX_PILOT_IMAGES];
static int Rank_pips_bitmaps;
static int Rank_pips_count;


static barracks_buttons Buttons[GR_NUM_RESOLUTIONS][NUM_BARRACKS_BUTTONS] = {
//XSTR:OFF
	{		// GR_640
			barracks_buttons("BAB_00", 120, 32,	11,	157,	0),		
			barracks_buttons("BAB_01", 504, 0,	0,		0,		1, 1),
			barracks_buttons("BAB_02", 56,  132,	0,		0,		2,	1),
			barracks_buttons("BAB_03", 252, 204,	0,		0,		3,	1),			
			barracks_buttons("BAB_04", 460, 204,	0,		0,		4,	1),
			barracks_buttons("BAB_05", 58,  240,	578,	413,	5),
			barracks_buttons("BAB_06", 252, 408,	500,	438,	6),
			barracks_buttons("BAB_07", 460, 408,	481,	465,	7),
	},
	{		// GR_1024
			barracks_buttons("2_BAB_00", 14,		196,	35,	252,	0),
			barracks_buttons("2_BAB_01", 518,	209,	0,		0,		1,	1),
			barracks_buttons("2_BAB_02", 561,	209,	0,		0,		2,	1),
			barracks_buttons("2_BAB_03", 896,	229,	0,		0,		3,	1),
			barracks_buttons("2_BAB_04", 958,	229,	0,		0,		4,	1),
			barracks_buttons("2_BAB_05", 914,	681,	932,	665,	5),
			barracks_buttons("2_BAB_06", 854,	681,	800,	704,	6),
			barracks_buttons("2_BAB_07", 854,	724,	778,	743,	7),
	}
//XSTR:ON
};

void check_barracks_hotspot(int x, int y)
{
	char str[20] = "";
	shader shader;
	int shader_y = 460;
	int w;
	int show_shader = 0;
		
	float gray_intensity = 0.02f;													// nearly black
	float c = (gr_screen.mode == GR_DIRECT3D) ? 0.11f : 0.07f;			// adjust for renderer differences
	gr_create_shader(&shader, gray_intensity, gray_intensity, gray_intensity, c);

		
	// combat records area
	if ((x >= Pilot_info_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Pilot_info_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Pilot_info_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Pilot_info_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			strcpy(str, "View Combat Record");
			show_shader = 1;
		}
	}
	

	// pilot management area
	if ((x >= Pilot_manage_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Pilot_manage_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Pilot_manage_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Pilot_manage_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			//str = (char *)malloc(13);
			strcpy(str, "Manage Pilots");
			show_shader = 1;
		}
	}

	// uniform area
	if ((x >= Uniform_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Uniform_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Uniform_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Uniform_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			//str = (char *)malloc(13);
			strcpy(str, "View Uniform");
			show_shader = 1;
		}
	}

	// exit area
	if ((x >= Exit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X1]) && 
		(x <= Exit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_X2]))
	{
		if ((y >= Exit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y1]) && 
			(y <= Exit_hotspot_coords[gr_screen.res][HOTSPOT_MASK_Y2]))
		{
			//str = (char *)malloc(13);
			strcpy(str, "Exit");
			show_shader = 1;
		}
	}

	if (show_shader == 1)
	{
		gr_get_string_size(&w, NULL, str);
						
		shader_y = Tooltip_y_coord[gr_screen.res] - Tooltip_padding[gr_screen.res];
		
		gr_set_shader(&shader);
		gr_shade(0, shader_y, gr_screen.clip_width, (gr_screen.clip_height - shader_y));

		gr_set_color_fast(&Color_bright_white);
		gr_string((gr_screen.max_w - w)/2, 
					Tooltip_y_coord[gr_screen.res], str);
	}

	//free(str);
}

// new pilot name has focus, so update stats/pic to that pilot
int new_pilot_selected()
{
	char stripped[MAX_FILENAME_LEN+1] = "";

	// save the previous pilot first, so changes to it are kept
	if (strlen(Cur_pilot->callsign)) {
		write_pilot_file();
	}

	/*// check if we have a valid pilot hilighted.  If so, attempt to active it
	if ((Num_pilots < 1) || (Selected_line < 0) || (Selected_line >= Num_pilots)) {
		Cur_pilot->callsign[0] = 0;  // this indicates no pilot active
		return -1;
	}

	if (read_pilot_file(Pilots[Selected_line], !Player_sel_mode, Cur_pilot)) {
		Cur_pilot->callsign[0] = 0;  // this indicates no pilot active
		return -1;
	}*/

	// init stuff to reflect new pilot
	int i;
//	barracks_init_stats(&Cur_pilot->stats);
	for (i=0; i<Num_pilot_images; i++) {
		strcpy(stripped, Cur_pilot->image_filename);
		strip_pcx(stripped);
		if (!stricmp(stripped, Pilot_image_names[i])) {
			break;
		}
	}
	Pic_number = i;
	for ( i=0; i<Num_pilot_squad_images; i++) {
		strcpy(stripped, Cur_pilot->squad_filename);
		strip_pcx(stripped);
		if (!stricmp(stripped, Pilot_squad_image_names[i])) {
			break;
		}
	}
	Pic_squad_number = i;	
	
	return 0;
}

void init_player_stuff(int mode)
{
	// determine if we should be looking for single or multiplayers at the outset
	Player_sel_mode = mode;
	
	// get the list of pilots based upon whether we're in single or multiplayer mode
	Num_pilots = 0;
//	Get_file_list_filter = barracks_pilot_filter;

	// single player specific stuff
	if (mode == PLAYER_SELECT_MODE_SINGLE) {
		Num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_SINGLE_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
}
	// multiplayer specific stuff
	else {
		Num_pilots = cf_get_file_list_preallocated(MAX_PILOTS, Pilots_arr, Pilots, CF_TYPE_MULTI_PLAYERS, NOX("*.plr"), CF_SORT_TIME);
	}

	int ranks[MAX_PILOTS];

	int i;
	for (i=0; i<Num_pilots; i++) {
		int j;
		for (j=0; j<Num_pilots; j++) {
			if (!strcmp(Pilots[i], Pilots_arr[j])) {
				ranks[i] = Pilot_ranks[j];
				break;
			}
		}
		Assert(j < Num_pilots);  // Pilot not found?  How is that possible?
	}

	for (i=0; i<Num_pilots; i++) {
		Pilot_ranks[i] = ranks[i];
	}

	Selected_line = List_scroll_offset = 0;
	new_pilot_selected();

}

// strip the possible .pcx extension off a filename
void strip_pcx(char *str)
{
	int flen = strlen(str);
	int elen = 4;		
	if ((flen > 4) && !stricmp(str + flen - elen, ".pcx")) {
		str[flen - elen] = '\0';
	}
}

// show previous pilot pic
void barracks_prev_pic()
{
	// check if no pilot images or no pilot selected
	if ((Num_pilot_images == 0) || (Cur_pilot->callsign[0] == '\0')) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	// reset pilot pic number
	Pic_number--;
	if (Pic_number < 0) {
		Pic_number = Num_pilot_images - 1;
	}

	// copy pilot pic filename into pilot struct
	if ((Pic_number >= 0) && (Pic_number < Num_pilot_images)) {
		strcpy(Cur_pilot->image_filename, Pilot_image_names[Pic_number]);
	}

	// play scroll sound
	gamesnd_play_iface(SND_SCROLL);
}

// show next pilot pic
void barracks_next_pic()
{
	// check if no pilot images or no pilot selected
	if ((Num_pilot_images == 0) || (Cur_pilot->callsign[0] == '\0')) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	// reset pilot pic number
	Pic_number++;
	if (Pic_number >= Num_pilot_images){
		Pic_number = 0;
	}

	// copy pilot pic filename into pilot struct
	if ((Pic_number >= 0) && (Pic_number < Num_pilot_images)){
		strcpy(Cur_pilot->image_filename, Pilot_image_names[Pic_number]);
	}

	// play scroll sound
	gamesnd_play_iface(SND_SCROLL);
}

// show previous squad pic
void barracks_prev_squad_pic()
{
	// check if no pilot images or no pilot selected
	if ((Num_pilot_squad_images == 0) || (Cur_pilot->callsign[0] == '\0')) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	// reset pilot pic number
	Pic_squad_number--;
	if (Pic_squad_number < 0) {
		Pic_squad_number = Num_pilot_squad_images - 1;
	}

	// copy pilot pic filename into pilot struct
	if ((Pic_squad_number >= 0) && (Pic_squad_number < Num_pilot_squad_images)) {
		strcpy(Cur_pilot->squad_filename, Pilot_squad_image_names[Pic_squad_number]);
	}

	// play scroll sound
	gamesnd_play_iface(SND_SCROLL);
}

// show next pilot pic
void barracks_next_squad_pic()
{
	// check if no pilot images or no pilot selected
	if ((Num_pilot_squad_images == 0) || (Cur_pilot->callsign[0] == '\0')) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	// reset pilot pic number
	Pic_squad_number++;
	if (Pic_squad_number >= Num_pilot_squad_images){
		Pic_squad_number = 0;
	}

	// copy pilot pic filename into pilot struct
	if ((Pic_squad_number >= 0) && (Pic_squad_number < Num_pilot_squad_images)){
		strcpy(Cur_pilot->squad_filename, Pilot_squad_image_names[Pic_squad_number]);
	}

	// play scroll sound
	gamesnd_play_iface(SND_SCROLL);
}

// draw pilot image and clean up afterwards
void barracks_draw_pilot_pic()
{
	// draw pilot pic
	if (Cur_pilot->callsign[0] && (Pic_number >= 0) && (Pic_number < Num_pilot_images)) {
		if (Pilot_images[Pic_number] >= 0) {
			// JAS: This code is hacked to allow the animation to use all 256 colors
			extern int Palman_allow_any_color;
			Palman_allow_any_color = 1;
			gr_set_bitmap(Pilot_images[Pic_number]);
			gr_bitmap(Barracks_image_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_image_coords[gr_screen.res][BARRACKS_Y_COORD]);
			Palman_allow_any_color = 0;

			// print number of the current pic
			char buf[40];			
			sprintf(buf, XSTR( "%.2d of %d", 71), Pic_number + 1, Num_pilot_images);
			gr_set_color_fast(&Color_bright_white);
			gr_printf(Barracks_image_number_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_image_number_coords[gr_screen.res][BARRACKS_Y_COORD], buf);				
		}
	} else {
		Pic_number = -1;
	}
}

// draw squad image and clean up afterwards
void barracks_draw_squad_pic()
{
	char buf[40];

	// draw pilot pic
	if (Cur_pilot->callsign[0] && (Pic_squad_number >= 0) && (Pic_squad_number < Num_pilot_squad_images)) {
		if (Pilot_squad_images[Pic_squad_number] >= 0) {
			// JAS: This code is hacked to allow the animation to use all 256 colors
			extern int Palman_allow_any_color;
			Palman_allow_any_color = 1;
			gr_set_bitmap(Pilot_squad_images[Pic_squad_number]);
			gr_bitmap(Barracks_squad_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_squad_coords[gr_screen.res][BARRACKS_Y_COORD]);
			Palman_allow_any_color = 0;

			// print number of current squad pic
			//if(Player_sel_mode != PLAYER_SELECT_MODE_SINGLE){
			sprintf(buf,XSTR( "%d of %d", 71), Pic_squad_number+1, Num_pilot_squad_images);
			gr_set_color_fast(&Color_bright_white);	
			gr_printf(Barracks_squad_number_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_squad_number_coords[gr_screen.res][BARRACKS_Y_COORD], buf);
			//}
		}
	} else {
		Pic_squad_number = -1;
	}	
}

void barracks_button_pressed(int n)
{
	switch (n) {
	// pilot management crap	
		case PILOT_MANAGE:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_PILOT_MANAGE);
			break;
		
	// exit to main hall
		case EXIT_BUTTON:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			break;
	
	// pilot stats
		case PILOT_STATS:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_PILOT_INFO);
			break;
	// view previous pilot pic
		case LAST_PILOT_PIC:
			barracks_prev_pic();
			break;
		// view next pilot pic
		case NEXT_PILOT_PIC:
			barracks_next_pic();
			break;
	
		// view uniform
		case VIEW_UNIFORM:
			gamesnd_play_iface(SND_SWITCH_SCREENS);
			gameseq_post_event(GS_EVENT_VIEW_MEDALS);
			break;
		
			// prve squad pic
		case LAST_SQUAD_PIC:
		
			barracks_prev_squad_pic();
			break;
	
		// next sqaud pic
		case NEXT_SQUAD_PIC:
			barracks_next_squad_pic();
			break;
			
	}
}

void barracks_init()
{
	// save current pilot file, so we don't possibly loose it.
	write_pilot_file();

	// text region crap
	snazzy_menu_init();
	
	// create interface
	Ui_window.create(0, 0, gr_screen.max_w, gr_screen.max_h, 0);
	Ui_window.set_mask_bmap(Barracks_bitmap_mask_fname[gr_screen.res]);

	// load background bitmap
	Background_bitmap = bm_load(Barracks_bitmap_fname[gr_screen.res]);
	//Barracks_mask = bm_lock(Background_bitmap, 8, BMP_AABITMAP);
	
	if(Background_bitmap < 0){
		// we failed to load the bitmap - this is very bad
		Int3();
	}

	// create buttons
	int i;	 
	for (i=0; i<NUM_BARRACKS_BUTTONS; i++){ //  change!
		// create the object
		Buttons[gr_screen.res][i].button.create(&Ui_window, "", Buttons[gr_screen.res][i].x, Buttons[gr_screen.res][i].y, 60, 30, Buttons[gr_screen.res][i].repeat, 1);

		// set the sound to play when highlighted
		Buttons[gr_screen.res][i].button.set_highlight_action(common_play_highlight_sound);

		// set the ani for the button
		Buttons[gr_screen.res][i].button.set_bmaps(Buttons[gr_screen.res][i].filename);

		// set the hotspot
		Buttons[gr_screen.res][i].button.link_hotspot(Buttons[gr_screen.res][i].hotspot);
	}

	// load in help overlay bitmap	
	help_overlay_load(BARRACKS_OVERLAY);
	help_overlay_set_state(BARRACKS_OVERLAY,0);	

	// other init stuff
	List_scroll_offset = Stats_scroll_offset = Pic_number = Pic_squad_number = Selected_line = 0;

	Cur_pilot = &Players[Player_num];
	
	// set up hotkeys for buttons so we draw the correct animation frame when a key is pressed
	//barracks_set_hotkeys(1);

	
	// load up the pilot pic list
	pilot_load_pic_list();	
	pilot_load_squad_pic_list();
	
	// don't load pilot images yet
	for (i=0; i<MAX_PILOT_IMAGES; i++) {
		Pilot_images[i] = BARRACKS_IMAGE_NOT_LOADED;  // while -1 is can't load
		Pilot_squad_images[i] = BARRACKS_IMAGE_NOT_LOADED;
	}
	
	List_region.create(&Ui_window, "", 0, 0, gr_screen.max_w, gr_screen.max_h, 0, 1);
	List_region.hide();

	// base the mode we're in (single or multi) on the status of the currently selected pilot
	init_player_stuff(is_pilot_multi(Player));	
}

// -----------------------------------------------------------------------------
void barracks_do_frame(float frametime)
{
	int k = Ui_window.process();
	int i;
	
	if ( k > 0 ) {
		if ( help_overlay_active(BARRACKS_OVERLAY) ) {
			help_overlay_set_state(BARRACKS_OVERLAY,0);
			k = 0;
		}
	}

	switch (k) {
					
		case KEY_ESC:  // cancel
			gamesnd_play_iface(SND_SWITCH_SCREENS);	
			gameseq_post_event(GS_EVENT_MAIN_MENU);
			
			break;

		
		case KEY_F1:  // show help overlay
			
			gamesnd_play_iface(SND_HELP_PRESSED);
			break;

		case KEY_F2:  // goto options screen
			popup( PF_USE_AFFIRMATIVE_ICON | PF_NO_NETWORKING, 1, POPUP_OK, XSTR("You cannot change your squadron in Single Player mode.", 1445));

			gamesnd_play_iface(SND_SWITCH_SCREENS);
			//gameseq_post_event(GS_EVENT_OPTIONS_MENU);
			break;
		}	// end switch

		// process buttons
		for (i=0; i<NUM_BARRACKS_BUTTONS; i++) { // change!
			if (Buttons[gr_screen.res][i].button.pressed()) {
				barracks_button_pressed(i);
			}
		//}

	}

	// check mouse over help
	if (mouse_down(MOUSE_LEFT_BUTTON)) {
		help_overlay_set_state(BARRACKS_OVERLAY, 0);
	}

	// do pilot pic stuff
	if ((Pic_number >= 0) && (Pic_number < Num_pilot_images)) {
		if (Pilot_images[Pic_number] == BARRACKS_IMAGE_NOT_LOADED) {  // haven't tried loading it yet
			Pilot_images[Pic_number] = bm_load(Pilot_image_names[Pic_number]);
			if (Pilot_images[Pic_number] >= 0) {
				int w, h;

				bm_get_info(Pilot_images[Pic_number], &w, &h, NULL);
				// check for invalid pilot pic file
				if ((w != PLAYER_PILOT_PIC_W) || (h != PLAYER_PILOT_PIC_H)) {
					bm_unload(Pilot_images[Pic_number]);
					Pilot_images[Pic_number] = -1;
				}
			}
		}		
	} else {
		Pic_number = -1;
	}

	// do squad pic stuff
	if ((Pic_squad_number >= 0) && (Pic_squad_number < Num_pilot_squad_images)) {
		if (Pilot_squad_images[Pic_squad_number] == BARRACKS_IMAGE_NOT_LOADED) {  // haven't tried loading it yet
			Pilot_squad_images[Pic_squad_number] = bm_load_duplicate(Pilot_squad_image_names[Pic_squad_number]);
			if (Pilot_squad_images[Pic_squad_number] >= 0) {
				int w, h;

				bm_get_info(Pilot_squad_images[Pic_squad_number], &w, &h, NULL);
				// check for invalid pilot pic file
				if ((w != PLAYER_SQUAD_PIC_W) || (h != PLAYER_SQUAD_PIC_H)) {
					bm_unload(Pilot_squad_images[Pic_squad_number]);
					Pilot_squad_images[Pic_squad_number] = -1;
				}
			}
		}
	} else {
		Pic_squad_number = -1;
	}

	// draw the background, etc
	gr_reset_clip();	
	GR_MAYBE_CLEAR_RES(Background_bitmap);
	if (Background_bitmap >= 0) {
		gr_set_bitmap(Background_bitmap);
		gr_bitmap(0, 0);	
	}		

	// draw pilot image and clean up afterwards
	barracks_draw_pilot_pic();
	barracks_draw_squad_pic();

	// draw the window	
	Ui_window.draw();	

	// blit help overlay if active
	help_overlay_maybe_blit(BARRACKS_OVERLAY);	
	
	// show hotspot help info
	int x,y;
	List_region.get_mouse_pos(&x, &y);
	if (!help_overlay_active(BARRACKS_OVERLAY)) 
		check_barracks_hotspot(x, y);

	
	// flip the page
	gr_flip();
}

// -----------------------------------------------------------------------------
void barracks_close()
{
	// destroy window
	Ui_window.destroy();

	// release background bitmap
	if (Background_bitmap >= 0) {
		bm_unload(Background_bitmap);
	}	

	// unload the overlay bitmap
	help_overlay_unload(BARRACKS_OVERLAY);

	game_flush();
}
