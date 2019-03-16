
#include "MdzHorzDividerPanel.h"
#include "MdzCursor.h"
#include "MdzWindow.h"
#include "MdzColor.h"

#define SIZEPANELWIDTH 5


MdzHorzDividerPanel::MdzHorzDividerPanel()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	lpWnd->OnSize = MDZ_CBK2(MdzHorzDividerPanel, OnSize);
	pLeftCtrl = NULL;
	pRightCtrl = NULL;
	iLeftCtrlWidth = 100;
	Add(sizePanel);
	sizePanel.SetCursor(MdzCursor::K_SIZEWE);
	sizePanel.SetOnLeftButtonDown(MDZ_CBK2(MdzHorzDividerPanel, sizePanel_OnLeftButtonDown));
	sizePanel.SetOnLeftButtonUp(MDZ_CBK2(MdzHorzDividerPanel, sizePanel_OnLeftButtonUp));
	sizePanel.SetOnMouseDrag(MDZ_CBK2(MdzHorzDividerPanel, sizePanel_OnMouseDrag));
	sizePanel.SetBackColor(MdzColor::GetSysColor());
}

MdzHorzDividerPanel::~MdzHorzDividerPanel()
{

}

void MdzHorzDividerPanel::SetLeftCtrl(MdzCtrl &ctrl, UINT iLeftCtrlWidth)
{
	this->iLeftCtrlWidth = iLeftCtrlWidth;
	pLeftCtrl = &ctrl;
	Add(ctrl);
}

void MdzHorzDividerPanel::SetRightCtrl(MdzCtrl &ctrl)
{
	pRightCtrl = &ctrl;
	Add(ctrl);
}

void MdzHorzDividerPanel::sizePanel_OnLeftButtonDown(int x, int y)
{
	graph.Init(GetWindowDC(GetDesktopWindow()));
	graph.SetDrawMode(MdzGraphic::K_NOT);
	MdzRect rc = GetClientRect();
	pt1 = MdzPoint(x, rc.top);
	pt1.ToScreen(sizePanel);
	pt2 = MdzPoint(x, rc.bottom);
	pt2.ToScreen(sizePanel);
	graph.DrawLine(MdzRect(pt1, pt2));

	MdzPoint leftTop = MdzPoint(rc.left, rc.top);
	leftTop.ToScreen(*this);
	MdzPoint rightBottom = MdzPoint(rc.right, rc.bottom);
	rightBottom.ToScreen(*this);

	MdzRect clipRect = MdzRect(leftTop, rightBottom);
	clipRect.right -= 50;
	clipRect.left += 50;
	ClipCursor(&clipRect);
}

void MdzHorzDividerPanel::sizePanel_OnLeftButtonUp(int x, int y)
{
	graph.DrawLine(MdzRect(pt1, pt2));
	ReleaseDC(GetDesktopWindow(), graph.GetHandle());
	graph.Release();
	ClipCursor(NULL);
	//pt1.ToScreen(sizePanel);
	pt1.ToClient(*this);
	iLeftCtrlWidth = pt1.x;
	MdzRect rc = GetClientRect();
	OnSize(rc.Width(), rc.Height());
}

void MdzHorzDividerPanel::sizePanel_OnMouseDrag(int x, int y)
{
	graph.DrawLine(MdzRect(pt1, pt2));

	MdzRect rc = sizePanel.GetClientRect();
	pt1 = MdzPoint(x, rc.top);
	pt1.ToScreen(sizePanel);
	pt2 = MdzPoint(x, rc.bottom);
	pt2.ToScreen(sizePanel);
	graph.DrawLine(MdzRect(pt1, pt2));
}

void MdzHorzDividerPanel::OnSize(int width, int height)
{
	if (pLeftCtrl)
		pLeftCtrl->SetBounds(0, 0, iLeftCtrlWidth, height);

	sizePanel.SetBounds(iLeftCtrlWidth, 0, SIZEPANELWIDTH, height);
	
	if (pRightCtrl)
		pRightCtrl->SetBounds(iLeftCtrlWidth + SIZEPANELWIDTH, 0, width - iLeftCtrlWidth - SIZEPANELWIDTH, height);
	
}


