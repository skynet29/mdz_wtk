// MdzAviFile.h: interface for the MdzAviFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZAVIFILE_H__3DC2E29C_1D9E_4E75_A7C2_5B7D9DD4C0DC__INCLUDED_)
#define AFX_MDZAVIFILE_H__3DC2E29C_1D9E_4E75_A7C2_5B7D9DD4C0DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "vfw.h"

class MdzAudioStream;
class MdzVideoStream;

class DllExport MdzAviFile  
{
public:
	BOOL GetVideoStream(MdzVideoStream& videoStream);
	BOOL GetAudioStream(MdzAudioStream& audioStream);
	void Close();
	BOOL Open(LPSTR strFileName);
	MdzAviFile();
	virtual ~MdzAviFile();
private:
	PAVIFILE pFile;
};

#endif // !defined(AFX_MDZAVIFILE_H__3DC2E29C_1D9E_4E75_A7C2_5B7D9DD4C0DC__INCLUDED_)
