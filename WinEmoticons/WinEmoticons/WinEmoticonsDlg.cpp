// WinEmoticonsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WinEmoticonsDlg.h"
#include "DlgPopup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinEmoticonsDlg 对话框




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
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWinEmoticonsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CWinEmoticonsDlg 消息处理程序

BOOL CWinEmoticonsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_dlgPopup.Create(CDlgPopup::IDD);

	// 
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CWinEmoticonsDlg::OnBnClickedOk()
{
	//OnOK();

	this->ShowWindow(SW_HIDE);
}
