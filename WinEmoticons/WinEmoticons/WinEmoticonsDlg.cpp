// WinEmoticonsDlg.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WinEmoticonsDlg.h"
#include "DlgPopup.h"
#include "DlgEditEmoticons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MSG_TRAYNOTIFY	WM_USER + 200  //自定义系统托盘消息

// CWinEmoticonsDlg

CWinEmoticonsDlg::CWinEmoticonsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinEmoticonsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CWinEmoticonsDlg::~CWinEmoticonsDlg()
{
}

void CWinEmoticonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinEmoticonsDlg, CDialog)
	ON_WM_PAINT()	
    ON_BN_CLICKED(IDOK, &CWinEmoticonsDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BTN_EMOTICONS, &CWinEmoticonsDlg::OnBnEmoticon)
    //}}AFX_MSG_MAP
	ON_MESSAGE(MSG_TRAYNOTIFY, OnTrayNotification)  //自定义系统托盘消息涵数
    ON_COMMAND(ID__EXIT,OnTrayExit)
    ON_COMMAND(ID__CONFIG,OnTrayConfig)
    ON_COMMAND(ID__ABOUT,OnTrayAbout)
END_MESSAGE_MAP()


BOOL CWinEmoticonsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_dlgPopup.Create();

	// 
	m_trayIcon.Create(this, IDR_MENU_TRAY, _T("WinEmotions"), 
		m_hIcon,					
		MSG_TRAYNOTIFY);


	return TRUE;
}


void CWinEmoticonsDlg::OnBnClickedOk()
{
	//OnOK();

	this->ShowWindow(SW_HIDE);
}

void CWinEmoticonsDlg::OnBnEmoticon()
{
	// hide window
	if (m_dlgPopup.IsWindowVisible())
	{
		m_dlgPopup.HideWindow();
	}

	// popup config window
    CDlgEditEmoticons dlgEmoticons(this);
    if(dlgEmoticons.DoModal() == IDOK)
	{
		m_dlgPopup.ReloadEmoticons();
	}
}

LRESULT CWinEmoticonsDlg::OnTrayNotification( WPARAM wParam, LPARAM lParam )
{
	return m_trayIcon.OnTrayNotification(wParam, lParam);
}

void CWinEmoticonsDlg::OnTrayExit()
{
    OnOK();
}

void CWinEmoticonsDlg::OnTrayConfig()
{
    this->ShowWindow(this->IsWindowVisible() ? SW_HIDE : SW_SHOW);
}

void CWinEmoticonsDlg::OnTrayAbout()
{
    
}