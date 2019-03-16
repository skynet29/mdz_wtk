// MdzStatusBar.cpp: implementation of the MdzStatusBar class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzStatusBar.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzStatusBar::MdzStatusBar()
{
	lpWnd->lpClassName = STATUSCLASSNAME;
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
}

MdzStatusBar::~MdzStatusBar()
{

}



void MdzStatusBar::SetText(LPSTR strText)
{
	lpWnd->SetText(strText);
}
