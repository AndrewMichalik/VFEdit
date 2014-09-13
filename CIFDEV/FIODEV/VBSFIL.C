/************************************************************************/
/* VFEdit VBase File Routines: VBSFil.c                 V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#if (defined (W31)) /****************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#endif /*****************************************************************/
#if (defined (DOS)) /****************************************************/
#include "visdef.h"                     /* VIS Standard type defs       */
#include "..\os_dev\dosmem.h"           /* Generic memory support defs  */
#include "..\os_dev\dosmsg.h"           /* User message support defs    */
#endif /*****************************************************************/
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "filutl.h"                     /* File utilities definitions   */
#include "vbsfil.h"                     /* VBase file format defs       */
  
#include <string.h>                     /* String manipulation funcs    */
#include <math.h>                       /* Floating point math funcs    */
#include <errno.h>                      /* errno value constants        */
  
/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/*                      Forward References                              */
/************************************************************************/
FIORET  ShfVBSFil (LPOFSTRUCT_V, VBSHDR FAR *, VBIREC FAR *, DWORD FAR *, 
        DWORD FAR *, DWORD, FIOPOLPRC, DWORD);       

/************************************************************************/
/* VBSHdrIni: Initialize header and index memory handles and contents   */
/************************************************************************/
FIORET  FAR PASCAL VBSHdrIni (OFSTRUCT_V FAR *pofDstFil, VISMEMHDL FAR *pmhHdrMem, 
        VISMEMHDL FAR *pmhIdxMem, WORD usIdxCnt, DWORD ulSmpFrq)
{
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxArr;
//    short       sDstHdl;
//    unsigned    uiErrCod;

    /********************************************************************/
    /* Allocate global memory for file header                           */
    /********************************************************************/
    if (NULL == (lpVBSHdr = GloAloLck (GMEM_MOVEABLE, pmhHdrMem, 
      (DWORD) sizeof (VBSHDR)))) {
        return (FIORETERR);
    }
    
    /********************************************************************/
    /********************************************************************/
    lpVBSHdr->ulIdxTot = (DWORD) usIdxCnt;      /* Prompt count max     */
    lpVBSHdr->ulSmpFrq = ulSmpFrq;              /* Sample frequency     */
    lpVBSHdr->ulIdxUse = 0L;                    /* Prompt count actv    */
    lpVBSHdr->uldummya = 0L;                    /* Dummy                */
    lpVBSHdr->ulBytUse = (DWORD) sizeof (VBSHDR)
        + (DWORD) usIdxCnt * sizeof (VBIREC);   /* Bytes used (file)    */
    lpVBSHdr->uldummyb = 0L;                    /* Dummy                */

    /********************************************************************/
    /* Allocate mem for new array in multiples of sizeof (VBIREC)       */
    /********************************************************************/
    if (NULL == (lpIdxArr = GloAloLck (GMEM_MOVEABLE, pmhIdxMem, 
      (DWORD) sizeof (VBIREC) * usIdxCnt))) {
        *pmhHdrMem = GloUnLRel (*pmhHdrMem);
        return (FIORETERR);
    }
    _fmemset (lpIdxArr, 0x00, sizeof (VBIREC) * usIdxCnt);
    
//    /********************************************************************/
//    /* Write header & index information                                 */
//    /********************************************************************/
//    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, SI_BADOPNDST))) {
//        *pmhHdrMem = GloUnLRel (*pmhHdrMem);
//        *pmhIdxMem = GloUnLRel (*pmhIdxMem);
//        return (FIORETERR);
//    }
//    if ((-1 == Wr_FilFwd (sDstHdl, lpVBSHdr, sizeof (VBSHDR), 0, &uiErrCod)) 
//      || (-1 == Wr_FilFwd (sDstHdl, lpIdxArr, sizeof (VBIREC) 
//      * (WORD) lpVBSHdr->ulIdxTot, 0, &uiErrCod))) {
//        FilHdlCls (sDstHdl);
//        *pmhHdrMem = GloUnLRel (*pmhHdrMem);
//        *pmhIdxMem = GloUnLRel (*pmhIdxMem);
//        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
//         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
//          else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_INSDSKSPC);  /* Ins Dsk Spc  */
//           else MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);                         /* No Overwrite */
//        return (FIORETERR);
//    }
//    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhHdrMem);
    GloMemUnL (*pmhIdxMem);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

/************************************************************************/
/* VBSHdrLod: Load index header & index to existing or NULL memory      */
/************************************************************************/
FIORET  FAR PASCAL VBSHdrLod (OFSTRUCT_V FAR *pofSrcFil, VISMEMHDL FAR *pmhHdrMem,
        VISMEMHDL FAR *pmhIdxMem)
{

    short       sSrcHdl;
    DWORD       ulFilLen;
    DWORD       ulIdxCnt;
    DWORD       ulMinLen;
    LPSTR       lpWrkBuf;
    unsigned    uiErrCod;

    /********************************************************************/
    /* SI_BADOPNSRC: Cannot Open Source File                            */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETERR);
    }
    if ((long) (ulFilLen = FilGetLen (sSrcHdl)) < (long) sizeof (VBSHDR)) {
        FilHdlCls (sSrcHdl);
        MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);    /* Invalid Fmt  */
        return (FIORETERR);
    }

    /********************************************************************/
    /* Re-Allocate global memory for file header                        */
    /********************************************************************/
    if (NULL == (*pmhHdrMem = GloReAMem (*pmhHdrMem, sizeof (VBSHDR)))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }
    if (NULL == (lpWrkBuf = GloMemLck (*pmhHdrMem))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }

    /********************************************************************/
    /* Read VBase Header Information                                    */
    /********************************************************************/
    if (sizeof (VBSHDR) != Rd_FilFwd (sSrcHdl, lpWrkBuf,
      sizeof (VBSHDR), 0, &uiErrCod)) {
        FilHdlCls (sSrcHdl);
        GloMemUnL (*pmhHdrMem);
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
          else MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);                          /* Invalid Fmt  */
        return (FIORETERR);
    }

    /********************************************************************/
    /* Check and set sample frequency                                   */
    /********************************************************************/
    if ((((VBSHDR FAR *)lpWrkBuf)->ulSmpFrq > VBSMAXFRQ)    
      || ((VBSHDR FAR *)lpWrkBuf)->ulSmpFrq <= 0)    
        ((VBSHDR FAR *)lpWrkBuf)->ulSmpFrq = VBSDEFFRQ;

    /********************************************************************/
    /* Perform test for valid format                                    */
    /********************************************************************/
    ulFilLen = FilGetLen (sSrcHdl);
    ulIdxCnt = ((VBSHDR FAR *)lpWrkBuf)->ulIdxTot;
    ulMinLen = (DWORD) sizeof(VBSHDR) + ((DWORD) sizeof (VBIREC) * ulIdxCnt);         
    GloMemUnL (*pmhHdrMem);

    if ((0L == ulIdxCnt) || (ulIdxCnt > (DWORD) VBSMAXIDX)
      || (-1L == ulFilLen) || (ulMinLen > ulFilLen)) {
        FilHdlCls (sSrcHdl);
        MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);    /* Invalid Fmt  */
        return (FIORETERR);
    }

    /********************************************************************/
    /* Allocate mem for whole array in multiples of sizeof (VBIREC)     */
    /********************************************************************/
    if (NULL == (*pmhIdxMem = GloReAMem (*pmhIdxMem, 
        (DWORD) sizeof (VBIREC) * ulIdxCnt))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }
    if (NULL == (lpWrkBuf = GloMemLck (*pmhIdxMem))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }

    /********************************************************************/
    /* Read indexes; if read not complete, return error                 */
    /********************************************************************/
    if (-1L == Rd_FilFwd (sSrcHdl, lpWrkBuf,
      sizeof (VBIREC) * (WORD) ulIdxCnt, 0, &uiErrCod)) {
        FilHdlCls (sSrcHdl);
        GloMemUnL (*pmhIdxMem);
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
          else MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILFMT);                          /* Invalid Fmt  */
        return (FIORETERR);
    }

    /********************************************************************/
    /********************************************************************/
    FilHdlCls (sSrcHdl);
    GloMemUnL (*pmhIdxMem);

    return (FIORETSUC);

}

FIORET  FAR PASCAL VBSHdrWrt (OFSTRUCT_V FAR *pofDstFil, VISMEMHDL mhHdrMem, 
        VISMEMHDL mhIdxMem)
{
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxArr;
    short       sDstHdl;
    unsigned    uiErrCod;

    /********************************************************************/
    /* Lock header memory and retrieve array information                */
    /********************************************************************/
    if ((VBSHDR FAR *) NULL == (lpVBSHdr = (VBSHDR FAR *) GloMemLck (mhHdrMem))) 
        return (FIORETERR); 

    /********************************************************************/
    /* Lock index array memory                                          */
    /********************************************************************/
    if ((VBIREC FAR *) NULL == (lpIdxArr = (VBIREC FAR *) GloMemLck (mhIdxMem))) {
        GloMemUnL (mhHdrMem);
        return (FIORETERR); 
    }

    /********************************************************************/
    /* Write header & index information                                 */
    /********************************************************************/
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, SI_BADOPNDST))) {
        GloMemUnL (mhIdxMem);
        GloMemUnL (mhHdrMem);
        return (FIORETERR);
    }
    if ((-1 == Wr_FilFwd (sDstHdl, lpVBSHdr, sizeof (VBSHDR), 0, &uiErrCod)) 
      || (-1 == Wr_FilFwd (sDstHdl, lpIdxArr, sizeof (VBIREC) 
      * (WORD) lpVBSHdr->ulIdxTot, 0, &uiErrCod))) {
        FilHdlCls (sDstHdl);
        GloMemUnL (mhIdxMem);
        GloMemUnL (mhHdrMem);
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
          else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_INSDSKSPC);  /* Ins Dsk Spc  */
           else MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);                         /* No Overwrite */
        return (FIORETERR);
    }
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhIdxMem);
    GloMemUnL (mhHdrMem);
    return (FIORETSUC);

}

FIORET  FAR PASCAL VBSHdrRel (VISMEMHDL FAR *pmhHdrMem, VISMEMHDL FAR *pmhIdxMem)
{
    *pmhHdrMem = GloAloRel (*pmhHdrMem);
    *pmhIdxMem = GloAloRel (*pmhIdxMem);
    return (FIORETSUC);
}

/************************************************************************/
/* Load and Write raw audio data into an existing indexed file          */
/************************************************************************/
FIORET FAR PASCAL VBSVoxLod (OFSTRUCT_V FAR *pofSrcFil, OFSTRUCT_V FAR *pofDstFil, 
                  IDXSEG FAR *pisIdxSeg, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{

    short   sSrcHdl, sDstHdl;

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETERR);                      /* Cannot Open Src File */
    }
    FilSetPos (sSrcHdl, pisIdxSeg->ulVoxOff, SEEK_SET);

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, 
      SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }

    if (-1L == FIOFilCop (sSrcHdl, sDstHdl, pisIdxSeg->ulVoxLen, 
      NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        return (FIORETBAD);
    }

    /********************************************************************/
    /********************************************************************/
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

FIORET  FAR PASCAL VBSVoxWrt (OFSTRUCT_V FAR *pofDstFil, VBSHDR FAR *lpVBSHdr,
        VBIREC FAR *lpIdxArr, OFSTRUCT_V FAR *pofSnpFil, IDXSEG FAR *pisIdxSeg, 
        FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short       sSnpHdl;
    WORD        usArrIdx;
    DWORD       ulNewLen;
    short       sDstHdl;

    /********************************************************************/
    /********************************************************************/
    if ((WORD) (usArrIdx = pisIdxSeg->usIdxNum - 1) >= (WORD) lpVBSHdr->ulIdxTot) 
        return (FIORETERR);
    ulNewLen = FIOOFSLen (pofSnpFil);

    /********************************************************************/
    /* For non auto-compressed file saves, zero current index           */
    /********************************************************************/
//    if (!bfAutCmp) lpIdxArr[usArrIdx].ulVoxOff = lpIdxArr[usArrIdx].ulVoxLen = 0; 

    /********************************************************************/
    /* Shift to adjust for new vox portion                              */
    /********************************************************************/
    if (FIORETSUC != ShfVBSFil (pofDstFil, lpVBSHdr, lpIdxArr,
      &lpIdxArr[usArrIdx].ulVoxOff, &lpIdxArr[usArrIdx].ulVoxLen, 
      ulNewLen, fpLngPolPrc, ulPolDat)) {
        MsgDspRes (FIOGlo.hLibIns, 0, SI_FILSHFERR); /* File Shift Err  */
        return (FIORETBAD);      
    }
    pisIdxSeg->ulVoxOff = lpIdxArr[usArrIdx].ulVoxOff;
    pisIdxSeg->ulVoxLen = lpIdxArr[usArrIdx].ulVoxLen;
    pisIdxSeg->ulTxtOff = lpIdxArr[usArrIdx].ulTxtOff;

    /********************************************************************/
    /* Copy snippet vox to indexed VBase work file                      */
    /********************************************************************/
    if (-1 == (sSnpHdl = OFSFilOpn (pofSnpFil, OF_READ, SI_BADOPNSRC)))
        return (FIORETERR);
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE, SI_BADOPNDST))) {
        FilHdlCls (sSnpHdl);
        return (FIORETERR);
    }
    FilSetPos (sSnpHdl, 0L, SEEK_SET);
    FilSetPos (sDstHdl, lpIdxArr[usArrIdx].ulVoxOff, SEEK_SET);
    if (-1L == FIOFilCop (sSnpHdl, sDstHdl, ulNewLen, NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSnpHdl);
        FilHdlCls (sDstHdl);
        MsgDspRes (FIOGlo.hLibIns, 0, SI_FILCOPERR);    /* File Copy Err */
        return (FIORETBAD);      
    }
    FilHdlCls (sSnpHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC); 

}

/************************************************************************/
/* VBSTxtLod: Load annotation text to existing or NULL memory           */
/************************************************************************/
FIORET  FAR PASCAL VBSTxtLod (OFSTRUCT_V FAR *pofSrcFil, DWORD ulTxtOff,
        VISMEMHDL FAR *pmhAnoMem)
{
    short       sSrcHdl;
    LPSTR       lpAnoTxt;
    WORD        usBytCnt;
    WORD        usTrmPos;
    unsigned    uiErrCod;

    /********************************************************************/
    /* Re-Allocate global memory annotation text string                 */
    /********************************************************************/
    if (NULL == (*pmhAnoMem = GloReAMem (*pmhAnoMem, VBSTXTMAX))) {
        return (FIORETERR);
    }
    if (NULL == (lpAnoTxt = GloMemLck (*pmhAnoMem))) {
        return (FIORETERR);
    }
    *lpAnoTxt = '\0';

    /********************************************************************/
    /* If annotation is inactive, return with empty buffer              */
    /********************************************************************/
    if (0L == ulTxtOff) {
        GloMemUnL (*pmhAnoMem);
        return (FIORETSUC);
    }

    /********************************************************************/
    /* Open source file for reading                                     */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        *pmhAnoMem = GloUnLRel (*pmhAnoMem);
        return (FIORETERR);
    }
    FilSetPos (sSrcHdl, ulTxtOff, SEEK_SET);

    /********************************************************************/
    /********************************************************************/
    usBytCnt = Rd_FilFwd (sSrcHdl, lpAnoTxt, VBSTXTMAX - 1, 0, &uiErrCod);
    if ((-1 == usBytCnt) || (0 == usBytCnt)) {
        *pmhAnoMem = GloUnLRel (*pmhAnoMem);
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }
    FilHdlCls (sSrcHdl);

    /********************************************************************/
    /* Scan string for terminator; if at end of buffer, set terminator  */
    /********************************************************************/
    for (usTrmPos=0; usTrmPos<usBytCnt; usTrmPos++) 
        if ('\0' == lpAnoTxt[usTrmPos]) break;
    lpAnoTxt[usTrmPos] = '\0';

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhAnoMem);
    return (FIORETSUC);

}

FIORET  FAR PASCAL VBSTxtRel (VISMEMHDL FAR *pmhAnoMem)
{
    *pmhAnoMem = GloAloRel (*pmhAnoMem);
    return (FIORETSUC);
}

FIORET  FAR PASCAL VBSTxtWrt (OFSTRUCT_V FAR *pofDstFil, VBSHDR FAR *lpVBSHdr,
        VBIREC FAR *lpIdxArr, VISMEMHDL mhAnoMem, IDXSEG FAR *pisIdxSeg, FIOPOLPRC fpLngPolPrc, 
        DWORD ulPolDat)
{

    WORD        usArrIdx;
    LPSTR       lpAnoTxt;
    WORD        usNewSiz;
    unsigned    uiErrCod;
    short       sDstHdl;

    /********************************************************************/
    /********************************************************************/
    if ((WORD) (usArrIdx = pisIdxSeg->usIdxNum - 1) >= (WORD) lpVBSHdr->ulIdxTot) 
        return (FIORETERR);

    /********************************************************************/
    /* For non auto-compressed file saves, zero current index           */
    /********************************************************************/
//    if (!bfAutCmp) lpIdxArr[usArrIdx].ulTxtOff = 0; 

    /********************************************************************/
    /* Calculate new text length; if not zero, increment for terminator */
    /* Note: usNewSiz = 0 deactivates text                              */
    /********************************************************************/
    if (NULL == (lpAnoTxt = GloMemLck (mhAnoMem))) return (FIORETBAD);
    usNewSiz = _fstrlen (lpAnoTxt);
    if (usNewSiz) usNewSiz++;         /* Increment for null term  */

    /********************************************************************/
    /* Exit if both original and new are zero length.                   */
    /********************************************************************/
    if ((0L == lpIdxArr[usArrIdx].ulTxtOff) && (0 == usNewSiz)) {
        GloMemUnL (mhAnoMem);
        return (FIORETSUC); 
    }

    /********************************************************************/
    /* Shift file to make room for annotation text                      */
    /* Note: Non-zero annotation offset with zero text resets offset    */
    /********************************************************************/
    if (FIORETSUC != ShfVBSFil (pofDstFil, lpVBSHdr, lpIdxArr,
      &lpIdxArr[usArrIdx].ulTxtOff, &pisIdxSeg->ulTxtSiz,
      (DWORD) usNewSiz, fpLngPolPrc, ulPolDat)) {
        MsgDspRes (FIOGlo.hLibIns, 0, SI_FILSHFERR); /* File Shift Err  */
        GloMemUnL (mhAnoMem);
        return (FIORETBAD);      
    }
    pisIdxSeg->ulVoxOff = lpIdxArr[usArrIdx].ulVoxOff;
    pisIdxSeg->ulVoxLen = lpIdxArr[usArrIdx].ulVoxLen;
    pisIdxSeg->ulTxtOff = lpIdxArr[usArrIdx].ulTxtOff;
    pisIdxSeg->ulTxtSiz = (DWORD) usNewSiz;

    /********************************************************************/
    /* Copy snippet text to indexed VBase work file                     */
    /********************************************************************/
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE, SI_BADOPNDST))) {
        GloMemUnL (mhAnoMem);
        return (FIORETERR);
    }
    if (usNewSiz) {
        FilSetPos (sDstHdl, lpIdxArr[usArrIdx].ulTxtOff, SEEK_SET);
        if (-1 == Wr_FilFwd (sDstHdl, lpAnoTxt, usNewSiz, 0, &uiErrCod)) {
            GloMemUnL (mhAnoMem);
            FilHdlCls (sDstHdl);
            return (FIORETBAD);      
        }
    }
    GloMemUnL (mhAnoMem);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);      

}

FIORET  FAR PASCAL VBSFilWrtOld (LPOFSTRUCT_V, LPOFSTRUCT_V, VISMEMHDL,
                    VISMEMHDL, DWORD, FIOPOLPRC, DWORD);
FIORET  FAR PASCAL VBSFilWrtOld (OFSTRUCT_V FAR *pofSrcFil, OFSTRUCT_V FAR *pofDstFil, 
        VISMEMHDL mhHdrMem, VISMEMHDL hIdxArr, DWORD ulOrgOff, 
        FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{

    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxRec;
    unsigned    uiErrCod;
    DWORD       ulNewOff;
    DWORD       ulShfAmt;
    WORD        usIdxSiz;
    short       sSrcHdl;
    short       sDstHdl;
    short       sDirFlg;

    /********************************************************************/
    /********************************************************************/
    if ((VBSHDR FAR *) NULL == (lpVBSHdr = GloDupLck (GMEM_MOVEABLE, &mhHdrMem)))
        return (FIORETERR);

    if ((VBIREC FAR *) NULL == (lpIdxRec = GloDupLck (GMEM_MOVEABLE, &hIdxArr))) {
        GloUnLRel (mhHdrMem);
        return (FIORETERR);
    }

    /********************************************************************/
    /* Compute shift parameters; If shift needed, re-compute Vbase      */
    /* indexes, ulIdxUse & ulBytUse header params                       */
    /********************************************************************/
    usIdxSiz = sizeof (VBIREC) * (WORD) lpVBSHdr->ulIdxTot;
    ulNewOff = (DWORD) (sizeof (VBSHDR) + usIdxSiz);         
    ulShfAmt = labs (ulNewOff - ulOrgOff);
    sDirFlg = (ulNewOff >= ulOrgOff) ? +1 : -1;
    if (0L != ulShfAmt) VBSIdxCmp (lpVBSHdr, lpIdxRec, ulOrgOff, ulShfAmt, sDirFlg);

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        GloUnLRel (mhHdrMem);
        GloUnLRel (hIdxArr);
        return (FIORETERR);                      /* Cannot Open Src File */
    }
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        GloUnLRel (mhHdrMem);
        GloUnLRel (hIdxArr);
        return (FIORETERR);
    }

    /********************************************************************/
    /* Write VBase Header Information                                   */
    /********************************************************************/
    if (-1 == Wr_FilFwd (sDstHdl, lpVBSHdr, sizeof (VBSHDR), 0, &uiErrCod)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        GloUnLRel (mhHdrMem);
        GloUnLRel (hIdxArr);
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
          else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_INSDSKSPC);  /* Ins Dsk Spc  */
           else MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);                         /* No Overwrite */
        return (FIORETERR);
    }

    /********************************************************************/
    /* Write VBase Index Information                                    */
    /********************************************************************/
    if (-1 == Wr_FilFwd (sDstHdl, lpIdxRec, usIdxSiz, 0, &uiErrCod)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        GloUnLRel (mhHdrMem);
        GloUnLRel (hIdxArr);
        if (EACCES == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_FILLCKORO);         /* No Access    */
         else if (EBADF == uiErrCod)  MsgDspRes (FIOGlo.hLibIns, 0, SI_INVFILHDL);   /* Bad Handle   */
          else if (ENOSPC == uiErrCod) MsgDspRes (FIOGlo.hLibIns, 0, SI_INSDSKSPC);  /* Ins Dsk Spc  */
           else MsgDspRes (FIOGlo.hLibIns, 0, SI_BADOVRWRT);                         /* No Overwrite */
        return (FIORETERR);
    }

    /********************************************************************/
    /* Write VBase Vox Information                                      */
    /********************************************************************/
    FilSetPos (sSrcHdl, ulOrgOff, SEEK_SET);
    if (-1L == FIOFilDup (sSrcHdl, sDstHdl, NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        GloUnLRel (mhHdrMem);
        GloUnLRel (hIdxArr);
        MsgDspRes (FIOGlo.hLibIns, 0, SI_FILCOPERR); /* File Copy Error      */
        return (FIORETBAD);
    }
  
    /********************************************************************/
    /********************************************************************/
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);
    GloUnLRel (mhHdrMem);
    GloUnLRel (hIdxArr);

    return (FIORETSUC);

}

/************************************************************************/
/*                  VBase Private Support Routines                      */
/************************************************************************/
FIORET  ShfVBSFil (OFSTRUCT_V FAR *pofVBSFil, VBSHDR FAR *lpVBSHdr,
        VBIREC FAR *lpIdxArr, DWORD FAR *lpSelOff, DWORD FAR *lpSelLen,
        DWORD ulNewLen, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short   sDirFlg;
    DWORD   ulOrgOff;
    DWORD   ulSavOff = *lpSelOff;
    DWORD   ulSavLen = *lpSelLen;

    /********************************************************************/
    /* If previously unused, request End Of File shifted by ShfAmt      */
    /* Set shift point and shift amount                                 */
    /********************************************************************/
    if ((0L == *lpSelOff) && (0L != ulNewLen)) {
        *lpSelOff = FIOOFSLen (pofVBSFil);
        *lpSelLen = 0L;
    }
    ulOrgOff = *lpSelOff;

    /********************************************************************/
    /* Compute shift parameters; if no shift required, return.          */
    /********************************************************************/
    if (*lpSelLen == ulNewLen) return (0);
    sDirFlg = (ulNewLen > *lpSelLen) ? +1 : -1;
    *lpSelOff += *lpSelLen;
    *lpSelLen = labs (ulNewLen - *lpSelLen);

    /********************************************************************/
    /* Shift file to reflect new indexes                                */
    /* Right Shift: Shift point appears at new position                 */
    /* Left  Shift: Shift point appears at new position, ulShfPnt       */
    /*              could be end of file!                               */
    /* Restore shift offset and length on failure                       */
    /********************************************************************/
    if (FIORETSUC != FIOOFSShf (pofVBSFil, *lpSelOff, 
      *lpSelLen * (long) sDirFlg, fpLngPolPrc, ulPolDat)) {
        *lpSelOff = ulSavOff;
        *lpSelLen = ulSavLen;
        return (FIORETBAD);
    }

    /********************************************************************/
    /* Re-compute VBase indexes, ulIdxUse & ulBytUse params             */
    /********************************************************************/
    VBSIdxCmp (lpVBSHdr, lpIdxArr, *lpSelOff, *lpSelLen, sDirFlg);

    /********************************************************************/
    /* Force this index offset and length back to pre-VBSIdxCmp values. */
    /* (if length == 0L, VBSIdxCmp moves offset by ulShfAmt)            */
    /********************************************************************/
    if (0L != (*lpSelLen = ulNewLen)) *lpSelOff = ulOrgOff;
    else *lpSelOff = 0L;

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

/************************************************************************/
/************************************************************************/
DWORD   RebSrcToD (short, short, LPSTR, WORD, VBSHDR FAR *, VBIREC FAR *, 
        FIOPOLPRC, DWORD);
DWORD   CopSrcVox (short, short, LPSTR, WORD, DWORD FAR *, DWORD FAR *);
DWORD   CopSrcTxt (short, short, LPSTR, WORD, DWORD FAR *);

FIORET  FAR PASCAL VBSFilWrt (OFSTRUCT_V FAR *pofSrcFil, OFSTRUCT_V FAR *pofDstFil, 
        VISMEMHDL mhHdrMem, VISMEMHDL mhIdxMem, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    VISMEMHDL   mhGloMem;
    LPSTR       lpWrkBuf;
    DWORD       ulBufSiz;
    VBSHDR FAR *lpVBSHdr;
    VBIREC FAR *lpIdxRec;
    DWORD       ulXfrCnt;
    short       sSrcHdl;
    short       sDstHdl;

    /********************************************************************/
    /* Allocate Global memory in multiples of 1024L and < 63Kbyte       */
    /********************************************************************/
    if (NULL == (mhGloMem = GloAloBlk (GMEM_FIXED, FIOGLOBLK, FIOGLOMIN,
        FIOGLOMAX, &ulBufSiz))) return (-1L);
    if ((LPSTR) NULL == (lpWrkBuf = (LPSTR) GloMemLck (mhGloMem))) {
        GloAloRel (mhGloMem);
        return (-1L);
    }

    /********************************************************************/
    /* Duplicate header and index entries                               */
    /********************************************************************/
    if ((VBSHDR FAR *) NULL == (lpVBSHdr = GloDupLck (GMEM_MOVEABLE, &mhHdrMem))) {
        GloUnLRel (mhGloMem);
        return (FIORETERR);
    }
    if ((VBIREC FAR *) NULL == (lpIdxRec = GloDupLck (GMEM_MOVEABLE, &mhIdxMem))) {
        GloUnLRel (mhGloMem);
        GloUnLRel (mhHdrMem);
        return (FIORETERR);
    }
    lpVBSHdr->ulIdxTot = min (lpVBSHdr->ulIdxTot, VBSMAXIDX);

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        GloUnLRel (mhGloMem);
        GloUnLRel (mhHdrMem);
        GloUnLRel (mhIdxMem);
        return (FIORETERR);                      /* Cannot Open Src File */
    }
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        GloUnLRel (mhGloMem);
        GloUnLRel (mhHdrMem);
        GloUnLRel (mhIdxMem);
        return (FIORETERR);
    }

    /********************************************************************/
    /********************************************************************/
    ulXfrCnt = RebSrcToD (sSrcHdl, sDstHdl, lpWrkBuf, (WORD) ulBufSiz, 
        lpVBSHdr, lpIdxRec, fpLngPolPrc, ulPolDat);

    /********************************************************************/
    /********************************************************************/
    GloUnLRel (mhGloMem);
    GloUnLRel (mhHdrMem);
    GloUnLRel (mhIdxMem);
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

DWORD   RebSrcToD (short sSrcHdl, short sDstHdl, LPSTR lpWrkBuf, WORD usBufSiz,
        VBSHDR FAR *lpVBSHdr, VBIREC FAR *lpIdxRec, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    VBIREC FAR* lpXfrRec = lpIdxRec;
    DWORD       ulXfrCnt = 0L;
    unsigned    uiErrCod;    
    WORD        usi;

    /********************************************************************/
    /********************************************************************/
    ulXfrCnt = (DWORD) sizeof (VBSHDR) + (DWORD) lpVBSHdr->ulIdxTot * sizeof (VBIREC);   

    /********************************************************************/
    /* Initialize destination file position                             */
    /********************************************************************/
    if (-1L == FilSetPos (sDstHdl, ulXfrCnt, SEEK_SET)) return ((DWORD) -1L);

    /********************************************************************/
    /* Show/Hide Progress indicator for time consuming operations       */
    /********************************************************************/
    if (fpLngPolPrc) fpLngPolPrc (FIOPOLBEG, FilGetLen (sSrcHdl), ulPolDat);

    /********************************************************************/
    /********************************************************************/
    lpVBSHdr->ulIdxUse = 0L;

    /********************************************************************/
    /* Copy all source index entries to the destination file            */
    /********************************************************************/
    for (usi=0; usi < lpVBSHdr->ulIdxTot; usi++) {
        if (lpXfrRec->ulVoxOff) ulXfrCnt += CopSrcVox (sSrcHdl, sDstHdl, 
            lpWrkBuf, usBufSiz, &lpXfrRec->ulVoxOff, &lpXfrRec->ulVoxLen);
        if (lpXfrRec->ulTxtOff) ulXfrCnt += CopSrcTxt (sSrcHdl, sDstHdl, 
            lpWrkBuf, usBufSiz, &lpXfrRec->ulTxtOff);
        if (lpXfrRec->ulVoxOff || lpXfrRec->ulTxtOff) lpVBSHdr->ulIdxUse++;
        if (fpLngPolPrc && !fpLngPolPrc (FIOPOLCNT,  ulXfrCnt, ulPolDat)) 
            return ((DWORD) -1L);
        lpXfrRec++;
    }        
    if (fpLngPolPrc) fpLngPolPrc (FIOPOLEND,  ulXfrCnt, ulPolDat);
    lpVBSHdr->ulBytUse = ulXfrCnt;

    /********************************************************************/
    /* Update destination file header & index records                   */
    /********************************************************************/
    if ((-1L == FilSetPos (sDstHdl, 0, SEEK_SET)) 
      || (-1L == Wr_FilFwd (sDstHdl, lpVBSHdr, sizeof (VBSHDR), FIOENCNON, &uiErrCod)) 
      || (-1L == Wr_FilFwd (sDstHdl, lpIdxRec, (WORD) (lpVBSHdr->ulIdxTot * sizeof (VBIREC)), 
      FIOENCNON, &uiErrCod))) return ((DWORD) -1L);

    /********************************************************************/
    /********************************************************************/
    return (ulXfrCnt);
}

DWORD   CopSrcVox (short sSrcHdl, short sDstHdl, LPSTR lpWrkBuf, WORD usBufSiz,
        DWORD FAR *pulVoxOff, DWORD FAR *pulVoxLen)
{
    unsigned    uiErrCod;    

    /********************************************************************/
    /* Copy Vox portion of file                                         */
    /********************************************************************/
    if ( (-1L != FilSetPos (sSrcHdl, *pulVoxOff, SEEK_SET))
      && (-1L != (*pulVoxOff = FilGetPos (sDstHdl)))
      && (-1L != (*pulVoxLen = FilCop (sSrcHdl, sDstHdl, lpWrkBuf, 
      usBufSiz, *pulVoxLen, FIOENCNON, &uiErrCod, NULL, 0L)))) {
        if (!*pulVoxLen) *pulVoxOff = 0L;
    }
    else *pulVoxOff = *pulVoxLen = 0L;

    /********************************************************************/
    /********************************************************************/
    return (*pulVoxLen);

}

DWORD   CopSrcTxt (short sSrcHdl, short sDstHdl, LPSTR lpWrkBuf, WORD usBufSiz,
        DWORD FAR *pulTxtOff)
{
    unsigned    uiErrCod;    
    WORD        usTxtLen;

    /********************************************************************/
    /* Copy Text portion of file                                        */
    /********************************************************************/
    if ( (-1L != FilSetPos (sSrcHdl, *pulTxtOff, SEEK_SET))
      && (-1L != (*pulTxtOff = FilGetPos (sDstHdl)))
      && (-1  != (usTxtLen = Rd_FilFwd (sSrcHdl, lpWrkBuf, 
      min (usBufSiz - 1, VBSTXTMAX - 1), FIOENCNON, &uiErrCod)))) {
        lpWrkBuf[usTxtLen] = '\0';
        usTxtLen = Wr_FilFwd (sDstHdl, lpWrkBuf, _fstrlen (lpWrkBuf) + 1, 
            FIOENCNON, &uiErrCod);
        if ((-1 == usTxtLen) || (0 == usTxtLen)) *pulTxtOff = 0L;
    }                
    else *pulTxtOff = usTxtLen = 0;

    /********************************************************************/
    /********************************************************************/
    return ((DWORD) usTxtLen);

}

