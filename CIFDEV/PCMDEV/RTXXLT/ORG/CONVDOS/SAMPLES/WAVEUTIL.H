/*ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป*/
/*บฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐบ*/
/*บฐ                                                                    ฐบ*/
/*บฐ                         WAVEUTIL.h                                 ฐบ*/
/*บฐ                                                                    ฐบ*/
/*บฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐบ*/
/*ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ*/

    #ifndef _CV_WAVEUTIL_H_INCLUDED
    #define _CV_WAVEUTIL_H_INCLUDED


/*ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ*/
/*ณ                     Definitions                                     ณ*/
/*ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู*/
#define WAVE_FORMAT_PCM 1
#define MAX_CHANNELS    1

typedef struct tagWAVEHEADER
{
        char    RIFF[4];                /* 'R','I','F','F'                */
        long    size;                   /* size of wave file from here on */
        char    WAVEfmt[8];             /* 'W','A','V','E','f','m','t',' '*/
        long    dataoffset;             /* offset of data chunk           */
        int     wFormatTag;             /* should be 1 for PCM type data  */
        int     nChannels;              /* should be 1 for MONO type data */
        long    nSamplesPerSec;         /* should be 11025, 22050, 44100  */
        long    nAvgBytesPerSec;        /* Average Data Rate              */
        int     nBlockAlign;            /* 1 for 8 bit data, 2 for 16 bit */
        int     wBitsPerSample;         /* 8 for 8 bit data, 16 for 16 bit*/
        char    data[4];                /* 'd','a','t','a'                */         
        long    datasize;               /* size of data from here on      */         
} WAVEHEADER;
    
    
/*ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ*/
/*ณ                     Function Prototypes                             ณ*/
/*ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู*/
extern WAVEHEADER *CreateWaveHeader( long nSamplesPerSec, int wBitsPerSample );
extern void DestroyWaveHeader(WAVEHEADER *wh);            
extern void CheckWaveHeader(WAVEHEADER *wh);
extern void UpdateWaveHeaderSize( char *filename, long datasize );
extern void Error(const char *fmt, ... );
    #endif  /* _CV_WAVEUTIL_H_INCLUDED */
