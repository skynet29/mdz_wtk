// MdzScroller.cpp: implementation of the MdzScroller class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzScroller.h"
#include "MdzCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzScroller::MdzScroller(MdzCtrl* lpParent, UINT iRange, UINT iIncrement, UINT iType)
{
	MEMBER_SET(lpParent);
	MEMBER_SET(iRange);
	MEMBER_SET(iIncrement);
	MEMBER_SET(iType);
}

MdzScroller::~MdzScroller()
{

}

void MdzScroller::Create()
{
	HWND hWnd = lpParent->GetHandle();

	MdzRect rc;
	GetClientRect(hWnd, &rc);

	SCROLLINFO info;
	info.cbSize = sizeof(info);
 	info.fMask = SIF_ALL;
 	info.nMin = 0;
	info.nPos = 0;
	info.nMax = iRange;
	info.nPage = (iType == SB_VERT) ? rc.Height() : rc.Width();

	SetScrollInfo(hWnd, iType, &info, FALSE);
}

void MdzScroller::Resize(UINT iNewSize)
{
	SCROLLINFO info;
	info.cbSize = sizeof(info);
	info.fMask = SIF_PAGE;
	info.nPage = iNewSize;
	SetScrollInfo(lpParent->GetHandle(), iType, &info, TRUE);

}

void MdzScroller::Scroll(UINT iCode, UINT iTrackPos)
{
	HWND hWnd = lpParent->GetHandle();

	SCROLLINFO info;
	info.cbSize = sizeof(info);
	info.fMask = SIF_ALL;
	GetScrollInfo(hWnd, iType, &info);
	int nPos = info.nPos;

	switch (iCode)
	{
	case SB_LINEUP:
		nPos -= iIncrement;
		break;

	case SB_LINEDOWN:
 		nPos += iIncrement;
		break;

	case SB_PAGEUP:
		nPos -= info.nPage;
		break;

	case SB_PAGEDOWN:
		nPos += info.nPage;
		break;

	case SB_THUMBTRACK:
		nPos = iTrackPos;
		break;
	}
	
	nPos = min(info.nMax - (int)info.nPage, max(info.nMin, nPos));

	SetScrollPos(hWnd, iType, nPos, TRUE);

	if (iType == SB_VERT)
		ScrollWindow(hWnd, 0, info.nPos - nPos, NULL, NULL);
	else
		ScrollWindow(hWnd, info.nPos - nPos, 0, NULL, NULL);

}

UINT MdzScroller::GetPos()
{
	return GetScrollPos(lpParent->GetHandle(), iType);
}

void MdzScroller::SetPos(UINT iPos)
{
	SetScrollPos(lpParent->GetHandle(), iType, iPos, TRUE);
}
