// MdzDockBar.h: interface for the MdzDockBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDOCKBAR_H__A9FB0830_BA3F_4AA6_BD76_783279E47C4D__INCLUDED_)
#define AFX_MDZDOCKBAR_H__A9FB0830_BA3F_4AA6_BD76_783279E47C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzVector.h"

class MdzToolBar;
class MdzCbk6;
class MdzEvent;


class DllExport MdzDockBar : public MdzCtrl  
{
public:
	MdzDockBar();

	void
	SetToolBarVisible(MdzToolBar &toolbar, BOOL bIsVisible);

	void
	AddToolBar(MdzToolBar &toolbar, BOOL bBreak = FALSE);

	virtual ~MdzDockBar();
	
	virtual void
	Create();
private:
	void OnNotify(MdzEvent& evt);
	MdzVector toolbarList;

	friend class MdzFrame;
};

#endif // !defined(AFX_MDZDOCKBAR_H__A9FB0830_BA3F_4AA6_BD76_783279E47C4D__INCLUDED_)
