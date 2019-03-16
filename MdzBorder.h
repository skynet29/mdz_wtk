// MdzBorder.h: interface for the MdzBorder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBORDER_H__01C40609_21F3_49DD_B570_50F9605D8447__INCLUDED_)
#define AFX_MDZBORDER_H__01C40609_21F3_49DD_B570_50F9605D8447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"

class MdzBorder : public MdzCtrl  
{
public:
	void SetTitle(LPSTR strTitle);
	MdzBorder();
	virtual ~MdzBorder();

};

#endif // !defined(AFX_MDZBORDER_H__01C40609_21F3_49DD_B570_50F9605D8447__INCLUDED_)
