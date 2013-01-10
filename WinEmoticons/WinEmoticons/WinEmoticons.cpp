// WinEmoticons.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WinEmoticonsDlg.h"
#include "TestContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinEmoticonsApp

BEGIN_MESSAGE_MAP(CWinEmoticonsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CWinEmoticonsApp::CWinEmoticonsApp()
{
}


CWinEmoticonsApp theApp;


// CWinEmoticonsApp

BOOL CWinEmoticonsApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CWinEmoticonsDlg dlg;
	//CTestContainer dlg;
	//m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}
