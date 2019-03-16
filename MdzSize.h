// MdzSize.h: interface for the MdzSize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSIZE_H__E7734DC7_40B3_4006_9E2A_899CE92AD93A__INCLUDED_)
#define AFX_MDZSIZE_H__E7734DC7_40B3_4006_9E2A_899CE92AD93A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"

class DllExport MdzSize : public tagSIZE  
{
public:
	MdzSize(int cx, int cy);
	MdzSize();
	virtual ~MdzSize();

};

#endif // !defined(AFX_MDZSIZE_H__E7734DC7_40B3_4006_9E2A_899CE92AD93A__INCLUDED_)
