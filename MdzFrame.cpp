// MdzFrame.cpp: implementation of the MdzFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFrame.h"
#include "MdzWindow.h"
#include "MdzGraphic.h"
#include "MdzMenuBar.h"
#include "MdzRect.h"
#include "MdzDockBar.h"
#include "MdzStatusBar.h"
#include "MdzFont.h"
#include "MdzSocket.h"
#include "MdzMenuItem.h"
#include "MdzStdDialog.h"
#include "Htmlhelp.h"

#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static MdzFrame* lpMainFrame = NULL;




MdzFrame::MdzFrame()
{
	lpMainFrame = this;
	lpDockBar = NULL;
	lpClientCtrl = NULL;
	lpStatusBar = NULL;
	hAccel = NULL;


	lpWnd->dwStyle = WS_OVERLAPPEDWINDOW;
	lpWnd->bounds = MdzBounds(CW_USEDEFAULT, 0, CW_USEDEFAULT, 0);
	lpWnd->lpTitle = "Frame";
	lpWnd->OnClose = MDZ_CBK5(MdzFrame, OnClose);
	lpWnd->OnSize  = MDZ_CBK2(MdzFrame, OnSize);
	lpWnd->OnFocus = MDZ_CBK6(MdzFrame, OnFocus);
	lpWnd->OnDestroy = MDZ_CBK1(MdzFrame, OnDestroy);
}

MdzFrame::~MdzFrame()
{
	if (hAccel)
		DestroyAcceleratorTable(hAccel);
	
	shortcuts.RemoveAll(TRUE);
}

int MdzFrame::Run(LPSTR strCmdLine, int iCmdShow)
{
	MEMBER_SET(strCmdLine);

	Create();

	if (!GetHandle())
		return -1;

	ShowWindow(GetHandle(), iCmdShow);

	MSG msg;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			if (!TranslateAccelerator(GetHandle(), hAccel, &msg))
			{
				char buffer[32];
				GetClassName(msg.hwnd, buffer, sizeof(buffer));
				if (!strcmp(buffer, "Edit"))
				{
					DWORD dwStyle = GetWindowLong(msg.hwnd, GWL_STYLE);
					if ((dwStyle & ES_MULTILINE) == 0)
					{
						if(IsDialogMessage(::GetParent(msg.hwnd), &msg))
							continue;
					}
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
			OnIdle();
	}

	return msg.wParam;
}

void MdzFrame::SetBackColor(COLORREF backColor)
{
	lpWnd->backColor = backColor;
}

void MdzFrame::SetTitle(LPSTR strTitle)
{
	lpWnd->SetText(strTitle);
}

void MdzFrame::SetResizable(BOOL bIsResizable)
{
	lpWnd->ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, bIsResizable);
}

void MdzFrame::Close()
{
	lpWnd->Close();
}

void MdzFrame::SetMenuBar(MdzMenuBar &menuBar)
{
	lpWnd->hMenu = menuBar.GetHandle();
	menuBar.lpParent = this;
}



BOOL MdzFrame::OnClose()
{
	return TRUE;
}

void MdzFrame::OpenHelpFile(LPSTR strFileName, LPSTR strKeyWord)
{
	WinHelp(GetHandle(), strFileName, 
		(strKeyWord) ? HELP_KEY : HELP_FINDER, (DWORD)strKeyWord);
}

void MdzFrame::OnSize(int width, int height)
{
	MdzRect rcClient = GetClientRect();

	if (lpDockBar)
	{
		SendMessage(lpDockBar->GetHandle(), WM_SIZE, 0, 0);
		MdzRect rc;
		GetWindowRect(lpDockBar->GetHandle(), &rc);
		rcClient.top += rc.Height();
	}

	if (lpStatusBar)
	{
		SendMessage(lpStatusBar->GetHandle(), WM_SIZE, 0, 0);
		MdzRect rc;
		GetWindowRect(lpStatusBar->GetHandle(), &rc);
		rcClient.bottom -= rc.Height();
	}

	OnSize(rcClient);

}

void MdzFrame::OnDockBarResized(MdzRect& rc)
{
	MdzRect rcClient = GetClientRect();

	rcClient.top += rc.Height();

	if (lpStatusBar)
	{
		//SendMessage(lpStatusBar->GetHandle(), WM_SIZE, 0, 0);
		MdzRect rc;
		GetWindowRect(lpStatusBar->GetHandle(), &rc);
		rcClient.bottom -= rc.Height();
	}
	
	OnSize(rcClient);
}

void MdzFrame::SetClientCtrl(MdzCtrl &ctrl)
{
	lpClientCtrl = &ctrl;
	Add(ctrl);
	lpWnd->bOpaque = FALSE;
}

void MdzFrame::SetDockBar(MdzDockBar &rebar)
{
	lpDockBar = &rebar;
	Add(rebar);
}

void MdzFrame::OnFocus(UINT bGotFocus)
{
	if (bGotFocus && lpClientCtrl)
		lpClientCtrl->RequestFocus();
}



void MdzFrame::SetIcon(WORD iResId)
{
	lpWnd->SetIcon(iResId);
}

void MdzFrame::SetStatusBar(MdzStatusBar &statusBar)
{
	lpStatusBar = &statusBar;
	Add(statusBar);
}

void MdzFrame::AddEventHandler(MdzEventHandler* lpEvtHandler)
{
    lpWnd->AddEventHandler(lpEvtHandler);
}

void MdzFrame::RemoveEventHandler(MdzEventHandler *lpEvtHandler)
{
    lpWnd->RemoveEventHandler(lpEvtHandler);
    delete lpEvtHandler;
}

BOOL MdzFrame::InitApp()
{
	srand( (unsigned)time( NULL ) );


    INITCOMMONCONTROLSEX iccex; 

    /* INITIALIZE COMMON CONTROLS */
    iccex.dwICC = ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES ;
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&iccex);

	MdzFont::InitClass();

	if (!MdzSocket::InitClass())
		return FALSE;

	if (! MdzWindow::RegisterWindow() )
		return FALSE;

    //MessageBox(NULL, MdzString::Format("sizeof(MdzWindow)=%d", sizeof(MdzWindow)), "Message", MB_OK);

    return TRUE;
}



void MdzFrame::OnDestroy()
{
	PostQuitMessage(0);
}

void MdzFrame::Redraw(BOOL bErase)
{
	lpWnd->Redraw(bErase);
}

void MdzFrame::OnCreate()
{
	MdzContainer::OnCreate();

	hAccel = lpWnd->CreateAccelTable(&shortcuts);
}

void MdzFrame::SetCursor(WORD iResId)
{
	lpWnd->SetCursor(iResId);
}

MdzFrame* MdzFrame::GetMainFrame()
{
	return lpMainFrame;
}

void MdzFrame::AddShortcut(UINT iKeyChanger, char character, MdzCbk1 *lpFunc)
{
	MdzMenuItem* pItem = new MdzMenuItem;
	pItem->SetShortcut(iKeyChanger, character);
	pItem->SetOnClick(lpFunc);
	shortcuts.Add(pItem);
}



void MdzFrame::OnIdle()
{
	WaitMessage();
}

void MdzFrame::OpenHtmlHelpFile(LPSTR strFileName, LPSTR strKeyWord)
{
	if (strKeyWord)
	{
		HH_AKLINK link;
		link.cbStruct =     sizeof(HH_AKLINK) ;
		link.fReserved =    FALSE ;
		link.pszKeywords =  strKeyWord; 
		link.pszUrl =       NULL ; 
		link.pszMsgText =   NULL ; 
		link.pszMsgTitle =  NULL ; 
		link.pszWindow =    NULL ;
		link.fIndexOnFail = TRUE ;
		HtmlHelp(GetHandle(), strFileName, HH_KEYWORD_LOOKUP, (DWORD)&link);
	}
	else
		HtmlHelp(GetHandle(), strFileName, HH_DISPLAY_TOPIC, 0);
			
}

MdzString MdzFrame::GetCmdLine()
{
	return strCmdLine;
}

void MdzFrame::OnSize(MdzRect &rc)
{
	if (lpClientCtrl)
		lpClientCtrl->SetBounds(MdzBounds(rc));

}
