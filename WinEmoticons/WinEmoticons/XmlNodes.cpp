#include "StdAfx.h"
#include ".\xmlnodes.h"


// 下面是构造函数 和 析构函数
CXmlNodes::CXmlNodes(MSXML2::IXMLDOMNodeListPtr pNodeList)
{
	m_pNodeList = pNodeList;
}

CXmlNodes::CXmlNodes( CXmlNodes & refNodes )
{
	m_pNodeList = refNodes.m_pNodeList;
}

CXmlNodes::CXmlNodes(void)
: m_pNodeList(NULL)
{
}

CXmlNodes::~CXmlNodes(void)
{
	SAFE_RELEASE(m_pNodeList);
}

//////////////////////////////////////////////////////////////////////////



//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNodesPtr pNodes
// Return           :CXmlNodesPtr
// Memo             :
//-------------------------------------------------------------------------
CXmlNodesPtr CXmlNodes::operator = ( CXmlNodesPtr pNodes IN )
{
	SAFE_RELEASE(m_pNodeList);

	m_pNodeList = pNodes->m_pNodeList;
	return pNodes;
}


//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNodes & refNodes
// Return           :CXmlNodes &
// Memo             :
//-------------------------------------------------------------------------
CXmlNodes & CXmlNodes::operator = (CXmlNodes & refNodes)
{
	SAFE_RELEASE(m_pNodeList);

	m_pNodeList = refNodes.m_pNodeList;
	return (*this);
}



//-------------------------------------------------------------------------
// Function Name    :GetCount
// Parameter(s)     :void
// Return           :LONG
// Memo             :
//-------------------------------------------------------------------------
LONG CXmlNodes::GetCount(void)
{
	ASSERT( m_pNodeList != NULL );

	LONG lCount = 0l;
	HRESULT hr = S_OK;
	MSXML2::DOMNodeType NodeType;
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	
	for( int i = 0; i < m_pNodeList->length; i++)
	{
		pNode = m_pNodeList->item[i];

		hr = pNode->get_nodeType(&NodeType);
		ASSERT( SUCCEEDED(hr) );

		if( NodeType == MSXML2::NODE_ELEMENT )
		{
			lCount ++;
		}

		SAFE_RELEASE(pNode);
	}

	return lCount;
}



//-------------------------------------------------------------------------
// Function Name    :GetItem
// Parameter(s)     :LONG nIndex	
// Return           :CXmlNodePtr
// Memo             :
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::GetItem( LONG nIndex )
{
	ASSERT( nIndex >= 0 && nIndex < GetCount() );

	LONG lCount = 0l;
	HRESULT hr = S_OK;
	MSXML2::DOMNodeType NodeType;
	MSXML2::IXMLDOMNodePtr pItem = NULL;

	CXmlNodePtr pNode ( new CXmlNode() );

	for( int i = 0; i < m_pNodeList->length; i++)
	{
		pItem = m_pNodeList->item[i];

		hr = pItem->get_nodeType(&NodeType);
		ASSERT( SUCCEEDED(hr) );


		if( NodeType == MSXML2::NODE_ELEMENT )
		{
			if( lCount == nIndex )
			{
				pNode->m_pNode = pItem;
				SAFE_RELEASE(pItem);
				return pNode;
			}

			lCount ++;
		}

		SAFE_RELEASE(pItem);
	}

	return pNode;
}


//-------------------------------------------------------------------------
// Function Name    :operator[]
// Parameter(s)     :INT nIndex
// Return           :CXmlNodePtr
// Memo             : GetItem( LONG nIndex )
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::operator[] ( LONG lIndex )
{
	return GetItem(lIndex);
}


CXmlNodePtr CXmlNodes::GetItem( LPCTSTR lpszName )
{
	ASSERT( lpszName != NULL );
	
	HRESULT hr = S_OK;
	CString strName;
	BSTR bstr = NULL;
	MSXML2::IXMLDOMNodePtr pItem = NULL;

	CXmlNodePtr pNode ( new CXmlNode() );

	for( int i = 0; i < m_pNodeList->length; i++)
	{
		pItem = m_pNodeList->item[i];

		hr = pItem->get_nodeName(&bstr);
		ASSERT( SUCCEEDED(hr) );

		strName = (LPCTSTR)_bstr_t( bstr, true);
		if( bstr != NULL )
		{
			SysFreeString(bstr);
			bstr = NULL;
		}

		// 
		if( strName.Compare(lpszName) == 0 )
		{
			pNode->m_pNode = pItem;
			SAFE_RELEASE(pItem);
			return pNode;
		}

		SAFE_RELEASE(pItem);
	}

	return pNode;
}

CXmlNodePtr CXmlNodes::operator[] ( LPCTSTR lpszName )
{
	return GetItem(lpszName);
}
