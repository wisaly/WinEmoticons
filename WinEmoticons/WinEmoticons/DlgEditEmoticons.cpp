// DlgEditEmoticons.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgEditEmoticons.h"
#include "DlgAddBatch.h"
#include "DlgAddOne.h"
#include "DlgEmoticonFile.h"


// CDlgEditEmoticons 

IMPLEMENT_DYNAMIC(CDlgEditEmoticons, CDialog)

CDlgEditEmoticons::CDlgEditEmoticons(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditEmoticons::IDD, pParent)
	, m_nRowCount(1)
	, m_nColCount(1)
{

	CConfigManager::Inst()->IsOnConfig = TRUE;
}

CDlgEditEmoticons::~CDlgEditEmoticons()
{
	CConfigManager::Inst()->IsOnConfig = FALSE;
}

void CDlgEditEmoticons::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX,IDC_LIST_GROUP,m_lbxGroup);
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
	DDX_Text(pDX, IDC_ROW, m_nRowCount);
	DDX_Text(pDX, IDC_COL, m_nColCount);
	DDX_Control(pDX, IDC_GROUP_EMOTICON, m_wndGroupEmoticon);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditEmoticons, CDialog)
	ON_BN_CLICKED(IDC_ADDGROUP, &CDlgEditEmoticons::OnBnClickedAddgroup)
	ON_BN_CLICKED(IDC_DELGROUP, &CDlgEditEmoticons::OnBnClickedDelgroup)
	ON_BN_CLICKED(IDC_MODGROUP, &CDlgEditEmoticons::OnBnClickedModgroup)
	ON_BN_CLICKED(IDC_LEFTGROUP, &CDlgEditEmoticons::OnBnClickedLeftgroup)
	ON_BN_CLICKED(IDC_RIGHTGROUP, &CDlgEditEmoticons::OnBnClickedRightgroup)
	ON_BN_CLICKED(IDC_ADDEMO, &CDlgEditEmoticons::OnBnClickedAddemo)
	ON_BN_CLICKED(IDC_DELEMO, &CDlgEditEmoticons::OnBnClickedDelemo)
	ON_LBN_SELCHANGE(IDC_LIST_GROUP, &CDlgEditEmoticons::OnLbnSelchangeListGroup)
	ON_BN_CLICKED(IDC_MODEMO, &CDlgEditEmoticons::OnBnClickedModemo)
	ON_BN_CLICKED(IDC_LEFTEMO, &CDlgEditEmoticons::OnBnClickedLeftemo)
	ON_BN_CLICKED(IDC_RIGHTEMO, &CDlgEditEmoticons::OnBnClickedRightemo)
	ON_BN_CLICKED(IDC_EXPORT, &CDlgEditEmoticons::OnBnClickedExport)
	ON_BN_CLICKED(IDC_IMPORT, &CDlgEditEmoticons::OnBnClickedImport)
	ON_BN_CLICKED(IDC_CLEAR, &CDlgEditEmoticons::OnBnClickedClear)
	ON_BN_CLICKED(IDOK, &CDlgEditEmoticons::OnBnClickedOk)
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
	m_wndGroupEmoticon.ShowWindow(bVisble ? SW_SHOW : SW_HIDE);
}

// initialize dialog
BOOL CDlgEditEmoticons::OnInitDialog()
{
    CDialog::OnInitDialog();

	m_font.CreatePointFont(
		CConfigManager::Inst()->PopWindow.FontSize,
		CConfigManager::Inst()->PopWindow.FontName);
	m_lbxGroup.SetFont(&m_font);
	m_lbxEmos.SetFont(&m_font);

	
	m_nColCount = CConfigManager::Inst()->PopWindow.PageItem.ColumnCount;
	m_nRowCount = CConfigManager::Inst()->PopWindow.PageItem.RowCount;
	UpdateData(FALSE);

	// load data from config
	reloadData(CConfigManager::Inst()->Emoticons);

    return TRUE;
}

// close dialog
void CDlgEditEmoticons::OnOK()
{
	UpdateData(TRUE);

	CConfigManager::Inst()->PopWindow.PageItem.ColumnCount = m_nColCount;
	CConfigManager::Inst()->PopWindow.PageItem.RowCount = m_nRowCount;

 	CConfigManager::Inst()->Emoticons.Pages.RemoveAll();
 	for (POSITION posPage = m_emoticons.Pages.GetHeadPosition();
 		posPage != NULL;)
 	{
 		CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetNext(posPage);
		CConfigManager::_tag_emoticons::_tag_page newPage;
		newPage.Caption = curPage.Caption;

 		for (POSITION posItem = curPage.Items.GetHeadPosition();
 			posItem != NULL;)
 		{
 			CConfigManager::_tag_emoticons::_tag_page::_tag_item item = curPage.Items.GetNext(posItem);
 
 			newPage.Items.AddTail(item);
 		}

		CConfigManager::Inst()->Emoticons.Pages.AddTail(newPage);
 	}

	CConfigManager::Inst()->SaveConfig();

	CDialog::OnOK();
}

// find position in group list
POSITION CDlgEditEmoticons::getGroupPos(int nIndex)
{
	POSITION posCur = m_emoticons.Pages.GetHeadPosition();
	for (int i = 0;i < nIndex;i ++)
	{
		m_emoticons.Pages.GetNext(posCur);
	}

	return posCur;
}

// find position in item list
POSITION CDlgEditEmoticons::getEmoPos( int nIndex,CConfigManager::_tag_emoticons::_tag_page &curPage )
{
	POSITION posEmo = curPage.Items.GetHeadPosition();
	for (int i = 0;i < nIndex;i ++)
	{
		curPage.Items.GetNext(posEmo);
	}

	return posEmo;
}

// add a group, both data and interface
void CDlgEditEmoticons::addGroup( CString strName )
{
	int nCurSel = m_lbxGroup.GetCurSel();
	
	POSITION posCurGroup = getGroupPos(nCurSel);

	CConfigManager::_tag_emoticons::_tag_page apage;
	apage.Caption = strName;
	m_emoticons.Pages.InsertAfter(posCurGroup,apage);

	m_lbxGroup.InsertString(nCurSel + 1,strName);
	// select new item
	m_lbxGroup.SetCurSel(nCurSel + 1);
	OnLbnSelchangeListGroup();
}

// reload data and interface
void CDlgEditEmoticons::reloadData(CConfigManager::_tag_emoticons &emoticons)
{
	clearAll();

	for (POSITION posPage = emoticons.Pages.GetHeadPosition();
		posPage != NULL;)
	{
		CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetNext(posPage);

		addGroup(curPage.Caption);

		for (POSITION posItem = curPage.Items.GetHeadPosition();
			posItem != NULL;)
		{
			CConfigManager::_tag_emoticons::_tag_page::_tag_item item = curPage.Items.GetNext(posItem);

			addEmo(item.Content);
		}
	}

	if (m_emoticons.Pages.GetCount() > 0)
	{
		showEmoCtrlsVisible(TRUE);

		m_lbxGroup.SetCurSel(0);
		OnLbnSelchangeListGroup();
	}
}

// clear all data and interface
void CDlgEditEmoticons::clearAll()
{
	m_emoticons.Pages.RemoveAll();
	m_lbxGroup.ResetContent();
	m_lbxEmos.ResetContent();

	showEmoCtrlsVisible(FALSE);
}

// button add group
void CDlgEditEmoticons::OnBnClickedAddgroup()
{
	// 
	CDlgAddBatch dlg;
	if (dlg.DoModal() == IDOK)
	{
		// add first group, show all control
		if(m_lbxGroup.GetCount() == 0 && dlg.input.GetCount() > 0)
		{
			showEmoCtrlsVisible(TRUE);
		}

		for (POSITION pos = dlg.input.GetHeadPosition();pos != NULL;)
		{
			CString strGroup = dlg.input.GetNext(pos);
			addGroup(strGroup);
		}
	}
}

// button delete group
void CDlgEditEmoticons::OnBnClickedDelgroup()
{
	int nCur = m_lbxGroup.GetCurSel();
	
	if (nCur < 0)
	{
		return;
	}
	if(MessageBox(_T("确认删除？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
	{
		return ;
	}

	m_emoticons.Pages.RemoveAt(getGroupPos(nCur));

	m_lbxGroup.DeleteString(nCur);
	// if deleted item is last item, select last item, else select next item
	m_lbxGroup.SetCurSel(nCur >= m_lbxGroup.GetCount() ? m_lbxGroup.GetCount() - 1 : nCur);
	OnLbnSelchangeListGroup();

	// delete last item, hide control
	if(m_lbxGroup.GetCount() == 0)
	{
		showEmoCtrlsVisible(FALSE);
	}
}

// button modify group
void CDlgEditEmoticons::OnBnClickedModgroup()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	
	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	CDlgAddOne dlg(this,curPage.Caption);

	if (dlg.DoModal() == IDOK)
	{
		curPage.Caption = dlg.input;

		m_lbxGroup.DeleteString(nCur);
		m_lbxGroup.InsertString(nCur,dlg.input);

		m_lbxGroup.SetCurSel(nCur);
		OnLbnSelchangeListGroup();
	}
}

// button move left
void CDlgEditEmoticons::OnBnClickedLeftgroup()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}

	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);
	
	POSITION posPrev = pos;
	m_emoticons.Pages.GetPrev(posPrev);
	if (posPrev == NULL)
	{
		return ;
	}
	m_emoticons.Pages.InsertBefore(posPrev,curPage);
	m_emoticons.Pages.RemoveAt(pos);

	m_lbxGroup.DeleteString(nCur);
	m_lbxGroup.InsertString(nCur - 1,curPage.Caption);

	m_lbxGroup.SetCurSel(nCur - 1);
	OnLbnSelchangeListGroup();
}

// button move right
void CDlgEditEmoticons::OnBnClickedRightgroup()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}

	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	POSITION posPrev = pos;
	m_emoticons.Pages.GetNext(posPrev);
	if (posPrev == NULL)
	{
		return ;
	}
	m_emoticons.Pages.InsertAfter(posPrev,curPage);
	m_emoticons.Pages.RemoveAt(pos);

	m_lbxGroup.DeleteString(nCur);
	m_lbxGroup.InsertString(nCur + 1,curPage.Caption);

	m_lbxGroup.SetCurSel(nCur + 1);
	OnLbnSelchangeListGroup();
}

// list box select change
void CDlgEditEmoticons::OnLbnSelchangeListGroup()
{
	// 
	int nCur = m_lbxGroup.GetCurSel();
	if (nCur < 0)
	{
		return ;
	}

	POSITION posGroup = getGroupPos(nCur);

	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(posGroup);

	m_lbxEmos.ResetContent();
	for (POSITION pos = curPage.Items.GetHeadPosition();pos != NULL;)
	{
		CConfigManager::_tag_emoticons::_tag_page::_tag_item item = curPage.Items.GetNext(pos);

		m_lbxEmos.AddString(item.Content);
	}
}

// add emoticon, both data and interface
void CDlgEditEmoticons::addEmo( CString strEmo )
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	POSITION pos = getGroupPos(nCur);

	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	int nCurEmo = m_lbxEmos.GetCurSel();
	POSITION posEmo = getEmoPos(nCurEmo,curPage);

	CConfigManager::_tag_emoticons::_tag_page::_tag_item item;
	item.Content = strEmo;
	curPage.Items.InsertAfter(posEmo,item);

	m_lbxEmos.InsertString(nCurEmo + 1,strEmo);
}

// button add emoticon
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

// button delete emoticon
void CDlgEditEmoticons::OnBnClickedDelemo()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return ;
	}

// 	if(MessageBox(_T("确认删除？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
// 	{
// 		return ;
// 	}

	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	nCur = m_lbxEmos.GetCurSel();
	
	pos = getEmoPos(nCur,curPage);

	curPage.Items.RemoveAt(pos);
	m_lbxEmos.DeleteString(nCur);
	m_lbxEmos.SetCurSel(nCur >= m_lbxEmos.GetCount() ? m_lbxEmos.GetCount() - 1 : nCur);
}

// button modify emoticon
void CDlgEditEmoticons::OnBnClickedModemo()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	nCur = m_lbxEmos.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	pos = getEmoPos(nCur,curPage);
	CConfigManager::_tag_emoticons::_tag_page::_tag_item &curItem = curPage.Items.GetAt(pos);

	CDlgAddOne dlg(this,curItem.Content);

	if (dlg.DoModal() == IDOK)
	{
		curItem.Content = dlg.input;

		m_lbxEmos.DeleteString(nCur);
		m_lbxEmos.InsertString(nCur,curItem.Content);

		m_lbxEmos.SetCurSel(nCur);
	}
}

// button move left
void CDlgEditEmoticons::OnBnClickedLeftemo()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	nCur = m_lbxEmos.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	pos = getEmoPos(nCur,curPage);
	CConfigManager::_tag_emoticons::_tag_page::_tag_item curItem = curPage.Items.GetAt(pos);

	POSITION posPrev = pos;
	curPage.Items.GetPrev(posPrev);
	if (posPrev == NULL)
	{
		return ;
	}
	curPage.Items.InsertBefore(posPrev,curItem);
	curPage.Items.RemoveAt(pos);

	m_lbxEmos.DeleteString(nCur);
	m_lbxEmos.InsertString(nCur - 1,curItem.Content);

	m_lbxEmos.SetCurSel(nCur - 1);
}

// button move right
void CDlgEditEmoticons::OnBnClickedRightemo()
{
	int nCur = m_lbxGroup.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	POSITION pos = getGroupPos(nCur);
	CConfigManager::_tag_emoticons::_tag_page &curPage = m_emoticons.Pages.GetAt(pos);

	nCur = m_lbxEmos.GetCurSel();

	if (nCur < 0)
	{
		return;
	}
	pos = getEmoPos(nCur,curPage);
	CConfigManager::_tag_emoticons::_tag_page::_tag_item curItem = curPage.Items.GetAt(pos);

	POSITION posAfter = pos;
	curPage.Items.GetNext(posAfter);
	if (posAfter == NULL)
	{
		return ;
	}
	curPage.Items.InsertAfter(posAfter,curItem);
	curPage.Items.RemoveAt(pos);

	m_lbxEmos.DeleteString(nCur);
	m_lbxEmos.InsertString(nCur + 1,curItem.Content);

	m_lbxEmos.SetCurSel(nCur + 1);
}

void CDlgEditEmoticons::OnBnClickedExport()
{
	CDlgEmoticonFile dlg(this,TRUE,m_emoticons);
	dlg.DoModal();
}

void CDlgEditEmoticons::OnBnClickedImport()
{
	CDlgEmoticonFile dlg(this,FALSE,m_emoticons);
	if(dlg.DoModal() == IDOK)
	{
		reloadData(dlg.emoticons);
	}
}

void CDlgEditEmoticons::OnBnClickedClear()
{
	if(MessageBox(_T("确认清空？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
	{
		return ;
	}
	clearAll();
}

void CDlgEditEmoticons::OnBnClickedOk()
{
	OnOK();
}
