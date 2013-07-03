// WETabCtrl.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WETabCtrl.h"
#include "ConfigManager.h"


// CWETabCtrl 

IMPLEMENT_DYNAMIC(CWETabCtrl, CWnd)

CWETabCtrl::CWETabCtrl()
: CWEPaintUint()
{
// 	m_nCtrlPadding = 5;
// 	m_nPageCount = 0;
// 	m_nHeaderHeight = 40;	
// 	m_nHeaderHorzMargin = 5;
// 	m_nHeaderTopMargin = 5;
// 	m_nHeaderActiveHorzMargin = 5;
// 	m_nHeaderActiveTopMargin = 0;
// 	m_nPagePadding = 2;
// 	m_nItemPadding = 5;
// 	m_nFontSize = 100;
// 	m_strFontName = _T("微软雅黑");
// 	m_nColumnCount = 3;
// 	m_nRowCount = 5;
// 
// 	m_lstPageBackgrounds.AddTail(RGB(44,143,197));
// 	m_lstPageBackgrounds.AddTail(RGB(216,80,83));
// 	m_lstPageBackgrounds.AddTail(RGB(253,105,43));
// 	m_lstPageBackgrounds.AddTail(RGB(152,248,192));
// 	m_lstPageBackgrounds.AddTail(RGB(223,141,235));

    m_nCtrlPadding = CConfigManager::Inst()->PopWindow.CtrlPadding;
    m_nHeaderHeight = CConfigManager::Inst()->PopWindow.PageHeader.HeaderHeight;	
    m_nHeaderHorzMargin = CConfigManager::Inst()->PopWindow.PageHeader.HeaderHorzMargin;
    m_nHeaderTopMargin = CConfigManager::Inst()->PopWindow.PageHeader.HeaderTopMargin;
    m_nHeaderActiveHorzMargin = CConfigManager::Inst()->PopWindow.PageHeader.HeaderActiveHorzMargin;
    m_nHeaderActiveTopMargin = CConfigManager::Inst()->PopWindow.PageHeader.HeaderActiveTopMargin;
    m_nPagePadding = CConfigManager::Inst()->PopWindow.PageHeader.PagePadding;
    m_nItemPadding = CConfigManager::Inst()->PopWindow.PageItem.ItemPadding;
    m_nFontSize = CConfigManager::Inst()->PopWindow.FontSize;
    m_strFontName = CConfigManager::Inst()->PopWindow.FontName;
    m_nColumnCount = CConfigManager::Inst()->PopWindow.PageItem.ColumnCount;
    m_nRowCount = CConfigManager::Inst()->PopWindow.PageItem.RowCount;

	ReloadColor();

    
    m_nPageCount = 0;
	m_bCaptured = FALSE;
	m_pActivePage = NULL;
}

CWETabCtrl::~CWETabCtrl()
{
}

BEGIN_MESSAGE_MAP(CWETabCtrl, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CWETabCtrl

void CWETabCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//
	if (nType == SIZE_RESTORED)
	{
		m_rcUnit.SetRect(0,0,cx,cy);

		// update children rect
		CRect rcPage;
		GetPageRect(rcPage);

		MoveRect(rcPage);
		Redraw();
	}
}

void CWETabCtrl::Draw( CDC *pDC )
{
	// double buffer
	CDC dcMem;
	CBitmap bmpMem;
	dcMem.CreateCompatibleDC(pDC);
	bmpMem.CreateCompatibleBitmap(pDC,m_rcUnit.Width(),m_rcUnit.Height());
	dcMem.SelectObject(&bmpMem);

	// draw background
	CBrush br(crBackground);
	dcMem.FillRect(m_rcUnit,&br);


	CFont font;
	font.CreatePointFont(m_nFontSize,m_strFontName);
	dcMem.SelectObject(font);
	dcMem.SetBkMode(TRANSPARENT);
	CWEPaintUint::Draw(&dcMem);

	// copy to screen
	pDC->BitBlt(m_rcUnit.left,m_rcUnit.top,m_rcUnit.Width(),m_rcUnit.Height(),&dcMem,0,0,SRCCOPY);//将内存DC上的图象拷贝到前台

	dcMem.DeleteDC();
	bmpMem.DeleteObject();
}
void CWETabCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	Draw(&dc);
}


CWETabPage * CWETabCtrl::AppendPage( CString strCaption /*= ""*/ )
{
	CRect rcPage;
	GetPageRect(rcPage);

	CWETabPage *pPage = (CWETabPage*)this->CreateChild(rcPage,RUNTIME_CLASS(CWETabPage));
	pPage->nIndex = m_nPageCount++;

	pPage->pnPageCount = &m_nPageCount;
	pPage->pnHeaderHeight = &m_nHeaderHeight;
	pPage->pnHeaderHorzMargin = &m_nHeaderHorzMargin;
	pPage->pnHeaderTopMargin = &m_nHeaderTopMargin;
	pPage->pnHeaderActiveHorzMargin = &m_nHeaderActiveHorzMargin;
	pPage->pnHeaderActiveTopMargin = &m_nHeaderActiveTopMargin;
	pPage->pnPagePadding = &m_nPagePadding;
	pPage->pnColumnCount = &m_nColumnCount;
	pPage->pnRowCount = &m_nRowCount;
	pPage->pnItemPadding = &m_nItemPadding;
	pPage->strCaption = strCaption;

	pPage->crBackground = m_lstPageBackgrounds.RemoveHead();
	m_lstPageBackgrounds.AddTail(pPage->crBackground);

	if (m_pActivePage == NULL)
	{
		m_pActivePage = pPage;
		pPage->bIsActive = TRUE;
	}

	Redraw();

	return pPage;
}

void CWETabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bCaptured = TRUE;
}

void CWETabCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// unsupport double click, to make it more simple
	OnLButtonDown(nFlags,point);
}

void CWETabCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bCaptured)
	{
		ReleaseCapture();
		
		CWEPaintUint *pHit = HitTest(point,LBTNUP);
		if (pHit != NULL)
		{
			CWETabPage *pPage = DYNAMIC_DOWNCAST(CWETabPage,pHit);
			if (pPage != NULL)
			{
				ActivePage(pPage);
			}
			CWETabItem *pItem = DYNAMIC_DOWNCAST(CWETabItem,pHit);
			if (pItem != NULL)
			{
				if (GetParent() != NULL)
				{
					GetParent()->SendMessage(MSG_HITITEM,(WPARAM)(LPCTSTR)pItem->strContent,0);
				}
			}
		}
	}
}

void CWETabCtrl::ActivePage( CWETabPage * pPage )
{
	if (!pPage->bIsActive)
	{
		m_pActivePage->bIsActive = FALSE;
		m_pActivePage = pPage;
		m_pActivePage->bIsActive = TRUE;
		Redraw();

		return;
	}
}

BOOL CWETabCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CWETabCtrl::GetPageRect( CRect &rcPage )
{
	rcPage = m_rcUnit;
	rcPage.DeflateRect(m_nCtrlPadding,m_nCtrlPadding);
}

void CWETabCtrl::Redraw()
{
	CClientDC dc(this);
	Draw(&dc);
}

void CWETabCtrl::Create( CRect rcWindow,CWnd *pParent,UINT nId )
{
	LPCTSTR pClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	CWnd::Create(pClassName,_T("WETabCtrl"),WS_VISIBLE|WS_CHILD,rcWindow,pParent,nId);
}

void CWETabCtrl::RemoveAllPages()
{
	this->RemoveChildren();
	ReloadColor();
	m_nPageCount = 0;
	m_pActivePage = NULL;
}

void CWETabCtrl::ReloadColor()
{
	m_lstPageBackgrounds.RemoveAll();

	for (POSITION pos = CConfigManager::Inst()->PopWindow.Pages.Colors.GetHeadPosition();
		pos != NULL;)
	{
		m_lstPageBackgrounds.AddTail(CConfigManager::Inst()->PopWindow.Pages.Colors.GetNext(pos));
	}
}