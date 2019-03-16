// MdzBounds.cpp: implementation of the MdzBounds class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzBounds.h"
#include "MdzRect.h"
#include "MdzStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzBounds::MdzBounds()
{
	left = top = 0;
	width = height = 0;
}



MdzBounds::MdzBounds(int left, int top, int width, int height)
{
	MEMBER_SET(left);
	MEMBER_SET(top);
	MEMBER_SET(width);
	MEMBER_SET(height);
}

MdzBounds::MdzBounds(MdzRect &rc)
{
	left = min(rc.left, rc.right);
	top = min(rc.top, rc.bottom);
	width = rc.Width();
	height = rc.Height();
}

MdzBounds::operator MdzRect()
{
	return MdzRect(left, top, left + width, top + height);
}






