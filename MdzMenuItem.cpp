// MdzMenuItem.cpp: implementation of the MdzMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMenuItem.h"
#include "MdzVector.h"
#include "MdzKey.h"
#include "MdzGraphic.h"
#include "MdzFont.h"
#include "MdzColor.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


static MdzVectorT<MdzMenuItem> items;
static MdzVector freeIdents;

MdzMenuItem::MdzMenuItem()
{
	static UINT gIdent = 100;

	bIsChecked = FALSE;
	bIsEnabled = TRUE;
	hMenu = NULL;

	if (freeIdents.GetCount() > 0)
	{
		iIdent = (UINT)freeIdents.GetAt(0);
		freeIdents.RemoveAt(0);
	}
	else
	{
		iIdent = gIdent++;
	}
	lpOnClick = NULL;
	lpAccel = NULL;
	items.Add(this);
}

MdzMenuItem::~MdzMenuItem()
{
	if (lpOnClick)
		delete lpOnClick;
	if (lpAccel)
		delete lpAccel;

	items.Remove(this);
	freeIdents.Add((MdzObject*)iIdent);

}


void MdzMenuItem::SetChecked(BOOL bIsChecked)
{
	MEMBER_SET(bIsChecked);
	CheckMenuItem(hMenu, iIdent, (bIsChecked) ? MF_CHECKED : MF_UNCHECKED);
}

void MdzMenuItem::SetEnabled(BOOL bIsEnabled)
{
	MEMBER_SET(bIsEnabled);
	EnableMenuItem(hMenu, iIdent, (bIsEnabled) ? MF_ENABLED : MF_GRAYED);
}

BOOL MdzMenuItem::IsChecked()
{
	return bIsChecked;
}

BOOL MdzMenuItem::IsEnabled()
{
	return bIsEnabled;
}

void MdzMenuItem::SetOnClick(MdzCbk1 *lpFunc)
{
	if (lpOnClick)
		delete lpOnClick;
	lpOnClick = lpFunc;
}


void MdzMenuItem::Create(HMENU hMenu, LPSTR strCaption)
{
	MEMBER_SET(hMenu);
	MEMBER_SET(strCaption);


	UINT uFlags = MF_OWNERDRAW;

	if (!bIsEnabled)
		uFlags |= MF_GRAYED;
	if (bIsChecked)
		uFlags |= MF_CHECKED;

	AppendMenu(hMenu, uFlags, iIdent, strCaption);

	/*
	MENUITEMINFO mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_DATA;
	mii.dwItemData = (DWORD) this;
	SetMenuItemInfo(hMenu, iIdent, FALSE, &mii);
	*/
}

BOOL MdzMenuItem::SetShortcut(UINT iKeyChanger, char character)
{
	char buff[4];

	if (character >= VK_F1 && character <= VK_F12)
	{
		sprintf(buff, "F%d", character-VK_F1+1);
	}
	else 
	{
		if (islower(character))
			character = toupper(character);
		buff[0] = character;
		buff[1] = 0;
	}

	BYTE fVirt = FVIRTKEY;

	switch (iKeyChanger)
	{
	case 0:
		SetCaption(MdzString::Format("%s\t%s", (LPSTR) GetCaption(), buff));
		break;

	case VK_SHIFT:
		fVirt |= FSHIFT;
		SetCaption(MdzString::Format("%s\tShift+%s", (LPSTR) GetCaption(), buff));
		break;

	case VK_CONTROL:
		fVirt |= FCONTROL;
		SetCaption(MdzString::Format("%s\tCtrl+%s", (LPSTR) GetCaption(), buff));
		break;

	case VK_MENU: //ALT
		fVirt |= FALT;
		SetCaption(MdzString::Format("%s\tAlt+%s", (LPSTR) GetCaption(), buff));
		break;

	default:
		return FALSE;
	}

	if (lpAccel)
		delete lpAccel;
	lpAccel = new tagACCEL;
	lpAccel->cmd = iIdent;
	lpAccel->fVirt = fVirt;
	lpAccel->key = character;

	return TRUE;
}

MdzString MdzMenuItem::GetCaption()
{
	/*
	MdzString ret;

	if (hMenu)
	{
		MENUITEMINFO mii;
		mii.cbSize = sizeof(mii);
		mii.fMask = MIIM_TYPE;
		mii.dwTypeData = NULL;
		GetMenuItemInfo(hMenu, iIdent, FALSE, &mii);

		mii.cch++;
		ret.Alloc(mii.cch);
		mii.dwTypeData = (LPSTR) ret;
		GetMenuItemInfo(hMenu, iIdent, FALSE, &mii);
	}

	return ret;
	*/
	return strCaption;
}

void MdzMenuItem::SetCaption(LPSTR strCaption)
{
	MEMBER_SET(strCaption);
	//ModifyMenu(hMenu, iIdent, MF_BYCOMMAND, iIdent, strCaption);
}

/*
MdzMenuItem* MdzMenuItem::GetPtrFromId(HMENU hMenu, UINT iIdent)
{
   MENUITEMINFO mii;
   mii.cbSize = sizeof(mii);
   mii.fMask = MIIM_DATA;
   if (!GetMenuItemInfo(hMenu, iIdent, FALSE, &mii))
	   return NULL;

   return (MdzMenuItem*) mii.dwItemData;
}
*/

MdzMenuItem* MdzMenuItem::GetPtrFromId(UINT iIdent)
{
	
	for(UINT i = 0; i < items.GetCount(); i++)
	{
		if (items[i].iIdent == iIdent)
			return &items[i];
	}	

   return NULL;
}

void MdzMenuItem::OnMeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	MdzSize sz = bitmap.GetSize();
	MdzSize szText = MdzFont().MeasureString(strCaption);
	OutputDebugString(MdzString::Format("(%d,%d)\n", 
		lpMeasureItemStruct->itemWidth, lpMeasureItemStruct->itemHeight));
	OutputDebugString(MdzString::Format("len=%d\n", szText.cx));
	//lpMeasureItemStruct->itemHeight = max(sz.cy, szText.cy) + 5;

	//lpMeasureItemStruct->itemWidth = szText.cx + sz.cx + 5;
	lpMeasureItemStruct->itemHeight = max(sz.cy, szText.cy) + 5;

	lpMeasureItemStruct->itemWidth = szText.cx + 16 + 5;

}

void MdzMenuItem::SetBitmap(MdzBitmap bitmap)
{
	MEMBER_SET(bitmap);

}

void MdzMenuItem::OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	MdzGraphic graph;
	graph.Init(lpDrawItemStruct->hDC);
	MdzRect rc = *(MdzRect*)&lpDrawItemStruct->rcItem;
	int idx = strCaption.GetIndexOf("\t");
	MdzString strText = strCaption.GetSubString(0, idx);
	MdzString strShortcut;
	if (idx > 0)
		strShortcut = strCaption.GetSubString(idx+1);

	MdzBitmap bmp = bitmap;
	if (bIsChecked)
	{
		HDC hMemDC = CreateCompatibleDC(graph.GetHandle());
		HBITMAP hBitmap = CreateCompatibleBitmap(graph.GetHandle(), 16, 16);
		SelectObject(hMemDC, hBitmap);
		MdzRect rect(0, 0, 16, 16);
		DrawFrameControl(hMemDC, &rect,  DFC_MENU, DFCS_MENUCHECK);
		DeleteDC(hMemDC);
		bmp = hBitmap;
		bmp.MapColor(MdzColor::K_GREEN);
		if ((lpDrawItemStruct->itemState & (ODS_SELECTED | ODS_GRAYED)) == ODS_SELECTED)
			bmp.MapColor(MdzColor::K_BLACK, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	
	if ((lpDrawItemStruct->itemState & (ODS_SELECTED | ODS_GRAYED)) == ODS_SELECTED)
	{
		graph.SetColor(GetSysColor(COLOR_HIGHLIGHT));
		graph.FillRect(rc);
		graph.DrawBitmapTransparent(bmp, rc.left + 3, rc.top + 3);
		graph.SetColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		graph.SetColor(GetSysColor(COLOR_MENU));
		graph.FillRect(rc);
		if ((lpDrawItemStruct->itemState & ODS_GRAYED) == ODS_GRAYED)
		{
			graph.DrawBitmapDisabled(bmp, rc.left + 3, rc.top + 3);
			graph.SetColor(GetSysColor(COLOR_GRAYTEXT));
		}
		else
		{
			graph.DrawBitmapTransparent(bmp, rc.left + 3, rc.top + 3);
			graph.SetColor(GetSysColor(COLOR_MENUTEXT));
		}

	}

	rc.left += 22;
	graph.DrawSingleString(strText, rc);		
	rc.right -= 16;
	if (strShortcut.GetLength())
		graph.DrawSingleString(strShortcut, rc, MdzGraphic::K_RIGHT);		


}
