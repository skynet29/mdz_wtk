// MdzFrame.h: interface for the MdzFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZFRAME_H__3CF1B688_5D4D_462A_A018_325E5727634C__INCLUDED_)
#define AFX_MDZFRAME_H__3CF1B688_5D4D_462A_A018_325E5727634C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzContainer.h"
#include "MdzCbk3.h"
#include "MdzCbk1.h"
#include "MdzString.h"	// Added by ClassView
#include "MdzBounds.h"

class MdzMenuItem;

#define MDZ_DECLARE_FRAME(Frame) \
int APIENTRY WinMain(HINSTANCE hInstance, \
                     HINSTANCE hPrevInstance, \
                     LPSTR     lpCmdLine, \
                     int       nCmdShow) \
{ \
	MdzFrame::InitApp(); \
	return Frame().Run(lpCmdLine, nCmdShow); \
}

class MdzMenuBar;
class MdzDockBar;
class MdzGraphic;
class MdzStatusBar;
class MdzEventHandler;


class DllExport MdzFrame : public MdzContainer  
{
public:
	MdzString GetCmdLine();
	void OpenHtmlHelpFile(LPSTR strFileName, LPSTR strKeyWord = NULL);
	MdzFrame();

	virtual ~MdzFrame();

	void
	AddShortcut(UINT iKeyChanger, char character, MdzCbk1* lpFunc);

	static MdzFrame*
	GetMainFrame();

	void
	SetStatusBar(MdzStatusBar& statusBar);

	void
	SetDockBar(MdzDockBar& rebar);

	void
	SetClientCtrl(MdzCtrl& ctrl);

	void
	SetMenuBar(MdzMenuBar &menuBar);

	void
	SetResizable(BOOL bIsResizable);

	void
	SetTitle(LPSTR strTitle);
	
	void
	SetBackColor(COLORREF backColor);
	
	void
	SetIcon(WORD iResId);
	
	void
	SetCursor(WORD iResId);

	void
	RemoveEventHandler(MdzEventHandler* lpEvtHandler);
	
	void
	AddEventHandler(MdzEventHandler* lpEvtHandler);

	void
	OpenHelpFile(LPSTR strFileName, LPSTR strKeyWord = NULL);

	void
	Close();

	int
	Run(LPSTR strCmdLine, int iCmdShow = SW_SHOW);

	void
	Redraw(BOOL bErase = TRUE);

	virtual void
	OnCreate();

	virtual void
	OnFocus(UINT bGotFocus);


	virtual BOOL
	OnClose();


	static BOOL
	InitApp();

private:
	void OnSize(int width, int height);
	void OnDestroy();
	void OnDockBarResized(MdzRect& rc);

	MdzDockBar* lpDockBar;
	MdzCtrl* lpClientCtrl;
	MdzStatusBar* lpStatusBar;
	HACCEL hAccel;
	MdzVectorT<MdzMenuItem> shortcuts;
	MdzString strCmdLine;

	friend class MdzDockBar;
protected:
	virtual void OnSize(MdzRect& rc);
	virtual void OnIdle();
};


#endif // !defined(AFX_MDZFRAME_H__3CF1B688_5D4D_462A_A018_325E5727634C__INCLUDED_)
