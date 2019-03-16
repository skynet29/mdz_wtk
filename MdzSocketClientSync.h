// MdzSocketClientSync.h: interface for the MdzSocketClientSync class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSOCKETCLIENTSYNC_H__A27FFB0B_35E9_46C9_BE06_E86C37993DBF__INCLUDED_)
#define AFX_MDZSOCKETCLIENTSYNC_H__A27FFB0B_35E9_46C9_BE06_E86C37993DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzSocketClient.h"
#include "MdzTimer.h"

class DllExport MdzSocketClientSync : public MdzSocketClient  
{
public:
	enum {
		K_STATUS_OK,
		K_STATUS_TIMEOUT,
		K_STATUS_CONNECTION_CLOSED
	};

	MdzSocketClientSync();

	int
	WaitForData(UINT iTimeout);

	virtual ~MdzSocketClientSync();

private:
	void OnTimeout();
	void OnConnectionClosed();
	void OnDataReceived();
	BOOL bWaitingData;
	MdzTimer timer;
};

#endif // !defined(AFX_MDZSOCKETCLIENTSYNC_H__A27FFB0B_35E9_46C9_BE06_E86C37993DBF__INCLUDED_)
