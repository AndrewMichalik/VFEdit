/************************************************************************/
/* File I/O Work File Support: FIOWrk.c                 V2.00  07/15/94 */
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
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
FIORET  FAR PASCAL  FIOWrkLod (LPOFSTRUCT_V pofWrkFil, MASINF FAR *pmiMasInf,
                    FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    FIORET      frRetCod = FIORETERR;

    /********************************************************************/
    /* Load work file based upon master file type                       */
    /********************************************************************/
    switch (pmiMasInf->ffFilFmt) {
        case ALLPURFMT:
            /************************************************************/
            /* SnpFil is duplicate of Master, WrkFil is inactive        */
            /************************************************************/
            frRetCod = FIORETSUC;
            break;

        case VBSIDXFMT:
            /************************************************************/
            /* New indexed file: copy header portion only               */
            /* Existing indexed file: Duplicate header & index          */
            /************************************************************/
            if (!_fstrlen (pmiMasInf->ofLodUpd.szPathName)) 
                frRetCod = VBSHdrWrt (pofWrkFil, pmiMasInf->mhHdrMem, 
                pmiMasInf->mhIdxMem);
            else frRetCod = FIOOFSDup (&pmiMasInf->ofLodUpd, pofWrkFil, 
                fpLngPolPrc, ulPolDat);

            /************************************************************/
            /* Indicate Load / Update OFS for subsequent calls          */    
            /************************************************************/
            if (FIORETSUC == frRetCod) pmiMasInf->ofLodUpd = *pofWrkFil;    
            break;

        case WAVHDRFMT:
            /************************************************************/
            /* SnpFil is dup of Master (sans header), WrkFil inactive   */
            /************************************************************/
            frRetCod = FIORETSUC;
            break;

    }

    /********************************************************************/
    /********************************************************************/
    return (frRetCod);
}

FIORET  FAR PASCAL  FIOWrkUpd (LPOFSTRUCT_V pofWrkFil, MASINF FAR *pmiMasInf, 
                    FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    return (FIORETSUC);
}

FIORET  FAR PASCAL  FIOWrkRel (MASINF FAR *pmiMasInf)
{
    return (FIORETSUC);
}


