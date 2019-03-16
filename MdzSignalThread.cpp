// MdzSignalThread.cpp: implementation of the MdzSignalThread class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSignalThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSignalThread::MdzSignalThread(UINT iNbEvents)
{
	m_pOnSignalFunc = NULL;
	m_iNbEvents = iNbEvents + 1;
	pEvents = new HANDLE[m_iNbEvents];

	for(UINT i = 0; i < m_iNbEvents; i++)
		pEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

}

MdzSignalThread::~MdzSignalThread()
{
	for(UINT i = 0; i < m_iNbEvents; i++)
		CloseHandle(pEvents[i]);
	delete [] pEvents;
	if (m_pOnSignalFunc)
		delete m_pOnSignalFunc;
}

void MdzSignalThread::SetSignal(UINT iSignalNumber)
{
	iSignalNumber++;
	if (iSignalNumber < m_iNbEvents)
		SetEvent(pEvents[iSignalNumber]);
}

void MdzSignalThread::ResetSignal(UINT iSignalNumber)
{
	iSignalNumber++;
	if (iSignalNumber < m_iNbEvents)
		ResetEvent(pEvents[iSignalNumber]);

}

void MdzSignalThread::OnSignal(UINT iSignalNumber)
{
	if (m_pOnSignalFunc)
		m_pOnSignalFunc->Fire(iSignalNumber);
}

void MdzSignalThread::OnRun()
{
	MdzThread::OnRun();
	while (1)
	{
		DWORD dwRet = WaitForMultipleObjects(m_iNbEvents, pEvents, FALSE, INFINITE);
		if (dwRet == WAIT_OBJECT_0)
			break;

		if (dwRet != WAIT_FAILED)
			OnSignal(dwRet - WAIT_OBJECT_0 - 1);
	}
}

void MdzSignalThread::SetOnSignal(MdzCbk6 *pFunc)
{
	if (m_pOnSignalFunc)
		delete m_pOnSignalFunc;
	m_pOnSignalFunc = pFunc;
}

void MdzSignalThread::Stop()
{
	SetEvent(pEvents[0]);
}
