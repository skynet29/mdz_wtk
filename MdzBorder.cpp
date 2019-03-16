// MdzBorder.cpp: implementation of the MdzBorder class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzBorder.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzBorder::MdzBorder()
{
	lpWnd->lpClassName = "BUTTON";
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | BS_GROUPBOX;
	bAutoDelete = TRUE;
}

MdzBorder::~MdzBorder()
{

}



void MdzBorder::SetTitle(LPSTR strTitle)
{
	lpWnd->SetText(strTitle);
}
