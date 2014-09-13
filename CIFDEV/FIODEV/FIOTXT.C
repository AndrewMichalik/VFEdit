/************************************************************************/
/* File I/O Text Support: FIOTxt.c                      V2.00  07/15/94 */
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
FIORET  FAR PASCAL  FIOTxtLod (VISMEMHDL FAR *pmhAnoMem, MASINF FAR *pmiMasInf,
                    SEGINF FAR *psiSegInf, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    /********************************************************************/
    /* Initialize to NULL for safe de-allocation                        */
    /********************************************************************/
    *pmhAnoMem = NULL;

    /********************************************************************/
    /********************************************************************/
    if ((ALLPURFMT == pmiMasInf->ffFilFmt) || (WAVHDRFMT == pmiMasInf->ffFilFmt))
        return (FIORETSUC);

    /********************************************************************/
    /* Load text based upon master file type                            */
    /********************************************************************/
    return (VBSTxtLod (&pmiMasInf->ofLodUpd, psiSegInf->isIdxSeg.ulTxtOff, pmhAnoMem));

}

FIORET  FAR PASCAL  FIOTxtUpd (VISMEMHDL mhAnoMem, MASINF FAR *pmiMasInf,
                    SEGINF FAR *psiSegInf, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod;
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxArr;              

    /********************************************************************/
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
    /* Insert a text string into an existing VBase prompt               */
    /********************************************************************/
    frRetCod = VBSTxtWrt (&pmiMasInf->ofLodUpd, lpVBSHdr, lpIdxArr, mhAnoMem, 
        &psiSegInf->isIdxSeg, fpLngPolPrc, ulPolDat);
    GloMemUnL (pmiMasInf->mhHdrMem);
    GloMemUnL (pmiMasInf->mhIdxMem);

    /********************************************************************/
    return (frRetCod);

}

FIORET  FAR PASCAL  FIOTxtRel (VISMEMHDL FAR *pmhAnoMem)
{
    if (*pmhAnoMem) VBSTxtRel (pmhAnoMem);
    return (FIORETSUC);
}

