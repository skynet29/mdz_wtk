// MdzVideoStream.h: interface for the MdzVideoStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZVIDEOSTREAM_H__BCE5ED9D_31D1_4AD9_A9A3_53FC46F21E83__INCLUDED_)
#define AFX_MDZVIDEOSTREAM_H__BCE5ED9D_31D1_4AD9_A9A3_53FC46F21E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "vfw.h"
#include "MdzSize.h"	// Added by ClassView

class MdzGraphic;

class DllExport MdzVideoStream  
{
public:
	LONG GetTimeFromFrame(LONG lFrame);
	LONG GetFrameFromTime(LONG lTime);
	LONG GetDuration();
	LONG GetFrameCount();
	MdzSize GetSize();
	void DrawFrame(MdzGraphic& graphic, int x, int y, LONG lFrame);
	void Close();
	BOOL Open(PAVIFILE pFile);
	MdzVideoStream();
	virtual ~MdzVideoStream();
private:
	PAVISTREAM pStream;
	AVISTREAMINFO si;
	PGETFRAME pFrame;
	HDRAWDIB hDrawDib;
};
#endif // !defined(AFX_MDZVIDEOSTREAM_H__BCE5ED9D_31D1_4AD9_A9A3_53FC46F21E83__INCLUDED_)
