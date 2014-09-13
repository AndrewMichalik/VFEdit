/************************************************************************/
/* Signal Processing IIR Filter Design                  V2.00  08/15/93 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
  
#include "nwviir.h"                     /* IIR filter design defs       */

/************************************************************************/
/************************************************************************/
#include <stdio.h>

main ()
{
    CVSFTR  cfCVSFtr;    
    WORD    usFtrTyp = EFFIIRCH2;
    WORD    usSecCnt = 3;
    WORD    usSecLen = 3;
    DWORD   ulStpFrq = 5000L;
    float   flGrdFac = ((float)   .3);
    float   flStpAtt = ((float) 40.0);
    DWORD   ulSmpFrq = 32000L;
    WORD    usRetCod;
    WORD    usi;
    WORD    usj;

    /********************************************************************/
    /********************************************************************/
    printf ("CHII: %ld\tLow Pass: %ld\tGrd: %.2f\tSec: %d\tLen: %d\tRej: %.2f", 
        ulSmpFrq, ulStpFrq, flGrdFac, usSecCnt, usSecLen, flStpAtt);

    /********************************************************************/
    /********************************************************************/
    usRetCod = EffILPAlo (usFtrTyp, usSecCnt, usSecLen, ulStpFrq, flGrdFac, 
                flStpAtt, ulSmpFrq, FALSE, &cfCVSFtr);

    if (usRetCod) {
        printf ("Err:%d\n", usRetCod);
        return (0);
    }

    /********************************************************************/
    /********************************************************************/
    for (usi=0; usi<usSecCnt; usi++) {
        printf ("\nSec %d:\t", usi);
        printf ("Zer: ");
        for (usj=0; usj<cfCVSFtr.fbZer.usLen; usj++) 
            printf ("%.4f\t", cfCVSFtr.fbZer.flCoe[usi*cfCVSFtr.fbZer.usLen + usj]);
        printf ("Pol: ");
        for (usj=0; usj<cfCVSFtr.fbPol.usLen; usj++) 
            printf ("%.4f\t", cfCVSFtr.fbPol.flCoe[usi*cfCVSFtr.fbPol.usLen + usj]);
    }

    /********************************************************************/
    /********************************************************************/
    return (0);

}
