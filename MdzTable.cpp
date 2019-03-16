// MdzTable.cpp: implementation of the MdzTable class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTable.h"
#include "MdzWindow.h"
#include "MdzTableItem.h"
#include "MdzRect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT MdzTable::K_CENTER	= LVCFMT_CENTER;
const UINT MdzTable::K_RIGHT	= LVCFMT_RIGHT;
const UINT MdzTable::K_LEFT		= LVCFMT_LEFT;

class MdzColumn : public MdzObject
{
public:
	MdzColumn(LPSTR strColName, int iColWidth, int iAlignment)
	{
		MEMBER_SET(strColName);
		MEMBER_SET(iColWidth);
		MEMBER_SET(iAlignment);

	}

	MdzString strColName;
	int iColWidth;
	int iAlignment;
};

MdzTable::MdzTable()
{
	lpWnd->lpClassName = WC_LISTVIEW;
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED;
	lpWnd->dwStyleEx = WS_EX_CLIENTEDGE;
	lpWnd->OnDrawItem = MDZ_CBK3(MdzTable, OnDrawItem);

	iIndex = 0;
}

MdzTable::~MdzTable()
{
	columns.RemoveAll(TRUE);
}

void MdzTable::AddColumn(LPSTR strColName, int iColWidth, int iAlignment)
{
	if (GetHandle())
	{
		LVCOLUMN col;

		col.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
		col.fmt = iAlignment;
		col.cx = iColWidth;
		col.pszText = strColName;
		col.cchTextMax = strlen(strColName);

		ListView_InsertColumn(GetHandle(), iIndex++, (LPARAM) &col);
	}
	else
		columns.Add(new MdzColumn(strColName, iColWidth, iAlignment));
}

void MdzTable::AddItem(MdzTableItem *lpItem)
{
	if (GetHandle())
	{
		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_PARAM;
		item.pszText = LPSTR_TEXTCALLBACK;
		item.lParam = (LPARAM) lpItem;
		item.iItem = GetItemCount();
		item.iSubItem = 0;

		ListView_InsertItem(GetHandle(), &item);
	}
	else
		items.Add(lpItem);
}

//DEL void MdzTable::OnGetDispInfo(LPNMHDR lpHeader)
//DEL {
//DEL 	LVITEM& item = ((NMLVDISPINFO*) lpHeader)->item;
//DEL 	MdzTableItem *lpItem = (MdzTableItem *) item.lParam;
//DEL 	MdzString str = lpItem->GetColumnData(item.iSubItem);
//DEL 	strcpy(item.pszText, str);
//DEL }

void MdzTable::Create()
{
	MdzCtrl::Create();
	ListView_SetExtendedListViewStyleEx(GetHandle(), LVS_EX_FULLROWSELECT,
		LVS_EX_FULLROWSELECT);

	UINT i;
	for(i = 0; i < columns.GetCount(); i++)
		AddColumn(columns[i].strColName, columns[i].iColWidth, columns[i].iAlignment);
	
	columns.RemoveAll(TRUE);

	for(i = 0; i < items.GetCount(); i++)
		AddItem(&items[i]);

	items.RemoveAll(FALSE);

}

int MdzTable::GetItemCount()
{
	if (!GetHandle())
		return items.GetCount();

	return ListView_GetItemCount(GetHandle());
}

void MdzTable::RemoveItemAt(int iIndex, BOOL bAutoDelete)
{
	if (bAutoDelete)
	{
		MdzTableItem* lpItem = GetItemAt(iIndex);
		if (lpItem)
		{
			if (!GetHandle())
				items.Remove(lpItem, FALSE);
			delete lpItem;
		}
	}

	ListView_DeleteItem(GetHandle(), iIndex);

}

int MdzTable::GetSelIndex()
{
	return ListView_GetSelectionMark(GetHandle());
}

MdzTableItem* MdzTable::GetItemAt(int iIndex)
{
	if (!GetHandle())
		return &items[iIndex];

	LVITEM item;
	item.iItem = iIndex;
	item.mask = LVIF_PARAM;

	if (ListView_GetItem(GetHandle(), &item))
	{
		return (MdzTableItem*) item.lParam;
	}
	
	return NULL;
}

MdzTableItem* MdzTable::GetSelItem()
{
	return GetItemAt(GetSelIndex());
}

void MdzTable::RemoveAllItems(BOOL bAutoDelete)
{
	if (bAutoDelete)
	{
		int iCount = GetItemCount();
		for (int i = 0; i < iCount; i++)
		{
			MdzTableItem* pItem = GetItemAt(i);
			delete pItem;
		}
	}
	items.RemoveAll(FALSE);
	ListView_DeleteAllItems(GetHandle());
}

void MdzTable::OnDrawItem(MdzEvent& evt)
{
	LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT) evt.lParam;

	RECT rc = lpDrawItem->rcItem;
	MdzTableItem* lpItem = (MdzTableItem*) lpDrawItem->itemData;
	HDC hdc = lpDrawItem->hDC;
	
	LVITEM item;
	item.mask = LVIF_STATE;
	item.stateMask = 0xFFFF;
	item.iItem = lpDrawItem->itemID;
	ListView_GetItem(GetHandle(), &item);


	for (int i = 0; i < iIndex; i++)
	{
		LVCOLUMN col;
		col.mask = LVCF_FMT | LVCF_WIDTH;
		ListView_GetColumn(GetHandle(), i, &col);

		rc.right = rc.left + col.cx;
		MdzString str = lpItem->GetColumnData(i);
		HBRUSH hBrush = CreateSolidBrush(lpItem->GetBackColor(i));

		FillRect(hdc, &rc, hBrush);
		SetTextColor(hdc, lpItem->GetTextColor(i));

		int nJustify;

		switch(col.fmt & LVCFMT_JUSTIFYMASK)
		{
			case LVCFMT_RIGHT:	
				nJustify = DT_RIGHT;
				break;

			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			
			default:
				nJustify = DT_LEFT;
				break;
		}

		RECT rc1 = rc;
		InflateRect(&rc1, -1, 0);
		DrawText(hdc, str, str.GetLength(), &rc1, DT_SINGLELINE | DT_VCENTER | nJustify | DT_END_ELLIPSIS);
		DeleteObject(hBrush);
		rc.left = rc.right;
	}

	if (item.state & LVIS_SELECTED)
	{
		InvertRect(hdc, &lpDrawItem->rcItem);
	}
}
