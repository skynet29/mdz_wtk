// MdzSystem.cpp: implementation of the MdzSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzSystem.h"
#include "MdzFrame.h"
#include <stdio.h>
#include <stdarg.h>


static bShow = TRUE;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzSystem::MdzSystem()
{

}



LONGLONG MdzSystem::GetCurrentTimeMillis()
{
  FILETIME ft;
  SYSTEMTIME st;

   GetSystemTime(&st);              // gets current time
   SystemTimeToFileTime(&st, &ft);  // converts to file time format

  return *((LONGLONG*)&ft) / 10000;
}

MdzSize MdzSystem::GetScreenSize()
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy =  GetSystemMetrics(SM_CYSCREEN);
	return MdzSize(cx, cy);
}

MdzString MdzSystem::GetExePath()
{
	char buffer[1024];
	GetModuleFileName(GetModuleHandle(NULL), buffer, sizeof(buffer));
	LPSTR lpTemp = strrchr(buffer, '\\');
	if (lpTemp)
		*lpTemp = 0;

	return MdzString(buffer);
}

void MdzSystem::FindFile(MdzStrVector &vector, LPSTR strFilter)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(strFilter, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return ;

	do
	{
		vector.Add(FindFileData.cFileName);			
	}
	while (FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
}

MdzString MdzSystem::GetDate()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	return MdzString::Format("%02d/%02d/%04d",
		sysTime.wDay,
		sysTime.wMonth,
		sysTime.wYear);
}

MdzString MdzSystem::GetTime()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	return MdzString::Format("%02d:%02d:%02d",
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond);

}

void MdzSystem::ShowCursor()
{
	if (!bShow)
	{
		::ShowCursor(TRUE);  
		bShow = TRUE;
	}

}

void MdzSystem::HideCursor()
{
	if (bShow)
	{
		::ShowCursor(FALSE);  
		bShow = FALSE;
	}
}



BOOL MdzSystem::RunProcess(LPSTR strCmdLine, BOOL bWaitEnd)
{
	PROCESS_INFORMATION piProcInfo; 
	STARTUPINFO siStartInfo; 
	 	 
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );	 	
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	 
	 
	if (! CreateProcess(NULL, 
		strCmdLine,       // command line 
	   NULL,          // process security attributes 
	   NULL,          // primary thread security attributes 
	   TRUE,          // handles are inherited 
	   CREATE_NO_WINDOW,             // creation flags 
	   NULL,          // use parent's environment 
	   NULL,          // use parent's current directory 
	   &siStartInfo,  // STARTUPINFO pointer 
	   &piProcInfo))  // receives PROCESS_INFORMATION 
		return FALSE;
	
	if (bWaitEnd)
		WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	return TRUE;
}

MdzString MdzSystem::GetShortPath(LPSTR strPath)
{
	char buffer[MAX_PATH];
	GetShortPathName(strPath, buffer, sizeof(buffer));
	return buffer;

}

void MdzSystem::DebugPrint(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buffer[1024];
	vsprintf(buffer, fmt, args);
	va_end(args);
	DWORD dwBytesWritten;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwBytesWritten, NULL);
}

MdzString MdzSystem::GetExeName()
{
	char buffer[1024];
	GetModuleFileName(GetModuleHandle(NULL), buffer, sizeof(buffer));
	LPSTR lpTemp = strrchr(buffer, '\\');
	return MdzString(lpTemp + 1);

}

BOOL MdzSystem::CopyToClipboard(LPSTR strText)
{
	if (!OpenClipboard(MdzFrame::GetMainFrame()->GetHandle()))
		return FALSE;
	EmptyClipboard();
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(strText) + 1);
	char* pBuff = (char*)GlobalLock(hMem);
	strcpy(pBuff, strText);
	GlobalUnlock(hMem);
	SetClipboardData(CF_TEXT, hMem);

	CloseClipboard();
	return TRUE;
}

void MdzSystem::SortVector(MdzVector &vector, MdzSortFunction func)
{
	UINT iCount = vector.GetCount();
	if (iCount < 2)
		return;
	
	MdzObject** pArray = new MdzObject*[iCount];
	for(UINT i = 0; i < iCount; i++)
		pArray[i] = vector.GetAt(i);
	
	BOOL bSwapped;

	do
	{
		bSwapped = FALSE;
		for(i = 0; i < iCount - 1; i++)
		{
			if (func(pArray[i], pArray[i+1]) > 0)
			{
				MdzObject* pTemp = pArray[i];
				pArray[i] = pArray[i+1];
				pArray[i+1] = pTemp;
				bSwapped = TRUE;
			}
		}
	}
	while (bSwapped);

	vector.RemoveAll();
	for(i = 0; i < iCount; i++)
		 vector.Add(pArray[i]);

	delete [] pArray;
}

static int SortFunc(MdzString* pA, MdzString* pB)
{
	return pA->Compare(*pB);
}

void MdzSystem::SortStrVector(MdzStrVector &vector)
{
	SortVector(vector, (MdzSortFunction)SortFunc);
}
