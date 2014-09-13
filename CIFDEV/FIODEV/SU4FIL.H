/************************************************************************/
/* Summa Four File Format Defs: Su4Fil.c                V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/* Portions Copyright (c) 1993 Summa Four, Inc.  All rights reserved    */
/************************************************************************/

/************************************************************************/
/*                  Summa Four File Header Definitions                  */
/************************************************************************/
#define SU4HDRFMT   0x53756d34L
#define SU4HDRVER   0x00000001L
#define SU4DEFPCM   1
#define SU4DEFFRQ   8000
#define SU4DESLEN   32

typedef struct _SU4HDR {
    DWORD   ulHdrFmt;
    DWORD   ulHdrSiz;
    DWORD   ulHdrVer;
    DWORD   ulFil_ID;
    DWORD   ulLibCod;
    DWORD   ulEncFmt;
    DWORD   ulSmpFrq;
    DWORD   ulRsv001;
    BYTE    ucFilDes[SU4DESLEN];
} SU4HDR;



