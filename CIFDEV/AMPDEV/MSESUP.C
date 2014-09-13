/************************************************************************/
/* Mouse Selection Support: MseSup.c                    V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "genamp.h"                     /* Amplitude Display defs       */
#include "ampsup.h"                     /* Amplitude Display supp defs  */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  AMPGLO  AmpGlo;                 /* Amplitude Display Globals    */

/************************************************************************/
/*              Selection Box Manipulation Routines                     */
/************************************************************************/
BOOL    InvPosMrk (HWND hWnd, HDC hDC, BOOL FAR *lpbPosBln, GENDPT lAtPSDP)
{
    RECT    rWrkRec;
    short   sTriDPtX;
    short   sTriDPtY;
    POINT   apTriGon[3];
    short   hOldDrw;
    HBRUSH  hOldBsh;
    HPEN    hOldPen;

    /********************************************************************/
    /********************************************************************/
    GetClientRect  (hWnd, &rWrkRec);
    sTriDPtX = sTriDPtY = POSMINSIZ + rWrkRec.right / POSRELSIZ; 
    apTriGon[0].x = (WINDPT) lAtPSDP;
    apTriGon[0].y = rWrkRec.bottom / 2;
    apTriGon[1].x = apTriGon[0].x - sTriDPtX / 2;
    apTriGon[1].y = apTriGon[0].y - sTriDPtY;
    apTriGon[2].x = apTriGon[0].x + sTriDPtX / 2;
    apTriGon[2].y = apTriGon[0].y - sTriDPtY;

    /********************************************************************/
    /********************************************************************/
    hOldDrw = SetROP2 (hDC, R2_NOTXORPEN);
    hOldBsh = SelectObject (hDC, AmpGlo.hPosBsh);
    hOldPen = SelectObject (hDC, AmpGlo.hPosPen);

    /********************************************************************/
    /********************************************************************/
    Polygon (hDC, apTriGon, sizeof (apTriGon) / sizeof (POINT));

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldBsh);
    SetROP2 (hDC, hOldDrw);

    /********************************************************************/
    /********************************************************************/
    *lpbPosBln = !*lpbPosBln;
    return (TRUE);

}

BOOL    MovPosMrk (HWND hWnd, BOOL FAR *lpbPosBln, GENDPT FAR *plCurSDPX,
        GENDPT lNewDPtX, WORD usArrLen)
{

    HDC     hDC;
    RECT    rWrkRec;

    /********************************************************************/
    /* Check if mouse has moved to new (snapped) position               */
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    lNewDPtX = DPToSnpDP (lNewDPtX, rWrkRec.right, usArrLen);
    if (*plCurSDPX == lNewDPtX) {
        return (FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    hDC = GetDC (hWnd);
    SetROP2 (hDC, R2_NOTXORPEN);

    /********************************************************************/
    /* Erase old position marker (if visible)                           */
    /********************************************************************/
    if (*lpbPosBln) InvPosMrk (hWnd, hDC, lpbPosBln, *plCurSDPX);

    /********************************************************************/
    /* Draw new position marker (if visible)                            */
    /********************************************************************/
    if ((lNewDPtX >= 0) & (lNewDPtX <= rWrkRec.right)) {
        InvPosMrk (hWnd, hDC, lpbPosBln, lNewDPtX);
        *plCurSDPX = lNewDPtX;
    }

    /********************************************************************/
    /********************************************************************/
    ReleaseDC (hWnd, hDC);

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

BOOL    GetPosSDP (HWND hWnd, GENDPT FAR *plAtPSDP, const AMPDES FAR *lpAmpDes, 
        const AMPUSR FAR *lpAmpUsr)
{
    /********************************************************************/
    /********************************************************************/
    *plAtPSDP = SmToSnpDP (hWnd, (long) lpAmpUsr->ulPosAtP - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);

    /********************************************************************/
    /********************************************************************/
    {
    RECT    rWrkRec;
    GetClientRect (hWnd, &rWrkRec);
    return ((*plAtPSDP >= 0) && (*plAtPSDP <= rWrkRec.right));
    }    

}
                             
BOOL    SetPosSmp (HWND hWnd, GENDPT lAtPSDP, const AMPDES FAR *lpAmpDes, 
        AMPUSR FAR *lpAmpUsr, BOOL bfInv_OK)
{

    RECT    rWrkRec;

    /********************************************************************/
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);

    /********************************************************************/
    /* Allow off-screen sample values to be set by caller.              */
    /* Inhibit setting off screen values for localized mouse operations */
    /* This permits rounding the selection to snapped device points     */
    /********************************************************************/
    if (bfInv_OK || ((lAtPSDP >= 0) && (lAtPSDP <= rWrkRec.right))) 
      lpAmpUsr->ulPosAtP = lpAmpDes->ulSmpOff + SnpDPToSm (hWnd, 
        lAtPSDP, lpAmpDes->usArrLen, lpAmpDes->flSmppGP);

    /********************************************************************/
    /* Future: If not active, return FALSE                              */
    /********************************************************************/
    return (TRUE);

}

/************************************************************************/
/************************************************************************/
BOOL    InvSelBox (HWND hWnd, HDC hDC, GENDPT lAncSDP, GENDPT lMovSDP)
{
    HPEN    hOldPen;
    HBRUSH  hOldBsh;
    short   hOldDrw;
    short   hOldBck;
    RECT    rWrkRec;

    /********************************************************************/
    /********************************************************************/
    GetClientRect  (hWnd, &rWrkRec);

//ajm: DCSLDR.DLL (Diamond's drivers?) explode when drawing rectangle beyond visible
//    rWrkRec.left    = (WINDPT) ((lAncSDP < lMovSDP) ? lAncSDP : lMovSDP);
//    rWrkRec.right   = (WINDPT) ((lAncSDP > lMovSDP) ? lAncSDP : lMovSDP);
{
    long lLeft;
    long lRight;
    lLeft    = ((lAncSDP < lMovSDP) ? lAncSDP : lMovSDP);
    lRight   = ((lAncSDP > lMovSDP) ? lAncSDP : lMovSDP);
    rWrkRec.left    = (WINDPT) ((lLeft  < rWrkRec.left)  ? rWrkRec.left  - 1 : lLeft);
    rWrkRec.right   = (WINDPT) ((lRight > rWrkRec.right) ? rWrkRec.right + 1 : lRight);
}
    rWrkRec.top     = UNDSHTCVT(rWrkRec.bottom) / 2;
    rWrkRec.bottom -= UNDSHTCVT(rWrkRec.bottom) / 2;

    /********************************************************************/
    /********************************************************************/
    hOldDrw = SetROP2 (hDC, R2_NOTXORPEN);
    hOldBck = SetBkMode (hDC, TRANSPARENT);
    hOldBsh = SelectObject (hDC, GetStockObject (NULL_BRUSH));
    hOldPen = SelectObject (hDC, AmpGlo.hSBxPen);

    Rectangle (hDC,
        rWrkRec.left, rWrkRec.top, rWrkRec.right, rWrkRec.bottom);

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldBsh);
    SetBkMode (hDC, hOldBck);
    SetROP2   (hDC, hOldDrw);

    return (TRUE);
}

BOOL    MovSelBox (HWND hWnd, GENDPT lAncSDPX, GENDPT FAR *plMovSDPX, 
        GENDPT lMseDPtX, WORD usArrLen)
{

    HDC     hDC;
    HPEN    hOldPen;
    HBRUSH  hOldBsh;
    RECT    rWrkRec;

    /********************************************************************/
    /* Check if mouse has moved to new (snapped) position               */
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    lMseDPtX = DPToSnpDP (lMseDPtX, rWrkRec.right, usArrLen);
    if (*plMovSDPX == lMseDPtX) {
        return (FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    hDC = GetDC (hWnd);
    SetROP2 (hDC, R2_NOTXORPEN);
    SetBkMode (hDC, TRANSPARENT);
    hOldPen = SelectObject (hDC, AmpGlo.hSBxPen);
    hOldBsh = SelectObject (hDC, GetStockObject (NULL_BRUSH));

    /********************************************************************/
    /* Erase old selection box                                          */
    /********************************************************************/
    if (lAncSDPX != *plMovSDPX) 
        InvSelBox (hWnd, hDC, lAncSDPX, *plMovSDPX);

    /********************************************************************/
    /* Draw new selection box                                           */
    /********************************************************************/
    if (lAncSDPX != lMseDPtX) 
        InvSelBox (hWnd, hDC, lAncSDPX, lMseDPtX);

    *plMovSDPX = lMseDPtX;

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldBsh);
    ReleaseDC (hWnd, hDC);

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

BOOL    GetSelFTo (const AMPUSR FAR *lpAmpUsr, DWORD FAR *lpulSelBeg, DWORD FAR *lpulSelEnd)
{

    /********************************************************************/
    /********************************************************************/
    if (lpAmpUsr->ulSelEnd == lpAmpUsr->ulSelBeg) return (FALSE);

    /********************************************************************/
    /********************************************************************/
    if (lpAmpUsr->ulSelBeg < lpAmpUsr->ulSelEnd) {
        *lpulSelBeg = lpAmpUsr->ulSelBeg;
        *lpulSelEnd = lpAmpUsr->ulSelEnd;
    }
    else {
        *lpulSelBeg = lpAmpUsr->ulSelEnd;
        *lpulSelEnd = lpAmpUsr->ulSelBeg;
    }

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

BOOL    GetSelSDP (HWND hWnd, GENDPT FAR *plBegSDP, GENDPT FAR *plEndSDP, 
        const AMPDES FAR *lpAmpDes, const AMPUSR FAR *lpAmpUsr)
{
    RECT    rWrkRec;

    /********************************************************************/
    /* Get selection box in snapped device points                       */
    /********************************************************************/
    *plBegSDP = SmToSnpDP (hWnd, (long) lpAmpUsr->ulSelBeg - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
    *plEndSDP = SmToSnpDP (hWnd, (long) lpAmpUsr->ulSelEnd - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);

    /********************************************************************/
    /* Normalize 32 bit device points to 16 bit to avoid overflow err   */
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    if (*plBegSDP < 0) *plBegSDP = -1;
    if (*plEndSDP < 0) *plEndSDP = -1;
    if (*plBegSDP > rWrkRec.right) *plBegSDP = rWrkRec.right + 1;
    if (*plEndSDP > rWrkRec.right) *plEndSDP = rWrkRec.right + 1;

    /********************************************************************/
    /********************************************************************/
    return (!(labs (*plBegSDP - *plEndSDP) <= SELOFFSEN));

}            
                             
BOOL    SetSelSmp (HWND hWnd, GENDPT lBegSDP, GENDPT lEndSDP, 
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr, BOOL bfInv_OK)
{

    RECT    rWrkRec;

    /********************************************************************/
    /********************************************************************/
    if (labs (lBegSDP - lEndSDP) <= SELOFFSEN) {
        lpAmpUsr->ulSelBeg = lpAmpUsr->ulSelEnd = lpAmpDes->ulSmpOff 
            + SnpDPToSm (hWnd, lEndSDP, lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
        return (FALSE);
    }
    GetClientRect (hWnd, &rWrkRec);

    /********************************************************************/
    /* Allow off-screen sample values to be set by caller.              */
    /* Inhibit setting off screen values for localized mouse operations */
    /* This permits rounding the selection to snapped device points     */
    /********************************************************************/
    if (bfInv_OK || ((lBegSDP >= 0) && (lBegSDP <= rWrkRec.right))) 
      lpAmpUsr->ulSelBeg = lpAmpDes->ulSmpOff + SnpDPToSm (hWnd, 
        lBegSDP, lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
    if (bfInv_OK || ((lEndSDP >= 0) && (lEndSDP <= rWrkRec.right))) 
      lpAmpUsr->ulSelEnd = lpAmpDes->ulSmpOff + SnpDPToSm (hWnd, 
        lEndSDP, lpAmpDes->usArrLen, lpAmpDes->flSmppGP);

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

/************************************************************************/
/************************************************************************/
GENDPT  SmToSnpDP (HWND hWnd, long lReqSmpX, WORD usArrLen, float flSmppGP)
{

    RECT    rWrkRec;
    float   flDPtpGP;

    /********************************************************************/
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    if (rWrkRec.right == 0) return (0L);

    /********************************************************************/
    /* Convert Samples to Device Points                                 */
    /* Snap Device Point to Graph Points                                */
    /********************************************************************/
    flDPtpGP = rWrkRec.right / (float) usArrLen;
    return (DPToSnpDP (lReqSmpX * flDPtpGP / flSmppGP, rWrkRec.right, usArrLen));  

}

long    SnpDPToSm (HWND hWnd, GENDPT lReqDPtX, WORD usArrLen, float flSmppGP)
{
    RECT    rWrkRec;
    float   flDPtpGP;
    float   flRndVal = (float) ((lReqDPtX < 0) ? -0.5 : +0.5);

    /********************************************************************/
    /* Convert Device Pts to sample pos rounded to nearest Graph Point  */
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    if (rWrkRec.right == 0) return (0L);

    /********************************************************************/
    /* Convert to samples. Round to nearest device point, then round    */
    /* to nearest sample point                                          */
    /********************************************************************/
    flDPtpGP = rWrkRec.right / (float) usArrLen;
//09/97
return ((long) (flRndVal + (flSmppGP * (long) (flRndVal + (lReqDPtX / flDPtpGP)))));
//    return ((DWORD) (.5 + (flSmppGP * (DWORD) (.5 + (lReqDPtX / flDPtpGP)))));

}

GENDPT  DPToSnpDP (double dbReqDPtX, GENDPT lRecRgt, WORD usArrLen)
{
    float   flDPtpGP;
    float   flRndVal = (float) ((dbReqDPtX < 0) ? -0.5 : +0.5);

    /********************************************************************/
    /* Note: accept (double) for device point position to handle longs  */
    /********************************************************************/
    if (0 == lRecRgt) return (0);

    /********************************************************************/
    /* Snap current device point to whole number that gives the minimun */
    /* error relative to the "ideal" point (based upon flDPtpGP).      */
    /********************************************************************/
    flDPtpGP = lRecRgt / (float) usArrLen;
//09/97
return ((GENDPT) (flRndVal + (flDPtpGP * ((GENDPT) (flRndVal + (dbReqDPtX / flDPtpGP)))))); 
//    return ((GENDPT) (0.5 + (flDPtpGP * ((GENDPT) (0.5 + (dbReqDPtX / flDPtpGP)))))); 

}

