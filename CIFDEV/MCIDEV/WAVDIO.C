/************************************************************************/
/* Wave Device I/O Support: WavDIO.c                    V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "mmsystem.h"                   /* Windows Multi Media defs     */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */
#include "..\effdev\geneff.h"           /* Sound Effects definitions    */
#include "genmci.h"                     /* Generic MCI definitions      */
#include "mcisup.h"                     /* MCI support definitions      */
#include "mciwav.h"                     /* MCI wave definitions         */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  MCIGLO  MCIGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
WORD  FAR PASCAL WavDevOut (MCIPOL, WIOBLK FAR *, LPWAVEHDR);
WORD  FAR PASCAL WavDevInp (MCIPOL, WIOBLK FAR *, LPWAVEHDR);
BOOL  FAR PASCAL TimPrcOut (WIOBLK FAR *);
BOOL  FAR PASCAL TimPrcInp (WIOBLK FAR *);
DWORD            OutSmpPos (HWAVEOUT, WORD);
DWORD            InpSmpPos (HWAVEIN, WORD);
void             MsgOutErr (WORD, WORD);
void             MsgInpErr (WORD, WORD);

/************************************************************************/
/************************************************************************/
MCIPRO FAR PASCAL WavFilSta (VISMEMHDL mhWIORes, DWORD FAR *pulSmpPos) 
{
    WIORES FAR *lpWIORes;
    MCIPRO      usCtlPro = MCIUNKPRO;
    DWORD       ulSmpPos = 0L;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return (MCIUNKPRO);
    }
    if (NULL == lpWIORes->wbWIOBlk.hWavGIO) {
        GloMemUnL (mhWIORes);
        return (MCIUNKPRO);
    }

    /********************************************************************/
    /* Playback?                                                        */
    /********************************************************************/
    if (WavDevOut == lpWIORes->fpDevPrc) {
        ulSmpPos = OutSmpPos (lpWIORes->wbWIOBlk.hWavOut, lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample);
        usCtlPro = MCIPROOUT;
    }

    /********************************************************************/
    /* Record?                                                          */
    /********************************************************************/
    if (WavDevInp == lpWIORes->fpDevPrc) {
        ulSmpPos = InpSmpPos (lpWIORes->wbWIOBlk.hWavInp, lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample);
        usCtlPro = MCIPROINP;
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);

    /********************************************************************/
    /********************************************************************/
    if (pulSmpPos) *pulSmpPos = ulSmpPos;
    return (usCtlPro);

}

WORD FAR PASCAL WavFilPla (VISMEMHDL mhWIORes, WORD usPCMTyp, WORD usChnCnt,
                DWORD ulSmpFrq, MCIWIOPRC fpWIOPrc, DWORD ulWIODat, 
                MCIPOLPRC fpPolPrc, DWORD ulPolDat) 
{
    WIORES FAR *lpWIORes;
    WORD        usErrCod;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize waveform device PCM format data block                 */
    /* Note: Uses "extended" waveformat structure                       */
    /********************************************************************/
    switch (usPCMTyp) {
        case DLGPCM004:
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_DIALOGIC_OKI_ADPCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 4;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case DLGPCM008: 
        case G11PCMF08: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_MULAW;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case G11PCMI08: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_ALAW;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case MPCPCM008: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            break;
        case MPCPCM016: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 16;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 2;
            break;
        default:
            GloMemUnL (mhWIORes);
            return ((WORD) -1);
    }
    lpWIORes->wbWIOBlk.wfWavFmt.nChannels = usChnCnt;
    lpWIORes->wbWIOBlk.wfWavFmt.nSamplesPerSec = ulSmpFrq;
    lpWIORes->wbWIOBlk.wfWavFmt.nAvgBytesPerSec    
        = lpWIORes->wbWIOBlk.wfWavFmt.nSamplesPerSec 
        * lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample / 8L;

    /********************************************************************/
    /*              Initialize callback procedures                      */
    /********************************************************************/
    lpWIORes->fpDevPrc = WavDevOut;
    lpWIORes->wbWIOBlk.fpWIOPrc = fpWIOPrc;
    lpWIORes->wbWIOBlk.ulWIODat = ulWIODat;
    lpWIORes->wbWIOBlk.usBufAct = lpWIORes->wbWIOBlk.usBufCnt;

    /********************************************************************/
    /* Open a waveform output device.                                   */
    /********************************************************************/
    if (usErrCod = waveOutOpen (&lpWIORes->wbWIOBlk.hWavOut, 
      lpWIORes->wbWIOBlk.usDev_ID, (LPWAVEFORMAT) &lpWIORes->wbWIOBlk.wfWavFmt,
      (UINT) lpWIORes->hCBkWnd, 0L, (DWORD) (CALLBACK_WINDOW | WAVE_ALLOWSYNC))) {
        MsgOutErr (usErrCod, SI_MCIOUTOPN);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Reset and load first data block; if 0 samples output, continue   */
    /********************************************************************/
    waveOutReset (lpWIORes->wbWIOBlk.hWavOut);
    waveOutPause (lpWIORes->wbWIOBlk.hWavOut);
    if (usErrCod = lpWIORes->fpDevPrc (MCIPOLBEG, &lpWIORes->wbWIOBlk, 
      (lpWIORes->bbBufBlk)[0].lpWavHdr)) {
        MsgOutErr (usErrCod, SI_MCIBLKREJ);
        WavFilTrm (mhWIORes);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Write subsequent data blocks; 0 samples written is OK            */
    /* Call poll procedure for time consuming initial PCM               */
    /* Don't report I/O errors for these subsequent block               */
    /********************************************************************/
    if (fpPolPrc) fpPolPrc (MCIPOLBEG, lpWIORes->wbWIOBlk.usBufCnt, ulPolDat);
    for (usi=1; usi<lpWIORes->wbWIOBlk.usBufCnt; usi++) {
        LPWAVEHDR   lpWavHdr = (lpWIORes->bbBufBlk)[usi].lpWavHdr;
        if (!lpWIORes->fpDevPrc (MCIPOLCNT, &lpWIORes->wbWIOBlk, lpWavHdr) 
            && lpWavHdr->dwBufferLength && fpPolPrc) fpPolPrc (MCIPOLCNT, usi, ulPolDat); 
    }
    if (fpPolPrc) fpPolPrc (MCIPOLEND, usi, ulPolDat);

    /********************************************************************/
    /* Initialize Timer procedure                                       */
    /********************************************************************/
    lpWIORes->fpTimPrc = NULL;
    if (!SetTimer (lpWIORes->hCBkWnd, WIOTIM_ID, WIOTIMDEF, NULL)) {
        MsgDspRes (MCIGlo.hLibIns, 0, SI_MCIINSTIM);
        WavFilTrm (mhWIORes);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (0);

}

WORD FAR PASCAL WavPlaBeg (VISMEMHDL mhWIORes)
{
    WIORES FAR *lpWIORes;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Begin playback                                                   */
    /********************************************************************/
    waveOutRestart (lpWIORes->wbWIOBlk.hWavOut);
    
    /********************************************************************/
    /* Activate timer procedure                                         */
    /********************************************************************/
    lpWIORes->fpTimPrc = TimPrcOut;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (0);

}

WORD FAR PASCAL WavFilRec (VISMEMHDL mhWIORes, WORD usPCMTyp, WORD usChnCnt,
                DWORD ulSmpFrq, MCIWIOPRC fpWIOPrc, DWORD ulWIODat)
{
    WIORES FAR *lpWIORes;
    WORD        usErrCod;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Initialize waveform device PCM format data block                 */
    /* Note: Uses "extended" waveformat structure                       */
    /********************************************************************/
    switch (usPCMTyp) {
        case DLGPCM004:
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_DIALOGIC_OKI_ADPCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 4;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case DLGPCM008: 
        case G11PCMF08: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_MULAW;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case G11PCMI08: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_ALAW;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            lpWIORes->wbWIOBlk.wfWavFmt.cbSize = 0;
            break;
        case MPCPCM008: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 8;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 1;
            break;
        case MPCPCM016: 
            lpWIORes->wbWIOBlk.wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample = 16;
            lpWIORes->wbWIOBlk.wfWavFmt.nBlockAlign = 2;
            break;
        default:
            GloMemUnL (mhWIORes);
            return ((WORD) -1);
    }
    lpWIORes->wbWIOBlk.wfWavFmt.nChannels = usChnCnt;
    lpWIORes->wbWIOBlk.wfWavFmt.nSamplesPerSec = ulSmpFrq;
    lpWIORes->wbWIOBlk.wfWavFmt.nAvgBytesPerSec    
        = lpWIORes->wbWIOBlk.wfWavFmt.nSamplesPerSec 
        * lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample / 8L;

    /********************************************************************/
    /*              Initialize callback procedures                      */
    /********************************************************************/
    lpWIORes->fpDevPrc = WavDevInp;
    lpWIORes->wbWIOBlk.fpWIOPrc = fpWIOPrc;
    lpWIORes->wbWIOBlk.ulWIODat = ulWIODat;
    lpWIORes->wbWIOBlk.usBufAct = lpWIORes->wbWIOBlk.usBufCnt;

    /********************************************************************/
    /* Open a waveform input device.                                    */
    /********************************************************************/
    if (usErrCod = waveInOpen (&lpWIORes->wbWIOBlk.hWavInp, 
      lpWIORes->wbWIOBlk.usDev_ID, (LPWAVEFORMAT) &lpWIORes->wbWIOBlk.wfWavFmt,
      (UINT) lpWIORes->hCBkWnd, 0L, (DWORD) (CALLBACK_WINDOW | WAVE_ALLOWSYNC))) {
        MsgInpErr (usErrCod, SI_MCIINPOPN);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Reset and release first empty data block to the wave device.     */
    /********************************************************************/
    waveInReset (lpWIORes->wbWIOBlk.hWavInp);
    waveInStop (lpWIORes->wbWIOBlk.hWavInp);
    if (usErrCod = lpWIORes->fpDevPrc (MCIPOLBEG, &lpWIORes->wbWIOBlk, 
      (lpWIORes->bbBufBlk)[0].lpWavHdr)) {
        MsgInpErr (usErrCod, SI_MCIBLKREJ);
        WavFilTrm (mhWIORes);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Release subsequent data blocks.                                  */
    /* Don't report I/O errors for these subsequent block               */
    /********************************************************************/
    for (usi=1; usi<lpWIORes->wbWIOBlk.usBufCnt; usi++) {
        lpWIORes->fpDevPrc (MCIPOLEMP, &lpWIORes->wbWIOBlk, 
            (lpWIORes->bbBufBlk)[usi].lpWavHdr);
    }

    /********************************************************************/
    /* Initialize Timer procedure                                       */
    /********************************************************************/
    lpWIORes->fpTimPrc = NULL;
    if (!SetTimer (lpWIORes->hCBkWnd, WIOTIM_ID, WIOTIMDEF, NULL)) {
        MsgDspRes (MCIGlo.hLibIns, 0, SI_MCIINSTIM);
        WavFilTrm (mhWIORes);
        GloMemUnL (mhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (0);

}

WORD FAR PASCAL WavRecBeg (VISMEMHDL mhWIORes)
{
    WIORES FAR *lpWIORes;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Begin recording                                                  */
    /********************************************************************/
    waveInStart (lpWIORes->wbWIOBlk.hWavInp);

    /********************************************************************/
    /* Activate timer procedure                                         */
    /********************************************************************/
    lpWIORes->fpTimPrc = TimPrcInp;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (0);

}

DWORD FAR PASCAL WavFilPau (VISMEMHDL mhWIORes, WORD usResFlg) 
{
    WIORES FAR *lpWIORes;
    DWORD       ulSmpPos = 0L;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return (ulSmpPos);
    }
    if (NULL == lpWIORes->wbWIOBlk.hWavGIO) {
        GloMemUnL (mhWIORes);
        return (ulSmpPos);
    }

    /********************************************************************/
    /* Playback?                                                        */
    /********************************************************************/
    if (WavDevOut == lpWIORes->fpDevPrc) {
        usResFlg ? waveOutRestart (lpWIORes->wbWIOBlk.hWavOut) :
            waveOutPause (lpWIORes->wbWIOBlk.hWavOut);
        ulSmpPos = OutSmpPos (lpWIORes->wbWIOBlk.hWavOut, lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample);
    }

    /********************************************************************/
    /* Record?                                                          */
    /********************************************************************/
    if (WavDevInp == lpWIORes->fpDevPrc) {
        usResFlg ? waveInStart (lpWIORes->wbWIOBlk.hWavInp) :
            waveInStop (lpWIORes->wbWIOBlk.hWavInp);
        ulSmpPos = InpSmpPos (lpWIORes->wbWIOBlk.hWavInp, lpWIORes->wbWIOBlk.wfWavFmt.wBitsPerSample);
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (ulSmpPos);
}

DWORD FAR PASCAL WavFilTrm (VISMEMHDL mhWIORes) 
{
    WIORES FAR *lpWIORes;
    WIOBLK FAR *lpWIOBlk;
    DWORD       ulSmpPos = 0L;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to wave I/O resource data block.                     */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (mhWIORes))) {
        return (ulSmpPos);
    }
    lpWIOBlk = &lpWIORes->wbWIOBlk; 

    /********************************************************************/
    /* Check that either an input or output device is available         */
    /********************************************************************/
    if (NULL == lpWIOBlk->hWavGIO) {
        GloMemUnL (mhWIORes);
        return (ulSmpPos);
    }
    KillTimer (lpWIORes->hCBkWnd, WIOTIM_ID);

    /********************************************************************/
    /* Playback?                                                        */
    /********************************************************************/
    if (WavDevOut == lpWIORes->fpDevPrc) {
        /****************************************************************/
        /* Get last sample position and stop I/O.                       */
        /* Note: The sample pos may be slightly less than actual count  */
        /****************************************************************/
        ulSmpPos = OutSmpPos (lpWIOBlk->hWavOut, lpWIOBlk->wfWavFmt.wBitsPerSample);
        waveOutReset (lpWIOBlk->hWavOut);

        /****************************************************************/
        /* Un-prepare headers (if previously prepared)                  */
        /****************************************************************/
        for (usi=0; usi<lpWIOBlk->usBufCnt; usi++) {
            LPWAVEHDR   lpWavHdr = (lpWIORes->bbBufBlk)[usi].lpWavHdr;
            if (lpWavHdr->dwFlags & WHDR_PREPARED) waveOutUnprepareHeader 
                (lpWIOBlk->hWavOut, lpWavHdr, sizeof (WAVEHDR));
        }

        /****************************************************************/
        /* Close waveform device                                        */
        /****************************************************************/
        waveOutClose (lpWIOBlk->hWavOut);      
    }

    /********************************************************************/
    /* Record?                                                          */
    /********************************************************************/
    if (WavDevInp == lpWIORes->fpDevPrc) {
        /****************************************************************/
        /* Get last sample position and stop I/O.                       */
        /* Note: The sample pos may be slightly less than actual count  */
        /****************************************************************/
        ulSmpPos = InpSmpPos (lpWIOBlk->hWavInp, lpWIOBlk->wfWavFmt.wBitsPerSample);
        waveInReset (lpWIOBlk->hWavInp);

        /****************************************************************/
        /* Flush any remaining buffers from message queue               */    
        /****************************************************************/
        for (usi=0; usi<lpWIOBlk->usBufCnt; usi++) {
            LPWAVEHDR   lpWavHdr = (lpWIORes->bbBufBlk)[usi].lpWavHdr;
            /************************************************************/
            /* Un-prepare headers (if previously prepared)              */
            /************************************************************/
            if (lpWavHdr->dwFlags & WHDR_PREPARED) {
                waveInUnprepareHeader (lpWIOBlk->hWavInp, lpWavHdr, sizeof (WAVEHDR));
                /********************************************************/
                /* Empty PCM data from memory buffer.                   */
                /* Warning: If more than one buffer remains, order      */
                /*          could be scrambled! Fix: Use larger buffers */
                /*          or read MM_WIM_DATA messages from queue.    */
                /********************************************************/
                if (NULL != lpWIOBlk->fpWIOPrc) lpWIOBlk->fpWIOPrc (MCIPOLCNT, 
                    lpWavHdr->lpData, lpWavHdr->dwBytesRecorded, 
                    lpWIOBlk->usBufAct, ulSmpPos, lpWIOBlk->ulWIODat);
            }
        }

        /****************************************************************/
        /* Close waveform device                                        */
        /****************************************************************/
        waveInClose (lpWIOBlk->hWavInp);      
    }

    /********************************************************************/
    /* Alert callback poll procedure to end of operation                */
    /********************************************************************/
    if (NULL != lpWIOBlk->fpWIOPrc) lpWIOBlk->fpWIOPrc
        (MCIPOLEND, NULL, 0L, lpWIOBlk->usBufAct, ulSmpPos, 
        lpWIOBlk->ulWIODat);

    /****************************************************************/
    /****************************************************************/
    lpWIOBlk->fpWIOPrc = NULL;
    lpWIOBlk->hWavGIO = NULL;      
    lpWIORes->fpDevPrc = NULL;
    lpWIORes->fpTimPrc = NULL;

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhWIORes);
    return (ulSmpPos);
}

/************************************************************************/
/************************************************************************/
BOOL FAR PASCAL TimPrcOut (WIOBLK FAR *lpWIOBlk)
{
    /********************************************************************/
    /* Note: In future, pass current buffer ptr for real time display   */
    /********************************************************************/
    lpWIOBlk->fpWIOPrc (MCIPOLPOS, NULL, 0L, lpWIOBlk->usBufAct, 
        OutSmpPos (lpWIOBlk->hWavOut, lpWIOBlk->wfWavFmt.wBitsPerSample), 
        lpWIOBlk->ulWIODat);

    /********************************************************************/
    /* Return TRUE to request call to WavDevOut()                       */
    /********************************************************************/
    return (TRUE);

}

BOOL FAR PASCAL TimPrcInp (WIOBLK FAR *lpWIOBlk)
{
    /********************************************************************/
    /* Note: In future, pass current buffer ptr for real time display   */
    /********************************************************************/
    lpWIOBlk->fpWIOPrc (MCIPOLPOS, NULL, 0L, lpWIOBlk->usBufAct, 
        InpSmpPos (lpWIOBlk->hWavInp, lpWIOBlk->wfWavFmt.wBitsPerSample), 
        lpWIOBlk->ulWIODat);

    /********************************************************************/
    /* Return TRUE to request call to WavDevInp()                       */
    /********************************************************************/
    return (TRUE);

}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL WavDevOut (MCIPOL usPolReq, WIOBLK FAR *lpWIOBlk, LPWAVEHDR lpWavHdr) 
{
    WORD    usErrCod;

    /********************************************************************/
    /* Decrement active buffer count (1 used)                           */  
    /********************************************************************/
    lpWIOBlk->usBufAct--;

    /********************************************************************/
    /********************************************************************/
    if ((HWAVEOUT) NULL == lpWIOBlk->hWavOut) return (MMSYSERR_INVALHANDLE);
    if (NULL == lpWIOBlk->fpWIOPrc) return (MMSYSERR_INVALPARAM);

    /********************************************************************/
    /* Un-prepare header (if previously prepared)                       */
    /********************************************************************/
    if (lpWavHdr->dwFlags & WHDR_PREPARED)
        waveOutUnprepareHeader (lpWIOBlk->hWavOut, lpWavHdr, sizeof (WAVEHDR));

    /********************************************************************/
    /* Fill memory buffer with PCM data.                                */
    /********************************************************************/
    lpWavHdr->dwBufferLength = lpWIOBlk->fpWIOPrc (usPolReq, 
        lpWavHdr->lpData, lpWIOBlk->ulBufSiz, lpWIOBlk->usBufAct, 
        OutSmpPos (lpWIOBlk->hWavOut, lpWIOBlk->wfWavFmt.wBitsPerSample), 
        lpWIOBlk->ulWIODat);
    if (!lpWavHdr->dwBufferLength) return (0);

    /********************************************************************/
    /* Prepare header:                                                  */
    /* 1) Verify valid memory & data buffer memory block pointers       */
    /* 2) DPMI page lock the header and data buffer.                    */
    /********************************************************************/
    if (usErrCod = waveOutPrepareHeader (lpWIOBlk->hWavOut, lpWavHdr, 
        sizeof (WAVEHDR))) return (usErrCod);

    /********************************************************************/
    /* Send data block to the wave device.                              */
    /********************************************************************/
    if (usErrCod = waveOutWrite (lpWIOBlk->hWavOut, lpWavHdr, 
        sizeof (WAVEHDR))) return (usErrCod);

    /********************************************************************/
    /* Increment active buffer count (1 reloaded)                       */  
    /********************************************************************/
    lpWIOBlk->usBufAct++;

    /********************************************************************/
    /********************************************************************/
    return (0L);

}

WORD FAR PASCAL WavDevInp (MCIPOL usPolReq, WIOBLK FAR *lpWIOBlk, LPWAVEHDR lpWavHdr) 
{
    WORD    usErrCod;

    /********************************************************************/
    /* Decrement active buffer count (1 used)                           */  
    /********************************************************************/
    lpWIOBlk->usBufAct--;

    /********************************************************************/
    /********************************************************************/
    if ((HWAVEIN) NULL == lpWIOBlk->hWavInp) return (MMSYSERR_INVALHANDLE);
    if (NULL == lpWIOBlk->fpWIOPrc) return (MMSYSERR_INVALPARAM);

    /********************************************************************/
    /* Un-prepare header (if previously prepared)                       */
    /********************************************************************/
    if (lpWavHdr->dwFlags & WHDR_PREPARED)
        waveInUnprepareHeader (lpWIOBlk->hWavInp, lpWavHdr, sizeof (WAVEHDR));

    /********************************************************************/
    /* Empty PCM data from memory buffer.                               */
    /********************************************************************/
    if ((MCIPOLBEG == usPolReq) || (MCIPOLEMP == usPolReq)) 
        lpWavHdr->dwBytesRecorded = lpWIOBlk->ulBufSiz; 
    lpWavHdr->dwBufferLength = lpWIOBlk->fpWIOPrc (usPolReq, lpWavHdr->lpData, 
        lpWavHdr->dwBytesRecorded, lpWIOBlk->usBufAct, 
        InpSmpPos (lpWIOBlk->hWavInp, lpWIOBlk->wfWavFmt.wBitsPerSample), 
        lpWIOBlk->ulWIODat);
    if (!lpWavHdr->dwBufferLength) return (0);

    /********************************************************************/
    /* Prepare header:                                                  */
    /* 1) Verify valid memory & data buffer memory block pointers       */
    /* 2) DPMI page lock the header and data buffer.                    */
    /********************************************************************/
    if (usErrCod = waveInPrepareHeader (lpWIOBlk->hWavInp, lpWavHdr, 
        sizeof (WAVEHDR))) return (usErrCod);

    /********************************************************************/
    /* Send data block to the wave device.                              */
    /********************************************************************/
    if (usErrCod = waveInAddBuffer (lpWIOBlk->hWavInp, lpWavHdr, 
        sizeof (WAVEHDR))) return (usErrCod);

    /********************************************************************/
    /* Increment active buffer count (1 reloaded)                       */  
    /********************************************************************/
    lpWIOBlk->usBufAct++;

    /********************************************************************/
    /********************************************************************/
    return (0L);

}

/************************************************************************/
/************************************************************************/
DWORD   OutSmpPos (HWAVEOUT hWavOut, WORD usBitLen)
{
    MMTIME  mmTimPos;

    /********************************************************************/
    /* Use samples for preferred format                                 */
    /********************************************************************/
    mmTimPos.wType = TIME_SAMPLES;
    waveOutGetPosition (hWavOut, &mmTimPos, sizeof (mmTimPos));

    /********************************************************************/
    /* SoundBlaster does not return position in TIME_SAMPLES            */
    /********************************************************************/
    if (TIME_SAMPLES == mmTimPos.wType) return (mmTimPos.u.sample);
    if (TIME_BYTES   == mmTimPos.wType) {
        if (!usBitLen) return (0L);
        return ((mmTimPos.u.sample * 8L) / (DWORD) usBitLen);
    }
    return (0L);
    
}

DWORD   InpSmpPos (HWAVEIN hWavInp, WORD usBitLen)
{
    MMTIME  mmTimPos;

    /********************************************************************/
    /* Use samples for preferred format                                 */
    /********************************************************************/
    mmTimPos.wType = TIME_SAMPLES;
    waveInGetPosition (hWavInp, &mmTimPos, sizeof (mmTimPos));

    /********************************************************************/
    /* SoundBlaster does not return position in TIME_SAMPLES            */
    /********************************************************************/
    if (TIME_SAMPLES == mmTimPos.wType) return (mmTimPos.u.sample);
    if (TIME_BYTES   == mmTimPos.wType) {
        if (!usBitLen) return (0L);
        return ((mmTimPos.u.sample * 8L) / (DWORD) usBitLen);
    }
    return (0L);
    
}

/************************************************************************/
/************************************************************************/
void    MsgOutErr (WORD usErrCod, WORD usDefMsg)
{
    char    szErrMsg[MAXERRORLENGTH];
    /********************************************************************/
    /* Display the MCI error messageif available; else use default msg  */
    /********************************************************************/
    if (!waveOutGetErrorText (usErrCod, szErrMsg, MAXERRORLENGTH)) MsgDspUsr (szErrMsg);
    else MsgDspRes (MCIGlo.hLibIns, 0, usDefMsg);    
}

void    MsgInpErr (WORD usErrCod, WORD usDefMsg)
{
    char    szErrMsg[MAXERRORLENGTH];
    /********************************************************************/
    /* Display the MCI error messageif available; else use default msg  */
    /********************************************************************/
    if (!waveInGetErrorText (usErrCod, szErrMsg, MAXERRORLENGTH)) MsgDspUsr (szErrMsg);
    else MsgDspRes (MCIGlo.hLibIns, 0, usDefMsg);    
}
