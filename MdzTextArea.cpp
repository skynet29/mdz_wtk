// MdzTextArea.cpp: implementation of the MdzTextArea class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzTextArea.h"
#include "MdzWindow.h"
#include "MdzFindDialog.h"
#include "MdzStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzTextArea::MdzTextArea()
{
	lpWnd->dwStyle = WS_CHILD | WS_VISIBLE | ES_MULTILINE |
		ES_AUTOVSCROLL | WS_VSCROLL | ES_NOHIDESEL;
	lpWnd->dwStyleEx = WS_EX_CLIENTEDGE;
	lpWnd->lpClassName = "EDIT";
	lpWnd->OnCtlColor = MDZ_CBK3(MdzTextArea, OnCtlColor);
	lpWnd->OnCommand = MDZ_CBK3(MdzTextArea, OnCommand);
	//lpWnd->OnChar = MDZ_CBK6(MdzTextArea, OnChar);
	iTabSize = 8;
	lpOnSelChange = NULL;
	lpOnFocus = NULL;
	lpOnChar = NULL;
}

MdzTextArea::~MdzTextArea()
{
	if (lpOnSelChange != NULL)
		delete lpOnSelChange;

	if (lpOnFocus != NULL)
		delete lpOnFocus;

}

MdzString MdzTextArea::GetText()
{
	return lpWnd->GetText();
}

void MdzTextArea::SetText(LPSTR strText)
{
	lpWnd->SetText(strText);
}

void MdzTextArea::SetEditable(BOOL bIsEditable)
{
	lpWnd->ModifyStyle(ES_READONLY, !bIsEditable);
}

void MdzTextArea::Append(LPSTR strText)
{

	SetText(GetText() + MdzString(strText));
}

void MdzTextArea::Copy()
{
	lpWnd->SendMsg(WM_COPY);
}

void MdzTextArea::Paste()
{
	lpWnd->SendMsg(WM_PASTE);

}

void MdzTextArea::Cut()
{
	lpWnd->SendMsg(WM_CUT);

}

MdzString MdzTextArea::GetSelText()
{
	DWORD dwStart, dwStop;

	lpWnd->SendMsg(EM_GETSEL, (WPARAM) &dwStart, (LPARAM) &dwStop);

	MdzString ret;

	if (dwStart != dwStop)
	{
		MdzString str = GetText();
		LPSTR lpTemp = (LPSTR) str;
		lpTemp[dwStop] = 0;
		ret = MdzString(&lpTemp[dwStart]);
	}

	return ret;
}

UINT MdzTextArea::GetLineCount()
{
	return lpWnd->SendMsg(EM_GETLINECOUNT);
}

MdzString MdzTextArea::GetLineAt(UINT iIndex)
{
	static WORD buffer[64];
	buffer[0] = sizeof(buffer);

	UINT length = lpWnd->SendMsg(EM_GETLINE, iIndex, (LPARAM) buffer);
	MdzString ret;
	if (length > 0)
	{
		ret.Alloc(length + 1);
		LPSTR strBuff = (LPSTR) ret;
		memcpy(strBuff, buffer, length);
		strBuff[length] = 0;		
	}
	return ret;
}

BOOL MdzTextArea::IsModified()
{
	return (lpWnd->SendMsg(EM_GETMODIFY) != 0);
}

void MdzTextArea::ResetModifiedFlag()
{
	lpWnd->SendMsg(EM_SETMODIFY, FALSE);
}

void MdzTextArea::Create()
{
	MdzCtrl::Create();

	int tab = iTabSize * 4;

	lpWnd->SendMsg(EM_SETTABSTOPS, 1, (LPARAM) &tab);
}

void MdzTextArea::SetTabSize(UINT iTabSize)
{
	MEMBER_SET(iTabSize);
}

void MdzTextArea::SetSelection(int iStartIndex, int iStopIndex)
{
	lpWnd->SendMsg(EM_SETSEL, iStartIndex, iStopIndex);
}

void MdzTextArea::ReplaceSelection(LPSTR strText)
{
	lpWnd->SendMsg(EM_REPLACESEL, TRUE, (LPARAM) strText);
}

int MdzTextArea::GetStartIndex()
{
	DWORD dwStart, dwStop;

	lpWnd->SendMsg(EM_GETSEL, (WPARAM) &dwStart, (LPARAM) &dwStop);
	return dwStart;
}

void MdzTextArea::ShowFindDialog()
{
	MdzFindDialog dlg(*this);
	dlg.Execute();
}

BOOL MdzTextArea::LoadFromFile(LPSTR strFileName)
{
	MdzStream stream;
	if (!stream.Open(strFileName, MdzStream::K_READ))
		return FALSE;

	SetText(stream.ReadText());
	return TRUE;

}

BOOL MdzTextArea::CanPaste()
{
	return IsClipboardFormatAvailable(CF_TEXT);
}

void MdzTextArea::SetOnFocus(MdzCbk6 *pFunc)
{
	if (lpOnFocus != NULL)
		delete lpOnFocus;
	lpOnFocus = pFunc;
}

void MdzTextArea::SetOnSelChange(MdzCbk1 *pFunc)
{
	if (lpOnSelChange != NULL)
		delete lpOnSelChange;
	lpOnSelChange = pFunc;
}

void MdzTextArea::OnCtlColor(MdzEvent &event)
{
	event.ProcessDefault(GetHandle());
	if (lpOnSelChange)
		lpOnSelChange->Fire();

}

void MdzTextArea::OnCommand(MdzEvent &evt)
{
	if (HIWORD(evt.wParam) == EN_SETFOCUS && lpOnFocus != NULL)
		lpOnFocus->Fire(TRUE);

	if (HIWORD(evt.wParam) == EN_KILLFOCUS && lpOnFocus != NULL)
		lpOnFocus->Fire(FALSE);


}

int MdzTextArea::GetIndexFromLine(int iLineNumber)
{
	return lpWnd->SendMsg(EM_LINEINDEX, iLineNumber);
}

void MdzTextArea::SelectLine(int iLineNumber)
{
	int iPos = GetIndexFromLine(iLineNumber);
	int iLength = GetLineAt(iLineNumber).GetLength();
	SetSelection(iPos, iPos+iLength);

}

void MdzTextArea::ScrollToEnd()
{
	lpWnd->SendMsg(EM_LINESCROLL , 0, GetLineCount());

}

//DEL void MdzTextArea::OnChar(UINT iChar)
//DEL {
//DEL 	if (lpOnChar)
//DEL 		lpOnChar->Fire(iChar);
//DEL }

void MdzTextArea::SetOnChar(MdzCbk6 *lpFunc)
{
	if (lpWnd->OnChar)
		delete lpWnd->OnChar;
	lpWnd->OnChar = lpFunc;
}

void MdzTextArea::SetOnEnter(MdzCbk1* lpFunc)
{
	if (lpWnd->OnEnter)
		delete lpWnd->OnEnter;
	lpWnd->OnEnter = lpFunc;

}

void MdzTextArea::SetOnLButtonDblClick(MdzCbk2* lpFunc)
{
	if (lpWnd->OnLButtonDblClk)
		delete lpWnd->OnLButtonDblClk;
	lpWnd->OnLButtonDblClk = lpFunc;

}

BOOL MdzTextArea::GetPosFromIndex(UINT iIndex, MdzPoint &pt)
{
	LRESULT lResult = lpWnd->SendMsg(EM_POSFROMCHAR, iIndex);
	if (lResult < 0)
		return FALSE;
	pt.x = LOWORD(lResult);
	pt.y = HIWORD(lResult);
	return TRUE;

}

UINT MdzTextArea::GetIndexFromPos(int x, int y)
{
	return LOWORD(lpWnd->SendMsg(EM_CHARFROMPOS, 0, MAKELONG(x, y)));

}

UINT MdzTextArea::GetLineFromIndex(UINT iIndex)
{
	return lpWnd->SendMsg(EM_LINEFROMCHAR, iIndex);
}

BOOL MdzTextArea::IsBeginOfLine(UINT iIndex)
{
	int iLine = GetLineFromIndex(iIndex);
	int idx = GetIndexFromLine(iLine);
	return (iIndex == idx);

}

BOOL MdzTextArea::IsEndOfLine(UINT iIndex)
{
	int iLine = GetLineFromIndex(iIndex);
	int idx = GetIndexFromLine(iLine) + GetLineAt(iLine).GetLength();
	return (iIndex == idx);

}
