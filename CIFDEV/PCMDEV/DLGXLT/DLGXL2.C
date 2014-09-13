/************************************************************************/
/* Dialogic ULaw PCM Translator: DlgXl2.c               V2.00  06/03/92 */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
static  int lmemset  (LPVOID, int,   WORD);

/************************************************************************/
/*  uLaw Waveform to Pulse Code Conversion:                             */
/*      Fu(x)   = sgn(x) * ln(1+ u * abs(x)) / ln(1+u)                  */
/*  uLaw Pulse Code to Waveform Conversion:                             */
/*      Wu(p)   = sgn(p) * ((exp (p * ln(1 + u)) - 1) / u)              */
/************************************************************************/
#include "dlgxl2.tab"                   /* cs:Step tables               */

/************************************************************************/
/************************************************************************/
#define TS_VAR "_CODE"                  /* Table storage segment        */
#define T_ cs:                          /* Table storage override seg   */

/************************************************************************/
/************************************************************************/
#define CVTW16TOF(Wav,uLF,x)                                                \
    _asm {                                                                  \
    _asm        cmp     Wav, 0              /* Positive Wave?           */  \
    _asm        jl      NegWav##x           /* No, Negative             */  \
    }                                                                       \
    _asm {                                                                  \
    _asm        cmp     Wav, ATDMAXDEF      /* Below Maximum?           */  \
    _asm        jle     PosNrm##x           /* Yes, continue            */  \
    _asm        mov     Wav, ATDMAXDEF      /* No, set to maximum       */  \
    }                                                                       \
    PosNrm##x:                                                              \
    _asm {                                                                  \
    _asm        mov     uLF, T_ WavToF[Wav] /* uLF = uLaw Folded 8 bit  */  \
    _asm        jmp     wfDone##x                                           \
    }                                                                       \
    NegWav##x:                                                              \
    _asm {                                                                  \
    _asm        cmp     Wav, ATDMINDEF      /* Above Minimum?           */  \
    _asm        jge     NegNrm##x           /* Yes, continue            */  \
    _asm        mov     Wav, ATDMINDEF      /* No, set to minimum       */  \
    }                                                                       \
    NegNrm##x:                                                              \
    _asm {                                                                  \
    _asm        neg     Wav                 /* Wav = abs (Wav)          */  \
    _asm        mov     uLF, T_ WavToF[Wav] /* uLF = uLaw Folded 8 bit  */  \
    _asm        and     uLF, 0x7f           /* Set sign bit to negative */  \
    }                                                                       \
    wfDone##x:                                                                  


/************************************************************************/
/*      Dummy PCM scan routine to init wave value, stepsize & offset    */
/************************************************************************/
LPITCB FAR PASCAL DlgF08toIni (LPITCB lpITC)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL DlgF08toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

/************************************************************************/
/*      Convert Folded uLaw bytes to 16 bit two's comp waveform value   */
/*          Note: usSmpCnt should be even for maximum throughput        */
/************************************************************************/
WORD FAR PASCAL DlgF08toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    TCMBLK  tbTCM = lpITC->tbTCM;       /* Init table coded I/F block   */
    WORD    usSmpCnt = *lpusBytCnt * 1; /* Sample input count           */
    WORD    usSmpWrd;                   /* # sample words               */

    /********************************************************************/
    /********************************************************************/

_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Initialize registers
            //***********************************************************
fwstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            mov     si, pcSrcBuf        // SI = &Source buffer
            mov     di, psDstBuf        // DI = &Destination buffer

            //***********************************************************
            // Test for 0/1 sample count
            //***********************************************************
chksmp:     mov     cx, usSmpCnt        // usSmpCnt = number of samples 
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSmpWrd, cx        // usSmpWrd = Number of sample words
            cmp     usSmpWrd, 0         // Null word request?
            jz      lstbyt              // Yes, check for straggler

            //***********************************************************
            //Compute waveform value for 1st & 2nd byte
            //***********************************************************
getwrd:     lodsw                       // AL = 1st PCM byte, AH = 2nd
            mov     dl, ah              // DL = 2nd PCM byte
            mov     bl, al              // BL = 1st PCM byte
            xor     bh, bh              // BH = 0
            shl     bx, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[bx]   // AX = uLawF 16 bit 2's comp
            stosw                       // Set waveform array value

            mov     bl, dl              // BL = 2nd PCM byte
            xor     bh, bh              // BH = 0
            shl     bx, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[bx]   // AX = uLawF 16 bit 2's comp
            stosw                       // Set waveform array value

decset:     loop    getwrd              // Continue with sample set?

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstbyt:     test    usSmpCnt, 01h       // No, straggler in set?
            jz      setret              // No, finish set
            lodsb                       // AL = last PCM byte
            mov     bl, al              // BL = last PCM byte
            xor     bh, bh              // BH = 0
            shl     bx, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[bx]   // AX = uLawF 16 bit 2's comp
            stosw                       // Set waveform array value

            //***********************************************************
            // End of waveform sequence - set return values
            //***********************************************************
setret:     mov     tbTCM.gsCurWav, ax  // AX = Ending waveform value
  
            //***********************************************************
            //***********************************************************
pwdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;                   /* Set TCM block            */
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 1);               /* Sample output count      */                            
  
}

/************************************************************************/
/*      Convert waveform word values to 8 bit uLaw Folded bytes         */
/************************************************************************/
WORD FAR PASCAL DlgG16toF08 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    TCMBLK  tbTCM = lpITC->tbTCM;       /* Init table coded I/F block   */
    WORD    usSmpCnt = *lpusSmpCnt;     /* Sample input count           */
    WORD    usSmpWrd;                   /* # sample words               */

    /********************************************************************/
    /********************************************************************/
  
_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Initialize registers
            //***********************************************************
wfstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            mov     si, psSrcBuf        // SI = &Source buffer
            mov     di, pcDstBuf        // DI = &Destination buffer

            //***********************************************************
            // Test for null sample count
            //***********************************************************
chksmp:     mov     cx, usSmpCnt        // usSmpCnt = number of samples 
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSmpWrd, cx        // usSmpWrd = Number of sample words
            cmp     usSmpWrd, 0         // Null word request?
            jz      lstwrd              // Yes, check for straggler

            //***********************************************************
            // Compute 1st & 2nd byte for 2 waveform values 
            //***********************************************************
fstwrd:     lodsw                       // AX = 1st waveform value
            mov     bx, ax              // BX = 1st waveform value
            CVTW16TOF(bx,dl,1)          // Convert BX to uLawF => DL

            lodsw                       // AX = 2nd waveform value
            mov     bx, ax              // BX = 2nd waveform value
            CVTW16TOF(bx,ah,2)          // Convert BX to uLawF => AH

            mov     al, dl              // AL = 1st 8 bit PCM, AH = 2nd
            stosw                       // Set 8 bit PCM array value
decset:     loop    fstwrd              // Continue with sample set?

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstwrd:     test    usSmpCnt, 01h       // No, straggler in set?
            jz      setret              // No, finish set
            lodsw                       // AX = waveform value
            mov     bx, ax              // BX = last waveform value
            CVTW16TOF(bx,al,3)          // Convert BX to uLawF => AL
            stosb                       // Set 8 bit PCM array value

            //***********************************************************
            // End of waveform sequence - set return values
            //***********************************************************
setret:     mov     tbTCM.gsCurWav, bx  // BX = Ending waveform value
  
            //***********************************************************
            //***********************************************************
wpdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;                   /* Set TCM block            */
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 1);               /* Full byte output count   */
  
}

/************************************************************************/
/*      Convert Folded uLaw bytes to a word oscillation array           */
/*          Note:  ulSetSiz must be non-zero, > 2 and < 64K.            */
/*                 ulSetSiz should be even for maximum throughput       */
/*          PCM:   0 to ff, midrange = 80                               */
/*                 Magnitude - 80h = signed, Signed + 80h = Mag         */
/************************************************************************/
WORD FAR PASCAL DlgF08toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    WORD    usSetWrd;                   /* # smp words/osc (words/osc)  */
    WORD    usSetSiz;                   /* 64K limited set size         */
    WORD    usOscOrg = usOscCnt;        /* Original oscillation count   */
    TCMBLK  tbTCM = lpITC->tbTCM;       /* Init table coded I/F block   */

    /********************************************************************/
    /* Test for null oscillation count, set size range                  */
    /********************************************************************/
    if (0 == usOscCnt) return (0);
    usSetSiz = (WORD) min (ulSetSiz, 0xffffL); 

_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Initialize registers, conversion parameters
            //***********************************************************
fmstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            // Initialize working registers
            //***********************************************************
            mov     bx, tbTCM.gsCurWav  // BX = Starting waveform value
            CVTW16TOF(bx,al,1)          // Convert BX to uLawF => AL
            mov     bx, OFFSET T_ uLFOrd // BX = uLawF <=> ordered table
            xlatb   T_ uLFOrd           // AL = initial uLawF (ordered)
            mov     dl, al              // Set init min uLawF (ordered)
            mov     dh, dl              // Set init max uLawF (ordered)
            mov     si, pcSrcBuf        // SI = &Source buffer
            mov     di, psDstBuf        // DI = &Destination buffer
  
            //***********************************************************
            // Test for null sample count (must be 2 or greater)
            //***********************************************************
chkset:     mov     cx, usSetSiz        // CX = # samples/ oscillation
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSetWrd, cx        // usSetWrd = # words/osc
            cmp     usSetWrd, 0         // Null word request?
            jz      pmdone              // Yes, exit

            //***********************************************************
            // Compute waveform value for 1st byte, test for min/max
            //***********************************************************
fstbyt:     lodsw                       // AL = 1st PCM byte, AH = 2nd
            xlatb   T_ uLFOrd           // AL = 1st uLawF (ordered)
            cmp     al, dl              // AL < current minimum?
            ja      tsthi1              // No, continue (unsigned)
            mov     dl, al              // Yes, set new minimum
tsthi1:     cmp     al, dh              // AL > current maximum?
            jb      secbyt              // No, continue (unsigned)
            mov     dh, al              // Yes, set new maximum

            //***********************************************************
            // Compute waveform value for 2nd byte, test for min/max
            //***********************************************************
            mov     al, ah              // AL = 2nd PCM byte
            xlatb   T_ uLFOrd           // AL = 2nd uLawF (ordered)
secbyt:     cmp     al, dl              // AL < current minimum?
            ja      tsthi2              // No, continue (unsigned)
            mov     dl, al              // Yes, set new minimum
tsthi2:     cmp     al, dh              // AL > current maximum?
            jb      decset              // No, continue (unsigned)
            mov     dh, al              // Yes, set new maximum

decset:     loop    fstbyt              // Continue with sample set?

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstbyt:     test    usSetSiz, 01h       // No, straggler in set?
            jz      endset              // No, finish set
            lodsb                       // AL = last PCM byte
            xlatb   T_ uLFOrd           // AL = last uLawF (ordered)
            cmp     al, dl              // AL < current minimum?
            ja      tsthil              // No, continue (unsigned)
            mov     dl, al              // Yes, set new minimum
tsthil:     cmp     al, dh              // AL > current maximum?
            jb      endset              // No, finish set (unsigned)
            mov     dh, al              // Yes, set new maximum

            //***********************************************************
            // Clean up and end of sample set 
            //***********************************************************
endset:     mov     cx, si              // CX = Current source word ptr
            xchg    al, dl              // AL = Minimum uLawF (ordered)
                                        // DL = Current PCM (ordered)
            xlatb   T_ uLFOrd           // AL = Minimum uLawF (folded)
            xor     ah, ah              // AH = 0
            mov     si, ax              // SI = Current minimum
            shl     si, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[si]   // AX = uLawF 16 bit 2's comp
            stosw                       // Set sample set minimum

            mov     al, dh              // AL = Maximum uLawF (ordered)
            xlatb   T_ uLFOrd           // AL = Maximum uLawF (folded)
            xor     ah, ah              // AH = 0
            mov     si, ax              // SI = Current maximum
            shl     si, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[si]   // AX = uLawF 16 bit 2's comp
            stosw                       // Set sample set maximum

            dec     usOscCnt            // Done with all oscillations?
            jz      setret              // Yes, set return values
            mov     si, cx              // SI = Current source word ptr
            mov     dh, dl              // Set init max = min = current
            mov     cx, usSetWrd        // CX = # samples/ oscillation
            jmp     fstbyt              // Continue with next byte
  
            //***********************************************************
            // End of oscillation sequence - set return values
            //***********************************************************
setret:     mov     al, dl              // AL = Current uLawF (ordered)
            xlatb   T_ uLFOrd           // AL = Current uLawF (folded)
            xor     ah, ah              // AH = 0
            mov     si, ax              // SI = Current minimum
            shl     si, 1               // Adjust for table lookup
            mov     ax, T_ uLFToW[si]   // AX = uLawF 16 bit 2's comp
            mov     tbTCM.gsCurWav, ax  // AX = Ending waveform value
  
            //***********************************************************
            //***********************************************************
pmdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;               /* Reset ADPCM interface block  */
    return (usOscOrg);                  /* Oscillation output count     */
  
}

/************************************************************************/
/*                      Set Buffer to Silence                           */
/************************************************************************/
WORD FAR PASCAL DlgSiltoF08 (BYTE FAR *lpcDstBuf, WORD usBufSiz)
{
    WORD    usi = usBufSiz;

    while (usi-- > 0) *lpcDstBuf++ = (BYTE) 0xff;
    return (usBufSiz);

}

/************************************************************************/
/************************************************************************/
int lmemset (LPVOID lpDstBlk, int nSetByt, WORD usBytCnt)
{
    while (usBytCnt-- > 0) *((LPSTR)lpDstBlk)++ = (char) nSetByt;
    return (0);
}
