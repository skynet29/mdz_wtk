// MdzPoint.cpp: implementation of the MdzPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzPoint.h"
#include "MdzCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzPoint::MdzPoint()
{
	x = 0;
	y = 0;
}

MdzPoint::~MdzPoint()
{

}

MdzPoint::MdzPoint(int x, int y)
{
	MEMBER_SET(x);
	MEMBER_SET(y);
}

void MdzPoint::ToScreen(MdzCtrl &ctrl)
{
	ClientToScreen(ctrl.GetHandle(), this);
}

void MdzPoint::ToClient(MdzCtrl &ctrl)
{
	ScreenToClient(ctrl.GetHandle(), this);
}
