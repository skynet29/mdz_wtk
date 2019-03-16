// MdzString.h: interface for the MdzString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSTRING_H__2FC89031_4233_436A_BBC1_9F76D21C66C9__INCLUDED_)
#define AFX_MDZSTRING_H__2FC89031_4233_436A_BBC1_9F76D21C66C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzObject.h"

class MdzStrVector;
class MdzStream;


class DllExport MdzString : public MdzObject
{
public:
	UCHAR GetCharAt(UINT iIndex);
	void Tokenize(LPSTR strToken, MdzStrVector& vector);
	int Compare(LPSTR lpStr);
	MdzString();
	MdzString(LPSTR lpStr);
	MdzString(const MdzString& str);

	MdzString
	ExtractPath();

	MdzString
	ToLower();

	MdzString
	ToUpper();

	int
	ToIntHex();
	
	MdzString
	ExtractFileName();
	
	int
	GetLength() const;

	int
	GetIndexOf(LPSTR str, int iStartIdx = 0);
	
	MdzString
	GetSubString(int iStartIdx, int iLength = -1);

	int
	ToInt();
	
	BOOL
	Equals(LPSTR lpStr);
	
	void
	Dump();
	
	void
	Alloc(UINT iSize);
	
	

	static MdzString
	Load(UINT iResId, HMODULE hModule = NULL);
	
	static MdzString
	Format(LPSTR fmt, ...);


	// Operators
	void
	operator +=(const MdzString &str);
	
	void
	operator =(const MdzString &str);

	UCHAR
	operator[](UINT iIndex);
	
	operator LPSTR();

	virtual ~MdzString();

private:
	void Clone(LPSTR lpStr);
	LPSTR lpData;
};


DllExport MdzString operator+(MdzString& str1, MdzString& str2);

#endif // !defined(AFX_MDZSTRING_H__2FC89031_4233_436A_BBC1_9F76D21C66C9__INCLUDED_)
