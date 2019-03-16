// MdzTreeCtrl.cpp: implementation of the MdzTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTreeCtrl.h"
#include "MdzWindow.h"
#include "MdzTreeNode.h"
#include "MdzSystem.h"

class MdzTreeItem : public MdzObject
{
public:
	MdzBitmap bitmap;
	UINT iIndex;
	MdzTreeItem(MdzBitmap bitmap, UINT iIndex)
	{
		MEMBER_SET(bitmap);
		MEMBER_SET(iIndex);
	}

};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzTreeCtrl::MdzTreeCtrl()
{
	lpWnd->lpClassName = WC_TREEVIEW;
	lpWnd->dwStyleEx = WS_EX_CLIENTEDGE;
	lpWnd->dwStyle = WS_VISIBLE | WS_CHILD |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		TVS_SHOWSELALWAYS | TVS_EDITLABELS;

	lpWnd->OnNotify = MDZ_CBK3(MdzTreeCtrl, OnNotify);
	lpWnd->OnMouseMove = MDZ_CBK2(MdzTreeCtrl, OnMouseMove);
	lpWnd->OnLeftButtonUp = MDZ_CBK2(MdzTreeCtrl, OnLeftButtonUp);

	lpRootNode = NULL;
	lpSelNode = NULL;
	lpOnSelChange = NULL;
	lpOnRightClick = NULL;
	hImageList = NULL;
	pDroppedNode = NULL;
}

MdzTreeCtrl::~MdzTreeCtrl()
{
	if (lpRootNode)
		delete lpRootNode;

	if (lpOnSelChange)
		delete lpOnSelChange;

	if (lpOnRightClick)
		delete lpOnRightClick;

	bmpList.RemoveAll(TRUE);
}

void MdzTreeCtrl::Create()
{
	MdzCtrl::Create();

	if (lpRootNode)
		lpRootNode->Create(this, NULL);
}

void MdzTreeCtrl::SetRootNode(MdzTreeNode *p_lpRootNode)
{
	if (lpRootNode)
	{
		lpRootNode->Remove();
		delete lpRootNode;
	}

	lpRootNode = p_lpRootNode;

	if (GetHandle() && lpRootNode)
		lpRootNode->Create(this, NULL);
}

MdzTreeNode* MdzTreeCtrl::GetSelNode()
{
	return lpSelNode;
}

void MdzTreeCtrl::OnNotify(MdzEvent &evt)
{
	LPNMHDR lpHeader = (LPNMHDR) evt.lParam;

	switch (lpHeader->code)
	{

	case TVN_SELCHANGED:
		OnSelChange((LPNMTREEVIEW) evt.lParam);
		break;


	case NM_RCLICK:
		OnRightClick();
		break;

	case TVN_BEGINDRAG:
		evt.lResult = OnBeginDrag((LPNMTREEVIEW) evt.lParam);
		break;

	case TVN_BEGINLABELEDIT: 
		evt.lResult = !OnBeginLabelEdit((LPNMTVDISPINFO) evt.lParam);
		break;

	case TVN_ENDLABELEDIT: 
		OnEndLabelEdit((LPNMTVDISPINFO) evt.lParam);
		break;

	}
}

MdzTreeNode* MdzTreeCtrl::GetNodeAt(int x, int y)
{
	MdzTreeNode* lpNode = NULL;
	TVHITTESTINFO ht;
	ht.pt.x = x;
	ht.pt.y = y;

	TreeView_HitTest(GetHandle(), &ht);
	
	if (ht.hItem)
	{
		MdzRect rcItem;
		TreeView_GetItemRect(GetHandle(), ht.hItem, &rcItem, TRUE); 

		if (rcItem.Contains(x, y))
			lpNode = GetNode(ht.hItem);
	}
	return lpNode;
}





void MdzTreeCtrl::SetOnSelChange(MdzCbk1 *lpFunc)
{
	if (lpOnSelChange)
		delete lpOnSelChange;
	lpOnSelChange = lpFunc;
}

MdzTreeNode* MdzTreeCtrl::GetRootNode()
{
	return lpRootNode;
}

UINT MdzTreeCtrl::AddBitmap(MdzBitmap bitmap)
{
	for(UINT i = 0; i < bmpList.GetCount(); i++)
	{
		MdzTreeItem* pItem = (MdzTreeItem*) bmpList.GetAt(i);
		if (pItem->bitmap == bitmap)
			return pItem->iIndex;
	}

	if (!hImageList)
	{
		hImageList = ImageList_Create(16, 16, ILC_COLOR24, 1, 1);

		TreeView_SetImageList(GetHandle(), hImageList, TVSIL_NORMAL);
	}

	UINT iIndex = ImageList_Add(hImageList, bitmap.GetHandle(), NULL);
	bmpList.Add(new MdzTreeItem(bitmap, iIndex));

	return iIndex;

}

void MdzTreeCtrl::OnMouseMove(int x, int y)
{
 
	// Drag the item to the current position of the mouse pointer. 
	ImageList_DragMove(x, y); 

	MdzTreeNode* pNode = GetNodeAt(x, y);

	if (pNode && pNode->OnDropTest(pDroppedNode))
	{
		MdzSystem::HideCursor();
	}
	else
	{
		MdzSystem::ShowCursor();
		SetCursor(LoadCursor(NULL, IDC_NO));
	}

}

void MdzTreeCtrl::OnLeftButtonUp(int x, int y)
{
	ImageList_DragLeave(GetHandle());
	ImageList_EndDrag(); 
	TreeView_SelectDropTarget(GetHandle(), NULL);
	MdzSystem::ShowCursor();

	MdzTreeNode* pNode = GetNodeAt(x, y);
	if (pNode && pNode->OnDropTest(pDroppedNode))
		pNode->OnDropAccept(pDroppedNode);
	pDroppedNode = NULL;
}

MdzTreeNode* MdzTreeCtrl::GetNode(HTREEITEM hItem)
{
	TV_ITEM tvi;	
	tvi.mask = TVIF_PARAM;
	tvi.hItem = hItem;
	TreeView_GetItem(GetHandle(), &tvi);
	return (MdzTreeNode*) tvi.lParam;

}

BOOL MdzTreeCtrl::OnBeginDrag(LPNMTREEVIEW lpnmtv)
{
	MdzTreeNode* pNode = (MdzTreeNode*) lpnmtv->itemNew.lParam;

	if (!pNode->bDroppable)
		return FALSE;

	pDroppedNode = pNode;
	pNode->Select();

	// Tell the tree-view control to create an image to use 
	// for dragging. 
	HIMAGELIST himl = TreeView_CreateDragImage(GetHandle(), lpnmtv->itemNew.hItem); 
	IMAGEINFO ii;
	ImageList_GetImageInfo(himl, 0, &ii);

	// Get the bounding rectangle of the item being dragged. 
	MdzRect rcItem;
	TreeView_GetItemRect(GetHandle(), lpnmtv->itemNew.hItem, &rcItem, TRUE); 

	// Start the drag operation. 
	ImageList_BeginDrag(himl, 0, rcItem.Width()/2+16, rcItem.Height()/2); 
	ImageList_DragEnter(GetHandle(), lpnmtv->ptDrag.x, lpnmtv->ptDrag.y);

	// Hide the mouse pointer, and direct mouse input to the 
	// parent window. 
	//ShowCursor(FALSE); 
	TreeView_SelectDropTarget(GetHandle(), NULL);
	return TRUE;
}

void MdzTreeCtrl::OnRightClick()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(GetHandle(), &pt);
	if (lpOnRightClick)
		lpOnRightClick->Fire(pt.x, pt.y);

}

void MdzTreeCtrl::OnSelChange(LPNMTREEVIEW lpnmtv)
{
	TV_ITEM& tvi = lpnmtv->itemNew;

	if (tvi.state & TVIS_SELECTED)
	{
		MdzTreeNode* lpNode = (MdzTreeNode*) tvi.lParam;
		if (lpNode != lpSelNode)
		{
			lpSelNode = lpNode;
			if (lpOnSelChange)
				lpOnSelChange->Fire();
		}
	}

}

void MdzTreeCtrl::SetOnRightClick(MdzCbk2 *lpFunc)
{
	if (lpOnRightClick)
		delete lpOnRightClick;
	lpOnRightClick = lpFunc;
}

BOOL MdzTreeCtrl::OnBeginLabelEdit(LPNMTVDISPINFO ptvdi)
{
	MdzTreeNode* pNode = (MdzTreeNode*)ptvdi->item.lParam;
	return (pNode) ? pNode->IsEditable() : FALSE;
}

void MdzTreeCtrl::OnEndLabelEdit(LPNMTVDISPINFO ptvdi)
{
	LPSTR strText = ptvdi->item.pszText;
	if (strText != NULL)
	{
		MdzTreeNode* pNode = (MdzTreeNode*)ptvdi->item.lParam;
		if (pNode)
			pNode->OnTextUpdated(strText);
	}
}
