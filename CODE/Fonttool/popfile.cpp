#include <windows.h>
#include <commdlg.h>

#include "popfile.h"

static OPENFILENAME ofn;

void PopFileInitialize(HWND hwnd, PTSTR Filter)
{
	//static TCHAR szFilter[] = "IA Fonts (*.if)\0*.if\0";

	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= hwnd;
	ofn.hInstance			= NULL;
	ofn.lpstrFilter			= Filter;
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 0;
	ofn.lpstrFile			= NULL;
	ofn.nMaxFile			= MAX_PATH;
	ofn.lpstrFileTitle		= NULL;
	ofn.nMaxFileTitle		= MAX_PATH;
	ofn.lpstrInitialDir		= NULL;
	ofn.lpstrTitle			= NULL;
	ofn.Flags				= 0;
	ofn.nFileOffset			= 0;
	ofn.nFileExtension		= 0;
	ofn.lpstrDefExt			= "if";
	ofn.lCustData			= 0L;
	ofn.lpfnHook			= NULL;
	ofn.lpTemplateName		= NULL;
}

BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR InitialDir, PTSTR Title)
{
	ofn.hwndOwner			= hwnd;
	ofn.lpstrFile			= pstrFileName;
	ofn.lpstrInitialDir		= InitialDir;
	//ofn.lpstrFileTitle		= pstrFileTitle;
	ofn.lpstrTitle			= Title;
	ofn.Flags				= OFN_HIDEREADONLY|OFN_FILEMUSTEXIST;

	return GetOpenFileName(&ofn);

}

