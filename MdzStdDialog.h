// MdzStdDialog.h: interface for the MdzStdDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSTDDIALOG_H__85EEDB6F_68D9_4EF8_AB37_D1671BF25BE9__INCLUDED_)
#define AFX_MDZSTDDIALOG_H__85EEDB6F_68D9_4EF8_AB37_D1671BF25BE9__INCLUDED_

#include "MdzString.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzCtrl;

class DllExport MdzStdDialog  
{
public:
	static const UINT K_YES;
	static const UINT K_NO;
	static const UINT K_CANCEL;

	static UINT
	ShowConfirm(LPSTR strText, LPSTR strTitle = NULL);
	
	static MdzString
	ShowInput(LPSTR strText = NULL, LPSTR strTitle = NULL);
	
	static void
	ShowMessage(LPSTR strText, LPSTR strTitle = NULL);

};

#endif // !defined(AFX_MDZSTDDIALOG_H__85EEDB6F_68D9_4EF8_AB37_D1671BF25BE9__INCLUDED_)
