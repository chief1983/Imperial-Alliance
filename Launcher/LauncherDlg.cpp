// LauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "LauncherDlg.h"

#include "TabCommLine.h"
#include "TabRegOptions.h"
#include "TabVideo.h"
#include "TabSound.h"
#include "TabJoystick.h"
#include "TabSpeech.h"
#include "TabNetwork.h"
#include "TabHelp.h"

#include "win32func.h"
#include "misc.h"

CTabCommLine   tab_comm_line;
CTabRegOptions tab_reg_options;
CTabVideo	   tab_video;
CTabSound	   tab_sound;
CTabJoystick   tab_joystick;
CTabSpeech	   tab_speech;
CTabNetwork	   tab_network;
CTabHelp	   tab_help;

char *save_file_name = "IA.ini";
const int NUM_TABS = 7;
CDialog *tab_dialogs[NUM_TABS];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLauncherDlg dialog

CLauncherDlg::CLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLauncherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLauncherDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	currently_selected_tab = -1;
}

void CLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLauncherDlg)
	DDX_Control(pDX, IDC_HOLDER, m_tabctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLauncherDlg, CDialog)
	//{{AFX_MSG_MAP(CLauncherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_NOTIFY(TCN_SELCHANGE, IDC_HOLDER, OnSelchangeHolder)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLauncherDlg message handlers

// Global variables 
 
/**
 * Initialises the tab control system including:
 *
 * Taking tab strings from the 'String Table' in resources
 * Create all dialogs ready for display
 *
 */
BOOL CLauncherDlg::InitTabControl()
{
	// Prepare the inferface
    TCITEM tab; 
	// Add tabs for each string 
    tab.mask = TCIF_TEXT | TCIF_IMAGE; 
    tab.iImage = -1; 

    for (int i = 0; i < NUM_TABS; i++) 
	{ 
        CString tab_name;
		tab_name.LoadString(IDS_1ST_TAB + i);

		tab.pszText = (LPTSTR) (LPCTSTR) tab_name;
	   	m_tabctrl.InsertItem(i, &tab); 

		tab_dialogs[i] = NULL;
	}

	// Prepare the dialog sheets
	tab_comm_line.Create(IDD_COMM_LINE,	GetDlgItem(IDC_DLG_HOLDER));
	//tab_reg_options.Create(IDD_REG_OPTIONS,	GetDlgItem(IDC_DLG_HOLDER));
	tab_video.Create(IDD_VIDEO, GetDlgItem(IDC_DLG_HOLDER));
	tab_sound.Create(IDD_SOUND, GetDlgItem(IDC_DLG_HOLDER));
	tab_speech.Create(IDD_SPEECH, GetDlgItem(IDC_DLG_HOLDER));
	tab_network.Create(IDD_NETWORK, GetDlgItem(IDC_DLG_HOLDER));
  	tab_help.Create(IDD_HELP, GetDlgItem(IDC_DLG_HOLDER));
	tab_joystick.Create(IDD_JOYSTICK, GetDlgItem(IDC_DLG_HOLDER));

  	tab_dialogs[0] = &tab_help;
	tab_dialogs[1] = &tab_comm_line;
	tab_dialogs[2] = &tab_video;
	tab_dialogs[3] = &tab_sound;
	tab_dialogs[4] = &tab_speech;
	tab_dialogs[5] = &tab_network;
	tab_dialogs[6] = &tab_joystick;
	//tab_dialogs[5] = &tab_reg_options;

	return TRUE;
}

BOOL CLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	InitCommonControls();
	InitTabControl();

	FILE * fp = fopen(save_file_name, "r");		

	// If no settings file exists use default settings
	if(fp == NULL)
	{
		const int MAX_FILENAME_TRYS = 1; //3
		char *filename_tries[MAX_FILENAME_TRYS] =
		
		{
			"ImperialAlliance.exe"
			//"fs2_open_r.exe",
			//"fs2_open.exe",
			//"fs2_open_d.exe",
		};

		m_exe_path[0] = '\0';
		for(int i = 0; i < MAX_FILENAME_TRYS; i++)
		{
			char full[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, full);
			int len = strlen(full);
			full[len] = '\\';
			
			strcpy(full + len + 1, filename_tries[i]); 
			
			if(file_exists(full) == true) {
				strcpy(m_exe_path, full); 
				break;
			}
		}
	}
	else
	{
		fread(m_exe_path, sizeof(char), MAX_PATH-1, fp);
		fclose(fp);
	}

	NewExeSet(m_exe_path);
	SelectTab();
	tab_comm_line.UpdateFields(m_exe_path);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

/**
 * If you add a minimize button to your dialog, you will need the code below
 *  to draw the icon.  For MFC applications using the document/view model,
 *  this is automatically done for you by the framework.
 */
void CLauncherDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLauncherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/**
 * Leave the launcher but save any setting changes first
 */
void CLauncherDlg::OnOK() 
{
	OnApply();
	CDialog::OnOK();
}

/**
 * Leave the launcher without saving any settings
 */
void CLauncherDlg::OnCancel() 
{
	CDialog::OnCancel();
}

/**
 * The user has chosen to accept these settings
 */
void CLauncherDlg::OnApply() 
{
	// Collect information
	char reg_path[MAX_PATH];

	int type  = tab_comm_line.GetRegPath(reg_path);
	int flags = tab_comm_line.GetFlags();

	// hack to make it save in our registry key
	strcpy(reg_path, "Software\\EH Works\\Imperial Alliance");

	// Now save details
	FILE *fp = fopen(save_file_name, "w");

	if(fp == NULL)
	{
		MessageBox("Failed to open file to save settings to!");
	}
	else
	{
		fwrite(m_exe_path, sizeof(char), MAX_PATH-1, fp);
		fclose(fp);
	}

	// Just incase try to create the main reg path
	reg_create_dir(reg_path);
						   
	// Save Command line settings
	tab_comm_line.SaveSettings(save_file_name, m_exe_path);

	if(type == EXE_TYPE_CUSTOM || flags & FLAG_FS2)
	{
		tab_video.OnApply(reg_path, flags);
		tab_sound.OnApply(reg_path, save_file_name);
		tab_speech.OnApply(reg_path, save_file_name);
		tab_network.OnApply(reg_path, save_file_name);
		tab_joystick.OnApply(reg_path, save_file_name);
	}


}

void CLauncherDlg::OnSelchangeHolder(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SelectTab(m_tabctrl.GetCurSel());
}

void CLauncherDlg::SelectTab(int selected_tab)
{
	if(selected_tab >= NUM_TABS)
	{
		return;
	}

	// Hide all windows not in use
	for(int i = 0; i < NUM_TABS; i++)
	{
		if(tab_dialogs[i])
		{
			tab_dialogs[i]->ShowWindow(SW_HIDE);
		}
	}
	
	char reg_path[MAX_PATH];
	tab_comm_line.GetRegPath(reg_path);

 	if(selected_tab == 6)
	{			
		tab_reg_options.FillRegList(reg_path);
	}					 

	// If tab control exists show it
	if(tab_dialogs[selected_tab] != NULL)
	{
		GetDlgItem(IDC_DLG_HOLDER)->ShowWindow(SW_SHOW);
		tab_dialogs[selected_tab]->ShowWindow(SW_SHOW);
		currently_selected_tab = selected_tab;
	}
	// Otherwise hide the whole tab
	else if(currently_selected_tab != -1)
	{
		GetDlgItem(IDC_DLG_HOLDER)->ShowWindow(SW_HIDE);
	}
}

/**
 * Try to run the selected exe with the selected command line options	
 */
void CLauncherDlg::OnRun() 
{
	OnApply();

	bool result = run_file( 
		(LPTSTR) (LPCTSTR) tab_comm_line.GetAppName(), 
		(LPTSTR) (LPCTSTR) tab_comm_line.GetAppPath(),
		(LPTSTR) (LPCTSTR) tab_comm_line.GetCommLine());

	if(!result)
	{
		char buffer[1000];
		sprintf(buffer,"Failed to run exe: %s %s %s",
			(LPTSTR) (LPCTSTR) tab_comm_line.GetAppName(), 
			(LPTSTR) (LPCTSTR) tab_comm_line.GetAppPath(),
			(LPTSTR) (LPCTSTR) tab_comm_line.GetCommLine());
		MessageBox(buffer);
	}
}

/**
 * Allows user to browse for a new exe
 */
void CLauncherDlg::OnBrowse() 
{
	char new_file[MAX_PATH];
	char new_path[MAX_PATH] = "";
	OPENFILENAME details;

	memset(&details, 0, sizeof(OPENFILENAME));
	details.lStructSize       = sizeof(OPENFILENAME); 
    details.hwndOwner         = this->GetSafeHwnd(); 
    details.lpstrFilter       = "FS2 Open exe\0*fs2_open*.exe\0Any exe\0*.exe\0"; 
    details.lpstrFileTitle    = new_file;
    details.nMaxFileTitle 	  = MAX_PATH;
    details.lpstrInitialDir   = "C:\\Games\\Freespace2";
    details.lpstrTitle        = "Open Freepspace exe"; 
    details.Flags			  = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR; 

	details.lpstrFile         = new_path;
	details.nMaxFile          = MAX_PATH;

	if(GetOpenFileName(&details) == TRUE)
	{
		strcpy(m_exe_path, new_path);
		NewExeSet(new_path);
	}
}

/**
 * Use this to change selected exe to a new file
 *
 */
void CLauncherDlg::NewExeSet(char *exe_path)
{
	// Update the options
	tab_comm_line.UpdateFields(exe_path);
	tab_comm_line.ConstructFlagList();

	GetDlgItem(IDC_RUN)->EnableWindow( (exe_path != NULL) );
	GetDlgItem(IDC_PATH)->SetWindowText(exe_path);	

	tab_video.Update(
		tab_comm_line.GetExeDescription(), tab_comm_line.GetFlags(), exe_path);

	// Determine the selected options
	char reg_path[MAX_PATH];

	int type  = tab_comm_line.GetRegPath(reg_path);
	int flags = tab_comm_line.GetFlags();

	// hack, hack, hacking a tree
	type = EXE_TYPE_CUSTOM;
	strcpy(reg_path, "Software\\EH Works\\Imperial Alliance");

	tab_comm_line.LoadSettings(reg_path, exe_path);

	tab_dialogs[2] = tab_dialogs[3] = tab_dialogs[4] = tab_dialogs[5] = NULL;

	if(type == EXE_TYPE_CUSTOM || flags & FLAG_FS2)
	{
		tab_video.LoadSettings(reg_path, flags);	
		tab_sound.LoadSettings(reg_path);
		tab_speech.LoadSettings(reg_path);
		tab_network.LoadSettings(reg_path);
		tab_joystick.LoadSettings(reg_path);
 
		tab_dialogs[2] = &tab_video;
		tab_dialogs[3] = &tab_sound;
		tab_dialogs[4] = &tab_speech;
		tab_dialogs[5] = &tab_network;
		tab_dialogs[6] = &tab_joystick;
	}
	
	m_tabctrl.SetCurSel(0);
	SelectTab(0);
}

