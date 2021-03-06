// $Id: AviReader.h,v 1.2 2008/04/24 23:41:46 samn Exp $ 
#ifndef AVI_READER_H
#define AVI_READER_H

#define DRAWDIB_INCLUDE_STRETCHDIB 
#include <vfw.h> // Header File For Video For Windows

typedef unsigned char byte;

//this class opens & reads avi files into bitmaps
class AVIReader
{
	AVIReader& operator=(const AVIReader& oR);
	AVIReader(const AVIReader& oR);

	static bool bInitLib;
	static int iReaders;

	bool m_bOpen;

	// First Frame Of The Stream
	int m_iFirstFrame;
	// Last Frame Of The Stream
	int m_iLastFrame;
	// current frame
	int m_iCurrFrame;
	PAVIFILE m_pAVIFile;
	AVIFILEINFO m_oFileInfo;
	// Pointer To A Structure Containing Stream Info
	AVISTREAMINFO m_oStreamInfo;
	// Handle To An Open Stream
	PAVISTREAM m_pAVIStream;
	// Pointer To A GetFrame Object
	PGETFRAME m_pGetFrame;
	// Header Information For DrawDibDraw Decoding
	BITMAPINFOHEADER	bmih;
	// Video Width
	int m_iWidth;
	// Video Height
	int m_iHeight;
	// Will Hold Rough Milliseconds Per Frame
	double m_dMPF;
	// Handle For Our Dib
	HDRAWDIB m_Hdd;
	// Handle To A Device Dependant Bitmap
	HBITMAP m_hBitmap;
public:
	bool Open(const char* fname);
	bool Close();
	LPBITMAPINFOHEADER GetFrame(int iFrame);
	LPBITMAPINFOHEADER GetCurrentFrame();
	int FirstFrame();
	int LastFrame();
	int CurrentFrame();
	bool GoToFrame(int iFrame);
	bool FreeFrame(byte*& pFrame);
	AVIReader();
	virtual ~AVIReader();
	int Width();
	int Height();
	double MSPerFrame();
	bool IsOpen();
};

#endif
