// MdzDialog.cpp: implementation of the MdzDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDialog.h"
#include "MdzWindow.h"
#include "MdzButton.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//MDZ_EV_PROTO1(MdzDialog, OnFocus);


MdzDialog::MdzDialog()
{
	lpWnd->bounds = MdzBounds(0, 0, 200, 200);
	lpWnd->lpTitle = "Dialog";
	lpWnd->dwStyleEx = WS_EX_DLGMODALFRAME;
	lpWnd->dwStyle = WS_POPUPWINDOW | WS_CAPTION;
	lpWnd->backColor = GetSysColor(COLOR_BTNFACE);
	lpWnd->OnFocus = MDZ_CBK6(MdzDialog, OnFocus);
	lpWnd->OnCommand = MDZ_CBK3(MdzDialog, OnCommand);

	lpDefaultBtn = NULL;
}

MdzDialog::~MdzDialog()
{
	lpWnd->Destroy();
}



int MdzDialog::Execute()
{
	if (!GetHandle())
		lpWnd->Create(GetActiveWindow());

	HWND hwnd = GetActiveWindow();

	lpWnd->CenterToParent();
	return lpWnd->Execute();
}

void MdzDialog::Close(int retCode)
{
	lpWnd->Close(retCode);
}

void MdzDialog::SetTitle(LPSTR strTitle)
{
	lpWnd->SetText(strTitle);
}



void MdzDialog::OnFocus(UINT bGotFocus)
{

}


void MdzDialog::OnCommand(MdzEvent& evt)
{
	if (LOWORD(evt.wParam) == IDCANCEL)
		Close(FALSE);
	else if (LOWORD(evt.wParam) == IDOK && lpDefaultBtn)
		lpWnd->SendMsg(WM_COMMAND, 0, (LPARAM) lpDefaultBtn->GetHandle());
}

void MdzDialog::SetDefaultButton(MdzButton& button)
{
	lpDefaultBtn = &button;
	button.SetAsDefault();
}




