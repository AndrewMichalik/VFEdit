/************************************************************************/
/* Telco Media Message Support: TMIMsg.c                V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\os_dev\dllsup.h"           /* Windows DLL support defs     */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <string.h>                     /* String manipulation funcs    */
#include <stdio.h>                      /* Standard I/O                 */
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  TMIGLO  TMIGlo;                 /* Generic TMI Lib Globals      */

/************************************************************************/
/************************************************************************/
int FAR PASCAL  TMIDspPrc (HWND hWnd, LPCSTR lpMsgTxt, LPCSTR lpTtlTxt, UINT uiStyFlg)
{
    return (MessageBox (hWnd, lpMsgTxt, TMIGlo.szLibNam, uiStyFlg));
}

/************************************************************************/
/************************************************************************/
void SetDlgItemHex (HWND hDlg, int usItm_ID, long lDefVal) 
{
    static  char    szEntVal[TMIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (lDefVal) wsprintf (szEntVal, "0x%lx", lDefVal);
    else strcpy (szEntVal, "0");
    SetDlgItemText (hDlg, usItm_ID, szEntVal);
}

long GetDlgItemHex (HWND hDlg, int usItm_ID)
{
    static  char    szEntVal[TMIMAXSTR];
    static  char *  pcEndChr;

    /********************************************************************/
    /********************************************************************/
    GetDlgItemText (hDlg, usItm_ID, szEntVal, TMIMAXSTR);
    if (_strnicmp (szEntVal, "0x", 2) == 0) {
        pcEndChr = strchr (&szEntVal[2], '\0');
        return (strtoul (&szEntVal[2], &pcEndChr, 16));
    }
    else return (atol (szEntVal));
}

/************************************************************************/
/************************************************************************/
long    GetPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    long            lEntVal;
    static  char    szEntVal[TMIMAXSTR];
    static  char *  pcEndChr;

    /********************************************************************/
    /********************************************************************/
    GetPrivateProfileString (szPrfSec, szPrfEnt, "", szEntVal, 
        TMIMAXSTR, szPrfNam);
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

    static  char    szPrfEnt[TMIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (TMIGlo.hLibIns, usPrfEnt, szPrfEnt, TMIMAXSTR)) return (lDefVal);
    return (GetPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}

/************************************************************************/
/************************************************************************/
BOOL    WrtPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    static  char    szEntVal[TMIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    wsprintf (szEntVal, "%ld", lDefVal);
    return (WritePrivateProfileString (szPrfSec, szPrfEnt, szEntVal, szPrfNam));

}
BOOL    WrtPrfLng (LPCSTR szPrfNam, LPCSTR szPrfSec, WORD usPrfEnt, long lDefVal)
{

    static  char    szPrfEnt[TMIMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (TMIGlo.hLibIns, usPrfEnt, szPrfEnt, TMIMAXSTR)) return ((WORD) -1);
    return (WrtPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}


