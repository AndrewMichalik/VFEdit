/////////////////////////////////////////////////////////////////////////////
// SesFil.cpp : Implementation of the CSesFil classes
// Copyright (c) 1987-1996 Andrew J. Michalik
//
// Class Audio Session File
// CSesFil encapsulates a complete copy of raw Audio File PCM data.
// May use cached headers and trailers for performance improvement.
// The snippet file is raw audio data (or "window" into raw Edit File data).
// CSesFil is responsible for read/write integrity of headers & trailers.
// CSesFil maintains a full undo/redo history. 
//
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "sesfil.h"						// Audio session file support defs
#include "undlst.h"						// Undo file support defs

/////////////////////////////////////////////////////////////////////////
// Note: Remove when MSADPCM and multi-channel are ready
#include "audeff.h"						// Audio effects support defs
extern "C"
WORD FAR PASCAL _export	AudFilOpn (CAudFil FAR * FAR *ppAudFil, 
						const char FAR *pszFilNam, DWORD ulSegSel, 
						WORD FAR *pusFilFmt, WORD FAR *pusPCMTyp,
						WORD FAR *pusChnCnt, DWORD FAR *pulSmpFrq,
						WORD FAR *pusEncMsk, 
						VISWNDHDL hPolWnd, DWORD ulPolArg);
/////////////////////////////////////////////////////////////////////////////

extern "C"
{
	#include "os_dev\winmsg.h"			// User message support
}

/////////////////////////////////////////////////////////////////////////////
//						External References
/////////////////////////////////////////////////////////////////////////////
extern  CIFGLO  CIFGlo;					// C Interface Library Globals

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const char	TMPFILPRE[] = "V_AF";		// Audio file temp file prefix
const char	WRKFILEXT[] = ".WRK";		// Work file extension		  
const char	SNPFILEXT[] = ".SNP";		// Snippet file extension	   

/////////////////////////////////////////////////////////////////////////////
// CSesFil
/////////////////////////////////////////////////////////////////////////////
CSesFil::CSesFil()
{
	/////////////////////////////////////////////////////////////////////////
	// CAudFil zeros info blocks for safe release on destructor
	/////////////////////////////////////////////////////////////////////////
	m_pUndLst = new CUndLst();
}

CSesFil::~CSesFil()
{
	/////////////////////////////////////////////////////////////////////////
	// Release any Segment allocations
	/////////////////////////////////////////////////////////////////////////
	FIOTxtRel (m_atAnoTxt.GetAnoHdl());
	FIOSnpRel (GetSegInf());
	delete m_pUndLst;
}

WORD	CSesFil::IniFilOFS (CString csFilNam,  
		FILFMT *pusFilFmt, PCMTYP *pusPCMTyp, WORD *pusChnCnt, 
		DWORD *pulSmpFrq, CString csTmpDir, HWND hPolWnd, UINT nMsgPrm)
{
	WORD	usRetCod;
	WORD	usEncMsk;
	FIORET	frRetCod;	
	CString	csTmpPfx;

	/////////////////////////////////////////////////////////////////////////
	// Initialize audio file
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = CAudFil::IniFilOFS (csFilNam, pusFilFmt, hPolWnd, nMsgPrm)) 
		return (usRetCod);
	if (usRetCod = CAudFil::IniFilFmt (pusPCMTyp, pusChnCnt, pulSmpFrq, 
		&usEncMsk)) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Generate full path for temporary files
	/////////////////////////////////////////////////////////////////////////
	if (!strlen (csTmpPfx = CTmpFil::GenTmpPfx (csTmpDir, TMPFILPRE))) {
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPDIRERR, (LPCSTR) csTmpDir);
		return ((WORD) -1);
	}
	m_csTmpDir = csTmpDir;

	/////////////////////////////////////////////////////////////////////////
	// Initialize work and snippet files
	/////////////////////////////////////////////////////////////////////////
	if (m_tfWrkFil.IniFilOFS(csTmpPfx + WRKFILEXT)) return ((WORD) -1);
	if (m_tfSnpFil.IniFilOFS(csTmpPfx + SNPFILEXT)) return ((WORD) -1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo list directory location
	/////////////////////////////////////////////////////////////////////////
	m_pUndLst->IniTmpPfx (csTmpPfx);

	/////////////////////////////////////////////////////////////////////////
	// IDS_WRKLODERR: "Error loading work file"
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOWrkLod (m_tfWrkFil.GetFilOFS(), GetMasInf(), 
	  GetCBkPrc(), GetCBkArg(IDS_POLACTMAS))) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_WRKLODERR);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);
}

DWORD		CSesFil::GetSegOff ()
{
	return (0);
}

BOOL		CSesFil::GetStatus (CFileStatus &rStatus)
{
	return (CFile::GetStatus (GetFilOFS()->szPathName, rStatus));
}

OFSTRUCT_V*	CSesFil::GetFilOFS ()
{
	return (m_tfSnpFil.GetFilOFS()); 
}

DWORD		CSesFil::GetSmpCnt ()
{
	CFileStatus	fsFilSta;
	if (!GetStatus (fsFilSta)) return (0L);
	return (PCMByt2Sl (GetPCMTyp(), GetChnCnt(), fsFilSta.m_size, NULL)); 	 
}

BOOL 	CSesFil::Is_ModSet (BOOL bfSegReq)
{
	/////////////////////////////////////////////////////////////////////////
	// Return modification status for entire session or segment only
	/////////////////////////////////////////////////////////////////////////
	return ((!bfSegReq && m_tfWrkFil.Is_ModSet()) || m_tfSnpFil.Is_ModSet() || m_atAnoTxt.Is_ModSet()); 
}

/////////////////////////////////////////////////////////////////////////////
// High Level Transfer functions
/////////////////////////////////////////////////////////////////////////////
WORD		CSesFil::CopTo_Clp (DWORD *pulSmpOff, DWORD *pulSmpCnt, 
			CAudFil *pClpFil)
{
	/////////////////////////////////////////////////////////////////////////
	if (!pClpFil) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Round offset, cut & paste count to guarantee invert-able copy
	/////////////////////////////////////////////////////////////////////////
	*pulSmpOff = SmpSmpLow (*pulSmpOff);
	*pulSmpCnt = SmpSmpLow (*pulSmpCnt);
	if (!*pulSmpCnt || (NULL == pClpFil)) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Write to specified clipboard file
	// Note: IniFilFmt should probably be removed/modified in future versions
	//		 to permit integration of IniFilOFS into a single AudFilOpn call
	/////////////////////////////////////////////////////////////////////////
	if (pClpFil->Open (CFile::modeWrite | CFile::modeCreate)) {
		if (Open (CFile::modeRead)) {
			Seek (*pulSmpOff);
			pClpFil->IniFilFmt (this);
		  	Copy (pClpFil, *pulSmpCnt);		
			Close();
		}
		pClpFil->Close();
	}
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD		CSesFil::LogAndShf (DWORD *pulSmpOff, DWORD *pulCutSmp, 
			DWORD *pulPstSmp, CUndLst *pUndLst, BOOL bfSilPst)
{
	DWORD	ulOrgCnt = GetSmpCnt();

	/////////////////////////////////////////////////////////////////////////
	// Round offset, cut & paste count to guarantee correct & full shift
	/////////////////////////////////////////////////////////////////////////
	*pulSmpOff = SmpSmpLow (*pulSmpOff);
	*pulCutSmp = SmpSmpLow (*pulCutSmp);
	*pulPstSmp = SmpSmpLow (*pulPstSmp);
	if (!*pulCutSmp && !*pulPstSmp) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Convert samples to bytes
	/////////////////////////////////////////////////////////////////////////
	long	lBytOff = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), *pulSmpOff, NULL);
	long	lCutByt = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), *pulCutSmp, NULL);
	long	lPstByt = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), *pulPstSmp, NULL);
//	long	lSilByt = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Adjust offset, cut and paste byte counts for paste past end of file
	/////////////////////////////////////////////////////////////////////////
	if ((*pulSmpOff + *pulPstSmp) > ulOrgCnt) {
		long	lFilLen = PCMSmp2Bh (GetPCMTyp(), GetChnCnt(), ulOrgCnt, NULL);
		if (lBytOff  > lFilLen) {
//			lSilByt  = lBytOff - lFilLen;
//			lPstByt += lSilByt;
			lPstByt += (lBytOff - lFilLen);
			lBytOff  = lFilLen;
			lCutByt  = 0L;
		}
		else lCutByt = min (lCutByt, lFilLen - lBytOff);
	}

	/////////////////////////////////////////////////////////////////////////
	// Log undo data
	/////////////////////////////////////////////////////////////////////////
	if (pUndLst && pUndLst->LogUndEvt (GetFilOFS(), lBytOff, lCutByt, lPstByt, 
		GetCBkPrc(), GetCBkArg(IDS_POLACTLOG))) return (IDS_USRCANREQ);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (FIORETSUC != FIOOFSShf (GetFilOFS(), lBytOff + lCutByt, lPstByt - lCutByt, 
	  GetCBkPrc(), GetCBkArg(IDS_POLACTSHF))) {
		if (pUndLst) pUndLst->DelUndEvt ();
		return (IDS_SHFFILERR);
	}

	/////////////////////////////////////////////////////////////////////////
	// Silence paste area (if requested)
	/////////////////////////////////////////////////////////////////////////
	if (bfSilPst && *pulPstSmp) {
		if (!Open (CFile::modeWrite)) {
			// undo shift
			return (IDS_OPNFILERR);
		}
		Seek (*pulSmpOff);
		Erase (*pulPstSmp);
		Close ();
	}

	/////////////////////////////////////////////////////////////////////////
	// Extend silence for paste past end of file
	/////////////////////////////////////////////////////////////////////////
	if (*pulSmpOff > ulOrgCnt) {
		if (!Open (CFile::modeWrite)) {
			// undo shift
			return (IDS_OPNFILERR);
		}
		Seek (ulOrgCnt);
		Erase (*pulSmpOff - ulOrgCnt);
		Close ();
	}

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

/////////////////////////////////////////////////////////////////////////////
// High Level functions
/////////////////////////////////////////////////////////////////////////////
WORD	CSesFil::SesFilOpn (CString csFilNam, DWORD ulSegSel,
							FILFMT FAR *pusFilFmt, PCMTYP FAR *pusPCMTyp, 
							WORD FAR *pusChnCnt, DWORD FAR *pulSmpFrq, 
							CString csTmpDir, HWND hPolWnd, UINT nMsgPrm)
{
	WORD			usRetCod;

	/////////////////////////////////////////////////////////////////////////
	//	(0 == csFilNam.GetLength()) open new file
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = IniFilOFS (csFilNam, pusFilFmt, 
		pusPCMTyp, pusChnCnt, pulSmpFrq, csTmpDir, hPolWnd, nMsgPrm))
		return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Load work file segment(s) 
	// If "Jump To" request, pass index number
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = SesFilSegLod (ulSegSel ? SEGJMPQRY : SEGSELQRY, ulSegSel)) 
		return (usRetCod);

/////////////////////////////////////////////////////////////////////////
// Convert from MSADPCM until fully supported
// Mix multi-channel down to one until x-channel support available
/////////////////////////////////////////////////////////////////////////
if ((GetChnCnt() > 1) || (MSAPCM004 == GetPCMTyp())) {
	*pusPCMTyp = MPCPCM016;
	*pusChnCnt = 1;
}

	/////////////////////////////////////////////////////////////////////////
	// Indicate that files are unmodified; Clear the undo / redo list
	/////////////////////////////////////////////////////////////////////////
	m_tfWrkFil.ClrModFlg();
	m_pUndLst->ClrUndLst();

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

WORD	CSesFil::SesFilOpn (CSesFil *pSesSrc)
{
	/////////////////////////////////////////////////////////////////////////
	// Duplicate an existing session file
	/////////////////////////////////////////////////////////////////////////
	DWORD	ulSegSel = 0;
	FILFMT	usFilFmt = pSesSrc->GetFilFmt();
	PCMTYP	usPCMTyp = pSesSrc->GetPCMTyp();
	WORD 	usChnCnt = pSesSrc->GetChnCnt(); 
	DWORD 	ulSmpFrq = pSesSrc->GetSmpFrq();
	WORD 	usEncMsk = pSesSrc->GetEncMsk();

	return (SesFilOpn (pSesSrc->m_ofFilOFS.szPathName, ulSegSel, 
		&usFilFmt, &usPCMTyp, &usChnCnt, &ulSmpFrq, pSesSrc->GetTmpDir(),
		pSesSrc->GetFIOCBk()->m_hPolWnd, pSesSrc->GetFIOCBk()->m_nMsgPrm));

}

WORD	CSesFil::SesFilSegLod (SEGQRY usSegQry, DWORD ulSegSel)
{
	FIORET	frRetCod;	
	SEGINF  siCurSeg = *GetSegInf();

	/////////////////////////////////////////////////////////////////////////
	// If "Jump To" request, pre-select index number
	// Future: May want cleaner parameter passing interface
	/////////////////////////////////////////////////////////////////////////
	if (ulSegSel) siCurSeg.isIdxSeg.usIdxNum = (WORD) ulSegSel;

	/////////////////////////////////////////////////////////////////////////
	// Select pre-defined segment or query user
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOSegSel (usSegQry, GetMasInf(), &siCurSeg, GetSegInf())) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_SEGSELERR);

/////////////////////////////////////////////////////////////////////////
// Convert from MSADPCM until fully supported
// Mix multi-channel down to one until x-channel support available
/////////////////////////////////////////////////////////////////////////
if ((GetChnCnt() > 1) || (MSAPCM004 == GetPCMTyp())) {
	CAudFil	*pSrcFil = new CAudFil;
	WORD	usFilFmt = GetFilFmt();
	WORD	usPCMTyp = GetPCMTyp();
	WORD	usChnCnt = 1;
	DWORD	ulSmpFrq = GetSmpFrq();
	WORD	usEncMsk = GetEncMsk();
	WORD	usRetCod;
	
	/////////////////////////////////////////////////////////////////////////
	// Initialize audio file
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = AudFilOpn (&pSrcFil, m_ofFilOFS.szPathName, 0L, 
		&usFilFmt, &usPCMTyp, &usChnCnt, &ulSmpFrq, &usEncMsk, 
		(VISWNDHDL) (LPVOID) GetFIOCBk()->m_hPolWnd, 
		GetFIOCBk()->m_nMsgPrm)) return (usRetCod);

	/////////////////////////////////////////////////////////////////////
	ITCBLK	ibOutITC;
	DWORD	ulSmpTot = 0L;
	DWORD	ulSmpOff = 0L;
	DWORD	ulSmpCnt = pSrcFil->GetSmpCnt(); 
	CEffChn *pEffChn = new CEffChn (1);
	CEffInp	*pEffInp = new CEffInp (pSrcFil);

	/////////////////////////////////////////////////////////////////////////
	// Open source audio file and destination snippet file
	/////////////////////////////////////////////////////////////////////////
	if (!m_tfSnpFil.Open(CFile::modeCreate | CFile::modeWrite)) 
		return (IDS_OPNFILERR);
	if (!pEffInp->Open(CFile::modeRead, 0L, ulSmpCnt)) {
		m_tfSnpFil.Close();
		return (IDS_OPNFILERR);
	}
	
	/////////////////////////////////////////////////////////////////////
	// Set destination type as pure (MSAPCM004 de-compressed) audio
	/////////////////////////////////////////////////////////////////////
	usPCMTyp = (MSAPCM004 == usPCMTyp) ? MPCPCM016 : usPCMTyp;
	
	/////////////////////////////////////////////////////////////////////
	// Show/Hide Progress indicator for time consuming operations
	// Adjust sample total for channel converted output total
	/////////////////////////////////////////////////////////////////////
	GetFIOCBk()->BegCBkPrc (pEffChn->DstSizEst (ulSmpCnt, pSrcFil->GetChnCnt()), 
		IDS_POLACTSNP);
	
	/////////////////////////////////////////////////////////////////////
	while (TRUE) {
		DWORD	ulSmpOut;
		/////////////////////////////////////////////////////////////////
		// Read & de-compress file, apply channel effect
		/////////////////////////////////////////////////////////////////
		pEffInp->ExeEffPrc ();
		pEffChn->ExeEffPrc (pEffInp);
		/////////////////////////////////////////////////////////////////////////
		// Write de-compressed, single channel file
		/////////////////////////////////////////////////////////////////////////
		ulSmpTot += (ulSmpOut = PCMByt2Sl ((PCMTYP) usPCMTyp, GetChnCnt(),
			EffEBStoP (pEffChn->GetEBSBlk(), -1L, m_tfSnpFil.m_hFile, -1L, 
			(PCMTYP) usPCMTyp, usEncMsk, &ibOutITC, (EBSFWRPRC) PCMWr_PCM),
			&ibOutITC));
		/////////////////////////////////////////////////////////////////
		if (!ulSmpOut || (-1L == ulSmpOut)) break;
		if (!GetFIOCBk()->CntCBkPrc (ulSmpTot)) break;
	}
	GetFIOCBk()->EndCBkPrc (ulSmpTot);
	
	/////////////////////////////////////////////////////////////////////
	if (pEffChn) delete pEffChn;
	if (pEffInp) delete pEffInp;
	if (pSrcFil) delete pSrcFil;
	m_tfSnpFil.Close();
	
	/////////////////////////////////////////////////////////////////////
	// Reset PCM type and channel count to converted values
	/////////////////////////////////////////////////////////////////////
	GetMasInf()->usPCMTyp = (PCMTYP) usPCMTyp;
	GetMasInf()->usChnCnt = 1;

	/////////////////////////////////////////////////////////////////////
	GetMasInf()->ofLodUpd = *m_tfSnpFil.GetFilOFS();	

	/////////////////////////////////////////////////////////////////////
	if (usRetCod) return (IDS_SNPLODERR);
		
}
else {
	/////////////////////////////////////////////////////////////////////////
	// IDS_SNPLODERR: "Error loading snippet file"
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOSnpLod (m_tfSnpFil.GetFilOFS(), GetMasInf(), GetSegInf(), 
		GetCBkPrc(), GetCBkArg(IDS_POLACTSNP))) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_SNPLODERR);
}

	/////////////////////////////////////////////////////////////////////////
	// IDS_TXTLODERR: "Error loading annotation text"
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOTxtLod (m_atAnoTxt.GetAnoHdl(), GetMasInf(), GetSegInf(), 
		GetCBkPrc(), GetCBkArg(IDS_POLACTSNP))) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_TXTLODERR);

	/////////////////////////////////////////////////////////////////////////
	// Indicate that files are unmodified; Clear the undo / redo list
	/////////////////////////////////////////////////////////////////////////
	m_tfSnpFil.ClrModFlg();
	m_atAnoTxt.ClrModFlg();
	m_pUndLst->ClrUndLst();

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

WORD	CSesFil::SesFilSegCre ()
{
	SEGINF	siCreSeg;
	FIORET	frRetCod;	

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOSegSel (SEGCREQRY, GetMasInf(), GetSegInf(), &siCreSeg)) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_SEGSELERR);
	if (frRetCod = FIOSegCre (GetMasInf(), GetSegInf(), &siCreSeg)) 
		return ((FIORETERR == frRetCod) ? IDS_SEGCREWRN : IDS_SEGCREERR);

	/////////////////////////////////////////////////////////////////////////
	// Force work file "dirty"
	/////////////////////////////////////////////////////////////////////////
	m_tfWrkFil.SetModFlg();		

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

WORD	CSesFil::SesFilSegDel ()
{
	SEGINF	siDelSeg;
	FIORET	frRetCod;	

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (frRetCod = FIOSegSel (SEGDELQRY, GetMasInf(), GetSegInf(), &siDelSeg)) 
		return ((FIORETCAN == frRetCod) ? IDS_USRCANREQ : IDS_SEGSELERR);
	if (frRetCod = FIOSegDel (GetMasInf(), GetSegInf(), &siDelSeg)) 
		return ((FIORETERR == frRetCod) ? IDS_SEGDELWRN : IDS_SEGDELERR);

	/////////////////////////////////////////////////////////////////////
	// Force work file "dirty"
	/////////////////////////////////////////////////////////////////////
	m_tfWrkFil.SetModFlg();		

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

WORD	CSesFil::SesFilSegUpd ()
{
	/////////////////////////////////////////////////////////////////////////
	// Update work file segment(s) 
	/////////////////////////////////////////////////////////////////////////
	if (m_atAnoTxt.Is_ModSet() && FIOTxtUpd (*m_atAnoTxt.GetAnoHdl(), 
		GetMasInf(), GetSegInf(), GetCBkPrc(), GetCBkArg(IDS_POLACTSAV)))
		return (IDS_TXTWRTERR);
	if (m_tfSnpFil.Is_ModSet() && FIOSnpUpd (m_tfSnpFil.GetFilOFS(), 
		GetMasInf(), GetSegInf(), GetCBkPrc(), GetCBkArg(IDS_POLACTSAV)))
		return (IDS_SNPWRTERR);

	/////////////////////////////////////////////////////////////////////////
	// Indicate that files are unmodified.
	/////////////////////////////////////////////////////////////////////////
	m_tfSnpFil.ClrModFlg();
	m_atAnoTxt.ClrModFlg();

	/////////////////////////////////////////////////////////////////////////
	return (0);
}

WORD	CSesFil::SesFilSav ()
{
	WORD			usRetCod;

	/////////////////////////////////////////////////////////////////////////
	// Update Work File segment components	
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = SesFilSegUpd ()) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Update Work File
	/////////////////////////////////////////////////////////////////////////
	if (FIOWrkUpd (m_tfWrkFil.GetFilOFS(), GetMasInf(), GetCBkPrc(), 
		GetCBkArg(IDS_POLACTSAV))) return (IDS_WRKWRTERR);

	/////////////////////////////////////////////////////////////////////////
	// Update Master File
	/////////////////////////////////////////////////////////////////////////
	if (FIOMasUpd (CAudFil::GetFilOFS(), GetMasInf(), GetCBkPrc(), 
		GetCBkArg(IDS_POLACTSAV))) return (IDS_WRKWRTERR);

	/////////////////////////////////////////////////////////////////////////
	// Indicate that files are unmodified.
	/////////////////////////////////////////////////////////////////////////
	m_tfWrkFil.ClrModFlg();

	/////////////////////////////////////////////////////////////////////////
	return (0);
}


