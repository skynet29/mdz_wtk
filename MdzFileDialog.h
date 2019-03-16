// MdzFileDialog.h: interface for the MdzFileDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZFILEDIALOG_H__8B7012D5_81A4_4761_A6ED_CA6EAECCECBA__INCLUDED_)
#define AFX_MDZFILEDIALOG_H__8B7012D5_81A4_4761_A6ED_CA6EAECCECBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MdzCtrl.h"
#include "MdzString.h"	// Added by ClassView

class DllExport MdzFileDialog  
{
public:
	void AddFilter(LPSTR strName, LPSTR strFilterExtention);
	MdzFileDialog();

	virtual ~MdzFileDialog();

	BOOL
	ShowSave();
	
	BOOL
	ShowOpen();

	MdzString
	GetFullPathName();

	MdzString
	GetCurrentDirectory();

	MdzString
	GetFileName();

	void
	SetFileName(LPSTR strFileName);

	void
	SetInitDirectory(LPSTR strInitDir);

	void
	SetDefaultExtension(LPSTR strDefaultExt);

    
private:
	BOOL Execute(int iOption);
	char strFileName[256];
	MdzString strDefaultExt;
	MdzString strFilter;
	MdzString strInitDir;


};

#endif // !defined(AFX_MDZFILEDIALOG_H__8B7012D5_81A4_4761_A6ED_CA6EAECCECBA__INCLUDED_)
