/************************************************************************/
/* Harris Semiconductor CVSD Translator: HarXl1.c       V2.00  10/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
  
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL HarC01toAlo (LPITCB lpITC, LPITCI lpIni)
{
    ITCINI      iiITCIni;
    
    /********************************************************************/
    /* Check for defaults requests: Use or request default list         */
    /********************************************************************/
    if ((NULL == lpITC) || (NULL == lpIni)) {
        if (NULL == lpIni) lpIni = &iiITCIni;       /* Def load request */
        /****************************************************************/
        /* Load default settings based upon Harris CVSD spec            */
        /* Note: usStpMin[Max] are doubled based on empirical test      */
        /****************************************************************/
        lpIni->ciCVS.ulSmpFrq = SMPFRQDEF;  /* Sample frequnecy         */
        lpIni->ciCVS.usLowTyp = CVSLI2LFA;  /* Output LP filter type    */
        lpIni->ciCVS.ulLowPas =     5000L;  /* Low  pass filter    (Hz) */
        lpIni->ciCVS.usSigFtr =       328;  /* Signal HP filter    (Hz) */
        lpIni->ciCVS.usSylAtk =        80;  /* Syllabic Attack LPF (Hz) */
        lpIni->ciCVS.usSylDcy =        80;  /* Syllabic Decay  LPF (Hz) */
        lpIni->ciCVS.usCoiBit =         3;  /* Coincidence       (bits) */
        lpIni->ciCVS.usStpMin =         4;  /* Minimum step size  (AtD) */
        lpIni->ciCVS.usStpMax =       128;  /* Maximum step size  (AtD) */
        /****************************************************************/
        /* Load default settings based upon Harris CVSD spec            */
        /* Note: usStpMin[Max] are quadrupoled based on empirical test  */
        /****************************************************************/
        lpIni->ciCVS.usAtDRes = ATDRESDEF;  /* A to D resolution (bits) */
        if (!lpITC) return (lpITC);         /* Default load request     */
    }

    /********************************************************************/
    /* Allocate and compute filter variables                            */
    /********************************************************************/
    NwVC01toAlo (lpITC, lpIni);

    /********************************************************************/
    /********************************************************************/
    return (lpITC);

}

LPITCB FAR PASCAL HarC01toIni (LPITCB lpITC)
{
    return (NwVC01toIni (lpITC));
}

WORD FAR PASCAL HarC01toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{

    /********************************************************************/
    /********************************************************************/
    return (NwVC01toCmp (_sBufSeg, pcSrcBuf, lpusRsv001, usSmpCnt, lpITC));

}

LPITCB FAR PASCAL HarC01toRel (LPITCB lpITC)
{
    return (NwVC01toRel (lpITC));
}

/************************************************************************/
/* Convert an array with cvsd data to an array with pcm samples.        */
/*                                                                      */
/* pcSrcBuf:    Pointer to buffer with cvsd bits.                       */
/*              High Order Bit is first sample.                         */
/* psDstBuf:    Pointer to buffer for the pcm output.                   */
/*              Must be usSmpCnt*sizeof(short) bytes long.              */
/* usSmpCnt:    Number of cvsd samples in the array.                    */
/************************************************************************/
WORD FAR PASCAL HarC01toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    /********************************************************************/
    /********************************************************************/
    return (NwVC01toG16 (_sBufSeg, pcSrcBuf, lpusBytCnt, psDstBuf, 
        usRsv001, lpITC));
}

WORD FAR PASCAL HarG16toC01 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    /********************************************************************/
    /********************************************************************/
    return (NwVG16toC01 (_sBufSeg, psSrcBuf, lpusSmpCnt, pcDstBuf, 
        usRsv001, lpITC));
}

WORD FAR PASCAL HarC01toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    return (NwVC01toM32 (_sBufSeg, pcSrcBuf, lpusRsv001, psDstBuf, 
        usOscCnt, ulSetSiz, lpITC));
}

WORD FAR PASCAL HarSiltoC01 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    while (usBufSiz-- > 0) *lpucDstBuf++ = 0x55;
    return (usBufSiz);
}

