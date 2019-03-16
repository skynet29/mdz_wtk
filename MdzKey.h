// MdzKey.h: interface for the MdzKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZKEY_H__4BDE84B1_5E9E_4CDB_BE17_01BDE627B418__INCLUDED_)
#define AFX_MDZKEY_H__4BDE84B1_5E9E_4CDB_BE17_01BDE627B418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class DllExport MdzKey  
{
public:
	static BOOL IsKeyDown(int key);

	static const UINT K_ENTER;
	static const UINT K_SHIFT;	
	static const UINT K_CTRL;	
	static const UINT K_LEFT;	
	static const UINT K_RIGHT;	
	static const UINT K_DOWN;	
	static const UINT K_UP;		
	static const UINT K_TAB;
	static const UINT K_DELETE;
	static const UINT K_ALT;
	static const UINT K_F1;
	static const UINT K_F2;
	static const UINT K_F3;
	static const UINT K_F4;
	static const UINT K_F5;
	static const UINT K_F6;
	static const UINT K_F7;
	static const UINT K_F8;
	static const UINT K_F9;
	static const UINT K_F10;
	static const UINT K_F11;
	static const UINT K_F12;
private:	
	MdzKey();
	virtual ~MdzKey();

};

#endif // !defined(AFX_MDZKEY_H__4BDE84B1_5E9E_4CDB_BE17_01BDE627B418__INCLUDED_)


