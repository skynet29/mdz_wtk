// MdzEvent.cpp: implementation of the MdzEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzEvent::MdzEvent(
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
)
{
	MEMBER_SET(uMsg);
	MEMBER_SET(wParam);
	MEMBER_SET(lParam);

	lResult	= 0;
}

MdzEvent::~MdzEvent()
{

}

void MdzEvent::ProcessDefault(HWND hWnd, HWND hMdiClient)
{
	lResult = DefFrameProc(hWnd, hMdiClient, uMsg, wParam, lParam);
}

void MdzEvent::ProcessMDIDefault(HWND hWnd)
{
	lResult = DefMDIChildProc(hWnd, uMsg, wParam, lParam);

}
