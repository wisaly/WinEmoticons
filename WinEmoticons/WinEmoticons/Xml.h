#pragma once
#include "XmlNode.h"


//-------------------------------------------------------------------------
// Classes Name	    :CXml CXmlNode CXmlNodes
// Author			:original[sky-sea-earth@21cn.com] improve[wisaly@gmail.com]
// CreateTime       :2005-10-07
// Memo             :Xml lib
// Version          :v1.1
//-------------------------------------------------------------------------



class CXml
{
public:
	CXml(void);
	~CXml(void);

protected:
	MSXML2::IXMLDOMDocumentPtr  m_pDoc; 
	CString						m_strFilePath;

public:
	BOOL Open(CString strXmlFilePath);
	BOOL Save(LPCTSTR lpszFilePath = NULL);
	void Close(void);

	BOOL Create(CString strXmlFilePath);	// add by mqm @ 2011.3.25

	CString GetLastError(void);

	CXmlNodePtr GetRoot(void);		


	static BOOL IsFileExist(CString strFilePath);
	CXmlNodePtr SelectSingleNode(LPCTSTR lpszPath);
	CXmlNodesPtr SelectNodes(LPCTSTR lpszPath);

	CString GetXmlText();					// add by mqm @ 2011.4.7
	BOOL SetXmlText(LPCTSTR lpszXml);		// add by mqm @ 2011.4.7
	static CString GetApplicationPath();	// add by mqm @ 2013.4.24
};
