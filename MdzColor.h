// MdzColor.h: interface for the MdzColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCOLOR_H__415AD5D4_F97D_42FB_9F00_58D55651123E__INCLUDED_)
#define AFX_MDZCOLOR_H__415AD5D4_F97D_42FB_9F00_58D55651123E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzCtrl;

class DllExport MdzColor  
{
public:
	MdzColor();
	MdzColor(BYTE red, BYTE green, BYTE blue);
	MdzColor(COLORREF value);
	
	BOOL
	ChooseColor();

	operator COLORREF();

	static MdzColor
	GetSysColor();

	static const COLORREF K_BLACK;		
	static const COLORREF K_WHITE;		
	static const COLORREF K_RED;		
	static const COLORREF K_GREEN;		
	static const COLORREF K_BLUE;		
	static const COLORREF K_CYAN;		
	static const COLORREF K_MAGENTA;
	static const COLORREF K_YELLOW;	
	static const COLORREF K_LIGHTGREY;
	static const COLORREF K_DARKGREY;	


private:
	COLORREF value;

};

#endif // !defined(AFX_MDZCOLOR_H__415AD5D4_F97D_42FB_9F00_58D55651123E__INCLUDED_)
