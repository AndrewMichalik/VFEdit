/************************************************************************/
/* CCITT G.711 PCM Translator: G11Xl1.c                 V2.00  11/22/93 */
/* Copyright (c) 1987-1993 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/* Author:  JMS.  Adapted from template by AJM */
#include "visdef.h"                     /* Standard type definitions    */
#include "..\genpcm.h"                  /* PCM/APCM conversion defs     */
#include "..\pcmsup.h"                  /* PCM/APCM xlate lib defs      */
#include "gsm.h"                        /* GSM client header            */  
#include "gsmxlt.h"                     /* Glue GSM defs. to ours       */
#include <stdlib.h>                     /* Misc string/math/error funcs */

/************************************************************************/
/* Initialize a GSM state block                                         */
/************************************************************************/
gsmBLK* FAR PASCAL GSMIni (gsmBLK* g)
{
	gsm_init(g);
	return g;
}

/************************************************************************/
/*      Convert GSM bytes to 16-bit two's comp. waveform values         */
/*      Tell caller how many bytes were consumed and how many output    */
/*      samples were produced.                                          */
/************************************************************************/
WORD FAR PASCAL GSMP33toG16 (_segment _sBufSeg, BYTBASPTR pcSrcBuf,
		WORD FAR *lpusBytCnt, GENBASPTR psDstBuf, 
		WORD usRsv001, gsm g)
{
    WORD    usi;
    WORD    usinputLeftOver = *lpusBytCnt % GSM_CMP_BLOCK;
    WORD    usn = 0;
    /********************************************************************/
    /********************************************************************/
    /* Tell caller how many input bytes we'll uncompress.  (No partial blocks.) */
    *lpusBytCnt -= usinputLeftOver;
    usi = *lpusBytCnt;

    while ( (usi -= GSM_CMP_BLOCK) > 0) {
	gsm_decode(g, _sBufSeg:>pcSrcBuf, _sBufSeg:>psDstBuf);
	pcSrcBuf += GSM_CMP_BLOCK;
	psDstBuf += GSM_SAMPLE_BLOCK; 
	usn += GSM_SAMPLE_BLOCK;
    }

    /********************************************************************/
    /********************************************************************/
    return usn;                /* Sample output count      */                            
}
/************************************************************************/
/*      Convert 16-bit two's comp. waveform values to GSM bytes         */
/*      Tell caller how many samples were consumed and how many output  */
/*      bytes were produced.                                            */
/************************************************************************/

WORD FAR PASCAL GSMG16toP33 (_segment _sBufSeg, GENBASPTR psSrcBuf,
		WORD FAR *lpusSmpCnt, BYTBASPTR pcDstBuf, 
		WORD usRsv001, gsm g)
{
    WORD    usi;
    WORD    usinputLeftOver = *lpusSmpCnt % GSM_SAMPLE_BLOCK;
    WORD    usnByte = 0;

    /********************************************************************/
    /********************************************************************/
    /* Tell caller how many samples we'll do.  (No partial blocks.) */
    *lpusSmpCnt -= usinputLeftOver;
    usi = *lpusSmpCnt;
    while ( (usi -= GSM_SAMPLE_BLOCK) > 0) {
	gsm_encode(g, _sBufSeg:>psSrcBuf, _sBufSeg:>pcDstBuf);
	psSrcBuf += GSM_SAMPLE_BLOCK;
	pcDstBuf += GSM_CMP_BLOCK; 
	usnByte += GSM_CMP_BLOCK;
    }

    /********************************************************************/
    /********************************************************************/
    return (usnByte);               /* Full byte output count   */

}
/************************************************************************/
/*      Create compressed silence.  Come as close as possible to        */
/*      filling the output array.  Tell caller how many bytes were      */
/*      produced.                                                       */
/*      Since this routine uses its own gsmBLK, it will probably not    */
/*      produce quite the right results if its output is inserted in    */
/*      the middle of a stream of other GSM compressed bytes.  Damped   */
/*      oscillations usually result.  Some users are willing to accept  */
/*      that in exchange for speed.                                     */
/************************************************************************/

WORD FAR PASCAL GSMSiltoP33 (BYTE FAR *lpucDstBuf, WORD usBufSiz)
{
    gsmBLK g;
    static gsm_signal silence[GSM_SAMPLE_BLOCK];        /* All zeroes */
    WORD usinputLeftOver = usBufSiz % GSM_CMP_BLOCK;
    WORD usi;
    gsm_init(&g);
    usBufSiz -= usinputLeftOver;
    usi = usBufSiz;
    while ( (usi -= GSM_CMP_BLOCK) > 0) {
	gsm_encode(&g, silence, lpucDstBuf);
	lpucDstBuf += GSM_CMP_BLOCK;
    }

    return usBufSiz;
}
