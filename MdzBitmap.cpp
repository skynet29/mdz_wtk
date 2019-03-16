// MdzBitmap.cpp: implementation of the MdzBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzBitmap.h"
#include "MdzColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
class MdzBmpInternal
{
public:
	UINT iRefCount;
	HBITMAP hBitmap;

	MdzBmpInternal(HBITMAP hBitmap)
	{
		MEMBER_SET(hBitmap);
		iRefCount = 1;
	}

	~MdzBmpInternal()
	{
		DeleteObject(hBitmap);
	}
};

MdzBitmap::MdzBitmap(LPSTR strFileName)
{
	HBITMAP hBitmap = (HBITMAP) LoadImage(NULL, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	lpData = (hBitmap) ? new MdzBmpInternal(hBitmap) : NULL;
}

MdzBitmap::~MdzBitmap()
{
	if (lpData && --lpData->iRefCount == 0)
		delete lpData;
}

HBITMAP MdzBitmap::GetHandle()
{
	return (lpData) ? lpData->hBitmap : NULL;
}

MdzBitmap::MdzBitmap()
{
	lpData = NULL;
}


void MdzBitmap::MapColor(COLORREF sysColor)
{
	if (lpData)
	{
		HBITMAP hBitmap = lpData->hBitmap;
		MdzSize sz = GetSize();

		HDC hDC = GetDC(NULL);
		HDC hMemDC = CreateCompatibleDC(hDC);

		SelectObject(hMemDC, hBitmap);


		//COLORREF sysColor = GetSysColor(COLOR_BTNFACE);
		//if (clMaskColor == -1)
		COLORREF clMaskColor = GetPixel(hMemDC, 0, 0);


		for (int y = 0; y < sz.cy; y++)
		{
			for (int x = 0; x < sz.cx; x++)
			{
				COLORREF color = GetPixel(hMemDC, x, y);
				if (color == clMaskColor)
					SetPixel(hMemDC, x, y, sysColor);
			}
		}

		DeleteDC(hMemDC);
		ReleaseDC(NULL, hDC);
	}
}


MdzBitmap::MdzBitmap(const MdzBitmap &bitmap)
{
	lpData = bitmap.lpData;
	if (lpData)
		lpData->iRefCount++;
}

void MdzBitmap::operator =(const MdzBitmap &bitmap)
{
	if (this != &bitmap)
	{
		if (lpData && --lpData->iRefCount == 0)
			delete lpData;

		lpData = bitmap.lpData;
		if (lpData)
			lpData->iRefCount++;
	}
}

MdzBitmap::MdzBitmap(UINT iResId, HMODULE hModule)
{
	HBITMAP hBitmap = LoadBitmap((hModule) ? hModule : GetModuleHandle(NULL),
		MAKEINTRESOURCE(iResId));

	lpData = new MdzBmpInternal(hBitmap);
}

MdzSize MdzBitmap::GetSize()
{
	MdzSize ret;

	if (lpData)
	{
		BITMAP bm;
		GetObject(lpData->hBitmap, sizeof(bm), &bm);
		ret.cx = bm.bmWidth;
		ret.cy = bm.bmHeight;
	}
	return ret;

}

MdzBitmap::MdzBitmap(HBITMAP hBitmap)
{
	lpData = new MdzBmpInternal(hBitmap);

}

BOOL MdzBitmap::operator ==(const MdzBitmap &bitmap)
{
	return (lpData == bitmap.lpData);
}

MdzBitmap MdzBitmap::Clone()
{
	if (!lpData)
		return MdzBitmap();

	HDC hDC = GetDC(NULL);
	HDC hSrcDC = CreateCompatibleDC(hDC);
	MdzSize sz = GetSize();

	SelectObject(hSrcDC, lpData->hBitmap);

	HDC hDestDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, sz.cx, sz.cy);
	SelectObject(hDestDC, hBitmap);	

	BitBlt(hDestDC, 0, 0, sz.cx, sz.cy, hSrcDC, 0, 0, SRCCOPY);
	DeleteDC(hSrcDC);
	DeleteDC(hDestDC);
	ReleaseDC(NULL, hDC);
	return MdzBitmap(hBitmap);

}

MdzBitmap MdzBitmap::GetMask(COLORREF clTransparent)
{
	if (!lpData)
		return MdzBitmap();
	MdzSize sz = GetSize();
	HBITMAP hBitmap = CreateBitmap(sz.cx, sz.cy, 1, 1, NULL);
	HDC hDC = GetDC(NULL);

	HDC hSrcDC = CreateCompatibleDC(hDC);
	SelectObject(hSrcDC, lpData->hBitmap);
	SetBkColor(hSrcDC, clTransparent);

	HDC hDestDC = CreateCompatibleDC(hDC);
	SelectObject(hDestDC, hBitmap);

	BitBlt(hDestDC, 0, 0, sz.cx, sz.cy, hSrcDC, 0, 0, SRCCOPY);

	DeleteDC(hSrcDC);
	DeleteDC(hDestDC);
	ReleaseDC(NULL, hDC);

	return hBitmap;
}

void MdzBitmap::MapColor(COLORREF clOldColor, COLORREF clNewColor)
{
	if (lpData)
	{
		HBITMAP hBitmap = lpData->hBitmap;
		MdzSize sz = GetSize();

		HDC hDC = GetDC(NULL);
		HDC hMemDC = CreateCompatibleDC(hDC);

		SelectObject(hMemDC, hBitmap);

		for (int y = 0; y < sz.cy; y++)
		{
			for (int x = 0; x < sz.cx; x++)
			{
				COLORREF color = GetPixel(hMemDC, x, y);
				if (color == clOldColor)
					SetPixel(hMemDC, x, y, clNewColor);
			}
		}

		DeleteDC(hMemDC);
		ReleaseDC(NULL, hDC);
	}
}
