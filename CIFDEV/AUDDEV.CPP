/////////////////////////////////////////////////////////////////////////////
// AudDev.cpp : Implementation of the CAudDev classes
// Copyright (c) 1987-1993 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "mmsystem.h"					// Windows Multi Media defs
#include "audfil.h"						// Audio file support defs
#include "tmpfil.h"						// Temp file support defs
#include "audeff.h"						// Audio effects support defs
#include "auddev.h"						// Device Control support defs
#include "ampdsp.h"						// Amplitude display window

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const float	FRQSHFTHR	= (float) 1.25;	// Frequency shift threshold (%)
const char	TMPFILPRE[] = "V_AD";		// Audio device temp file prefix

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C" WORD	 FAR PASCAL	_export	AudDevBstPCM (WORD usCtlPro, WORD usPCMTyp); 
extern "C" WORD	 FAR PASCAL	_export	AudDevBstChn (WORD usCtlPro, WORD usPCMTyp, WORD usChnCnt);
extern "C" DWORD FAR PASCAL	_export	AudDevBstFrq (WORD usCtlPro, WORD usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CAudDev::CAudDev()
{
	m_pWIOCBk = NULL;

	/////////////////////////////////////////////////////////////////////////
	// Allocate work memory in multiples of PCMBLKSIZ, initialize
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (m_hgWrkHdl = GloAloBlk (GMEM_MOVEABLE, PCMBLKSIZ, PCMMINCNT, 
	  PCMMAXCNT, &m_ulWrkSiz))) {
		m_hgWrkHdl = NULL;
		m_ulWrkSiz = 0L;
	}
	return;

}	

CAudDev::~CAudDev()
{
	/////////////////////////////////////////////////////////////////////////
	if (m_pWIOCBk) delete m_pWIOCBk;
	GloAloRel (m_hgWrkHdl);
}	

BOOL		CAudDev::SelBstFmt (CAudFil *pAudFil, WORD usCtlPro, float flCvtVec)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!pAudFil) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Find best format if requested
	// Note: Enumeration routines use "Output" device format for simplicity
	/////////////////////////////////////////////////////////////////////////
	m_usSelPCM = m_usDefPCM ? m_usDefPCM 
		: (PCMTYP) AudDevBstPCM (usCtlPro, (WORD) pAudFil->GetPCMTyp());
	m_usSelChn = m_usDefChn ? m_usDefChn 
		: AudDevBstChn (usCtlPro, (WORD) m_usSelPCM, pAudFil->GetChnCnt());
	m_ulSelFrq = m_ulDefFrq ? m_ulDefFrq 
		: AudDevBstFrq (usCtlPro, (WORD) m_usSelPCM, m_usSelChn, 
			(DWORD) (flCvtVec * pAudFil->GetSmpFrq()));

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CWIOCBk::CWIOCBk()
{
	m_hTimWnd = 0; 
	m_pAmpDsp = NULL;
	m_pRecFil = NULL;

	m_pEffInp = NULL; 
	m_pEffAAF = NULL; 
	m_pEffRes = NULL;
	m_pEffAtD = NULL;

	/////////////////////////////////////////////////////////////////////////
	// Allocate work memory in multiples of LVLBUFSIZ, initialize
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (m_hgLvlHdl = GloAloBlk (GMEM_MOVEABLE, LVLBUFSIZ, LVLMINCNT, 
	  LVLMAXCNT, &m_ulLvlSiz))) {
		m_hgLvlHdl = NULL;
		m_ulLvlSiz = 0L;
	}
	m_ulLvlByt = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Set ITC Block contents to zero
	/////////////////////////////////////////////////////////////////////////
	_fmemset (m_ibITCBlk, 0, sizeof (m_ibITCBlk));

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return;
}	

CWIOCBk::~CWIOCBk()
{
	if (m_pEffInp) delete m_pEffInp; 
	if (m_pEffAAF) delete m_pEffAAF; 
	if (m_pEffRes) delete m_pEffRes;
	if (m_pEffAtD) delete m_pEffAtD; 

	if (m_pRecFil) m_pRecFil->Close();

	/////////////////////////////////////////////////////////////////////////
	// Free ITC Blocks
	/////////////////////////////////////////////////////////////////////////
	PCMRelITC (m_usPCMTyp, m_ibITCBlk);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	GloAloRel (m_hgLvlHdl);

}

WORD		CWIOCBk::PlaPolIni (CAudFil *pSrcFil, DWORD ulSmpOff, DWORD ulSmpCnt, 
				DWORD ulPosVec, DWORD ulLopCnt, PCMTYP usSelPCM, WORD usSelChn, 
				DWORD ulSelFrq, WORD usAAFAlg, WORD usResAlg, CAmpDsp *pAmpDsp, 
				HWND hTimWnd, DWORD ulTimArg)
{

	/////////////////////////////////////////////////////////////////////////
	// Initialize Effects processing for conversion
	// Destination frequency is set to effect speed up, slow dowm
	/////////////////////////////////////////////////////////////////////////
	m_pEffInp = new CEffInp (pSrcFil);
	m_pEffAAF = new CEffAAF (ulSelFrq / 2L, pSrcFil->GetSmpFrq(), (CEffAAF::AAFALG) usAAFAlg);
	m_pEffRes = new CEffRes (pSrcFil->GetSmpFrq(), ulSelFrq, (CEffRes::RESALG) usResAlg);
	m_pEffAtD = new CEffAtD (usSelPCM);

	/////////////////////////////////////////////////////////////////////////
	// Initialize Raw/Convert mode indicator and Loop Modulus
	/////////////////////////////////////////////////////////////////////////
	ulSmpCnt = min (ulSmpCnt, pSrcFil->GetSmpCnt() - ulSmpOff);
	m_bfRawMod = pSrcFil->Is_FmtCmp (usSelPCM, PCMBIODEF, usSelChn, ulSelFrq, FRQSHFTHR);
	m_ulLopMod = m_pEffRes->DstSizEst (ulSmpCnt, pSrcFil->GetSmpFrq());

	/////////////////////////////////////////////////////////////////////////
	// Set sample I/O callback variables
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp  = pAmpDsp;
	m_hTimWnd  = hTimWnd; 
	m_ulTimArg = ulTimArg; 

	/////////////////////////////////////////////////////////////////////////
	// Initialize Audio Device output parameters
	// Future: Initialize the ITC block frequency for CVSD PCM types
	/////////////////////////////////////////////////////////////////////////
	PCMAloITC (usSelPCM, m_ibITCBlk, NULL);
	m_usPCMTyp = usSelPCM;

	/////////////////////////////////////////////////////////////////////////
	// Open the source PCM file; Initialize file position & ITCBlk
	// Initialize position vector in device relative samples
	/////////////////////////////////////////////////////////////////////////
	if (!m_pEffInp->Open(CFile::modeRead, ulSmpOff, ulSmpCnt, ulLopCnt)) 
		return (-1);
	if (-1L == (m_ulPosVec = m_pEffInp->Seek (ulPosVec))) {
		m_pEffInp->Close();		
		return (-1);
	}
	m_ulPosVec = m_pEffRes->DstSizEst (m_ulPosVec, pSrcFil->GetSmpFrq());

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD		CWIOCBk::RecPolIni (CAudFil *pDstFil, DWORD ulSmpOff, DWORD ulSmpCnt, 
				CAudFil *pRecFil, BOOL bfOpnFlg, CAmpDsp *pAmpDsp, HWND hTimWnd, 
				DWORD ulTimArg)
{
	/////////////////////////////////////////////////////////////////////////
	// Initialize Effects processing for conversion
	// Future: Use usAAFAlg & usResAlg to activate conversion during record
	/////////////////////////////////////////////////////////////////////////
	m_pEffRes  = new CEffRes (pRecFil->GetSmpFrq(), pDstFil->GetSmpFrq(), CEffRes::RESALGNRM);
	m_ulLopMod = m_pEffRes->SrcSizEst (ulSmpCnt, pRecFil->GetSmpFrq());

	/////////////////////////////////////////////////////////////////////////
	// Initialize Audio Device input parameters
	// Future: Initialize the ITC block frequency for CVSD PCM types
	/////////////////////////////////////////////////////////////////////////
	PCMAloITC (pRecFil->GetPCMTyp(), m_ibITCBlk, NULL);
	m_usPCMTyp = pRecFil->GetPCMTyp();

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	m_pRecFil  = pRecFil;
	m_ulSmpOff = ulSmpOff;
	m_ulDstFrq = pDstFil->GetSmpFrq();
	m_ulBytReq = PCMSmp2Bh (pRecFil->GetPCMTyp(), pRecFil->GetChnCnt(), m_ulLopMod, m_ibITCBlk);

	/////////////////////////////////////////////////////////////////////////
	// Set sample I/O callback variables
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp  = pAmpDsp;
	m_hTimWnd  = hTimWnd; 
	m_ulTimArg = ulTimArg; 

	/////////////////////////////////////////////////////////////////////////
	// Open the destination PCM file; Initialize file position & ITCBlk
	/////////////////////////////////////////////////////////////////////////
	if (bfOpnFlg && !m_pRecFil->Open(CFile::modeCreate | CFile::modeReadWrite)) 
		return (-1);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

DWORD	CWIOCBk::LodMemBuf (LPVOID lpDstBuf, DWORD ulBufSiz)
{

	/////////////////////////////////////////////////////////////////////////
	// Perform simple transparent file read if raw mode requested
	/////////////////////////////////////////////////////////////////////////
	if (m_bfRawMod) 
		return (m_pEffInp->Read ((LPBYTE) lpDstBuf, ulBufSiz));

	/////////////////////////////////////////////////////////////////////////
	// Convert Mode: Convert from one PCM format to another
	/////////////////////////////////////////////////////////////////////////
	m_pEffInp->ExeEffPrc ();
	m_pEffRes->ExeEffPrc (m_pEffInp);
	m_pEffAtD->ExeEffPrc (m_pEffRes);
	
	/////////////////////////////////////////////////////////////////////////
	// Convert and indicate number of output buffer bytes written
	/////////////////////////////////////////////////////////////////////////
	return (m_pEffAtD->Rd_EBStoP (lpDstBuf, ulBufSiz, -1L,
		m_usPCMTyp, PCMBIODEF, m_ibITCBlk));

}

DWORD	CWIOCBk::RecLvlChk (LPVOID lpLvlBuf, DWORD ulLvlByt, DWORD ulLvlSmp)
{
	MXMBLK	mbMxMBlk;
	DWORD	ulLvlVal;

	/////////////////////////////////////////////////////////////////////////
	if (!m_pRecFil) return (0L);

	/////////////////////////////////////////////////////////////////////////
	memset (&mbMxMBlk, 0, sizeof (mbMxMBlk));

	/////////////////////////////////////////////////////////////////////////
	// Use data in memory buffer to compute current audio level
	/////////////////////////////////////////////////////////////////////////
	PCMPtoMxM (lpLvlBuf, ulLvlByt, &mbMxMBlk, 1, (WORD) ulLvlSmp,  
		m_pRecFil->GetPCMTyp(), m_pRecFil->GetChnCnt(), PCMBIODEF,
		m_ibITCBlk, NULL, NULL); 

	/////////////////////////////////////////////////////////////////////////
	ulLvlVal = max (labs (mbMxMBlk.gsMinWav), labs (mbMxMBlk.gsMaxWav));
	return (min (100L, 100L * ulLvlVal / PCMCapQry (m_pRecFil->GetPCMTyp(), ATDMAXQRY, 0L)));

}

DWORD	CWIOCBk::SmpPosAdj (DWORD ulSmpPos)
{
	/////////////////////////////////////////////////////////////////////////
	// Adjust output sample position for looping; protect against zero
	// Adjust output sample position for offset vector sample position
	/////////////////////////////////////////////////////////////////////////
	if (m_ulLopMod + 1L) ulSmpPos %= (m_ulLopMod + 1L);
	ulSmpPos += m_ulPosVec;		
	return (ulSmpPos);
}

/////////////////////////////////////////////////////////////////////////////
// Public C interface
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export	AudDevCfgLod (VISMEMHDL FAR *pmhDevCfg, WORD usCtlPro, 
						LPCSTR lpCfgFil, LPCSTR lpSecNam)
{
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			return (TMICfgLod (pmhDevCfg, lpCfgFil, lpSecNam));
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			return (MCICfgLod (pmhDevCfg, lpCfgFil, lpSecNam));
	} 
	/////////////////////////////////////////////////////////////////////////
	return (-1);

}

extern "C"
WORD FAR PASCAL _export	AudDevCfgQry (VISMEMHDL FAR *pmhDevCfg, WORD usCtlPro,
						WORD bfUsrQry)
{
	/////////////////////////////////////////////////////////////////////////
	// Note: Query with NULL argument indicates if options are available
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			if (bfUsrQry) return (TMICfgQry (*pmhDevCfg));
			return (0);
		/////////////////////////////////////////////////////////////////////
        // Note: Not active for this release
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			if (bfUsrQry) return (MCICfgQry (*pmhDevCfg));
			return (-1);
	} 
	/////////////////////////////////////////////////////////////////////////
	return (-1);

}

extern "C"
WORD FAR PASCAL _export	AudDevCfgRel (VISMEMHDL FAR *pmhDevCfg, WORD usCtlPro,
				LPSTR lpCfgFil, LPCSTR lpSecNam)
{
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			TMICfgRel (pmhDevCfg, lpCfgFil, lpSecNam);
			return (0);
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			MCICfgRel (pmhDevCfg, lpCfgFil, lpSecNam);
			return (0);
	} 
	/////////////////////////////////////////////////////////////////////////
	return (-1);

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export	AudDevOpn (CAudDev FAR * FAR *ppAudDev, WORD usCtlPro,
						WORD usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq, 
						WORD usBlkLen, WORD usBlkCnt, VISMEMHDL mhDevCfg,
						HWND hEvtWnd, DWORD ulEvtArg, LPCSTR pszTmpDir, 
						LPSTR szDesStr, WORD usMaxLen)
{
	/////////////////////////////////////////////////////////////////////////
	*ppAudDev = new CAudDev;

	/////////////////////////////////////////////////////////////////////////
	// Create temporary files
	/////////////////////////////////////////////////////////////////////////
	if (!strlen ((*ppAudDev)->m_csTmpPfx = CTmpFil::GenTmpPfx (pszTmpDir, TMPFILPRE))) return (-1);
	if ((*ppAudDev)->m_tfChdFil.IniFilOFS((*ppAudDev)->m_csTmpPfx + CHDFILEXT)) return (-1);
	if ((*ppAudDev)->m_tfRecFil.IniFilOFS((*ppAudDev)->m_csTmpPfx + RECFILEXT)) return (-1);
	if ((*ppAudDev)->m_afRecFil.IniFilOFS((*ppAudDev)->m_tfRecFil.GetFilOFS()->szPathName)) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize audio device internal parameters
	/////////////////////////////////////////////////////////////////////////
	(*ppAudDev)->m_usCtlPro = usCtlPro;
	(*ppAudDev)->m_usDefPCM = (PCMTYP) usPCMTyp;
	(*ppAudDev)->m_usDefChn = usChnCnt;
	(*ppAudDev)->m_ulDefFrq = ulSmpFrq;
	(*ppAudDev)->m_mhSysRes = NULL;
	(*ppAudDev)->m_mhDevRes = NULL;
	(*ppAudDev)->m_usLinNum = 0;

	/////////////////////////////////////////////////////////////////////////
	// Initialize actual audio device
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			TMICfgMod (mhDevCfg, 0, ulSmpFrq);
			if (TMISysIni (&(*ppAudDev)->m_mhSysRes, mhDevCfg)) return (-1);
			if (TMIDigAlo (&(*ppAudDev)->m_mhDevRes, mhDevCfg, &(*ppAudDev)->m_hCBkWnd, usBlkLen, usBlkCnt, hEvtWnd, ulEvtArg)) {
				TMISysTrm (&(*ppAudDev)->m_mhSysRes);
				return (-1);
			}						
			if (TMILinOpn (&(*ppAudDev)->m_usLinNum, (*ppAudDev)->m_hCBkWnd, mhDevCfg, szDesStr, usMaxLen)) {
				TMIDigRel (&(*ppAudDev)->m_mhDevRes);
				TMISysTrm (&(*ppAudDev)->m_mhSysRes);
				return (-1);
			}						
			return (0);
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			return (MCIWavOpn ((MCIPRO) usCtlPro, &(*ppAudDev)->m_mhDevRes,
				mhDevCfg, usBlkLen, usBlkCnt, szDesStr, usMaxLen));
	}
	
	return (-1);
	
}	

extern "C"
WORD FAR PASCAL _export	AudDevCls (CAudDev FAR * FAR *ppAudDev)
{

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (NULL == *ppAudDev) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Deactivate actual audio device
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP((*ppAudDev)->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			TMILinCls ((*ppAudDev)->m_usLinNum, (*ppAudDev)->m_hCBkWnd); 
			TMIDigRel (&(*ppAudDev)->m_mhDevRes);
			TMISysTrm (&(*ppAudDev)->m_mhSysRes);
			break;
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			MCIWavCls (&(*ppAudDev)->m_mhDevRes); 
			break;
	}

	/////////////////////////////////////////////////////////////////////////
	// Free audio device object
	/////////////////////////////////////////////////////////////////////////
	delete *ppAudDev;
	*ppAudDev = NULL;
	return (0);

}	

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export AudDevSta (CAudDev FAR *pAudDev, DWORD FAR *pulTimPos)
{
	DWORD	ulSmpPos = 0L;
	WORD	usRetCod = 0;

	/////////////////////////////////////////////////////////////////////////
	// Return zero if device is inactive
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pAudDev->m_pWIOCBk)) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Pause / Resume
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		usRetCod = WavFilSta (pAudDev->m_mhDevRes, &ulSmpPos);
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		usRetCod = TMIFilSta (pAudDev->m_mhDevRes, &ulSmpPos);
	}

	/////////////////////////////////////////////////////////////////////////
	// Loop adjust and convert samples to milliseconds
	/////////////////////////////////////////////////////////////////////////
	if (pulTimPos) *pulTimPos = (DWORD) (1000. 
		* pAudDev->m_pWIOCBk->SmpPosAdj(ulSmpPos) / pAudDev->m_ulSelFrq);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export AudDevPlaCue (CAudDev FAR *pAudDev, CAudFil FAR *pAudFil, 
				DWORD ulSmpOff, DWORD ulSmpCnt, DWORD ulPosVec, float flCvtVec, 
				DWORD ulLopCnt, WORD usAAFAlg, WORD usResAlg, CAmpDsp FAR *pAmpDsp, 
				VISWNDHDL hTimWnd, DWORD ulTimArg)
{
	WORD		usRetCod = -1;
	CWIOCBk	*	pWIOCBk = new CWIOCBk;

	/////////////////////////////////////////////////////////////////////////
	// Check for valid pointers; insure current callback is inactive
	/////////////////////////////////////////////////////////////////////////
	if (!pAudFil || !pAudDev || pAudDev->m_pWIOCBk || !pWIOCBk) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Select best device format and frequency
	/////////////////////////////////////////////////////////////////////////
	pAudDev->SelBstFmt (pAudFil, pAudDev->m_usCtlPro, flCvtVec);

	/////////////////////////////////////////////////////////////////////////
	// Initialized Effects processing for conversion
	// Note: Divide destination frequency for speed up, slow down
	/////////////////////////////////////////////////////////////////////////
	if (pWIOCBk->PlaPolIni (pAudFil, ulSmpOff, ulSmpCnt, ulPosVec, ulLopCnt, 
	  pAudDev->m_usSelPCM, pAudDev->m_usSelChn, (DWORD) (pAudDev->m_ulSelFrq / flCvtVec),  
	  usAAFAlg, usResAlg, pAmpDsp, (HWND) hTimWnd, ulTimArg)) {
		delete pWIOCBk;
		return (-1);
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Set up for play; test for error
		/////////////////////////////////////////////////////////////////////
		usRetCod = WavFilPla (pAudDev->m_mhDevRes, 
			pAudDev->m_usSelPCM, pAudDev->m_usSelChn, pAudDev->m_ulSelFrq, 
			pWIOCBk->PlaPolCBk, (DWORD) pWIOCBk,
			(MCIPOLPRC) pAudFil->GetCBkPrc(), (DWORD) pAudFil->GetCBkArg(IDS_POLACTCUE));
		if (usRetCod) WavFilTrm (pAudDev->m_mhDevRes);
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Set up for play; test for error
		/////////////////////////////////////////////////////////////////////
		usRetCod = TMIFilPla (pAudDev->m_usLinNum, pAudDev->m_mhDevRes, 
			pAudDev->m_usSelPCM, pAudDev->m_usSelChn, pAudDev->m_ulSelFrq, 
			pAudDev->m_tfChdFil.GetFilOFS()->szPathName, 
			(TMIDIOPRC) pWIOCBk->PlaPolCBk, (DWORD) pWIOCBk,
			(TMIPOLPRC) pAudFil->GetCBkPrc(), (DWORD) pAudFil->GetCBkArg(IDS_POLACTCUE));
		if (usRetCod) TMIFilTrm (pAudDev->m_mhDevRes);
	}

	/////////////////////////////////////////////////////////////////////////
	// Device cue routines yield, permitting re-entrancy
	// Check again to insure that current callback is inactive
	// Note: Caller must insure that device is not deleted during this call
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod || pAudDev->m_pWIOCBk)	{
		delete pWIOCBk;
		return (usRetCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// Update current callback to indicate playback is ready (and stable!)
	/////////////////////////////////////////////////////////////////////////
	pAudDev->m_pWIOCBk = pWIOCBk;
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export AudDevPlaBeg (CAudDev FAR *pAudDev)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pAudDev->m_pWIOCBk)) return (-1);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Begin play; return error
		/////////////////////////////////////////////////////////////////////
		return (WavPlaBeg (pAudDev->m_mhDevRes));
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Begin play; return error
		/////////////////////////////////////////////////////////////////////
		return (TMIPlaBeg (pAudDev->m_mhDevRes));
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (-1);

}

extern "C"
WORD FAR PASCAL _export AudDevRecCue (CAudDev FAR *pAudDev, CAudFil FAR *pAudFil, 
				DWORD ulSmpOff, DWORD ulSmpCnt, DWORD ulRsv001, WORD usAAFAlg, 
				WORD usResAlg, CAmpDsp FAR *pAmpDsp, VISWNDHDL hTimWnd, DWORD ulTimArg)
{
	WORD		usRetCod = -1;
	CWIOCBk	*	pWIOCBk = new CWIOCBk;

	/////////////////////////////////////////////////////////////////////////
	// Check for valid pointers; insure current callback is inactive
	/////////////////////////////////////////////////////////////////////////
	if (!pAudFil || !pAudDev || pAudDev->m_pWIOCBk || !pWIOCBk) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Find best format if requested
	/////////////////////////////////////////////////////////////////////////
	pAudDev->SelBstFmt (pAudFil, pAudDev->m_usCtlPro, 1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize recording audio file
	// Note: IniFilFmt should probably be removed/modified in future versions
	//		 to permit integration of IniFilOFS into a single AudFilOpn call
	/////////////////////////////////////////////////////////////////////////
	pAudDev->m_afRecFil.IniFilFmt(&pAudDev->m_usSelPCM, &pAudDev->m_usSelChn, 
		&pAudDev->m_ulSelFrq, &pAudDev->m_usSelMsk);

	/////////////////////////////////////////////////////////////////////////
	// Set sample I/O callback variables
	// Open destination PCM file for output if MCI operation requested
	// Future: Use usAAFAlg & usResAlg to activate conversion during record
	/////////////////////////////////////////////////////////////////////////
	if (pWIOCBk->RecPolIni (pAudFil, ulSmpOff, ulSmpCnt, &pAudDev->m_afRecFil, 
	  CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro),
	  pAmpDsp, (HWND) hTimWnd, ulTimArg)) {
		delete pWIOCBk;
		return (-1);
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Set up for record
		/////////////////////////////////////////////////////////////////////
		usRetCod = WavFilRec (pAudDev->m_mhDevRes, 
			pAudDev->m_usSelPCM, pAudDev->m_usSelChn, pAudDev->m_ulSelFrq, 
			pWIOCBk->RecPolCBk, (DWORD) pWIOCBk);
		if (usRetCod) WavFilTrm (pAudDev->m_mhDevRes);
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Set up for record
		/////////////////////////////////////////////////////////////////////
		usRetCod = TMIFilRec (pAudDev->m_usLinNum, pAudDev->m_mhDevRes,	
			pAudDev->m_usSelPCM, pAudDev->m_usSelChn, pAudDev->m_ulSelFrq, 
			pAudDev->m_afRecFil.GetFilOFS()->szPathName, 
			(TMIDIOPRC) pWIOCBk->RecPolCBk, (DWORD) pWIOCBk);
		if (usRetCod) TMIFilTrm (pAudDev->m_mhDevRes);
	}

	/////////////////////////////////////////////////////////////////////////
	// Device cue routines yield, permitting re-entrancy
	// Check again to insure that current callback is inactive
	// Note: Caller must insure that device is not deleted during this call
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod || pAudDev->m_pWIOCBk)	{
		delete pWIOCBk;
		return (usRetCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// Update current callback to indicate playback is ready (and stable!)
	/////////////////////////////////////////////////////////////////////////
	pAudDev->m_pWIOCBk = pWIOCBk;
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export AudDevRecBeg (CAudDev FAR *pAudDev)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pAudDev->m_pWIOCBk)) return (-1);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Begin recording; return error
		/////////////////////////////////////////////////////////////////////
		return (WavRecBeg (pAudDev->m_mhDevRes));
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// Begin recording; return error
		/////////////////////////////////////////////////////////////////////
		return (TMIRecBeg (pAudDev->m_mhDevRes));
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (-1);

}

extern "C"
DWORD FAR PASCAL _export AudDevRecLvl (CAudDev FAR *pAudDev, float flLvlTim)
{
	LPVOID		lpLvlBuf;
	DWORD		ulLvlSmp;
	DWORD		ulLvlVal;
	DWORD		ulBytCnt;
	CWIOCBk	*	pWIOCBk = pAudDev->m_pWIOCBk;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pWIOCBk)) return (0L);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!(ulLvlSmp = (DWORD) (flLvlTim * pAudDev->m_ulSelFrq))) return (0L);
	if (NULL == (lpLvlBuf = GloMemLck (pWIOCBk->m_hgLvlHdl))) return (0L);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(pAudDev->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		// MCI record routines save sample of data in level buffer
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			ulBytCnt = PCMSmp2Bh (pAudDev->m_usSelPCM, pAudDev->m_usSelChn, ulLvlSmp, NULL); 	 
			ulBytCnt = min (ulBytCnt, pWIOCBk->m_ulLvlByt);
			ulLvlSmp = PCMByt2Sl (pAudDev->m_usSelPCM, pAudDev->m_usSelChn, ulBytCnt, NULL); 	 
			lpLvlBuf = &((LPBYTE)lpLvlBuf)[pWIOCBk->m_ulLvlByt - ulBytCnt];
			ulLvlVal = pWIOCBk->RecLvlChk (lpLvlBuf, ulBytCnt, ulLvlSmp);
			break;
		/////////////////////////////////////////////////////////////////////
		// TMI device writes directly to file; ask TMI for a buffer of data
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			ulBytCnt = PCMSmp2Bh (pAudDev->m_usSelPCM, pAudDev->m_usSelChn, ulLvlSmp, NULL); 	 
			ulBytCnt = TMIRecLvl (pAudDev->m_mhDevRes, lpLvlBuf, min (ulBytCnt, pWIOCBk->m_ulLvlSiz));
			ulLvlSmp = PCMByt2Sl (pAudDev->m_usSelPCM, pAudDev->m_usSelChn, ulBytCnt, NULL); 	 
			ulLvlVal = pWIOCBk->RecLvlChk (lpLvlBuf, ulBytCnt, ulLvlSmp);
			break;
	}
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	GloMemUnL (pWIOCBk->m_hgLvlHdl);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (ulLvlVal);

}

extern "C"
DWORD FAR PASCAL _export AudDevRecGet (CAudDev FAR *pAudDev)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudDev) return (NULL);
	return ((DWORD) ((CAudFil FAR *) &pAudDev->m_afRecFil));
}

extern "C"
DWORD FAR PASCAL _export AudDevPau (CAudDev FAR *pAudDev, WORD usResFlg)
{
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pAudDev->m_pWIOCBk)) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Pause / Resume; return adjusted sample position
	/////////////////////////////////////////////////////////////////////////
	if (CAudDev::MCIWAVPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		return (pAudDev->m_pWIOCBk->SmpPosAdj(WavFilPau (pAudDev->m_mhDevRes, usResFlg)));
	}
	if (CAudDev::TMIDIGPRO == CTLPROTYP(pAudDev->m_usCtlPro)) {
		return (pAudDev->m_pWIOCBk->SmpPosAdj(TMIFilPau (pAudDev->m_mhDevRes, usResFlg)));
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

extern "C"
DWORD FAR PASCAL _export AudDevStp (CAudDev FAR *pAudDev)
{
	DWORD	ulSmpPos = 0L;
	DWORD	ulTimPos = 0L;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudDev) || (NULL == pAudDev->m_pWIOCBk)) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Stop and get sample position
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP((pAudDev)->m_usCtlPro)) {
		/////////////////////////////////////////////////////////////////////
		case CAudDev::MCIWAVPRO:
			ulSmpPos = WavFilTrm (pAudDev->m_mhDevRes);
			break;
		/////////////////////////////////////////////////////////////////////
		case CAudDev::TMIDIGPRO:
			ulSmpPos = TMIFilTrm (pAudDev->m_mhDevRes);
			break;
	}

	/////////////////////////////////////////////////////////////////////////
	// Loop adjust and convert samples to milliseconds
	/////////////////////////////////////////////////////////////////////////
	ulTimPos = (DWORD) (1000.
		* pAudDev->m_pWIOCBk->SmpPosAdj(ulSmpPos) / pAudDev->m_ulSelFrq);

	/////////////////////////////////////////////////////////////////////////
	// Note: (NULL != pAudDev->m_pWIOCBk) Inhibits re-entrancy for cueing 
	/////////////////////////////////////////////////////////////////////////
	delete pAudDev->m_pWIOCBk;
	pAudDev->m_pWIOCBk = NULL;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (ulTimPos);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export AudDevCtlEnu (WORD FAR *pusCtlPro, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Query for protocol information. Add Protocol Type Flag.
	// Note: TMI only returns on possible device; MCI returns multiple.
	/////////////////////////////////////////////////////////////////////////
	if ((CTLPROTYP(*pusCtlPro) < CAudDev::TMIDIGPRO) 
	  && (VER_PLATFORM_WIN32_NT != CIFOS_Inf (NULL))) {
		*pusCtlPro = TMIDigEnu (TMIUNKPRO, szDesStr, usMaxLen);
		*pusCtlPro |= CAudDev::TMIDIGPRO;
		return (TRUE);
	}

	/////////////////////////////////////////////////////////////////////////
	// Set to first type (first MCI is zero). Increment if scanning.
	/////////////////////////////////////////////////////////////////////////
	if (CTLPROTYP(*pusCtlPro) < CAudDev::MCIWAVPRO) 
		*pusCtlPro = CAudDev::MCIWAVPRO | WAVDEVFST;
	else WAVDEVNXT (*pusCtlPro);

	/////////////////////////////////////////////////////////////////////////
	// Enumerate MCI Wave devices; return FALSE at end.
	/////////////////////////////////////////////////////////////////////////
	if (!MCIWavEnu ((MCIPRO) *pusCtlPro, szDesStr, usMaxLen)) return (FALSE);
	*pusCtlPro |= CAudDev::MCIWAVPRO;
	return (TRUE);

}

extern "C"
WORD FAR PASCAL _export AudDevPCMEnu (WORD usCtlPro, WORD FAR *pusPCMTyp, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		case CAudDev::TMIDIGPRO:				// Audio Device = Generic TMI
			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			if (QRYBSTFMT == *pusPCMTyp) {		// Select best format
				if (!TMICapQry ((TMIPRO) usCtlPro, DYNPCMQRY, 0L)) return (FALSE);
				if (!csWrkStr.LoadString(IDS_SELBSTFMT)) return (FALSE);
				strncpy (szDesStr, csWrkStr, usMaxLen);
				*pusPCMTyp = SELBSTFMT;
				return (TRUE);
			}
			if (*pusPCMTyp = TMIPCMEnu ((TMIPRO) usCtlPro, (PCMTYP) *pusPCMTyp)) {
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}
			break;
		case CAudDev::MCIWAVPRO: 				// Audio Device = Wave MCI
			/////////////////////////////////////////////////////////////////
			// Note: Enumeration routine defaults to output protocol
			/////////////////////////////////////////////////////////////////
			if (QRYBSTFMT == *pusPCMTyp) {		// Select best format
				if (!csWrkStr.LoadString(IDS_SELBSTFMT)) return (FALSE);
				strncpy (szDesStr, csWrkStr, usMaxLen);
				*pusPCMTyp = SELBSTFMT;
				return (TRUE);
			}
			if (MCIPROINP == CTLPRODIR(usCtlPro)) {
				if (*pusPCMTyp = MCIPCMEnu ((MCIPRO) usCtlPro,
				  (PCMTYP) *pusPCMTyp)) {
					PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
					return (TRUE);
				}
			} else {
				if (*pusPCMTyp = MCIPCMEnu ((MCIPRO) (usCtlPro | MCIPROOUT),
				  (PCMTYP) *pusPCMTyp)) {
					PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
					return (TRUE);
				}
			}
			break;
	}
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

extern "C"
WORD FAR PASCAL _export AudDevChnEnu (WORD usCtlPro, WORD usPCMTyp, WORD FAR *pusChnCnt)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudDevFrqEnu (WORD usCtlPro, WORD usPCMTyp, WORD usChnCnt, DWORD FAR *pulSmpFrq)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (CTLPROTYP(usCtlPro)) {
		case CAudDev::TMIDIGPRO:		 		// Audio Device: Dialogic TMI
			if (QRYBSTFMT == *pulSmpFrq) {		// Select best format
				if (!TMICapQry ((TMIPRO) usCtlPro, DYNFRQQRY, 0L)) return (FALSE);
				*pulSmpFrq = SELBSTFMT;
				return (TRUE);
			}
			if (*pulSmpFrq = TMIFrqEnu ((TMIPRO) usCtlPro, (PCMTYP) usPCMTyp, 
				usChnCnt, *pulSmpFrq)) return (TRUE);
			break;
		case CAudDev::MCIWAVPRO: 				// Audio Device = Wave MCI
			/////////////////////////////////////////////////////////////////
			// Note: Enumeration routine defaults to output protocol
			/////////////////////////////////////////////////////////////////
			if (QRYBSTFMT == *pulSmpFrq) {		// Select best format
				*pulSmpFrq = SELBSTFMT;
				return (TRUE);
			}
			if (MCIPROINP == CTLPRODIR(usCtlPro)) {
				if (*pulSmpFrq = MCIFrqEnu ((MCIPRO) usCtlPro, 
					(PCMTYP) usPCMTyp, usChnCnt, *pulSmpFrq)) return (TRUE);
			} else {
				if (*pulSmpFrq = MCIFrqEnu ((MCIPRO) (usCtlPro | MCIPROOUT),
					(PCMTYP) usPCMTyp, usChnCnt, *pulSmpFrq)) return (TRUE);
			}
			break;
	}
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

extern "C"
WORD FAR PASCAL _export AudDevPlaAAFEnu (WORD FAR *pusAAFAlg, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (*pusAAFAlg < CEffAAF::AAFALGNON) {
		if (!csWrkStr.LoadString(IDS_AAFALGNON)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGNON;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALGFST) {
		if (!csWrkStr.LoadString(IDS_AAFALGFST)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGFST;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALGNRM) {
		if (!csWrkStr.LoadString(IDS_AAFALGNRM)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGNRM;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALG6II) {
		if (!csWrkStr.LoadString(IDS_AAFALG6II)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALG6II;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALG6IF) {
		if (!csWrkStr.LoadString(IDS_AAFALG6IF)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALG6IF;			
		return (TRUE);
	}
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudDevPlaResEnu (WORD FAR *pusResAlg, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (*pusResAlg < CEffRes::RESALGNRM) {
		if (!csWrkStr.LoadString(IDS_RESALGNRM)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusResAlg = CEffRes::RESALGNRM;			
		return (TRUE);
	}
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudDevRecAAFEnu (WORD FAR *pusAAFAlg, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (*pusAAFAlg < CEffAAF::AAFALGNON) {
		if (!csWrkStr.LoadString(IDS_AAFALGNON)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGNON;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALGFST) {
		if (!csWrkStr.LoadString(IDS_AAFALGFST)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGFST;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALGNRM) {
		if (!csWrkStr.LoadString(IDS_AAFALGNRM)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGNRM;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALG6II) {
		if (!csWrkStr.LoadString(IDS_AAFALG6II)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALG6II;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALG6IF) {
		if (!csWrkStr.LoadString(IDS_AAFALG6IF)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALG6IF;			
		return (TRUE);
	}
	if (*pusAAFAlg < CEffAAF::AAFALGFFT) {
		if (!csWrkStr.LoadString(IDS_AAFALGFFT)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusAAFAlg = CEffAAF::AAFALGFFT;			
		return (TRUE);
	}
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudDevRecResEnu (WORD FAR *pusResAlg, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (*pusResAlg < CEffRes::RESALGNRM) {
		if (!csWrkStr.LoadString(IDS_RESALGNRM)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusResAlg = CEffRes::RESALGNRM;			
		return (TRUE);
	}
	if (*pusResAlg < CEffRes::RESALGFFT) {
		if (!csWrkStr.LoadString(IDS_RESALGFFT)) return (FALSE);
		strncpy (szDesStr, csWrkStr, usMaxLen);
		*pusResAlg = CEffRes::RESALGFFT;			
		return (TRUE);
	}				
	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export AudDevBstPCM (WORD usCtlPro, WORD usPCMTyp) 
{
	WORD	usCurPCM = 0;
	WORD	usBstPCM = 0;
	WORD	usHghPCM = 0;
	WORD	usMinErr = -1;
	WORD	usAtDRes = (WORD) PCMCapQry ((PCMTYP) usPCMTyp, ATDRESQRY, 0L);;
	WORD	usCurAtD = 0;
	WORD	usHghAtD = 0;

	/////////////////////////////////////////////////////////////////////////
	// Scan for exact match; scan for best resolution greater than original
	/////////////////////////////////////////////////////////////////////////
	while (AudDevPCMEnu (usCtlPro, &usCurPCM, NULL, 0)) {
		if (usCurPCM == usPCMTyp) return (usCurPCM);
		usCurAtD = (WORD) PCMCapQry ((PCMTYP) usCurPCM, ATDRESQRY, 0L);;
		if ((usCurAtD > usAtDRes) && ((usCurAtD - usAtDRes) < usMinErr)) {
			usMinErr = usCurAtD - usAtDRes;
			usBstPCM = usCurPCM;
		}
		if (usCurAtD > usHghAtD) usHghPCM = usCurPCM;
	}	
	return (usBstPCM ? usBstPCM : usHghPCM);
}

extern "C"
WORD FAR PASCAL _export AudDevBstChn (WORD usCtlPro, WORD usPCMTyp, WORD usChnCnt)
{
	return (1);
}

extern "C"
DWORD FAR PASCAL _export AudDevBstFrq (WORD usCtlPro, WORD usPCMTyp, WORD usChnCnt, DWORD ulSmpFrq)
{
	DWORD	ulCurFrq = 0L;
	DWORD	ulBstFrq = 0L;
	DWORD	ulHghFrq = 0L;
	DWORD	ulMinErr = (DWORD) -1L;

	/////////////////////////////////////////////////////////////////////////
	// Scan for exact match; scan for closest frequency 
	/////////////////////////////////////////////////////////////////////////
	while (AudDevFrqEnu (usCtlPro, usPCMTyp, usChnCnt, &ulCurFrq)) {
		if (ulCurFrq == ulSmpFrq) return (ulCurFrq);
		if (((DWORD) labs (ulCurFrq - ulSmpFrq)) < ulMinErr) { 
			ulBstFrq = ulCurFrq; 
			ulMinErr = labs (ulCurFrq - ulSmpFrq);
		}
		if (ulCurFrq > ulHghFrq) ulHghFrq = ulCurFrq;
	}	
	return (ulBstFrq ? ulBstFrq : ulHghFrq);
}

/////////////////////////////////////////////////////////////////////////////
// Private Callback Procedures
/////////////////////////////////////////////////////////////////////////////
DWORD CALLBACK EXPORT 	CWIOCBk::PlaPolCBk (MCIPOL usPolReq, LPVOID lpDstBuf, 
						DWORD ulBufSiz, WORD usBufAct, DWORD ulSmpPos, DWORD ulCBkArg)
{
	CWIOCBk FAR*lpAudCBk = (CWIOCBk FAR *) ulCBkArg;
	CEffInp FAR*lpEffInp = lpAudCBk->m_pEffInp;
	CEffRes FAR*lpEffRes = lpAudCBk->m_pEffRes;
	DWORD		ulBytOut = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Get adjusted sample position
	/////////////////////////////////////////////////////////////////////////
	ulSmpPos = lpAudCBk->SmpPosAdj(ulSmpPos);

	/////////////////////////////////////////////////////////////////////////
	// Update display cursor position (if requested)
	// Note: Use resampled output to compute sample to time position
	/////////////////////////////////////////////////////////////////////////
	if (lpAudCBk->m_pAmpDsp) lpAudCBk->m_pAmpDsp->CarSetEvt (lpEffInp->GetSmpOff()
		+ lpEffInp->MSecToSmp (lpEffRes->SmpToMSec(ulSmpPos)), FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Return (!= 0) to continue processing
	/////////////////////////////////////////////////////////////////////////
	switch (usPolReq) {
		case MCIPOLBEG:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with total time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKBEG, IDS_POLACTPLA); 

			/////////////////////////////////////////////////////////////////
			ulBytOut = lpAudCBk->LodMemBuf (lpDstBuf, ulBufSiz);
			break;

		case MCIPOLCNT:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKCNT, (DWORD) lpEffRes->SmpToMSec (ulSmpPos));

			/////////////////////////////////////////////////////////////////
			ulBytOut = lpAudCBk->LodMemBuf (lpDstBuf, ulBufSiz);
			break;

		case MCIPOLPOS:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				usBufAct ? WIOCBKCNT : WIOCBKEMP, (DWORD) lpEffRes->SmpToMSec(ulSmpPos));
			break;

		case MCIPOLEND:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKEND, (DWORD) lpEffRes->SmpToMSec(ulSmpPos));
			break;
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (ulBytOut);

} 

DWORD CALLBACK EXPORT 	CWIOCBk::RecPolCBk (MCIPOL usPolReq, LPVOID lpSrcBuf,
						DWORD ulBufSiz, WORD usBufAct, DWORD ulSmpPos, DWORD ulCBkArg)
{
	CWIOCBk FAR*lpAudCBk = (CWIOCBk FAR *) ulCBkArg;
	CAudFil FAR*lpRecFil = lpAudCBk->m_pRecFil;
	DWORD		ulBytInp = 0L;
	LPVOID		lpLvlBuf;

	/////////////////////////////////////////////////////////////////////////
	// Update display cursor position (if requested)
	// Note: Use resampled output to compute sample to time position
	/////////////////////////////////////////////////////////////////////////
	if (lpAudCBk->m_pAmpDsp) lpAudCBk->m_pAmpDsp->CarSetEvt (lpAudCBk->m_ulSmpOff
		+ (DWORD) (lpAudCBk->m_ulDstFrq * (lpRecFil->SmpToMSec(ulSmpPos)) / 1000L), FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Return (!= 0) to continue processing
	/////////////////////////////////////////////////////////////////////////
	switch (usPolReq) {
		case MCIPOLBEG:
			/////////////////////////////////////////////////////////////////
			// Initialize level meter buffer to zero
			/////////////////////////////////////////////////////////////////
			if (NULL != (lpLvlBuf = GloMemLck (lpAudCBk->m_hgLvlHdl))) {
				memset (lpLvlBuf, 0, (WORD) lpAudCBk->m_ulLvlSiz);
				GloMemUnL (lpAudCBk->m_hgLvlHdl);
				lpAudCBk->m_ulLvlByt = 0L;
			}

			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with total time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKBEG, IDS_POLACTREC);

			/////////////////////////////////////////////////////////////////
			// Recording has not yet started; all buffers are empty
			// Look-ahead for byte remaining count based upon zero out
			// Return the size of first buffer request
			/////////////////////////////////////////////////////////////////
			ulBytInp = min (lpAudCBk->m_ulBytReq, ulBufSiz);
			lpAudCBk->m_ulBytReq -= ulBytInp;
			break;

		case MCIPOLCNT:
			/////////////////////////////////////////////////////////////////
			// Save copy of tail end of recorded data for level meters
			// TMI writes directly to file, lpSrcBuf == NULL
			/////////////////////////////////////////////////////////////////
			if (lpSrcBuf && (lpLvlBuf = GloMemLck (lpAudCBk->m_hgLvlHdl))) {
				lpAudCBk->m_ulLvlByt = min (lpAudCBk->m_ulLvlSiz, ulBufSiz);
				memcpy (lpLvlBuf, &((LPBYTE)lpSrcBuf)[ulBufSiz - lpAudCBk->m_ulLvlByt], 
					(WORD) lpAudCBk->m_ulLvlByt);
				GloMemUnL (lpAudCBk->m_hgLvlHdl);
			}

			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKCNT, (DWORD) lpRecFil->SmpToMSec (ulSmpPos));

			/////////////////////////////////////////////////////////////////
			// Write PCM data; TMI writes directly to file, lpSrcBuf == NULL
			// Note: Assume all bytes are written to file
			/////////////////////////////////////////////////////////////////
			if (lpSrcBuf && ulBufSiz) _hwrite (lpRecFil->m_hFile, lpSrcBuf, ulBufSiz);

			/////////////////////////////////////////////////////////////////
			// Indicate number of bytes required to refill this buffer
			/////////////////////////////////////////////////////////////////
			ulBytInp = min (lpAudCBk->m_ulBytReq, ulBufSiz);
			lpAudCBk->m_ulBytReq -= ulBytInp;

			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			break;

		case MCIPOLPOS:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				usBufAct ? WIOCBKCNT : WIOCBKEMP, (DWORD) lpRecFil->SmpToMSec (ulSmpPos));
			break;

		case MCIPOLEMP:
			/////////////////////////////////////////////////////////////////
			// Recording has not yet started; all buffers are empty
			// Return the size of subsequent buffer request
			/////////////////////////////////////////////////////////////////
			ulBytInp = min (lpAudCBk->m_ulBytReq, ulBufSiz);
			lpAudCBk->m_ulBytReq -= ulBytInp;
			break;

		case MCIPOLEND:
			/////////////////////////////////////////////////////////////////
			// Update poll callback routine with current time position		 
			/////////////////////////////////////////////////////////////////
			if (0 != lpAudCBk->m_hTimWnd) 
				SendMessage (lpAudCBk->m_hTimWnd, (WORD) lpAudCBk->m_ulTimArg,
				WIOCBKEND, (DWORD) lpRecFil->SmpToMSec (ulSmpPos));
			break;
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (ulBytInp);

}



