/************************************************************************/
/* Telco Media Display Msg Support Defs: TMIMsg.h       V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
int  WINAPI TMIDspPrc (HWND, LPCSTR, LPCSTR, UINT);
void        SetDlgItemHex (HWND, int, long);
long        GetDlgItemHex (HWND, int);
long        GetPrfLng (LPCSTR, LPCSTR, WORD, long);
BOOL        WrtPrfLng (LPCSTR, LPCSTR, WORD, long);

    /********************************************************************/
    /*                  TMI Library reported errors                     */
    /********************************************************************/
#define SI_TMIUNKMSG    0 + TMIGLOBAS   /* Unknown TMI message          */
#define SI_TMITIFMIS    1 + TMIGLOBAS   /* Module ver mismatch: TIF DLL */
#define SI_TMIINSREA    2 + TMIGLOBAS   /* Insufficient DOS real memory */
#define SI_TMISIZCHD    3 + TMIGLOBAS   /* Failed to size cached file   */
#define SI_TMIACCCHD    4 + TMIGLOBAS   /* Error accessing cached file  */
#define SI_TMICRECBK    5 + TMIGLOBAS   /* Failed to create cbk window  */
#define SI_TMIFSTBLK    6 + TMIGLOBAS   /* Failed to write first block  */
#define SI_TMIVBDWIO    7 + TMIGLOBAS   /* Voice brd wave I/O error %i  */
#define SI_TMIINSTIM    8 + TMIGLOBAS   /* Not enough Windows timers    */
#define SI_TMIBUFUND    9 + TMIGLOBAS   /* Buffer underflow; increase   */
#define SI_TMIEXTUND   10 + TMIGLOBAS   /* Extended underflow; increase */

    /********************************************************************/
    /*                  System reported errors                          */
    /********************************************************************/
#define SI_TMIUNKERR   32 + TMIGLOBAS   /* Unknown TMI error            */
#define SI_TMIUSEDEF   33 + TMIGLOBAS   /* Init Param Err, using defs   */
#define SI_TMISYSACT   34 + TMIGLOBAS   /* System Active, using defs    */
#define SI_TMINOLINI   35 + TMIGLOBAS   /* Cannot Initialize Line       */
#define SI_TMINOHOOK   36 + TMIGLOBAS   /* Cannot go on/off hook        */
#define SI_TMIBADVBD   37 + TMIGLOBAS   /* V board(s) failed self test  */
#define SI_TMIVBDINA   38 + TMIGLOBAS   /* V board(s) NOT active        */
#define SI_TMIVBHERR   39 + TMIGLOBAS   /* V board(s) hardware error    */
#define SI_TMIVBIERR   40 + TMIGLOBAS   /* V board int level not avail  */
#define SI_TMIDRIMEM   41 + TMIGLOBAS   /* V driver insufficient memory */
#define SI_TMIBADEMS   42 + TMIGLOBAS   /* V driver EMS missing/corrup  */
#define SI_TMIERREMS   43 + TMIGLOBAS   /* V driver EMS error           */
#define SI_TMIVBDERR   44 + TMIGLOBAS   /* V brd fail: Chk inst & set   */
#define SI_TMIMXINUL   45 + TMIGLOBAS   /* Mpx brd(s) not installed     */
#define SI_TMIMXIERR   46 + TMIGLOBAS   /* Mpx brd(s) int not avail     */
#define SI_TMIMXSTRT   47 + TMIGLOBAS   /* Mpx brd(s) already started   */
#define SI_TMIMXBERR   48 + TMIGLOBAS   /* Mpx brd fail: Chk inst & set */
                       
    /********************************************************************/
    /*                  TIFDLL reported errors                          */
    /********************************************************************/
#define TIFBASMSG      64 + TMIGLOBAS   /* TIF DLL base error           */
#define SI_TIFUNKMSG    0 + TIFBASMSG   /* TIF DLL unknown message      */
#define SI_EXTSUPERR    1 + TIFBASMSG   /* Cannot init Dos Extender sup */
#define SI_TSRNOTACT    2 + TIFBASMSG   /* DOS TSR not active           */
#define SI_INVLINNUM    3 + TIFBASMSG   /* Invalid line/port number     */
                        
#define CTLBASMSG      64 + TIFBASMSG   /* TIF CTL exec base error      */
#define SI_CTLINSMEM    0 + CTLBASMSG   /* Insufficient memory          */
#define SI_CTLFILNOF    2 + CTLBASMSG   /* File not found               */
#define SI_CTLPTHNOF    3 + CTLBASMSG   /* Path not found               */
#define SI_CTLLNKTSK    5 + CTLBASMSG   /* Attempt to link to task      */
#define SI_CTLSEPSEG    6 + CTLBASMSG   /* Library requires sep segs    */
#define SI_CTLAPLMEM    8 + CTLBASMSG   /* Insuff mem to load appl      */
#define SI_CTLWINVER   10 + CTLBASMSG   /* Incorrect Windows version    */
#define SI_CTLBADEXE   11 + CTLBASMSG   /* Invalid EXE file             */
#define SI_CTLOS2APP   12 + CTLBASMSG   /* OS/2 application             */
#define SI_CTLDOSAPP   13 + CTLBASMSG   /* Dos 4.0 Application          */
#define SI_CTLUNKEXE   14 + CTLBASMSG   /* Unknow EXE type              */
#define SI_CTLMODVER   15 + CTLBASMSG   /* Protected mode wrong version */
#define SI_CTLSECINS   16 + CTLBASMSG   /* Attempt to load second inst  */
#define SI_CTLEMSERR   17 + CTLBASMSG   /* Large frame EMS error        */
#define SI_CTLPROMOD   18 + CTLBASMSG   /* Attempt to load prot mode    */
#define SI_CTLPSPERR   33 + CTLBASMSG   /* Error setting PSP            */
#define SI_CTLWNDERR   34 + CTLBASMSG   /* Error setting window handle  */
                       
#define TMILSTMSG      34 + CTLBASMSG   /* TIF DLL last error           */








