// TabCommLine.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "TabCommLine.h"

#include "win32func.h"
#include "misc.h"

#include "LauncherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
{
	char *exe_name;
	int   file_size;
	char *company;
	char *regname;
	int   flags;

} ExeType;				  

char *exe_types_string[MAX_EXE_TYPES + 2] = 
{
	"Official Freespace 2",     
	"Official Freespace 2 Demo v1.0",
	"Official Freespace 2 Demo v1.1",
	"Official Freespace 1 v1.0",     
	"Official Freespace 1 v1.06",     
	"No valid exe selected",
	"Custom exe (assuming fs2_open exe)",
	// Insert new exe data here and in exe_types
};

// This array stored specific information about the various exe's the launcher may be asked to deal with
ExeType exe_types[MAX_EXE_TYPES + 2] = 
{
//	exe name	   size     Reg dir 1	Reg dir 2			Flags
	"FS2.exe",     2310144,	"Volition", "Freespace2",		FLAG_MULTI | FLAG_D3D5 | FLAG_FS2 | FLAG_3DFX, 
	"FS2Demo.exe", 2224128, "Volition", "Freespace2Demo",	FLAG_MULTI | FLAG_D3D5 | FLAG_FS2 | FLAG_3DFX, 
	"FS2Demo.exe", 2228224, "Volition", "Freespace2Demo",	FLAG_MULTI | FLAG_D3D5 | FLAG_FS2 | FLAG_3DFX, 
	"FS.exe",	   2262016, "Volition", "Freespace", 		FLAG_MULTI | FLAG_D3D5 | FLAG_3DFX,	
	//"FS.exe",	   2279424, "Volition", "Freespace", 		FLAG_MULTI | FLAG_D3D5 | FLAG_3DFX,	
	"ImperialAlliance.exe", 25600100, "EH Works", "Imperial Alliance",	FLAG_MULTI | FLAG_SCP, 
	"Placeholder", 0, NULL, NULL, 0,
	//"ImperialAlliance", 
	// Insert new exe data here and in exe_types_string
	"CUSTOM DONT CHANGE", -1, NULL, NULL,					FLAG_MULTI | FLAG_SCP,
};

typedef struct
{
	char *name;
	bool  use;
	int   flags;
	int   on_flags;
	int   off_flags;
	char *effect;
	char *requires;
	char *desc;
} Flag;
 
enum
{
	EASY_CUSTOM,
	EASY_DEFAULT,
	EASY_ALL_ON,
	EASY_MEM_ON,
	EASY_MEM_OFF,
	// Add new flags here
	EASY_MAX,
};

enum
{
	EFLAG_DEFAULT  =  1 << EASY_DEFAULT,
	EFLAG_ALL_ON   =  1 << EASY_ALL_ON,
	EFLAG_MEM_ON   =  1 << EASY_MEM_ON,
	EFLAG_MEM_OFF  =  1 << EASY_MEM_OFF,
	// Add new flags here

	// Combos
	EFLAG_MEM_ALL_ON  = EFLAG_ALL_ON  | EFLAG_MEM_ON,
	EFLAG_DEFAULT_MEM = EFLAG_DEFAULT | EFLAG_MEM_OFF,
};

char *easy_flag_names[EASY_MAX] =
{
	"Custom",	 
	"Default IA (All features off)",
	"All features on",
	"High memory usage features on",
	"High memory usage features off",
};

// This should contain all know parameters possible
// Flags can be used to describe 'belonging' to a version
const int NUM_PARAMS = 18;
Flag exe_params[NUM_PARAMS] = 
{
	//"-spec",		  false, FLAG_FS2OPEN, EFLAG_ALL_ON,	EFLAG_DEFAULT,		"Slower",		"N/A",			"Enable specular, looks great and doesnt seem to slow things down much",
	"-glow",		  false, FLAG_FS2OPEN, EFLAG_MEM_ALL_ON,EFLAG_DEFAULT_MEM,	"Slower",		"Extra Art",	"Enable glow maps, glow effect on windows and other parts of ships. Some glow map textures can be very large, may cause low video memory cards to struggle",
	"-pcx32",		  false, FLAG_D3D8,	   EFLAG_MEM_ALL_ON,EFLAG_DEFAULT_MEM,	"Slower",		"N/A",			"Enable 32bit PCX, this will load PCX files into 32bit textures which will slightly improve the quality of image but will slow the engine down.",
	"-jpgtga",		  false, FLAG_D3D8,	   EFLAG_MEM_ALL_ON,EFLAG_DEFAULT_MEM,	"Slower",		"Extra Art",	"Enable loading textures from JPG and TGA , this will make colors look smoother but will slow the engine down. You must have JPG and TGA data for this to have any effect.",
	"-d3dmipmap",	  false, FLAG_D3D8,	   EFLAG_MEM_ALL_ON,EFLAG_DEFAULT_MEM,	"Slower",		"N/A",			"Turns on D3D mipmapping which smooths textures over distance, will increase the amount of memory required",
	//"-cell",		  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Slower",		"Extra Art",	NULL,
//	"-phreak", 		  false, FLAG_FS2OPEN, EFLAG_ALL_ON,	EFLAG_DEFAULT,		"None",			"N/A",			"Gives access to Phreaks targeting-code and options",
	//"-ship_choice_3d",false, FLAG_FS2OPEN, EFLAG_ALL_ON,	EFLAG_DEFAULT,		"None",			"N/A",			"Shows the 3D model in the ship selection tab in briefing instead of an ani",
	//"-nobeampierce",  false, FLAG_FS2OPEN, EFLAG_ALL_ON,	EFLAG_DEFAULT,		"None",			"N/A",			"Beams do not pierce shields",
	//"-fps",			  false, 0,			   0,				EFLAG_DEFAULT,		"Dev Tool",		"N/A",			"Enable Frames Per Second counter, developer feature",
	//"-window",		  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Dev Tool",		"N/A",			"Runs game in window, developer feature",
	//"-timerbar",	  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Dev Tool",		"N/A",			"Puts bars at the top of the screen that represent how processer time is spent, best not to make use of this since the meaning of the different colours may change between builds, developer feature",
	//"-stats",		  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Dev Tool",		"N/A",			"Shows memory usage ingame, developer feature",
	//"-coords",		  false, 0,			   0,				EFLAG_DEFAULT,		"Dev Tool",		"N/A",			"Spews out coordinates for the mouse cursor, live on screen. Useful for determining positions for ANI files etc etc",
	//"-show_mem_usage",false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Dev Tool",		"Debug exe",	"Displays an ingame rundown of memory usage, will only work with debug exes",
	"-oldfire",		  false, 0,			   0,				EFLAG_DEFAULT,		"None",			"N/A",			NULL,
	"-d3d_no_vsync",  false, FLAG_D3D8,	   0,				EFLAG_DEFAULT,		"Faster",		"N/A",			"Turn off vsync, may speed things up but you may experience vsync problems",
	"-nohtl",		  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Disable Hardware Transform and Light, this is a really bad idea, the game will go really slowly",
	"-nosound",		  false, 0,			   0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Turns off sound",
	"-nomusic",		  false, 0,			   0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Turns off music",
	"-no_set_gamma",  false, FLAG_D3D8,	   0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Disable D3D gamma code, useful if IA exit causes gamma problems on the desktop",
	//"-dnoshowvid", 	  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Prevents cutscenes from being played",
	"-safeloading",	  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Uses old loading system",
	//"-query_speech",  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Troubleshoot",	"N/A",			"Gives info on sim speech condition within build, indicates if its compiled in and working",
	//"-standalone",	  false, 0,			   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Starts FS2:SCP as a Standalone server. Not acctualy starting the game, a server for multiplayer games",
	"-startgame",	  false, FLAG_MULTI,   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Starts a net game as client master uses last pilot",
	"-closed",		  false, FLAG_MULTI,   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Multiplayer game is closed",
	"-restricted",	  false, FLAG_MULTI,   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Multiplayer game is restricted",
	"-multilog",	  false, FLAG_MULTI,   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Log Multiplayer games",
	"-clientdamage",  false, FLAG_MULTI,   0,				EFLAG_DEFAULT,		"Multi",		"N/A",			"Means that the client, when on his screen he does damage, the server accepts this, instead of having the server determining if the client is doing damage. (net stuff; ping; lag; prediction etc )",
	//"-tablecrcs",	  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"None",			"N/A",			NULL,
	//"-missioncrcs",   false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"None",			"N/A",			NULL,
	//"-pofspew",		  false, 0,			   0,				EFLAG_DEFAULT,		"None",			"N/A",			NULL,
	//"-d3d_particle",  false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Buggy",		"N/A",			"Alternitive particle code, not finished",
	//"-d3d_notmanaged",false, FLAG_FS2OPEN, 0,				EFLAG_DEFAULT,		"Buggy",		"N/A",			"Alternitive texturing code, not finished",
	"-ogg",			  false, 0,				0,				EFLAG_DEFAULT,		"Audio",		"N/A",			"Enable Ogg Vorbis jukebox",
	"-radar",		  false, 0,				0,				EFLAG_DEFAULT,		"None",			"N/A",			"Enable Front/Back radar style",

};

char command_line[MAX_PATH * 3]   = "";
char exe_path[MAX_PATH]           = "";
char standard_param[MAX_PATH]     = "";

/////////////////////////////////////////////////////////////////////////////
// CTabCommLine dialog


CTabCommLine::CTabCommLine(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCommLine::IDD, pParent)
{
	m_exe_path_set = false;
	m_dont_check_comm_params = false;

	//{{AFX_DATA_INIT(CTabCommLine)
	//}}AFX_DATA_INIT
}


void CTabCommLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabCommLine)
	DDX_Control(pDX, IDC_FLAG_SETUP, m_easy_flag);
	DDX_Control(pDX, IDC_USE_FLAGS_CHECK, m_use_flags_check);
	DDX_Control(pDX, IDC_FLAG_LIST, m_flag_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabCommLine, CDialog)
	//{{AFX_MSG_MAP(CTabCommLine)
	ON_EN_CHANGE(IDC_CUSTOM_PARAM, OnChangeCustomParam)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FLAG_LIST, OnItemchangedFlagList)
//	ON_BN_CLICKED(IDC_SELECT_MOD, OnSelectMod)
//	ON_BN_CLICKED(IDC_NO_MOD, OnNoMod)
	ON_CBN_SELCHANGE(IDC_FLAG_SETUP, OnSelchangeFlagSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCommLine message handlers

BOOL CTabCommLine::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Make sure its a checkbox and insert a column 
	m_flag_list.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	m_flag_list.InsertColumn(0, "Flag", LVCFMT_LEFT, 115);
	m_flag_list.InsertColumn(1, "Effect", LVCFMT_LEFT, 75);
	m_flag_list.InsertColumn(2, "Requires", LVCFMT_LEFT, 68);

	((CButton *) GetDlgItem(IDC_FLAG_HELP))->SetCheck(1);

	for(int i = 0; i < EASY_MAX; i++)
	{
		m_easy_flag.InsertString(i,easy_flag_names[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/**
 *
 *
 * @param char *new_path
 */
void CTabCommLine::UpdateFields(char *new_path)
{
	if(new_path == NULL)
	{
		m_exe_path_set = false;
		GetDlgItem(IDC_COMM_LINE_PATH)->SetWindowText("");
		return;
	}

	CString custom_param;
	GetDlgItem(IDC_CUSTOM_PARAM)->GetWindowText(custom_param);

//	CString mod_param;
//	GetDlgItem(IDC_MOD_NAME)->GetWindowText(mod_param);

	strcpy(exe_path, new_path);
	m_exe_path_set = true;

  	strcpy(command_line, exe_path);

	if(strlen(standard_param) > 0)
	{
 		strcat(command_line, " ");
 		strcat(command_line, standard_param);
	}

	if(strlen(custom_param) > 0)
	{
 		strcat(command_line, " ");
 		strcat(command_line, custom_param);
	}

/*	if(strlen(mod_param) > 0)
	{
 		strcat(command_line, " -mod ");
 		strcat(command_line, mod_param);
	}*/

	GetDlgItem(IDC_COMM_LINE_PATH)->SetWindowText(command_line);	
}

/**
 * When the custom parameter edit box is typed into reflect this change in the
 * final command line box
 */
void CTabCommLine::OnChangeCustomParam() 
{
	UpdateFields(exe_path);	
}

/**
 * @return CString - string holding command line (may be empty)
 */
CString CTabCommLine::GetCommLine()
{
	return CString(command_line);
}

/**
 * @return CString - string holding app name, ie C:\Games\Freespace2
 */
CString CTabCommLine::GetAppName()
{
	return CString(exe_path);
}

/**
 * @return CString - string holding app path, ie C:\Games
 */
CString CTabCommLine::GetAppPath()
{
	CString path_only(exe_path);

	int found = path_only.ReverseFind('\\');

	if(found != -1)
	{
		path_only.SetAt(found, '\0');
	}

	return path_only;
}

/**
 * @return int - type of exe (one of following)
 *
 * EXE_TYPE_NONE
 * EXE_TYPE_CUSTOM
 * An integer to reference the 'exe_types' array with
 */
int CTabCommLine::GetExeDescription()
{
	if(m_exe_path_set == false)
	{
		return EXE_TYPE_NONE;
	}

	// If the file doesnt even exist bomb out
	if(!file_exists(exe_path))
	{
		m_exe_path_set = false;
		return EXE_TYPE_NONE;
	}

	// This helps us find the size of the exe
	int file_size = get_file_size(exe_path);
	if(file_size == -1)
	{
		m_exe_path_set = false;
		return EXE_TYPE_NONE;
	}

	// Find the exe name only
	char *filename = cap_file_from_path(exe_path);

	// Use filename and size to determine official builds
	for(int i = 0; i < MAX_EXE_TYPES; i++)
	{
		bool correct_size = true;
		if(exe_types[i].file_size != 0)	{
			correct_size = (exe_types[i].file_size == file_size) ? 1 : 0;
		}

		// Try to identify the exe by size
		if(correct_size)
		{
			// Confirm this by name
			if(stricmp(exe_types[i].exe_name, filename) == 0)
			{
				return i;
			}
		}

	}

	return EXE_TYPE_CUSTOM;
}

/**
 *  This is called when a tick box is ticked or unticked on the parameter list
 */
void CTabCommLine::OnItemchangedFlagList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	UpdateStandardParam();
	UpdateFields(exe_path);

	*pResult = 0;

	if(this->IsWindowVisible() == false)
		return;

	if(pNMListView->iItem == -1)
		return;

	if(pNMListView->iSubItem != 0)
		return;

	if(m_dont_check_comm_params == true)
		return;

	m_easy_flag.SetCurSel(0);

	if(((CButton *) GetDlgItem(IDC_FLAG_HELP))->GetCheck() == 0)
		return;

	if(m_flag_list.GetCheck(pNMListView->iItem) == 0)
		return;

	if(exe_params[pNMListView->iItem].desc == NULL)
	 	return;

	char title[32];
	char body[512];
	sprintf(title,"Info %s", exe_params[pNMListView->iItem].name);
	sprintf(body,"%s:\n\n%s", 
	 	exe_params[pNMListView->iItem].name,
	 	exe_params[pNMListView->iItem].desc );
	MessageBox(body, title, MB_ICONINFORMATION);

	RedrawWindow();
}

/**
 * This takes the standard parameter choices the user has made and turns them into a string
 */
void CTabCommLine::UpdateStandardParam()
{
	strcpy(standard_param, "");

	for(int i = 0; i < NUM_PARAMS; i++)
	{
		if(m_flag_list.GetCheck(i) == TRUE)
		{
			int real_index = m_flag_list.GetItemData(i);

			strcat(standard_param, exe_params[real_index].name);		
			strcat(standard_param, " ");		
		}
	}
}

/**
 *
 */
void CTabCommLine::ConstructFlagList()
{
	// Delete all items ready for a new list
	m_flag_list.DeleteAllItems();

	int exe_flags = 0;
	int exe_type  = GetExeDescription();

	// If we are not sure what this exe is give access to all parameters
	if(exe_type != EXE_TYPE_NONE)
	{
		exe_flags = exe_types[exe_type].flags;
	}

	// For each parameter
	for(int i = 0, j = 0; i < NUM_PARAMS; i++)
	{
		int param = exe_params[i].flags;

		// If this parameter has a required flag and the exe doesnt have it	move onto next
		if( (param != 0) && !(param & exe_flags))
		{
			continue;
		}

		// Insert this item but keep a record of the index number
		// The insert item index will not stay as is and will mess up if there are gaps (unshown params)
		m_flag_list.InsertItem(j, exe_params[i].name, 0);
	  	m_flag_list.SetItemData(j, i);
		m_flag_list.SetItemText(j, 1, exe_params[i].effect);
		m_flag_list.SetItemText(j, 2, exe_params[i].requires);
		j++;
	}
}

bool check_cfg_file(char *dest_buffer, char *path)
{
	strcpy(dest_buffer, path);
			
	char *path_end = strrchr(dest_buffer, '\\');
			
	if(path_end) 
		*path_end = '\0';
			
	strcat(dest_buffer, "\\data\\cmdline_ia.cfg");
			
	return file_exists(dest_buffer);
}

void CTabCommLine::GetCustomParams(char *comm_line)
{
	char custom_param[MAX_PATH] = {'\0'};

	GetDlgItem(IDC_CUSTOM_PARAM)->GetWindowText(custom_param, MAX_PATH);

	strcpy(comm_line, custom_param);
}

/**
 *
 */
bool CTabCommLine::SaveSettings(char *filename, char *game_exe_path)
{
	char reg_path[MAX_PATH];
	int type  = GetRegPath(reg_path);
	int flags = GetFlags();

	
	// more hacky to get to work with our registry key
	type = EXE_TYPE_CUSTOM;
	strcpy(reg_path, "Software\\EH Works\\Imperial Alliance");

	if(type == EXE_TYPE_CUSTOM || flags & FLAG_FS2)
	{
		char custom_param[MAX_PATH] = {'\0'};

		GetDlgItem(IDC_CUSTOM_PARAM)->GetWindowText(custom_param, MAX_PATH);

		if(strlen(standard_param) > 0)
		{
			strcat(custom_param, " ");
			strcat(custom_param, standard_param);
		}

		if(reg_set_sz(reg_path, "CmdLineOptions", custom_param) == false)
		{
			MessageBox("Failed to set command line options");
		}

		/*char mod_param[MAX_PATH];
		GetDlgItem(IDC_MOD_NAME)->GetWindowText(mod_param, MAX_PATH);
		if(reg_set_sz(reg_path, "ModSelected", mod_param) == false)
		{
			MessageBox("Failed to set mod command line option");
		}

		if(strlen(mod_param) > 0)
		{
			strcat(custom_param, "-mod ");
			strcat(custom_param, mod_param);
		}*/

		{
			char path_buffer[MAX_PATH];
			bool cfg_exists  = check_cfg_file(path_buffer, game_exe_path);
			bool flag_use_on = (m_use_flags_check.GetCheck() != 0);
			
			// Make the cfg file
			if(flag_use_on || cfg_exists)
			{
				FILE *fp = fopen(path_buffer, "w");
			
				if(fp != NULL)
				{
					// If use flags write, otherwise leave empty
					if(flag_use_on) {
					  	fwrite(custom_param, strlen(custom_param) * sizeof(char), 1, fp);
					}
			
					fclose(fp);
				}
			}
		}
	}

	return true;
}

/**
 * @return - EXE_TYPE_NONE, EXE_TYPE_CUSTOM or if recognised exe it returns the flag list.
 */
int CTabCommLine::GetFlags()
{
	int type = GetExeDescription();

	if(type == EXE_TYPE_NONE) 
		return 0;

	return exe_types[type].flags;
}

/**
 * @return - EXE_TYPE_NONE, EXE_TYPE_CUSTOM or if recognised exe it returns the flag list.
 */
int CTabCommLine::GetRegPath(char *reg_path)
{
	int currently_selected = GetExeDescription();

	if(currently_selected < MAX_EXE_TYPES)
	{
		sprintf(reg_path, "SOFTWARE\\%s\\%s", 
			exe_types[currently_selected].company,
			exe_types[currently_selected].regname);
		return currently_selected;
	}
	/*else if(currently_selected == EXE_TYPE_NONE)
	{
		reg_path[0] = '\0';
		return EXE_TYPE_NONE;
	}

	sprintf(reg_path, "SOFTWARE\\%s\\%s", 
		exe_types[EXE_TYPE_FS2_OFFICIAL].company,
		exe_types[EXE_TYPE_FS2_OFFICIAL].regname);*/

	return EXE_TYPE_CUSTOM;
}

void CTabCommLine::LoadSettings(char *reg_path, char *game_exe_path)
{
	int  flags = GetFlags();

	/*if(flags & FLAG_MOD)
	{
		GetDlgItem(IDC_SELECT_MOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_NO_MOD)->EnableWindow(TRUE);
		char mod_param[MAX_PATH];
		reg_get_sz(reg_path, "ModSelected", mod_param, MAX_PATH);
		SetModParam(mod_param);
	}
	else
	{
		GetDlgItem(IDC_SELECT_MOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_NO_MOD)->EnableWindow(FALSE);
		SetModParam();
	}*/

	// Get the combined options
	char custom_param[MAX_PATH];
	if(reg_get_sz(reg_path, "CmdLineOptions", custom_param, MAX_PATH) == false)
	{
		return;
	}

	char path_buffer[MAX_PATH];
	bool cfg_exisits = check_cfg_file(path_buffer, game_exe_path);

	if(cfg_exisits && (get_file_size(path_buffer) > 0))
	{
		((CButton *) GetDlgItem(IDC_USE_FLAGS_CHECK))->SetCheck(1);
	}

	UpdateFlagList(custom_param);
}						 

void CTabCommLine::OnSelectMod() 
{
	// taken out since not using this feature right now

	/*char current_dir[MAX_PATH]; 
	GetCurrentDirectory(MAX_PATH, current_dir);

	char freespace_dir[MAX_PATH];
	strcpy(freespace_dir, exe_path);

	char *end = strrchr(freespace_dir, '\\');

	if(end)
	{
		*end = '\0';
	}
	
	if(stricmp(current_dir, freespace_dir) != 0) 
	{
		MessageBox("Please run launcher from same dir as your exe");
		return;
	}

	char buffer[MAX_PATH];
	if(browse_for_dir(
		this->GetSafeHwnd(), 
		current_dir, buffer, 
		"Select your Imperial Alliance mod dir") == false)
	{
		return;
	}

	if(strlen(buffer) == 0)
	{  
		MessageBox("Not a valid MOD directory");
	}

	if(strchr(buffer,' '))
	{
		MessageBox("Mod directory name contains a space, this may cause problems", "Warning");
	}

	if(stricmp(current_dir, buffer)	== 0)
	{
		MessageBox("Cannot choose root");
		return;
	}

	SetModParam(buffer + strlen(current_dir) + 1);*/
}

void CTabCommLine::OnNoMod() 
{
	SetModParam();
}

void CTabCommLine::SetModParam(char *path)
{
//	GetDlgItem(IDC_MOD_NAME)->SetWindowText(path ? path : "");
//	UpdateFields(exe_path);
}

void CTabCommLine::OnSelchangeFlagSetup() 
{				   
  	int easy_flag = m_easy_flag.GetCurSel();

	// Custom setting, leave it alone
	if(easy_flag == 0)
		return;

	m_dont_check_comm_params = true;

	int num_int_flags = m_flag_list.GetItemCount( );
	for(int i = 0; i < num_int_flags; i++)
	{
	  	int index = m_flag_list.GetItemData(i);

		if(exe_params[index].on_flags & (1 << easy_flag))
	  		m_flag_list.SetCheck(i, true);

		if(exe_params[index].off_flags & (1 << easy_flag))
	  		m_flag_list.SetCheck(i, false);
	}

	m_dont_check_comm_params = false;

	// Force launcher to apply these settings to fs2_open
	((CButton *) GetDlgItem(IDC_USE_FLAGS_CHECK))->SetCheck(1);
}

void CTabCommLine::UpdateFlagList(char *string_flag_list)
{
	bool flag_states[NUM_PARAMS];
	memset(flag_states, 0, sizeof(bool) * NUM_PARAMS);

	char *end_string_here = NULL;

	// Seperate custom flags from standard one
	for(int i = 0; i < NUM_PARAMS; i++)
	{
		char *found_str = strstr(string_flag_list, exe_params[i].name);

		if(found_str)
		{
			flag_states[i] = true;

			if(end_string_here == NULL)
			{
				end_string_here = found_str;
			}
		}
	}

	// Cut the standard options out of the custom string
	if(end_string_here != NULL)
	{
	   	if(end_string_here > string_flag_list && end_string_here[-1] == ' ')
		{
			end_string_here[-1] = '\0';
		}
	  	else
		{
			end_string_here[0] = '\0';
		}
	}

	// Now set the standard options in the interface
	int num_int_flags = m_flag_list.GetItemCount( );

	m_dont_check_comm_params = true;

	for(i = 0; i < num_int_flags; i++)
	{
	  	int index = m_flag_list.GetItemData(i);

		m_flag_list.SetCheck(i, flag_states[index]);
	}

	m_dont_check_comm_params = false;

	GetDlgItem(IDC_CUSTOM_PARAM)->SetWindowText(string_flag_list);
}
