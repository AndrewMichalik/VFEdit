/************************************************************************/
/* CCITT G.72x Common Routines: G2XXlt.c                V2.00  09/22/93 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
#include "G2xXlt.h"                     /* G.721 common functions       */
  
#include <math.h>                       /* Floating point math funcs    */
  
/************************************************************************/
/************************************************************************/
static SHORT power2[15] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80,
        0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000};
  
/************************************************************************/
/*
 * quan()
 *
 * quantizes the input val against the table of size short integers.
 * It returns i if table[i - 1] <= val < table[i].
 *
 * Using linear search for simple coding.
 */
/************************************************************************/
static INT
quan(
    INT     val,
    SHORT       *table,
    INT     size)
{
    INT     i;
  
    for (i = 0; i < size; i++)
    if (val < *table++)
        break;
    return (i);
}
  
/************************************************************************/
/*
 * fmult()
 *
 * returns the integer product of the 14-bit integer "an" and
 * "floating point" representation (4-bit exponent, 6-bit mantessa) "srn".
 */
/************************************************************************/
static INT
fmult(
    INT     an,
    INT     srn)
{
    SHORT       anmag, anexp, anmant;
//    SHORT       wanexp, wanmag, wanmant;
INT         wanexp, wanmant;
    SHORT       retval;
  
    anmag = (an > 0) ? an : ((-an) & 0x1FFF);
    anexp = quan(anmag, power2, 15) - 6;
    anmant = (anmag == 0) ? 32 :
    (anexp >= 0) ? anmag >> anexp : anmag << -anexp;
    wanexp = anexp + ((srn >> 6) & 0xF) - 13;
  
    wanmant = (anmant * (srn & 077) + 0x30) >> 4;
    retval = (wanexp >= 0) ? ((wanmant << wanexp) & 0x7FFF) :
    (wanmant >> -wanexp);
  
    return (((an ^ srn) < 0) ? -retval : retval);
}
  
/************************************************************************/
/*
 * g72x_init_state()
 * This routine initializes and/or resets the g72x_state structure
 * pointed to by 'state_ptr'.
 * All the initial state values are specified in the CCITT G.721 document.
 */
/************************************************************************/
void
g72x_init_state(
    struct g72x_state far *state_ptr)
{
    INT     cnta;
  
    state_ptr->yl = 34816;
    state_ptr->yu = 544;
    state_ptr->dms = 0;
    state_ptr->dml = 0;
    state_ptr->ap = 0;
    for (cnta = 0; cnta < 2; cnta++) {
    state_ptr->a[cnta] = 0;
    state_ptr->pk[cnta] = 0;
    state_ptr->sr[cnta] = 32;
    }
    for (cnta = 0; cnta < 6; cnta++) {
    state_ptr->b[cnta] = 0;
    state_ptr->dq[cnta] = 32;
    }
    state_ptr->td = 0;
}
  
/************************************************************************/
/*
 * predictor_zero()
 * computes the estimated signal from 6-zero predictor.
 */
/************************************************************************/
INT
predictor_zero(
    struct g72x_state far *state_ptr)
{
    INT     i;
    INT     sezi;
  
    sezi = fmult(state_ptr->b[0] >> 2, state_ptr->dq[0]);
    for (i = 1; i < 6; i++)     /* ACCUM */
    sezi += fmult(state_ptr->b[i] >> 2, state_ptr->dq[i]);
    return (sezi);
}

/************************************************************************/
/*
 * predictor_pole()
 * computes the estimated signal from 2-pole predictor.
 */
/************************************************************************/
INT
predictor_pole(
    struct g72x_state far *state_ptr)
{
    return (fmult(state_ptr->a[1] >> 2, state_ptr->sr[1]) +
    fmult(state_ptr->a[0] >> 2, state_ptr->sr[0]));
}
/*
 * step_size()
 *
 * computes the quantization step size of the adaptive quantizer.
 *
 */
INT
step_size(
    struct g72x_state far *state_ptr)
{
    INT     y;
    INT     dif;
    INT     al;
  
    if (state_ptr->ap >= 256)
    return (state_ptr->yu);
    else {
    y = state_ptr->yl >> 6;
    dif = state_ptr->yu - y;
    al = state_ptr->ap >> 2;
    if (dif > 0)
        y += (dif * al) >> 6;
    else if (dif < 0)
        y += (dif * al + 0x3F) >> 6;
    return (y);
    }
}
  
/************************************************************************/
/*
 * quantize()
 * Given a raw sample, 'd', of the difference signal and a
 * quantization step size scale factor, 'y', this routine returns the
 * ADPCM codeword to which that sample gets quantized.  The step
 * size scale factor division operation is done in the log base 2 domain
 * as a subtraction.
 */
/************************************************************************/
INT
quantize(
    INT     d,      /* Raw difference signal sample */
    INT     y,      /* Step size multiplier */
    SHORT       *table, /* quantization table */
    INT     size)   /* table size of short integers */
{
    SHORT       dqm;    /* Magnitude of 'd' */
    SHORT       exp;    /* Integer part of base 2 log of 'd' */
    SHORT       mant;   /* Fractional part of base 2 log */
    SHORT       dl;     /* Log of magnitude of 'd' */
    SHORT       dln;    /* Step size scale factor normalized log */
    INT     i;
  
    /*
     * LOG
     *
     * Compute base 2 log of 'd', and store in 'dl'.
     */
    dqm = labs(d);
    exp = quan(dqm >> 1, power2, 15);
    mant = ((dqm << 7) >> exp) & 0x7F;      /* Fractional portion. */
    dl = (exp << 7) + mant;
  
    /*
     * SUBTB
     *
     * "Divide" by step size multiplier.
     */
    dln = dl - (y >> 2);
  
    /*
     * QUAN
     *
     * Obtain codword i for 'd'.
     */
    i = quan(dln, table, size);
    if (d < 0)          /* take 1's complement of i */
    return ((size << 1) + 1 - i);
    else if (i == 0)    /* take 1's complement of 0 */
    return ((size << 1) + 1); /* new in 1988 */
    else
    return (i);
}

/************************************************************************/
/*
 * reconstruct()
 * Returns reconstructed difference signal 'dq' obtained from
 * codeword 'i' and quantization step size scale factor 'y'.
 * Multiplication is performed in log base 2 domain as addition.
 */
/************************************************************************/
INT
reconstruct(
    INT     sign,   /* 0 for non-negative value */
    INT     dqln,   /* G.72x codeword */
    INT     y)      /* Step size multiplier */
{
    SHORT       dql;    /* Log of 'dq' magnitude */
    SHORT       dex;    /* Integer part of log */
    SHORT       dqt;
    SHORT       dq;     /* Reconstructed difference signal sample */
  
    dql = dqln + (y >> 2);  /* ADDA */
  
    if (dql < 0) {
    return ((sign) ? -0x8000L : 0);
    } else {    /* ANTILOG */
    dex = (dql >> 7) & 15;
    dqt = 128 + (dql & 127);
    dq = (dqt << 7) >> (14 - dex);
    return ((sign) ? (dq - 0x8000L) : dq);
    }
}
  
/************************************************************************/
/*
 * update()
 * updates the state variables for each output code
 */
/************************************************************************/
void
update(
    INT     code_size,      /* distinguish 723_40 with others */
    INT     y,      /* quantizer step size */
    INT     wi,     /* scale factor multiplier */
    INT     fi,     /* for long/short term energies */
    INT     dq,     /* quantized prediction difference */
    INT     sr,     /* reconstructed signal */
    INT     dqsez,      /* difference from 2-pole predictor */
    struct g72x_state far *state_ptr)   /* coder state pointer */
{
    INT     cnt;
//    SHORT       mag, exp, mant; /* Adaptive predictor, FLOAT A */
SHORT       mag, exp;       /* Adaptive predictor, FLOAT A */
    SHORT       a2p;    /* LIMC */
    SHORT       a1ul;       /* UPA1 */
//    SHORT       ua2, pks1;      /* UPA2 */
SHORT       pks1;   /* UPA2 */
//    SHORT       uga2a, fa1;
SHORT       fa1;
//    SHORT       uga2b;
    char    tr;     /* tone/transition detector */
    SHORT       ylint, thr2, dqthr;
    SHORT       ylfrac, thr1;
    SHORT       pk0;
  
    pk0 = (dqsez < 0) ? 1 : 0;      /* needed in updating predictor poles */
  
    mag = dq & 0x7FFF;      /* prediction difference magnitude */
    /* TRANS */
    ylint = state_ptr->yl >> 15;    /* exponent part of yl */
    ylfrac = (state_ptr->yl >> 10) & 0x1F;  /* fractional part of yl */
    thr1 = (32 + ylfrac) << ylint;      /* threshold */
    thr2 = (ylint > 9) ? 31 << 10 : thr1;   /* limit thr2 to 31 << 10 */
    dqthr = (thr2 + (thr2 >> 1)) >> 1;      /* dqthr = 0.75 * thr2 */
    if (state_ptr->td == 0)     /* signal supposed voice */
    tr = 0;
    else if (mag <= dqthr)      /* supposed data, but small mag */
    tr = 0;     /* treated as voice */
    else        /* signal is data (modem) */
    tr = 1;
  
    /*
     * Quantizer scale factor adaptation.
     */
  
    /* FUNCTW & FILTD & DELAY */
    /* update non-steady state step size multiplier */
    state_ptr->yu = (short) (y + ((wi - y) >> 5));
  
    /* LIMB */
    if (state_ptr->yu < 544)    /* 544 <= yu <= 5120 */
    state_ptr->yu = 544;
    else if (state_ptr->yu > 5120)
    state_ptr->yu = 5120;
  
    /* FILTE & DELAY */
    /* update steady state step size multiplier */
    state_ptr->yl += state_ptr->yu + ((-state_ptr->yl) >> 6);
  
    /*
     * Adaptive predictor coefficients.
     */
    if (tr == 1) {      /* reset a's and b's for modem signal */
    state_ptr->a[0] = 0;
    state_ptr->a[1] = 0;
    state_ptr->b[0] = 0;
    state_ptr->b[1] = 0;
    state_ptr->b[2] = 0;
    state_ptr->b[3] = 0;
    state_ptr->b[4] = 0;
    state_ptr->b[5] = 0;
    } else {        /* update a's and b's */
    pks1 = pk0 ^ state_ptr->pk[0];      /* UPA2 */
  
    /* update predictor pole a[1] */
    a2p = state_ptr->a[1] - (state_ptr->a[1] >> 7);
    if (dqsez != 0) {
        fa1 = (pks1) ? state_ptr->a[0] : -state_ptr->a[0];
        if (fa1 < -8191)    /* a2p = function of fa1 */
        a2p -= 0x100;
        else if (fa1 > 8191)
        a2p += 0xFF;
        else
        a2p += fa1 >> 5;
  
        if (pk0 ^ state_ptr->pk[1])
        /* LIMC */
        if (a2p <= -12160)
            a2p = -12288;
        else if (a2p >= 12416)
            a2p = 12288;
        else
            a2p -= 0x80;
        else if (a2p <= -12416)
        a2p = -12288;
        else if (a2p >= 12160)
        a2p = 12288;
        else
        a2p += 0x80;
    }
  
    /* TRIGB & DELAY */
    state_ptr->a[1] = (short) a2p;
  
    /* UPA1 */
    /* update predictor pole a[0] */
    state_ptr->a[0] -= state_ptr->a[0] >> 8;
    if (dqsez != 0)
        if (pks1 == 0)
        state_ptr->a[0] += 192;
        else
        state_ptr->a[0] -= 192;
  
    /* LIMD */
    a1ul = 15360 - a2p;
    if (state_ptr->a[0] < -a1ul)
        state_ptr->a[0] = (short) -a1ul;
    else if (state_ptr->a[0] > a1ul)
        state_ptr->a[0] = (short) a1ul;
  
    /* UPB : update predictor zeros b[6] */
    for (cnt = 0; cnt < 6; cnt++) {
        if (code_size == 5)     /* for 40Kbps G.723 */
        state_ptr->b[cnt] -= state_ptr->b[cnt] >> 9;
        else        /* for G.721 and 24Kbps G.723 */
        state_ptr->b[cnt] -= state_ptr->b[cnt] >> 8;
        if (dq & 0x7FFF) {          /* XOR */
        if ((dq ^ state_ptr->dq[cnt]) >= 0)
            state_ptr->b[cnt] += 128;
        else
            state_ptr->b[cnt] -= 128;
        }
    }
    }
  
    for (cnt = 5; cnt > 0; cnt--)
    state_ptr->dq[cnt] = state_ptr->dq[cnt-1];
    /* FLOAT A : convert dq[0] to 4-bit exp, 6-bit mantissa f.p. */
    if (mag == 0) {
    state_ptr->dq[0] = (dq >= 0) ? 0x20 : 0xFC20;
    } else {
    exp = quan(mag, power2, 15);
    state_ptr->dq[0] = (short) ((dq >= 0) ?
        (exp << 6) + ((mag << 6) >> exp) :
        (exp << 6) + ((mag << 6) >> exp) - 0x400);
    }
  
    state_ptr->sr[1] = state_ptr->sr[0];
    /* FLOAT B : convert sr to 4-bit exp., 6-bit mantissa f.p. */
    if (sr == 0) {
    state_ptr->sr[0] = 0x20;
    } else if (sr > 0) {
    exp = quan(sr, power2, 15);
    state_ptr->sr[0] = (short) ((exp << 6) + ((sr << 6) >> exp));
    } else if (sr > -32768) {
    mag = -sr;
    exp = quan(mag, power2, 15);
    state_ptr->sr[0] =  (short) ((exp << 6) + ((mag << 6) >> exp) - 0x400);
    } else
    state_ptr->sr[0] = 0xFC20;
  
    /* DELAY A */
    state_ptr->pk[1] = state_ptr->pk[0];
    state_ptr->pk[0] = (short) pk0;
  
    /* TONE */
    if (tr == 1)    /* this sample has been treated as data */
    state_ptr->td = 0;      /* next one will be treated as voice */
    else if (a2p < -11776)  /* small sample-to-sample correlation */
    state_ptr->td = 1;      /* signal may be data */
    else        /* signal is voice */
    state_ptr->td = 0;
  
    /*
     * Adaptation speed control.
     */
    state_ptr->dms += (short) ((fi - state_ptr->dms) >> 5);       /* FILTA */
    state_ptr->dml += (short) ((((fi << 2) - state_ptr->dml) >> 7));  /* FILTB */
  
    if (tr == 1)
    state_ptr->ap = 256;
    else if (y < 1536)              /* SUBTC */
    state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
    else if (state_ptr->td == 1)
    state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
    else if (abs((state_ptr->dms << 2) - state_ptr->dml) >=
    (state_ptr->dml >> 3))
    state_ptr->ap += (0x200 - state_ptr->ap) >> 4;
    else
    state_ptr->ap += (-state_ptr->ap) >> 4;
}

#if (defined (TANDEMADJ)) /**********************************************/

/************************************************************************/
/*
 * tandem_adjust(sr, se, y, i, sign)
 *
 * At the end of ADPCM decoding, it simulates an encoder which may be receiving
 * the output of this decoder as a tandem process. If the output of the
 * simulated encoder differs from the input to this decoder, the decoder output
 * is adjusted by one level of A-law or u-law codes.
 *
 * Input:
 *      sr      decoder output linear PCM sample,
 *      se      predictor estimate sample,
 *      y       quantizer step size,
 *      i       decoder input code,
 *      sign    sign bit of code i
 *
 * Return:
 *      adjusted A-law or u-law compressed sample.
 */
/************************************************************************/
INT tandem_adjust_alaw(
    INT     sr,                         /* decoder output linear PCM    */
    INT     se,                         /* predictor estimate sample    */
    INT     y,                          /* quantizer step size          */
    INT     i,                          /* decoder input code           */
    INT     sign,
    SHORT       *qtab)
{
    unsigned char   sp;                 /* A-law compressed 8-bit code  */
    SHORT       dx;                     /* prediction error             */
    char    id;                         /* quantized prediction error   */
    INT     sd;                         /* adjusted A-law decoded samp  */
    INT     im;                         /* biased magnitude of i        */
    INT     imx;                        /* biased magnitude of id       */
  
    if (sr <= -32768)
    sr = -1;
    sp = linear2alaw((sr >> 1) << 3);   /* short to A-law compression   */
    dx = (alaw2linear(sp) >> 2) - se;   /* 16-bit prediction error      */
    id = quantize(dx, y, qtab, sign - 1);
  
    if (id == i) {                      /* no adjustment on sp          */
    return (sp);
    } else {                            /* sp adjustment needed         */
    /* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
    im = i ^ sign;                      /* 2's comp to biased unsigned  */
    imx = id ^ sign;
  
    if (imx > im) {                     /* sp adj to next lower value   */
        if (sp & 0x80) {
        sd = (sp == 0xD5) ? 0x55 :
            ((sp ^ 0x55) - 1) ^ 0x55;
        } else {
        sd = (sp == 0x2A) ? 0x2A :
            ((sp ^ 0x55) + 1) ^ 0x55;
        }
    } else {    /* sp adjusted to next higher value */
        if (sp & 0x80)
        sd = (sp == 0xAA) ? 0xAA :
            ((sp ^ 0x55) + 1) ^ 0x55;
        else
        sd = (sp == 0x55) ? 0xD5 :
            ((sp ^ 0x55) - 1) ^ 0x55;
    }
    return (sd);
    }
}
  
INT tandem_adjust_ulaw(
    INT     sr,                         /* decoder output linear PCM    */
    INT     se,                         /* predictor estimate sample    */
    INT     y,                          /* quantizer step size          */
    INT     i,                          /* decoder input code           */
    INT     sign,
    SHORT       *qtab)
{
    unsigned char   sp;                 /* u-law compressed 8-bit code  */
    SHORT       dx;                     /* prediction error             */
    char    id;                         /* quantized prediction error   */
    INT     sd;                         /* adjusted u-law decoded samp  */
    INT     im;                         /* biased magnitude of i        */
    INT     imx;                        /* biased magnitude of id       */
  
    if (sr <= -32768)
    sr = 0;
    sp = linear2ulaw(sr << 2);          /* short to u-law compression   */
    dx = (ulaw2linear(sp) >> 2) - se;   /* 16-bit prediction error      */
    id = quantize(dx, y, qtab, sign - 1);
    if (id == i) {
    return (sp);
    } else {
    /* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
    im = i ^ sign;                      /* 2's comp to biased unsigned  */
    imx = id ^ sign;
    if (imx > im) {                     /* sp adj to next lower value   */
        if (sp & 0x80)
        sd = (sp == 0xFF) ? 0x7E : sp + 1;
        else
        sd = (sp == 0) ? 0 : sp - 1;
  
    } else {    /* sp adjusted to next higher value */
        if (sp & 0x80)
        sd = (sp == 0x80) ? 0x80 : sp - 1;
        else
        sd = (sp == 0x7F) ? 0xFE : sp + 1;
    }
    return (sd);
    }
}

#endif /*****************************************************************/

