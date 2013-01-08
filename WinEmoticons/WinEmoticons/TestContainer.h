#pragma once
#include "afxwin.h"
#include "WETabCtrl.h"


// CTestContainer 对话框

class CTestContainer : public CDialog
{
	DECLARE_DYNAMIC(CTestContainer)

public:
	CTestContainer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestContainer();

// 对话框数据
	enum { IDD = IDD_TESTCONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWETabCtrl m_wndWETabCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
};
