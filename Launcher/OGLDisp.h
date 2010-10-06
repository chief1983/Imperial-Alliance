#if !defined(AFX_OGLDISP_H__C726A944_1EB3_437C_9A27_DC1125A823A4__INCLUDED_)
#define AFX_OGLDISP_H__C726A944_1EB3_437C_9A27_DC1125A823A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OGLDisp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COGLDisp dialog

class COGLDisp : public CDialog
{
// Construction
public:
	void LoadSettings(char *reg_path);
	void UpdateResList(
		unsigned int requested_wdith = -1, 
		unsigned int requested_height = -1, 
		int requested_cdepth = -1);
	COGLDisp(CWnd* pParent = NULL);   // standard constructor
	void OnApply(char *reg_path);

// Dialog Data
	//{{AFX_DATA(COGLDisp)
	enum { IDD = IDD_OGL };
	CButton	m_show_all_modes_checkbox;
	CComboBox	m_res_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGLDisp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COGLDisp)
	virtual BOOL OnInitDialog();
	afx_msg void OnAllowNonSmodes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_allow_only_standard_modes;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLDISP_H__C726A944_1EB3_437C_9A27_DC1125A823A4__INCLUDED_)
