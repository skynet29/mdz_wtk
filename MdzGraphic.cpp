// MdzGraphic.cpp: implementation of the MdzGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzCtrl.h"
#include "MdzGraphic.h"
#include "MdzBitmap.h"
#include "MdzPen.h"
#include "MdzBrush.h"
#include "MdzFont.h"
#include "MdzColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT MdzGraphic::K_NORMAL	= R2_COPYPEN;
const UINT MdzGraphic::K_NOT	= R2_NOT;
const UINT MdzGraphic::K_XOR	= R2_XORPEN;

const UINT MdzGraphic::K_LEFT	= DT_LEFT;
const UINT MdzGraphic::K_RIGHT	= DT_RIGHT;
const UINT MdzGraphic::K_CENTER	= DT_CENTER;

MdzGraphic::MdzGraphic()
{
	hWnd = NULL;
	lpPen = new MdzPen();
	lpBrush = new MdzBrush();
	hFont = NULL;
	hDC = NULL;

}

MdzGraphic::~MdzGraphic()
{
	delete lpPen;
	delete lpBrush;

	Release();
}

void MdzGraphic::DrawBitmap(MdzBitmap& bitmap, int x, int y)
{
	HBITMAP hBitmap = bitmap.GetHandle();
	if (hBitmap)
	{
		MdzSize bmSize = bitmap.GetSize();

		HDC hMemDC = CreateCompatibleDC(hDC);
		SelectObject(hMemDC, hBitmap);	
		BitBlt(hDC, x, y, bmSize.cx, bmSize.cy, hMemDC, 0, 0, SRCCOPY);
		DeleteDC(hMemDC);
	}
}

void MdzGraphic::DrawRect(MdzRect rc)
{
	MdzBrush::SetHollowBrush(hDC);
	lpPen->Select(hDC);

	Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

}

void MdzGraphic::DrawOval(MdzRect rc)
{
	MdzBrush::SetHollowBrush(hDC);
	lpPen->Select(hDC);

	Ellipse(hDC, rc.left, rc.top, rc.right, rc.bottom);

}

void MdzGraphic::DrawLine(MdzRect rc)
{
	lpPen->Select(hDC);

	MoveToEx(hDC, rc.left, rc.top, NULL);
	LineTo(hDC, rc.right, rc.bottom);

}

void MdzGraphic::DrawString(LPSTR str, int x, int y)
{
	if (hFont)
		SelectObject(hDC, hFont);

	TextOut(hDC, x, y, str, strlen(str));
}





void MdzGraphic::FillRect(MdzRect rc)
{
	lpPen->Select(hDC);
	lpBrush->Select(hDC);

	Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

}

void MdzGraphic::FillOval(MdzRect rc)
{
	lpPen->Select(hDC);
	lpBrush->Select(hDC);

	Ellipse(hDC, rc.left, rc.top, rc.right, rc.bottom);

}

void MdzGraphic::SetColor(COLORREF color)
{
	lpPen->SetColor(color);
	lpBrush->SetColor(color);

	SetTextColor(hDC, color);
}

void MdzGraphic::Init(MdzCtrl& ctrl)
{
	hWnd = ctrl.GetHandle();
	hDC = GetDC(hWnd);
	SetBkMode(hDC, TRANSPARENT);
}

HDC MdzGraphic::GetHandle()
{
	return hDC;
}

void MdzGraphic::SetFont(MdzFont &font)
{
	if (hFont)
		DeleteObject(hFont);

	hFont = font.GetHandle();
}

void MdzGraphic::SetDrawMode(UINT iMode)
{
	switch (iMode)
	{
	case K_NORMAL:
	case K_NOT:
	case K_XOR:
		break;
	default:
		return;
	}
	SetROP2(hDC, iMode);
}

//DEL void MdzGraphic::DrawOval(int x, int y, int w, int h)
//DEL {
//DEL 	DrawOval(MdzBounds(x, y, w, h));
//DEL }

//DEL void MdzGraphic::DrawRect(int x, int y, int w, int h)
//DEL {
//DEL 	DrawRect(MdzBounds(x, y, w, h));
//DEL }

//DEL void MdzGraphic::FillOval(int x, int y, int w, int h)
//DEL {
//DEL 	FillOval(MdzBounds(x, y, w, h));
//DEL 
//DEL }

//DEL void MdzGraphic::FillRect(int x, int y, int w, int h)
//DEL {
//DEL 	FillRect(MdzBounds(x, y, w, h));
//DEL 
//DEL }

//DEL void MdzGraphic::DrawLine(int x1, int y1, int x2, int y2)
//DEL {
//DEL 	DrawLine(MdzRect(x1, y1, x2, y2));
//DEL 
//DEL }

MdzBitmap MdzGraphic::CopyArea(MdzRect rc)
{
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.Width(), rc.Height());
	SelectObject(hMemDC, hBitmap);	
	BitBlt(hMemDC, 0, 0, rc.Width(), rc.Height(), hDC, rc.left, rc.top, SRCCOPY);
	DeleteDC(hMemDC);
	return MdzBitmap(hBitmap);
}

void MdzGraphic::Release()
{
	if (hWnd)	
		ReleaseDC(hWnd, hDC);

	if (hFont)
		DeleteObject(hFont);

	hFont = NULL;
	hWnd = NULL;
	hDC = NULL;
}

void MdzGraphic::Init(HDC hDC)
{
	MEMBER_SET(hDC);
	SetBkMode(hDC, TRANSPARENT);

}

BOOL MdzGraphic::IsValid()
{
	return (hDC != NULL);
}

void MdzGraphic::DrawString(LPSTR str, MdzRect rc)
{
	if (hFont)
		SelectObject(hDC, hFont);

	DrawText(hDC,  str, strlen(str), &rc, DT_WORDBREAK);

}



void MdzGraphic::DrawSingleString(LPSTR str, MdzRect rc, UINT iTextAlignment)
{
	if (hFont)
		SelectObject(hDC, hFont);

	DrawText(hDC,  str, strlen(str), &rc, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | iTextAlignment);

}

void MdzGraphic::DrawBitmapTransparent(MdzBitmap &bitmap, int x, int y, COLORREF clTransparent)
{
	HBITMAP hBitmap = bitmap.GetHandle();
	if (hBitmap)
	{
		MdzSize bmSize = bitmap.GetSize();

		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hOldBmp = (HBITMAP) SelectObject(hMemDC, hBitmap);	
		if (clTransparent == (COLORREF)-1)
			clTransparent = GetPixel(hMemDC, 0, 0);
		SelectObject(hMemDC, hOldBmp);
		MdzBitmap bmMask = bitmap.GetMask(clTransparent);

		SelectObject(hMemDC, hBitmap);	

		MaskBlt(hDC, x, y, bmSize.cx, bmSize.cy, hMemDC, 0, 0, bmMask.GetHandle(),
			0, 0, MAKEROP4(PATCOPY, SRCCOPY));
		//TransparentBlt(hDC, x, y, bmSize.cx, bmSize.cy, hMemDC, 0, 0, bmSize.cx, bmSize.cy, clTransparent);
		DeleteDC(hMemDC);
	}

}

void MdzGraphic::DrawBitmapDisabled(MdzBitmap &bitmap, int x, int y)
{
	HBITMAP hBitmap = bitmap.GetHandle();
	if (hBitmap)
	{
		MdzSize bmSize = bitmap.GetSize();
		
		MdzBitmap bm = bitmap.Clone();
		bm.MapColor(MdzColor::K_WHITE);

		DrawState(hDC, NULL, NULL, (LPARAM)bm.GetHandle(), 0, x, y, bmSize.cx, bmSize.cy,
			DST_BITMAP | DSS_DISABLED);
		

	}
}
