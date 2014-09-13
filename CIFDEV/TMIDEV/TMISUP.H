/************************************************************************/
/* Generic Media Control I/F Support Defs: TMISup.h     V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                  Array/String Length Constants                       */
/************************************************************************/
#define TMIMAXSTR      40               /* Gen purpose string length    */
#define TMIMAXMSG      81               /* Message Box string length    */
#define REGKEYLEN       8               /* Registration key length      */
#define SERSEGLEN       4               /* Serial number segment length */
#define TMIGLOBAS       0               /* TMI DLL global base msg      */
#define TMILOCBAS     512               /* TMI DLL local  base msg      */
#define DIOTIM_ID       1               /* Dig I/O timer ID             */
#define DIOTIMDEF     125               /* Dig I/O timer period (ms)    */
#define BYTMAXFIO  0xfc00L              /* Maximum file I/O byte count  */

/************************************************************************/
/*              Global Data Structures Definitions                      */
/************************************************************************/
typedef struct _TMIGLO {
    char    szLibNam  [TMIMAXSTR];      /* Library name                 */
    char    RelKeyArr [REGKEYLEN];      /* Operating/Demo Only Key      */
    char    SeqNumArr [SERSEGLEN];      /* Op/Demo sequence number      */
    DWORD   ulDBxClr;                   /* Dlg box background RGB value */
    HANDLE  hLibIns;                    /* Global instance handle       */
    HBRUSH  hDBxBsh;                    /* Dlg box background brush     */
} TMIGLO;

/************************************************************************/
/*                          Resource Control                            */
/************************************************************************/
WORD    TMIResIni   (HANDLE);
WORD    TMIResTrm   (HANDLE);

/************************************************************************/
/*      These procedures are exported and called by Windows.            */
/************************************************************************/
LONG FAR PASCAL TMICBkWin (HWND, unsigned, WPARAM, LPARAM);
BOOL FAR PASCAL RngWaiBoxPrc (HWND, unsigned, WPARAM, LPARAM);
BOOL FAR PASCAL CfgEdtBoxPrc (HWND, unsigned, WPARAM, LPARAM);

/************************************************************************/
/*                      Generic profile strings                         */
/************************************************************************/
#define SI_TMIBCMPRO       16 + TMILOCBAS   /* BiCom telephony          */
#define SI_TMIDLGPRO       17 + TMILOCBAS   /* Dialogic telephony       */
#define SI_TMINWVPRO       18 + TMILOCBAS   /* New Voice telephony      */
#define SI_TMIRTXPRO       19 + TMILOCBAS   /* Rhetorex telephony       */

#define SI_DBXBKGCLR       24 + TMILOCBAS   /* Dialog box bkg color     */

/************************************************************************/
/************************************************************************/
#define PI_VBSWIN          32 + TMILOCBAS   /* SW int address           */
#define PI_VBHWIR          33 + TMILOCBAS   /* HW int req number        */
#define PI_MXSWIN          34 + TMILOCBAS   /* SW int address           */
#define PI_MXHWIR          35 + TMILOCBAS   /* HW int req number        */
#define PI_LINENO          36 + TMILOCBAS   /* Line Number              */
#define PI_MAXSIL          37 + TMILOCBAS   /* Max sil duration (secs)  */
#define PI_MAXSND          38 + TMILOCBAS   /* Max snd duration (secs)  */
#define PI_MPXINP          39 + TMILOCBAS   /* Microphone Input on/ off */
#define PI_MPXLOC          40 + TMILOCBAS   /* Local conn on or off     */
#define PI_MPXOUT          41 + TMILOCBAS   /* Speaker Output on or off */
#define PI_SILCMP          42 + TMILOCBAS   /* Sil compress sens (msec) */
#define PI_AGCMOD          43 + TMILOCBAS   /* AGC mode                 */
#define PI_TRMOOH          44 + TMILOCBAS   /* Term on/off hook state   */
#define PI_WAICAL          45 + TMILOCBAS   /* Wait for call            */
                            
/************************************************************************/
/*                      Dialogic profile strings                        */
/************************************************************************/
#define PI_FLASH_CHAR      48 + TMILOCBAS   /* flash_char               */ 
#define PI_FLASH_TIME      49 + TMILOCBAS   /* flash_time               */ 
#define PI_PAUSE_TIME      50 + TMILOCBAS   /* pause_time               */ 
#define PI_DIGRATE         51 + TMILOCBAS   /* digrate                  */ 
#define PI_SCH_TM          52 + TMILOCBAS   /* sch_tm                   */ 
#define PI_P_BK            53 + TMILOCBAS   /* p_bk                     */ 
#define PI_P_MK            54 + TMILOCBAS   /* p_mk                     */ 
#define PI_P_IDD           55 + TMILOCBAS   /* p_idd                    */ 
#define PI_T_IDD           56 + TMILOCBAS   /* t_idd                    */ 
#define PI_OH_DLY          57 + TMILOCBAS   /* oh_dly                   */ 
#define PI_R_ON            58 + TMILOCBAS   /* r_on                     */ 
#define PI_R_OFF           59 + TMILOCBAS   /* r_off                    */ 
#define PI_R_IRD           60 + TMILOCBAS   /* r_ird                    */ 
#define PI_S_BNC           61 + TMILOCBAS   /* s_bnc                    */ 
#define PI_TTDATA          62 + TMILOCBAS   /* ttdata                   */ 
#define PI_MINPDON         63 + TMILOCBAS   /* minpdon                  */ 
#define PI_MINPDOFF        64 + TMILOCBAS   /* minpdoff                 */ 
#define PI_MINIPD          65 + TMILOCBAS   /* minipd                   */ 
#define PI_MINLCOFF        66 + TMILOCBAS   /* minlcoff                 */ 
#define PI_REDGE           67 + TMILOCBAS   /* redge                    */ 
#define PI_MAXPDOFF        68 + TMILOCBAS   /* maxpdoff                 */ 
                                                                        
#define PI_DTPL_DLY        69 + TMILOCBAS   /* dtpl_dly                 */ 
#define PI_DT_EDGE         70 + TMILOCBAS   /* dt_edge                  */ 
#define PI_DTRC_DLY        71 + TMILOCBAS   /* dtrc_dly                 */ 
#define PI_SB_SIZ          72 + TMILOCBAS   /* sb_siz                   */ 
#define PI_CSTINT          73 + TMILOCBAS   /* cstint                   */ 

#define SI_TMICBKCLS    "TMI DLL Callback"  /* Callback window class    */
#define SI_TMILIBNAM    "Telco Media"       /* Library name             */

/************************************************************************/
/*                      Configuration Dialog ID's                       */
/************************************************************************/
#define DI_VBSWIN       0x10             
#define DI_VBHWIR       0x12             
#define DI_MXHWIR       0x14             
#define DI_LINNUM       0x16             
#define DI_MPXINP       0x18             
#define DI_MPXOUT       0x1a             
#define DI_MPXLOC       0x1c             
#define DI_SILCMP       0x1e
#define DI_MAXSIL       0x20
#define DI_MAXSND       0x22
#define DI_AGCMOD       0x24
#define DI_WAICAL       0x25

