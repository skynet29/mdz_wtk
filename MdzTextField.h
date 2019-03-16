// MdzTextField.h: interface for the MdzTextField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTEXTFIELD_H__5B3C14D6_4018_46FA_84AA_C73E1E41E430__INCLUDED_)
#define AFX_MDZTEXTFIELD_H__5B3C14D6_4018_46FA_84AA_C73E1E41E430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"	// Added by ClassView
#include "MdzCbk1.h"


class DllExport MdzTextField : public MdzCtrl  
{
public:
	MdzTextField();

	void
	Select();

	void
	SetDigitOnly(BOOL bIsNumber);

	void
	SetMaxChar(UINT iMaxChar);
	
	void
	SetPassword(BOOL bIsPassword);
	
	void
	SetText(LPSTR strText);

	MdzString
	GetText();
	
	virtual void
	Create();

	virtual ~MdzTextField();

private:
	UINT iMaxChar;

};

#endif // !defined(AFX_MDZTEXTFIELD_H__5B3C14D6_4018_46FA_84AA_C73E1E41E430__INCLUDED_)
