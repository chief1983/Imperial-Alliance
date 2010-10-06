// brief_map_tag.cpp: implementation of the brief_map_tag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "brief_tag.h"
#include "mission/missionbriefcommon.h"
#include "mission/missionparse.h"
#include "resource.h"

extern int g_curr_stage;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

brief_map_tag::brief_map_tag(CWnd* pParent /*=NULL*/)
	: CDialog(brief_map_tag::IDD, pParent)
{
	//{{AFX_DATA_INIT(brief_map_tag)
	m_x_pos = 0;
	m_y_pos = 0;
	m_tag_text = _T("");
	//}}AFX_DATA_INIT
}

void brief_map_tag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(brief_map_tag)
	DDX_Text(pDX, IDC_TAG_TEXT, m_tag_text);
	DDX_Text(pDX, IDC_X_POS, m_x_pos);
	DDX_Text(pDX, IDC_Y_POS, m_y_pos);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(brief_map_tag, CDialog)
	//{{AFX_MSG_MAP(brief_map_tag)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(IDC_CREATE_TAG, OnCreateTag)
		ON_BN_CLICKED(IDC_UPDATE_TAG, OnUpdateTag)
		ON_BN_CLICKED(IDC_DELETE_TAG, OnDeleteTag)
		ON_BN_CLICKED(IDC_NEXT, OnNextTag)
		ON_BN_CLICKED(IDC_PREV, OnPrevTag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL brief_map_tag::OnInitDialog() 
{
	brief_stage *ptr = NULL;
	char c[10];
	
	CDialog::OnInitDialog();

	Briefing = &Briefings[g_curr_stage];



	/*if (Briefing->num_stages <= 0) {
		GetDlgItem(IDC_TAG_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_PREV)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CREATE_TAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_UPDATE_TAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELETE_TAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_X_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_Y_POS)->EnableWindow(FALSE);
	}*/

	ptr = &Briefing->stages[g_curr_stage];

	if (ptr->num_tags <= 0) {
	/*	GetDlgItem(IDC_TAG_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_PREV)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_UPDATE_TAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELETE_TAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_X_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_Y_POS)->EnableWindow(FALSE);*/

		SetDlgItemText(IDC_TAG_NUM, "0");
	}
	else {
		SetDlgItemText(IDC_TAG_TEXT, ptr->tag[0].text);

		sprintf(c, "%g", ptr->tag[0].pos.xyz.x);
		SetDlgItemText(IDC_X_POS, c);

		sprintf(c, "%g", ptr->tag[0].pos.xyz.z);
		SetDlgItemText(IDC_Y_POS, c);

		SetDlgItemText(IDC_TAG_NUM, "1");
	}

	return TRUE;
}

void brief_map_tag::OnCreateTag()
{
	Briefing = &Briefings[g_curr_stage];
	brief_stage *ptr = NULL;
	char c[10];

		//Briefing->stages[g_curr_stage].tag = (brief_tag *)malloc(sizeof(brief_tag)*MAX_TAG_LINES);
		//Briefing->stages[g_curr_stage].num_tags = 0;

	ptr = &Briefing->stages[g_curr_stage];

	if (ptr->num_tags >= 10) {
		MessageBox("Max number of 10 tags created.", "ImpED");
		return;
	}
		
	if (ptr == NULL) {
		// allocate space for max number of briefing tags on this stage
		// don't have to worry about unused ones since number per stage
		// is tracked in num_tags
		Briefing->stages[g_curr_stage].tag = (brief_tag *)malloc(sizeof(brief_tag)*MAX_TAG_LINES);
		Briefing->stages[g_curr_stage].num_tags = 0;
	MessageBox("a");

		goto enable;
	}
	else {
		ptr->num_tags += 1;
		//strcpy(ptr->tag[0].text, "test");
		//ptr->num_tags++;
		sprintf(c, "%d", ptr->num_tags);
		SetDlgItemText(IDC_TAG_NUM, c);

		SetDlgItemText(IDC_TAG_TEXT, "");
		SetDlgItemText(IDC_X_POS, "0");
		SetDlgItemText(IDC_Y_POS, "0");

		goto enable;
	}

// yay for labels!
enable:
	GetDlgItem(IDC_TAG_TEXT)->EnableWindow(TRUE);
	GetDlgItem(IDC_PREV)->EnableWindow(TRUE);
	GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE_TAG)->EnableWindow(TRUE);
	GetDlgItem(IDC_DELETE_TAG)->EnableWindow(TRUE);
	GetDlgItem(IDC_X_POS)->EnableWindow(TRUE);
	GetDlgItem(IDC_Y_POS)->EnableWindow(TRUE);
}

void brief_map_tag::OnUpdateTag()
{
	Briefing = &Briefings[g_curr_stage];
	brief_stage *ptr = NULL;
	char c[10];
	int tag_num;
	double x, y;
	
	ptr = &Briefing->stages[g_curr_stage];

	GetDlgItemText(IDC_TAG_NUM, c, 10);

	tag_num = atoi(c);

	// strcpy(ptr->tag[tag_num-1].text, 
	GetDlgItemText(IDC_TAG_TEXT, ptr->tag[tag_num-1].text, 255);
	
	GetDlgItemText(IDC_X_POS, c, 10);
	x = atof(c);
	ptr->tag[tag_num-1].pos.xyz.x = x;
	
	GetDlgItemText(IDC_Y_POS, c, 10);
	y = atof(c);
	ptr->tag[tag_num-1].pos.xyz.z = y;
}

void brief_map_tag::OnDeleteTag()
{
	Briefing = &Briefings[g_curr_stage];
	brief_stage *ptr = NULL;
	int curr_tag, max_tag;
	char c[10];

	ptr = &Briefing->stages[g_curr_stage];

	Briefing->stages[g_curr_stage].tag = (brief_tag *)malloc(sizeof(brief_tag)*MAX_TAG_LINES);
	Briefing->stages[g_curr_stage].num_tags = 0;


	/*GetDlgItemText(IDC_TAG_NUM, c, 10);

	curr_tag = atoi(c);
	curr_tag--;

	max_tag = ptr->num_tags;

	for (int i=curr_tag; i<=max_tag; i++) {
	//	if (i == max_tag) {
			strcpy(ptr->tag[i].text, ptr->tag[i+1].text);
			ptr->tag[i].pos.xyz.x = ptr->tag[i+1].pos.xyz.x;
			//ptr->tag[i].pos.xyz.y = 0;
			ptr->tag[i].pos.xyz.z = ptr->tag[i+1].pos.xyz.z;

		//	continue;
	//	}
	}

	
	SetDlgItemText(IDC_TAG_TEXT, ptr->tag[curr_tag].text);

	sprintf(c, "%g", ptr->tag[curr_tag].pos.xyz.x);
	SetDlgItemText(IDC_X_POS, c);

	sprintf(c, "%g", ptr->tag[curr_tag].pos.xyz.z);
	SetDlgItemText(IDC_Y_POS, c);*/
}

void brief_map_tag::OnNextTag()
{
	Briefing = &Briefings[g_curr_stage];
	brief_stage *ptr = NULL;
	int tag_num;
	char c[10];

	ptr = &Briefing->stages[g_curr_stage];

	GetDlgItemText(IDC_TAG_NUM, c, 10);

	tag_num = atoi(c);

	tag_num++;

	if (tag_num > ptr->num_tags) {
		SetDlgItemText(IDC_TAG_TEXT, ptr->tag[0].text);

		// x pos
		sprintf(c, "%g", ptr->tag[0].pos.xyz.x);
		SetDlgItemText(IDC_X_POS, c);

		// y pos
		sprintf(c, "%g", ptr->tag[0].pos.xyz.z);
		SetDlgItemText(IDC_Y_POS, c);

		// tag num
		sprintf(c, "1");
		SetDlgItemText(IDC_TAG_NUM, c);
	} else {
		SetDlgItemText(IDC_TAG_TEXT, ptr->tag[tag_num-1].text);
		
		// x pos
		sprintf(c, "%g", ptr->tag[tag_num-1].pos.xyz.x);
		SetDlgItemText(IDC_X_POS, c);

		// y pos
		sprintf(c, "%g", ptr->tag[tag_num-1].pos.xyz.z);
		SetDlgItemText(IDC_Y_POS, c);

		// tag num
		sprintf(c, "%d", tag_num);
		SetDlgItemText(IDC_TAG_NUM, c);
	}
}

void brief_map_tag::OnPrevTag()
{
	Briefing = &Briefings[g_curr_stage];
	brief_stage *ptr = NULL;
	int tag_num;
	char c[10];

	ptr = &Briefing->stages[g_curr_stage];

	GetDlgItemText(IDC_TAG_NUM, c, 10);
	
	tag_num = atoi(c);

	tag_num--;

	if (tag_num < 1) {
		SetDlgItemText(IDC_TAG_TEXT, ptr->tag[ptr->num_tags-1].text);
		
		// x pos
		sprintf(c, "%g", ptr->tag[ptr->num_tags-1].pos.xyz.x);
		SetDlgItemText(IDC_X_POS, c);

		// y pos
		sprintf(c, "%g", ptr->tag[ptr->num_tags-1].pos.xyz.z);
		SetDlgItemText(IDC_Y_POS, c);

		// tag num
		sprintf(c, "%d", ptr->num_tags);
		SetDlgItemText(IDC_TAG_NUM, c);
	} else {
		SetDlgItemText(IDC_TAG_TEXT, ptr->tag[tag_num-1].text);
		
		// x pos
		sprintf(c, "%g", ptr->tag[tag_num-1].pos.xyz.x);
		SetDlgItemText(IDC_X_POS, c);

		// y pos
		sprintf(c, "%g", ptr->tag[tag_num-1].pos.xyz.z);
		SetDlgItemText(IDC_Y_POS, c);

		// tag num
		sprintf(c, "%d", tag_num);
		SetDlgItemText(IDC_TAG_NUM, c);
	}
}