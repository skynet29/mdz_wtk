// MdzRect.h: interface for the MdzRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZRECT_H__163B65F9_80B8_4B95_A6F4_66A5EC5DE82B__INCLUDED_)
#define AFX_MDZRECT_H__163B65F9_80B8_4B95_A6F4_66A5EC5DE82B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzPoint.h"
//#include "MdzBounds.h"
class MdzBounds;

class DllExport MdzRect : public tagRECT
{
public:
	MdzRect(MdzPoint p1, MdzPoint p2);
	MdzRect();
	MdzRect(int left, int top, int right, int bottom);

	void
	Inflate(int dx, int dy);

	int
	Height();

	int
	Width();
	
	BOOL
	Contains(int x, int y);
	void operator +=(const MdzRect &rect);

};

#endif // !defined(AFX_MDZRECT_H__163B65F9_80B8_4B95_A6F4_66A5EC5DE82B__INCLUDED_)
