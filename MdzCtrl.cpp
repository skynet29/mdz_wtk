// MdzCtrl.cpp: implementation of the MdzCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzCtrl.h"
#include "MdzWindow.h"
#include "MdzContainer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzCtrl::MdzCtrl()
{
	lpWnd		= new MdzWindow();
	lpParent	= NULL;

	lpWnd->lpUserData = this;
	bAutoDelete = FALSE;
}


MdzCtrl::~MdzCtrl()
{
	delete lpWnd;
}

void MdzCtrl::SetBounds(int left, int top, int width, int height)
{
	lpWnd->SetBounds(MdzBounds(left, top, width, height));
		
}

void MdzCtrl::SetParent(MdzCtrl *lpParent)
{
	MEMBER_SET(lpParent);
}

void MdzCtrl::Create()
{
	lpWnd->Create((lpParent) ? lpParent->GetHandle() : NULL);
}

void MdzCtrl::SetSize(int width, int height)
{
	lpWnd->SetSize(width, height);
}

HWND MdzCtrl::GetHandle()
{
	return lpWnd->GetHandle();
}



void MdzCtrl::SetEnabled(BOOL bIsEnabled)
{
	lpWnd->SetEnabled(bIsEnabled);
}

void MdzCtrl::SetBounds(MdzBounds &bounds)
{
	lpWnd->SetBounds(bounds);
}

void MdzCtrl::RequestFocus()
{
	lpWnd->RequestFocus();
}

BOOL MdzCtrl::IsEnabled()
{
	return lpWnd->IsEnabled();
}

BOOL MdzCtrl::IsVisible()
{
	return lpWnd->IsVisible();
}


void MdzCtrl::SetFont(MdzFont &font)
{
	lpWnd->SetFont(font);
}

void MdzCtrl::SetLocation(int left, int top)
{
	lpWnd->SetLocation(left, top);
}

void MdzCtrl::SetVisible(BOOL bIsVisible)
{
	lpWnd->SetVisible(bIsVisible);
}

MdzBounds MdzCtrl::GetBounds()
{
	return lpWnd->GetBounds();
}

MdzFont MdzCtrl::GetFont()
{
	return lpWnd->GetFont();
}

void MdzCtrl::SetAutoDelete(BOOL bAutoDelete)
{
	MEMBER_SET(bAutoDelete);
}



MdzCtrl* MdzCtrl::GetParent()
{
	return lpParent;
}

void MdzCtrl::Update()
{	
	UpdateWindow(GetHandle());
}

BOOL MdzCtrl::HasFocus()
{
	return (GetFocus() == GetHandle());
}
