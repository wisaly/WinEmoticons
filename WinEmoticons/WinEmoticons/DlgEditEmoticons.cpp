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
    DDX_Control(pDX,IDC_TAB_GROUP,m_tabGroup);
    DDX_Control(pDX,IDC_LIST_EMOS,m_lbxEmos);
    DDX_Control(pDX,IDC_ADDEMO,m_btnAddEmo);
    DDX_Control(pDX,IDC_DELEMO,m_btnDelEmo);
    DDX_Control(pDX,IDC_MODEMO,m_btnModEmo);

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditEmoticons, CDialog)
END_MESSAGE_MAP()


void CDlgEditEmoticons::showEmoCtrlsVisible( BOOL bVisble )
{
    m_lbxEmos.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
    m_btnAddEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
    m_btnDelEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
    m_btnModEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
}

BOOL CDlgEditEmoticons::OnInitDialog()
{
    CDialog::OnInitDialog();

    showEmoCtrlsVisible(FALSE);

    return TRUE;
}

void CDlgEditEmoticons::OnOK()
{

}