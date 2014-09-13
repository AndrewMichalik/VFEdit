/////////////////////////////////////////////////////////////////////////////
// SesEff.cpp : Implementation of the CSesEff classes
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "sesedt.h"						// Audio session edit support defs
#include "audeff.h"						// Audio effects support defs

extern "C"
{
	#include <math.h>					// Math library defs
}

/////////////////////////////////////////////////////////////////////////////
// Compressor / Expander interface structure
/////////////////////////////////////////////////////////////////////////////
typedef struct _CMPEXP {
	float	flCmpThr;
	DWORD	ulCmpAtk;
	float	flCmpMin;
	float	flExpThr;
	DWORD	ulExpAtk;
	float	flExpMax;
	DWORD	ulCE_Dcy;
	float	flNoiThr;
	float	flNoiAtt;
} CMPEXP;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEffChgFrq (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flFrqMul, WORD usAAFAlg, 
						WORD usResAlg, const char *pszDesStr) 
{
	WORD		usRetCod;
	CSesEdt 	seTmpEdt;
	DWORD		ulDstFrq;
	DWORD		ulTmpOff = 0L;
	DWORD		ulTmpCnt = 0L;
	DWORD		ulPstSmp = ulSmpCnt;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Calculate required "source freq" to achieve "destination freq" shift
	/////////////////////////////////////////////////////////////////////////
	if (flFrqMul <= 0) return (0);	
	if (!(ulDstFrq = (DWORD) (pSesEdt->GetSmpFrq() / flFrqMul))) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Duplicate characteristics of an existing session file
	// Override frequency setting
	/////////////////////////////////////////////////////////////////////////
	PCMTYP	usPCMTyp = pSesEdt->GetPCMTyp();
	WORD 	usChnCnt = pSesEdt->GetChnCnt(); 
	WORD 	usEncMsk = pSesEdt->GetEncMsk();

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = seTmpEdt.SesFilOpn ("", 0, NULL, &usPCMTyp, &usChnCnt, 
		&ulDstFrq, pSesEdt->GetTmpDir(), pSesEdt->GetFIOCBk()->m_hPolWnd, 
		pSesEdt->GetFIOCBk()->m_nMsgPrm)) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Convert to new frequency and store in temporary file
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = seTmpEdt.AudFilRep (&ulTmpOff, &ulTmpCnt, TRUE,
		usAAFAlg, usResAlg, pSesEdt, &ulSmpOff, &ulPstSmp, FALSE, NULL)) 
		return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Paste back into original, force resampling to "none"
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = pSesEdt->AudFilRep (&ulSmpOff, &ulSmpCnt, TRUE, usAAFAlg, 
		CEffRes::RESALGNON, &seTmpEdt, &ulTmpOff, &ulPstSmp, FALSE, pszDesStr)) 
		return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (ulSmpOff + ulSmpCnt, ulPstSmp - ulSmpCnt);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);
}

extern "C"
WORD FAR PASCAL _export SesEffCmpExp (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, CMPEXP FAR *lpCmpExp, const char *pszDesStr)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	CEffDCE	aeEffDCE (pSesEdt->GetPCMTyp(), pSesEdt->GetChnCnt(), 
		pSesEdt->GetSmpFrq(), lpCmpExp->flCmpThr / 100, lpCmpExp->ulCmpAtk, 
        lpCmpExp->flCmpMin, lpCmpExp->flExpThr / 100, lpCmpExp->ulExpAtk, 
        lpCmpExp->flExpMax, lpCmpExp->ulCE_Dcy, lpCmpExp->flNoiThr / 100, 
        lpCmpExp->flNoiAtt);

	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffDCE, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEffEchDec (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flDlyTim, float flDec_dB,
						const char *pszDesStr) 
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

// ajm 03/18/96 - should zero delay do anything?
/////////////////////////////////////////////////////////////////////////
// Ignore request if delay time is zero
/////////////////////////////////////////////////////////////////////////
if (!(DWORD) (flDlyTim * pSesEdt->GetSmpFrq())) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Prepare echo delay buffers and data stream
	/////////////////////////////////////////////////////////////////////////
	CEffEch	aeEffEch (0, (DWORD) (flDlyTim * pSesEdt->GetSmpFrq()), flDec_dB);

	/////////////////////////////////////////////////////////////////////////
	// Apply echo effect
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffEch, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEffFad_IO (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flFadBeg, float flFadEnd, 
						WORD usFadAlg, const char *pszDesStr) 
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Perform fade operation
	/////////////////////////////////////////////////////////////////////////
	CEffFad	aeEffFad (usFadAlg, flFadBeg, flFadEnd, ulSmpCnt);
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffFad, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);
	
	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEffFrqEqu (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, WORD usFFTOrd, float FAR *lpEquArr, 
						WORD usEquBnd, float flEquGai, const char *pszDesStr)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Check parameters
	/////////////////////////////////////////////////////////////////////////
	if (usEquBnd > FEQMAXCNT) return (-1);
	
	/////////////////////////////////////////////////////////////////////////
	// Initialize graphic equalizer
	/////////////////////////////////////////////////////////////////////////
	CEffEqu aeEffEqu (usFFTOrd, pSesEdt->GetSmpFrq(), usEquBnd, 
		lpEquArr, flEquGai);

	/////////////////////////////////////////////////////////////////////////
	// Filter and update display
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffEqu, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export SesEffMixFil (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, WORD usMixCnt, CAudFil FAR **ppMixFil, 
						float FAR *pflFdITim, WORD FAR *pusMixLvl, 
						float FAR *pflFdOTim, WORD usAAFAlg, WORD usResAlg, 
						const char *pszDesStr)
{
	WORD	usRetCod;
	WORD	usi;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Check for valid array of mix files
	/////////////////////////////////////////////////////////////////////////
	for (usi = 0; usi < usMixCnt; usi++) {
		if (NULL == ppMixFil[usi]) return (-1);
	}

	/////////////////////////////////////////////////////////////////////////
	// Prepare track data streams
	/////////////////////////////////////////////////////////////////////////
	CEffMix aeEffMix (pSesEdt, pusMixLvl[0], ulSmpOff, &ulSmpCnt, *ppMixFil, 
		pusMixLvl[1], usAAFAlg, usResAlg);

	/////////////////////////////////////////////////////////////////////////
	// Mix all tracks into pSesEdt
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffMix, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEffRedNoi (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flMutThr, float flAtt_dB, 
						const char *pszDesStr) 
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	CEffNoi	aeEffNoi (flMutThr / 100, flAtt_dB, pSesEdt->GetPCMTyp(), 0);	

	/////////////////////////////////////////////////////////////////////////
	// Scan file and lower amplitude on signals below threshold
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffNoi, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEffTonGen (CAudFil FAR *pAudFil, DWORD ulSmpOff, 
						DWORD ulSmpCnt, WORD usSigCnt, 
						CEffTon::TONBLK FAR *lpSigArr, 
						float flTimLen, const char *pszDesStr)
{
	DWORD		ulSmpTot = 0L;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize tone generator
	/////////////////////////////////////////////////////////////////////////
	CEffTon aeEffTon (lpSigArr, usSigCnt, flTimLen, 
		PCMCapQry (pAudFil->GetPCMTyp(), ATDMAXQRY, 0L), pAudFil->GetSmpFrq());

	/////////////////////////////////////////////////////////////////////////
	// Allocate and open the destination file
	// Note: Seek to end for append - do not truncate
	/////////////////////////////////////////////////////////////////////////
	if (!pAudFil->Open(CFile::modeWrite)) return (IDS_OPNFILERR);
	pAudFil->Seek(0L, CFile::end);

	/////////////////////////////////////////////////////////////////////
	// Show/Hide Progress indicator for time consuming operations
	/////////////////////////////////////////////////////////////////////
	pAudFil->GetFIOCBk()->BegCBkPrc ((DWORD) (flTimLen * pAudFil->GetSmpFrq()), 
		IDS_POLACTTON);
	while (TRUE) {
		DWORD	ulSmpOut;
		/////////////////////////////////////////////////////////////////
	 	// Generate tones
		/////////////////////////////////////////////////////////////////
		aeEffTon.ExeEffPrc ();
		ulSmpTot += (ulSmpOut = pAudFil->Write (&aeEffTon));
		if (!ulSmpOut || (-1L == ulSmpOut)) break;
		if (!pAudFil->GetFIOCBk()->CntCBkPrc (ulSmpTot)) break;
	}
	pAudFil->GetFIOCBk()->EndCBkPrc (ulSmpTot);

	/////////////////////////////////////////////////////////////////////////
 	// Update display; close destination
	/////////////////////////////////////////////////////////////////////////
 	pAudFil->Close ();

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

extern "C"
WORD FAR PASCAL _export SesEffVolAdj (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flLvl_dB, const char *pszDesStr) 
{
	CEffVol	aeEffVol (flLvl_dB);
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Adjust volume and update display
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilEff (&ulSmpOff, &ulSmpCnt, &aeEffVol, pszDesStr); 
	pSesEdt->WrkDspUpd (0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

/////////////////////////////////////////////////////////////////////////////
// Non-destructive functions that provide audio analysis information 
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEffNrmLvl (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulSmpCnt, float flNrmLvl, float flNrmExc, 
						float flNrmMax, float FAR *lpLvl_dB) 
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);
	*lpLvl_dB = 0;

	/////////////////////////////////////////////////////////////////////////
	// Scan file for peak audio levels
	/////////////////////////////////////////////////////////////////////////
	if (!pSesEdt->Open (CFile::modeRead)) return (IDS_OPNFILERR);
	pSesEdt->Seek (ulSmpOff);
	*lpLvl_dB = pSesEdt->Read (ulSmpCnt, flNrmLvl / 100, flNrmExc / 100, flNrmMax);
	pSesEdt->Close ();

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

extern "C"
WORD FAR PASCAL _export SesEffSndPos (CAudFil FAR *pAudFil, DWORD FAR *pulSmpOff, 
							DWORD FAR *pulSmpLen, float flCrpSnd, float flCrpGrd,
							float FAR *lpPrmArr)
{
	/////////////////////////////////////////////////////////////////////////
	// Default values
	/////////////////////////////////////////////////////////////////////////
    #define CRPFRMDEF  (float)  .50		// Crop frame length (sec)
    #define CRPRESDEF  (float)  .01		// Crop resolution (sec)
    #define CRPATKDEF        20			// Crop atk ratio (%frm)
    #define CRPDCYDEF        10			// Crop dcy ratio (%frm)
	#define	CRPDCFDEF		20L			// Crop DC high pass filter (Hz)

	/////////////////////////////////////////////////////////////////////////
	// Future: Read from lpPrmArr
	/////////////////////////////////////////////////////////////////////////
	float	flCrpFrm = CRPFRMDEF;
	float	flCrpRes = CRPRESDEF;
	float	flCrpAtk = CRPATKDEF / (float) 100;
	float	flCrpDcy = CRPDCYDEF / (float) 100;
	DWORD	ulSndOff;
	DWORD	ulSndLen;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Scan file for sound and silence sections
	/////////////////////////////////////////////////////////////////////////
	if (!pAudFil->Open (CFile::modeRead)) return (IDS_OPNFILERR);
	pAudFil->Seek (*pulSmpOff);
	pAudFil->Read (*pulSmpLen, flCrpFrm, flCrpRes, flCrpSnd / 100, flCrpAtk, 
		flCrpDcy, flCrpGrd, flCrpGrd, CRPDCFDEF, &ulSndOff, &ulSndLen);
	pAudFil->Close ();

	/////////////////////////////////////////////////////////////////////////
	// Adjust caller's offset position with first sound event offset
	/////////////////////////////////////////////////////////////////////////
	*pulSmpOff += ulSndOff;
	*pulSmpLen  = ulSndLen;

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

extern "C"
WORD FAR PASCAL _export SesEffShwFrq (CAudFil FAR *pAudFil, DWORD ulSmpOff, 
							WORD usFFTOrd, float flSetSiz, WORD FAR *pusPltArr, 
							DWORD ulTimPnt, DWORD FAR *pulCmpCnt)
{
	/////////////////////////////////////////////////////////////////////////
	// Round FFT point count to power of two
	// Note: Data requirement is twice the FFT point size - real signals
	// Note: Round FFT points down to insure valid plot array bounds
	/////////////////////////////////////////////////////////////////////////
	WORD	usFFTPts = (WORD) pow (2, usFFTOrd);
	DWORD	ulSmpCnt = (DWORD) (2 * usFFTPts * flSetSiz * ulTimPnt);

	/////////////////////////////////////////////////////////////////////////
	// Insure valid request parameters
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (-1);
	if ((usFFTPts < 4) || (flSetSiz < 1) || !ulTimPnt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Allocate and open source file
	/////////////////////////////////////////////////////////////////////////
	CEffInp	aeEffInp (pAudFil);
	if (!aeEffInp.Open (CFile::modeRead, ulSmpOff, ulSmpCnt)) return (IDS_OPNFILERR);

	/////////////////////////////////////////////////////////////////////////
	// Allocate power spectrum effect
	// Note: ceil (LOGBASTWO (x)) may actually incr due to rounding error
	/////////////////////////////////////////////////////////////////////////
	CEffPow	aeEffPow (usFFTOrd, flSetSiz, ulTimPnt, 
		PCMCapQry (pAudFil->GetPCMTyp(), ATDMAXQRY, 0L), pAudFil->GetCBkPrc(), 
		pAudFil->GetCBkArg(IDS_POLACTPOW));

	/////////////////////////////////////////////////////////////////////////
	// Compute power spectrum for file
	/////////////////////////////////////////////////////////////////////////
	while (ulTimPnt) {
		DWORD	ulTimOut;
		/////////////////////////////////////////////////////////////////////
		// Convert incoming samples to an array of floating point magnitudes
		// Note: Should probably re-work this for cleaner increment of
		//		 pusPltArr pointer and less inter-module dependencies (such
		//   	 as synchronizing the value of ulSmpCnt and usFFTPts)
		/////////////////////////////////////////////////////////////////////
		if (!aeEffInp.ExeEffPrc()) break;
		aeEffPow.ExeEffPrc (&aeEffInp);
		ulTimOut = aeEffPow.Write (pusPltArr, ulTimPnt);
		if (!ulTimOut && (FIOEOS_OK != aeEffPow.GetEBSBlk()->usEOSCod)) break;
		/////////////////////////////////////////////////////////////////////
		// Increment time position and update caller for real-time display
		/////////////////////////////////////////////////////////////////////
		ulTimPnt -= min (ulTimPnt, ulTimOut);
		pusPltArr = &pusPltArr[ulTimOut * usFFTPts];
		*pulCmpCnt += ulTimOut; 
	}

	/////////////////////////////////////////////////////////////////////////
 	aeEffInp.Close ();

	/////////////////////////////////////////////////////////////////////////
	return (0);

}
