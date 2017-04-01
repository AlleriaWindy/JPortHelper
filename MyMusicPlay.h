// MyMusicPlay.h: interface for the MyMusicPlay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMUSICPLAY_H__3F6A6F3E_0FCB_4A69_B577_926A7B8F0AD6__INCLUDED_)
#define AFX_MYMUSICPLAY_H__3F6A6F3E_0FCB_4A69_B577_926A7B8F0AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MPB_Playing 0
#define MPB_Buffering 1

#include "Lcylib.h"

typedef union MyNote
{
	UINT16 data16;
	UCHAR data8[2];
	struct  
	{
		UCHAR Length:4;
		UCHAR Volume:4;
		
		UCHAR Name:3;
		UCHAR Res:1;
		UCHAR Group:3;
		UCHAR Sharp:1;			
	}info;
}MyNote;

class MyMusicPlay  
{
private:
	float * buffer1;
	float * buffer2;
	UINT32 SampleRate;
	float Amplift;
	UCHAR CurrentPlayingBuff;
	UINT32 DataPos;
	UINT32 NotePos;
	UINT32 WritePos;
	float *& GetCurrentBuffer(UCHAR pl);
	void *stream;
	CWinThread * MyTh;
	bool ThreadRunning;
	UCHAR * MusicTable;
	UINT MusicLen;
	bool MyThAlive;
	UINT Code2Len(UCHAR x,UINT baseLen);
	UINT Base_Len;
	const UINT16 *Music;
protected:
	static int lcy_Callback(void *inputBuffer, void *outputBuffer,
							unsigned long framesPerBuffer,
							double outTime, void *userData );
	static UINT MyThreadCallback(void * param);
	UINT GetFreqByNote(UCHAR name,UCHAR sharp,UCHAR group);

public:
	bool Openning;
	MyMusicPlay(float amp,const UINT16 *data,UINT len,UINT bs = 300);
	void OpenSoundCard();
	void CloseSoundCard();
	void FillBufferEx(float * buff,UINT freq,UCHAR vol,UINT startpos,UINT len,UCHAR type);
	virtual ~MyMusicPlay();

};

#endif // !defined(AFX_MYMUSICPLAY_H__3F6A6F3E_0FCB_4A69_B577_926A7B8F0AD6__INCLUDED_)
