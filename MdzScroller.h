// MdzScroller.h: interface for the MdzScroller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSCROLLER_H__B565AE61_E598_4163_A76E_2F9C3A843C15__INCLUDED_)
#define AFX_MDZSCROLLER_H__B565AE61_E598_4163_A76E_2F9C3A843C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzCtrl;

class MdzScroller  
{
public:
	void SetPos(UINT iPos);
	UINT GetPos();
	void Scroll(UINT  iCode, UINT iTrackPos);
	void Resize(UINT iNewSize);
	void Create();
	MdzScroller(MdzCtrl* lpParent, UINT iRange, UINT iIncrement, UINT iType);
	virtual ~MdzScroller();
private:
	MdzCtrl* lpParent;
	UINT iRange;
	UINT iIncrement;
	UINT iType;

};

#endif // !defined(AFX_MDZSCROLLER_H__B565AE61_E598_4163_A76E_2F9C3A843C15__INCLUDED_)
