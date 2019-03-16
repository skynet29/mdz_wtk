// MdzLabel.cpp: implementation of the MdzLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzLabel.h"
#include "MdzWindow.h"
#include "MdzCbk4.h"
#include "MdzGraphic.h"
#include "MdzColor.h"
#include "MdzFont.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT MdzLabel::K_LEFT		= DT_LEFT;
const UINT MdzLabel::K_RIGHT	= DT_RIGHT;
const UINT MdzLabel::K_CENTER	= DT_CENTER;

MdzLabel::MdzLabel()
{
	iAlignment = DT_LEFT;

	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	lpWnd->bOpaque = FALSE;
	lpWnd->OnPaint = MDZ_CBK4(MdzLabel, OnPaint);

	clrText = MdzColor::K_BLACK;
	hFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
}

MdzLabel::~MdzLabel()
{
	if (hFont)
		DeleteObject(hFont);
}





void MdzLabel::SetText(LPSTR strText)
{
	MEMBER_SET(strText);
	lpWnd->Redraw(TRUE);
}

void MdzLabel::SetBorder(BOOL bHasBorder)
{
	lpWnd->ModifyStyle(WS_BORDER, bHasBorder);
}

void MdzLabel::SetAlignment(UINT iAlignment)
{
	switch (iAlignment)
	{
	case K_LEFT:
	case K_RIGHT:
	case K_CENTER:
		MEMBER_SET(iAlignment);
	}
}


void MdzLabel::SetBackColor(COLORREF color)
{
	lpWnd->bOpaque = TRUE;
	lpWnd->backColor = color;
	lpWnd->Redraw(TRUE);
}

void MdzLabel::SetTextColor(COLORREF clrText)
{
	MEMBER_SET(clrText);
	lpWnd->Redraw(TRUE);
}

void MdzLabel::OnPaint(MdzGraphic &g)
{
	HDC hdc = g.GetHandle();
	RECT rc;
	GetClientRect(GetHandle(), &rc);
	SelectObject(hdc, hFont);
	::SetTextColor(hdc, clrText);
	DrawText(hdc, strText, strText.GetLength(), &rc,
		DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | iAlignment);
}

void MdzLabel::SetFont(MdzFont &font)
{
	if (hFont)
		DeleteObject(hFont);

	hFont = font.GetHandle();
	lpWnd->Redraw(TRUE);
}

MdzString MdzLabel::GetText()
{
	return strText;
}
