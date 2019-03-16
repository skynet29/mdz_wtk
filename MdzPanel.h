// MdzPanel.h: interface for the MdzPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZPANEL_H__13E90289_85FB_4B81_B48D_A94B95293ADA__INCLUDED_)
#define AFX_MDZPANEL_H__13E90289_85FB_4B81_B48D_A94B95293ADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzGraphic.h"
#include "MdzContainer.h"
#include "MdzCbk1.h"
#include "MdzCbk2.h"
#include "MdzCbk4.h"
#include "MdzCbk6.h"
#include "MdzPoint.h"	// Added by ClassView

class MdzScroller;
class MdzEvent;

class DllExport MdzPanel : public MdzContainer  
{
public:
	MdzPanel();

	void
	SetOnSize(MdzCbk2* lpFunc);

	void
	SetBorder(BOOL bHasBorder);
	
	void
	SetBackColor(COLORREF backColor);

	void
	Redraw(BOOL bErase = TRUE);
	
	MdzPoint
	GetPageOrigin();

	void
	SetHorzScrollbar(UINT iPageWidth, UINT iIncrement);
	
	void
	SetVertScrollbar(UINT iPageHeight, UINT iIncrement);
	
	void
	SetCursor(WORD iResId);
	
	void
	SetOnPaint(MdzCbk4* lpFunc);
	
	void
	SetOnMouseMove(MdzCbk2* lpFunc);
	
	void
	SetOnMouseDrag(MdzCbk2* lpFunc);
	
	void
	SetOnRightButtonUp(MdzCbk2* lpFunc);
	
	void
	SetOnRightButtonDown(MdzCbk2* lpFunc);
	
	void
	SetOnLeftButtonUp(MdzCbk2* lpFunc);
	
	void
	SetOnLeftButtonDown(MdzCbk2* lpFunc);
	
	void
	SetOnKeyUp(MdzCbk6* lpFunc);
	
	void
	SetOnKeyDown(MdzCbk6* lpFunc);

	virtual ~MdzPanel();
private:
	void OnPaint(MdzGraphic& graphic);
	void OnVScroll(MdzEvent& evt);
	void OnHScroll(MdzEvent& evt);
	MdzScroller*	iVertScroller;
	MdzScroller*	iHorzScroller;
	MdzCbk4* lpOnPaint;
	MdzCbk2* lpOnSize;


protected:
	virtual void OnCreate();
	virtual void OnSize(int iWidth, int iHeight);
public:
	void GetGraphic(MdzGraphic& xGraphic);
};

#endif // !defined(AFX_MDZPANEL_H__13E90289_85FB_4B81_B48D_A94B95293ADA__INCLUDED_)
