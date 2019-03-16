// MdzRect.cpp: implementation of the MdzRect class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzRect.h"
#include "MdzBounds.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzRect::MdzRect()
{
	SetRectEmpty(this);
}



MdzRect::MdzRect(int left, int top, int right, int bottom)
{
	SetRect(this, left, top, right, bottom);
}	

int MdzRect::Width()
{
	return abs(left - right);
}

int MdzRect::Height()
{
	return abs(top - bottom);
}

BOOL MdzRect::Contains(int x, int y)
{
	POINT pt = {x, y};
	return PtInRect(this, pt);
}

MdzRect::MdzRect(MdzPoint p1, MdzPoint p2)
{
	SetRect(this, p1.x, p1.y, p2.x, p2.y);
}


void MdzRect::Inflate(int dx, int dy)
{
	InflateRect(this, dx, dy);
}

void MdzRect::operator +=(const MdzRect &rect)
{
	MdzRect dest;
	UnionRect(&dest, this, &rect);
	CopyRect(this, &dest);
}
