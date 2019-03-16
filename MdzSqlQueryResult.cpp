// MdzSqlQueryResult.cpp: implementation of the MdzSqlQueryResult class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSqlQueryResult.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSqlQueryResult::MdzSqlQueryResult()
{
	hstmt = SQL_NULL_HSTMT;
}



MdzSqlQueryResult::~MdzSqlQueryResult()
{
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

int MdzSqlQueryResult::GetNbColumn()
{
	RETCODE retcode;
	short cbCols;
	retcode = SQLNumResultCols(hstmt, &cbCols);
	if (retcode != 0)
		return -1;
	
	return cbCols;

}

BOOL MdzSqlQueryResult::GetNext()
{
	RETCODE retcode;
	retcode = SQLFetch(hstmt);

	if (retcode != 0)
		return FALSE;

	return TRUE;
}



MdzString MdzSqlQueryResult::GetString(int iColIdx)
{
	RETCODE retcode;
	char buffer[1024];
	SDWORD cNull;

		
	retcode = SQLGetData(hstmt, (UWORD)(iColIdx),
						 SQL_C_DEFAULT,
						 buffer,
						 sizeof(buffer),
						 &cNull);

	switch (GetType(iColIdx))
	{
	case SQL_INTEGER:
		return MdzString::Format("%d", *((int*)buffer));

	case SQL_VARCHAR:
		return buffer;

	case SQL_NUMERIC:
		return MdzString::Format("%.2f", atof(buffer));
	}

	throw MdzString("MdzSqlQueryResult::GetString: SqlType not supported yet");
}

int MdzSqlQueryResult::GetInteger(int iColIdx)
{
	RETCODE retcode;
	char buffer[1024];
	SDWORD cNull;

		
	retcode = SQLGetData(hstmt, (UWORD)(iColIdx),
						 SQL_C_DEFAULT,
						 buffer,
						 sizeof(buffer),
						 &cNull);

	return *((int*)buffer);

}

MdzString MdzSqlQueryResult::GetColumnName(int iColIdx)
{
	RETCODE retcode;
	char        szColumnName[256];
	SWORD       fSqlType;
	UDWORD      precision;
	SWORD       scale;
	SWORD       fNullable;

	retcode = SQLDescribeCol(hstmt,
						   (UWORD)(iColIdx), (UCHAR*)szColumnName,
						   sizeof(szColumnName),
						   NULL,
						   &fSqlType, &precision, &scale, &fNullable);
	
	return MdzString(szColumnName);
}

float MdzSqlQueryResult::GetFloat(int iColIdx)
{
	RETCODE retcode;
	char buffer[1024];
	SDWORD cNull;

		
	retcode = SQLGetData(hstmt, (UWORD)(iColIdx),
						 SQL_C_DEFAULT,
						 buffer,
						 sizeof(buffer),
						 &cNull);

	return (float) atof(buffer);

}

int MdzSqlQueryResult::GetColumnIdxFromName(LPSTR strName)
{
	int nbCol = GetNbColumn();

	for (int i = 0; i < nbCol; i++)
	{
		MdzString ret = GetColumnName(i + 1);
		if (ret.Equals(strName))
			return i + 1;
	}
	return -1;
}

MdzString MdzSqlQueryResult::ConvertToSqlFloat(float val)
{
	MdzString str = MdzString::Format("%.2f", val);
	char* p = strchr((LPSTR) str, '.');
	if (p)
		*p = ',';
	return str;
}

int MdzSqlQueryResult::GetType(int iColIdx)
{
	RETCODE retcode;
	char        szColumnName[256];
	SWORD       fSqlType;
	UDWORD      precision;
	SWORD       scale;
	SWORD       fNullable;

	retcode = SQLDescribeCol(hstmt,
						   (UWORD)(iColIdx), (UCHAR*)szColumnName,
						   sizeof(szColumnName),
						   NULL,
						   &fSqlType, &precision, &scale, &fNullable);
	
	return fSqlType;
}

void MdzSqlQueryResult::Attach(SQLHSTMT hstmt1)
{
	if (hstmt != SQL_NULL_HSTMT)
			SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	
	hstmt = hstmt1;
}
