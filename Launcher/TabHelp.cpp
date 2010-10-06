// TabHelp.cpp : implementation file
//

#include "stdafx.h"
#include "launcher.h"
#include "TabHelp.h"
#include "Win32func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabHelp dialog


CTabHelp::CTabHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CTabHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabHelp, CDialog)
	//{{AFX_MSG_MAP(CTabHelp)
	ON_BN_CLICKED(IDC_GAME_README, OnReadme)
	ON_BN_CLICKED(IDC_GOTO_FORUM, OnGotoForum)
	ON_BN_CLICKED(IDC_REPORT_BUG, OnReportBug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabHelp message handlers

void CTabHelp::OnReadme() 
{
	OpenInternetPage("http://dynamic4.gamespy.com/~freespace/fsdoc/index.php/Launcher%20v4.x");
}

void CTabHelp::OnGotoForum() 
{
	OpenInternetPage("http://dynamic4.gamespy.com/~freespace/forums/");
}

void CTabHelp::OnReportBug() 
{
	OpenInternetPage("http://mgo.maxgaming.net/mantis/login_page.php");
}

void CTabHelp::OpenInternetPage(char *path)
{
	char buffer[MAX_PATH];
	sprintf(buffer,"explorer.exe \"%s\"", path);

	WinExec(buffer,SW_SHOW);
}
