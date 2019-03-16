// MdzOdbcDriver.h: interface for the MdzOdbcDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZODBCDRIVER_H__9B18200B_1D47_47F1_AB49_E1A3E316E5E3__INCLUDED_)
#define AFX_MDZODBCDRIVER_H__9B18200B_1D47_47F1_AB49_E1A3E316E5E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include "MdzString.h"

class MdzSqlQueryResult;

class DllExport MdzOdbcDriver  
{
public:
	MdzOdbcDriver();

	virtual ~MdzOdbcDriver();

	BOOL
	IsConnected();

	BOOL
	Connect(LPSTR strDbName, LPSTR strUserName, LPSTR strPassword);

	void
	Disconnect();
	
	MdzString
	ExecuteQuery(LPSTR strQuery, MdzSqlQueryResult& result);

private:
	SQLHENV      henv; 
	SQLHDBC      hdbc1;
	BOOL			 bIsConnected;
};

#endif // !defined(AFX_MDZODBCDRIVER_H__9B18200B_1D47_47F1_AB49_E1A3E316E5E3__INCLUDED_)
