// MdzVector.h: interface for the MdzVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZVECTOR_H__50684559_CDB6_4250_A93F_F204AB72D5E6__INCLUDED_)
#define AFX_MDZVECTOR_H__50684559_CDB6_4250_A93F_F204AB72D5E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzString.h"

class MdzObject;

class DllExport MdzVector  
{
public:
	MdzVector();
	
	void
	InsertAt(MdzObject* lpElt, UINT iIndex);
	
	void
	Remove(MdzObject* lpElt, BOOL bAutoDelete = FALSE);
	
	int
	Find(MdzObject* lpElt);

	void
	Add(MdzObject* lpElt);

	void
	RemoveAt(UINT iIndex, BOOL bAutoDelete = FALSE);

	void
	RemoveAll(BOOL bAutoDelete = FALSE);
	
	BOOL
	IsEmpty();

	MdzObject*
	GetAt(UINT iIndex);
	
	UINT
	GetCount();
	
	virtual ~MdzVector();

private:
	void Grow();
	UINT	iSize;
	UINT	iCount;
	MdzObject** lpData;
};

template <class T>
class DllExport MdzVectorT : public MdzVector
{
public:
	T& operator[](UINT iIndex) {return *((T*)GetAt(iIndex));}
};

class DllExport MdzStrVector : public MdzVectorT<MdzString>
{
public:
	~MdzStrVector();
	BOOL Add(LPSTR strText, BOOL bCheckUnicity = FALSE);
};


#endif // !defined(AFX_MDZVECTOR_H__50684559_CDB6_4250_A93F_F204AB72D5E6__INCLUDED_)
