// TabRegOptions.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "TabRegOptions.h"
#include "win32func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
	REG_TYPE_SZ,
	REG_TYPE_DWORD,
	REG_TYPE_UNSUPPORTED,
	MAX_REG_TYPES
};

char *string_reps[MAX_REG_TYPES] =
{
	"String", 
	"DWord", 
	"N\\A"
};
						   
/////////////////////////////////////////////////////////////////////////////
// CTabRegOptions dialog


CTabRegOptions::CTabRegOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CTabRegOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabRegOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabRegOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabRegOptions)
	DDX_Control(pDX, IDC_REG_LIST, m_reg_option_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabRegOptions, CDialog)
	//{{AFX_MSG_MAP(CTabRegOptions)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REG_LIST, OnItemchangedRegList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabRegOptions message handlers

/**
 *
 */
BOOL CTabRegOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_reg_option_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_reg_option_list.InsertColumn(0, "Name", LVCFMT_LEFT, 125);
	m_reg_option_list.InsertColumn(1, "Type", LVCFMT_LEFT, 60);
	m_reg_option_list.InsertColumn(2, "Data", LVCFMT_LEFT, 129);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/**
 *
 */
void CTabRegOptions::InsertItem(char *name, int type, void *data)
{
	// Insert name and get new value, may differ from requested index value
	int new_value = m_reg_option_list.InsertItem(m_list_count, name, 0);

	// Insert type
	LVITEM item;

	item.iItem    = new_value;
	item.iSubItem = 1;
	item.mask	  = LVIF_TEXT;
	item.pszText  = string_reps[type];

	if(m_reg_option_list.SetItem(&item) == FALSE)
	{
		MessageBox("Failed to set item");
		return;
	}

	item.iSubItem = 2;

	if(data)
	{
		switch(type)
		{
			case REG_TYPE_SZ:
				item.pszText = (char *) data;
				m_reg_option_list.SetItem(&item);
				break;
			case REG_TYPE_DWORD:
				char buffer[100];
				sprintf(buffer, "%d", *(DWORD *) data);
				item.pszText = buffer;
				m_reg_option_list.SetItem(&item);
				break;
			case REG_TYPE_UNSUPPORTED: break;
		}
	}

	m_reg_option_list.SetItemData(new_value, type);
}

/**
 *
 */
void CTabRegOptions::FillRegList(char *reg_path)
{
	int count = 0;
	LONG result;

	m_reg_option_list.DeleteAllItems();

	if(reg_path == NULL)
	{
		GetDlgItem(IDC_REG_LOCATION)->SetWindowText("No valid game exe chosen");
		return;
	}

	if(strlen(reg_path) == 0)
	{
		return;
	}

	HKEY hkey = reg_open_dir(reg_path);

	// Try to open the correct registry dir
	if(hkey == NULL)
	{
		return;
	}

	// Upon success keep the variables for later and display path for user
	strcpy(m_reg_path, reg_path);

	GetDlgItem(IDC_REG_LOCATION)->SetWindowText(reg_path);

	// Now find and display all the items at this path
	do
	{
		unsigned long subkey_size = MAX_PATH;
		char subkey_name[MAX_PATH];
		DWORD subkey_type;
		DWORD data_len = 100;
		BYTE pdata[100];

		result = RegEnumValue(
				  	hkey, 
					count, 
					subkey_name, 
					&subkey_size,
					0, // reserved
					&subkey_type,
					pdata,
					&data_len);

		if(result == ERROR_NO_MORE_ITEMS)
		{
			break;
		}

		if(result != ERROR_SUCCESS && result != ERROR_NO_MORE_ITEMS)
		{
			MessageBox("A error has occured reading from the registry, cancelling");
			break;
		}

		int reg_type = REG_TYPE_UNSUPPORTED;

		switch(subkey_type)
		{
			case REG_DWORD:	reg_type = REG_TYPE_DWORD; break;
			case REG_SZ:	reg_type = REG_TYPE_SZ; break;
		}

		InsertItem(subkey_name, reg_type, (void *) pdata);
		count++;

	} while(1);

	// Close this path now we have all the info we need
	RegCloseKey(hkey);

	// Nothing is selected so this should be blank
	GetDlgItem(IDC_NEW_VALUE)->SetWindowText("");
}

/**
 *
 */
void CTabRegOptions::OnSet() 
{
	// Check the paths are valid
	if(strlen(m_reg_path) == 0)
	{
		MessageBox("No reg path for this exe");
		FillRegList(NULL);
		return;
	}

	// Check a valid item is selected
	int selection = (int) m_reg_option_list.GetFirstSelectedItemPosition() - 1;

	if(selection == -1)
	{
		MessageBox("No entry chosen");
		return;
	}

	CString new_value, name = m_reg_option_list.GetItemText(selection, 0);

	// Get the new value
	GetDlgItem(IDC_NEW_VALUE)->GetWindowText(new_value); 

	const int data_type = m_reg_option_list.GetItemData(selection);
	bool result;

	switch(data_type)
	{
		case REG_TYPE_SZ:
		{
			result = reg_set_sz(m_reg_path, name, (LPCTSTR) new_value); 
			break;
		}
		case REG_TYPE_DWORD:
		{
			DWORD number = atoi( (LPCTSTR) new_value );
			result = reg_set_dword(m_reg_path, name, number);
			break;
		}
		default:
		case REG_TYPE_UNSUPPORTED:
			MessageBox("Viewing or changing this registry type is not supported");
			return;
	}

	if(result == false)
	{
		MessageBox("Failed to set reg value");
	}

	// Lets update the list the slow way and ensure everything is how it should be
	FillRegList(m_reg_path);
}

/**
 *
 */
void CTabRegOptions::OnItemchangedRegList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	// Get the name and type and data
	POSITION selection = m_reg_option_list.GetFirstSelectedItemPosition();
	CString data = m_reg_option_list.GetItemText((int) selection - 1, 2);

	GetDlgItem(IDC_NEW_VALUE)->SetWindowText(data);

	*pResult = 0;
}
