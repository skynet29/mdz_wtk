// MdzTextField.cpp: implementation of the MdzTextField class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTextField.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzTextField::MdzTextField()
{
   lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP;
	lpWnd->dwStyleEx = WS_EX_CLIENTEDGE;
	lpWnd->lpClassName = "EDIT";
	iMaxChar = (UINT) -1;
}

MdzTextField::~MdzTextField()
{

}

MdzString MdzTextField::GetText()
{
	return lpWnd->GetText();
}

void MdzTextField::SetText(LPSTR strText)
{
	lpWnd->SetText(strText);
}

void MdzTextField::SetMaxChar(UINT iMaxChar)
{
	MEMBER_SET(iMaxChar);
}

void MdzTextField::Create()
{
	MdzCtrl::Create();

	if (iMaxChar != (UINT) -1)
		lpWnd->SendMsg(EM_LIMITTEXT, iMaxChar);
}

void MdzTextField::SetPassword(BOOL bIsPassword)
{
	lpWnd->ModifyStyle(ES_PASSWORD, bIsPassword);
}

void MdzTextField::SetDigitOnly(BOOL bIsNumber)
{
	lpWnd->ModifyStyle(ES_NUMBER, bIsNumber);
	//lpWnd->ModifyStyle(ES_RIGHT, bIsNumber);
}

void MdzTextField::Select()
{
	lpWnd->SendMsg(EM_SETSEL, 0, -1);

}
