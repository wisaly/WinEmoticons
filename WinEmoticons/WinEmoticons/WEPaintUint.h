#pragma once

class CWEPaintUint : public CObject	// use rtti feathers
{
public:
	CWEPaintUint(CRect rcThis = CRect(),CWEPaintUint *pParent = NULL);
	virtual ~CWEPaintUint(void);
	// Constant:
	enum MouseEvent{NOTHING,LBTNDOWN,LBTNUP,LBTNMOVE,RBTNDOWN,RBTNUP,RBTNMOVE};

	// Attributes:
public:
	BOOL			bVisible;		// is this unit visible
	COLORREF		crBackground;	// background color
	COLORREF		crForeground;	// foreground color
	COLORREF		crHightlight;	// highlight color
	COLORREF		crChecked;		// checked color
	COLORREF		crDisabled;		// disabled color
protected:
	CRect			m_rcUnit;		// rect of this unit
	CWEPaintUint	*m_pParent;		// parent unit
	CWEPaintUint	*m_pFirstChild;	// first child unit
	CWEPaintUint	*m_pNextSibling;// next sibling unit
	BOOL			m_bIsNew;		// is this should be delete in destructor

	// Methods:
public:
	// init all member data
	void InitData( CRect rcThis,CWEPaintUint * pParent );
	// draw this unit
	virtual void Draw(CDC *pDC);
	// hit test
	virtual CWEPaintUint *HitTest(CPoint ptHit,MouseEvent meMouse = NOTHING);
	// move unit to new rect
	virtual void MoveRect(CRect rcNew);
	// create child unit
	CWEPaintUint *CreateChild(CRect rcChild,CRuntimeClass *pClass);
	// remove this unit
	void Remove();
	// offset unit
	void Offset(int nx,int ny);
	// get rect coordinate to unit
	void GetUnitRect(CRect &rcUnit);
	// get parent unit
	inline CWEPaintUint *Parent(){ return m_pParent; }
	// get first child unit
	inline CWEPaintUint *FirstChild(){ return m_pFirstChild; }
	// get next sibling unit
	inline CWEPaintUint *NextSibling(){ return m_pNextSibling; }

protected:
	// offset point to paint coordinate
	CPoint &CalcPosition(CPoint &ptThis);
	// offset rect to paint coordinate
	CRect &CalcPosition(CRect &rcThis);
};
