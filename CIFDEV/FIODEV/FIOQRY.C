/************************************************************************/
/* File I/O Query: FIOQry.c                             V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
FILFMT  FAR PASCAL  FIOOpnEnu (FILFMT usFilFmt)
{
#if ((defined (DLG) || defined (RTX)))    /******************************/
    if (ALLPURFMT > usFilFmt) return (ALLPURFMT);
    if (VBSIDXFMT > usFilFmt) return (VBSIDXFMT);
    if (WAVHDRFMT > usFilFmt) return (WAVHDRFMT);
#endif /*****************************************************************/

#if (defined (NWV)) /****************************************************/
    if (ALLPURFMT > usFilFmt) return (ALLPURFMT);
    if (VBSIDXFMT > usFilFmt) return (VBSIDXFMT);
    if (WAVHDRFMT > usFilFmt) return (WAVHDRFMT);
#endif /*****************************************************************/

    /********************************************************************/
    /********************************************************************/
    return (0);
}

FILFMT  FAR PASCAL  FIOIXPEnu (FILFMT usFilFmt)
{
    if (ALLPURFMT > usFilFmt) return (ALLPURFMT);
    return (0);
}

ENUPCM  FAR PASCAL  FIOPCMEnu (FILFMT usFilFmt, ENUPCM usPCMTyp)
{
    return (0);
}

WORD    FAR PASCAL  FIOChnEnu (FILFMT usFilFmt, WORD usChnCnt)
{
    return (0);
}

DWORD   FAR PASCAL  FIOFrqEnu (FILFMT usFilFmt, DWORD ulSmpFrq)
{
    return (0L);
}

LPSTR FAR PASCAL FIODesQry (FILFMT usFilFmt, LPSTR szMsgTxt, WORD usMaxLen)
{

    /********************************************************************/
    /********************************************************************/
    if (!usMaxLen) return (szMsgTxt);
    *szMsgTxt = '\0';

    /********************************************************************/
    /********************************************************************/
    switch (usFilFmt) {
        case ALLPURFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILFMTPUR, szMsgTxt, usMaxLen);
            break;
        case PL2HDRFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILFMTPL2, szMsgTxt, usMaxLen);
            break;
        case VBSIDXFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILFMTVBS, szMsgTxt, usMaxLen);
            break;
        case WAVHDRFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILFMTWAV, szMsgTxt, usMaxLen);
            break;
        default:
            MsgLodStr (FIOGlo.hLibIns, SI_FILFMTUNK, szMsgTxt, usMaxLen);
    }
    return (szMsgTxt);

}  

LPSTR FAR PASCAL FIOExtQry (FILFMT usFilFmt, LPSTR szMsgTxt, WORD usMaxLen)
{

    *szMsgTxt = '\0';

    /********************************************************************/
    /********************************************************************/
    switch (usFilFmt) {
        case ALLPURFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILEXTPUR, szMsgTxt, usMaxLen);
            break;
        case PL2HDRFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILEXTPL2, szMsgTxt, usMaxLen);
            break;
        case VBSIDXFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILEXTVBS, szMsgTxt, usMaxLen);
            break;
        case WAVHDRFMT:
            MsgLodStr (FIOGlo.hLibIns, SI_FILEXTWAV, szMsgTxt, usMaxLen);
            break;
        default:
            MsgLodStr (FIOGlo.hLibIns, SI_FILEXTUNK, szMsgTxt, usMaxLen);
    }
    return (szMsgTxt);

}  

DWORD FAR PASCAL FIOCapQry (FIOQRY usFilFmt, DWORD ulCapTyp, DWORD ulRsv001)
{

    /********************************************************************/
    /********************************************************************/
    if (usFilFmt >= MAXFILFMT) usFilFmt = 0;

    /********************************************************************/
    /* Return defaults for usFilFmt == 0                                */
    /********************************************************************/
    if (!usFilFmt) switch (ulCapTyp) {
        case FIODEFQRY: return (ALLPURFMT);             /* Def fil fmt  */
        case PCMLCKQRY: return (FALSE);                 /* Def lck off  */
        case FRQLCKQRY: return (FALSE);                 /* Def lck off  */
    }
    else switch (ulCapTyp) {
        case PCMLCKQRY: return (FALSE);                 /* Def lck off  */
        case FRQLCKQRY: return (FALSE);                 /* Def lck off  */
    }

    /********************************************************************/
    /********************************************************************/
    return ((DWORD) -1L);                           /* Unknown query    */

}

