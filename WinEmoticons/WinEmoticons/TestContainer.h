#pragma once
#include "afxwin.h"
#include "WETabCtrl.h"


// CTestContainer

class CTestContainer : public CDialog
{
	DECLARE_DYNAMIC(CTestContainer)

public:
	CTestContainer(CWnd* pParent = NULL);
	virtual ~CTestContainer();

	enum { IDD = IDD_TESTCONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CWETabCtrl m_wndWETabCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
};
