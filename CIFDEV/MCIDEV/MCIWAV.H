/************************************************************************/
/* MCI Wave Definitions: MCISup.h                       V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/*                  Array/String Length Constants                       */
/************************************************************************/
#define BLKCNTMIN        4              /* Wave I/O buffer blk cnt max  */
#define BLKCNTMAX       64              /* Wave I/O buffer blk cnt min  */
#define BLKLENMIN        4              /* Wave I/O buffer blk len max  */
#define BLKLENMAX     1024              /* Wave I/O buffer blk len min  */

/************************************************************************/
/*                      Wave I/O data structures                        */
/************************************************************************/
typedef struct  _WIOBLK {               /* Wave I/O callback block      */
    union   {
    HWAVEOUT        hWavOut;            /* Wave Output device           */ 
    HWAVEIN         hWavInp;            /* Wave Input  device           */ 
    HANDLE          hWavGIO;            /* Wave generic device          */
    };
    MCIWIOPRC       fpWIOPrc;           /* Wave I/O user poll proc      */
    DWORD           ulWIODat;           /* Wave I/O user poll data      */
    WAVEFORMATEX    wfWavFmt;           /* Device wave format           */
    DWORD           ulBufSiz;           /* Sample I/O buffer size       */
    WORD            usBufCnt;           /* Sample I/O buffer count      */
    WORD            usBufAct;           /* Active buffer count          */
    WORD            usDev_ID;           /* Wave I/O Device ID           */
} WIOBLK;

typedef struct  _BUFBLK {               /* Wave I/O buffer block        */
    LPWAVEHDR       lpWavHdr;      
    VISMEMHDL       mhHdrHdl;      
    VISMEMHDL       mhBufHdl;      
} BUFBLK;

typedef WORD    (FAR PASCAL *DEVPRC)(MCIPOL,WIOBLK FAR*,LPWAVEHDR);
typedef BOOL    (FAR PASCAL *TIMPRC)(WIOBLK FAR*);

typedef struct  _WIORES {               /* MCI callback resources       */
    HWND        hCBkWnd;                /* Callback window handle       */
    BUFBLK      bbBufBlk[BLKCNTMAX];
    DEVPRC      fpDevPrc;               /* Wave I/O device proc         */
    WIOBLK      wbWIOBlk;               /* Wave I/O callback data       */
    TIMPRC      fpTimPrc;               /* Wave I/O WM_TIMER proc       */
} WIORES;

/************************************************************************/
/*                      MM Registration values                          */
/************************************************************************/
#define WAVE_FORMAT_ADPCM               0x0002
#define WAVE_FORMAT_IBM_CVSD            0x0005
#define WAVE_FORMAT_ALAW                0x0006
#define WAVE_FORMAT_MULAW               0x0007
#define WAVE_FORMAT_OKI_ADPCM           0x0010
#define WAVE_FORMAT_DIGISTD             0x0015
#define WAVE_FORMAT_DIGIFIX             0x0016
#define WAVE_FORMAT_DIALOGIC_OKI_ADPCM	0x0017  /* Dialogic Corporation */
