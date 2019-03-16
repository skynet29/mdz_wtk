// MdzTreeNode.cpp: implementation of the MdzTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTreeNode.h"
#include "MdzTreeCtrl.h"
#include "MdzMenu.h"

#include "MdzStdDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzTreeNode::MdzTreeNode(LPSTR strText)
{
	MEMBER_SET(strText);

	lpParent = NULL;
	hTreeItem = NULL;
	lpTreeCtrl = NULL;
	//lpCtxMenu = NULL;
	bDroppable = TRUE;
}

MdzTreeNode::~MdzTreeNode()
{
	/*
	MdzStdDialog::ShowMessageDialog(MdzString::Format("%s:%d",
		(LPSTR)GetText(), childs.GetCount()));
	childs.RemoveAll(TRUE);
	*/
	for(int i = 0; i < (int)childs.GetCount(); i++)
		delete (MdzTreeNode*)childs.GetAt(i);
}

void MdzTreeNode::Create(MdzTreeCtrl *lpTreeCtrl, MdzTreeNode* lpParent, HTREEITEM hInsertAfter)
{
	MEMBER_SET(lpTreeCtrl);
	MEMBER_SET(lpParent);

	TV_INSERTSTRUCT tvins;
	TV_ITEM& tvi = tvins.item;

	tvins.hParent = (lpParent) ? lpParent->hTreeItem : NULL;
	tvins.hInsertAfter = hInsertAfter;

	tvi.mask = TVIF_TEXT | TVIF_PARAM;
	tvi.pszText = strText;
	tvi.cchTextMax = strText.GetLength();
	tvi.lParam = (LPARAM) this;

	if (bitmap.GetHandle())
	{
		tvi.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvi.iImage = tvi.iSelectedImage = lpTreeCtrl->AddBitmap(bitmap);
	}


	hTreeItem = TreeView_InsertItem(lpTreeCtrl->GetHandle(), &tvins);

	for (UINT i = 0; i < childs.GetCount(); i++)
		((MdzTreeNode*)childs.GetAt(i))->Create(lpTreeCtrl, this);

	OnCreate();
}

void MdzTreeNode::Add(MdzTreeNode *lpNode)
{
	childs.Add(lpNode);

	if (lpTreeCtrl)
		lpNode->Create(lpTreeCtrl, this);
}



MdzString MdzTreeNode::GetText()
{
	return strText;
}

void MdzTreeNode::Remove()
{
	if (lpTreeCtrl)
		SendMessage(lpTreeCtrl->GetHandle(), TVM_DELETEITEM, 0, (LPARAM) hTreeItem);
	if (lpParent)
		lpParent->OnChildRemoved(this);
	//delete this;
}

MdzTreeNode* MdzTreeNode::GetParent()
{
	return lpParent;
}

BOOL MdzTreeNode::IsLeaf()
{
	return (childs.GetCount() == 0);
}

void MdzTreeNode::SetExpanded(BOOL bIsExpanded)
{
	if (lpTreeCtrl)
		TreeView_Expand(lpTreeCtrl->GetHandle(), hTreeItem,
			(bIsExpanded) ? TVE_EXPAND : TVE_COLLAPSE);

}

//DEL void MdzTreeNode::OnRightClick(UINT x, UINT y)
//DEL {
//DEL 	if (lpCtxMenu)
//DEL 		lpCtxMenu->Track(lpTreeCtrl, x, y);
//DEL }

//DEL void MdzTreeNode::SetCtxMenu(MdzMenu &menu)
//DEL {
//DEL 	lpCtxMenu = &menu;
//DEL }

//DEL void MdzTreeNode::OnSelect()
//DEL {
//DEL 
//DEL }

void MdzTreeNode::OnCreate()
{

}

void MdzTreeNode::OnChildRemoved(MdzTreeNode *pChild)
{
	childs.Remove(pChild, FALSE);
}

MdzTreeNode* MdzTreeNode::GetNext(MdzTreeNode *pChild)
{
	UINT iIdx = childs.Find(pChild);
	if (iIdx + 1  < childs.GetCount())
		return (MdzTreeNode*) childs.GetAt(iIdx + 1);

	if (lpParent)
		return lpParent->GetNext(this);

	return NULL;

}

MdzTreeNode* MdzTreeNode::GetNext()
{
	if (childs.GetCount())
		return (MdzTreeNode*) childs.GetAt(0);

	if (lpParent)
		return lpParent->GetNext(this);

	return NULL;

}





UINT MdzTreeNode::GetChildCount()
{
	return childs.GetCount();
}

MdzTreeNode* MdzTreeNode::GetChildAt(UINT iIndex)
{
	return (MdzTreeNode*) childs.GetAt(iIndex);
}






MdzTreeNode::MdzTreeNode()
{
	lpParent = NULL;
	hTreeItem = NULL;
	lpTreeCtrl = NULL;
	//lpCtxMenu = NULL;
	bDroppable = FALSE;
}

UINT MdzTreeNode::GetPosition()
{
	UINT iPos = 0;
	MdzTreeNode* pNode = GetParent();
	while (pNode)
	{
		iPos++;
		pNode = pNode->GetParent();
	}
	return iPos;
}

//DEL void MdzTreeNode::AddHead(MdzTreeNode *lpNode)
//DEL {
//DEL 	childs.InsertAt(lpNode, 0);
//DEL 
//DEL 	if (lpTreeCtrl)
//DEL 		lpNode->Create(lpTreeCtrl, this, TVI_FIRST);
//DEL 
//DEL }

void MdzTreeNode::InsertAt(MdzTreeNode *pNode, UINT idx)
{
	childs.InsertAt(pNode, idx);
	if (lpTreeCtrl)
	{
		pNode->Create(lpTreeCtrl, this,
			(idx == 0) ? TVI_FIRST : GetChildAt(idx-1)->hTreeItem);
	}

}

void MdzTreeNode::SetBitmap(MdzBitmap bitmap)
{
	MEMBER_SET(bitmap);
	bitmap.MapColor(GetSysColor(COLOR_WINDOW));
}

UINT MdzTreeNode::GetChildPos()
{
	return GetParent()->childs.Find(this);
}

void MdzTreeNode::Select()
{
	if (lpTreeCtrl)
		TreeView_SelectItem(lpTreeCtrl->GetHandle(), hTreeItem);

}

void MdzTreeNode::OnDropAccept(MdzTreeNode *pDroppedNode)
{
}

BOOL MdzTreeNode::OnDropTest(MdzTreeNode *pNode)
{
	return FALSE;
}

BOOL MdzTreeNode::IsLastChild()
{
	return (GetChildPos() + 1 == GetParent()->GetChildCount());
}

void MdzTreeNode::SetText(LPSTR strText)
{
	MEMBER_SET(strText);

	if (hTreeItem)
	{
		TV_ITEM tvi;

		tvi.mask = TVIF_TEXT;
		tvi.pszText = strText;
		tvi.cchTextMax = strlen(strText);
		tvi.hItem = hTreeItem;
		TreeView_SetItem(lpTreeCtrl->GetHandle(), &tvi);
	}

}

void MdzTreeNode::SortChildren()
{
	TVSORTCB sort;

	sort.hParent = hTreeItem;
	sort.lParam = (LPARAM) this;
	sort.lpfnCompare = CompareFunc;

	TreeView_SortChildrenCB(lpTreeCtrl->GetHandle(),
		&sort, FALSE);

	childs.RemoveAll(FALSE);
	HTREEITEM hChild = TreeView_GetChild(lpTreeCtrl->GetHandle(), hTreeItem);
	while (hChild)
	{
		MdzTreeNode* pNode = lpTreeCtrl->GetNode(hChild);
		childs.Add(pNode);
		hChild = TreeView_GetNextSibling(lpTreeCtrl->GetHandle(), hChild);
	}

}

int CALLBACK MdzTreeNode::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return ((MdzTreeNode*)lParamSort)->OnCompareChild((MdzTreeNode*)lParam1, (MdzTreeNode*)lParam2);

}

int MdzTreeNode::OnCompareChild(MdzTreeNode *pNode1, MdzTreeNode *pNode2)
{
	return pNode1->GetText().Compare(pNode2->GetText());

}

BOOL MdzTreeNode::IsEditable()
{
	return FALSE;
}

void MdzTreeNode::Rename()
{
	HWND hEdit = TreeView_EditLabel(lpTreeCtrl->GetHandle(), hTreeItem);
}

void MdzTreeNode::OnTextUpdated(LPSTR strNewText)
{
	SetText(strNewText);
}

//DEL BOOL MdzTreeNode::IsInstanceOf(LPSTR strClass)
//DEL {
//DEL 	return (GetClass().Equals(strClass)) ? TRUE : MdzObject::IsInstanceOf(strClass);
//DEL }

BOOL MdzTreeNode::MoveUp()
{
	UINT iPos = GetChildPos();
	MdzTreeNode* parent = GetParent();
	if (iPos > 0)
	{
		Remove();
		parent->InsertAt(this, iPos-1);	
		Select();
		return TRUE;
	}
	return FALSE;
}

BOOL MdzTreeNode::MoveDown()
{
	UINT iPos = GetChildPos();
	MdzTreeNode* parent = GetParent();
	if (iPos < parent->GetChildCount()-1)
	{
		Remove();
		parent->InsertAt(this, iPos+1);	
		Select();
		return TRUE;
	}
	return FALSE;
}

BOOL MdzTreeNode::IsFirstChild()
{
	return (GetChildPos() == 0);
}
