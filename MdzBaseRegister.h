// MdzBaseRegister.h: interface for the MdzBaseRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBASEREGISTER_H__B6E4906D_EE96_4490_96EA_0CFC28C5B3B6__INCLUDED_)
#define AFX_MDZBASEREGISTER_H__B6E4906D_EE96_4490_96EA_0CFC28C5B3B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzString.h"
#include "MdzVector.h"

class DllExport MdzBaseRegister  
{
public:
	static BOOL EnumKey(LPSTR strPath, MdzStrVector& vector);
	static BOOL
	SetStringValue(LPSTR strPath, LPSTR strName, LPSTR strValue);

	static BOOL
	GetStringValue(LPSTR strPath, LPSTR strName, MdzString& strValue);

	static BOOL
	GetDwordValue(LPSTR strPath, LPSTR strName, DWORD& dwValue);

	static BOOL
	SetDwordValue(LPSTR strPath, LPSTR strName, DWORD dwValue);
private:
	MdzBaseRegister();
	virtual ~MdzBaseRegister();

};

#endif // !defined(AFX_MDZBASEREGISTER_H__B6E4906D_EE96_4490_96EA_0CFC28C5B3B6__INCLUDED_)
