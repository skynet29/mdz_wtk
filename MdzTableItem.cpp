// MdzTableItem.cpp: implementation of the MdzTableItem class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTableItem.h"
#include "MdzColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzTableItem::MdzTableItem()
{

}

MdzTableItem::~MdzTableItem()
{

}

COLORREF MdzTableItem::GetBackColor(int iNumCol)
{
	return MdzColor::K_WHITE;
}

COLORREF MdzTableItem::GetTextColor(int iNumCol)
{
	return MdzColor::K_BLACK;
}
