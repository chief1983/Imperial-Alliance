#include "stdafx.h"
#include "flightgroupeditor.h"
#include "wing.h"
#include "resource.h"
 
char flight_group1[25] = "None";
char flight_group2[25] = "None";
char flight_group3[25] = "None";

int flight_groups_changed = 0;
     
/////////////////////////////////////////////////////////////////////////////
// fg_editor dialog

fg_editor::fg_editor(CWnd* pParent /*=NULL*/)
	: CDialog(fg_editor::IDD, pParent)
{
	//{{AFX_DATA_INIT(fg_editor)
	//}}AFX_DATA_INIT
}

void fg_editor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(fg_editor)
	DDX_Control(pDX, IDC_GROUP_1, m_list1);
	DDX_Control(pDX, IDC_GROUP_2, m_list2);
	DDX_Control(pDX, IDC_GROUP_3, m_list3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(fg_editor, CDialog)
	//{{AFX_MSG_MAP(fg_editor)
		// NOTE: the ClassWizard will add message map macros here
		ON_COMMAND(IDC_OK, OnOk)
		ON_CBN_SELCHANGE(IDC_GROUP_1, OnChangeList1)
		ON_CBN_SELCHANGE(IDC_GROUP_2, OnChangeList2)
		ON_CBN_SELCHANGE(IDC_GROUP_3, OnChangeList3)
		//ON_COMMAND(IDC_RESET_VIEW, OnResetView)
		//ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL fg_editor::OnInitDialog() 
{
	int i;
	
	CDialog::OnInitDialog();
	 	
	m_list1.AddString("None");
	m_list2.AddString("None");
	m_list3.AddString("None");

	// load in all the available wings
	for (int x=0; x<=MAX_WINGS; x++)
	{
		if (strcmp(Wings[x].name, "") != 0)
		{
			m_list1.AddString(Wings[x].name);
			m_list2.AddString(Wings[x].name);
			m_list3.AddString(Wings[x].name);
		}
	}
		
	// if a flight group hasn't been selected make sure 'none' is 
	// highlighted
	if (flight_groups_changed == 0)
	{
		m_list1.SetCurSel(0);
		m_list2.SetCurSel(0);
		m_list3.SetCurSel(0);
	}
	// highlight the correct flight group
	else
	{
		i = m_list1.FindStringExact(-1, flight_group1);
		m_list1.SetCurSel(i);

		i = m_list2.FindStringExact(-1, flight_group2);
		m_list2.SetCurSel(i);

		// if an actual group name is loaded enable the window otherwise
		// don't
		if (i > 0)
			GetDlgItem(IDC_GROUP_2)->EnableWindow(TRUE);

		i = m_list3.FindStringExact(-1, flight_group3);
		m_list3.SetCurSel(i);

		// if an actual group name is loaded enable the window otherwise
		// don't
		if (i > 0)
			GetDlgItem(IDC_GROUP_3)->EnableWindow(TRUE);
	}
		
	return TRUE;
}

void fg_editor::OnOk()
{
	int i;

	i = m_list1.GetCurSel();
	m_list1.GetLBText(i, flight_group1);

	i = m_list2.GetCurSel();
	m_list2.GetLBText(i, flight_group2);

	i = m_list3.GetCurSel();
	m_list3.GetLBText(i, flight_group3);

	flight_groups_changed = 1;
	
	CDialog::EndDialog(0);
}

void fg_editor::OnChangeList1()
{
	int i;
	char temp[25];
	char other[25];

	i = m_list1.GetCurSel();
	m_list1.GetLBText(i, temp);

	// check to see if same name is in another box
	i = m_list2.GetCurSel();
	m_list2.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");

			m_list2.SetCurSel(0);

			return;
		}
	}

	i = m_list3.GetCurSel();
	m_list3.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");

			m_list3.SetCurSel(0);

			return;
		}
	}
	

	if (strcmp(temp, "None") != 0)
		GetDlgItem(IDC_GROUP_2)->EnableWindow(TRUE);
		
}

void fg_editor::OnChangeList2()
{
	int i;
	char temp[25];
	char other[25];

	i = m_list2.GetCurSel();
	m_list2.GetLBText(i, temp);

	// check to see if same name is in another box
	i = m_list1.GetCurSel();
	m_list1.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");
	
			m_list2.SetCurSel(0);

			return;
		}
	}

	i = m_list3.GetCurSel();
	m_list3.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");

			m_list3.SetCurSel(0);

			return;
		}
	}

	if (strcmp(temp, "None") != 0)
		GetDlgItem(IDC_GROUP_3)->EnableWindow(TRUE);
		
}

void fg_editor::OnChangeList3()
{
	int i;
	char temp[25];
	char other[25];
	
	i = m_list3.GetCurSel();
	m_list1.GetLBText(i, temp);
	
	// check to see if same name is in another box
	i = m_list2.GetCurSel();
	m_list2.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");

			m_list3.SetCurSel(0);

			return;
		}
	}

	i = m_list1.GetCurSel();
	m_list1.GetLBText(i, other);

	if (strcmp(other, "None") != 0)
	{
		if (strcmp(temp, other) == 0)
		{
			MessageBox("Can't have the same group in two lists");
			
			m_list3.SetCurSel(0);

			return;
		}
	}
}