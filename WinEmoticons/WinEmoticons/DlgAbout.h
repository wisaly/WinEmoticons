#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgAbout 

class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 
	virtual ~CDlgAbout();

// 
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickLink(NMHDR *pNMHDR, LRESULT *pResult);
	CLinkCtrl m_editHomePage;
	CStatic m_editVer;
	virtual BOOL OnInitDialog();
};
