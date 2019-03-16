// MdzDividerPanel.h: interface for the MdzDividerPanel class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MDZVERTDIVIDERPANEL_H
#define MDZVERTDIVIDERPANEL_H

#include "MdzContainer.h"
#include "MdzPanel.h"
#include "MdzGraphic.h"

class DllExport MdzVertDividerPanel : public MdzContainer  
{
public:
	void SetTopCtrl(MdzCtrl &ctrl);
	void SetBottomCtrl(MdzCtrl& ctrl, UINT iBottomCtrlHeight = 100);
	MdzVertDividerPanel();
	virtual ~MdzVertDividerPanel();
private:
	void OnSize(int iWidth, int iHeight);
	void sizePanel_OnMouseDrag(int x, int y);
	void sizePanel_OnLeftButtonUp(int x, int y);
	void sizePanel_OnLeftButtonDown(int x, int y);
	MdzCtrl* pTopCtrl;
	MdzCtrl* pBottomCtrl;
	MdzPanel sizePanel;
	UINT iBottomCtrlHeight;
	MdzGraphic graph;
	MdzPoint pt1, pt2;
};
#endif // MDZVERTDIVIDERPANEL_H
