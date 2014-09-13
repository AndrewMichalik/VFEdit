/************************************************************************/
/* VFEdit VBase File Ask Support: VBSFAs.c              V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#if (defined (W31)) /****************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#endif /*****************************************************************/
#if (defined (DOS)) /****************************************************/
#include "visdef.h"                     /* VIS Standard type defs       */
#include "..\os_dev\dosmem.h"           /* Generic memory support defs  */
#include "..\os_dev\dosmsg.h"           /* User message support defs    */
#endif /*****************************************************************/
#include "..\os_dev\dllsup.h"           /* Windows DLL support defs     */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "vbsfil.h"                     /* VBase file format defs       */

#include <string.h>                     /* String manipulation functions*/
  
/************************************************************************/
/*                  Forward & External References                       */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */
  
/************************************************************************/
/*                  Dialog Box Data Transfer Defs                       */
/*   Separate local allocs and dialog inst props permit full re-entry   */
/************************************************************************/
#define usIDXSEL    (pInsBlk->usIdxSel) /* Current array index number   */
#define usIDXCNT    (pInsBlk->usIdxCnt) /* Current index array maximum  */
#define dbARRBPS    (pInsBlk->dbArrBpS) /* Byte per sec rate for array  */
#define lpIDXARR    (pInsBlk->lpIdxArr) /* Index source array pointer   */
#define usINSSID    (pInsBlk->usInsSID) /* User instruction string ID   */
#define usTXTLEN    (pInsBlk->usTxtLen) /* Annotation text length       */
#define ofTXTFIL    (pInsBlk->ofTxtFil) /* Annotation text file         */

typedef struct {                        /* Dbx instance data block      */
    WORD        usIdxSel;               /* Current array index number   */
    WORD        usIdxCnt;               /* Current index array maximum  */
    double      dbArrBpS;               /* Byte per sec rate for array  */
    VBIREC FAR *lpIdxArr;               /* Index source array pointer   */
    WORD        usInsSID;               /* User instruction string ID   */
    WORD        usTxtLen;               /* Annotation text length       */
    OFSTRUCT_V    ofTxtFil;               /* Annotation text file         */
} DBXINSBLK;

/************************************************************************/
/************************************************************************/
void    IdxLstCmd (HWND, LONG, WORD *, WORD *, VBIREC FAR *, OFSTRUCT_V *, WORD *);
LPSTR   IdxSelTxt (WORD, DWORD, double, LPSTR);  
WORD    SetAnoTxt (LPOFSTRUCT_V, DWORD, HWND, WORD);
LPSTR   _fdtorna (double, short, LPSTR);

/************************************************************************/
/************************************************************************/
WORD    FAR PASCAL VBSCntAsk ()
{       
    unsigned    uiIdxCnt = VBSCNTDEF;

    /********************************************************************/
    /* New indexed file: Ask user for index count                       */
    /********************************************************************/
    if (!MsgAskRes (FIOGlo.hLibIns, "MSGASKBOX", MsgAskFmtPrc,
      SI_IDXCNTREQ, "%i", (LPVOID) &uiIdxCnt)) {
        return (0);
    }
    while ((uiIdxCnt <= 0) || (uiIdxCnt > VBSMAXIDX)) {
        MessageBeep (0);
        uiIdxCnt = VBSCNTDEF;
        if (!MsgAskRes (FIOGlo.hLibIns, "MSGASKBOX", MsgAskFmtPrc,
          SI_IDXCNTREQ, "%i", (LPVOID) &uiIdxCnt)) {
            return (0);
        }
    }
    return (uiIdxCnt);
    
}

FIORET  FAR PASCAL VBSIdxJmp (short sIdxOff, OFSTRUCT_V FAR * pofSrcFil, 
        VISMEMHDL mhHdrMem, VISMEMHDL mhIdxMem, IDXSEG FAR *lpIdxSeg)
{
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxArr;
    DWORD       ulIdxTot;
    long        lIdxNew;

    /********************************************************************/
    /* Lock header memory and retrieve array information                */
    /********************************************************************/
    if ((VBSHDR FAR *) NULL == (lpVBSHdr = (VBSHDR FAR *) GloMemLck (mhHdrMem))) 
        return (FIORETERR); 
    ulIdxTot = (WORD) lpVBSHdr->ulIdxTot;
    GloMemUnL (mhHdrMem);

    /********************************************************************/
    /* Calculate new index position; ensure range; return if unchanged  */
    /********************************************************************/
    lIdxNew = (long) lpIdxSeg->usIdxNum + (long) sIdxOff;
    lIdxNew = max (1, min (lIdxNew, (long) ulIdxTot));
    if (lIdxNew == (long) lpIdxSeg->usIdxNum) return (FIORETCAN);

    /********************************************************************/
    /* Assume VBase format is OK for present; lock index array          */
    /********************************************************************/
    if ((VBIREC FAR *) NULL == (lpIdxArr = (VBIREC FAR *) GloMemLck (mhIdxMem)))
        return (FIORETERR); 

    /********************************************************************/
    /* Update segment information block                                 */
    /********************************************************************/
    lpIdxSeg->usIdxNum = (WORD) lIdxNew;
    lpIdxSeg->ulVoxOff = lpIdxArr[lpIdxSeg->usIdxNum - 1].ulVoxOff; 
    lpIdxSeg->ulVoxLen = lpIdxArr[lpIdxSeg->usIdxNum - 1].ulVoxLen; 
    lpIdxSeg->ulTxtOff = lpIdxArr[lpIdxSeg->usIdxNum - 1].ulTxtOff; 
    lpIdxSeg->ulTxtSiz = SetAnoTxt (pofSrcFil, lpIdxSeg->ulTxtOff, 0, 0)
                         + lpIdxSeg->ulTxtOff ? 1L : 0L;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhIdxMem);
    return (FIORETSUC);

}

FIORET  FAR PASCAL VBSIdxAsk (WORD usTtlSID, OFSTRUCT_V FAR * pofSrcFil, 
        float flPCMSiz, VISMEMHDL mhHdrMem, VISMEMHDL mhIdxMem, 
        IDXSEG FAR *lpIdxSeg)
{       
    VISMEMHDL   hInsBlk;                /* Instance data block handle   */
    DBXINSBLK * pInsBlk;                /* Inst local data block ptr    */
    VBSHDR FAR *lpVBSHdr;
    FARPROC     lpPrcAdr;

    /********************************************************************/
    /* Allocate shared local memory for this instance of dialog box     */
    /********************************************************************/
    if (NULL == (pInsBlk = LocAloLck (&hInsBlk, sizeof (DBXINSBLK)))) 
        return (FIORETERR);

    /********************************************************************/
    /* Lock header memory and retrieve array information                */
    /********************************************************************/
    if ((VBSHDR FAR *) NULL == (lpVBSHdr = (VBSHDR FAR *) GloMemLck (mhHdrMem))) {
        LocUnLRel (hInsBlk);
        return (FIORETERR); 
    }
    usIDXCNT = (WORD) lpVBSHdr->ulIdxTot;
    dbARRBPS = flPCMSiz * lpVBSHdr->ulSmpFrq;
    GloMemUnL (mhHdrMem);

    if ((lpIdxSeg->usIdxNum > 0) && (lpIdxSeg->usIdxNum <= usIDXCNT)) 
        usIDXSEL = lpIdxSeg->usIdxNum - 1;
    else usIDXSEL = 0;

    /********************************************************************/
    /* Assume VBase format is OK for present; lock index array          */
    /********************************************************************/
    if ((VBIREC FAR *) NULL == (lpIDXARR = (VBIREC FAR *) GloMemLck (mhIdxMem))) {
        LocUnLRel (hInsBlk);
        return (FIORETERR); 
    }

    /********************************************************************/
    /* Set the instruction text ID and annotation text source file      */
    /********************************************************************/
    usINSSID = usTtlSID;     
    ofTXTFIL = *pofSrcFil;

    /********************************************************************/
    /* Activate dialog box procedure                                    */
    /********************************************************************/
    lpPrcAdr = MakeProcInstance ((FARPROC) SelFilIdxPrc, FIOGlo.hLibIns);
    if (-1 == DialogBoxParam (FIOGlo.hLibIns, "IDXSELBOX", GetParWnd (NULL), 
      (DLGPROC) lpPrcAdr, (DWORD) (WORD) pInsBlk)) {
        FreeProcInstance (lpPrcAdr);
        GloMemUnL (mhIdxMem);
        LocUnLRel (hInsBlk);
        return (FIORETCAN);
    }
    FreeProcInstance (lpPrcAdr);

    /********************************************************************/
    /* Update segment information block                                 */
    /********************************************************************/
    lpIdxSeg->usIdxNum = usIDXSEL + 1;
    if (SI_IDXCREBFR == usINSSID) {
        lpIdxSeg->ulVoxOff = 0L;
        lpIdxSeg->ulVoxLen = 0L;
        lpIdxSeg->ulTxtOff = 0L;
        lpIdxSeg->ulTxtSiz = 0L;
    }
    else {
        lpIdxSeg->ulVoxOff = lpIDXARR[usIDXSEL].ulVoxOff; 
        lpIdxSeg->ulVoxLen = lpIDXARR[usIDXSEL].ulVoxLen; 
        lpIdxSeg->ulTxtOff = lpIDXARR[usIDXSEL].ulTxtOff; 
        lpIdxSeg->ulTxtSiz = (DWORD) usTXTLEN + lpIdxSeg->ulTxtOff ? 1L : 0L;
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhIdxMem);
    LocUnLRel (hInsBlk);
    return (FIORETSUC);

}

/************************************************************************/
/************************************************************************/
BOOL    FAR PASCAL SelFilIdxPrc (HWND hWnd, unsigned uMsg, WPARAM wParam,
        LPARAM lParam)
{
    #define DBXPRPTXT   "SelFilIdx"
    #define FAKLOCHDL   HANDLE          /* Fake local handle            */
    #define FAKLOCPTR   VOID NEAR *     /* Fake local pointer           */

    char        szWrkBuf [FIOMAXSTR];
    DBXINSBLK * pInsBlk;                /* Inst local data block ptr    */
    WORD        usi;
    HCURSOR     hLngCurOrg;             

    switch (uMsg) {
    case WM_INITDIALOG:
        /****************************************************************/
        /* Store instance specific data pointer                         */
        /****************************************************************/
        if (!SetProp (hWnd, DBXPRPTXT, (FAKLOCHDL) (pInsBlk = (FAKLOCPTR) lParam))) {
            EndDialog (hWnd, -1);
            break;
        }
        /****************************************************************/
        /****************************************************************/
        CtrDlgBox (NULL, hWnd, NULL, CTR_CTR);
        MsgLodStr (FIOGlo.hLibIns, usINSSID, (LPSTR) szWrkBuf, FIOMAXSTR);
        SetDlgItemText (hWnd, DI_IDXINS, szWrkBuf);

        /****************************************************************/
        /* Set system fixed font listbox if Win 3                       */
        /****************************************************************/
        #if (defined (WF_ENHANCED))                         /* Win 2/3  */ 
            SendMessage (GetDlgItem (hWnd, DI_IDXHDR),
                WM_SETFONT, (WPARAM) GetStockObject (SYSTEM_FIXED_FONT), 0L);
            SendMessage (GetDlgItem (hWnd, DI_IDXLST),
                WM_SETFONT, (WPARAM) GetStockObject (SYSTEM_FIXED_FONT), 0L);
        #endif            

        /****************************************************************/
        /* Show Hour-Glass for time consuming operations                */
        /****************************************************************/
        hLngCurOrg = SetCursor (LoadCursor (NULL, IDC_WAIT));
        ShowCursor (TRUE);

        /****************************************************************/
        /* Update list box entries                                      */
        /****************************************************************/
        for (usi = 0; usi < usIDXCNT; usi++) {
            IdxSelTxt (usi+1, lpIDXARR[usi].ulVoxLen, dbARRBPS, szWrkBuf);  
            if (LB_ERRSPACE == (WORD) SendDlgItemMessage (hWnd,
              DI_IDXLST, LB_ADDSTRING, 0, (LONG) ((LPSTR) szWrkBuf))) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_IDXINSMEM); /* Insuff Idx Mem   */
                break;
            }
        }

        /****************************************************************/
        /* Hide Hour-Glass                                              */
        /****************************************************************/
        ShowCursor (FALSE);
        SetCursor (hLngCurOrg);

        /****************************************************************/
        /****************************************************************/
        if (SI_IDXCREBFR == usINSSID) {
            MsgLodStr (FIOGlo.hLibIns, SI_IDXEOFTXT, (LPSTR) szWrkBuf, FIOMAXSTR);
            SendDlgItemMessage (hWnd, DI_IDXLST,
                LB_ADDSTRING, 0, (LONG) ((LPSTR) szWrkBuf));
        }
        /****************************************************************/
        /****************************************************************/
        if (usIDXSEL != -1) {
            SendDlgItemMessage (hWnd, DI_IDXLST, LB_SETCURSEL,
                usIDXSEL, (LONG) NULL);
            SendMessage (hWnd, WM_COMMAND, DI_IDXLST,
                MAKELONG (0, LBN_SELCHANGE));
            SendDlgItemMessage (hWnd, DI_IDXNUM, EM_SETSEL, 0, MAKELONG (0, 32767));
        }
        return TRUE;

   case WM_CTLCOLOR:
      if ((CTLCOLOR_DLG == HIWORD (lParam)) 
        || (CTLCOLOR_STATIC == HIWORD (lParam))) { 
          SetBkColor ((HDC) wParam, FIOGlo.ulDBxClr);
          return ((BOOL) FIOGlo.hDBxBsh);
      }
      return (FALSE);

   case WM_COMMAND:
      if (NULL == (pInsBlk = (FAKLOCPTR) GetProp (hWnd, DBXPRPTXT))) {
          EndDialog (hWnd, -1);
          break;
      }
      switch (wParam) {
        case DI_IDXLST:
            IdxLstCmd (hWnd, lParam, &usIDXSEL, &usIDXCNT, lpIDXARR, 
                &ofTXTFIL, &usTXTLEN);
            break;
  
        /****************************************************************/
        /* OK Button (or OK message sent by double-click                */
        /****************************************************************/
        case IDOK:
            GetDlgItemText (hWnd, DI_IDXNUM, szWrkBuf, FIOMAXSTR);
            usIDXSEL = _fatoi (szWrkBuf) - 1;
            if (((unsigned) usIDXSEL > usIDXCNT) ||
                ((usIDXSEL == usIDXCNT) && (SI_IDXCREBFR != usINSSID))) {
                usIDXSEL = (WORD) -1;
                MessageBeep (0);
                break;
            }
            EndDialog (hWnd, 0);
            break;
  
        case IDCANCEL:
            EndDialog (hWnd, -1);
            break;
  
        default:
            return FALSE;
      }
      break;

    case WM_DESTROY:
      RemoveProp (hWnd, DBXPRPTXT);
      break;

    default:
        /****************************************************************/
        /****************************************************************/
        return FALSE;

    }
    return TRUE;
}


/************************************************************************/
/*              Index List Box Command Procedure                        */
/************************************************************************/
void    IdxLstCmd (HWND hWnd, LPARAM lParam, WORD *pusIdxSel, WORD *pusIdxCnt,
        VBIREC FAR * lpIdxArr, OFSTRUCT_V *pofTxtFil, WORD *pusTxtLen)
{
    char    szWrkBuf [FIOMAXSTR];

    /********************************************************************/
    /********************************************************************/
    switch (HIWORD (lParam)) {
        /****************************************************************/
        /* Return key hit on entry box                                  */
        /****************************************************************/
        case LBN_SELCHANGE:
            /************************************************************/
            /* Update index number box                                  */
            /************************************************************/
            *pusIdxSel = (short) SendDlgItemMessage (hWnd, DI_IDXLST, 
                LB_GETCURSEL, 0, 0L);
            SetDlgItemText (hWnd, DI_IDXNUM, 
                _fitoa (*pusIdxSel + 1, szWrkBuf, 10));
            /************************************************************/
            /* Update annotation text box                               */
            /************************************************************/
            if ((*pusIdxSel < *pusIdxCnt) && (*pusTxtLen = SetAnoTxt
              (pofTxtFil, lpIdxArr[*pusIdxSel].ulTxtOff, hWnd, DI_IDXTXT))) {
                EnableWindow (GetDlgItem (hWnd, DI_IDXTIN), TRUE);
                EnableWindow (GetDlgItem (hWnd, DI_IDXTXT), TRUE);
            } else {
                EnableWindow (GetDlgItem (hWnd, DI_IDXTIN), FALSE);
                EnableWindow (GetDlgItem (hWnd, DI_IDXTXT), FALSE);
            }
            /************************************************************/
            /* Update index offset box                                  */
            /************************************************************/
            if ((*pusIdxSel < *pusIdxCnt) && (0L != lpIdxArr[*pusIdxSel].ulVoxOff)) {
                SetDlgItemText (hWnd, DI_IDXOFF,
                    _fultoa (lpIdxArr[*pusIdxSel].ulVoxOff, szWrkBuf, 10));
                EnableWindow (GetDlgItem (hWnd, DI_IDXOIN), TRUE);
                EnableWindow (GetDlgItem (hWnd, DI_IDXOFF), TRUE);
            }
            else {
                SetDlgItemText (hWnd, DI_IDXOFF, "");
                EnableWindow (GetDlgItem (hWnd, DI_IDXOIN), FALSE);
                EnableWindow (GetDlgItem (hWnd, DI_IDXOFF), FALSE);
            }
            break;

        /****************************************************************/
        /* Double-click on list name                                    */
        /****************************************************************/
        case LBN_DBLCLK:
            *pusIdxSel = (short) SendDlgItemMessage (hWnd, DI_IDXLST,
                LB_GETCURSEL, 0, 0L);
            SetDlgItemText (hWnd, DI_IDXNUM,
                _fitoa (*pusIdxSel + 1, szWrkBuf, 10));
            SendMessage (hWnd, WM_COMMAND, IDOK, 0L);
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return;

}


/************************************************************************/
/*                  Index to rounded ASCII converter                    */
/************************************************************************/
LPSTR   IdxSelTxt (WORD usIdxNum, DWORD ulVoxLen, double dBypSec, 
        LPSTR szSelTxt)
{
    char    szIdxNum [20];
    char    szIdxLen [20];
    short   sNumLen, sNumPos;
    short   sLenLen, sLenPos;

    /********************************************************************/
    /* INDEX SECS.DD                                                    */            
    /* 0123456789012345678901234567890                                  */
    /********************************************************************/
    sNumLen = _fstrlen (_fitoa (usIdxNum, szIdxNum, 10));
    if (sNumLen > 4) {
        _fstrcpy (szIdxNum, "****");
        sNumLen = 4;
    }
    sNumPos = 4 - sNumLen;

    /********************************************************************/
    /********************************************************************/
    sLenLen = _fstrlen (_fdtorna ((double) ulVoxLen / dBypSec, 2, szIdxLen));
    if (sLenLen > 7) {
        _fstrcpy (szIdxLen, "*******");
        sLenLen = 7;
    }
    sLenPos = 7 - sLenLen;

    /********************************************************************/
    /********************************************************************/
    _fmemset (szSelTxt, ' ', 20);
    _fmemcpy (&szSelTxt[sNumPos], szIdxNum, sNumLen);
    _fstrcpy (&szSelTxt[5 + sLenPos], szIdxLen);

    return (szSelTxt);
  
}

/************************************************************************/
/************************************************************************/
WORD    SetAnoTxt (OFSTRUCT_V FAR *pofSrcFil, DWORD ulTxtOff, HWND hWnd, 
        WORD usTxtCID)
{
    VISMEMHDL   mhAnoMem = NULL;
    LPSTR       lpAnoTxt;
    WORD        usTxtLen;

    /********************************************************************/
    /********************************************************************/
    SetDlgItemText (hWnd, usTxtCID, "");

    /********************************************************************/
    /* If error or no text, return zero length                          */
    /********************************************************************/
    if (FIORETSUC != VBSTxtLod (pofSrcFil, ulTxtOff, &mhAnoMem)) return (0);
    if (NULL == (lpAnoTxt = GloMemLck (mhAnoMem))) return (0);
    if (!(usTxtLen = _fstrlen (lpAnoTxt))) {
        mhAnoMem = GloUnLRel (mhAnoMem);
        return (0);
    }

    /********************************************************************/
    /********************************************************************/
    if (hWnd) SetDlgItemText (hWnd, usTxtCID, lpAnoTxt);
    mhAnoMem = GloUnLRel (mhAnoMem);
    return (usTxtLen);
// Future: Return usTxtLen + 1 for active text so caller doesn't have to

}

/************************************************************************/
/*                  Double to rounded ASCII converter                   */
/************************************************************************/
LPSTR   _fdtorna (double dbSrcVal, short sDecCnt, LPSTR szTxtBuf)
{
    LPSTR   lpcCvtTxt;
    LPSTR   lpcWrkBuf = szTxtBuf;
    int     iDecPos, iSgnFlg;

    /********************************************************************/
    /********************************************************************/
    if (0.0 == dbSrcVal) return (_fstrcpy (szTxtBuf, "0"));

    /********************************************************************/
    /* Convert dbSrcVal to string, sDecCnt digits after decimal pt       */
    /********************************************************************/
    lpcCvtTxt = _ffcvt (dbSrcVal, sDecCnt, &iDecPos, &iSgnFlg);
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