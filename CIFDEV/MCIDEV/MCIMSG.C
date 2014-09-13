/************************************************************************/
/* MCI Message Support: MCIMsg.c                        V2.00  07/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\os_dev\dllsup.h"           /* Windows DLL support defs     */
#include "genmci.h"                     /* Generic MCI definitions      */
#include "mcisup.h"                     /* Generic MCI support defs     */
#include "mcimsg.h"                     /* File I/O support error defs  */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <string.h>                     /* String manipulation funcs    */
#include <stdio.h>                      /* Standard I/O                 */
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  MCIGLO  MCIGlo;                 /* Generic MCI Lib Globals      */

/************************************************************************/
/************************************************************************/
int FAR PASCAL  MCIDspPrc (HWND hWnd, LPCSTR lpMsgTxt, LPCSTR lpTtlTxt, UINT uiStyFlg)
{
    return (MessageBox (hWnd, lpMsgTxt, MCIGlo.szLibNam, uiStyFlg));
}

/************************************************************************/
/************************************************************************/
long    GetPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    long            lEntVal;
    static  char    szEntVal[MCIMAXSTR];
    static  char *  pcEndChr;

    /********************************************************************/
    /********************************************************************/
    GetPrivateProfileString (szPrfSec, szPrfEnt, "", szEntVal, 
        MCIMAXSTR, szPrfNam);
    if (!*szEntVal) return (lDefVal);
  
    if (_strnicmp (szEntVal, "0x", 2) == 0) {
        pcEndChr = strchr (&szEntVal[2], '\0');
        lEntVal = strtoul (&szEntVal[2], &pcEndChr, 16);
    }
    else lEntVal = atol (szEntVal);

    /********************************************************************/
    /********************************************************************/
    return (lEntVal);

}
long    GetPrfLng (LPCSTR szPrfNam, LPCSTR szPrfSec, WORD usPrfEnt, long lDefVal)
{

    static  char    szPrfEnt[MCIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (MCIGlo.hLibIns, usPrfEnt, szPrfEnt, MCIMAXSTR)) return (lDefVal);
    return (GetPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}

/************************************************************************/
/************************************************************************/
BOOL    WrtPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    static  char    szEntVal[MCIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    wsprintf (szEntVal, "0x%lx", lDefVal);
    return (WritePrivateProfileString (szPrfSec, szPrfEnt, szEntVal, szPrfNam));

}
BOOL    WrtPrfLng (LPCSTR szPrfNam, LPCSTR szPrfSec, WORD usPrfEnt, long lDefVal)
{

    static  char    szPrfEnt[MCIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (MCIGlo.hLibIns, usPrfEnt, szPrfEnt, MCIMAXSTR)) return ((WORD) -1);
    return (WrtPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}


