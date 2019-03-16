// MdzSocket.h: interface for the MdzSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSOCKET_H__05B5874B_02F5_43E1_95BF_7F84E56C0462__INCLUDED_)
#define AFX_MDZSOCKET_H__05B5874B_02F5_43E1_95BF_7F84E56C0462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
//#include <winsock2.h>

class MdzEvent;
class MdzEventHandler;

class DllExport MdzSocket  
{
public:
	virtual void Close();
	static BOOL InitClass();
	MdzSocket();
	virtual ~MdzSocket();
protected:
	BOOL CatchEvent(long lEvent);
	BOOL Create();
	SOCKET sock;
	virtual void OnWSAEvent(MdzEvent& evt) {}
   MdzEventHandler* lpEvtHandler;

};

#endif // !defined(AFX_MDZSOCKET_H__05B5874B_02F5_43E1_95BF_7F84E56C0462__INCLUDED_)
