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

/************************************************************************/
/************************************************************************/
WORD    NwVIIRAloFlt (DWORD, DWORD, CVSFTR FAR *);
WORD    NwVIIRFtrFlt (short FAR *, WORD, CVSFTR FAR *);
WORD    NwVIIRAloLFA221 (DWORD, DWORD, CVSFTR FAR *);
WORD    NwVIIRFtrLFA221 (short FAR *, WORD, CVSFTR FAR *);
void    NwVIIRResAll (CVSFTR FAR *);
LNGFRA  FrqToFCoe (DWORD, DWORD);

/************************************************************************/
/************************************************************************/
LPITCB FAR PASCAL NwVC01toAlo (LPITCB lpITC, LPITCI lpIni)
{
    ITCINI      iiITCIni;
    
    /********************************************************************/
    /* Check for defaults requests: Use or request default list         */
    /********************************************************************/
    if ((NULL == lpITC) || (NULL == lpIni)) {
        if (NULL == lpIni) lpIni = &iiITCIni;       /* Use defaults req */
        /****************************************************************/
        /* Load default settings based upon Harris CVSD spec            */
        /* Note: usStpMin[Max] are doubled based on empirical test      */
        /****************************************************************/
        lpIni->ciCVS.ulSmpFrq = SMPFRQDEF;  /* Sample frequnecy         */
        lpIni->ciCVS.usLowTyp = IIRFSTTYP;  /* Output LP filter type    */
        lpIni->ciCVS.ulLowPas =     5000L;  /* Output LP filter    (Hz) */
        lpIni->ciCVS.usSigFtr =       328;  /* Signal HP filter    (Hz) */
        lpIni->ciCVS.usSylAtk =        80;  /* Syllabic Attack LPF (Hz) */
        lpIni->ciCVS.usSylDcy =        80;  /* Syllabic Decay  LPF (Hz) */
        lpIni->ciCVS.usCoiBit =         3;  /* Coincidence       (bits) */
        lpIni->ciCVS.usStpMin =         4;  /* Minimum step size  (AtD) */
        lpIni->ciCVS.usStpMax =       128;  /* Maximum step size  (AtD) */
        lpIni->ciCVS.usAtDRes = ATDRESDEF;  /* A to D resolution (bits) */
        if (!lpITC) return (lpITC);         /* Default load request     */
    }

/********************************************************************/
/********************************************************************/
//Denker's settings
//#define    FC    28                   /* Syllabic Attack      */
//#define    FG    28                   /* Syllabic Decay       */
//#define    FS    72                   /* Signal Filter        */
//#define    FH    50                   /* High Pass filter     */
//#define    FA    80                   /* Compander Attack     */
//#define    FD    16                   /* Compander Decay      */
//#define    FO    5000                 /* Output Low Pass      */

    /********************************************************************/
    /* Initialize CVSD ITC parameter block                              */
    /********************************************************************/
    _fmemset (lpITC, 0, sizeof (*lpITC));               /* Initialize   */

    /********************************************************************/
    /* Initialize low pass filters                                      */
    /********************************************************************/
    if (IIRFSTTYP == lpIni->ciCVS.usLowTyp)
        NwVIIRAloLFA221 (lpIni->ciCVS.ulLowPas, lpIni->ciCVS.ulSmpFrq, 
        &lpITC->cbCVS.cfLowPas);
    if (IIRFLTTYP == lpIni->ciCVS.usLowTyp)
        NwVIIRAloFlt (lpIni->ciCVS.ulLowPas, lpIni->ciCVS.ulSmpFrq, 
        &lpITC->cbCVS.cfLowPas);
    
    /********************************************************************/
    /* Initialize signal filters & step params; convert to time domain  */
    /********************************************************************/
    lpITC->cbCVS.lfSigFtr = FrqToFCoe (lpIni->ciCVS.usSigFtr, lpIni->ciCVS.ulSmpFrq);
    lpITC->cbCVS.lfSylAtk = FrqToFCoe (lpIni->ciCVS.usSylAtk, lpIni->ciCVS.ulSmpFrq);
    lpITC->cbCVS.lfSylDcy = FrqToFCoe (lpIni->ciCVS.usSylDcy, lpIni->ciCVS.ulSmpFrq);
    lpITC->cbCVS.lfMinStp = ONE * (LNGFRA) lpIni->ciCVS.usStpMin;
    lpITC->cbCVS.lfMaxStp = ONE * (LNGFRA) lpIni->ciCVS.usStpMax;
    lpITC->cbCVS.lfClpMax = (LNGFRA) (ONE * ((pow (2,lpIni->ciCVS.usAtDRes)/2) 
                            - lpIni->ciCVS.usStpMax));
    lpITC->cbCVS.usCoiMsk = ((1 << lpIni->ciCVS.usCoiBit) - 1) << 7;

    /********************************************************************/
    /* Initialize data history variables                                */    
    /********************************************************************/
    NwVC01toIni (lpITC);

    /********************************************************************/
    /********************************************************************/
    return (lpITC);

}

LPITCB FAR PASCAL NwVC01toIni (LPITCB lpITC)
{
    /********************************************************************/
    /* Initialize PCM conversion history values                         */
    /********************************************************************/
    lpITC->usBitOff = 0;
    lpITC->usBytOff = 0x5500;
    lpITC->cbCVS.lfCurWav = 0;
    lpITC->cbCVS.lfCurStp = lpITC->cbCVS.lfMinStp;

    /********************************************************************/
    /********************************************************************/
    NwVIIRResAll (&lpITC->cbCVS.cfLowPas);

    /********************************************************************/
    /********************************************************************/
    return (lpITC);
}

WORD FAR PASCAL NwVC01toCmp (_segment _sBufSeg, BYTE _based(void) *pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    short   _based(void) *psDstBuf = (short _based(void) *) pcSrcBuf;
    WORD    usBufSiz = usSmpCnt / 8;
    WORD    usBytCnt = (usBufSiz / sizeof (short)) / 8;
    
    /********************************************************************/
    /* Patch: Since NwvC01toG16 uses based pointers, there is no way    */
    /* to specify a NULL output, thus psDstBuf output must be in same   */
    /* segment. For non-destructive call, save and restore first samps. */
    /********************************************************************/
    /********************************************************************/
    /* Select buffer positions so that last short overwrites last       */
    /* sample byte, ie, use last last sixteenth for CVSD.               */
    /********************************************************************/
    pcSrcBuf += usBufSiz - usBytCnt;
    NwVC01toG16 (_sBufSeg, pcSrcBuf, &usBytCnt, psDstBuf, 0, lpITC);

    /********************************************************************/
    /********************************************************************/
    return (usSmpCnt);
}

LPITCB FAR PASCAL NwVC01toRel (LPITCB lpITC)
{
    return (lpITC);
}

/************************************************************************/
/* Convert an array with cvsd data to an array with pcm samples.        */
/*                                                                      */
/* pcSrcBuf:    Pointer to buffer with cvsd bits.                       */
/*              High Order Bit is first sample.                         */
/* psDstBuf:    Pointer to buffer for the pcm output.                   */
/*              Must be usSmpCnt*sizeof(short) bytes long.              */
/* usSmpCnt:    Number of cvsd samples in the array.                    */
/************************************************************************/
WORD FAR PASCAL NwVC01toG16 (_segment _sBufSeg, BYTE _based (void) *pcSrcBuf,
                WORD FAR *lpusBytCnt, short _based (void) *psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    CVSBLK      cbCVS = lpITC->cbCVS;   /* Init CVSD interface block    */
    short FAR * lpFtrBuf;
    WORD        usBitOff;
    WORD        usOldBit;
    WORD        usCo_Inc;
    WORD        usi;

    /********************************************************************/
    /* Insure bit offset range                                          */
    /********************************************************************/
    usBitOff = lpITC->usBitOff % 8;
    usOldBit = lpITC->usBytOff;

    /********************************************************************/
    /* Initialize low pass filter source / destination pointer          */
    /********************************************************************/
    lpFtrBuf = _sBufSeg:>psDstBuf;    

    /********************************************************************/
    /* For all input bytes                                              */
    /********************************************************************/
    for (usi = 0; usi < *lpusBytCnt; usi++) {
        /****************************************************************/
        /* Get next byte                                                */
        /****************************************************************/
        usOldBit |= *(_sBufSeg:>pcSrcBuf++); 

        /****************************************************************/
        /* For each CVSD bit                                            */
        /****************************************************************/
        for (usBitOff = 0; usBitOff < 8; usBitOff++) {
            /************************************************************/
            /* Coincidence & syllabic filter (last 3 or 4 bits)         */
            /* Syllabic filter: Under small input signal conditions,    */
            /*     the syllabic filter has no effect, and algorithm     */
            /*     functions as simple 1 bit delta modulator.           */
            /************************************************************/
            usCo_Inc = usOldBit & cbCVS.usCoiMsk;

            /************************************************************/
            /* Whenever 3/4 consecutive bits appear, the syllabic       */
            /* filter increases the multiplier gain.                    */
            /* Stepsize approaches min/max exponentially.               */
            /* Equivalent to BrookTrout: delstep = beta * delstep + dn  */
            /*     where beta = 1-lfSylAtk, dn = lfSylAtk * Min[Max]Stp */
            /************************************************************/
            if ((usCo_Inc == cbCVS.usCoiMsk) || (0 == usCo_Inc))  
                cbCVS.lfCurStp += MUL ((cbCVS.lfMaxStp - cbCVS.lfCurStp),
                    cbCVS.lfSylAtk);
            else {
                cbCVS.lfCurStp += MUL ((cbCVS.lfMinStp - cbCVS.lfCurStp),
                    cbCVS.lfSylDcy);
            }
  
            /************************************************************/
            /* Decay lfCurWav (HP leaky integrator)                     */
            /************************************************************/
            cbCVS.lfCurWav -= MUL (cbCVS.lfCurWav, cbCVS.lfSigFtr);

            /************************************************************/
            /* Clip to prevent overload                                 */
            /************************************************************/
            cbCVS.lfCurWav = min (cbCVS.lfCurWav, + cbCVS.lfClpMax);  
            cbCVS.lfCurWav = max (cbCVS.lfCurWav, - cbCVS.lfClpMax);  

            /************************************************************/
            /* Add new bit-sample                                       */
            /************************************************************/
            cbCVS.lfCurWav += 
                ((usOldBit & 0x80) ? cbCVS.lfCurStp : -cbCVS.lfCurStp);

            /************************************************************/
            /* Write current wave value                                 */
            /************************************************************/
            *(_sBufSeg:>psDstBuf++) = (short) (cbCVS.lfCurWav >> NRM);

            /************************************************************/
            /* Prepare next bit                                         */
            /************************************************************/
            usOldBit <<= 1;
        }
    }
    lpITC->usBitOff = usBitOff;
    lpITC->usBytOff = usOldBit;
  
    /********************************************************************/
    /* Low pass filter                                                  */
    /********************************************************************/
    if (IIRFSTTYP == lpITC->cbCVS.cfLowPas.usTyp)
        NwVIIRFtrLFA221 (lpFtrBuf, *lpusBytCnt * 8, &cbCVS.cfLowPas);
    if (IIRFLTTYP == lpITC->cbCVS.cfLowPas.usTyp)
        NwVIIRFtrFlt (lpFtrBuf, *lpusBytCnt * 8, &cbCVS.cfLowPas);

    /********************************************************************/
    /********************************************************************/
    lpITC->cbCVS = cbCVS;                   /* Set CVSD block           */
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 8);               /* Sample output count      */                            

}

WORD FAR PASCAL NwVG16toC01 (_segment _sBufSeg, short _based(void) *psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTE _based(void) *pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    CVSBLK      cbCVS = lpITC->cbCVS;   /* Init CVSD interface block    */
    WORD        usBitOff;
    WORD        usOldBit;
    WORD        usCo_Inc;
    LNGFRA      lfFtrWav;
    WORD        usi;

    /********************************************************************/
    /********************************************************************/
    usBitOff = (lpITC->usBitOff & 0xff) ? lpITC->usBitOff & 0xff : 0x01;
    usOldBit = lpITC->usBytOff;
  
    /********************************************************************/
    /********************************************************************/
    for (usi = 0; usi < *lpusSmpCnt; usi++) {
        /****************************************************************/
        /* Get PCM sample                                               */
        /****************************************************************/
        lfFtrWav = ((long) *(_sBufSeg:>psSrcBuf++)) << NRM;

        /****************************************************************/
        /* Decay lfCurWav (HP leaky integrator)                         */
        /****************************************************************/
        cbCVS.lfCurWav -= MUL (cbCVS.lfCurWav, cbCVS.lfSigFtr);
  
        /****************************************************************/
        /* Comparator: add bit to previous stream                       */
        /****************************************************************/
        usOldBit |= (lfFtrWav > cbCVS.lfCurWav) ? (BYTE) 0x80 : 0; 

        /****************************************************************/
        /* Clip to prevent overload                                     */
        /****************************************************************/
        cbCVS.lfCurWav = min (cbCVS.lfCurWav, + cbCVS.lfClpMax);  
        cbCVS.lfCurWav = max (cbCVS.lfCurWav, - cbCVS.lfClpMax);  

        /****************************************************************/
        /* Coincidence & syllabic filter (last 3 or 4 bits)             */
        /* Syllabic filter: Under small input signal conditions,        */
        /*     the syllabic filter has no effect, and algorithm         */
        /*     functions as simple 1 bit delta modulator.               */
        /* Note: If converted file sounds overmodulated on CVSD system, */
        /*       try increasing MaxStp and decreasing ATDRESDEF         */
        /****************************************************************/
        usCo_Inc = usOldBit & cbCVS.usCoiMsk; 

        /****************************************************************/
        /* Whenever 3/4 consecutive digits appear, the syllabic         */
        /* filter increases the multiplier gain.                        */
        /* Stepsize approaches min/max exponentially.                   */
        /* Equivalent to BrookTrout: delstep = beta * delstep + dn      */
        /*     where beta = 1-lfSylAtk, dn = lfSylAtk * Min[Max]Stp     */
        /****************************************************************/
        if ((usCo_Inc == cbCVS.usCoiMsk) || (0 == usCo_Inc))  
            cbCVS.lfCurStp += MUL ((cbCVS.lfMaxStp - cbCVS.lfCurStp),
                cbCVS.lfSylAtk);
        else {
            cbCVS.lfCurStp += MUL ((cbCVS.lfMinStp - cbCVS.lfCurStp),
                cbCVS.lfSylDcy);
        }
  
        /****************************************************************/
        /* Add new bit-sample                                           */
        /****************************************************************/
        cbCVS.lfCurWav += 
            ((usOldBit & 0x80) ? cbCVS.lfCurStp : -cbCVS.lfCurStp);
  
        /****************************************************************/
        /****************************************************************/
        usOldBit <<= 1;                 /* Put bit in place             */
        usBitOff <<= 1;
        if (0x100 == usBitOff) {
            *(_sBufSeg:>pcDstBuf++) = (BYTE) (usOldBit >> 8);
            usBitOff = 0x01;
        }
    }
    lpITC->usBitOff = usBitOff;
    lpITC->usBytOff = usOldBit;
  
    /********************************************************************/
    /********************************************************************/
    lpITC->cbCVS = cbCVS;                   /* Set CVSD block           */
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 8);               /* Full byte output count   */

}

WORD FAR PASCAL NwVC01toM32 (_segment _sBufSeg, BYTE _based(void) *pcSrcBuf,
                WORD FAR *lpusRsv001, short _based(void) *psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    WORD    usSetByt;                   /* # smp 8samp/osc (bytes/osc)  */
    WORD    usOscOrg = usOscCnt;        /* Original oscillation count   */
    CVSBLK  cbCVS = lpITC->cbCVS;       /* Init CVSD interface block    */
    WORD    usBitOff;
    WORD    usOldBit;
    WORD    usCo_Inc;
    WORD    usi;

    /********************************************************************/
    /* Test for null oscillation count, set size range                  */
    /********************************************************************/
    if (0 == usOscCnt) return (0);
    usSetByt = (WORD) min (ulSetSiz / 8L, 0xffffL);

    /********************************************************************/
    /* Insure bit offset range                                          */
    /********************************************************************/
    usBitOff = lpITC->usBitOff % 8;
    usOldBit = lpITC->usBytOff;

    /********************************************************************/
    /********************************************************************/
    while (usOscCnt--) {
        LNGFRA  lfCurMin = cbCVS.lfCurWav;  /* Current min oscillation  */
        LNGFRA  lfCurMax = cbCVS.lfCurWav;  /* Current max oscillation  */

        /****************************************************************/
        /****************************************************************/
        for (usi = 0; usi < usSetByt; usi++) {
            /************************************************************/
            /* Get next byte                                            */
            /************************************************************/
            usOldBit |= *(_sBufSeg:>pcSrcBuf++); 
    
            /************************************************************/
            /* For each CVSD bit                                        */
            /************************************************************/
            for (usBitOff = 0; usBitOff < 8; usBitOff++) {
                /********************************************************/
                /* Coincidence & syllabic filter (last 3 or 4 bits)     */
                /* Syllabic filter: Under small input signal conditions */
                /*     the syllabic filter has no effect, and algorithm */
                /*     functions as simple 1 bit delta modulator.       */
                /********************************************************/
                usCo_Inc = usOldBit & cbCVS.usCoiMsk;
    
                /********************************************************/
                /* Whenever 3/4 consecutive bits appear, the syllabic   */
                /* filter increases the multiplier gain.                */
                /********************************************************/
                if ((usCo_Inc == cbCVS.usCoiMsk) || (0 == usCo_Inc))  
                    cbCVS.lfCurStp += MUL ((cbCVS.lfMaxStp - cbCVS.lfCurStp),
                        cbCVS.lfSylAtk);
                else {
                    cbCVS.lfCurStp += MUL ((cbCVS.lfMinStp - cbCVS.lfCurStp),
                        cbCVS.lfSylDcy);
                }
      
                /********************************************************/
                /* Decay lfCurWav (HP leaky integrator)                 */
                /********************************************************/
                cbCVS.lfCurWav -= MUL (cbCVS.lfCurWav, cbCVS.lfSigFtr);
    
                /********************************************************/
                /* Clip to prevent overload                             */
                /********************************************************/
                cbCVS.lfCurWav = min (cbCVS.lfCurWav, + cbCVS.lfClpMax);  
                cbCVS.lfCurWav = max (cbCVS.lfCurWav, - cbCVS.lfClpMax);  
    
                /********************************************************/
                /* Add new bit-sample                                   */
                /********************************************************/
                cbCVS.lfCurWav += 
                    ((usOldBit & 0x80) ? cbCVS.lfCurStp : -cbCVS.lfCurStp);
    
                /********************************************************/
                /* Test current max / min value                         */
                /********************************************************/
                lfCurMin = min (lfCurMin, cbCVS.lfCurWav);
                lfCurMax = max (lfCurMax, cbCVS.lfCurWav);
    
                /********************************************************/
                /* Prepare next bit                                     */
                /********************************************************/
                usOldBit <<= 1;
            }
        }
        /************************************************************/
        /* Write current max / min value                            */
        /************************************************************/
        *(_sBufSeg:>psDstBuf++) = (short) (lfCurMin >> NRM);
        *(_sBufSeg:>psDstBuf++) = (short) (lfCurMax >> NRM);
    }
    lpITC->usBitOff = usBitOff;
    lpITC->usBytOff = usOldBit;

    /********************************************************************/
    /********************************************************************/
    lpITC->cbCVS = cbCVS;               /* Set CVSD block               */
    return (usOscOrg);                  /* Oscillation output count     */

}

WORD FAR PASCAL NwVSiltoC01 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    while (usBufSiz-- > 0) *lpucDstBuf++ = 0x55;
    return (usBufSiz);
}

/************************************************************************/
/************************************************************************/
WORD    NwVIIRAloFlt (DWORD ulLowPas, DWORD ulSmpFrq, CVSFTR FAR *lpCVSFtr)
{

    /********************************************************************/
    /********************************************************************/
    _fmemset (lpCVSFtr, 0, sizeof (*lpCVSFtr));         /* Initialize   */

    /********************************************************************/
    /********************************************************************/
    //CHII Low Pass: 5000	Grd: 0.300000	Sec: 3	Len: 3	Rej: 40.000000
    //Sec 0:	Zer: 0.4873	-0.5177	0.4873	Pol: -1.3212	0.7782	
    //Sec 1:	Zer: 0.3083	-0.1682	0.3083	Pol: -0.9568	0.4053	
    //Sec 2:	Zer: 0.1474	0.1828	0.1474	Pol: -0.6571	0.1348	

    /********************************************************************/
    /********************************************************************/
//if (ulSmpFrq >= 32000L) {
    lpCVSFtr->usSec = 3;
    lpCVSFtr->fbZer.usLen = 3;
    lpCVSFtr->fbZer.flCoe[0] = (float)  0.4873;
    lpCVSFtr->fbZer.flCoe[1] = (float) -0.5177;
    lpCVSFtr->fbZer.flCoe[2] = (float)  0.4873;
    lpCVSFtr->fbZer.flCoe[3] = (float)  0.3083;
    lpCVSFtr->fbZer.flCoe[4] = (float) -0.1682;
    lpCVSFtr->fbZer.flCoe[5] = (float)  0.3083;
    lpCVSFtr->fbZer.flCoe[6] = (float)  0.1474;
    lpCVSFtr->fbZer.flCoe[7] = (float)  0.1828;
    lpCVSFtr->fbZer.flCoe[8] = (float)  0.1474;
    
    lpCVSFtr->fbPol.usLen = 2;
    lpCVSFtr->fbPol.flCoe[0] = (float) -1.3212;
    lpCVSFtr->fbPol.flCoe[1] = (float)  0.7782;
    lpCVSFtr->fbPol.flCoe[2] = (float) -0.9568;
    lpCVSFtr->fbPol.flCoe[3] = (float)  0.4053;
    lpCVSFtr->fbPol.flCoe[4] = (float) -0.6571;
    lpCVSFtr->fbPol.flCoe[5] = (float)  0.1348;
//}

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->usTyp = IIRFLTTYP;
    NwVIIRResAll (lpCVSFtr);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD    NwvIIRFtrFlt (short FAR *lpSrcBuf, WORD usSmpCnt, CVSFTR FAR *lpCVSFtr)
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
        *lpSrcBuf++ = (short) flx;

    }

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->fbZer = fbZer;
    lpCVSFtr->fbPol = fbPol;
    return (0);
}

/************************************************************************/
/************************************************************************/
WORD    NwVIIRAloLFA221 (DWORD ulLowPas, DWORD ulSmpFrq, CVSFTR FAR *lpCVSFtr)
{
    /********************************************************************/
    /********************************************************************/
    _fmemset (lpCVSFtr, 0, sizeof (*lpCVSFtr));         /* Initialize   */

//    /********************************************************************/
//    /********************************************************************/
//    //CHII Low Pass: 5000	Grd: 0.300000	Sec: 3	Len: 2	Rej: 40.000000
//    //Sec 0:	Zer: 0.5074	0.5074	Pol: 0.0149	
//    //Sec 1:	Zer: 0.2738	0.2738	Pol: -0.4524	
//    //Sec 2:	Zer: 0.2163	0.2163	Pol: -0.5674	
//    lpCVSFtr->usSec = 3;
//    lpCVSFtr->fbZer.usLen = 2;
//    lpCVSFtr->fbZer.lfCoe[0] = (LNGFRA) (ONE *  0.5074);
//    lpCVSFtr->fbZer.lfCoe[1] = (LNGFRA) (ONE *  0.5074);
//    lpCVSFtr->fbZer.lfCoe[2] = (LNGFRA) (ONE *  0.2738);
//    lpCVSFtr->fbZer.lfCoe[3] = (LNGFRA) (ONE *  0.2738);
//    lpCVSFtr->fbZer.lfCoe[4] = (LNGFRA) (ONE *  0.2163);
//    lpCVSFtr->fbZer.lfCoe[5] = (LNGFRA) (ONE *  0.2163);
//    lpCVSFtr->fbPol.usLen = 1;          
//    lpCVSFtr->fbPol.lfCoe[0] = (LNGFRA) (ONE *  0.0149);
//    lpCVSFtr->fbPol.lfCoe[1] = (LNGFRA) (ONE * -0.4524);
//    lpCVSFtr->fbPol.lfCoe[2] = (LNGFRA) (ONE * -0.5674);

    /********************************************************************/
    /********************************************************************/
//CHII Low Pass: 5000	Grd: 0.300000	Sec: 2	Len: 2	Rej: 40.000000
//Sec 0:	Zer: 0.2856	0.2856	Pol: -0.4289	
//Sec 1:	Zer: 0.1420	0.1420	Pol: -0.7159	

//if (ulSmpFrq >= 32000L) {
    lpCVSFtr->usSec = 2;
    lpCVSFtr->fbZer.usLen = 2;
    lpCVSFtr->fbZer.lfCoe[0] = (LNGFRA) (ONE *  0.2856);
    lpCVSFtr->fbZer.lfCoe[1] = (LNGFRA) (ONE *  0.2856);
    lpCVSFtr->fbZer.lfCoe[2] = (LNGFRA) (ONE *  0.1420);
    lpCVSFtr->fbZer.lfCoe[3] = (LNGFRA) (ONE *  0.1420);
    lpCVSFtr->fbPol.usLen = 1;          
    lpCVSFtr->fbPol.lfCoe[0] = (LNGFRA) (ONE * -0.4289);
    lpCVSFtr->fbPol.lfCoe[1] = (LNGFRA) (ONE * -0.7159);
//}

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->usTyp = IIRFSTTYP;
    NwVIIRResAll (lpCVSFtr);

    /********************************************************************/
    /********************************************************************/
    return (0);

}

//WORD    NwVIIRFtrLFA (short FAR *lpSrcBuf, WORD usSmpCnt, CVSFTR FAR *lpCVSFtr)
//{
//    CVSFCB  fbZer = lpCVSFtr->fbZer;
//    CVSFCB  fbPol = lpCVSFtr->fbPol;
//
//    /********************************************************************/
//    /********************************************************************/
//    if ((fbZer.usLen <= 1) || (fbPol.usLen != (fbZer.usLen - 1))) 
//        return ((WORD) -1);
//
//    /********************************************************************/
//    /********************************************************************/
//    while (usSmpCnt--) {
//        WORD    usi;
//        WORD    usSec;
//        LNGFRA  lfx =  ONE * *lpSrcBuf;
//        /****************************************************************/
//        /* Filter each section of a cascaded filter.                    */
//        /* Note zeros range from 0 to usLen, poles from 0 to usLen - 1  */
//        /****************************************************************/
//        for (usSec = 0; usSec < lpCVSFtr->usSec; usSec++) {
//            LNGFRA FAR * lpZerCoe = &(fbZer.lfCoe[usSec*fbZer.usLen]);
//            LNGFRA FAR * lpZerHis = &(fbZer.lfHis[usSec*fbZer.usLen]);
//            LNGFRA FAR * lpPolCoe = &(fbPol.lfCoe[usSec*fbPol.usLen]);
//            LNGFRA FAR * lpPolHis = &(fbPol.lfHis[usSec*fbPol.usLen]);
//            /************************************************************/
//            /* Compute output for this section of filter                */
//            /************************************************************/
//            lpZerHis[0] = lfx;             
//            lfx = MUL (lpZerCoe[0], lpZerHis[0]);
//            for (usi = 1; usi < fbZer.usLen; usi++) 
//                lfx += MUL (lpZerCoe[usi],   lpZerHis[usi])
//                     - MUL (lpPolCoe[usi-1], lpPolHis[usi-1]);
//            /************************************************************/
//            /* Shift input and output histories                         */
//            /************************************************************/
//            _fmemmove (&(lpZerHis[1]), &(lpZerHis[0]), 
//                (fbZer.usLen - 1) * sizeof (*lpZerHis));
//            _fmemmove (&(lpPolHis[1]), &(lpPolHis[0]), 
//                (fbPol.usLen - 1) * sizeof (*lpPolHis));
//            lpPolHis[0] = lfx;       
//
//        }
//        /****************************************************************/
//        /****************************************************************/
//        *lpSrcBuf++ = (short) (lfx >> NRM);
//
//    }
//
//    /********************************************************************/
//    /********************************************************************/
//    lpCVSFtr->fbZer = fbZer;
//    lpCVSFtr->fbPol = fbPol;
//    return (0);
//}

WORD    NwVIIRFtrLFA221 (short FAR *lpSrcBuf, WORD usSmpCnt, CVSFTR FAR *lpCVSFtr)
{
    LNGFRA  lfZerCoeA0 = lpCVSFtr->fbZer.lfCoe[0];
    LNGFRA  lfZerCoeA1 = lpCVSFtr->fbZer.lfCoe[1];
    LNGFRA  lfZerHisA0 = lpCVSFtr->fbZer.lfHis[0];
    LNGFRA  lfZerHisA1 = lpCVSFtr->fbZer.lfHis[1];
    LNGFRA  lfPolCoeA0 = lpCVSFtr->fbPol.lfCoe[0];
    LNGFRA  lfPolHisA0 = lpCVSFtr->fbPol.lfHis[0];
    LNGFRA  lfZerCoeB0 = (&(lpCVSFtr->fbZer.lfCoe[lpCVSFtr->fbZer.usLen]))[0];
    LNGFRA  lfZerCoeB1 = (&(lpCVSFtr->fbZer.lfCoe[lpCVSFtr->fbZer.usLen]))[1];
    LNGFRA  lfZerHisB0 = (&(lpCVSFtr->fbZer.lfHis[lpCVSFtr->fbZer.usLen]))[0];
    LNGFRA  lfZerHisB1 = (&(lpCVSFtr->fbZer.lfHis[lpCVSFtr->fbZer.usLen]))[1];
    LNGFRA  lfPolCoeB0 = (&(lpCVSFtr->fbPol.lfCoe[lpCVSFtr->fbPol.usLen]))[0];
    LNGFRA  lfPolHisB0 = (&(lpCVSFtr->fbPol.lfHis[lpCVSFtr->fbPol.usLen]))[0];

    /********************************************************************/
    /* Filter a 2 section, 2 zero, 1 pole IIR filter                    */
    /********************************************************************/
    if ((lpCVSFtr->usSec != 2) || (lpCVSFtr->fbZer.usLen != 2) ||
        (lpCVSFtr->fbPol.usLen != 1)) return ((WORD) -1);

    /********************************************************************/
    /* Apply all sections to each sample (cascaded implementation)      */
    /********************************************************************/
    while (usSmpCnt--) {
        /****************************************************************/
        /* Compute output for first section (A) of filter               */
        /****************************************************************/
        lfZerHisA0 = ONE * *lpSrcBuf;             
        lfPolHisA0 = ACC (MAC (lfZerCoeA0, lfZerHisA0)
                        + MAC (lfZerCoeA1, lfZerHisA1)
                        - MAC (lfPolCoeA0, lfPolHisA0));
        lfZerHisA1 = lfZerHisA0;

        /****************************************************************/
        /* Compute output for second section (B) of filter              */
        /****************************************************************/
        lfZerHisB0 = lfPolHisA0;
        lfPolHisB0 = ACC (MAC (lfZerCoeB0, lfZerHisB0)
                        + MAC (lfZerCoeB1, lfZerHisB1)
                        - MAC (lfPolCoeB0, lfPolHisB0));
        lfZerHisB1 = lfZerHisB0;

        /****************************************************************/
        /****************************************************************/
        *lpSrcBuf++ = (short) (lfPolHisB0 >> NRM);

    }

    /********************************************************************/
    /********************************************************************/
    lpCVSFtr->fbZer.lfCoe[0] = lfZerCoeA0;
    lpCVSFtr->fbZer.lfCoe[1] = lfZerCoeA1;
    lpCVSFtr->fbZer.lfHis[0] = lfZerHisA0;
    lpCVSFtr->fbZer.lfHis[1] = lfZerHisA1;
    lpCVSFtr->fbPol.lfCoe[0] = lfPolCoeA0;
    lpCVSFtr->fbPol.lfHis[0] = lfPolHisA0;
    (&(lpCVSFtr->fbZer.lfCoe[lpCVSFtr->fbZer.usLen]))[0] = lfZerCoeB0;
    (&(lpCVSFtr->fbZer.lfCoe[lpCVSFtr->fbZer.usLen]))[1] = lfZerCoeB1;
    (&(lpCVSFtr->fbZer.lfHis[lpCVSFtr->fbZer.usLen]))[0] = lfZerHisB0;
    (&(lpCVSFtr->fbZer.lfHis[lpCVSFtr->fbZer.usLen]))[1] = lfZerHisB1;
    (&(lpCVSFtr->fbPol.lfCoe[lpCVSFtr->fbPol.usLen]))[0] = lfPolCoeB0;
    (&(lpCVSFtr->fbPol.lfHis[lpCVSFtr->fbPol.usLen]))[0] = lfPolHisB0;
    
    /********************************************************************/
    /********************************************************************/
    return (0);
}

void    NwVIIRResAll (CVSFTR FAR *lpCVSFtr)
{
    WORD    usi;
    for (usi=0; usi<lpCVSFtr->fbPol.usLen; usi++) lpCVSFtr->fbPol.lfHis[usi] = 0;
    for (usi=0; usi<lpCVSFtr->fbZer.usLen; usi++) lpCVSFtr->fbZer.lfHis[usi] = 0;
}

LNGFRA  FrqToFCoe (DWORD ulReqFrq, DWORD ulSmpFrq)
{
    float       flX;

    /********************************************************************/
    /* FtrCon = 1 - (e ** -2*PI * ulReqFrq / ulSmpFrq)                  */
    /* ReqFrq = ulSmpFrq * ln (1 - FtrCon) / -2*PI                      */
    /********************************************************************/
    flX = (float) exp ((-2.0 * dbPI * ulReqFrq) / ulSmpFrq);
    return ((LNGFRA) (ONE * (1 - flX)));
}

