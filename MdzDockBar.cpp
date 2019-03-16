// MdzDockBar.cpp: implementation of the MdzDockBar class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDockBar.h"
#include "MdzWindow.h"
#include "MdzToolBar.h"
#include "MdzFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzDockBar::MdzDockBar()
{
	lpWnd->lpClassName = REBARCLASSNAME;
	lpWnd->dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS | RBS_AUTOSIZE |
		WS_CLIPCHILDREN | RBS_BANDBORDERS |RBS_VARHEIGHT |CCS_NODIVIDER; //| CCS_NOPARENTALIGN;
	lpWnd->OnNotify = MDZ_CBK3(MdzDockBar, OnNotify);
}

MdzDockBar::~MdzDockBar()
{
}

void MdzDockBar::Create()
{
	MdzCtrl::Create();

	REBARINFO rbi;
	rbi.cbSize = sizeof(REBARINFO);
	rbi.fMask  = 0;
	rbi.himl   = (HIMAGELIST)NULL;
	lpWnd->SendMsg(RB_SETBARINFO, 0, (LPARAM)&rbi);

	for (UINT i = 0; i < toolbarList.GetCount(); i++)
	{
		MdzToolBar* lpToolBar = (MdzToolBar*) toolbarList.GetAt(i);
		lpToolBar->Create();

		DWORD dwBtnSize = SendMessage(lpToolBar->GetHandle(), TB_GETBUTTONSIZE, 0, 0);

		REBARBANDINFO rbBand;
 
		rbBand.cbSize		= sizeof(REBARBANDINFO); 
		rbBand.fMask		= RBBIM_CHILD | RBBIM_ID | RBBIM_STYLE | RBBIM_CHILDSIZE | RBBIM_SIZE;
		rbBand.fStyle		= RBBS_GRIPPERALWAYS;
		rbBand.cyMinChild	= HIWORD(dwBtnSize) + 4;
		rbBand.cx			= lpToolBar->GetWidth() + 12;
		rbBand.cxMinChild	= 0;
		rbBand.hwndChild	= lpToolBar->GetHandle();
		rbBand.wID			= lpToolBar->GetIdent();

		if (lpToolBar->bBreak)
			rbBand.fStyle |= RBBS_BREAK;

		lpWnd->SendMsg(RB_INSERTBAND, -1, (LPARAM) &rbBand);

	}
}	



void MdzDockBar::SetToolBarVisible(MdzToolBar &toolbar, BOOL bIsVisible)
{
	UINT index = lpWnd->SendMsg(RB_IDTOINDEX, toolbar.GetIdent());
	lpWnd->SendMsg(RB_SHOWBAND, index, bIsVisible);
	SendMessage(::GetParent(GetHandle()), WM_SIZE, 0, 0);
}

void MdzDockBar::AddToolBar(MdzToolBar &toolbar, BOOL bBreak)
{
	toolbar.SetParent(this);
	toolbar.bBreak = bBreak;
	toolbarList.Add(&toolbar);
}

void MdzDockBar::OnNotify(MdzEvent& evt)
{
	LPNMHDR lpHeader = (LPNMHDR) evt.lParam;

	if (lpHeader->code == RBN_AUTOSIZE)
	{
		MdzRect rc = * (MdzRect*) &((LPNMRBAUTOSIZE) lpHeader)->rcTarget;

		((MdzFrame*) lpParent)->OnDockBarResized(rc);
	}
}
