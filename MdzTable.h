// MdzTable.h: interface for the MdzTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTABLE_H__FC2A63F3_898E_44B8_B7E1_E9DDECB31BCB__INCLUDED_)
#define AFX_MDZTABLE_H__FC2A63F3_898E_44B8_B7E1_E9DDECB31BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzVector.h"

class MdzTableItem;
class MdzEvent;
class MdzColumn;

class DllExport MdzTable : public MdzCtrl  
{
public:
	static const UINT K_CENTER;
	static const UINT K_RIGHT;
	static const UINT K_LEFT;

	MdzTable();

	MdzTableItem*
	GetSelItem();
	
	MdzTableItem*
	GetItemAt(int iIndex);
	
	int
	GetItemCount();
	
	int
	GetSelIndex();

	void
	RemoveItemAt(int iIndex, BOOL bAutoDelete = TRUE);
	
	void
	RemoveAllItems(BOOL bAutoDelete = TRUE);
	
	void
	AddItem(MdzTableItem* lpItem);
	
	void
	AddColumn(LPSTR strColName, int iColWidth, int iAlignment = K_LEFT);

	virtual void
	Create();

	virtual ~MdzTable();
private:
	void OnDrawItem(MdzEvent& evt);
	int iIndex;
	MdzVectorT<MdzColumn> columns;
	MdzVectorT<MdzTableItem> items;

};

#endif // !defined(AFX_MDZTABLE_H__FC2A63F3_898E_44B8_B7E1_E9DDECB31BCB__INCLUDED_)
