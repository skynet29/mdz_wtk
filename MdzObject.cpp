// MdzObject.cpp: implementation of the MdzObject class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



MdzObject::~MdzObject()
{

}

BOOL MdzObject::IsInstanceOf(LPSTR strClass)
{
	return (strcmp(strClass, "MdzObject") == 0);

}
