/************************************************************************/
/* Amplitude Display Definitions: wavsup.h              V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define ZOMMINFAC         1.25          /* Zoom factor, no dimension    */
#define ZOMNRMFAC         2.00          /* Zoom normal, no dimension    */
#define ZOMMAXFAC         8.00          /* Zoom max,    no dimension    */

/************************************************************************/
/*                  Array/String Length Constants                       */
/************************************************************************/
#define AMPMAXSTR           40          /* Gen purpose string length    */
#define AMPMAXMSG           81          /* Message Box string length    */
#define REGKEYLEN            8          /* Registration key length      */
#define SERSEGLEN            4          /* Serial number segment length */
#define AMPLOCBAS          256          /* Amp DLL local msg base       */

/************************************************************************/
/************************************************************************/
#define SHDBOXHGT            3          /* Shadowed recessed box height */
#define SHDBOXWID            6          /* Shadowed recessed box width  */

/************************************************************************/
/************************************************************************/
#define FNTSIZDEF            8          /* Default fixed font pt size   */
#define AMPDECPRC            2          /* Numeric decimal precision    */
#define SELSTRSEN            3          /* Stretch box hit sensitivity  */
#define SELOFFSEN            0          /* Stretch box off sensitivity  */
#define POSPICSEN            3          /* Mark pick hit sensitivity    */
#define POSMINSIZ            4          /* Marker minimum size          */
#define POSRELSIZ           60          /* Marker relative size divisor */
#define XAXLFTOVR           10          /* X- Axis left overhang (pels) */
#define GPHEXTCVT(a) ((short)(a>>2))    /* 1 bit safety scaling         */
#define OVRSHTCVT(a) (a + a/10)         /* +/-10% Amp overshoot         */
#define UNDSHTCVT(a) (a/20)             /* +/- 5% Amp overshoot         */

/************************************************************************/
/************************************************************************/
#define FNTFIXNAM   "MS Sans Serif"     /* Fixed font name              */

/************************************************************************/
/*              Global Data Structures Definitions                      */
/************************************************************************/
typedef struct _AMPGLO {
    char    szLibNam  [AMPMAXSTR];      /* Library name                 */
    char    RelKeyArr [REGKEYLEN];      /* Operating/Demo Only Key      */
    char    SeqNumArr [SERSEGLEN];      /* Op/Demo sequence number      */
    DWORD   ulGphClr;                   /* Amp graph RGB value          */
    DWORD   ulGraClr;                   /* Amp graticule RGB value      */
    DWORD   ulSBxClr;                   /* Selection box RGB value      */
    DWORD   ulSRgClr;                   /* Selection region RGB value   */
    DWORD   ulSOvClr;                   /* Selection overview RGB value */
    DWORD   ulPosClr;                   /* Position at point RGB value  */
    DWORD   ulShdClr;                   /* Rec box shaded RGB value     */
    DWORD   ulLgtClr;                   /* Rec box light  RGB value     */
    DWORD   ulOvrClr;                   /* Overview shading RGB value   */
    WORD    usFntSiz;                   /* Default fixed fixed pt size  */
    WORD    usDecPrc;                   /* Numeric decimal precision    */
    HANDLE  hLibIns;                    /* Global instance handle       */
    HPEN    hGphPen;                    /* Amp graph pen                */
    HPEN    hGraPen;                    /* Amp graticule pen            */
    HPEN    hSBxPen;                    /* Selection box pen            */
    HPEN    hSRgPen;                    /* Selection region pen         */
    HPEN    hSOvPen;                    /* Selection overview pen       */
    HPEN    hPosPen;                    /* Position at point pen        */
    HPEN    hShdPen;                    /* Recessed box shaded pen      */
    HPEN    hLgtPen;                    /* Recessed box light  pen      */
    HPEN    hOvrPen;                    /* Overview shading pen         */
    HBRUSH  hPosBsh;                    /* Position at point brush      */
    HBRUSH  hOvrBsh;                    /* Overview shading brush       */
} AMPGLO;

typedef long    GENDPT;                 /* Generic device points        */
typedef short   WINDPT;                 /* Windows device points        */

/************************************************************************/
/*                          Resource Control                            */
/************************************************************************/
WORD    AmpResIni   (HANDLE);
WORD    AmpResTrm   (HANDLE);

/************************************************************************/
/*                  Amplitude selection support routines                */
/************************************************************************/
BOOL    InvPosMrk (HWND, HDC, BOOL FAR *, GENDPT);                            
BOOL    MovPosMrk (HWND, BOOL FAR *, GENDPT FAR *, GENDPT, WORD);
BOOL    GetPosSDP (HWND, GENDPT FAR *, const AMPDES FAR *, const AMPUSR FAR *);
BOOL    SetPosSmp (HWND, GENDPT, const AMPDES FAR *, AMPUSR FAR *, BOOL);

BOOL    InvSelBox (HWND, HDC, GENDPT, GENDPT);                      
BOOL    MovSelBox (HWND, GENDPT, GENDPT FAR *, GENDPT, WORD);       
BOOL    GetSelSDP (HWND, GENDPT FAR *, GENDPT FAR *, const AMPDES FAR *, const AMPUSR FAR *);
BOOL    GetSelFTo (const AMPUSR FAR *, DWORD FAR *, DWORD FAR *);
BOOL    SetSelSmp (HWND, GENDPT, GENDPT, const AMPDES FAR *, AMPUSR FAR *, BOOL);

GENDPT  SmToSnpDP (HWND, long, WORD, float);
long    SnpDPToSm (HWND, GENDPT, WORD, float);      
GENDPT  DPToSnpDP (double, GENDPT, WORD); 

BOOL    TstMseHit (HWND, const AMPDES FAR *, AMPUSR FAR *, POINT FAR *); 
BOOL    SetMseHit (HWND, POINT);
void    AncMseSel (HWND, WPARAM, POINT, const AMPDES FAR *, AMPUSR FAR *); 
BOOL    MseMov_XY (HWND, WPARAM, POINT, const AMPDES FAR *, AMPUSR FAR *); 

/************************************************************************/
/*                      Local Usage Text Strings                        */
/************************************************************************/
//#define SI_LOCINSMEM        1 + AMPLOCBAS   /* Insufficient Memory      */
//#define SI_LOCNOLMEM        2 + AMPLOCBAS   /* Cannot Lock Memory       */
//#define SI_LOCNULMEM        3 + AMPLOCBAS   /* Cannot Unlock Memory     */

#define SI_XAXSECTXT       16 + AMPLOCBAS   /* Amplitude axis seconds   */
#define SI_EXTSEGSYM       17 + AMPLOCBAS   /* Extents line symbol      */
#define SI_EXTSEGSEC       18 + AMPLOCBAS   /* Extents line seconds     */
#define SI_EXTSEGATP       19 + AMPLOCBAS   /* Extents line At Point    */
#define SI_EXTSEGLEN       20 + AMPLOCBAS   /* Extents line length      */
#define SI_YAXMINTXT       21 + AMPLOCBAS   /* Y-Axis minimum text      */
#define SI_YAXMAXTXT       22 + AMPLOCBAS   /* Y-Axis maximum text      */
                            
/************************************************************************/
/*                  Configuration Profile Strings                       */
/************************************************************************/
#define SI_FNTDEFSIZ       32 + AMPLOCBAS   /* Default fixed font pt sz */
#define SI_AMPGPHCLR       33 + AMPLOCBAS   /* Amp graph RGB value      */
#define SI_AMPGRACLR       34 + AMPLOCBAS   /* Amp graticule RGB value  */
#define SI_SELBOXCLR       35 + AMPLOCBAS   /* Selection box RGB value  */
#define SI_SELREGCLR       36 + AMPLOCBAS   /* Selection region RGB val */
#define SI_SELOVRCLR       37 + AMPLOCBAS   /* Selection overview RGB   */
#define SI_AT_POSCLR       38 + AMPLOCBAS   /* At position RGB val      */
#define SI_RECSHDCLR       39 + AMPLOCBAS   /* Rec box shaded RGB value */
#define SI_RECLGTCLR       40 + AMPLOCBAS   /* Rec box light  RGB value */
#define SI_OVRFILCLR       41 + AMPLOCBAS   /* Overview fill RGB value  */
                                                                        
/************************************************************************/
/************************************************************************/
#define SI_AMPLIBNAM    "Amplitude Display" /* Library name             */


