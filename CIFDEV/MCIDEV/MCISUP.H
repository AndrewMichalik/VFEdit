/************************************************************************/
/* MCI Support Definitions: MCISup.h                    V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/*                  Array/String Length Constants                       */
/************************************************************************/
#define MCIMAXSTR      40               /* Gen purpose string length    */
#define MCIMAXMSG      81               /* Message Box string length    */
#define REGKEYLEN       8               /* Registration key length      */
#define SERSEGLEN       4               /* Serial number segment length */
#define MCIGLOBAS       0               /* File DLL global base msg     */
#define MCILOCBAS     256               /* File DLL local  base msg     */
#define WIOTIM_ID       1               /* Wave I/O timer ID            */
#define WIOTIMDEF     125               /* Wave I/O timer period (ms)   */

/************************************************************************/
/*              Global Data Structures Definitions                      */
/************************************************************************/
typedef struct _MCIGLO {
    char    szLibNam  [MCIMAXSTR];      /* Library name                 */
    char    RelKeyArr [REGKEYLEN];      /* Operating/Demo Only Key      */
    char    SeqNumArr [SERSEGLEN];      /* Op/Demo sequence number      */
    DWORD   ulDBxClr;                   /* Dlg box background RGB value */
    HANDLE  hLibIns;                    /* Global instance handle       */
    HBRUSH  hDBxBsh;                    /* Dlg box background brush     */
} MCIGLO;

/************************************************************************/
/*      These procedures are exported and called by Windows.            */
/************************************************************************/
LONG    FAR PASCAL  MCICBkWin (HWND, unsigned, WPARAM, LPARAM);
BOOL    FAR PASCAL  CfgEdtBox (HWND, unsigned, WPARAM, LPARAM);

/************************************************************************/
/*                          Resource Control                            */
/************************************************************************/
WORD    MCIResIni   (HANDLE);
WORD    MCIResTrm   (HANDLE);

/************************************************************************/
/*                              Queries                                 */
/************************************************************************/
WORD    GetDevCap (MCIPRO, DWORD FAR *);
WORD    GetDevNam (MCIPRO, LPSTR, WORD);

/************************************************************************/
/************************************************************************/
int WINAPI  MCIDspPrc (HWND, LPCSTR, LPCSTR, UINT);
long        GetPrfLng (LPCSTR, LPCSTR, WORD, long);
BOOL        WrtPrfLng (LPCSTR, LPCSTR, WORD, long);

/************************************************************************/
/************************************************************************/
#define SI_MCILIBNAM   "Media Control I/F"  /* Library name             */
#define SI_MCICBKCLS   "MCI DLL Callback"   /* Callback window class    */

#define SI_MCIWAVPRO   16 + MCILOCBAS   /* Protocol name                */
#define SI_MCIWAVGEN   17 + MCILOCBAS   /* Protocol generic device      */
#define SI_DBXBKGCLR   24 + MCILOCBAS   /* Dialog box bkg color         */

#define SI_MCICRECBK   32 + MCILOCBAS   /* Failed to create cbk win     */
#define SI_MCIOUTOPN   33 + MCILOCBAS   /* Failed to open wave out      */
#define SI_MCIINPOPN   34 + MCILOCBAS   /* Failed to open wave inp      */
#define SI_MCIWAVHDR   35 + MCILOCBAS   /* Unable to prep wave hdr      */
#define SI_MCIBLKREJ   36 + MCILOCBAS   /* Failed to write 1st blk      */
#define SI_MCIINSTIM   37 + MCIGLOBAS   /* Not enough Windows timers    */

/************************************************************************/
/*                      Generic profile strings                         */
/************************************************************************/
#define PI_LVLINP      48 + MCILOCBAS   /* Input volume level           */
#define PI_LVLOUT      49 + MCILOCBAS   /* Output volume level           */

/************************************************************************/
/************************************************************************/
#define DI_LVLINP       0x10            /* Input volume level           */    
#define DI_LVLOUT       0x12            /* Output volume level           */ 
