/************************************************************************/
/* Dialogic Device I/O Support: DlgDIO.c                V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define  NOCOMM                         /* Inhibit certain windows defs */
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\..\tifdll\tiflib\dlglib.h" /* Dialogic D4x stand defs      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */
#include "..\pcmdev\pcmsup.h"           /* PCM/APCM xlate lib defs      */
#include "..\effdev\geneff.h"           /* Sound Effects definitions    */
#include "..\fiodev\filutl.h"           /* File utilities definitions   */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */
#include "dlgdig.h"                     /* Dialogic TMI definitions     */

#include <string.h>                     /* String manipulation funcs    */
#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <fcntl.h>                      /* Flags used in open/ sopen    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  TMIGLO  TMIGlo;                 /* Generic TMI Lib Globals      */

/************************************************************************/
/************************************************************************/
DWORD FAR PASCAL DigBufOut (TMIPOL, DIOBLK FAR *, CHDBLK FAR *); 
DWORD FAR PASCAL DigBufInp (TMIPOL, DIOBLK FAR *, CHDBLK FAR *); 
BOOL  FAR PASCAL TimPrc_IO (DIOBLK FAR *, CHDBLK FAR *);
void             TMIResOut (DIORES FAR *);
void             TMIResInp (DIORES FAR *);
WORD             CvtModFlg (PCMTYP, BOOL, BOOL, long);
DWORD            DigSmpPos (DIOBLK FAR *);
DWORD            DigBytPos (DIOBLK FAR *, BOOL);
DWORD            DigByttoS (PCMTYP, DWORD);
DWORD            hWrFilFwd (int, void huge *, DWORD, unsigned, unsigned far *);

/************************************************************************/
/************************************************************************/
TMIPRO FAR PASCAL TMIFilSta (VISMEMHDL mhDIORes, DWORD FAR *pulSmpPos) 
{
    DIORES FAR *lpDIORes;
    TMIPRO      usCtlPro = TMIUNKPRO;
	DWORD		ulSmpPos = 0L;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Playback?                                                        */
    /********************************************************************/
    if (DigBufOut == lpDIORes->fpDevPrc) {
        ulSmpPos = DigSmpPos (&lpDIORes->dbDIOBlk); 
		usCtlPro = TMIPROOUT;
    }

    /********************************************************************/
    /* Record?                                                          */
    /********************************************************************/
    if (DigBufInp == lpDIORes->fpDevPrc) {
        ulSmpPos = DigSmpPos (&lpDIORes->dbDIOBlk); 
		usCtlPro = TMIPROINP;
    }

    /********************************************************************/
    /********************************************************************/
	if (pulSmpPos) *pulSmpPos = ulSmpPos;
    return (usCtlPro);

}

WORD FAR PASCAL TMIFilPla (WORD usLinNum, VISMEMHDL mhDIORes, 
                WORD usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq, 
                LPCSTR szChdFil, TMIDIOPRC fpDIOPrc, DWORD ulDIODat,
                TMIPOLPRC fpPolPrc, DWORD ulPolDat) 
{
    DIORES FAR *lpDIORes;
    unsigned    uiErrCod;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize cached transfer file; initialize index memory         */
    /********************************************************************/
    if (-1 == (lpDIORes->cbChdBlk.usProFil = FilHdlOpn (szChdFil, 
      OF_WRITE | OF_SHARE_DENY_NONE))) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIACCCHD);    
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }
    if (-1 == FilSiz (lpDIORes->cbChdBlk.usProFil, 0, 
      lpDIORes->dbDIOBlk.ulBufSiz * lpDIORes->dbDIOBlk.usBufCnt, &uiErrCod, 0, 0L)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMISIZCHD);    
        FilHdlCls (lpDIORes->cbChdBlk.usProFil);
        lpDIORes->cbChdBlk.usProFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }
    if (-1 == (lpDIORes->cbChdBlk.usReaFil = DskFilOpn ((LPSTR) szChdFil, 
        OF_READ | OF_SHARE_DENY_NONE, &uiErrCod))) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIACCCHD);    
        FilHdlCls (lpDIORes->cbChdBlk.usProFil);
        lpDIORes->cbChdBlk.usReaFil = 0;
        lpDIORes->cbChdBlk.usProFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize WOM_DONE simulator variables                          */
    /********************************************************************/
    lpDIORes->cbChdBlk.ulPstByt = 0L;
    lpDIORes->cbChdBlk.usCurIdx = 0;
    lpDIORes->cbChdBlk.usNxtIdx = 0;
    _fmemset (lpDIORes->cbChdBlk.irIdxRec, 0xff, lpDIORes->cbChdBlk.usMemSiz);

    /********************************************************************/
    /*              Initialize callback procedures                      */
    /********************************************************************/
    lpDIORes->fpDevPrc = DigBufOut;
    lpDIORes->dbDIOBlk.usLinNum = usLinNum;
    lpDIORes->dbDIOBlk.usPCMTyp = usPCMTyp;
    lpDIORes->dbDIOBlk.usChnCnt = usChnCnt;
    lpDIORes->dbDIOBlk.ulSmpFrq = ulSmpFrq;
    lpDIORes->dbDIOBlk.fpDIOPrc = fpDIOPrc;
    lpDIORes->dbDIOBlk.ulDIODat = ulDIODat;
    lpDIORes->dbDIOBlk.usBufAct = lpDIORes->dbDIOBlk.usBufCnt;
    lpDIORes->dbDIOBlk.ulPauFsh = 0L;
    lpDIORes->dbDIOBlk.ulPauPos = 0L;

    /********************************************************************/
    /* Load first data block; if 0 samples output, continue             */
    /********************************************************************/
    if (-1L == lpDIORes->fpDevPrc (TMIPOLBEG, &lpDIORes->dbDIOBlk, 
        &lpDIORes->cbChdBlk)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIFSTBLK);    
        DskFilCls (lpDIORes->cbChdBlk.usReaFil, &uiErrCod);
        FilHdlCls (lpDIORes->cbChdBlk.usProFil);
        lpDIORes->cbChdBlk.usReaFil = 0;
        lpDIORes->cbChdBlk.usProFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Write subsequent data blocks; 0 samples written is OK            */
    /* Call poll procedure for time consuming initial PCM               */
    /* Note: Parent insures that re-entrant termination does not occur  */
    /********************************************************************/
    if (fpPolPrc) fpPolPrc (TMIPOLBEG, lpDIORes->dbDIOBlk.usBufCnt, ulPolDat);
    for (usi=1; usi<lpDIORes->dbDIOBlk.usBufCnt; usi++) {
        if (lpDIORes->fpDevPrc (TMIPOLCNT, &lpDIORes->dbDIOBlk, 
            &lpDIORes->cbChdBlk) && fpPolPrc) fpPolPrc (TMIPOLCNT, usi, ulPolDat); 
    }
    if (fpPolPrc) fpPolPrc (TMIPOLEND, usi, ulPolDat);

    /********************************************************************/
    /* Initialize read/write block parameters                           */
    /********************************************************************/
    clrrwb (&lpDIORes->cbChdBlk.drDlgRWB);
    lpDIORes->cbChdBlk.drDlgRWB.filehndl = lpDIORes->cbChdBlk.usReaFil;
    lpDIORes->cbChdBlk.drDlgRWB.indexseg = HIWORD (lpDIORes->cbChdBlk.ulReaMem);
    lpDIORes->cbChdBlk.drDlgRWB.indexoff = LOWORD (lpDIORes->cbChdBlk.ulReaMem);
    lpDIORes->cbChdBlk.drDlgRWB.isxrwb = 1;
    lpDIORes->cbChdBlk.drDlgRWB.dtinit  = lpDIORes->lcLinCfg.sDigIni;
    lpDIORes->cbChdBlk.drDlgRWB.dtterm  = lpDIORes->lcLinCfg.sDigTrm;

    /********************************************************************/
    /* Disconnect input during playback to eliminate feedback           */
    /********************************************************************/
//AMX
//if (lpDIORes->dbDIOBlk.usMpxInp && (lpDIORes->dbDIOBlk.usMpxInp != lpDIORes->dbDIOBlk.usMpxOut))
//    atdisc (lpDIORes->dbDIOBlk.usMpxInp);

    /********************************************************************/
    /* Initialize Timer procedure                                       */
    /********************************************************************/
    lpDIORes->fpTimPrc = NULL;
    if (!SetTimer (lpDIORes->hCBkWnd, DIOTIM_ID, DIOTIMDEF, NULL)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIINSTIM);
        DskFilCls (lpDIORes->cbChdBlk.usReaFil, &uiErrCod);
        FilHdlCls (lpDIORes->cbChdBlk.usProFil);
        lpDIORes->cbChdBlk.usReaFil = 0;
        lpDIORes->cbChdBlk.usProFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    ClrEvtQue (usLinNum);                                   /* Clr Que  */

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (0);

}

WORD FAR PASCAL TMIPlaBeg (VISMEMHDL mhDIORes)
{
    DIORES FAR *lpDIORes;
    unsigned    uiErrCod;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block.                */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Note: Set AGCMod true to eliminate flag                          */
    /********************************************************************/
    if (uiErrCod = xplayf (lpDIORes->dbDIOBlk.usLinNum, 
      PM_NDX | CvtModFlg (lpDIORes->dbDIOBlk.usPCMTyp, TRUE, 
      FALSE, lpDIORes->dbDIOBlk.ulSmpFrq), &lpDIORes->cbChdBlk.drDlgRWB)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBDWIO, uiErrCod);
        GloMemUnL (mhDIORes);
        TMIFilTrm (mhDIORes); 
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Activate timer procedure                                         */
    /********************************************************************/
    lpDIORes->fpTimPrc = TimPrc_IO;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (0);

}

WORD FAR PASCAL TMIFilRec (WORD usLinNum, VISMEMHDL mhDIORes, 
                WORD usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq, 
                LPCSTR szChdFil, TMIDIOPRC fpDIOPrc, DWORD ulDIODat)
{
    DIORES FAR *lpDIORes;
    unsigned    uiErrCod;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize recording transfer file.                              */
    /********************************************************************/
    if (-1 == (lpDIORes->cbChdBlk.usReaFil = DskFilCre ((LPSTR) szChdFil, 
      OF_READWRITE, &uiErrCod))) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIACCCHD);    
        lpDIORes->cbChdBlk.usReaFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize WIM_DATA simulator variables                          */
    /********************************************************************/
    lpDIORes->cbChdBlk.ulPstByt = 0L;
    lpDIORes->cbChdBlk.usCurIdx = 0;
    lpDIORes->cbChdBlk.usNxtIdx = 0;
    _fmemset (lpDIORes->cbChdBlk.irIdxRec, 0xff, lpDIORes->cbChdBlk.usMemSiz);

    /********************************************************************/
    /*              Initialize callback procedures                      */
    /********************************************************************/
    lpDIORes->fpDevPrc = DigBufInp;
    lpDIORes->dbDIOBlk.usLinNum = usLinNum;
    lpDIORes->dbDIOBlk.usPCMTyp = usPCMTyp;
    lpDIORes->dbDIOBlk.usChnCnt = usChnCnt;
    lpDIORes->dbDIOBlk.ulSmpFrq = ulSmpFrq;
    lpDIORes->dbDIOBlk.fpDIOPrc = fpDIOPrc;
    lpDIORes->dbDIOBlk.ulDIODat = ulDIODat;
    lpDIORes->dbDIOBlk.usBufAct = lpDIORes->dbDIOBlk.usBufCnt;
    lpDIORes->dbDIOBlk.ulPauFsh = 0L;
    lpDIORes->dbDIOBlk.ulPauPos = 0L;

    /********************************************************************/
    /* Initialize read/write block parameters                           */
    /********************************************************************/
    clrrwb (&lpDIORes->cbChdBlk.drDlgRWB);
    lpDIORes->cbChdBlk.drDlgRWB.filehndl = lpDIORes->cbChdBlk.usReaFil;
    lpDIORes->cbChdBlk.drDlgRWB.maxsil  = (BYTE) lpDIORes->lcLinCfg.sMaxSil;
    lpDIORes->cbChdBlk.drDlgRWB.maxnsil = (BYTE) lpDIORes->lcLinCfg.sMaxSnd;
    lpDIORes->cbChdBlk.drDlgRWB.isxrwb = 1;
    lpDIORes->cbChdBlk.drDlgRWB.dtinit  = lpDIORes->lcLinCfg.sDigIni;
    lpDIORes->cbChdBlk.drDlgRWB.dtterm  = lpDIORes->lcLinCfg.sDigTrm;

    /********************************************************************/
    /* Initialize recording data unload callback procedure.             */
    /* Note: Although I/O is direct to disk, these calls set the size   */
    /*       of each incoming buffer, which in turn affects the total   */
    /*       recording length for limited length recordings.            */
    /********************************************************************/
    if (-1L == lpDIORes->fpDevPrc (TMIPOLBEG, &lpDIORes->dbDIOBlk, 
        &lpDIORes->cbChdBlk)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIFSTBLK);    
        DskFilCls (lpDIORes->cbChdBlk.usReaFil, &uiErrCod);
        lpDIORes->cbChdBlk.usReaFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Init subsequent data blocks; 0 samples written is OK             */
    /********************************************************************/
    for (usi=1; usi<lpDIORes->dbDIOBlk.usBufCnt; usi++) {
        lpDIORes->fpDevPrc (TMIPOLEMP, &lpDIORes->dbDIOBlk, 
            &lpDIORes->cbChdBlk);
    }

    /********************************************************************/
    /* Initialize Timer procedure                                       */
    /********************************************************************/
    lpDIORes->fpTimPrc = NULL;
    if (!SetTimer (lpDIORes->hCBkWnd, DIOTIM_ID, DIOTIMDEF, NULL)) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIINSTIM);
        DskFilCls (lpDIORes->cbChdBlk.usReaFil, &uiErrCod);
        lpDIORes->cbChdBlk.usReaFil = 0;
        GloMemUnL (mhDIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    ClrEvtQue (usLinNum);                                   /* Clr Que  */

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (0);

}

WORD FAR PASCAL TMIRecBeg (VISMEMHDL mhDIORes)
{
    DIORES FAR *lpDIORes;
    unsigned    uiErrCod;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Begin recording                                                  */
    /********************************************************************/
    if (uiErrCod = recfile (lpDIORes->dbDIOBlk.usLinNum, 
      &lpDIORes->cbChdBlk.drDlgRWB, CvtModFlg (lpDIORes->dbDIOBlk.usPCMTyp, 
      lpDIORes->lcLinCfg.sAGCMod, lpDIORes->lcLinCfg.sSilCmp, 
      lpDIORes->dbDIOBlk.ulSmpFrq))) {
        MsgDspRes (TMIGlo.hLibIns, 0, SI_TMIVBDWIO, uiErrCod);
        GloMemUnL (mhDIORes);
        TMIFilTrm (mhDIORes); 
        return ((WORD) -1);
    }
    
    /********************************************************************/
    /* Activate timer procedure                                         */
    /********************************************************************/
    lpDIORes->fpTimPrc = TimPrc_IO;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (0);

}

DWORD FAR PASCAL TMIRecLvl (VISMEMHDL mhDIORes, LPVOID lpMemBuf, DWORD ulBufSiz)
{
    DIORES FAR *lpDIORes;
    DWORD       ulFilLen;
    WORD        usErrCod;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Check for valid file handle and length                           */
    /********************************************************************/
    if (!lpDIORes->cbChdBlk.usReaFil) {
        GloMemUnL (mhDIORes);
        return (0);
    }
    ulFilLen = DskFilLen (lpDIORes->cbChdBlk.usReaFil, &usErrCod);
    if (!ulFilLen || (-1L == ulFilLen)) {
        GloMemUnL (mhDIORes);
        return (0);
    }

    /********************************************************************/
    /********************************************************************/
    ulBufSiz = min (ulFilLen, (DWORD) ulBufSiz);
    DskFilPos (lpDIORes->cbChdBlk.usReaFil, ulFilLen - ulBufSiz, SEEK_SET, &usErrCod);
    DskFilInp (lpDIORes->cbChdBlk.usReaFil, lpMemBuf, (WORD) ulBufSiz, &usErrCod);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (ulBufSiz);
}

DWORD FAR PASCAL TMIFilPau (VISMEMHDL mhDIORes, WORD usResFlg) 
{
    DIORES FAR *lpDIORes;
    DWORD       ulSmpPos = 0L;

    /********************************************************************/
    /* Get pointer to digitizer I/O resource data block & config.       */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return (ulSmpPos);
    }

    /********************************************************************/
    /* Playback?                                                        */
    /********************************************************************/
    if (DigBufOut == lpDIORes->fpDevPrc) {
        if (usResFlg) {
            TMIResOut (lpDIORes);
            TMIPlaBeg (mhDIORes);
        }
        else {
            DigDevStp (lpDIORes->dbDIOBlk.usLinNum, lpDIORes->hCBkWnd);
            lpDIORes->dbDIOBlk.ulPauPos = DigBytPos (&lpDIORes->dbDIOBlk, FALSE);
        }
        ulSmpPos = DigSmpPos (&lpDIORes->dbDIOBlk);
    }

    /********************************************************************/
    /* Record?                                                          */
    /********************************************************************/
    if (DigBufInp == lpDIORes->fpDevPrc) {
        if (usResFlg) {
            TMIResInp (lpDIORes);
            TMIRecBeg (mhDIORes);
        }
        else {
            DigDevStp (lpDIORes->dbDIOBlk.usLinNum, lpDIORes->hCBkWnd);
            lpDIORes->dbDIOBlk.ulPauPos = DigBytPos (&lpDIORes->dbDIOBlk, FALSE);
        }
        ulSmpPos = DigSmpPos (&lpDIORes->dbDIOBlk);
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (ulSmpPos);

}

DWORD FAR PASCAL TMIFilTrm (VISMEMHDL mhDIORes) 
{
    DIORES FAR *lpDIORes;
    unsigned    uiErrCod;
    DWORD       ulSmpPos;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if (NULL == (lpDIORes = (DIORES FAR *) GloMemLck (mhDIORes))) {
        return (0L);
    }
    KillTimer (lpDIORes->hCBkWnd, DIOTIM_ID);

    /********************************************************************/
    /* Stop I/O, wait for stop completion (critical for rec buf flush)  */
    /********************************************************************/
    DigDevStp (lpDIORes->dbDIOBlk.usLinNum, lpDIORes->hCBkWnd);

    /********************************************************************/
    /* Get last sample position and stop I/O.                           */
    /********************************************************************/
    lpDIORes->dbDIOBlk.ulPauPos = DigBytPos (&lpDIORes->dbDIOBlk, FALSE);
    ulSmpPos = DigSmpPos (&lpDIORes->dbDIOBlk);

    /********************************************************************/
    /* Re-connect input after playback (eliminated feedback)            */
    /********************************************************************/
//AMX
//if (lpDIORes->dbDIOBlk.usMpxInp && (lpDIORes->dbDIOBlk.usMpxInp != lpDIORes->dbDIOBlk.usMpxOut))
//    atconn (lpDIORes->dbDIOBlk.usMpxInp);

    /********************************************************************/
    /* Close cached transfer file                                       */
    /********************************************************************/
    if (lpDIORes->cbChdBlk.usProFil) FilHdlCls (lpDIORes->cbChdBlk.usProFil);
    if (lpDIORes->cbChdBlk.usReaFil) DskFilCls (lpDIORes->cbChdBlk.usReaFil, &uiErrCod);
    lpDIORes->cbChdBlk.usProFil = 0;
    lpDIORes->cbChdBlk.usReaFil = 0;

    /********************************************************************/
    /* Alert callback poll procedure to end of operation                */
    /********************************************************************/
    if (NULL != lpDIORes->dbDIOBlk.fpDIOPrc) lpDIORes->dbDIOBlk.fpDIOPrc
        (TMIPOLEND, NULL, 0L, lpDIORes->dbDIOBlk.usBufAct, ulSmpPos, lpDIORes->dbDIOBlk.ulDIODat);

    /********************************************************************/
    /********************************************************************/
    lpDIORes->dbDIOBlk.usLinNum = 0;
    lpDIORes->dbDIOBlk.fpDIOPrc = NULL;
    lpDIORes->fpDevPrc = NULL;
    lpDIORes->fpTimPrc = NULL;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhDIORes);
    return (ulSmpPos);
}

/************************************************************************/
/************************************************************************/
BOOL FAR PASCAL TimPrc_IO (DIOBLK FAR *lpDIOBlk, CHDBLK FAR *lpChdBlk)
{
    DWORD   ulIdxLen;
    DWORD   ulEndBuf;
    DWORD   ulDigPos;

    /********************************************************************/
    /* Index overflow?                                                  */
    /********************************************************************/
    if (lpChdBlk->usCurIdx >= (IDXARRCNT - 1)) return (FALSE);

    /********************************************************************/
    /* The voice boards do not generate a "buffer done" message.        */
    /* This logic simulates one.                                        */
    /* Note: In future, pass current buffer ptr for real time display   */
    /* Note: ulPstByt is set to zero after pause operation              */
    /********************************************************************/
    ulIdxLen = lpChdBlk->irIdxRec[lpChdBlk->usCurIdx].ulIdxLen;
    ulEndBuf = lpChdBlk->ulPstByt + ulIdxLen;
    ulDigPos = DigBytPos (lpDIOBlk, TRUE);

    /********************************************************************/
    /* It appears that the ulDigPos is a counting number, and may jump  */
    /* to the ulEndBuf prematurely (due to inaccurate board reporting   */
    /* Therefore, load the next buffer when (ulDigPos > ulEndBuf)       */
    /********************************************************************/
    if ((-1L == ulIdxLen) || (ulDigPos <= ulEndBuf) || !lpDIOBlk->usBufAct) {
        lpDIOBlk->fpDIOPrc (TMIPOLPOS, NULL, 0L, lpDIOBlk->usBufAct, 
            DigByttoS (lpDIOBlk->usPCMTyp, lpDIOBlk->ulPauFsh + ulDigPos), 
            lpDIOBlk->ulDIODat);
        return (FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    lpChdBlk->ulPstByt = ulEndBuf;  
    lpChdBlk->usCurIdx++;

    /********************************************************************/
    /* Return TRUE to request call to DigBufOut() or DigBufInp()        */
    /********************************************************************/
    return (TRUE);

}

/************************************************************************/
/************************************************************************/
DWORD FAR PASCAL DigBufOut (TMIPOL usPolReq, DIOBLK FAR *lpDIOBlk, 
                 CHDBLK FAR *lpChdBlk)
{
    #define     INDACTBUF   1
    DWORD       ulXfrSiz;
    WORD        usBufNum = lpChdBlk->usNxtIdx % lpDIOBlk->usBufCnt;
    IDXREC FAR *lpIdxRec = &lpChdBlk->irIdxRec[lpChdBlk->usNxtIdx];
    unsigned    uiErrCod;

    /********************************************************************/
    /* Decrement active buffer count (1 used)                           */  
    /********************************************************************/
    lpDIOBlk->usBufAct--;

    /********************************************************************/
    /********************************************************************/
    if (0 == lpDIOBlk->usLinNum) return ((DWORD) -1L);
    if (NULL == lpDIOBlk->fpDIOPrc) return ((DWORD) -1L);

    /********************************************************************/
    /********************************************************************/
    if (lpChdBlk->usNxtIdx >= (IDXARRCNT - 1)) return ((DWORD) -1L);
    if (-1L == FilSetPos (lpChdBlk->usProFil, lpDIOBlk->ulBufSiz * usBufNum,
        SEEK_SET)) return ((DWORD) -1L);

    /********************************************************************/
    /* Fill memory buffer with PCM data and write to file.              */
    /********************************************************************/
    if (!(ulXfrSiz = lpDIOBlk->fpDIOPrc (usPolReq, lpChdBlk->bbPCMWrk.lpBufMem, 
        lpDIOBlk->ulBufSiz, lpDIOBlk->usBufAct, DigSmpPos (lpDIOBlk),
        lpDIOBlk->ulDIODat))) return (0L);
    if (!(ulXfrSiz = hWrFilFwd (lpChdBlk->usProFil, lpChdBlk->bbPCMWrk.lpBufMem, 
        ulXfrSiz, FIOENCNON, &uiErrCod))) return (0L);

    /********************************************************************/
    /* Update cached file index record with new offset and length       */
    /********************************************************************/
    lpIdxRec->ulIdxOff = lpDIOBlk->ulBufSiz * usBufNum;
    lpIdxRec->ulIdxLen = ulXfrSiz;
    lpChdBlk->usNxtIdx++;

    /********************************************************************/
    /* Call fpDIOPrc until cached file segment is 1/2 full              */
    /* Note: Indicate that at least 1 buffer (current) is active        */
    /********************************************************************/
    while (lpIdxRec->ulIdxLen < (lpDIOBlk->ulBufSiz / 2)) {
      if (!(ulXfrSiz = lpDIOBlk->fpDIOPrc (TMIPOLCNT, lpChdBlk->bbPCMWrk.lpBufMem, 
        lpDIOBlk->ulBufSiz - lpIdxRec->ulIdxLen, lpDIOBlk->usBufAct + INDACTBUF, 
        DigSmpPos (lpDIOBlk), lpDIOBlk->ulDIODat))) break;
      if (!(ulXfrSiz = hWrFilFwd (lpChdBlk->usProFil, lpChdBlk->bbPCMWrk.lpBufMem, 
        ulXfrSiz, FIOENCNON, &uiErrCod))) break;
      lpIdxRec->ulIdxLen += ulXfrSiz;
    }
    
    /********************************************************************/
    /* Increment active buffer count (1 reloaded)                       */  
    /********************************************************************/
    lpDIOBlk->usBufAct++;

    /********************************************************************/
    /********************************************************************/
    return (lpIdxRec->ulIdxLen);

}

DWORD FAR PASCAL DigBufInp (TMIPOL usPolReq, DIOBLK FAR *lpDIOBlk, 
                 CHDBLK FAR *lpChdBlk)
{
    DWORD       ulXfrSiz;
    WORD        usBufNum = lpChdBlk->usNxtIdx % lpDIOBlk->usBufCnt;
    IDXREC FAR *lpIdxRec = &lpChdBlk->irIdxRec[lpChdBlk->usNxtIdx];

    /********************************************************************/
    /* Since the indexed array limits input to some time length, this   */
    /* routine will only use one "buffer" (a file) of very long length  */
    /* This allows all other processing to remain the same as for       */
    /* playback.                                                        */
    /********************************************************************/
    #define     ulBUFSIZ    0x00ffffffL

    /********************************************************************/
    /* Decrement active buffer count (1 used)                           */  
    /********************************************************************/
    lpDIOBlk->usBufAct--;

    /********************************************************************/
    /********************************************************************/
    if (0 == lpDIOBlk->usLinNum) return ((DWORD) -1L);
    if (NULL == lpDIOBlk->fpDIOPrc) return ((DWORD) -1L);

    /********************************************************************/
    /********************************************************************/
    if (lpChdBlk->usNxtIdx >= (IDXARRCNT - 1)) return ((DWORD) -1L);

    /********************************************************************/
    /* Empty PCM data from memory buffer.                               */
    /* Note: Although I/O is direct to disk, these calls set the size   */
    /*       of each incoming buffer, which in turn affects the total   */
    /*       recording length for limited length recordings.            */
    /********************************************************************/
    if (!(ulXfrSiz = lpDIOBlk->fpDIOPrc (usPolReq, NULL, 
        ulBUFSIZ, lpDIOBlk->usBufAct, DigSmpPos (lpDIOBlk),
        lpDIOBlk->ulDIODat))) return (0L);

    /********************************************************************/
    /* Update cached file index record with new offset and length       */
    /********************************************************************/
    lpIdxRec->ulIdxOff = 0L;
    lpIdxRec->ulIdxLen = ulXfrSiz;
    lpChdBlk->usNxtIdx++;

    /********************************************************************/
    /* Increment active buffer count (1 unloaded)                       */  
    /********************************************************************/
    lpDIOBlk->usBufAct++;

    /********************************************************************/
    /********************************************************************/
    return (lpIdxRec->ulIdxLen);

}

/************************************************************************/
/************************************************************************/
void TMIResOut (DIORES FAR *lpDIORes)
{
    IDXREC FAR *lpIdxRec = lpDIORes->cbChdBlk.irIdxRec;
    DWORD       ulZerByt;

    /********************************************************************/
    /* Move through index record and zero bytes played since last pause */
    /* Future: Re-design using memory shift to reset old data           */
    /********************************************************************/
    ulZerByt = lpDIORes->dbDIOBlk.ulPauPos;
    while (-1L != lpIdxRec->ulIdxOff) {
        if (lpIdxRec->ulIdxLen <= ulZerByt) {
            ulZerByt -= lpIdxRec->ulIdxLen;
            lpIdxRec->ulIdxOff = 0L;
            lpIdxRec->ulIdxLen = 0L;
        }    
        else {
            lpIdxRec->ulIdxOff += ulZerByt;
            lpIdxRec->ulIdxLen -= ulZerByt;
            break;
        }
        lpIdxRec++;
    }

    /********************************************************************/
    /* Update flushed bytes and paused position                         */
    /********************************************************************/
    lpDIORes->dbDIOBlk.ulPauFsh += lpDIORes->dbDIOBlk.ulPauPos;
    lpDIORes->dbDIOBlk.ulPauPos  = 0L;
    lpDIORes->cbChdBlk.ulPstByt  = 0L;
    return;
}

void TMIResInp (DIORES FAR *lpDIORes)
{
    lpDIORes->dbDIOBlk.ulPauFsh += lpDIORes->dbDIOBlk.ulPauPos;
    lpDIORes->dbDIOBlk.ulPauPos  = 0L;
    lpDIORes->cbChdBlk.ulPstByt  = 0L;
    return;
}

/************************************************************************/
/*              PCM Type, AGC Mode, Freq Flags Converter                */
/************************************************************************/
WORD    CvtModFlg (PCMTYP usPCMTyp, BOOL bAGCMod, BOOL bSilCmp, long lSmpFrq)
{

    WORD    usDlgFlg = 0;

    /********************************************************************/
    /********************************************************************/
    if (DLGPCM008 == usPCMTyp) usDlgFlg = RM_PCM; 
    else usDlgFlg = RM_ADPCM;

    /********************************************************************/
    /********************************************************************/
    if (labs (lSmpFrq - SMPFRQDEF) < labs (lSmpFrq - SMPFRQHGH)) usDlgFlg |= RM_SR6;
    else usDlgFlg |= RM_SR8;

    /********************************************************************/
    /********************************************************************/
    if (!bAGCMod) usDlgFlg |= RM_NOAGC;

    /********************************************************************/
    /********************************************************************/
    if (bSilCmp) usDlgFlg |= RM_SCOMP;

    /********************************************************************/
    /********************************************************************/
    return (usDlgFlg);

}

DWORD   hWrFilFwd (int iFilHdl, void huge *hpSrcBuf, DWORD ulSrcByt, 
        unsigned int uiEncFmt, unsigned int far *lpErrCod)
{
    DWORD   ulXfrByt = 0L;
    WORD    usInpByt;

    /********************************************************************/
    /********************************************************************/
    while (ulSrcByt > 0L) {
        /****************************************************************/
        /****************************************************************/
        usInpByt = (WORD) min (ulSrcByt, BYTMAXFIO); 
        usInpByt = Wr_FilFwd (iFilHdl, ((BYTE huge *) hpSrcBuf) + ulXfrByt,
            usInpByt, uiEncFmt, lpErrCod);
        if (!usInpByt || (-1 == usInpByt)) break;

        /****************************************************************/
        /****************************************************************/
        ulXfrByt += (DWORD) usInpByt;
        ulSrcByt -= (DWORD) usInpByt;
    }
    return (ulXfrByt);

}

WORD    DigOutWrt (CHDBLK FAR *lpChdBlk, DWORD ulFilPos, BYTE huge *hpSrcBuf, 
        DWORD ulSrcByt)
{
    DWORD       ulXfrByt = 0L;
    WORD        usOutByt;
    WORD        usErrCod;

    /********************************************************************/
    /********************************************************************/
    if (-1L == FilSetPos (lpChdBlk->usProFil, ulFilPos, SEEK_SET))
        return ((WORD) -1);
    if (lpChdBlk->usNxtIdx >= (IDXARRCNT - 1)) return ((WORD) -1);

    /********************************************************************/
    /********************************************************************/
    while (ulSrcByt > 0L) {
        /****************************************************************/
        /****************************************************************/
        usOutByt = (WORD) min (ulSrcByt, BYTMAXFIO); 
        usOutByt = Wr_FilFwd (lpChdBlk->usProFil, 
            (BYTE FAR *) (hpSrcBuf + ulXfrByt),
            usOutByt, FIOENCNON, &usErrCod);
        if (!usOutByt || (-1 == usOutByt)) break;

        /****************************************************************/
        /****************************************************************/
        ulXfrByt += (DWORD) usOutByt;
        ulSrcByt -= (DWORD) usOutByt;

    }
    lpChdBlk->irIdxRec[lpChdBlk->usNxtIdx].ulIdxOff = ulFilPos;
    lpChdBlk->irIdxRec[lpChdBlk->usNxtIdx].ulIdxLen = ulXfrByt;
    lpChdBlk->usNxtIdx++;

    /********************************************************************/
    /********************************************************************/
    return (0);

}

/************************************************************************/
/************************************************************************/
DWORD   DigSmpPos (DIOBLK FAR *lpDIOBlk)
{
    return (DigByttoS (lpDIOBlk->usPCMTyp, 
        lpDIOBlk->ulPauFsh + DigBytPos (lpDIOBlk, TRUE)));
}

DWORD   DigBytPos (DIOBLK FAR *lpDIOBlk, BOOL bfStaChk)
{
    #define BUFDLYCNT   0L
    DWORD   ulDigPos;
    CSB     cbDlgCSB;

    /********************************************************************/
    /********************************************************************/
    if (getcstat (lpDIOBlk->usLinNum, &cbDlgCSB)) return (0L);

    /********************************************************************/
    /* Play or record active?                                           */
    /* Note: ulPauPos insures no initial or race condition errors occur */
    /*       when the device has just paused and ulPauFsh has just been */
    /*       updated.                                                   */
    /********************************************************************/
    if (bfStaChk && ((S_RECORD != cbDlgCSB.status) && (S_PLAY != cbDlgCSB.status)))
        return (lpDIOBlk->ulPauPos);

    /********************************************************************/
    /* Note: Apparently, these boards do not provide very accurate      */
    /*       position information; use slight delay to compensate.      */
    /********************************************************************/
    ulDigPos = MAKELONG (cbDlgCSB.bufcnt, cbDlgCSB.bufcnth);
    ulDigPos = ulDigPos - min (ulDigPos, BUFDLYCNT);

    /********************************************************************/
    /********************************************************************/
    return (ulDigPos);
}

DWORD   DigByttoS (PCMTYP usPCMTyp, DWORD ulBytPos)
{
    /********************************************************************/
    /********************************************************************/
    switch (usPCMTyp) {
        case AVAPCM004: return ((DWORD) (ulBytPos / AVABPS004)); 
        case BKTPCM001: return ((DWORD) (ulBytPos / BKTBPS001)); 
        case CPXPCM064: return ((DWORD) (ulBytPos / CPXBPS064)); 
        case DLGPCM004: return ((DWORD) (ulBytPos / DLGBPS004)); 
        case DLGPCM008: return ((DWORD) (ulBytPos / DLGBPS008)); 
        case FLTPCM032: return ((DWORD) (ulBytPos / FLTBPS032)); 
        case G11PCMF08: return ((DWORD) (ulBytPos / G11BPS008)); 
        case G11PCMI08: return ((DWORD) (ulBytPos / G11BPS008)); 
        case G21PCM004: return ((DWORD) (ulBytPos / G21BPS004)); 
        case G22PCM004: return ((DWORD) (ulBytPos / G22BPS004)); 
        case G23PCM003: return ((DWORD) (ulBytPos / G23BPS003)); 
        case HARPCM001: return ((DWORD) (ulBytPos / HARBPS001)); 
        case MPCPCM008: return ((DWORD) (ulBytPos / MPCBPS008)); 
        case MPCPCM016: return ((DWORD) (ulBytPos / MPCBPS016)); 
        case MSAPCM004: return ((DWORD) (ulBytPos / MSABPS004)); 
        case NWVPCM001: return ((DWORD) (ulBytPos / NWVBPS001)); 
        case PTCPCM001: return ((DWORD) (ulBytPos / PTCBPS001)); 
        case RTXPCM003: return ((DWORD) (ulBytPos / RTXBPS003)); 
        case RTXPCM004: return ((DWORD) (ulBytPos / RTXBPS004)); 
        case TTIPCM008: return ((DWORD) (ulBytPos / TTIBPS008)); 
    }
    return ((DWORD) (ulBytPos / UNKBPS000));

}

/************************************************************************/
/*                      Event Support Routines                          */
/************************************************************************/
void DigDevStp (WORD usLinNum, HWND hCBkWnd)
{
    CSB cbDlgCSB;
    if (getcstat (usLinNum, &cbDlgCSB)) return;
    /********************************************************************/
    /* Device active?                                                   */
    /********************************************************************/
    if (S_STOP != cbDlgCSB.status) {
        ClrEvtQue (usLinNum);
        /****************************************************************/
        /* Note: NewVoice 3.08 (3.02 also?) driver hangs randomly at    */
        /* stopch() during record only!                                 */
        /****************************************************************/
        stopch (usLinNum);
        PolEvtQue (usLinNum, hCBkWnd, WIO_TRM, EVTPOLTIM);
    }
    return;
}

BOOL TstTrmEvt (WORD usTIFEvt, EVTTRM usTstTrm)  
{

    switch (usTIFEvt) {
        case T_STOP:                    /* Rec/play/getdtmf stopped     */
        case T_TIME:                    /* Rec/play/getdtmf timed out   */
        case T_LCTERM:                  /* Term by drop in loop signal  */
        case T_HFAIL:                   /* Hardware failure             */
        case T_DOSERR:                  /* Dos error                    */
        case T_EMSERR:                  /* Terminated by EMS error      */
            return (TRUE);
        case T_RING:                    /* Rings received               */         
            return (RNG_TRM == usTstTrm);           
        case T_ONH:                     /* Onhook complete              */
        case T_OFFH:                    /* Offhook complete             */
            return (OOH_TRM == usTstTrm);
        case T_DFULL:                   /* Disk full                    */
        case T_MAXBYT:                  /* Max bytes on play or rec     */
        case T_EOF:                     /* Eof reached on playback      */
        case T_SIL:                     /* Maximum silence received     */
        case T_NSIL:                    /* Term by a max non-silence    */
            return (WIO_TRM == usTstTrm);
    }

    /********************************************************************/
    /********************************************************************/
    return (NUL_TRM);
}

WORD    ClrEvtQue (WORD usLinNum)
{

    WORD    usDmyDat;
    CSB     cbDlgCSB;                   /* Dialogic CSB (channel stat)  */

    /********************************************************************/
    /* Clear event queue                                                */
    /********************************************************************/
    while (GetLinEvt (usLinNum, &usDmyDat, NULL) != 0);     /* Clr Que  */
    getcstat (usLinNum, &cbDlgCSB);                         /* Clr CSB  */

    /********************************************************************/
    /********************************************************************/
    return (0);

}

EVTTRM PolEvtQue (WORD usLinNum, HWND hMsgWnd, EVTTRM usBrkEvt, DWORD ulTimOut)
{
    DWORD   ulEndTim;
    WORD    usEvtDat;
  
    ulEndTim = (DWORD) GetTickCount() + ulTimOut;       /* 1/1000th Sec */

    /********************************************************************/
    /********************************************************************/
    while (TRUE) {
        MSG msg;
        if (PeekMessage (&msg, hMsgWnd, WM_TIFEVT, WM_TIFEVT, PM_REMOVE) 
          && TstTrmEvt (GetLinEvt (usLinNum, &usEvtDat, NULL), usBrkEvt)) 
            return (usBrkEvt);
        if (GetTickCount () > ulEndTim) break;
    }

    /********************************************************************/
    /********************************************************************/
    return (0);

}

