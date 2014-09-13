/************************************************************************/
/* NwVTst: Conversion Tester                            V2.00  06/15/92 */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM conversion routine hdr   */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <malloc.h>                     /* Memory library defs          */
#include <fcntl.h>                      /* Flags used in open/ sopen    */
#include <sys\stat.h>                   /* File status types            */
#include <stdio.h>                      /* Standard I/O                 */
#include <share.h>                      /* Flags used in open/ sopen    */
#include <math.h>                       /* Math library defs            */
#include <dos.h>                        /* Low level dos calls          */
#include <io.h>                         /* Low level file I/O           */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
ALOITCPRC   DefAloITC = NwVC01toAlo;
CMPITCPRC   DefCmpIni = NwVC01toCmp;
PCMTOGPRC   DefPCMToG = NwVC01toG16;
GTOPCMPRC   DefGToPCM = NwVG16toC01;
PCMTOMPRC   DefPCMToO = NwVC01toM32;

/************************************************************************/
/************************************************************************/
#define _BYTMAXFIO  (BYTMAXFIO/2)
BYTE    ucTstVox[_BYTMAXFIO + (_BYTMAXFIO / 16)];

/************************************************************************/
/************************************************************************/
TstGtoC01 (char *szSrcFil, char *szDstFIl);
CvtGtoC01 (short, short, GENSMP *, WORD, BYTE *, ITCBLK *);
TstC01toG (char *szSrcFil, char *szDstFIl);
CvtC01toG (short, short, BYTE *, WORD, GENSMP *, ITCBLK *);

/************************************************************************/
/************************************************************************/
void main ()
{

    /********************************************************************/
    /********************************************************************/
    TstC01toG ("jimtst.v01", "jimtst.v16");
    TstGtoC01 ("jimtst.v16", "nwvtst.c01");
    TstC01toG ("nwvtst.c01", "nwvtst.g16");
    exit (0);

}

/************************************************************************/
/************************************************************************/
TstC01toG (char *szSrcFil, char *szDstFil)
{
    ITCBLK  ibITC;
    short   sSrcHdl;
    short   sDstHdl;

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sSrcHdl = _open (szSrcFil, _O_BINARY | _O_RDONLY))) {
        printf ("Cannot open test input file %s\n", szSrcFil);
        exit (-1); 
    }
    if (-1 == (sDstHdl = _open (szDstFil, _O_BINARY | _O_CREAT | _O_TRUNC | _O_RDWR,
        _S_IREAD | _S_IWRITE))) {
        printf ("Cannot open test output file %s\n", szSrcFil);
        _close (sSrcHdl);
        exit (-1); 
    }
    /********************************************************************/
    /********************************************************************/
    DefAloITC (&ibITC, NULL);

    /********************************************************************/
    /********************************************************************/
    while (CvtC01toG (sSrcHdl, sDstHdl, ucTstVox, _BYTMAXFIO / 16,
        (GENSMP *) (&ucTstVox[_BYTMAXFIO / 16]), &ibITC));

    /********************************************************************/
    /********************************************************************/
    _close (sSrcHdl);
    _close (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

CvtC01toG (short sSrcHdl, short sDstHdl, BYTE *pucTstVox, WORD usSrcByt, 
           GENSMP *pgsTstSmp, ITCBLK *pibITC)
{
    WORD    usDstByt;
    WORD    usSmpCnt;

    /********************************************************************/
    /********************************************************************/
    usSrcByt = _read (sSrcHdl, pucTstVox, usSrcByt);
    if ((0 == usSrcByt) || (-1 == usSrcByt)) { 
        _close (sSrcHdl);
        _close (sDstHdl);
        return (0);
    }

    /********************************************************************/
    /********************************************************************/
    usSmpCnt = DefPCMToG ((_segment) pucTstVox,
        (char _based ((_segment) pucTstVox) *) FP_OFF (pucTstVox), &usSrcByt, 
        (char _based ((_segment) pucTstVox) *) FP_OFF (pgsTstSmp),
        usSrcByt * 8, pibITC);

    /********************************************************************/
    /********************************************************************/
    usDstByt = _write (sDstHdl, pgsTstSmp, usSmpCnt * sizeof (*pgsTstSmp));

    /********************************************************************/
    /********************************************************************/
    return (usSmpCnt);

}

/************************************************************************/
/************************************************************************/
TstGtoC01 (char *szSrcFil, char *szDstFil)
{
    ITCBLK  ibITC;
    short   sSrcHdl;
    short   sDstHdl;

    /********************************************************************/
    /********************************************************************/
    if (-1 == (sSrcHdl = _open (szSrcFil, _O_BINARY | _O_RDONLY))) {
        printf ("Cannot open test input file %s\n", szSrcFil);
        exit (-1); 
    }
    if (-1 == (sDstHdl = _open (szDstFil, _O_BINARY | _O_CREAT | _O_TRUNC | _O_RDWR,
        _S_IREAD | _S_IWRITE))) {
        printf ("Cannot open test output file %s\n", szSrcFil);
        _close (sSrcHdl);
        exit (-1); 
    }
    /********************************************************************/
    /********************************************************************/
    DefAloITC (&ibITC, NULL);

    /********************************************************************/
    /********************************************************************/
    while (CvtGtoC01 (sSrcHdl, sDstHdl, (GENSMP *) ucTstVox, 
        _BYTMAXFIO / sizeof (GENSMP), &ucTstVox[_BYTMAXFIO], &ibITC));

    /********************************************************************/
    /********************************************************************/
    _close (sSrcHdl);
    _close (sDstHdl);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

CvtGtoC01 (short sSrcHdl, short sDstHdl, GENSMP *pgsTstSmp, WORD usSrcSmp, 
           BYTE *pucTstVox, ITCBLK *pibITC)
{
    WORD    usDstByt;
    WORD    usBytCnt;

    /********************************************************************/
    /********************************************************************/
    usBytCnt = _read (sSrcHdl, pgsTstSmp, usSrcSmp * sizeof (GENSMP));
    if ((0 == usBytCnt) || (-1 == usBytCnt)) { 
        _close (sSrcHdl);
        _close (sDstHdl);
        return (0);
    }
    usSrcSmp = usBytCnt / sizeof (GENSMP);

    /********************************************************************/
    /********************************************************************/
    usBytCnt = DefGToPCM ((_segment) pgsTstSmp,
        (char _based ((_segment) pgsTstSmp) *) FP_OFF (pgsTstSmp), &usSrcSmp, 
        (char _based ((_segment) pgsTstSmp) *) FP_OFF (pucTstVox),
        usSrcSmp / 8, pibITC);       
                                 
    /********************************************************************/
    /********************************************************************/
    usDstByt = _write (sDstHdl, pucTstVox, usBytCnt);

    /********************************************************************/
    /********************************************************************/
    return (usBytCnt);

}
