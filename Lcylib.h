/*声卡音频实时函数库的应用程序接口头文件*/
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

/*1.函数库的初始化函数，使用库之前，要先调用该函数。*/
int Pa_Initialize( void );

/*2.函数库的中止函数，使用库之后，要调用该函数。*/
int Pa_Terminate( void );

/*3.返回错误代码函数*/
long Pa_GetHostError( void );

/*4.翻译错误代码为人可读懂信息函数*/
const char *Pa_GetErrorText( int errnum );

/*(1)采样所得数据的格式定义*/
#define paFloat32      ((unsigned long) (1<<0))        
#define paInt16        ((unsigned long) (1<<1))        
#define paInt32        ((unsigned long) (1<<2))        
#define paInt24        ((unsigned long) (1<<3))
#define paPackedInt24  ((unsigned long) (1<<4))
#define paInt8         ((unsigned long) (1<<5))
#define paUInt8        ((unsigned long) (1<<6))    
#define paCustomFormat ((unsigned long) (1<<16))

#define paNoDevice -1
/*(2)声卡信息定义*/
typedef struct{
        int structVersion;
        const char *name;
        int maxInputChannels;
        int maxOutputChannels;
        int numSampleRates;
        const double *sampleRates;
        unsigned long nativeSampleFormats;
} PaDeviceInfo;

/*5.获得声卡数量函数*/
int Pa_CountDevices();
    
/*6.获得声卡默认的输入端数量函数*/
int Pa_GetDefaultInputDeviceID( void );
    
/*7.获得声卡默认的输出端数量函数*/
int Pa_GetDefaultOutputDeviceID( void );

/*8.获得存储声卡信息地址函数*/
const PaDeviceInfo* Pa_GetDeviceInfo( int devID );

/*9.回调函数及参数说明：
 inputBuffer and outputBuffer：采样的数据、格式、存储和通道数量。
 framesPerBuffer：采样数据帧的数量。
 outTime()：数据流时间。
 userData：向数据流传送的数据。
*/
typedef int (PortAudioCallback)(
                void *inputBuffer, void *outputBuffer,
                unsigned long framesPerBuffer,
                double outTime, void *userData );


/*(3)数据流属性定义*/
#define   paNoFlag      (0)
#define   paClipOff     (1<<0)   
#define   paDitherOff   (1<<1)   
#define   paPlatformSpecificFlags (0x00010000)

/*10.打开输入或输出端的数据流，或两者同时打开函数。*/
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


/*11.打开声卡默认的输入或输出端，或两者同时打开函数。*/
int Pa_OpenDefaultStream( void** stream,
                                int numInputChannels,
                                int numOutputChannels,
                                unsigned long sampleFormat,
                                double sampleRate,
                                unsigned long framesPerBuffer,
                                unsigned long numberOfBuffers,
                                PortAudioCallback *callback,
                                void *userData );

/*12.关闭数据流并清空缓冲区函数*/
int Pa_CloseStream( void* );

/*13.开始数据流函数*/
int Pa_StartStream( void *stream );
    
/*14.中止数据流函数，但要等缓冲区的数据空后。*/
int Pa_StopStream( void *stream );
    
/*15.立即中止数据流函数，不等缓冲区的数据空后。*/
int Pa_AbortStream( void *stream );

/* 16.数据流处理状况函数：返回１值，数据流正在进行；０值数据流没在进行；
 负值：数据流无效。*/
int Pa_StreamActive( void *stream );

/*17.返回数据流要用的时间函数*/
double Pa_StreamTime( void *stream );

/*18.返回数据流占用CPU百分比函数，0.5表示占用50%。*/
double Pa_GetCPULoad( void* stream );

/*18.获得所需最小缓冲区函数*/
int Pa_GetMinNumBuffers( int framesPerBuffer, double sampleRate );

/*19.暂停函数，以微秒（msec）单位。*/
void Pa_Sleep( long msec );
    
/*20.返回bytes表示的采样数据大小函数*/
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