// MdzObject.h: interface for the MdzObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZOBJECT_H__8E7763C6_86BF_469A_9977_6B8982735AAF__INCLUDED_)
#define AFX_MDZOBJECT_H__8E7763C6_86BF_469A_9977_6B8982735AAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

#define DEFINE_STD_METHODS(aClass, aBaseClass)\
	virtual LPSTR GetClass() {return #aClass;}\
	virtual BOOL IsInstanceOf(LPSTR strClass) {\
		return (MdzString(strClass).Equals(#aClass)) ? TRUE : aBaseClass::IsInstanceOf(strClass);}

class DllExport MdzObject  
{
public:
	virtual ~MdzObject();
	virtual BOOL IsInstanceOf(LPSTR strClass);
	virtual LPSTR GetClass() {return "MdzObject";}

};




#endif // !defined(AFX_MDZOBJECT_H__8E7763C6_86BF_469A_9977_6B8982735AAF__INCLUDED_)
