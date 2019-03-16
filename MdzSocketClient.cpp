// MdzSocketClient.cpp: implementation of the MdzSocketClient class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFrame.h"
#include "MdzSocketClient.h"
#include "MdzCtrl.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MdzSocketClient::MdzSocketClient()
{
	lpOnDataReceived = NULL;
	lpOnConnectionClosed = NULL;

}

MdzSocketClient::~MdzSocketClient()
{

    if (lpOnDataReceived)
        delete lpOnDataReceived;

	 if (lpOnConnectionClosed)
		 delete lpOnConnectionClosed;

	Close();
}

BOOL MdzSocketClient::Connect(LPSTR strHostName, UINT iPortNumber)
{
	if (!Create())
		return FALSE;

	SOCKADDR_IN sockaddr;
	
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(iPortNumber);

	ULONG ipAddr = inet_addr(strHostName);

	if (ipAddr == INADDR_NONE)
	{
		// try with hostname
		PHOSTENT phe;
		phe = gethostbyname(strHostName);

		if (phe == NULL)
		{
			Close();
			return FALSE;
		}

		memcpy((char*)&(sockaddr.sin_addr), phe->h_addr, phe->h_length);
	}
	else
		sockaddr.sin_addr.s_addr = ipAddr;


	if (connect(sock, (PSOCKADDR) &sockaddr, sizeof(sockaddr)) != 0)
	{
		Close();
		return FALSE;
	}

	if (!CatchEvent(FD_READ | FD_CLOSE))
	{
		Close();
		return FALSE;
	}


	return TRUE;

}



void MdzSocketClient::SetOnDataReceived(MdzCbk1 *lpFunc)
{
	if (lpOnDataReceived)
        delete lpOnDataReceived;

    lpOnDataReceived = lpFunc;
}

BOOL MdzSocketClient::SendData(LPSTR buffer)
{
	return (send(sock, buffer, strlen(buffer), 0) != SOCKET_ERROR);
}

MdzString MdzSocketClient::GetData()
{
	MdzString ret;

	char buffer[1024];
	int bytesRead = recv(sock, buffer, sizeof(buffer), 0);
	if (bytesRead != SOCKET_ERROR)
	{
		buffer[bytesRead] = 0;
		ret = MdzString(buffer);
	}

	return ret;
}





void MdzSocketClient::OnWSAEvent(MdzEvent& evt)
{
	switch (WSAGETSELECTEVENT(evt.lParam))
	{
	case FD_READ:
		if (lpOnDataReceived)
			lpOnDataReceived->Fire();
		break;

	case FD_CLOSE:
		Close();
		if (lpOnConnectionClosed)
			lpOnConnectionClosed->Fire();
		break;
	}
}

void MdzSocketClient::SetOnConnectionClosed(MdzCbk1 *lpFunc)
{
	if (lpOnConnectionClosed)
        delete lpOnConnectionClosed;

    lpOnConnectionClosed = lpFunc;
}

BOOL MdzSocketClient::IsConnected()
{
	return (sock != INVALID_SOCKET);
}

BOOL MdzSocketClient::SendBuffer(LPBYTE buffer, UINT buffSize)
{
	return (send(sock, (LPCSTR)buffer, buffSize, 0) != SOCKET_ERROR);

}

int MdzSocketClient::GetBuffer(LPBYTE buffer, UINT buffSize)
{
	return recv(sock, (LPSTR)buffer, buffSize, 0);

}

MdzSocketClient::MdzSocketClient(SOCKET sock)
{
	lpOnDataReceived = NULL;
	lpOnConnectionClosed = NULL;
	MEMBER_SET(sock);
	CatchEvent(FD_READ | FD_CLOSE);
}
