// MdzSocketClientSync.cpp: implementation of the MdzSocketClientSync class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSocketClientSync.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSocketClientSync::MdzSocketClientSync()
{
	SetOnDataReceived(MDZ_CBK1(MdzSocketClientSync, OnDataReceived));
	SetOnConnectionClosed(MDZ_CBK1(MdzSocketClientSync, OnConnectionClosed));
	bWaitingData = FALSE;
	timer.SetOnTimeout(MDZ_CBK1(MdzSocketClientSync, OnTimeout));
}

MdzSocketClientSync::~MdzSocketClientSync()
{

}

void MdzSocketClientSync::OnDataReceived()
{
	if (bWaitingData)
		PostQuitMessage(K_STATUS_OK);
}

void MdzSocketClientSync::OnConnectionClosed()
{
	if (bWaitingData)
		PostQuitMessage(K_STATUS_CONNECTION_CLOSED);

}

void MdzSocketClientSync::OnTimeout()
{
	if (bWaitingData)
		PostQuitMessage(K_STATUS_TIMEOUT);
	timer.Stop();

}

int MdzSocketClientSync::WaitForData(UINT iTimeout)
{
	if (!IsConnected())
		return K_STATUS_CONNECTION_CLOSED;

	bWaitingData = TRUE;
	timer.SetDelay(iTimeout);
	timer.Start();
	int status = MdzWindow::MessageLoop();
	bWaitingData = FALSE;
	return status;
}
