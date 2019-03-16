// MdzContainer.cpp: implementation of the MdzContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzContainer.h"
#include "MdzWindow.h"
#include "MdzDlgInput.h"
#include "MdzStdDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzContainer::MdzContainer()
{
	lpWnd->OnCreate = MDZ_CBK1(MdzContainer, OnCreate);
}

MdzContainer::~MdzContainer()
{
	for (UINT i = 0; i < childs.GetCount(); i++)
	{
		MdzCtrl* pChild = (MdzCtrl*)childs.GetAt(i);

		if (pChild->bAutoDelete)
			delete pChild;
	}
	childs.RemoveAll(FALSE);
}

void MdzContainer::Add(MdzCtrl &ctrl)
{
	ctrl.SetParent(this);
	childs.Add(&ctrl);
	//ctrl.SetBounds(curBounds);
}

void MdzContainer::OnCreate()
{
	for (UINT i = 0; i < childs.GetCount(); i++)
	{
		MdzCtrl* lpCtrl = (MdzCtrl*) childs.GetAt(i);
		lpCtrl->Create();
	}
}

void MdzContainer::Add(MdzCtrl &ctrl, MdzBounds &bounds)
{
	Add(ctrl);
	ctrl.SetBounds(bounds);
	//curBounds = bounds;
}

void MdzContainer::Pack(int xPad, int yPad)
{
	int right = 0;
	int bottom = 0;

	for (UINT i = 0 ; i < childs.GetCount(); i++)
	{ 
		MdzCtrl* pCtrl = (MdzCtrl*) childs.GetAt(i);
		MdzRect rc = pCtrl->GetBounds();
	
		right = max(right, rc.right);
		bottom = max(bottom, rc.bottom);
	}

	MdzRect rc(0, 0, right + xPad, bottom + yPad);
	lpWnd->AdjustWindowRect(rc);
	SetSize(rc.Width(), rc.Height());	
}





MdzRect MdzContainer::GetClientRect()
{
	MdzRect rc;
	::GetClientRect(GetHandle(), &rc);
	return rc;
}



void MdzContainer::Add(MdzCtrl &ctrl, MdzSize &size)
{
	Add(ctrl);
	ctrl.SetSize(size.cx, size.cy);
	
}
