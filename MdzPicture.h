// MdzPicture.h: interface for the MdzPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZPICTURE_H__B48CAF8E_EDB9_4319_AF01_E0E6267A6636__INCLUDED_)
#define AFX_MDZPICTURE_H__B48CAF8E_EDB9_4319_AF01_E0E6267A6636__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzBitmap.h"

class MdzGraphic;

class DllExport MdzPicture  : public MdzCtrl
{
public:
	void Clear();
	MdzPicture();

	void
	SetBorder(BOOL bHasBorder);
	
	void
	SetBitmap(MdzBitmap bitmap);

	virtual ~MdzPicture();

private:
	void OnPaint(MdzGraphic& graphic);
	MdzBitmap bitmap;
};

#endif // !defined(AFX_MDZPICTURE_H__B48CAF8E_EDB9_4319_AF01_E0E6267A6636__INCLUDED_)
