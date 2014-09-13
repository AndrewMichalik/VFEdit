/************************************************************************/
/* Swap bit table generator                             V2.00  08/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
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
/************************************************************************/
void main ()
{
    WORD    usi;
    WORD    usj;
    BYTE    bNewByt;
    BYTE    bSrcMsk;
    BYTE    bDstMsk;
    /********************************************************************/
    /********************************************************************/
    printf ("static BYTE ucBitRev[256] = {\n");

    /********************************************************************/
    /********************************************************************/
    for (usi=0; usi<256; usi++) {
        bNewByt = 0;
        bSrcMsk = 0x01;
        bDstMsk = 0x80;
        for (usj=0; usj<8; usj++) {
            if (usi & bSrcMsk) bNewByt |= bDstMsk;
            bSrcMsk <<= 1;    
            bDstMsk >>= 1;    
        }
        if (usi && !(usi % 8)) printf ("\n");
        printf ("0x%02x, ", bNewByt);
    }
    printf ("\n};");
}

