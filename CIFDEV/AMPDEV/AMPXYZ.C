/************************************************************************/
/* Amplitude Display XYZ-Axis Support: AmpXYZ.c         V2.00  07/15/94 */
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

#include <string.h>                     /* String manipulation funcs    */
#include <math.h>                       /* Math library defs            */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  AMPGLO  AmpGlo;                 /* Amplitude Display Globals    */

/************************************************************************/
/*                      Forward References                              */
/************************************************************************/
WORD    CalXAxHgt (HWND, WORD, DWORD);
WORD    CalYAxWid (WORD, DWORD);     

/************************************************************************/
/*                      Local References                                */
/************************************************************************/
#define SCRPAGDEF ((DWORD) ((lpAmpDes->usArrLen * lpAmpDes->flSmppGP)/SCRPERPAG))
#define PTPMAJRND(x)       (PTPMAJDIV * ((x) / PTPMAJDIV))

/************************************************************************/
/*                          AmpXAx Routines                             */
/************************************************************************/
BOOL FAR PASCAL AmpXAxPos (HWND hWnd, RECT FAR *lpBndRec)
{
    DWORD   ulTxtExt;
    WORD    usXAxHgt;
    RECT    rWrkRec;

    /********************************************************************/
    /********************************************************************/
    rWrkRec = *lpBndRec;

    /********************************************************************/
    /* Get width & height of default fixed font                         */
    /********************************************************************/
    ulTxtExt = ExtFntFix (hWnd, AmpGlo.usFntSiz, *lpBndRec);

    /********************************************************************/
    /* Position at bottom of Amplitude Window, check for room           */
    /********************************************************************/
    usXAxHgt = CalXAxHgt (hWnd, lpBndRec->bottom, ulTxtExt);
    if (0 == usXAxHgt) {   
        ShowWindow (hWnd, SW_HIDE);
        return (FALSE);
    }
    rWrkRec.top = lpBndRec->bottom - usXAxHgt;                  /* Up Y */
    rWrkRec.bottom = usXAxHgt - 2;                              /* Hgt  */

    /********************************************************************/
    /* Position at bottom of Amp Window, XAXLFTOVR overhang on left     */
    /********************************************************************/
    rWrkRec.left   = CalYAxWid (lpBndRec->right, ulTxtExt) - XAXLFTOVR; /* Up X */
    rWrkRec.right -= rWrkRec.left;                                      /* Wid  */

    /********************************************************************/
    /********************************************************************/
    MoveWindow (hWnd, rWrkRec.left, rWrkRec.top, rWrkRec.right, 
        rWrkRec.bottom, TRUE);
    ShowWindow (hWnd, SW_SHOW);

    /********************************************************************/
    /********************************************************************/
    lpBndRec->bottom = rWrkRec.top;                             /* Hgt  */
    return (TRUE);

}

void FAR PASCAL AmpXAxPnt (HWND hWnd, const AMPDES FAR *lpAmpDes)
{
    PAINTSTRUCT ps;          
    HDC     hDC;
    DWORD   ulTxtExt;
    WORD    usTxtWid, usTxtHgt;
    WORD    usLabInc, usLabWid;
    char    szTxtBuf [AMPMAXSTR];
    RECT    rWrkRec;
    HFONT   hFixFnt;
    HFONT   hOldFnt;
    HPEN    hOldPen;
    float   flTimOff;
    float   flTimInc;
    WORD    usLTkOff;
    WORD    usSTkOff;
    WORD    usi;
    #define SIDPIX_3D   1
    #define TOPPIX_3D   2

    /********************************************************************/
    /********************************************************************/
    hDC = BeginPaint (hWnd, &ps);         
    SetBkMode (hDC, TRANSPARENT);
    GetClientRect (hWnd, &rWrkRec);

    /********************************************************************/
    /* Set the map mode for usArrLen (x) by pixel count (y)             */
    /* Set viewport to be 0 to usArrLen by client area y.               */
    /* (ArrLen + (XL_OVL * (ArrLen/rWrkRec.right-XL_OVL))               */
    /* Set origin offset by XAXLFTOVR width                             */
    /********************************************************************/
    SetMapMode   (hDC, MM_ANISOTROPIC);
    if (rWrkRec.right <= XAXLFTOVR) SetWindowExt (hDC, 0, rWrkRec.bottom);
    else SetWindowExt (hDC, lpAmpDes->usArrLen
      + (WORD) ((float) 0.5 +
        (float) (XAXLFTOVR * lpAmpDes->usArrLen) / (float) (rWrkRec.right - XAXLFTOVR)),
        rWrkRec.bottom);

    SetViewportExt (hDC, rWrkRec.right, rWrkRec.bottom);
    SetViewportOrg (hDC, XAXLFTOVR, 0);
  
    /********************************************************************/
    /* Set & Get Dimensions of default fixed font                       */
    /********************************************************************/
    hFixFnt = CreFntFix (hDC, AmpGlo.usFntSiz, rWrkRec);
    hOldFnt = SelectObject (hDC, hFixFnt);
    ulTxtExt = GetTextExtent (hDC, "X", 1);
    usTxtWid = LOWORD (ulTxtExt);
    usTxtHgt = HIWORD (ulTxtExt);

    /********************************************************************/
    /* Draw 3-D horizontal axis, text & tick marks                      */
    /* Skip first tick mark, include tick at or past waveform end       */
    /********************************************************************/
    hOldPen = SelectObject (hDC, AmpGlo.hLgtPen);
    MoveTo (hDC, 0, SIDPIX_3D);
    LineTo (hDC, lpAmpDes->usArrLen - 1, SIDPIX_3D);
    SelectObject (hDC, AmpGlo.hShdPen);
    MoveTo (hDC, 0, TOPPIX_3D);
    LineTo (hDC, lpAmpDes->usArrLen - 1, TOPPIX_3D);

    /********************************************************************/
    /* Compute large tick alignment offset                              */
    /* Compute time offset and increment factor                         */
    /********************************************************************/
    usLTkOff = PTPMAJDIV - (WORD) 
        ((DWORD) (lpAmpDes->ulSmpOff / lpAmpDes->flSmppGP) % PTPMAJDIV);
    usLTkOff = usLTkOff % PTPMAJDIV;
    flTimOff  = lpAmpDes->ulSmpOff / (float) lpAmpDes->ulSmpFrq;
    flTimInc  = lpAmpDes->flSmppGP / (float) lpAmpDes->ulSmpFrq;

	/********************************************************************/
	/* Label X-Axis with default fixed font                             */
	/* Position first char left of tick mark; insure half char space    */
	/********************************************************************/
	MsgLodStr (AmpGlo.hLibIns, SI_XAXSECTXT, szTxtBuf, AMPMAXSTR);
	usLabWid = lpAmpDes->usArrLen - 1 - LOWORD (GetTextExtent (hDC, szTxtBuf, _fstrlen (szTxtBuf)));
	TextOut (hDC, usLabWid, 6, szTxtBuf, _fstrlen (szTxtBuf));
	for (usi = usLTkOff; usi <= lpAmpDes->usGPtCnt;) {
	    _fdtorna (flTimOff + usi * flTimInc, AmpGlo.usDecPrc, szTxtBuf);
	    usLabInc = PTPMAJDIV * (1 + 
	        ((usTxtWid / 2) + LOWORD (GetTextExtent (hDC, szTxtBuf, _fstrlen(szTxtBuf))))
	        / PTPMAJDIV);
	    usLabInc = max (usLabInc, PTPMAJDIV);
	    if ((usi + usLabInc) > usLabWid) break;
	    TextOut (hDC, usi - usTxtWid, 6, szTxtBuf, _fstrlen (szTxtBuf));
	    usi += usLabInc;    
	}

//    /********************************************************************/
//    /* Draw X-Axis text; prevent overlap for large numbers              */
//    /********************************************************************/
//    usi = usLTkOff;
//    while (usi <= lpAmpDes->usGPtCnt) {
//        _fdtorna (flTimOff + usi * flTimInc, AmpGlo.usDecPrc, szTxtBuf);
//        TextOut (hDC, usi - usTxtWid, 6, szTxtBuf, _fstrlen (szTxtBuf));
//        usi += PTPMAJDIV * (1 + 
//            (usTxtWid + LOWORD (GetTextExtent (hDC, szTxtBuf, _fstrlen(szTxtBuf))))
//            / PTPMAJDIV);
//    }

    /********************************************************************/
    /* Compute small tick alignment offset                              */
    /********************************************************************/
    usSTkOff = PTPMINDIV - (WORD) 
        ((DWORD) (lpAmpDes->ulSmpOff / lpAmpDes->flSmppGP) % PTPMINDIV);
    usSTkOff = usSTkOff % PTPMINDIV;

    for (usi = usSTkOff; usi < lpAmpDes->usArrLen; usi+=PTPMINDIV) {
        MoveTo (hDC, usi, TOPPIX_3D);
        LineTo (hDC, usi, TOPPIX_3D + (((PTPMAJDIV + usi - usLTkOff) % PTPMAJDIV) ? 3 : 6));
    }

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldFnt);
    DeleteObject (hFixFnt);
    EndPaint (hWnd, &ps);                   /* Done painting for now    */
}
  
BOOL FAR PASCAL AmpXAxUpd (HWND hWnd, WORD usScrReq, DWORD ulNewPos, 
                long FAR *lpDocDlt, const AMPDES FAR *lpAmpDes)
{
    int     iMinPos;
    int     iMaxPos;
    long    lWrpPos = 0L;                   /* Scroll wrap position     */
  
    /********************************************************************/
    /* Force initial / default condition                                */
    /********************************************************************/
    *lpDocDlt = 0L;                   

    /********************************************************************/
    /* Check if scroll bar is currently enabled                         */
    /********************************************************************/
    GetScrollRange (hWnd, SB_HORZ, &iMinPos, &iMaxPos);
    if (iMinPos == iMaxPos) return (FALSE);

    /********************************************************************/
    /* Test for valid scroll request                                    */
    /********************************************************************/
    switch (usScrReq) {
        case SB_LINELEFT:
            *lpDocDlt = - (long) (1 * lpAmpDes->flSmppGP);
            break;
        case SB_LINERIGHT:
            *lpDocDlt = + (long) (1 * lpAmpDes->flSmppGP);
            break;
        case SB_PAGELEFT:
            *lpDocDlt = - (long) SCRPAGDEF;
            break;
        case SB_PAGERIGHT:
            *lpDocDlt = + (long) SCRPAGDEF;
            break;
        case SB_SCRFULLFT:
            *lpDocDlt = - (long) (lpAmpDes->usArrLen * lpAmpDes->flSmppGP);
            break;
        case SB_SCRFULRGT:
            *lpDocDlt = + (long) (lpAmpDes->usArrLen * lpAmpDes->flSmppGP);
            break;
        case SB_LEFT:
            *lpDocDlt = - (long) lpAmpDes->ulSmpOff;
            break;
        case SB_RIGHT:
            *lpDocDlt = 0x7fffffffL - lpAmpDes->ulSmpOff;
            break;
        case SB_THUMBPOSITION:
            lWrpPos = ((long) ceil ((float) lpAmpDes->ulSmpOff / (float) SCRPAGDEF)
                / 0x7fffL) * 0x8000L;
            *lpDocDlt = ((lWrpPos + (DWORD) LOWORD (ulNewPos)) * SCRPAGDEF) 
                - lpAmpDes->ulSmpOff;
            break;
        case SB_SCRSMPGTO:
            *lpDocDlt = ulNewPos - lpAmpDes->ulSmpOff;
            break;
        default:
            return (FALSE);
    }
  
    /********************************************************************/
    /* Check *lpDocDlt for overflow/underflow.                            */
    /********************************************************************/
    if (((long) lpAmpDes->ulSmpOff + *lpDocDlt) > (long) (lpAmpDes->ulDocLen - SCRPAGDEF)) 
        *lpDocDlt = (lpAmpDes->ulDocLen - SCRPAGDEF) - lpAmpDes->ulSmpOff;
    if (((long) lpAmpDes->ulSmpOff + *lpDocDlt) < 0L) 
        *lpDocDlt = - (long) lpAmpDes->ulSmpOff;

    /********************************************************************/
    /* Return delta position; indicate that message was processed       */
    /********************************************************************/
    return (TRUE);

}

WORD FAR PASCAL AmpXAxScr (HWND hWnd, long lDocDlt, DWORD FAR *lpNewOff,
                const AMPDES FAR *lpAmpDes)
{
    int     iOldMin;
    int     iOldMax;
    int     iOldPos;
    long    lNewMax; 
    long    lNewPos; 

    /********************************************************************/
    /* Adjust the scrollbar range and position values                   */
    /********************************************************************/
    GetScrollRange (hWnd, SB_HORZ, &iOldMin, &iOldMax);

    /********************************************************************/
    /* Check ulSmpOff for overflow/underflow.                           */
    /********************************************************************/
    if (ceil (lpAmpDes->ulDocLen / lpAmpDes->flSmppGP) <= (float) lpAmpDes->usArrLen) {
        *lpNewOff = 0L;
        SetScrollRange (hWnd, SB_HORZ, 0, 0, FALSE);
        return (iOldMin != iOldMax ? SCREXTUPD : 0);
    }
    *lpNewOff = min (lpAmpDes->ulSmpOff + lDocDlt, lpAmpDes->ulDocLen - SCRPAGDEF);

    /********************************************************************/
    /* Note that for very long files, max = 7fff and scroll wraps       */
    /********************************************************************/
    lNewMax = (long) ceil ((float) lpAmpDes->ulDocLen / (float) SCRPAGDEF);
    lNewPos = (long) ceil ((float) *lpNewOff / (float) SCRPAGDEF);
  
    if (lNewMax <= SCRPERPAG) lNewMax = 0L;
    if (lNewMax >  0x7fffL) lNewMax = 0x7fff;
    if (lNewPos >= 0x7fffL) lNewPos = lNewPos % 0x7fffL;
  
    /********************************************************************/
    /********************************************************************/
    if (iOldMax != (int) lNewMax) 
        SetScrollRange (hWnd, SB_HORZ, 0, (int) lNewMax, FALSE);
    if ((int) lNewPos != (iOldPos = GetScrollPos (hWnd, SB_HORZ)))
        SetScrollPos   (hWnd, SB_HORZ, (int) lNewPos, TRUE);

    /********************************************************************/
    /* Indicate whether scroll extents or thumb position has changed    */
    /********************************************************************/
    return ((iOldMin == iOldMax ? SCREXTUPD : 0) | (iOldPos != (int) lNewPos ? SCRPOSUPD : 0));

}

WORD    CalXAxHgt (HWND hWnd, WORD usMaxHgt, DWORD ulTxtExt)
{
    WORD    usXAxHgt;
    int     iMinPos;
    int     iMaxPos;
  
    /********************************************************************/
    /* Set height to text height + 10 pels above bottom + Scroll bar    */
    /********************************************************************/
    usXAxHgt = 10 + HIWORD (ulTxtExt);

    /********************************************************************/
    /* Adjust height if scroll bar is wil be enabled.                   */
    /********************************************************************/
    GetScrollRange (hWnd, SB_HORZ, &iMinPos, &iMaxPos);
    if (iMinPos != iMaxPos) usXAxHgt += GetSystemMetrics (SM_CYHSCROLL);    

    /********************************************************************/
    /* Check if enough room to show                                     */
    /********************************************************************/
    if ((WORD) (2 * usXAxHgt) > usMaxHgt) usXAxHgt = 0;

    /********************************************************************/
    /********************************************************************/
    return (usXAxHgt);                                 /* X Axis Height */

}

/************************************************************************/
/*                          AmpYAx Routines                             */
/************************************************************************/
BOOL FAR PASCAL AmpYAxPos (HWND hWnd, RECT FAR *lpBndRec)
{
    DWORD   ulTxtExt;
    RECT    rWrkRec;

    /********************************************************************/
    /********************************************************************/
    rWrkRec = *lpBndRec;

    /********************************************************************/
    /* Get width & height of default fixed font                         */
    /********************************************************************/
    ulTxtExt = ExtFntFix (hWnd, AmpGlo.usFntSiz, *lpBndRec);

    /********************************************************************/
    /* Position below Extents, above X-Axis                             */
    /********************************************************************/
    rWrkRec.right = CalYAxWid (lpBndRec->right, ulTxtExt);      /* Wid  */
    if (0 == rWrkRec.right) {
        ShowWindow (hWnd, SW_HIDE);
        return (FALSE);
    }
                                                               
    /********************************************************************/
    /********************************************************************/
    ShowWindow (hWnd, SW_SHOW);
    MoveWindow (hWnd, rWrkRec.left, rWrkRec.top, rWrkRec.right, 
        rWrkRec.bottom, TRUE);

    /********************************************************************/
    /********************************************************************/
    lpBndRec->left  += rWrkRec.right;                           /* Lft  */
    lpBndRec->right -= rWrkRec.right;                           /* Wid  */

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}

void FAR PASCAL AmpYAxPnt (HWND hWnd, const AMPPNT FAR *lpAmpPnt)
{
    PAINTSTRUCT ps;                         /* Used for painting.       */
    HDC     hDC;
    DWORD   ulTxtExt;
    WORD    usTxtWid, usTxtHgt, usTxtLen;
    char    szTxtBuf [AMPMAXSTR];
    WORD    usHgtOff;
    RECT    rWrkRec;
    HFONT   hFixFnt;
    HFONT   hOldFnt;
    HPEN    hOldPen;
    short   sAbsExt;
    short   si;
    #define SIDPIX_3D   1
    #define TOPPIX_3D   2
  
    /********************************************************************/
    /********************************************************************/
    sAbsExt = lpAmpPnt->sYAxMax;

    /********************************************************************/
    /********************************************************************/
    hDC = BeginPaint (hWnd, &ps);   
    SetBkMode (hDC, TRANSPARENT);
    GetClientRect (hWnd, &rWrkRec);

    /********************************************************************/
    /* Set the map mode for pixel count (x) by +/- sAbsRng (y)          */
    /* Set viewport to be the entire client area.                       */
    /* Frame picture for "|-" X/Y                                       */
    /* Adjust for % overshoot (OVRSHTCVT)                               */
    /********************************************************************/
    SetMapMode     (hDC, MM_ANISOTROPIC);
    SetWindowExt   (hDC, rWrkRec.right, -2 * OVRSHTCVT (sAbsExt));
    SetViewportExt (hDC, rWrkRec.right, rWrkRec.bottom);
    SetWindowOrg   (hDC, 0, OVRSHTCVT (sAbsExt));

    /********************************************************************/
    /* Set & Get Dimensions of default fixed font                       */
    /********************************************************************/
    hFixFnt = CreFntFix (hDC, AmpGlo.usFntSiz, rWrkRec);
    hOldFnt = SelectObject (hDC, hFixFnt);
    ulTxtExt = GetTextExtent (hDC, "X", 1);
    usTxtWid = LOWORD (ulTxtExt);
    usTxtHgt = HIWORD (ulTxtExt);

    /********************************************************************/
    /* Draw 3D vertical axis and and tick marks                         */
    /********************************************************************/
    hOldPen = SelectObject (hDC, AmpGlo.hShdPen);
    MoveTo  (hDC, rWrkRec.right - SIDPIX_3D, +OVRSHTCVT (sAbsExt) - UNDSHTCVT(sAbsExt));
    LineTo  (hDC, rWrkRec.right - SIDPIX_3D, -OVRSHTCVT (sAbsExt));
    SelectObject (hDC, AmpGlo.hLgtPen);
    MoveTo  (hDC, rWrkRec.right - TOPPIX_3D, +OVRSHTCVT (sAbsExt) - UNDSHTCVT(sAbsExt));
    LineTo  (hDC, rWrkRec.right - TOPPIX_3D, -OVRSHTCVT (sAbsExt));
    SelectObject (hDC, AmpGlo.hShdPen);
    for (si=-sAbsExt; si <= sAbsExt; si += lpAmpPnt->sYAxInc) {
        MoveTo  (hDC, rWrkRec.right - (usTxtWid / 2) - TOPPIX_3D, si);
        LineTo  (hDC, rWrkRec.right - TOPPIX_3D, si);
    }

    /********************************************************************/
    /* Draw Y-Axis text; prevent overlap for large numbers              */
    /********************************************************************/
    MsgLodStr (AmpGlo.hLibIns, SI_YAXMINTXT, szTxtBuf, AMPMAXSTR);
    TextOut (hDC, usTxtWid, -sAbsExt + (usTxtHgt+1)/2, szTxtBuf, _fstrlen (szTxtBuf));
    usHgtOff = 20 + 20 * ((1 + usTxtHgt) / 20);
    si = -sAbsExt + usHgtOff;
    while (si <= (short) (sAbsExt - usHgtOff)) {
        _fitoa (abs(si), szTxtBuf, lpAmpPnt->sYAxInc);
        usTxtLen = _fstrlen (szTxtBuf);
        TextOut (hDC, (4 - usTxtLen) * usTxtWid,
            si + (usTxtHgt+1)/2, szTxtBuf, usTxtLen);
        si += usHgtOff;
    }
    MsgLodStr (AmpGlo.hLibIns, SI_YAXMAXTXT, szTxtBuf, AMPMAXSTR);
    TextOut (hDC, usTxtWid, +sAbsExt + (usTxtHgt+1)/2, szTxtBuf, _fstrlen (szTxtBuf));

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldPen);
    SelectObject (hDC, hOldFnt);
    DeleteObject (hFixFnt);
    EndPaint (hWnd, &ps);                   /* Done painting for now    */

}
  
WORD    CalYAxWid (usMaxWid, ulTxtExt)
WORD    usMaxWid;
DWORD   ulTxtExt;
{

    WORD    usYAxWid;

    /********************************************************************/
    /********************************************************************/
    usYAxWid = 5 * LOWORD (ulTxtExt);

    if ((WORD) (4 * usYAxWid) > usMaxWid) return (0);
    return (usYAxWid);

}

/************************************************************************/
/*                          AmpZAx Routines                             */
/************************************************************************/
BOOL FAR PASCAL AmpZAxUpd (HWND hWnd, WORD usScrReq, DWORD ulSmpCnt, 
                float FAR *lpResFac, const AMPDES FAR *lpAmpDes)
{
    float   flSmppGP = lpAmpDes->flSmppGP;

    /********************************************************************/
    /* Force initial / default condition                                */
    /********************************************************************/
    *lpResFac = 1;

    /********************************************************************/
    /* Test for valid scroll request                                    */
    /********************************************************************/
    switch (usScrReq) {
        case SB_LINEUP:                                 /* Zoom In min  */
            flSmppGP = lpAmpDes->flSmppGP / (float) ZOMMINFAC;
            break;
        case SB_LINEDOWN:                               /* Zoom Out min */
            flSmppGP = lpAmpDes->flSmppGP * (float) ZOMMINFAC;
            break;
        case SB_PAGEUP:                                 /* Zoom In def  */
            flSmppGP = lpAmpDes->flSmppGP / (float) ZOMNRMFAC;
            break;
        case SB_PAGEDOWN:                               /* Zoom Out def */
            flSmppGP = lpAmpDes->flSmppGP * (float) ZOMNRMFAC;
            break;                                      
        case SB_SCRFUL_UP:                              /* Zoom In max  */
            flSmppGP = lpAmpDes->flSmppGP / (float) ZOMMAXFAC;
            break;
        case SB_SCRFULDWN:                              /* Zoom Out max */
            flSmppGP = lpAmpDes->flSmppGP * (float) ZOMMAXFAC;
            break;
        case SB_SCRSMPFIT:                              /* Zoom to fit  */
            if (!ulSmpCnt) break;
            flSmppGP = ulSmpCnt / (float) (lpAmpDes->usArrLen - 1);
            break;
        case SB_SCRSMPPMD:                          /* ulSmpCnt=smp/div */
            if (!ulSmpCnt) break;                   
            flSmppGP = ulSmpCnt / (float) PTPMAJDIV;
            break;
        default:
            return (FALSE);
    }

    /********************************************************************/
    /* Adjust to max / min resolutions                                  */
    /********************************************************************/
    if (flSmppGP < SMPPGPMIN) flSmppGP = SMPPGPMIN;
    if (flSmppGP < lpAmpDes->usViwCon)  flSmppGP = (float) ceil (flSmppGP);
    if (flSmppGP > SMPPGPMAX) flSmppGP = SMPPGPMAX;

    /********************************************************************/
    /* Return delta resolution; indicate that message was processed     */
    /********************************************************************/
    *lpResFac = flSmppGP / lpAmpDes->flSmppGP;
    return (TRUE);
 
}

BOOL FAR PASCAL AmpZAxScr (HWND hWnd, float flResFac, float FAR *lpNewRes,
                const AMPDES FAR *lpAmpDes)
{
    /********************************************************************/
    /* Adjust the scrollbar range and position values                   */
    /********************************************************************/
    return (TRUE);
}
