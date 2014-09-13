/************************************************************************/
/* TTI Powerline II PCM Translator: TTIXl2.c            V2.00  06/03/92 */
/* Copyright (c) 1987-1991 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/************************************************************************/
static  int lmemset (LPVOID, int, WORD);

/************************************************************************/
/************************************************************************/
#define CHKOVRP08(Wav,x)                                                    \
    _asm {                                                                  \
    _asm        cmp     Wav, 007fh      /* Check 8 bit two's comp high  */  \
    _asm        jle     TstLow##x       /* Below maximum?               */  \
    _asm        mov     Wav, 007fh      /* No, set to maximum           */  \
    _asm        jmp     SMDone##x       /* Exit                         */  \
    }                                                                       \
    TstLow##x: _asm {                                                       \
    _asm        cmp     Wav, 0ff80h     /* Check 8 bit two's comp high  */  \
    _asm        jge     SMDone##x       /* Above minimum?               */  \
    _asm        mov     Wav, 0ff80h     /* No, set to minimum           */  \
    }                                                                       \
    SMDone##x:

// Should eliminate shift to 11 bit, use ulPCMAtDRes functions to 
// correct for A to D scaling. Correct ulPCMAtDres entry when complete
#define AL_TOW_AX                                                           \
    _asm {                                                                  \
    _asm        sub     al, 80h         /* AL = 8 bit two's comp PCM    */  \
    _asm        cbw                     /* AH = Sign of AL (extended)   */  \
    _asm        SAL3    (ax)            /* AX = 11 bit two's comp PCM   */  \
    _asm        or     ax, 0x04         /* round truncated bits         */  \
    }                                                                       


/************************************************************************/
/*      Dummy PCM scan routine to init wave value, stepsize & offset    */
/************************************************************************/
LPITCB FAR PASCAL PL2P08toIni (LPITCB lpITC, LPVOID lpRsv001)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL PL2P08toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    return (usSmpCnt);
}

/************************************************************************/
/*              Convert PCM bytes to waveform word values               */
/************************************************************************/
WORD FAR PASCAL PL2P08toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
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
pwstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            mov     si, pcSrcBuf        // SI = &Source buffer
            mov     di, psDstBuf        // DI = &Destination buffer

            //***********************************************************
            // Test for null sample count
            //***********************************************************
chksmp:     mov     cx, usSmpCnt        // sSmpCnt = number of samples 
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSmpWrd, cx        // usSmpWrd = Number of sample words
            cmp     usSmpWrd, 0         // Null word request?
            jz      lstbyt              // Yes, check for straggler

            //***********************************************************
            //Compute waveform value for 1st & 2nd byte
            //***********************************************************
getwrd:     lodsw                       // AL = 1st PCM byte, AH = 2nd
            mov     dl, ah              // DL = 2nd PCM byte
            AL_TOW_AX                   // AX = 11 bit two's comp PCM
            stosw                       // Set waveform array value
            mov     al, dl              // AL = 2nd PCM byte
            AL_TOW_AX                   // AX = 11 bit two's comp PCM
            stosw                       // Set waveform array value
decset:     loop    getwrd              // Continue with sample set?

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstbyt:     test    usSmpCnt, 01h       // No, straggler in set?
            jz      setret              // No, finish set
            lodsb                       // AL = last PCM byte
            AL_TOW_AX                   // AX = 11 bit two's comp PCM
            stosw                       // Set waveform array value

            //***********************************************************
            // End of waveform sequence - set return values
            //***********************************************************
setret:     mov     tbTCM.gsCurWav, ax  // AX = Ending waveform value
  
            //***********************************************************
pwdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;                   /* Set PCM block            */
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 1);               /* Sample output count      */                            
  
}

/************************************************************************/
/*              Convert waveform word values to 8 bit PCM bytes         */
/************************************************************************/
WORD FAR PASCAL PL2G16toP08 (_segment _sBufSeg, GENBASPTR psSrcBuf,
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
wpstrt:     mov     ax, _sBufSeg
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
            SAR3    (ax)                // AL = 8 bit two's comp PCM
            CHKOVRP08 (ax,1)            // Check for over range
            add     al, 80h             // AL = 8 bit magnitude PCM
            mov     dl, al              // DL = 8 bit PCM
            lodsw                       // AX = 2nd waveform value
            SAR3    (ax)                // AL = 8 bit two's comp PCM
            CHKOVRP08 (ax,2)            // Check for over range
            add     al, 80h             // AL = 8 bit magnitude PCM
            mov     ah, al              // AH = 2nd 8 bit PCM
            mov     al, dl              // AL = 1st 8 bit PCM
            stosw                       // Set 8 bit PCM array value
decset:     loop    fstwrd              // Continue with sample set?
            mov     al, ah              // AL = 2nd smp (for setret)

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstwrd:     test    usSmpCnt, 01h       // No, straggler in set?
            jz      setret              // No, finish set
            lodsw                       // AX = waveform value
            SAR3    (ax)                // AL = 8 bit two's comp PCM
            CHKOVRP08 (ax,3)            // Check for over range
            add     al, 80h             // AL = 8 bit magnitude PCM
            stosb                       // Set 8 bit PCM array value

            //***********************************************************
            // End of waveform sequence - set return values
            //***********************************************************
setret:     AL_TOW_AX                   // AX = 11 bit two's comp PCM
            mov     tbTCM.gsCurWav, ax  // AX = Ending waveform value
  
            //***********************************************************
wpdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;                   /* Set TCM block            */
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 1);               /* Full byte output count   */
  
}

/************************************************************************/
/*      Convert PCM bytes to a word oscillation array                   */
/*          Note:  ulSetSiz must be non-zero, > 2 and < 64K.            */
/*                 ulSetSiz should be even for maximum throughput       */
/*          PCM:   0 to ff, midrange = 80                               */
/*                 Magnitude - 80h = signed, Signed + 80h = Mag         */
/************************************************************************/
WORD FAR PASCAL PL2P08toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
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
            mov     ax, tbTCM.gsCurWav  // AX = Starting waveform value
            SAR3    (ax)                // AX = 8 bit two's comp PCM
            add     al, 80h             // AL = 8 bit magnitude PCM
            mov     dl, al              // Set initial minimum
            mov     dh, al              // Set initial maximum
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
            cmp     al, dl              // AL < current minimum?
            ja      tsthi1              // No, continue (unsigned)
            mov     dl, al              // Yes, set new minimum
tsthi1:     cmp     al, dh              // AL > current maximum?
            jb      secbyt              // No, continue (unsigned)
            mov     dh, al              // Yes, set new maximum

            //***********************************************************
            // Compute waveform value for 2nd byte, test for min/max
            //***********************************************************
secbyt:     cmp     ah, dl              // AH < current minimum?
            ja      tsthi2              // No, continue (unsigned)
            mov     dl, ah              // Yes, set new minimum
tsthi2:     cmp     ah, dh              // AH > current maximum?
            jb      decset              // No, continue (unsigned)
            mov     dh, ah              // Yes, set new maximum

decset:     loop    fstbyt              // Continue with sample set?
            mov     al, ah              // AL = 2nd smp (for endset)

            //***********************************************************
            // Check for last (odd) sample of at end of word sample set 
            //***********************************************************
lstbyt:     test    usSetSiz, 01h       // No, straggler in set?
            jz      endset              // No, finish set
            lodsb                       // AL = last PCM byte
            cmp     al, dl              // AL < current minimum?
            ja      tsthil              // No, continue (unsigned)
            mov     dl, al              // Yes, set new minimum
tsthil:     cmp     al, dh              // AL > current maximum?
            jb      endset              // No, finish set (unsigned)
            mov     dh, al              // Yes, set new maximum

            //***********************************************************
            // Clean up and end of sample set 
            //***********************************************************
endset:     mov     cl, al              // CL = Current PCM
            mov     al, dl              // AL = Current minimum
            AL_TOW_AX                   // AX = 11 bit two's comp PCM
            stosw                       // Set sample set minimum
            mov     al, dh              // AL = Current maximum
            AL_TOW_AX                   // AX = 11 bit two's comp PCM
            stosw                       // Set sample set maximum
            mov     al, cl              // AL = Current PCM
            dec     usOscCnt            // Done with all oscillations?
            jz      setret              // Yes, set return values
            mov     dl, al              // Set initial minimum
            mov     dh, al              // Set initial maximum
            mov     cx, usSetWrd        // CX = # samples/ oscillation
            jmp     fstbyt              // Continue with next byte
  
            //***********************************************************
            // End of oscillation sequence - set return values
            //***********************************************************
setret:     AL_TOW_AX                   // AX = 11 bit two's comp PCM
            mov     tbTCM.gsCurWav, ax  // AX = Ending waveform value
  
            //***********************************************************
pmdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->tbTCM = tbTCM;               /* Reset ADPCM interface block  */
    return (usOscOrg);                  /* Oscillation output count     */
  
}

/************************************************************************/
/*                      Set Buffer to Silence                           */
/************************************************************************/
WORD FAR PASCAL PL2SiltoP08 (BYTE FAR *lpcDstBuf, WORD usBufSiz)
{
    WORD    usi = usBufSiz;

    while (usi-- > 0) *lpcDstBuf++ = (BYTE) 0x80;
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