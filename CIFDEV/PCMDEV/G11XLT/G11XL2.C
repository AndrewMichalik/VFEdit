/************************************************************************/
/* CCITT G.711 PCM Translator: G11Xl1.c                 V2.00  11/22/93 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
#include "G11Xlt.h"                     /* G.711 definitions            */
  
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
static  int lmemset (LPVOID, int, WORD);

/************************************************************************/
/************************************************************************/
BYTE    linear2alaw (GENSMP);               /* 2's comp (16-bit range)  */
GENSMP  alaw2linear (BYTE);

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL G11I08toIni (LPITCB lpITC)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL G11I08toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

/************************************************************************/
/*      Convert G.711 nibbles to 16 bit two's comp waveform value       */
/************************************************************************/
WORD FAR PASCAL G11I08toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusBytCnt;
    while (usi--) {
        *(_sBufSeg:>psDstBuf++) = alaw2linear (*(_sBufSeg:>pcSrcBuf++));
    }

    /********************************************************************/
    /********************************************************************/
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 1);               /* Sample output count      */                            

}

WORD FAR PASCAL G11G16toI08 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusSmpCnt;
    while (usi--) {
        *(_sBufSeg:>pcDstBuf++) = linear2alaw (*(_sBufSeg:>psSrcBuf++));
    }

    /********************************************************************/
    /********************************************************************/
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 1);               /* Full byte output count   */

}

WORD FAR PASCAL G11I08toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    return (usOscCnt);                  /* Oscillation output count     */
}

WORD FAR PASCAL G11SiltoI08 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    while (usBufSiz-- > 0) *lpucDstBuf++ = 0xd5;
    return (usBufSiz);
}

/************************************************************************/
/*                                                                      */
/* linear2alaw() - Convert a 16-bit linear PCM value to 8-bit A-law     */
/*                                                                      */
/* linear2alaw() accepts a 16-bit integer and encodes it as A-law data. */
/*                                                                      */
/*              Linear Input Code       Compressed Code                 */
/*      ------------------------        ---------------                 */
/*      0000000wxyza                    000wxyz                         */
/*      0000001wxyza                    001wxyz                         */
/*      000001wxyzab                    010wxyz                         */
/*      00001wxyzabc                    011wxyz                         */
/*      0001wxyzabcd                    100wxyz                         */
/*      001wxyzabcde                    101wxyz                         */
/*      01wxyzabcdef                    110wxyz                         */
/*      1wxyzabcdefg                    111wxyz                         */
/*                                                                      */
/* For further information see John C. Bellamy's Digital Telephony,     */
/* 1982, John Wiley & Sons, pps 98-111 and 472-476.                     */
/************************************************************************/
static int search (int val, short *table, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (val <= *table++) return (i);
    }
    return (size);
}
  
/************************************************************************/
/************************************************************************/
BYTE    linear2alaw (GENSMP pcm_val)        /* 2's comp (16-bit range)  */
{
    int             mask;
    int             seg;
    unsigned char   aval;

    /********************************************************************/
    /********************************************************************/
    pcm_val <<= 2;

    /********************************************************************/
    /********************************************************************/
    if (pcm_val >= 0) {
        mask = 0xD5;                        /* sign (7th) bit = 1       */
    } else {
        mask = 0x55;                        /* sign bit = 0             */
        pcm_val = -pcm_val - 8;
    }

    /* Convert the scaled magnitude to segment number. */
    seg = search(pcm_val, seg_end, 8);

    /* Combine the sign, segment, and quantization bits. */
    if (seg >= 8)               /* out of range, return maximum value.  */
        return (0x7F ^ mask);
    else {
        aval = seg << SEG_SHIFT;
        if (seg < 2)
                aval |= (pcm_val >> 4) & QUANT_MASK;
        else
                aval |= (pcm_val >> (seg + 3)) & QUANT_MASK;
        return (aval ^ mask);
    }
}
  
/************************************************************************/
/*      alaw2linear() - Convert an A-law value to 16-bit linear PCM     */
/************************************************************************/
GENSMP alaw2linear (BYTE a_val)
{
    int             t;
    int             seg;

    a_val ^= 0x55;

    t = (a_val & QUANT_MASK) << 4;
    seg = ((unsigned)a_val & SEG_MASK) >> SEG_SHIFT;
    switch (seg) {
    case 0:
            t += 8;
            break;
    case 1:
            t += 0x108;
            break;
    default:
            t += 0x108;
            t <<= seg - 1;
    }
    return (((a_val & SIGN_BIT) ? t : -t) >> 2);
}
  
/************************************************************************/
/************************************************************************/
int lmemset (LPVOID lpDstBlk, int nSetByt, WORD usBytCnt)
{
    while (usBytCnt-- > 0) *((LPSTR)lpDstBlk)++ = (char) nSetByt;
    return (0);
}

