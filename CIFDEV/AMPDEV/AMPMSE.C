/************************************************************************/
/* Amplitude Display Mouse Control: AmpMse.c            V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "genamp.h"                     /* Amplitude Display defs       */
#include "ampsup.h"                     /* Amplitude Display supp defs  */

#include <math.h>                       /* Math library defs            */

/************************************************************************/
/************************************************************************/
void    FAR PASCAL AmpMseLDn (HWND hWnd, WORD usFlags, POINT mpMsePos, 
                   const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{
    /********************************************************************/
    /* Check new mouse ownership                                        */
    /********************************************************************/
    if (TstMseHit (hWnd, lpAmpDes, lpAmpUsr, &mpMsePos)) {
        SetMseHit (hWnd, mpMsePos);
    }
    else AncMseSel (hWnd, usFlags, mpMsePos, lpAmpDes, lpAmpUsr); 

}

BOOL    FAR PASCAL AmpMseMov (HWND hWnd, WORD usFlags, POINT mpMsePos, 
                   const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{

    /********************************************************************/
    /* Check mouse ownership and button status                          */
    /********************************************************************/
    if ((usFlags & MK_LBUTTON) && (GetCapture () == hWnd)) {
        MseMov_XY (hWnd, usFlags, mpMsePos, lpAmpDes, lpAmpUsr); 
        return (TRUE);
	} 
    
    /********************************************************************/
    /* Hit test and set appropriate cursor                              */
    /********************************************************************/
    TstMseHit (hWnd, lpAmpDes, lpAmpUsr, &mpMsePos);
    return (FALSE);

}

void    FAR PASCAL AmpMseLUp (HWND hWnd, WORD usFlags, POINT mpMsePos, 
                   const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{
    lpAmpUsr->amMseOwn = AMPMSENON;
}

/************************************************************************/
/************************************************************************/
void    FAR PASCAL AmpCarMov (HWND hWnd, DWORD ulNewOff, 
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{
    GENDPT  lAtPSDP;                    /* At Pos (snapped device pts)  */
    GENDPT  lNewSDP;

    /********************************************************************/
    /* Move caret to new position: erase old, redraw                    */   
    /********************************************************************/
    GetPosSDP (hWnd, &lAtPSDP, lpAmpDes, lpAmpUsr);
    lNewSDP = SmToSnpDP (hWnd, (long) ulNewOff - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
    MovPosMrk (hWnd, &lpAmpUsr->bPosBln, &lAtPSDP, lNewSDP, lpAmpDes->usArrLen);
    SetPosSmp (hWnd, lAtPSDP, lpAmpDes, lpAmpUsr, FALSE);
}

void    FAR PASCAL AmpCarBln (HWND hWnd,
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{
    HDC     hDC;
    RECT    rWrkRec;
    GENDPT  lAtPSDP;

    /********************************************************************/
    /* Blink caret by inverting pixels                                  */   
    /********************************************************************/
    if (GetPosSDP (hWnd, &lAtPSDP, lpAmpDes, lpAmpUsr)) {
        hDC = GetDC (hWnd);
        GetClientRect (hWnd, &rWrkRec);
        InvPosMrk (hWnd, hDC, &lpAmpUsr->bPosBln, lAtPSDP);
        ReleaseDC (hWnd, hDC);
    }

}

/************************************************************************/
/************************************************************************/
void    FAR PASCAL AmpSelMov (HWND hWnd, DWORD ulNewOff, DWORD ulNewLen,
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{
    GENDPT  lBegSDP;
    GENDPT  lEndSDP;
    HDC     hDC;

    /********************************************************************/
    /* Erase old selection box if active                                */
    /********************************************************************/
    if (GetSelSDP (hWnd, &lBegSDP, &lEndSDP, lpAmpDes, lpAmpUsr)) {
        hDC = GetDC (hWnd);
        InvSelBox (hWnd, hDC, lBegSDP, lEndSDP);
        ReleaseDC (hWnd, hDC);
    }

    /********************************************************************/
    /* Find new box beginning and end in Snapped Device Points (SDPs)   */
    /********************************************************************/
    lBegSDP = SmToSnpDP (hWnd, (long) ulNewOff - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
    lEndSDP = SmToSnpDP (hWnd, (long) ulNewOff + (long) ulNewLen - (long) lpAmpDes->ulSmpOff, 
        lpAmpDes->usArrLen, lpAmpDes->flSmppGP);
    SetSelSmp (hWnd, lBegSDP, lEndSDP, lpAmpDes, lpAmpUsr, TRUE);

    /********************************************************************/
    /* Exit if selection remains inactive                               */
    /********************************************************************/
    if (lBegSDP == lEndSDP) return;

    /********************************************************************/
    /* Force at position to follow beginning of the selection box       */
    /********************************************************************/
    SetPosSmp (hWnd, lBegSDP, lpAmpDes, lpAmpUsr, TRUE);

    /********************************************************************/
    /* Set new selection sample values                                  */
    /********************************************************************/
    hDC = GetDC (hWnd);
    InvSelBox (hWnd, hDC, lBegSDP, lEndSDP);
    ReleaseDC (hWnd, hDC);

}

void    AncMseSel (HWND hWnd, WPARAM wParam, POINT mpMsePos, 
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{

    GENDPT  lMseSDPX;                   /* Mouse X-Pt in snp dev pts    */
    RECT    rWrkRec;       
    GENDPT  lBegSDP;
    GENDPT  lEndSDP;
    HDC     hDC;

    /********************************************************************/
    /* Erase old selection box if active                                */
    /********************************************************************/
    if (GetSelSDP (hWnd, &lBegSDP, &lEndSDP, lpAmpDes, lpAmpUsr)) {
        hDC = GetDC (hWnd);
        InvSelBox (hWnd, hDC, lBegSDP, lEndSDP);
        ReleaseDC (hWnd, hDC);
    }

    /********************************************************************/
    /* Use mouse position to set new anchor point                       */
    /********************************************************************/
    GetClientRect (hWnd, &rWrkRec);
    lMseSDPX = DPToSnpDP (mpMsePos.x, rWrkRec.right, lpAmpDes->usArrLen);
    SetSelSmp (hWnd, lMseSDPX, lMseSDPX, lpAmpDes, lpAmpUsr, FALSE);

    /********************************************************************/
    /********************************************************************/
    lpAmpUsr->amMseOwn = AMPMSEEND;

}

/************************************************************************/
/************************************************************************/
BOOL    MseMov_XY (HWND hWnd, WPARAM wParam, POINT mpMsePos,
        const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr) 
{

    GENDPT  lBegSDP;
    GENDPT  lEndSDP;
    GENDPT  lAtPSDP;

    /********************************************************************/
    /* Set cursor if mouse is owned by At Point                         */
    /********************************************************************/
    if (AMPMSEATP == lpAmpUsr->amMseOwn) {
        GetPosSDP (hWnd, &lAtPSDP, lpAmpDes, lpAmpUsr);
        MovPosMrk (hWnd, &lpAmpUsr->bPosBln, &lAtPSDP, mpMsePos.x, lpAmpDes->usArrLen);
        SetPosSmp (hWnd, lAtPSDP, lpAmpDes, lpAmpUsr, FALSE);

        /****************************************************************/
        /* Clear selection box if at position is active                 */
        /****************************************************************/
        AmpSelMov (hWnd, 0L, 0L, lpAmpDes, lpAmpUsr); 
    }

    /********************************************************************/
    /* Set draw selection box if mouse is owned by selection box        */
    /********************************************************************/
    if ((AMPMSEBEG == lpAmpUsr->amMseOwn) || (AMPMSEEND == lpAmpUsr->amMseOwn)) {
        GetSelSDP (hWnd, &lBegSDP, &lEndSDP, lpAmpDes, lpAmpUsr);
        if (AMPMSEBEG == lpAmpUsr->amMseOwn) 
            MovSelBox (hWnd, lEndSDP, &lBegSDP, mpMsePos.x, lpAmpDes->usArrLen);
        else 
            MovSelBox (hWnd, lBegSDP, &lEndSDP, mpMsePos.x, lpAmpDes->usArrLen);
        SetSelSmp (hWnd, lBegSDP, lEndSDP, lpAmpDes, lpAmpUsr, FALSE);

        /****************************************************************/
        /* Force at position to follow beginning of the selection box   */
        /****************************************************************/
        AmpCarMov (hWnd, min (lpAmpUsr->ulSelBeg, lpAmpUsr->ulSelEnd), 
            lpAmpDes, lpAmpUsr); 
    }

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

BOOL    TstMseHit (HWND hWnd, const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr, 
        POINT FAR *lpmpMsePos)
{

    GENDPT  lBegSDP;
    GENDPT  lEndSDP;
    GENDPT  lAtPSDP;
    DWORD   ulPrxBeg;
    DWORD   ulPrxEnd;
    DWORD   ulPrxAtP;
    RECT    rWrkRec;       

    /********************************************************************/
    /********************************************************************/
    lpAmpUsr->amMseOwn = AMPMSENON;

    /********************************************************************/
    /* Test if mouse position is near selection box right/left border   */
    /********************************************************************/
    if (GetSelSDP (hWnd, &lBegSDP, &lEndSDP, lpAmpDes, lpAmpUsr)) {
        ulPrxBeg = labs (lBegSDP - lpmpMsePos->x);
        ulPrxEnd = labs (lEndSDP - lpmpMsePos->x);

        if ((ulPrxBeg <= ulPrxEnd) && (ulPrxBeg <= SELSTRSEN)) {
            lpmpMsePos->x = (WINDPT) lBegSDP;
            lpAmpUsr->amMseOwn = AMPMSEBEG;
        }       
        else if (ulPrxEnd <= SELSTRSEN) {
            lpmpMsePos->x = (WINDPT) lEndSDP;
            lpAmpUsr->amMseOwn = AMPMSEEND;
        }
    }

    /********************************************************************/
    /* Test if mouse position is near At Point Marker                   */
    /********************************************************************/
    if (!lpAmpUsr->amMseOwn && GetPosSDP (hWnd, &lAtPSDP, lpAmpDes, lpAmpUsr)) {
        WORD    usPicSen;
        GetClientRect (hWnd, &rWrkRec);
        ulPrxAtP = ((rWrkRec.bottom - rWrkRec.top) / 2) - lpmpMsePos->y;
        usPicSen = POSMINSIZ + rWrkRec.right / POSRELSIZ;
        if (ulPrxAtP <= usPicSen) {
            ulPrxAtP = labs (lAtPSDP - lpmpMsePos->x);
            if (ulPrxAtP <= usPicSen) {
                lpmpMsePos->x = (WINDPT) lAtPSDP;
                lpAmpUsr->amMseOwn = AMPMSEATP;
            }
        }
    }

    /********************************************************************/
    /* Test if mouse position is near X-Axis                            */
    /********************************************************************/
    if (!lpAmpUsr->amMseOwn) { 
        GetClientRect (hWnd, &rWrkRec);
        ulPrxAtP = labs (((rWrkRec.bottom - rWrkRec.top) / 2) - lpmpMsePos->y);
        if (ulPrxAtP <= POSPICSEN) {
            lpAmpUsr->amMseOwn = AMPMSEATP;
        }
    }

    /********************************************************************/
    /* Set appropriate cursor for mouse ownership                       */ 
    /********************************************************************/
    switch (lpAmpUsr->amMseOwn) {
        case AMPMSEBEG:
            SetCursor (LoadCursor (NULL, IDC_SIZEWE));
            break;
        case AMPMSEEND:
            SetCursor (LoadCursor (NULL, IDC_SIZEWE));
            break;
        case AMPMSEMAX:
            SetCursor (LoadCursor (NULL, IDC_SIZENS));
            break;
        case AMPMSEMIN:
            SetCursor (LoadCursor (NULL, IDC_SIZENS));
            break;
        case AMPMSEATP:
            SetCursor (LoadCursor (NULL, IDC_IBEAM));
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (lpAmpUsr->amMseOwn);

}

BOOL    SetMseHit (HWND hWnd, POINT mpMsePos)
{

    /********************************************************************/
    /********************************************************************/
    ClientToScreen (hWnd, &mpMsePos);
    SetCursorPos (mpMsePos.x, mpMsePos.y);

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}


