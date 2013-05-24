#pragma once
#include "afxwin.h"


// CDlgAddOne 

class CDlgAddOne : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddOne)

public:
	CDlgAddOne(CWnd* pParent,CString strInit);   // 
	virtual ~CDlgAddOne();

	CString input;
// 
	enum { IDD = IDD_ADDONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_input;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
