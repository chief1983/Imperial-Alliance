/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/OperatorArgTypeSelect.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/07/15 03:11:00 $
 * $Author: inquisitor $
 *
 * Dialog box handling code for selecting an argument return type of an SEXP.
 * Changes to SEXPs made this no longer needed, but just in case more changes
 * cause it to be needed again, it's still around.
 *
 * $Log: OperatorArgTypeSelect.h,v $
 * Revision 1.1.1.1  2002/07/15 03:11:00  inquisitor
 * Initial FRED2 Checking
 *
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:01p Dave
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 3     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

/////////////////////////////////////////////////////////////////////////////
// OperatorArgTypeSelect dialog

class OperatorArgTypeSelect : public CDialog
{
// Construction
public:
	OperatorArgTypeSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OperatorArgTypeSelect)
	enum { IDD = IDD_OPERATOR_ARGUMENT_TYPES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OperatorArgTypeSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OperatorArgTypeSelect)
	afx_msg void OnBoolean();
	afx_msg void OnNumbers();
	afx_msg void OnShips();
	afx_msg void OnWings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
