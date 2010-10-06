#if !defined(AFX_TABSOUND_H__9A8D1027_1D16_4973_B367_823DEA924303__INCLUDED_)
#define AFX_TABSOUND_H__9A8D1027_1D16_4973_B367_823DEA924303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSound.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSound dialog

class CTabSound : public CDialog
{
// Construction
public:
	void LoadSettings(char *reg_path);
	void OnApply(char *reg_file, char *settings_file);
	bool SearchFolder(char *Folder);
	bool FindMusicFiles(char *Folder);
	CTabSound(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabSound)
	enum { IDD = IDD_SOUND };
	CComboBox	m_sound_api_list;
	CComboBox   m_cdrom_drive_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSound)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabSound)
	virtual BOOL OnInitDialog();
	afx_msg void OnCDClick();
	afx_msg void OnOggClick();
	afx_msg void OnRandomize();
	afx_msg void OnCreatePlaylist();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSOUND_H__9A8D1027_1D16_4973_B367_823DEA924303__INCLUDED_)
