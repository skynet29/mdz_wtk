// MdzMenuBar.h: interface for the MdzMenuBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMENUBAR_H__5B05FAFF_58EB_449F_88CC_596059364329__INCLUDED_)
#define AFX_MDZMENUBAR_H__5B05FAFF_58EB_449F_88CC_596059364329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class MdzMenu;
class MdzCtrl;

class DllExport MdzMenuBar  
{
public:
	MdzMenuBar();
	
	void
	Add(MdzMenu& menu, LPSTR strCaption);

	HMENU
	GetHandle();

	virtual ~MdzMenuBar();
private:
	HMENU hMenu;
	MdzCtrl* lpParent;

	friend class MdzFrame;
};

#endif // !defined(AFX_MDZMENUBAR_H__5B05FAFF_58EB_449F_88CC_596059364329__INCLUDED_)
