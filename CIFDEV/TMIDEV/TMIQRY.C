/************************************************************************/
/* Telco Media Query: TMIQry.c                          V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */

#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  TMIGLO  TMIGlo;                 /* Generic TMI Lib Globals      */

/************************************************************************/
/************************************************************************/
TMIPRO  FAR PASCAL  TMIDigEnu (TMIPRO usTMIPro, LPSTR szDesStr, WORD usMaxLen)
{
    TMIPRO  usNxtPro = TMIUNKPRO;

    /********************************************************************/
    /* Isolate the Device ID portion of the Protocol Word               */
    /********************************************************************/
    usTMIPro = TMIDEV_ID(usTMIPro);

    /********************************************************************/
    /********************************************************************/
#if ((defined (BCM))) /**************************************************/
    if (usTMIPro < TMIBCMPRO) {
        usNxtPro = TMIBCMPRO;
        MsgLodStr (TMIGlo.hLibIns, SI_TMIBCMPRO, szDesStr, usMaxLen);
    }
#endif /*****************************************************************/
#if ((defined (DLG))) /**************************************************/
    if (usTMIPro < TMIDLGPRO) {
        usNxtPro = TMIDLGPRO;
        MsgLodStr (TMIGlo.hLibIns, SI_TMIDLGPRO, szDesStr, usMaxLen);
    }
#endif /*****************************************************************/
#if ((defined (NWV))) /**************************************************/
    if (usTMIPro < TMINWVPRO) {
        usNxtPro = TMINWVPRO;
        MsgLodStr (TMIGlo.hLibIns, SI_TMINWVPRO, szDesStr, usMaxLen);
    }
#endif /*****************************************************************/
#if ((defined (RTX))) /**************************************************/
    if (usTMIPro < TMIRTXPRO) {
        usNxtPro = TMIRTXPRO;
        MsgLodStr (TMIGlo.hLibIns, SI_TMIRTXPRO, szDesStr, usMaxLen);
    }
#endif /*****************************************************************/
    return (usNxtPro);
}

PCMTYP  FAR PASCAL  TMIPCMEnu (TMIPRO usTMIPro, PCMTYP usPCMTyp)
{
    switch (TMIDEV_ID(usTMIPro)) {
        case TMIDLGPRO:
            if (usPCMTyp < DLGPCM004) return (DLGPCM004);
            if (usPCMTyp < DLGPCM008) return (DLGPCM008);
//Future
//if (usPCMTyp < G11PCMI08) return (G11PCMI08);
            break;
        case TMINWVPRO:
            if (usPCMTyp < NWVPCM001) return (NWVPCM001);
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD    FAR PASCAL  TMIChnEnu (TMIPRO usTMIPro, PCMTYP usPCMTyp, WORD usChnCnt)
{
    switch (TMIDEV_ID(usTMIPro)) {
        case TMIDLGPRO:
            if (usChnCnt < 1) return (1);
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (0);
}

DWORD   FAR PASCAL  TMIFrqEnu (TMIPRO usTMIPro, PCMTYP usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq)
{
    switch (TMIDEV_ID(usTMIPro)) {
        case TMIDLGPRO:
            if (ulSmpFrq < 6000L) return (6000L);
            if (ulSmpFrq < 6053L) return (6053L);
            if (ulSmpFrq < 8000L) return (8000L);
            break;
        case TMINWVPRO:
            if (ulSmpFrq < 16000L) return (16000L);
            if (ulSmpFrq < 24000L) return (24000L);
            if (ulSmpFrq < 32000L) return (32000L);
            break;
    }
    return (0L);
}

DWORD FAR PASCAL TMICapQry (TMIPRO usTMIPro, DWORD ulCapTyp, DWORD ulRsv001)
{
    switch (TMIDEV_ID(usTMIPro)) {
        case TMIDLGPRO:
            switch (ulCapTyp) {
                case PRFPCMQRY: return (DLGPCM004);     /* Prf PCM typ  */
                case PRFCHNQRY: return (1L);            /* Prf Chn cnt  */
                case PRFFRQQRY: return (6000L);         /* Prf smp frq  */
                case DYNPCMQRY: return (TRUE);          /* Dyn smp frq  */
                case DYNCHNQRY: return (TRUE);          /* Dyn smp frq  */
                case DYNFRQQRY: return (TRUE);          /* Dyn smp frq  */
            }
            break;
        case TMINWVPRO:
            switch (ulCapTyp) {
                case PRFPCMQRY: return (NWVPCM001);     /* Prf PCM typ  */
                case PRFCHNQRY: return (1L);            /* Prf Chn cnt  */
                case PRFFRQQRY: return (32000L);        /* Prf smp frq  */
                case DYNPCMQRY: return (FALSE);         /* Dyn smp frq  */
                case DYNCHNQRY: return (FALSE);         /* Dyn smp frq  */
                case DYNFRQQRY: return (FALSE);         /* Dyn smp frq  */
            }
            break;
    }
    return (0L);
}
