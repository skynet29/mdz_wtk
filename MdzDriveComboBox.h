// MdzDriveComboBox.h: interface for the MdzDriveComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDRIVECOMBOBOX_H__A9D8D3E8_A77C_4862_A673_6FAB5F44C931__INCLUDED_)
#define AFX_MDZDRIVECOMBOBOX_H__A9D8D3E8_A77C_4862_A673_6FAB5F44C931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzComboBox.h"
#include "MdzString.h"	// Added by ClassView

class DllExport MdzDriveComboBox : public MdzComboBox  
{
public:
	MdzDriveComboBox();

	MdzString
	GetDrive();

	virtual void
	Create();

	virtual ~MdzDriveComboBox();

};

#endif // !defined(AFX_MDZDRIVECOMBOBOX_H__A9D8D3E8_A77C_4862_A673_6FAB5F44C931__INCLUDED_)
