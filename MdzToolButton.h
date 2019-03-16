// MdzToolButton.h: interface for the MdzToolButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTOOLBUTTON_H__EF396997_5D2C_401F_A56C_F8A32B6022DB__INCLUDED_)
#define AFX_MDZTOOLBUTTON_H__EF396997_5D2C_401F_A56C_F8A32B6022DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzRect.h"	// Added by ClassView
#include "MdzCbk1.h"
#include "MdzBitmap.h"
#include "MdzString.h"

class MdzWindow;
class MdzCtrl;

class DllExport MdzToolButton : public MdzObject
{
public:
	void SetAutoDelete(BOOL bAutoDelete);
	static const UINT K_BUTTON;
	static const UINT K_CHECK;
	static const UINT K_CHECKGROUP;


	MdzToolButton();

	BOOL
	IsEnabled();
	
	BOOL
	IsChecked();
	
	void
	SetToolTips(LPSTR strToolTips);
	
	void
	SetOnClick(MdzCbk1* lpFunc);
	
	void
	SetEnabled(BOOL bIsEnabled);
	
	void
	SetChecked(BOOL bIsChecked);
	
	virtual ~MdzToolButton();
private:
	void Init(MdzWindow* lpWnd);
	void Init(MdzWindow *lpWnd, MdzCtrl* lpCtrl, int iWidth);
	void Init(MdzWindow* lpWnd, MdzBitmap bitmap, UINT iStyle);
	MdzRect GetItemRect();
	void Create();
	TBBUTTON tbb;
	MdzWindow *lpWnd;
	MdzBitmap bitmap;
	MdzCtrl* lpCtrl;
	BOOL bAutoDelete;
	MdzCbk1* lpOnClick;
	MdzString strToolTips;


	friend class MdzEvtToolTipsHandler;
	friend class MdzToolBar;
};

#endif // !defined(AFX_MDZTOOLBUTTON_H__EF396997_5D2C_401F_A56C_F8A32B6022DB__INCLUDED_)
