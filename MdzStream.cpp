// MdzStream.cpp: implementation of the MdzStream class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzStream.h"
#include "MdzString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT MdzStream::K_READ	= 0;
const UINT MdzStream::K_WRITE	= 1;

MdzStream::MdzStream()
{
	lpFile = NULL;
}

MdzStream::~MdzStream()
{
	Close();
}



void MdzStream::Close()
{
	if (lpFile)
	{	
		fflush(lpFile);
		fclose(lpFile);
		lpFile = NULL;
	}
}

BOOL MdzStream::Open(LPSTR lpFileName, int iMode)
{
	if (!lpFileName)
		return FALSE;

	switch (iMode)
	{
	case K_READ:
	case K_WRITE:
		break;
	default:
		return FALSE;
	}

	lpFile = fopen(lpFileName, (iMode == K_READ) ? "rb" : "wb");
	return (lpFile != NULL);
}

void MdzStream::Read(LPVOID lpBuffer, int iBuffSize)
{
	int iByteRead = fread(lpBuffer, iBuffSize, 1, lpFile);
	if (iByteRead != 1)
		throw MdzString("Read error");
}

void MdzStream::Write(LPVOID lpBuffer, int iBuffSize)
{
	int iBytesWritten = fwrite(lpBuffer, iBuffSize, 1, lpFile);
	if (iBytesWritten != 1)
		throw MdzString("Write error");

}

FILE* MdzStream::GetDesc()
{
	return lpFile;
}

ULONG MdzStream::GetFileSize()
{
	long cur = ftell(lpFile);
	fseek(lpFile, 0, SEEK_END);
	long ret = ftell(lpFile);
	fseek(lpFile, cur, SEEK_SET);
	return ret;
}

MdzString MdzStream::ReadText()
{
	MdzString strText;
	int fileSize = GetFileSize();
	if (fileSize > 0)
	{
		strText.Alloc(fileSize + 1);
		Read(strText, fileSize);
		((LPSTR) strText)[fileSize] = 0;
	}
	return strText;
}

void MdzStream::WriteText(LPSTR strText)
{
	if (strText && strlen(strText) > 0)
		Write(strText, strlen(strText));
}
