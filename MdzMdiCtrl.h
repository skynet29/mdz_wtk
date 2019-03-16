// MdzMdiCtrl.h: interface for the MdzMdiCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMDICTRL_H__951FAEF6_5531_43B0_B9FB_9F7B589E8B85__INCLUDED_)
#define AFX_MDZMDICTRL_H__951FAEF6_5531_43B0_B9FB_9F7B589E8B85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"

class MdzMenu;
class MdzMdiChild;

class DllExport MdzMdiCtrl : public MdzCtrl  
{
public:
	MdzMdiCtrl();
	
	void
	CreateChild(MdzMdiChild* lpChild);

	MdzCtrl*
	GetActiveChild();

	void
	SetWndMenu(MdzMenu& menu);

	void
	TileVertically();

	void
	TileHorizontally();
	
	void
	Cascade();
	
	virtual ~MdzMdiCtrl();
private:
	CLIENTCREATESTRUCT ccs;

};

#endif // !defined(AFX_MDZMDICTRL_H__951FAEF6_5531_43B0_B9FB_9F7B589E8B85__INCLUDED_)
