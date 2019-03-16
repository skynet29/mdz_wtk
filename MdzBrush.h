// MdzBrush.h: interface for the MdzBrush class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBRUSH_H__8646D3AB_7F0E_44ED_ACF6_7A72955D22B5__INCLUDED_)
#define AFX_MDZBRUSH_H__8646D3AB_7F0E_44ED_ACF6_7A72955D22B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mdztypes.h"

class MdzBrush  
{
public:
	static HBRUSH SetHollowBrush(HDC hdc);
	void SetColor(COLORREF color);
	HBRUSH Select(HDC hdc);
	MdzBrush();
	virtual ~MdzBrush();
private:
	void Destroy();
	HBRUSH hBrush;
	COLORREF color;

};

#endif // !defined(AFX_MDZBRUSH_H__8646D3AB_7F0E_44ED_ACF6_7A72955D22B5__INCLUDED_)
