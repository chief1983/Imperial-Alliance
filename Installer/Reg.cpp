#include <windows.h>
#include <shlwapi.h>

#include "installer.h"

void make_registry_entries(char *GamePath)
{
	HKEY pHKey;
	DWORD size = MAX_PATH;
	char temp[MAX_PATH];

	strcpy(temp, GamePath);
	strcat(temp, "\\ia.cnt");
	
	// associate icon with *.iam files
	RegCreateKeyEx(HKEY_CLASSES_ROOT,
					".iam\\DefaultIcon",
					0,
					NULL,
					REG_OPTION_VOLATILE,
					KEY_SET_VALUE,
					NULL,
					&pHKey,
					NULL);

	 RegSetValueEx(pHKey,
					NULL,
					0,
					REG_SZ,
					(BYTE *)temp, 
					size);

	 RegCloseKey(pHKey);

	 memset(temp, 0, MAX_PATH);
	 strcpy(temp, GamePath);
	 strcat(temp, "\\ImpEd.exe \"%1\"");

		 // have ImpEd open up *.iam files
	 RegCreateKeyEx(HKEY_CLASSES_ROOT,
					".iam\\Shell\\Open\\Command",
					0,
					NULL,
					REG_OPTION_VOLATILE,
					KEY_SET_VALUE,
					NULL,
					&pHKey,
					NULL);

	 RegSetValueEx(pHKey,
					NULL,
					0,
					REG_SZ,
					(BYTE *)temp, 
					size);

	RegCloseKey(pHKey);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Imperial Alliance",
					0,
					NULL,
					REG_OPTION_VOLATILE,
					KEY_SET_VALUE,
					NULL,
					&pHKey,
					NULL);

	strcpy(temp, "Imperial Alliance");
	
	RegSetValueEx(pHKey,
					"DisplayName",
					0,
					REG_SZ,
					(BYTE *)temp, 
					size);

	strcpy(temp, GamePath);
	strcat(temp, "\\Setup.exe");
	
	RegSetValueEx(pHKey,
					"UninstallString",
					0,
					REG_SZ,
					(BYTE *)temp, 
					size);
	
	RegCloseKey(pHKey);
	
}

void delete_registry_entries(char *GamePath)
{
	HKEY pHKey;
	DWORD size = MAX_PATH;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		         "SOFTWARE",
				 0,
				 KEY_ALL_ACCESS,
				 &pHKey);

	SHDeleteKey(pHKey,
		         "EH Works");

	RegCloseKey(pHKey);

    RegOpenKeyEx(HKEY_CLASSES_ROOT,
		         NULL,
				 0,
				 KEY_ALL_ACCESS,
				 &pHKey);
	
	SHDeleteKey(pHKey, ".iam");
		
	RegCloseKey(pHKey);
}
//HKEY_CURRENT_USER\Software\Microsoft\Windows\Current Version\Explorer\Shell Folders\programs 

// 2000/xp
// "folder" - current user desktop
// "desktop - all users desktop
// "CurrentVersion" - start bar programs

// 98
// "desktop" - all users desktop
// "programs" - start bar programs