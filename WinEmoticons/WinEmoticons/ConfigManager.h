#pragma once

class CConfigManager
{
public:
	CString configFilePath;
	struct _tag_configwindow_
	{
		bool PopAtStart;
	}ConfigWindow;
	struct _tag_acceratekey_
	{
		CString PopSelect;
	}AccerateKey;
	struct _tag_popwindow_
	{
		int CtrlPadding;
		int FontSize;
		CString FontName;
		int Width;
		int Height;
		struct _tag_pageheader_
		{
			int HeaderHeight;
			int HeaderHorzMargin;
			int HeaderTopMargin;
			int HeaderActiveHorzMargin;
			int HeaderActiveTopMargin;
			int PagePadding;
		}PageHeader;
		struct
		{
			CList<COLORREF,COLORREF> Colors;
		}Pages;
		struct
		{
			int ItemPadding;
			int ColumnCount;
			int RowCount;
			struct  
			{
				COLORREF Background;
				COLORREF Foreground;
				COLORREF Hightlight;
				COLORREF Checked;
				COLORREF Disabled;
			}Colors;
		}PageItem;
	}PopWindow;
	struct _tag_emoticons
	{
		struct _tag_page
		{
			CString Caption;
			struct _tag_item
			{
				CString Content;
			};
			CList<_tag_item,_tag_item&> Items;

			_tag_page &operator=(_tag_page &src)
			{
				this->Caption = src.Caption;
				this->Items.RemoveAll();
				for (POSITION pos = src.Items.GetHeadPosition();pos != NULL;)
				{
					this->Items.AddTail(src.Items.GetNext(pos));
				}
				return *this;
			}
		};
		CList<_tag_page,_tag_page&> Pages;
	}Emoticons;

	BOOL IsOnConfig;
private:
	CConfigManager();
public:	
	static CConfigManager *Inst();
	static BOOL ParseCombineKeys(CString strComKeys,UINT &nModifier,UINT &nVKey);
	static CString Version();
private:
	static CString translateVKey( int nVKey,CString strNullString = _T("") );
	static int translateVKey( CString strKey );

public:
	BOOL LoadConfig();
	BOOL SaveConfig();
public:
	static BOOL ExportEmoticons(_tag_emoticons &emoticons,CString &strFilePath,CString &strAuthor,CString &strTitle);
	static BOOL ImportEmoticons(_tag_emoticons &emoticons,CString &strFilePath,CString &strAuthor,CString &strTitle);
};