/************************************************************************/
/* File I/O Master File Support: FIOMas.c               V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "fiomsg.h"                     /* File I/O support error defs  */

#include "vbsfil.h"                     /* VBase file format defs       */
#include "wavfil.h"                     /* Wave file (DOS) definitions  */
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
FIORET  FAR PASCAL  FIOMasLod (LPOFSTRUCT_V pofMasFil, MASINF FAR *pmiMasInf,
                    FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod = FIORETERR;
    HMMIO       hFilHdl;
    VBSHDR FAR *lpVBSHdr;
    ITCBLK FAR *pibITCBlk;
    MMCKINFO    ciChkInf;

    /********************************************************************/
    /* Note: Master information block is initialized by caller!         */
    /********************************************************************/
                                                                        
    /********************************************************************/
    /* Indicate Load / Update OFS for subsequent Work File, etc, calls  */    
    /********************************************************************/
    pmiMasInf->ofLodUpd = *pofMasFil;    

    /********************************************************************/
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            /************************************************************/
			/* Enforce some defaults									*/
            /************************************************************/
            frRetCod = FIORETSUC;
            break;

        case VBSIDXFMT:
            /************************************************************/
            /* New indexed file: Ask user for index count               */
            /************************************************************/
            if (!_fstrlen (pofMasFil->szPathName)) {
                WORD    usIdxCnt;
                if (!(usIdxCnt = VBSCntAsk ())) {
                    frRetCod = FIORETCAN;
                    break;
                }
                frRetCod = VBSHdrIni (NULL, &pmiMasInf->mhHdrMem, 
                    &pmiMasInf->mhIdxMem, usIdxCnt, pmiMasInf->ulSmpFrq);
            }
            else {
                /********************************************************/
                /* Existing indexed file: Duplicate header & index      */
                /********************************************************/
                if (VBSHdrLod (pofMasFil, &pmiMasInf->mhHdrMem, &pmiMasInf->mhIdxMem)) {
                    MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);
                    break;
                }
            }
            /************************************************************/
            /* Read back header info                                    */
            /************************************************************/
            if (NULL == (lpVBSHdr = GloMemLck (pmiMasInf->mhHdrMem))) break;
            pmiMasInf->ulSmpFrq = lpVBSHdr->ulSmpFrq;
            GloMemUnL (pmiMasInf->mhHdrMem); 
            frRetCod = FIORETSUC;
            break;

        case WAVHDRFMT:
            /************************************************************/
            /* Exit if new file                                         */
            /************************************************************/
            if (!_fstrlen (pofMasFil->szPathName)) {
                frRetCod = FIORETSUC;
                break;
            }        
            /************************************************************/
            /* Read wave header                                         */
            /************************************************************/
            hFilHdl = mmioOpen_V (pofMasFil->szPathName, NULL, MMIO_READ);
            if (hFilHdl == NULL) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOPNSRC);
                break;
            }
            if (WIOFndNxt (hFilHdl, &pmiMasInf->usPCMTyp, &pmiMasInf->mhHdrMem, 
              &ciChkInf)) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);
                mmioClose (hFilHdl, 0);
                break;
            }
            mmioClose (hFilHdl, 0);

            if (UNKPCM000 == pmiMasInf->usPCMTyp) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_INVPCMFMT);
                break;
            }
            if (NULL == (pibITCBlk = GloMemLck (pmiMasInf->mhHdrMem))) break;
            pmiMasInf->usChnCnt = pibITCBlk->mwMSW.afWEX.wfx.nChannels;
            pmiMasInf->ulSmpFrq = pibITCBlk->mwMSW.afWEX.wfx.nSamplesPerSec;
            GloMemUnL (pmiMasInf->mhHdrMem);
            frRetCod = FIORETSUC;
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

DWORD   FAR PASCAL  FIOMasQry (MASINF FAR *pmiMasInf, WORD usReqTyp, 
                    LPVOID lpPrm001, DWORD ulPrm002)
{
    ITCBLK FAR *pibSrcITC;
    ITCBLK FAR *pibDstITC;

    /********************************************************************/
    /********************************************************************/
    if (NULL == pmiMasInf) return (SI_INVFILFMT);
    if (MASITCQRY != usReqTyp) return (SI_INVFILFMT);
    if (WAVHDRFMT != pmiMasInf->ffFilFmt) return (FIORETSUC);
    if (NULL == (pibDstITC = (ITCBLK FAR *) lpPrm001)) return (SI_INVFILFMT);

    /********************************************************************/
    /* Retrieve the stored ITC Block for Wave files                     */
    /********************************************************************/
    if (NULL == (pibSrcITC = GloMemLck (pmiMasInf->mhHdrMem))) return (SI_INVFILFMT);
    _fmemcpy (pibDstITC, pibSrcITC, (WORD) min (sizeof (*pibSrcITC), ulPrm002));

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (pmiMasInf->mhHdrMem);
    return (FIORETSUC);
}

FIORET  FAR PASCAL  FIOMasUpd (LPOFSTRUCT_V pofDstFil, MASINF FAR *pmiMasInf, 
                    FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod = FIORETERR;
    MMCKINFO    ciChkInf;
    HMMIO       hSrcHdl;
    HMMIO       hDstHdl;

    /********************************************************************/
    /* Update contents of work file                                     */
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master                            */
            /************************************************************/
            frRetCod = FIOOFSDup (&pmiMasInf->ofLodUpd, pofDstFil, 
                fpLngPolPrc, ulPolDat);
            break;

        case VBSIDXFMT:
            /************************************************************/
			/* Re-write header, index, audio and text					*/
            /************************************************************/
            frRetCod = VBSFilWrt (&pmiMasInf->ofLodUpd, pofDstFil, 
                pmiMasInf->mhHdrMem, pmiMasInf->mhIdxMem, fpLngPolPrc, ulPolDat);
            break;

        case WAVHDRFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master (sans header)              */
            /************************************************************/
            hSrcHdl = mmioOpen_V (pmiMasInf->ofLodUpd.szPathName, NULL, MMIO_READ);
            if (hSrcHdl == NULL) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOPNSRC);
                break;
            }

            /************************************************************/
            /* Open and truncate destination                            */
            /************************************************************/
            hDstHdl = mmioOpen_V (pofDstFil->szPathName, NULL, MMIO_WRITE | MMIO_CREATE);
            if (hDstHdl == NULL) {
                mmioClose (hSrcHdl, 0);
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOPNDST);
                break;
            }
            if (WIOOutIni (hDstHdl, pmiMasInf->usPCMTyp, pmiMasInf->usChnCnt,
              pmiMasInf->ulSmpFrq, &pmiMasInf->mhHdrMem, &ciChkInf)) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);
                mmioClose (hSrcHdl, 0);
                mmioClose (hDstHdl, 0);
                break;
            }
            if (-1L == WIOFilCop (hSrcHdl, hDstHdl, (DWORD) -1L, fpLngPolPrc, 
              ulPolDat)) {
                // Displays message in WIOFilCop
                mmioClose (hSrcHdl, 0);
                mmioClose (hDstHdl, 0);
                break;
            }
            if (WIOOutEnd (hDstHdl, &pmiMasInf->mhHdrMem, &ciChkInf)) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);
                mmioClose (hSrcHdl, 0);
                mmioClose (hDstHdl, 0);
                break;
            }
            mmioClose (hSrcHdl, 0);
            mmioClose (hDstHdl, 0);
            frRetCod = FIORETSUC;
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

FIORET  FAR PASCAL  FIOMasRel (MASINF FAR *pmiMasInf)
{

    /********************************************************************/
    /* Release memory blocks                                            */
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case VBSIDXFMT:
            VBSHdrRel (&pmiMasInf->mhHdrMem, &pmiMasInf->mhIdxMem);
            break;

        case WAVHDRFMT:
            pmiMasInf->mhHdrMem = GloUnLRel (pmiMasInf->mhHdrMem);
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}



