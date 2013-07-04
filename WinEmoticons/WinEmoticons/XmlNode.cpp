#include "StdAfx.h"
#include ".\xmlnode.h"




//-------------------------------------------------------------------------
// Function Name    :CXmlNode
// Parameter(s)     : MSXML2::IXMLDOMNodePtr pNode	[in]
// Return           :
// Memo             :
//-------------------------------------------------------------------------
CXmlNode::CXmlNode( MSXML2::IXMLDOMNodePtr pNode IN)
{
	m_pNode = pNode;
}


//-------------------------------------------------------------------------
// Function Name    :CXmlNode
// Parameter(s)     :void
// Return           :
// Memo             :
//-------------------------------------------------------------------------
CXmlNode::CXmlNode(void)
{
	m_pNode = NULL;	
}


//-------------------------------------------------------------------------
// Function Name    :CXmlNode
// Parameter(s)     :CXmlNode & refNode [in]
// Return           :
// Memo             :
//-------------------------------------------------------------------------
CXmlNode::CXmlNode( CXmlNode & refNode IN)
{
	m_pNode = refNode.m_pNode;
}


//-------------------------------------------------------------------------
// Function Name    :~CXmlNode
// Parameter(s)     :void
// Return           :
// Memo             :
//-------------------------------------------------------------------------
CXmlNode::~CXmlNode(void)
{
	m_pNode = NULL;
}





//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNodePtr pNode	[in]
// Return           :CXmlNodePtr
// Memo             :
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNode::operator = ( CXmlNodePtr pNode IN)
{
	m_pNode = pNode->m_pNode;
	return pNode;
}


//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNode & refNode	[in]
// Return           :CXmlNode &
// Memo             :
//-------------------------------------------------------------------------
CXmlNode & CXmlNode::operator = ( CXmlNode & refNode IN)
{
	m_pNode = refNode.m_pNode;
	return (*this);
}


//-------------------------------------------------------------------------
// Function Name    :IsNull
// Parameter(s)     :
// Return           :BOOL
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::IsNull(void)
{
	return m_pNode == NULL;
}




//-------------------------------------------------------------------------
// Function Name    :GetChild
// Parameter(s)     :CString strName	
// Return           :
// Memo             :
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNode::GetChild(CString strName IN)
{
	ASSERT( m_pNode != NULL );

	MSXML2::IXMLDOMNodePtr pChildNode = NULL;
	pChildNode = m_pNode->selectSingleNode(_bstr_t((TCHAR*)(LPCTSTR)strName));
	
	// 
	if( pChildNode == NULL )
	{
		MSXML2::IXMLDOMDocumentPtr pDoc = NULL;
		HRESULT hr = m_pNode->get_ownerDocument(&pDoc);
		ASSERT( SUCCEEDED(hr) );

		pChildNode = pDoc->createElement( _bstr_t(strName) );
		ASSERT( pChildNode != NULL );
		
		m_pNode->appendChild(pChildNode);
		
		SAFE_RELEASE(pDoc);
	}

	CXmlNodePtr pChild( new CXmlNode(pChildNode) );
	
	SAFE_RELEASE(pChildNode);

	return pChild;
}


CXmlNodePtr CXmlNode::AppendChild( CString strName )
{
	ASSERT( m_pNode != NULL );
	
	MSXML2::IXMLDOMNodePtr pChildNode = NULL;
	
	
	MSXML2::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = m_pNode->get_ownerDocument(&pDoc);
	ASSERT( SUCCEEDED(hr) );
	
	pChildNode = pDoc->createElement( _bstr_t(strName) );
	ASSERT( pChildNode != NULL );
	
	m_pNode->appendChild(pChildNode);
	
	SAFE_RELEASE(pDoc);
	
	
	CXmlNodePtr pChild( new CXmlNode(pChildNode) );
	
	SAFE_RELEASE(pChildNode);
	
	return pChild;
}



//-------------------------------------------------------------------------
// Function Name    :_GetValue
// Parameter(s)     :CString & strValue IN
// Return           :BOOL	
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::_GetValue(CString & strValue OUT)
{
	ASSERT( m_pNode != NULL );

	if( HasChildren() )
	{
		// 
		ASSERT( FALSE );
		return FALSE;
	}

	BSTR bstr = NULL;
	HRESULT hr = m_pNode->get_text( &bstr );
	ASSERT( SUCCEEDED(hr) );	
	strValue = (LPCTSTR)_bstr_t( bstr, true);

	if( bstr != NULL )
	{
		SysFreeString(bstr);
		bstr = NULL;
	}
	
	return SUCCEEDED(hr);
}



//-------------------------------------------------------------------------
// Function Name    :_SetValue
// Parameter(s)     :CString & strValue IN
// Return           :BOOL	
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode:: _SetValue(CString & strValue IN)
{
	ASSERT( m_pNode != NULL );

	if( HasChildren() )
	{
		//  
		ASSERT( FALSE );
		return FALSE;
	}
	
	HRESULT hr = S_OK;
	hr = m_pNode->put_text( _bstr_t(strValue) );
	ASSERT( SUCCEEDED(hr) );

	return SUCCEEDED(hr);
}



//-------------------------------------------------------------------------
// Function Name    :GetName
// Parameter(s)     :void
// Return           :CString
// Memo             :
//-------------------------------------------------------------------------
CString CXmlNode::GetName(void)
{
	ASSERT( m_pNode != NULL );

	BSTR bstr = NULL;
	HRESULT hr = m_pNode->get_nodeName(&bstr);
	ASSERT( SUCCEEDED(hr) );	
	CString strRet( (LPCTSTR)_bstr_t( bstr, true) );

	if( bstr != NULL )
	{
		SysFreeString(bstr);
		bstr = NULL;
	}

	return strRet;
}






//-------------------------------------------------------------------------
// Function Name    :GetAttribute
// Parameter(s)     :CString strName		
//					:LPCTSTR lpszDefault	
// Return           :CString
// Memo             :
//-------------------------------------------------------------------------
CString CXmlNode::GetAttribute( CString strName IN
							   , LPCTSTR lpszDefault /* = NULL */ IN)
{
	ASSERT( m_pNode != NULL );

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNamedNodeMapPtr pIXMLDOMNamedNodeMap = NULL;
	hr = m_pNode->get_attributes(&pIXMLDOMNamedNodeMap);
	ASSERT( SUCCEEDED(hr) );

	MSXML2::IXMLDOMNodePtr pIXMLDOMNode = NULL;
	pIXMLDOMNode = pIXMLDOMNamedNodeMap->getNamedItem( _bstr_t(strName) );
	
	CString strValue;
	if( pIXMLDOMNode == NULL )
	{
		strValue = lpszDefault;
		SetAttribute( strName, strValue);		
	}
	else
	{
		VARIANT varValue;
		hr = pIXMLDOMNode->get_nodeValue(&varValue);
		ASSERT( SUCCEEDED(hr) );

		strValue = (LPCTSTR)(_bstr_t)varValue;
	}

	pIXMLDOMNode = NULL;

	pIXMLDOMNamedNodeMap = NULL;
	return strValue;
}

DWORD CXmlNode::GetAttribute( CString strName, int iValue )
{
	CString strValue = GetAttribute(strName);

	return _ttol(strValue);
}

bool CXmlNode::GetAttribute( CString strName, bool bValue )
{
	CString strValue = GetAttribute(strName);

	if (strValue.CompareNoCase(_T("TRUE")) == 0)
	{
		return true;
	}
	else if (strValue.CompareNoCase(_T("FALSE")) == 0)
	{
		return false;
	}
	else
	{
		return bValue;
	}
}

COLORREF CXmlNode::GetAttribute( CString strName,COLORREF crValue )
{
	CString strValue = GetAttribute(strName);

    int spos1 = strValue.Find(',');
    if (spos1 == -1)
    {
        return crValue;
    }
	int spos2 = strValue.Find(',',spos1 + 1);
	if (spos2 == -1)
	{
		return crValue;
	}

	CString r = strValue.Left(spos1);
	CString g = strValue.Mid(spos1 + 1,spos2 - spos1 - 1);
	CString b = strValue.Right(strValue.GetLength() - spos2 - 1);

	return RGB(_ttoi(r),_ttoi(g),_ttoi(b));
}
//-------------------------------------------------------------------------
// Function Name    :SetAttribute
// Parameter(s)     :CString strValue
// Return           :BOOL
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::SetAttribute( CString strName IN
							, CString strValue IN)
{
	ASSERT( m_pNode != NULL );

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMElementPtr pElement = NULL;
	pElement = static_cast<MSXML2::IXMLDOMElementPtr> (m_pNode);
	hr = pElement->setAttribute( _bstr_t(strName), _variant_t((LPCTSTR)strValue) );
	ASSERT( SUCCEEDED(hr) );

	SAFE_RELEASE(pElement);
    
	return SUCCEEDED(hr);
}

BOOL CXmlNode::SetAttribute( CString strName IN, int iValue  IN)
{
	CString strText;
	strText.Format(_T("%d"),iValue);

	return SetAttribute(strName,strText);
}

BOOL CXmlNode::SetAttribute( CString strName, bool bValue )
{
	return SetAttribute(strName,bValue ? CString(_T("TRUE")) : CString(_T("FALSE")));
}

BOOL CXmlNode::SetAttribute( CString strName,COLORREF crValue )
{
	CString strValue;
	strValue.Format(_T("%d,%d,%d"),
		GetRValue(crValue),
		GetGValue(crValue),
		GetBValue(crValue));
	return SetAttribute(strName,strValue);
		
}
//-------------------------------------------------------------------------
// Function Name    :DelAttribute
// Parameter(s)     :CString strName IN
// Return           :BOOL
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::DelAttribute( CString strName IN )
{
	ASSERT( m_pNode != NULL );

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNamedNodeMapPtr pIXMLDOMNamedNodeMap = NULL;
	hr = m_pNode->get_attributes(&pIXMLDOMNamedNodeMap);
	ASSERT( SUCCEEDED(hr) );

	hr = SUCCEEDED(hr) ? 
		pIXMLDOMNamedNodeMap->removeNamedItem( _bstr_t(strName) ) != NULL // add !=NULL by mqm @ 2011.3.25
		: hr;
	ASSERT( SUCCEEDED(hr) );

	SAFE_RELEASE(pIXMLDOMNamedNodeMap);
	return SUCCEEDED(hr);
}



//-------------------------------------------------------------------------
// Function Name    :HasChildren
// Parameter(s)     :
// Return           :
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::HasChildren(void)
{
	ASSERT( m_pNode != NULL );

	BOOL bHasChildren = FALSE;

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	MSXML2::DOMNodeType NodeType;
	MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
	hr = m_pNode->get_childNodes(&pNodeList);
	ASSERT( SUCCEEDED(hr) );

	for( int i = 0; i < pNodeList->length; i++)
	{
		pNode = pNodeList->item[i];
		
		hr = pNode->get_nodeType(&NodeType);
		ASSERT( SUCCEEDED(hr) );
		
		SAFE_RELEASE(pNode);

		if( NodeType == MSXML2::NODE_ELEMENT )
		{
			bHasChildren = TRUE;
			break;
		}
	}

	SAFE_RELEASE(pNodeList);

	return bHasChildren;
}



//-------------------------------------------------------------------------
// Function Name    :Remove
// Parameter(s)     :
// Return           :
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::Remove(void)
{
	ASSERT( m_pNode != NULL );

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	hr = m_pNode->get_parentNode(&pNode);
	ASSERT( SUCCEEDED(hr) );
	
	pNode->removeChild(m_pNode);

	return TRUE;
}

//-------------------------------------------------------------------------
// Function Name    :RemoveChildren
// Parameter(s)     :
// Return           :BOOL
// Memo             :
//-------------------------------------------------------------------------
BOOL CXmlNode::RemoveChildren(void)
{
	ASSERT( m_pNode != NULL );

	if( !HasChildren() )
		return FALSE;
	
	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	MSXML2::DOMNodeType NodeType;
	MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
	hr = m_pNode->get_childNodes(&pNodeList);
	ASSERT( SUCCEEDED(hr) );

	// Bug fixed by mqm @ 2011.10.25
	while(pNodeList->length != 0)
	{
		pNode = pNodeList->item[0];
		
		hr = pNode->get_nodeType(&NodeType);
		ASSERT( SUCCEEDED(hr) );

		if( NodeType == MSXML2::NODE_ELEMENT )
		{
			m_pNode->removeChild(pNode);
		}

		SAFE_RELEASE(pNode);
	}

	SAFE_RELEASE(pNodeList);
	return TRUE;
}


//-------------------------------------------------------------------------
// Function Name    :GetChildren
// Parameter(s)     :void
// Return           :CXmlNodesPtr
// Memo             :
//-------------------------------------------------------------------------
CXmlNodesPtr CXmlNode::GetChildren()
{
	ASSERT( m_pNode != NULL );

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
	hr = m_pNode->get_childNodes(&pNodeList);
	ASSERT( SUCCEEDED(hr) );

	CXmlNodesPtr pNodes(new CXmlNodes(pNodeList));

	return pNodes;
}




//////////////////////////////////////////////////////////////////////////
// 

CString CXmlNode::GetString(LPCTSTR lpszValue /* = NULL */ IN)
{
	CString strValue;
	_GetValue(strValue);

	if( strValue.IsEmpty() &&
		lpszValue != NULL )
	{
		strValue = lpszValue;
		_SetValue(strValue);
	}

	return strValue;
}



BOOL CXmlNode::GetBOOL( BOOL bDefault /* = FALSE */ IN)
{
	CString strValue;
	_GetValue(strValue);

	if( strValue.CompareNoCase(_T("true")) == 0 )
	{
		return TRUE;
	}
	else if( strValue.CompareNoCase(_T("false")) == 0 )
	{
		return FALSE;
	}
	else
	{
		strValue = bDefault ? "true" : "false";
		_SetValue(strValue);
		return bDefault;
	}	
}


INT CXmlNode::GetInt( INT nDefault /* = 0 */ IN)
{
	CString strValue;
	_GetValue(strValue);

	if( strValue.IsEmpty() )
	{
		strValue.Format( _T("%ld"), nDefault);
		_SetValue(strValue);
	}

	return _ttoi(strValue);
}



DOUBLE CXmlNode::GetFloat( DOUBLE fDefault /* = 0.0 */)
{
	CString strValue;
	_GetValue(strValue);

	if( strValue.IsEmpty() )
	{
		strValue.Format( _T("%f"), fDefault);
		_SetValue(strValue);
	}

	return _tstof(strValue);
}


//////////////////////////////////////////////////////////////////////////
// 

BOOL CXmlNode::SetString( LPCTSTR lpszValue )
{
	CString strValue(lpszValue);
	return _SetValue(strValue);
}


BOOL CXmlNode::SetBOOL( BOOL bValue )
{
	CString strValue;
	strValue = bValue ? "true" : "false";

	return _SetValue(strValue);
}

BOOL CXmlNode::SetInt( INT nValue )
{
	CString strValue;
	strValue.Format( _T("%ld"), nValue);

	return _SetValue(strValue);
}

BOOL CXmlNode::SetFloat( FLOAT fValue )
{
	CString strValue;
	strValue.Format( _T("%f"), fValue);

	return _SetValue(strValue);
}

BOOL CXmlNode::HasChild( CString strName )
{
	ASSERT( m_pNode != NULL );
	
	return m_pNode->selectSingleNode(_bstr_t((TCHAR*)(LPCTSTR)strName)) != NULL;
}
//////////////////////////////////////////////////////////////////////////

