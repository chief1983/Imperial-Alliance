#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <process.h>

#include "installer.h"
#include "resource.h"

BOOL CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK PathDlgProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK BrowseCallbackProc(HWND, UINT, LPARAM, LPARAM);

char GamePath[MAX_PATH] = "C:\\Program Files\\EH Works\\Imperial Alliance";
HINSTANCE hInst;
HWND hWnd;
BOOL IsInstalled = FALSE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow)
{
	hInst = hInstance;

	DialogBox(hInst, "MAIN", NULL, MainDlgProc);

	return 0;
}

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HICON hIcon;
	char UninstallPath[MAX_PATH] = "";
	FILE *fp;
	
	switch (message)
	{
	case WM_INITDIALOG:
		hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON),
				IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hDlg, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);

		GetCurrentDirectory(MAX_PATH, UninstallPath);
		strcat(UninstallPath, "\\Uninstall.cfg");

		fp = fopen(UninstallPath, "r");
		if (fp == NULL)
			EnableWindow(GetDlgItem(hDlg, IDC_UNINSTALL), FALSE);
		else
			fclose(fp);

		CoInitialize(NULL);
		
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_INSTALL:
								
				DialogBox(hInst, "PATH", hDlg, PathDlgProc);
				EnableWindow(GetDlgItem(hDlg, IDC_UNINSTALL), TRUE);

				return TRUE;
			case IDC_UNINSTALL:
				uninstall();
				delete_registry_entries(GamePath);

				{
				//	MessageBox(hDlg, "Imperial Alliance Uninstalled!", "Success", MB_OK);
				//	EnableWindow(GetDlgItem(hDlg, IDC_UNINSTALL), FALSE);
				}
				return TRUE;		
		}
	
	case WM_DESTROY:

		CoUninitialize();
				
		EndDialog(hDlg, 0);
		PostQuitMessage(0);

		return TRUE;
	}

	return FALSE;
}

BOOL CALLBACK PathDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char temp[MAX_PATH+30];
	int ret;
	static int timer = 0;
	FILE *fp;
		
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_PATH, GamePath);

		hWnd = hDlg;

		return TRUE;

	case WM_TIMER:
		switch (timer)
		{
		case 0:
			SetDlgItemText(hDlg, IDC_STATUS, " |");

			break;
		case 1:
			SetDlgItemText(hDlg, IDC_STATUS, "/");

			break;
		case 2:
			SetDlgItemText(hDlg, IDC_STATUS, "--");

			break;
		case 3:
			SetDlgItemText(hDlg, IDC_STATUS, "\\");

			break;

		}

		timer++;
		if (timer > 3)
			timer = 0;

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_PATH:
			return TRUE;

		case IDC_CONTINUE:
			if (IsInstalled)
			{
				EndDialog(hDlg, 0);
				PostQuitMessage(0);
			}
			
			fp = fopen("IA.ehf", "r");
			
			if (fp != NULL)
			{
				fclose(fp);

				GetDlgItemText(hDlg, IDC_PATH, GamePath, MAX_PATH);

				if (!PathFileExists(GamePath))
				{
					strcat(temp, GamePath);
					strcat(temp, "\ndoesn't exist. Create it?");

					ret = MessageBox(hDlg, temp, "Setup", MB_YESNO);

					if (ret == IDYES)
						CreateFolder(GamePath);
					else
						return TRUE;
				}
				
				SetTimer(hWnd, 1, 500, NULL);

				ShowWindow(GetDlgItem(hDlg, IDC_TEXT), SW_SHOW);
				
				make_registry_entries(GamePath);
				
				if(_beginthread(unzip,0,GamePath)==-1)//||_beginthread(make_timer,0,NULL)==-1)
				{
					// failed to create thread
					MessageBox(hDlg, "Error installing!  Code 1", "Error", MB_ICONEXCLAMATION|MB_OK);
					
					return TRUE;
				}

				copy_setup(GamePath);
			}
			else
				MessageBox(hDlg, "Can't find installion package!  Aborting install!", "Error", MB_ICONEXCLAMATION|MB_OK);
			
		return TRUE;
		
		case IDC_BROWSE:
			BROWSEINFO bi;
			LPITEMIDLIST pIDL;
			LPMALLOC pMem = NULL;
			ZeroMemory(&bi, sizeof(BROWSEINFO));

			GetDlgItemText(hDlg, IDC_PATH, GamePath, MAX_PATH);

			bi.hwndOwner    = hDlg;
			bi.lpszTitle	= "Current folder is:";
			bi.ulFlags		= BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_VALIDATE;
			bi.lpfn			= BrowseCallbackProc;
			bi.lParam       = (LPARAM)GamePath;
					
			pIDL = SHBrowseForFolder(&bi);

			SetDlgItemText(hDlg, IDC_PATH, GamePath);
			
			if(SHGetPathFromIDList(pIDL, GamePath))
			{
				
				SetDlgItemText(hDlg, IDC_PATH, GamePath);

				if( SHGetMalloc(&pMem) == NOERROR )    
				{        
					pMem->Free(pIDL);        
					pMem->Release();    
				}
			}		

			return TRUE;
		}
	

	case IDC_CANCEL:
	case WM_DESTROY:
		EndDialog(hDlg, 0);

		return TRUE;
	}

	return FALSE;
}

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{    
	const int iEditMagicItemId = 0x3744;
	char szPath[MAX_PATH];
		
	HWND hEdit = GetDlgItem(hWnd, iEditMagicItemId);

	switch(uMsg)    
	{        
	case BFFM_INITIALIZED:            
		// select the default directory in the browse folder treeview             
		SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);
		SendMessage(hWnd, BFFM_ENABLEOK, NULL, TRUE);
		
         if (hEdit)
            SetWindowText(hEdit, LPCTSTR(lpData));
        
		break;    
	
	case BFFM_SELCHANGED:
         SHGetPathFromIDList(LPITEMIDLIST(lParam), szPath);
         
		 if (hEdit)
            SetWindowText(hEdit, szPath);
      break;
	
	case BFFM_VALIDATEFAILED:
		GetWindowText(hEdit, szPath, MAX_PATH);

		strcpy(GamePath, szPath);

		break;
	} 
    
	return 0;
}


//C:\Documents and Settings\All Users\Start Menu\Programs