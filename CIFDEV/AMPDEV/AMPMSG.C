/************************************************************************/
/* Amplitude Display Message Support: AmpMsg.c          V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "genamp.h"                     /* Amplitude Display defs       */
#include "ampsup.h"                     /* Amplitude Display supp defs  */
#include "ampmsg.h"                     /* Amplitude Display error defs */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\os_dev\dllsup.h"           /* Windows DLL support defs     */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <string.h>                     /* String manipulation funcs    */
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  AMPGLO  AmpGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
BOOL    MsgCatStr (WORD usMsgSID, char FAR * szMsgTxt, WORD usMaxLen)
{
    WORD usStrLen;

    /********************************************************************/
    /********************************************************************/
    if ((usStrLen = _fstrlen (szMsgTxt)) >= usMaxLen) return (FALSE);

    /********************************************************************/
    /********************************************************************/
    return (MsgLodStr (AmpGlo.hLibIns, usMsgSID, &szMsgTxt[usStrLen], usMaxLen - usStrLen));

}

long    GetPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    long            lEntVal;
    static  char    szEntVal[AMPMAXSTR];
    static  char *  pcEndChr;

    /********************************************************************/
    /********************************************************************/
    GetPrivateProfileString (szPrfEnt, szPrfEnt, "", szEntVal, 
        AMPMAXSTR, szPrfNam);
    if (szEntVal[0] == '\0') return (lDefVal);
  
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

    static  char    szPrfEnt[AMPMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (AmpGlo.hLibIns, usPrfEnt, szPrfEnt, AMPMAXSTR)) return (lDefVal);
    return (GetPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}

/************************************************************************/
/************************************************************************/
HFONT   CreFntFix (HDC hDC, WORD usPntSiz, RECT rCltRec)
{

    WORD    usWrkSiz;
    WORD    usLogExt;
    WORD    usDevExt;
    HFONT   hFixFnt;

    /********************************************************************/
    /********************************************************************/
    if (0 == (usDevExt = rCltRec.bottom)) return (NULL); 
    DPtoLP (hDC, (LPPOINT) &rCltRec, 2);
    usLogExt = abs (rCltRec.top - rCltRec.bottom);

    /********************************************************************/
    /* Point size in logical points:                                    */
    /*   = (PntSiz * DevPnt/inch * 1/72 in/pt) * LogPnt/DevPnt          */
    /********************************************************************/
    usWrkSiz = (WORD) (((DWORD) usPntSiz * (DWORD) GetDeviceCaps (hDC, LOGPIXELSY)
        * (DWORD) usLogExt) / (72L * (DWORD) usDevExt));

    /********************************************************************/
    /* Create font using size without descent                           */
    /********************************************************************/
    hFixFnt = CreateFont (- (short) usWrkSiz, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, FF_MODERN,
        (LPSTR) FNTFIXNAM);

    return (hFixFnt);

}

DWORD   ExtFntFix (HWND hWnd, WORD usPntSiz, RECT rBndRec)
{
    HDC     hDC;
    HFONT   hFixFnt;
    HFONT   hOldFnt;
    DWORD   ulTxtExt;

    /********************************************************************/
    /********************************************************************/
    hFixFnt = CreFntFix (hDC = GetDC (hWnd), usPntSiz, rBndRec);
    hOldFnt = SelectObject (hDC, hFixFnt);
    ulTxtExt = GetTextExtent (hDC, "X", 1);
    SelectObject (hDC, hOldFnt);
    DeleteObject (hFixFnt);
    ReleaseDC (hWnd, hDC);

    /********************************************************************/
    /********************************************************************/
    return (ulTxtExt);

}


RECT ShdRecBox (HDC hDC, RECT rBndRec, HPEN hShdPen, HPEN hLgtPen)
{

    HPEN    hOldPen;

    /********************************************************************/
    /********************************************************************/
    if ((rBndRec.right - rBndRec.left) < 2 * SHDBOXWID) return (rBndRec);
    if ((rBndRec.bottom - rBndRec.top) < 2 * SHDBOXHGT) return (rBndRec);
    
    /********************************************************************/
    /* Calculate recessed shading                                       */
    /********************************************************************/
    rBndRec.left   = rBndRec.left   + SHDBOXWID;
    rBndRec.right  = rBndRec.right  - SHDBOXWID;
    rBndRec.top    = rBndRec.top    + SHDBOXHGT;
    rBndRec.bottom = rBndRec.bottom - SHDBOXHGT;

    /********************************************************************/
    /********************************************************************/
    hOldPen = SelectObject (hDC, hShdPen);
    MoveTo (hDC, rBndRec.left,  rBndRec.top);               /*  Top     */
    LineTo (hDC, rBndRec.right, rBndRec.top);
    MoveTo (hDC, rBndRec.left,  rBndRec.top);               /*  Left    */
    LineTo (hDC, rBndRec.left,  rBndRec.bottom);

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hLgtPen);
    MoveTo (hDC, rBndRec.left  - SHDBOXWID, + 1);           /*  Top     */
    LineTo (hDC, rBndRec.right + SHDBOXWID, + 1);
    MoveTo (hDC, rBndRec.right, rBndRec.bottom);            /*  Right   */
    LineTo (hDC, rBndRec.right, rBndRec.top);
    MoveTo (hDC, rBndRec.right, rBndRec.bottom);            /* Bottom   */
    LineTo (hDC, rBndRec.left - 1, rBndRec.bottom);

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    return (rBndRec);

}

int ShdRecTxt (HDC hDC, char FAR *szTxtStr, RECT rShdRec, WORD usTotWid)
{

    DWORD   ulTxtExt;                       /* Current text extents     */
    WORD    usTxtLen;                       /* Current text string len  */
    RECT    rTxtRec;

    /********************************************************************/
    /********************************************************************/
    usTxtLen = _fstrlen (szTxtStr);
    ulTxtExt = GetTextExtent (hDC, szTxtStr, usTxtLen);
    rShdRec.right = rShdRec.left + LOWORD (ulTxtExt) + 4 * SHDBOXWID;
    if (rShdRec.right <= (int) usTotWid) {
        rTxtRec = ShdRecBox (hDC, rShdRec, AmpGlo.hShdPen, AmpGlo.hLgtPen);
        TextOut (hDC, rTxtRec.left + SHDBOXWID, 
            (rTxtRec.bottom - HIWORD (ulTxtExt)) / 2 + 2, szTxtStr, usTxtLen);
        return (rShdRec.right);
    }

    /********************************************************************/
    /********************************************************************/
    return (rShdRec.left);

}

int ShdRecRec (HDC hDC, RECT rBndRec, DWORD ulRecBeg, DWORD ulRecEnd, 
    DWORD ulRecTot, HPEN hRecPen, HBRUSH hRecBsh)
{
    HPEN    hOldPen;
    HBRUSH  hOldBsh;
    WORD    usLft, usRgt;

    /********************************************************************/
    /* Insure valid total area; 0 causes percentage of end to fill      */
    /********************************************************************/
    if (!ulRecTot && !(ulRecTot = ulRecEnd)) return (0);

    /********************************************************************/
    /* Calculate interior of shaded rectangle                           */
    /********************************************************************/
    rBndRec.left    += (SHDBOXWID + 1);
    rBndRec.right   -= (SHDBOXWID + 1);
    rBndRec.top     += (SHDBOXHGT + 1);
    rBndRec.bottom  -= (SHDBOXHGT + 1);

    /********************************************************************/
    /* Calculate overview selection box; force to 1 pixel width         */
    /********************************************************************/
    usLft = rBndRec.left + (WORD) ((ulRecBeg / (float) ulRecTot)
        * (rBndRec.right - rBndRec.left)) - 1;
    usRgt = rBndRec.left + (WORD) ((ulRecEnd / (float) ulRecTot)
        * (rBndRec.right - rBndRec.left)) + 1;

    /********************************************************************/
    /* Enforce rectangle boundaries                                     */
    /********************************************************************/
    rBndRec.left   = max (min (usLft, (WORD) rBndRec.right), (WORD) rBndRec.left);
    rBndRec.right  = max (min (usRgt, (WORD) rBndRec.right), (WORD) rBndRec.left);

    /********************************************************************/
    /********************************************************************/
    hOldPen = SelectObject (hDC, hRecPen);
    hOldBsh = SelectObject (hDC, hRecBsh);
    Rectangle (hDC, rBndRec.left, rBndRec.top, rBndRec.right, rBndRec.bottom);
    SelectObject (hDC, hOldBsh);
    SelectObject (hDC, hOldPen);

    /********************************************************************/
    return (0);
}

LPSTR   _fdtorna (double dSrcVal, short sDecCnt, LPSTR szTxtBuf)
{
    LPSTR   lpcCvtTxt;
    LPSTR   lpcWrkBuf = szTxtBuf;
    int     iDecPos, iSgnFlg;

    /********************************************************************/
    /********************************************************************/
    if (0.0 == dSrcVal) return (_fstrcpy (szTxtBuf, "0"));

    /********************************************************************/
    /* Convert dSrcVal to string, sDecCnt digits after decimal pt       */
    /********************************************************************/
    lpcCvtTxt = _ffcvt (dSrcVal, sDecCnt, &iDecPos, &iSgnFlg);
    if (iSgnFlg) *lpcWrkBuf++ = '-';

    /********************************************************************/
    /* Adjust iDecPos since fcvt returns < -sDecCnt for small values    */
    /********************************************************************/
    if (iDecPos < -sDecCnt) iDecPos = -sDecCnt;

    /********************************************************************/
    /********************************************************************/
    if (iDecPos <= 0) {
        *lpcWrkBuf++ = '.';
        while (iDecPos++ < 0) *lpcWrkBuf++ = '0';
    } else {
        while (iDecPos-- > 0) *lpcWrkBuf++ = *lpcCvtTxt++;
        *lpcWrkBuf++ = '.';
    }
    _fstrcpy (lpcWrkBuf, lpcCvtTxt);

    /********************************************************************/
    /********************************************************************/
    return (szTxtBuf);
  
}
