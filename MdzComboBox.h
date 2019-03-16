// MdzComboBox.h: interface for the MdzComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCOMBOBOX_H__0A0E0A43_7A7C_47CD_B651_495FC23F945B__INCLUDED_)
#define AFX_MDZCOMBOBOX_H__0A0E0A43_7A7C_47CD_B651_495FC23F945B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"
#include "MdzCbk1.h"
#include "MdzVector.h"

class MdzEvent;

class DllExport MdzComboBox : public MdzCtrl  
{
public:
	BOOL SetSelItem(LPSTR strItem);
	void SetOnDropDown(MdzCbk1* lpFunc);
	MdzComboBox();

	void
	AddItem(LPSTR strItem, LPVOID pArg = NULL);

	void
	AddItems(MdzStrVector& vector);

	void
	RemoveAllItems();
	
	void
	SetOnSelChange(MdzCbk1* lpFunc);

	void
	SetSelIndex(int iIndex);

	MdzString
	GetSelItem();

	MdzString
	GetItemAt(int iIndex);

	int
	GetSelIndex();

	UINT
	GetItemCount();

	LPVOID GetDataAt(int iIndex);

	virtual ~MdzComboBox();
	
	virtual void
	Create();
private:
	class ComboBoxData : public MdzObject
	{
	public:
		MdzString strText;
		LPVOID pArg;
	};	
	MdzVectorT<ComboBoxData> listData;
	
	void OnCommand(MdzEvent& evt);
	//MdzStrVector strList;
	int	iSelIndex;
	MdzCbk1* lpOnSelChange;
	MdzCbk1* lpOnDropDown;

protected:
	virtual void OnSelChange();
};

#endif // !defined(AFX_MDZCOMBOBOX_H__0A0E0A43_7A7C_47CD_B651_495FC23F945B__INCLUDED_)
