// DlgEmoticonFile.cpp : 
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "DlgEmoticonFile.h"
#include "Xml.h"
#include "MsgBox.h"


// CDlgEmoticonFile 

IMPLEMENT_DYNAMIC(CDlgEmoticonFile, CDialog)

CDlgEmoticonFile::CDlgEmoticonFile(CWnd* pParent,BOOL bIsExport,CConfigManager::_tag_emoticons &emotions)
	: CDialog(CDlgEmoticonFile::IDD, pParent)
	,m_bIsExport(bIsExport)
	,m_emotions(emotions)
{

}

CDlgEmoticonFile::~CDlgEmoticonFile()
{
}

void CDlgEmoticonFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTHOR, m_editAuthor);
	DDX_Control(pDX, IDC_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_INFO, m_editInfo);
	DDX_Control(pDX, IDC_FILE_PATH, m_editFilePath);
}


BEGIN_MESSAGE_MAP(CDlgEmoticonFile, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgEmoticonFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SELFILE, &CDlgEmoticonFile::OnBnClickedSelfile)
END_MESSAGE_MAP()


// CDlgEmoticonFile 


void CDlgEmoticonFile::calcInfo(CConfigManager::_tag_emoticons &emoticons)
{
	int nTotalEmoticons = 0;
	for (POSITION pos = emoticons.Pages.GetHeadPosition();
		pos != NULL;)
	{
		nTotalEmoticons += emoticons.Pages.GetNext(pos).Items.GetCount();
	}

	CString strInfo;
	strInfo.Format(_T("共%d个分组，%d个单词"),
		emoticons.Pages.GetCount(),nTotalEmoticons);
	m_editInfo.SetWindowText(strInfo);
}

BOOL CDlgEmoticonFile::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 
	if (m_bIsExport)
	{
		this->SetWindowText(_T("导出"));
		this->SetDlgItemText(IDOK,_T("导出"));

		// calc total emoticons
		calcInfo(m_emotions);


		// default file name
		CTime tmNow = CTime::GetCurrentTime();
		
		strFilePath.Format(_T("%s\\WEExp%04d%02d%02d%02d%02d%02d.txt"),
			CXml::GetApplicationPath(),
			tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay(),
			tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());

		m_editFilePath.SetWindowText(strFilePath);
	}
	else
	{
		this->SetWindowText(_T("导入"));
		this->SetDlgItemText(IDOK,_T("导入"));
		m_editInfo.SetWindowText(_T(""));

		m_editAuthor.SetReadOnly(TRUE);
		m_editTitle.SetReadOnly(TRUE);
		
		m_editFilePath.SetWindowText(strFilePath);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgEmoticonFile::OnBnClickedSelfile()
{
	m_editFilePath.GetWindowText(strFilePath);

	CFileDialog dlg(!m_bIsExport,_T("txt"),strFilePath,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("文本文件(*.txt)|*.txt||所有文件(*.*)|*.*||"),
		this);

	if (dlg.DoModal() == IDOK)
	{
		m_editFilePath.SetWindowText(dlg.GetPathName());


		if (!m_bIsExport)
		{
			CString strAuthor;
			CString strTitle;
			if(!CConfigManager::ImportEmoticons(emoticons,dlg.GetPathName(),strAuthor,strTitle))
			{
				CMsgBox::Error(_T("文件无法读取或格式不正确"),this);
				return;
			}

			m_editAuthor.SetWindowText(strAuthor);
			m_editTitle.SetWindowText(strTitle);

			calcInfo(emoticons);
		}
	}
}


void CDlgEmoticonFile::OnBnClickedOk()
{
	CString strAuthor;
	CString strTitle;
	m_editFilePath.GetWindowText(strFilePath);
	m_editAuthor.GetWindowText(strAuthor);
	m_editTitle.GetWindowText(strTitle);

	if (m_bIsExport)
	{
		if(CConfigManager::ExportEmoticons(m_emotions,strFilePath,strAuthor,strTitle))
		{
			CMsgBox::Info(_T("导出成功"),this);
		}
		else
		{
			CMsgBox::Error(_T("导出失败"),this);
		}
	}
	else
	{
		
	}

	OnOK();
}