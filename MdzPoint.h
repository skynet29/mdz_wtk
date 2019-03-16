// MdzPoint.h: interface for the MdzPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZPOINT_H__5081A08D_D9E1_4C4A_B2F3_D99D62D8B9EF__INCLUDED_)
#define AFX_MDZPOINT_H__5081A08D_D9E1_4C4A_B2F3_D99D62D8B9EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzCtrl;

class DllExport MdzPoint : public tagPOINT  
{
public:
	void ToClient(MdzCtrl &ctrl);
	void ToScreen(MdzCtrl& ctrl);
	MdzPoint(int x, int y);
	MdzPoint();
	virtual ~MdzPoint();

};

#endif // !defined(AFX_MDZPOINT_H__5081A08D_D9E1_4C4A_B2F3_D99D62D8B9EF__INCLUDED_)
