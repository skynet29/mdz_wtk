// MdzDividerPanel.cpp: implementation of the MdzDividerPanel class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzVertDividerPanel.h"
#include "MdzCursor.h"
#include "MdzWindow.h"
#include "MdzColor.h"

#define SIZEPANELHEIGHT 5
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



MdzVertDividerPanel::MdzVertDividerPanel()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE;
	pTopCtrl = NULL;
	pBottomCtrl = NULL;
	iBottomCtrlHeight = 100;
	lpWnd->OnSize = MDZ_CBK2(MdzVertDividerPanel, OnSize);
	Add(sizePanel);
	sizePanel.SetCursor(MdzCursor::K_SIZENS);
	sizePanel.SetOnLeftButtonDown(MDZ_CBK2(MdzVertDividerPanel, sizePanel_OnLeftButtonDown));
	sizePanel.SetOnLeftButtonUp(MDZ_CBK2(MdzVertDividerPanel, sizePanel_OnLeftButtonUp));
	sizePanel.SetOnMouseDrag(MDZ_CBK2(MdzVertDividerPanel, sizePanel_OnMouseDrag));
	sizePanel.SetBackColor(MdzColor::GetSysColor());
}

MdzVertDividerPanel::~MdzVertDividerPanel()
{

}

void MdzVertDividerPanel::SetBottomCtrl(MdzCtrl &ctrl, UINT iBottomCtrlHeight)
{
	MEMBER_SET(iBottomCtrlHeight);
	pBottomCtrl = &ctrl;
	Add(ctrl);
}

void MdzVertDividerPanel::SetTopCtrl(MdzCtrl &ctrl)
{
	pTopCtrl = &ctrl;
	Add(ctrl);
}

void MdzVertDividerPanel::sizePanel_OnLeftButtonDown(int x, int y)
{
	graph.Init(GetWindowDC(GetDesktopWindow()));
	graph.SetDrawMode(MdzGraphic::K_NOT);
	MdzRect rc = GetClientRect();
	pt1 = MdzPoint(rc.left, y);
	pt1.ToScreen(sizePanel);
	pt2 = MdzPoint(rc.right, y);
	pt2.ToScreen(sizePanel);
	graph.DrawLine(MdzRect(pt1, pt2));

	MdzPoint leftTop = MdzPoint(rc.left, rc.top);
	leftTop.ToScreen(*this);
	MdzPoint rightBottom = MdzPoint(rc.right, rc.bottom);
	rightBottom.ToScreen(*this);

	MdzRect clipRect = MdzRect(leftTop, rightBottom);
	clipRect.bottom -= 50;
	clipRect.top += 50;
	ClipCursor(&clipRect);
}

void MdzVertDividerPanel::sizePanel_OnLeftButtonUp(int x, int y)
{
	graph.DrawLine(MdzRect(pt1, pt2));
	ReleaseDC(GetDesktopWindow(), graph.GetHandle());
	graph.Release();
	ClipCursor(NULL);
	//pt1.ToScreen(sizePanel);
	pt1.ToClient(*this);
	MdzRect rc = GetClientRect();
	iBottomCtrlHeight = rc.Height() - pt1.y;
	OnSize(rc.Width(), rc.Height());
}

void MdzVertDividerPanel::sizePanel_OnMouseDrag(int x, int y)
{
	graph.DrawLine(MdzRect(pt1, pt2));

	MdzRect rc = sizePanel.GetClientRect();
	pt1 = MdzPoint(rc.left, y);
	pt1.ToScreen(sizePanel);
	pt2 = MdzPoint(rc.right, y);
	pt2.ToScreen(sizePanel);
	graph.DrawLine(MdzRect(pt1, pt2));
}

void MdzVertDividerPanel::OnSize(int width, int height)
{
	
	if (pBottomCtrl)
		pBottomCtrl->SetBounds(0, height - iBottomCtrlHeight, width, iBottomCtrlHeight);

	sizePanel.SetBounds(0, height - iBottomCtrlHeight - SIZEPANELHEIGHT, width, SIZEPANELHEIGHT);
	
	if (pTopCtrl)
		pTopCtrl->SetBounds(0, 0, width, height - iBottomCtrlHeight - SIZEPANELHEIGHT);

}
