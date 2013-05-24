// DlgAddOne.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgAddOne.h"


// CDlgAddOne 

IMPLEMENT_DYNAMIC(CDlgAddOne, CDialog)

CDlgAddOne::CDlgAddOne(CWnd* pParent,CString strInit)
	: CDialog(CDlgAddOne::IDD, pParent),input(strInit)
{

}

CDlgAddOne::~CDlgAddOne()
{
}

void CDlgAddOne::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EINPUT, m_input);
}


BEGIN_MESSAGE_MAP(CDlgAddOne, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddOne::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAddOne 

BOOL CDlgAddOne::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_input.SetWindowText(input);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgAddOne::OnBnClickedOk()
{
	m_input.GetWindowText(input);

	OnOK();
}