// brief_map_tag.h: interface for the brief_map_tag class.
//
//////////////////////////////////////////////////////////////////////
#include "resource.h"


class brief_map_tag : public CDialog
{
public:

public:
	brief_map_tag(CWnd* pParent = NULL);

	// Dialog Data
	//{{AFX_DATA(zoom_map)
	enum { IDD = IDD_BRIEF_TAG };
	int m_x_pos;
	int m_y_pos;
	CString m_tag_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(brief_map_tag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(brief_map_tag)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateTag();
	afx_msg void OnUpdateTag();
	afx_msg void OnDeleteTag();
	afx_msg void OnNextTag();
	afx_msg void OnPrevTag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

