/************************************************************************/
/* Rhetorex 4 bit PCM Translator: RtxXl1.c              V2.00  08/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
  
#include <string.h>                     /* String manipulation funcs    */
#include <malloc.h>                     /* Memory allocation functions  */

#include "rhet24.h"
#include "rhet32.h"

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL RtxA04toAlo (LPITCB lpITC, LPITCI lpIni)
{
    /********************************************************************/
    /********************************************************************/
    lpITC->rbRtx.lpR24Exp = CVC_Rhet24Create (CVT_RHET24_EXP);
    lpITC->rbRtx.lpR24Cmp = CVC_Rhet24Create (CVT_RHET24_CMP);
    lpITC->rbRtx.lpR32Exp = CVC_Rhet32Create (CVT_RHET32_EXP);
    lpITC->rbRtx.lpR32Cmp = CVC_Rhet32Create (CVT_RHET32_CMP);
    return (lpITC);
}

LPITCB FAR PASCAL RtxA04toIni (LPITCB lpITC)
{
    return (lpITC);
}

WORD FAR PASCAL RtxA04toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

LPITCB FAR PASCAL RtxA04toRel (LPITCB lpITC)
{
    return (lpITC);
}

/************************************************************************/
/************************************************************************/
int iTmp[4096];
WORD FAR PASCAL RtxA04toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    unsigned int  iOutBufSiz = 4 * *lpusBytCnt;
    unsigned int  iInpCnt = 0;
    unsigned int  iOutCnt = 0;

//    CVC_ExpandRhet24 (lpITC->rbRtx.lpR24Exp, (unsigned FAR *) _sBufSeg:>pcSrcBuf, 
//        *lpusBytCnt, &iInpCnt, _sBufSeg:>psDstBuf, iOutBufSiz, &iOutCnt);
//CVC_ExpandRhet24 (lpITC->rbRtx.lpR24Exp, (unsigned FAR *) _sBufSeg:>pcSrcBuf, 
//    0, &iInpCnt, _sBufSeg:>psDstBuf, 0, &iOutCnt);
//CVC_ExpandRhet24 (iTmp, (unsigned FAR *) _sBufSeg:>pcSrcBuf, 
//    0, &iInpCnt, _sBufSeg:>psDstBuf, 0, &iOutCnt);
//CVC_ExpandRhet24 (CVC_Rhet24Create (CVT_RHET24_EXP), (unsigned FAR *) _sBufSeg:>pcSrcBuf, 
//    *lpusBytCnt, &iInpCnt, _sBufSeg:>psDstBuf, iOutBufSiz, &iOutCnt);
CVC_ExpandRhet24 (CVC_Rhet24Create (CVT_RHET24_EXP), iTmp, 0, &iInpCnt, iTmp, 0, &iOutCnt);

    /********************************************************************/
    /********************************************************************/
    *lpusBytCnt -= iInpCnt;
    return (iOutCnt / 2);
}


WORD FAR PASCAL RtxG16toA04 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{

    unsigned int  iInpBufSiz = 2 * *lpusSmpCnt;
    unsigned int  iOutBufSiz = *lpusSmpCnt / 2;
    unsigned int  iInpCnt;
    unsigned int  iOutCnt;

    CVC_CompressRhet24 (lpITC->rbRtx.lpR24Cmp, _sBufSeg:>psSrcBuf, iInpBufSiz, 
        &iInpCnt, (unsigned int FAR *) _sBufSeg:>pcDstBuf, iOutBufSiz, &iOutCnt);
    *lpusSmpCnt -= (2 * iInpCnt);

    /********************************************************************/
    /********************************************************************/
    return (iOutCnt);
}

WORD FAR PASCAL RtxA04toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    WORD    usOscOrg = usOscCnt;        /* Original oscillation count   */
    return (usOscOrg);                  /* Oscillation output count     */
}

WORD FAR PASCAL RtxSiltoA04 (BYTE FAR *lpcDstBuf, WORD usBufSiz)
{
    return (usBufSiz);
}

/************************************************************************/
/************************************************************************/
LPVOID  FAR __cdecl visalo (int iSiz)
{
    return (_fmalloc (iSiz));
}
void    FAR __cdecl visf (LPVOID lpMem)
{
    _ffree (lpMem);
}
LPVOID  FAR __cdecl visset (LPVOID lpMem, int iVal, int iSiz)
{
    return (_fmemset (lpMem, iVal, iSiz));
}
LPVOID  FAR __cdecl vismove (LPVOID lpDst, const LPVOID lpSrc, int iSiz)
{
    return (_fmemmove (lpDst, lpSrc, iSiz));
}
int     FAR __cdecl vissprf ()
{
    return (0);
}
