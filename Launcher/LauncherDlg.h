// LauncherDlg.h : header file
//

#if !defined(AFX_LAUNCHERDLG_H__5B7FC6D5_4D7B_4D82_BCA0_D2D5143B9160__INCLUDED_)
#define AFX_LAUNCHERDLG_H__5B7FC6D5_4D7B_4D82_BCA0_D2D5143B9160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLauncherDlg dialog

class CLauncherDlg : public CDialog
{
// Construction
public:
	void NewExeSet(char *exe_path);
	void SelectTab(int selected_tab = 0);
	CLauncherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLauncherDlg)
	enum { IDD = IDD_LAUNCHER_DIALOG };
	CTabCtrl	m_tabctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLauncherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int currently_selected_tab;
	BOOL InitTabControl();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLauncherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
	afx_msg void OnSelchangeHolder(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRun();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char m_exe_path[MAX_PATH];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAUNCHERDLG_H__5B7FC6D5_4D7B_4D82_BCA0_D2D5143B9160__INCLUDED_)
