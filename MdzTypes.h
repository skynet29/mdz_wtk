// MdzTypes.h: interface for the MdzTypes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTYPES_H__5FA696A0_B32C_4A53_8704_34187864EF3D__INCLUDED_)
#define AFX_MDZTYPES_H__5FA696A0_B32C_4A53_8704_34187864EF3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef DLLMDZ
#define DllExport __declspec( dllexport )
#elif LIBMDZ
#define DllExport
#else
#define DllExport __declspec( dllimport )

#endif

//#define WINVER 0x0500 
#include <windows.h>
#include <commctrl.h>



// MACRO

#define MEMBER_SET(a) \
	this->a = a;




#endif // !defined(AFX_MDZTYPES_H__5FA696A0_B32C_4A53_8704_34187864EF3D__INCLUDED_)
