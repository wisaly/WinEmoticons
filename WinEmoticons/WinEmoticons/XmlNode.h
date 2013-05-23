#pragma once


#include <memory>
#import "msxml6.dll"


#define SAFE_RELEASE(x)	\
	if( x != NULL )		\
	{					\
		x.Release();	\
		x = NULL;		\
	}


class CXml;

class CXmlNode;
typedef std::auto_ptr<CXmlNode>  CXmlNodePtr;

class CXmlNodes;
typedef std::auto_ptr<CXmlNodes>  CXmlNodesPtr;



#include ".\XmlNodes.h"



class CXmlNode
{
	friend class CXml;
	friend class CXmlNode;
	friend class CXmlNodes;


public:	
	~CXmlNode(void);

protected:
	
	MSXML2::IXMLDOMNodePtr   m_pNode;

	CXmlNode( MSXML2::IXMLDOMNodePtr pNode);	
	BOOL _GetValue(CString & strValue);
	BOOL _SetValue(CString & strValue);

public:

	//		_________________
	//______|	Constructor  |___________________________________________________________________
	CXmlNode(void);
	CXmlNode( CXmlNode & refNode IN);


	//		_________________
	//______|	operator =	|___________________________________________________________________
	CXmlNodePtr operator = ( CXmlNodePtr pNode);
	CXmlNode & operator = ( CXmlNode & refNode);



	//		_________________
	//______|  Node Name     |___________________________________________________________________
	CString GetName(void);
	


	//		_________________
	//______|	Attributes   |___________________________________________________________________
	CString GetAttribute( CString strName, LPCTSTR lpszDefault = NULL);
	DWORD GetAttribute( CString strName, int iValue);			// add by mqm @ 2011.3.25
	BOOL GetAttribute( CString strName, bool bValue);			// add by mqm @ 2011.3.25
	COLORREF GetAttribute( CString strName,COLORREF crValue);	// add by mqm @ 2013.4.24

	BOOL SetAttribute(  CString strName, CString strValue);
	BOOL SetAttribute(  CString strName, int iValue);			// add by mqm @ 2011.3.25
	BOOL SetAttribute(  CString strName, bool bValue);			// add by mqm @ 2011.3.25
	BOOL SetAttribute( CString strName,COLORREF crValue);		// add by mqm @ 2013.4.24

	BOOL DelAttribute( CString strName );



	//		_________________
	//______|	Child nodes  |___________________________________________________________________
	CXmlNodePtr GetChild(CString strName);
	CXmlNodesPtr GetChildren();
	BOOL HasChildren(void);
	BOOL RemoveChildren(void);
	
	CXmlNodePtr AppendChild(CString strName);	// add by mqm @ 2011.3.25
	BOOL HasChild(CString strName);				// add by mqm @ 2011.7.14

	//		_________________
	//______|	Remove Node  |___________________________________________________________________
	BOOL Remove(void);
	


	//		_________________
	//______|	Get value    |___________________________________________________________________	
	CString GetString( LPCTSTR lpszDefault = NULL );
	BOOL GetBOOL( BOOL bDefault = FALSE );
	INT GetInt( INT nDefault = 0 );
	DOUBLE GetFloat( DOUBLE fDefault = 0.0f );
	


	//		_________________
	//______|	Set value    |___________________________________________________________________
	BOOL SetString( LPCTSTR lpszValue );
	BOOL SetBOOL( BOOL bValue );
	BOOL SetInt( INT nValue );
	BOOL SetFloat( FLOAT fValue );
	
	BOOL IsNull(void);
};
