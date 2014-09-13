/************************************************************************/
/* Generic Media Control I/F Defs: GenMCI.h             V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define MCIVERNUM       0x0300          /* Media Ctl support ver number */
#define MCIMAXCHN            4          /* Maximum channel count        */

/************************************************************************/
/*  Device Protocol: Fully defines I/O device.                          */
/*  Protocol Word: | 4 bit Protocol | 4 bit I/O Flag | 8 bit Dev# |     */
/************************************************************************/
typedef enum _MCIPRO {
    MCIUNKPRO = 0x0000,                 /* MCI protocol = Unknown       */
    MCIPROINP = 0x0200,                 /* MCI Input  flag              */
    MCIPROOUT = 0x0400,                 /* MCI Output flag              */
    MCIMAXPRO                           /* Maximum # entries            */
} MCIPRO;                  

#define WAVDEV_ID(x)    ((x) & 0x00ff)  /* Control protocol device #    */
#define WAVDEVDIR(x)    ((x) & 0x0f00)  /* Control protocol direction   */

#define WAVDEVFST       0               /* Control protocol first       */
#define WAVDEVNXT(x)    (((WORD)(x))++) /* Control protocol next        */

/************************************************************************/
/************************************************************************/
#define ENUPCM      enum _PCMTYP        /* Forward reference for PCMTYP */

/************************************************************************/
/*                  Callback procedure definitions                      */
/************************************************************************/
typedef enum _MCIPOL {
    MCIPOLBEG,                              /* Begin poll operation     */
    MCIPOLCNT,                              /* Continuation poll op     */
    MCIPOLPOS,                              /* Position poll notify     */
    MCIPOLEMP,                              /* Empty poll operation     */
    MCIPOLEND                               /* End poll operation       */
} MCIPOL;
typedef WORD  (FAR PASCAL *MCIPOLPRC)(MCIPOL,DWORD,DWORD);
typedef DWORD (FAR PASCAL *MCIWIOPRC)(MCIPOL,LPVOID,DWORD,WORD,DWORD,DWORD);

/************************************************************************/
/************************************************************************/
WORD    FAR PASCAL  MCIDLLIni (WORD, DWORD, DWORD);
WORD    FAR PASCAL  MCISupVer (void);

MCIPRO  FAR PASCAL  MCIWavEnu (MCIPRO, LPSTR, WORD);
ENUPCM  FAR PASCAL  MCIPCMEnu (MCIPRO, ENUPCM);
WORD    FAR PASCAL  MCIChnEnu (MCIPRO, ENUPCM, WORD);
DWORD   FAR PASCAL  MCIFrqEnu (MCIPRO, ENUPCM, WORD, DWORD);
WORD    FAR PASCAL  MCICapQry (MCIPRO, ENUPCM, WORD, DWORD);

WORD    FAR PASCAL  MCICfgLod (VISMEMHDL FAR *, LPCSTR, LPCSTR);
WORD    FAR PASCAL  MCICfgRel (VISMEMHDL FAR *, LPCSTR, LPCSTR);
WORD    FAR PASCAL  MCICfgMod (VISMEMHDL, WORD, DWORD);
WORD    FAR PASCAL  MCICfgQry (VISMEMHDL);
        
WORD    FAR PASCAL  MCIWavOpn (MCIPRO, VISMEMHDL FAR *, VISMEMHDL, WORD, WORD, LPSTR, WORD); 
WORD    FAR PASCAL  MCIWavCls (VISMEMHDL FAR *); 
MCIPRO  FAR PASCAL  WavFilSta (VISMEMHDL, DWORD FAR *);
WORD    FAR PASCAL  WavFilPla (VISMEMHDL, WORD, WORD, DWORD, MCIWIOPRC, DWORD, MCIPOLPRC, DWORD);
WORD    FAR PASCAL  WavPlaBeg (VISMEMHDL);
WORD    FAR PASCAL  WavFilRec (VISMEMHDL, WORD, WORD, DWORD, MCIWIOPRC, DWORD);
WORD    FAR PASCAL  WavRecBeg (VISMEMHDL);
DWORD   FAR PASCAL  WavFilPau (VISMEMHDL, WORD); 
DWORD   FAR PASCAL  WavFilTrm (VISMEMHDL);

