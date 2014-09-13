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
BYTE    linear2ulaw (GENSMP);               /* 2's comp (16-bit range)  */
GENSMP  ulaw2linear (BYTE);

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL G11F08toIni (LPITCB lpITC)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL G11F08toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

/************************************************************************/
/*      Convert G.711 nibbles to 16 bit two's comp waveform value       */
/************************************************************************/
WORD FAR PASCAL G11F08toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusBytCnt;
    while (usi--) {
        *(_sBufSeg:>psDstBuf++) = ulaw2linear (*(_sBufSeg:>pcSrcBuf++));
    }

    /********************************************************************/
    /********************************************************************/
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 1);               /* Sample output count      */                            

}

WORD FAR PASCAL G11G16toF08 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusSmpCnt;
    while (usi--) {
        *(_sBufSeg:>pcDstBuf++) = linear2ulaw (*(_sBufSeg:>psSrcBuf++));
    }

    /********************************************************************/
    /********************************************************************/
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 1);               /* Full byte output count   */

}

WORD FAR PASCAL G11F08toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    return (usOscCnt);                  /* Oscillation output count     */
}

WORD FAR PASCAL G11SiltoF08 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    while (usBufSiz-- > 0) *lpucDstBuf++ = 0xff;
    return (usBufSiz);
}

/************************************************************************/
/*              u-law, A-law and linear PCM conversions.                */
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
/*                                                                      */
/* linear2ulaw() - Convert a linear PCM value to u-law                  */
/*                                                                      */
/* In order to simplify the encoding process, the original linear       */
/* magnitude is biased by adding 33 which shifts the encoding range     */
/* from (0 - 8158) to (33 - 8191). The result can be seen in the        */
/* following encoding table:                                            */
/*                                                                      */
/*      Biased Linear Input Code        Compressed Code                 */
/*      ------------------------        ---------------                 */
/*      00000001wxyza                   000wxyz                         */
/*      0000001wxyzab                   001wxyz                         */
/*      000001wxyzabc                   010wxyz                         */
/*      00001wxyzabcd                   011wxyz                         */
/*      0001wxyzabcde                   100wxyz                         */
/*      001wxyzabcdef                   101wxyz                         */
/*      01wxyzabcdefg                   110wxyz                         */
/*      1wxyzabcdefgh                   111wxyz                         */
/*                                                                      */
/* Each biased linear code has a leading 1 which identifies the         */
/* segment number. The value of the segment number is equal to 7 minus  */
/* the number of leading 0's. The quantization interval is directly     */
/* available as the four bits wxyz. Trailing bits (a - h) are ignored.  */
/*                                                                      */
/* Ordinarily the complement of the resulting code word is used for     */
/* transmission, and so the code word is complemented before it is      */
/* returned.                                                            */
/*                                                                      */
/* For further information see John C. Bellamy's Digital Telephony,     */
/* 1982, John Wiley & Sons, pps 98-111 and 472-476.                     */
/************************************************************************/
#define BIAS            (0x84)              /* Bias for linear code.    */
  
BYTE    linear2ulaw (GENSMP pcm_val)        /* 2's comp (16-bit range)  */
{
    int             mask;
    int             seg;
    unsigned char   uval;

    /********************************************************************/
    /********************************************************************/
    pcm_val <<= 2;

    /********************************************************************/
    /* Get the sign and the magnitude of the value.                     */
    /********************************************************************/
    if (pcm_val < 0) {
        pcm_val = BIAS - pcm_val;
        mask = 0x7F;
    } else {
        pcm_val += BIAS;
        mask = 0xFF;
    }

    /* Convert the scaled magnitude to segment number. */
    seg = search(pcm_val, seg_end, 8);

    /*
     * Combine the sign, segment, quantization bits;
     * and complement the code word.
     */
    if (seg >= 8)           /* out of range, return maximum value. */
        return (0x7F ^ mask);
    else {
        uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
        return (uval ^ mask);
    }

}
  
/************************************************************************/
/* ulaw2linear() - Convert a u-law value to 16-bit linear PCM           */
/*                                                                      */
/* First, a biased linear code is derived from the code word. An        */
/* unbiased output can then be obtained by subtracting 33 from the      */
/* code.                                                                */
/*                                                                      */
/* Note that this function expects to be passed the complement of the   */
/* original code word. This is in keeping with ISDN conventions.        */
/************************************************************************/
GENSMP ulaw2linear (BYTE u_val)
{
    int t;

    /* Complement to obtain normal u-law value. */
    u_val = ~u_val;

    /*
     * Extract and bias the quantization bits. Then
     * shift up by the segment number and subtract out the bias.
     */
    t = ((u_val & QUANT_MASK) << 3) + BIAS;
    t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;

    return (((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS)) >> 2);
}

/************************************************************************/
/************************************************************************/
int lmemset (LPVOID lpDstBlk, int nSetByt, WORD usBytCnt)
{
    while (usBytCnt-- > 0) *((LPSTR)lpDstBlk)++ = (char) nSetByt;
    return (0);
}

