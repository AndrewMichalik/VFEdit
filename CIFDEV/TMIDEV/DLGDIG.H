/************************************************************************/
/* Dialogic Media Control I/F Defs: DlgTMI.h           V2.00  06/10/92 */
/* Copyright (c) 1987-1992 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define SMPFRQHGH      8000             /* Highest sample frequency     */

/************************************************************************/
/*                  Array/String Length Constants                       */
/************************************************************************/
#define IDXARRCNT      512              /* Dig indexed play (x 8 bytes) */
                                        /* 512 * 4K @ 64Kbs = 4.25 min  */
#define BLKCNTMIN        4              /* Dig I/O buffer blk cnt max   */
#define BLKCNTMAX       64              /* Dig I/O buffer blk cnt min   */
#define BLKLENMIN        4              /* Dig I/O buffer blk len max   */
#define BLKLENMAX     1024              /* Dig I/O buffer blk len min   */
#define EVTPOLTIM     2000L             /* Dig I/O event poll time out  */

/************************************************************************/
/*              Digitizer configuration data structures                 */
/************************************************************************/
typedef struct _SYSCFG {                /* Dig system control           */
    short       sVBSwIn;                /* Dig default software int lvl */
    short       sVBHwIn;                /* Dig default hardware int lvl */
    short       sMxHwIn;                /* Mpx default hardware int lvl */
    short       sLinNum;                /* Voice board line number      */
    short       sMpxInp;                /* Mpx input  address           */
    short       sMpxOut;                /* Mpx output address           */
    short       sMpxLoc;                /* Mpx local  address           */
    short       sTrmOOH;                /* Term on/off hook state       */
    short       sWaiCal;                /* Wait for call                */
    BYTE        ucRsv001[32-18];        /* Reserved                     */
} SYSCFG;  

typedef struct _LINCFG {                /* Dig line control             */
    short       sMaxSil;                /* Max sil allowed during rcrd  */
    short       sMaxSnd;                /* Max snd allowed during rcrd  */
    short       sSilCmp;                /* Sil compression sensitivity  */
    short       sAGCMod;                /* AGC mode                     */
    short       sDigIni;                /* DTMF digit init I/O          */
    short       sDigTrm;                /* DTMF digit term I/O          */
    BYTE        ucRsv001[32-12];        /* Reserved                     */
} LINCFG;  

typedef struct _TMIDEF {                /* Telco Media defaults         */
    SYSCFG  scSysCfg;                   /* Dig system controls          */
    LINCFG  lcLinCfg;                   /* Dig line   controls          */
} TMIDEF;  

typedef struct _DIGCFG {                /* Digitizer system params      */
    TMIDEF  tdTMIDef;                   /* Telco Media defaults         */
    DCB     dbDlgDCB;                   /* Dlg Specific control block   */
    CPB     cbDlgCPB;                   /* Dlg Specific control block   */
    WORD    usCSTInt;                   /* Dlg call status transition   */
} DIGCFG;

/************************************************************************/
/*                      Dig I/O data structures                         */
/************************************************************************/
#if	(defined (PCMVERNUM) && defined (EFFVERNUM))
    typedef struct  _DIOBLK {           /* Dig I/O callback block       */
        WORD            usLinNum;       /* Tel I/F line number          */
        PCMTYP          usPCMTyp;       /* PCM type                     */
        WORD            usChnCnt;       /* Channel count                */
        DWORD           ulSmpFrq;       /* Sample frequency             */
        WORD            usMpxInp;       /* Tel I/F port number          */
        WORD            usMpxOut;       /* Tel I/F port number          */
        TMIDIOPRC       fpDIOPrc;       /* Dig I/O user poll proc       */
        DWORD           ulDIODat;       /* Dig I/O user poll data       */
        DWORD           ulBufSiz;       /* Sample I/O buffer size       */
        WORD            usBufCnt;       /* Sample I/O buffer count      */
        WORD            usBufAct;       /* Active buffer count          */
        DWORD           ulPauFsh;       /* Paused flushed bytes        */
        DWORD           ulPauPos;       /* Paused byte position        */
    } DIOBLK;

    typedef struct  _TIFBLK {           /* Tel I/F callback block       */
        HWND            hEvtWnd;        /* Tel I/F event user proc      */
        DWORD           ulEvtArg;       /* Tel I/F event user data      */
    } TIFBLK;

    typedef struct  _BUFBLK {           /* Dig I/O buffer block         */
        VISMEMHDL       mhBufHdl;      
        LPVOID          lpBufMem;      
    } BUFBLK;

    typedef struct  _IDXREC {           /* Indexed play record          */
        DWORD           ulIdxOff;
        DWORD           ulIdxLen;
    } IDXREC;

    typedef struct  _CHDBLK {           /* Cached transfer block        */
        BUFBLK          bbPCMWrk;       /* Cached transfer PCM work blk */
        WORD            usReaFil;       /* Cached transfer file hdl     */
        WORD            usProFil;       /* Cached transfer file hdl     */
        WORD            usMemSiz;       /* Cached transfer mem size     */
        WORD            usMemHdl;       /* Cached transfer mem hndl     */
        DWORD           ulReaMem;       /* Cached transfer real mem     */
        DWORD           ulPstByt;       /* Cached transfer past bytes   */
        WORD            usCurIdx;       /* Cached transfer current idx  */
        WORD            usNxtIdx;       /* Cached transfer next index   */
        IDXREC FAR *    irIdxRec;       /* Cached transfer prot mem     */
        RWB             drDlgRWB;       /* Cached transfer rd/wr blk    */
    } CHDBLK;

    typedef DWORD (FAR PASCAL *DEVPRC)(TMIPOL,DIOBLK FAR*,CHDBLK FAR *);
    typedef BOOL  (FAR PASCAL *TIMPRC)(DIOBLK FAR*,CHDBLK FAR *);

    typedef struct  _DIORES {           /* Digitizer wave/mpx params    */
        HWND            hCBkWnd;        /* Callback window handle       */
        LINCFG          lcLinCfg;       /* Dig line control             */
        TIFBLK          tbTIFBlk;       /* Telephone interface block    */
        CHDBLK          cbChdBlk;       /* Cached transfer block        */
        DEVPRC          fpDevPrc;       /* Dig I/O playback proc        */
        DIOBLK          dbDIOBlk;       /* Dig I/O callback data        */
        TIMPRC          fpTimPrc;       /* Dig WM_TIMER proc            */
    } DIORES;      

#endif

/************************************************************************/
/************************************************************************/
typedef struct _SYSRES {                /* Digitizer system resources   */
    WORD            usDigIni;           /* Digitizer init code          */
    WORD            usMpxIni;           /* Multiplexer init code        */
    WORD            usLinCnt;           /* Line count                   */
    WORD            usPrtCnt;           /* Port count                   */
    WORD            usDigTyp;           /* Dig board type               */
} SYSRES;

/************************************************************************/
/************************************************************************/
typedef enum _EVTTRM {                  /* Generalized term events      */
    NUL_TRM,
    OOH_TRM,
    RNG_TRM,
    WIO_TRM
} EVTTRM;

/************************************************************************/
/************************************************************************/
void    DigDevStp (WORD, HWND);
WORD    ClrEvtQue (WORD);
EVTTRM  PolEvtQue (WORD, HWND, EVTTRM, DWORD);
BOOL    TstTrmEvt (WORD, EVTTRM);  


