#pragma once
#include "afxwin.h"
#include "ConfigManager.h"


// CDlgEditEmoticons

class CDlgEditEmoticons : public CDialog
{
	DECLARE_DYNAMIC(CDlgEditEmoticons)

public:
	CDlgEditEmoticons(CWnd* pParent = NULL);   // 
	virtual ~CDlgEditEmoticons();

// 
	enum { IDD = IDD_EDIT_EMOTICONS };

protected:
    CTabCtrl m_tabGroup;
    CListBox m_lbxEmos;
    CButton m_btnAddEmo;
    CButton m_btnDelEmo;
	CButton m_btnModEmo;
	CButton m_btnLeftEmo;
	CButton m_btnRightEmo;
	CButton m_btnDelGroup;
	CButton m_btnRenGroup;
	CButton m_btnLeftGroup;
	CButton m_btnRightGroup;
	CConfigManager::_tag_emoticons m_emotions;
	void showEmoCtrlsVisible(BOOL bVisble);
	POSITION getGroupPos(int nIndex);
	void addGroup(CString strName);
	void delGroup(int nCur);
	void addEmo(CString strEmo);
	POSITION getEmoPos(int nIndex,,CConfigManager::_tag_emoticons::_tag_page &curPage);

    void OnBtnAddGroup();
    void OnBtnDelGroup();
    void OnBtnModGroup();
    void OnBtnAddEmo();
    void OnBtnDelEmo();
    void OnBtnModEmo();
    void OnOK();

    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editRow;
	CEdit m_editCol;
	afx_msg void OnBnClickedAddgroup();
	afx_msg void OnBnClickedDelgroup();

	afx_msg void OnBnClickedModgroup();
	afx_msg void OnBnClickedLeftgroup();
	afx_msg void OnBnClickedRightgroup();
	afx_msg void OnBnClickedAddemo();
	afx_msg void OnTcnSelchangeTabGroup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelemo();
};