#include "DlgPopup.h"
// WinEmoticonsDlg.h : 头文件
//

#pragma once


// CWinEmoticonsDlg 对话框
class CWinEmoticonsDlg : public CDialog
{
// 构造
public:
	CWinEmoticonsDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CWinEmoticonsDlg();

// 对话框数据
	enum { IDD = IDD_WINEMOTICONS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDlgPopup m_dlgPopup;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
