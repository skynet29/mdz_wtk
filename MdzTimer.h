// MdzTimer.h: interface for the MdzTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTIMER_H__E8D22F9B_C7AF_4CEF_83F4_08360033359B__INCLUDED_)
#define AFX_MDZTIMER_H__E8D22F9B_C7AF_4CEF_83F4_08360033359B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzCbk1.h"
#include "MdzEventHandler.h"

class DllExport MdzTimer  
{
public:
	UINT GetDelay();
	MdzTimer();

	virtual ~MdzTimer();

	void
	SetOnTimeout(MdzCbk1* lpFunc);
	
	void
	SetDelay(UINT delay);

	void
	Stop();
	
	void
	Start();
	
	BOOL
	IsRunning();
private:
	void OnTimer(MdzEvent& evt);
	UINT delay;
	UINT iIdent;
	BOOL bIsRunning;
	MdzEventHandler* lpEvtHandler;
	MdzCbk1* lpOnTimeout;

};

#endif // !defined(AFX_MDZTIMER_H__E8D22F9B_C7AF_4CEF_83F4_08360033359B__INCLUDED_)
