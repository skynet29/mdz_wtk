// MdzContainer.h: interface for the MdzContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCONTAINER_H__F4AD3638_115B_47D4_BF35_838767DD0472__INCLUDED_)
#define AFX_MDZCONTAINER_H__F4AD3638_115B_47D4_BF35_838767DD0472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzVector.h"
#include "MdzSize.h"
#include "MdzString.h"	// Added by ClassView

class DllExport MdzContainer : public MdzCtrl  
{
public:
	DEFINE_STD_METHODS(MdzContainer, MdzCtrl)
	void Add(MdzCtrl& ctrl, MdzSize& size);
	MdzRect GetClientRect();
	
	MdzContainer();
	
	void
	Add(MdzCtrl& ctrl, MdzBounds& bounds);

	void
	Add(MdzCtrl& ctrl);

	void
	Pack(int xPad = 0, int yPad = 0);

	virtual ~MdzContainer();


	virtual void
	OnCreate();
private:
	MdzVectorT<MdzCtrl> childs;
	friend class MdzLayout;

};

#endif // !defined(AFX_MDZCONTAINER_H__F4AD3638_115B_47D4_BF35_838767DD0472__INCLUDED_)
