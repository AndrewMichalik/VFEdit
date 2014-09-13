/************************************************************************/
/* Xl1Sim: Dialogic ADPCM simulator                   V1.3    07/15/91  */
/* Copyright (c) 1987-1991  Andrew J. Michalik                          */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM conversion routine hdr   */
#include "xltsim.h"                     /* Translation simulator defs   */

#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
#define STPTABSIZ   49

/************************************************************************/
/************************************************************************/
short   StpTab[64] =
            { 16,   17,   19,   21,   23,   25,   28,   31,
              34,   37,   41,   45,   50,   55,   60,   66,
              73,   80,   88,   97,  107,  118,  130,  143,
             157,  173,  190,  209,  230,  253,  279,  307,
             337,  371,  408,  449,  494,  544,  598,  658,
             724,  796,  876,  963, 1060, 1166, 1282, 1411,
            1552, 1552, 1552, 1552, 1552, 1552, 1552, 1552,
            1552, 1552, 1552, 1552, 1552, 1552, 1552, 1552 };

short   MLNTab[16] =
            { -1,   -1,   -1,   -1,    2,    4,    6,    8,
              -1,   -1,   -1,   -1,    2,    4,    6,    8 };



/************************************************************************/
/* Calculate delta (n) based upon current step size and sample          */
/************************************************************************/
DltTab (StepIx, sample)
short StepIx, sample;
{
    int retval;

    /********************************************************************/
    /* DltTab = Delta (n) = [+/-] [(nib * step + 2)/4 + (step+4)/8]     */
    /*        = int (nib*step/4 + 1/2) + int (step/8 + 1/2)             */
    /* d(n)   = (B2*ss(n)) + (B1*ss(n)/2) + (B0*ss(n)/4) + ss(n)/8)     */
    /********************************************************************/
    retval = ((((sample & 0x07) * StpTab[StepIx]) + 2) >> 2)
	   + ((StpTab[StepIx] + 4) >> 3);

    if ((sample & 0x08) != 0)  retval = -retval;
    return (retval);
}

/************************************************************************/
/* Calculate next sample based upon current step size & waveform delta  */
/************************************************************************/
DltSmp (StepIx, wdelta)
short StepIx, wdelta;
{
    int retval;

    /********************************************************************/
    /* DltSmp = int ((4*wdelta/step) + 0)                               */
    /* d(n)   = (ss(n)/B2) + (ss(n)/2*B1) + (ss(n)/4*B0))               */
    /********************************************************************/
    retval = abs((4*wdelta)/StpTab[StepIx]);

    if (retval > 0x07) retval = 0x07;
    if (wdelta < 0) retval = retval | 0x08;    

    return (retval);
}

/************************************************************************/
/* Calculate next step size based upon current step size and sample     */
/************************************************************************/
NxtStp (StepIx, sample)
short StepIx, sample;
{
    /********************************************************************/
    /* NxtStp = Next stepsize index                                     */
    /********************************************************************/
    StepIx = StepIx + MLNTab[sample];
    if (StepIx <  0) StepIx = 0;
    if (StepIx >= STPTABSIZ) StepIx = STPTABSIZ-1;
    return (StepIx);
}


/************************************************************************/
/* CMAKOSC: MAKOSC Simulator                            V1.0  03/15/90  */
/*                                                                      */
/************************************************************************/
ITCBLK * CMAKOSC (SrcBuf, DstBuf, OscCnt, SetSiz, IniPtr)
char *  SrcBuf;
short * DstBuf;
short   OscCnt, SetSiz;
ITCBLK * IniPtr;
{
    short   dxwave;
    short   bxstep;
    char    alsamp;
    short   cxcntr;
    short   axdelt;
    short   cursmp;
  
    /****************************************************************/
    cursmp = SetSiz;
  
    /****************************************************************/
    /* Initialize registers                                         */
    /****************************************************************/
    dxwave = IniPtr->abAPC.gsCurWav;
    bxstep = IniPtr->abAPC.sNxtSIx;
    cxcntr = IniPtr->abAPC.sResCnt;
  
    /****************************************************************/
    /* Set initial minimum and maximum                              */
    /****************************************************************/
mooslp:
    *DstBuf = dxwave;
    *(DstBuf + 1) = dxwave;
  
    /****************************************************************/
    /* Compute new waveform value for input byte                    */
    /****************************************************************/
mobylp:
    alsamp = *SrcBuf++;
    axdelt = DltTab (bxstep, ((alsamp >> 4) & 0x0f));
    dxwave = dxwave + axdelt;
  
    if (dxwave < *DstBuf) *DstBuf = dxwave;
    if (dxwave > *(DstBuf + 1)) *(DstBuf + 1) = dxwave;
  
    bxstep = NxtStp (bxstep, ((alsamp >> 4) & 0x0f));
  
  
    /****************************************************************/
    /****************************************************************/
    if (--cursmp > 0) goto nxhalf;
  
    /****************************************************************/
    *DstBuf = (*DstBuf++);
    *DstBuf = (*DstBuf++);
    if (--OscCnt <= 0) goto setret;
    cursmp = SetSiz;
    *DstBuf = dxwave;
    *(DstBuf + 1) = dxwave;
    /****************************************************************/
    /****************************************************************/
  
nxhalf:
    /****************************************************************/
    axdelt = DltTab (bxstep, (alsamp & 0x0f));
    dxwave = dxwave + axdelt;
  
    if (dxwave < *DstBuf) *DstBuf = dxwave;
    if (dxwave > *(DstBuf + 1)) *(DstBuf + 1) = dxwave;
  
    bxstep = NxtStp (bxstep, (alsamp & 0x0f));
  
    /****************************************************************/
    if (--cursmp > 0) goto mobylp;
  
    /****************************************************************/
    *DstBuf = (*DstBuf++);
    *DstBuf = (*DstBuf++);
    cursmp = SetSiz;
    if (--OscCnt <= 0) goto setret;
    goto mooslp;
  
    /****************************************************************/
setret:
    IniPtr->abAPC.gsCurWav = dxwave;
    IniPtr->abAPC.sNxtSIx = bxstep;
    IniPtr->abAPC.sResCnt = cxcntr;
    return (IniPtr);
  
}
  
  
/************************************************************************/
/* CMAKWAV: MAKWAV Simulator                            V1.0  03/15/90  */
/*                                                                      */
/************************************************************************/
ITCBLK * CPCMTOWAVE (SrcBuf, DstBuf, SmpCnt, DCFChk, DCFDiv, IniPtr)
char *  SrcBuf;
short * DstBuf;
short   SmpCnt, DCFChk, DCFDiv;
ITCBLK * IniPtr;
{
  
    return (IniPtr);
}

  
/************************************************************************/
/* CMAKAPC: CMAKAPC Simulator                           V1.0  04/15/90  */
/*                                                                      */
/************************************************************************/
ITCBLK * CMAKAPC (SrcBuf, DstBuf, SmpCnt, IniPtr)
short * SrcBuf;
char  * DstBuf;
short   SmpCnt;
ITCBLK * IniPtr;
{
    short   cxwave;
    short   bxstep;
    char    alsamp;
    short   axdelt;
  
    /****************************************************************/
    /* Initialize registers                                         */
    /****************************************************************/
    cxwave = IniPtr->abAPC.gsCurWav;
    bxstep = IniPtr->abAPC.sNxtSIx;
  
    /****************************************************************/
    /* Compute new ADPCM value for input wave                       */
    /****************************************************************/
frstnb:
    axdelt = *SrcBuf++ - cxwave;
    alsamp = (unsigned char) (0x0f & DltSmp (bxstep, axdelt));
    *DstBuf  = (char) (alsamp << 4);    
    
    axdelt = DltTab (bxstep, (alsamp & 0x0f));
    cxwave = cxwave + axdelt;
  
    bxstep = NxtStp (bxstep, (alsamp & 0x0f));

    if (--SmpCnt <= 0) goto setret;

scndnb:
    /****************************************************************/
    axdelt = *SrcBuf++ - cxwave;
    alsamp = (unsigned char) (0x0f & DltSmp (bxstep, axdelt));
    *DstBuf = *DstBuf | alsamp;    
    
    axdelt = DltTab (bxstep, (alsamp & 0x0f));
    cxwave = cxwave + axdelt;
  
    bxstep = NxtStp (bxstep, (alsamp & 0x0f));

    DstBuf++;
    if (--SmpCnt <= 0) goto setret;
    goto frstnb;
  
    /****************************************************************/
setret:
    IniPtr->abAPC.gsCurWav = cxwave;
    IniPtr->abAPC.sNxtSIx = bxstep;
    return ((ITCBLK *) IniPtr);
  
}
  
