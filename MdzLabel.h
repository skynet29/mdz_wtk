// MdzLabel.h: interface for the MdzLabel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZLABEL_H__3F2D2BFF_42BC_48D4_97D7_6423B921A1A8__INCLUDED_)
#define AFX_MDZLABEL_H__3F2D2BFF_42BC_48D4_97D7_6423B921A1A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"

class MdzGraphic;

class DllExport MdzLabel : public MdzCtrl  
{
public:
	MdzString GetText();
	MdzLabel();

	void
	SetFont(MdzFont& font);

	void
	SetTextColor(COLORREF clrColor);
	
	void
	SetBackColor(COLORREF color);
	
	void
	SetAlignment(UINT iAlignment);
	
	void
	SetBorder(BOOL bHasBorder);
	
	void
	SetText(LPSTR strText);

	virtual ~MdzLabel();


	static const UINT K_LEFT;
	static const UINT K_RIGHT;
	static const UINT K_CENTER;

private:
	void OnPaint(MdzGraphic& g);
	UINT iAlignment;
	COLORREF clrText;
	MdzString strText;
	HFONT hFont;
};

#endif // !defined(AFX_MDZLABEL_H__3F2D2BFF_42BC_48D4_97D7_6423B921A1A8__INCLUDED_)
