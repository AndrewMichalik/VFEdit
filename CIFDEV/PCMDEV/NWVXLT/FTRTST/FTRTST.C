/************************************************************************/
/* New Voice PCM Translator: NwVXl1.c                   V2.00  07/03/93 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
  
#include <string.h>                     /* String manipulation funcs    */
#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <math.h>                       /* Math library defs            */
#include <stdio.h>

/************************************************************************/
/************************************************************************/
WORD    NwVFIRLow (WORD, float, WORD, CVSFCB FAR *);
WORD    NwVFIRFtr (short FAR *, WORD, CVSFCB FAR *);
double  NwVFIRWin (WORD, WORD, WORD);

/************************************************************************/
/************************************************************************/
typedef long            LNGFRA;         /* long "fractional" value      */
#define NRM                 16          /* Normalization shift count    */
#define ONE            (1L << NRM)      /* Normalized unity value       */   
#define MUL(x,y) ((((x)>>5)*((y)>>5))>>6)   /* Mul w/o und/ovr flow     */

/************************************************************************/
/************************************************************************/
#define M_PI    3.14159265358979323846
#define BIG	    1e10

/************************************************************************/
/* This function generates a single sample of a data window.            */
/* usWin = 1 (Rectangular), 2 (Tapered rectangular), 3 (Triangular),    */
/*         4 (Hanning), 5 (Hamming), or 6 (Blackman).                   */
/*         (Note:  tapered rectangular has cosine-tapered 10% ends.)    */
/* usSiz  = Size (total no. samples) of window.                         */
/* usPos  = Sample number within window, from 0 through n-1.            */
/*         (if k is outside this range, window is set to 0.)            */
/************************************************************************/
double NwVFIRWin (WORD usWin, WORD usSiz, WORD usPos)
{
    WORD    usTmp;

    /********************************************************************/
    /********************************************************************/
    if ((usWin < 1 || usWin > 6) || (usPos < 0 || usPos >= usSiz)) return (0.0);

    switch (usWin) {
        /****************************************************************/
        /****************************************************************/
        case 1:
            break;
        /****************************************************************/
        /****************************************************************/
        case 2:
            usTmp = (usSiz - 2) / 10;
            if (usPos <= usTmp) 
                return (0.5 * (1.0 - cos((double) usPos * M_PI 
                / ((double) usTmp + 1.0))));
            if (usPos > (usSiz - usTmp - 2)) 
                return (0.5 * (1.0 - cos((double) (usSiz - usPos - 1) * M_PI
                / ((double) usTmp + 1.0))));
            break;
        /****************************************************************/
        /****************************************************************/
        case 3:
            return (1.0 - fabs(1.0 - (double) (usPos * 2) / ((double) usSiz - 1.0)));
        /****************************************************************/
        /****************************************************************/
        case 4:
            return (0.5 * (1.0 - cos((double) (usPos * 2) * M_PI
                / ((double) usSiz - 1.0))));
        /****************************************************************/
        /****************************************************************/
        case 5:
            return (0.54 - 0.46 * cos((double) (usPos * 2) * M_PI
                / ((double) usSiz - 1.0)));
            break;
        /****************************************************************/
        /****************************************************************/
        case 6:
            return (0.42 - 0.5 * cos((double) (usPos * 2) * M_PI
                / ((double) usSiz - 1.0))
                + 0.08 * cos((double) (usPos * 4) * M_PI
                / ((double) usSiz - 1.0)));
    }

    /********************************************************************/
    /********************************************************************/
    return (1.0);
}

/************************************************************************/
/* FIR Lowpass filter design using windowed Fourier series.             */
/* usLen  = Length: f(z) = b(0)+b(1)*z**(-1) +...+ b(l)*z**(usLen - 1)  */
/* flFrq  = Normalized cut-off freq in hertz-seconds (FtrFrq/SmpFrq)    */
/* usWin  = Window used to truncate fourier series                      */
/* usCoe  = Digital filter coefficients returned (0:usLen-1)            */
/* ierror = 0 no errors detected                                        */
/*          1 invalid filter length                                     */
/*          2 invalid window type iwndo                                 */
/*          3 invalid cut-off fcn; <=0 or >=0.5                         */
/************************************************************************/
WORD    NwVFIRLow (WORD usLen, float flFrq, WORD usWin, CVSFCB FAR *lpFtrBlk)
{
    WORD    usi;
    float   flDly;

    /********************************************************************/
    /********************************************************************/
    _fmemset (lpFtrBlk, 0, sizeof (*lpFtrBlk));          /* Initialize   */

    /********************************************************************/
    /********************************************************************/
    if (usLen <= 1) return (1);
    if (usWin < 1 || usWin > 6) return (2);
    if (flFrq <= 0.0 || flFrq >= 0.5) return (3);

    /********************************************************************/
    /* If length is odd, set middle coefficient                         */
    /* Note: all windows equal unity at exact center                    */
    /********************************************************************/
    for (usi = 0; usi < usLen; usi++) lpFtrBlk->flCoe[usi] = 0;
    if (usLen % 2) lpFtrBlk->flCoe[(usLen-1) / 2] = (float) (2 * flFrq);

    /********************************************************************/
    /********************************************************************/
    flFrq = (float) (2.0 * M_PI * flFrq);       /* Convert to radians   */
    flDly = (float) ((usLen-1) / 2.0);

    /********************************************************************/
    /********************************************************************/
    for (usi = 0; usi < usLen/2; usi++) {
        lpFtrBlk->flCoe[usi] = (float) (sin((double) (flFrq * ((float) usi - flDly)))
            / (M_PI * ((float) usi - flDly)) * NwVFIRWin(usWin, usLen, usi));
        lpFtrBlk->flCoe[usLen - usi - 1] = lpFtrBlk->flCoe[usi];
    }
    lpFtrBlk->usLen = usLen;

    /********************************************************************/
    /********************************************************************/
    return (0);
}

/************************************************************************/
/* Filters N-point data sequence in place using array X                 */
/* Transfer function is composed of NS sections in cascade with         */
/*       Mth stage transfer function                                    */
/*            b(0,m)+b(1,m)*z**(-1)+......+b(ls,m)*z**(-ls)             */
/*     h(z) = -------------------------------------------               */
/*               1+a(1,m)*z**(-1)+.......+a(ls,m)*z**(-ls)              */
/* px retains past values of input x                                    */
/* py retains past values of output y                                   */
/* returns:  0  No errors detected                                      */
/*           m  Output at stage [m] exceeds 1.e10                       */
/************************************************************************/
WORD    spcflt (float FAR *lpSrcBuf, WORD usSmpCnt, WORD usSecCnt, WORD usFtrLen, 
        float FAR *lpZer, float FAR *lpPol, float FAR *lpHisInp, float FAR *lpHisOut)
{
    WORD usSec, usSmp, ll, usZCo, usPCo, usHIn, usHOu;

    usZCo = usFtrLen;
    usPCo = usFtrLen-1;
    usHIn = usFtrLen;
    usHOu = usFtrLen-1;

    /********************************************************************/
    /********************************************************************/
    for (usSec=0; usSec < usSecCnt; usSec++) for (usSmp=0; usSmp < usSmpCnt; usSmp++) {
        lpHisInp[usSec * usHIn] = lpSrcBuf[usSmp];
        lpSrcBuf[usSmp] = lpZer[usSec * usZCo] * lpHisInp[usSec * usHIn];

        for (ll = 1; ll < usFtrLen; ++ll) {
            lpSrcBuf[usSmp] = lpSrcBuf[usSmp] + lpZer[ll + usSec * usZCo] * lpHisInp[ll + usSec * usHIn]
               - lpPol[ll - 1 + usSec * usPCo] * lpHisOut[ll - 1 + usSec * usHOu];
        }

        if (fabs(lpSrcBuf[usSmp]) > BIG) return (usSec);

        for (ll = (usFtrLen-1); ll >= 2; --ll) {
            lpHisInp[ll + usSec * usHIn] = lpHisInp[ll - 1 + usSec * usHIn];
            lpHisOut[ll - 1 + usSec * usHOu] = lpHisOut[ll - 2 + usSec * usHOu];
        }

        lpHisInp[usSec * usHIn + 1] = lpHisInp[usSec * usHIn];
        lpHisOut[usSec * usHOu] = lpSrcBuf[usSmp];
    }

    /********************************************************************/
    /********************************************************************/
    return (0);
}

WORD    NwVIIRFtrFLT (float FAR *lpSrcBuf, WORD usSmpCnt, CVSFTR FAR *lpCVSFtr)
{
    CVSFCB  fbZer = lpCVSFtr->fbZer;
    CVSFCB  fbPol = lpCVSFtr->fbPol;

    /********************************************************************/
    /********************************************************************/
    if ((fbZer.usLen <= 1) || (fbPol.usLen != (fbZer.usLen - 1))) 
        return ((WORD) -1);

    /********************************************************************/
    /********************************************************************/
    while (usSmpCnt--) {
        WORD    usi;
        WORD    usSec;
        float   flx =  *lpSrcBuf;
        /****************************************************************/
        /* Filter each section of a cascaded filter.                    */
        /* Note zeros range from 0 to usLen, poles from 0 to usLen - 1  */
        /****************************************************************/
        for (usSec = 0; usSec < lpCVSFtr->usSec; usSec++) {
            float FAR * lpZerCoe = &(fbZer.flCoe[usSec*fbZer.usLen]);
            float FAR * lpZerHis = &(fbZer.flHis[usSec*fbZer.usLen]);
            float FAR * lpPolCoe = &(fbPol.flCoe[usSec*fbPol.usLen]);
            float FAR * lpPolHis = &(fbPol.flHis[usSec*fbPol.usLen]);
            /************************************************************/
            /* Compute output for this section of filter                */
            /************************************************************/
            lpZerHis[0] = flx;             
            flx = lpZerCoe[0] * lpZerHis[0];
            for (usi = 1; usi < fbZer.usLen; usi++) 
                flx += lpZerCoe[usi]   * lpZerHis[usi]
                     - lpPolCoe[usi-1] * lpPolHis[usi-1];
            /************************************************************/
            /* Shift input and output histories                         */
            /************************************************************/
            _fmemmove (&(lpZerHis[1]), &(lpZerHis[0]), 
                (fbZer.usLen - 1) * sizeof (*lpZerHis));
            _fmemmove (&(lpPolHis[1]), &(lpPolHis[0]), 
                (fbPol.usLen - 1) * sizeof (*lpPolHis));
            lpPolHis[0] = flx;       

        }
        /****************************************************************/
        /****************************************************************/
//        flx = min (flx, ONE * + ATDMAXDEF);  
//        flx = max (flx, ONE * - ATDMAXDEF);  
        *lpSrcBuf++ = flx;

    }

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->fbZer = fbZer;
    lpCVSFtr->fbPol = fbPol;
    return (0);
}

WORD    NwVIIRFtrLFA (GENSMP FAR *lpSrcBuf, WORD usSmpCnt, CVSFTR FAR *lpCVSFtr)
{
    CVSFCB  fbZer = lpCVSFtr->fbZer;
    CVSFCB  fbPol = lpCVSFtr->fbPol;

    /********************************************************************/
    /********************************************************************/
    if ((fbZer.usLen <= 1) || (fbPol.usLen != (fbZer.usLen - 1))) 
        return ((WORD) -1);

    /********************************************************************/
    /********************************************************************/
    while (usSmpCnt--) {
        WORD    usi;
        WORD    usSec;
        LNGFRA  lfx =  ONE * *lpSrcBuf;
        /****************************************************************/
        /* Filter each section of a cascaded filter.                    */
        /* Note zeros range from 0 to usLen, poles from 0 to usLen - 1  */
        /****************************************************************/
        for (usSec = 0; usSec < lpCVSFtr->usSec; usSec++) {
            LNGFRA FAR * lpZerCoe = &(fbZer.lfCoe[usSec*fbZer.usLen]);
            LNGFRA FAR * lpZerHis = &(fbZer.lfHis[usSec*fbZer.usLen]);
            LNGFRA FAR * lpPolCoe = &(fbPol.lfCoe[usSec*fbPol.usLen]);
            LNGFRA FAR * lpPolHis = &(fbPol.lfHis[usSec*fbPol.usLen]);
            /************************************************************/
            /* Compute output for this section of filter                */
            /************************************************************/
            lpZerHis[0] = lfx;             
            lfx = MUL (lpZerCoe[0], lpZerHis[0]);
            for (usi = 1; usi < fbZer.usLen; usi++) 
                lfx += MUL (lpZerCoe[usi],   lpZerHis[usi])
                     - MUL (lpPolCoe[usi-1], lpPolHis[usi-1]);
            /************************************************************/
            /* Shift input and output histories                         */
            /************************************************************/
            _fmemmove (&(lpZerHis[1]), &(lpZerHis[0]), 
                (fbZer.usLen - 1) * sizeof (*lpZerHis));
            _fmemmove (&(lpPolHis[1]), &(lpPolHis[0]), 
                (fbPol.usLen - 1) * sizeof (*lpPolHis));
            lpPolHis[0] = lfx;       

        }
        /****************************************************************/
        /****************************************************************/
//        lfx = min (lfx, ONE * + ATDMAXDEF);  
//        lfx = max (lfx, ONE * - ATDMAXDEF);  
        *lpSrcBuf++ = (short) (lfx >> NRM);

    }

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->fbZer = fbZer;
    lpCVSFtr->fbPol = fbPol;
    return (0);
}

/************************************************************************/
/************************************************************************/
main ()
{
//    CVSFCB  fbFtrBlk;
//    BYTE    Stack[256];
//    WORD    usi;
//    NwVFIRLow(21, .2, 6, &fbFtrBlk);
//    for (usi=0; usi<21; usi++) printf ("%d: %f\n", usi, fbFtrBlk.flCoe[usi]);

    #define N 25
    #define LS 3
    #define NS 2
    float   fx[N];
    GENSMP  gx[N];
    float   b[6]  = {(float) .001836, (float) .003672, (float) .001836, 1, 2, 1 };
    float   a[4]  = {(float) -1.4996, (float) .8482, (float) -1.5548, (float) .6493 };
    float   px[6] = {0, 0, 0, 0, 0, 0 };
    float   py[4] = {0, 0, 0, 0 };
    static  CVSFTR  cfLowPas;
    WORD    usB;
    WORD    usi;

//    /********************************************************************/
//    /* Original spcflt function                                         */
//    /********************************************************************/
//    for (usi = 0; usi < N; usi++) fx[usi] = 0;
//    fx[0] = 1;
//    for (usB=0; usB<4; usB++) {
//        spcflt (fx, N, NS, LS, b, a, px, py);
//        for (usi=0; usi<N; usi++) printf ("%d: \t%f\n", N*usB + usi, fx[usi]);
//        for (usi = 0; usi < N; usi++) fx[usi] = 0;
//    }

    /********************************************************************/
    /********************************************************************/
    cfLowPas.usSec = NS;
    _fmemset (&cfLowPas.fbZer, 0, sizeof (cfLowPas.fbZer));
    cfLowPas.fbZer.usLen = LS;
    _fmemcpy (&cfLowPas.fbZer.flCoe, &b, NS * cfLowPas.fbZer.usLen * sizeof (*cfLowPas.fbZer.flCoe));
    _fmemset (&cfLowPas.fbPol, 0, sizeof (cfLowPas.fbPol));
    cfLowPas.fbPol.usLen = LS-1;
    _fmemcpy (&cfLowPas.fbPol.flCoe, &a, NS * cfLowPas.fbPol.usLen * sizeof (*cfLowPas.fbPol.flCoe));

//    /********************************************************************/
//    /* Test floating point implementation of cascaded IIR filter        */
//    /********************************************************************/
//    for (usi = 0; usi < N; usi++) fx[usi] = 0;
//    fx[0] = 1;
//    for (usB=0; usB<4; usB++) {
//        NwVIIRFtrFLT (fx, N, &cfLowPas);
//        for (usi=0; usi<N; usi++) printf ("%d: \t%f\n", N*usB + usi, fx[usi]);
//        for (usi = 0; usi < N; usi++) fx[usi] = 0;
//    }

    cfLowPas.fbZer.lfCoe[0] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[0]);
    cfLowPas.fbZer.lfCoe[1] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[1]);
    cfLowPas.fbZer.lfCoe[2] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[2]);
    cfLowPas.fbZer.lfCoe[3] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[3]);
    cfLowPas.fbZer.lfCoe[4] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[4]);
    cfLowPas.fbZer.lfCoe[5] = (LNGFRA) (ONE * cfLowPas.fbZer.flCoe[5]);
    cfLowPas.fbPol.lfCoe[0] = (LNGFRA) (ONE * cfLowPas.fbPol.flCoe[0]);
    cfLowPas.fbPol.lfCoe[1] = (LNGFRA) (ONE * cfLowPas.fbPol.flCoe[1]);
    cfLowPas.fbPol.lfCoe[2] = (LNGFRA) (ONE * cfLowPas.fbPol.flCoe[2]);
    cfLowPas.fbPol.lfCoe[3] = (LNGFRA) (ONE * cfLowPas.fbPol.flCoe[3]);

    /********************************************************************/
    /* Test long fraction implementation of cascaded IIR filter         */
    /********************************************************************/
    for (usi = 0; usi < N; usi++) gx[usi] = 0;
    gx[0] = 1000;
    for (usB=0; usB<4; usB++) {
        NwVIIRFtrLFA (gx, N, &cfLowPas);
        for (usi=0; usi<N; usi++) printf ("%d: \t%f\n", N*usB + usi, gx[usi] / (float) 1000);
        for (usi = 0; usi < N; usi++) gx[usi] = 0;
    }

    /********************************************************************/
    /********************************************************************/
    return (0);
}

