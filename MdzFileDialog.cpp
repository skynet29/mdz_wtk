// MdzFileDialog.cpp: implementation of the MdzFileDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFileDialog.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MdzFileDialog::MdzFileDialog()
{
	strFileName[0] = 0;
}

MdzFileDialog::~MdzFileDialog()
{

}


BOOL MdzFileDialog::Execute(int iOption)
//BOOL MdzFileDialog::Execute(int iOption, MdzCtrl *lpParent)
{
	BOOL bRet;
	LPSTR lpTemp = NULL;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	
	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = lpParent->GetHandle();
	ofn.hwndOwner = GetActiveWindow();

	if (strFilter.GetLength() > 0)
	{
		/*
		lpTemp = new char[(strlen(strFilter) + 2)];
		strcpy(lpTemp, strFilter);
		strcat(lpTemp, "|");
		*/
		lpTemp = strdup(strFilter);

		LPSTR lpTemp2 = lpTemp;
		while (lpTemp2 = strchr(lpTemp2, '|'))
			*lpTemp2++ = 0;

		ofn.lpstrFilter = lpTemp;
	}

	ofn.lpstrFile = strFileName;
	ofn.nMaxFile = sizeof(strFileName);
	if (strDefaultExt.GetLength())
		ofn.lpstrDefExt = strDefaultExt;
	ofn.Flags = OFN_HIDEREADONLY;

	if (strInitDir.GetLength())
		ofn.lpstrInitialDir = strInitDir;

	if (iOption == 0)
	{
		bRet = GetOpenFileName(&ofn);
	}
	else
	{
		bRet = GetSaveFileName(&ofn);
	}

	if (lpTemp)
	{
		free(lpTemp);
	}

	return bRet;
}



void MdzFileDialog::SetDefaultExtension(LPSTR strDefaultExt)
{
	MEMBER_SET(strDefaultExt);

}

MdzString MdzFileDialog::GetFileName()
{
	return MdzString(strFileName).ExtractFileName();
}

void MdzFileDialog::SetInitDirectory(LPSTR strInitDir)
{
	MEMBER_SET(strInitDir);
	
}

void MdzFileDialog::SetFileName(LPSTR strFileName)
{
	strcpy(this->strFileName, strFileName);
}

MdzString MdzFileDialog::GetCurrentDirectory()
{
	MdzString ret;

	LPSTR lpFileName = strdup(strFileName);

	LPSTR lpTemp = strrchr(lpFileName, '\\');

	if (lpTemp)
	{
		*lpTemp = 0;
		ret = lpFileName;
	}

	free(lpFileName);

	return ret;
}

MdzString MdzFileDialog::GetFullPathName()
{
	return strFileName;
}

BOOL MdzFileDialog::ShowOpen()
{
	return Execute(0);
}

BOOL MdzFileDialog::ShowSave()
{
	return Execute(1);
}

void MdzFileDialog::AddFilter(LPSTR strName, LPSTR strFilterExt)
{
	strFilter += MdzString::Format("%s|*.%s|", strName, strFilterExt);
}
