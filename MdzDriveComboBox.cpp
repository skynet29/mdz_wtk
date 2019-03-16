// MdzDriveComboBox.cpp: implementation of the MdzDriveComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDriveComboBox.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzDriveComboBox::MdzDriveComboBox()
{

}

MdzDriveComboBox::~MdzDriveComboBox()
{

}

void MdzDriveComboBox::Create()
{
	MdzComboBox::Create();

	char buffer[] = "";
	lpWnd->SendMsg(CB_DIR, DDL_DRIVES | DDL_EXCLUSIVE, (LPARAM) buffer);
	UINT iCount = GetItemCount();
	for (UINT i = 0; i < iCount; i++)
	{
		if (GetItemAt(i).GetSubString(2, 1).Equals("c"))
		{
			SetSelIndex(i);
			break;
		}
	}
}

MdzString MdzDriveComboBox::GetDrive()
{
	return GetSelItem().GetSubString(2, 1);
}
