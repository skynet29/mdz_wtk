// MdzRadioButton.h: interface for the MdzRadioButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZRADIOBUTTON_H__9597E963_3246_4F59_82C4_89C964964242__INCLUDED_)
#define AFX_MDZRADIOBUTTON_H__9597E963_3246_4F59_82C4_89C964964242__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"

class MdzEvent;

class DllExport MdzRadioButton : public MdzCtrl  
{
public:
public:
	MdzRadioButton();

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

	virtual ~MdzRadioButton();

private:
	void OnCommand(MdzEvent& evt);
	BOOL bIsChecked;
	MdzCbk1* lpOnClick;

};

#endif // !defined(AFX_MDZRADIOBUTTON_H__9597E963_3246_4F59_82C4_89C964964242__INCLUDED_)
