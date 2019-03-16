// MdzMdiChild.cpp: implementation of the MdzMdiChild class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMdiChild.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzMdiChild::MdzMdiChild()
{
	lpWnd->bounds		= MdzBounds(CW_USEDEFAULT, 0, CW_USEDEFAULT, 0);
	lpWnd->dwStyleEx	= WS_EX_MDICHILD;
	lpWnd->OnSize		= MDZ_CBK2(MdzMdiChild, OnSize);
	lpWnd->OnFocus		= MDZ_CBK6(MdzMdiChild, OnFocus);

	lpClientCtrl = NULL;
}

MdzMdiChild::~MdzMdiChild()
{
	lpWnd->Destroy();
}

void MdzMdiChild::SetTitle(LPSTR strTitle)
{
	lpWnd->SetText(strTitle);
}

void MdzMdiChild::OnSize(int width, int height)
{
	if (lpClientCtrl)
		lpClientCtrl->SetBounds(0, 0, width, height);
}

void MdzMdiChild::OnFocus(UINT bGotFocus)
{
	if (bGotFocus && lpClientCtrl)
		lpClientCtrl->RequestFocus();
}

void MdzMdiChild::SetClientCtrl(MdzCtrl &ctrl)
{
	lpClientCtrl = &ctrl;
	Add(ctrl);;
}

void MdzMdiChild::SetBackColor(MdzColor backColor)
{
	lpWnd->backColor = backColor;
}

void MdzMdiChild::SetMaximized(BOOL bIsMaximized)
{
	lpWnd->ModifyStyle(WS_MAXIMIZE, bIsMaximized);
}
