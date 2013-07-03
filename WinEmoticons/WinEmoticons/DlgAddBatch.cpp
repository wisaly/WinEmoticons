// DlgAddBatch.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgAddBatch.h"
#include "MsgBox.h"


// CDlgAddBatch 

IMPLEMENT_DYNAMIC(CDlgAddBatch, CDialog)

CDlgAddBatch::CDlgAddBatch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddBatch::IDD, pParent)
{

}

CDlgAddBatch::~CDlgAddBatch()
{
}

void CDlgAddBatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTENT, m_editContent);
}


BEGIN_MESSAGE_MAP(CDlgAddBatch, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddBatch::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddBatch::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgAddBatch 

void CDlgAddBatch::OnBnClickedOk()
{
	CString strContent;
	m_editContent.GetWindowText(strContent);

	if (strContent.IsEmpty())
	{
		CMsgBox::Error(_T("«Î ‰»Îƒ⁄»›"),this);
		return;
	}

	input.RemoveAll();

	int nSplitPos = -1;
	while (-1 != (nSplitPos = strContent.Find('\n')))
	{
		input.AddTail(strContent.Left(nSplitPos));

		strContent = strContent.Right(strContent.GetLength() - nSplitPos - 1);
	}

	if (!strContent.IsEmpty())
	{
		input.AddTail(strContent);
	}

	OnOK();
}

void CDlgAddBatch::OnBnClickedCancel()
{
	OnCancel();
}
