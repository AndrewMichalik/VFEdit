/************************************************************************/
/* File I/O OFS Functions: FIOOFS.c                     V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "filutl.h"                     /* File utilities definitions   */

#include <string.h>                     /* String manipulation funcs    */
#include <sys\stat.h>                   /* File status types            */
#include <stdio.h>                      /* Standard I/O                 */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
HFILE  FAR PASCAL FIOOFSOpn (LPCSTR szFilNam, LPOFSTRUCT_V pofFilOFS, 
                  WORD usOpnFlg)
{
    return (OpenFileEx_V (szFilNam, pofFilOFS, usOpnFlg));
}

//HFILE  FAR PASCAL FIOOFSOpn (LPCSTR szFilNam, LPOFSTRUCT_V pofFilOFS, 
//                  WORD usOpnFlg)
//{
//    HFILE   hFilHdl;
//    HANDLE  hKrnLib;
//    static  HFILE (FAR PASCAL *lpKrnFnc) () = NULL;
//
//    /********************************************************************/
//    /* Store file open function for subsequent use                      */
//    /* Use OpenFile() if OpenFileEx() is not available.                 */
//    /********************************************************************/
//    if ((NULL == lpKrnFnc) && 
//        (((hKrnLib = LoadLibrary ("KERNEL")) < 32) || 
//        (NULL == (lpKrnFnc = GetProcAddress (hKrnLib, "OpenFileEx"))))) 
//        lpKrnFnc = OpenFile;
//
//    /********************************************************************/
//    /* If using OpenFile, compress out extra 2nd length byte            */
//    /* Note: Low|High byte ordering of nBytes permits initial overwrite */
//    /********************************************************************/
//    if (lpKrnFnc == OpenFile) {
//        LPBYTE  lpFilOFS = (LPBYTE) pofFilOFS;
//        _fmemmove (&(lpFilOFS[1]), &(lpFilOFS[2]), sizeof (OFSTRUCT_V) - 2);    
//        hFilHdl = OpenFile (szFilNam, (LPOFSTRUCT) pofFilOFS, usOpnFlg);       
//        _fmemmove (&(lpFilOFS[2]), &(lpFilOFS[1]), sizeof (OFSTRUCT_V) - 2);    
//        lpFilOFS[1] = 0;
//        return (hFilHdl);
//    }
//    return (lpKrnFnc (szFilNam, pofFilOFS, usOpnFlg));
//}

FIORET FAR PASCAL FIOOFSApp (LPOFSTRUCT_V pofSrcFil, LPOFSTRUCT_V pofDstFil, 
                  DWORD ulFilPos, DWORD ulReqCnt, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short   sSrcHdl;
    short   sDstHdl;

    /********************************************************************/
    /* SI_BADOPNSRC: Cannot Open Source File                            */
    /* SI_BADOPNDST: Cannot Open Output File                            */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETERR);
    }
    FilSetPos (sSrcHdl, ulFilPos, SEEK_SET);

    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }
    FilSetPos (sDstHdl, 0L, SEEK_END);
  
    if (-1L == FIOFilCop (sSrcHdl, sDstHdl, ulReqCnt, NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        return (FIORETERR);
    }
  
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

FIORET FAR PASCAL FIOOFSDup (LPOFSTRUCT_V pofSrcFil, LPOFSTRUCT_V pofDstFil, 
        FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short   sSrcHdl;
    short   sDstHdl;

    /********************************************************************/
    /* SI_BADOPNSRC: Cannot Open Source File                            */
    /* SI_BADOPNDST: Cannot Open Output File                            */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofSrcFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETERR);
    }
    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE | OF_CREATE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }
  
    if (-1L == FIOFilDup (sSrcHdl, sDstHdl, NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        return (FIORETERR);
    }
  
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

FIORET FAR PASCAL FIOOFSShf (LPOFSTRUCT_V pofShfFil, DWORD ulShfPnt, 
                long lShfAmt, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short   sSrcHdl;
    short   sDstHdl;

    /********************************************************************/
    /* SI_BADOPNSRC: Cannot Open Source File                            */
    /* SI_BADOPNDST: Cannot Open Output File                            */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofShfFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETERR);
    }
    if (-1 == (sDstHdl = OFSFilOpn (pofShfFil, OF_READWRITE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        return (FIORETERR);
    }

    if (-1L == FIOFilShf (sSrcHdl, sDstHdl, ulShfPnt, lShfAmt, NULL, 
      fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        return (FIORETERR);
    }
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

FIORET FAR PASCAL FIOOFSRep (LPOFSTRUCT_V pofDstFil, DWORD FAR *pulCutPos, 
        DWORD FAR *pulCutLen, LPOFSTRUCT_V pofCutFil, DWORD ulPstPos, 
        DWORD ulPstLen, LPOFSTRUCT_V pofPstFil, FIOPOLPRC fpLngPolPrc, DWORD ulPolDat)
{
    short   sSrcHdl;
    short   sDstHdl;
    DWORD   ulDstLen;
    DWORD   ulSrcLen;

    /********************************************************************/
    /* Insure that replace position and cut length are within bounds    */
    /********************************************************************/
    ulDstLen = FIOOFSLen (pofDstFil);
    *pulCutPos = min ((DWORD) ulDstLen, *pulCutPos);
    *pulCutLen = min (*pulCutLen, ulDstLen - *pulCutPos);

    /********************************************************************/
    /* Append cut data to cut file                                      */
    /********************************************************************/
    if (NULL != pofCutFil) {
        if (FIORETSUC != FIOOFSApp (pofDstFil, pofCutFil, *pulCutPos,
          *pulCutLen, fpLngPolPrc, ulPolDat)) return (FIORETERR);
    }

    /********************************************************************/
    /* Insure that insert position and length are within bounds         */
    /********************************************************************/
    ulSrcLen = FIOOFSLen (pofPstFil);
    ulPstPos = min (ulSrcLen, ulPstPos);
    ulPstLen = min (ulPstLen, ulSrcLen - ulPstPos);

    /********************************************************************/
    /* Adjust file size to add/remove space                             */
    /********************************************************************/
    if ((*pulCutLen != ulPstLen) && (FIORETSUC != FIOOFSShf (pofDstFil, 
        *pulCutPos + *pulCutLen, (long) ulPstLen - (long) *pulCutLen, 
        fpLngPolPrc, ulPolDat))) return (FIORETBAD);
    if (!ulPstLen) return (FIORETSUC);          /* No insert, done!     */

    /********************************************************************/
    /* Prepare source and destination file positions                    */
    /********************************************************************/
    if (-1 == (sSrcHdl = OFSFilOpn (pofPstFil, OF_READ, SI_BADOPNSRC))) {
        return (FIORETBAD);
    }
    FilSetPos (sSrcHdl, ulPstPos, SEEK_SET);

    if (-1 == (sDstHdl = OFSFilOpn (pofDstFil, OF_READWRITE, SI_BADOPNDST))) {
        FilHdlCls (sSrcHdl);
        return (FIORETBAD);
    }
    FilSetPos (sDstHdl, *pulCutPos, SEEK_SET);

    /********************************************************************/
    /* Copy insert data to file                                         */
    /********************************************************************/
    if (-1L == FIOFilCop (sSrcHdl, sDstHdl, ulPstLen, NULL, fpLngPolPrc, ulPolDat)) {
        FilHdlCls (sSrcHdl);
        FilHdlCls (sDstHdl);
        return (FIORETBAD);
    }
  
    FilHdlCls (sSrcHdl);
    FilHdlCls (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);

}

DWORD FAR PASCAL FIOOFSLen (LPOFSTRUCT_V pofFilOFS)
{
    struct  _stat   ssStaBlk;
    char    szFilNam[FIOMAXPTH];

    /********************************************************************/
    /********************************************************************/
    if (NULL == pofFilOFS) return (0L);

    /********************************************************************/
    /* Convert to short file name and get status                        */
    /********************************************************************/
    FIOLngCvt (pofFilOFS->szPathName, szFilNam, FIOMAXPTH);
    if (FilGetSta (szFilNam, &ssStaBlk)) return (0L);
    return (ssStaBlk.st_size);
}

FIORET FAR PASCAL FIOOFSRen (LPOFSTRUCT_V pofFilOFS, LPCSTR szDstFil, 
        WORD usMsgSID)
{
    if (!FIOLngRen (pofFilOFS->szPathName, szDstFil)) return (FIORETBAD);
    return (FIORETSUC);
}

FIORET FAR PASCAL FIOOFSDel (LPCSTR szLngFil, WORD usMsgSID)
{
    static  char    szFilNam[FIOMAXPTH];

    /********************************************************************/
    /* Convert to short file name and delete                            */
    /********************************************************************/
    FIOLngCvt (szLngFil, szFilNam, FIOMAXPTH);
    if (!remove (szFilNam)) return (FIORETBAD);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);
}

FIORET FAR PASCAL FIOOFSCvt (LPCSTR szLngNam, LPSTR szShtNam, DWORD ulShtLen)
{
    /********************************************************************/
    /* Convert to short file name and return                            */
    /********************************************************************/
    if (0 == FIOLngCvt (szLngNam, szShtNam, FIOMAXPTH)) return (FIORETBAD);

    /********************************************************************/
    /********************************************************************/
    return (FIORETSUC);
}

/************************************************************************/
/* OFS Support Functions                                                */
/************************************************************************/
short FAR PASCAL OFSFilOpn (LPOFSTRUCT_V pofFilOFS, WORD usOpnFlg, WORD usMsgSID)
{
    short   sFilHdl;

    /********************************************************************/
    /* Open/ Create file, if error display message usMsgSID             */
    /* Note: OF_CREATE creates & truncates the file                     */
    /********************************************************************/
    if (OF_CREATE & usOpnFlg) {
        if (FIOLngCre (pofFilOFS->szPathName, S_IREAD | S_IWRITE)) {
            if (usMsgSID) MsgDspRes (FIOGlo.hLibIns, 0, usMsgSID);
            return (-1);
        }
        sFilHdl = OFSFilOpn (pofFilOFS, (~OF_CREATE) & usOpnFlg, usMsgSID);
    } else {
        char    szFilNam[FIOMAXPTH];
        /****************************************************************/
        /* Convert to short file name                                   */
        /****************************************************************/
        FIOLngCvt (pofFilOFS->szPathName, szFilNam, FIOMAXPTH);
        if (-1 == (sFilHdl = FilHdlOpn (szFilNam, usOpnFlg))) {
            if (usMsgSID) MsgDspRes (FIOGlo.hLibIns, 0, usMsgSID);
        }
    }
    return (sFilHdl);

}

