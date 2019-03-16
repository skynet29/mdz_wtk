// MdzToolBar.cpp: implementation of the MdzToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFrame.h"

#include "MdzToolBar.h"
#include "MdzWindow.h"
#include "MdzRect.h"
#include "MdzGraphic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MdzToolBar::MdzToolBar()
{
	static UINT gIdent = 100;
	lpWnd->lpClassName = TOOLBARCLASSNAME;
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | 
		CCS_NORESIZE | CCS_NODIVIDER | TBSTYLE_TOOLTIPS | CCS_NOPARENTALIGN;//| TBSTYLE_FLAT;
	lpWnd->OnCommand = MDZ_CBK3(MdzToolBar, OnCommand);
	lpWnd->OnNotify = MDZ_CBK3(MdzToolBar, OnNotify);

	bIsLargeIcon = FALSE;
	bBreak = FALSE;
	maskColor = -1;
	iIdent = gIdent++;
}

MdzToolBar::~MdzToolBar()
{
	for (UINT i = 0; i < btnList.GetCount(); i++)
	{
		MdzToolButton* lpBtn = (MdzToolButton*) btnList.GetAt(i);
		if (lpBtn->bAutoDelete)
			delete lpBtn;
	}

	btnList.RemoveAll(FALSE);
}

void MdzToolBar::Create()
{

	MdzCtrl::Create();

	lpWnd->SendMsg(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON));
	lpWnd->SendMsg(TB_SETBUTTONSIZE, 0, (LPARAM) MAKELONG(24, 24));

	HWND hTooltips = (HWND) lpWnd->SendMsg(TB_GETTOOLTIPS);
	SetWindowLong(hTooltips, GWL_USERDATA, (LONG) lpWnd);

	/*
	TBADDBITMAP bmp;
	bmp.hInst = HINST_COMMCTRL ;
	if (bIsLargeIcon)
		bmp.nID = IDB_STD_LARGE_COLOR;
	else
		bmp.nID = IDB_STD_SMALL_COLOR;

	lpWnd->SendMsg(TB_ADDBITMAP, 0, (LPARAM) &bmp);
	*/

	for (UINT i = 0; i < btnList.GetCount(); i++)
	{
		MdzToolButton* lpButton = (MdzToolButton*) btnList.GetAt(i);
		lpButton->Create();
	}

}

//DEL void MdzToolBar::AddButton(MdzToolButton& btn, UINT iBmpIdx, UINT iStyle)
//DEL {
//DEL 	btn.Init(lpWnd, iBmpIdx, iStyle);
//DEL 	btnList.Add(&btn);
//DEL }

void MdzToolBar::AddSeparator()
{
	MdzToolButton* lpToolBtn = new MdzToolButton();
	lpToolBtn->Init(lpWnd);
	btnList.Add(lpToolBtn);
}


void MdzToolBar::AddButton(MdzToolButton& btn, MdzBitmap bitmap, UINT iStyle)
{
	/*
	if (maskColor != -1)
		bitmap.MapColor(maskColor);
		*/
	bitmap.MapColor(GetSysColor(COLOR_BTNFACE));

	btn.Init(lpWnd, bitmap, iStyle);
	btnList.Add(&btn);
}


//DEL void MdzToolBar::SetLargeIcon(BOOL bIsLargeIcon)
//DEL {
//DEL 	MEMBER_SET(bIsLargeIcon);
//DEL }

UINT MdzToolBar::GetIdent()
{	
	return iIdent;
}

void MdzToolBar::AddCtrl(MdzCtrl &ctrl, int iWidth, int iHeight)
{
	AddSeparator();
	//ctrl.SetParent(MdzFrame::GetMainFrame());
	ctrl.SetParent(this);
	ctrl.SetSize(iWidth, iHeight);

	MdzToolButton* lpBtn = new MdzToolButton();
	lpBtn->Init(lpWnd, &ctrl, iWidth);
	btnList.Add(lpBtn);
}











UINT MdzToolBar::GetWidth()
{
	UINT iWidth = 0;

	for (UINT i = 0; i < btnList.GetCount(); i++)
	{
		MdzToolButton* lpButton = (MdzToolButton*) btnList.GetAt(i);
		iWidth += lpButton->GetItemRect().Width();
	}

	return iWidth;
}

//DEL void MdzToolBar::SetMaskColor(COLORREF maskColor)
//DEL {	
//DEL 	MEMBER_SET(maskColor);
//DEL }

void MdzToolBar::OnCommand(MdzEvent& evt)
{
	MdzToolButton* lpButton = GetButton(LOWORD(evt.wParam));
	if (lpButton && lpButton->lpOnClick)
		lpButton->lpOnClick->Fire();
}

void MdzToolBar::OnNotify(MdzEvent& evt)
{
	LPNMHDR lpHeader = (LPNMHDR) evt.lParam;

	if (lpHeader->code == TTN_GETDISPINFO)
	{
		MdzToolButton* lpButton = GetButton(lpHeader->idFrom);
		if (lpButton)
		{
			MdzString strToolTips = lpButton->strToolTips;
			if (strToolTips.GetLength() > 0)
			{
				LPNMTTDISPINFO lpnmtdi = (LPNMTTDISPINFO) lpHeader;
				strcpy(lpnmtdi->szText, (LPSTR) strToolTips);						
			}
		}
	}

}

MdzToolButton* MdzToolBar::GetButton(UINT iIdent)
{
	
	int index = lpWnd->SendMsg(TB_COMMANDTOINDEX, iIdent);
	TBBUTTON tbb;
	lpWnd->SendMsg(TB_GETBUTTON, index, (LPARAM) &tbb);
	return (MdzToolButton*) tbb.dwData;

}


