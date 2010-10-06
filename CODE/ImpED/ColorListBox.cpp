#include "stdafx.h"
#include "ColorListBox.h"

void CColorListBox::AddItem(const CString& str, COLORREF rgbText)
{
   int   nIndex;
   
   nIndex = AddString(str);
   
   if( CB_ERR != nIndex )
      SetItemData(nIndex, rgbText);
}


void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
   CDC      dc;
   CRect      rcItem(lpDIS->rcItem);
   UINT      nIndex = lpDIS->itemID;
   COLORREF   rgbBkgnd = RGB(0,0,0);//::GetSysColor(
         //(lpDIS->itemState & ODS_SELECTED) ?
            //   COLOR_HIGHLIGHT : COLOR_WINDOW);
   
   dc.Attach(lpDIS->hDC);
   CBrush br(rgbBkgnd);
   dc.FillRect(rcItem, &br);
   
   if( lpDIS->itemState & ODS_FOCUS )
      dc.DrawFocusRect(rcItem);
   
   if( nIndex != (UINT)-1 )
   {
      // The text color is stored as the item data.
      COLORREF   rgbText = (lpDIS->itemState & ODS_SELECTED) ?
            ::GetSysColor(COLOR_HIGHLIGHTTEXT) : GetItemData(nIndex);
      CString str;
      GetText(nIndex, str);
      
	  dc.SetBkColor(rgbBkgnd);
      dc.SetTextColor(rgbText);
      dc.TextOut(rcItem.left + 2, rcItem.top + 2, str);
   }
   
   dc.Detach();

}

void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
   // Set the item height. Get the DC, select the font for the
   // list box, and compute the average height.
   CClientDC   dc(this);
   TEXTMETRIC   tm;
   
   CFont* pFont = GetFont();
   CFont* pOldFont = dc.SelectObject(pFont);
   
   dc.GetTextMetrics(&tm);
   dc.SelectObject(pOldFont);
   
   lpMIS->itemHeight = tm.tmHeight + 4;   
}


