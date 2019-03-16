// MdzMdiCtrl.cpp: implementation of the MdzMdiCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMdiCtrl.h"
#include "MdzWindow.h"
#include "MdzMenu.h"
#include "MdzMdiChild.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzMdiCtrl::MdzMdiCtrl()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN;
	lpWnd->lpClassName = "MDICLIENT";
	lpWnd->lpParam = &ccs;

	ccs.hWindowMenu = NULL;
	ccs.idFirstChild = 500;
}

MdzMdiCtrl::~MdzMdiCtrl()
{

}



void MdzMdiCtrl::Cascade()
{
	lpWnd->SendMsg(WM_MDICASCADE);
}

void MdzMdiCtrl::TileHorizontally()
{
	lpWnd->SendMsg(WM_MDITILE, MDITILE_HORIZONTAL);

}

void MdzMdiCtrl::TileVertically()
{
   lpWnd->SendMsg(WM_MDITILE, MDITILE_VERTICAL);

}

void MdzMdiCtrl::SetWndMenu(MdzMenu &menu)
{
	ccs.hWindowMenu = menu.GetHandle();
}

MdzCtrl* MdzMdiCtrl::GetActiveChild()
{
	HWND hWnd = (HWND) lpWnd->SendMsg(WM_MDIGETACTIVE);

	if (hWnd)
	{
		MdzWindow* lpActive = (MdzWindow*) GetWindowLong(hWnd, GWL_USERDATA);
		if (lpActive)
			return (MdzCtrl*) lpActive->lpUserData;
	}
	return NULL;
}

void MdzMdiCtrl::CreateChild(MdzMdiChild *lpChild)
{
	lpChild->SetParent(this);
	lpChild->Create();
}


