// WinEmoticons.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include stdafx.h¡±before this to generate PCH file"
#endif

#include "resource.h"		//


// CWinEmoticonsApp:
//

class CWinEmoticonsApp : public CWinApp
{
public:
	CWinEmoticonsApp();

// 
	public:
	virtual BOOL InitInstance();

	HANDLE m_hApp;
// 

	DECLARE_MESSAGE_MAP()
};

extern CWinEmoticonsApp theApp;