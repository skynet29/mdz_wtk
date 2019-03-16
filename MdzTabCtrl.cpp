// MdzTabCtrl.cpp: implementation of the MdzTabCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTabCtrl.h"
#include "MdzWindow.h"
#include "MdzRect.h"

class MdzTabCtrlItem : public MdzObject
{
public:
	MdzString strCaption;
	MdzCtrl* lpCtrl;

	MdzTabCtrlItem(LPSTR strCaption, MdzCtrl* lpCtrl)
	{
		MEMBER_SET(strCaption);
		MEMBER_SET(lpCtrl);

	}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MdzTabCtrl::MdzTabCtrl()
{
	lpWnd->lpClassName = WC_TABCONTROL;
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	lpWnd->OnNotify = MDZ_CBK3(MdzTabCtrl, OnNotify);
	lpWnd->OnSize = MDZ_CBK2(MdzTabCtrl, OnSize);
	iIndex = 0;
}	

MdzTabCtrl::~MdzTabCtrl()
{
	tabs.RemoveAll(TRUE);
}

void MdzTabCtrl::AddTab(LPSTR strCaption, MdzCtrl &ctrl)
{
	ctrl.SetParent(this);
	tabs.Add(new MdzTabCtrlItem(strCaption, &ctrl));
}

void MdzTabCtrl::Create()
{
	MdzCtrl::Create();

	MdzRect rc;
	GetClientRect(GetHandle(), &rc);


	for (UINT i = 0; i < tabs.GetCount(); i++)
	{
		MdzTabCtrlItem* lpItem = (MdzTabCtrlItem*) tabs.GetAt(i);

		TC_ITEM item;
		item.mask = TCIF_TEXT;
		item.pszText = lpItem->strCaption;
		item.cchTextMax = strlen(item.pszText);
		TabCtrl_InsertItem(GetHandle(), i, &item);
		
		if (i == 0)
			TabCtrl_AdjustRect(GetHandle(), FALSE, &rc);

		MdzCtrl* pCtrl = lpItem->lpCtrl;
		pCtrl->SetBounds(MdzBounds(rc));
		pCtrl->SetVisible(i == iIndex);
		pCtrl->Create();
	}


}

void MdzTabCtrl::OnNotify(MdzEvent& evt)
{
	if (((LPNMHDR)evt.lParam)->code == TCN_SELCHANGE)
	{
		GetSelTab()->SetVisible(FALSE);
		iIndex = TabCtrl_GetCurSel(GetHandle());
		GetSelTab()->SetVisible(TRUE);
	}

}

MdzCtrl* MdzTabCtrl::GetSelTab()
{
	return (MdzCtrl*)((MdzTabCtrlItem*)tabs.GetAt(iIndex))->lpCtrl;
}

void MdzTabCtrl::OnSize(int width, int height)
{
	MdzRect rc;
	GetClientRect(GetHandle(), &rc);

	TabCtrl_AdjustRect(GetHandle(), FALSE, (LPARAM) &rc);

	for (UINT i = 0; i < tabs.GetCount(); i++)
	{
		MdzTabCtrlItem* lpItem = (MdzTabCtrlItem*) tabs.GetAt(i);

		MdzCtrl* pCtrl = lpItem->lpCtrl;
		pCtrl->SetBounds(MdzBounds(rc));
	}
}

UINT MdzTabCtrl::GetSelIndex()
{
	return iIndex;
}

void MdzTabCtrl::SetSelIndex(UINT iIndex)
{
	if (iIndex < tabs.GetCount())
	{
		GetSelTab()->SetVisible(FALSE);
		TabCtrl_SetCurSel(GetHandle(), iIndex);
		this->iIndex = iIndex;
		GetSelTab()->SetVisible(TRUE);
	}

}
