#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <process.h>

#include "installer.h"
#include "resource.h"
#include "unzipper.h"

extern char GamePath[MAX_PATH];
extern HWND hWnd;
extern BOOL IsInstalled;

void unzip(void *GamePath)
{
	CUnzipper zip;
	UZ_FileInfo info;
	char file_path[MAX_PATH];
	int num_files, i;
	FILE *fp;

	strcpy(file_path, (char *)GamePath);
	strcat(file_path, "\\Uninstall.cfg");

	fp = fopen(file_path, "w");

	if (fp != NULL)
	{
		zip.OpenZip("IA.ehf");
		//zip.SetOutputFolder((char *)GamePath);
		CreateFolder((char *)GamePath);

		num_files = zip.GetFileCount();

		for (i=0; i<num_files; i++)
		{
			zip.GetFileInfo(i, info); 
			zip.UnzipFile(i, (char *)GamePath, TRUE);

			fprintf(fp, "%s\\%s\n", GamePath, info.szFileName);
		}
	
		zip.CloseZip();

		fcloseall();
	}
	else
	{
		KillTimer(hWnd, 1);
		
		MessageBox(hWnd, "Error installing!  Code 2", "Error", MB_ICONEXCLAMATION|MB_OK);

		SetDlgItemText(hWnd, IDC_STATUS, "Error");

		return;
	}

	KillTimer(hWnd, 1);
	SetDlgItemText(hWnd, IDC_STATUS, "Done");

	SetDlgItemText(hWnd, IDC_CONTINUE, "Finish");
	EnableWindow(GetDlgItem(hWnd, IDC_CANCEL), FALSE);
	IsInstalled = TRUE;

	MessageBox(hWnd, "Imperial Alliance Installed!", "Success", MB_OK);

	return;
}

bool CreateFolder(LPCTSTR szFolder)
{
	if (!szFolder || !lstrlen(szFolder))
		return FALSE;

	DWORD dwAttrib = GetFileAttributes(szFolder);

	// already exists ?
	if (dwAttrib != 0xffffffff)
		return ((dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

	// recursively create from the top down
	char* szPath = _strdup(szFolder);
	char* p = strrchr(szPath, '\\');

	if (p) 
	{
		// The parent is a dir, not a drive
		*p = '\0';
			
		// if can't create parent
		if (!CreateFolder(szPath))
		{
			free(szPath);
			return FALSE;
		}
		free(szPath);

		if (!::CreateDirectory(szFolder, NULL)) 
			return FALSE;
	}
	
	return TRUE;
}

void copy_setup(char *GamePath)
{
	char source[MAX_PATH];
	char dest[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, source);
	strcat(source, "\\Setup.exe");

	strcpy(dest, GamePath);
	strcat(dest, "\\Setup.exe");

	CopyFile(source, dest, FALSE);
}

int uninstall(void)
{
	char uninstall_path[MAX_PATH];
	char error_message[100];
	char path[MAX_PATH];
	char temp[MAX_PATH];
	int length, i;
	FILE *fp;

	GetCurrentDirectory(MAX_PATH, uninstall_path);
	strcat(uninstall_path, "\\Uninstall.cfg");

	fp = fopen(uninstall_path, "r");
	
	if (fp != NULL)
	{
		while(!feof(fp))
		{
			fgets(path, MAX_PATH, fp);

			length = strlen(path);

			memset(temp, 0, MAX_PATH);
			for (i=0; i<length-1; i++)
				temp[i] = path[i];
									
			if (DeleteFile(temp) == FALSE)
			{
				//memset(error_message, 0, 100);
				//sprintf(error_message, "Error removing %s", temp);
				//MessageBox(NULL, error_message, "Error", MB_ICONEXCLAMATION|MB_OK);
			}
			
		}

		fcloseall();

		DeleteFile(uninstall_path);

		return 1;
	}
	else
	{
		MessageBox(hWnd, "Error uninstalling!  Code 3", "Error", MB_ICONEXCLAMATION|MB_OK);

		return 0;
	}

	return 0;
}