// MdzBrush.cpp: implementation of the MdzBrush class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzBrush.h"
#include "MdzColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzBrush::MdzBrush()
{
	hBrush = NULL;
	color = MdzColor::K_BLACK;
}

MdzBrush::~MdzBrush()
{
	Destroy();
}

void MdzBrush::Destroy()
{
	if (hBrush)
	{
		DeleteObject(hBrush);
		hBrush = NULL;
	}
}

HBRUSH MdzBrush::Select(HDC hdc)
{
	if (!hBrush)
		hBrush = CreateSolidBrush(color);

	return (HBRUSH) SelectObject(hdc, hBrush);
}

void MdzBrush::SetColor(COLORREF color)
{
	if (this->color != color)
	{
		MEMBER_SET(color);
		Destroy();
	}
}

HBRUSH MdzBrush::SetHollowBrush(HDC hdc)
{
	return (HBRUSH) SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
}
