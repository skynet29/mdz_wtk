// MdzFindDialog.cpp: implementation of the MdzFindDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzFindDialog.h"
#include "MdzLayout.h"
#include "MdzStdDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzFindDialog::MdzFindDialog(MdzTextArea& txtArea) : txtArea(txtArea)
{
	SetTitle("Replace");
	MdzLayout layout(this, 10, 10);
	layout.Add(lblFindWhat, 150, 20);
	layout.Save();

	layout.Add(txtFindWhat, 150, 20, MdzLayout::K_NEXT_LINE, 0);
	layout.Add(lblReplaceWidth, 150, 20,  MdzLayout::K_NEXT_LINE);
	layout.Add(txtReplaceWidth, 150, 20, MdzLayout::K_NEXT_LINE, 0);

	layout.Restore();
	layout.Add(btnFindNext, 60, 25, MdzLayout::K_RIGHT, 30);
	layout.Add(btnReplace, 60, 25, MdzLayout::K_BOTTOM_LEFT);
	layout.Add(btnCancel, 60, 25, MdzLayout::K_BOTTOM_LEFT);

	btnFindNext.SetCaption("Find Next");
	btnReplace.SetCaption("Replace");
	btnCancel.SetCaption("Cancel");
	lblFindWhat.SetText("Find what:");
	lblReplaceWidth.SetText("Replace with:");

	btnCancel.SetOnClick(MDZ_CBK1(MdzFindDialog, BtnCancel_OnClick));
	btnFindNext.SetOnClick(MDZ_CBK1(MdzFindDialog, BtnFindNext_OnClick));
	btnReplace.SetOnClick(MDZ_CBK1(MdzFindDialog, BtnReplace_OnClick));

	SetDefaultButton(btnFindNext);
	Pack(10, 10);
}

MdzFindDialog::~MdzFindDialog()
{

}

void MdzFindDialog::BtnCancel_OnClick()
{
	Close(TRUE);
}

void MdzFindDialog::BtnFindNext_OnClick()
{
	MdzString strFindText = txtFindWhat.GetText();
	iCurrentIdx = txtArea.GetText().GetIndexOf(strFindText, iCurrentIdx + 1);
	if (iCurrentIdx < 0)
		MdzStdDialog::ShowMessage(MdzString::Format("Unable to find \"%s\"",
			(LPSTR) strFindText));
	else
		txtArea.SetSelection(iCurrentIdx, iCurrentIdx + strFindText.GetLength());

}

void MdzFindDialog::BtnReplace_OnClick()
{
	txtArea.ReplaceSelection(txtReplaceWidth.GetText());
}

void MdzFindDialog::OnCreate()
{
	MdzDialog::OnCreate();

	if (txtArea.GetSelText().GetLength())
	{
		txtFindWhat.SetText(txtArea.GetSelText());
		txtFindWhat.Select();
	}
	iCurrentIdx = txtArea.GetStartIndex();
}

void MdzFindDialog::OnFocus(UINT bGotFocus)
{
	txtFindWhat.RequestFocus();
}
