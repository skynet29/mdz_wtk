// MdzVideoStream.cpp: implementation of the MdzVideoStream class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzVideoStream.h"

#include "MdzRect.h"
#include "MdzGraphic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzVideoStream::MdzVideoStream()
{
	pStream = NULL;
	pFrame = NULL;
	hDrawDib = DrawDibOpen();
}

MdzVideoStream::~MdzVideoStream()
{
	DrawDibClose(hDrawDib);
}

BOOL MdzVideoStream::Open(PAVIFILE pFile)
{
	Close();

	HRESULT hr;
	hr = AVIFileGetStream(pFile, &pStream, streamtypeVIDEO, 0);
	if (FAILED(hr))
		return FALSE;

	AVIStreamInfo(pStream, &si, sizeof(si));

	pFrame = AVIStreamGetFrameOpen(pStream, NULL);
	if (!pFrame)
	{
		AVIStreamRelease(pStream);
		pStream = NULL;
		return FALSE;
	}

	return TRUE;
}

void MdzVideoStream::Close()
{
	if (pFrame)
	{
		AVIStreamGetFrameClose(pFrame);
		pFrame = NULL;
	}

	if (pStream)
	{
		AVIStreamRelease(pStream);
		pStream = NULL;
	}
}

void MdzVideoStream::DrawFrame(MdzGraphic &graphic, int x, int y, LONG lFrame)
{
	if (pFrame)
	{
		MdzSize sz = GetSize();

		LPBITMAPINFOHEADER lpBi;
		lpBi = (LPBITMAPINFOHEADER) AVIStreamGetFrame(pFrame, lFrame);

		DrawDibDraw(hDrawDib, graphic.GetHandle(), x, y, sz.cx, sz.cy, lpBi,
			NULL, 0, 0, sz.cx, sz.cy, 0);
	}

}

MdzSize MdzVideoStream::GetSize()
{
	MdzRect rc = *(MdzRect*) &si.rcFrame;
	return MdzSize(rc.Width(), rc.Height());
}

LONG MdzVideoStream::GetFrameCount()
{
	return (pStream) ? si.dwLength : 0;
}

LONG MdzVideoStream::GetDuration()
{
	return AVIStreamSampleToTime(pStream, si.dwLength);
}

LONG MdzVideoStream::GetFrameFromTime(LONG lTime)
{
	return AVIStreamTimeToSample(pStream, lTime);
}

LONG MdzVideoStream::GetTimeFromFrame(LONG lFrame)
{
	return AVIStreamSampleToTime(pStream, lFrame);
}
