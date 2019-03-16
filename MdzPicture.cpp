// MdzPicture.cpp: implementation of the MdzPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzPicture.h"
#include "MdzWindow.h"
#include "MdzGraphic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzPicture::MdzPicture()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	lpWnd->OnPaint = MDZ_CBK4(MdzPicture, OnPaint);
}

MdzPicture::~MdzPicture()
{

}

void MdzPicture::OnPaint(MdzGraphic &graphic)
{
	HBITMAP hBitmap = bitmap.GetHandle();
	if (hBitmap)
	{
		MdzSize bmSize = bitmap.GetSize();
		MdzRect rc;
		GetClientRect(GetHandle(), &rc);
		HDC hDC = graphic.GetHandle();
		HDC hMemDC = CreateCompatibleDC(hDC);
		SelectObject(hMemDC, hBitmap);
		StretchBlt(hDC, 0, 0, rc.Width(), rc.Height(), hMemDC, 0, 0, bmSize.cx, bmSize.cy, SRCCOPY);
		DeleteDC(hMemDC);
	}
}

void MdzPicture::SetBitmap(MdzBitmap bitmap)
{
	MEMBER_SET(bitmap);
	lpWnd->Redraw(TRUE);
}

void MdzPicture::SetBorder(BOOL bHasBorder)
{
	lpWnd->ModifyStyle(WS_BORDER, bHasBorder);
}

void MdzPicture::Clear()
{
	bitmap = MdzBitmap();
	lpWnd->Redraw(TRUE);
	
}
