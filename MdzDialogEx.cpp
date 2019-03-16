// MdzDialogEx.cpp: implementation of the MdzDialogEx class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDialogEx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzDialogEx::MdzDialogEx()
{
	btnOk.SetCaption("OK");
	btnCancel.SetCaption("Cancel");

	btnOk.SetOnClick(MDZ_CBK1(MdzDialogEx, OnBtnOkClicked));
	btnCancel.SetOnClick(MDZ_CBK1(MdzDialogEx, OnBtnCancelClicked));

	SetDefaultButton(btnOk);

}

MdzDialogEx::~MdzDialogEx()
{

}

void MdzDialogEx::OnBtnOkClicked()
{
	Close(TRUE);
}

void MdzDialogEx::OnBtnCancelClicked()
{
	Close(FALSE);

}