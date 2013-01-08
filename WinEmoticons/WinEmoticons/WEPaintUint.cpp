#include "StdAfx.h"
#include "WEPaintUint.h"

// Constructor
CWEPaintUint::CWEPaintUint(CRect rcThis,CWEPaintUint *pParent)
{
	InitData(rcThis,pParent);
}

// Init member
void CWEPaintUint::InitData( CRect rcThis,CWEPaintUint * pParent )
{
	// keep tree struct
	m_pNextSibling = NULL;
	m_pFirstChild = NULL;
	m_pParent = pParent;
	if (m_pParent != NULL)
	{
		if (m_pParent->m_pFirstChild == NULL)
		{
			// if parent has no child, be the first
			m_pParent->m_pFirstChild = this;
		}
		else
		{
			// if parent have children, be the last
			CWEPaintUint *pThisPrevious = m_pParent->m_pFirstChild;
			while(pThisPrevious->m_pNextSibling != NULL)
			{
				pThisPrevious = pThisPrevious->m_pNextSibling;
			}
			pThisPrevious->m_pNextSibling = this;
		}
	}

	// 
	m_rcUnit = rcThis;
	m_bIsNew = FALSE;
	this->bVisible = TRUE;
	crBackground = RGB(255,255,255);
	crForeground = RGB(0,0,0);
	crHightlight = RGB(255,255,255);
	crChecked = RGB(255,255,255);
	crDisabled = RGB(128,128,128);
}

// Destructor, free memory
CWEPaintUint::~CWEPaintUint(void)
{
	CWEPaintUint *pChild = m_pFirstChild;
	while(pChild != NULL)
	{
		CWEPaintUint *pDelete = pChild;
		pChild = pChild->m_pNextSibling;

		if (pDelete->m_bIsNew)
		{
			delete pDelete;
		}
	}
}

// Create child unit
CWEPaintUint * CWEPaintUint::CreateChild( CRect rcChild,CRuntimeClass *pClass )
{
	ASSERT (pClass->IsDerivedFrom(RUNTIME_CLASS(CWEPaintUint)));
	
	CWEPaintUint *pNew = DYNAMIC_DOWNCAST(CWEPaintUint,pClass->CreateObject());
	ASSERT(pNew != NULL);

	pNew->InitData(rcChild,this);
	pNew->m_bIsNew = TRUE;
	return pNew;
}

void CWEPaintUint::Remove()
{
	if (m_bIsNew)
	{
		delete this;
	}
}

void CWEPaintUint::Draw( CDC *pDC )
{
	// Draw child
	if (this->bVisible)
	{
		CWEPaintUint *pChild = m_pFirstChild;
		while (pChild != NULL)
		{
			pChild->Draw(pDC);

			pChild = pChild->m_pNextSibling;
		}
	}
}

CPoint &CWEPaintUint::CalcPosition( CPoint &ptThis )
{
	ptThis.Offset(m_rcUnit.left,m_rcUnit.right);
	return ptThis;
}

CRect &CWEPaintUint::CalcPosition( CRect &rcThis )
{
	rcThis.OffsetRect(m_rcUnit.left,m_rcUnit.top);
	return rcThis;
}

CWEPaintUint * CWEPaintUint::HitTest( CPoint ptHit,MouseEvent meMouse )
{
	if (m_rcUnit.PtInRect(ptHit) && this->bVisible)
	{
		CWEPaintUint *pChild = m_pFirstChild;
		while (pChild != NULL)
		{
			CWEPaintUint *pChildHit = pChild->HitTest(ptHit,meMouse);
			if (pChildHit != NULL)
			{
				return pChildHit;
			}
			pChild = pChild->m_pNextSibling;
		}

		return this;
	}
	return NULL;
}

void CWEPaintUint::Offset( int nx,int ny )
{
	m_rcUnit.OffsetRect(nx,ny);
}

void CWEPaintUint::GetUnitRect( CRect &rcUnit )
{
	rcUnit.SetRect(0,0,m_rcUnit.Width(),m_rcUnit.Height());
}

void CWEPaintUint::MoveRect( CRect rcNew )
{
	CWEPaintUint *pChild = m_pFirstChild;
	while(pChild != NULL)
	{
		pChild->MoveRect(rcNew);
		pChild = pChild->m_pNextSibling;
	}
}
