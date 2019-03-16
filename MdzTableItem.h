// MdzTableItem.h: interface for the MdzTableItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTABLEITEM_H__4382FFB8_A81F_4B18_A6B5_45EC1C7D3609__INCLUDED_)
#define AFX_MDZTABLEITEM_H__4382FFB8_A81F_4B18_A6B5_45EC1C7D3609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzString.h"
#include "MdzObject.h"

class DllExport MdzTableItem : public MdzObject 
{
public:
	DEFINE_STD_METHODS(MdzTableItem, MdzObject)

	MdzTableItem();

	virtual ~MdzTableItem();

	virtual COLORREF
	GetTextColor(int iNumCol);
	
	virtual COLORREF
	GetBackColor(int iNumCol);
	
	virtual MdzString
	GetColumnData(int iNumCol) = 0;

};

#endif // !defined(AFX_MDZTABLEITEM_H__4382FFB8_A81F_4B18_A6B5_45EC1C7D3609__INCLUDED_)
