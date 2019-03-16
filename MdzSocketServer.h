// MdzSocketServer.h: interface for the MdzSocketServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSOCKETSERVER_H__A8B47F1F_D85A_4975_A971_B273EE79EF8F__INCLUDED_)
#define AFX_MDZSOCKETSERVER_H__A8B47F1F_D85A_4975_A971_B273EE79EF8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzSocket.h"

class MdzEvent;
class MdzEventHandler;
class MdzCbk1;
class MdzSocketClient;

class DllExport MdzSocketServer : public MdzSocket
{
public:
	MdzSocketClient* Accept();
	void SetOnIncomingConnection(MdzCbk1* lpFunc);
	BOOL Listen(UINT iPort, UINT iMaxPendingConnection = 1);
	MdzSocketServer();
	virtual ~MdzSocketServer();
private:
	virtual void OnWSAEvent(MdzEvent& evt);
	MdzCbk1* lpOnIncomingConnection;
};

#endif // !defined(AFX_MDZSOCKETSERVER_H__A8B47F1F_D85A_4975_A971_B273EE79EF8F__INCLUDED_)
