// MdzPen.h: interface for the MdzPen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZPEN_H__CA596F18_EED5_4DD2_8DE2_33B715E6A0F9__INCLUDED_)
#define AFX_MDZPEN_H__CA596F18_EED5_4DD2_8DE2_33B715E6A0F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzPen  
{
public:
	void SetWidth(int iWidth);
	void SetColor(COLORREF color);
	HPEN Select(HDC hdc);
	MdzPen();
	virtual ~MdzPen();
private:
	void Destroy();
	HPEN hPen;
	COLORREF color;
	int iWidth;
};

#endif // !defined(AFX_MDZPEN_H__CA596F18_EED5_4DD2_8DE2_33B715E6A0F9__INCLUDED_)
