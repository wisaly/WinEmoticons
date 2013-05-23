// WinEmoticons.cpp
//

#include "stdafx.h"
#include "WinEmoticons.h"
#include "WinEmoticonsDlg.h"
#include "TestContainer.h"
#include "ConfigManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WE_MUTEX _T("WinEmoticonsApp")

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

	// global mutex
	m_hApp = ::CreateMutex(NULL,FALSE,WE_MUTEX);
	if(GetLastError()==ERROR_ALREADY_EXISTS)   
	{  
		AfxMessageBox(
			_T("Application already launched, WinEmoticons can only run once."),
			MB_OK|MB_ICONERROR);
		return FALSE;
	}

    CoInitialize(NULL);

    CConfigManager::Inst()->LoadConfig();

    // construct dialog after loadconfig
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

	CloseHandle(m_hApp);

    CoUninitialize();

	return FALSE;
}
