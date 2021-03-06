#include "DlgPopup.h"
#include "Ntray.h"
#include "afxwin.h"
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
	CTrayNotifyIcon m_trayIcon;
	BOOL m_bVisible;

	virtual BOOL OnInitDialog();
	void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	LRESULT OnTrayNotification( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
    afx_msg void OnBnEmoticon();
    afx_msg void OnTrayExit();
    afx_msg void OnTrayConfig();
    afx_msg void OnTrayAbout();
	afx_msg LRESULT OnTrayMButtonUp(WPARAM,LPARAM);
	afx_msg void OnBnClickedCheckNostartpop();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	CButton m_editNoStartpop;
};
