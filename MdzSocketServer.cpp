// MdzSocketServer.cpp: implementation of the MdzSocketServer class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSocketServer.h"
#include "MdzEvent.h"
#include "MdzCbk1.h"
#include "MdzSocketClient.h"
#include "MdzStdDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSocketServer::MdzSocketServer()
{
	lpOnIncomingConnection = NULL;
}

MdzSocketServer::~MdzSocketServer()
{
	if (lpOnIncomingConnection)
		delete lpOnIncomingConnection;
}

void MdzSocketServer::OnWSAEvent(MdzEvent& evt)
{
	switch (WSAGETSELECTEVENT(evt.lParam))
	{
	case FD_ACCEPT:
		if (lpOnIncomingConnection)
			lpOnIncomingConnection->Fire();
		break;

	}
}

BOOL MdzSocketServer::Listen(UINT iPort, UINT iMaxPendingConnection)
{
	if (!Create())
		return FALSE;

	SOCKADDR_IN sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(iPort);
	sockaddr.sin_addr.s_addr = INADDR_ANY;


	if (bind(sock, (PSOCKADDR) &sockaddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		Close();
		return FALSE;
	}

	if (listen(sock, iMaxPendingConnection) < 0)
	{
		Close();
		return FALSE;
	}

	if (!CatchEvent(FD_ACCEPT))
	{
		Close();
		return FALSE;
	}

	return TRUE;
}

void MdzSocketServer::SetOnIncomingConnection(MdzCbk1 *lpFunc)
{
	if (lpOnIncomingConnection)
		delete lpOnIncomingConnection;

	lpOnIncomingConnection = lpFunc;
}

MdzSocketClient* MdzSocketServer::Accept()
{
	SOCKET sClient = accept(sock, NULL, NULL);
	if (sClient < 0)
		return NULL;

	return new MdzSocketClient(sClient);
}
