/************************************************************************/
/* TTITst: Assemby Language Tester                      V1.30  09/15/90 */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM conversion routine hdr   */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <malloc.h>                     /* Memory library defs          */
#include <math.h>                       /* Math library defs            */
#include <stdio.h>                      /* Standard I/O                 */
#include <share.h>                      /* Flags used in open/ sopen    */
#include <io.h>                         /* Low level file I/O           */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
CMPITCPRC   DefCmpIni = PL2A04toCmp;
PCMTOMPRC   DefPCMToO = PL2A04toM32;
PCMTOGPRC   DefPCMToW = PL2A04toG16;
GTOPCMPRC   DefWavToP = PL2G16toA04;

/************************************************************************/
/************************************************************************/
BYTE    tstvox[10000] = {0x00, 0x89, 0xab, 0xcc, 
                         0xa9, 0x90, 0xa9, 0x04, 
                         0x74, 0x21, 0x00, 0x08,
                         0xa9, 0xbb, 0xea, 0xa8, 
                         0x88, 0xa0, 0x27, 0x53};
//char    tstvox[10000] = {0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 
//                         0x83, 0x84, 0x83, 0x82, 0x81, 0x80, 
//                         0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 
//                         0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80 }; 
short   tstwav[10000];
short   tstosc[20][2];


/************************************************************************/
/************************************************************************/
void main ()
{
    int i, j, pasnum;
    WORD    usBytCnt;
    WORD    usSmpCnt;
    ITCBLK  ibITC;

    /********************************************************************/
    /********************************************************************/
    for (i=40; i<10000; i++) tstvox[i] = (char) i;
  
    /********************************************************************/
    /********************************************************************/
    for (pasnum=1; pasnum<100; pasnum++) {
  
        /********************************************************/
        printf ("\nTest 1: Initialize Idx/Off test %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        DefCmpIni (_segname ("_DATA"), tstvox, NULL, 40, &ibITC);
        printf ("gsCurWav:%5d  sNxtSIx:%5d  sResCnt:  %6d\n",
            ibITC.abAPC.gsCurWav, ibITC.abAPC.sNxtSIx, ibITC.abAPC.sResCnt);
  
        /********************************************************/
        printf ("\nTest 2: Repeated (sep calls) Idx/Off test %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        for (i=0; i<20; i++) {
            DefCmpIni (_segname ("_DATA"), &tstvox[i], NULL, 2, &ibITC);
            printf ("gsCurWav:%5d  sNxtSIx:%5d  sResCnt:  %5d\n",
                ibITC.abAPC.gsCurWav, ibITC.abAPC.sNxtSIx, ibITC.abAPC.sResCnt);
        }
  
        /********************************************************/
        printf ("\nTest 3: Idx/Off timing (1 pass / 60 sec vox) %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        for (i=0; i<10; i++) {
            for (j=0; j<60; j++) DefCmpIni (_segname ("_DATA"), tstvox, NULL, 6053, &ibITC);
            printf ("%2d ", i);
        }
        printf ("\nEnd timing test:\n");
  
        /********************************************************/
        printf ("\nTest 4: Oscillation Conversion test %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        DefPCMToO (_segname ("_DATA"), tstvox, NULL, tstosc[0], 20, 2, &ibITC);
        for (i=0; i<20; i++) {
            printf ("Low:%5d  High:%5d  Run total:  %6ld\n",
            tstosc[i][0], tstosc[i][1], ibITC.abAPC.lWavSum);
        }
  
        /********************************************************/
        printf ("\nTest 5: Repeated (sep calls) Osc Conv test %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        for (i=0; i<20; i++) {
            DefPCMToO (_segname ("_DATA"), &tstvox[i], NULL, tstosc[i], 1, 2, &ibITC);
            printf ("Low:%5d  High:%5d  Run total:  %6ld\n",
            tstosc[i][0], tstosc[i][1], ibITC.abAPC.lWavSum);
        }
  
        /********************************************************/
        printf ("\nTest 6: Osc timing test (1 pass / 60 sec vox) %d:\n", pasnum);
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        for (i=0; i<10; i++) {
            for (j=0; j<60; j++) DefPCMToO (_segname ("_DATA"), tstvox, NULL, tstwav, 101, 60, &ibITC);
            printf ("%2d ", i);
        }
        printf ("\nEnd timing test:\n");
  
        /********************************************************/
        printf ("\nTest 7: Wave conversion test %d:\n", pasnum);
        usBytCnt = 40;
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        DefPCMToW (_segname ("_DATA"), tstvox, &usBytCnt, tstwav, 0, &ibITC);
        for (i=0; i<20; i++) {
            printf ("P->W:\t%3x\t\t%3x\t%5d\t%5d\t%5d\t%5d\n",
                tstvox[(2*i)+0] & 0xff, tstvox[(2*i)+1] & 0xff,
                tstwav[(4*i)+0], tstwav[(4*i)+1],
                tstwav[(4*i)+2], tstwav[(4*i)+3]);
        }
        printf ("\ngsCurWav: %4d, sNxtSIx: %4d\n", ibITC.abAPC.gsCurWav, ibITC.abAPC.sNxtSIx);

        /********************************************************/
        printf ("\nTest 8: ADPCM conversion test %d:\n", pasnum);
        for (i=0; i<20; i++) {
                tstvox[(4*i)+0] = 0;
                tstvox[(4*i)+1] = 0;
        }
        usSmpCnt = 80;
        ibITC.abAPC.lWavSum = 0L;
        ibITC.abAPC.gsCurWav = ibITC.abAPC.sNxtSIx = ibITC.abAPC.sResCnt = 0;
        DefWavToP (_segname ("_DATA"), tstwav, &usSmpCnt, tstvox, 0, &ibITC);
        for (i=0; i<20; i++) {
            printf ("P->W:\t%3x\t%3x\t\t%5d\t%5d\t%5d\t%5d\n",
                tstvox[(2*i)+0] & 0xff, tstvox[(2*i)+1] & 0xff,
                tstwav[(4*i)+0], tstwav[(4*i)+1],
                tstwav[(4*i)+2], tstwav[(4*i)+3]);
        }
        printf ("\ngsCurWav: %4d, sNxtSIx: %4d\n", ibITC.abAPC.gsCurWav, ibITC.abAPC.sNxtSIx);
  
    }

    /********************************************************************/
    /********************************************************************/
    exit (0);

}


  
