/************************************************************************/
/* File I/O Snippet File Support: FIOSnp.c              V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */

#include "vbsfil.h"                     /* VBase file format defs       */
#include "wavfil.h"                     /* Wave file (DOS) definitions  */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/************************************************************************/
FIORET  FAR PASCAL  FIOSnpLod (LPOFSTRUCT_V pofSnpFil, MASINF FAR *pmiMasInf, 
                    SEGINF FAR *psiSegInf, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod = FIORETERR;

    /********************************************************************/
    /* Load snippet file based upon master file type                    */
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master                            */
            /* Exit if new file                                         */
            /************************************************************/
            if (!_fstrlen (pmiMasInf->ofLodUpd.szPathName)) frRetCod = FIORETSUC;
            else frRetCod = FIOOFSDup (&pmiMasInf->ofLodUpd, pofSnpFil, fpLngPolPrc, ulPolDat);

            /************************************************************/
            /* Indicate Load / Update OFS for subsequent calls          */    
            /************************************************************/
            if (FIORETSUC == frRetCod) pmiMasInf->ofLodUpd = *pofSnpFil;    
            break;

        case VBSIDXFMT:
            /************************************************************/
            /* Load vox portion of indexed file                         */
            /************************************************************/
            frRetCod = VBSVoxLod (&pmiMasInf->ofLodUpd, pofSnpFil, &psiSegInf->isIdxSeg, 
                fpLngPolPrc, ulPolDat);
            break;

        case WAVHDRFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master (sans header)              */
            /* Note: pofSnpFil assumed to be zero length                */
            /************************************************************/
            if (!_fstrlen (pmiMasInf->ofLodUpd.szPathName)) frRetCod = FIORETSUC;
            else frRetCod = FIOOFSApp (&pmiMasInf->ofLodUpd, pofSnpFil, 
                psiSegInf->wsWavSeg.ulAudOff, psiSegInf->wsWavSeg.ulAudLen,
                fpLngPolPrc, ulPolDat);

            /************************************************************/
            /* Indicate Load / Update OFS for subsequent calls          */    
            /************************************************************/
            if (FIORETSUC == frRetCod) pmiMasInf->ofLodUpd = *pofSnpFil;    
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);

}

FIORET  FAR PASCAL  FIOSnpUpd (LPOFSTRUCT_V pofSnpFil, MASINF FAR *pmiMasInf,
                    SEGINF FAR *psiSegInf, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod;
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxArr;              

    /********************************************************************/
    /* Update handled by higher level (through Load / Update OFS)       */
    /********************************************************************/
    if ((ALLPURFMT == pmiMasInf->ffFilFmt) || (WAVHDRFMT == pmiMasInf->ffFilFmt))
        return (FIORETSUC);

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpVBSHdr = GloMemLck (pmiMasInf->mhHdrMem))) return (FIORETERR);
    if (NULL == (lpIdxArr = GloMemLck (pmiMasInf->mhIdxMem))) {
        GloMemUnL (pmiMasInf->mhHdrMem);
        return (FIORETERR);
    }

    /********************************************************************/
    /* Insert a raw vox snippet into an existing VBase prompt           */
    /********************************************************************/
    frRetCod = VBSVoxWrt (&pmiMasInf->ofLodUpd, lpVBSHdr, lpIdxArr, pofSnpFil, 
        &psiSegInf->isIdxSeg, fpLngPolPrc, ulPolDat);
    GloMemUnL (pmiMasInf->mhHdrMem);
    GloMemUnL (pmiMasInf->mhIdxMem);

    /********************************************************************/
    return (frRetCod);
}

FIORET  FAR PASCAL  FIOSnpRel (SEGINF FAR *psiSegInf)
{
    return (FIORETSUC);
}

