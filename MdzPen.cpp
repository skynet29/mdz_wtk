// MdzPen.cpp: implementation of the MdzPen class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzPen.h"
#include "MdzColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzPen::MdzPen()
{
	hPen = NULL;
	color = MdzColor::K_BLACK;
	iWidth = 1;
}

MdzPen::~MdzPen()
{
	Destroy();
}

HPEN MdzPen::Select(HDC hdc)
{
	if (!hPen)
		hPen = CreatePen(PS_SOLID, iWidth, color);

	return (HPEN) SelectObject(hdc, hPen);
}

void MdzPen::Destroy()
{
	if (hPen)
	{
		DeleteObject(hPen);
		hPen = NULL;
	}
}

void MdzPen::SetColor(COLORREF color)
{
	if (this->color != color)
	{
		MEMBER_SET(color);
		Destroy();
	}
}

void MdzPen::SetWidth(int iWidth)
{
	if (this->iWidth != iWidth)
	{
		MEMBER_SET(iWidth);
		Destroy();
	}

}
