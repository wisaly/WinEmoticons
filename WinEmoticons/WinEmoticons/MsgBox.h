#pragma once

class CMsgBox
{
private:
    CMsgBox();

public:
    static void Error(CString strMsg,CWnd *pParent = NULL);
    static void Info(CString strMsg,CWnd *pParent = NULL);
};