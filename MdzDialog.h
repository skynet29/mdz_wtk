// MdzDialog.h: interface for the MdzDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDIALOG_H__233CF5BE_95E6_45EC_A1C2_9AC027422057__INCLUDED_)
#define AFX_MDZDIALOG_H__233CF5BE_95E6_45EC_A1C2_9AC027422057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzContainer.h"
#include "MdzButton.h"	// Added by ClassView

class MdzEvent;
class MdzButton;

class DllExport MdzDialog : public MdzContainer  
{
public:
	MdzDialog();


	void
	SetTitle(LPSTR strTitle);

	void
	Close(int retCode);

	int
	Execute();

	void
	SetDefaultButton(MdzButton& button);

	virtual ~MdzDialog();

	virtual void
	OnFocus(UINT bGotFocus);
private:
	void OnCommand(MdzEvent& evt);
	MdzButton* lpDefaultBtn;

};

#endif // !defined(AFX_MDZDIALOG_H__233CF5BE_95E6_45EC_A1C2_9AC027422057__INCLUDED_)
