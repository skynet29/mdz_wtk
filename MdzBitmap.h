// MdzBitmap.h: interface for the MdzBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBITMAP_H__DFDBE0EB_FB69_4263_B696_11C2704FDE25__INCLUDED_)
#define AFX_MDZBITMAP_H__DFDBE0EB_FB69_4263_B696_11C2704FDE25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzSize.h"	// Added by ClassView

class MdzBmpInternal;

class DllExport MdzBitmap  
{
public:
	void MapColor(COLORREF clOldColor, COLORREF clNewColor);
	MdzBitmap GetMask(COLORREF clTransparent);
	MdzBitmap Clone();
	MdzBitmap();
	MdzBitmap(LPSTR strFileName);
	MdzBitmap(UINT iResId, HMODULE hModule = NULL);
	MdzBitmap(HBITMAP hBitmap);
	MdzBitmap(const MdzBitmap& bitmap);

	void
	operator =(const MdzBitmap &bitmap);

	BOOL
	operator ==(const MdzBitmap &bitmap);

	virtual ~MdzBitmap();

	MdzSize
	GetSize();

	void
	MapColor(COLORREF clNewColor);
	
	HBITMAP
	GetHandle();


private:
	MdzBmpInternal* lpData;
};

#endif // !defined(AFX_MDZBITMAP_H__DFDBE0EB_FB69_4263_B696_11C2704FDE25__INCLUDED_)
