#pragma once
#include "afxwin.h"


// CDlgAddBatch 

class CDlgAddBatch : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddBatch)

public:
	CDlgAddBatch(CWnd* pParent = NULL);   // 
	virtual ~CDlgAddBatch();

// 
	enum { IDD = IDD_ADDBATCH };
	CStringList input;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editContent;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
