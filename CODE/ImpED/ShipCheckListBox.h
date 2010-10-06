/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/FRED2/ShipCheckListBox.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/07/15 03:11:02 $
 * $Author: inquisitor $
 *
 * A custom check list box class that allows space bar to toggle the state of all
 * the selected checkboxes.
 *
 * $Log: ShipCheckListBox.h,v $
 * Revision 1.1.1.1  2002/07/15 03:11:02  inquisitor
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
 * 5     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

#ifndef _SHIPCHECKLISTBOX_H
#define _SHIPCHECKLISTBOX_H

class ShipCheckListBox : public CCheckListBox
{
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	//{{AFX_MSG(CCheckListBox)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif