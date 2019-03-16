// MdzMenuBar.cpp: implementation of the MdzMenuBar class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMenuBar.h"
#include "MdzMenu.h"
#include "MdzCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzMenuBar::MdzMenuBar()
{
	hMenu = CreateMenu();
	lpParent = NULL;
}

MdzMenuBar::~MdzMenuBar()
{

}

HMENU MdzMenuBar::GetHandle()
{
	return hMenu;
}

void MdzMenuBar::Add(MdzMenu &menu, LPSTR strCaption)
{
	AppendMenu(hMenu, MF_POPUP, (UINT) menu.GetHandle(), strCaption);
	if (lpParent && lpParent->GetHandle())
		DrawMenuBar(lpParent->GetHandle());
}
