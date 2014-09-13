/////////////////////////////////////////////////////////////////////////////
// AudFil.cpp : Implementation of the CAudFil classes
// Copyright (c) 1987-1996 Andrew J. Michalik
//
// Class Audio File
// CAudFil is an object shell around an existing or new (empty) audio file.
// CSesFil is responsible for read access integrity of headers & trailers.
// CAudFil is responsible for sample level PCM data format integrity.
//
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "audfil.h"						// Audio file support defs
#include "tmpfil.h"						// Temp file support defs
#include "audeff.h"						// Audio effects support defs
#include "ampdsp.h"						// Amplitude display window

extern "C"
{
	#include "fiodev\filutl.h"			// File utilities definitions
	#include "os_dev\winmsg.h"			// User message support
}

/////////////////////////////////////////////////////////////////////////////
//						External References
/////////////////////////////////////////////////////////////////////////////
extern  CIFGLO  CIFGlo;					// C Interface Library Globals

/////////////////////////////////////////////////////////////////////////////
// CFIOCBk
/////////////////////////////////////////////////////////////////////////////
WORD		CFIOCBk::CntCBkPrc (DWORD ulFilPos, WORD *pusMsgSID)
{
	if (FIOPolCBk (FIOPOLCNT, ulFilPos, this)) return (TRUE); 
	if (pusMsgSID) *pusMsgSID = IDS_USRCANREQ; 
	return (FALSE);
}

WORD CALLBACK EXPORT CFIOCBk::FIOPolCBk (FIOPOL usPolReq, DWORD ulFilPos, 
										 CFIOCBk FAR *lpFIOCBk)
{
	WORD	usRetCod = TRUE;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!lpFIOCBk->m_hPolWnd) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Only poll callback count if an estimation indicated that at least 
	// CBKPOLTHR time will elapse before processing is complete.
	// Once polling is active, don't poll faster than the specified frequency
	// Return TRUE to continue processing
	/////////////////////////////////////////////////////////////////////////
	if (lpFIOCBk->m_hPolWnd) switch (usPolReq) {
		/////////////////////////////////////////////////////////////////////
		// Begin: Notify caller, returning without multitasking
		/////////////////////////////////////////////////////////////////////
		case FIOCBKBEG:
			lpFIOCBk->m_bfCntAct = FALSE;
			lpFIOCBk->m_ulTotCnt = ulFilPos;
			lpFIOCBk->m_ulLstTim = GetTickCount();
			SendMessage (lpFIOCBk->m_hPolWnd, (WORD) lpFIOCBk->m_nMsgPrm, 
				FIOPOLBEG, lpFIOCBk->m_usActDes);
			return (usRetCod);
		/////////////////////////////////////////////////////////////////////
		// Continue / Position: If time elapsed, notify caller & multitask  
		/////////////////////////////////////////////////////////////////////
		case FIOCBKCNT:
		case FIOCBKPOS:
			if (lpFIOCBk->Is_CntAct(ulFilPos) && lpFIOCBk->Is_PolTim()) {
				SendMessage (lpFIOCBk->m_hPolWnd, (WORD) lpFIOCBk->m_nMsgPrm,  
				  usPolReq, lpFIOCBk->m_ulTotCnt ? (DWORD) 
				  ((100L * (float) ulFilPos) / lpFIOCBk->m_ulTotCnt) : ulFilPos);
				break;
			}
			return (usRetCod);
		/////////////////////////////////////////////////////////////////////
		// End: Notify caller, returning without multitasking
		/////////////////////////////////////////////////////////////////////
		case FIOCBKEND:
			SendMessage (lpFIOCBk->m_hPolWnd, (WORD) lpFIOCBk->m_nMsgPrm, 
				usPolReq, lpFIOCBk->m_ulTotCnt ? 100L : ulFilPos);
			lpFIOCBk->m_bfCntAct = FALSE;
			lpFIOCBk->m_ulTotCnt = 0L;
			return (usRetCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// Look for Ctrl-C messages and yield during polling to multi-task
	/////////////////////////////////////////////////////////////////////////
	LockData(0);
	MSG msg;
	while (lpFIOCBk->m_bfCntAct && PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
		/////////////////////////////////////////////////////////////////////
		// Look for ^C messages
		/////////////////////////////////////////////////////////////////////
		if ((WM_KEYDOWN == msg.message) && ('C' == msg.wParam)
			&& (0x8000 & GetKeyState (VK_CONTROL))) {
			usRetCod = FALSE;
			MessageBeep (0);
			break;
		}
		/////////////////////////////////////////////////////////////////////
		// Recycle quit messages
		/////////////////////////////////////////////////////////////////////
		if (WM_QUIT == msg.message) {
			::PostMessage (msg.hwnd, msg.message, msg.wParam, msg.lParam);
			break;
		}
		if(!AfxGetApp()->PreTranslateMessage (&msg))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}
	UnlockData(0);
	AfxGetApp()->OnIdle(0);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);

}	
BOOL	CFIOCBk::Is_CntAct (DWORD ulFilPos)
{
	if (m_bfCntAct) return (TRUE);
	if (ulFilPos && (((m_ulTotCnt / (float) ulFilPos) 
		* (GetTickCount() - m_ulLstTim)) >= CBKPOLTHR)) m_bfCntAct = TRUE;
	return (m_bfCntAct);
}
BOOL	CFIOCBk::Is_PolTim ()
{
	if ((GetTickCount() - m_ulLstTim) >= CBKPOLPER) {
		m_ulLstTim = GetTickCount();
		return (TRUE);
	}
	return (FALSE);
}

WORD CALLBACK EXPORT CFSECBk::FSEPolCBk (WORD usPolReq, DWORD ulInpCnt, 
										 CFSECBk FAR *lpFSECBk)
{
	CFIOCBk	FAR*lpFIOCBk = lpFSECBk->m_lpFIOCBk;
	WORD		usMsgSID = 0;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (usPolReq) {
		case EFFFSEINI:								// Initialization event
			lpFSECBk->m_ulTotCnt = ulInpCnt;
			lpFSECBk->m_ulBegPos = (DWORD) -1L; 
			lpFSECBk->m_ulEndPos = (DWORD) -1L; 
			if (lpFIOCBk) lpFIOCBk->BegCBkPrc (lpFSECBk->m_ulTotCnt, lpFSECBk->m_usActDes);
			break;
		case EFFFSEPOL:								// No sound event
			/////////////////////////////////////////////////////////////////////
			if ((lpFIOCBk) && !lpFIOCBk->CntCBkPrc (ulInpCnt, &usMsgSID)) {
				break;
			}
			break;
		case EFFFSESND:								// Change to snd event
			if (-1L == lpFSECBk->m_ulBegPos) lpFSECBk->m_ulBegPos = ulInpCnt; 
			break;
		case EFFFSESIL:								// Change to sil event
			lpFSECBk->m_ulEndPos = ulInpCnt; 
			break;
		case EFFFSETRM:								// Termination event
			if (lpFIOCBk) lpFIOCBk->EndCBkPrc (ulInpCnt);
			break;
	}

	/////////////////////////////////////////////////////////////////////////
	// Return TRUE to continue processing
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudFil
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CAudFil, CFile)

CAudFil::CAudFil()
{
	/////////////////////////////////////////////////////////////////////////
	// Zero info blocks for safe release on destructor
	/////////////////////////////////////////////////////////////////////////
	memset (&m_ofFilOFS, 0, sizeof (m_ofFilOFS));
	memset (&m_miMasInf, 0, sizeof (m_miMasInf));
	memset (&m_siSegInf, 0, sizeof (m_siSegInf));
	memset (&m_ibInpITC, 0, sizeof (m_ibInpITC));
	memset (&m_ibOutITC, 0, sizeof (m_ibOutITC));

	/////////////////////////////////////////////////////////////////////////
	// Initialize file handle and display event notification window
	/////////////////////////////////////////////////////////////////////////
	m_hFile = CFile::hFileNull;
	m_pAmpDsp = NULL;

	/////////////////////////////////////////////////////////////////////////
	// Allocate work memory in multiples of PCMBLKSIZ, initialize
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (m_hgWrkHdl = GloAloBlk (GMEM_MOVEABLE, PCMBLKSIZ, PCMMINCNT, 
	  PCMMAXCNT, &m_ulWrkSiz))) {
		m_hgWrkHdl = NULL;
		m_ulWrkSiz = 0L;
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return;

}

CAudFil::~CAudFil()
{
	/////////////////////////////////////////////////////////////////////////
	// Release ITCBlk conversion parameters 
	/////////////////////////////////////////////////////////////////////////
	PCMRelITC (GetPCMTyp(), m_ibInpITC);
	PCMRelITC (GetPCMTyp(), m_ibOutITC);

	/////////////////////////////////////////////////////////////////////////
	// Release any Master File allocations
	// Note: Call is safe even if m_miMasInf is only set to zero
	/////////////////////////////////////////////////////////////////////////
	FIOMasRel (&m_miMasInf);
	GloAloRel (m_hgWrkHdl);
	if (m_pAmpDsp = AmpDspEnu()) m_pAmpDsp->RemAudFil (this);
}

/////////////////////////////////////////////////////////////////////////////
// Master File query functions
/////////////////////////////////////////////////////////////////////////////
WORD	CAudFil::IniFilOFS (CString csFilNam, FILFMT *pusFilFmt, HWND hPolWnd, 
		UINT nMsgPrm, CFileException* pError)
{
	/////////////////////////////////////////////////////////////////////////
	// Attempt to open file if name is specified
	/////////////////////////////////////////////////////////////////////////
	if (csFilNam.GetLength()) {
		/////////////////////////////////////////////////////////////////////
		// IDS_OPNFILERR: "Error opening file"
		/////////////////////////////////////////////////////////////////////
		if (HFILE_ERROR == FIOOFSOpn (csFilNam, &m_ofFilOFS, OF_EXIST)) 
			return (IDS_OPNFILERR);
	}

	/////////////////////////////////////////////////////////////////////////
	// Set default file format to PURE
	// Future: Query file if format is "unknown"
	/////////////////////////////////////////////////////////////////////////
	if (!pusFilFmt || !*pusFilFmt) m_miMasInf.ffFilFmt = ALLPURFMT;
	else m_miMasInf.ffFilFmt = *pusFilFmt;

	/////////////////////////////////////////////////////////////////////////
	// Initialize file I/O callback window and callback argument
	/////////////////////////////////////////////////////////////////////////
	m_fcFIOCBk.m_hPolWnd = hPolWnd;
	m_fcFIOCBk.m_nMsgPrm = nMsgPrm;

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CAudFil::IniFilFmt (PCMTYP *pusPCMTyp, WORD *pusChnCnt, 
							DWORD *pulSmpFrq, WORD *pusEncMsk)
{
	/////////////////////////////////////////////////////////////////////////
	// Note: IniFilFmt should probably be integrated in future versions
	//		 with IniFilOFS into a single AudFilOpn call
	// Note: This will also solve the problem of multiple ITC blocks
	//		 being allocated if IniFilFmt is called multiple times
	/////////////////////////////////////////////////////////////////////////
	FIORET	frRetCod;	

	/////////////////////////////////////////////////////////////////////////
	// Set default audio data information
	/////////////////////////////////////////////////////////////////////////
	m_miMasInf.usPCMTyp = (ENUPCM) *pusPCMTyp;					// PCM type	  
	m_miMasInf.usChnCnt = *pusChnCnt;							// Channel count 
	m_miMasInf.ulSmpFrq = *pulSmpFrq;							// Sample freq   
	m_miMasInf.usEncMsk = *pusEncMsk;							// Encoding mask   

	/////////////////////////////////////////////////////////////////////////
	// IDS_MASLODERR: "Error loading master file"
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOMasLod (&m_ofFilOFS, &m_miMasInf, NULL, 0L)) 
			return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_MASLODERR);

	/////////////////////////////////////////////////////////////////////////
	// Retrieve header specified audio data information
	/////////////////////////////////////////////////////////////////////////
	*pusPCMTyp = m_miMasInf.usPCMTyp;				// PCM type	  
	*pusChnCnt = m_miMasInf.usChnCnt;				// Channel count 
	*pulSmpFrq = m_miMasInf.ulSmpFrq;				// Sample freq   
	*pusEncMsk = m_miMasInf.usEncMsk;				// Encoding mask   

	/////////////////////////////////////////////////////////////////////////
	// Fill in default values if not specified by caller or header
	/////////////////////////////////////////////////////////////////////////
	*pusPCMTyp = m_miMasInf.usPCMTyp = *pusPCMTyp ? *pusPCMTyp : GENPCM000;
	*pusChnCnt = m_miMasInf.usChnCnt = *pusChnCnt ? *pusChnCnt : (WORD) PCMCapQry (*pusPCMTyp, CHNDEFQRY, 0L);
	*pulSmpFrq = m_miMasInf.ulSmpFrq = *pulSmpFrq ? *pulSmpFrq : PCMCapQry (*pusPCMTyp, FRQDEFQRY, 0L);
	*pusEncMsk = m_miMasInf.usEncMsk = *pusEncMsk ? *pusEncMsk : FIOENCNON;

	/////////////////////////////////////////////////////////////////////////
	// Note: Multiple calls are made to PCMAloITC, but no current PCM 
	//		 formats require additional memory allocations
	/////////////////////////////////////////////////////////////////////////
	LPITCI		lpInpIni = NULL;
	LPITCI		lpOutIni = NULL;
	ITCINI		iiInpIni;
	ITCINI		iiOutIni;

	/////////////////////////////////////////////////////////////////////////
	// Initialize the ITC block frequency for CVSD PCM types
	/////////////////////////////////////////////////////////////////////////
	if ((HARPCM001 == GetPCMTyp()) || 
		(PTCPCM001 == GetPCMTyp()) ||
		(NWVPCM001 == GetPCMTyp())) {
		PCMAloITC (GetPCMTyp(), NULL, &iiInpIni);				// Load def
		PCMAloITC (GetPCMTyp(), NULL, &iiOutIni);				// Load def

//		/////////////////////////////////////////////////////////////////////
//		// Use higher order filter for CVSD if requested
//		/////////////////////////////////////////////////////////////////////
//		if ((AAF_Q6TYP == lpCvtBlk->usTDLAAF) || lpCvtBlk->bfFFTAAF) {
//			iiInpIni.ciCVS.usLowTyp = CVSLI6FLT;
//			iiOutIni.ciCVS.usLowTyp = CVSLI6FLT;
//		}

		iiInpIni.ciCVS.ulSmpFrq = GetSmpFrq();
		iiOutIni.ciCVS.ulSmpFrq = GetSmpFrq();
	}

	/////////////////////////////////////////////////////////////////////////
	// Initialize ITCBlk conversion parameters 
	/////////////////////////////////////////////////////////////////////////
	PCMAloITC (GetPCMTyp(), m_ibInpITC, lpInpIni);
	PCMAloITC (GetPCMTyp(), m_ibOutITC, lpOutIni);

	/////////////////////////////////////////////////////////////////////////
	// Load any ITC block header information from master file
	/////////////////////////////////////////////////////////////////////////
	FIOMasQry (&m_miMasInf, MASITCQRY, m_ibInpITC, sizeof (m_ibInpITC));
	FIOMasQry (&m_miMasInf, MASITCQRY, m_ibOutITC, sizeof (m_ibOutITC));

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CAudFil::IniFilFmt (CAudFil *pAudFil)
{
	PCMTYP	usPCMTyp = pAudFil->GetPCMTyp();
	WORD 	usChnCnt = pAudFil->GetChnCnt(); 
	DWORD 	ulSmpFrq = pAudFil->GetSmpFrq();
	WORD 	usEncMsk = pAudFil->GetEncMsk();
	return (IniFilFmt (&usPCMTyp, &usChnCnt, &ulSmpFrq, &usEncMsk));
}

BOOL		CAudFil::GetStatus (CFileStatus &rStatus)
{
	/////////////////////////////////////////////////////////////////////////
	// Get basic file status information
	/////////////////////////////////////////////////////////////////////////
// ajm
// 09/29/97: Long File Name support
//	if (!CFile::GetStatus (m_ofFilOFS.szPathName, rStatus)) return (FALSE);
	char	szShtNam[FIOMAXPTH];
	if (FIORETSUC != FIOOFSCvt (GetFilOFS()->szPathName, szShtNam, FIOMAXPTH))
		return (FALSE);	
	if (!CFile::GetStatus (szShtNam, rStatus)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Retrieve segment byte length
    // Note: FIOSegSel() updates m_miMasInf for correct GetSmpCnt() usage
	/////////////////////////////////////////////////////////////////////////
	if (FIOSegDes (SEGLENQRY, &m_miMasInf, &m_siSegInf, &rStatus.m_size, 
		sizeof (rStatus.m_size))) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);

}

OFSTRUCT_V*	CAudFil::GetFilOFS ()
{
	return (&m_ofFilOFS); 
}

MASINF	*	CAudFil::GetMasInf ()
{
	return (&m_miMasInf); 
}

SEGINF	*	CAudFil::GetSegInf ()
{
	return (&m_siSegInf); 
}

FILFMT		CAudFil::GetFilFmt ()
{
	return (m_miMasInf.ffFilFmt);
}

PCMTYP		CAudFil::GetPCMTyp ()
{
	return (m_miMasInf.usPCMTyp);
}

WORD		CAudFil::GetEncMsk ()
{
	return (PCMBIODEF);
}

WORD		CAudFil::GetChnCnt ()
{
	return (m_miMasInf.usChnCnt);
}

DWORD		CAudFil::GetSmpFrq ()
{
	return (m_miMasInf.ulSmpFrq);
}

DWORD		CAudFil::GetSmpCnt ()
{
	CFileStatus	fsFilSta;

	/////////////////////////////////////////////////////////////////////////
    // Note: FIOSegSel() updates m_miMasInf for correct GetStatus() usage
	/////////////////////////////////////////////////////////////////////////
	if (!GetStatus (fsFilSta)) return (0L);
	return (PCMByt2Sl (GetPCMTyp(), GetChnCnt(), fsFilSta.m_size, m_ibInpITC)); 	 
}

float		CAudFil::SmpToMSec (DWORD ulSmpPos)
{
	/////////////////////////////////////////////////////////////////////////
	// Convert samples to millisec
	/////////////////////////////////////////////////////////////////////////
	return (GetSmpFrq() ? (1000L * (ulSmpPos / (float) GetSmpFrq())) : 0L);
}

DWORD		CAudFil::MSecToSmp (float flTimPos)
{
	/////////////////////////////////////////////////////////////////////////
	// Convert millisec to samples
	/////////////////////////////////////////////////////////////////////////
	return (GetSmpFrq() ? (DWORD) ((flTimPos * GetSmpFrq()) / 1000L) : 0L);
}

DWORD		CAudFil::SmpSmpLow (DWORD ulSmpCnt)
{
	return (PCMSmpLow (GetPCMTyp(), GetChnCnt(), ulSmpCnt, m_ibInpITC));
}

BOOL		CAudFil::Is_FmtCmp (PCMTYP usPCMTyp, WORD usEncMsk, WORD usChnCnt, 
			DWORD ulSmpFrq, float flFrqThr)
{
	#define		FRQUNDTHR(f1,f2,th) ((labs (f1 - f2) / 100.) <= th) 

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return ((usPCMTyp == GetPCMTyp()) 
		&& (usEncMsk == GetEncMsk()) 
		&& (usChnCnt == GetChnCnt()) 
		&& FRQUNDTHR (ulSmpFrq, GetSmpFrq(), flFrqThr));
}

BOOL		CAudFil::Is_FmtCmp (CAudFil *pAudFil, float flFrqThr)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (Is_FmtCmp (pAudFil->GetPCMTyp(), pAudFil->GetEncMsk(),
		pAudFil->GetChnCnt(), pAudFil->GetSmpFrq(), flFrqThr));
}


CAmpDsp	*	CAudFil::AmpDspEnu (CAmpDsp *pAmpDsp) 
{
	/////////////////////////////////////////////////////////////////////////
	// Enumerate associated amplitude displays
	// Note: Only one allowed at present, so return NULL after first call
	/////////////////////////////////////////////////////////////////////////
	if (pAmpDsp) return (NULL);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (AfxIsValidAddress (m_pAmpDsp, sizeof (*m_pAmpDsp), FALSE) 
		&& m_pAmpDsp->IsKindOf(RUNTIME_CLASS(CAmpDsp)) ? m_pAmpDsp : NULL);
}

/////////////////////////////////////////////////////////////////////////////
// Low Level File I/O functions
/////////////////////////////////////////////////////////////////////////////
BOOL		CAudFil::Open (UINT nOpenFlags, CFileException* pError)
{
	CFileStatus	fsFilSta;

	/////////////////////////////////////////////////////////////////////////
	// Calculate number of audio bytes available
	/////////////////////////////////////////////////////////////////////////
	if (!GetStatus (fsFilSta)) m_ulBytRem = 0L;
	else m_ulBytRem = fsFilSta.m_size;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
// ajm
// 09/29/97: Long File Name support
//	return (CFile::Open(GetFilOFS()->szPathName, nOpenFlags, pError));
	char	szShtNam[FIOMAXPTH];
	if (FIORETSUC != FIOOFSCvt (GetFilOFS()->szPathName, szShtNam, FIOMAXPTH))
		return (-1);	
	return (CFile::Open(szShtNam, nOpenFlags, pError));
}

DWORD		CAudFil::GetSegOff ()
{
	DWORD		ulSegOff;
	if (FIOSegDes (SEGOFFQRY, &m_miMasInf, &m_siSegInf, &ulSegOff, 
		sizeof (ulSegOff))) return (0L);
	return (ulSegOff);
}
LONG		CAudFil::Seek (LONG lSmpOff, UINT nFrom, DWORD ulGrdSmp)
{
	DWORD		ulSegOff;
	DWORD		ulBytOff;
	CFileStatus	fsFilSta;
	LPVOID		lpWrkBuf;

	/////////////////////////////////////////////////////////////////////////
	// Retrieve segment byte offset
	/////////////////////////////////////////////////////////////////////////
	ulSegOff = GetSegOff();

	/////////////////////////////////////////////////////////////////////////
	// Retrieve segment audio byte length
	/////////////////////////////////////////////////////////////////////////
	if (!GetStatus (fsFilSta)) m_ulBytRem = 0L;
	else m_ulBytRem = fsFilSta.m_size;

	/////////////////////////////////////////////////////////////////////////
	// Round offset sample position down to guarantee full read/write
	// Adjust byte remaining count to insure read within bounds
	// Note: Seek past EOF inhibited, even for write operation (pad silence)
	/////////////////////////////////////////////////////////////////////////
	ulBytOff = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), SmpSmpLow (lSmpOff), m_ibInpITC);
	m_ulBytRem -= (ulBytOff = min (ulBytOff, m_ulBytRem));

	/////////////////////////////////////////////////////////////////////////
	// Safely move to new position past header, before trailer (if any)
	// Adjust for (CFile::current == nFrom)
	// Future: negative and relative positions
	/////////////////////////////////////////////////////////////////////////
	if (-1L == (ulBytOff = CFile::Seek(ulSegOff + ulBytOff, nFrom))) return (-1L);
	ulBytOff -= ulSegOff;

	/////////////////////////////////////////////////////////////////////////
	// Adjust Guard sample count to insure read within bounds
	/////////////////////////////////////////////////////////////////////////
	if (!ulGrdSmp) ulGrdSmp = PCMCapQry (GetPCMTyp(), GRDSMPQRY, 0L);
	ulGrdSmp = min (ulGrdSmp, PCMByt2Sl (GetPCMTyp(), GetChnCnt(), ulBytOff, m_ibInpITC)); 	 

	/////////////////////////////////////////////////////////////////////////
	// Compute ITCBlk conversion parameters for current position
	/////////////////////////////////////////////////////////////////////////
	lpWrkBuf = GloMemLck (m_hgWrkHdl);
	PCMGrdITC (m_hFile, ulGrdSmp, lpWrkBuf, lpWrkBuf ? m_ulWrkSiz : 0L, 
		GetPCMTyp(), GetChnCnt(), PCMBIODEF, m_ibInpITC, NULL, NULL, NULL, 0L);
	if (lpWrkBuf) GloMemUnL (m_hgWrkHdl);

	/////////////////////////////////////////////////////////////////////////
	// Duplicate current position ITCBLK for both input and output
	// Note: This simple duplication is permissable for now, since, no
	// 		 current PCM formats require additional memory allocations. This
	//		 condition will probably not hold true for future versions.
	/////////////////////////////////////////////////////////////////////////
	*m_ibOutITC = *m_ibInpITC; 

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (PCMByt2Sl (GetPCMTyp(), GetChnCnt(), ulBytOff, m_ibInpITC)); 	 
}

DWORD		CAudFil::Read (LPBYTE lpDstBuf, DWORD ulBufSiz, DWORD ulSmpCnt, 
			DWORD *pulBytCnt, BOOL bfRawMod)
{
	DWORD	ulBytCnt;
	DWORD	ulSmpInp;

	/////////////////////////////////////////////////////////////////////////
	if (pulBytCnt) *pulBytCnt = 0L;
	if (!ulBufSiz) return (0L);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (bfRawMod) {
		/////////////////////////////////////////////////////////////////////
		// Perform simple file read if raw mode requested
		// Prevent buffer or file boundary overflow
		/////////////////////////////////////////////////////////////////////
		DWORD	ulBytReq = min (min (m_ulBytRem, ulBufSiz), 
				PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), ulSmpCnt, m_ibInpITC));
		ulBytCnt = Read (lpDstBuf, ulBytReq);
		if ((-1L == ulBytCnt) || (0L == ulBytCnt)) return (ulBytCnt);
		ulSmpInp = min (ulSmpCnt, PCMByt2Sl (GetPCMTyp(), GetChnCnt(), ulBytCnt, m_ibInpITC));
	} else {
		DWORD	ulSmpReq = min (ulSmpCnt, sizeof (GENSMP) / ulBufSiz);
		ulSmpInp = PCMRd_G16 (m_hFile, m_ulBytRem, (LPGSMP) lpDstBuf, 
			min (ulSmpCnt, sizeof (GENSMP) / ulBufSiz), GetPCMTyp(), 
			GetChnCnt(), PCMBIODEF, m_ibInpITC, &ulBytCnt, NULL, NULL, 0L);
		if ((-1L == ulSmpInp) || (0L == ulSmpInp)) return (ulSmpInp);
	}
	if (pulBytCnt) *pulBytCnt = ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	m_ulBytRem -= ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	// Compute sample count reduced for PCM with multiple samples per byte
	/////////////////////////////////////////////////////////////////////////
	return (min (ulSmpInp, ulSmpCnt));

}

DWORD		CAudFil::Read (MXMBLK *lpMxMArr, WORD usArrLen, float flSmppGP)
{
	DWORD		ulGPtCnt;
	LPVOID		lpWrkBuf;
	DWORD		ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (lpWrkBuf = GloMemLck (m_hgWrkHdl))) return (0L);
	ulGPtCnt = PCMRd_MxM (m_hFile, -1L, lpMxMArr, usArrLen, flSmppGP, lpWrkBuf, 
		m_ulWrkSiz, GetPCMTyp(), GetChnCnt(), PCMBIODEF, m_ibInpITC, &ulBytCnt, 
		NULL, (PCMPOLPRC) GetCBkPrc(), (DWORD) GetCBkArg(IDS_POLACTGPH));
	GloMemUnL (m_hgWrkHdl);

	/////////////////////////////////////////////////////////////////////////
	m_ulBytRem -= ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	return (ulGPtCnt);
}

DWORD		CAudFil::Read (CAudEff *pAudEff, DWORD ulSmpCnt)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (EffPtoEBS (m_hFile, &m_ulBytRem, pAudEff->GetEBSBlk(), ulSmpCnt,
		GetPCMTyp(), GetChnCnt(), PCMBIODEF, GetSmpFrq(), m_ibInpITC, 
		(EBSFRDPRC) PCMRd_G16));
}

float		CAudFil::Read (DWORD ulSmpCnt, float flTrgLvl, float flTrgExc, 
						float flAdjMax)
{
	#define	NRMNOILVL (float) .05
	#define	NRMNOIEXC (float) .01
	float	flNrmAtt;
	DWORD	ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	ulBytCnt = min (m_ulBytRem, PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), ulSmpCnt, m_ibInpITC));

	/////////////////////////////////////////////////////////////////////////
	// Scan file for normalization level
	/////////////////////////////////////////////////////////////////////////
	EffNrmLvl (m_hFile, ulBytCnt, NRMNOILVL, NRMNOIEXC, flTrgLvl, flTrgExc, 
		flAdjMax, GetPCMTyp(), GetChnCnt(), PCMBIODEF, GetSmpFrq(), &flNrmAtt, 
		m_ibInpITC, (EFFPOLPRC) GetCBkPrc(), (DWORD) GetCBkArg(IDS_POLACTSCN), 
		(EBSFRDPRC) PCMRd_G16);

	/////////////////////////////////////////////////////////////////////////
	return (flNrmAtt);
}

WORD		CAudFil::Read (DWORD ulSmpCnt, float flFrmTim, float flResTim, 
						float flSndThr, float flAtkRat, float flDcyRat, 
						float flAtkGrd, float flDcyGrd, DWORD ulHghPas, 
						DWORD *pulSndOff, DWORD *pulSndLen)
{
	CFSECBk	fcFSECBk(&m_fcFIOCBk);
	FSEBLK  fbFSEBlk;
	DWORD	ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	ulBytCnt = min (m_ulBytRem, PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), ulSmpCnt, m_ibInpITC));

	/////////////////////////////////////////////////////////////////////////
	// Scan file for silence / sound
	/////////////////////////////////////////////////////////////////////////
	if (EffFSEAlo (flFrmTim, flResTim, flSndThr, flAtkRat, flDcyRat, 
		flAtkGrd, flDcyGrd, ulHghPas, GetPCMTyp(), GetChnCnt(), PCMBIODEF, 
		GetSmpFrq(), &fbFSEBlk)) return (IDS_INSMEMERR);
	EffFSEEnu (m_hFile, ulBytCnt, &fbFSEBlk, m_ibInpITC, 
		(EFFFSECBK) fcFSECBk.GetCBkPrc(), (DWORD) fcFSECBk.GetCBkArg(IDS_POLACTSCN),
		(EBSFRDPRC) PCMRd_G16);
	EffFSERel (&fbFSEBlk);

	/////////////////////////////////////////////////////////////////////////
	// Compute offset and length; insure non-negative values
	/////////////////////////////////////////////////////////////////////////
	*pulSndOff = fcFSECBk.m_ulBegPos;
	*pulSndLen = fcFSECBk.m_ulEndPos - min (fcFSECBk.m_ulBegPos, fcFSECBk.m_ulEndPos);

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

DWORD		CAudFil::Write (LPBYTE lpSrcBuf, DWORD ulSmpCnt, DWORD *pulBytCnt)
{
	DWORD	ulBytCnt;
	DWORD	ulSmpOut;

	/////////////////////////////////////////////////////////////////////////
	if (pulBytCnt) *pulBytCnt = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Sample request rounding assures a full write 
	/////////////////////////////////////////////////////////////////////////
	ulSmpCnt = SmpSmpLow (ulSmpCnt);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	ulBytCnt = PCMWr_PCM ((LPGSMP) lpSrcBuf, ulSmpCnt, m_hFile, 
		-1L, GetPCMTyp(), GetChnCnt(), PCMBIODEF, m_ibOutITC, 
		&ulSmpOut, NULL, NULL, 0L);
	if ((-1L == ulBytCnt) || (0L == ulBytCnt)) return (ulBytCnt);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (pulBytCnt) *pulBytCnt = ulBytCnt;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (ulSmpOut);

}

DWORD		CAudFil::Write (CAudEff *pAudEff, DWORD ulSmpCnt)
{
	DWORD	ulSmpOut = pAudEff->GetEBSBlk()->ulSmpCnt;

	/////////////////////////////////////////////////////////////////////////
	if (-1L == EffEBStoP (pAudEff->GetEBSBlk(), ulSmpCnt, m_hFile, -1L,
		GetPCMTyp(), PCMBIODEF, m_ibOutITC, (EBSFWRPRC) PCMWr_PCM)) return (-1L);

	/////////////////////////////////////////////////////////////////////////
	return (ulSmpOut - pAudEff->GetEBSBlk()->ulSmpCnt);
}

DWORD	CAudFil::Copy (CAudFil *pDstFil, DWORD ulSmpCnt, CFIOCBk *pFIOCBk)
{
	LPBYTE	lpWrkBuf;
	DWORD	ulBytOut;
	DWORD	ulSmpOut;
	DWORD	ulSmpInp;
	DWORD	ulSmpTot = 0L;
	WORD	usMsgSID = 0;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!(lpWrkBuf = (LPBYTE) GloMemLck (m_hgWrkHdl))) return (0L);

	/////////////////////////////////////////////////////////////////////////
	// Show/Hide Progress indicator for time consuming operations
	/////////////////////////////////////////////////////////////////////////
	if (pFIOCBk) pFIOCBk->BegCBkPrc (min (ulSmpCnt, GetSmpCnt()), IDS_POLACTCOP);

	/////////////////////////////////////////////////////////////////////////
	// Raw mode requested: simply transfer raw PCM to audio file
	/////////////////////////////////////////////////////////////////////////
	while (TRUE) {
		/////////////////////////////////////////////////////////////////////
		ulSmpInp = Read (lpWrkBuf, m_ulWrkSiz, ulSmpCnt, &ulBytOut, TRUE);
		if (!ulSmpInp || (-1L == ulSmpInp)) break;

		/////////////////////////////////////////////////////////////////////
		//	Future: Add "raw" mode switch to CAudFil::Write() function
		//	(this will also localize ITCBlk for PCMByt2Sl use)
		/////////////////////////////////////////////////////////////////////
		ulBytOut = pDstFil->Write (lpWrkBuf, ulBytOut);
		if (!ulBytOut || (-1L == ulBytOut)) break;
		ulSmpOut = min (ulSmpCnt, PCMByt2Sl (pDstFil->GetPCMTyp(), 
					pDstFil->GetChnCnt(), ulBytOut, NULL));

		/////////////////////////////////////////////////////////////////////
		ulSmpCnt   -= ulSmpInp;
		ulSmpTot   += ulSmpOut;

		/////////////////////////////////////////////////////////////////////
		if ((pFIOCBk) && !pFIOCBk->CntCBkPrc (ulSmpTot, &usMsgSID)) {
			ulSmpTot = -1L;
			break;
		}

	}
	if (pFIOCBk) pFIOCBk->EndCBkPrc (ulSmpTot);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	GloMemUnL (m_hgWrkHdl);
	return (((-1L == ulSmpInp) || (-1L == ulBytOut)) ? -1L : ulSmpTot);
}

DWORD		CAudFil::Erase (DWORD ulSmpCnt, BOOL bfRawMod)
{
	LPBYTE	lpWrkBuf;
	DWORD	ulSmpOut;
	DWORD	ulSmpTot = 0L;
	WORD	usMsgSID = 0;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (lpWrkBuf = (LPBYTE) GloMemLck (m_hgWrkHdl))) return (0L);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	ulSmpCnt = SmpSmpLow (ulSmpCnt);

	/////////////////////////////////////////////////////////////////////////
	// Show/Hide Progress indicator for time consuming operations
	/////////////////////////////////////////////////////////////////////////
	m_fcFIOCBk.BegCBkPrc (ulSmpCnt, IDS_POLACTERA);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (bfRawMod) {
		/////////////////////////////////////////////////////////////////////
		// Perform simple file write if raw mode requested
		/////////////////////////////////////////////////////////////////////
		PCMSetSil (GetPCMTyp(), lpWrkBuf, m_ulWrkSiz);
		while (ulSmpCnt) {
			DWORD	ulBytCnt = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), ulSmpCnt, m_ibOutITC);
			DWORD	ulBytOut = Write (lpWrkBuf, min (m_ulWrkSiz, ulBytCnt));
			if ((-1L == ulBytOut) || (0L == ulBytOut)) return (ulBytOut);
			ulSmpOut = min (ulSmpCnt, PCMByt2Sl (GetPCMTyp(), GetChnCnt(), ulBytOut, m_ibOutITC));
			ulSmpTot += ulSmpOut;
			ulSmpCnt -= min (ulSmpCnt, ulSmpOut);
			if (!m_fcFIOCBk.CntCBkPrc (ulSmpTot)) break;
		}
	}
	else {
		/////////////////////////////////////////////////////////////////////
		// Perform converted PCM write; refresh silence buffer every pass
		/////////////////////////////////////////////////////////////////////
		DWORD ulSmpSil = PCMByt2Sl (GENPCM000, GetChnCnt(), m_ulWrkSiz, m_ibOutITC); 	 
		while (ulSmpCnt) {
			PCMSetSil (GENPCM000, lpWrkBuf, m_ulWrkSiz);
			ulSmpOut = Write (lpWrkBuf, min (ulSmpCnt, ulSmpSil), NULL);
			if (!ulSmpOut || (-1L == ulSmpOut)) break;
			ulSmpTot += ulSmpOut;
			ulSmpCnt -= min (ulSmpCnt, ulSmpOut);
			if (!m_fcFIOCBk.CntCBkPrc (ulSmpTot)) break;
		}
	}
	GloMemUnL (m_hgWrkHdl);
	m_fcFIOCBk.EndCBkPrc (ulSmpTot);

	/////////////////////////////////////////////////////////////////////////
	return (ulSmpTot);

}

void		CAudFil::Close ()
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (CFile::hFileNull != m_hFile) CFile::Close();

}

/////////////////////////////////////////////////////////////////////////////
// Exported Functions
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export AudFilTypEnu (WORD FAR *pusFilTyp, LPSTR szDesStr, WORD usMaxLen)
{
	char	szWrkBuf[FIOMAXDES];
	CString csWrkStr;
	int		ii;

	/////////////////////////////////////////////////////////////////////////
	// Return the CDocTemplate format description string
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Scan File I/O DLL for all supported types
	/////////////////////////////////////////////////////////////////////////
	if (*pusFilTyp = FIOOpnEnu ((FILFMT) *pusFilTyp)) {
		if (!csWrkStr.LoadString(IDS_VFEAUDTYP)) return (FALSE);

		FIODesQry ((FILFMT) *pusFilTyp, szWrkBuf, FIOMAXDES);	
		while (-1 != (ii = csWrkStr.Find("%1")))
			csWrkStr = csWrkStr.Left(ii) + szWrkBuf 
				+ csWrkStr.Right(csWrkStr.GetLength() - ii - 2);

		FIOExtQry ((FILFMT) *pusFilTyp, szWrkBuf, FIOMAXDES);	
		while (-1 != (ii = csWrkStr.Find("%2")))
			csWrkStr = csWrkStr.Left(ii) + szWrkBuf 
				+ csWrkStr.Right(csWrkStr.GetLength() - ii - 2);

		strncpy (szDesStr, csWrkStr, usMaxLen);
		return (TRUE);
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

extern "C"
WORD FAR PASCAL _export AudFilPCMEnu (WORD usFilTyp, WORD FAR *pusPCMTyp, LPSTR szDesStr, WORD usMaxLen)
{
	if (!usMaxLen) return (FALSE);
	/////////////////////////////////////////////////////////////////////////
	// Scan PCM DLL and associate PCM types with file format
	/////////////////////////////////////////////////////////////////////////
	switch (usFilTyp) {
		case ALLPURFMT: 				// File format = Pure
		case VBSIDXFMT:					// File format = Indexed VBase
			if (*pusPCMTyp = PCMTypEnu ((PCMTYP) *pusPCMTyp)) {
				// Note: Remove when MSADPCM is ready
				if ((MSAPCM004 == *pusPCMTyp) 
					&& !(*pusPCMTyp = PCMTypEnu ((PCMTYP) *pusPCMTyp))) break;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}
			break;
		case WAVHDRFMT:					// File format = MM Wave		
			if (*pusPCMTyp < DLGPCM004) { 
				*pusPCMTyp = DLGPCM004;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}				 
			if (*pusPCMTyp < DLGPCM008) { 
				*pusPCMTyp = DLGPCM008;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}				 
			if (*pusPCMTyp < G11PCMF08) { 
				*pusPCMTyp = G11PCMF08;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}				 
			if (*pusPCMTyp < G11PCMI08) { 
				*pusPCMTyp = G11PCMI08;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}
			if (*pusPCMTyp < MPCPCM008) { 
				*pusPCMTyp = MPCPCM008;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}
			if (*pusPCMTyp < MPCPCM016) {
				*pusPCMTyp = MPCPCM016;
				PCMDesQry ((PCMTYP) *pusPCMTyp, szDesStr, usMaxLen);	
				return (TRUE);
			}
			break;
		//
		// Use custom format #'s for redundant ones like "OKI"
		// This will permit AudFilxxxEnu to distinguish based upon PCMTyp
		//
	}
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

extern "C"
WORD FAR PASCAL _export AudFilChnEnu (WORD usPCMTyp, WORD FAR *pusChnCnt)
{
	/////////////////////////////////////////////////////////////////////////
	// Scan PCM DLL for all supported channel counts
	/////////////////////////////////////////////////////////////////////////
	if (*pusChnCnt = PCMChnEnu ((PCMTYP) usPCMTyp, *pusChnCnt)) {
		return (TRUE);
	}
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudFilFrqEnu (WORD usPCMTyp, DWORD FAR *pulSmpFrq)
{
	/////////////////////////////////////////////////////////////////////////
	// Scan PCM DLL for all supported frequencies
	/////////////////////////////////////////////////////////////////////////
	if (*pulSmpFrq = PCMFrqEnu ((PCMTYP) usPCMTyp, *pulSmpFrq)) {
		return (TRUE);
	}
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export AudFilAAFEnu (WORD FAR *pusAAFAlg, LPSTR szDesStr, WORD usMaxLen)
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
WORD FAR PASCAL _export AudFilResEnu (WORD FAR *pusResAlg, LPSTR szDesStr, WORD usMaxLen)
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
WORD FAR PASCAL _export	AudFilOpn (CAudFil FAR * FAR *ppAudFil, 
						const char FAR *pszFilNam, DWORD ulSegSel, 
						WORD FAR *pusFilFmt, WORD FAR *pusPCMTyp,
						WORD FAR *pusChnCnt, DWORD FAR *pulSmpFrq,
						WORD FAR *pusEncMsk, 
						VISWNDHDL hPolWnd, DWORD ulPolArg)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	*ppAudFil = new CAudFil;

	/////////////////////////////////////////////////////////////////////////
	// Note: IniFilFmt should probably be integrated in future versions
	//		 with IniFilOFS into a single AudFilOpn call
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = (*ppAudFil)->IniFilOFS (pszFilNam, (FILFMT FAR *) pusFilFmt,
		(HWND) hPolWnd, (UINT) ulPolArg)) {
		delete *ppAudFil;
		*ppAudFil = NULL;
		return (usRetCod);
	}
	if (usRetCod = (*ppAudFil)->IniFilFmt ((PCMTYP FAR *) pusPCMTyp, pusChnCnt, 
		pulSmpFrq, pusEncMsk)) {
	  	delete *ppAudFil;
		*ppAudFil = NULL;
		return (usRetCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// Query user for segment selection
    // Note: FIOSegSel() updates m_miMasInf for correct GetSmpCnt() usage
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = FIOSegSel (SEGSELQRY, (*ppAudFil)->GetMasInf(), 
		(*ppAudFil)->GetSegInf(), (*ppAudFil)->GetSegInf())) 
		return ((FIORETCAN == usRetCod) ? IDS_USRCANREQ : IDS_SEGSELERR);

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

extern "C"
WORD FAR PASCAL _export AudFilCls (CAudFil FAR * FAR *ppAudFil)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == *ppAudFil) return (-1);

	/////////////////////////////////////////////////////////////////////////
	delete *ppAudFil;
	*ppAudFil = NULL;
	return (0);

}

extern "C"
DWORD FAR PASCAL _export AudFilSmpCnt (CAudFil FAR *pAudFil)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (0L);
	return (pAudFil->GetSmpCnt());
}

extern "C"
DWORD FAR PASCAL _export AudFilSmpFrq (CAudFil FAR *pAudFil)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (0L);
	return (pAudFil->GetSmpFrq());
}

extern "C"
WORD FAR PASCAL _export AudFilCmpChk (CAudFil FAR *pAudFil, CAudFil FAR *pCmpFil,
						 float flFrqThr)
{
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAudFil) || (NULL == pCmpFil)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Check for frequency compatability (only!)
	// Future: Offer other conversion options
	/////////////////////////////////////////////////////////////////////////
	return (pAudFil->Is_FmtCmp (pAudFil->GetPCMTyp(), pAudFil->GetEncMsk(),
		pAudFil->GetChnCnt(), pCmpFil->GetSmpFrq(), flFrqThr));
}

extern "C"
float FAR PASCAL _export AudFilSmpToMSec (CAudFil FAR *pAudFil, DWORD ulSmpPos)
{
	/////////////////////////////////////////////////////////////////////////
	// Convert samples to millisec
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (0);
	return (pAudFil->SmpToMSec(ulSmpPos));
}

extern "C"
DWORD FAR PASCAL _export AudFilMSecToSmp (CAudFil FAR *pAudFil, float flTimPos)
{
	/////////////////////////////////////////////////////////////////////////
	// Convert millisec to samples
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (0L);
	return (pAudFil->MSecToSmp(flTimPos));
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
extern "C"
DWORD FAR PASCAL _export CIFFndFst (LPCSTR lpFilNam, LPVOID lpFndDat)
{
	return (FIOFndFst (lpFilNam, lpFndDat));
}

extern "C"
DWORD FAR PASCAL _export CIFFndNxt (DWORD hFndFil, LPVOID lpFndDat)
{
	return (FIOFndNxt (hFndFil, lpFndDat));
}

extern "C"
DWORD FAR PASCAL _export CIFFndEnd (DWORD hFndFil)
{
	return (FIOFndEnd (hFndFil));
}

