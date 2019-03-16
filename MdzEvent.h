// MdzEvent.h: interface for the MdzEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZEVENT_H__8C12C941_21D4_4C67_8B94_3526462EA489__INCLUDED_)
#define AFX_MDZEVENT_H__8C12C941_21D4_4C67_8B94_3526462EA489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class DllExport MdzEvent  
{
public:

	virtual ~MdzEvent();

	UINT	uMsg;
	WPARAM	wParam;
	LPARAM	lParam;
	LRESULT	lResult;
	void ProcessDefault(HWND hWnd, HWND hMdiClient = NULL);
private:
	void ProcessMDIDefault(HWND hWnd);
	MdzEvent(UINT uMsg, WPARAM	wParam, LPARAM lParam);

	friend class MdzWindow;

};

#endif // !defined(AFX_MDZEVENT_H__8C12C941_21D4_4C67_8B94_3526462EA489__INCLUDED_)
