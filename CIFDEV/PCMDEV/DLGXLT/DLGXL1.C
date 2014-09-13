/************************************************************************/
/* Dialogic PCM Translator: DlgXl1.c                    V2.00  06/03/92 */
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
/* DltTab = Delta (n) = [+/-] [(nib * step + 2)/4 + (step+4)/8]         */
/* NxtStp = Next stepsize index << 5 [shift for nibble and word addr]   */
/************************************************************************/
#include "dlgxl1.tab"                   /* cs:Step tables               */

/************************************************************************/
/************************************************************************/
#define TS_VAR "_CODE"                  /* Table storage segment        */
#define T_ cs:                          /* Table storage override seg   */

/************************************************************************/
/*      Scan ADPCM nibbles to init wave value, stepsize & offset        */
/*      Note:  usSmpCnt must be non-zero and < 64K                      */
/*             usSmpCnt should be even for most accurate results        */
/************************************************************************/
LPITCB FAR PASCAL DlgA04toIni (LPITCB lpITC)
{
    lmemset (lpITC, 0, sizeof (*lpITC));
    return (lpITC);                     /* Return Init/Term/Cont block  */
}

WORD FAR PASCAL DlgA04toCmp (_segment _sBufSeg, BYTBASPTR pcSrcBuf, 
                WORD FAR *lpusRsv001, WORD usSmpCnt, LPITCB lpITC)
{
    WORD    usSetByt;                   /* # smp pairs/osc (bytes/osc)  */
    APCBLK  abAPC = lpITC->abAPC;       /* Init ADPCM interface block   */

_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Round sample count up to nearest byte, test for zero
            //***********************************************************
chkset:     mov     cx, usSmpCnt        // CX = # samples/ oscillation
            inc     cx                  // CX = smp/osc + 1 (for full byte)
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSetByt, cx        // usSetByt = # bytes/osc
            cmp     usSetByt, 0         // Null request?
            jnz     cistrt              // No,  continue
            jmp     cidone              // Yes, exit
  
            //***********************************************************
            // Initialize registers, conversion parameters
            //***********************************************************
cistrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            // Initialize working registers
            //***********************************************************
            mov     dx, abAPC.gsCurWav  // DX = Starting waveform value
            mov     bx, abAPC.sNxtSIx   // BX = Starting stepsize index
            SHL5    (bx)                // Adjust for table lookup
            mov     si, pcSrcBuf        // SI = &Source buffer
  
            //***********************************************************
            // Check for reset on sample pair
            //***********************************************************
chkres:     lodsb                       // AL = ADPCM pair
            xor     ah, ah              // AH = 0
            mov     di, ax              // DI = ADPCM pair table offset
            test    al, 77h             // Reset pattern?
            jz      cisres              // Yes, possible reset
            mov     abAPC.sResCnt, 0    // Non-zero, Reset counter

            //***********************************************************
            // Compute waveform values for 1st & 2nd nibble
            //***********************************************************
fstnib:     or      bl, T_ SmTab1[di]   // BL = BL || 1st nib shifted & masked
            add     dx, T_ DltTab[bx]   // DX = waveform value
            mov     ax, dx              // AX = 1st nib waveform 
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
            or      bl, T_ SmTab2[di]   // BL = BL || 2nd nib shifted & masked
            add     dx, T_ DltTab[bx]   // DX = waveform value
        
            //***********************************************************
            //***********************************************************
dcfsum:     mov     di, dx              // DI = Saved waveform value
            add     ax, dx              // AX = waveform sum for nib pair
            sar     ax, 1               // AX = normalized sum 
            cwd                         // DX = Sign of AX (extended)
            add     ax, abAPC.sLowSum   // AX = Sum for DC offset (low)
            adc     dx, abAPC.sHghSum   // DX = Sum for DC offset (high)

            //***********************************************************
            // Adaptive DC Filter
            //***********************************************************
            idiv    T_ DCFDiv[bx]       // AX = dc avg waveform value + rem DX
            sub     di, ax              // DI = wave value - dc avg value

            mov     ax, dx              // AX = remainder after division
            cwd                         // DX = Sign of CX (extended)
            mov     abAPC.sLowSum, ax   // sLowSum = remainder after div (low)
            mov     abAPC.sHghSum, dx   // sHghSum = remainder after div (high)

            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
            mov     dx, di              // Restore saved waveform value

decset:     loop    chkres              // Done with sample set?
            jmp     setret              // Yes, set return values

            //***********************************************************
            // Possible reset detected: check/clear & return
            //***********************************************************
cisres:     inc     abAPC.sResCnt       // Update reset counter
            cmp     abAPC.sResCnt, 23   // 48 patterns (approx 23 pairs)?
            jl      fstnib              // Not yet
            mov     bx, 0               // Reset step index
            mov     dx, 0               // Reset waveform
            mov     abAPC.sLowSum, 0    // Reset DC offset low
            mov     abAPC.sHghSum, 0    // Reset DC offset high
            mov     abAPC.sResCnt, 0    // Reset counter
            jmp     fstnib              // Continue
  
            //***********************************************************
            // End of sample sequence - set return values
            //***********************************************************
setret:     mov     abAPC.gsCurWav, dx  // DX = Ending waveform value
            SHR5    (bx)                // Adjust for table lookup
            mov     abAPC.sNxtSIx, bx   // BX = Ending stepsize index
  
            //***********************************************************
            //***********************************************************
cidone:     CPOPA                       // Pop c language regs
  
}

    lpITC->abAPC = abAPC;               /* Reset ADPCM interface block  */
    return (usSmpCnt); 
  
}

/************************************************************************/
/*      Convert ADPCM nibbles to a 2's complement word array            */
/************************************************************************/
WORD FAR PASCAL DlgA04toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    APCBLK  abAPC = lpITC->abAPC;       /* Init ADPCM interface block   */
    WORD    usSmpCnt = *lpusBytCnt * 2; /* Sample input count           */

    /********************************************************************/
    /* Test for null sample count                                       */
    /********************************************************************/
    if (0 == usSmpCnt) return (0);
  
_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Initialize registers
            //***********************************************************
awstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            // Initialize working registers
            //***********************************************************
            mov     cx, abAPC.gsCurWav  // CX = Starting waveform value
            mov     bx, abAPC.sNxtSIx   // BX = Starting stepsize index
            SHL5    (bx)                // Adjust for table lookup
            mov     si, pcSrcBuf        // SI = &Source buffer
            jmp     chkres              // Begin sample processing

            //***********************************************************
            // Possible reset detected: check/clear & return
            //***********************************************************
posres:     inc     abAPC.sResCnt       // Update reset counter
            cmp     abAPC.sResCnt, 23   // 48 patterns (approx 23 pairs)?
            jl      fstnib              // Not yet
            mov     bx, 0               // Reset step index
            mov     cx, 0               // Reset waveform
            mov     abAPC.sLowSum, 0    // Reset DC offset low
            mov     abAPC.sHghSum, 0    // Reset DC offset high
            mov     abAPC.sResCnt, 0    // Reset counter
            jmp     fstnib              // Continue

            //***********************************************************
            // Compute new waveform value for input byte
            //***********************************************************
chkres:     lodsb                       // AL = ADPCM pair
            xor     ah, ah              // AH = 0
            mov     di, ax              // DI = ADPCM pair table offset
            test    al, 77h             // Reset pattern?
            jz      posres              // Yes
            mov     abAPC.sResCnt, 0    // No, Reset counter
                                           
fstnib:     or      bl, T_ SmTab1[di]   // BL = BL || 1st nib shifted & masked
            add     cx, T_ DltTab[bx]   // CX = waveform value
            mov     ax, cx              // AX = waveform value
            cwd                         // DX = Sign of CX (extended)
            add     ax, abAPC.sLowSum   // AX = Sum for DC offset (low)
            adc     dx, abAPC.sHghSum   // DX = Sum for DC offset (high)
                                           
            //***********************************************************
            // Adaptive DC Filter           
            //***********************************************************
            idiv    T_ DCFDiv[bx]       // AX = dc avg waveform value + rem DX
            sub     cx, ax              // CX = wave value - dc avg value
                                           
            mov     abAPC.sLowSum, dx   // abAPC.sLowSum = remainder after division
            mov     ax, dx              // AX = abAPC.sLowSum
            cwd                         // DX = Sign of AX (extended)
            mov     abAPC.sHghSum, dx   // abAPC.sHghSum = sign extension of abAPC.sLowSum
                                           
            //***********************************************************
store1:     xchg    di, psDstBuf        // Save shifted/masked table ptr (temp)
                                        // DI => waveform array
            mov     [di], cx            // Waveform array = CX
            add     di, 2               // DI++
            xchg    di, psDstBuf        // *psDstBuf++ = Next wave word
                                        // Restore shifted/masked table ptr
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
                                           
tstss1:     dec     usSmpCnt            // Done with sample set?
            jz      setret              // Yes, set return values
                                           
            //***********************************************************
scndnb:     or      bl, T_ SmTab2[di]   // BL = BL || 2nd nib shifted & masked
            add     cx, T_ DltTab[bx]   // CX = waveform value
            mov     ax, cx              // AX = waveform value
            cwd                         // DX = Sign of CX (extended)
            add     ax, abAPC.sLowSum   // AX = Sum for DC offset (low)
            adc     dx, abAPC.sHghSum   // DX = Sum for DC offset (high)
                                           
            //***********************************************************
            // Adaptive DC Filter
            //***********************************************************
            idiv    T_ DCFDiv[bx]       // AX = dc avg waveform value + rem DX
            sub     cx, ax              // CX = wave value - dc avg value
                                           
            mov     abAPC.sLowSum, dx   // abAPC.sLowSum = remainder after division
            mov     ax, dx              // AX = abAPC.sLowSum
            cwd                         // DX = Sign of AX (extended)
            mov     abAPC.sHghSum, dx   // abAPC.sHghSum = sign extension of abAPC.sLowSum
                                           
            //***********************************************************
store2:     xchg    di, psDstBuf        // Save shifted/masked table ptr (temp)
                                        // DI => waveform array
            mov     [di], cx            // Waveform array = CX
            add     di, 2               // DI++
            xchg    di, psDstBuf        // *psDstBuf++ = Next wave word
                                        // Restore shifted/masked table ptr
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
                                           
tstss2:     dec     usSmpCnt            // Done with sample set?
            jnz     chkres              // No, continue
            jmp     setret              // Yes, set return values
                                           
            //***********************************************************
            // End of sample sequence - set return values
            //***********************************************************
setret:     mov     abAPC.gsCurWav, cx  // CX = Ending waveform value
            SHR5    (bx)                // Adjust for table lookup
            mov     abAPC.sNxtSIx, bx   // BX = Ending stepsize index
  
            //***********************************************************
            //***********************************************************
awdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->abAPC = abAPC;                   /* Set ADPCM block          */
    *lpusBytCnt = *lpusBytCnt;              /* Full byte inp count      */
    return (*lpusBytCnt * 2);               /* Sample output count      */                            
  
}

/************************************************************************/
/*      Convert 16 bit 2's complement word to ADPCM                     */
/************************************************************************/
WORD FAR PASCAL DlgG16toA04 (_segment _sBufSeg, GENBASPTR psSrcBuf,
                WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
                WORD usRsv001, LPITCB lpITC)
{
    APCBLK  abAPC = lpITC->abAPC;       /* Init ADPCM interface block   */
    WORD    usSmpCnt = *lpusSmpCnt;     /* Sample input count           */

    /********************************************************************/
    /* Test for null sample count                                       */
    /********************************************************************/
    if (0 == usSmpCnt) return (0);
  
_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Initialize registers
            //***********************************************************
wastrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            // Initialize working registers
            //***********************************************************
            mov     cx, abAPC.gsCurWav  // CX = Starting waveform value
            mov     bx, abAPC.sNxtSIx   // BX = Starting stepsize index
            SHL5    (bx)                // Adjust for table lookup
            mov     si, psSrcBuf        // SI = &Source buffer
            mov     di, pcDstBuf        // DI = &Destination buffer
  
            //***********************************************************
            // Compute new output byte for waveform value
            //***********************************************************
frstnb:     lodsw                       // AX = SI++ -> next waveform value
            sub     ax, cx              // AX = delta for next wave value
            SHL2    (ax)                // AX = next waveform value * 4
            cwd                         // DX = Sign of AX (extended)
            SHR4    (bx)                // Adjust for table word lookup
            idiv    T_ StpTab[bx]       // AX = delta/stepsize + rem DX
            SHL4    (bx)                // Restore for table lookup

            //***********************************************************
            // Convert to ADPCM nibble; correct for overflow
            //***********************************************************
            or      dx, ax              // DX sign = sign of original delta
            and     dx, 8000h           // Isolate sign (+/- zero support)
            xchg    dh, dl              // DL sign = sign of original delta
            and     ax, 007fh           // Isolate 7 bit two's comp delta 
            or      dl, al              // DX = 00 || sign || 7 bit 2's cmp

            xchg    di, dx              // Save DI; DI =>short to nib table
            mov     al, T_ SToSsn[di]   // AL = ADPCM nib shifted & masked
            xchg    dx, di              // Restore DI
            or      bl, al              // BL = BL || nib shifted & masked
            add     cx, T_ DltTab[bx]   // CX = waveform value
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5

            SHL3    (ax)                // Position first sample
            mov     [di], al            // Save for merge with 2nd nibble
        
tstss1:     dec     usSmpCnt            // Done with all samples?
            jz      setret              // Yes, set return values
  
            //***********************************************************
scndnb:     lodsw                       // AX = SI++ -> next waveform value
            sub     ax, cx              // AX = delta for next wave value
            SHL2    (ax)                // AX = next waveform value * 4
            cwd                         // DX = Sign of AX (extended)
            SHR4    (bx)                // Adjust for table word lookup
            idiv    T_ StpTab[bx]       // AX = delta/stepsize + rem DX
            SHL4    (bx)                // Restore for table lookup

            //***********************************************************
            // Convert to ADPCM nibble//  correct for overflow
            //***********************************************************
            or      dx, ax              // DX sign = sign of original delta
            and     dx, 8000h           // Isolate sign (+/- zero support)
            xchg    dh, dl              // DL sign = sign of orginal delta
            and     ax, 007fh           // Isolate 7 bit two's comp delta 
            or      dl, al              // DX = 00 || sign || 7 bit 2's cmp

            xchg    di, dx              // Save DI; DI =>short to nib table
            mov     al, T_ SToSsn[di]   // AL = ADPCM nib shifted & masked
            xchg    dx, di              // Restore DI
            or      bl, al              // BL = BL || nib shifted & masked
            add     cx, T_ DltTab[bx]   // CX = waveform value
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5

            shr     ax, 1               // Position second sample
            or      [di], al            // Merge with 1st nibble
            inc     di                  // DI++ -> ADPCM sample array
  
tstss2:     dec     usSmpCnt            // No, done with all samples?
            jz      setret              // Yes, set return values
            jmp     frstnb              // No, continue
  
            //***********************************************************
            // End of waveform sequence - set return values
            //***********************************************************
setret:     mov     abAPC.gsCurWav, cx  // CX = Ending waveform value
            SHR5    (bx)                // Adjust for table lookup
            mov     abAPC.sNxtSIx, bx   // BX = Ending stepsize index
  
            //***********************************************************
            //***********************************************************
wadone:     CPOPA                       // Pop c language regs
  
}

    lpITC->abAPC = abAPC;                   /* Set ADPCM block          */
    *lpusSmpCnt = *lpusSmpCnt;              /* Sample input count       */
    return (*lpusSmpCnt / 2);               /* Full byte output count   */
  
}

/************************************************************************/
/*      Convert ADPCM nibbles to a word pair oscillation array          */
/*      Note:  ulSetSiz must be non-zero and < 64K                      */
/*             ulSetSiz should be even for most accurate results        */
/************************************************************************/
WORD FAR PASCAL DlgA04toM32 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
                WORD FAR *lpusRsv001, GENBASPTR psDstBuf, 
                WORD usOscCnt, DWORD ulSetSiz, LPITCB lpITC)
{
    WORD    usSetByt;                   /* # smp pairs/osc (bytes/osc)  */
    WORD    usDthOdd;                   /* Dither odd set size counter  */
    WORD    usSetSiz;                   /* 64K limited set size         */
    WORD    sCurMin;                    /* Current minimum oscillation  */
    WORD    sCurMax;                    /* Current maximum oscillation  */
    WORD    usOscOrg = usOscCnt;        /* Original oscillation count   */
    APCBLK  abAPC = lpITC->abAPC;       /* Init ADPCM interface block   */

    /********************************************************************/
    /* Test for null oscillation count, set size range                  */
    /********************************************************************/
    if (0 == usOscCnt) return (0);
    usSetSiz = (WORD) min (ulSetSiz, 0xffffL); 

_asm {
            CPUSHA                      // Push c language regs

            //***********************************************************
            // Round set size count down to nearest byte, test for zero
            //***********************************************************
chkset:     mov     cx, usSetSiz        // CX = # samples/ oscillation
            shr     cx, 1               // CX = # smp pairs/osc (bytes/osc)
            mov     usSetByt, cx        // SetByt = # bytes/osc
            cmp     usSetByt, 0         // Null request?
            jnz     amstrt              // No,  continue
            jmp     amdone              // Yes, exit
  
            //***********************************************************
            // Initialize registers, conversion parameters
            //***********************************************************
amstrt:     mov     ax, _sBufSeg
            mov     ds, ax              // DS = Src/Dst buf segment
            mov     es, ax              // ES = DS
            cld                         // Clear direction flag (+)

            //***********************************************************
            // Initialize working registers
            //***********************************************************
            mov     dx, abAPC.gsCurWav  // DX = Starting waveform value
            mov     bx, abAPC.sNxtSIx   // BX = Starting stepsize index
            SHL5    (bx)                // Adjust for table lookup
            mov     si, pcSrcBuf        // SI = &Source buffer
            mov     sCurMin, dx         // Set initial minimum
            mov     sCurMax, dx         // Set initial maximum
            mov     usDthOdd, 0         // Init odd dither counter
  
            //***********************************************************
            // Check for reset on sample pair
            //***********************************************************
chkres:     lodsb                       // AL = ADPCM pair
            xor     ah, ah              // AH = 0
            mov     di, ax              // DI = ADPCM pair table offset
            test    al, 77h             // Reset pattern?
            jz      posres              // Yes, possible reset
            mov     abAPC.sResCnt, 0    // Non-zero, Reset counter
  
            //***********************************************************
            // Compute waveform values for 1st & 2nd nibble
            //***********************************************************
fstnib:     or      bl, T_ SmTab1[di]   // BL = BL || 1st nib shifted & masked
            add     dx, T_ DltTab[bx]   // DX = waveform value
            mov     ax, dx              // AX = 1st nib waveform 
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
            or      bl, T_ SmTab2[di]   // BL = BL || 2nd nib shifted & masked
            add     dx, T_ DltTab[bx]   // DX = waveform value
            mov     bx, T_ NxtStp[bx]   // BX = next step index << 5
        
            //***********************************************************
            //***********************************************************
tstlo1:     cmp     ax, dx              // 1st nib < 2nd nib?
            jg      tstlo2              // No, continue
            cmp     ax, sCurMin         // 1st nib < current minimum?
            jg      tsthi1              // No, continue
            mov     sCurMin, ax         // Yes, set new minimum
            jmp     tsthi1              // Continue
tstlo2:     cmp     dx, sCurMin         // 2nd nib < current minimum?
            jg      tsthi1              // No, continue
            mov     sCurMin, dx         // Yes, set new minimum

tsthi1:     cmp     ax, dx              // 1st nib > 2nd nib?
            jl      tsthi2              // No, continue
            cmp     ax, sCurMax         // 1st nib > current minimum?
            jl      dcfsum              // No, continue
            mov     sCurMax, ax         // Yes, set new maximum
tsthi2:     cmp     dx, sCurMax         // 2nd nib > current maximum?
            jl      dcfsum              // No, continue
            mov     sCurMax, dx         // Yes, set new maximum

            //***********************************************************
            //***********************************************************
dcfsum:     mov     di, dx              // DI = Saved waveform value
            add     ax, dx              // AX = waveform sum for nib pair
            cwd                         // DX = Sign of AX (extended)
            add     abAPC.sLowSum, ax   // Sum for DC offset (low)
            adc     abAPC.sHghSum, dx   // Sum for DC offset (high)
            mov     dx, di              // Restore saved waveform value

decset:     loop    chkres              // Done with sample set?
            jmp     endset              // Yes, clean up sample set

            //***********************************************************
            // Possible reset detected: check/clear & return
            //***********************************************************
posres:     inc     abAPC.sResCnt       // Update reset counter
            cmp     abAPC.sResCnt, 23   // 48 patterns (approx 23 pairs)?
            jl      fstnib              // Not yet
            mov     bx, 0               // Reset step index
            mov     dx, 0               // Reset waveform
            mov     abAPC.sLowSum, 0    // Reset DC offset low
            mov     abAPC.sHghSum, 0    // Reset DC offset high
            mov     abAPC.sResCnt, 0    // Reset counter
            jmp     fstnib              // Continue

            //***********************************************************
            // Compute DC offset & subtract.
            // Clean up and end of sample set.
            // Dither usSetByt for non-even usSetSiz.
            //***********************************************************
endset:     mov     cx, dx              // CX = waveform value
            mov     ax, abAPC.sLowSum   // AX = Sum for DC offset (low)
            mov     dx, abAPC.sHghSum   // DX = Sum for DC offset (high)
            idiv    usSetSiz            // AX = dc avg waveform value + rem DX
            sub     cx, ax              // CX = wave value - dc avg value
            sub     sCurMin, ax         // sCurMin = Current min - dc avg value
            sub     sCurMax, ax         // sCurMax = Current max - dc avg value
            mov     ax, dx              // AX = DC offset low remainder
            cwd                         // DX = Sign of AX (extended)
            mov     abAPC.sLowSum, ax   // Set DC offset (low)
            mov     abAPC.sHghSum, dx   // Set DC offset (high)

            //***********************************************************
            xchg    di, psDstBuf        // Save cvt table ptr, DI => Osc array
            mov     ax, sCurMin         // AX = Current minimum
            stosw                       // Set sample set minimum
            mov     ax, sCurMax         // AX = Current maximum
            stosw                       // Set sample set maximum
            xchg    psDstBuf, di        // Save psDstBuf++, DI => cvt table
            mov     dx, cx              // DX = waveform value
            dec     usOscCnt            // Done with all oscillations?
            jz      setret              // Yes, set return values
            mov     sCurMin, dx         // Set initial minimum
            mov     sCurMax, dx         // Set initial maximum

            ;***********************************************************
            ; Perform dither operation
            ;***********************************************************
            mov     cx, usSetSiz        // CX = # smp/osc (nibbles/osc)
            xor     cx, usDthOdd        // Toggle dither if odd usSetSiz 
            and     cx, 01h             // Mask dither bit
            mov     usDthOdd, cx        // Set new dither counter
            add     cx, usSetByt        // CX = dithered # smp pairs/osc

            jmp     chkres              // Continue with next pair
  
            //***********************************************************
            // End of oscillation sequence - set return values
            //***********************************************************
setret:     mov     abAPC.gsCurWav, dx  // DX = Ending waveform value
            SHR5    (bx)                // Adjust for table lookup
            mov     abAPC.sNxtSIx, bx   // BX = Ending stepsize index
  
            //***********************************************************
            //***********************************************************
amdone:     CPOPA                       // Pop c language regs
  
}

    lpITC->abAPC = abAPC;               /* Reset ADPCM interface block  */
    return (usOscOrg);                  /* Oscillation output count     */
  
}

/************************************************************************/
/*                      Set Buffer to Silence                           */
/************************************************************************/
WORD FAR PASCAL DlgSiltoA04 (BYTE FAR *lpcDstBuf, WORD usBufSiz)
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