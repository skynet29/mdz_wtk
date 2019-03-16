// MdzKey.cpp: implementation of the MdzKey class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzKey.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT MdzKey::K_ENTER		= VK_RETURN;
const UINT MdzKey::K_SHIFT		= VK_SHIFT;
const UINT MdzKey::K_CTRL		= VK_CONTROL;
const UINT MdzKey::K_LEFT		= VK_LEFT;
const UINT MdzKey::K_RIGHT		= VK_RIGHT;
const UINT MdzKey::K_DOWN		= VK_DOWN;
const UINT MdzKey::K_UP			= VK_UP;
const UINT MdzKey::K_TAB		= VK_TAB;
const UINT MdzKey::K_DELETE	= VK_DELETE;
const UINT MdzKey::K_ALT		= VK_MENU;
const UINT MdzKey::K_F1			= VK_F1;
const UINT MdzKey::K_F2			= VK_F2;
const UINT MdzKey::K_F3			= VK_F3;
const UINT MdzKey::K_F4			= VK_F4;
const UINT MdzKey::K_F5			= VK_F5;
const UINT MdzKey::K_F6			= VK_F6;
const UINT MdzKey::K_F7			= VK_F7;
const UINT MdzKey::K_F8			= VK_F8;
const UINT MdzKey::K_F9			= VK_F9;
const UINT MdzKey::K_F10		= VK_F10;
const UINT MdzKey::K_F11		= VK_F11;
const UINT MdzKey::K_F12		= VK_F12;


MdzKey::MdzKey()
{

}

MdzKey::~MdzKey()
{

}

BOOL MdzKey::IsKeyDown(int key)
{
	return ((GetKeyState(key) & 0x8000) == 0x8000);
}
