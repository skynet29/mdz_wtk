// MdzCursor.h: interface for the MdzCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCURSOR_H__F34BA356_6D22_4644_A41F_FA826C715BD5__INCLUDED_)
#define AFX_MDZCURSOR_H__F34BA356_6D22_4644_A41F_FA826C715BD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzCursorInternal;

class DllExport MdzCursor  
{
public:
	static const UINT K_ARROW;
	static const UINT K_IBEAM;           
	static const UINT K_WAIT;            
	static const UINT K_CROSS;           
	static const UINT K_UPARROW;         
	static const UINT K_SIZENWSE;        
	static const UINT K_SIZENESW;        
	static const UINT K_SIZEWE;          
	static const UINT K_SIZENS;          
	static const UINT K_SIZEALL;         
	static const UINT K_NO;              
	static const UINT K_HAND;            
	static const UINT K_HELP;            
};

#endif // !defined(AFX_MDZCURSOR_H__F34BA356_6D22_4644_A41F_FA826C715BD5__INCLUDED_)
