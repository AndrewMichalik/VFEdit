/************************************************************************/
/* IIR Filter Design Defs: IIRDes.h                     V2.00  08/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/************************************************************************/
typedef enum _EFFIIRFTR {
    EFFIIRNUL = 0,                      /* Null filter                  */
    EFFIIRCH1 = 1,                      /* Chebyshev Type I             */
    EFFIIRCH2 = 2,                      /* Chebyshev Type II            */
    EFFIIRBUT = 3,                      /* Butterworth                  */
} EFFIIRFTR;

/************************************************************************/
/* Redefine these routines to prevent conflict in ToolBox DOS libaries  */
/************************************************************************/
#define EffIIROpt   NwV_EffIIROpt
#define spbfct      NwV_spbfct   
#define spcbii      NwV_spcbii   
#define spbwcf      NwV_spbwcf   
#define pow_ri      NwV_pow_ri   
#define spchbi      NwV_spchbi   
#define spiird      NwV_spiird   
#define spbiln      NwV_spbiln   
#define spfblt      NwV_spfblt   

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL EffIIROpt (WORD usFtrTyp, WORD usSecCnt, WORD usSecLen,
                DWORD ulStpFrq, float flGrdFac, float flStpAtt, 
                DWORD ulSmpFrq, BOOL bfFstFlg, CVSFTR FAR *lpCVSFtr);

