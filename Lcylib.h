/*������Ƶʵʱ�������Ӧ�ó���ӿ�ͷ�ļ�*/
#ifndef PORT_AUDIO_H
#define PORT_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
        paNoError = 0,

        paHostError = -10000,
        paInvalidChannelCount,
        paInvalidSampleRate,
        paInvalidDeviceId,
        paInvalidFlag,
        paSampleFormatNotSupported,
        paBadIODeviceCombination,
        paInsufficientMemory,
        paBufferTooBig,
        paBufferTooSmall,
        paNullCallback,
        paBadStreamPtr,
        paTimedOut,
        paInternalError
} PaErrorNum;

/*1.������ĳ�ʼ��������ʹ�ÿ�֮ǰ��Ҫ�ȵ��øú�����*/
int Pa_Initialize( void );

/*2.���������ֹ������ʹ�ÿ�֮��Ҫ���øú�����*/
int Pa_Terminate( void );

/*3.���ش�����뺯��*/
long Pa_GetHostError( void );

/*4.����������Ϊ�˿ɶ�����Ϣ����*/
const char *Pa_GetErrorText( int errnum );

/*(1)�����������ݵĸ�ʽ����*/
#define paFloat32      ((unsigned long) (1<<0))        
#define paInt16        ((unsigned long) (1<<1))        
#define paInt32        ((unsigned long) (1<<2))        
#define paInt24        ((unsigned long) (1<<3))
#define paPackedInt24  ((unsigned long) (1<<4))
#define paInt8         ((unsigned long) (1<<5))
#define paUInt8        ((unsigned long) (1<<6))    
#define paCustomFormat ((unsigned long) (1<<16))

#define paNoDevice -1
/*(2)������Ϣ����*/
typedef struct{
        int structVersion;
        const char *name;
        int maxInputChannels;
        int maxOutputChannels;
        int numSampleRates;
        const double *sampleRates;
        unsigned long nativeSampleFormats;
} PaDeviceInfo;

/*5.���������������*/
int Pa_CountDevices();
    
/*6.�������Ĭ�ϵ��������������*/
int Pa_GetDefaultInputDeviceID( void );
    
/*7.�������Ĭ�ϵ��������������*/
int Pa_GetDefaultOutputDeviceID( void );

/*8.��ô洢������Ϣ��ַ����*/
const PaDeviceInfo* Pa_GetDeviceInfo( int devID );

/*9.�ص�����������˵����
 inputBuffer and outputBuffer�����������ݡ���ʽ���洢��ͨ��������
 framesPerBuffer����������֡��������
 outTime()��������ʱ�䡣
 userData�������������͵����ݡ�
*/
typedef int (PortAudioCallback)(
                void *inputBuffer, void *outputBuffer,
                unsigned long framesPerBuffer,
                double outTime, void *userData );


/*(3)���������Զ���*/
#define   paNoFlag      (0)
#define   paClipOff     (1<<0)   
#define   paDitherOff   (1<<1)   
#define   paPlatformSpecificFlags (0x00010000)

/*10.�����������˵���������������ͬʱ�򿪺�����*/
int Pa_OpenStream( void** stream,
                       int inputDevice,
                       int numInputChannels,
                       unsigned long inputSampleFormat,
                       void *inputDriverInfo,
                       int outputDevice,
                       int numOutputChannels,
                       unsigned long outputSampleFormat,
                       void *outputDriverInfo,
                       double sampleRate,
                       unsigned long framesPerBuffer,
                       unsigned long numberOfBuffers,
                       unsigned long streamFlags,
                       PortAudioCallback *callback,
                       void *userData );


/*11.������Ĭ�ϵ����������ˣ�������ͬʱ�򿪺�����*/
int Pa_OpenDefaultStream( void** stream,
                                int numInputChannels,
                                int numOutputChannels,
                                unsigned long sampleFormat,
                                double sampleRate,
                                unsigned long framesPerBuffer,
                                unsigned long numberOfBuffers,
                                PortAudioCallback *callback,
                                void *userData );

/*12.�ر�����������ջ���������*/
int Pa_CloseStream( void* );

/*13.��ʼ����������*/
int Pa_StartStream( void *stream );
    
/*14.��ֹ��������������Ҫ�Ȼ����������ݿպ�*/
int Pa_StopStream( void *stream );
    
/*15.������ֹ���������������Ȼ����������ݿպ�*/
int Pa_AbortStream( void *stream );

/* 16.����������״�����������أ�ֵ�����������ڽ��У���ֵ������û�ڽ��У�
 ��ֵ����������Ч��*/
int Pa_StreamActive( void *stream );

/*17.����������Ҫ�õ�ʱ�亯��*/
double Pa_StreamTime( void *stream );

/*18.����������ռ��CPU�ٷֱȺ�����0.5��ʾռ��50%��*/
double Pa_GetCPULoad( void* stream );

/*18.���������С����������*/
int Pa_GetMinNumBuffers( int framesPerBuffer, double sampleRate );

/*19.��ͣ��������΢�루msec����λ��*/
void Pa_Sleep( long msec );
    
/*20.����bytes��ʾ�Ĳ������ݴ�С����*/
int Pa_GetSampleSize( unsigned long format );

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* PORT_AUDIO_H */


#include <math.h>
//#ifndef M_PI
//#define M_PI  (2*asin(1))
//#endif
const double M_PI=2*asin(1.0);