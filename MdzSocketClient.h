// MdzSocketClient.h: interface for the MdzSocketClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSOCKETCLIENT_H__B43C229B_7912_474E_8FBA_E36570F08105__INCLUDED_)
#define AFX_MDZSOCKETCLIENT_H__B43C229B_7912_474E_8FBA_E36570F08105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzSocket.h"
#include "MdzCbk1.h"
#include "MdzString.h"	// Added by ClassView

#include "MdzEventHandler.h"

class DllExport MdzSocketClient : public MdzSocket 
{
public:
	int GetBuffer(LPBYTE buffer, UINT buffSize);
	BOOL SendBuffer(LPBYTE buffer, UINT buffSize);
	MdzSocketClient();
	
	BOOL
	IsConnected();

	void
	SetOnConnectionClosed(MdzCbk1* lpFunc);


	MdzString
	GetData();

	BOOL
	SendData(LPSTR buffer);
	
	void
	SetOnDataReceived(MdzCbk1* lpFunc);
	

	BOOL
	Connect(LPSTR strHostName, UINT iPortNumber);

	virtual ~MdzSocketClient();
private:
	MdzSocketClient(SOCKET sock);
	virtual void OnWSAEvent(MdzEvent& evt);
	MdzCbk1* lpOnDataReceived;
	MdzCbk1* lpOnConnectionClosed;

	friend class MdzSocketServer;
};

#endif // !defined(AFX_MDZSOCKETCLIENT_H__B43C229B_7912_474E_8FBA_E36570F08105__INCLUDED_)
