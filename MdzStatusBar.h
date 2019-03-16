// MdzStatusBar.h: interface for the MdzStatusBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSTATUSBAR_H__C25449F9_D8A8_459B_A4CC_E21D736C0000__INCLUDED_)
#define AFX_MDZSTATUSBAR_H__C25449F9_D8A8_459B_A4CC_E21D736C0000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"

class DllExport MdzStatusBar : public MdzCtrl
{
public:
	MdzStatusBar();

	void
	SetText(LPSTR strText);

	virtual ~MdzStatusBar();
};

#endif // !defined(AFX_MDZSTATUSBAR_H__C25449F9_D8A8_459B_A4CC_E21D736C0000__INCLUDED_)
