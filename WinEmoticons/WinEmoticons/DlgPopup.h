#include "WETabCtrl.h"
#pragma once


// CDlgPopup

class CDlgPopup : public CDialog
{
	DECLARE_DYNAMIC(CDlgPopup)

public:
	CDlgPopup(CWnd* pParent = NULL);
	virtual ~CDlgPopup();

	void PopupWindow();
	void HideWindow();

	void SendEmoticon(CString strText);
	int ReloadHotkey();
	void ReloadEmoticons();

	CWETabCtrl m_wndTab;

	int m_nHotKeyId;
	CWnd *m_pForeWnd;
	CWnd *m_pFocusedControl;

	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMsgTabItemHit(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnHotKey( WPARAM wParam,LPARAM lParam );
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
