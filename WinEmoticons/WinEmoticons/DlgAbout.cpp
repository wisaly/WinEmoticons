// DlgAbout.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgAbout.h"


// CDlgAbout 

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbout::IDD, pParent)
{

}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOME_PAGE, m_editHomePage);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_HOME_PAGE, &CDlgAbout::OnNMClickLink)
	ON_NOTIFY(NM_CLICK, IDC_ISSUE_PAGE, &CDlgAbout::OnNMClickLink)
END_MESSAGE_MAP()


// CDlgAbout 

void CDlgAbout::OnNMClickLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString strLink;
	GetDlgItemText(pNMHDR->idFrom,strLink);
	strLink.Replace(_T("<a>"),_T(""));
	strLink.Replace(_T("</a>"),_T(""));
	
	ShellExecute(NULL, _T("open"),strLink, NULL, NULL, SW_SHOW);
	*pResult = 0;
}
