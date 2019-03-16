// MdzToolButton.cpp: implementation of the MdzToolButton class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzToolButton.h"
#include "MdzWindow.h"
#include "MdzCtrl.h"
#include "MdzString.h"
#include "MdzEventHandler.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static UINT iIdent = 300;

const UINT MdzToolButton::K_BUTTON		= TBSTYLE_BUTTON;
const UINT MdzToolButton::K_CHECK		= TBSTYLE_CHECK;
const UINT MdzToolButton::K_CHECKGROUP		= TBSTYLE_CHECKGROUP;



void MdzToolButton::Init(MdzWindow* lpWnd)
{
	MEMBER_SET(lpWnd);

	tbb.fsStyle = TBSTYLE_SEP;
	tbb.iBitmap = 5;
	bAutoDelete = TRUE;
}

MdzToolButton::~MdzToolButton()
{
	if (lpOnClick)
		delete lpOnClick;
}



void MdzToolButton::Init(MdzWindow *lpWnd, MdzBitmap bitmap, UINT iStyle)
{
	MEMBER_SET(lpWnd);
	MEMBER_SET(bitmap);

	tbb.fsStyle = iStyle;
}

void MdzToolButton::Create()
{
	if (bitmap.GetHandle())
	{
		TBADDBITMAP bmp;

		bmp.hInst = NULL ;
		bmp.nID = (UINT) bitmap.GetHandle();

		tbb.iBitmap = lpWnd->SendMsg(TB_ADDBITMAP, 1, (LPARAM) &bmp);
	}

	lpWnd->SendMsg(TB_ADDBUTTONS, 1, (LPARAM) &tbb); 

	if (lpCtrl)
	{
		MdzRect rc = GetItemRect();
		MdzBounds bds = lpCtrl->GetBounds();
		lpCtrl->SetLocation(rc.left, rc.top + (rc.Height() - bds.height)/2);
		lpCtrl->Create();
		//SetParent(lpCtrl->GetHandle(), lpWnd->GetHandle());
	}

}

//DEL void MdzToolButton::Init(MdzWindow *lpWnd, UINT iBmpIdx, UINT iStyle)
//DEL {
//DEL 	MEMBER_SET(lpWnd);
//DEL 
//DEL 	tbb.fsStyle = TBSTYLE_BUTTON;
//DEL 	tbb.iBitmap = iBmpIdx;
//DEL 	tbb.fsStyle = iStyle;
//DEL }

MdzRect MdzToolButton::GetItemRect()
{
	MdzRect rc;

	int index = lpWnd->SendMsg(TB_COMMANDTOINDEX, tbb.idCommand);

	lpWnd->SendMsg(TB_GETITEMRECT, index, (LPARAM) &rc);

	return rc;
}

void MdzToolButton::Init(MdzWindow *lpWnd, MdzCtrl *lpCtrl, int iWidth)
{
	MEMBER_SET(lpWnd);
	MEMBER_SET(lpCtrl);

	tbb.fsStyle = TBSTYLE_SEP;
	tbb.iBitmap = iWidth + 5;
	bAutoDelete = TRUE;
}

void MdzToolButton::SetChecked(BOOL bIsChecked)
{
	if (bIsChecked)
		tbb.fsState |= TBSTATE_CHECKED;
	else
		tbb.fsState &= ~TBSTATE_CHECKED;

	if (lpWnd)
		lpWnd->SendMsg(TB_CHECKBUTTON, tbb.idCommand, MAKELONG(bIsChecked, 0));

}

BOOL MdzToolButton::IsChecked()
{
	return ((tbb.fsState & TBSTATE_CHECKED) != 0);
}

void MdzToolButton::SetEnabled(BOOL bIsEnabled)
{
	if (bIsEnabled)
		tbb.fsState |= TBSTATE_ENABLED;
	else
		tbb.fsState &= ~TBSTATE_ENABLED;

	if (lpWnd)
		lpWnd->SendMsg(TB_ENABLEBUTTON, tbb.idCommand, MAKELONG(bIsEnabled, 0));

}

BOOL MdzToolButton::IsEnabled()
{
	return ((tbb.fsState & TBSTATE_ENABLED) != 0);

}

void MdzToolButton::SetOnClick(MdzCbk1 *lpFunc)
{
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}

void MdzToolButton::SetToolTips(LPSTR strToolTips)
{
	MEMBER_SET(strToolTips);
}

MdzToolButton::MdzToolButton()
{
	ZeroMemory(&tbb, sizeof(tbb));
	tbb.idCommand = iIdent++;
	tbb.fsState = TBSTATE_ENABLED;
	tbb.dwData = (DWORD) this;
	tbb.iBitmap = -2;
	lpCtrl = NULL;
	lpWnd = NULL;
	lpOnClick = NULL;
	bAutoDelete = FALSE;

}



void MdzToolButton::SetAutoDelete(BOOL bAutoDelete)
{
	this->bAutoDelete = bAutoDelete;
}
