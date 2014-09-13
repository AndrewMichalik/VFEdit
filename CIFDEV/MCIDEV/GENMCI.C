/************************************************************************/
/* Generic Media Control I/F Support: GenMCI.c          V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genmci.h"                     /* Generic MCI definitions      */
#include "mcisup.h"                     /* MCI support definitions      */
#include "mcimsg.h"                     /* MCI support message defs     */

#include <string.h>                     /* String manipulation funcs    */
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/*                      Global variables                                */
/************************************************************************/
MCIGLO MCIGlo = {                       /* File I/O Library Globals     */
    SI_MCILIBNAM,                       /* Library name                 */
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
    MCIGlo.hLibIns = hLibIns;

    /********************************************************************/
    /********************************************************************/
    MCIResIni (MCIGlo.hLibIns);

    /********************************************************************/
    /********************************************************************/
    return (1);

}

int FAR PASCAL WEP (int nParam)
{

    return (1);

}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL MCIDLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{
    /********************************************************************/
    /********************************************************************/
    if (usReqTyp == 0) {
        // Check for accelerator key
    }

return (0);

    /********************************************************************/
    /********************************************************************/
    MCIResTrm (MCIGlo.hLibIns);
    MCIGlo.ulDBxClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_DBXBKGCLR, MCIGlo.ulDBxClr);

    return (0);
}

WORD FAR PASCAL MCISupVer ()
{
    /********************************************************************/
    /********************************************************************/
    return (MCIVERNUM);
}

//WORD    FAR PASCAL  MCILodStr (WORD, LPSTR, WORD);
//WORD FAR PASCAL MCILodStr (WORD usMsgSID, LPSTR szMsgTxt, WORD usMaxLen)
//{
//
//    /********************************************************************/
//    /* Retrieve a MCI specific message                                  */
//    /********************************************************************/
//    if (usMsgSID > MCILSTMSG) return (0);
//    return (LoadString (MCIGlo.hLibIns, usMsgSID, szMsgTxt, usMaxLen));
//
//}


/************************************************************************/
/************************************************************************/
WORD    MCIResIni (HANDLE hLibIns)
{
    WNDCLASS wcWinCls;

    /********************************************************************/
    /********************************************************************/
    MsgDspPrc = MCIDspPrc;              /* Re-assignable msg output     */
    MCIGlo.hDBxBsh = CreateSolidBrush (MCIGlo.ulDBxClr);

    /********************************************************************/
    /*  Set window class info & register for Waveform Document window   */
    /********************************************************************/
    wcWinCls.lpszClassName = SI_MCICBKCLS;
    wcWinCls.hInstance     = hLibIns;
    wcWinCls.lpfnWndProc   = MCICBkWin;
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

WORD    MCIResTrm (HANDLE hLibIns)
{
    /********************************************************************/
    /********************************************************************/
    if (NULL != MCIGlo.hDBxBsh) DeleteObject (MCIGlo.hDBxBsh);
    return (0);
}

