#include "StdAfx.h"
#include "WETabItem.h"

IMPLEMENT_DYNCREATE(CWETabItem,CWEPaintUint)

CWETabItem::CWETabItem( CRect rcThis,CWEPaintUint *pParent /*= NULL*/ )
	:CWEPaintUint(rcThis,pParent)
{

}
CWETabItem::~CWETabItem(void)
{
}

void CWETabItem::Draw( CDC *pDC )
{
	CBrush br(crBackground);

	// calc item rect
	CRect rcThis;
	GetItemRect(rcThis);

	pDC->FillRect(rcThis,&br);

	// draw text
	CPen pen(PS_SOLID,1,crForeground);
	CPen *pOldPen = pDC->SelectObject(&pen);
	pDC->DrawText(strContent,rcThis,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	pDC->SelectObject(pOldPen);
}

void CWETabItem::GetItemRect( CRect &rcThis )
{
	rcThis = m_rcUnit;
	rcThis.DeflateRect(*pnItemPadding,*pnItemPadding);
}

void CWETabItem::MoveRect( CRect rcNew )
{
	m_rcUnit = rcNew;
}

CWEPaintUint * CWETabItem::HitTest( CPoint ptHit,MouseEvent meMouse /*= NOTHING*/ )
{
	CRect rcThis;
	GetItemRect(rcThis);

	if (!rcThis.PtInRect(ptHit))
	{
		return NULL;
	}
	
	// in unit
	if (meMouse == NOTHING)
	{
		return this;
	}
	if (meMouse == LBTNUP)
	{
		return this;
	}

	return this;
}