// MdzWindow.h: interface for the MdzWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZWINDOW_H__CFC98690_BF6F_4AA0_AAC8_9638A249C39E__INCLUDED_)
#define AFX_MDZWINDOW_H__CFC98690_BF6F_4AA0_AAC8_9638A249C39E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzBounds.h"
#include "MdzCbk1.h"
#include "MdzCbk2.h"
#include "MdzCbk3.h"
#include "MdzCbk4.h"
#include "MdzCbk5.h"
#include "MdzCbk6.h"

#include "MdzString.h"
#include "MdzVector.h"
#include "MdzEventHandler.h"
#include "MdzFont.h"	// Added by ClassView

class MdzEvent;
class MdzFont;

class MdzWindow  
{
public:
	void ProcessChildEvent(MdzEvent &evt);
	MdzWindow();
	~MdzWindow();

	MdzBounds
	GetRealBounds();
	
	MdzFont
	GetFont();
	
	MdzBounds
	GetBounds();
	
	void
	SetCursor(WORD iResId);
	
	HACCEL
	CreateAccelTable(MdzVector* pVector = NULL);
	
	static void
	ScanMenu(HMENU hMenu, MdzVector &vector, BOOL bRecurse = TRUE);
	
	void
	AdjustWindowRect(MdzRect& rc);
	
	void
	RemoveEventHandler(MdzEventHandler* lpEvtHandler);
	
	void
	AddEventHandler(MdzEventHandler* lpEvtHandler);
	
	void
	SetVisible(BOOL bIsVisible);
	
	void
	SetIcon(WORD iResId);

	void
	SetEnabled(BOOL bIsEnabled);
	
	void
	SetSize(int width, int height);
	
	void
	SetLocation(int left, int top);
	
	void
	SetText(LPSTR lpText);
	
	void
	SetBounds(MdzBounds& bounds);
	
	void
	SetFont(MdzFont& font);

	MdzString
	GetText();
	
	HWND
	GetHandle();

	BOOL
	IsEnabled();

	BOOL IsVisible();
	
	BOOL
	Create(HWND hParent);
	
	void
	Destroy();
	
	void
	RequestFocus();
	
	void
	Redraw(BOOL bErase);
	
	void
	ModifyStyle(DWORD dwNewStyle, BOOL bState);
	
	void
	Pack(int xPad, int yPad);
	
	void
	CenterToParent();
	
	void
	Close(int iRetValue = 0);
	
	int
	Execute();
	
	LRESULT
	SendMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0);

	static int
	MessageLoop();
	
	static BOOL
	RegisterWindow();
	
	static MdzWindow*
	GetWindowPtr(HWND hWnd);

	LPSTR		lpClassName;
	MdzString	lpTitle;
	DWORD		dwStyle;
	DWORD		dwStyleEx;
	HMENU		hMenu;
	LPVOID		lpParam;
	COLORREF	backColor;
	MdzBounds	bounds;
	BOOL		bOpaque;	  
    LPVOID		lpUserData;
	WNDPROC		lpWndProc;

	MdzCbk4*	OnPaint;
	MdzCbk1*    OnCreate;
	MdzCbk1*    OnDestroy;
	MdzCbk6*    OnFocus;
	MdzCbk2*    OnSize;
	MdzCbk2*    OnMouseMove;
	MdzCbk2*    OnMouseDrag;
	MdzCbk2*    OnLeftButtonUp;
	MdzCbk2*    OnLeftButtonDown;
	MdzCbk2*    OnRightButtonUp;
	MdzCbk2*    OnRightButtonDown;
	MdzCbk5*    OnClose;
	MdzCbk3*    OnCommand;
	MdzCbk3*    OnNotify;
	MdzCbk3*    OnHScroll;
	MdzCbk3*    OnVScroll;
	MdzCbk3*    OnDrawItem;
	MdzCbk3*	OnMeasureItem;
	MdzCbk3*    OnCtlColor;
	MdzCbk6*	OnKeyDown;
	MdzCbk6*	OnKeyUp;
	MdzCbk6*	OnChar;
	MdzCbk2*	OnLButtonDblClk;
	MdzCbk1*	OnEnter;

private:
	void ProcessEvent(MdzEvent& evt);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND		hWnd;
	HWND		hMdiClient;
	HFONT		hFont;
	HICON		hIcon;
   MdzVectorT<MdzEventHandler>   evtHandlers;
	HCURSOR hCursor;
	MdzWindow* pDragWnd;

};

#endif // !defined(AFX_MDZWINDOW_H__CFC98690_BF6F_4AA0_AAC8_9638A249C39E__INCLUDED_)
