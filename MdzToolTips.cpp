// MdzToolTips.cpp: implementation of the MdzToolTips class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzToolTips.h"
#include "MdzWindow.h"

#include <commctrl.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzToolTips::MdzToolTips(MdzCtrl* lpParent, LPSTR lpText)
{
	strText = lpText;

	SetParent(lpParent);

	lpWnd->lpClassName = TOOLTIPS_CLASS;
	lpWnd->dwStyle = WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP;
	lpWnd->dwStyleEx = WS_EX_TOPMOST;
	lpWnd->bounds = MdzBounds(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);
								
}

MdzToolTips::~MdzToolTips()
{

}

void MdzToolTips::Create()
{
	MdzCtrl::Create();


	HWND hwndTT = GetHandle();
	HWND hwnd = lpParent->GetHandle();

	SetWindowPos(hwndTT,
	  HWND_TOPMOST,
	  0,
	  0,
	  0,
	  0,
	  SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	RECT rect;
	GetClientRect (hwnd, &rect);

	TOOLINFO ti;

	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_SUBCLASS;
	ti.hwnd		= hwnd;
	ti.hinst	= GetModuleHandle(NULL);;
	ti.uId		= 0;
	ti.lpszText = strText;
	ti.rect		= rect;
    
	SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) &ti);	


}
