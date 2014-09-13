/************************************************************************/
/* Dialogic Digitizer Media Ctl I/F: DlgDig.c           V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define  NOCOMM                         /* Inhibit certain windows defs */
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\..\tifdll\tiflib\dlglib.h" /* Dialogic D4x stand defs      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */
#include "..\effdev\geneff.h"           /* Sound Effects definitions    */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */
#include "dlgdig.h"                     /* Dialogic TMI definitions     */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  TMIGLO  TMIGlo;                 /* Generic TMI Lib Globals      */

/************************************************************************/
/************************************************************************/
WORD    BufBlkAlo (BUFBLK FAR *, DWORD);
WORD    BufBlkRel (BUFBLK FAR *);
WORD    WaiForEvt (HWND, FARPROC, LPSTR);

/************************************************************************/
/************************************************************************/
LONG FAR PASCAL TMICBkWin (HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    VISMEMHDL       mhDIOMem;
    DIORES FAR    * lpDIORes;    

    switch (uMsg) {
        case WM_CREATE:
            /************************************************************/
            /* Store instance specific data pointer                     */
            /************************************************************/
            mhDIOMem = (VISMEMHDL) ((LPCREATESTRUCT) lParam)->lpCreateParams;
            if (!SetProp (hWnd, PRPLOW, (HANDLE) LOWORD (mhDIOMem)) ||
                !SetProp (hWnd, PRPHGH, (HANDLE) HIWORD (mhDIOMem))) {
                EndDialog (hWnd, -1);
                break;
            }
            break;

        case WM_TIFEVT:
            /************************************************************/
            /************************************************************/
            if (NULL == (mhDIOMem = (VISMEMHDL) MAKELONG 
                (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) break;
            if (NULL == (lpDIORes = GloMemLck (mhDIOMem))) break;

            /************************************************************/
            /************************************************************/
            if (T_EOF == wParam) {
                /********************************************************/
                /* Alert user to underflow condition                    */
                /* Insure that index count underflow does not cause err */
                /* Force buffer routines to recognize end of I/O        */
                /********************************************************/
                if (lpDIORes->cbChdBlk.usCurIdx >= (IDXARRCNT - 1)) {
                    MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIEXTUND);
                    lpDIORes->dbDIOBlk.usBufAct = 0;
                }
                else {
                    if (-1L != lpDIORes->cbChdBlk.irIdxRec
                        [lpDIORes->cbChdBlk.usCurIdx+1].ulIdxOff)
                        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIBUFUND);
                        lpDIORes->dbDIOBlk.usBufAct = 0;
                }
            }
            /************************************************************/
            /************************************************************/
            if (NULL != lpDIORes->tbTIFBlk.hEvtWnd) 
                SendMessage (lpDIORes->tbTIFBlk.hEvtWnd, 
                (WORD) lpDIORes->tbTIFBlk.ulEvtArg, wParam, lParam);
            GloMemUnL (mhDIOMem);
            break;

        case WM_TIMER:
            /************************************************************/
            /* Get pointer to instance data for digitizer callback.     */
            /************************************************************/
            if (NULL == (mhDIOMem = (VISMEMHDL) MAKELONG 
                (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) break;
            if (NULL == (lpDIORes = GloMemLck (mhDIOMem))) break;

            /************************************************************/
            /* Call timer procedure, ask if buffer is done.             */
            /************************************************************/
            if ((NULL != lpDIORes->fpTimPrc) && lpDIORes->fpTimPrc 
              (&lpDIORes->dbDIOBlk, &lpDIORes->cbChdBlk)) {
                /********************************************************/
                /* Buffer done; request another                         */
                /********************************************************/
                if (NULL != lpDIORes->fpDevPrc) lpDIORes->fpDevPrc (TMIPOLCNT, 
                    &lpDIORes->dbDIOBlk, &lpDIORes->cbChdBlk);
            }
            GloMemUnL (mhDIOMem);
            break;

        case WM_DESTROY:
            RemoveProp (hWnd, PRPLOW);
            RemoveProp (hWnd, PRPHGH);
            break;

    }

    return DefWindowProc (hWnd, uMsg, wParam, lParam);
}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL TMISysIni (VISMEMHDL FAR *pmhSysRes, VISMEMHDL mhCfgMem)
{
    SYSRES FAR *lpSysRes;    
    DIGCFG FAR *lpDigCfg;    
    WORD        usRetCod;

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpSysRes = GloAloLck (GMEM_MOVEABLE, pmhSysRes, 
        sizeof (SYSRES)))) return ((WORD) -1);
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) {
        *pmhSysRes = GloAloRel (*pmhSysRes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Check if Voice Board driver is installed. If not, return.        */
    /*                                                                  */
    /* Set Reg Key = strrev (BASE36 (App Key || Usr Key))               */
    /* Full: 1033 || 1123 (x11) = swap (NR80 || 5J90)                   */ 
    /* Beta: 1039 || 1129 (x11) = swap (HT80 || ZK90)                   */ 
    /********************************************************************/
    usRetCod = TIFSupIni (lpDigCfg->tdTMIDef.scSysCfg.sVBSwIn, 0L, 
        (DWORD) (LPSTR) "-kz990z990");
    if (usRetCod) {
        MsgDspRes (TMIGlo.hLibIns, 0, TIFBASMSG + usRetCod);
        *pmhSysRes = GloAloRel (*pmhSysRes);
        GloMemUnL (mhCfgMem);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Set board parameters; if error, use defaults and continue        */
    /********************************************************************/
    usRetCod = setxparm (&lpDigCfg->dbDlgDCB);
    if (usRetCod && (E_SACT != usRetCod)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIUSEDEF);
    }

    /********************************************************************/
    /* Initialize Voice and Multiplexer boards.                         */
    /* Start system, on error return code for ASCII error message       */
    /********************************************************************/
    lpSysRes->usDigIni = startsys (lpDigCfg->tdTMIDef.scSysCfg.sVBHwIn, 0, 0, &lpSysRes->usLinCnt);
    if (E_SUCC != lpSysRes->usDigIni) {
        switch (lpSysRes->usDigIni) {
        case E_FAILST:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIBADVBD);    /* Voice brd(s) failed self tst */
          break;
        case E_SNACT:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBDINA);    /* Voice board(s) NOT active    */
          break;
        case E_BADDL:                
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBHERR);    /* Voice board(s) hardware err  */
          break;
        case E_BADINT:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBIERR);    /* Voice brd int lvl not avail  */
          break;
        case E_NOMEM:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIDRIMEM);    /* Voice driver insuff mem      */
          break;
        case E_EMSSW:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIBADEMS);    /* Voice drv EMS missing/corrup */
          break;
        case E_EMSERR:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIERREMS);    /* Voice driver EMS error       */
          break;
        default:
          MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBDERR);    /* V brd fail: Chk inst & set   */
          break;
        }
        TIFSupTrm ();
        GloMemUnL (mhCfgMem);
        *pmhSysRes = GloAloRel (*pmhSysRes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Start Multiplexer driver                                         */
    /********************************************************************/
    if (0 != lpDigCfg->tdTMIDef.scSysCfg.sMxHwIn) {      /* MXHWIR = 0: disabled */
        lpSysRes->usMpxIni = startamx (lpDigCfg->tdTMIDef.scSysCfg.sMxHwIn, &lpSysRes->usPrtCnt);
        if (E_SUCC != lpSysRes->usMpxIni) {
            switch (usRetCod) {
            case E_NOAMX:
              MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIMXINUL);  /* Mpx board not installed      */
              break;
            case E_BADINT:
              MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIMXIERR);  /* Mpx brd int level not avail  */
              break;
            case E_AMXON:
              MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIMXSTRT);  /* Mpx board(s) already started */
              break;
            default:
              MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIMXBERR);  /* Mpx brd fail: Chk inst & set */
              break;
            }
            stopsys ();
            TIFSupTrm ();
            GloMemUnL (mhCfgMem);
            *pmhSysRes = GloAloRel (*pmhSysRes);
            return ((WORD) -1);
        }
    }

#if ((defined (DLG))) /**************************************************/
    /********************************************************************/
    /* Get additional information about Dialogic board type             */
    /********************************************************************/
    {
        LPVOID  FAR PASCAL  ExtGetSig (WORD, short);
        #define BRDTYPOFF   0x010d
        #define BRDTYP_AB   0x0001
        lpSysRes->usDigTyp = * (LPBYTE) ExtGetSig (getvctr (), BRDTYPOFF) > BRDTYP_AB;
    }
#endif /*****************************************************************/

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    GloMemUnL (*pmhSysRes);
    return (0);

}

BOOL FAR PASCAL TMISysTrm (VISMEMHDL FAR *pmhSysRes)
{
    SYSRES FAR *lpSysRes;    

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpSysRes = GloMemLck (*pmhSysRes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    stopamx ();
    stopsys ();
    TIFSupTrm ();

    /********************************************************************/
    /********************************************************************/
    *pmhSysRes = GloAloRel (*pmhSysRes);
    return (0);
}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL TMIDigAlo (VISMEMHDL FAR *pmhDIORes, VISMEMHDL mhCfgMem, 
                HWND FAR *phCBkWnd, WORD usBlkLen, WORD usBlkCnt, 
                HWND hEvtWnd, DWORD ulEvtArg) 
{
    DIORES FAR *lpDIORes;    
    DIGCFG FAR *lpDigCfg;    

    /********************************************************************/
    /* Allocate and initialize digitizer I/O resource data block.       */
    /********************************************************************/
    if (NULL == (lpDIORes = GloAloLck (GMEM_MOVEABLE, pmhDIORes, 
        sizeof (DIORES)))) return ((WORD) -1);
    _fmemset (lpDIORes, 0, sizeof (*lpDIORes));

    /********************************************************************/
    /* Lock system configuration memory                                 */
    /********************************************************************/
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) {
        *pmhDIORes = GloUnLRel (*pmhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Copy line configuration                                          */
    /********************************************************************/
    lpDIORes->lcLinCfg = lpDigCfg->tdTMIDef.lcLinCfg;
    GloMemUnL (mhCfgMem);

    /********************************************************************/
    /* Allocate & lock all buffered data blocks                         */
    /* On failure, release previous blks (ignore failed, already clear) */
    /********************************************************************/
    lpDIORes->dbDIOBlk.ulBufSiz = max (min (usBlkLen, BLKLENMAX), BLKLENMIN) * 1024L;
    lpDIORes->dbDIOBlk.usBufCnt = max (min (usBlkCnt, BLKCNTMAX), BLKCNTMIN);

    if (BufBlkAlo (&lpDIORes->cbChdBlk.bbPCMWrk, lpDIORes->dbDIOBlk.ulBufSiz)) {
        BufBlkRel (&lpDIORes->cbChdBlk.bbPCMWrk);
        *pmhDIORes = GloUnLRel (*pmhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Allocate cached transfer indexed file memory                     */
    /********************************************************************/
    lpDIORes->cbChdBlk.irIdxRec = (IDXREC FAR *) 
        MemGetRea (&lpDIORes->cbChdBlk.ulReaMem, 
        &lpDIORes->cbChdBlk.usMemHdl, 
        lpDIORes->cbChdBlk.usMemSiz = IDXARRCNT * sizeof (IDXREC));
    if (NULL == lpDIORes->cbChdBlk.irIdxRec) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIINSREA);    
        *pmhDIORes = GloUnLRel (*pmhDIORes);
        return ((WORD) -1);
    }
    _fmemset (lpDIORes->cbChdBlk.irIdxRec, 0xff, lpDIORes->cbChdBlk.usMemSiz);

    /********************************************************************/
    /* Create the callback window                                       */
    /********************************************************************/
    *phCBkWnd = lpDIORes->hCBkWnd = CreateWindow (
    SI_TMICBKCLS,                           /*  Window class name.      */
    "",                                     /*  Window title.           */
    WS_DISABLED,                            /*  Type of window.         */
    CW_USEDEFAULT,                          /*  x - default location    */
    0,                                      /*  y - default             */
    CW_USEDEFAULT,                          /*  cx - (width)  default   */
    0,                                      /*  cy - (height) default   */
    NULL,                                   /*  No parent for this wind */
    NULL,                                   /*  Use the class menu.     */
    TMIGlo.hLibIns,                         /*  Who created this window */
    (LPSTR) (DWORD) *pmhDIORes              /*  Pass Dig I/O resource   */
    );

    if (NULL == lpDIORes->hCBkWnd) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMICRECBK);    
        BufBlkRel (&lpDIORes->cbChdBlk.bbPCMWrk);
        *pmhDIORes = GloUnLRel (*pmhDIORes);
        return ((WORD) -1);
    }
    lpDIORes->tbTIFBlk.hEvtWnd  = hEvtWnd;
    lpDIORes->tbTIFBlk.ulEvtArg = ulEvtArg;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhDIORes);
    return (0);
}

BOOL FAR PASCAL TMIDigRel (VISMEMHDL FAR *pmhDIORes)
{
    DIORES FAR *lpDIORes;    

    /********************************************************************/
    /* Get pointer to instance data for digitizer callback.             */
    /********************************************************************/
    if (NULL == (lpDIORes = GloMemLck (*pmhDIORes))) return ((WORD) -1);
    
    /********************************************************************/
    /* Destroy the callback window                                      */
    /********************************************************************/
    DestroyWindow (lpDIORes->hCBkWnd);

    /********************************************************************/
    /* Free buffer memory                                               */
    /********************************************************************/
    BufBlkRel (&lpDIORes->cbChdBlk.bbPCMWrk);

    /********************************************************************/
    /* Free cached transfer indexed file memory                         */
    /********************************************************************/
    lpDIORes->cbChdBlk.usMemHdl = MemRelRea (lpDIORes->cbChdBlk.usMemHdl);
        
    /********************************************************************/
    /********************************************************************/
    *pmhDIORes = GloUnLRel (*pmhDIORes);
    return (0);

}

WORD FAR PASCAL TMILinOpn (WORD FAR *pusLinNum, HWND hCBkWnd, 
                VISMEMHDL mhCfgMem, LPSTR szDesStr, WORD usMaxLen)
{
    DIGCFG FAR *lpDigCfg;    
    CSB         cbDlgCSB;

    /********************************************************************/
    /********************************************************************/
    if (szDesStr) *szDesStr = '\0';

    /********************************************************************/
    /* Lock system configuration memory                                 */
    /********************************************************************/
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Request a digitizer line                                         */
    /********************************************************************/
    if (0 == (*pusLinNum = TIFLinGet (lpDigCfg->tdTMIDef.scSysCfg.sLinNum,
      CALLBACK_WINDOW, MAKELONG (hCBkWnd, WM_TIFEVT)))) {
        GloMemUnL (mhCfgMem);
        return (SI_TMINOLINI);          /* Cannot Initialize Line       */
    }
//AMX
//    if (0 == (*pusMpxInp = TIFPrtGet (lpDigCfg->tdTMIDef.scSysCfg.sMpxInp, lpDigCfg->tdTMIDef.scSysCfg.sMpxOut)

    /********************************************************************/
    /*                  Initialize line parameters.                     */
    /********************************************************************/
    getcstat (*pusLinNum, &cbDlgCSB);                       /* Clr err  */
    setcparm (*pusLinNum, &lpDigCfg->cbDlgCPB);             /* Set CPB  */
    setcst   (*pusLinNum, lpDigCfg->usCSTInt, 1);           /* CST ints */

    /********************************************************************/
    /* Stop & clear all current line activity                           */
    /********************************************************************/
    stopch (*pusLinNum);
    ClrEvtQue (*pusLinNum);                                 /* Clr Que  */

    /********************************************************************/
    /********************************************************************/
//AMX
//    TIFPrtGet (usPrtNum, 0L, 0L);

    /********************************************************************/
    /* Set line hook state                                              */
    /********************************************************************/
    if (lpDigCfg->tdTMIDef.scSysCfg.sWaiCal) {
        sethook (*pusLinNum, H_ONH);
        if (OOH_TRM != PolEvtQue (*pusLinNum, hCBkWnd, OOH_TRM, EVTPOLTIM)) {
            GloMemUnL (mhCfgMem);
            return ((DWORD) SI_TMINOHOOK);      /* Cannot on/off hook   */
        }
        /****************************************************************/
        /****************************************************************/
        WaiForEvt (hCBkWnd, (FARPROC) RngWaiBoxPrc, "RNGWAIBOX"); 
        ClrEvtQue (*pusLinNum);
    }

    /********************************************************************/
    /* Flush event que and pick up line                                 */
    /********************************************************************/
    sethook (*pusLinNum, H_OFFH);

//    char        szWrkStr[TMIMAXMSG];
//    /********************************************************************/
//    /* Load manufacturer-specific name string                           */
//    /********************************************************************/
//#if ((defined (BCM))) /**************************************************/
//    MsgLodStr (TMIGlo.hLibIns, SI_TMIBCMPRO, szWrkStr, TMIMAXMSG-1);
//#endif /*****************************************************************/
//#if ((defined (DLG))) /**************************************************/
//    MsgLodStr (TMIGlo.hLibIns, SI_TMIDLGPRO, szWrkStr, TMIMAXMSG-1);
//#endif /*****************************************************************/
//#if ((defined (NWV))) /**************************************************/
//    MsgLodStr (TMIGlo.hLibIns, SI_TMINWVPRO, szWrkStr, TMIMAXMSG-1);
//#endif /*****************************************************************/
//#if ((defined (RTX))) /**************************************************/
//    MsgLodStr (TMIGlo.hLibIns, SI_TMIRTXPRO, szWrkStr, TMIMAXMSG-1);
//#endif /*****************************************************************/

    /********************************************************************/
    /********************************************************************/
    if (szDesStr) wsprintf (szDesStr, "Telephony TSR Line %i (%i, %i)", 
        *pusLinNum, 0, 0);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    return (0);
}

BOOL FAR PASCAL TMILinCls (WORD usLinNum, HWND hCBkWnd)
{

//    DIGCFG FAR *lpDigCfg;    
//    /********************************************************************/
//    /********************************************************************/
//    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) return ((WORD) -1);

    /********************************************************************/
    /********************************************************************/
    DigDevStp (usLinNum, hCBkWnd);

//    /********************************************************************/
//    /* Set final hook state                                             */
//    /********************************************************************/
//    if (lpDigCfg->tdTMIDef.scSysCfg.sTrmOOH) {
//        sethook (usLinNum, H_ONH);
//        PolEvtQue (usLinNum, hCBkWnd, OOH_TRM, EVTPOLTIM);
//    }

    /********************************************************************/
    /* Release digitizer line                                           */
    /********************************************************************/
    TIFLinRel (usLinNum, 0L, 0L);

    /********************************************************************/
    /********************************************************************/
//AMX
//    TIFPrtRel (usPrtNum, 0L, 0L);
//    GloMemUnL (mhCfgMem);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

/************************************************************************/
/************************************************************************/
WORD    BufBlkAlo (BUFBLK FAR *lpBufBlk, DWORD ulBufSiz)
{
    /********************************************************************/
    /* Allocate & lock buffered waveform data memory.                   */
    /********************************************************************/
    if (NULL == (lpBufBlk->lpBufMem = GloAloLck 
      (GMEM_MOVEABLE | GMEM_SHARE, &lpBufBlk->mhBufHdl, ulBufSiz))) {
        return ((WORD) -1);
    }
    return (0);

}

WORD    BufBlkRel (BUFBLK FAR *lpBufBlk)
{
    lpBufBlk->mhBufHdl= GloUnLRel (lpBufBlk->mhBufHdl);
    return (0);
}

/************************************************************************/
/*                      Event Support Routines                          */
/************************************************************************/
WORD WaiForEvt (HWND hCBkWnd, FARPROC lpDBxPrc, LPSTR szDBxNam)
{

    FARPROC     lpPrcAdr;
    BOOL        bWaiCnt;
    HWND        hWaiBox;
    MSG         msg;

    /********************************************************************/
    /* Assume that the current active window is the message window      */
    /********************************************************************/
    EnableWindow (GetParWnd (NULL), FALSE);

    /********************************************************************/
    /********************************************************************/
    lpPrcAdr = MakeProcInstance (lpDBxPrc, TMIGlo.hLibIns);
    hWaiBox = CreateDialogParam (TMIGlo.hLibIns, szDBxNam, GetParWnd (NULL), 
        (DLGPROC) lpPrcAdr, (DWORD) ((LPVOID) &bWaiCnt));

    /********************************************************************/
    /* Wait fo rmessages to come in for event callback window           */
    /********************************************************************/
    while ((bWaiCnt) && GetMessage (&msg, NULL, 0, 0)) {
        if ((hCBkWnd == msg.hwnd) && (WM_TIFEVT == msg.message))
            msg.hwnd = hWaiBox;
        if (!IsDialogMessage (hWaiBox, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage (&msg);
        }
    }

    /********************************************************************/
    /********************************************************************/
    EnableWindow  (GetParWnd (NULL), TRUE);
    DestroyWindow (hWaiBox);
    FreeProcInstance (lpPrcAdr);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

BOOL FAR PASCAL RngWaiBoxPrc (HWND hWnd, unsigned uMsg, WPARAM wParam,
                LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    BOOL FAR *      lpWaiCnt;

    switch (uMsg) {
        case WM_INITDIALOG:
            /************************************************************/
            /* Store instance specific data pointer                     */
            /************************************************************/
            if (!SetProp (hWnd, PRPLOW, (HANDLE) LOWORD (lParam)) ||
                !SetProp (hWnd, PRPHGH, (HANDLE) HIWORD (lParam))) {
                *lpWaiCnt = FALSE;
                break;
            }
            lpWaiCnt = (BOOL FAR *) lParam;
        
            /************************************************************/
            /************************************************************/
            CtrDlgBox (NULL, hWnd, NULL, CTR_CTR);
            *lpWaiCnt = TRUE;
            break;

            /************************************************************/
            /* Terminate on rings received                              */
            /************************************************************/
        case WM_TIFEVT:
            if (NULL == (lpWaiCnt = (BOOL FAR *) MAKELONG 
                (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) break;
            if (!TstTrmEvt (wParam, RNG_TRM)) break;
            *lpWaiCnt = FALSE;
            break;

        case WM_CTLCOLOR:
          if ((CTLCOLOR_DLG == HIWORD (lParam)) 
            || (CTLCOLOR_STATIC == HIWORD (lParam)) 
            || (CTLCOLOR_BTN == HIWORD (lParam))) { 
              SetBkColor ((HDC) wParam, TMIGlo.ulDBxClr);
              return ((BOOL) TMIGlo.hDBxBsh);
          }
          return (FALSE);

        /****************************************************************/
        /* Do not use WM_CLOSE and DestroyWindow: Focus gets messy      */
        /****************************************************************/
        case WM_CHAR:
            if (' ' != wParam) break;
        case WM_COMMAND:
            if (NULL == (lpWaiCnt = (BOOL FAR *) MAKELONG 
                (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) break;
            *lpWaiCnt = FALSE;
            break;

        case WM_DESTROY:
            RemoveProp (hWnd, PRPLOW);
            RemoveProp (hWnd, PRPHGH);
            break;

        default:
            return(FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    return (TRUE);

}
  


