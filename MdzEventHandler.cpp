// MdzEventHandler.cpp: implementation of the MdzEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzEventHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MdzEventHandler::MdzEventHandler(
	MdzTestFunc lpTestFunc, MdzCbk3* lpCallbackFunc, DWORD dwArg)
{
    MEMBER_SET(lpTestFunc);
    MEMBER_SET(lpCallbackFunc);
    MEMBER_SET(dwArg);
}

MdzEventHandler::~MdzEventHandler()
{
    delete lpCallbackFunc;
}


BOOL MdzEventHandler::HandleEvent(MdzEvent &evt)
{
    if (lpTestFunc(evt, dwArg))
    {
        lpCallbackFunc->Fire(evt);
        return TRUE;
    }
    return FALSE;
}
