// MdzWindow.cpp: implementation of the MdzWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzWindow.h"
#include "MdzEvent.h"
#include "MdzEventHandler.h"
#include "MdzRect.h"
#include "MdzGraphic.h"
#include "MdzFont.h"
#include "MdzMenuItem.h"
#include "MdzMenu.h"

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzWindow::MdzWindow()
{


	lpClassName		= NULL;
	dwStyle			= 0;
	dwStyleEx		= 0;
	hMenu				= NULL;
	lpParam			= this;;
	backColor		= GetSysColor(COLOR_WINDOW);
	bOpaque			= TRUE;
	lpUserData		= NULL;
	lpWndProc		= NULL;

	hWnd			= NULL;
	hMdiClient	= NULL;
	hFont			= (HFONT) GetStockObject(DEFAULT_GUI_FONT);
	hIcon			= NULL;
	pDragWnd		= NULL;
	hCursor		= NULL;
	hCursor		= LoadCursor(NULL, IDC_ARROW);

	OnCreate			= NULL;
	OnDestroy			= NULL;
	OnSize				= NULL;
	OnFocus				= NULL;
	OnPaint				= NULL;
	OnMouseMove			= NULL;
	OnLeftButtonUp		= NULL;
	OnLeftButtonDown	= NULL;
	OnRightButtonUp		= NULL;
	OnRightButtonDown	= NULL;
	OnClose				= NULL;
	OnCommand			= NULL;
	OnNotify			= NULL;
	OnHScroll			= NULL;
	OnVScroll			= NULL;
	OnDrawItem			= NULL;
	OnCtlColor			= NULL;
	OnKeyDown			= NULL;
	OnKeyUp				= NULL;
	OnMouseDrag			= NULL;
	OnChar				= NULL;
	OnMeasureItem		= NULL;
	OnLButtonDblClk		= NULL;
	OnEnter				= NULL;
}



BOOL MdzWindow::RegisterWindow()
{
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));

	//wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hInstance		= GetModuleHandle(NULL);
	wc.lpszClassName	= "MDZ_WINDOW";
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	
	return RegisterClass(&wc);
}

LRESULT MdzWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   MdzEvent evt(uMsg, wParam, lParam);
   MdzWindow* lpWnd = GetWindowPtr(hWnd);
   if (lpWnd && lpWnd->lpWndProc)
   {
	   lpWnd->ProcessChildEvent(evt);
	   return evt.lResult;
   }

   if (uMsg == WM_CREATE)
   {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT) lParam;

      if (lpcs->dwExStyle & WS_EX_MDICHILD)
         lpWnd = (MdzWindow*) ((LPMDICREATESTRUCT) lpcs->lpCreateParams)->lParam;
      else
         lpWnd = (MdzWindow*) lpcs->lpCreateParams;

      lpWnd->hWnd = hWnd;
      SetWindowLong(hWnd, GWL_USERDATA, (LONG) lpWnd);
   }


   if (lpWnd)
   {
      lpWnd->ProcessEvent(evt);
   }
   else
      evt.ProcessDefault(hWnd);

   return evt.lResult;
}



void MdzWindow::ProcessEvent(MdzEvent &evt)
{
	MdzPoint pt;
	pt.x = GET_X_LPARAM(evt.lParam);
	pt.y = GET_Y_LPARAM(evt.lParam);

	if (evt.uMsg == WM_SETCURSOR && LOWORD(evt.lParam) == HTCLIENT)
	{
		::SetCursor(hCursor);
		evt.lResult = TRUE;
		return;
	}
	
	if (evt.uMsg == WM_KEYDOWN && OnKeyDown)
	{
		OnKeyDown->Fire(evt.wParam);
		return;
	}
	
	if (evt.uMsg == WM_KEYUP && OnKeyUp)
	{
		OnKeyUp->Fire(evt.wParam);
		return;
	}

	if (evt.uMsg == WM_RBUTTONDOWN && OnRightButtonDown)
	{
			OnRightButtonDown->Fire(pt.x, pt.y);
		return;
	}

	if (evt.uMsg == WM_RBUTTONUP && OnRightButtonUp)
	{
		OnRightButtonUp->Fire(pt.x, pt.y);
		return;
	}

	if (evt.uMsg == WM_LBUTTONDOWN)
	{
		SetCapture(hWnd);
		if (OnLeftButtonDown)
			OnLeftButtonDown->Fire(pt.x, pt.y);
		return;
	}

	if (evt.uMsg == WM_LBUTTONUP)
	{
		ReleaseCapture();

		if (pDragWnd)
		{
			ClientToScreen(hWnd, &pt);
			MdzRect rc;
			GetWindowRect(pDragWnd->hWnd, &rc);
			//ScreenToClient(pDragWnd->hWnd, &pt);
			pt.x -= rc.left;
			pt.y -= rc.top;
			if (pDragWnd->OnLeftButtonUp)
				pDragWnd->OnLeftButtonUp->Fire(pt.x, pt.y);
			pDragWnd = NULL;
		}

		else if (OnLeftButtonUp)
			OnLeftButtonUp->Fire(pt.x, pt.y);
		
		return;
	}

	if (evt.uMsg == WM_MOUSEMOVE)
	{
		if (pDragWnd)
		{
			ClientToScreen(hWnd, &pt);
			MdzRect rc;
			GetWindowRect(pDragWnd->hWnd, &rc);
			//ScreenToClient(pDragWnd->hWnd, &pt);
			pt.x -= rc.left;
			pt.y -= rc.top;

			if (pDragWnd->OnMouseMove)
				pDragWnd->OnMouseMove->Fire(pt.x, pt.y);
			return;
		}

		if (OnMouseMove && GetCapture() != hWnd)
		{
			OnMouseMove->Fire(pt.x, pt.y);
			return;
		}

		if (OnMouseDrag && GetCapture() == hWnd)
		{
			OnMouseDrag->Fire(pt.x, pt.y);
			return;
		}
	}


   if (evt.uMsg == WM_DESTROY)
   {
	   if (OnDestroy != NULL)
		   OnDestroy->Fire();
	   return;
   }

   if (evt.uMsg == WM_CREATE && OnCreate != NULL)
      OnCreate->Fire();

   if (evt.uMsg == WM_SIZE)
   {
	   if (OnSize != NULL)
	   {
		   OnSize->Fire(LOWORD(evt.lParam), HIWORD(evt.lParam));
	   }

	   if ((dwStyleEx & WS_EX_MDICHILD) == 0)
		return;
   }
/*
   if (evt.uMsg == WM_SETFOCUS)
   {
		MdzWindow* lpWnd = GetWindowPtr((HWND) evt.wParam);
		if (lpWnd && lpWnd->OnFocus)
			lpWnd->OnFocus->Fire(FALSE);
	if (OnFocus != NULL)
		OnFocus->Fire(TRUE);
   }

   if (evt.uMsg == WM_KILLFOCUS)
   {
		MdzWindow* lpWnd = GetWindowPtr((HWND) evt.wParam);
		if (lpWnd && lpWnd->OnFocus)
			lpWnd->OnFocus->Fire(TRUE);
   }
*/

   if (evt.uMsg == WM_SETFOCUS && OnFocus != NULL)
      OnFocus->Fire(TRUE);

   if (evt.uMsg == WM_KILLFOCUS && OnFocus != NULL)
      OnFocus->Fire(FALSE);

  if (evt.uMsg == WM_CLOSE)
   {
	  if ((dwStyleEx & WS_EX_DLGMODALFRAME))
	  {
		PostQuitMessage(evt.wParam);
		return;
	  }

	  if (OnClose != NULL)
	  {
		  if (! OnClose->Fire())
			return;
	  }
   }


   if (evt.uMsg == WM_PARENTNOTIFY && LOWORD(evt.wParam) == WM_CREATE)
   {
      char buffer[32];
      GetClassName((HWND) evt.lParam, buffer, sizeof(buffer));

	  if (!strcmp(strupr(buffer), "MDICLIENT"))
	  {
		 hMdiClient = (HWND) evt.lParam;
	  }

   }
   
   
   if (evt.uMsg == WM_ERASEBKGND)
   {
	  if (bOpaque)
	  {
		  RECT rc;
		  GetClientRect(hWnd, &rc);
		  HBRUSH hBrush = CreateSolidBrush(backColor);
		  FillRect((HDC) evt.wParam, &rc, hBrush);
		  DeleteObject(hBrush);
	  }
      evt.lResult = TRUE;
      return;
   }
   

   if (evt.uMsg == WM_PAINT)
   {
	   PAINTSTRUCT ps;
	   BeginPaint(hWnd, &ps);
	   if (OnPaint)
	   {
		   MdzGraphic graphic;
		   graphic.Init(ps.hdc);
		   OnPaint->Fire(graphic);
	   }
	   EndPaint(hWnd, &ps);
	   return;
   }


   if (evt.uMsg == WM_COMMAND)
   {
	   if (evt.lParam)
	   {
		   MdzWindow* lpWnd = GetWindowPtr((HWND) evt.lParam);
		   if (lpWnd && lpWnd->OnCommand)
			   lpWnd->OnCommand->Fire(evt);

	   }
	   else if (evt.wParam >= 100)
	   {
		   MdzMenuItem* lpMenuItem = MdzMenuItem::GetPtrFromId(LOWORD(evt.wParam));
//		   MdzMenuItem* lpMenuItem = MdzMenuItem::GetPtrFromId(evt.wParam);
		   if (lpMenuItem)
		   {
			   if (lpMenuItem->lpOnClick)			
					lpMenuItem->lpOnClick->Fire();
		   }
		}
		else if (OnCommand)
		{
		   OnCommand->Fire(evt);
		}

	  
   }

	if (evt.uMsg == WM_NOTIFY)
	{
		LPNMHDR lpHeader = (LPNMHDR) evt.lParam;
	   MdzWindow* lpWnd = GetWindowPtr(lpHeader->hwndFrom);
	   if (lpWnd && lpWnd->OnNotify)
	   {
		   lpWnd->OnNotify->Fire(evt);	
			if (lpHeader->code == TVN_BEGINDRAG && evt.lResult)
			{
				pDragWnd = lpWnd;
				SetCapture(hWnd);
			}
		   return;
	   }
	}

	/*
	if (evt.uMsg == WM_INITMENUPOPUP)
	{
		MENUINFO mi;
		mi.cbSize = sizeof(mi);
		mi.fMask = MIM_MENUDATA;
		GetMenuInfo((HMENU) evt.wParam, &mi);	
		MdzMenu* lpMenu = (MdzMenu*) mi.dwMenuData;
		if (lpMenu && lpMenu->lpOnClick)
			lpMenu->lpOnClick->Fire();
	}
	*/

	if (evt.uMsg == WM_HSCROLL)
	{
		if (evt.lParam)
		{
		   MdzWindow* lpWnd = GetWindowPtr((HWND) evt.lParam);
			if (lpWnd && lpWnd->OnHScroll)
				lpWnd->OnHScroll->Fire(evt);
		}
		else if (OnHScroll)
		{
			OnHScroll->Fire(evt);
		}
	}

	if (evt.uMsg == WM_VSCROLL)
	{
		if (evt.lParam)
		{
		   MdzWindow* lpWnd = GetWindowPtr((HWND) evt.lParam);
			if (lpWnd && lpWnd->OnVScroll)
				lpWnd->OnVScroll->Fire(evt);
		}
		else if (OnVScroll)
		{
			OnVScroll->Fire(evt);
		}
	}

	if (evt.uMsg == WM_DRAWITEM)
	{
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT) evt.lParam;
		if (lpDrawItem->CtlType == ODT_MENU)
		{
			MdzMenuItem* lpItem = MdzMenuItem::GetPtrFromId(lpDrawItem->itemID);
			if (lpItem)
				lpItem->OnDrawItem(lpDrawItem);
		}
		else
		{
			MdzWindow* lpWnd = GetWindowPtr(lpDrawItem->hwndItem);
			if (lpWnd && lpWnd->OnDrawItem)
				lpWnd->OnDrawItem->Fire(evt);
		}
	}

	if (evt.uMsg == WM_MEASUREITEM)
	{
		LPMEASUREITEMSTRUCT lpMeasureItem = (LPMEASUREITEMSTRUCT)evt.lParam;
		if (lpMeasureItem->CtlType == ODT_MENU)
		{
			MdzMenuItem* lpItem = MdzMenuItem::GetPtrFromId(lpMeasureItem->itemID);
			if (lpItem)
				lpItem->OnMeasureItem(lpMeasureItem);
		}
	}

	if (evt.uMsg == WM_CTLCOLORSTATIC ||
		evt.uMsg == WM_CTLCOLOREDIT)
	{
		MdzWindow* lpWnd = GetWindowPtr((HWND) evt.lParam);
		if (lpWnd && lpWnd->OnCtlColor)
		{
			lpWnd->OnCtlColor->Fire(evt);
			return;
		}
	}

	//BOOL found = FALSE;
   for (UINT i = 0; i < evtHandlers.GetCount(); i++)
   {
       if (evtHandlers[i].HandleEvent(evt))		 
		   return;
   }


   if (dwStyleEx & WS_EX_MDICHILD)
      evt.ProcessMDIDefault(hWnd);
   else
      evt.ProcessDefault(hWnd, hMdiClient);
}

BOOL MdzWindow::Create(HWND hParent)
{
	if ((dwStyle & WS_CHILD) != 0)
		dwStyle |= WS_CLIPSIBLINGS;

	hWnd = CreateWindowEx(
		dwStyleEx,
		(lpClassName) ? lpClassName : "MDZ_WINDOW",
		lpTitle,
		dwStyle,
		bounds.left, bounds.top,
		bounds.width, bounds.height,
		hParent,
		hMenu,
		GetModuleHandle(NULL),
		lpParam);

	SetWindowLong(hWnd, GWL_USERDATA, (LONG) this);
	
	if (lpClassName)
		lpWndProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);
	

	if (hFont)
		SendMsg(WM_SETFONT, (WPARAM) hFont, TRUE);

	if (hIcon)
	{
		SendMsg(WM_SETICON, ICON_BIG, (LPARAM) hIcon);
		SendMsg(WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
	}

	
		

	return (hWnd != NULL);

}

HWND MdzWindow::GetHandle()
{
	return hWnd;
}

int MdzWindow::MessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



LRESULT MdzWindow::SendMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendMessage(hWnd, uMsg, wParam, lParam);
}

void MdzWindow::Close(int iRetValue)
{
	SendMsg(WM_CLOSE, iRetValue);
}

void MdzWindow::SetBounds(MdzBounds& bounds)
{
	MEMBER_SET(bounds);
	//MoveWindow(hWnd, bounds.left, bounds.top, bounds.width, bounds.height, TRUE);
	SetWindowPos(hWnd, NULL, bounds.left, bounds.top, bounds.width, bounds.height, SWP_NOZORDER);

	if (lpClassName && OnSize)
		OnSize->Fire(bounds.width, bounds.height);
}

void MdzWindow::SetText(LPSTR lpText)
{
	lpTitle = lpText;
	SetWindowText(hWnd, lpText);
}

void MdzWindow::CenterToParent()
{
	MdzRect rcParent;
	
	if (GetParent(hWnd))
	{
		GetWindowRect(GetParent(hWnd), &rcParent);
	}
	else
	{
		rcParent.bottom = GetSystemMetrics(SM_CYSCREEN);
		rcParent.right = GetSystemMetrics(SM_CXSCREEN);
	}

	MdzRect rc;
	GetWindowRect(hWnd, &rc);
	int left = rcParent.left + (rcParent.Width() - rc.Width()) / 2;
	int top = rcParent.top + (rcParent.Height() - rc.Height()) / 2;
	SetLocation(left, top);
}


void MdzWindow::SetLocation(int left, int top)
{
	bounds.left = left;
	bounds.top = top;
	SetWindowPos(hWnd, NULL, left, top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}


void MdzWindow::Pack(int xPad, int yPad)
{
	HWND hChild = GetWindow(hWnd, GW_CHILD);
	int right = 0;
	int bottom = 0;

	while (hChild)
	{ 
		RECT rc;
		GetWindowRect(hChild, &rc);
		ScreenToClient(hWnd, (LPPOINT) &rc.right);
		right = max(right, rc.right);
		bottom = max(bottom, rc.bottom);

		hChild = GetWindow(hChild, GW_HWNDNEXT);
	}

	MdzRect rc(0, 0, right + xPad, bottom + yPad);
	AdjustWindowRectEx(&rc, dwStyle, hMenu != NULL, dwStyleEx);
	SetSize(rc.Width(), rc.Height());
}

void MdzWindow::SetSize(int width, int height)
{
	bounds.width = width;
	bounds.height = height;

	SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

void MdzWindow::ModifyStyle(DWORD dwNewStyle, BOOL bState)
{
	if (bState)
		dwStyle |= dwNewStyle;
	else
		dwStyle &= ~dwNewStyle;
}

int MdzWindow::Execute()
{
	ShowWindow(hWnd, SW_SHOW);
	HWND hParent = GetParent(hWnd);
	EnableWindow(hParent, FALSE);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if(!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	EnableWindow(hParent, TRUE);
	ShowWindow(hWnd, SW_HIDE);
	return msg.wParam;
}


void MdzWindow::Redraw(BOOL bErase)
{
	if (hWnd)
		InvalidateRect(hWnd, NULL, bErase);
}

void MdzWindow::SetEnabled(BOOL bIsEnabled)
{
	ModifyStyle(WS_DISABLED, !bIsEnabled);
	EnableWindow(hWnd, bIsEnabled);
}

void MdzWindow::RequestFocus()
{
	SetFocus(hWnd);
}

void MdzWindow::Destroy()
{
	DestroyWindow(hWnd);
}

BOOL MdzWindow::IsEnabled()
{
	return ((dwStyle & WS_DISABLED) == 0);
}

BOOL MdzWindow::IsVisible()
{
	return ((dwStyle & WS_VISIBLE) == WS_VISIBLE);
}

MdzString MdzWindow::GetText()
{
	if (!hWnd)
		return lpTitle;

	MdzString ret;
	int length = GetWindowTextLength(hWnd);
	if (length > 0)
	{
		length++;
		ret.Alloc(length);
		GetWindowText(hWnd, (LPSTR) ret, length);
	}
	return ret;
}

void MdzWindow::SetFont(MdzFont &font)
{
	if (hFont)
		DeleteObject(hFont);

	hFont = font.GetHandle();

	SendMsg(WM_SETFONT, (WPARAM) hFont, TRUE);

}

MdzWindow::~MdzWindow()
{
	SetWindowLong(hWnd, GWL_USERDATA, 0);
	DestroyWindow(hWnd);


    evtHandlers.RemoveAll(TRUE);

	if (hFont)
		DeleteObject(hFont);

	if (hIcon)
		DeleteObject(hIcon);

	if (OnLButtonDblClk)
		delete OnLButtonDblClk;

	if (OnChar)
		delete OnChar;

	if (OnEnter)
		delete OnEnter;

	if (OnMeasureItem)
		delete OnMeasureItem;


	if (OnPaint)
		delete OnPaint;
	
	if (OnCreate)
		delete OnCreate;

	if (OnFocus)
		delete OnFocus;
	
	if (OnSize)
		delete OnSize;

	if (OnMouseMove)
		delete OnMouseMove;
	
	if (OnLeftButtonUp)
		delete OnLeftButtonUp;

	if (OnLeftButtonDown)
		delete OnLeftButtonDown;

	if (OnRightButtonUp)
		delete OnRightButtonUp;

	if (OnRightButtonDown)
		delete OnRightButtonDown;

	if (OnClose)
		delete OnClose;

	if (OnCommand)
		delete OnCommand;

	if (OnNotify)
		delete OnNotify;

	if (OnHScroll)
		delete OnHScroll;

	if (OnVScroll)
		delete OnVScroll;

	if (OnDrawItem)
		delete OnDrawItem;

	if (OnCtlColor)
		delete OnCtlColor;

	if (OnKeyDown)
		delete OnKeyDown;

	if (OnKeyUp)
		delete OnKeyUp;
}

void MdzWindow::SetIcon(WORD iResId)
{
	hIcon = (HICON) LoadIcon((iResId < 32000) ? GetModuleHandle(NULL) : NULL,
		MAKEINTRESOURCE(iResId));
}

void MdzWindow::SetVisible(BOOL bIsVisible)
{
	ModifyStyle(WS_VISIBLE, bIsVisible);
	ShowWindow(hWnd, (bIsVisible) ? SW_SHOW : SW_HIDE);
}

MdzWindow* MdzWindow::GetWindowPtr(HWND hWnd)
{
	return (MdzWindow*) GetWindowLong(hWnd, GWL_USERDATA);
}

void MdzWindow::AddEventHandler(MdzEventHandler* lpEvtHandler)
{
    evtHandlers.Add(lpEvtHandler);
}

void MdzWindow::RemoveEventHandler(MdzEventHandler *lpEvtHandler)
{
    int idx = evtHandlers.Find(lpEvtHandler);

    if (idx >= 0)
        evtHandlers.RemoveAt(idx);
}

void MdzWindow::AdjustWindowRect(MdzRect &rc)
{
	AdjustWindowRectEx(&rc, dwStyle, hMenu != NULL, dwStyleEx);
}

void MdzWindow::ScanMenu(HMENU hMenu, MdzVector &vector, BOOL bRecurse)
{
	int iCount = GetMenuItemCount(hMenu);
	for (int i = 0; i < iCount; i++)
	{
		UINT iId = GetMenuItemID(hMenu, i);
		if (iId == (UINT) -1)
		{
			if (bRecurse)
				ScanMenu(GetSubMenu(hMenu, i), vector);
		}
		else if (iId != 0)
		{
			//MdzMenuItem* lpMenuItem = MdzMenuItem::GetPtrFromId(hMenu, iId);
			MdzMenuItem* lpMenuItem = MdzMenuItem::GetPtrFromId(iId);
			lpMenuItem->iPos = i;
			vector.Add(lpMenuItem);
		}
	}
}

//HACCEL MdzWindow::CreateAccelTable()
HACCEL MdzWindow::CreateAccelTable(MdzVector* pVector)
{
	MdzVector vector;

	if (hMenu)
		ScanMenu(hMenu, vector);

	if (pVector)
	{
		for (UINT i = 0; i < pVector->GetCount(); i++)
			vector.Add(pVector->GetAt(i));
	}

	if (vector.GetCount() == 0)
		return NULL;

	int iSize = 0;
	for (UINT i = 0; i < vector.GetCount(); i++)
	{
		MdzMenuItem* lpItem = (MdzMenuItem*) vector.GetAt(i);
		if (lpItem->lpAccel)
			iSize++;
	}
	if (iSize == 0)
		return NULL;

	LPACCEL lpAccel = new tagACCEL[iSize];
	UINT iIndex = 0;

	for ( i = 0; i < vector.GetCount(); i++)
	{
		MdzMenuItem* lpItem = (MdzMenuItem*) vector.GetAt(i);
		if (lpItem->lpAccel)
			CopyMemory(&lpAccel[iIndex++], lpItem->lpAccel, sizeof(ACCEL));
	}
	HACCEL hAccel = CreateAcceleratorTable(lpAccel, iSize);	
	delete [] lpAccel;

	return hAccel;
}	

void MdzWindow::SetCursor(WORD iResId)
{
	if (hCursor)
		DeleteObject(hCursor);

	hCursor = (HCURSOR) LoadCursor((iResId < 32000) ? GetModuleHandle(NULL) : NULL,
		MAKEINTRESOURCE(iResId));
}

MdzBounds MdzWindow::GetBounds()
{
	if (!hWnd)
		return GetRealBounds();

	MdzRect rc;
	GetWindowRect(hWnd, &rc);
	HWND hParent = GetParent(hWnd);

	if (hParent)
	{
		ScreenToClient(hParent, (LPPOINT) &rc.left);
		ScreenToClient(hParent, (LPPOINT) &rc.right);
	}
	return rc;
}

MdzFont MdzWindow::GetFont()
{
	return MdzFont(hFont);
}

MdzBounds MdzWindow::GetRealBounds()
{
	MdzBounds ret = bounds;

	if (lpClassName &&
		!strcmp(lpClassName, "COMBOBOX"))
	{
		HDC hdc = GetDC(NULL);
		SelectObject(hdc, hFont);
		SIZE sz;
		GetTextExtentPoint32(hdc, "AaPp", 4, &sz);
		ReleaseDC(NULL, hdc);
		ret.height = sz.cy + 8;
	}
	return ret;
}



void MdzWindow::ProcessChildEvent(MdzEvent &evt)
{
	if (evt.uMsg == WM_CHAR)
	{
		if (evt.wParam == 13)
		{
			if (OnEnter)
				OnEnter->Fire();
			else
				evt.lResult = CallWindowProc(lpWndProc, hWnd, evt.uMsg, evt.wParam, evt.lParam);

		}
		else
		{
			if (OnChar && (evt.wParam >= 32 || evt.wParam == 9))
				OnChar->Fire(evt.wParam);
			else
				evt.lResult = CallWindowProc(lpWndProc, hWnd, evt.uMsg, evt.wParam, evt.lParam);
		}
		return;
	}

	if (evt.uMsg == WM_LBUTTONDBLCLK)
	{
		if (OnLButtonDblClk)
			OnLButtonDblClk->Fire(LOWORD(evt.lParam), HIWORD(evt.lParam));
		else
			evt.lResult = CallWindowProc(lpWndProc, hWnd, evt.uMsg, evt.wParam, evt.lParam);
		return;
	}

	if (evt.uMsg == WM_COMMAND)
	{
		MdzWindow* pWnd = GetWindowPtr((HWND)evt.lParam);
		if (pWnd && pWnd->OnCommand)
			pWnd->OnCommand->Fire(evt);
		else
			evt.lResult = CallWindowProc(lpWndProc, hWnd, evt.uMsg, evt.wParam, evt.lParam);
	}
	else
		evt.lResult = CallWindowProc(lpWndProc, hWnd, evt.uMsg, evt.wParam, evt.lParam);
}
