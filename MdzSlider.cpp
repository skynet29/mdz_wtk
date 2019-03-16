// MdzSlider.cpp: implementation of the MdzSlider class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSlider.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSlider::MdzSlider()
{
	lpWnd->lpClassName = TRACKBAR_CLASS;
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE; // | TBS_AUTOTICKS;
	lpWnd->OnHScroll = MDZ_CBK3(MdzSlider, OnHScroll);

	iMin = 0;
	iMax = 100;
	iValue = 50;
	lpOnSelChange = NULL;
}

MdzSlider::~MdzSlider()
{
	if (lpOnSelChange)
		delete lpOnSelChange;
}

void MdzSlider::SetRange(int iMin, int iMax)
{
	MEMBER_SET(iMin);
	MEMBER_SET(iMax);

	//lpWnd->SendMsg(TBM_SETRANGE, (WPARAM) TRUE, MAKELONG(iMin, iMax));
	lpWnd->SendMsg(TBM_SETRANGEMIN, FALSE, iMin);
	lpWnd->SendMsg(TBM_SETRANGEMAX, TRUE, iMax);

}

void MdzSlider::SetValue(int iValue)
{
	MEMBER_SET(iValue);

	lpWnd->SendMsg(TBM_SETPOS, (WPARAM) TRUE, iValue); 

}

int MdzSlider::GetValue()
{
	return iValue;
}

void MdzSlider::SetOnSelChange(MdzCbk1 *lpFunc)
{
	if (lpOnSelChange)
		delete lpOnSelChange;
	lpOnSelChange = lpFunc;
}

void MdzSlider::SetBorder(BOOL bHasBorder)
{
	lpWnd->ModifyStyle(WS_BORDER, bHasBorder);
}

void MdzSlider::Create()
{
	MdzCtrl::Create();

	SetRange(iMin, iMax);
	SetValue(iValue);
}

void MdzSlider::OnHScroll(MdzEvent& evt)
{
	iValue = lpWnd->SendMsg(TBM_GETPOS);

	if (lpOnSelChange)
	{
		switch (LOWORD(evt.wParam))
		{
		case TB_PAGEDOWN:
		case TB_PAGEUP:
		case TB_LINEUP:
		case TB_LINEDOWN:
		case TB_THUMBTRACK:
			lpOnSelChange->Fire();
			break;
		}
	}
}
