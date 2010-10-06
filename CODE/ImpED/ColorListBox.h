class CColorListBox : public CListBox
{
public:
	virtual void AddItem(const CString& str, COLORREF rgbText);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	
	
};