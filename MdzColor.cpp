// MdzColor.cpp: implementation of the MdzColor class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzColor.h"
#include "MdzCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const COLORREF MdzColor::K_BLACK			= RGB(0, 0, 0);
const COLORREF MdzColor::K_WHITE			= RGB(255, 255, 255);
const COLORREF MdzColor::K_RED			= RGB(255, 0, 0);
const COLORREF MdzColor::K_GREEN			= RGB(0, 255, 0);
const COLORREF MdzColor::K_BLUE			= RGB(0, 0, 255);
const COLORREF MdzColor::K_CYAN			= RGB(0, 255, 255);
const COLORREF MdzColor::K_MAGENTA		= RGB(255, 0, 255);
const COLORREF MdzColor::K_YELLOW		= RGB(255, 255, 0);
const COLORREF MdzColor::K_LIGHTGREY	= RGB(192, 192, 192);
const COLORREF MdzColor::K_DARKGREY		= RGB(128, 128, 128);

MdzColor::MdzColor()
{
	value = K_BLACK;	
}





MdzColor::MdzColor(BYTE red, BYTE green, BYTE blue)
{
	value = RGB(red, green, blue);
}

MdzColor::operator COLORREF()
{
	return value;
}

MdzColor::MdzColor(COLORREF value)
{
	MEMBER_SET(value);
}

MdzColor MdzColor::GetSysColor()
{
	return ::GetSysColor(COLOR_BTNFACE);
}

//BOOL MdzColor::ChooseColor(MdzCtrl *lpParent)
BOOL MdzColor::ChooseColor()
{
	CHOOSECOLOR cc;
	static COLORREF acrCustClr[16]; 

	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
//	cc.hwndOwner = lpParent->GetHandle();
	cc.hwndOwner = GetActiveWindow();
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = value;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	if (::ChooseColor(&cc))
	{
		value = cc.rgbResult;
		return TRUE;
	}
	return FALSE;

}
