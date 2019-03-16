// MdzMenu.cpp: implementation of the MdzMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMenu.h"
#include "MdzMenuItem.h"
#include "MdzFrame.h"
#include "MdzCbk3.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static BOOL TestFunc(MdzEvent& evt, DWORD dwArg)
{
	return (evt.uMsg == WM_INITMENUPOPUP && evt.wParam == dwArg);
}

static BOOL TestFunc2(MdzEvent& evt, DWORD dwArg)
{
	return (evt.uMsg == WM_MENUCHAR && evt.lParam == dwArg);
}

MdzMenu::MdzMenu()
{
	hMenu = CreatePopupMenu();

	lpEvtHandler = new MdzEventHandler(TestFunc, MDZ_CBK3(MdzMenu, OnInitMenu), (DWORD)hMenu);
	lpOnCharHandler = new MdzEventHandler(TestFunc2, MDZ_CBK3(MdzMenu, OnChar), (DWORD)hMenu);
	MdzFrame::GetMainFrame()->AddEventHandler(lpEvtHandler);
	MdzFrame::GetMainFrame()->AddEventHandler(lpOnCharHandler);

	lpOnClick = NULL;
}

MdzMenu::~MdzMenu()
{
	MdzFrame::GetMainFrame()->RemoveEventHandler(lpEvtHandler);
	MdzFrame::GetMainFrame()->RemoveEventHandler(lpOnCharHandler);

	if (lpOnClick)
		delete lpOnClick;

	DestroyMenu(hMenu);

	items.RemoveAll(TRUE);
}



void MdzMenu::Add(MdzMenuItem& item, LPSTR strCaption, MdzCbk1* pFunc)
{
	item.Create(hMenu, strCaption);
	if (pFunc)
		item.SetOnClick(pFunc);
}


void MdzMenu::AddSeparator()
{
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
}

HMENU MdzMenu::GetHandle()
{
	return hMenu;
}

void MdzMenu::SetOnClick(MdzCbk1 *lpFunc)
{
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}

void MdzMenu::Add(MdzMenu &menu, LPSTR strCaption)
{
	AppendMenu(hMenu, MF_POPUP, (UINT) menu.GetHandle(), strCaption);
}

void MdzMenu::OnInitMenu(MdzEvent& evt)
{
	if (lpOnClick)
		lpOnClick->Fire();
}

MdzMenuItem* MdzMenu::Track(MdzCtrl& ctrl, int x, int y)
{
	MdzPoint pt(x, y);
	pt.ToScreen(ctrl);

	if (lpOnClick)
		lpOnClick->Fire();

	UINT ident = TrackPopupMenu(hMenu, 
		TPM_LEFTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY,
		pt.x, pt.y, 0,
		MdzFrame::GetMainFrame()->GetHandle(), NULL);

	if (ident == 0)
		return NULL;

	MdzMenuItem* lpItem = MdzMenuItem::GetPtrFromId(ident);
	if (lpItem && lpItem->lpOnClick)
			lpItem->lpOnClick->Fire();
	return lpItem;
}

MdzMenuItem* MdzMenu::FindItem(LPSTR strCaption)
{
	MdzVector vector;
	MdzWindow::ScanMenu(hMenu, vector);
	for (UINT i = 0; i < vector.GetCount(); i++)
	{
		MdzMenuItem* pItem = (MdzMenuItem*) vector.GetAt(i);
		if (pItem->GetCaption().Equals(strCaption))
			return pItem;
	}
	return NULL;

}

UINT MdzMenu::GetItemCount()
{
	return GetMenuItemCount(hMenu);
}

MdzMenuItem* MdzMenu::AddItem(LPSTR strCaption, MdzCbk1 *pFunc)
{
	MdzMenuItem* pItem = new MdzMenuItem;
	items.Add(pItem);
	pItem->Create(hMenu, strCaption);
	if (pFunc)
		pItem->SetOnClick(pFunc);
	return pItem;
}

void MdzMenu::OnChar(MdzEvent &evt)
{
	MdzVectorT<MdzMenuItem> vector;
	MdzWindow::ScanMenu(hMenu, vector, FALSE);
	UCHAR ch = LOWORD(evt.wParam);
	for(UINT i = 0; i < vector.GetCount(); i++)
	{
		if (vector[i].IsEnabled() && vector[i].GetCaption().ToLower().GetCharAt(0) == ch)
		{
			evt.lResult = MAKELONG(vector[i].iPos, MNC_SELECT);
			return;
		}
	}
}
