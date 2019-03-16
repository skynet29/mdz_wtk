// MdzTextArea.h: interface for the MdzTextArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTEXTAREA_H__4319DC23_3CDE_4035_A72F_4C68123B7DEE__INCLUDED_)
#define AFX_MDZTEXTAREA_H__4319DC23_3CDE_4035_A72F_4C68123B7DEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"	// Added by ClassView
#include "MdzCbk6.h"
#include "MdzCbk1.h"
#include "MdzCbk3.h"
#include "MdzCbk2.h"

class DllExport MdzTextArea : public MdzCtrl  
{
public:
	BOOL IsEndOfLine(UINT iIndex);
	BOOL IsBeginOfLine(UINT iIndex);
	UINT GetLineFromIndex(UINT iIndex);
	UINT GetIndexFromPos(int x, int y);
	BOOL GetPosFromIndex(UINT iIndex, MdzPoint& pt);
	void SetOnLButtonDblClick(MdzCbk2* lpFunc);
	void SetOnEnter(MdzCbk1* lpFunc);
	void SetOnChar(MdzCbk6* lpFunc);
	void ScrollToEnd();
	void SelectLine(int iLineNumber);
	int GetIndexFromLine(int iLineNumber);
	void SetOnSelChange(MdzCbk1* pFunc);
	void SetOnFocus(MdzCbk6* pFunc);
	BOOL CanPaste();
	BOOL LoadFromFile(LPSTR strFileName);
	MdzTextArea();

	void
	ShowFindDialog();

	int
	GetStartIndex();

	void
	ReplaceSelection(LPSTR strText);

	void
	SetSelection(int iStartIndex, int iStopIndex);
	
	void
	SetTabSize(UINT iTabSize);

	void
	ResetModifiedFlag();
	
	BOOL
	IsModified();

	MdzString
	GetLineAt(UINT iIndex);
	
	UINT
	GetLineCount();

	void
	SetEditable(BOOL bIsEditable);
	
	void
	SetText(LPSTR strText);

	MdzString
	GetText();
	
	MdzString
	GetSelText();

	void
	Cut();
	
	void
	Paste();
	
	void
	Copy();
	
	void
	Append(LPSTR strText);

	virtual void
	Create();

	virtual ~MdzTextArea();
private:
	void OnCommand(MdzEvent& evt);
	void OnCtlColor(MdzEvent& event);
	UINT iTabSize;
	MdzCbk1* lpOnSelChange;
	MdzCbk6* lpOnFocus;
	MdzCbk6* lpOnChar;
};

#endif // !defined(AFX_MDZTEXTAREA_H__4319DC23_3CDE_4035_A72F_4C68123B7DEE__INCLUDED_)
