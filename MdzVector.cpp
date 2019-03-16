// MdzVector.cpp: implementation of the MdzVector class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzVector.h"
#include "MdzString.h"
#include "MdzObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzVector::MdzVector()
{
	lpData = NULL;
	iCount = 0;
	iSize = 0;
}

MdzVector::~MdzVector()
{
	if (lpData)
		delete [] lpData;
}

UINT MdzVector::GetCount()
{
	return iCount;
}

void MdzVector::Add(MdzObject* lpElt)
{
	Grow();
	lpData[iCount++] = lpElt;
}

MdzObject* MdzVector::GetAt(UINT iIndex)
{
	if (iIndex >= iCount)
		throw MdzString("Index out of range");
	
	return lpData[iIndex];
}

void MdzVector::RemoveAt(UINT iIndex, BOOL bAutoDelete)
{
	if (iIndex >= iCount)
		throw MdzString("Index out of range");

	void* lpTemp = lpData[iIndex];

	if ( (iIndex + 1) != iCount ) 
	{
		MoveMemory(&lpData[iIndex], &lpData[iIndex + 1],
			(iCount - iIndex - 1) * sizeof(MdzObject*));
	}

	iCount--;

	if (bAutoDelete)
		delete lpTemp;
}

void MdzVector::RemoveAll(BOOL bAutoDelete)
{
	if (bAutoDelete)
	{
		for (UINT i = 0; i < iCount; i++)
			delete lpData[i];
	}

	if (lpData)
	{
		iCount = 0;
		iSize = 0;
		delete [] lpData;
		lpData = NULL;
	}
}

BOOL MdzVector::IsEmpty()
{
	return (iCount == 0);
}

int MdzVector::Find(MdzObject* lpElt)
{
    for (UINT i = 0; i < iCount; i++)
    {    
        if (lpData[i] == lpElt)
            return i;
    }
    return -1;
}

void MdzVector::Remove(MdzObject* lpElt, BOOL bAutoDelete)
{
	RemoveAt(Find(lpElt), bAutoDelete);
}

void MdzVector::InsertAt(MdzObject* lpElt, UINT iIndex)
{
	if (iIndex > iCount)
		throw MdzString("Index out of range");

	if (iIndex == iCount)
	{
		Add(lpElt);
		return;
	}

	Grow();
	MoveMemory(&lpData[iIndex + 1], &lpData[iIndex], (iCount - iIndex) * sizeof(MdzObject*));
	lpData[iIndex] = lpElt;
	iCount++;
}

void MdzVector::Grow()
{
	if (iCount == iSize)
	{
		iSize += 5;
		MdzObject** lpTemp = new MdzObject*[iSize];
		if (iCount)
		{
			CopyMemory(lpTemp, lpData, sizeof(MdzObject*) * iCount);
			delete [] lpData;
		}
		lpData = lpTemp;
	}

}

BOOL MdzStrVector::Add(LPSTR strText, BOOL bCheckUnicity)
{
	for(UINT i = 0; i < GetCount() && bCheckUnicity; i++)
	{
		if ((*this)[i].Equals(strText))
			return FALSE;
	}
	MdzVector::Add(new MdzString(strText));
	return TRUE;
}

MdzStrVector::~MdzStrVector()
{
	RemoveAll(TRUE);
}
