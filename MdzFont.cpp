// MdzFont.cpp: implementation of the MdzFont class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFont.h"
#include "MdzCtrl.h"
#include "MdzStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const UINT MdzFont::K_ITALIC	= 1;
const UINT MdzFont::K_BOLD		= 2;

static int logPixelSy;


MdzFont::MdzFont(LPSTR strName, UINT iSize, UINT iStyle)
{
	MEMBER_SET(strName);
	MEMBER_SET(iSize);
	MEMBER_SET(iStyle);
}

MdzFont::~MdzFont()
{

}

void MdzFont::InitClass()
{
 	HDC hDC = GetDC(NULL);
	logPixelSy = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);
}

MdzFont::MdzFont()
{
	LOGFONT lf;
	::GetObject(GetStockObject(SYSTEM_FONT), sizeof(lf), &lf);
	Init(lf, FALSE);
}

HFONT MdzFont::GetHandle()
{
	LOGFONT lf;
	Init(lf, TRUE);
	return CreateFontIndirect(&lf);
}

//BOOL MdzFont::ChooseFont(MdzCtrl* lpCtrl)
BOOL MdzFont::ChooseFont()
{
	LOGFONT lf;
	Init(lf, TRUE);
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof(cf);  
	//cf.hwndOwner = lpCtrl->GetHandle();
	cf.hwndOwner = GetActiveWindow();
	cf.lpLogFont = &lf; 
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS; 
	if (::ChooseFont(&cf))
	{
		Init(lf, FALSE);
		return TRUE;
	}
	return FALSE;
}




void MdzFont::Init(LOGFONT &lf, BOOL bGet)
{
	if (bGet)
	{
		ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = -MulDiv(iSize, logPixelSy, 72);
		if ((iStyle & K_ITALIC) != 0)
			lf.lfItalic = TRUE;
		lf.lfWeight = ((iStyle & K_BOLD) != 0) ? FW_BOLD : FW_NORMAL;
		strcpy(lf.lfFaceName, strName);
	}
	else
	{
		strName = lf.lfFaceName;
		iSize = abs(MulDiv(lf.lfHeight, 72, logPixelSy));
		iStyle = 0;
		if (lf.lfWeight == FW_BOLD)
			iStyle |= K_BOLD;
		if (lf.lfItalic)
			iStyle |= K_ITALIC;
	}
}

MdzFont::MdzFont(HFONT hFont)
{
	LOGFONT lf;
	::GetObject(hFont, sizeof(lf), &lf);
	Init(lf, FALSE);

}







MdzFont::MdzFont(const MdzFont &font)
{
	strName = font.strName;
	iSize = font.iSize;
	iStyle = font.iStyle;
}

void MdzFont::operator =(const MdzFont &font)
{
	if (&font != this)
	{
		strName = font.strName;
		iSize = font.iSize;
		iStyle = font.iStyle;
	}
}

MdzFont MdzFont::GetDefaultGuiFont()
{
	return MdzFont((HFONT) GetStockObject(DEFAULT_GUI_FONT));
}

MdzString MdzFont::ToString()
{
	return MdzString::Format("%s,%d,%d", (char*)strName, iSize, iStyle);
}

MdzSize MdzFont::MeasureString(LPSTR strText)
{
	HDC hdc = GetDC(NULL);
	HFONT hFont = GetHandle();
	SelectObject(hdc, hFont);
	MdzSize sz;
	GetTextExtentPoint32(hdc, strText, strlen(strText), &sz);
	ReleaseDC(NULL, hdc);
	DeleteObject(hFont);
	return sz;
}
