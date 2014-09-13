/************************************************************************/
/* File I/O Work Segment Support: FIOSeg.c              V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\os_dev\dllsup.h"           /* Windows DLL support defs     */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */

#include "vbsfil.h"                     /* VBase file format defs       */
#include "wavfil.h"                     /* Wave file (DOS) definitions  */

#include <string.h>                     /* String manipulation funcs    */
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/*                      Forward References                              */
/************************************************************************/
FIORET  VBSSegSel (LPOFSTRUCT_V, MASINF FAR *, SEGQRY, IDXSEG FAR *);
FIORET  VBSSegCre (MASINF FAR *, IDXSEG FAR *, IDXSEG FAR *); 
FIORET  VBSSegDel (MASINF FAR *, IDXSEG FAR *, IDXSEG FAR *); 
float   FIOBypSmp (enum _PCMTYP, WORD);

/************************************************************************/
/************************************************************************/
FIORET  FAR PASCAL  FIOSegSel (SEGQRY usSegQry, MASINF FAR *pmiMasInf,
                    const SEGINF FAR *psiCurSeg, SEGINF FAR *psiSegInf)
{
    FIORET      frRetCod = FIORETERR;  
    VISMEMHDL   mhTmpHdl;
    MMCKINFO    ciChkInf;
    HMMIO       hFilHdl;

    /********************************************************************/
    /* Use previous selection info to prompt user (if available)        */
    /********************************************************************/
    if (NULL == psiCurSeg) _fmemset (psiSegInf, 0, sizeof (*psiSegInf));
    else *psiSegInf = *psiCurSeg;

    /********************************************************************/
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master, WrkFil is inactive        */
            /************************************************************/
            psiSegInf->rsPurSeg.ulAudOff = 0L;
            psiSegInf->rsPurSeg.ulAudLen = FIOOFSLen (&pmiMasInf->ofLodUpd);
            frRetCod = FIORETSUC;
            break;

        case VBSIDXFMT:
            /************************************************************/
            /* Ask user for / jump to vox and text index                */
            /************************************************************/
            frRetCod = VBSSegSel (&pmiMasInf->ofLodUpd, pmiMasInf, usSegQry, &psiSegInf->isIdxSeg);
            break;

        case WAVHDRFMT:
            /************************************************************/
            /************************************************************/
            if (!_fstrlen (pmiMasInf->ofLodUpd.szPathName)) {
                frRetCod = FIORETSUC;
                break;
            }
            /************************************************************/
            /* Read wave header                                         */
            /************************************************************/
            hFilHdl = mmioOpen_V (pmiMasInf->ofLodUpd.szPathName, NULL, MMIO_READ);
            if (hFilHdl == NULL) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOPNSRC);
                break;
            }
            if (WIOFndNxt (hFilHdl, &pmiMasInf->usPCMTyp, &mhTmpHdl, &ciChkInf)) {
                MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);
                mmioClose (hFilHdl, 0);
                break;
            }
            mmioClose (hFilHdl, 0);
            /************************************************************/
            /* SnpFil is dup of Master (sans header), WrkFil inactive   */
            /************************************************************/
            psiSegInf->wsWavSeg.ulAudOff = ciChkInf.dwDataOffset;
            psiSegInf->wsWavSeg.ulAudLen = ciChkInf.cksize;
            frRetCod = FIORETSUC;
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

FIORET  FAR PASCAL  FIOSegDes (SEGQRY usSegQry, MASINF FAR *pmiMasInf, 
                    const SEGINF FAR *psiSegInf, LPVOID lpReqDat, DWORD ulReqSiz)
{
    #define LTAMAXLEN   101             /* itoa/ltoa max string length  */
    char    szWrkBuf[LTAMAXLEN];

    /********************************************************************/
    /********************************************************************/
    switch (usSegQry) {
        /****************************************************************/
        /* Segment byte offset                                          */
        /****************************************************************/
        case SEGOFFQRY:
            if (ulReqSiz != sizeof (DWORD)) return (FIORETERR);
            if (ALLPURFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) = 
                psiSegInf->rsPurSeg.ulAudOff;
            if (VBSIDXFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) = 
                psiSegInf->isIdxSeg.ulVoxOff;
            if (WAVHDRFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) = 
                psiSegInf->wsWavSeg.ulAudOff;
            return (FIORETSUC);
        /****************************************************************/
        /* Segment byte length                                          */
        /****************************************************************/
        case SEGLENQRY:
            if (ulReqSiz != sizeof (DWORD)) return (FIORETERR);
            if (ALLPURFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) =
                FIOOFSLen (&pmiMasInf->ofLodUpd);
            if (VBSIDXFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) =
                psiSegInf->isIdxSeg.ulVoxLen;
            if (WAVHDRFMT == pmiMasInf->ffFilFmt) (*(DWORD FAR *)lpReqDat) = 
                psiSegInf->wsWavSeg.ulAudLen;
            return (FIORETSUC);
        /****************************************************************/
        /* Index number as string (if segmented file)                   */
        /****************************************************************/
        case SEGNUMQRY:
            if (!ulReqSiz) return (FIORETERR);
            if ((VBSIDXFMT == pmiMasInf->ffFilFmt) && (psiSegInf->isIdxSeg.usIdxNum)) {  
                _fitoa (psiSegInf->isIdxSeg.usIdxNum, szWrkBuf, 10);
                _fstrncpy (lpReqDat, szWrkBuf, (WORD) ulReqSiz);
            } else *((LPSTR)lpReqDat) = '\0';    
            return (FIORETSUC);
    }

    /********************************************************************/
    /********************************************************************/
    return (FIORETERR);
}

FIORET  FAR PASCAL  FIOSegCre (MASINF FAR *pmiMasInf, SEGINF FAR *psiCurSeg, 
                    SEGINF FAR *psiCreSeg)
{
    FIORET  frRetCod = FIORETERR;

    /********************************************************************/
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            break;
        case VBSIDXFMT:
            frRetCod = VBSSegCre (pmiMasInf, &psiCurSeg->isIdxSeg,
                &psiCreSeg->isIdxSeg);
            break;
        case WAVHDRFMT:
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

FIORET  FAR PASCAL  FIOSegDel (MASINF FAR *pmiMasInf, SEGINF FAR *psiCurSeg, 
                    SEGINF FAR *psiDelSeg)
{
    FIORET  frRetCod = FIORETERR;

    /********************************************************************/
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            break;
        case VBSIDXFMT:
            frRetCod = VBSSegDel (pmiMasInf, &psiCurSeg->isIdxSeg,
                &psiDelSeg->isIdxSeg);
            break;
        case WAVHDRFMT:
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

/************************************************************************/
/*              Indexed file local support functions                    */
/************************************************************************/
FIORET  VBSSegSel (LPOFSTRUCT_V pofWrkFil, MASINF FAR *pmiMasInf, 
        SEGQRY usSegQry, IDXSEG FAR *pisIdxSeg)
{
    WORD    usTtlSID = 0;
    short   sIdxOff = 0;

    /********************************************************************/
    /* Parse request; Simulate "Jump To" as delta off index zero        */
    /********************************************************************/
    switch (usSegQry) {
        case SEGNULQRY: return (FIORETSUC);
        case SEGJMPQRY: sIdxOff  = pisIdxSeg->usIdxNum; 
                                   pisIdxSeg->usIdxNum = 0;
                                   break;
        case SEGSELQRY: usTtlSID = SI_IDXSELNEW;        break;
        case SEGCREQRY: usTtlSID = SI_IDXCREBFR;        break;
        case SEGDELQRY: usTtlSID = SI_IDXSELDEL;        break;
        case SEGFSTQRY: sIdxOff  = 0x8000;              break;
        case SEGLSTQRY: sIdxOff  = 0x7fff;              break;
        case SEGPRVQRY: sIdxOff  = -1;                  break;
        case SEGNXTQRY: sIdxOff  = +1;                  break;
        default: return (FIORETERR);
    }

    /********************************************************************/
    /* Ask user for vox and text index                                  */
    /********************************************************************/
    if (usTtlSID) return (VBSIdxAsk (usTtlSID, pofWrkFil, 
        FIOBypSmp (pmiMasInf->usPCMTyp, pmiMasInf->usChnCnt), 
        pmiMasInf->mhHdrMem, pmiMasInf->mhIdxMem, pisIdxSeg));

    /********************************************************************/
    /* Jump to vox and text index                                       */
    /********************************************************************/
    return (VBSIdxJmp (sIdxOff, pofWrkFil, pmiMasInf->mhHdrMem, 
        pmiMasInf->mhIdxMem, pisIdxSeg));

}

FIORET  VBSSegCre (MASINF FAR *pmiMasInf, IDXSEG FAR *pisPrvSeg, 
        IDXSEG FAR *pisCreSeg) 
{
    FIORET      frRetCod = FIORETERR;

    /********************************************************************/
    /* Shift memory to create new index before specified one            */
    /********************************************************************/
    if (frRetCod = VBSIdxShf (pmiMasInf->mhHdrMem, &pmiMasInf->mhIdxMem,
        pisCreSeg->usIdxNum, +1, +1)) return (frRetCod);

    /********************************************************************/
    /* Update current index number                                      */
    /********************************************************************/
    if (pisPrvSeg->usIdxNum >= pisCreSeg->usIdxNum) pisPrvSeg->usIdxNum++;

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);

}

FIORET  VBSSegDel (MASINF FAR *pmiMasInf, IDXSEG FAR *pisPrvSeg, 
        IDXSEG FAR *pisDelSeg) 
{
    FIORET      frRetCod = FIORETERR;

    /********************************************************************/
    /* Insure that the current index is not the one to be deleted       */
    /********************************************************************/
    if (pisPrvSeg->usIdxNum == pisDelSeg->usIdxNum) return (FIORETERR);

    /********************************************************************/
    /* Shift memory to delete selected index                            */
    /********************************************************************/
    if (frRetCod = VBSIdxShf (pmiMasInf->mhHdrMem, &pmiMasInf->mhIdxMem,
        pisDelSeg->usIdxNum +1, +1, -1)) return (frRetCod);

    /********************************************************************/
    /* Update current index number                                      */
    /********************************************************************/
    if (pisPrvSeg->usIdxNum >= pisDelSeg->usIdxNum) pisPrvSeg->usIdxNum--;

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);

}

/************************************************************************/
/*                      PCM size / length local support                 */
/************************************************************************/
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */
#include "..\pcmdev\pcmsup.h"           /* PCM/APCM xlate lib defs      */

float   FIOBypSmp (PCMTYP usPCMTyp, WORD usChnCnt)
{
    /********************************************************************/
    /********************************************************************/
    switch (usPCMTyp) {
        case AVAPCM004: return (AVABPS004); 
        case BKTPCM001: return (BKTBPS001); 
        case CPXPCM064: return (CPXBPS064); 
        case DLGPCM004: return (DLGBPS004); 
        case DLGPCM008: return (DLGBPS008); 
        case FLTPCM032: return (FLTBPS032); 
        case G11PCMF08: return (G11BPS008); 
        case G11PCMI08: return (G11BPS008); 
        case G21PCM004: return (G21BPS004); 
        case G22PCM004: return (G22BPS004); 
        case G23PCM003: return (G23BPS003); 
        case HARPCM001: return (HARBPS001); 
        case MPCPCM008: return (MPCBPS008); 
        case MPCPCM016: return (MPCBPS016); 
        case MSAPCM004: return (MSABPS004); 
        case NWVPCM001: return (NWVBPS001); 
        case PTCPCM001: return (PTCBPS001); 
        case RTXPCM003: return (RTXBPS003); 
        case RTXPCM004: return (RTXBPS004); 
        case TTIPCM008: return (TTIBPS008); 
    }
    return (UNKBPS000);

}

