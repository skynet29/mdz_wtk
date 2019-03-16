// MdzDividerPanel.h: interface for the MdzDividerPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDIVIDERPANEL_H__E186C97B_1254_4D3D_BB03_CA3091D77A55__INCLUDED_)
#define AFX_MDZDIVIDERPANEL_H__E186C97B_1254_4D3D_BB03_CA3091D77A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzContainer.h"
#include "MdzPanel.h"
#include "MdzGraphic.h"

class DllExport MdzHorzDividerPanel : public MdzContainer  
{
public:
	void SetRightCtrl(MdzCtrl &ctrl);
	void SetLeftCtrl(MdzCtrl& ctrl, UINT iLeftCtrlWidth = 100);
	MdzHorzDividerPanel();
	virtual ~MdzHorzDividerPanel();
private:
	void OnSize(int iWidth, int iHeight);
	void sizePanel_OnMouseDrag(int x, int y);
	void sizePanel_OnLeftButtonUp(int x, int y);
	void sizePanel_OnLeftButtonDown(int x, int y);
	MdzCtrl* pLeftCtrl;
	MdzCtrl* pRightCtrl;
	MdzPanel sizePanel;
	UINT iLeftCtrlWidth;
	MdzGraphic graph;
	MdzPoint pt1, pt2;
};


#endif // !defined(AFX_MDZDIVIDERPANEL_H__E186C97B_1254_4D3D_BB03_CA3091D77A55__INCLUDED_)
