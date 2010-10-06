// zoom_map.cpp: implementation of the zoom_map class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zoom_map.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// zoom_map dialog

zoom_map::zoom_map(CWnd* pParent /*=NULL*/)
	: CDialog(zoom_map::IDD, pParent)
{
	//{{AFX_DATA_INIT(zoom_map)
	//m_factor = _T("0");
	//}}AFX_DATA_INIT
}

void zoom_map::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(zoom_map)
	DDX_Control(pDX, IDC_ZOOM_TEXT, m_factor);
	DDX_Control(pDX, IDC_ZOOM_SLIDER, m_slider);
		//}}AFX_DATA_MAP

//	DDV_MaxChars(pDX, m_name, NAME_LENGTH - 4);
}

BEGIN_MESSAGE_MAP(zoom_map, CDialog)
	//{{AFX_MSG_MAP(zoom_map)
		// NOTE: the ClassWizard will add message map macros here
		ON_COMMAND(IDC_RESET_VIEW, OnResetView)
		ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern void zoom(float);
extern void reset_view();
float factor;

BOOL zoom_map::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	factor = 5;

	m_slider.SetRange(0,40);

	m_slider.SetPos(int(factor));
	m_factor.SetWindowText("100");

	return TRUE;
}

void zoom_map::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	char ch[10];
	float curpos = -1;

	//switch(pScrollBar->GetDlgCtrlID()) 
	//{
	//case IDC_ZOOM_SLIDER:
	
	curpos = m_slider.GetPos();
	
	wsprintf(ch, "%d", curpos);
	m_factor.SetWindowText(ch);

	curpos *= 100;

	zoom(curpos);

	//break;
	//}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	
}

void zoom_map::OnResetView()
{
	reset_view();
}



