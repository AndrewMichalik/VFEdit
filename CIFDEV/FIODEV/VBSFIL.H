/************************************************************************/
/* VBase Indexed File Format Defs: VBsFil.c             V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/************************************************************************/

/************************************************************************/
/*              VBase File Header & Records Definitions                 */
/************************************************************************/
#define VBSMAXIDX   5000                /* Maximum allowed index count  */
#define VBSMAXFRQ 0xffffL               /* Maximum VBase sample freq    */
#define VBSDEFFRQ   6000L               /* Default VBase sample freq    */
#define VBSCNTDEF    100                /* Default VBase idx count      */
#define VBSTXTMAX  16384                /* Maximum text length          */

typedef struct _VBSHDR {                /* VBase record format          */
    DWORD   ulIdxTot;                   /* VBase File prompt count max  */
    DWORD   ulSmpFrq;                   /* Sample frequency             */
    DWORD   ulIdxUse;                   /* VBase File prompt count actv */
    DWORD   uldummya;                   /* Dummy                        */
    DWORD   ulBytUse;                   /* Bytes used (for Idx used)    */
    DWORD   uldummyb;                   /* Dummy                        */
} VBSHDR;

typedef struct _VBIREC {                /* VBase record format          */
    DWORD   ulVoxOff;                   /* Source File prompt offset    */
    DWORD   ulVoxLen;                   /* Source File prompt length    */
    DWORD   ulTxtOff;                   /* Snippet text offset          */
} VBIREC;

/************************************************************************/
/*              VBase File Manipulation Functions                       */
/************************************************************************/
FIORET  FAR PASCAL  VBSHdrIni (LPOFSTRUCT_V, VISMEMHDL FAR *, VISMEMHDL FAR *, WORD, DWORD);
FIORET  FAR PASCAL  VBSHdrLod (LPOFSTRUCT_V, VISMEMHDL FAR *, VISMEMHDL FAR *);
FIORET  FAR PASCAL  VBSHdrWrt (LPOFSTRUCT_V, VISMEMHDL, VISMEMHDL);
FIORET  FAR PASCAL  VBSHdrRel (VISMEMHDL FAR *, VISMEMHDL FAR *);

FIORET  FAR PASCAL  VBSVoxLod (LPOFSTRUCT_V, LPOFSTRUCT_V, IDXSEG FAR *, 
                    FIOPOLPRC, DWORD);
FIORET  FAR PASCAL  VBSVoxWrt (LPOFSTRUCT_V, VBSHDR FAR *, VBIREC FAR *,
                    LPOFSTRUCT_V, IDXSEG FAR *, FIOPOLPRC, DWORD);

FIORET  FAR PASCAL  VBSTxtLod (LPOFSTRUCT_V, DWORD, VISMEMHDL FAR *);
FIORET  FAR PASCAL  VBSTxtRel (VISMEMHDL FAR *);
FIORET  FAR PASCAL  VBSTxtWrt (LPOFSTRUCT_V, VBSHDR FAR *, VBIREC FAR *,
                    VISMEMHDL, IDXSEG FAR *, FIOPOLPRC, DWORD);

FIORET  FAR PASCAL  VBSFilWrt (LPOFSTRUCT_V, LPOFSTRUCT_V, VISMEMHDL, VISMEMHDL,
                    FIOPOLPRC, DWORD);

WORD    FAR PASCAL  VBSCntAsk ();
FIORET  FAR PASCAL  VBSIdxJmp (short, LPOFSTRUCT_V, VISMEMHDL, VISMEMHDL, IDXSEG FAR *);    
FIORET  FAR PASCAL  VBSIdxAsk (WORD, LPOFSTRUCT_V, float, VISMEMHDL, VISMEMHDL, IDXSEG FAR *);    

FIORET              VBSIdxShf (VISMEMHDL, VISMEMHDL FAR *, WORD, WORD, short);
short               VBSIdxCmp (VBSHDR FAR *, VBIREC FAR *, DWORD, DWORD, short);



