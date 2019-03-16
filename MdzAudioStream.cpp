// MdzAudioStream.cpp: implementation of the MdzAudioStream class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzAudioStream.h"


#include "MdzFrame.h"
#include "MdzWindow.h"

#define AUDIO_BUFFER_SIZE 1024

static BOOL TestFunc(MdzEvent& evt, DWORD dwArg)
{
	return (evt.uMsg == MM_WOM_DONE);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzAudioStream::MdzAudioStream()
{
	pStream = NULL;
	hWaveOut = NULL;
	bPlaying = FALSE;
	lpOnEndReached = NULL;
	nbBufferOut = 0;
	lpEvtHandler = new MdzEventHandler(TestFunc,
		MDZ_CBK3(MdzAudioStream, OnWomDone), 0);

	MdzFrame::GetMainFrame()->AddEventHandler(lpEvtHandler);
}

MdzAudioStream::~MdzAudioStream()
{
	delete lpEvtHandler;

	if (lpOnEndReached)
		delete lpOnEndReached;
}

BOOL MdzAudioStream::Open(PAVIFILE pFile)
{
	Close();

	HRESULT hr;
	hr = AVIFileGetStream(pFile, &pStream, streamtypeAUDIO, 0);
	if (FAILED(hr))
		return FALSE;

	AVIStreamInfo(pStream, &si, sizeof(si));

	LONG cbFormat;
	AVIStreamFormatSize(pStream, 0, &cbFormat);
	LPWAVEFORMATEX lpFormat = (LPWAVEFORMATEX) malloc(cbFormat);
	AVIStreamReadFormat(pStream, 0, lpFormat, &cbFormat);
	lSamplePerSec = lpFormat->nSamplesPerSec;

	HWND hWnd = MdzFrame::GetMainFrame()->GetHandle();

	MMRESULT ret = waveOutOpen(&hWaveOut, WAVE_MAPPER, lpFormat, (DWORD) hWnd, 0, CALLBACK_WINDOW);
	free(lpFormat);
	if (ret != 0)
		return FALSE;

	for (nbBuffer = 0; nbBuffer < 16; nbBuffer++)
	{
		LPWAVEHDR lpwh = &buffers[nbBuffer];

		lpwh->lpData = (LPSTR)malloc(AUDIO_BUFFER_SIZE);
		lpwh->dwBufferLength = AUDIO_BUFFER_SIZE;
		lpwh->dwFlags = WHDR_DONE;
		MMRESULT ret = waveOutPrepareHeader(hWaveOut, lpwh, sizeof(WAVEHDR));
		if (ret != 0)
		{
			free(lpwh->lpData);
			break;
		}
	}

	iCurBuffer = 0;
	nbBufferOut = 0;

	return TRUE;
}

LPWAVEHDR MdzAudioStream::GetBuffer()
{
	LPWAVEHDR lpwh = &buffers[iCurBuffer];
	iCurBuffer = (iCurBuffer + 1) % nbBuffer;
	return lpwh;

}

void MdzAudioStream::OnWomDone(MdzEvent &evt)
{
	--nbBufferOut;

	
	if (bPlaying)
	{
		if (nbBufferOut == 0)
		{
			bPlaying = FALSE;
			waveOutReset(hWaveOut);
			if (lpOnEndReached)
				lpOnEndReached->Fire();
		}
		else
			PlaySamples();
	}
	else if (nbBufferOut == 0)
		PostQuitMessage(0);
	

}

void MdzAudioStream::PlaySamples()
{
	while (nbBufferOut < nbBuffer)
	{
		LONG lSamplesToPlay = min(si.dwLength - lCurrentSample, AUDIO_BUFFER_SIZE / si.dwSampleSize);

		if (lSamplesToPlay == 0)
			break;
	
		LPWAVEHDR lpwh = GetBuffer();
		LONG lRead;

		AVIStreamRead(pStream, lCurrentSample, lSamplesToPlay,
		   lpwh->lpData,
		   AUDIO_BUFFER_SIZE,
		   (LONG*)&lpwh->dwBufferLength,
		   &lRead);

		lCurrentSample += lRead;
		MMRESULT ret = waveOutWrite(hWaveOut, lpwh, sizeof(WAVEHDR));
		nbBufferOut++;

	}
}

void MdzAudioStream::Close()
{
	Stop();

	if (hWaveOut) 
	{
	while (nbBuffer > 0) 
	{
		 LPWAVEHDR lpwh = &buffers[--nbBuffer];

		 waveOutUnprepareHeader(hWaveOut, lpwh, sizeof(WAVEHDR));
		 free(lpwh->lpData);
	}

	waveOutClose(hWaveOut);
	hWaveOut = NULL;	
	}		

	if (pStream)
	{
	AVIStreamRelease(pStream);
	pStream = NULL;
	}	
}

void MdzAudioStream::Play(LONG lTime)
{
	lStartTime = lTime;

	lCurrentSample = AVIStreamTimeToSample(pStream, lTime);
	bPlaying = TRUE;
	//waveOutReset(hWaveOut);
	PlaySamples();

}

LONG MdzAudioStream::GetElapsedTime()
{
   MMTIME	mmtime;

	mmtime.wType = TIME_SAMPLES;
	waveOutGetPosition(hWaveOut, &mmtime, sizeof(mmtime));

	if (mmtime.wType == TIME_SAMPLES)
		return lStartTime + MulDiv(mmtime.u.sample, 1000, lSamplePerSec);

	return 0;
}





LONG MdzAudioStream::GetDuration()
{
	return (pStream) ? AVIStreamSampleToTime(pStream, si.dwLength) : 0;
}

void MdzAudioStream::Stop()
{
	waveOutReset(hWaveOut);
	bPlaying = FALSE;	
	if (nbBufferOut > 0)
		MdzWindow::MessageLoop();
		
}

BOOL MdzAudioStream::IsPlaying()
{
	return bPlaying;
}

void MdzAudioStream::SetOnEndReached(MdzCbk1 *lpFunc)
{
	if (lpOnEndReached)
		delete lpOnEndReached;
	lpOnEndReached = lpFunc;
}
