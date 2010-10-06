// zoom_map.h: interface for the zoom_map class.
//
//////////////////////////////////////////////////////////////////////

class zoom_map : public CDialog  
{
public:
// Construction
public:
	zoom_map(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(zoom_map)
	enum { IDD = 0 };
	CSliderCtrl m_slider;
	CStatic	m_factor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(zoom_map)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(zoom_map)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	afx_msg void OnResetView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

