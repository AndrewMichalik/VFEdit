/************************************************************************/
/* CCITT G.721 PCM Translator: G21Xl1.c                 V2.00  04/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
#include "G2xXlt.h"                     /* G.721 common functions       */
  
#include <stdlib.h>                     /* Misc string/math/error funcs */

    #include <stdio.h>

/************************************************************************/
/************************************************************************/
static  short lmemset (LPVOID, short, WORD);

/************************************************************************/
/************************************************************************/
short g721_decoder (short, short, G2XBLK FAR *);
short g721_encoder (short, short, G2XBLK FAR *);

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL G21A04toIni (LPITCB lpITC)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    g72x_init_state (&lpITC->gbG2X);
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL G21A04toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

/************************************************************************/
/*          Convert G.721 bits to 16 bit two's comp waveform value      */
/************************************************************************/
#define BITCNT  4
#define BYTSIZ  8

WORD FAR PASCAL G21A04toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    G2XBLK  gbG2X = lpITC->gbG2X;       /* Init G721 interface block    */
    WORD    usBit = lpITC->usBitOff;
    WORD    usByt = lpITC->usBytOff;
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusBytCnt;
    while (usi || (usBit >= BITCNT)) {
        if (usBit < BITCNT) {
            usByt |= (*(_sBufSeg:>pcSrcBuf++) << usBit);
            usBit += BYTSIZ;
            usi--;
        }
        *(_sBufSeg:>psDstBuf++) = g721_decoder (usByt & 0xf, 0, &gbG2X);
        usByt >>= BITCNT;
        usBit  -= BITCNT;
    }
    lpITC->usBitOff = usBit;
    lpITC->usBytOff = usByt;

    /********************************************************************/
    /********************************************************************/
    lpITC->gbG2X = gbG2X;                   /* Set G721 block           */
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 2);               /* Sample output count      */                            

}

WORD FAR PASCAL G21G16toA04 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    G2XBLK  gbG2X = lpITC->gbG2X;       /* Init G721 interface block    */
    WORD    usBit = lpITC->usBitOff;
    WORD    usByt = lpITC->usBytOff;
    WORD    usi;

    /********************************************************************/
    /********************************************************************/
    usi = *lpusSmpCnt;
    while (usi--) {
        usByt |= (g721_encoder (*(_sBufSeg:>psSrcBuf++), 0, &gbG2X) << usBit);
        usBit  += BITCNT;
        if (usBit >= BYTSIZ) {
            *(_sBufSeg:>pcDstBuf++) = (BYTE) (usByt & 0xff);
            usBit  -= BYTSIZ;
            usByt >>= BYTSIZ;
        }
    }
    lpITC->usBitOff = usBit;
    lpITC->usBytOff = usByt;

    /********************************************************************/
    /********************************************************************/
    lpITC->gbG2X = gbG2X;                   /* Set G721 block           */
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 2);               /* Full byte output count   */

}

WORD FAR PASCAL G21A04toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    G2XBLK  gbG2X = lpITC->gbG2X;       /* Init G721 interface block    */
    lpITC->gbG2X = gbG2X;               /* Set G721 block               */
    return (usOscCnt);                  /* Oscillation output count     */
}

WORD FAR PASCAL G21SiltoA04 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    while (usBufSiz-- > 0) *lpucDstBuf++ = 0x00;
    return (usBufSiz);
}

/************************************************************************/
/*
 * g721.c
 *
 * Description:
 *
 * g721_encoder(), g721_decoder()
 *
 * These routines comprise an implementation of the CCITT G.721 ADPCM
 * coding algorithm.  Essentially, this implementation is identical to
 * the bit level description except for a few deviations which
 * take advantage of work station attributes, such as hardware 2's
 * complement arithmetic and large memory.  Specifically, certain time
 * consuming operations such as multiplications are replaced
 * with lookup tables and software 2's complement operations are
 * replaced with hardware 2's complement.
 *
 * The deviation from the bit level specification (lookup tables)
 * preserves the bit level performance specifications.
 *
 * As outlined in the G.721 Recommendation, the algorithm is broken
 * down into modules.  Each section of code below is preceded by
 * the name of the module which it is implementing.
 *
 */
/************************************************************************/
static  short   qtab_721[7] = {-124, 80, 178, 246, 300, 349, 400};
/*
 * Maps G.721 code word to reconstructed scale factor normalized log
 * magnitude values.
 */
static  short   _dqlntab[16] = {-2048, 4, 135, 213, 273, 323, 373, 425,
                425, 373, 323, 273, 213, 135, 4, -2048};
  
/* Maps G.721 code word to log of scale factor multiplier. */
static  SHORT   _witab[16] = {-12, 18, 41, 64, 112, 198, 355, 1122,
                1122, 355, 198, 112, 64, 41, 18, -12};
/*
 * Maps G.721 code words to a set of values whose long and short
 * term averages are computed and then compared to give an indication
 * how stationary (steady state) the signal is.
 */
static  short   _fitab[16] = {0, 0, 0, 0x200, 0x200, 0x200, 0x600, 0xE00,
                0xE00, 0x600, 0x200, 0x200, 0x200, 0, 0, 0};
  
/************************************************************************/
/*
 * g721_encoder()
 *
 * Encodes the input vale of linear PCM, A-law or u-law data sl and returns
 * the resulting code. -1 is returned for unknown input coding value.
 * Note: Input sample is linear 14-bit PCM
 */
/************************************************************************/
short g721_encoder (short sl, short in_coding, struct g72x_state far *state_ptr)
{
    short       sezi, se, sez;                              /* ACCUM    */
    short       d;                                          /* SUBTA    */
    short       sr;                                         /* ADDB     */
    short       y;                                          /* MIX      */
    short       dqsez;                                      /* ADDC     */
    short       dq, i;

    sezi = predictor_zero(state_ptr);
    sez = sezi >> 1;
    se = (sezi + predictor_pole(state_ptr)) >> 1;   /* estimated signal */
    d = sl - se;                                    /* estimation diff  */
  
    /********************************************************************/
    /*              Quantize the prediction difference                  */
    /********************************************************************/
    y = step_size(state_ptr);                   /* quantizer step size  */
    i = quantize(d, y, qtab_721, 7);            /* i = ADPCM code       */
    dq = reconstruct(i & 8, _dqlntab[i], y);    /* quantized est diff   */
    sr = (dq < 0) ? se - (dq & 0x3FFF) : se + dq;   /* reconst. signal  */
    dqsez = sr + sez - se;                      /* pole prediction diff */
    update(4, y, _witab[i] << 5, _fitab[i], dq, sr, dqsez, state_ptr);
  
    /********************************************************************/
    /********************************************************************/
    return (i);
}
  
/************************************************************************/
/*
 * g721_decoder()
 *
 * Description:
 *
 * Decodes a 4-bit code of G.721 encoded data of i and
 * returns the resulting linear PCM, A-law or u-law value.
 * return -1 for unknown out_coding value.
 * Note: Output sample is linear 14-bit PCM
 */
/************************************************************************/
short g721_decoder (short i, short out_coding, struct g72x_state far *state_ptr)
{
    short       sezi, sei, sez, se;                         /* ACCUM    */
    short       y;                                          /* MIX      */
    short       sr;                                         /* ADDB     */
    short       dq;
    short       dqsez;
  
    i &= 0x0f;                              /* mask to get proper bits  */
    sezi = predictor_zero(state_ptr);
    sez = sezi >> 1;
    sei = sezi + predictor_pole(state_ptr);
    se = sei >> 1;                          /* se = estimated signal    */
    y = step_size(state_ptr);           /* dynamic quantizer step size  */
    dq = reconstruct(i & 0x08, _dqlntab[i], y);     /* quantized diff.  */
    sr = (dq < 0) ? (se - (dq & 0x3FFF)) : se + dq; /* reconst. signal  */
    dqsez = sr - se + sez;              /* pole prediction diff.        */
    update(4, y, _witab[i] << 5, _fitab[i], dq, sr, dqsez, state_ptr);
  
    return (sr);                        /* sr has 14-bit dynamic range  */
}

/************************************************************************/
/************************************************************************/
short lmemset (LPVOID lpDstBlk, short nSetByt, WORD usBytCnt)
{
    while (usBytCnt-- > 0) *((LPSTR)lpDstBlk)++ = (char) nSetByt;
    return (0);
}

