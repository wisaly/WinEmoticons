#pragma once

#define nUNICODE_BOM      0xFEFF  // Unicode "byte order mark" which goes at start of file
#define sNEWLINE        _T("\r\n") // New line characters
#define sDEFAULT_UNICODE_FILLER_CHAR "#"   // Filler char used when no conversion from Unicode to local code page is possible

class CStdioFileEx: public CStdioFile
{
public:
	CStdioFileEx();
	CStdioFileEx( LPCTSTR lpszFileName, UINT nOpenFlags );

	virtual BOOL Open( LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL );
	virtual BOOL ReadString(CString& rString);
	virtual void WriteString( LPCTSTR lpsz );
	bool    IsFileUnicodeText() { return m_bIsUnicodeText; } 
	unsigned long GetCharCount();

	// Additional flag to allow Unicode text writing
	static const UINT modeWriteUnicode;

	// static utility functions

	// --------------------------------------------------------------------------------------------
	//
	// CStdioFileEx::GetUnicodeStringFromMultiByteString()
	//
	// --------------------------------------------------------------------------------------------
	// Returns:    bool
	// Parameters: char *  szMultiByteString  (IN) Multi-byte input string
	//     wchar_t*  szUnicodeString  (OUT) Unicode output string
	//     short   nUnicodeBufferSize (IN) Size of Unicode output buffer
	//     UINT   nCodePage    (IN) Code page used to perform conversion
	//                  Default = -1 (Get local code page).
	//
	// Purpose:  Gets a Unicode string from a MultiByte string.
	// Notes:  None.
	// Exceptions: None.
	//
	static bool  GetUnicodeStringFromMultiByteString(char * szMultiByteString,wchar_t* szUnicodeString,
		short nUnicodeBufferSize,UINT nCodePage=-1);

	// --------------------------------------------------------------------------------------------
	//
	// CStdioFileEx::GetMultiByteStringFromUnicodeString()
	//
	// --------------------------------------------------------------------------------------------
	// Returns:    BOOL
	// Parameters: wchar_t * szUnicodeString   (IN) Unicode input string
	//     char*   szMultiByteString   (OUT) Multibyte output string
	//     short   nMultiByteBufferSize  (IN) Multibyte buffer size
	//     UINT   nCodePage     (IN) Code page used to perform conversion
	//                   Default = -1 (Get local code page).
	//
	// Purpose:  Gets a MultiByte string from a Unicode string.
	// Notes:  .
	// Exceptions: None.
	//
	static BOOL   GetMultiByteStringFromUnicodeString(wchar_t * szUnicodeString,char* szMultiByteString,
		short nMultiByteBufferSize,UINT nCodePage=-1);


	// --------------------------------------------------------------------------------------------
	//
	// CStdioFileEx::IsFileUnicode()
	//
	// --------------------------------------------------------------------------------------------
	// Returns:    bool
	// Parameters: const CString& sFilePath
	//
	// Purpose:  Determines whether a file is Unicode by reading the first character and detecting
	//     whether it's the Unicode byte marker.
	// Notes:  None.
	// Exceptions: None.
	//
	static bool IsFileUnicode(const CString& sFilePath);


protected:
	UINT ProcessFlags(const CString& sFilePath, UINT& nOpenFlags);

	bool  m_bIsUnicodeText;
	UINT  m_nFlags;
};


