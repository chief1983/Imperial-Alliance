class fg_editor : public CDialog  
{
public:
// Construction
public:
	fg_editor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(fg_editor)
	enum { IDD = 0 };
	CComboBox m_list1;
	CComboBox m_list2;
	CComboBox m_list3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(fg_editor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(fg_editor)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnChangeList1();
	afx_msg void OnChangeList2();
	afx_msg void OnChangeList3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

