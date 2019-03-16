// MdzListBox.cpp: implementation of the MdzListBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzListBox.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzListBox::MdzListBox()
{
	lpWnd->lpClassName = "LISTBOX";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | LBS_NOTIFY |
		WS_VSCROLL | LBS_NOINTEGRALHEIGHT | LBS_USETABSTOPS ;
	lpWnd->dwStyleEx = WS_EX_CLIENTEDGE;
	lpWnd->OnCommand = MDZ_CBK3(MdzListBox, OnCommand);

	lpOnDblClk = NULL;
	lpOnSelChange = NULL;
	iSelIndex = -1;
}

MdzListBox::~MdzListBox()
{
	if (lpOnDblClk)
		delete lpOnDblClk;

	if (lpOnSelChange)
		delete lpOnSelChange;

	listData.RemoveAll(TRUE);
}

void MdzListBox::AddItem(LPSTR strItem, LPVOID pArg)
{
	if (GetHandle())
	{
		int index = lpWnd->SendMsg(LB_ADDSTRING, 0, (LPARAM) strItem);
		lpWnd->SendMsg(LB_SETITEMDATA, index, (LPARAM) pArg);
	}
	else
	{
		ListBoxData* pData = new ListBoxData;
		pData->strText = strItem;
		pData->pArg = pArg;
		listData.Add(pData);
	}
}

int MdzListBox::GetSelIndex()
{
	return (GetHandle()) ? lpWnd->SendMsg(LB_GETCURSEL) : iSelIndex;
}

void MdzListBox::SetOnSelChange(MdzCbk1 *lpFunc)
{
	if (lpOnSelChange)
		delete lpOnSelChange;
	lpOnSelChange = lpFunc;
}

void MdzListBox::SetOnDblClick(MdzCbk1 *lpFunc)
{
	if (lpOnDblClk)
		delete lpOnDblClk;
	lpOnDblClk = lpFunc;
}

void MdzListBox::SetSelIndex(int iSelIndex)
{
	MEMBER_SET(iSelIndex);

	lpWnd->SendMsg(LB_SETCURSEL, iSelIndex);
}

MdzString MdzListBox::GetItemAt(int iIndex)
{
	if (!GetHandle())
		return listData[iIndex].strText;

	MdzString ret;

	int length = lpWnd->SendMsg(LB_GETTEXTLEN, iIndex);
	if (length > 0)
	{
		length++;
		ret.Alloc(length);
		lpWnd->SendMsg(LB_GETTEXT, iIndex, (LPARAM) (LPSTR) ret);
	}
	return ret;
}

MdzString MdzListBox::GetSelItem()
{
	return GetItemAt(GetSelIndex());
}

void MdzListBox::RemoveAllItems()
{
	lpWnd->SendMsg(LB_RESETCONTENT);
	listData.RemoveAll(TRUE);
}

void MdzListBox::RemoveItemAt(int iIndex)
{
	if (GetHandle())
		lpWnd->SendMsg(LB_DELETESTRING, iIndex);
	else
		listData.RemoveAt(iIndex, TRUE);
}

void MdzListBox::SetSorted(BOOL bIsSorted)
{
	lpWnd->ModifyStyle(LBS_SORT, bIsSorted);
}

void MdzListBox::Create()
{
	MdzCtrl::Create();

	for (UINT i = 0; i < listData.GetCount(); i++)
		AddItem(listData[i].strText, listData[i].pArg);

	listData.RemoveAll(TRUE);

	SetSelIndex(iSelIndex);
}

void MdzListBox::OnCommand(MdzEvent& evt)
{
	if (HIWORD(evt.wParam) == LBN_SELCHANGE && lpOnSelChange)
		lpOnSelChange->Fire();

	if (HIWORD(evt.wParam) == LBN_DBLCLK)
		OnDblClick();

}

UINT MdzListBox::GetItemCount()
{
	return (!lpWnd->GetHandle()) ? listData.GetCount() : lpWnd->SendMsg(LB_GETCOUNT);
}

void MdzListBox::AddItems(MdzStrVector &vector)
{
	for(UINT i = 0; i < vector.GetCount(); i++)
		AddItem(vector[i]);

}

void MdzListBox::InsertItemAt(LPSTR strItem, UINT iIndex, LPVOID pArg)
{
	if (GetHandle())
	{
		lpWnd->SendMsg(LB_INSERTSTRING, iIndex, (LPARAM)strItem);
		lpWnd->SendMsg(LB_SETITEMDATA, iIndex, (LPARAM) pArg);
	}
	else
	{
		ListBoxData* pData = new ListBoxData;
		pData->strText = strItem;
		pData->pArg = pArg;
		listData.InsertAt(pData, iIndex);
	}
}

int MdzListBox::FindItem(LPSTR strItem)
{
	if (GetHandle())
		return lpWnd->SendMsg(LB_FINDSTRING, -1, (LPARAM)strItem);

	for(UINT i = 0; i < listData.GetCount(); i++)
	{
		if (listData[i].strText.Equals(strItem))
			return i;
	}

	return -1;
}

void MdzListBox::SetMultiSelection(BOOL bIsMultiSel)
{
	lpWnd->ModifyStyle(LBS_MULTIPLESEL, bIsMultiSel);

}

BOOL MdzListBox::IsItemSelected(UINT iIndex)
{
	return (lpWnd->SendMsg(LB_GETSEL, iIndex) > 0);
}

void MdzListBox::SelectAll(BOOL bIsSelected)
{
	lpWnd->SendMsg(LB_SETSEL, bIsSelected, -1);

}

LPVOID MdzListBox::GetDataAt(int iIndex)
{
	if (GetHandle())	
		return (LPVOID)lpWnd->SendMsg(LB_GETITEMDATA, iIndex);
	else
		return listData[iIndex].pArg;
}

void MdzListBox::SetSelItem(LPSTR strItem)
{
	SetSelIndex(FindItem(strItem));
}

void MdzListBox::OnDblClick()
{
	if (lpOnDblClk)
		lpOnDblClk->Fire();
}
