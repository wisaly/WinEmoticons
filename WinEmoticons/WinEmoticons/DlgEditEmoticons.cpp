// DlgEditEmoticons.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgEditEmoticons.h"


// CDlgEditEmoticons 

IMPLEMENT_DYNAMIC(CDlgEditEmoticons, CDialog)

CDlgEditEmoticons::CDlgEditEmoticons(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditEmoticons::IDD, pParent)
{

}

CDlgEditEmoticons::~CDlgEditEmoticons()
{
}

void CDlgEditEmoticons::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditEmoticons, CDialog)
END_MESSAGE_MAP()
