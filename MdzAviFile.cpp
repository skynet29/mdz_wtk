// MdzAviFile.cpp: implementation of the MdzAviFile class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzAviFile.h"
#include "MdzAudioStream.h"
#include "MdzVideoStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzAviFile::MdzAviFile()
{
	AVIFileInit();
	pFile = NULL;
}

MdzAviFile::~MdzAviFile()
{
	AVIFileExit();

}

BOOL MdzAviFile::Open(LPSTR strFileName)
{
	Close();

	HRESULT hr;
	hr = AVIFileOpen(&pFile, strFileName, OF_SHARE_DENY_WRITE, NULL);
	if (FAILED(hr))
		return FALSE;

	return TRUE;
}

void MdzAviFile::Close()
{
	if (pFile)
	{
		AVIFileRelease(pFile);
		pFile = NULL;
	}
}

BOOL MdzAviFile::GetAudioStream(MdzAudioStream &audioStream)
{
	return audioStream.Open(pFile);
}

BOOL MdzAviFile::GetVideoStream(MdzVideoStream &videoStream)
{
	return videoStream.Open(pFile);

}
