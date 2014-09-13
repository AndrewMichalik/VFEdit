/************************************************************************/
/* Amplitude Display Status Support: AmpSta.c           V2.00  07/15/94 */
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

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  AMPGLO  AmpGlo;                 /* Amplitude Display Globals    */

/************************************************************************/
/************************************************************************/
WORD    CalStaHgt (WORD, DWORD);   

/************************************************************************/
/*                  Amplitude Extents Paint Message Routine             */
/************************************************************************/
void FAR PASCAL AmpStaPnt (HWND hWnd, const AMPDES FAR *lpAmpDes, 
                const AMPUSR FAR *lpAmpUsr)
{
    PAINTSTRUCT ps;               
    char    szTxtBuf[AMPMAXSTR];      
    DWORD   ulSelBeg;
    DWORD   ulSelEnd;
    WORD    usTotWid;                       /* Total window width       */
    HFONT   hFixFnt;
    HFONT   hOldFnt;
    RECT    rShdRec;                        /* Shd rec outer bounds     */
    HDC     hDC;

    /********************************************************************/
    /********************************************************************/
    GetClientRect  (hWnd, &rShdRec);
    usTotWid = rShdRec.right;

    /********************************************************************/
    /********************************************************************/
    hDC = BeginPaint (hWnd, &ps);           /* Prepare the client area  */
    SetBkMode (hDC, TRANSPARENT);

    /********************************************************************/
    /********************************************************************/
    hFixFnt = CreFntFix (hDC, AmpGlo.usFntSiz, rShdRec);
    hOldFnt = SelectObject (hDC, hFixFnt);

    /********************************************************************/
    /* Display document length position                                 */
    /********************************************************************/
    MsgLodStr (AmpGlo.hLibIns, SI_EXTSEGLEN, szTxtBuf, AMPMAXSTR);
    _fdtorna ((lpAmpDes->ulDocLen) / (float) lpAmpDes->ulSmpFrq, 
        AmpGlo.usDecPrc, &szTxtBuf[_fstrlen(szTxtBuf)]);
    MsgCatStr (SI_EXTSEGSEC, szTxtBuf, AMPMAXSTR);
    rShdRec.left = ShdRecTxt (hDC, szTxtBuf, rShdRec, usTotWid);

    /********************************************************************/
    /* Display "at" position                                            */
    /********************************************************************/
    MsgLodStr (AmpGlo.hLibIns, SI_EXTSEGATP, szTxtBuf, AMPMAXSTR);
    _fdtorna ((lpAmpUsr->ulPosAtP) / (float) lpAmpDes->ulSmpFrq, 
        AmpGlo.usDecPrc, &szTxtBuf[_fstrlen(szTxtBuf)]);
    MsgCatStr (SI_EXTSEGSEC, szTxtBuf, AMPMAXSTR);
    rShdRec.left = ShdRecTxt (hDC, szTxtBuf, rShdRec, usTotWid);

    /********************************************************************/
    /* Display selection extents & length                               */
    /********************************************************************/
    if (GetSelFTo (lpAmpUsr, &ulSelBeg, &ulSelEnd)) {
        /****************************************************************/
        /* Display text fields                                          */
        /****************************************************************/
        _fdtorna (ulSelBeg / (float) lpAmpDes->ulSmpFrq, AmpGlo.usDecPrc, 
            szTxtBuf);
        MsgCatStr (SI_EXTSEGSYM, szTxtBuf, AMPMAXSTR);
        _fdtorna (ulSelEnd / (float) lpAmpDes->ulSmpFrq, AmpGlo.usDecPrc, 
            &szTxtBuf[_fstrlen(szTxtBuf)]);
        _fstrcat (szTxtBuf, " (");
        _fdtorna ((ulSelEnd - ulSelBeg) / (float) lpAmpDes->ulSmpFrq, 
            AmpGlo.usDecPrc, &szTxtBuf[_fstrlen(szTxtBuf)]);
        MsgCatStr (SI_EXTSEGSEC, szTxtBuf, AMPMAXSTR);
        _fstrcat (szTxtBuf, ")");
        rShdRec.left = ShdRecTxt (hDC, szTxtBuf, rShdRec, usTotWid);
        /****************************************************************/
        /* Display current window overview                              */
        /* Display selection region overview                            */
        /****************************************************************/
        ShdRecRec (hDC, rShdRec, lpAmpDes->ulSmpOff, lpAmpDes->ulSmpOff +
            (DWORD) (lpAmpDes->flSmppGP * lpAmpDes->usArrLen), 
            lpAmpDes->ulDocLen, AmpGlo.hOvrPen, AmpGlo.hOvrBsh);
        ShdRecRec (hDC, rShdRec, ulSelBeg, ulSelEnd, lpAmpDes->ulDocLen ? 
            lpAmpDes->ulDocLen : (DWORD) (lpAmpDes->flSmppGP * lpAmpDes->usArrLen), 
	        AmpGlo.hSOvPen, GetStockObject (NULL_BRUSH));

    }
    else {
        /****************************************************************/
        /* Display current window overview only                         */
        /****************************************************************/
        ShdRecRec (hDC, rShdRec, lpAmpDes->ulSmpOff, lpAmpDes->ulSmpOff +
            (DWORD) (lpAmpDes->flSmppGP * lpAmpDes->usArrLen), 
            lpAmpDes->ulDocLen, AmpGlo.hLgtPen, AmpGlo.hOvrBsh);
    }
    
    /********************************************************************/
    /********************************************************************/
    rShdRec.right = usTotWid;
    ShdRecBox (hDC, rShdRec, AmpGlo.hShdPen, AmpGlo.hLgtPen);

    /********************************************************************/
    /********************************************************************/
    SelectObject (hDC, hOldFnt);
    DeleteObject (hFixFnt);

    /********************************************************************/
    /********************************************************************/
    EndPaint (hWnd, &ps);                   /* Done painting for now    */

}

BOOL FAR PASCAL AmpStaPos (HWND hWnd, RECT FAR *lpBndRec)
{
    DWORD   ulTxtExt;
    WORD    usExtHgt;
    RECT    rWrkRec;


    /********************************************************************/
    /********************************************************************/
    rWrkRec = *lpBndRec;

    /********************************************************************/
    /* Set & Get Dimensions of default fixed font                       */
    /********************************************************************/
    ulTxtExt = ExtFntFix (hWnd, AmpGlo.usFntSiz, *lpBndRec);
  
    /********************************************************************/
    /* Position at bottom of Wave Document Window                       */
    /********************************************************************/
    if (0 == (usExtHgt = CalStaHgt (lpBndRec->bottom, ulTxtExt))) {   
        ShowWindow (hWnd, SW_HIDE);
        return (FALSE);
    }
    rWrkRec.top    = lpBndRec->bottom - usExtHgt;               /* Up Y */
    rWrkRec.bottom = usExtHgt;                                  /* Hgt  */

    /********************************************************************/
    /********************************************************************/
    ShowWindow (hWnd, SW_SHOW);
    MoveWindow (hWnd, rWrkRec.left, rWrkRec.top, rWrkRec.right, 
        rWrkRec.bottom, TRUE);

    /********************************************************************/
    /********************************************************************/
    lpBndRec->bottom = rWrkRec.top;                             /* Hgt  */
    return (TRUE);

}

WORD    CalStaHgt (WORD usMaxHgt, DWORD ulTxtExt)
{

    WORD    usExtHgt;

    /********************************************************************/
    /* Set height to text height + 8 pels                              */
    /********************************************************************/
    usExtHgt = 8 + HIWORD (ulTxtExt);

    /********************************************************************/
    /* Check if enough room to show                                     */
    /********************************************************************/
    if ((WORD) (5 * usExtHgt) > usMaxHgt) usExtHgt = 0;

    return (usExtHgt);

}



