// MdzMenu.h: interface for the MdzMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMENU_H__A0847538_6FAA_4409_A91A_99F7ED641BEB__INCLUDED_)
#define AFX_MDZMENU_H__A0847538_6FAA_4409_A91A_99F7ED641BEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

#include "MdzCbk1.h"
#include "MdzVector.h"

class MdzMenuItem;
class MdzEventHandler;
class MdzEvent;
class MdzCtrl;

class DllExport MdzMenu  
{
public:
	MdzMenuItem* AddItem(LPSTR strCaption, MdzCbk1* pFunc = NULL);
	MdzMenu();

	UINT
	GetItemCount();

	MdzMenuItem*
	FindItem(LPSTR strCaption);

	MdzMenuItem*
	Track(MdzCtrl& ctrl, int x, int y);

	HMENU
	GetHandle();

	void
	SetOnClick(MdzCbk1* lpFunc);

	void
	AddSeparator();

	void
	Add(MdzMenu& menu, LPSTR strCaption);

	void
	Add(MdzMenuItem& item, LPSTR strCaption, MdzCbk1* pFunc = NULL);

	virtual ~MdzMenu();
private:
	void OnChar(MdzEvent& evt);
	void OnInitMenu(MdzEvent& evt);
	HMENU hMenu;
	MdzCbk1* lpOnClick;
	MdzEventHandler* lpEvtHandler;
	MdzEventHandler* lpOnCharHandler;
	MdzVectorT<MdzMenuItem> items;

};

#endif // !defined(AFX_MDZMENU_H__A0847538_6FAA_4409_A91A_99F7ED641BEB__INCLUDED_)
