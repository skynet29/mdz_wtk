// MdzSignalThread.h: interface for the MdzSignalThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSIGNALTHREAD_H__C428CCAC_54FA_489B_BF4C_90A486512B28__INCLUDED_)
#define AFX_MDZSIGNALTHREAD_H__C428CCAC_54FA_489B_BF4C_90A486512B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzThread.h"
#include "MdzCbk6.h"

class MdzSignalThread : public MdzThread  
{
public:
	void Stop();
	void SetOnSignal(MdzCbk6* pFunc);
	void ResetSignal(UINT iSignalNumber);
	void SetSignal(UINT iSignalNumber);
	MdzSignalThread(UINT iNbEvents);
	virtual ~MdzSignalThread();
private:
	HANDLE* pEvents;
	UINT m_iNbEvents;
	MdzCbk6* m_pOnSignalFunc;
protected:
	virtual void OnRun();
	virtual void OnSignal(UINT iSignalNumber);
};

#endif // !defined(AFX_MDZSIGNALTHREAD_H__C428CCAC_54FA_489B_BF4C_90A486512B28__INCLUDED_)
