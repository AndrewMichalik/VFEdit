/** msadpcm.h
 *
 *  DESCRIPTION:
 *
 *
 **/

#ifndef _MSADPCM_H_
#define _MSADPCM_H_

//
//  function prototypes from MSADPCM.C
//
DWORD FAR PASCAL adpcmDecode4Bit(LPADPCMWAVEFORMAT lpwfADPCM, HPSTR hpSrc, LPPCMWAVEFORMAT lpwfPCM, HPSTR hpDst, DWORD dwSrcLen, DWORD dwDstLen, WORD FAR *);
DWORD FAR PASCAL adpcmEncode4Bit(LPPCMWAVEFORMAT lpwfPCM, HPSTR hpSrc, LPADPCMWAVEFORMAT lpwfADPCM, HPSTR hpDst, DWORD dwSrcLen, WORD FAR *);

//
//  support functions (also in MSADPCM.C)
//
BOOL FAR PASCAL pcmIsValidFormat(LPWAVEFORMATEX lpwfx);
BOOL FAR PASCAL adpcmIsValidFormat(LPWAVEFORMATEX lpwfx);
BOOL FAR PASCAL adpcmBuildFormatHeader(LPWAVEFORMATEX lpwfxSrc, LPWAVEFORMATEX lpwfxDst);

#endif

/** EOF: msadpcm.h **/
