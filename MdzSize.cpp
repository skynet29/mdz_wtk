// MdzSize.cpp: implementation of the MdzSize class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSize.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSize::MdzSize()
{
	cx = 0;
	cy = 0;
}

MdzSize::~MdzSize()
{

}

MdzSize::MdzSize(int cx, int cy)
{
	MEMBER_SET(cx);
	MEMBER_SET(cy);
}
