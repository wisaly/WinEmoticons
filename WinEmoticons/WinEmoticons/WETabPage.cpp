#include "StdAfx.h"
#include "WETabPage.h"

IMPLEMENT_DYNCREATE(CWETabPage,CWEPaintUint)

CWETabPage::CWETabPage( CRect rcThis,CWEPaintUint *pParent /*= NULL*/ )
	:CWEPaintUint(rcThis,pParent),
	pnHeaderHeight(NULL),
	pnPageCount(NULL),
	pnHeaderHorzMargin(NULL),
	pnHeaderTopMargin(NULL),
	pnHeaderActiveHorzMargin(NULL),
	pnHeaderActiveTopMargin(NULL),
	pnPagePadding(NULL),
	pnColumnCount(NULL),
	pnRowCount(NULL),
	m_nItemCount(0)
{
	bIsActive = FALSE;
}
CWETabPage::~CWETabPage(void)
{
}

void CWETabPage::Draw( CDC *pDC )
{
	CBrush br(crBackground);

	// draw header
	CRect rcHeader;
	GetHeaderRect(rcHeader);

	pDC->FillRect(rcHeader,&br);

	// draw header text
	CPen pen(PS_SOLID,1,crForeground);
	CPen *pOldPen = pDC->SelectObject(&pen);
	pDC->DrawText(strCaption,rcHeader,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	pDC->SelectObject(pOldPen);

	// draw page
	if (bIsActive)
	{
		CRect rcPage;
		GetBodyRect(rcPage);

		pDC->FillRect(rcPage,&br);

		// draw children
		CWEPaintUint::Draw(pDC);
	}
}

CWEPaintUint *CWETabPage::HitTest( CPoint ptHit,MouseEvent meMouse )
{
	// test hit header
	CRect rcHeader;
	GetHeaderRect(rcHeader);
	if (rcHeader.PtInRect(ptHit))
	{
		return this;
	}
	else
	{
		if (bIsActive)
		{
			// test hit body
			CRect rcBody;
			GetBodyRect(rcBody);
			
			if (rcBody.PtInRect(ptHit))
			{
				return CWEPaintUint::HitTest(ptHit,meMouse);
			}
		}

		return NULL;
	}
}

void CWETabPage::GetHeaderRect( CRect &rcHeader)
{
	rcHeader.SetRect(
		nIndex * m_rcUnit.Width() / *pnPageCount + (bIsActive ? *pnHeaderActiveHorzMargin : *pnHeaderHorzMargin),
		bIsActive ? *pnHeaderActiveTopMargin : *pnHeaderTopMargin,
		(nIndex + 1) * m_rcUnit.Width() / *pnPageCount - (bIsActive ? *pnHeaderActiveHorzMargin : *pnHeaderHorzMargin),
		*pnHeaderHeight - (bIsActive ? 0 : *pnHeaderTopMargin));

	CalcPosition(rcHeader);
}

void CWETabPage::GetBodyRect( CRect &rcPage )
{
	rcPage.SetRect(
		0,
		*pnHeaderHeight,
		m_rcUnit.Width(),
		m_rcUnit.Height());

	CalcPosition(rcPage);
}

CWETabItem *CWETabPage::AppendItem( CString strContent )
{
	CRect rcItem;
	GetItemRect(m_nItemCount,rcItem);


	CWETabItem *pItem = (CWETabItem*)this->CreateChild(rcItem,RUNTIME_CLASS(CWETabItem));
	pItem->nIndex = m_nItemCount++;
	pItem->pnItemPadding = this->pnItemPadding;

	pItem->strContent = strContent;

	return pItem;
}

void CWETabPage::GetItemRect( int nIndex,CRect &rcItem )
{
	GetBodyRect(rcItem);
	rcItem.DeflateRect(*pnPagePadding,*pnPagePadding);
	rcItem.SetRect(
		rcItem.left + nIndex % *pnColumnCount * rcItem.Width() / *pnColumnCount,
		rcItem.top + nIndex / *pnColumnCount * rcItem.Height() / *pnRowCount,
		rcItem.left + (nIndex % *pnColumnCount + 1) * rcItem.Width() / *pnColumnCount,
		rcItem.top + (nIndex / *pnColumnCount + 1) * rcItem.Height() / *pnRowCount
		);
}

void CWETabPage::MoveRect( CRect rcNew )
{
	m_rcUnit = rcNew;

	CWEPaintUint *pChild = m_pFirstChild;
	while(pChild != NULL)
	{
		CWETabItem *pItem = DYNAMIC_DOWNCAST(CWETabItem,pChild);
		ASSERT(pItem != NULL);
		GetItemRect(pItem->nIndex, rcNew);
		pItem->MoveRect(rcNew);

		pChild = pChild->NextSibling();
	}
}
