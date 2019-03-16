// MdzBounds.h: interface for the MdzBounds class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBOUNDS_H__6581892C_0D13_4ADF_A4B1_7B4729E10979__INCLUDED_)
#define AFX_MDZBOUNDS_H__6581892C_0D13_4ADF_A4B1_7B4729E10979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzRect.h"	// Added by ClassView


class DllExport MdzBounds 
{
public:
	MdzBounds();
	MdzBounds(MdzRect& rc);
	MdzBounds(int left, int top, int width, int height);

	operator MdzRect();




	int left;
	int top;
	int width;
	int height;

};

#endif // !defined(AFX_MDZBOUNDS_H__6581892C_0D13_4ADF_A4B1_7B4729E10979__INCLUDED_)
