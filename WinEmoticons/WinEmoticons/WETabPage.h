#include "WEPaintUint.h"
#include "WETabItem.h"
#pragma once

class CWETabPage : public CWEPaintUint
{
	DECLARE_DYNCREATE(CWETabPage)
public:
	CWETabPage(CRect rcThis = CRect(),CWEPaintUint *pParent = NULL);
	~CWETabPage(void);

	// Attributes:
public:
	int		nIndex;						// index of tab
	CString	strCaption;					// caption text
	BOOL	bIsActive;					// is this page actived
	int		*pnHeaderHeight;			// tab header height
	int		*pnPageCount;				// tab pages count
	int		*pnHeaderHorzMargin;		// page header margin on horizontal
	int		*pnHeaderTopMargin;			// page header margin on top
	int		*pnHeaderActiveHorzMargin;	// active page header margin on horizontal
	int		*pnHeaderActiveTopMargin;	// active page header margin on top
	int		*pnPagePadding;				// padding of page
	int		*pnColumnCount;				// count of column
	int		*pnRowCount;				// count of row
	int		*pnItemPadding;				// padding of items
private:
	int		m_nItemCount;				// item count

	// Methods:
public:
	// draw page
	void Draw(CDC *pDC);
	// hit test
	CWEPaintUint *HitTest(CPoint ptHit,MouseEvent meMouse = NOTHING);
	// move to new rect
	void MoveRect(CRect rcNew);
	// apend item
	CWETabItem *AppendItem(CString strContent);

	void GetItemRect( int nIndex,CRect &rcItem );

private:
	// get rect of page header
	void GetBodyRect( CRect &rcPage );
	// get rect of page body
	void GetHeaderRect( CRect &rcHeader );
};
