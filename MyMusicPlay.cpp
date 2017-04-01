// MyMusicPlay.cpp: implementation of the MyMusicPlay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testMFC.h"
#include "MyMusicPlay.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




static const UINT freqtable[7][13]={
	0,32,34,36,38,41,43,46,49,51,55,58,61, 
	0,65,69,73,77,82,87,92,98,103,110,116,123,
	0,130,138,146,155,164,174,185,196,207,220,233,246,
	0,261,277,293,311,329,349,369,392,415,440,466,493,
	0,523,554,587,622,659,698,740,784,831,880,932,987,
	0,1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975,
	0,2093,2217,2349,2489,2637,2793,2959,3135,3322,3520,3729,3951,
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyMusicPlay::MyMusicPlay(float amp,const UINT16 *data,UINT len,UINT bs /*= 300*/)
{
	SampleRate = 88200;
	Amplift = amp;
	DataPos = 0;
	NotePos = 0;
	WritePos = 0;
	buffer1 = NULL;
	buffer2 = NULL;
	CurrentPlayingBuff = 0;
	Music = data;
	MusicLen = len;
	Base_Len = bs;
	MyThAlive = false;
}



MyMusicPlay::~MyMusicPlay()
{
	if(Openning)
		CloseSoundCard();
	
}

void MyMusicPlay::OpenSoundCard()
{
	
	float *& buff = GetCurrentBuffer(MPB_Playing);
	if(buffer1)
		delete[] buffer1;
	buffer1 = new float[SampleRate];
	if(buffer2)
		delete[] buffer2;
	buffer2 = new float[SampleRate];
	FillBufferEx(buff,0,0,0,SampleRate,0);
	DataPos = 0;
	int err;
	err=Pa_OpenStream(
		&stream,    /*������ָ��*/
		paNoDevice, /*�ر������*/
		0,          /*�������Ϊ0*/
		paFloat32,  /*��������Ϊ32λ��������*/
		NULL,       /*�����������������*/
		Pa_GetDefaultOutputDeviceID(), /*���Ĭ�ϵ�����˵�ַ*/
		1,          /*�����������ʽ*/
		paFloat32,  /*�������Ϊ32λ��������*/
		NULL,       /*����������������*/
		SampleRate,/*����Ƶ��*/
		1,       /*framesPerBufferÿ����������С*/
		0,          /*��������,Ϊ0ʱ��Ĭ����Сֵ*/
		paClipOff,  /*�ر���Ч*/
		lcy_Callback, /*�ص�����*/
		this       /*�û�����*/
		);
	if(err!=paNoError) CloseSoundCard();
	/*����ʼ�������������*/
	err=Pa_StartStream(stream);
	 if(err!=paNoError) CloseSoundCard();

	 Openning = true;
	 MyTh = AfxBeginThread(MyThreadCallback,this);


}

void MyMusicPlay::CloseSoundCard()
{
	/*���ر�����������*/
	Pa_CloseStream(stream);
	/*���˳�������*/
	Pa_Terminate();
	/*�ͷſ��ٵ��ڴ�ռ�*/
	ThreadRunning = false;
	ResumeThread(MyTh->m_hThread);
	while(MyThAlive);
	if(buffer1!=NULL)
		delete []buffer1;
	if(buffer2 != NULL)
		delete[] buffer2;
	buffer1 = buffer2 = 0;

	
}



/*type:0=pulse | 1=sine | 2=half sine | 88=user func.*/
void MyMusicPlay::FillBufferEx(float * buff,UINT freq,UCHAR vol,UINT startpos,UINT len,UCHAR type)
{
	
	 static bool level = true;
	//UINT rlen = (SampleRate - startpos)<len?(SampleRate - startpos):len;

	 static double twoPiF = 0.0;
	 static double phase = 0.0;
	 double sin_val = 0.0;
	 double x = 0;
	 if(type == 1)
		twoPiF = 2.0*3.1415*(double)freq;
	 else if(type == 2)
		 twoPiF = 3.1415*(double)freq;
	for(UINT i=startpos;i<(startpos+len);i++ )
	{

		WritePos++;
		if(freq == 0)
		{
			buff[i] = 0;
			sin_val = 0;
			phase = 0;
			continue;
		}
		
		if(type == 1 || type == 2)
		{
			
			double lcy_w= twoPiF /(double)SampleRate;
			x = (double)i*lcy_w + phase;
			sin_val = sin(x);
			if(type == 2 && sin_val < 0)
				sin_val = 0.0 - sin_val;

			if(type == 1)
				buff[i] = (float)sin_val * 5 * Amplift * vol / 16   ;
			if(type == 2)
				buff[i] = (float)sin_val * 5 * Amplift * vol / 16   ;

		}
		else
		{
			if(i % (SampleRate / freq / 2) == 0)
				level = !level;
			if(level)
				buff[i] = Amplift * vol / 16;
			else
			buff[i] = 0;
		}
		

	}
	if(type == 1 || type == 2)
		phase = x - (twoPiF * (UINT)(x / twoPiF));
}

float *&  MyMusicPlay::GetCurrentBuffer(UCHAR pl)
{
	if(CurrentPlayingBuff == 0)
		return pl?buffer1:buffer2;
	if(CurrentPlayingBuff == 1)
		return pl?buffer2:buffer1;
	throw "û���Ǹ����壡";
	return buffer1;
}

int MyMusicPlay::lcy_Callback(void *inputBuffer, 
							  void *outputBuffer, 
							  unsigned long framesPerBuffer,
							  double outTime, 
							  void *userData)
{
	MyMusicPlay * cls = (MyMusicPlay *)userData;

	if(framesPerBuffer != 1)
		throw "Frame����1��";

	float *out = (float*)outputBuffer;
		float *& buff = cls->GetCurrentBuffer(MPB_Playing);
		for(UINT32 i=0; i<framesPerBuffer; i++ ){
		*out++=buff[cls->DataPos]; 
		cls->DataPos++;
		if(cls->DataPos>=cls->SampleRate )
		{
			cls->DataPos =0;
			cls->CurrentPlayingBuff = cls->CurrentPlayingBuff==0?1:0;
			ResumeThread(cls->MyTh->m_hThread);
		}
		}

  return 0;
}

UINT MyMusicPlay::MyThreadCallback(void * param)
{
	MyMusicPlay * cls = (MyMusicPlay *)param;	
	cls->NotePos = 0;
	cls->WritePos = 0;
	UINT writetimes = 0;
	UINT last_note = -1;
	UINT currfreq,restLen;
	UCHAR curr_vol = 0;
	while(cls->ThreadRunning)
	{
		cls->MyThAlive = true;
		float *& buff = cls->GetCurrentBuffer(MPB_Buffering);
		if(buff && cls->WritePos == 0)
		{
			delete[] buff;
			buff = new float[cls->SampleRate];
		}
		if(last_note != cls->NotePos)
		{
			MyNote nt;
			nt.data16 = cls->Music[cls->NotePos];
			currfreq = cls->GetFreqByNote(nt.info.Name,nt.info.Sharp,nt.info.Group);
			UINT bb = cls->Code2Len(nt.info.Length,cls->Base_Len);
			restLen =   bb;
			curr_vol = nt.info.Volume;
			
		}
		
		UINT wlen = restLen<(cls->SampleRate-cls->WritePos)?restLen:(cls->SampleRate-cls->WritePos);
		cls->FillBufferEx(buff,currfreq,curr_vol,cls->WritePos,wlen,1);

			
		restLen -= wlen;
		writetimes += wlen;
		last_note = cls->NotePos;
		if(restLen == 0)
		{
			cls->NotePos++;
			writetimes = 0;
		}
		if(cls->NotePos >= cls->MusicLen)
			cls->NotePos = 0;

		if(cls->WritePos >= cls->SampleRate)
		{
			cls->WritePos = 0;
			UINT err = SuspendThread(cls->MyTh->m_hThread);
			if(err == 0xFFFFFFFF)
			{
				MessageBox(0,"����ʧ�ܣ�","����",0);
				while(1);
			}

		}
	}
	cls->MyThAlive = false;
	return 0;
}

UINT MyMusicPlay::Code2Len(UCHAR x,UINT baseLen)
{
	UCHAR rrr = 0;
	switch(x)
	{
	case 0:rrr = 1;break;
	case 1:rrr = 2;break;
	case 2:rrr = 4;break;
	case 3:rrr = 8;break;
	case 4:rrr = 16;break;
	case 5:rrr = 24;break;
	case 6:rrr = 32;break;
	case 7:rrr = 40;break;
	case 8:rrr = 48;break;
	default:rrr = 0;break;
	}
	return baseLen * rrr;
}

UINT MyMusicPlay::GetFreqByNote(UCHAR name,UCHAR sharp,UCHAR group)
{
		UCHAR x = 0;
		switch (name)
		{
		case 0:x = 0;break;
		case 1:!sharp?x=1:x=2;break;
		case 2:!sharp?x=3:x=4;break;
		case 3:!sharp?x=5:x=6;break;
		case 4:!sharp?x=6:x=7;break;
		case 5:!sharp?x=8:x=9;break;
		case 6:!sharp?x=10:x=11;break;
		case 7:!sharp?x=12:(x=1,group++);break;
		default: throw "����Ƶ�ʴ���";
		}
		return freqtable[group][x];
}
