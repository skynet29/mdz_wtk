// MdzToolBar.h: interface for the MdzToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTOOLBAR_H__0693889E_E26A_4882_9687_135A8143EBC3__INCLUDED_)
#define AFX_MDZTOOLBAR_H__0693889E_E26A_4882_9687_135A8143EBC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"
#include "MdzRect.h"
#include "MdzVector.h"
#include "MdzBitmap.h"

#include "MdzToolButton.h"

class MdzEvent;

class DllExport MdzToolBar : public MdzCtrl  
{
public:


	MdzToolBar();

	void
	AddCtrl(MdzCtrl& ctrl, int iWidth, int iHeight);
	
	void
	AddSeparator();
	
	void
	AddButton(MdzToolButton& btn, MdzBitmap bitmap, UINT iStyle = MdzToolButton::K_BUTTON);
	

	virtual void
	Create();
	
	virtual ~MdzToolBar();
private:
	MdzToolButton* GetButton(UINT iIdent);
	void OnNotify(MdzEvent& evt);
	void OnCommand(MdzEvent& evt);
	UINT	GetIdent();
	UINT	GetWidth();

	MdzVector	btnList;
	BOOL		bIsLargeIcon;
	UINT		iIdent;
	COLORREF	maskColor;
	BOOL		bBreak;

	friend class MdzDockBar;
};

#endif // !defined(AFX_MDZTOOLBAR_H__0693889E_E26A_4882_9687_135A8143EBC3__INCLUDED_)
