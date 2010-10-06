// TabSound.cpp : implementation file
//
#include <stdio.h>

#include "stdafx.h"
#include "launcher.h"
#include "TabSound.h"
#include "TabJoystick.h"

#define DIRECTINPUT_VERSION 0x0500 

#include <Dinput.h> 

#include "win32func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int NUM_SND_MODES = 4;

int num_songs = 0;

char *sound_card_modes[NUM_SND_MODES] =
{
	"DirectSound",
	"EAX",
	"Aureal A3D",
	"No Sound"
}; 

/////////////////////////////////////////////////////////////////////////////
// CTabSound dialog

CTabSound::CTabSound(CWnd* pParent /*=NULL*/)
	: CDialog(CTabSound::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabSound)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CTabSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSound)
	DDX_Control(pDX, IDC_CDROM_DRIVE, m_cdrom_drive_list);
	DDX_Control(pDX, IDC_SOUND_CARD, m_sound_api_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabSound, CDialog)
	//{{AFX_MSG_MAP(CTabSound)
	ON_BN_CLICKED(IDC_CD, OnCDClick)
	ON_BN_CLICKED(IDC_OGG, OnOggClick)
	ON_BN_CLICKED(IDC_RANDOMIZE, OnRandomize)
	ON_BN_CLICKED(IDC_CREATE_PLAYLIST, OnCreatePlaylist)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSound message handlers

void CTabSound::OnApply(char *reg_path, char *settings_file)
{
	// Sound settings
	int index = m_sound_api_list.GetCurSel();

	DWORD check = 1;
	const int CHECKED = 1;
	char drive[4];
	int cd_index;
	
	char string[20];
	m_sound_api_list.GetLBText(index, string);
	reg_set_sz(reg_path, "Soundcard", string);

	check = (((CButton *) GetDlgItem(IDC_CD))->GetCheck() == CHECKED) ? 1 : 0;
	if (check == 1) {
		reg_set_dword(reg_path, "Play Mode", 0);
		cd_index = m_cdrom_drive_list.GetCurSel();
		m_cdrom_drive_list.GetLBText(cd_index, drive);
		reg_set_sz(reg_path, "Drive Letter", drive);
	} else
		reg_set_dword(reg_path, "Play Mode", 1);

	check = (((CButton *) GetDlgItem(IDC_RANDOMIZE))->GetCheck() == CHECKED) ? 1 : 0;
	
	reg_set_dword(reg_path, "Random Playback", check);
	
}

BOOL CTabSound::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char drive_buffer[300];
	char drive[4];
	int returned_chars, offset = 0;
	
	for(int i = 0; i < NUM_SND_MODES; i++)
		m_sound_api_list.InsertString(i, sound_card_modes[i]);
		
	m_sound_api_list.SetCurSel(0);

	returned_chars = GetLogicalDriveStrings(sizeof(drive_buffer), drive_buffer);
	
	while (offset < returned_chars) {
		for (int x=0; x<4; x++) 
			drive[x] = drive_buffer[x+offset];
	
		offset += 4;
		if (GetDriveType(drive) == DRIVE_CDROM) 
			m_cdrom_drive_list.AddString(drive);
	}

	m_cdrom_drive_list.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabSound::LoadSettings(char *reg_path)
{
	DWORD play_mode, random;
	char drive[4];
	int index;
				
	char local_port_text[50];
	reg_get_sz(reg_path, "SoundCard", local_port_text, 50);

	for(int i = 0; i < NUM_SND_MODES; i++)
	{
		if(stricmp(sound_card_modes[i], local_port_text) == 0)
		{
			m_sound_api_list.SetCurSel(i);
			continue;
		}
	}

	reg_get_dword(reg_path, "Play Mode", &play_mode);
	reg_get_dword(reg_path, "Random Playback", &random);
	reg_get_sz(reg_path, "Drive Letter", drive, 4);
	
	if (play_mode == 0)
		((CButton *) GetDlgItem(IDC_CD))->SetCheck(TRUE);
	
	if (play_mode == 1)
		((CButton *) GetDlgItem(IDC_OGG))->SetCheck(TRUE);
	
	if (random == 1)
		((CButton *) GetDlgItem(IDC_RANDOMIZE))->SetCheck(TRUE);

	index = m_cdrom_drive_list.FindString(-1, drive);
	if (index >= 0)
		m_cdrom_drive_list.SetCurSel(index);
	
}

void CTabSound::OnCDClick()
{
	
}

void CTabSound::OnOggClick()
{
	
}

void CTabSound::OnRandomize()
{
	
}

void CTabSound::OnCreatePlaylist()
{
	char browse_folder[MAX_PATH] = "";
	char ch;
	FILE *fp, *fp1;
	
	if (browse_for_dir(browse_folder)) {
		CTabSound::SearchFolder(browse_folder);
		if (num_songs > 0) {
			fp = fopen("Playlist.mrp", "w");
			fp1 = fopen("temp_____.mrp", "r");
			fprintf(fp, "%d\n", num_songs);

			while (!feof(fp1)) {
				ch = fgetc(fp1);
				fputc(ch, fp);
			}
		
			fcloseall();

			remove("temp_____.mrp");

			MessageBox("Playlist sucessfully created!", "Imperial Alliance Launcher", MB_OK);
		} else {
			MessageBox("No valid music files found!", "Imperial Alliance Launcher", MB_OK);
			fcloseall();
			remove("temp_____.mrp");
		}
	}

}

bool CTabSound::SearchFolder(char *Folder)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char SearchPath[MAX_PATH] = "";
	char SubFolder[MAX_PATH] = "";
	char temp[MAX_PATH];
	

	strcpy(SearchPath, Folder);
	strcat(SearchPath, "\\*.*");

	hFind = FindFirstFile(SearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox("No valid music files in this folder!", "Imperial Alliance Launcher", MB_OK);

		return false;
	}

	CTabSound::FindMusicFiles(Folder);
	//	return false;

	if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		strcpy(temp, Folder);
		strcat(temp, "\\");
		strcat(temp, FindFileData.cFileName);
		
		if ((strcmp(FindFileData.cFileName,".") != 0) && 
		    (strcmp(FindFileData.cFileName, "..") != 0))
			CTabSound::SearchFolder(temp);
		
	}

	while (FindNextFile(hFind, &FindFileData))
	{
		  
		if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			strcpy(temp, Folder);
			strcat(temp, "\\");
			strcat(temp, FindFileData.cFileName);
	
				if ((strcmp(FindFileData.cFileName,".") != 0) && 
					(strcmp(FindFileData.cFileName, "..") != 0))
						CTabSound::SearchFolder(temp);
		}
	}
	
	FindClose(hFind);

	return true;
}

bool CTabSound::FindMusicFiles(char *Folder)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char SearchPath[MAX_PATH] = "";
	char SubFolder[MAX_PATH] = "";
	char TrimedFilename[MAX_PATH] = "";
	FILE *fp;
	
	strcpy(SearchPath, Folder);
	strcat(SearchPath, "\\*.mp3");
	
	fp = fopen("temp_____.mrp", "a+");
	
	hFind = FindFirstFile(SearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//MessageBox("No valid music files in this folder!", "Imperial Alliance Launcher", MB_OK);

		return false;
	}

	//TrimExtension(FindFileData.cFileName, TrimedFilename);
	
	//SendMessage(GetDlgItem(g_hwnd, IDC_FILELIST), LB_ADDSTRING,
	//	        0, (LPARAM)TrimedFilename);

	//fprintf(fp, "%s\n", TrimedFilename);
	fprintf(fp, "%s\\%s\n", Folder, FindFileData.cFileName);
	num_songs++;

	while (FindNextFile(hFind, &FindFileData))
	{
		//TrimExtension(FindFileData.cFileName, TrimedFilename);
		
		//SendMessage(GetDlgItem(g_hwnd, IDC_FILELIST), LB_ADDSTRING,
		 //       0, (LPARAM)TrimedFilename);

		//fprintf(fp, "%s\n", TrimedFilename);
		fprintf(fp, "%s\\%s\n", Folder, FindFileData.cFileName);

		num_songs++;
	}
		
	FindClose(hFind);

	fclose(fp);

	return true;
}

void CTabSound::OnDestroy() 
{
	//if(dinput)
	//	dinput->Release();

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
