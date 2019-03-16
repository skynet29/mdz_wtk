// MdzCheckBox.h: interface for the MdzCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCHECKBOX_H__C129986A_8BB5_4F8A_99B9_ED7E7BF961BA__INCLUDED_)
#define AFX_MDZCHECKBOX_H__C129986A_8BB5_4F8A_99B9_ED7E7BF961BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"

class MdzEvent;

class DllExport MdzCheckBox : public MdzCtrl  
{
public:
	MdzCheckBox();

	void
	SetOnClick(MdzCbk1* lpFunc);

	void
	SetChecked(BOOL bIsChecked);

	void
	SetCaption(LPSTR strCaption);

	BOOL
	IsChecked();

	virtual void
	Create();

	virtual ~MdzCheckBox();

private:
	void OnCommand(MdzEvent& evt);
	MdzCbk1* lpOnClick;
	BOOL bIsChecked;
};

#endif // !defined(AFX_MDZCHECKBOX_H__C129986A_8BB5_4F8A_99B9_ED7E7BF961BA__INCLUDED_)
