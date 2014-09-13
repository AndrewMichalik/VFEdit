/************************************************************************/
/* Generic Amplitude Display Definitions: GenAmp.h      V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define AMPVERNUM       0x0300          /* Waveform support ver number  */
#define SCRPERPAG           5L          /* Scroll: scroll pos/ page     */
#define SCRPOSUPD       0x0002          /* Scroll position update flag  */
#define SCREXTUPD       0x0008          /* Scroll extents  update flag  */
#define SMPPGPMIN            1          /* Min samples per graph point  */
#define SMPPGPMAX       0x7fff          /* Max samples per graph point  */
#define PTPMAJDIV           20          /* Pts / major div (large tick) */
#define PTPMINDIV            4          /* Pts / minor div (small tick) */

#define SB_SCRFULLFT    SB_ENDSCROLL+10 /* Scroll msg: Ctl PageDown     */
#define SB_SCRFULRGT    SB_ENDSCROLL+11 /* Scroll msg: Ctl PageUp       */
#define SB_SCRSMPGTO    SB_ENDSCROLL+12 /* Scroll msg: Goto sample      */
#define SB_SCRFUL_UP    SB_ENDSCROLL+10 /* Scroll msg: Ctl PageUp       */
#define SB_SCRFULDWN    SB_ENDSCROLL+11 /* Scroll msg: Ctl PageDown     */
#define SB_SCRSMPFIT    SB_ENDSCROLL+12 /* Scroll msg: Goto sample      */
#define SB_SCRSMPPMD    SB_ENDSCROLL+13 /* Scroll msg: Smp / maj div    */

/************************************************************************/
/*                  Mouse Selection Definitions                         */
/************************************************************************/
typedef enum _AMPMSE {
    AMPMSENON = 0,                      /* Mouse not owned              */
    AMPMSEBEG,                          /* Mouse owned by Sel op        */
    AMPMSEEND,                          /* Mouse owned by Sel op        */
    AMPMSEMAX,                          /* Mouse owned by Amp op        */
    AMPMSEMIN,                          /* Mouse owned by Amp op        */
    AMPMSEATP,                          /* Mouse owned by AtP op        */
} AMPMSE;

/************************************************************************/
/************************************************************************/
typedef short   GENSMP;                 /* Generic PCM storage type     */

typedef struct _AMPDES {
    DWORD       ulSmpOff;               /* Wave beginning sample pos    */
    DWORD       ulDocLen;               /* Doc length (samples)         */
    DWORD       ulSmpFrq;               /* File recording speed: samp/s */
    float       flSmppGP;               /* Current res (smp/graph pt)   */
    WORD        usArrLen;               /* Waveform display length      */
    WORD        usGPtCnt;               /* Graph valid point count      */
    WORD        usBlkSiz;               /* Graph edit block boundary    */
    WORD        usViwCon;               /* Graph connected threshold    */
    BYTE        ucRsv001[64 - 22];      /* Reserved                     */
} AMPDES;

typedef struct _AMPPNT {
    long        lYAxExt;                /* Y-Axis extents               */
    short       sYAxMax;                /* Y-Axis maximum               */
    short       sYAxMin;                /* Y-Axis minimum               */
    short       sYAxInc;                /* Y-Axis increment             */
    BYTE        ucRsv001[64 -  8];      /* Reserved                     */
} AMPPNT;

typedef struct _AMPUSR {
    AMPMSE      amMseOwn;               /* Current mouse owner          */
    DWORD       ulSelBeg;               /* Sel from position (samp)     */
    DWORD       ulSelEnd;               /* Sel to   position (samp)     */
                                        /* Note: ulSelBeg may be >= End */
    WORD        usAmpMax;               /* Amp max  magnitude           */
    WORD        usAmpMin;               /* Amp min  magnitude           */
    DWORD       ulPosAtP;               /* Pos at   position (samp)     */
    BOOL        bPosBln;                /* Pos at   blink state         */
    BYTE        ucRsv001[64 - 20];      /* Reserved                     */
} AMPUSR;

typedef struct _AMPGPH {                /* Max / Min display block      */   
    GENSMP      gsMinWav;                   
    GENSMP      gsMaxWav;                   
} AMPGPH;

/************************************************************************/
/*                  Amplitude Display Operation codes                   */
/************************************************************************/
typedef enum _AMPREQ {
    AOPNULREQ = 0,                      /* Null request                 */
    AOPREGREQ,
    AOPCFGREQ,
} AMPREQ;                  

/************************************************************************/
/*              Amplitude Display Resource Support Routines             */       
/************************************************************************/
WORD    FAR PASCAL AmpDLLIni (WORD, DWORD, DWORD);
WORD    FAR PASCAL AmpSupVer (void);

BOOL    FAR PASCAL AmpStaPos (HWND, RECT FAR *);
void    FAR PASCAL AmpStaPnt (HWND, const AMPDES FAR *, const AMPUSR FAR *);

BOOL    FAR PASCAL AmpXAxPos (HWND, RECT FAR *);
void    FAR PASCAL AmpXAxPnt (HWND, const AMPDES FAR *);
BOOL    FAR PASCAL AmpXAxUpd (HWND, WORD, DWORD, long FAR *, const AMPDES FAR *);
WORD    FAR PASCAL AmpXAxScr (HWND, long, DWORD FAR *, const AMPDES FAR *);

BOOL    FAR PASCAL AmpYAxPos (HWND, RECT FAR *);
void    FAR PASCAL AmpYAxPnt (HWND, const AMPPNT FAR *);

BOOL    FAR PASCAL AmpZAxUpd (HWND, WORD, DWORD, float FAR *, const AMPDES FAR *);
BOOL    FAR PASCAL AmpZAxScr (HWND, float, float FAR *, const AMPDES FAR *);

BOOL    FAR PASCAL AmpGphPos (HWND, RECT FAR *);
void    FAR PASCAL AmpGphPnt (HWND, const AMPPNT FAR *, const AMPDES FAR *, AMPUSR FAR *, AMPGPH FAR *);

void    FAR PASCAL AmpMseLDn (HWND, WORD, POINT, const AMPDES FAR *, AMPUSR FAR *); 
BOOL    FAR PASCAL AmpMseMov (HWND, WORD, POINT, const AMPDES FAR *, AMPUSR FAR *); 
void    FAR PASCAL AmpMseLUp (HWND, WORD, POINT, const AMPDES FAR *, AMPUSR FAR *); 

void    FAR PASCAL AmpCarMov (HWND, DWORD, const AMPDES FAR *, AMPUSR FAR *); 
void    FAR PASCAL AmpCarBln (HWND, const AMPDES FAR *, AMPUSR FAR *); 

void    FAR PASCAL AmpSelMov (HWND, DWORD, DWORD, const AMPDES FAR *, AMPUSR FAR *);
