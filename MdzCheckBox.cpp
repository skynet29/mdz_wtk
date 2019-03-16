// MdzCheckBox.cpp: implementation of the MdzCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzCheckBox.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzCheckBox::MdzCheckBox()
{
	lpWnd->lpClassName = "BUTTON";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX;
	lpWnd->OnCommand = MDZ_CBK3(MdzCheckBox, OnCommand);
	bIsChecked = FALSE;
	lpOnClick = NULL;
}

MdzCheckBox::~MdzCheckBox()
{
	if (lpOnClick)
		delete lpOnClick;
}

void MdzCheckBox::SetCaption(LPSTR strCaption)
{
	lpWnd->SetText(strCaption);
}

void MdzCheckBox::SetChecked(BOOL bIsChecked)
{
	MEMBER_SET(bIsChecked);
	lpWnd->SendMsg(BM_SETCHECK, bIsChecked);
}

void MdzCheckBox::Create()
{
	MdzCtrl::Create();

	lpWnd->SendMsg(BM_SETCHECK, bIsChecked);
}

void MdzCheckBox::SetOnClick(MdzCbk1 *lpFunc)
{
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}

BOOL MdzCheckBox::IsChecked()
{
	return bIsChecked;
}

void MdzCheckBox::OnCommand(MdzEvent &evt)
{
	bIsChecked = (lpWnd->SendMsg(BM_GETCHECK) == BST_CHECKED);

	if (HIWORD(evt.wParam) == BN_CLICKED && lpOnClick)
		lpOnClick->Fire();
}
