// MdzButton.h: interface for the MdzButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZBUTTON_H__84C7CD54_E09C_474B_9DEF_4CAAC1A98777__INCLUDED_)
#define AFX_MDZBUTTON_H__84C7CD54_E09C_474B_9DEF_4CAAC1A98777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"
#include "MdzBitmap.h"

class MdzToolTips;
class MdzEvent;

class DllExport MdzButton : public MdzCtrl  
{
public:
	MdzButton();

	void
	SetBitmap(MdzBitmap bitmap);

	void
	SetCaption(LPSTR strCaption);

	void
	SetToolTips(LPSTR strToolTips);

	void
	SetOnClick(MdzCbk1* lpFunc);

	virtual ~MdzButton();
	
	virtual void
	Create();
private:
	void SetAsDefault();
	void OnCommand(MdzEvent& evt);
	MdzBitmap bitmap;
	MdzToolTips* lpToolTips;
	MdzCbk1* lpOnClick;

	friend class MdzDialog;
};

#endif // !defined(AFX_MDZBUTTON_H__84C7CD54_E09C_474B_9DEF_4CAAC1A98777__INCLUDED_)
