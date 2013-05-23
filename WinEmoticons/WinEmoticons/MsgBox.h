#pragma once

class CMsgBox
{
private:
    CMsgBox();

public:
    static void Error(CString strMsg,HWND hwndParent = NULL);
    static void Info(CString strMsg,HWND hwndParent = NULL);
};