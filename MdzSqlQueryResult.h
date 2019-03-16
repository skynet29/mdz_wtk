// MdzSqlQueryResult.h: interface for the MdzSqlQueryResult class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSQLQUERYRESULT_H__BFDD442B_0B4C_4E16_ACEC_858B5C574987__INCLUDED_)
#define AFX_MDZSQLQUERYRESULT_H__BFDD442B_0B4C_4E16_ACEC_858B5C574987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include <sql.h>
#include <sqlext.h>
#include "MdzString.h"	// Added by ClassView

class DllExport MdzSqlQueryResult  
{
public:

	MdzSqlQueryResult();

	int
	GetType(int iColIdx);

	int
	GetColumnIdxFromName(LPSTR strName);
	
	float
	GetFloat(int iColIdx);
	
	MdzString
	GetColumnName(int iColIdx);
	
	int
	GetInteger(int iColIdx);
	
	MdzString
	GetString(int iColIdx);
	
	BOOL
	GetNext();
	
	int
	GetNbColumn();

	static MdzString
	ConvertToSqlFloat(float val);

	virtual ~MdzSqlQueryResult();
private:
	void Attach(SQLHSTMT hstmt);
	SQLHSTMT hstmt;

	friend class MdzOdbcDriver;
};

#endif // !defined(AFX_MDZSQLQUERYRESULT_H__BFDD442B_0B4C_4E16_ACEC_858B5C574987__INCLUDED_)
