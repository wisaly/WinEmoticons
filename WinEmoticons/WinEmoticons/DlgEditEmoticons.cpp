// DlgEditEmoticons.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgEditEmoticons.h"
#include "DlgAddBatch.h"
#include "DlgAddOne.h"


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
	DDX_Control(pDX, IDC_ROW, m_editRow);
	DDX_Control(pDX, IDC_COL, m_editCol);
	DDX_Control(pDX, IDC_LEFTEMO, m_btnLeftEmo);
	DDX_Control(pDX, IDC_RIGHTEMO, m_btnRightEmo);
	DDX_Control(pDX, IDC_DELGROUP, m_btnDelGroup);
	DDX_Control(pDX, IDC_MODGROUP, m_btnRenGroup);
	DDX_Control(pDX, IDC_LEFTGROUP, m_btnLeftGroup);
	DDX_Control(pDX, IDC_RIGHTGROUP, m_btnRightGroup);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditEmoticons, CDialog)
	ON_BN_CLICKED(IDC_ADDGROUP, &CDlgEditEmoticons::OnBnClickedAddgroup)
	ON_BN_CLICKED(IDC_DELGROUP, &CDlgEditEmoticons::OnBnClickedDelgroup)
	ON_BN_CLICKED(IDC_MODGROUP, &CDlgEditEmoticons::OnBnClickedModgroup)
	ON_BN_CLICKED(IDC_LEFTGROUP, &CDlgEditEmoticons::OnBnClickedLeftgroup)
	ON_BN_CLICKED(IDC_RIGHTGROUP, &CDlgEditEmoticons::OnBnClickedRightgroup)
	ON_BN_CLICKED(IDC_ADDEMO, &CDlgEditEmoticons::OnBnClickedAddemo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_GROUP, &CDlgEditEmoticons::OnTcnSelchangeTabGroup)
	ON_BN_CLICKED(IDC_DELEMO, &CDlgEditEmoticons::OnBnClickedDelemo)
END_MESSAGE_MAP()


void CDlgEditEmoticons::showEmoCtrlsVisible( BOOL bVisble )
{
    m_lbxEmos.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
    m_btnAddEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
    m_btnDelEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnModEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnLeftEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnRightEmo.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnDelGroup.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnRenGroup.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnLeftGroup.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
	m_btnRightGroup.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
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

POSITION CDlgEditEmoticons::getGroupPos(int nIndex)
{
	POSITION posCur = m_emotions.Pages.GetHeadPosition();
	for (int i = 0;i < nIndex;i ++)
	{
		m_emotions.Pages.GetNext(posCur);
	}

	return posCur;
}

void CDlgEditEmoticons::addGroup( CString strName )
{
	m_tabGroup.InsertItem(m_tabGroup.GetCurSel() + 1,strName);
	CConfigManager::_tag_emoticons::_tag_page apage;
	apage.Caption = strName;
	m_emotions.Pages.AddTail(apage);
	m_tabGroup.SetCurSel(m_tabGroup.GetCurSel() + 1);
}

void CDlgEditEmoticons::delGroup( int nCur )
{
	m_emotions.Pages.RemoveAt(getGroupPos(nCur));

	m_tabGroup.DeleteItem(nCur);
	m_tabGroup.SetCurSel(nCur > 1 ? nCur - 1 : 0);
}

void CDlgEditEmoticons::OnBnClickedAddgroup()
{
	// 
	CDlgAddBatch dlg;
	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.input.GetHeadPosition();pos != NULL;)
		{
			CString strGroup = dlg.input.GetNext(pos);
			addGroup(strGroup);
		}

		showEmoCtrlsVisible(TRUE);
	}
}

void CDlgEditEmoticons::OnBnClickedDelgroup()
{
	int nCur = m_tabGroup.GetCurSel();
	
	if (nCur < 0)
	{
		return;
	}
	if(MessageBox(_T("确认删除？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
	{
		return ;
	}

	delGroup(nCur);

	if(m_tabGroup.GetItemCount() == 0)
	{
		showEmoCtrlsVisible(FALSE);
	}
	else
	{
		m_tabGroup.ShowWindow(SW_HIDE);
		m_tabGroup.ShowWindow(SW_SHOW);
	}
}


void CDlgEditEmoticons::OnBnClickedModgroup()
{
	int nCur = m_tabGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	
	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emotions.Pages.GetAt(pos);

	CDlgAddOne dlg(this,curPage.Caption);

	if (dlg.DoModal() == IDOK)
	{
		curPage.Caption = dlg.input;

		TCITEM tabCtrlItem;
		tabCtrlItem.mask = TCIF_TEXT;
		tabCtrlItem.pszText = dlg.input.GetBuffer();
		m_tabGroup.SetItem(nCur,&tabCtrlItem);
	}
}

void CDlgEditEmoticons::OnBnClickedLeftgroup()
{
	int nCur = m_tabGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}

	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emotions.Pages.GetAt(pos);
	
	POSITION posPrev = pos;
	m_emotions.Pages.GetPrev(posPrev);
	if (posPrev == NULL)
	{
		return ;
	}
	m_emotions.Pages.InsertBefore(posPrev,curPage);
	m_emotions.Pages.RemoveAt(pos);

	m_tabGroup.DeleteItem(nCur);
	m_tabGroup.InsertItem(nCur - 1,curPage.Caption);

	m_tabGroup.ShowWindow(SW_HIDE);
	m_tabGroup.ShowWindow(SW_SHOW);
}

void CDlgEditEmoticons::OnBnClickedRightgroup()
{
	int nCur = m_tabGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}

	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emotions.Pages.GetAt(pos);

	POSITION posPrev = pos;
	m_emotions.Pages.GetNext(posPrev);
	if (posPrev == NULL)
	{
		return ;
	}
	m_emotions.Pages.InsertAfter(posPrev,curPage);
	m_emotions.Pages.RemoveAt(pos);

	m_tabGroup.DeleteItem(nCur);
	m_tabGroup.InsertItem(nCur + 1,curPage.Caption);

	m_tabGroup.ShowWindow(SW_HIDE);
	m_tabGroup.ShowWindow(SW_SHOW);
}

void CDlgEditEmoticons::OnTcnSelchangeTabGroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 
	int nCur = m_tabGroup.GetCurSel();
	POSITION posGroup = getGroupPos(nCur);

	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emotions.Pages.GetAt(posGroup);

	m_lbxEmos.ResetContent();
	for (POSITION pos = curPage.Items.GetHeadPosition();pos != NULL;)
	{
		CConfigManager::_tag_emoticons::_tag_page::_tag_item item = curPage.Items.GetNext(pos);

		m_lbxEmos.AddString(item.Content);
	}

	*pResult = 0;
}

void CDlgEditEmoticons::addEmo( CString strEmo )
{
	int nCur = m_tabGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	POSITION pos = getGroupPos(nCur);

	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emotions.Pages.GetAt(pos);

	CConfigManager::_tag_emoticons::_tag_page::_tag_item item;
	item.Content = strEmo;
	curPage.Items.AddTail(item);

	m_lbxEmos.InsertString(m_lbxEmos.GetCurSel(),strEmo);
}

void CDlgEditEmoticons::OnBnClickedAddemo()
{
	CDlgAddBatch dlg;
	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.input.GetHeadPosition();pos != NULL;)
		{
			CString strItem = dlg.input.GetNext(pos);
			addEmo(strItem);
		}
	}
}


void CDlgEditEmoticons::OnBnClickedDelemo()
{
	
}
