/************************************************************************/
/* Dialogic PCM simulator defs: XltSim.h                V2.00  11/15/93 */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/************************************************************************/
int DltTab (short StepIx, short sample);
int DltSmp (short StepIx, short wdelta);
int NxtStp (short StepIx, short sample);

/************************************************************************/
/************************************************************************/
char    WavToF (short);
short   uLFToW (BYTE);
BYTE    uLFOrd (BYTE);

/************************************************************************/
/************************************************************************/
ITCBLK * CMAKOSC (char  *SrcBuf, short *DstBuf, short OscCnt,
                short SetSiz, ITCBLK *IniPtr);
ITCBLK * CPCMTOWAVE (char  *SrcBuf, short *DstBuf, short SmpCnt,
                short DCFChk, short DCFDiv, ITCBLK *IniPtr);
ITCBLK * CMAKAPC (short *SrcBuf, char  *DstBuf, short SmpCnt,
                ITCBLK *IniPtr);
