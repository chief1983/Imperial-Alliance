// OGLDisp.cpp : implementation file
//

#include "stdafx.h"
#include "launcher.h"
#include "OGLDisp.h"

#include "win32func.h"

typedef struct
{
	int xres;
	int yres;
	int cdepth;

} ModeOGL;

const int NUM_OGL_MODES = 24;

ModeOGL ogl_modes[NUM_OGL_MODES] =
{
	1600, 1200, 32,
	1600, 1024, 32,
	1600,  900, 32,
	1360,  768, 32,
	1280, 1024, 32,
	1280,  960, 32,
	1280,  768, 32,
	1280,  720, 32,
	1152,  864, 32,
	1024,  768, 32,
	 800,  600, 32,
	 640,  480, 32,

	1600, 1200, 16,
	1600, 1024, 16,
	1600,  900, 16,
	1360,  768, 16,
	1280, 1024, 16,
	1280,  960, 16,
	1280,  768, 16,
	1280,  720, 16,
	1152,  864, 16,
	1024,  768, 16,
	 800,  600, 16,
	 640,  480, 16,

};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COGLDisp dialog


COGLDisp::COGLDisp(CWnd* pParent /*=NULL*/)
	: CDialog(COGLDisp::IDD, pParent)
{
	//{{AFX_DATA_INIT(COGLDisp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_allow_only_standard_modes = true;
}


void COGLDisp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COGLDisp)
	DDX_Control(pDX, IDC_ALLOW_NON_SMODES, m_show_all_modes_checkbox);
	DDX_Control(pDX, IDC_OGL_RES, m_res_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COGLDisp, CDialog)
	//{{AFX_MSG_MAP(COGLDisp)
	ON_BN_CLICKED(IDC_ALLOW_NON_SMODES, OnAllowNonSmodes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGLDisp message handlers

BOOL COGLDisp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/**
 * The user has chosen to accept these settings
 *
 * @param char *reg_path - Registry path that any settings should be saved to
 */
void COGLDisp::OnApply(char *reg_path)
{
	int index = m_res_list.GetCurSel();

	if( index == CB_ERR)
	{
		MessageBox("Failed to set graphic mode");
		return;
	}

	int current = m_res_list.GetItemData(index);

	char videocard[100];
	sprintf(videocard, "OGL-(%dx%d)x%d bit",
		ogl_modes[current].xres,
		ogl_modes[current].yres,
		ogl_modes[current].cdepth);

	if(reg_set_sz(reg_path, "Videocard", videocard) == false)
	{
		MessageBox("Failed to set graphic mode");
	}

}

void COGLDisp::UpdateResList(unsigned int requested_width, unsigned int requested_height, int requested_cdepth)
{
	int selected_sel = 0;
	int count = 0;
 	m_res_list.ResetContent();

	for(int i = 0; i < NUM_OGL_MODES; i++)
	{
		bool non_standard_match = (ogl_modes[i].xres == requested_width && 
								   ogl_modes[i].yres == requested_height &&
								   ogl_modes[i].cdepth == requested_cdepth);


		// ignore invalid modes unless we have an exact match (user picked non standard mode last time)
		if(m_allow_only_standard_modes && !non_standard_match)
		{
			// Just the standard modes
			if(	!(ogl_modes[i].xres == 1024 && ogl_modes[i].yres == 768) &&
				!(ogl_modes[i].xres == 640 && ogl_modes[i].yres == 480))
			{
				continue;
			}
		}
		else
		{
			// Anything above the minimum
			if(	!(ogl_modes[i].xres == 640 && ogl_modes[i].yres == 480) &&
				(ogl_modes[i].xres < 800 || ogl_modes[i].yres < 600))
			{
		  		continue;
			}
		}

		char mode_string[20];
		sprintf(mode_string, "%d x %d x %d", ogl_modes[i].xres, ogl_modes[i].yres, ogl_modes[i].cdepth);

		// Store the index
		int index = m_res_list.InsertString(count, mode_string);
		m_res_list.SetItemData(index, i);

		if( requested_width  == ogl_modes[i].xres &&
			requested_height == ogl_modes[i].yres &&
			requested_cdepth == ogl_modes[i].cdepth)

		{
	   		selected_sel = count;
		} 

		count++;
	}

	if(selected_sel < 0) selected_sel = 0;

	m_res_list.SetCurSel(selected_sel);
}

void COGLDisp::LoadSettings(char *reg_path)
{
	unsigned int width, height;
	int cdepth;
	char videocard_string[MAX_PATH];

	// Lets get those video card settings
	if(reg_get_sz(reg_path, "Videocard", videocard_string, MAX_PATH) == false)
		return;

	if(sscanf(videocard_string, "OGL-(%dx%d)x%d bit", &width, &height, &cdepth)  != 3) 
		return;

	UpdateResList(width, height, cdepth);
}

void COGLDisp::OnAllowNonSmodes() 
{
   	m_allow_only_standard_modes = !m_show_all_modes_checkbox.GetCheck();

   	UpdateResList();

	if(!m_allow_only_standard_modes)
	{
		MessageBox("IA OGL will run under non standard modes but it is not fully supported so expect bugs."
			" Also your monitor may not support all the resolutions you are offered","Warning",MB_ICONWARNING);
	}
}
