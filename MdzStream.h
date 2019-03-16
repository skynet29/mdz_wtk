// MdzStream.h: interface for the MdzStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSTREAM_H__B1BD2D1F_37DA_41BC_8328_0EF1E9095453__INCLUDED_)
#define AFX_MDZSTREAM_H__B1BD2D1F_37DA_41BC_8328_0EF1E9095453__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include <stdio.h>
#include "MdzString.h"	// Added by ClassView

class DllExport MdzStream  
{
public:
	// Constants
	static const UINT K_READ;
	static const UINT K_WRITE;


	// Constructor
	MdzStream();

	// Destructor
	virtual ~MdzStream();

	// Methods
	FILE*
	GetDesc();

	ULONG
	GetFileSize();

	MdzString
	ReadText();
	
	BOOL
	Open(LPSTR lpFileName, int iMode);
	
	void
	Write(LPVOID lpBuffer, int iBuffSize);
	
	void
	WriteText(LPSTR strText);
	
	void
	Read(LPVOID lpBuffer, int iBuffSize);
	
	void
	Close();


private:
	FILE* lpFile;
};

#endif // !defined(AFX_MDZSTREAM_H__B1BD2D1F_37DA_41BC_8328_0EF1E9095453__INCLUDED_)
