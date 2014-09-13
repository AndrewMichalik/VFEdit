/************************************************************************/
/* Generic File I/O Support: GenFIO.c                   V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "fiomsg.h"                     /* File I/O support msg defs    */

/************************************************************************/
/*                      Global variables                                */
/************************************************************************/
FIOGLO FIOGlo = {                       /* File I/O Library Globals     */
    SI_FIOLIBNAM,                       /* Library name                 */
    {'0','0','0','0','0','0','0','0'},  /* Operating/Demo Only Key      */
    {'1','0','0','0'},                  /* Op/Demo sequence number      */
    RGB (192, 192, 192),                /* Dlg box background RGB value */
    NULL,                               /* Global instance handle       */
    NULL,                               /* Dlg box background brush     */
};

W32GLO W32Glo = {                       /* File I/O Library Globals     */
    NULL,                               /* KERNEL lib handle            */
    NULL,                               /* LoadLibraryEx32W  address    */
    NULL,                               /* GetProcAddress32W address    */
    NULL,                               /* _CallProcEx32W    address    */
    NULL,                               /* FreeLibrary32W    address    */
    0L,                                 /* KERNEL32 lib handle          */
};

/************************************************************************/
/************************************************************************/
int FAR PASCAL LibMain (HANDLE hLibIns, WORD usDatSeg, WORD usHeapSz,
               LPSTR lpCmdLin)
{

    /********************************************************************/
    /********************************************************************/
    if (usHeapSz != 0) UnlockData(0);
    FIOGlo.hLibIns = hLibIns;

    /********************************************************************/
    /********************************************************************/
    FIOResIni (FIOGlo.hLibIns);

    /********************************************************************/
    /********************************************************************/
    return (1);

}

int FAR PASCAL WEP (int nParam)
{

    /********************************************************************/
    /********************************************************************/
    FIOResTrm (FIOGlo.hLibIns);
    return (1);

}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL FIODLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{
    /********************************************************************/
    /********************************************************************/
    if (usReqTyp == 0) {
        // Check for accelerator key
    }

return (0);

    /********************************************************************/
    /********************************************************************/
    FIOResTrm (FIOGlo.hLibIns);
    FIOGlo.ulDBxClr = GetPrfLng ((LPSTR) ulPrm001, (LPSTR) ulPrm002, 
        SI_DBXBKGCLR, FIOGlo.ulDBxClr);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD FAR PASCAL FIOSupVer ()
{
    /********************************************************************/
    /********************************************************************/
    return (FIOVERNUM);
}

/************************************************************************/
/************************************************************************/
WORD    FIOResIni (HANDLE hLibIns)
{
    /********************************************************************/
    /* Initialize Graphics Resources                                    */
    /********************************************************************/
    MsgDspPrc = FIODspPrc;              /* Re-assignable msg output     */
    FIOGlo.hDBxBsh = CreateSolidBrush (FIOGlo.ulDBxClr);

    /********************************************************************/
    /* Initialize Win32 Resources                                       */
    /********************************************************************/
    if ((W32Glo.hKrnW16 = LoadLibrary ("KERNEL")) < 32) W32Glo.hKrnW16 = NULL;
    else {
        /****************************************************************/
        /* Get address of 32 bit extension functions                    */
        /****************************************************************/
        W32Glo.LoadLibraryEx32W  = (LPVOID) GetProcAddress (W32Glo.hKrnW16, "LoadLibraryEx32W"); 
        W32Glo.GetProcAddress32W = (LPVOID) GetProcAddress (W32Glo.hKrnW16, "GetProcAddress32W");
        W32Glo._CallProcEx32W    = (LPVOID) GetProcAddress (W32Glo.hKrnW16, "_CallProcEx32W");
        W32Glo.FreeLibrary32W    = (LPVOID) GetProcAddress (W32Glo.hKrnW16, "FreeLibrary32W");

        /****************************************************************/
        /* Get address of 32 bit kernel                                 */
        /****************************************************************/
        if (W32Glo.LoadLibraryEx32W && W32Glo.GetProcAddress32W && 
            W32Glo._CallProcEx32W   && W32Glo.FreeLibrary32W) {  
            W32Glo.hKrnW32 = W32Glo.LoadLibraryEx32W ((LPCSTR) "KERNEL32.DLL",
                (DWORD) NULL, (DWORD) NULL);
        }

        /****************************************************************/
        /* Disable all procedures if any one or kernel unavailable      */
        /****************************************************************/
        if (!W32Glo.hKrnW32) {
            W32Glo.LoadLibraryEx32W = NULL; 
            W32Glo.GetProcAddress32W = NULL;
            W32Glo._CallProcEx32W = NULL;   
            W32Glo.FreeLibrary32W = NULL;   
        }
    }
    
    /********************************************************************/
    /********************************************************************/
    return (0);
}

WORD    FIOResTrm (HANDLE hLibIns)
{
    /********************************************************************/
    /* Release Graphics Resources                                       */
    /********************************************************************/
    if (NULL != FIOGlo.hDBxBsh) DeleteObject (FIOGlo.hDBxBsh);

    /********************************************************************/
    /* Release Win32 Resources                                          */
    /********************************************************************/
    if (W32Glo.hKrnW32) W32Glo.FreeLibrary32W (W32Glo.hKrnW32);
    if (W32Glo.hKrnW16) FreeLibrary (W32Glo.hKrnW16);

    /********************************************************************/
    /********************************************************************/
    return (0);
}
