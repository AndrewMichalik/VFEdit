/************************************************************************/
/* Amplitude Graph Display: AmpGph.c                    V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "genamp.h"                     /* Amplitude Display defs       */
#include "ampsup.h"                     /* Amplitude Display supp defs  */
#include "ampmsg.h"                     /* Amplitude Display error defs */
#include "..\os_dev\winmsg.h"           /* User message support         */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  AMPGLO  AmpGlo;                 /* Wave Display Lib Globals     */

/************************************************************************/
/************************************************************************/
BOOL FAR PASCAL AmpWavPnt (HDC hDC, const AMPDES FAR *lpAmpDes, 
                AMPUSR FAR *lpAmpUsr, AMPGPH FAR *lpagGphArr);

/************************************************************************/
/*                     AmpGph Paint Message Routine                     */
/************************************************************************/
void FAR PASCAL AmpGphPnt (HWND hWnd, const AMPPNT FAR *lpAmpPnt, 
                const AMPDES FAR *lpAmpDes, AMPUSR FAR *lpAmpUsr,
                AMPGPH FAR *lpagGphArr)
{
    PAINTSTRUCT ps;                         /* Used for painting.       */
    HDC     hDC;
    RECT    rCltRec, rWrkRec;
    GENDPT  lAncSDP, lMovSDP, lAtPSDP;     
    int     hOldDC;
    HPEN    hOldPen;
    WORD    usi, usIdxOff;

    /********************************************************************/
    /********************************************************************/
    hDC = BeginPaint (hWnd, &ps);           /* Prepare the client area  */
    hOldDC = SaveDC (hDC);                  /* Save default dev context */

    /********************************************************************/
    /* Set the map mode and frame picture for "|-" X/Y                  */
    /* Set viewport to be the entire client area.                       */
    /********************************************************************/
    SetMapMode     (hDC, MM_ANISOTROPIC);
    SetWindowExt   (hDC, lpAmpDes->usArrLen, -2 * OVRSHTCVT (GPHEXTCVT (lpAmpPnt->lYAxExt)));
    GetClientRect  (hWnd, &rCltRec);
    SetViewportExt (hDC, rCltRec.right, rCltRec.bottom);
    SetWindowOrg   (hDC, 0, OVRSHTCVT (GPHEXTCVT (lpAmpPnt->lYAxExt)));
  
    /********************************************************************/
    /* Draw gray, horizontal graticule and tick marks                   */
    /* Skip first tick mark, include tick at or past waveform end       */
    /********************************************************************/
    hOldPen = (HPEN) SelectObject (hDC, AmpGlo.hGraPen);
    MoveTo (hDC, 0, 0);
    LineTo (hDC, lpAmpDes->usArrLen - 1, 0);

    rWrkRec.left   =  0;                        /* X pt for conversion  */
    rWrkRec.top    =  rCltRec.bottom/2 - 4;     /* Y pt for conversion  */
    rWrkRec.right  =  0;                        /* X pt for conversion  */
    rWrkRec.bottom =  rCltRec.bottom/2 + 4;     /* Y pt for conversion  */
    DPtoLP (hDC, (LPPOINT) &rWrkRec, 2);

    usIdxOff = PTPMAJDIV - (WORD) ((DWORD) (lpAmpDes->ulSmpOff / lpAmpDes->flSmppGP) % PTPMAJDIV);

    for (usi = usIdxOff; usi <= lpAmpDes->usArrLen; usi+=PTPMAJDIV) {
        MoveTo (hDC, usi, rWrkRec.top);
        LineTo (hDC, usi, rWrkRec.bottom);
    }

    /********************************************************************/
    /*              Draw center focus point "[]" mark                   */
    /********************************************************************/
    #define XHRMAXWID   6
    #define XHRMAXGAP   1
    
    MoveTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 3 * rWrkRec.top);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 2 * rWrkRec.top);
    MoveTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 3 * rWrkRec.top);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXGAP, 3 * rWrkRec.top);

    MoveTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 3 * rWrkRec.top);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 2 * rWrkRec.top);
    MoveTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 3 * rWrkRec.top);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXGAP, 3 * rWrkRec.top);

    MoveTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 3 * rWrkRec.bottom);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 2 * rWrkRec.bottom);
    MoveTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXWID, 3 * rWrkRec.bottom);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) - XHRMAXGAP, 3 * rWrkRec.bottom);

    MoveTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 3 * rWrkRec.bottom);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 2 * rWrkRec.bottom);
    MoveTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXWID, 3 * rWrkRec.bottom);
    LineTo (hDC, (lpAmpDes->usArrLen / 2) + XHRMAXGAP, 3 * rWrkRec.bottom);

    /********************************************************************/
    /* Draw Audio waveform                                              */
    /********************************************************************/
    AmpWavPnt (hDC, lpAmpDes, lpAmpUsr, lpagGphArr);

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);

    /********************************************************************/
    /* Restore Device point based context                               */
    /********************************************************************/
    RestoreDC (hDC, hOldDC);                /* Restore default context  */

    /********************************************************************/
    /* Position At marker (if valid)                                    */
    /********************************************************************/
    if (GetPosSDP (hWnd, &lAtPSDP, lpAmpDes, lpAmpUsr)) {
        InvPosMrk (hWnd, hDC, &lpAmpUsr->bPosBln, lAtPSDP);
        lpAmpUsr->bPosBln = TRUE;
    }

    /********************************************************************/
    /* Position mouse Anchor & Terminator device points                 */
    /* Draw selection box                                               */
    /********************************************************************/
    if (GetSelSDP (hWnd, &lAncSDP, &lMovSDP, lpAmpDes, lpAmpUsr))
        InvSelBox (hWnd, hDC, lAncSDP, lMovSDP);

    /********************************************************************/
    /********************************************************************/
    EndPaint (hWnd, &ps);                   /* Done painting for now    */

}

/************************************************************************/
/* Draw Audio waveform                                                  */
/************************************************************************/
BOOL FAR PASCAL AmpWavPnt (HDC hDC, const AMPDES FAR *lpAmpDes, 
                AMPUSR FAR *lpAmpUsr, AMPGPH FAR *lpagGphArr)
{
    HPEN    hOldPen;
    DWORD   ulSelBeg;
    DWORD   ulSelEnd;
    WORD    usBegIdx = (WORD) -1;
    WORD    usEndIdx = (WORD) -1;
    WORD    usi; 

    /********************************************************************/
    /********************************************************************/
    if (GetSelFTo (lpAmpUsr, &ulSelBeg, &ulSelEnd)) {
        DWORD   ulOffGPt = (DWORD) (lpAmpDes->ulSmpOff / lpAmpDes->flSmppGP);
        DWORD   ulBegGPt = (DWORD) (ulSelBeg / lpAmpDes->flSmppGP);
        DWORD   ulEndGPt = (DWORD) (ulSelEnd / lpAmpDes->flSmppGP);
        if (ulEndGPt >= ulOffGPt) {
            if (ulBegGPt <= ulOffGPt) usBegIdx = 0;
                else usBegIdx = (WORD) (ulBegGPt - ulOffGPt);    
            usEndIdx = (WORD) (ulEndGPt - ulOffGPt);    
        }
    }

    /********************************************************************/
    /* Draw Max / Min waveform                                          */
    /********************************************************************/
    hOldPen = SelectObject (hDC, AmpGlo.hGphPen);
    for (usi = 0; usi < lpAmpDes->usGPtCnt; usi++) {
        if (usBegIdx == usi) SelectObject (hDC, AmpGlo.hSRgPen);
        if (usEndIdx == usi) SelectObject (hDC, AmpGlo.hGphPen);
        MoveTo (hDC, usi, GPHEXTCVT (lpagGphArr[usi].gsMinWav));
        LineTo (hDC, usi, GPHEXTCVT (lpagGphArr[usi].gsMaxWav));
    }

    /********************************************************************/
    /* Draw connecting lines for low sample resolutions                 */
    /********************************************************************/
    if ((WORD) lpAmpDes->flSmppGP <= lpAmpDes->usViwCon) {
        if (!usBegIdx) SelectObject (hDC, AmpGlo.hSRgPen);
        else SelectObject (hDC, AmpGlo.hGphPen);
        MoveTo (hDC, 0, (GPHEXTCVT (lpagGphArr[0].gsMinWav) + GPHEXTCVT (lpagGphArr[0].gsMaxWav))/2);
        for (usi = 1; usi < lpAmpDes->usGPtCnt; usi++) {
            if (usBegIdx == usi) SelectObject (hDC, AmpGlo.hSRgPen);
            if (usEndIdx == usi) SelectObject (hDC, AmpGlo.hGphPen);
            LineTo (hDC, usi, (GPHEXTCVT (lpagGphArr[usi].gsMinWav) + GPHEXTCVT (lpagGphArr[usi].gsMaxWav))/2);
        }
    }
    SelectObject (hDC, hOldPen);

    /********************************************************************/
    /********************************************************************/
    return (0);
}

BOOL FAR PASCAL AmpGphPos (HWND hWnd, RECT FAR *lpBndRec)
{

    /********************************************************************/
    /********************************************************************/
    MoveWindow (hWnd, lpBndRec->left, lpBndRec->top, lpBndRec->right, 
        lpBndRec->bottom, TRUE);

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

