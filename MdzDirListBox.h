// MdzDirListBox.h: interface for the MdzDirListBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZDIRLISTBOX_H__A5332469_35BB_4AF9_BF0E_C6CF0D0C2D59__INCLUDED_)
#define AFX_MDZDIRLISTBOX_H__A5332469_35BB_4AF9_BF0E_C6CF0D0C2D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzListBox.h"
#include "MdzString.h"	// Added by ClassView

class DllExport MdzDirListBox : public MdzListBox  
{
public:
	MdzDirListBox();

	void
	SetDrive(LPSTR strDrive);

	MdzString
	GetPath();

	virtual void
	Create();

	virtual ~MdzDirListBox();
private:
	void UpdatePath();
	MdzString strPath;
protected:
	virtual void OnDblClick();

};

#endif // !defined(AFX_MDZDIRLISTBOX_H__A5332469_35BB_4AF9_BF0E_C6CF0D0C2D59__INCLUDED_)
