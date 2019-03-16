// MdzDialogEx.h: interface for the MdzDialogEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDIALOGEX_H__894462AC_8AC0_4447_AAB3_909D0EDA782B__INCLUDED_)
#define AFX_MDZDIALOGEX_H__894462AC_8AC0_4447_AAB3_909D0EDA782B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzDialog.h"

class DllExport MdzDialogEx : public MdzDialog  
{
public:
	MdzDialogEx();
	virtual ~MdzDialogEx();
private:
	void OnBtnCancelClicked();
protected:
	virtual void OnBtnOkClicked();
	MdzButton btnOk;
	MdzButton btnCancel;

};

#endif // !defined(AFX_MDZDIALOGEX_H__894462AC_8AC0_4447_AAB3_909D0EDA782B__INCLUDED_)
