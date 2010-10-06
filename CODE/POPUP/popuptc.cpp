#include <process.h>

#include "freespace2/freespace.h"
#include "gamesnd/gamesnd.h"
#include "io/key.h"
#include "io/mouse.h"
#include "ui/ui.h"
#include "osapi/osapi.h"
#include "gamesequence/gamesequence.h"
#include "globalincs/alphacolors.h"
#include "playerman/managepilot.h"
#include "graphics/font.h"
#include "popup/popuptc.h"
#include "EH_Medals/idline.h"
#include "io/timer.h"

int popup_tc_check_buttons();
void popup_tc_close(int screen);
void popup_tc_force_draw_buttons();
void popup_tc_process_keys(int k);
void popup_tc_draw_button_text();
void popup_tc_print_text();

void popup_tc_get_id_info(void *pin);

int bg_wo_mouse;

#define BUTTON_OK			0
#define BUTTON_CANCEL		1
#define BUTTON_CONNECT		2

#define COORD_X				0
#define COORD_Y				1
#define COORD_WIDTH			2
#define COORD_HEIGHT		3

UI_WINDOW	Popup_tc_window;
UI_BUTTON	Popup_tc_buttons[POPUP_TC_MAX_CHOICES];			// actual lit button
UI_BUTTON	Popup_tc_button_regions[POPUP_TC_MAX_CHOICES];	// fake buttons used for mouse detection over text
UI_INPUTBOX	Popup_tc_pin_input;								// input box for pin
UI_INPUTBOX	Popup_tc_password_input;						// input box for password
UI_INPUTBOX	Popup_tc_callsign_input;						// input box for callsign

int Popup_tc_default_choice;	// which choice is highlighted (ie what gets choosen when enter is pressed)
int current_input;				// tells which of the three input boxes should have focus

// 0 if not trying to connect to TC database, 1 if trying so that some status messages can be displayed
int connecting_to_database; 
// horrible this has to be a global but since i'm using a thread to connect i can't return anything so this is
// going here
Idline id;	
int connection_result;			// holds value of any errors that occured while trying to connect
int ok_to_create_pilot;			// if valid profile has been found then we can create a pilot

int state;						// holds what state the game was in when the popup gets called			

static int Popup_tc_coords[GR_NUM_RESOLUTIONS][4] = 
{
	{ // GR_640
		129, 99, 380, 313
	},
	{ // GR_1024
		206, 159, 1, 1
	}
};

static int Button_tc_coords[GR_NUM_RESOLUTIONS][3][2] =
{
	{ // GR_640
		{474, 224},		// upper left pixel
		{474, 258},
		{474, 292}		
	},
	{ // GR_1024
		{758, 358},		// upper left pixel
		{758, 413},
		{758, 458},		
	}
};

static int Button_tc_regions[GR_NUM_RESOLUTIONS][3][4] = {
	{ // GR_640		
		{464, 232, 474, 257},		// upper right pixel of text, lower left pixel of button
		{464, 267, 474, 292}, 		
		{464, 301, 474, 330} 	
	},
	{ // GR_1024
		{752, 373, 806, 406},		// upper right pixel of text, lower left pixel of button
		{752, 421, 806, 461},		
		{752, 468, 806, 506}		
	}
};

static int Input_box_coords[GR_NUM_RESOLUTIONS][3][2] = {
	{ // GR_640
		{275, 156},		// callsign
		{275, 181},		// pin
		{275, 206}		// password
	},
	{	// GR_1024
		{275, 156},		// callsign
		{275, 181},		// pin
		{275, 206}		// password
	}
};

static int Popup_tc_databox_coords[GR_NUM_RESOLUTIONS][2] = 
{
	{ // GR_640
		160,337
	},
	{ // GR_1024
		160,337
	}
};


static char *Popup_tc_button_filenames[GR_NUM_RESOLUTIONS][3] = 
{
	{ // GR_640
		"Pop_01",				// positive
		"Pop_00",				// negative
		"Pop_05",				// connect
	},
	{
		"2_Pop_01",				// positive
		"2_Pop_00",				// negative
		"2_Pop_05",				// connect
	}
};

#define POPUP_TC_NUM_TEXT 4

UI_XSTR Popup_tc_text[GR_NUM_RESOLUTIONS][POPUP_TC_NUM_TEXT] = {
	{ // GR_640
		{ "Enter your TC Details",	-1,		175,	120,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Name",					-1,		230,	156,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "PIN",					-1,		243,	181,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Password",				-1,		198,	206,	UI_XSTR_COLOR_GREEN, -1, NULL },
	}, 
	{ // GR_1024
		{ "Enter your TC Details",	-1,		288,	193,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Name",					-1,		230,	170,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "PIN",					-1,		216,	195,	UI_XSTR_COLOR_GREEN, -1, NULL },
		{ "Password",				-1,		195,	220,	UI_XSTR_COLOR_GREEN, -1, NULL },
	}
};


static int Popup_tc_hotkeys[3] =
{
	KEY_ENTER,				// OK
	KEY_ESC,				// Cancel
	KEY_SHIFTED | KEY_ENTER	// Connect
};

static char *Popup_tc_button_text[3] =
{
	"OK",
	"Cancel",
	"Connect"
};

// get the filename of the background image to display for the popup
// this should only be called from either the reg desk or the pilot management screen
char *Popup_tc_get_bg_filename(int state)
{		
	if (state == GS_STATE_PILOT_MANAGE) {
		if (gr_screen.res == GR_640)
			return "Pop4PM";
		else
			return "2_Pop4PM";
	}
	if (state == GS_STATE_INITIAL_PLAYER_SELECT) {
		if (gr_screen.res == GR_640)
			return "Pop4";
		else
			return "2_Pop4";
	}

	// default to the pilot select screen
	return "Pop4";
}

int init_popup_tc()
{	
	UI_BUTTON *b;
	char *background; 
	
	if ( (Game_mode & GM_NORMAL) || ((Game_mode && GM_MULTIPLAYER) && !(Game_mode & GM_IN_MISSION)) ){
		game_stop_time();
	}

	// get what game state we are in so we can do different things
	state = gameseq_get_state();
			
	background = Popup_tc_get_bg_filename(state);
	
	Popup_tc_window.create(Popup_tc_coords[gr_screen.res][COORD_X], Popup_tc_coords[gr_screen.res][COORD_Y], Popup_tc_coords[gr_screen.res][COORD_WIDTH], Popup_tc_coords[gr_screen.res][COORD_HEIGHT], 0);
	Popup_tc_window.set_foreground_bmap(background);

	for (int i=0; i<POPUP_TC_MAX_CHOICES; i++) {
		b = &Popup_tc_buttons[i];
		b->create(&Popup_tc_window, "", Button_tc_coords[gr_screen.res][i][0], Button_tc_coords[gr_screen.res][i][1], 30, 25, 0, 1);
	
		b->set_bmaps(Popup_tc_button_filenames[gr_screen.res][i], 4, 0);
		b->set_highlight_action(common_play_highlight_sound);
		b->set_hotkey(Popup_tc_hotkeys[i]);

		// create invisible buttons to detect mouse presses... can't use mask since button region is dynamically sized
		int lx, w, h;

		gr_get_string_size(&w, &h, Popup_tc_button_text[i]);
		lx = Button_tc_regions[gr_screen.res][i][0] - w;
		b = &Popup_tc_button_regions[i];	
	
		b->create(&Popup_tc_window, "", lx, Button_tc_regions[gr_screen.res][i][1], Button_tc_regions[gr_screen.res][i][2]-lx, Button_tc_regions[gr_screen.res][i][3]-Button_tc_regions[gr_screen.res][i][1], 0, 1);
		
		b->hide();
	}

	// create our input boxes
	Popup_tc_callsign_input.create(&Popup_tc_window, Input_box_coords[gr_screen.res][0][COORD_X], Input_box_coords[gr_screen.res][0][COORD_Y], 355, 20, "", UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_LETTER_FIRST);
	Popup_tc_pin_input.create(&Popup_tc_window, Input_box_coords[gr_screen.res][1][COORD_X], Input_box_coords[gr_screen.res][1][COORD_Y], 355, 20, "", UI_INPUTBOX_FLAG_INVIS | UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_NO_LETTERS);
	Popup_tc_password_input.create(&Popup_tc_window, Input_box_coords[gr_screen.res][2][COORD_X], Input_box_coords[gr_screen.res][2][COORD_Y], 355, 20, "", UI_INPUTBOX_FLAG_INVIS |  UI_INPUTBOX_FLAG_KEYTHRU | UI_INPUTBOX_FLAG_PASSWD);
	
	Popup_tc_pin_input.set_focus();
		

	Popup_tc_default_choice = 0;
	connecting_to_database = -1;
	connection_result = ERR_NONE;
	current_input = 1;
	ok_to_create_pilot = 0;
	
	return 0;
}

void popup_tc_check_conn_result(int result, char *status)
{
	switch (result) {
		case ERR_OK: 
			// if the pilot has a callsign make it the default name, if not give it a generic name
			if (id.nick != std::string("")) 
				Popup_tc_callsign_input.set_text((char *)id.nick.c_str());
			else
				Popup_tc_callsign_input.set_text("TCPilot");

			strcat(status, "\nProfile acquired");
			strcat(status, "\nPress OK to create pilot");
			connection_result = ERR_NONE;
			ok_to_create_pilot = 1;
			break;

		case ERR_CONNECT:
			strcat(status, "\nError connecting to Holonet");
			connection_result = ERR_NONE;
			break;

		case ERR_PIN: 
			strcat(status, "\nPIN seems to be invalid");
			connection_result = ERR_NONE;
			break;

		case ERR_CFG:
			strcat(status, "\nNo address to Holonet");
			connection_result = ERR_NONE;
			break;
	}
}

void popup_tc_do()
{
	int k, done = 0, x = 0;
	int screen_id;
	int choice = -1;
	char status[500] = "";
	char pin[5];
	char password[40];
	int tics = 0;
	
	screen_id = gr_save_screen();

	while(!done) {
		os_poll();

		game_set_frametime(-1);
		game_do_state_common(gameseq_get_state(), 0);

		k = Popup_tc_window.process();
		popup_tc_process_keys(k);

		choice = popup_tc_check_buttons();

		switch (choice) {
			case BUTTON_CONNECT: 
				Popup_tc_pin_input.get_text(pin);
				if (pin[0] != 0) {
					// check to see if we have a password
					Popup_tc_password_input.get_text(password);
					if (password[0] == 0)
						strcpy(status, "You must enter a password");
					else {
						connecting_to_database = 1;
						_beginthread(popup_tc_get_id_info, 0, (void *)pin);
						strcpy(status, "Connecting to Imperial Holonet");
					}
				}
				else
					strcpy(status, "You must enter a PIN");
				break;

			case BUTTON_CANCEL:
				done = 1;
				break;

			case BUTTON_OK: 
				char callsign[CALLSIGN_LEN + 1] = "TCPilot";
				if (ok_to_create_pilot == 1) {
					Popup_tc_callsign_input.get_text(callsign);

					// goto which pilot making function we need based on where at in the game we are when
					// trying to create the pilot
					switch (state) {
						case GS_STATE_PILOT_MANAGE:
							pilot_manage_make_tc_pilot(id, callsign);
							break;
	
						case GS_STATE_INITIAL_PLAYER_SELECT:
							player_select_make_tc_pilot(id, callsign);
							break;
					}
					
					done = 1;
				}
				break;
		}
		
		if (k == KEY_ESC)
			done = 1;
	
		gr_restore_screen(screen_id);
		Popup_tc_window.draw();
			
		popup_tc_force_draw_buttons();
		popup_tc_draw_button_text();
		// give a status message so player doesn't think game has locked up
		if (connecting_to_database == 1) {
			Sleep(200);
			strcat(status, ".");
			// just to make it a bit more exciting we shall only print so many '.' and then start over again
			tics++;
			if (tics > 5) {
				strcpy(status, "Connecting to Imperial Holonet");
				tics = 0;
			}
			
		}

		popup_tc_check_conn_result(connection_result, status);

		// print out some text
		popup_tc_print_text();
		gr_string(Popup_tc_databox_coords[gr_screen.res][0], Popup_tc_databox_coords[gr_screen.res][1], status);
			
		gr_flip();
	}

	popup_tc_close(screen_id);
	
}

void popup_tc_close(int screen)
{
	if (screen >= 0){
		gr_free_screen(screen);	
	}

	id.name = "";
	
	Popup_tc_window.destroy();

	if ( (Game_mode & GM_NORMAL) || ((Game_mode && GM_MULTIPLAYER) && !(Game_mode & GM_IN_MISSION)) )
		game_start_time();
}

// See if any of the button should change appearance based on mouse position
void popup_tc_force_draw_buttons()
{
	int i,mouse_is_highlighting=0;
	UI_BUTTON *br, *b;
	
	for ( i=0; i<POPUP_TC_MAX_CHOICES; i++ ) {
		br = &Popup_tc_button_regions[i];
		b = &Popup_tc_buttons[i];
		if ( br->button_down() ) {
			b->draw_forced(2);
			mouse_is_highlighting=1;
			continue;
		}
	}
}

// Draw the button text nicely formatted in the popup
void popup_tc_draw_button_text()
{
	int w, h, i, sx, sy;

	gr_set_color_fast(&Color_bright_blue);

	for ( i=0; i<POPUP_TC_MAX_CHOICES; i++ ) {
		gr_get_string_size(&w, &h, Popup_tc_button_text[i]);

		sx = Button_tc_regions[gr_screen.res][i][0]-w;
		sy = Button_tc_regions[gr_screen.res][i][1]+4;
	
		gr_string(sx, sy, Popup_tc_button_text[i]);
	}


	
}


void popup_tc_process_keys(int k)
{
	if ( k <= 0 ) {
		return;
	}

	if (k == KEY_TAB) {
		current_input++;
		if (current_input > 3)
			current_input = 1;
		
		switch (current_input) {
			case 1:
				Popup_tc_pin_input.set_focus();
				break;
			case 2:
				Popup_tc_password_input.set_focus();
				break;
			case 3:
				Popup_tc_callsign_input.set_focus();
				break;
		}
	}
}

int popup_tc_check_buttons()
{
	int			i;
	UI_BUTTON	*b;

	for ( i = 0; i < POPUP_TC_MAX_CHOICES; i++ ) {
		b = &Popup_tc_button_regions[i];
		if ( b->pressed() ) {
			return i;
		}

		b = &Popup_tc_buttons[i];
		if ( b->pressed() ) {
			return i;
		}
	}

	return -1;
}

void popup_tc_print_text()
{
	gr_set_color_fast(&Color_bright_white);
		
	for (int i=0; i<POPUP_TC_NUM_TEXT; i++) { 
		if (i == 0)
			gr_set_font(FONT2);
		else
			gr_set_font(FONT1);

		gr_string(Popup_tc_text[gr_screen.res][i].x, Popup_tc_text[gr_screen.res][i].y, Popup_tc_text[gr_screen.res][i].xstr);
	}
}

void popup_tc_get_id_info(void *pin)
{
	char ch[100];
	strcpy(ch, (char *)pin);
		
	id = GetIdline(ch);
	
	if (id.name != std::string(""))
		connection_result = ERR_OK;
	else
		connection_result = ERR_CONNECT;

	if (id.name == std::string("PIN Error"))
		connection_result = ERR_PIN;

	if (id.name == std::string("NoCFG"))
		connection_result = ERR_CFG;

	connecting_to_database = 0;

	//return id;
}

void popup_tc()
{		
	init_popup_tc();

	//gamesnd_play_iface(SND_POPUP_APPEAR); 	// play sound when popup appears

	popup_tc_do();

}
