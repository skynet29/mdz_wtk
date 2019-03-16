// MdzTimer.cpp: implementation of the MdzTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTimer.h"
#include "MdzCtrl.h"
#include "MdzFrame.h"


static BOOL TestFunc(MdzEvent& evt, DWORD dwArg)
{
	return (evt.uMsg == WM_TIMER && evt.wParam == dwArg);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static UINT gIdent = 1;

MdzTimer::MdzTimer()
{
	delay = 1000; // 1 sec
	iIdent = gIdent++;
	bIsRunning = FALSE;
	lpEvtHandler = new MdzEventHandler(TestFunc,
		MDZ_CBK3(MdzTimer, OnTimer), iIdent);

	MdzFrame::GetMainFrame()->AddEventHandler(lpEvtHandler);
	lpOnTimeout = NULL;
}

MdzTimer::~MdzTimer()
{
    MdzFrame::GetMainFrame()->RemoveEventHandler(lpEvtHandler);

    if (lpOnTimeout)
        delete lpOnTimeout;

}

void MdzTimer::SetDelay(UINT delay)
{
	MEMBER_SET(delay);
}

void MdzTimer::Start()
{
	SetTimer(MdzFrame::GetMainFrame()->GetHandle(), iIdent, delay, NULL);
	bIsRunning = TRUE;
}

void MdzTimer::Stop()
{
	KillTimer(MdzFrame::GetMainFrame()->GetHandle(), iIdent);
	bIsRunning = FALSE;
}



void MdzTimer::SetOnTimeout(MdzCbk1 *lpFunc)
{
    if (lpOnTimeout)
        delete lpOnTimeout;
    lpOnTimeout = lpFunc;
}

BOOL MdzTimer::IsRunning()
{
	return bIsRunning;
}

void MdzTimer::OnTimer(MdzEvent& evt)
{
	if (lpOnTimeout)
		lpOnTimeout->Fire();
}

UINT MdzTimer::GetDelay()
{
	return delay;
}
