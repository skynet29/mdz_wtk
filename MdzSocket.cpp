// MdzSocket.cpp: implementation of the MdzSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSocket.h"
#include "MdzFrame.h"
#include "MdzEventHandler.h"

#define WSA_EVENT     (WM_USER + 1)


static BOOL TestFunc(MdzEvent& evt, DWORD dwArg)
{
	return (evt.uMsg == WSA_EVENT && evt.wParam == dwArg);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSocket::MdzSocket()
{
	sock = INVALID_SOCKET;
	lpEvtHandler = NULL;

}

MdzSocket::~MdzSocket()
{
	Close();
}

BOOL MdzSocket::InitClass()
{
	WSADATA WSAData;

	return (WSAStartup(MAKEWORD(2,0), &WSAData) == 0);

}

BOOL MdzSocket::Create()
{
	sock = socket( AF_INET, SOCK_STREAM, 0);

	return (sock != INVALID_SOCKET);

}

void MdzSocket::Close()
{
	if (lpEvtHandler)
		MdzFrame::GetMainFrame()->RemoveEventHandler(lpEvtHandler);

	lpEvtHandler = NULL;

	closesocket(sock);
	sock = INVALID_SOCKET;

}

BOOL MdzSocket::CatchEvent(long lEvent)
{
	lpEvtHandler = new MdzEventHandler(TestFunc, 
		MDZ_CBK3(MdzSocket, OnWSAEvent), (DWORD) sock);
	MdzFrame::GetMainFrame()->AddEventHandler(lpEvtHandler);

	return (WSAAsyncSelect(sock, MdzFrame::GetMainFrame()->GetHandle(),
		WSA_EVENT, lEvent) != SOCKET_ERROR);

}
