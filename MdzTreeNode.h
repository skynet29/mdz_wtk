// MdzTreeNode.h: interface for the MdzTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTREENODE_H__5B5D62C4_9AB3_4AF8_8BA9_03EE98E0464D__INCLUDED_)
#define AFX_MDZTREENODE_H__5B5D62C4_9AB3_4AF8_8BA9_03EE98E0464D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzVector.h"
#include "MdzString.h"
#include "MdzBitmap.h"
#include "MdzObject.h"

class MdzTreeCtrl;
class MdzMenu;


class DllExport MdzTreeNode : public MdzObject
{
public:
	BOOL IsFirstChild();
	BOOL MoveDown();
	BOOL MoveUp();
	DEFINE_STD_METHODS(MdzTreeNode, MdzObject)
	void Rename();
	void SortChildren();
	void SetText(LPSTR strText);
	MdzTreeNode();
	MdzTreeNode(LPSTR strText);

	BOOL
	IsLastChild();

	void
	Select();
	
	UINT
	GetChildPos();
	
	void
	SetBitmap(MdzBitmap bitmap);
	
	void
	InsertAt(MdzTreeNode* pNode, UINT idx);
	
	
	UINT
	GetPosition();
	
	
	
	
	MdzTreeNode*
	GetChildAt(UINT iIndex);
	
	UINT
	GetChildCount();
	
	MdzTreeNode*
	GetNext();
	
	
	MdzString
	GetText();
	
	MdzTreeNode*
	GetParent();
	
	BOOL
	IsLeaf();
	
	void
	SetExpanded(BOOL bIsExpanded);
	
	void
	Add(MdzTreeNode* lpNode);
	
	void
	Remove();

	MdzTreeCtrl* GetTreeCtrl() {return lpTreeCtrl;}

	virtual ~MdzTreeNode();
private:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	MdzTreeNode* GetNext(MdzTreeNode* pChild);
	void Create(MdzTreeCtrl* lpTreeCtrl, MdzTreeNode* lpParent, HTREEITEM hInsertAfter = TVI_LAST);
	MdzString strText;
	MdzVector childs;
	HTREEITEM hTreeItem;
	MdzTreeNode* lpParent;
	MdzTreeCtrl* lpTreeCtrl;
	//MdzMenu* lpCtxMenu;
	MdzBitmap bitmap;

	friend class MdzTreeCtrl;
protected:
	virtual void OnTextUpdated(LPSTR strNewText);
	virtual BOOL IsEditable();
	virtual int OnCompareChild(MdzTreeNode *pNode1, MdzTreeNode *pNode2);
	virtual BOOL OnDropTest(MdzTreeNode* pNode);
	virtual void OnDropAccept(MdzTreeNode* pDroppedNode);

	BOOL bDroppable;
	virtual void OnChildRemoved(MdzTreeNode* pChild);
	virtual void OnCreate();
};

#endif // !defined(AFX_MDZTREENODE_H__5B5D62C4_9AB3_4AF8_8BA9_03EE98E0464D__INCLUDED_)
