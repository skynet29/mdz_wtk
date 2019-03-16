// MdzTreeCtrl.h: interface for the MdzTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTREECTRL_H__D4378BB2_C9FC_42F3_9DB7_E5AECC8DB364__INCLUDED_)
#define AFX_MDZTREECTRL_H__D4378BB2_C9FC_42F3_9DB7_E5AECC8DB364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzBitmap.h"
#include "MdzVector.h"

class MdzTreeNode;
class MdzEvent;
class MdzCbk2;
class MdzCbk1;

class DllExport MdzTreeCtrl : public MdzCtrl  
{
public:
	MdzTreeCtrl();

	virtual ~MdzTreeCtrl();

	MdzTreeNode*
	GetNodeAt(int x, int y);
	
	MdzTreeNode*
	GetSelNode();
	
	MdzTreeNode*
	GetRootNode();

	void
	SetOnRightClick(MdzCbk2* lpFunc);

	void
	SetOnSelChange(MdzCbk1* lpFunc);
	
	void
	SetRootNode(MdzTreeNode* lpRootNode);

	virtual void
	Create();
private:
	void OnEndLabelEdit(LPNMTVDISPINFO ptvdi);
	BOOL OnBeginLabelEdit(LPNMTVDISPINFO ptvdi);
	void OnSelChange(LPNMTREEVIEW lpnmtv);
	void OnRightClick();
	BOOL OnBeginDrag(LPNMTREEVIEW lpnmtv);
	MdzTreeNode* GetNode(HTREEITEM hItem);
	void OnLeftButtonUp(int x, int y);
	void OnMouseMove(int x, int y);
	UINT AddBitmap(MdzBitmap bitmap);
	void OnNotify(MdzEvent& evt);
	MdzTreeNode* lpRootNode;
	MdzTreeNode* lpSelNode;
	MdzTreeNode* pDroppedNode;
	MdzCbk1* lpOnSelChange;
	MdzCbk2* lpOnRightClick;
	HIMAGELIST hImageList;
	MdzVector bmpList;
	friend class MdzTreeNode;
};

#endif // !defined(AFX_MDZTREECTRL_H__D4378BB2_C9FC_42F3_9DB7_E5AECC8DB364__INCLUDED_)
