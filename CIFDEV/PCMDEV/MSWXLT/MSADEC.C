/************************************************************************/
/* Microsoft ADPCM Decoder: MSADec.c                    V2.00  10/15/95 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define STRICT
#include "windows.h"
#include "windowsx.h"
#include "mmsystem.h"
#include "mmreg.h"
#include "msadpcm.h"

#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */

//
//  constants used by the Microsoft 4 Bit ADPCM algorithm
//
//  CAUTION: the code contained in this file assumes that the number of
//  channels will be no greater than 2! this is for minor optimization
//  purposes and would be very easy to change if >2 channels is required.
//  it also assumes that the PCM data will either be 8 or 16 bit.
//
//  the code to look out for looks 'similar' to this:
//
//      PCM.BytesPerSample = (PCM.BitsPerSample >> 3) << (Channels >> 1);
//
#define MSADPCM_NUM_COEF        (7)
#define MSADPCM_MAX_CHANNELS    (2)

#define MSADPCM_CSCALE          (8)
#define MSADPCM_PSCALE          (8)
#define MSADPCM_CSCALE_NUM      (1 << MSADPCM_CSCALE)
#define MSADPCM_PSCALE_NUM      (1 << MSADPCM_PSCALE)

#define MSADPCM_DELTA4_MIN      (16)

#define MSADPCM_OUTPUT4_MAX     (7)
#define MSADPCM_OUTPUT4_MIN     (-8)


//
//  Fixed point Delta adaption table:
//
//      Next Delta = Delta * gaiP4[ this output ] / MSADPCM_PSCALE
//
static short  gaiP4[] = { 230, 230, 230, 230, 307, 409, 512, 614,
                          768, 614, 512, 409, 307, 230, 230, 230 };


/** DWORD FAR PASCAL adpcmDecode4Bit(LPADPCMWAVEFORMAT lpwfADPCM, HPSTR hpSrc, LPPCMWAVEFORMAT lpwfPCM, HPSTR hpDst, DWORD dwSrcLen)
 *
 *  DESCRIPTION:
 *      
 *
 *  ARGUMENTS:
 *      (LPADPCMWAVEFORMAT lpwfADPCM, HPSTR hpSrc, LPPCMWAVEFORMAT lpwfPCM, HPSTR hpDst, DWORD dwSrcLen)
 *
 *  RETURN (DWORD FAR PASCAL):
 *
 *
 *  NOTES:
 *
 **  */

DWORD FAR PASCAL adpcmDecode4Bit(LPADPCMWAVEFORMAT lpwfADPCM, HPSTR hpSrc, 
                 LPPCMWAVEFORMAT lpwfPCM, HPSTR hpDst, DWORD dwSrcLen, 
                 DWORD dwDstLen, WORD FAR *lpErrCod)
{
    short   iInput;
    short   iNextInput;
    short   iFirstNibble;
    short   iDelta;
    long    lSamp;
    long    lPrediction;
    BYTE    bPredictors;
    BYTE    bChannels;
    BYTE    bBitsPerSample;
    BYTE    m;
    WORD    n;
    WORD    wSamplesPerBlock;
    WORD    wBlockHeaderBytes;
    DWORD   dwTotalPos;
    DWORD   dwDecoded;
    short   aiSamp1[MSADPCM_MAX_CHANNELS];
    short   aiSamp2[MSADPCM_MAX_CHANNELS];
    short   aiCoef1[MSADPCM_MAX_CHANNELS];
    short   aiCoef2[MSADPCM_MAX_CHANNELS];
    short   aiDelta[MSADPCM_MAX_CHANNELS];
    LPADPCMCOEFSET  lpCoefSet;

//ajm
*lpErrCod = 0;
//ajm

    //
    //  put some commonly used info in more accessible variables and init
    //  the wBlockHeaderBytes, dwDecoded and dwTotalPos vars...
    //
    lpCoefSet           = &lpwfADPCM->aCoef[0];
    bPredictors         = (BYTE)lpwfADPCM->wNumCoef;
    bChannels           = (BYTE)lpwfADPCM->wfx.nChannels;
    bBitsPerSample      = (BYTE)lpwfPCM->wBitsPerSample;
    wSamplesPerBlock    = lpwfADPCM->wSamplesPerBlock;
    wBlockHeaderBytes   = bChannels * 7;
    dwDecoded           = 0L;
    dwTotalPos          = 0L;


    //
    //  step through each byte of ADPCM data and decode it to the requested
    //  PCM format (8 or 16 bit).
    //
    while (dwTotalPos < dwSrcLen)
    {
        //
        //  the first thing we need to do with each block of ADPCM data is
        //  to read the header which consists of 7 bytes of data per channel.
        //  so our first check is to make sure that we have _at least_
        //  enough input data for a complete ADPCM block header--if there
        //  is not enough data for the header, then exit.
        //
        //  the header looks like this:
        //      1 byte predictor per channel
        //      2 byte delta per channel
        //      2 byte first sample per channel
        //      2 byte second sample per channel
        //
        //  this gives us (7 * bChannels) bytes of header information. note
        //  that as long as there is _at least_ (7 * bChannels) of header
        //  info, we will grab the two samples from the header (and if no
        //  data exists following the header we will exit in the decode
        //  loop below).
        //
        dwTotalPos += wBlockHeaderBytes;
        if (dwTotalPos > dwSrcLen)
            goto adpcmDecode4BitExit;
            
        //
        //  grab and validate the predictor for each channel
        //
        for (m = 0; m < bChannels; m++)
        {
            BYTE    bPredictor;

            bPredictor = (BYTE)(*hpSrc++);
            if (bPredictor >=  bPredictors)
            {
                //
                //  the predictor is out of range--this is considered a
                //  fatal error with the ADPCM data, so we fail by returning
                //  zero bytes decoded
                //
                dwDecoded = 0;
//ajm
*lpErrCod = (WORD) -1;
//ajm
                goto adpcmDecode4BitExit;
            }

            //
            //  get the coefficients for the predictor index
            //
            aiCoef1[m] = lpCoefSet[bPredictor].iCoef1;
            aiCoef2[m] = lpCoefSet[bPredictor].iCoef2;
        }
        
        //
        //  get the starting delta for each channel
        //
        for (m = 0; m < bChannels; m++)
        {
            aiDelta[m] = *(short huge *)hpSrc;
            hpSrc++;
            hpSrc++;
        }

        //
        //  get the sample just previous to the first encoded sample per
        //  channel
        //
        for (m = 0; m < bChannels; m++)
        {
            aiSamp1[m] = *(short huge *)hpSrc;
            hpSrc++;
            hpSrc++;
        }

        //
        //  get the sample previous to aiSamp1[x] per channel
        //
        for (m = 0; m < bChannels; m++)
        {
            aiSamp2[m] = *(short huge *)hpSrc;
            hpSrc++;
            hpSrc++;
        }


        //
        //  write out first 2 samples for each channel.
        //
        //  NOTE: the samples are written to the destination PCM buffer
        //  in the _reverse_ order that they are in the header block:
        //  remember that aiSamp2[x] is the _previous_ sample to aiSamp1[x].
        //
        if (bBitsPerSample == (BYTE)8)
        {
            for (m = 0; m < bChannels; m++)
            {
                *hpDst++ = (char)((aiSamp2[m] >> 8) + 128);
            }
            for (m = 0; m < bChannels; m++)
            {
                *hpDst++ = (char)((aiSamp1[m] >> 8) + 128);
            }
        }
        else
        {
            for (m = 0; m < bChannels; m++)
            {
                *(short huge *)hpDst = aiSamp2[m];
                hpDst++;
                hpDst++;
            }
            for (m = 0; m < bChannels; m++)
            {
                *(short huge *)hpDst = aiSamp1[m];
                hpDst++;
                hpDst++;
            }
        }

        //
        //  we have decoded the first two samples for this block, so add
        //  two to our decoded count
        //
        dwDecoded += 2;


        //
        //  we now need to decode the 'data' section of the ADPCM block.
        //  this consists of packed 4 bit nibbles.
        //
        //  NOTE: we start our count for the number of data bytes to decode
        //  at 2 because we have already decoded the first 2 samples in
        //  this block.
        //
        iFirstNibble = 1;
        for (n = 2; n < wSamplesPerBlock; n++)
        {
            for (m = 0; m < bChannels; m++)
            {
                if (iFirstNibble)
                {
                    //
                    //  we need to grab the next byte to decode--make sure
                    //  that there is a byte for us to grab before continue
                    //
                    dwTotalPos++;
                    if (dwTotalPos > dwSrcLen)
                        goto adpcmDecode4BitExit;

                    //
                    //  grab the next two nibbles and create sign extended
                    //  integers out of them:
                    //
                    //      iInput is the first nibble to decode
                    //      iNextInput will be the next nibble decoded
                    //
                    iNextInput  = (short)*hpSrc++;
                    iInput      = iNextInput >> 4;
                    iNextInput  = (iNextInput << 12) >> 12;

                    iFirstNibble = 0;
                }
                else
                {
                    //
                    //  put the next sign extended nibble into iInput and
                    //  decode it--also set iFirstNibble back to 1 so we
                    //  will read another byte from the source stream on
                    //  the next iteration...
                    //
                    iInput = iNextInput;
                    iFirstNibble = 1;
                }


                //
                //  compute the next Adaptive Scale Factor (ASF) and put
                //  this value in aiDelta for the current channel.
                //
                iDelta = aiDelta[m];
                aiDelta[m] = (short)((gaiP4[iInput & 15] * (long)iDelta) >> MSADPCM_PSCALE);
                if (aiDelta[m] < MSADPCM_DELTA4_MIN)
                    aiDelta[m] = MSADPCM_DELTA4_MIN;

                //
                //  decode iInput (the sign extended 4 bit nibble)--there are
                //  two steps to this:
                //
                //  1.  predict the next sample using the previous two
                //      samples and the predictor coefficients:
                //
                //      Prediction = (aiSamp1[channel] * aiCoef1[channel] + 
                //              aiSamp2[channel] * aiCoef2[channel]) / 256;
                //
                //  2.  reconstruct the original PCM sample using the encoded
                //      sample (iInput), the Adaptive Scale Factor (aiDelta)
                //      and the prediction value computed in step 1 above.
                //
                //      Sample = (iInput * aiDelta[channel]) + Prediction;
                //
                lPrediction = (((long)aiSamp1[m] * aiCoef1[m]) +
                                ((long)aiSamp2[m] * aiCoef2[m])) >> MSADPCM_CSCALE;
                lSamp = ((long)iInput * iDelta) + lPrediction;

                //
                //  now we need to clamp lSamp to [-32768..32767]--this value
                //  will then be a valid 16 bit sample.
                //
                if (lSamp > 32767)
                    lSamp = 32767;
                else if (lSamp < -32768)
                    lSamp = -32768;
        
                //
                //  lSamp contains the decoded iInput sample--now write it
                //  out to the destination buffer
                //
                if (bBitsPerSample == (BYTE)8)
                {
                    *hpDst++ = (char)(((short)lSamp >> 8) + 128);
                }
                else
                {
                    *(short huge *)hpDst = (short)lSamp;
                    hpDst++;
                    hpDst++;
                }
                
                //
                //  ripple our previous samples down making the new aiSamp1
                //  equal to the sample we just decoded
                //
                aiSamp2[m] = aiSamp1[m];
                aiSamp1[m] = (short)lSamp;
            }

            //
            //  we have decoded one more complete sample
            //
            dwDecoded++;
//ajm
if (dwDecoded >= dwDstLen)
    goto adpcmDecode4BitExit;
//ajm
        }
//ajm
if (lpwfADPCM->wfx.nBlockAlign) {
    WORD    usPadCnt;
    if (usPadCnt = (WORD) (dwTotalPos % (DWORD) lpwfADPCM->wfx.nBlockAlign)) {
        usPadCnt = lpwfADPCM->wfx.nBlockAlign - usPadCnt;
        dwTotalPos += (DWORD) usPadCnt;
        hpSrc += (DWORD) usPadCnt;
    }
}
//ajm
    }

    //
    //  we're done decoding the input data. dwDecoded contains the number
    //  of complete _SAMPLES_ that were decoded. we need to return the
    //  number of _BYTES_ decoded. so calculate the number of bytes per
    //  sample and multiply that with dwDecoded...
    //
adpcmDecode4BitExit:

    return (dwDecoded * ((bBitsPerSample >> (BYTE)3) << (bChannels >> 1)));
} /* adpcmDecode4Bit() */




