// $Id: CAviFile.h,v 1.1 2008/03/29 03:13:10 samn Exp $ 
// CAviFile.h: interface for the CAviFile class.
// http://homepages.msn.com/RedmondAve/darrennix
// darrennix@msn.com
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAVIFILE_H__A0BF6284_6EA6_11D3_84CE_868B4118D102__INCLUDED_)
#define AFX_CAVIFILE_H__A0BF6284_6EA6_11D3_84CE_868B4118D102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_AUDIO_STREAMS 5
#define MAX_VIDEO_STREAMS 5

#include <windowsx.h>
#include <mmsystem.h>
#include <vfw.h>
//#include <memory.h>
//#include <commdlg.h>
//#include <mmreg.h>
//#include <msacm.h>


class CAviFile  
{
public:
	CAviFile();
	virtual ~CAviFile();
	void Release();

	bool IsOpen(){ return m_bIsOpen; }
	bool Open(LPCSTR lpszFileName);

	int GetAudioStreamCount();
	int GetVideoStreamCount();
	LPWAVEFORMAT GetAudioFormat(UINT nStreamNum);
	LPBITMAPINFO GetVideoFormat(UINT nStreamNum);

	LPBYTE ExtractAudioStream(UINT nStreamNum);

	bool StartVideoRetrieve(UINT nStreamNum);

	// In these functions:
	//	NULL in last param means no more frames.
	//  Frame is only valid until the next
	//  call of one of these functions, or EndVideoRetrieve.
	void GetVideoFrameAtTime(UINT nStreamNum, LONG lTimeInMilliSec, LPBITMAPINFOHEADER *ppbi);
	void GetVideoFrame(UINT nStreamNum, LONG lFrame, LPBITMAPINFOHEADER *ppbi);

	void GetCurrentFrame(LPBITMAPINFOHEADER* ppbi){ return GetVideoFrame(m_iCurrentStream,m_iCurrentFrame[m_iCurrentStream],ppbi); }

	bool EndVideoRetrieve(UINT nStreamNum);

	LONG VideoEndTime(){ return m_lVideoEndTime[m_iCurrentStream]; }
	int CurrentFrame(){ return m_iCurrentFrame[m_iCurrentStream]; }
	int FirstFrame(){ return m_iFirstFrame[m_iCurrentStream]; }
	int LastFrame(){ return m_iLastFrame[m_iCurrentStream]; }
	int CurrentStream(){ return m_iCurrentStream; }
	bool GoToFrame(int iFrame)
	{
		if(iFrame>=m_iFirstFrame[m_iCurrentStream] &&
		   iFrame<m_iLastFrame[m_iCurrentStream])
		{
			m_iCurrentFrame[m_iCurrentStream]=iFrame;
			return true;
		}
		return false;
	}
	
protected:
	void Init();
	void FindStreams();
	bool DetermineAudioFormats();
	bool DetermineVideoFormats();

	int m_iCurrentStream;
	int m_iFirstFrame[MAX_VIDEO_STREAMS];
	int m_iLastFrame[MAX_VIDEO_STREAMS];
	int m_iCurrentFrame[MAX_VIDEO_STREAMS];
	bool m_bIsOpen;

	PAVIFILE m_pAviFile;

	PAVISTREAM
		m_pAudioStreams[MAX_AUDIO_STREAMS],
		m_pVideoStreams[MAX_VIDEO_STREAMS];

	int m_nNumAudioStreams,
		m_nNumVideoStreams;

	LPWAVEFORMAT m_pAudioFormats[MAX_AUDIO_STREAMS];
	LPBYTE m_pAudioData[MAX_AUDIO_STREAMS];

	LPBITMAPINFO m_pVideoFormats[MAX_VIDEO_STREAMS];
	PGETFRAME m_pVideoPGF[MAX_VIDEO_STREAMS];
	LONG m_lVideoEndTime[MAX_VIDEO_STREAMS];
};

#endif // !defined(AFX_CAVIFILE_H__A0BF6284_6EA6_11D3_84CE_868B4118D102__INCLUDED_)
