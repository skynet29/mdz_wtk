// MdzFont.h: interface for the MdzFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZFONT_H__547CF3DB_09AE_4106_AC77_1508723093C3__INCLUDED_)
#define AFX_MDZFONT_H__547CF3DB_09AE_4106_AC77_1508723093C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MdzString.h"
#include "MdzSize.h"	// Added by ClassView

class MdzCtrl;

class DllExport MdzFont
{
public:
	MdzSize MeasureString(LPSTR strText);
	MdzString ToString();
	static MdzFont GetDefaultGuiFont();
	MdzFont();
	MdzFont(const MdzFont& font);
	MdzFont(HFONT hFont);
	MdzFont(LPSTR fontName, UINT iSize, UINT iStyle = 0);

	void 
	operator =(const MdzFont &font);




	HFONT
	GetHandle();

	BOOL
	ChooseFont();

	static void
	InitClass();

	static const UINT K_ITALIC;
	static const UINT K_BOLD;

	virtual ~MdzFont();
	UINT iSize;
	UINT iStyle;
	MdzString strName;
private:
	void Init(LOGFONT& lf, BOOL bGet);
	friend class MdzWindow;
};

#endif // !defined(AFX_MDZFONT_H__547CF3DB_09AE_4106_AC77_1508723093C3__INCLUDED_)
