 
 /**************************************************
 *                                                 *
 *   DDDDDD     4444    00000            HH   HH   *
 *   DD   DD   44 44   00   00           HH   HH   *
 *   DD   DD  44  44   00   00           HH   HH   *
 *   DD   DD  44  44   00   00           HHHHHHH   *
 *   DD   DD  4444444  00   00           HH   HH   *
 *   DD   DD      44   00   00   ..      HH   HH   *
 *   DDDDDD       44    00000    ..      HH   HH   *
 *                                                 *
 ***************************************************
 *   Version 3.20                       03/20/94   *
 **************************************************/


/* DIALOG/4x standard header for "C" */

#ifndef  byte
#define  byte   unsigned char
#endif

#ifndef  word
#define  word   unsigned short int
#endif

#ifndef  dword
#define  dword  unsigned long int
#endif

#pragma pack(1)

/*
 * Dialog/4x driver function codes
 */

#define  F_SSTART    1         /* System start                     */
#define  F_SPARMS    2         /* Set global parameters            */
#define  F_SSTOP     3         /* System stop                      */
#define  F_CHSTOP    4         /* Channel stop                     */
#define  F_CHSTAT    5         /* Get channel status block         */
#define  F_SETH      6         /* Set hook switch                  */
#define  F_SETCST    7         /* Set CST mask                     */
#define  F_CLRDT     8         /* Clear dtmf buffer                */
#define  F_GETDT     9         /* Get dtmf digit                   */
#define  F_RECB      10        /* Record to buffer                 */
#define  F_PLAYB     11        /* Playback from buffer             */
#define  F_RECF      12        /* Record to file                   */
#define  F_PLAYF     13        /* Playback from file               */
#define  F_DIAL      14        /* Dial string                      */
#define  F_GETDTS    15        /* Get dtmf string                  */
#define  F_GETEVT    16        /* Get next event                   */
#define  F_SCHED     18        /* Scheduler time slice             */
#define  F_XPLAYF    19        /* Extended play function           */
#define  F_PLAYGTG   20        /* General tone generation          */
#define  F_TNINFO    21        /* Get tone info                    */
#define  F_TNFLUSH   22        /* Flush tone info buffer           */
#define  F_GETCAR    27        /* Get the Call Analysis Results    */
#define  F_SXPARM    28        /* Set ext'd shared ram parms funct */
#define  F_SCPARM    29        /* Set channel parameters           */
#define  F_CALL      30        /* Call a numbr using call analysis */
#define  F_SETD      31        /* Set the digit control mask       */
#define  F_GETVER    32        /* Get the current driver vers numb */
#define  F_PLAYUB    34        /* Playback from a users envir bufr */
#define  F_RECUB     35        /* Record to a users envir buffer   */
#define  F_GETCOM    36        /* Get the comm area                */
#define  F_PUTCOM    37        /* Put the comm area                */
#define  F_STPARM    38        /* Set channel parameter            */
#define  F_WINK      39        /* Perform wink command             */
#define  F_ROUTETS   40        /* Perform timeslot routing         */
#define  F_ADDTONE   43        /* Add current tone to channel      */
#define  F_BUILDTONE 44        /* Build temporary tone             */
#define  F_DELTONES  45        /* Delete all tones from channel    */
#define  F_TNSTAT    46        /* Enable/disable tones             */
#define  F_XCALL     47        /* Call number(call analysis w/term)*/
#define  F_ADJSV     48        /* Adjust S/V conditions            */
#define  F_SETSVCOND 49        /* Set S/V adjustment conditions    */
#define  F_CLRSVCOND 51        /* Clear S/V adjust conditions      */
#define  F_GETCURSV  52        /* Get S/V adjustment conditions    */
#define  F_SETSVMT   53        /* Update S/V modification table    */
#define  F_GETSVMT   54        /* Read S/V modification table      */
#define  F_READQUAL  55        /* Read qualification template      */
#define  F_UPDQUAL   56        /* Write qualification template     */
#define  F_CHGCALLP  57        /* Change Call Analysis tones */
#define  F_SERNUM    59        /* Get the Serial number            */
#define  F_LISTEN    60        /* Get the Serial number            */
#define  MAXFCN      60        /* Max(last) Dialog\4x fcn number   */



#define  MINMFCN     80        /* Min(first) AMX8x fcn number      */
#define  F_MSTART    80        /* Start all AMX8x boards           */
#define  F_MOFF      81        /* Disconnect all AMX8x switches    */
#define  F_MMK       82        /* Connect the specified AMX8x chs  */
#define  F_MBRK      83        /* Disconnect the specified AMX8 ch */
#define  F_MMASK     84        /* Set AMX8x mask for a channel     */
#define  F_MSTOP     85        /* Stop all AMX8x boards            */
#define  F_RSTART    86        /* Start ringing an AMX8 connection */
#define  F_RSET      87        /* Set AMX81 ring parms for a conn  */
#define  MAXMFCN     87        /* Max(last) AMX8x fcn number       */

#define  MINID       129       /* Min AMX8x telephone station ID   */

/*
 * Values for STATUS byte in the CSB
 */
#define  S_STOP      0         /* Channel is stopped               */
#define  S_RECORD    1         /* Channel is in record mode        */
#define  S_PLAY      2         /* Channel is in playback mode      */
#define  S_GETDTS    3         /* Channel is getting a DTMF string */
#define  S_OFFH      4         /* Channel is waiting for offhook   */
#define  S_DIAL      5         /* Channel is dialing               */
#define  S_ONH       6         /* Channel is waiting for onhook    */
#define  S_CALL      7         /* Channel is in call analysis stat */
#define  S_PARM      8         /* Channel parameter is being upd   */
#define  S_WINK      9         /* Channel is waiting for wink cmpl */
#define  S_PLAYGTG   10        /* Channel is waiting for tone cmpl */

/*
 * Hook states
 */
#define  H_OFFH      0         /* Off hook                         */
#define  H_ONH       1         /* On hook                          */

/*
 * Values for termination types (last_term) and event type
 */
#define  T_NOTERM    0         /* No termination received          */
#define  T_MAXDT     1         /* Maximum DTMF digits received     */
#define  T_TERMDT    2         /* Terminating DTMF digit received  */
#define  T_STOP      3         /* User stop                        */
#define  T_DOSERR    4         /* Dos error                        */
#define  T_MAXBYT    5         /* Max bytes reached on play or rec */
#define  T_HFAIL     6         /* Hardware failure                 */
#define  T_TIME      7         /* Multi-tasking function timed out */
#define  T_OFFH      8         /* Offhook complete                 */
#define  T_DIAL      9         /* Dialing complete                 */
#define  T_SIL       10        /* Maximum silence received         */
#define  T_EOF       11        /* Eof reached on playback          */
#define  T_LCTERM    12        /* Terminate by drop in loop signal */
#define  T_DFULL     13        /* Disk full                        */
#define  T_ONH       14        /* Onhook complete                  */
#define  T_MDTERM    17        /* AMX80 disconnect termination     */
#define  T_CATERM    18        /* Call analysis termination        */
#define  T_LCREV     19        /* Loop signal battery reversal     */
#define  T_LC        20        /* Loop signal drop event           */
#define  T_RING      21        /* Rings received                   */
#define  T_SILOFF    22        /* Silence off                      */
#define  T_SILON     23        /* Silence on                       */
#define  T_AMXCON    24        /* AMX8x channel connect            */
#define  T_AMXDIS    25        /* AMX8x channel disconnect         */
#define  T_LCON      26        /* Loop signal on event             */
#define  T_MAXRNG    27        /* Max rings reached on AMX81 conn  */
#define  T_MCTERM    28        /* Rings termiated by AMX8 connect  */
#define  T_MDTMF     29        /* Terminated by masked DTMF digit  */
#define  T_IDTIME    30        /* Interdigit delay exceeded        */
#define  T_NSIL      31        /* Terminated by a max non-silence  */
#define  T_BUFFUL    32        /* Termination from EMS buffer full */
#define  T_BUFEMP    33        /* Terminated from EMS buffer empty */
#define  T_EMSERR    34        /* Terminated by EMS error          */
#define  T_EMSLOW    35        /* EMS buffer low                   */
#define  T_EMSHI     36        /* EMS buffer high                  */
#define  T_STPARM    37        /* Parameter updated                */
#define  T_WINK      38        /* Wink protocol complete           */
#define  T_WKRECV    39        /* Wink received                    */
#define  T_DTMF      40        /* DTMF digit received              */
#define  T_TONEON    41        /* Tone on detect                   */
#define  T_TONEOFF   42        /* Tone off detect                  */
#define  T_BADTERM   43        /* Invalid termination condition    */
#define  T_MTONEON   44        /* Terminated by Tone On            */
#define  T_MTONEOFF  45        /* Terminated by Tone Off           */
#define  T_CAERROR   46        /* Call progress error              */
#define  T_TGERR     47        /* Tone generation template error   */
#define  T_TGCMPLT   48        /* Tone generation complete         */
#define  T_ADSIERR   49        /* ADSI protocol failure            */
#define  MAXTERM     49        /* Max(last) termination type       */

/*
 * Values for system mode
 */
#define  SM_POLL     0         /* Polled mode                      */
#define  SM_EVENT    1         /* Event driven mode                */

/*
 * Equates for error (return) codes
 */
#define  E_SUCC      0         /* Function was successful          */
#define  E_FAILST    1         /* Board failed self test           */
#define  E_NODT      2         /* Dtmf buffer empty                */
#define  E_SACT      3         /* System already active            */
#define  E_SNACT     4         /* System not active                */
#define  E_BADDL     5         /* D4x hardware error               */
#define  E_BADFCN    6         /* Invalid function code requested  */
#define  E_BADINT    7         /* Interrupt level not available    */
#define  E_BADDCB    8         /* DCB parmameter error             */
#define  E_BADCH     9         /* Invalid channel number           */
#define  E_MTACT     10        /* Multitasking func already active */
#define  E_MTNACT    11        /* Multitasking function not active */
#define  E_BADPAR    12        /* Bad parameter                    */
#define  E_BADVER    13        /* Incorrect version of firmware    */
#define  E_NOTIMP    14        /* Function not implemented/avail   */
#define  E_NOTERM    15        /* Terminating cond not specified   */
#define  E_NOMEM     16        /* Insufficent buffer mem available */
#define  E_DOSERR    24        /* DOS error (DOS error code in al) */
#define  E_DSKCNT    25        /* Error in data read/wrote to disk */
#define  E_NOAMX     26        /* No AMX8x boards present          */
#define  E_AMXON     27        /* AMX 8xs already started          */
#define  E_AMXOFF    28        /* AMX 8xs already stopped          */
#define  E_BADXY     29        /* Invalid X,Y coordinate           */
#define  E_BADPRT    30        /* Bad AMX8x tel. station ID specified */
#define  E_BADCUR    31        /* Bad cursor position specified    */
#define  E_EMSSW     32        /* EMM not installed or corrupted   */
#define  E_EMSERR    33        /* EMM reported error               */
#define  E_NOVBUF    34        /* No buffer alloc for EMS ram disk */
#define  E_TSBADSLOT 35        /* Bad timeslot number              */
#define  E_TIMEOUT   36        /* Timer expired                    */
#define  E_BADPROD   37        /* Not supported by this product    */
#define  E_TONEID    38        /* Bad tone template id             */
#define  E_TNPARM    39        /* Invalid param in tone template   */
#define  E_MAXTMPLT  40        /* Max tone detection templates     */
#define  E_MAXSVCB   41        /* Invalid number of SVCB blocks    */
#define  E_SVMTTYPE  42        /* Invalid table type specified     */
#define  E_SVMTRANGE 43        /* Entry in SVMT was out of range   */
#define  E_BADSVCB   44        /* Invalid SV condition block(SVCB) */
#define  E_BADADJSIZ 45        /* Invalid SV adjustment size       */
#define  E_QUALID    46        /* bad qualification template id */

/*
 * Equates for cst_mask
 */
#define  C_LC        0x01      /* Loop signal drop                 */
#define  C_RING      0x02      /* Rings received                   */
#define  C_SILOFF    0x04      /* Silence off                      */
#define  C_SILON     0x08      /* Silence on                       */
#define  C_OFFH      0x10      /* Offhook complete                 */
#define  C_ONH       0x20      /* Onhook complete                  */
#define  C_LCON      0x40      /* Loop signal on                   */
#define  C_WKRECV    0x80      /* Recv incoming wink               */
#define  C_LCREV     0x100     /* Loop signal reversal             */

/*
 * Equates for set parameter function
 */
#define  CH_WKDLY    0x204     /* Delay before sending wink */
#define  CH_WKOUT    0x205     /* Duration of outgoing wink */
#define  CH_WKMIN    0x206     /* Min on for wink detection */
#define  CH_WKMAX    0x207     /* Max on for wink detection */
#define  RATE_PLAY  0x0E01     /* Parm id for playback sampling rate */
#define  RATE_REC   0x0E02     /* Parm id for record sampling rate   */
#define  WALLPARM   0x0E03     /* Parm id for wall parameter         */
#define  CH_MINREVON  0x419    /* Min LC reversal on time   */
#define  CH_MINREVOFF 0x419    /* Min LC reversal off time  */
                              
#define  SR_6K      6000       /* Parm value for 6KHz */
#define  SR_8K      8000       /* Parm value for 8KHz */

/*
 * Equates for digit_ctl_mask
 */
#define  D_DTMF      1         /* DTMF digit detection enable      */
#define  D_LPD       2         /* Loop pulse digit detect enabled  */
#define  D_DPDZ      8         /* Dial pulse detection with zero training */
#define  D_DPD       16        /* Dial pulse detection without zero training */

/*
 * Equates for digit_ctl_type
 */
#define  DT_FLUSH    1         /* Flush dtmf digit buffer          */
#define  DT_QUEUE    2         /* Put dtmf digits onto event queue */


/*
 * Equates for channel error conditions
 */
#define  X_NOERR     0         /* No error                         */
#define  X_BUFERR    1         /* Error occurred                   */


/*
 * Record mode types  (bit mapped)
 */
#define  RM_NORM     0         /* Normal record                    */
#define  RM_SCOMP    1         /* Compress sil. from incoming data */
#define  RM_RDISK    4         /* I/O from an EMS ram disk         */
#define  RM_ALAW     0x10      /* Record A-law data                */
#define  RM_ADPCM    0         /* ADPCM encoding                   */
#define  RM_PCM      0x100     /* Mu Law PCM mode                  */
#define  RM_SR8      0x200     /* 8KHz sampling rate               */
#define  RM_NOAGC    0x400     /* Turn off AGC                     */
#define  RM_SR6      0x800     /* 6KHz sampling rate               */
#define  RM_DOSBUF   0x01      /* Use DOS buffers for recuser      */


/*
 * Play mode types    (bit mapped)
 */
#define  PM_NORM     0         /* Normal playback                  */
#define  PM_NDX      1         /* Indexed playback                 */
#define  PM_RDISK    4         /* I/O from an EMS ram disk         */
#define  PM_FILES    8         /* Multiple file handles for index play */
#define  PM_ALAW     0x10      /* Play A-law data                  */
#define  PM_ADPCM    0         /* ADPCM encoded file               */
#define  PM_PCM      0x100     /* Mu Law PCM encoded file          */
#define  PM_SR8      0x200     /* 8KHz sampled file                */
#define  PM_SR6      0x800     /* 6KHz sampled file                */
#define  PM_ADSI     0x2000    /* ADSI data transfer               */
#define  PM_RAW      0x4000    /* Raw PCM mode                     */
#define  PM_DOSBUF   0x01      /* Use DOS buffers for playuser     */

/*
 * Bit mask for rwb_flags in RWB
 */
#define  RW_DINIT    1         /* Touch tone initiation on/off     */
#define  RW_TONE     2         /* Tone before rec/playback on/off  */
#define  RW_DELAY    4         /* Inter-digit delay starts on first digit */
#define  RW_10MSEC   8         /* 10 msec unit for maxsec (-y option) */
#define  RW_100MSEC  0x10      /* 100 msec unit for maxsec (-y option) */


/*
 * Bit mask for AMX8x event mask
 */
#define  A_CON       1         /* AMX8x connect (pickup)           */
#define  A_DIS       2         /* AMX8x disconnect (hangup)        */


/*
 * Bit mask for line status register
 */
#define  LS_CARNG    0x04      /* Call analysis detecting ring     */
#define  LS_HOOK     0x08      /* Hook status bit                  */
#define  LS_RING     0x10      /* Ring current bit                 */
#define  LS_LOOP     0x20      /* Loop current bit                 */
#define  LS_TT       0x40      /* Touch tone is waiting to be read */
#define  LS_SIL      0x80      /* Silence bit                      */


/*
 * Call Analysis termination data types/call status values
 */
#define  CA_BUSY     7         /* Called line is busy              */
#define  CA_NOAN     8         /* Called line did not answer       */
#define  CA_NORNG    9         /* Called line did not ring         */
#define  CA_CONN     10        /* Called line connected            */
#define  CA_OPINT    11        /* Called line recvd oper intercept */
#define  CA_NODIALTONE  17     /* Called line recvd no dialtone    */
#define  CA_FAXTONE  18        /* Called line recvd fax tone       */

/* 
 * Call Analysis connection type
 */
#define  CON_CAD     1         /* Cadence break            */
#define  CON_LPC     2         /* Loop current drop        */
#define  CON_PVD     3         /* Positive Voice Detection */
#define  CON_PAMD    4         /* Positive Answering Machine Detection */

/* 
 * Call Analysis CPB intflg
 */
#define  OPTEN       1         /* Enable operator intercept w/connect   */
#define  OPTDIS      2         /* Disable operator                      */
#define  OPTCON      3         /* Enable operator intercept w/o connect */
#define  PVD_ENABLE  4         /* Enable Positive Voice Detection(PVD)  */
#define  PVD_OPTEN   5         /* Enable PVD + OPTEN                    */
#define  PVD_OPTCON  6         /* Enable PVD + OPTCON                   */
#define  PAMD_ENABLE 7         /* Enable PAMD w/ no Operator intercept  */
#define  PAMD_OPTEN  8         /* Enable PAMD with Operator intercept   */

/* 
 * Call Analysis error codes
 */
#define  MEMERR      1         /* Out of memory trying to create SIT    */
#define  TMOUTON     2         /* Timeout waiting for a SIT tone        */
#define  TMOUTOFF    3         /* SIT tone too long                     */
#define  UNEXPTN     4         /* Unexpected SIT tone                   */
#define  MAXFRQERR   5         /* Invalid mxtimefrq field in CPB far */
#define  UPFRQERR    6         /* Invalid upper frequency selection     */
#define  LGTUERR     7         /* Lower frequency > upper frequency     */
#define  OVRLPERR    8         /* Overlap in selected SIT tones         */

/*
 * Masked DTMF termination/initiation equates
 */
#define  DM_D        0x0001    /* Mask for DTMF d. */
#define  DM_1        0x0002    /* Mask for DTMF 1. */
#define  DM_2        0x0004    /* Mask for DTMF 2. */
#define  DM_3        0x0008    /* Mask for DTMF 3. */
#define  DM_4        0x0010    /* Mask for DTMF 4. */
#define  DM_5        0x0020    /* Mask for DTMF 5. */
#define  DM_6        0x0040    /* Mask for DTMF 6. */
#define  DM_7        0x0080    /* Mask for DTMF 7. */
#define  DM_8        0x0100    /* Mask for DTMF 8. */
#define  DM_9        0x0200    /* Mask for DTMF 9. */
#define  DM_0        0x0400    /* Mask for DTMF 0. */
#define  DM_S        0x0800    /* Mask for DTMF *. */
#define  DM_P        0x1000    /* Mask for DTMF #. */
#define  DM_A        0x2000    /* Mask for DTMF a. */
#define  DM_B        0x4000    /* Mask for DTMF b. */
#define  DM_C        0x8000    /* Mask for DTMF c. */

/*
 * GTD Amplitude define
 */
#define  GT_DEF_MIN   -50      /* Minimum default amplitude */
#define  GT_DEF_MAX     0      /* Maximum default amplitude */

/*
 * Speed and Volume(S/V) Control
 */
#define  SV_SPEEDTBL   0x01    /* Modify speed */
#define  SV_VOLUMETBL  0x02    /* Modify volume */
                       
#define  SV_ABSPOS     0x00    /* Absolute position */
#define  SV_RELCURPOS  0x10    /* Relative position from current position */
#define  SV_TOGGLE     0x20    /* Toggle */
                       
#define  SV_WRAPMOD    0x0010  /* S/V Modification Table wraparound enable */
#define  SV_SETDEFAULT 0x0020  /* Reset to default S/V Modification Table */
#define  SV_LEVEL      0x0100  /* Digit level sensitive */
#define  SV_BEGINPLAY  0x0200  /* Apply play adjustment at beginning of each playback */

/*
 * S/V toggle modes for Play Adjustment Conditions
 */
#define  SV_TOGORIGIN  0x00    /* Toggle between origin and last modified position */
#define  SV_CURORIGIN  0x01    /* Reset current position to the origin */
#define  SV_CURLASTMOD 0x02    /* Reset current position to last modified position */
#define  SV_RESETORIG  0x03    /* Reset current position and last modified state to origin */

/*
 * S/V defines for far pascal dl_addspddig()
 */
#define  SV_ADD10PCT      1    /* Speed up playback 10 percent     */
#define  SV_ADD20PCT      2    /* Speed up playback 20 percent     */
#define  SV_ADD30PCT      3    /* Speed up playback 30 percent     */
#define  SV_ADD40PCT      4    /* Speed up playback 40 percent     */
#define  SV_ADD50PCT      5    /* Speed up playback 50 percent     */
#define  SV_SUB10PCT     -1    /* Slow down playback 10 percent    */
#define  SV_SUB20PCT     -2    /* Slow down playback 20 percent    */
#define  SV_SUB30PCT     -3    /* Slow down playback 30 percent    */
#define  SV_SUB40PCT     -4    /* Slow down playback 40 percent    */
#define  SV_SUB50PCT     -5    /* Slow down playback 50 percent    */
#define  SV_NORMAL     0xFF    /* Set playback to normal speed/vol */

/*
 * S/V defines for far pascal dl_addvoldig()
 */
#define  SV_ADD2DB        1    /* Increase volume of playback 2dB */
#define  SV_ADD4DB        2    /* Increase volume of playback 4dB */
#define  SV_ADD6DB        3    /* Increase volume of playback 6dB */
#define  SV_ADD8DB        4    /* Increase volume of playback 8dB */
#define  SV_SUB2DB       -1    /* Decrease volume of playback 2dB */
#define  SV_SUB4DB       -2    /* Decrease volume of playback 4dB */
#define  SV_SUB6DB       -3    /* Decrease volume of playback 6dB */
#define  SV_SUB8DB       -4    /* Decrease volume of playback 8dB */

/*
 * Tone definitions for Call Analysis
 */
#define  TID_FIRST     250
#define  TID_DIAL_LCL  250
#define  TID_DIAL_INTL 251
#define  TID_DIAL_XTRA 252
#define  TID_BUSY1     253
#define  TID_RNGBK1    254
#define  TID_BUSY2     255
#define  TID_RNGBK2    256
#define  TID_FAX1      258
#define  TID_FAX2      259
#define  TID_LAST      259

/*
 * PAMD decision type (spdval field of the CPB)
 */
#define  PAMD_FULL     1      /* Wait for full decision (after ansrsize) */
#define  PAMD_QUICK    2      /* Decide as soon as voice decides         */

#define  PAMD_QUAL1TMP 11     /* PAMD Qualifcation template              */     
#define  PAMD_QUAL2TMP 12     /* PAMD Qualifcation template              */     

/*
 * Call Analysis Tone classes
 */
#define  TNTYP_RNGBACK   1     /* Ringback Class                         */
#define  TNTYP_BUSY      2     /* Busy Class                             */
#define  TNTYP_FAX       3     /* FAX tone Class                         */

/*
 * Battery Reversal equates
 */
#define  LC_NORM2REV     0
#define  LC_REV2NORM     1


/*
 * Channel Parameter Block structure
 */
#define  CPB_SIZE    128       /* Size of CPB in bytes  */

typedef struct {
   byte dtpl_dly;              /* Playback DTMF delay in 10ms intervals  */
   byte dt_edge;               /* DTMF message edge select               */
   word dtrc_dly;              /* Record DTMF delay in 10ms intervals    */
   word sb_siz;                /* Silence buffer size for this channel   */
   byte nbrdna;                /* # of rings before no answer            */
   word stdely;                /* Delay after dialing before analysis    */
   word cnosig;                /* Duration of no signal time out delay   */
   word lcdly;                 /* Delay after dial before lc drop connect*/
   word lcdly1;                /* Delay after lc drop con. before msg    */
   byte hedge;                 /* Edge of answer to send connect message */
   word cnosil;                /* Initial continuous noise timeout delay */
   byte lo1tola;               /* % acceptable pos. dev of short low sig */
   byte lo1tolb;               /* % acceptable neg. dev of short low sig */
   byte lo2tola;               /* % acceptable pos. dev of long low sig  */
   byte lo2tolb;               /* % acceptable neg. dev of long low sig  */
   byte hi1tola;               /* % acceptable pos. dev of high signal   */
   byte hi1tolb;               /* % acceptable neg. dev of high signal   */
   word lo1bmax;               /* Maximum interval for shrt low for busy */
   word lo2bmax;               /* Maximum interval for long low for busy */
   word hi1bmax;               /* Maximum interval for 1st high for busy */
   byte nsbusy;                /* Num. of highs after nbrdna busy check  */
   word logltch;               /* Silence deglitch duration              */
   word higltch;               /* Non-silence deglitch duration          */
   word lo1rmax;               /* Max. short low  dur. of double ring    */
   word lo2rmin;               /* Min. long low  dur. of double ring     */
   byte intflg;                /* Operator intercept mode                */
   byte intfltr;               /* Minimum signal to qualify freq. detect */
   byte cpbrfu1[14];           /* Reserved for future use                */
   word spdeb;                 /* Trailing edge silence ptr debounce     */
   word hisiz;                 /* Used to determine which lowmax to use  */
   word alowmax;               /* Max. low before con. if high >hisize   */
   word blowmax;               /* Max. low before con. if high <hisize   */
   byte nbrbeg;                /* Number of rings before analysis begins */
   word hi1ceil;               /* Maximum 2nd high dur. for a retrain    */
   word lo1ceil;               /* Maximum 1st low dur. for a retrain     */
   word lowerfrq;              /* Lower allowable frequency in Hz        */
   word upperfrq;              /* Upper allowable frequency in Hz        */
   byte timefrq;               /* Total duration of good signal required */
   byte rejctfrq;              /* Allowable % of bad signal              */
   word maxansr;               /* Maximum duration of answer             */
   word ansrdgl;               /* Silence deglitching value for answer   */
   byte pvdmxper;              /* Percent of maximum sum                 */
   word pvdszwnd;              /* Length of window in 10ms               */
   word pvddly;                /* Delay time before starting PVD for each nonsilence in 10ms */
   word mxtimefrq;             /* Max. time for first frequency to remain in bound */
   word lower2frq;             /* Lower bound for second frequency       */
   word upper2frq;             /* Upper bound for second frequency       */
   word time2frq;              /* Min. time for second frequency to remain in bound */
   word mxtime2frq;            /* Max. time for second frequency to remain in bound */
   word lower3frq;             /* Lower bound for third frequency        */
   word upper3frq;             /* Upper bound for third frequency        */
   word time3frq;              /* Min. time for third frequency to remain in bound */
   word mxtime3frq;            /* Max. time for third frequency to remain in bound */
   word dtn_pres;              /* length of valid dialtone  (1 sec)      */
   word dtn_npres;             /* max time to wait for dial tone (3 sec) */
   word dtn_deboff;            /* dialtone off debouncer (100 msec)      */
   word pamd_failtime;         /* Wait for PAMD/PVD after cadence break (4 sec) */
   word pamd_minring;          /* Min. allowable ring duration (1.9 sec) */
   byte pamd_spdval;           /* full/quick PAMD decision (1 - full)    */
   byte pamd_qtemp;            /* Qualification to use for PAMD(11)      */
   word noanswer;              /* noanswer after 1st far pascal ring(30sec)        */
   word maxintering;           /* intering delay before connect (8sec)   */
   byte cpbrfu[CPB_SIZE-117];  /* Reserved for future use                */
   } CPB;


/*
 * DIALOG/4x Control Block data structure
 */
#define  DCB_SIZE    128       /* Size of DCB far */

typedef struct {
   byte flashchr;              /* Flash char in dialing string           */
   word flashtm;               /* Flash time 10ms units                  */
   word pausetm;               /* Pause time 10ms units                  */
   word digrate;               /* Digitizing rate in Hz                  */
   word sch_tm;                /* Maximum time slice given to scheduler  */
   word p_bk;                  /* Pulse break interval in 10ms units     */
   word p_mk;                  /* Pulse make interval in 10ms units      */
   word p_idd;                 /* Pulse dial inter-digit delay in 10ms   */
   word t_idd;                 /* Tone dial inter-digit delay in 10ms    */
   word oh_dly;                /* Offhook delay interval in 10 ms        */
   word r_on;                  /* Min. ring on interval in 100ms units   */
   word r_off;                 /* Min. ring off interval in 100ms units  */
   word r_ird;                 /* Delay after ring cnt is reset in 100ms */
   word s_bnc;                 /* Sil. message debounce interval in 10ms */
   word dcbrfu1;               /* Reserved for future use                */
   byte ttdata;                /* Duration of DTMF digit in 10ms units   */
   byte minpdon;               /* Min. dur. for lc on for a valid pulse  */
   byte minpdoff;              /* Min. dur. for lc off for a valid pulse */
   word minipd;                /* Min. interpulse digit time for lc on   */
   word minlcoff;              /* Min. dur. of lc off for CST_CUR_ON     */
   byte dcbrfu2[4];            /* Reserved for future use                */
   byte redge;                 /* Ring edge                              */
   word maxpdoff;              /* Max. dur. for pd make                  */
   byte dcbrfu[DCB_SIZE-43];   /* Reserved for future use                */
   } DCB;

#define  dcbrfu3  redge        /* backward compatible redge name         */


/*
 * Channel status block data structure
 */

#define  CSB_SIZE    32        /* Size of CSB far */

typedef struct {
   word cstmask;              /* Call status interupt mask              */
   byte status;               /* Current channel status                 */
   byte cherr;                /* Set if buffer under/overflow detected  */
   byte mtfcn;                /* Multitasking function in progress      */
   word lastterm;             /* Last termination event                 */
   word bufcnth;              /* High order data transfer count         */
   word bufcnt;               /* Low order data transfer count          */
   byte dtmfrcvd;             /* Number of DTMFs in ch.'s DTMF buffer   */
   word doserr;               /* Last DOS error                         */
   byte linestat;             /* Current line status                    */
   word callstat;             /* Call Analysis termination type         */
   word intrfreq;             /* Intercept frequency in 20 Hz           */
   byte dig_mask;             /* Digit control mask                     */
   byte csbrfu1;              /* Reserved for future use                */
   byte csbrfu[CSB_SIZE-21];  /* Reserved for future use                */
   } CSB;


/*
 * Read/Write block structure
 */

#define  RWB_SIZE    32        /* Size in bytes of RWB far */
#define  XRWB_SIZE   64        /* Size in bytes of XRWB                 */

typedef struct {
   word filehndl;              /* Open DOS handle for file transfer     */
   word xferoff;               /* Transfer buffer address offset        */
   word xferseg;               /* Transfer buffer address segment       */
   word maxbyteh;              /* High order max # of bytes to xfer     */
   word maxbyte;               /* Low order max # of bytes to xfer      */
   word maxsec;                /* Max # of secs before timeout term     */
   byte maxdtmf;               /* Max # of DTMF digits to cause term    */
   byte termdtmf;              /* DTMF digit which will cause term      */
   byte maxsil;                /* Seconds of silence to cause term      */
   byte loopsig;               /* Terminate on drop in loop current     */
   word indexoff;              /* Index table address offset            */
   word indexseg;              /* Index table address segment           */
   byte rwbflags;              /* Record/Playback initiation bits       */
   byte rwbdata1;              /* Initiation tone duration (bits 0-3)   */
   byte amxterm;               /* Terminating AMX telephone station ID  */
   word curpos;                /* Low order cursor position             */
   word curposh;               /* High order cursor position            */
   byte isxrwb;                /* Extended RWB flag                     */
   byte rwbrfu2[RWB_SIZE-28];  /* Reserved for future use               */

/*
 * Extended RWB fields
 */
   word emsmode;               /* Playuser/recuser mode field           */
   byte xrwbrfu1[4];           /* Reserved for future use               */
   word dtinit;                /* DTMF function initiator set           */
   word dtterm;                /* DTMF function terminator set          */
   byte intrdig;               /* Maximum interdigit delay in secs      */
   byte maxnsil;               /* Max # of secs of non-sil to cause term*/
   word emsthrsh;              /* Min byte count before warning         */
   word trmdig_cnt;            /* Count of entries in the digit termination array */
   word trmdig_ofs;            /* Offset of digit termination array     */
   word trmdig_seg;            /* Segment of digit termination array    */
   word toneon_cnt;            /* Count of entries in the tone on termination array */
   word toneon_ofs;            /* Offset of tone on termination array   */
   word toneon_seg;            /* Segment of tone on termination array  */
   word tonoff_cnt;            /* Count of entries in the tone off termination array */
   word tonoff_ofs;            /* Offset of tone off termination array  */
   word tonoff_seg;            /* Segment of tone off termination array */
   byte xrwbrfu[XRWB_SIZE-32]; /* Reserved for future use               */
   } RWB;


/*
 * Call analysis results structure
 */

#define  CAR_SIZE    32        /* Size of the structure  */

typedef struct {
   byte termtype;              /* Last call progress term. for this ch  */
   byte frqout;                /* Percent of frequency out of bounds    */
   word frqherz;               /* Frequency detected in Hz              */
   word sizehigh;              /* Dur. of non-silent period. 10ms units */
   word shortlow;              /* Dur. of shorter silent period         */
   word longlow;               /* Duration of longer silent period      */
   word ansrsize;              /* Duration of answer in 10ms units      */
   byte conntype;              /* Connection type                       */
   byte dtnfail;               /* Dial Tone failure character           */
   word freqdur;               /* The duration of the first frequency   */
   word frqherz2;              /* The frequency of the second tone      */
   word freqdur2;              /* The duration of the second frequency  */
   word frqherz3;              /* The frequency of the third tone       */
   word freqdur3;              /* The duration of the third frequency   */
   word stoptype;              /* reason for Call Progress stop         */
   word tone_id;               /* The tone ID that caused termination   */
   byte carrfu[CAR_SIZE-28];   /* Reserved for future use               */
   } CAR;


/*
 * Application to Device Driver Communication Area
 */

#define  ADCCB_SIZE  32

typedef struct {
   unsigned long a_d_bct;
   char          a_d_rfu[ADCCB_SIZE-4];
   } ADCCB;


/*
 * Device Driver to Application Communication Area
 */

#define  DACCB_SIZE  32

typedef struct {
   unsigned long d_a_bct;
   char          d_a_rfu[DACCB_SIZE-4];
   } DACCB;



/*
 * IDDS system function codes
 */
#define  MIDDSFN     0x70      /* Min(first) IDDS function   */
#define  F_DEVSRV    0x70      /* Device level services      */
#define  F_EXESRV    0x71      /* Executive level services   */
#define  F_DEVCOM    0x75      /* Application level services */
#define  MXIDDSFN    0x75      /* Max(last) IDDS function    */

/*
 * Service function Executive level services function codes
 */
#define  MSEXESFN    0x00      /* Min(first) IDDS function          */
#define  FI_APSCH    0x00      /* Inform appl of scheduler entry    */
#define  FI_APACT    0x01      /* Inform appl of scheduler activity */
#define  FI_APEVT    0x02      /* Inform appl of event queue entry  */
#define  MXEXESFN    0x02      /* Max(last) IDDS function           */

/*
 * Service function Device level services function codes
 */
#define  MSDEVSFN    0x00      /* Min (first) IDDS function */
#define  FI_REGDRV   0x00      /* Register driver */
#define  FI_SIZEQ    0x01      /* Get the memory requirements of a Q */
#define  FI_OPENQ    0x02      /* Request to open a Q */
#define  FI_PUTQ     0x03      /* Enqueue a message */
#define  FI_GETQ     0x04      /* Get a message off a Q */
#define  FI_EMPTYQ   0x05      /* Empty a queue */
#define  FI_FLUSHQ   0x06      /* Flush 1 entry from the queue */
#define  FI_SCANQ    0x07      /* Scan the queue for a value */
#define  FI_GETLVL   0x08      /* Get the h/w interrupt level */
#define  FI_PUTLVL   0x09      /* Store the hardware intr level */
#define  FI_INSINT   0x0A      /* Install drivers interrupt hndlr */
#define  FI_UININT   0x0B      /* De-install drivers h/w intr hndlr */
#define  FI_GETIV    0x0C      /* Get the interrupt vector */
#define  FI_PUTIV    0x0D      /* Install this interrupt vector */
#define  FI_GETMSG   0x0E      /* Get vector to the intr msg hdlr */
#define  FI_PUTMSG   0x0F      /* Install h/w intr msg hdlr */
#define  FI_PUT55    0x10      /* Install a 55ms timer */
#define  FI_DIS55    0x11      /* Deinstall a 55ms timer */
#define  FI_ISDRV    0x12      /* Determine if a driver is installed */
#define  FI_SCHED    0x13      /* Call the scheduler */
#define  FI_PAUSE    0x14      /* Wait for a real time interval */
#define  FI_UREG     0x15      /* Unregister a device */
#define  FI_GETREV   0x16      /* Get IDDS revision */
#define  FI_USREVT   0x17      /* Put user event onto event queue */
#define  FI_BEEP     0x18      /* Beep the speaker on error condition */
#define  MXDEVSFN    0x18      /* Max (last) IDDS function */


/*
 * IDDS error return codes
 */
#define  EI_SUCC     0         /* Function was successful   */
#define  EI_REGERR   113       /* Driver registration error */
#define  EI_BADHND   114       /* Bad handle                */
#define  EI_BADDEV   115       /* Bad device type specified */
#define  EI_MAXQS    116       /* Maximum number of queues  */
#define  EI_BADQT    117       /* Queue type error          */
#define  EI_QFULL    118       /* Queue full                */
#define  EI_QMPTY    119       /* Queue empty               */
#define  EI_BADFCN   120       /* Bad function              */
#define  EI_BADPAR   121       /* Bad parmeter              */
#define  EI_VECUSD   122       /* Vector already in use     */
#define  EI_NOIMP    123       /* Function not implemented  */


/*
 * Defined Device Types
 */

#define  DV_IDDS     1         /* IDDS device type  */
#define  DV_D40      2         /* D40 driver type   */

/*
 * User definable devices
 */
#define  DV_USER1   0x0F0      /* User defined device 1 */
#define  DV_USER2   0x0F1      /* User defined device 2 */
#define  DV_USER3   0x0F2      /* User defined device 3 */
#define  DV_USER4   0x0F3      /* User defined device 4 */
#define  DV_USER5   0x0F4      /* User defined device 5 */
#define  DV_USER6   0x0F5      /* User defined device 6 */
#define  DV_USER7   0x0F6      /* User defined device 7 */
#define  DV_USER8   0x0F7      /* User defined device 8 */


/*
 * Defined Q Types
 */
#define  Q_NRML     0          /* Non-prioriorized FIFO Q              */
#define  Q_NPSLL    1          /* Non-priority FIFO Single Linked List */

/*
 * Miscellaneous
 */
#define  Q_STDREQ    0         /* Standard request queue handle */
#define  Q_STDEVT    1         /* Standard event queue handle   */

 /*************************************************************************
 *
 * Event Block - Structure for the get event block function
 *
 **************************************************************************/

struct evtblk {
   unsigned short int  devtype; /* Device type             */
   unsigned short int  evtcode; /* Event code              */
   unsigned short int  evtdata; /* Event data              */
   unsigned short int  devchan; /* Channel                 */
   unsigned short int  memofst; /* Far pointer to the data */
   unsigned short int  memseg;  /*                         */
   unsigned short int  board;   /* Board number            */
   unsigned short int  rfu;     /* Reserved for future use */
   };

typedef struct evtblk EVTBLK;

/*
 * GLOBAL TONE DETECTION
 */

/*
 * Masks for functions far pascal dl_enbtone() and far pascal dl_distone()
 */
#define  TONE_ON  1           /* Enables/disables Tone On messages  */
#define  TONE_OFF 2           /* Enables/disables Tone Off messages */

#define  TONE_ALL 0xFFFF      /* Enables/disables ALL tone messages */

/*
 * Tone detection modes
 */
#define  TN_LEADING  0x0100   /* Leading edge detection  */
#define  TN_TRAILING 0x0200   /* Trailing edge detection */

/*
 * Miscellaneous GTD items
 */
#define  TN_DIGTYPE     5     /* Reserved digit type for user */


/*
 * GENERAL TONE GENERATION
 */

/*
 * Tone generation template
 */
typedef struct {
          unsigned short int tg_dflag;     /* Dual Tone - 1, Single Tone - 0    */
          unsigned short int tg_freq1;     /* Frequency for tone 1 (Hz)         */
          unsigned short int tg_freq2;     /* Frequency for tone 2 (Hz)         */
          short int          tg_ampl1;     /* Amplitude for tone 1 (dB)         */
          short int          tg_ampl2;     /* Amplitude for tone 2 (dB)         */
          short int          tg_dur;       /* Duration of generated tone (10ms) */
} TN_GEN;

/*
 * For use with tg_dflag parameter in TN_GEN
 */
#define  TN_SINGLE      0     /* Indicates single tone */
#define  TN_DUAL        1     /* Indicates dual tone   */


 /*************************************************************************
 *
 * Speed/Volume Adjustment Condition Block(SVCB)
 *
 **************************************************************************/

typedef struct {
   unsigned short type;    /* Type of adjustment                      */
   int            adjsize; /* Adjustment size                         */
   unsigned char  digit;   /* ASCII digit that causes play adjustment */
   unsigned char  digtype; /* Digit type                              */
} SVCB;

 /*************************************************************************
 *
 * Speed/Volume Modification Table(SVMT)
 *
 **************************************************************************/

typedef struct {
   char  decrease[10];     /*        */ 
   char  origin;           /* Origin */              
   char  increase[10];     /*        */
} SVMT;


 /*************************************************
 *                                                *
 * Tone Information Structure : INTERNAL use only *
 *                                                *
 *************************************************/

typedef struct {
   unsigned short int  tn_frqahi;   /* actual frequency in Hz of tone with higher amplitude */
   unsigned short int  tn_frqalo;   /* actual frequency in Hz of tone with lower amplitude */
   unsigned short int  tn_on;       /* actual on time (in 10 msec units) */
   unsigned short int  tn_off;      /* actual off time (in 10 msec units) */
   unsigned short int  tn_rep_cnt;  /* actual rep count */
} TN_INFO;

#define tn_freq1 tn_frqahi
#define tn_freq2 tn_frqalo

 /*******************************************************
 *                                                      *
 * Qualification Template Structure : INTERNAL use only *
 *                                                      *
 *******************************************************/
 
typedef struct {
     unsigned short int  q_nfrm;      /* no. of frames required to verify prior to energy drop */
     unsigned short int  q_snr0;      /* value of SNR required to begin suspecting tone */
     unsigned short int  q_snr1;      /* value of SNR required for all frames not dropping */
     unsigned short int  q_b0;        /* value of Broad required to begin suspecting tone */
     unsigned short int  q_b1;        /* value of Broad required for all frames not dropping */
     unsigned short int  q_trat;      /* maximum value of twist allowed */
     unsigned short int  q_qmax;      /* if fail talkoff, but pass qual qmax times, suspect */
     unsigned short int  q_tnfrm;     /* number of past frames to test talkoff with */
     unsigned short int  q_tflg;      /* talkoff flag */
     unsigned short int  q_minfrm;    /* min number of frames a tone must be present to verify */
     unsigned short int  q_zidflg;    /* zero inter digit delay flag */
     unsigned short int  q_oldprm;    /* set to 1 if old debounce parameters are to be used    */
   } TONE_QUAL;

typedef struct {
     unsigned short int  qminsnr;     /* minimum allowable SNR for voice */
     unsigned long  int  qmaxsnr;     /* maximum allowable SNR for voice */
     unsigned short int  maxpk;       /* maximum number of peaks for voice */
     unsigned short int  maxring;     /* maximum number of frames for ringback not voice */
     unsigned long  int  ringthres;   /* signal to noise ratio for ringback */
     unsigned short int  pvdwin;      /* number of frames in a window sample */
     unsigned long  int  pvdthresh;   /* minimum energy for voice */
     unsigned short int  pvdrblow;    /* lower frequency of ringback */
     unsigned short int  pvdrbhig;    /* upper frequency of ringback */
   } PVD_QUAL;

/*
 *	AMD Quality template structure
 */		
typedef struct {                         
   unsigned short int maxansiz;         /* Size of answer #1 */ 
   unsigned short int maxans2;
   unsigned short int maxans3;
   unsigned short int lohiss;           /* Low hiss (noise) range */ 
   unsigned short int hihiss;           /* High hiss (noise) */ 
   unsigned short int bhparm;           /* noise below hiss ratio */ 
   unsigned short int cvthr1;           /* cv. threshold #1 */ 
   unsigned short int cvthr2;
   unsigned short int maxcvth;          /* Maximum cv threshold */ 
   unsigned short int nmaxbrod;         /* Maximum broad band energy - noise */ 
   unsigned short int nmaxerg;          /* Maximum total energy - noise */ 
   unsigned short int maxsil;
   unsigned short int voice_thres;
   unsigned short int sil_thres;
   unsigned short int bandf_low;        /* Frequency Band filter, lower limit in hz */ 
   unsigned short int bandf_high;       /* upper limit in hz */ 
} AMD_QUAL;

typedef union {
   TONE_QUAL gen_qual;
   PVD_QUAL  pvd_qual;
   AMD_QUAL  amd_qual;
} TN_QLT;


 /***********************************************************
 *                                                          *
 *   DDDDDD     4444    00000   LL       IIIIII   BBBBBB    *
 *   DD   DD   44 44   00   00  LL         II     BB   BB   *
 *   DD   DD  44  44   00   00  LL         II     BB   BB   *
 *   DD   DD  44  44   00   00  LL         II     BBBBBB    *
 *   DD   DD  4444444  00   00  LL         II     BB   BB   *
 *   DD   DD      44   00   00  LL         II     BB   BB   *
 *   DDDDDD       44    00000   LLLLLL   IIIIII   BBBBBB    *
 *                                                          *
 ************************************************************
 *   Version 3.91                                03/20/94   *
 ***********************************************************/

/*
 * Defines for compatability to old d40lib versions.
 */
#define Sys_Start                _X_startsys
#define Set_Global_Params(S,O)   setgparm(O)
#define Sys_Stop                 _X_stopsys
#define Chn_Stop                 stopch
#define Chn_Status(C,O,S)        far pascal getcstat(C,O)
#define Sethook                  sethook
#define Set_CST_Mask             setcst
#define Clear_DTMF               clrdtmf
#define Read_DTMF                readdtmf
#define Record_Buffer(C,O,S)     far pascal recbuf(C,O)
#define Play_Buffer(C,O,S)       far pascal playbuf(C,O)
#define Record_File(C,O,S,M)     far pascal recfile(C,O,M)
#define Play_File(C,O,S)         far pascal playfile(C,O)
#define Dial                     dial
#define Get_DTMF_String(C,O,S)   far pascal getdtmfs(C,O)
#define vopen(S,O,M)             vhopen(O,M)
#define vclose                   vhclose

/*
 * VOPEN function access mode definitions
 */
#define READ    0
#define RDWR    1
#define CREATE  2
#define APPEND  3


/*
 * D40lib function prototypes
 */
void far pascal clrrwb(RWB far *);
void far pascal clrxrwb(RWB far *);
void far pascal clrdcb(DCB far *);
void far pascal clrcpb(CPB far *);
int _X_isdrvact(unsigned char);
int _X_startsys(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int far *);
int setgparm(DCB far *);
int _X_setxparm(DCB far *);
int far pascal setcparm(unsigned int,CPB far *);
int _X_stopsys(void);
int far pascal stopch(unsigned int);
int far pascal getcstat(unsigned int,CSB far *);
int far pascal sethook(unsigned int,unsigned int);
int far pascal setcst(unsigned int,unsigned int,unsigned int);
int far pascal clrdtmf(unsigned int);
int far pascal readdtmf(unsigned int,unsigned char far *);
int far pascal recbuf(unsigned int,RWB far *);
int far pascal playbuf(unsigned int,RWB far *);
int far pascal recfile(unsigned int,RWB far *,unsigned int);
int far pascal playfile(unsigned int,RWB far *);
int far pascal xplayf(unsigned int,unsigned int,RWB far *);
int far pascal dial(unsigned int,unsigned char far *);
int far pascal callp(unsigned int,unsigned char far *);
int far pascal xcallp(unsigned int,RWB far *);
int far pascal getdtmfs(unsigned int,RWB far *);
int getevt(unsigned int far *,unsigned int far *,unsigned int far *);
int Get_Next_Event(unsigned int far *,unsigned int far *,unsigned int far *);
int far pascal setdmask(unsigned int,unsigned int,unsigned int);
int far pascal getver(unsigned int far *,unsigned int far *);
int far pascal sched(void);
int far pascal getcom(unsigned int,DACCB far *);
int far pascal putcom(unsigned int,ADCCB far *);
int far pascal playuser(unsigned int,unsigned char far *,unsigned int far *);
int far pascal recuser(unsigned int,unsigned char far *,unsigned int far *);
int far pascal getcar(unsigned int,CAR far *);
int _X_startamx(unsigned int,unsigned int far *);
int _X_stopamx(void);
int far pascal sw_on(unsigned int,unsigned int);
int far pascal sw_off(unsigned int,unsigned int);
int far pascal amx_off(void);
int far pascal amx_msk(unsigned int,unsigned int);
int far pascal ring(unsigned int,unsigned int);
int far pascal set_ring(unsigned int,unsigned int,unsigned int,unsigned int);
char far *far pascal d4xerr(unsigned int);
int gtevtblk(EVTBLK far *);
unsigned int _X_getvctr(void);
int far pascal putevt(unsigned int,unsigned int,unsigned int);
int far pascal setiparm(unsigned int,unsigned int,unsigned int);
int far pascal wink(unsigned int);
int far pascal sb_route(unsigned int, int);
int far pascal sb_rtrcvxmt(unsigned int, int, int);
void peek(unsigned int, unsigned int, char far *, unsigned int);
int far pascal dl_addtone(unsigned int, unsigned char, unsigned char);
int far pascal dl_deltones(unsigned int);
int far pascal dl_enbtone(unsigned int, unsigned int, unsigned int);
int far pascal dl_distone(unsigned int, unsigned int, unsigned int);
int far pascal dl_blddt(unsigned int, unsigned int, unsigned int 
            ,unsigned int, unsigned int, unsigned int);
int far pascal dl_blddtcad(unsigned int, unsigned int, unsigned int 
               ,unsigned int, unsigned int, unsigned int 
               ,unsigned int, unsigned int, unsigned int 
               ,unsigned int);
int far pascal dl_bldst(unsigned int, unsigned int, unsigned int, unsigned int);
int far pascal dl_bldstcad(unsigned int, unsigned int, unsigned int 
               ,unsigned int, unsigned int, unsigned int 
               ,unsigned int, unsigned int);
int buildtone(unsigned int, unsigned int, unsigned int, unsigned int,
              unsigned int, unsigned int, unsigned int, unsigned int,
              unsigned int, unsigned int, unsigned int, unsigned int);
void far pascal dl_setgtdamp(int,int,int,int);
int far pascal dl_playtone(unsigned int, RWB far *);
void far pascal dl_bldtngen(TN_GEN far *,unsigned int,unsigned int, int, int, int);
int far pascal dl_adjsv(unsigned int, unsigned int, unsigned int, int);
int far pascal dl_setsvcond(unsigned int, unsigned int, SVCB far *);
int far pascal dl_clrsvcond(unsigned int);
int far pascal dl_getcursv(unsigned int, int far *, int far *);
int far pascal dl_setsvmt(unsigned int, unsigned int, SVMT far *, unsigned int);
int far pascal dl_getsvmt(unsigned int, unsigned int, SVMT far *);
int far pascal dl_addspddig(unsigned int, unsigned char, unsigned int);
int far pascal dl_addvoldig(unsigned int, unsigned char, unsigned int);
int far pascal dl_gtsernum(unsigned int, char far *);
int far pascal dl_initcallp(unsigned int);
int far pascal dl_chgfreq(int,int,int,int,int);
int far pascal dl_chgdur(int,int,int,int,int);
int far pascal dl_chgrepcnt(int,int);
int far pascal dl_chgqualid(int);
int far pascal dl_gettninfo(int, TN_INFO far *);
void far pascal dl_flushtn(void);
int far pascal dl_getqual(unsigned int, unsigned int, TN_QLT far *);
int far pascal dl_setqual(unsigned int, unsigned int, TN_QLT far *);
int far pascal dl_getextqual(unsigned int, unsigned int, unsigned int, TN_QLT far *);
int far pascal dl_setextqual(unsigned int, unsigned int, unsigned int, TN_QLT far *);
void far pascal dl_selqual(unsigned int);


/************************************************************************/
/* Dialogic TIF support defs: DlgTIF.h                  V1.21  01/01/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define MAXDEVCNT       64              /* Total # device types allowed */
#define MAXDIGCNT       64              /* Total # active lines allowed */
#define MAXMPXCNT       64              /* Total # active Mpx X allowed */
#define MAXSERNUM       32              /* Maximum serial number length */
#define TIFVERNUM       0x0121          /* Tel I/F support ver number   */

#define CALLBACK_WINDOW 0x0010L         /* Callback window event mode   */
#define CALLBACK_PROC   0x0040L         /* Callback proc   event mode   */
#define FORCE_REQUEST   0x0100L         /* Force resource reuest        */

/************************************************************************/
/*                  TSR Support routines                                */
/************************************************************************/
unsigned short far pascal TIFSupIni (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFSupVer (void);
unsigned short far pascal TIFSupTrm (void);

unsigned short far pascal TIFSysGet (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFSysRel (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFDevGet (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFDevRel (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFLinGet (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFLinRel (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFPrtGet (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFPrtRel (unsigned short, unsigned long, unsigned long);
unsigned short far pascal TIFPolEvt (void);

char far *     far pascal MemGetRea (unsigned long far *, unsigned short far *, unsigned long);
int            far pascal MemRelRea (unsigned short);

/************************************************************************/
/*                  Dialogic Dos support structures                     */
/************************************************************************/
typedef struct {                        /* TIF event block: 64 bytes    */
    unsigned long   ulEvtTim;
    unsigned long   ucRsv001;
    EVTBLK          ebDlgBlk;
    unsigned char   ucRsv002[40];
} TIFEVTBLK;

typedef struct {
    short  version;                     /* firmware revision            */
    short  segment;                     /* segment address              */
    char   type;                        /* board type                   */
    char   int_lvl;                     /* hardware interrupt level     */
    short  bufsize;                     /* size of buffer               */
    char   numchan;                     /* number of channels           */
    char   basechn;                     /* base channel - 1             */
    char   config;                      /* copy of dl_syscfg from d40   */
    char   product;                     /* copy of dl_product, A/B info */
    char   rfu[20];                     /* 20 chars                     */
} IDCB;

/************************************************************************/
/*                  Dialogic Dos support extensions                     */
/************************************************************************/
short           far pascal DskFilOpn (char far *,  short, short far *);
short           far pascal DskFilCre (char far *,  short, short far *);
unsigned short  far pascal DskFilInp (short, void far *, unsigned short, short far *);
unsigned short  far pascal DskFilOut (short, void far *, unsigned short, short far *);
long            far pascal DskFilPos (short, long, short, short far *);  
long            far pascal DskFilLen (short, short far *);
short           far pascal DskFilCls (short, short far *);  
int             far pascal GetDevEvt (unsigned short, unsigned short far *, unsigned short far *, TIFEVTBLK far *);
int             far pascal GetLinEvt (unsigned short, unsigned short far *, TIFEVTBLK far *);
int             far pascal ChkDevEvt (unsigned short, unsigned short far *, unsigned short far *, TIFEVTBLK far *, unsigned short);
int             far pascal ChkLinEvt (unsigned short, unsigned short far *, TIFEVTBLK far *, unsigned short);

unsigned int far pascal getvctr  (void);
int          far pascal isdrvact (unsigned char);

int far pascal CalDxxInt (unsigned char, unsigned char far *,
    unsigned int far *, unsigned int far *, void far *, unsigned short);
int far pascal calld40  (unsigned char, unsigned char far *,
    unsigned int far *, unsigned int far *, unsigned int far *);
int far pascal calld40x (unsigned char, unsigned char far *,
    unsigned int far *, unsigned int far *, void far *);

int far pascal startsys (unsigned int, unsigned int, unsigned int,
        unsigned int far *);
int far pascal startamx (unsigned int, unsigned int far *); 
int far pascal stopamx  (void);
int far pascal setxparm (DCB far *);
int far pascal stopsys  (void);
