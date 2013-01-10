// TestContainer.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "TestContainer.h"


// CTestContainer

IMPLEMENT_DYNAMIC(CTestContainer, CDialog)

CTestContainer::CTestContainer(CWnd* pParent /*=NULL*/)
	: CDialog(CTestContainer::IDD, pParent)
{

}

CTestContainer::~CTestContainer()
{
}

void CTestContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestContainer, CDialog)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()


// CTestContainer

BOOL CTestContainer::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	CRect rcClient;
	m_wndWETabCtrl.GetClientRect(&rcClient);
	m_wndWETabCtrl.Create(rcClient,this,1);;
	m_wndWETabCtrl.ShowWindow(SW_SHOW);


	CWETabPage *pg1 = m_wndWETabCtrl.AppendPage(_T("Page"));

	pg1->AppendItem(_T("Item1"));
	pg1->AppendItem(_T("Item2"));
	pg1->AppendItem(_T("Item3"));
	pg1->AppendItem(_T("Item4"));
	pg1->AppendItem(_T("Item5"));
	pg1->AppendItem(_T("Item6"));
	pg1->AppendItem(_T("Item1"));
	pg1->AppendItem(_T("Item2"));
	pg1->AppendItem(_T("Item3"));
	pg1->AppendItem(_T("Item4"));
	pg1->AppendItem(_T("Item5"));
	pg1->AppendItem(_T("Item6"));

	return TRUE;
}

void CTestContainer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (nType == SIZE_RESTORED && m_wndWETabCtrl.GetSafeHwnd() != NULL)
	{
		CRect rcCtrl(0,0,cx,cy);

		m_wndWETabCtrl.MoveWindow(rcCtrl,TRUE);
	}
}

void CTestContainer::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CDialog::OnNcLButtonUp(nHitTest, point);
	if (nHitTest == HTCAPTION)
	{
		CWETabPage *pg1 = m_wndWETabCtrl.AppendPage(_T("Page"));

		pg1->AppendItem(_T("Item1"));
		pg1->AppendItem(_T("Item2"));
		pg1->AppendItem(_T("Item3"));
		pg1->AppendItem(_T("Item4"));
		pg1->AppendItem(_T("Item5"));
		pg1->AppendItem(_T("Item6"));
		pg1->AppendItem(_T("Item1"));
		pg1->AppendItem(_T("Item2"));
		pg1->AppendItem(_T("Item3"));
		pg1->AppendItem(_T("Item4"));
		pg1->AppendItem(_T("Item5"));
		pg1->AppendItem(_T("Item6"));
	}
}
