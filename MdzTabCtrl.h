// MdzTabCtrl.h: interface for the MdzTabCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTABCTRL_H__8E8ECBD8_E952_44B4_927A_05F8A0728103__INCLUDED_)
#define AFX_MDZTABCTRL_H__8E8ECBD8_E952_44B4_927A_05F8A0728103__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzVector.h"

class MdzEvent;

class DllExport MdzTabCtrl : public MdzCtrl  
{
public:
	void SetSelIndex(UINT iIndex);
	MdzTabCtrl();
	
	UINT
	GetSelIndex();

	void
	AddTab(LPSTR strCaption, MdzCtrl& ctrl);

	virtual void
	Create();

	virtual ~MdzTabCtrl();
private:
	MdzCtrl* GetSelTab();
	void OnSize(int width, int height);
	void OnNotify(MdzEvent& evt);
	UINT iIndex;
	MdzVector tabs;

};

#endif // !defined(AFX_MDZTABCTRL_H__8E8ECBD8_E952_44B4_927A_05F8A0728103__INCLUDED_)
