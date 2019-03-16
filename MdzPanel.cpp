// MdzPanel.cpp: implementation of the MdzPanel class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzPanel.h"
#include "MdzWindow.h"
#include "MdzScroller.h"
#include ".\mdzpanel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzPanel::MdzPanel()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	lpWnd->OnHScroll = MDZ_CBK3(MdzPanel, OnHScroll);
	lpWnd->OnVScroll = MDZ_CBK3(MdzPanel, OnVScroll);
	lpWnd->OnPaint = MDZ_CBK4(MdzPanel, OnPaint);
	lpWnd->OnSize = MDZ_CBK2(MdzPanel, OnSize);

	iVertScroller = NULL;
	iHorzScroller = NULL;

	lpOnPaint = NULL;
	lpOnSize = NULL;

}

MdzPanel::~MdzPanel()
{
	if (iVertScroller)
		delete iVertScroller;

	if (iHorzScroller)
		delete iHorzScroller;

	if (lpOnPaint)
		delete lpOnPaint;

	if (lpOnSize)
		delete lpOnSize;
}

void MdzPanel::SetBackColor(COLORREF backColor)
{
	lpWnd->backColor = backColor;
}

void MdzPanel::SetOnPaint(MdzCbk4* lpFunc)
{
	if (lpOnPaint)
		delete lpOnPaint;
	lpOnPaint = lpFunc;
}





void MdzPanel::SetOnMouseMove(MdzCbk2* lpFunc)
{
	lpWnd->OnMouseMove = lpFunc;
}


void MdzPanel::Redraw(BOOL bErase)
{
	lpWnd->Redraw(bErase);
}

void MdzPanel::SetBorder(BOOL bHasBorder)
{
	lpWnd->ModifyStyle(WS_BORDER, bHasBorder);
}



void MdzPanel::SetOnLeftButtonDown(MdzCbk2* lpFunc)
{
	lpWnd->OnLeftButtonDown = lpFunc;
}

void MdzPanel::SetOnLeftButtonUp(MdzCbk2* lpFunc)
{
	lpWnd->OnLeftButtonUp = lpFunc;

}

void MdzPanel::SetOnRightButtonDown(MdzCbk2* lpFunc)
{
	lpWnd->OnRightButtonDown = lpFunc;

}

void MdzPanel::SetOnRightButtonUp(MdzCbk2* lpFunc)
{
	lpWnd->OnRightButtonUp = lpFunc;

}

void MdzPanel::SetOnKeyDown(MdzCbk6 *lpFunc)
{
	lpWnd->OnKeyDown = lpFunc;
}

void MdzPanel::SetOnKeyUp(MdzCbk6 *lpFunc)
{
	lpWnd->OnKeyUp = lpFunc;

}

void MdzPanel::SetCursor(WORD iResId)
{
	lpWnd->SetCursor(iResId);
}

void MdzPanel::SetVertScrollbar(UINT iPageHeight, UINT iIncrement)
{
	if (!iVertScroller)
		iVertScroller = new MdzScroller(this, iPageHeight, iIncrement, SB_VERT);
}

void MdzPanel::SetHorzScrollbar(UINT iPageWidth, UINT iIncrement)
{
	if (!iHorzScroller)
		iHorzScroller = new MdzScroller(this, iPageWidth, iIncrement, SB_HORZ);

}

void MdzPanel::OnCreate()
{
	MdzContainer::OnCreate();

	if (iVertScroller)
		iVertScroller->Create();

	if (iHorzScroller)
		iHorzScroller->Create();
}

void MdzPanel::OnHScroll(MdzEvent &evt)
{
	if (iHorzScroller)
		iHorzScroller->Scroll(LOWORD(evt.wParam), HIWORD(evt.wParam));
}

void MdzPanel::OnVScroll(MdzEvent &evt)
{
	if (iVertScroller)
		iVertScroller->Scroll(LOWORD(evt.wParam), HIWORD(evt.wParam));

}

void MdzPanel::OnPaint(MdzGraphic &graphic)
{
	MdzPoint pt = GetPageOrigin();
	SetWindowOrgEx(graphic.GetHandle(), pt.x, pt.y, NULL);

	if (lpOnPaint)
		lpOnPaint->Fire(graphic);
}

MdzPoint MdzPanel::GetPageOrigin()
{
	MdzPoint pt;

	if (iHorzScroller)
		pt.x = iHorzScroller->GetPos();
	if (iVertScroller)
		pt.y = iVertScroller->GetPos();
	
	return pt;

}

void MdzPanel::OnSize(int iWidth, int iHeight)
{
	if (iHorzScroller)
		iHorzScroller->Resize(iWidth);
	if (iVertScroller)
		iVertScroller->Resize(iHeight);
	if (lpOnSize)
		lpOnSize->Fire(iWidth, iHeight);
}

void MdzPanel::SetOnMouseDrag(MdzCbk2 *lpFunc)
{
	lpWnd->OnMouseDrag = lpFunc;
}

void MdzPanel::SetOnSize(MdzCbk2 *lpFunc)
{
	if (lpOnSize)
		delete lpOnSize;
	lpOnSize = lpFunc;
}



void MdzPanel::GetGraphic(MdzGraphic& xGraphic)
{
	xGraphic.Init(*this);
}
