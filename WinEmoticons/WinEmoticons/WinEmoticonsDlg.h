#include "DlgPopup.h"
// WinEmoticonsDlg.h
//

#pragma once


// CWinEmoticonsDlg
class CWinEmoticonsDlg : public CDialog
{
public:
	CWinEmoticonsDlg(CWnd* pParent = NULL);
	~CWinEmoticonsDlg();

	enum { IDD = IDD_WINEMOTICONS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	HICON m_hIcon;
	CDlgPopup m_dlgPopup;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
