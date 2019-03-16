// MdzFindDialog.h: interface for the MdzFindDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZFINDDIALOG_H__0ED94D79_0669_4929_AC57_21A4E756C139__INCLUDED_)
#define AFX_MDZFINDDIALOG_H__0ED94D79_0669_4929_AC57_21A4E756C139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzDialog.h"
#include "MdzTextField.h"
#include "MdzLabel.h"
#include "MdzButton.h"
#include "MdzTextArea.h"

class MdzFindDialog : public MdzDialog  
{
public:
	MdzFindDialog(MdzTextArea& txtArea);
	virtual ~MdzFindDialog();
private:
	void BtnReplace_OnClick();
	void BtnFindNext_OnClick();
	void BtnCancel_OnClick();
	MdzTextField txtFindWhat;
	MdzTextField txtReplaceWidth;
	MdzLabel lblFindWhat;
	MdzLabel lblReplaceWidth;
	MdzButton btnFindNext;
	MdzButton btnReplace;
	MdzButton btnCancel;
	MdzTextArea& txtArea;
	int iCurrentIdx;


protected:
	virtual void OnFocus(UINT bGotFocus);
	virtual void OnCreate();
};

#endif // !defined(AFX_MDZFINDDIALOG_H__0ED94D79_0669_4929_AC57_21A4E756C139__INCLUDED_)
