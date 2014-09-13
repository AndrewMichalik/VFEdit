/************************************************************************/
/* Generic Amplitude Display Support: GenAmp.c          V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "genamp.h"                     /* Amplitude Display defs       */
#include "ampsup.h"                     /* Amplitude Display supp defs  */
#include "ampmsg.h"                     /* Amplitude Display msg defs   */
                                                                        
/************************************************************************/
/*                      Global variables                                */
/************************************************************************/
AMPGLO AmpGlo = {                       /* Amp Display Lib Globals      */
    SI_AMPLIBNAM,                       /* Library name                 */
    {'0','0','0','0','0','0','0','0'},  /* Operating/Demo Only Key      */
    {'1','0','0','0'},                  /* Op/Demo sequence number      */
    RGB (0, 0, 255),                    /* Amp graph RGB value          */
    RGB (96, 96, 96),                   /* Amp graticule RGB value      */
    RGB (255, 0, 0),                    /* Selection box RGB value      */
    RGB (255, 0, 0),                    /* Selection region RGB value   */
    RGB (255, 0, 0),                    /* Selection overview RGB value */
    RGB (255, 0, 0),                    /* Position at point RGB value */
    RGB (128, 128, 128),                /* Rec box shaded RGB value     */
    RGB (255, 255, 255),                /* Rec box light  RGB value     */
    RGB (255, 255, 255),                /* Overview shading RGB value   */
    FNTSIZDEF,                          /* Default fixed font pt size   */
    AMPDECPRC,                          /* Numeric decimal precision    */
    NULL,                               /* Global instance handle       */
    NULL,                               /* Amp graph pen                */
    NULL,                               /* Amp graticule pen            */
    NULL,                               /* Selection box pen            */
    NULL,                               /* Selection region pen         */
    NULL,                               /* Selection overview pen       */
    NULL,                               /* Position at point pen        */
    NULL,                               /* Recessed box shaded pen      */
    NULL,                               /* Recessed box light  pen      */
    NULL,                               /* Overview shading pen         */
    NULL,                               /* Position at point brush      */
    NULL,                               /* Overview shading brush       */
};

/************************************************************************/
/************************************************************************/
int FAR PASCAL LibMain (HANDLE hLibIns, WORD usDatSeg, WORD usHeapSz,
               LPSTR lpCmdLin)
{

    /********************************************************************/
    /********************************************************************/
    if (usHeapSz != 0) UnlockData(0);
    AmpGlo.hLibIns = hLibIns;

    /********************************************************************/
    /********************************************************************/
    AmpResIni (AmpGlo.hLibIns);

    /********************************************************************/
    /********************************************************************/
    return (1);

}

/************************************************************************/
/************************************************************************/
int FAR PASCAL WEP (int nParam)
{

    /********************************************************************/
    /********************************************************************/
    AmpResTrm (AmpGlo.hLibIns);

    /********************************************************************/
    /********************************************************************/
    return (1);

}

WORD FAR PASCAL AmpDLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{

    /********************************************************************/
    /********************************************************************/
    if (usReqTyp == 0) {
        // Check for accelerator key
        return (0);
    }

    /********************************************************************/
    /********************************************************************/
    AmpResTrm (AmpGlo.hLibIns);
    AmpGlo.ulGphClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_AMPGPHCLR, AmpGlo.ulGphClr);
    AmpGlo.ulGraClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_AMPGRACLR, AmpGlo.ulGraClr);
    AmpGlo.ulSBxClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_SELBOXCLR, AmpGlo.ulSBxClr);
    AmpGlo.ulSRgClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_SELREGCLR, AmpGlo.ulSRgClr);
    AmpGlo.ulSOvClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_SELOVRCLR, AmpGlo.ulSOvClr);
    AmpGlo.ulPosClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_AT_POSCLR, AmpGlo.ulPosClr);
    AmpGlo.ulShdClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_RECSHDCLR, AmpGlo.ulShdClr);
    AmpGlo.ulLgtClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_RECLGTCLR, AmpGlo.ulLgtClr);
    AmpGlo.ulOvrClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_OVRFILCLR, AmpGlo.ulOvrClr);
    AmpGlo.usFntSiz = (WORD) GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_FNTDEFSIZ, AmpGlo.usFntSiz);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL AmpSupVer ()
{
    /********************************************************************/
    /********************************************************************/
    return (AMPVERNUM);
}

//WORD FAR PASCAL AmpLodStr (WORD usMsgSID, LPSTR szMsgTxt, WORD usMaxLen)
//{
//
//    /********************************************************************/
//    /* Retrieve a Amplitude Display specific message                      */
//    /********************************************************************/
//    if (usMsgSID > AMPLSTMSG) return (0);
//    return (LoadString (AmpGlo.hLibIns, usMsgSID, szMsgTxt, usMaxLen));
//
//}

/************************************************************************/
/************************************************************************/
WORD    AmpResIni (HANDLE hLibIns)
{
    /********************************************************************/
    /********************************************************************/
    AmpGlo.hGphPen = CreatePen (PS_SOLID, 0, (DWORD) AmpGlo.ulGphClr);
    AmpGlo.hGraPen = CreatePen (PS_SOLID, 0, AmpGlo.ulGraClr);
    AmpGlo.hSBxPen = CreatePen (PS_DASHDOT, 1, AmpGlo.ulSBxClr);
    AmpGlo.hSRgPen = CreatePen (PS_SOLID, 0, AmpGlo.ulSRgClr);
    AmpGlo.hSOvPen = CreatePen (PS_SOLID, 0, AmpGlo.ulSOvClr);
    AmpGlo.hPosPen = CreatePen (PS_SOLID, 0, AmpGlo.ulPosClr);
    AmpGlo.hShdPen = CreatePen (PS_SOLID, 0, AmpGlo.ulShdClr);
    AmpGlo.hLgtPen = CreatePen (PS_SOLID, 0, AmpGlo.ulLgtClr);
    AmpGlo.hOvrPen = CreatePen (PS_SOLID, 1, AmpGlo.ulOvrClr);
    AmpGlo.hPosBsh = CreateSolidBrush (AmpGlo.ulPosClr);
    AmpGlo.hOvrBsh = CreateSolidBrush (AmpGlo.ulOvrClr);

    /********************************************************************/
    /********************************************************************/
    return (0);
}

WORD    AmpResTrm (HANDLE hLibIns)
{

    /********************************************************************/
    /********************************************************************/
    if (NULL != AmpGlo.hGphPen) DeleteObject (AmpGlo.hGphPen);
    if (NULL != AmpGlo.hGraPen) DeleteObject (AmpGlo.hGraPen);
    if (NULL != AmpGlo.hSBxPen) DeleteObject (AmpGlo.hSBxPen);
    if (NULL != AmpGlo.hSRgPen) DeleteObject (AmpGlo.hSRgPen);
    if (NULL != AmpGlo.hSOvPen) DeleteObject (AmpGlo.hSOvPen);
    if (NULL != AmpGlo.hPosPen) DeleteObject (AmpGlo.hPosPen);
    if (NULL != AmpGlo.hShdPen) DeleteObject (AmpGlo.hShdPen);
    if (NULL != AmpGlo.hLgtPen) DeleteObject (AmpGlo.hLgtPen);
    if (NULL != AmpGlo.hOvrPen) DeleteObject (AmpGlo.hOvrPen);
    if (NULL != AmpGlo.hPosBsh) DeleteObject (AmpGlo.hPosBsh);
    if (NULL != AmpGlo.hOvrBsh) DeleteObject (AmpGlo.hOvrBsh);

    /********************************************************************/
    /********************************************************************/
    return (0);
}
