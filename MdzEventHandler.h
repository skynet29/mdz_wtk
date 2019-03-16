// MdzEventHandler.h: interface for the MdzEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZEVENTHANDLER_H__0CAB5FB0_26C6_4B7A_A0A7_5AEA76238BE5__INCLUDED_)
#define AFX_MDZEVENTHANDLER_H__0CAB5FB0_26C6_4B7A_A0A7_5AEA76238BE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzEvent.h"
#include "MdzCbk3.h"
#include "MdzObject.h"

typedef BOOL (*MdzTestFunc)(MdzEvent& evt, DWORD dwArg);

class DllExport MdzEventHandler : public MdzObject 
{
public:
	MdzEventHandler(MdzTestFunc lpTestFunc, MdzCbk3* lpCallbackFunc, DWORD dwArg);
	virtual ~MdzEventHandler();

private:
	BOOL HandleEvent(MdzEvent& evt);
   MdzCbk3* lpCallbackFunc;
	MdzTestFunc lpTestFunc;
	DWORD dwArg;


	friend class MdzWindow;
};

#endif // !defined(AFX_MDZEVENTHANDLER_H__0CAB5FB0_26C6_4B7A_A0A7_5AEA76238BE5__INCLUDED_)
