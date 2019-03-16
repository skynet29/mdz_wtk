// MdzListBox.h: interface for the MdzListBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZLISTBOX_H__EC686F93_08BF_485E_9BC5_8C2C09E9A523__INCLUDED_)
#define AFX_MDZLISTBOX_H__EC686F93_08BF_485E_9BC5_8C2C09E9A523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"
#include "MdzString.h"	// Added by ClassView
#include "MdzVector.h"

class MdzEvent;

class DllExport MdzListBox : public MdzCtrl  
{
public:
	void SetSelItem(LPSTR strItem);
	LPVOID GetDataAt(int iIndex);
	void SelectAll(BOOL bIsSelected);
	BOOL IsItemSelected(UINT iIndex);
	void SetMultiSelection(BOOL bIsMultiSel);
	int FindItem(LPSTR strItem);
	void InsertItemAt(LPSTR strItem, UINT iIndex, LPVOID pArg = NULL);
	void AddItems(MdzStrVector &vector);
	MdzListBox();

	UINT
	GetItemCount();

	MdzString
	GetSelItem();
	
	MdzString
	GetItemAt(int iIndex);
	
	int
	GetSelIndex();

	void
	SetSorted(BOOL bIsSorted);
	
	void
	SetSelIndex(int iIndex);
	
	void
	SetOnDblClick(MdzCbk1* lpFunc);
	
	void
	SetOnSelChange(MdzCbk1* lpFunc);

	void
	AddItem(LPSTR strItem, LPVOID pArg = NULL);
	
	void
	RemoveItemAt(int iIndex);
	
	void
	RemoveAllItems();

	virtual ~MdzListBox();
	
	virtual void
	Create();
private:
	class ListBoxData : public MdzObject
	{
	public:
		MdzString strText;
		LPVOID pArg;
	};

	void OnCommand(MdzEvent& evt);
	MdzVectorT<ListBoxData> listData;
	int iSelIndex;
	MdzCbk1* lpOnDblClk;
	MdzCbk1* lpOnSelChange;

protected:
	virtual void OnDblClick();
};

#endif // !defined(AFX_MDZLISTBOX_H__EC686F93_08BF_485E_9BC5_8C2C09E9A523__INCLUDED_)
