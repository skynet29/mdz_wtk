// MdzDlgInput.h: interface for the MdzDlgInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDLGINPUT_H__54FF5189_74F1_41FB_8B3E_D40F5B603829__INCLUDED_)
#define AFX_MDZDLGINPUT_H__54FF5189_74F1_41FB_8B3E_D40F5B603829__INCLUDED_

#include "MdzString.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzDialogEx.h"
#include "MdzButton.h"
#include "MdzLabel.h"
#include "MdzTextField.h"


class MdzDlgInput : public MdzDialogEx  
{
public:
	void SetText(LPSTR strText);
	MdzString GetText();
	virtual void OnFocus(UINT bGotFocus);
	MdzDlgInput();
	virtual ~MdzDlgInput();
	void SetLabel(LPSTR strText);
private:
	MdzTextField textField;
	MdzLabel label;

};

#endif // !defined(AFX_MDZDLGINPUT_H__54FF5189_74F1_41FB_8B3E_D40F5B603829__INCLUDED_)
