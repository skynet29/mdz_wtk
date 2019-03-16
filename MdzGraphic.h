// MdzGraphic.h: interface for the MdzGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZGRAPHIC_H__7922B19F_D950_46A7_8125_6ACCBB57BB41__INCLUDED_)
#define AFX_MDZGRAPHIC_H__7922B19F_D950_46A7_8125_6ACCBB57BB41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzRect.h"
#include "MdzBitmap.h"	// Added by ClassView

class MdzBitmap;
class MdzPen;
class MdzBrush;
class MdzCtrl;
class MdzFont;

class DllExport MdzGraphic  
{
public:
	void DrawBitmapDisabled(MdzBitmap& bitmap, int x, int y);
	void DrawBitmapTransparent(MdzBitmap& bitmap, int x, int y, COLORREF clTransparent = -1);
	void DrawSingleString(LPSTR str, MdzRect rc, UINT iTextAlignment = K_LEFT);
	void DrawString(LPSTR str, MdzRect rc);
	BOOL IsValid();
	void Init(HDC hDC);
	void Release();
	void Init(MdzCtrl& ctrl);
	MdzGraphic();

	MdzBitmap
	CopyArea(MdzRect rc);






	HDC
	GetHandle();

	void
	SetColor(COLORREF color);

	void
	SetFont(MdzFont& font);
	
	void
	SetDrawMode(UINT iMode);

	void
	DrawLine(MdzRect rc);

	void
	DrawOval(MdzRect rc);
	
	void
	DrawRect(MdzRect rc);
	
	void
	DrawString(LPSTR str, int x, int y);
	
	void
	DrawBitmap(MdzBitmap& bitmap, int x, int y);
	
	void
	FillOval(MdzRect rc);
	
	void
	FillRect(MdzRect rc);

	static const UINT K_NORMAL;
	static const UINT K_NOT;
	static const UINT K_XOR;

	static const UINT K_LEFT;
	static const UINT K_RIGHT;
	static const UINT K_CENTER;

	virtual ~MdzGraphic();

private:
	HDC			hDC;
	HWND		hWnd;
	MdzPen*		lpPen;
	MdzBrush*	lpBrush;
	HFONT		hFont;
};

#endif // !defined(AFX_MDZGRAPHIC_H__7922B19F_D950_46A7_8125_6ACCBB57BB41__INCLUDED_)
