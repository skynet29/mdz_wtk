// MdzAudioStream.h: interface for the MdzAudioStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZAUDIOSTREAM_H__27E50F1B_2400_4802_9A66_16EDBC9135E4__INCLUDED_)
#define AFX_MDZAUDIOSTREAM_H__27E50F1B_2400_4802_9A66_16EDBC9135E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzTypes.h"
#include "vfw.h"

class MdzEvent;
class MdzCbk1;
class MdzEventHandler;

class DllExport MdzAudioStream  
{
public:
	void SetOnEndReached(MdzCbk1* lpFunc);
	BOOL IsPlaying();
	void Stop();
	LONG GetDuration();
	LONG GetElapsedTime();
	void Play(LONG lTime);
	void Close();
	BOOL Open(PAVIFILE pFile);
	MdzAudioStream();
	virtual ~MdzAudioStream();
private:
	void PlaySamples();
	void OnWomDone(MdzEvent &evt);
	LPWAVEHDR GetBuffer();
	PAVISTREAM pStream;
	HWAVEOUT hWaveOut;
	WAVEHDR buffers[16];
	int nbBuffer;
	AVISTREAMINFO si;
	LONG lCurrentSample;
	LONG lSamplePerSec;
	int nbBufferOut;
	int iCurBuffer;
	BOOL bPlaying;
	LONG lStartTime;
	MdzCbk1* lpOnEndReached;
	MdzEventHandler* lpEvtHandler;
};

#endif // !defined(AFX_MDZAUDIOSTREAM_H__27E50F1B_2400_4802_9A66_16EDBC9135E4__INCLUDED_)
