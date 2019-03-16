// MdzSystem.h: interface for the MdzSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSYSTEM_H__6C189985_0B39_44E1_876C_0894B4FAFD53__INCLUDED_)
#define AFX_MDZSYSTEM_H__6C189985_0B39_44E1_876C_0894B4FAFD53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "MdzSize.h"
#include "MdzString.h"	// Added by ClassView
#include "MdzVector.h"

#define TRACE MdzSystem::DebugPrint

typedef int (*MdzSortFunction)(void*, void*);

class DllExport MdzSystem  
{
public:
	static void SortStrVector(MdzStrVector& vector);
	static void SortVector(MdzVector& vector, MdzSortFunction func);
	static BOOL CopyToClipboard(LPSTR strText);
	static MdzString GetExeName();
	static void DebugPrint(char* fmt, ...);
	static MdzString GetShortPath(LPSTR strPath);
	static BOOL RunProcess(LPSTR strCmdLine, BOOL bWaitEnd = FALSE);

	static void
	HideCursor();
	
	static void
	ShowCursor();

	static MdzString
	GetTime();

	static MdzString
	GetDate();

	static void
	FindFile(MdzStrVector& vector, LPSTR strFilter);
	
	static MdzString
	GetExePath();
	
	static MdzSize
	GetScreenSize();
	
	static LONGLONG
	GetCurrentTimeMillis();
private:
	MdzSystem();

};

#endif // !defined(AFX_MDZSYSTEM_H__6C189985_0B39_44E1_876C_0894B4FAFD53__INCLUDED_)
