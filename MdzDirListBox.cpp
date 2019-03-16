// MdzDirListBox.cpp: implementation of the MdzDirListBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDirListBox.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzDirListBox::MdzDirListBox()
{
	char* p = getenv("USERPROFILE");
	strPath = (p) ? p : "c:";
//	SetOnDblClick(MDZ_CBK1(MdzDirListBox, OnDblClick));
}

MdzDirListBox::~MdzDirListBox()
{

}

void MdzDirListBox::UpdatePath()
{
	MdzString temp = strPath + MdzString("\\*");

	RemoveAllItems();

	lpWnd->SendMsg(LB_DIR, DDL_DIRECTORY | DDL_EXCLUSIVE, (LPARAM) (LPSTR) temp);
}

void MdzDirListBox::Create()
{
	MdzListBox::Create();
	UpdatePath();
}

void MdzDirListBox::OnDblClick()
{
	MdzString selText = GetSelItem();
	selText = selText.GetSubString(1, selText.GetIndexOf("]")-1);

	if (selText.Equals(".."))
	{
		char* tmp = strdup(strPath);
		char* p = strrchr(tmp, '\\');
		if (p)
		{
			*p = 0;
			strPath = tmp;
		}
		free(tmp);
	}
	else
	{
		strPath += MdzString("\\");
		strPath += selText;
	}
	UpdatePath();
	MdzListBox::OnDblClick();
}

MdzString MdzDirListBox::GetPath()
{
	/*
	char buffer[MAX_PATH];
	GetShortPathName(strPath, buffer, sizeof(buffer));
	return buffer;
	*/
	return strPath;
}

void MdzDirListBox::SetDrive(LPSTR strDrive)
{
	strPath = MdzString::Format("%s:", strDrive);
	UpdatePath();
}
