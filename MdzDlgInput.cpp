// MdzDlgInput.cpp: implementation of the MdzDlgInput class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzDlgInput.h"
#include "MdzLayout.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzDlgInput::MdzDlgInput()
{
	SetTitle("Input");

	MdzLayout layout(this, 10, 10);
	layout.Add(label, 200, 20);
	layout.Add(textField, 200, 20, MdzLayout::K_NEXT_LINE, 0);
	layout.Add(btnOk, 60, 25, MdzLayout::K_BOTTOM_RIGHT);
	layout.Add(btnCancel, 60, 25, MdzLayout::K_LEFT);

	label.SetText("Enter a value :");
	label.SetAlignment(MdzLabel::K_LEFT);

	Pack(10, 10);
}

MdzDlgInput::~MdzDlgInput()
{

}



void MdzDlgInput::SetLabel(LPSTR strText)
{
	label.SetText(strText);
}

void MdzDlgInput::OnFocus(UINT bGotFocus)
{
	textField.RequestFocus();
}

MdzString MdzDlgInput::GetText()
{
	return textField.GetText();
}



void MdzDlgInput::SetText(LPSTR strText)
{
	textField.SetText(strText);
}
