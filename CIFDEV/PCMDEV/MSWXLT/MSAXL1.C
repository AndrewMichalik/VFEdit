/************************************************************************/
/* Microsoft ADPCM Translator: MSAXl1.c                 V2.00  10/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "mmsystem.h"                   /* Windows Multi Media defs     */
#include "mmreg.h"                      /* Windows Multi Media reg defs */
#include "msadpcm.h"                    /* MS ADPCM function defs       */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

/************************************************************************/
/************************************************************************/
static  int lmemset (LPVOID, int, WORD);

/************************************************************************/
/*                      Initialize ITC Block                            */                            
/************************************************************************/
LPITCB FAR PASCAL MSWA04toIni (LPITCB lpITC)
{
    /********************************************************************/
    /* Zero only the "history" variables - do not destroy blocking info */
    /********************************************************************/
    lpITC->usBitOff = 0;                /* Current sample bit   offset  */
    lpITC->usBytOff = 0;                /* Current sample byte  offset  */
    lpITC->ulBlkOff = 0;                /* Current sample block offset  */
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

/************************************************************************/
/*      Convert ADPCM nibbles to a 2's complement word array            */
/************************************************************************/
WORD FAR PASCAL MSWA04toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usSmpCnt, LPITCB lpITC)
{
    WORD            usBytCnt;
    unsigned        uiErrCod;
    PCMWAVEFORMAT   wfPCMOut;

    /********************************************************************/
    /* Initialize destination PCM format block                          */
    /********************************************************************/
    wfPCMOut.wBitsPerSample = 16;

    /********************************************************************/
    /********************************************************************/
    usBytCnt = (WORD) adpcmDecode4Bit ((LPADPCMWAVEFORMAT) &lpITC->mwMSW.afWEX, 
        (char huge *) _sBufSeg:>pcSrcBuf, &wfPCMOut, 
        (char huge *) _sBufSeg:>psDstBuf, (DWORD) *lpusBytCnt, (DWORD) usSmpCnt, 
        &uiErrCod);

    /********************************************************************/
    /********************************************************************/
    if (lpusBytCnt) *lpusBytCnt = *lpusBytCnt;  /* Full byte inp count  */
    return (usBytCnt / sizeof (GENSMP));        /* Sample output count  */                            
  
}

WORD FAR PASCAL MSWG16toA04 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    return (0);
}

/************************************************************************/
/************************************************************************/
int lmemset (LPVOID lpDstBlk, int nSetByt, WORD usBytCnt)
{
    while (usBytCnt-- > 0) *((LPSTR)lpDstBlk)++ = (char) nSetByt;
    return (0);
}

