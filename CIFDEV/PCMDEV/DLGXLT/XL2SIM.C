/************************************************************************/
/* Xl2Sim: Dialogic uLawF simulator                   V1.3    07/15/91  */
/* Copyright (c) 1987-1991  Andrew J. Michalik                          */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM conversion routine hdr   */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
#include "xltsim.h"                     /* Translation simulator defs   */

#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
#define     MAGBIT  (1 << (ATDRESDEF - 2))

/************************************************************************/
/************************************************************************/
short   uLFToW (ucSmpuLF)
BYTE    ucSmpuLF;
{
    short   sWavVal;

    WORD    usWavAbs;
    WORD    usSegNum;
    WORD    usSmpuLw;

    /********************************************************************/
    /********************************************************************/
    usSmpuLw = ucSmpuLF ^ 0x7f;                 /* Invert to unfold     */

    /********************************************************************/
    /* Note: Use (usSegNum - 2) for Dialogic 12 bit uLaw                */
    /********************************************************************/
    usSegNum = (WORD) ((usSmpuLw & 0x70) >> 4);
    switch (usSegNum) {
        case 0:
            usWavAbs = usSmpuLw & 0x000f;
            break;
        case 1:
            usWavAbs = (usSmpuLw & 0x000f) | 0x0010;
            break;
        default:
            usWavAbs = (((usSmpuLw & 0x000f) << 1) | 0x021) << (usSegNum - 2);
            break;
    }
    sWavVal = (ucSmpuLF & 0x80) ? usWavAbs : - (short) usWavAbs;

    /********************************************************************/
    /********************************************************************/
    return (sWavVal);

}
    

/************************************************************************/
/************************************************************************/
char    WavToF (sWavVal)
short   sWavVal;
{
    WORD    usWavAbs;
    WORD    usSegNum;
    BYTE    ucSmpuLw;

    /********************************************************************/
    /********************************************************************/
    sWavVal = max (sWavVal, (short) (long) ATDMINDEF);
    sWavVal = min (sWavVal, (short) (long) ATDMAXDEF);
    usWavAbs = abs (sWavVal);

    /********************************************************************/
    /*  Find number of leading zeros, subtract from 7 for segment #     */
    /********************************************************************/
    _asm {
            mov     ax, usWavAbs        // AX = waveform absolute value
            mov     cx, 7               // Set initial 7 - #0's count
FndSeg:     test    ax, MAGBIT          // Bit 11 Set?
            jnz     FSDone              // Yes, CX = 7 - #0's count
            shl     ax, 1               // No, check next bit
            loop    FndSeg              // keep looking
FSDone:     mov     usSegNum, cx        // usSegNum = 7 - #0's count
    }

    /********************************************************************/
    /* Note: Use (usSegNum - 1) for Dialogic 12 bit uLaw                */
    /********************************************************************/
    switch (usSegNum) {
        case 0:
        case 1:
            break;
        default:
            usWavAbs = usWavAbs >> (usSegNum - 1);
            break;
    }
    ucSmpuLw = (BYTE) ((usSegNum << 4) | (usWavAbs & 0x000f));

    if (sWavVal >= 0) ucSmpuLw |= 0x80;         /* Pos: Leading bit set */
    ucSmpuLw ^= 0x7f;                           /* Invert to fold       */

    /********************************************************************/
    /********************************************************************/
    return (ucSmpuLw);

}


/************************************************************************/
/*              uLaw Folded <=> Ordered PCM (symmetrical)               */
/************************************************************************/
BYTE    uLFOrd (ucuLFOrd)
BYTE    ucuLFOrd;
{
    
    if (ucuLFOrd & 0x80) return ((BYTE) (ucuLFOrd ^ 0x7f));
    else return (ucuLFOrd);

}


