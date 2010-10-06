#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "globalincs/pstypes.h"
#include "osapi/osregistry.h"
#include "osapi/osapi.h"
#include "math/floating.h"
#include "cmdline/cmdline.h"
#include "gamesequence/gamesequence.h"
#include "graphics/2d.h"
#include "bmpman/bmpman.h"
#include "exceptionhandler/exceptionhandler.h"
#include "io/timer.h"
#include "cfile/cfile.h"
#include "io/key.h"
#include "io/mouse.h"
#include "graphics/font.h"
#include "globalincs/alphacolors.h"
#include "palman/palman.h"
  
#include "fonttool/fonttool.h"
#include "fonttool/resource.h"
#include "fonttool/popfile.h"

BOOL CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK CreateDlgProc(HWND, UINT, WPARAM, LPARAM);

char *create_string = "If you specify a PCX file, then a font will be" \
" created with the same base name.  If you also" \
" specify a font file, then it will use the kerning" \
" data from that font file when it creates the new" \
" font from the PCX file.";

char *edit_string = "If you specify a font file by itself then it will" \
" allow you to interactively kern that font.";

char *copy_string = "If you specify two font files, then the kerning" \
" data from the first font will be copied into the second font.";

void CreateMyTooltip(HWND hwnd, LPSTR lptstr);

HWND output_window;

#define EXE_FNAME			("fonttool.exe")

char *program_title = "Fonttool";
char *program_class_name = "FonttoolClass";
char *program_app_name = "Imperial Alliance";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow)
{
	int result = -1;
	HICON hIcon;

	hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON),
				IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

	SendMessage((HWND)os_get_window(), WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
	SendMessage((HWND)os_get_window(), WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);

	DialogBox(hInst, "MAIN", NULL, MainDlgProc);

	return result;
}


BOOL CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HICON hIcon;
	char pcx_name[MAX_PATH] = "";
	char font_name[MAX_PATH] = "";
	char font_name2[MAX_PATH] = "";
	char curr_dir[100] = "";
	bool has_pcx = false;
	bool has_font = false;
	bool has_font2 = false;
	
	switch (message)
	{
	case WM_INITDIALOG:
		hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON),
				IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);

		CreateMyTooltip(GetDlgItem(hDlg, IDC_CREATE), create_string);
		CreateMyTooltip(GetDlgItem(hDlg, IDC_EDIT), edit_string);
		CreateMyTooltip(GetDlgItem(hDlg, IDC_COPY), copy_string);

		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_CREATE:
				GetCurrentDirectory(MAX_PATH, curr_dir);
				
				PopFileInitialize(hDlg, "PCX Files (*.pcx)\0*.pcx\0");
				if (PopFileOpenDlg(hDlg, pcx_name, curr_dir, "Open PCX To Build Font") != 0) {
					has_pcx = TRUE;
					PopFileInitialize(hDlg, "IA Fonts (*.if)\0*.if\0");
					if (PopFileOpenDlg(hDlg, font_name, curr_dir, "Font To Use Kerning Data") != 0) {
						has_font = TRUE;
					}
				}

				SetCurrentDirectory(curr_dir);
				
				if (has_pcx) {
					output_window = CreateDialog(GetModuleHandle(NULL), "CREATE", hDlg, CreateDlgProc);
					ShowWindow(output_window, SW_NORMAL);
				}

				if (has_pcx && !has_font)
					fonttool_create_font(pcx_name, NULL);
				if (has_pcx && has_font)
					fonttool_create_font(pcx_name, font_name);

				return TRUE;		
			case IDC_EDIT:
				GetCurrentDirectory(MAX_PATH, curr_dir);
			
				PopFileInitialize(hDlg, "IA Fonts (*.if)\0*.if\0");
				
				if (PopFileOpenDlg(hDlg, font_name, curr_dir, "Open Imperial Alliance Font") != 0) {
					SetCurrentDirectory(curr_dir);
					EndDialog(hDlg, 0);	
					fonttool_edit_kerning(font_name);
				}

				return TRUE;
			case IDC_COPY:
				GetCurrentDirectory(MAX_PATH, curr_dir);
			
				PopFileInitialize(hDlg, "IA Fonts (*.if)\0*.if\0");

				if (PopFileOpenDlg(hDlg, font_name, curr_dir, "Open Imperial Alliance Font To Copy Kerning From") != 0) {
					has_font = true;
					if (PopFileOpenDlg(hDlg, font_name2, curr_dir, "Open Imperial Alliance Font To Copy Kerning To") != 0) {
						has_font2 = true;
					}
				}

				SetCurrentDirectory(curr_dir);
			
				if (has_font && has_font2) {
					output_window = CreateDialog(GetModuleHandle(NULL), "CREATE", hDlg, CreateDlgProc);
					ShowWindow(output_window, SW_NORMAL);

					fonttool_kerning_copy(font_name, font_name2);
				}

				return TRUE;
		}
	 
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		PostQuitMessage(0);

		return TRUE;
	}

	return FALSE;
}

BOOL CALLBACK CreateDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HICON hIcon;
	
	switch (message)
	{
	case WM_INITDIALOG:
		hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON),
				IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
		
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDOK:
				EndDialog(hDlg, 0);
				PostQuitMessage(0);
				return TRUE;		
			
			case IDC_INFO:
				return TRUE;
		}
	
	case WM_DESTROY:
		EndDialog(hDlg, 0);
		PostQuitMessage(0);
	
		return TRUE;
	}

	return FALSE;
}

void CreateMyTooltip(HWND hwnd, LPSTR lptstr)
{
    // struct specifying control classes to register
    INITCOMMONCONTROLSEX iccex; 
    HWND hwndTT;                 // handle to the ToolTip control
    // struct specifying info about tool in ToolTip control
    TOOLINFO ti;
    unsigned int uid = 0;       // for ti initialization
    RECT rect;                  // for client area coordinates

    /* INITIALIZE COMMON CONTROLS */
    iccex.dwICC = ICC_WIN95_CLASSES;
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&iccex);

    /* CREATE A TOOLTIP WINDOW */
    hwndTT = CreateWindowEx(WS_EX_TOPMOST,
        TOOLTIPS_CLASS,
        NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,		
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        hwnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
        );

    SetWindowPos(hwndTT,
        HWND_TOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    /* GET COORDINATES OF THE MAIN CLIENT AREA */
    GetClientRect (hwnd, &rect);

    /* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = hwnd;
    ti.hinst = GetModuleHandle(NULL);
    ti.uId = uid;
    ti.lpszText = lptstr;
        // ToolTip control will cover the whole window
    ti.rect.left = rect.left;    
    ti.rect.top = rect.top;
    ti.rect.right = rect.right;
    ti.rect.bottom = rect.bottom;

    /* SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW */
    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);	
	SendMessage(hwndTT, TTM_SETMAXTIPWIDTH, 0, (LPARAM)300);
	SendMessage(hwndTT, TTM_SETDELAYTIME, (WPARAM)TTDT_AUTOPOP, (LPARAM)25000);

}

void app_init()
{
	// Initialize the timer before the os
	timer_init();

	int s1, e1;

	char whee[1024];
	GetCurrentDirectory(1024, whee);
	strcat(whee, "\\");
	strcat(whee, EXE_FNAME);

	//Initialize the libraries
	s1 = timer_get_milliseconds();
	if(cfile_init(whee, NULL)){			// initialize before calling any cfopen stuff!!!
		exit(1);
	}		
	e1 = timer_get_milliseconds();
		
	os_init(program_class_name, program_app_name);
	os_set_title(program_title);

	gr_init(GR_640, GR_OPENGL, 32, 640, 480);
	
	// tried d3d ?
	extern int Gr_inited;
	if(!Gr_inited){
		extern char Device_init_error[512];		
		MessageBox( NULL, Device_init_error, "Error intializing OpenGL!", MB_OK|MB_TASKMODAL|MB_SETFOREGROUND );
		return;
	}

	// Set the gamma
	gr_set_gamma(1.0f);
	
	key_init();
	mouse_init();

	// load non-darkening pixel defs
	palman_load_pixels();

	// initialize alpha colors
	alpha_colors_init();	

	timeBeginPeriod(1);
}

void close_graphics()
{
	timeEndPeriod(1);

	gr_reset_clip();
	gr_clear();
	gr_flip();

	bm_unload_all();				// free bitmaps

	gr_close();

	ShowCursor(TRUE);
}

void app_shutdown(void)
{
	os_cleanup();
}

void print_out(char *text)
{
	SendMessage(GetDlgItem(output_window, IDC_INFO), LB_ADDSTRING, 0, (LPARAM)text);

	int count = SendMessage(GetDlgItem(output_window, IDC_INFO), LB_GETCOUNT, 0, 0);
	SendMessage(GetDlgItem(output_window, IDC_INFO), LB_SETCURSEL, (WPARAM)count-1, 0);
	SendMessage(GetDlgItem(output_window, IDC_INFO), LB_SETCARETINDEX, -1, 0);
}

