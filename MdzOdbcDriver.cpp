// MdzOdbcDriver.cpp: implementation of the MdzOdbcDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzOdbcDriver.h"
#include "MdzSqlQueryResult.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzOdbcDriver::MdzOdbcDriver()
{
	henv = SQL_NULL_HENV;
	hdbc1 = SQL_NULL_HDBC;
	bIsConnected = FALSE;
}

MdzOdbcDriver::~MdzOdbcDriver()
{
	Disconnect();
}

BOOL MdzOdbcDriver::Connect(LPSTR strDbName, LPSTR strUserName, LPSTR strPassword)
{
	RETCODE retcode;

	retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv);
	if (retcode != 0)
		return FALSE;

	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
					 (SQLPOINTER)SQL_OV_ODBC3,
					 SQL_IS_INTEGER);

	if (retcode != 0)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return FALSE;
	}

	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);

	if (retcode != 0)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return FALSE;
	}


	retcode = SQLConnect(hdbc1, 
				  (SQLCHAR*) strDbName, SQL_NTS,
				  (SQLCHAR*) strUserName, SQL_NTS,
				  (SQLCHAR*) strPassword, SQL_NTS);

	if (retcode != 0)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return FALSE;
	}

	bIsConnected = TRUE;

	return TRUE;
}

void MdzOdbcDriver::Disconnect()
{
	if (bIsConnected)
	{
		SQLDisconnect(hdbc1);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		bIsConnected = FALSE;
	}
}

MdzString MdzOdbcDriver::ExecuteQuery(LPSTR strQuery, MdzSqlQueryResult& result)
{
	if (!bIsConnected)
		return FALSE;

	RETCODE retcode;
	SQLHSTMT hstmt;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt);
	
	if (retcode != 0)
		return FALSE;

	retcode = SQLExecDirect(hstmt, (UCHAR*)strQuery, SQL_NTS);

	if (retcode != 0)
	{
		SQLCHAR Sqlstate[6];
		SQLCHAR       Msg[SQL_MAX_MESSAGE_LENGTH];
		SQLSMALLINT   MsgLen;

		SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, 1, Sqlstate,
			NULL, Msg, sizeof(Msg), &MsgLen);

		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
//		return MdzString((LPSTR) &Sqlstate[0]);
		return MdzString((char*)Msg);
	}
	
	result.Attach(hstmt);
	return MdzString();
}



BOOL MdzOdbcDriver::IsConnected()
{
	return bIsConnected;
}
