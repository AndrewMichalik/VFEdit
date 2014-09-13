/************************************************************************/
/* Generic Telco Media I/F Support: GenTMI.c            V2.00  06/10/92 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define  NOCOMM                         /* Inhibit certain windows defs */
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\..\tifdll\tiflib\dlglib.h" /* Dialogic D4x stand defs      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */

#include <string.h>                     /* String manipulation funcs    */
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/*                      Global variables                                */
/************************************************************************/
TMIGLO TMIGlo = {                       /* File I/O Library Globals     */
    SI_TMILIBNAM,                       /* Library name                 */
    {'0','0','0','0','0','0','0','0'},  /* Operating/Demo Only Key      */
    {'1','0','0','0'},                  /* Op/Demo sequence number      */
    RGB (192, 192, 192),                /* Dlg box background RGB value */
    NULL,                               /* Global instance handle       */
    NULL,                               /* Dlg box background brush     */
};

/************************************************************************/
/************************************************************************/
int FAR PASCAL LibMain (HANDLE hLibIns, WORD usDatSeg, WORD usHeapSz,
               LPSTR lpCmdLin)
{

    /********************************************************************/
    /********************************************************************/
    if (usHeapSz != 0) UnlockData(0);
    TMIGlo.hLibIns = hLibIns;

    /********************************************************************/
    /********************************************************************/
    TMIResIni (TMIGlo.hLibIns);

    /********************************************************************/
    /********************************************************************/
    return (1);

}

int FAR PASCAL WEP (int nParam)
{

    /********************************************************************/
    /********************************************************************/
    TMIResTrm (TMIGlo.hLibIns);
    return (1);

}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL TMIDLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{
    /********************************************************************/
    /********************************************************************/
    if (usReqTyp == 0) {
        // Check for accelerator key
    }

return (0);

    /********************************************************************/
    /********************************************************************/
    TMIResTrm (TMIGlo.hLibIns);
    TMIGlo.ulDBxClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_DBXBKGCLR, TMIGlo.ulDBxClr);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD FAR PASCAL TMISupVer ()
{
    /********************************************************************/
    /* Check expected TI/F DLL version number                           */
    /********************************************************************/
    if (TIFVERNUM != TIFSupVer()) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMITIFMIS);
    }

    /********************************************************************/
    /********************************************************************/
    return (TMIVERNUM);
}

/************************************************************************/
/************************************************************************/
WORD    TMIResIni (HANDLE hLibIns)
{
    WNDCLASS wcWinCls;

    /********************************************************************/
    /********************************************************************/
    MsgDspPrc = TMIDspPrc;              /* Re-assignable msg output     */
    TMIGlo.hDBxBsh = CreateSolidBrush (TMIGlo.ulDBxClr);

    /********************************************************************/
    /*  Set window class info & register for Waveform Document window   */
    /********************************************************************/
    wcWinCls.lpszClassName = SI_TMICBKCLS;
    wcWinCls.hInstance     = hLibIns;
    wcWinCls.lpfnWndProc   = TMICBkWin;
    wcWinCls.hCursor       = NULL;
    wcWinCls.hIcon         = NULL;
    wcWinCls.lpszMenuName  = NULL;
    wcWinCls.hbrBackground = NULL;
    wcWinCls.style         = NULL;
    wcWinCls.cbClsExtra    = 0;
    wcWinCls.cbWndExtra    = 0;
    RegisterClass (&wcWinCls);        

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD    TMIResTrm (HANDLE hLibIns)
{
    /********************************************************************/
    /********************************************************************/
    if (NULL != TMIGlo.hDBxBsh) DeleteObject (TMIGlo.hDBxBsh);
    return (0);
}
