#pragma once


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
    CTabCtrl m_tabAll;
    CListBox m_lbxEmos;
    CButton m_btnAddEmo;
    CButton m_btnDelEmo;
    CButton m_btnModEmo;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

	DECLARE_MESSAGE_MAP()
};