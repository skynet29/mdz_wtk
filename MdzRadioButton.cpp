// MdzRadioButton.cpp: implementation of the MdzRadioButton class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzRadioButton.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzRadioButton::MdzRadioButton()
{
	lpWnd->lpClassName = "BUTTON";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON;;
	lpWnd->OnCommand = MDZ_CBK3(MdzRadioButton, OnCommand);
	bIsChecked = FALSE;
	lpOnClick = NULL;
}

MdzRadioButton::~MdzRadioButton()
{
	if (lpOnClick)
		delete lpOnClick;
}

void MdzRadioButton::SetCaption(LPSTR strCaption)
{
	lpWnd->SetText(strCaption);
}

void MdzRadioButton::SetChecked(BOOL bIsChecked)
{
	MEMBER_SET(bIsChecked);
	lpWnd->SendMsg(BM_SETCHECK, bIsChecked);
}

void MdzRadioButton::Create()
{
	MdzCtrl::Create();

	lpWnd->SendMsg(BM_SETCHECK, bIsChecked);
}

void MdzRadioButton::SetOnClick(MdzCbk1 *lpFunc)
{
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}

BOOL MdzRadioButton::IsChecked()
{
	return bIsChecked;
}

void MdzRadioButton::OnCommand(MdzEvent &evt)
{
	bIsChecked = (lpWnd->SendMsg(BM_GETCHECK) == BST_CHECKED);

	if (HIWORD(evt.wParam) == BN_CLICKED && lpOnClick)
		lpOnClick->Fire();
}
