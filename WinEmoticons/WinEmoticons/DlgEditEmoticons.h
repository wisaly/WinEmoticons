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
    CTabCtrl m_tabGroup;
    CListBox m_lbxEmos;
    CButton m_btnAddEmo;
    CButton m_btnDelEmo;
    CButton m_btnModEmo;
    void showEmoCtrlsVisible(BOOL bVisble);

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
};