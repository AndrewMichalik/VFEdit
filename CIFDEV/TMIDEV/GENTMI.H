/************************************************************************/
/* Generic Telco Media Control I/F Defs: GenTMI.h       V2.00  06/10/92 */
/* Copyright (c) 1987-1992 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define TMIVERNUM       0x0300          /* Media Ctl support ver number */
#define TMIMAXCHN            4          /* Maximum channel count        */
#define WM_TIFEVT      WM_USER          /* Tel I/F event                */

/************************************************************************/
/*  Device Protocol: Fully defines I/O device.                          */
/*  Protocol Word: | 4 bit Protocol | 4 bit I/O Flag | 8 bit Dev# |     */
/************************************************************************/
typedef enum _TMIPRO {                  /* Telco media control protocol */
    TMIUNKPRO = 0x0000,                 /* Audio Device = Unknown       */
    TMIBCMPRO = 0x0001,                 /* Audio Device = BiCom    TMI  */
    TMIDLGPRO = 0x0002,                 /* Audio Device = Dialogic TMI  */
    TMINWVPRO = 0x0004,                 /* Audio Device = NewVoice TMI  */
    TMIRTXPRO = 0x0008,                 /* Audio Device = Rhetorex TMI  */
    TMIPROINP = 0x0200,                 /* TMI Input  flag              */
    TMIPROOUT = 0x0400,                 /* TMI Output flag              */
    TMIMAXPRO                           /* Maximum # entries            */
} TMIPRO;

#define TMIDEV_ID(x)    ((x) & 0x00ff)  /* Control protocol device ID   */

/************************************************************************/
/*                      TMI Query Types                                 */
/************************************************************************/
typedef enum _TMIQRY {
    UNKTMIQRY = 0,                      /* Unknown query                */
    TMIDEFQRY,                          /* TMI default protocol         */
    PRFPCMQRY,                          /* Preferred PCM type           */
    PRFCHNQRY,                          /* Preferred Channel count      */
    PRFFRQQRY,                          /* Preferred Sample frequency   */
    DYNPCMQRY,                          /* Dynamic PCM  select yes/no   */
    DYNCHNQRY,                          /* Dynamic chan select yes/no   */
    DYNFRQQRY,                          /* Dynamic freq select yes/no   */
} TMIQRY;

/************************************************************************/
/************************************************************************/
#define ENUPCM      enum _PCMTYP        /* Forward reference for PCMTYP */

/************************************************************************/
/*                  Callback procedure definitions                      */
/************************************************************************/
typedef enum _TMIPOL {
    TMIPOLBEG,                              /* Begin poll operation     */
    TMIPOLCNT,                              /* Continue poll? (yield)	*/
    TMIPOLPOS,                              /* Position poll (no yield) */
    TMIPOLEMP,                              /* Empty poll operation     */
    TMIPOLEND                               /* End poll operation       */
} TMIPOL;
typedef WORD  (FAR PASCAL *TMIPOLPRC)(TMIPOL,DWORD,DWORD);
typedef DWORD (FAR PASCAL *TMIDIOPRC)(TMIPOL,LPVOID,DWORD,WORD,DWORD,DWORD);

/************************************************************************/
/*                  TMI Resource Support Routines                       */
/************************************************************************/
WORD    FAR PASCAL TMIDLLIni (WORD, DWORD, DWORD);
WORD    FAR PASCAL TMISupVer (void);

TMIPRO  FAR PASCAL TMIDigEnu (TMIPRO, LPSTR, WORD);
ENUPCM  FAR PASCAL TMIPCMEnu (TMIPRO, ENUPCM);
WORD    FAR PASCAL TMIChnEnu (TMIPRO, ENUPCM, WORD);
DWORD   FAR PASCAL TMIFrqEnu (TMIPRO, ENUPCM, WORD, DWORD);
DWORD   FAR PASCAL TMICapQry (TMIPRO, DWORD, DWORD);

WORD    FAR PASCAL TMICfgLod (VISMEMHDL FAR *, LPCSTR, LPCSTR);
WORD    FAR PASCAL TMICfgRel (VISMEMHDL FAR *, LPCSTR, LPCSTR);
WORD    FAR PASCAL TMICfgMod (VISMEMHDL, WORD, DWORD);
WORD    FAR PASCAL TMICfgQry (VISMEMHDL);
        
WORD    FAR PASCAL TMISysIni (VISMEMHDL FAR *, VISMEMHDL);
WORD    FAR PASCAL TMISysUpd (VISMEMHDL, VISMEMHDL, WORD, DWORD);
BOOL    FAR PASCAL TMISysTrm (VISMEMHDL FAR *);
WORD    FAR PASCAL TMIDigAlo (VISMEMHDL FAR *, VISMEMHDL, HWND FAR *, WORD, WORD, HWND, DWORD); 
BOOL    FAR PASCAL TMIDigRel (VISMEMHDL FAR *);
WORD    FAR PASCAL TMILinOpn (WORD FAR *, HWND, VISMEMHDL, LPSTR, WORD);
BOOL    FAR PASCAL TMILinCls (WORD, HWND);

TMIPRO  FAR PASCAL TMIFilSta (VISMEMHDL, DWORD FAR *);
WORD    FAR PASCAL TMIFilPla (WORD, VISMEMHDL, WORD, WORD, DWORD, LPCSTR, TMIDIOPRC, DWORD, TMIPOLPRC, DWORD); 
WORD    FAR PASCAL TMIPlaBeg (VISMEMHDL);
WORD    FAR PASCAL TMIFilRec (WORD, VISMEMHDL, WORD, WORD, DWORD, LPCSTR, TMIDIOPRC, DWORD); 
WORD    FAR PASCAL TMIRecBeg (VISMEMHDL);
DWORD   FAR PASCAL TMIRecLvl (VISMEMHDL, LPVOID, DWORD);
DWORD   FAR PASCAL TMIFilPau (VISMEMHDL, WORD); 
DWORD   FAR PASCAL TMIFilTrm (VISMEMHDL); 


