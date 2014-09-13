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
/************************************************************************/
WORD FAR PASCAL EffIIROpt (WORD usFtrTyp, WORD usSecCnt, WORD usSecLen,
                DWORD ulStpFrq, float flGrdFac, float flStpAtt, 
                DWORD ulSmpFrq, BOOL bfFstFlg, CVSFTR FAR *lpCVSFtr);

