// MdzStdDialog.cpp: implementation of the MdzStdDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzStdDialog.h"
#include "MdzDlgInput.h"

const UINT MdzStdDialog::K_YES = IDYES;
const UINT MdzStdDialog::K_NO = IDNO; 
const UINT MdzStdDialog::K_CANCEL = IDCANCEL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////





void MdzStdDialog::ShowMessage(LPSTR strText, LPSTR strTitle)
{
	MessageBox(GetActiveWindow(), strText, (strTitle) ? strTitle : "Message Dialog", MB_OK);
}

MdzString MdzStdDialog::ShowInput(LPSTR strText, LPSTR strTitle)
{
	MdzDlgInput dlg;
	if (strTitle)
		dlg.SetTitle(strTitle);
	if (strText)
		dlg.SetLabel(strText);
	//dlg.SetParent(lpParent);
	MdzString ret;
	if (dlg.Execute())
		ret = dlg.GetText();
	return ret;
}

UINT MdzStdDialog::ShowConfirm(LPSTR strText, LPSTR strTitle)
{
	return MessageBox(GetActiveWindow(), strText, (strTitle) ? strTitle : "Confirm Dialog", MB_YESNO);

}
