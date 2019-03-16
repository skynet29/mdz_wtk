// MdzClassFactory.cpp: implementation of the MdzClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzClassFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static MdzClassFactory* lpHead = NULL;

MdzClassFactory::MdzClassFactory(LPSTR strClassName)
{
	lpNext = lpHead;
	lpHead = this;
	MEMBER_SET(strClassName);
}

MdzClassFactory::~MdzClassFactory()
{

}

MdzClassFactory* MdzClassFactory::GetFactory(LPSTR lpClassName)
{
	MdzClassFactory* lpFactory = lpHead;

	while (lpFactory)
	{
		if (lpFactory->strClassName.Equals(lpClassName) )
			return lpFactory;

		lpFactory = lpFactory->lpNext;
	}

	return NULL;
}

LPVOID MdzClassFactory::CreateObject(LPSTR strClassName)
{
	MdzClassFactory* pFactory = GetFactory(strClassName);
	if (!pFactory)
		return NULL;

	return pFactory->NewObject();
}


