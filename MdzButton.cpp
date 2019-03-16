// MdzButton.cpp: implementation of the MdzButton class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzButton.h"
#include "MdzWindow.h"
#include "MdzBitmap.h"
#include "MdzToolTips.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzButton::MdzButton()
{
	lpWnd->lpClassName = "BUTTON";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
	lpWnd->OnCommand = MDZ_CBK3(MdzButton, OnCommand);
	lpToolTips = NULL;
	lpOnClick = NULL;
}

MdzButton::~MdzButton()
{
	if (lpToolTips)
		delete lpToolTips;

	if (lpOnClick)
		delete lpOnClick;
}

void MdzButton::SetOnClick(MdzCbk1* lpFunc)
{	
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}

void MdzButton::SetCaption(LPSTR strCaption)
{
	lpWnd->SetText(strCaption);
}

void MdzButton::SetBitmap(MdzBitmap bitmap)
{
	bitmap.MapColor(GetSysColor(COLOR_BTNFACE));
	lpWnd->dwStyle |= BS_BITMAP;
	MEMBER_SET(bitmap);

	lpWnd->SendMsg(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bitmap.GetHandle());
}

void MdzButton::Create()
{
	MdzCtrl::Create();

	if (lpToolTips)
		lpToolTips->Create();

	if (bitmap.GetHandle())
		lpWnd->SendMsg(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bitmap.GetHandle());

}

void MdzButton::SetToolTips(LPSTR strToolTips)
{
	lpToolTips = new MdzToolTips(this, strToolTips);
}



void MdzButton::OnCommand(MdzEvent& evt)
{
	if (HIWORD(evt.wParam) == BN_CLICKED && lpOnClick)
		lpOnClick->Fire();
}

void MdzButton::SetAsDefault()
{
	lpWnd->ModifyStyle(BS_DEFPUSHBUTTON, TRUE);
}
