// MdzThread.h: interface for the MdzThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTHREAD_H__E013C80E_16DA_4D73_A5CA_C10ED2D8FE9C__INCLUDED_)
#define AFX_MDZTHREAD_H__E013C80E_16DA_4D73_A5CA_C10ED2D8FE9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzCbk1.h"

class MdzThread  
{
public:
	void SetOnRun(MdzCbk1* pFunc);
	void Start();
	MdzThread();
	virtual ~MdzThread();

protected:
	virtual void OnRun();
private:
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	MdzCbk1* m_pFunc;
	HANDLE hThread;
	DWORD dwThreadId;
};

#endif // !defined(AFX_MDZTHREAD_H__E013C80E_16DA_4D73_A5CA_C10ED2D8FE9C__INCLUDED_)
