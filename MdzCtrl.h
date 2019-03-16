// MdzCtrl.h: interface for the MdzCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZCTRL_H__3DB931EC_042B_496A_A8C9_91D7561CBA09__INCLUDED_)
#define AFX_MDZCTRL_H__3DB931EC_042B_496A_A8C9_91D7561CBA09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzBounds.h"
#include "MdzFont.h"	// Added by ClassView
#include "MdzObject.h"	// Added by ClassView

class MdzWindow;
class MdzFont;


class DllExport MdzCtrl : public MdzObject
{
public:
	BOOL HasFocus();
	DEFINE_STD_METHODS(MdzCtrl, MdzObject)
	void Update();

	MdzCtrl* GetParent();
	MdzCtrl();

	void
	SetAutoDelete(BOOL bAutoDelete);

	MdzFont
	GetFont();

	MdzBounds
	GetBounds();

	virtual ~MdzCtrl();

	void
	SetVisible(BOOL bIsVisible);

	void
	SetFont(MdzFont& font);

	void
	SetBounds(MdzBounds& bounds);

	void
	SetBounds(int left, int top, int width, int height);

	void
	SetEnabled(BOOL bIsEnabled);

	void
	SetParent(MdzCtrl* lpParent);
	
	void
	SetSize(int width, int height);
	
	void
	SetLocation(int left, int top);

	HWND
	GetHandle();

	BOOL
	IsEnabled();

	BOOL IsVisible();

	void
	RequestFocus();

	virtual void
	Create();
protected:
	MdzWindow*	lpWnd;
	MdzCtrl*	lpParent;
	BOOL bAutoDelete;
	friend class MdzContainer;

};

#endif // !defined(AFX_MDZCTRL_H__3DB931EC_042B_496A_A8C9_91D7561CBA09__INCLUDED_)
