#include "WEPaintUint.h"
#include "WETabPage.h"
#pragma once


// CWETabCtrl

class CWETabCtrl : public CWnd,public CWEPaintUint
{
	DECLARE_DYNAMIC(CWETabCtrl)

public:
	CWETabCtrl();

	virtual ~CWETabCtrl();

	// Attributes:
public:
	enum { MSG_HITITEM = WM_USER + 0x100};
private:
	// ctrl attributes
	int		m_nCtrlPadding;				// padding of this ctrl
	// page attributes
	int		m_nPageCount;				// pages count
	int		m_nHeaderHeight;			// page header height
	int		m_nHeaderHorzMargin;		// page header margin on horizontal
	int		m_nHeaderTopMargin;			// page header margin on top
	int		m_nHeaderActiveHorzMargin;	// active page header margin on horizontal
	int		m_nHeaderActiveTopMargin;	// active page header margin on top
	int		m_nPagePadding;				// padding of page
	CString	m_strFontName;				// font name
	int		m_nFontSize;				// point size * 10
	int		m_nColumnCount;				// count of column
	int		m_nRowCount;				// count of row
	int		m_nItemPadding;				// padding of items

	CList<COLORREF,COLORREF>	m_lstPageBackgrounds;	// background color queue
	
	CWETabPage	*m_pActivePage;			// page which is actived
	BOOL	m_bCaptured;				// is mouse captured


	//Methods:
public:
	void Create(CRect rcWindow,CWnd *pParent,UINT nId);
	void Draw(CDC *pDC);
	CWETabPage *AppendPage(CString strCaption = _T(""));
	void RemoveAllPages();
	void ActivePage( CWETabPage * pPage );
	void Redraw();
	void ReloadColor();
private:
	void GetPageRect( CRect &rcPage );

protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
