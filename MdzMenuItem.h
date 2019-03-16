// MdzMenuItem.h: interface for the MdzMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMENUITEM_H__EBA9C356_EA54_40A5_8B45_477040561CC6__INCLUDED_)
#define AFX_MDZMENUITEM_H__EBA9C356_EA54_40A5_8B45_477040561CC6__INCLUDED_

#include "MdzString.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzObject.h"
#include "MdzCbk1.h"
#include "MdzBitmap.h"


class DllExport MdzMenuItem  : public MdzObject
{
public:
	void SetBitmap(MdzBitmap bitmap);
	MdzMenuItem();

	void
	SetOnClick(MdzCbk1* lpFunc);

	BOOL
	SetShortcut(UINT iKeyChanger, char character);
	
	void
	SetCaption(LPSTR strCaption);
	
	void
	SetEnabled(BOOL bIsEnabled);
	
	void
	SetChecked(BOOL bIsChecked);

	MdzString
	GetCaption();

	BOOL
	IsEnabled();
	
	BOOL
	IsChecked();

	virtual ~MdzMenuItem();
private:
	virtual void OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//static MdzMenuItem* GetPtrFromId(HMENU hMenu, UINT iIdent);
	static MdzMenuItem* GetPtrFromId(UINT iIdent);
	void Create(HMENU hMenu, LPSTR strCaption);
	virtual void OnMeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	UINT iIdent;
	UINT iPos;
	HMENU hMenu;
	BOOL bIsChecked;
	BOOL bIsEnabled;
	MdzCbk1* lpOnClick;
	LPACCEL lpAccel;
	MdzBitmap bitmap;
	MdzString strCaption;

	friend class MdzMenu;
	friend class MdzWindow;
protected:
};

#endif // !defined(AFX_MDZMENUITEM_H__EBA9C356_EA54_40A5_8B45_477040561CC6__INCLUDED_)
