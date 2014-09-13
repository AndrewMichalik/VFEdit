/************************************************************************/
/* File Find Functions: FF_W32.c                        V3.00  07/15/94 */
/* Copyright (c) 1987-1997 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "filutl.h"                     /* File utilities definitions   */

#include <string.h>                     /* String manipulation funcs    */
#include <stdio.h>                      /* Standard I/O                 */
#include <dos.h>                        /* DOS low-level routines       */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  W32GLO  W32Glo;                 /* Win 32 Library Globals       */

/************************************************************************/
/************************************************************************/
#define _MAX_PATH    260                /* max. length of full pathname */

/************************************************************************/
/*                  Win32 File Support Operations                       */
/************************************************************************/
DWORD FAR PASCAL LoadLibraryEx32W (LPCSTR lpszLibFile, DWORD hFile, DWORD dwFlags);
DWORD FAR PASCAL GetProcAddress32W (DWORD hModule, LPCSTR lpszProc);
DWORD FAR _cdecl _CallProcEx32W (DWORD, DWORD, DWORD, ... );
DWORD FAR PASCAL FreeLibrary32W (DWORD hLibModule);

/************************************************************************/
/*          Library model independant file find functions               */
/************************************************************************/
unsigned __cdecl l_dos_findfirst (const char FAR *filename, unsigned attrib,
                    struct _find_t FAR *fileinfo)
{
    static  struct _find_t  fiLocInf;
    static  char            szLocNam[_MAX_PATH];
    unsigned                uiRetCod;

    /********************************************************************/
    /********************************************************************/
    _fstrncpy (szLocNam, filename, _MAX_PATH);
    _fmemcpy  (&fiLocInf, fileinfo, sizeof (fiLocInf)); 
    uiRetCod = _dos_findfirst (szLocNam, attrib, &fiLocInf);
    _fmemcpy  (fileinfo, &fiLocInf, sizeof (fiLocInf));
    return (uiRetCod);
}

unsigned __cdecl l_dos_findnext (struct _find_t FAR *fileinfo) 
{
    static  struct _find_t  fiLocInf;
    unsigned                uiRetCod;

    /********************************************************************/
    /********************************************************************/
    _fmemcpy  (&fiLocInf, fileinfo, sizeof (fiLocInf)); 
    uiRetCod = _dos_findnext (&fiLocInf);
    _fmemcpy  (fileinfo, &fiLocInf, sizeof (fiLocInf));
    return (uiRetCod);
}

/************************************************************************/
/************************************************************************/
#include "wownt16.h"                    /* Win on Win 16 bit I/F        */

typedef struct _FILETIME {
    DWORD   dwLowDateTime;
    DWORD   dwHighDateTime;
} FILETIME, *PFILETIME, FAR *LPFILETIME;
typedef struct _WIN32_FIND_DATAA {
    DWORD   dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD   nFileSizeHigh;
    DWORD   nFileSizeLow;
    DWORD   dwReserved0;
    DWORD   dwReserved1;
    char    cFileName[ _MAX_PATH ];
    char    cAlternateFileName[ 14 ];
    BYTE    bShtBlk[64];                /* Added to support short names */
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, FAR *LPWIN32_FIND_DATAA;
typedef struct _SECURITY_ATTRIBUTES { 
    DWORD  nLength; 
    LPVOID lpSecurityDescriptor; 
    DWORD  bInheritHandle; 
} SECURITY_ATTRIBUTES; 

#define FILE_ATTRIBUTE_READONLY         (0x00000001L)  
#define FILE_ATTRIBUTE_HIDDEN           (0x00000002L)  
#define FILE_ATTRIBUTE_SYSTEM           (0x00000004L)  
#define FILE_ATTRIBUTE_DIRECTORY        (0x00000010L)  
#define FILE_ATTRIBUTE_ARCHIVE          (0x00000020L)  
#define FILE_ATTRIBUTE_NORMAL           (0x00000080L)  
#define FILE_ATTRIBUTE_TEMPORARY        (0x00000100L)  
#define FILE_ATTRIBUTE_COMPRESSED       (0x00000800L)  
#define GENERIC_READ                    (0x80000000L)
#define GENERIC_WRITE                   (0x40000000L)
#define GENERIC_EXECUTE                 (0x20000000L)
#define GENERIC_ALL                     (0x10000000L)
#define CREATE_NEW                      1L
#define CREATE_ALWAYS                   2L
#define OPEN_EXISTING                   3L
#define OPEN_ALWAYS                     4L
#define TRUNCATE_EXISTING               5L

#define INVALID_HANDLE_VALUE            ((DWORD) -1L)

DWORD   WINAPI  FindFirstFileA (LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
BOOL    WINAPI  FindNextFileA  (DWORD  hFindFile,  LPWIN32_FIND_DATAA lpFindFileData);
BOOL    WINAPI  FindClose      (DWORD  hFindFile);

DWORD   WINAPI  CreateFileA    (LPCSTR lpFileName, DWORD dwDesiredAccess,    
                                DWORD dwShareMode, LPVOID lpSecurityAttributes,
                                DWORD dwCreationDistribution, DWORD dwFlagsAndAttributes, 
                                DWORD hTemplateFile);
BOOL    WINAPI  CloseHandle    (DWORD hObject);

/************************************************************************/
/************************************************************************/
DWORD FAR PASCAL FIOFndFst (const char FAR *lpFilNam, LPWIN32_FIND_DATAA lpFndDat)
{
    DWORD   ulRetHdl;
    static  FARPROC lpFindFirstFile = NULL;

    /********************************************************************/
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        struct _find_t FAR * lpDOSFnd;
        /****************************************************************/
        /* Allocate memory for DOS find file structure                  */
        /****************************************************************/
        if (NULL == (lpDOSFnd = GloAloLck (GMEM_MOVEABLE, &ulRetHdl, 
            sizeof (struct _find_t)))) {
            return (INVALID_HANDLE_VALUE);
        }
        /****************************************************************/
        /* Find first file                                              */
        /****************************************************************/
        if (0 != l_dos_findfirst (lpFilNam, _A_NORMAL | _A_RDONLY | 
            _A_HIDDEN | _A_SYSTEM | _A_VOLID | _A_SUBDIR | _A_ARCH, lpDOSFnd))    {
            GloUnLRel (ulRetHdl); 
            return (INVALID_HANDLE_VALUE);
        }
        /****************************************************************/
        /* Adjust values to match FILE_ constants                       */
        /****************************************************************/
        if (_A_NORMAL == (lpFndDat->dwFileAttributes = lpDOSFnd->attrib))
            lpFndDat->dwFileAttributes |= FILE_ATTRIBUTE_NORMAL;
        lpFndDat->nFileSizeHigh = 0L;
        lpFndDat->nFileSizeLow  = lpDOSFnd->size;
        _fstrlwr (_fstrcpy (lpFndDat->cFileName, lpDOSFnd->name));
        _fstrlwr (_fstrcpy (lpFndDat->cAlternateFileName, lpDOSFnd->name));
        return (ulRetHdl);
    }

    /********************************************************************/
    /* Get the address of FindFirstFileA in KERNEL32.DLL                */
    /********************************************************************/
    if (!lpFindFirstFile && !(lpFindFirstFile = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "FindFirstFileA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (INVALID_HANDLE_VALUE);
    }

    /********************************************************************/
    /********************************************************************/
    ulRetHdl = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 2L, 0x3L, lpFindFirstFile, 
        lpFilNam, lpFndDat);

    /********************************************************************/
    /* FindFirstFileA() does not copy short name if short name only.    */
    /* If short file name, copy to alternate as well.                   */
    /********************************************************************/
    if ('\0' == *lpFndDat->cAlternateFileName) _fstrncpy (lpFndDat->cAlternateFileName,
        lpFndDat->cFileName, sizeof (lpFndDat->cAlternateFileName));

// Future: Strip off "." and ".." from long file name directory search

    /********************************************************************/
    /********************************************************************/
    return (ulRetHdl);
}

DWORD FAR PASCAL FIOFndNxt (DWORD hFndFil, LPWIN32_FIND_DATAA lpFndDat)
{
    DWORD   ulRetCod;
    static  FARPROC lpFindNextFile = NULL;

    /********************************************************************/
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        struct _find_t FAR * lpDOSFnd;
        /****************************************************************/
        /* Lock memory for DOS find file structure                      */
        /****************************************************************/
        if (NULL == (lpDOSFnd = GloMemLck (hFndFil))) return (FALSE);

        /****************************************************************/
        /* Find next file                                               */
        /****************************************************************/
        if (0 != l_dos_findnext (lpDOSFnd)) return (FALSE);

        /****************************************************************/
        /* Adjust values to match FILE_ constants                       */
        /****************************************************************/
        if (_A_NORMAL == (lpFndDat->dwFileAttributes = lpDOSFnd->attrib))
            lpFndDat->dwFileAttributes |= FILE_ATTRIBUTE_NORMAL;
        lpFndDat->nFileSizeHigh = 0L;
        lpFndDat->nFileSizeLow  = lpDOSFnd->size;
        _fstrlwr (_fstrcpy (lpFndDat->cFileName, lpDOSFnd->name));
        _fstrlwr (_fstrcpy (lpFndDat->cAlternateFileName, lpDOSFnd->name));
        GloMemUnL (hFndFil);
        return (TRUE);
    }

    /********************************************************************/
    /* Get the address of FindNextFileA in KERNEL32.DLL                 */
    /********************************************************************/
    if (!lpFindNextFile && !(lpFindNextFile = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "FindNextFileA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    ulRetCod = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 2L, 0x2L, lpFindNextFile, 
        hFndFil, lpFndDat);

    /********************************************************************/
    /* FindNextFileA() does not copy short name if short name only.     */
    /* If short file name, copy to alternate as well.                   */
    /********************************************************************/
    if ('\0' == *lpFndDat->cAlternateFileName) _fstrncpy (lpFndDat->cAlternateFileName,
         lpFndDat->cFileName, sizeof (lpFndDat->cAlternateFileName));

// Future: Strip off "." and ".." from long file name directory search

    /********************************************************************/
    /********************************************************************/
    return (ulRetCod);
}

DWORD FAR PASCAL FIOFndEnd (DWORD hFndFil)
{
    DWORD   ulRetCod;
    static  FARPROC lpFindClose = NULL;

    /********************************************************************/
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        GloAloRel (hFndFil);
        return (TRUE);
    }

    /********************************************************************/
    /* Get the address of FindClose in KERNEL32.DLL                     */
    /********************************************************************/
    if (!lpFindClose && !(lpFindClose = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "FindClose"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (FALSE);
    }

    /********************************************************************/
    /********************************************************************/
    ulRetCod = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 1L, 0x0L, lpFindClose, 
        hFndFil);

    /********************************************************************/
    /********************************************************************/
    return (ulRetCod);
}

/************************************************************************/
/************************************************************************/
DWORD FAR PASCAL FIOLngCvt (LPCSTR szLngNam, LPSTR szShtNam, DWORD ulShtLen)
{
    static  FARPROC     lpGetShortPathName = NULL;
    DWORD               ulRetCod;

    /********************************************************************/
    /* 16 bit? Return short file name.                                  */
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        _fstrncpy (szShtNam, szLngNam, (WORD) ulShtLen);    
        return (_fstrlen (szShtNam));
    }

    /********************************************************************/
    /* Get the address of GetShortPathNameA in KERNEL32.DLL             */
    /********************************************************************/
    if (!lpGetShortPathName && !(lpGetShortPathName = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "GetShortPathNameA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (0L);
    }

    /********************************************************************/
    /* Get full path for short file name.                               */
    /********************************************************************/
    ulRetCod = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 3L, 0x3L, lpGetShortPathName, 
        szLngNam, szShtNam, ulShtLen);
    if (!ulRetCod) return (0);

    /********************************************************************/
    /********************************************************************/
    return (_fstrlen (szShtNam));
}

DWORD FAR PASCAL FIOLngCre (LPCSTR szFilNam, DWORD ulModFlg)
{
    SECURITY_ATTRIBUTES saSecurityAttributes;
    static  FARPROC     lpCreateFile    = NULL; 
    static  FARPROC     lpCloseHandle   = NULL; 
    DWORD               ulRetHdl;

    /********************************************************************/
    /* 16 bit? Create using short file name.                            */
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        short   sFilHdl;
        if (-1 == (sFilHdl = FilHdlCre (szFilNam, 0, (WORD) ulModFlg)))
            return ((DWORD) -1L);
        _lclose (sFilHdl);
        return (0L);
    }

    /********************************************************************/
    /* Initialize security attributes to "none".                        */
    /********************************************************************/
    saSecurityAttributes.nLength = sizeof (saSecurityAttributes); 
    saSecurityAttributes.lpSecurityDescriptor = NULL; 
    saSecurityAttributes.bInheritHandle = FALSE; 

    /********************************************************************/
    /* Get the address of CreateFileA in KERNEL32.DLL                   */
    /********************************************************************/
    if (!lpCreateFile && !(lpCreateFile = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "CreateFileA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return ((DWORD) -1L);
    }
    if (!lpCloseHandle && !(lpCloseHandle = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "CloseHandle"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return ((DWORD) -1L);
    }

    /********************************************************************/
    /* Create the actual file and close it                              */
    /********************************************************************/
    ulRetHdl = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 7L, 0x49L, lpCreateFile, 
        szFilNam, 0L, 0L, (LPVOID) &saSecurityAttributes, CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, (LPVOID) NULL);
    if (INVALID_HANDLE_VALUE == ulRetHdl) return ((DWORD) -1L);
    ulRetHdl = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 1L, 0x0L, lpCloseHandle, 
        ulRetHdl);

    /********************************************************************/
    /********************************************************************/
    return (0L);
}

DWORD FAR PASCAL FIOLngRen (LPCSTR szSrcFil, LPCSTR szDstFil)
{
    static  FARPROC     lpMoveFile = NULL;
    DWORD               ulRetCod;

    /********************************************************************/
    /* 16 bit? Return short file name.                                  */
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        static  char    szSrcLoc[FIOMAXNAM];
        static  char    szDstLoc[FIOMAXNAM];
        /****************************************************************/
        /* Make a local copy of the file name                           */
        /****************************************************************/
        _fstrncpy (szSrcLoc, szSrcFil, FIOMAXNAM);
        _fstrncpy (szDstLoc, szDstFil, FIOMAXNAM);

        /****************************************************************/
        /* Rename Old to New                                            */
        /****************************************************************/
        if (0 != rename (szSrcLoc, szDstLoc)) return (FALSE);
        return (TRUE);
    }

    /********************************************************************/
    /* Get the address of MoveFileA in KERNEL32.DLL                     */
    /********************************************************************/
    if (!lpMoveFile && !(lpMoveFile = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "MoveFileA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (FALSE);
    }

    /********************************************************************/
    /* Rename using full path and long file name.                       */
    /********************************************************************/
    ulRetCod = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 2L, 0x3L, lpMoveFile, 
        szSrcFil, szDstFil);

    /********************************************************************/
    /* True if successful                                               */
    /********************************************************************/
    return (ulRetCod);
}

/************************************************************************/
/************************************************************************/
HFILE   OpenFile_V (LPCSTR szFilNam, LPOFSTRUCT_V pofFilOFS, UINT uiOpnFlg) 
{
    HFILE   hFilHdl;
    LPBYTE  lpFilOFS = (LPBYTE) pofFilOFS;

    /********************************************************************/
    /* Open using short file name and extended OFSTRUCT                 */
    /********************************************************************/
    _fmemmove (&(lpFilOFS[1]), &(lpFilOFS[2]), sizeof (OFSTRUCT_V) - 2);    
    hFilHdl = OpenFile (szFilNam, (LPOFSTRUCT) pofFilOFS, uiOpnFlg);       
    _fmemmove (&(lpFilOFS[2]), &(lpFilOFS[1]), sizeof (OFSTRUCT_V) - 2);    
    lpFilOFS[1] = 0;
    return (hFilHdl);
}

HFILE   WINAPI OpenFileEx_V (LPCSTR szFilNam, LPOFSTRUCT_V pofFilOFS,
        UINT uiOpnFlg) 
{
    WIN32_FIND_DATAA    fdFndDat;
    static  FARPROC     lpFindFirstFile = NULL;
    DWORD   ulRetHdl;

    /********************************************************************/
    /* 16 bit? Open using short file name.                              */
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        return (OpenFile_V (szFilNam, pofFilOFS, uiOpnFlg));       
    }

    /********************************************************************/
    /* Just filling out OFS?                                            */
    /* Note: FindFirstFile() does not return the full path name of the  */
    /* file. For our purposes, however, using the original filename     */
    /* (see upper level actual flag usage for this routine) will        */
    /* suffice.                                                         */
    /********************************************************************/
    if (OF_PARSE & uiOpnFlg) {
        _fmemset (pofFilOFS, 0, sizeof (*pofFilOFS));
        _fstrncpy (pofFilOFS->szPathName, szFilNam, sizeof (pofFilOFS->szPathName));    
        return (0);
    }

    /********************************************************************/
    /* Use previously specified file name?                              */
    /* Just checking for existence? Don't clear if OF_REOPEN.           */
    /********************************************************************/
    if (OF_REOPEN & uiOpnFlg) {
        szFilNam = pofFilOFS->szPathName;
    }
    else if (OF_EXIST & uiOpnFlg) {
        /****************************************************************/
        /* Update OFS file path name                                    */
        /* Note: FindFirstFile() will search for file, but does         */
        /* not return the full path name.                               */
        /****************************************************************/
        _fmemset (pofFilOFS, 0, sizeof (*pofFilOFS));
        _fstrncpy (pofFilOFS->szPathName, szFilNam, sizeof (pofFilOFS->szPathName));    
    }

    /********************************************************************/
    /* Do we have to create a long file name?                           */
    /********************************************************************/
    if (OF_CREATE & uiOpnFlg) {
        if (-1L == FIOLngCre (szFilNam, 0L)) return (HFILE_ERROR);
    }

    /********************************************************************/
    /* Initialize the FindFile data structure.                          */
    /********************************************************************/
    _fmemset (&fdFndDat, 0, sizeof (fdFndDat));
     fdFndDat.dwFileAttributes |= FILE_ATTRIBUTE_NORMAL;

    /********************************************************************/
    /* Get the address of FindFirstFileA in KERNEL32.DLL                */
    /********************************************************************/
    if (!lpFindFirstFile && !(lpFindFirstFile = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "FindFirstFileA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return ((HFILE) -1);
    }

    /********************************************************************/
    /* Check for existence of the file                                  */
    /********************************************************************/
    ulRetHdl = W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 2L, 0x3L, lpFindFirstFile, 
        szFilNam, (LPWIN32_FIND_DATAA) &fdFndDat);
    if (INVALID_HANDLE_VALUE == ulRetHdl) return ((HFILE) -1);

    /********************************************************************/
    /* No file open - checking for existence? Yes, it exists.           */
    /********************************************************************/
    if (OF_EXIST & uiOpnFlg) return (0);

    /********************************************************************/
    /* Legacy function; not actually used to return file handle         */
    /********************************************************************/
    return ((HFILE) -1);
}

/************************************************************************/
/* Conditional OS functionality support                                 */
/************************************************************************/
DWORD FAR PASCAL FIOOS_Inf (OSVERSIONINFO FAR *lpVerInf) 
{
    static FARPROC  lpGetVersionEx = NULL; 
    OSVERSIONINFO   osVerInf;

    /********************************************************************/
    /* Copy full info if requested; otherwise, just return platform ID  */  
    /********************************************************************/
    if (NULL == lpVerInf) lpVerInf = &osVerInf;

    /********************************************************************/
    /* Initialize for 16 bit as default                                 */
    /********************************************************************/
    _fmemset (lpVerInf, 0, sizeof (*lpVerInf));
    lpVerInf->dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    lpVerInf->dwPlatformId = (DWORD) VER_PLATFORM_WIN16;
    lpVerInf->dwMajorVersion = 3;
    lpVerInf->dwMinorVersion = 0;
    lpVerInf->dwBuildNumber = 0;

    /********************************************************************/
    /* 16 bit?                                                          */
    /********************************************************************/
    if (!W32Glo.hKrnW32) {
        return (lpVerInf->dwPlatformId);
    }

    /********************************************************************/
    /* Get the address of GetVersionExA in KERNEL32.DLL and call        */
    /********************************************************************/
    if (!lpGetVersionEx && !(lpGetVersionEx = (FARPROC) W32Glo.GetProcAddress32W 
        (W32Glo.hKrnW32, (LPCSTR) "GetVersionExA"))) {
        MessageBox (NULL, "GetProcAddress32W Failed", "FILFIO", MB_OK);
        return (lpVerInf->dwPlatformId);
    }
    W32Glo._CallProcEx32W (CPEX_DEST_STDCALL | 1L, 0x1L, lpGetVersionEx, 
        (LPVOID) lpVerInf);

    /********************************************************************/
    /********************************************************************/
    return (lpVerInf->dwPlatformId);

}

