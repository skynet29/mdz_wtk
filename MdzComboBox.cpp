// MdzComboBox.cpp: implementation of the MdzComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzComboBox.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzComboBox::MdzComboBox()
{
	lpWnd->lpClassName = "COMBOBOX";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL;
	lpWnd->OnCommand = MDZ_CBK3(MdzComboBox, OnCommand);

	iSelIndex = -1;
	lpOnSelChange = NULL;
	lpOnDropDown = NULL;
}

MdzComboBox::~MdzComboBox()
{
	if (lpOnSelChange)
		delete lpOnSelChange;
}

void MdzComboBox::AddItem(LPSTR strItem, LPVOID pArg)
{
	if (!GetHandle())
	{
		ComboBoxData* pData = new ComboBoxData;
		pData->strText = strItem;
		pData->pArg = pArg;
		listData.Add(pData);
	}
	else
	{
		int idx = lpWnd->SendMsg(CB_ADDSTRING, 0, (LPARAM) strItem);
		lpWnd->SendMsg(CB_SETITEMDATA, idx, (LPARAM) pArg);
	}
}

int MdzComboBox::GetSelIndex()
{
	return (lpWnd->GetHandle()) ? lpWnd->SendMsg(CB_GETCURSEL) : iSelIndex;
}

MdzString MdzComboBox::GetItemAt(int index)
{
	if (!GetHandle())
		return listData[index].strText;

	MdzString ret;

	int length = lpWnd->SendMsg(CB_GETLBTEXTLEN, index);
	if (length > 0)
	{
		length++;
		ret.Alloc(length);
		lpWnd->SendMsg(CB_GETLBTEXT, index, (LPARAM) (LPSTR) ret);
	}
	return ret;
}

MdzString MdzComboBox::GetSelItem()
{
	return GetItemAt(GetSelIndex());
}

void MdzComboBox::SetSelIndex(int iSelIndex)
{
	MEMBER_SET(iSelIndex);

	lpWnd->SendMsg(CB_SETCURSEL, iSelIndex);
}

void MdzComboBox::SetOnSelChange(MdzCbk1 *lpFunc)
{
	if (lpOnSelChange)
		delete lpOnSelChange;
	lpOnSelChange = lpFunc;
}

void MdzComboBox::RemoveAllItems()
{
	lpWnd->SendMsg(CB_RESETCONTENT);
	listData.RemoveAll(TRUE);
}

void MdzComboBox::Create()
{
	MdzCtrl::Create();

	for (UINT i = 0; i < listData.GetCount(); i++)
		AddItem(listData[i].strText, listData[i].pArg);

	listData.RemoveAll(TRUE);

	SetSelIndex(iSelIndex);
}



void MdzComboBox::OnCommand(MdzEvent& evt)
{
	if (HIWORD(evt.wParam) == CBN_SELCHANGE)
		OnSelChange();

	if (HIWORD(evt.wParam) == CBN_DROPDOWN && lpOnDropDown)
		lpOnDropDown->Fire();
}

UINT MdzComboBox::GetItemCount()
{
	return (GetHandle()) ? lpWnd->SendMsg(CB_GETCOUNT) : listData.GetCount();
}

void MdzComboBox::OnSelChange()
{
	if (lpOnSelChange)
		lpOnSelChange->Fire();

}

void MdzComboBox::AddItems(MdzStrVector &vector)
{
	for(UINT i = 0; i < vector.GetCount(); i++)
		AddItem(vector[i]);
}

void MdzComboBox::SetOnDropDown(MdzCbk1 *lpFunc)
{
	if (lpOnDropDown)
		delete lpOnDropDown;
	lpOnDropDown = lpFunc;
}

BOOL MdzComboBox::SetSelItem(LPSTR strItem)
{
	for(int i = 0; i < (int)GetItemCount(); i++)
	{
		if (GetItemAt(i).Equals(strItem))
		{
			SetSelIndex(i);
			return TRUE;
		}
	}

	return FALSE;
}

LPVOID MdzComboBox::GetDataAt(int iIndex)
{
	if (GetHandle())	
		return (LPVOID)lpWnd->SendMsg(CB_GETITEMDATA, iIndex);
	else
		return listData[iIndex].pArg;

}
