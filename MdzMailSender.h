// MdzMailSender.h: interface for the MdzMailSender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMAILSENDER_H__780E889A_7FE4_4DCB_9086_ED9689596B56__INCLUDED_)
#define AFX_MDZMAILSENDER_H__780E889A_7FE4_4DCB_9086_ED9689596B56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzString.h"
#include "MdzSocketClient.h"
#include "MdzTimer.h"

class DllExport MdzMailSender  
{
public:
	MdzMailSender();

	MdzString
	Send();
	
	void
	SetTimeout(UINT iTimeout);

	void
	SetBody(LPSTR strBody);

	void
	SetSubject(LPSTR strSubject);
	
	void
	SetFrom(LPSTR strFrom);
	
	void
	SetTo(LPSTR strTo);
	
	void
	SetSmtpServer(LPSTR strHost);
	
	virtual ~MdzMailSender();
private:
	void OnTimeout();
	void OnDataReceived();
	MdzString strHost;
	MdzString strTo;
	MdzString strFrom;
	MdzString strSubject;
	MdzString strBody;
	UINT iState;
	MdzSocketClient sock;
	MdzTimer timer;
	MdzString bError;

};

#endif // !defined(AFX_MDZMAILSENDER_H__780E889A_7FE4_4DCB_9086_ED9689596B56__INCLUDED_)
