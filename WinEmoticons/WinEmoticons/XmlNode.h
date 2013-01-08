#pragma once


#import "msxml4.dll"
#include <memory>


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
	//______|	���캯��	|___________________________________________________________________
	CXmlNode(void);
	CXmlNode( CXmlNode & refNode IN);


	//		_________________
	//______|	���� = ��	|___________________________________________________________________
	CXmlNodePtr operator = ( CXmlNodePtr pNode);
	CXmlNode & operator = ( CXmlNode & refNode);



	//		_________________
	//______|  ��ȡ�������	|___________________________________________________________________
	CString GetName(void);
	


	//		_________________
	//______|	���Բ���	|___________________________________________________________________
	CString GetAttribute( CString strName, LPCTSTR lpszDefault = NULL);
	DWORD GetAttribute( CString strName, DWORD dwValue);		// add by mqm @ 2011.3.25
	BOOL GetAttribute( CString strName, BOOL bValue);			// add by mqm @ 2011.3.25

	BOOL SetAttribute(  CString strName, CString strValue);
	BOOL SetAttribute(  CString strName, DWORD dwValue);		// add by mqm @ 2011.3.25
	BOOL SetAttribute(  CString strName, BOOL bValue);			// add by mqm @ 2011.3.25

	BOOL DelAttribute( CString strName );



	//		_________________
	//______|	�ӽ�����	|___________________________________________________________________
	CXmlNodePtr GetChild(CString strName);
	CXmlNodesPtr GetChildren();
	BOOL HasChildren(void);
	BOOL RemoveChildren(void);
	
	CXmlNodePtr AppendChild(CString strName);	// add by mqm @ 2011.3.25
	BOOL HasChild(CString strName);				// add by mqm @ 2011.7.14

	//		_________________
	//______|	ɾ�����	|___________________________________________________________________
	BOOL Remove(void);
	


	//		_________________
	//______|	ȡֵ����	|___________________________________________________________________	
	CString GetString( LPCTSTR lpszDefault = NULL );
	BOOL GetBOOL( BOOL bDefault = FALSE );
	INT GetInt( INT nDefault = 0 );
	DOUBLE GetFloat( DOUBLE fDefault = 0.0f );
	


	//		_________________
	//______|	��ֵ����	|___________________________________________________________________
	BOOL SetString( LPCTSTR lpszValue );
	BOOL SetBOOL( BOOL bValue );
	BOOL SetInt( INT nValue );
	BOOL SetFloat( FLOAT fValue );
	
	BOOL IsNull(void);
};