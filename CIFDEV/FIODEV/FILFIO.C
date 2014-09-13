/************************************************************************/
/* File I/O Functions: FilFIO.c                         V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "filutl.h"                     /* File utilities definitions   */

#include <errno.h>                      /* errno value constants        */
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
long FAR PASCAL FIOFilCop (short sSrcHdl, short sDstHdl, DWORD ulReqCnt,
                short FAR *lpErrCod, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    VISMEMHDL   hgGloMem;
    LPSTR       lpWrkBuf;
    DWORD       ulBufSiz;
    unsigned    uiErrCod;
    long        lXfrCnt;

    /********************************************************************/
    /* Allocate Global memory in multiples of 1024L and < 63Kbyte       */
    /********************************************************************/
    if (NULL == (hgGloMem = GloAloBlk (GMEM_FIXED, FIOGLOBLK, FIOGLOMIN,
        FIOGLOMAX, &ulBufSiz))) return (-1L);
    if ((LPSTR) NULL == (lpWrkBuf = (LPSTR) GloMemLck (hgGloMem))) {
        GloAloRel (hgGloMem);
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    lXfrCnt = FilCop (sSrcHdl, sDstHdl, lpWrkBuf, (WORD) ulBufSiz, 
        ulReqCnt, FIOENCNON, &uiErrCod, fpLngPolPrc, ulPolDat);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (hgGloMem);
    GloAloRel (hgGloMem);

    /********************************************************************/
    /* Future: if (NULL != lpErrCod) Return error code, no message.     */
    /********************************************************************/
    if (-1L == lXfrCnt) {
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_FILLCKORO);                              /* No Access    */
        else if (EBADF  == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INVFILHDL);                              /* Bad Handle   */
        else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INSDSKSPC);                              /* Ins Dsk Spc  */
        else if (FIO_E_ABT == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_USRCANREQ);                              /* User cancel  */
        else MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_UNKACCERR);                              /* Unknown err  */
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    return (lXfrCnt);
}

long FAR PASCAL FIOFilDup (short sSrcHdl, short sDstHdl, short FAR *lpErrCod, 
                FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    VISMEMHDL   hgGloMem;
    LPSTR       lpWrkBuf;
    DWORD       ulBufSiz;
    unsigned    uiErrCod;
    long        lXfrCnt;

    /********************************************************************/
    /* Allocate Global memory in multiples of 1024L and < 63Kbyte       */
    /********************************************************************/
    if (NULL == (hgGloMem = GloAloBlk (GMEM_FIXED, FIOGLOBLK, FIOGLOMIN,
        FIOGLOMAX, &ulBufSiz))) return (-1L);
    if ((LPSTR) NULL == (lpWrkBuf = (LPSTR) GloMemLck (hgGloMem))) {
        GloAloRel (hgGloMem);
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    lXfrCnt = FilDup (sSrcHdl, sDstHdl, lpWrkBuf, (WORD) ulBufSiz, 
        FIOENCNON, &uiErrCod, fpLngPolPrc, ulPolDat);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (hgGloMem);
    GloAloRel (hgGloMem);

    /********************************************************************/
    /* Future: if (NULL != lpErrCod) Return error code, no message.     */
    /********************************************************************/
    if (-1L == lXfrCnt) {
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_FILLCKORO);                              /* No Access    */
        else if (EBADF  == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INVFILHDL);                              /* Bad Handle   */
        else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INSDSKSPC);                              /* Ins Dsk Spc  */
        else if (FIO_E_ABT == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_USRCANREQ);                             /* User cancel  */
        else MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_UNKACCERR);                              /* Unknown err  */
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    return (lXfrCnt);
}

long FAR PASCAL FIOFilMov (char *szSrcFil, char *szDstFil, BOOL bDatSav, 
                short FAR *lpErrCod, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    VISMEMHDL   hgGloMem;
    LPSTR       lpWrkBuf;
    DWORD       ulBufSiz;
    unsigned    uiErrCod;
    long        lRetCod;

    /********************************************************************/
    /* Allocate Global memory in multiples of 1024L and < 63Kbyte       */
    /********************************************************************/
    if (NULL == (hgGloMem = GloAloBlk (GMEM_FIXED, FIOGLOBLK, FIOGLOMIN,
        FIOGLOMAX, &ulBufSiz))) return (-1L);
    if ((LPSTR) NULL == (lpWrkBuf = (LPSTR) GloMemLck (hgGloMem))) {
        GloAloRel (hgGloMem);
        return (-1L);
    }

    lRetCod = FilMov (szSrcFil, szDstFil, lpWrkBuf, (WORD) ulBufSiz, bDatSav, 
        &uiErrCod, fpLngPolPrc, ulPolDat);

    /********************************************************************/
    /* Future: if (NULL != lpErrCod) Return error code, no message.     */
    /********************************************************************/
    if (-1L == lRetCod) {
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_FILLCKORO);                              /* No Access    */
        else if (EBADF  == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INVFILHDL);                              /* Bad Handle   */
        else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INSDSKSPC);                              /* Ins Dsk Spc  */
        else if (FIO_E_ABT == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_USRCANREQ);                             /* User cancel  */
        else MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_UNKACCERR);                              /* Unknown err  */
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (hgGloMem);
    GloAloRel (hgGloMem);

    /********************************************************************/
    /********************************************************************/
    return (lRetCod);

}

long FAR PASCAL FIOFilShf (short sSrcHdl, short sDstHdl, DWORD ulShfPnt, 
                long lShfAmt, short FAR *lpErrCod, FIOPOLPRC fpLngPolPrc, 
                DWORD ulPolDat)
{
    VISMEMHDL   hgGloMem;
    LPSTR       lpWrkBuf;
    DWORD       ulBufSiz;
    unsigned    uiErrCod;
    long        lXfrCnt;

    /********************************************************************/
    /* Allocate Global memory in multiples of 1024L and < 63Kbyte       */
    /********************************************************************/
    if (NULL == (hgGloMem = GloAloBlk (GMEM_FIXED, FIOGLOBLK, FIOGLOMIN,
        FIOGLOMAX, &ulBufSiz))) return (-1L);
    if ((LPSTR) NULL == (lpWrkBuf = (LPSTR) GloMemLck (hgGloMem))) {
        GloAloRel (hgGloMem);
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    lXfrCnt = FilShf (sSrcHdl, sDstHdl, lpWrkBuf, (WORD) ulBufSiz,
        ulShfPnt, labs (lShfAmt), lShfAmt < 0 ? FIODIRREV : FIODIRFWD,
        &uiErrCod, fpLngPolPrc, ulPolDat);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (hgGloMem);
    GloAloRel (hgGloMem);

    /********************************************************************/
    /* Future: if (NULL != lpErrCod) Return error code, no message.     */
    /********************************************************************/
    if (-1L == lXfrCnt) {
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_FILLCKORO);                              /* No Access    */
        else if (EBADF  == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INVFILHDL);                              /* Bad Handle   */
        else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_INSDSKSPC);                              /* Ins Dsk Spc  */
        else if (FIO_E_ABT == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_USRCANREQ);                             /* User cancel  */
        else MsgDspRes (FIOGlo.hLibIns, 0, 
            SI_UNKACCERR);                              /* Unknown err  */
        return (-1L);
    }

    /********************************************************************/
    /********************************************************************/
    return (lXfrCnt);

}


