// MdzMdiChild.h: interface for the MdzMdiChild class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZMDICHILD_H__F3342BE1_9994_4168_8DED_DE2600FFCBE1__INCLUDED_)
#define AFX_MDZMDICHILD_H__F3342BE1_9994_4168_8DED_DE2600FFCBE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzContainer.h"
#include "MdzColor.h"

class DllExport MdzMdiChild  : public MdzContainer
{
public:
	MdzMdiChild();
	
	void
	SetTitle(LPSTR strTitle);

	void
	SetMaximized(BOOL bIsMaximized);
	
	void
	SetBackColor(MdzColor backColor);
	
	void
	SetClientCtrl(MdzCtrl& ctrl);
	
	virtual void
	OnFocus(UINT bGotFocus);
	
	virtual void
	OnSize(int width, int height);
	
	virtual ~MdzMdiChild();
private:
	MdzCtrl* lpClientCtrl;
};

#endif // !defined(AFX_MDZMDICHILD_H__F3342BE1_9994_4168_8DED_DE2600FFCBE1__INCLUDED_)
