// MdzThread.cpp: implementation of the MdzThread class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD MdzThread::ThreadProc(LPVOID lpParam)
{
	((MdzThread*)lpParam)->OnRun();
	return 0;
}

MdzThread::MdzThread()
{
	m_pFunc = NULL;
	hThread = NULL;
}

MdzThread::~MdzThread()
{
	CloseHandle(hThread);
	if (m_pFunc)
		delete m_pFunc;
}

void MdzThread::OnRun()
{
	if (m_pFunc)
		m_pFunc->Fire();
}

void MdzThread::Start()
{
	hThread = CreateThread(NULL, 4096, ThreadProc, this, 0, &dwThreadId);
}

void MdzThread::SetOnRun(MdzCbk1 *pFunc)
{
	if (m_pFunc)
		delete m_pFunc;
	m_pFunc = pFunc;
}
