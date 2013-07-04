#include "stdafx.h"
#include "ConfigManager.h"
#include "Xml.h"
#include "StdioFileEx.h"

CConfigManager * CConfigManager::Inst()
{
	static CConfigManager inst;
	return &inst;
}

CConfigManager::CConfigManager()
{
	configFilePath = CXml::GetApplicationPath() + _T("\\WEConfig.xml");
	IsOnConfig = FALSE;
}

#pragma comment(lib,"version.lib")
CString CConfigManager::Version()
{
	TCHAR szFullPath[MAX_PATH];
    DWORD dwVerInfoSize = 0;
    DWORD dwVerHnd;
    VS_FIXEDFILEINFO * pFileInfo;
   
    GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
    dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
    if (dwVerInfoSize)
    {
        // If we were able to get the information, process it:
        HANDLE  hMem;
        LPVOID  lpvMem;
        unsigned int uInfoSize = 0;
       
        hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
        lpvMem = GlobalLock(hMem);
        GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
       
        ::VerQueryValue(lpvMem, (LPCTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);
       
        int ret = GetLastError();
        WORD nProdVersion[4];
       
        // Product version from the FILEVERSION of the version info resource
        nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS);
        nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
        nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
        nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS);
       
        CString strVersion ;
        strVersion.Format(_T("Ver.%d.%d.%d.%d"),
			nProdVersion[0],nProdVersion[1],
			nProdVersion[2],nProdVersion[3]);
       
        GlobalUnlock(hMem);
        GlobalFree(hMem);
       
        return strVersion;
    }
	return _T("-");
}

BOOL CConfigManager::LoadConfig()
{
	CXml xml;
	if (!xml.Open(configFilePath))
	{
		SaveConfig();
		return FALSE;
	}

	CXmlNodePtr pRoot = xml.GetRoot();
	
    CString s = pRoot->GetName();
	// ConfigWindow
	CXmlNodePtr pConfigWindow = pRoot->GetChild(_T("ConfigWindow"));
	this->ConfigWindow.PopAtStart = pConfigWindow->GetAttribute(_T("PopAtStart"),false);

	// AccerateKey
	CXmlNodePtr pAccerateKey = pRoot->GetChild(_T("AccerateKey"));
	this->AccerateKey.PopSelect = pAccerateKey->GetAttribute(_T("PopSelect"));

	// PopWindow
	CXmlNodePtr pPopWindow = pRoot->GetChild(_T("PopWindow"));
	this->PopWindow.CtrlPadding = pPopWindow->GetAttribute(_T("CtrlPadding"),int(0));
	this->PopWindow.FontSize = pPopWindow->GetAttribute(_T("FontSize"),int(0));
	this->PopWindow.FontName = pPopWindow->GetAttribute(_T("FontName"));
	this->PopWindow.Width = pPopWindow->GetAttribute(_T("Width"),int(100));
	this->PopWindow.Height = pPopWindow->GetAttribute(_T("Height"),int(50));

	// PopWindow.PageHeader
	CXmlNodePtr pPageHeader = pPopWindow->GetChild(_T("PageHeader"));
	this->PopWindow.PageHeader.HeaderHeight = pPageHeader->GetAttribute(_T("HeaderHeight"),int(0));
	this->PopWindow.PageHeader.HeaderHorzMargin = pPageHeader->GetAttribute(_T("HeaderHorzMargin"),int(0));
	this->PopWindow.PageHeader.HeaderTopMargin = pPageHeader->GetAttribute(_T("HeaderTopMargin"),int(0));
	this->PopWindow.PageHeader.HeaderActiveHorzMargin = pPageHeader->GetAttribute(_T("HeaderActiveHorzMargin"),int(0));
	this->PopWindow.PageHeader.HeaderActiveTopMargin = pPageHeader->GetAttribute(_T("HeaderActiveTopMargin"),int(0));
	this->PopWindow.PageHeader.PagePadding = pPageHeader->GetAttribute(_T("PagePadding"),int(0));
	// PopWindow.Pages
	CXmlNodePtr pPages = pPopWindow->GetChild(_T("Pages"));
	this->PopWindow.Pages.Colors.RemoveAll();
	CXmlNodesPtr pColors = pPages->GetChild(_T("Colors"))->GetChildren();
	for (int i = 0;i < pColors->GetCount();i ++)
	{
		this->PopWindow.Pages.Colors.AddTail((*pColors)[i]->GetAttribute(_T("rgb"),COLORREF(0)));
	}
	// PopWindow.PageItem
	CXmlNodePtr pPageItem = pPopWindow->GetChild(_T("PageItem"));
	this->PopWindow.PageItem.ItemPadding = pPageItem->GetAttribute(_T("ItemPadding"),int(0));
	this->PopWindow.PageItem.ColumnCount = pPageItem->GetAttribute(_T("ColumnCount"),int(1));  // use default to avoid deviding by 0
	this->PopWindow.PageItem.RowCount = pPageItem->GetAttribute(_T("RowCount"),int(1));        // 
	this->PopWindow.PageItem.Colors.Background = pPageItem->GetChild(_T("Colors"))->GetAttribute(_T("Background"),COLORREF(0));
	this->PopWindow.PageItem.Colors.Foreground = pPageItem->GetChild(_T("Colors"))->GetAttribute(_T("Foreground"),COLORREF(0));
	this->PopWindow.PageItem.Colors.Hightlight = pPageItem->GetChild(_T("Colors"))->GetAttribute(_T("Hightlight"),COLORREF(0));
	this->PopWindow.PageItem.Colors.Checked = pPageItem->GetChild(_T("Colors"))->GetAttribute(_T("Checked"),COLORREF(0));
	this->PopWindow.PageItem.Colors.Disabled = pPageItem->GetChild(_T("Colors"))->GetAttribute(_T("Disabled"),COLORREF(0));
	
	// Emoticons
	CXmlNodePtr pEmoticons = pRoot->GetChild(_T("Emoticons"));
	this->Emoticons.Pages.RemoveAll();
	CXmlNodesPtr pEmoticonPages = pEmoticons->GetChild(_T("Pages"))->GetChildren();
	for (int i = 0;i < pEmoticonPages->GetCount();i ++)
	{
		_tag_emoticons::_tag_page page;
		page.Caption = (*pEmoticonPages)[i]->GetAttribute(_T("Caption"));

		CXmlNodesPtr pItems = (*pEmoticonPages)[i]->GetChildren();
		for (int j = 0;j < pItems->GetCount();j ++)
		{
			_tag_emoticons::_tag_page::_tag_item item;
			item.Content = (*pItems)[j]->GetAttribute(_T("Content"));
			page.Items.AddTail(item);
		}

		this->Emoticons.Pages.AddTail(page);
	}

	return TRUE;
}

BOOL CConfigManager::SaveConfig()
{
	CXml xml;
	if (!xml.Open(configFilePath))
	{
		if (xml.Create(configFilePath))
		{
			return FALSE;
		}

		xml.SetXmlText(_T("<WEConfig/>"));
	}

	CXmlNodePtr pRoot = xml.GetRoot();
	pRoot->RemoveChildren();

	// ConfigWindow
	CXmlNodePtr pConfigWindow = pRoot->AppendChild(_T("ConfigWindow"));
	pConfigWindow->SetAttribute(_T("PopAtStart"),(bool)this->ConfigWindow.PopAtStart);

	// AccerateKey
	CXmlNodePtr pAccerateKey = pRoot->AppendChild(_T("AccerateKey"));
	pAccerateKey->SetAttribute(_T("PopSelect"),this->AccerateKey.PopSelect);

	// PopWindow
	CXmlNodePtr pPopWindow = pRoot->AppendChild(_T("PopWindow"));
	pPopWindow->SetAttribute(_T("CtrlPadding"),this->PopWindow.CtrlPadding);
	pPopWindow->SetAttribute(_T("FontSize"),this->PopWindow.FontSize);
	pPopWindow->SetAttribute(_T("FontName"),this->PopWindow.FontName);
	pPopWindow->SetAttribute(_T("Width"),this->PopWindow.Width);
	pPopWindow->SetAttribute(_T("Height"),this->PopWindow.Height);
	

	// PopWindow.PageHeader
	CXmlNodePtr pPageHeader = pPopWindow->AppendChild(_T("PageHeader"));
	pPageHeader->SetAttribute(_T("HeaderHeight"),this->PopWindow.PageHeader.HeaderHeight);
	pPageHeader->SetAttribute(_T("HeaderHorzMargin"),this->PopWindow.PageHeader.HeaderHorzMargin);
	pPageHeader->SetAttribute(_T("HeaderTopMargin"),this->PopWindow.PageHeader.HeaderTopMargin);
	pPageHeader->SetAttribute(_T("HeaderActiveHorzMargin"),this->PopWindow.PageHeader.HeaderActiveHorzMargin);
	pPageHeader->SetAttribute(_T("HeaderActiveTopMargin"),this->PopWindow.PageHeader.HeaderActiveTopMargin);
	pPageHeader->SetAttribute(_T("PagePadding"),this->PopWindow.PageHeader.PagePadding);
	// PopWindow.Pages
	CXmlNodePtr pPages = pPopWindow->AppendChild(_T("Pages"));
    CXmlNodePtr pColors = pPages->AppendChild(_T("Colors"));
	
	for (POSITION pos = this->PopWindow.Pages.Colors.GetHeadPosition();pos != NULL;)
	{
		pColors->AppendChild(_T("Color"))->SetAttribute(_T("rgb"),this->PopWindow.Pages.Colors.GetNext(pos));
	}
	// PopWindow.PageItem
	CXmlNodePtr pPageItem = pPopWindow->AppendChild(_T("PageItem"));
	pPageItem->SetAttribute(_T("ItemPadding"),this->PopWindow.PageItem.ItemPadding);
	pPageItem->SetAttribute(_T("ColumnCount"),this->PopWindow.PageItem.ColumnCount);
	pPageItem->SetAttribute(_T("RowCount"),this->PopWindow.PageItem.RowCount);
	pPageItem->AppendChild(_T("Colors"))->SetAttribute(_T("Background"),this->PopWindow.PageItem.Colors.Background);
	pPageItem->AppendChild(_T("Colors"))->SetAttribute(_T("Foreground"),this->PopWindow.PageItem.Colors.Foreground);
	pPageItem->AppendChild(_T("Colors"))->SetAttribute(_T("Hightlight"),this->PopWindow.PageItem.Colors.Hightlight);
	pPageItem->AppendChild(_T("Colors"))->SetAttribute(_T("Checked"),this->PopWindow.PageItem.Colors.Checked);
	pPageItem->AppendChild(_T("Colors"))->SetAttribute(_T("Disabled"),this->PopWindow.PageItem.Colors.Disabled);

	// Emoticons
	CXmlNodePtr pEmoticons = pRoot->AppendChild(_T("Emoticons"));
	
	CXmlNodePtr pEmoticonPages = pEmoticons->AppendChild(_T("Pages"));
	for (POSITION pos = this->Emoticons.Pages.GetHeadPosition();pos != NULL;)
	{
		_tag_emoticons::_tag_page &page = this->Emoticons.Pages.GetNext(pos);
		CXmlNodePtr pPage = pEmoticonPages->AppendChild(_T("Page"));
		pPage->SetAttribute(_T("Caption"),page.Caption);
		
		for (POSITION posItem = page.Items.GetHeadPosition();posItem != NULL;)
		{
			_tag_emoticons::_tag_page::_tag_item &item = page.Items.GetNext(posItem);
			pPage->AppendChild(_T("Item"))->SetAttribute(_T("Content"),item.Content);
		}
	}

	return xml.Save();
}

BOOL CConfigManager::ParseCombineKeys( CString strComKeys,UINT &nModifier,UINT &nVKey )
{
    // make lower to calc
    strComKeys = strComKeys.MakeLower();

    // detect modifier
    nModifier = 0;
    if (strComKeys.Find(_T("ctrl+")) >= 0)
    {
        nModifier |= MOD_CONTROL;
        strComKeys.Replace(_T("ctrl+"),_T(""));
    }
    if (strComKeys.Find(_T("alt+")) >= 0)
    {
        nModifier |= MOD_ALT;
        strComKeys.Replace(_T("alt+"),_T(""));
    }
    if (strComKeys.Find(_T("shift+")) >= 0)
    {
        nModifier |= MOD_SHIFT;
        strComKeys.Replace(_T("shift+"),_T(""));
    }
    if (strComKeys.Find(_T("win+")) >= 0)
    {
        nModifier |= MOD_WIN;
        strComKeys.Replace(_T("win+"),_T(""));
    }

    // vkey
    nVKey = translateVKey(strComKeys);
    
    return (nModifier == 0 && nVKey == 0) ? FALSE : TRUE;
}
CString CConfigManager::translateVKey( int nVKey,CString strNullString /*= _T("")*/ )
{
    switch(nVKey)
    {
// 	case 0x01 : // vk_lbutton  left mouse button  
// 		return "lbutton";
// 	case 0x02 : // vk_rbutton  right mouse button  
// 		return "rbutton";
// 	case 0x03 : // vk_cancel  control-break processing  
// 		return "cancel";
// 	case 0x04 : // vk_mbutton  middle mouse button (three-button mouse)  
// 		return "mbutton";
// 		//〞05每07 undefined  
    case 0x08 : // vk_back  backspace key  
        return _T("backspace");
    case 0x09 : // vk_Tab  tab key  
        return _T("tab");
//〞0a每0b undefined  
// 	case 0x0c : // vk_clear  clear key  
// 		return _T("clear");
    case 0x0d : // vk_return  enter key  
        return _T("return");
//〞0e每0f undefined  
// 	case 0x10 : // vk_shift  shift key  
// 		return _T("shift");
// 	case 0x11 : // vk_control  ctrl key  
// 		return _T("ctrl");
// 	case 0x12 : // vk_menu  alt key  
// 		return _T("alt");
    case 0x13 : // vk_pause  pause key  
        return _T("pause");
// 	case 0x14 : // vk_capital  caps lock key  
// 		return _T("capital");
//〞15每19 reserved for kanji systems  
//〞1a undefined  
    case 0x1b : // vk_escape  esc key  
        return _T("escape");
    //〞1c每1f reserved for kanji systems  
    case 0x20 : // vk_space  spacebar  
        return _T("space");
    case 0x21 : // vk_prior  page up key  
        return _T("pgup");
    case 0x22 : // vk_next  page down key  
        return _T("pgdn");
    case 0x23 : // vk_end  end key  
        return _T("end");
    case 0x24 : // vk_home  home key  
        return _T("home");
    case 0x25 : // vk_left  left arrow key  
        return _T("left");
    case 0x26 : // vk_up  up arrow key  
        return _T("up");
    case 0x27 : // vk_right  right arrow key  
        return _T("right");
    case 0x28 : // vk_down  down arrow key  
        return _T("down");
// 	case 0x29 : // vk_select  select key  
// 		return _T("select");
//〞2a original equipment manufacturer (oem) specific  
// 	case 0x2b : // vk_execute  execute key  
// 		return _T("execute");
    case 0x2c : // vk_snapshot  print screen key  
        return _T("prtscn");
    case 0x2d : // vk_insert  ins key  
        return _T("insert");
    case 0x2e : // vk_delete  del key  
        return _T("delete");
// 	case 0x2f : // vk_help  help key  
// 		return _T("help");
    case 0x30 : // vk_0  0 key  
        return _T("0");
    case 0x31 : // vk_1  1 key  
        return _T("1");
    case 0x32 : // vk_2  2 key  
        return _T("2");
    case 0x33 : // vk_3  3 key  
        return _T("3");
    case 0x34 : // vk_4  4 key  
        return _T("4");
    case 0x35 : // vk_5  5 key  
        return _T("5");
    case 0x36 : // vk_6  6 key  
        return _T("6");
    case 0x37 : // vk_7  7 key  
        return _T("7");
    case 0x38 : // vk_8  8 key  
        return _T("8");
    case 0x39 : // vk_9  9 key  
        return _T("9");
    //〞3a每40 undefined  
    case 0x41 : // vk_a  a key  
        return _T("a");
    case 0x42 : // vk_b  b key  
        return _T("b");
    case 0x43 : // vk_c  c key  
        return _T("c");
    case 0x44 : // vk_d  d key  
        return _T("d");
    case 0x45 : // vk_e  e key  
        return _T("e");
    case 0x46 : // vk_f  f key  
        return _T("f");
    case 0x47 : // vk_g  g key  
        return _T("g");
    case 0x48 : // vk_h  h key  
        return _T("h");
    case 0x49 : // vk_i  i key  
        return _T("i");
    case 0x4a : // vk_j  j key  
        return _T("j");
    case 0x4b : // vk_k  k key  
        return _T("k");
    case 0x4c : // vk_l  l key  
        return _T("l");
    case 0x4d : // vk_m  m key  
        return _T("m");
    case 0x4e : // vk_n  n key  
        return _T("n");
    case 0x4f : // vk_o  o key  
        return _T("o");
    case 0x50 : // vk_p  p key  
        return _T("p");
    case 0x51 : // vk_q  q key  
        return _T("q");
    case 0x52 : // vk_r  r key  
        return _T("r");
    case 0x53 : // vk_s  s key  
        return _T("s");
    case 0x54 : // vk_T  t key  
        return _T("t");
    case 0x55 : // vk_u  u key  
        return _T("u");
    case 0x56 : // vk_v  v key  
        return _T("v");
    case 0x57 : // vk_w  w key  
        return _T("w");
    case 0x58 : // vk_x  x key  
        return _T("x");
    case 0x59 : // vk_y  y key  
        return _T("y");
    case 0x5a : // vk_z  z key  
        return _T("z");
// 	case 0x5b : // vk_lwin  left windows key (microsoft natural keyboard)  
// 		return _T("lwin");
// 	case 0x5c : // vk_rwin  right windows key (microsoft natural keyboard)  
// 		return _T("rwin");
// 	case 0x5d : // vk_apps  applications key (microsoft natural keyboard)  
// 		return _T("apps");
//〞5e每5f undefined  
    case 0x60 : // vk_numpad0  numeric keypad 0 key  
        return _T("numpad0");
    case 0x61 : // vk_numpad1  numeric keypad 1 key  
        return _T("numpad1");
    case 0x62 : // vk_numpad2  numeric keypad 2 key  
        return _T("numpad2");
    case 0x63 : // vk_numpad3  numeric keypad 3 key  
        return _T("numpad3");
    case 0x64 : // vk_numpad4  numeric keypad 4 key  
        return _T("numpad4");
    case 0x65 : // vk_numpad5  numeric keypad 5 key  
        return _T("numpad5");
    case 0x66 : // vk_numpad6  numeric keypad 6 key  
        return _T("numpad6");
    case 0x67 : // vk_numpad7  numeric keypad 7 key  
        return _T("numpad7");
    case 0x68 : // vk_numpad8  numeric keypad 8 key  
        return _T("numpad8");
    case 0x69 : // vk_numpad9  numeric keypad 9 key  
        return _T("numpad9");
    case 0x6a : // vk_multiply  multiply key  
        return _T("numpad*");
    case 0x6b : // vk_add  add key  
        return _T("numpad+");
    case 0x6c : // vk_separator  separator key  
        return _T("separator");
    case 0x6d : // vk_subtract  subtract key  
        return _T("numpad-");
    case 0x6e : // vk_decimal  decimal key  
        return _T("numpad.");
    case 0x6f : // vk_divide  divide key  
        return _T("numpad/");
    case 0x70 : // vk_f1  f1 key  
        return _T("f1");
    case 0x71 : // vk_f2  f2 key  
        return _T("f2");
    case 0x72 : // vk_f3  f3 key  
        return _T("f3");
    case 0x73 : // vk_f4  f4 key  
        return _T("f4");
    case 0x74 : // vk_f5  f5 key  
        return _T("f5");
    case 0x75 : // vk_f6  f6 key  
        return _T("f6");
    case 0x76 : // vk_f7  f7 key  
        return _T("f7");
    case 0x77 : // vk_f8  f8 key  
        return _T("f8");
    case 0x78 : // vk_f9  f9 key  
        return _T("f9");
    case 0x79 : // vk_f10  f10 key  
        return _T("f10");
    case 0x7a : // vk_f11  f11 key  
        return _T("f11");
    case 0x7b : // vk_f12  f12 key  
        return _T("f12");
    case 0x7c : // vk_f13  f13 key  
        return _T("f13");
    case 0x7d : // vk_f14  f14 key  
        return _T("f14");
    case 0x7e : // vk_f15  f15 key  
        return _T("f15");
    case 0x7f : // vk_f16  f16 key  
        return _T("f16");
    case 0x80 : // vk_f17  f17 key  
        return _T("f17");
    case 0x81 : // vk_f18  f18 key  
        return _T("f18");
    case 0x82 : // vk_f19  f19 key  
        return _T("f19");
    case 0x83 : // vk_f20  f20 key  
        return _T("f20");
    case 0x84 : // vk_f21  f21 key  
        return _T("f21");
    case 0x85 : // vk_f22  f22 key  
        return _T("f22");
    case 0x86 : // vk_f23  f23 key  
        return _T("f23");
    case 0x87 : // vk_f24  f24 key  
        return _T("f24");
//〞88每8f unassigned  
// 	case 0x90 : // vk_numlock  num lock key  
// 		return _T("numlock");
// 	case 0x91 : // vk_scroll  scroll lock key  
// 		return _T("scroll");
// 	case 0xa0 : // vk_lshift         
// 		return _T("lshift");
// 	case 0xa1 : // vk_rshift         
// 		return _T("rshift");
// 	case 0xa2 : // vk_lcontrol       
// 		return _T("lctrl");
// 	case 0xa3 : // vk_rcontrol       
// 		return _T("rctrl");
// 	case 0xa4 : // vk_lmenu          
// 		return _T("lalt");
// 	case 0xa5 : // vk_rmenu          
// 		return _T("ralt");
//〞92每b9 unassigned  
//〞ba每c0 oem specific  
//〞c1每da unassigned  
//〞db每e4 oem specific  
//〞e5 unassigned  
//〞e6 oem specific  
//〞e7每e8 unassigned  
//〞e9每f5 oem specific  
// 	case 0xf6 : // vk_attn  attn key 
// 		return _T("attn");
// 	case 0xf7 : // vk_crsel  crsel key 
// 		return _T("crsel");
// 	case 0xf8 : // vk_exsel  exsel key 
// 		return _T("exsel");
// 	case 0xf9 : // vk_ereof  erase eof key 
// 		return _T("ereof");
// 	case 0xfa : // vk_play  play key 
// 		return _T("play");
// 	case 0xfb : // vk_zoom  zoom key 
// 		return _T("zoom");
// 	case 0xfc : // vk_noname  reserved for future use.  
// 		return _T("noname");
// 	case 0xfd : // vk_pa1  pa1 key 
// 		return _T("pa1");
// 	case 0xfe : // vk_oem_clear  clear key 
// 		return _T("clear");
    }

    return strNullString;
}

int CConfigManager::translateVKey( CString strKey )
{
    for (int i = 0;i < 0xff;i ++)
    {
        if (translateVKey(i) == strKey)
        {
            return i;
        }
    }

    return 0;
}


#define EXPORT_SEP_LINE _T("==================================================")
#define EXPORT_TITLE _T("WinEmoticons Dictionary File")
#define WriteLine(x) WriteString((x) + CString(sNEWLINE))

BOOL CConfigManager::ExportEmoticons( _tag_emoticons &emoticons,CString &strFilePath,CString &strAuthor,CString &strTitle )
{
	CStdioFileEx file;

	if (!file.Open(strFilePath,CFile::modeCreate| CFile::modeWrite | CFile::typeText | CStdioFileEx::modeWriteUnicode))
	{
		return FALSE;
	}

	CTime tmNow = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay(),
		tmNow.GetHour(),tmNow.GetMinute(),tmNow.GetSecond());

	// write header
	file.WriteLine(EXPORT_SEP_LINE);
	file.WriteLine(EXPORT_TITLE);
	file.WriteLine(CConfigManager::Version());
	file.WriteLine(strTime);
	file.WriteLine(EXPORT_SEP_LINE);
	
	// write author,title
	if (strAuthor.IsEmpty())
	{
		strAuthor = _T("Anonymous");
	}
	if (strTitle.IsEmpty())
	{
		strTitle = _T("Unmarked");
	}
	file.WriteLine(strAuthor);
	file.WriteLine(strTitle);
	file.WriteLine(EXPORT_SEP_LINE);

	for (POSITION posPage = emoticons.Pages.GetHeadPosition();
		posPage != NULL;)
	{
		CConfigManager::_tag_emoticons::_tag_page &curPage = emoticons.Pages.GetNext(posPage);

		// write group
		file.WriteLine(curPage.Caption);

		for (POSITION posItem = curPage.Items.GetHeadPosition();
			posItem != NULL;)
		{
			CConfigManager::_tag_emoticons::_tag_page::_tag_item item = curPage.Items.GetNext(posItem);

			// write item
			file.WriteLine(item.Content);
		}

		file.WriteLine(EXPORT_SEP_LINE);
	}

	file.Close();

	return TRUE;
}
#undef WriteLine

BOOL CConfigManager::ImportEmoticons( _tag_emoticons &emoticons,CString &strFilePath,CString &strAuthor,CString &strTitle )
{
	emoticons.Pages.RemoveAll();

	CStdioFileEx file;

	if (!file.Open(strFilePath,CFile::modeRead|CFile::typeText))
	{
		return FALSE;
	}

	CString strRead;
	// read header
	file.ReadString(strRead);
	file.ReadString(strRead);
	file.ReadString(strRead);
	file.ReadString(strRead);
// 	if (strRead != CConfigManager::Version())
// 	{
// 		return FALSE;
// 	}
	file.ReadString(strRead);

	// write author,title
	file.ReadString(strAuthor);
	file.ReadString(strTitle);
	file.ReadString(strRead);

	if (strRead != EXPORT_SEP_LINE)
	{
		return FALSE;
	}

	while (file.ReadString(strRead))
	{
		// write page
		_tag_emoticons::_tag_page newPage;
		newPage.Caption = strRead;
		
		while(file.ReadString(strRead))
		{
			if (strRead == EXPORT_SEP_LINE)
			{
				break;
			}
			// write item
			_tag_emoticons::_tag_page::_tag_item newItem;
			newItem.Content = strRead;

			newPage.Items.AddTail(newItem);
		}

		emoticons.Pages.AddTail(newPage);
	}
	file.Close();

	return TRUE;
}