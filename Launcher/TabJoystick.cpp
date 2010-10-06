// TabJoystick.cpp : implementation file
//

#include "stdafx.h"
#include "launcher.h"
#include "TabJoystick.h"

#define DIRECTINPUT_VERSION 0x0500 

#include <Dinput.h> 
#include <mmsystem.h>

#include "win32func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabJoystick dialog

LPDIRECTINPUT dinput = NULL;
int joystick_index_value = 0;
GUID guid_array[64];

CTabJoystick::CTabJoystick(CWnd* pParent /*=NULL*/)
	: CDialog(CTabJoystick::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabJoystick)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if(FAILED(DirectInputCreate(GetModuleHandle(NULL), DIRECTINPUT_VERSION, &dinput,NULL)))
	{
		MessageBox("Failed to init dinput");
	}
}


void CTabJoystick::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSound)
	DDX_Control(pDX, IDC_JOYSTICK, m_joystick_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTabJoystick, CDialog)
	//{{AFX_MSG_MAP(CTabJoystick)
	ON_BN_CLICKED(IDC_CALIBRATE, OnCalibrate)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabJoystick message handlers

void CTabJoystick::OnApply(char *reg_path, char *settings_file)
{
	int index;
	
	// Joystick settings
	const int CHECKED = 1; 

	int ff = (((CButton *) GetDlgItem(IDC_FORCE_FREEDBACK))->GetCheck() == CHECKED) ? 1 : 0;
	int dh = (((CButton *) GetDlgItem(IDC_DIR_HIT))->GetCheck() == CHECKED) ? 1 : 0;
		
	reg_set_dword(reg_path, "EnableJoystickFF", ff);
	reg_set_dword(reg_path, "EnableHitEffect", dh);

	// Set joystick
	index = m_joystick_list.GetCurSel();
	if(index < 0) index = 0;
    int enum_id = m_joystick_list.GetItemData(index);
	
	reg_set_dword(reg_path, "CurrentJoystick", enum_id);
}

// Callback for each joystick
BOOL CALLBACK joy_di_enum(
  const struct DIDEVICEINSTANCEA *lpddi,  
  LPVOID m_joystick_list)               
{
	int index = ((CComboBox *) m_joystick_list)->AddString(lpddi->tszInstanceName);
	((CComboBox *) m_joystick_list)->SetItemData(index, joystick_index_value);

	guid_array[joystick_index_value] = lpddi->guidInstance; 

	joystick_index_value++;

	return TRUE;
}


BOOL CTabJoystick::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Joystick
	int index = m_joystick_list.AddString("No Joystick");
	m_joystick_list.SetItemData(index, 99999);

	joystick_index_value = 0;
	HRESULT hr = dinput->EnumDevices(DIDEVTYPE_JOYSTICK, &joy_di_enum, &m_joystick_list, DIEDFL_ATTACHEDONLY);

	if (FAILED(hr)) {
		MessageBox("Failed joystick enumeration", "Error", MB_OK);
	}

	JOYINFO jinfo;
	if(joyGetPos(JOYSTICKID1, &jinfo) == JOYERR_NOERROR)
	{
		index = m_joystick_list.AddString("Win32 Joystick 1");
		m_joystick_list.SetItemData(index, 0);
	}

	if(joyGetPos(JOYSTICKID2, &jinfo) == JOYERR_NOERROR)
	{
		index = m_joystick_list.AddString("Win32 Joystick 2");
		m_joystick_list.SetItemData(index, 1);
	}

	index = m_joystick_list.AddString("Force 0 (To reslove problems only)");
	m_joystick_list.SetItemData(index, 0);

	index = m_joystick_list.AddString("Force 1 (To reslove problems only)");
	m_joystick_list.SetItemData(index, 1);

	m_joystick_list.SetCurSel(0);

	return TRUE;  
}

void CTabJoystick::LoadSettings(char *reg_path) 
{
	DWORD ff, dh;
	reg_get_dword(reg_path, "EnableJoystickFF", &ff);
	reg_get_dword(reg_path, "EnableHitEffect", &dh);

	((CButton *) GetDlgItem(IDC_FORCE_FREEDBACK))->SetCheck(ff ? 1 : 0);
	((CButton *) GetDlgItem(IDC_DIR_HIT))->SetCheck(dh ? 1 : 0);

	
	// Get joystick
	DWORD enum_id = 0;
	reg_get_dword(reg_path, "CurrentJoystick", &enum_id);
	int num_joy = m_joystick_list.GetCount();
	//num_joy++;
	
	for(int i = 0; i < num_joy; i++)
	{
		if(m_joystick_list.GetItemData(i) == enum_id)
		{
			// add 1 to the controller id since the list starts with
			// "no joystick" and this item 0 in the list.  this is a
			// problem because the first controller is enumerated as 0
			// so we add 1 to the entry from the registry to match up
			// with the actual joystick
			m_joystick_list.SetCurSel(enum_id+1);
			break;
		}
	}
}

void CTabJoystick::OnCalibrate() 
{
	int index = m_joystick_list.GetCurSel();

	if(index < 0) return;

    int enum_id = m_joystick_list.GetItemData(index);

	if(enum_id == 99999)
	{
		MessageBox("No Joystick is setup","Error");
		return;
	}

	LPDIRECTINPUTDEVICE device;
	if(FAILED(dinput->CreateDevice(guid_array[enum_id], &device, NULL))	)
	{
		MessageBox("Failed to get joystick device, calibrate joystick in 'Game Controllers'","Error");
		dinput->RunControlPanel(this->GetSafeHwnd(), 0);
		return;
	}

	if(device)
	{
		device->RunControlPanel(this->GetSafeHwnd(), 0);
		device->Release();
	}
}

void CTabJoystick::OnDestroy() 
{
	if(dinput)
		dinput->Release();

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}