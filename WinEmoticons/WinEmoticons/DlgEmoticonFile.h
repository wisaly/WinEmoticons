#pragma once
#include "afxwin.h"
#include "ConfigManager.h"


// CDlgEmoticonFile 

class CDlgEmoticonFile : public CDialog
{
	DECLARE_DYNAMIC(CDlgEmoticonFile)

public:
	CDlgEmoticonFile(CWnd* pParent,BOOL bIsExport,CConfigManager::_tag_emoticons &emotions);   // 
	virtual ~CDlgEmoticonFile();
	CString strFilePath;
	CConfigManager::_tag_emoticons emoticons;
// 
	enum { IDD = IDD_EMOTICON_FILE };

protected:
	CConfigManager::_tag_emoticons &m_emotions;
	BOOL m_bIsExport;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void calcInfo(CConfigManager::_tag_emoticons &emoticons);
	CEdit m_editAuthor;
	CEdit m_editTitle;
	CStatic m_editInfo;
	CEdit m_editFilePath;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSelfile();
};
