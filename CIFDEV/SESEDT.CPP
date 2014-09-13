/////////////////////////////////////////////////////////////////////////////
// SesEdt.cpp : Implementation of the CSesEdt classes
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "sesedt.h"						// Audio session edit support defs
#include "audeff.h"						// Audio effects support defs
#include "ampdsp.h"						// Amplitude display window

extern "C"
{
	#include "os_dev\winmsg.h"			// User message support
	#include "regdev\vfereg.h"			// User Registration defs
}

/////////////////////////////////////////////////////////////////////////////
//						External References
/////////////////////////////////////////////////////////////////////////////
extern  CIFGLO  CIFGlo;					// C Interface Library Globals

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const char	BAKFILEXT[] = ".BK1";		// Backup file extension		

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void	CSesSta::UndStaSav (CSesEdt *pSesEdt)
{
	m_bfModFlg = FALSE;
	m_ulDocOff = 0L;
	m_ulAtPOff = 0L;
	m_ulSelOff = 0L;
	m_ulSelLen = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Save current amplitude display view and selection
	/////////////////////////////////////////////////////////////////////////
	for (CAmpDsp *pAmpDsp = pSesEdt->AmpDspEnu(); pAmpDsp; pAmpDsp = pSesEdt->AmpDspEnu(pAmpDsp)) {
		pAmpDsp->SelGetEvt(&m_ulSelOff, &m_ulSelLen);
	}
}

void	CSesSta::UndStaRes (CSesEdt *pSesEdt)
{
	DWORD	ulSelOff = 0L;
	DWORD	ulSelLen = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Restore current amplitude display view and selection
	/////////////////////////////////////////////////////////////////////////
	for (CAmpDsp *pAmpDsp = pSesEdt->AmpDspEnu(); pAmpDsp; pAmpDsp = pSesEdt->AmpDspEnu(pAmpDsp)) {
		pAmpDsp->DspArrUpd ();
		pAmpDsp->SelGetEvt(&ulSelOff, &ulSelLen);
		pAmpDsp->SelSetEvt(m_ulSelOff, m_ulSelLen);
		m_ulSelOff = ulSelOff;
		m_ulSelLen = ulSelLen;
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
WORD	CSesEdt::MasUpdBeg (CString csDstNam)
{
	int			iExtDot;
	CString		csBakNam;

	/////////////////////////////////////////////////////////////////////////
	memset (&m_ofBakOFS, 0, sizeof (m_ofBakOFS));

	/////////////////////////////////////////////////////////////////////////
	// Save original master file name.
	// Check for valid new file name; update OFS.
	// "Save as" different name or Null original file inhibits backup.
	/////////////////////////////////////////////////////////////////////////
	csBakNam = CAudFil::GetFilOFS()->szPathName;
// 09/29/97: Long File Name support
// OF_PARSE checks for valid file name. This file name should
// always be valid since it was created from a valid source file name.
	if (HFILE_ERROR == FIOOFSOpn (csDstNam, CAudFil::GetFilOFS(), OF_PARSE)) {
		strncpy (CAudFil::GetFilOFS()->szPathName, csBakNam, sizeof (CAudFil::GetFilOFS()->szPathName));
		return (IDS_MASBAKERR);
	}
	if (csBakNam.CompareNoCase (CAudFil::GetFilOFS()->szPathName)) return (0);
	if (csBakNam.IsEmpty()) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Generate backup file name
	// Increment extension if original name is same as backup name
	/////////////////////////////////////////////////////////////////////////
	if (-1 == (iExtDot = csBakNam.ReverseFind ('.'))) csBakNam += BAKFILEXT;
	else csBakNam = csBakNam.Left(iExtDot) + BAKFILEXT;
	if (!csBakNam.CompareNoCase (CAudFil::GetFilOFS()->szPathName))	{
		int		LTAMAXLEN = 101;		// itoa/ltoa max string length
		int		BAKEXTBAS =  10;
		CString	csLstDig;
		itoa (atoi (csBakNam.Right(1)) + 1, csLstDig.GetBuffer (LTAMAXLEN), BAKEXTBAS);
		csLstDig.ReleaseBuffer();
		csBakNam = csBakNam.Left(csBakNam.GetLength() - 1) + csLstDig;
	}

	/////////////////////////////////////////////////////////////////////////
	// remove (don't care if not there)
	/////////////////////////////////////////////////////////////////////////
	MasBakRem (csBakNam);

	/////////////////////////////////////////////////////////////////////////
	TRY 
	{
		/////////////////////////////////////////////////////////////////////
		// Note: Rename only occurs if csBakNam == original master file name
		// Future: Rename should probably check OF_EXIST on old name first
		// in cases where a user rename has caused original name to change
		/////////////////////////////////////////////////////////////////////
// 09/29/97: Long File Name support
//ajm
//		CFile::Rename (CAudFil::GetFilOFS()->szPathName, csBakNam);
		if (FIORETSUC != FIOOFSRen (CAudFil::GetFilOFS(), csBakNam, 0)) 
			AfxThrowFileException (CFileException::badPath, -1);
	}

	/////////////////////////////////////////////////////////////////////////
	// IDS_MASBAKERR: "Error backing up master file."
	// Future: could get more sophisticated, try another backup file name
	/////////////////////////////////////////////////////////////////////////
	CATCH (CFileException, e)
	{
		return (IDS_MASBAKERR);
	}
	END_CATCH

	/////////////////////////////////////////////////////////////////////////
	// Re-open backup file to reset OFS
	/////////////////////////////////////////////////////////////////////////
	if (HFILE_ERROR == FIOOFSOpn (csBakNam, &m_ofBakOFS, OF_EXIST)) return (IDS_MASBAKERR);

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CSesEdt::MasUpdAbt ()
{
	/////////////////////////////////////////////////////////////////////////
	// Restore from backup file (if there is anything to back up)
	/////////////////////////////////////////////////////////////////////////
	if (!strlen (m_ofBakOFS.szPathName)) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Delete current file
	/////////////////////////////////////////////////////////////////////////
	MasBakRem (CAudFil::GetFilOFS()->szPathName);

	/////////////////////////////////////////////////////////////////////////
	TRY 
	{
// 09/29/97: Long File Name support
//ajm
//		CFile::Rename (m_ofBakOFS.szPathName, CAudFil::GetFilOFS()->szPathName);
		if (FIORETSUC != FIOOFSRen (&m_ofBakOFS, CAudFil::GetFilOFS()->szPathName, 0)) 
			AfxThrowFileException (CFileException::fileNotFound, -1);
	}

	/////////////////////////////////////////////////////////////////////////
	// IDS_MASRESERR: "Error restoring master backup file."
	/////////////////////////////////////////////////////////////////////////
	CATCH (CFileException, e)
	{
		return (IDS_MASRESERR);
	}
	END_CATCH

	/////////////////////////////////////////////////////////////////////////
	// Re-open master file to reset OFS
	/////////////////////////////////////////////////////////////////////////
	if (HFILE_ERROR == FIOOFSOpn (NULL, CAudFil::GetFilOFS(), OF_EXIST | OF_REOPEN))
		return (IDS_MASRESERR);

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CSesEdt::MasUpdEnd (BOOL bfAutBak)
{
	/////////////////////////////////////////////////////////////////////////
	// Restore from backup file (if there is anything to back up)
	/////////////////////////////////////////////////////////////////////////
	if (!strlen (m_ofBakOFS.szPathName)) return (0);

	/////////////////////////////////////////////////////////////////////////
	if (!bfAutBak) MasBakRem (m_ofBakOFS.szPathName);

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CSesEdt::MasBakRem (CString csFilNam)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (csFilNam.IsEmpty()) return (0);
	TRY 
	{
// 09/29/97: Long File Name support
//		CFile::Remove (csFilNam);
		if (FIORETSUC != FIOOFSDel (csFilNam, 0)) 
			AfxThrowFileException (CFileException::accessDenied, -1);
	}
	CATCH (CFileException, e)
	{
		return (e->m_cause);
	}
	END_CATCH

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

WORD	CSesEdt::WrkDspUpd (DWORD ulShfPnt, long lShfAmt, BOOL bfResFlg)
{
	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed
	/////////////////////////////////////////////////////////////////////////
	for (CAmpDsp *pAmpDsp = AmpDspEnu(); pAmpDsp; pAmpDsp = AmpDspEnu(pAmpDsp)) {
		pAmpDsp->DspArrUpd ();
		if (!bfResFlg) pAmpDsp->SelShfEvt (ulShfPnt, lShfAmt);
		else pAmpDsp->SelSetEvt (ulShfPnt, lShfAmt);
	}
	return (0);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
WORD	CSesEdt::AudFilEff (DWORD *pulSmpOff, DWORD *pulSmpCnt, CAudEff *pAudEff, 
		const char *pszDesStr) 
{
	CEffInp	*	pEffInp = new CEffInp (this);
	DWORD		ulSmpTot = 0L;
	DWORD		ulSrcPos;
	DWORD		ulDstPos;
	WORD		usRetCod;

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo log if requested
	/////////////////////////////////////////////////////////////////////////
	if (NULL != pszDesStr) GetUndLst()->CreUndEvt (pszDesStr, new CSesSta(this));

	/////////////////////////////////////////////////////////////////////////
	// Insure that sample count is no larger than available
    // Note: Mono to n channels requires inserting silence, convert in place
	/////////////////////////////////////////////////////////////////////////
	*pulSmpOff = min (*pulSmpOff, GetSmpCnt());
	*pulSmpCnt = min (*pulSmpCnt, GetSmpCnt() - *pulSmpOff);

	/////////////////////////////////////////////////////////////////////////
    // Log any cut area; shift to add/remove space; silence extend
	// Note: CAudFil file access functions round offset, cut & paste count 
	// down to destination format to guarantee correct & full write
	/////////////////////////////////////////////////////////////////////////
	usRetCod = LogAndShf (pulSmpOff, pulSmpCnt, pulSmpCnt, GetUndLst());

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!pEffInp->Open (CFile::modeReadWrite, *pulSmpOff, *pulSmpCnt)) 
		return (IDS_OPNFILERR);
	ulSrcPos = ulDstPos = CFile::GetPosition();

	/////////////////////////////////////////////////////////////////////
	// Show/Hide Progress indicator for time consuming operations
	/////////////////////////////////////////////////////////////////////
	GetFIOCBk()->BegCBkPrc (*pulSmpCnt, IDS_POLACTCVT);
	while (TRUE) {
		DWORD	ulSmpOut;
		/////////////////////////////////////////////////////////////////
		// Position file for source sample read
		/////////////////////////////////////////////////////////////////
		CFile::Seek (ulSrcPos, CFile::begin);
		pEffInp->ExeEffPrc ();
		ulSrcPos = CFile::GetPosition();

		/////////////////////////////////////////////////////////////////
		// Apply effect to sample range
		/////////////////////////////////////////////////////////////////
		pAudEff->ExeEffPrc (pEffInp);

		/////////////////////////////////////////////////////////////////
		// Position file for effects output sample write
		/////////////////////////////////////////////////////////////////
		CFile::Seek (ulDstPos, CFile::begin);
		ulSmpTot += (ulSmpOut = Write (pAudEff));
		ulDstPos = CFile::GetPosition();

		/////////////////////////////////////////////////////////////////
		if (!ulSmpOut || (-1L == ulSmpOut)) break;
		if (!GetFIOCBk()->CntCBkPrc (ulSmpTot)) break;
	}
	GetFIOCBk()->EndCBkPrc (ulSmpTot);

	/////////////////////////////////////////////////////////////////////
	// Shorten file length if effect reduced the sample count
	/////////////////////////////////////////////////////////////////////
	if (ulSmpTot < *pulSmpCnt) {
		DWORD	ulCutOff = *pulSmpOff + ulSmpTot;	
		DWORD	ulCutLen = *pulSmpCnt - ulSmpTot;	
		DWORD	ulPstLen = 0;
		usRetCod = LogAndShf (&ulCutOff, &ulCutLen, &ulPstLen);
	}

	/////////////////////////////////////////////////////////////////////////
	// Close source and destination
	/////////////////////////////////////////////////////////////////////////
	pEffInp->Close ();
	Close ();

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	delete pEffInp;

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
WORD	CSesEdt::AudFilRep (DWORD *pulSmpOff, DWORD *pulCutSmp, BOOL bfSizAdj,
		WORD usAAFAlg, WORD usResAlg, CAudFil *pSrcFil, DWORD *pulPstOff, 
		DWORD *pulPstSmp, BOOL bfRawInh, const char *pszDesStr) 
{
	DWORD		ulSmpTot = 0L;

	/////////////////////////////////////////////////////////////////////////
	// Replace sections of current session file with pSrcFil
	/////////////////////////////////////////////////////////////////////////
	CEffInp	*	pEffInp = new CEffInp (pSrcFil);
	CEffChn	*	pEffChn = new CEffChn (GetChnCnt());
	CEffAAF	*	pEffAAF = new CEffAAF (GetSmpFrq() / 2L, pSrcFil->GetSmpFrq(), (CEffAAF::AAFALG) usAAFAlg);
	CEffRes	*	pEffRes = new CEffRes (pSrcFil->GetSmpFrq(), GetSmpFrq(), (CEffRes::RESALG) usResAlg);
	CEffAtD	*	pEffAtD = new CEffAtD (GetPCMTyp());

	/////////////////////////////////////////////////////////////////////////
	// Insure that past count is no larger than available
	/////////////////////////////////////////////////////////////////////////
	*pulPstOff = min (*pulPstOff, pSrcFil->GetSmpCnt());
	*pulPstSmp = min (*pulPstSmp, pSrcFil->GetSmpCnt() - *pulPstOff);

	/////////////////////////////////////////////////////////////////////////
	// Adjust paste replacement size for resample and channel conversion
	// Note: Paste offset and count initially refer to pSrcFil freq & channel
	/////////////////////////////////////////////////////////////////////////
	*pulPstSmp = pEffChn->DstSizEst (*pulPstSmp, pSrcFil->GetChnCnt());
	*pulPstSmp = pEffRes->DstSizEst (*pulPstSmp, pSrcFil->GetSmpFrq());

	/////////////////////////////////////////////////////////////////////////
	// If ( ulCutSmp &&  bfSizAdj), replace audio @ulSmpOff, len ulCutSmp 
	// If ( ulCutSmp && !bfSizAdj), overlay audio @ulSmpOff,  <= ulCutSmp 
	// If (!ulCutSmp &&  bfSizAdj), insert  audio @ulSmpOff
	// If (!ulCutSmp && !bfSizAdj), do nothing
	/////////////////////////////////////////////////////////////////////////
	if ( *pulCutSmp && !bfSizAdj) *pulPstSmp = *pulCutSmp = min (*pulPstSmp, *pulCutSmp);
	if (!*pulCutSmp && !bfSizAdj) return (0);

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo log if requested
	/////////////////////////////////////////////////////////////////////////
	if (NULL != pszDesStr) GetUndLst()->CreUndEvt (pszDesStr, new CSesSta(this));

	/////////////////////////////////////////////////////////////////////////
    // Log any cut area; shift to add/remove space; silence extend
	// Note: CAudFil file access functions round offset, cut & paste count 
	// down to destination format to guarantee correct & full write
	/////////////////////////////////////////////////////////////////////////
	if (LogAndShf (pulSmpOff, pulCutSmp, pulPstSmp, GetUndLst()))
		return (IDS_SHFFILERR);	

	/////////////////////////////////////////////////////////////////////////
	// Re-compute paste replacement source size based upon destination limits
	// Open file and seek to offset
	/////////////////////////////////////////////////////////////////////////
	if (!pEffInp->Open (CFile::modeRead, *pulPstOff, 
		pEffRes->SrcSizEst(pEffChn->SrcSizEst(*pulPstSmp, pSrcFil->GetChnCnt()),
		pSrcFil->GetSmpFrq()))) return (IDS_OPNFILERR);
	if (!Open (CFile::modeWrite)) {
		pEffInp->Close ();
		return (IDS_OPNFILERR);
	}
	Seek (*pulSmpOff);

	/////////////////////////////////////////////////////////////////////////
	// Perform simple transparent file read if raw mode requested
	// Note: Caller can inhibit raw mode for ADPCM file seek guard operations
	/////////////////////////////////////////////////////////////////////////
	if (!bfRawInh && Is_FmtCmp (pSrcFil, usResAlg ? 0 : FLT_MAX))
		ulSmpTot = pSrcFil->Copy (this, pEffInp->GetSmpTot(), GetFIOCBk());
	else {
		/////////////////////////////////////////////////////////////////////
		// Show/Hide Progress indicator for time consuming operations
		/////////////////////////////////////////////////////////////////////
		GetFIOCBk()->BegCBkPrc (*pulPstSmp, IDS_POLACTCVT);
		while (TRUE) {
			DWORD	ulSmpOut;
			/////////////////////////////////////////////////////////////////
			// Convert Mode: Convert from one PCM format to another
			/////////////////////////////////////////////////////////////////
			pEffInp->ExeEffPrc ();
			pEffChn->ExeEffPrc (pEffInp);
			pEffAAF->ExeEffPrc (pEffChn);
			pEffRes->ExeEffPrc (pEffAAF);
			pEffAtD->ExeEffPrc (pEffRes);
			ulSmpTot += (ulSmpOut = Write (pEffAtD));
			if (!ulSmpOut || (-1L == ulSmpOut)) break;

			/////////////////////////////////////////////////////////////////
			if (!GetFIOCBk()->CntCBkPrc (ulSmpTot)) break;
		}
		GetFIOCBk()->EndCBkPrc (ulSmpTot);
	}

	/////////////////////////////////////////////////////////////////////
	// Shorten file length if conversion reduced the sample count
	/////////////////////////////////////////////////////////////////////
	if (ulSmpTot < *pulPstSmp) {
		DWORD	ulCutOff = *pulSmpOff + ulSmpTot;	
		DWORD	ulCutLen = *pulPstSmp - ulSmpTot;	
		DWORD	ulPstLen = 0;
		LogAndShf (&ulCutOff, &ulCutLen, &ulPstLen);
	}

	/////////////////////////////////////////////////////////////////////////
	// Close source and destination
	/////////////////////////////////////////////////////////////////////////
	pEffInp->Close ();
	Close ();

	/////////////////////////////////////////////////////////////////////////
	delete pEffAtD;
	delete pEffRes;
	delete pEffAAF;
	delete pEffChn;
	delete pEffInp;

	/////////////////////////////////////////////////////////////////////////
	return (0);

}

/////////////////////////////////////////////////////////////////////////////
// Public C interface
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export	SesEdtOpn (CSesEdt FAR * FAR *ppSesEdt, 
						const char FAR *pszFilNam, DWORD ulSegSel, 
						WORD FAR *pusFilFmt, WORD FAR *pusPCMTyp, 
						WORD FAR *pusChnCnt, DWORD FAR *pulSmpFrq, 
						WORD FAR *pusEncMsk, const char* pszTmpDir, 
						VISWNDHDL hPolWnd, DWORD ulPolArg)
{
	WORD			usRetCod;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	*ppSesEdt = new CSesEdt;

	/////////////////////////////////////////////////////////////////////////
	// (0 == csFilNam.GetLength()) open new file
	/////////////////////////////////////////////////////////////////////////
	if (!(usRetCod = (*ppSesEdt)->SesFilOpn (pszFilNam, ulSegSel, 
		(FILFMT FAR *) pusFilFmt, (PCMTYP FAR *) pusPCMTyp, pusChnCnt, 
		pulSmpFrq, pszTmpDir, (HWND) hPolWnd, (UINT) ulPolArg))) {
		/////////////////////////////////////////////////////////////////////
		// Query for demo new/open limit
		// Check after the fact to make reverse engineering more difficult
		/////////////////////////////////////////////////////////////////////
		if (REGDEMKEY == CIFGlo.usRegKey) {
			static WORD	m_usOpnCnt = DEMOPNCNT;
			if (!m_usOpnCnt) usRetCod = IDS_DEMLIMERR;
			else CIFGlo.usDemLim = --m_usOpnCnt;
		}
	}

	/////////////////////////////////////////////////////////////////////////
	// Clean up and return
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod) {
		delete *ppSesEdt;
		*ppSesEdt = NULL;
	}
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export	SesEdtRev (CSesEdt FAR * FAR *ppSesEdt) 
{
	WORD	usRetCod;
	CSesEdt	*pSesNew;

	/////////////////////////////////////////////////////////////////////////
	// Check for existing session edit file, create a fresh one
	/////////////////////////////////////////////////////////////////////////
	if (NULL == (*ppSesEdt)) return (-1L);
	if (NULL == (pSesNew = new CSesEdt)) return (-1L);

	/////////////////////////////////////////////////////////////////////////
	// (0 == csFilNam.GetLength()) open new file
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesNew->SesFilOpn (*ppSesEdt);

	/////////////////////////////////////////////////////////////////////////
	// Close current session edit file, swap new one into place
	/////////////////////////////////////////////////////////////////////////
	if (!usRetCod) {
		delete *ppSesEdt;
		*ppSesEdt = pSesNew;
	}
	else delete pSesNew;

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export SesEdtDes (CSesEdt FAR *pSesEdt, LPSTR szDesStr, 
						WORD usMaxLen, WORD usRsv001)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1L);

	return (FIOSegDes (SEGNUMQRY, pSesEdt->GetMasInf(), pSesEdt->GetSegInf(), 
		szDesStr, usMaxLen));
}

extern "C"
WORD FAR PASCAL _export SesEdtMod (CSesEdt FAR *pSesEdt, WORD bfSegReq)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (FALSE);
	return (pSesEdt->Is_ModSet(bfSegReq));
}

extern "C"
DWORD FAR PASCAL _export SesEdtFil (CSesEdt FAR *pSesEdt)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (NULL);
	return ((DWORD) ((CAudFil FAR *) pSesEdt));
}

extern "C"
WORD FAR PASCAL _export SesEdtSav (CSesEdt FAR *pSesEdt, LPCSTR pszFilNam, 
						WORD bfAutBak)
{
	WORD	usRetCod;
	CString	csDstNam;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	csDstNam = (!pszFilNam || !strlen (pszFilNam)) 
		? pSesEdt->CAudFil::GetFilOFS()->szPathName : pszFilNam;
	if (csDstNam.IsEmpty()) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Create backup and copy work to master
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = pSesEdt->MasUpdBeg (csDstNam)) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (usRetCod = pSesEdt->SesFilSav ()) {
		if (pSesEdt->MasUpdAbt()) MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MASRESERR);
		return (usRetCod);
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->MasUpdEnd (bfAutBak);
	return (0);

}

extern "C"
WORD FAR PASCAL _export SesEdtCls (CSesEdt FAR * FAR *ppSesEdt)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == *ppSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	delete *ppSesEdt;
	*ppSesEdt = NULL;
	return (0);

}

/////////////////////////////////////////////////////////////////////////////
// Cut / Paste Editing operations
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEdtCut (CSesEdt FAR *pSesEdt, CAudFil FAR *pClpFil,
						DWORD ulSmpOff, DWORD ulSmpCnt, const char *pszDesStr)
{
	WORD	usRetCod;
	DWORD	ulPstSmp = 0L;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// CopTo_Clp may round down sample counts
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->CopTo_Clp (&ulSmpOff, &ulSmpCnt, pClpFil);

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo log if requested
	/////////////////////////////////////////////////////////////////////////
	if (NULL != pszDesStr) pSesEdt->GetUndLst()->CreUndEvt (pszDesStr, new CSesSta(pSesEdt));

	/////////////////////////////////////////////////////////////////////////
    // Log any cut area; shift to add/remove space; silence extend
	// Note: CAudFil file access functions round offset, cut & paste count 
	// down to destination format to guarantee correct & full write
	/////////////////////////////////////////////////////////////////////////
	ulSmpCnt = min (ulSmpCnt, pSesEdt->GetSmpCnt());
	usRetCod = pSesEdt->LogAndShf (&ulSmpOff, &ulSmpCnt, &ulPstSmp, pSesEdt->GetUndLst());

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed (reset)
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (0L, 0L, TRUE);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtCrp (CSesEdt FAR *pSesEdt, DWORD ulSmpOff, 
						DWORD ulCrpOff, DWORD ulCrpCnt, DWORD ulSmpCnt, 
						const char *pszDesStr)
{
	WORD	usRetCod;
	DWORD	ulFilSmp;
	DWORD	ulLftOff;
	DWORD	ulLftSmp;
	DWORD	ulRgtOff;
	DWORD	ulRgtSmp;
	DWORD	ulPstSmp = 0L;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo log if requested
	/////////////////////////////////////////////////////////////////////////
	if (NULL != pszDesStr) pSesEdt->GetUndLst()->CreUndEvt (pszDesStr, new CSesSta(pSesEdt));

	/////////////////////////////////////////////////////////////////////////
	// Insure that ulSmpOff <= ulCrpOff <= ulFilSmp
	/////////////////////////////////////////////////////////////////////////
	ulFilSmp = pSesEdt->GetSmpCnt();
	ulSmpOff = min (ulSmpOff, ulFilSmp);
	ulSmpCnt = min (ulSmpCnt, ulFilSmp - ulSmpOff);
	ulCrpOff = max (ulSmpOff, min (ulCrpOff, (ulSmpOff + ulSmpCnt)));
	ulCrpCnt = min (ulCrpCnt, (ulSmpOff + ulSmpCnt) - ulCrpOff);

	/////////////////////////////////////////////////////////////////////////
    // Log any cut area; shift to remove space
	// Note: CAudFil file access functions round offset, cut & paste count 
	// down to destination format to guarantee correct & full write
	/////////////////////////////////////////////////////////////////////////
	ulRgtOff = ulCrpOff + ulCrpCnt;
	ulRgtSmp = (ulSmpOff + ulSmpCnt) - ulRgtOff;
	usRetCod = pSesEdt->LogAndShf (&ulRgtOff, &ulRgtSmp, &ulPstSmp, pSesEdt->GetUndLst());

	ulLftOff = ulSmpOff;
	ulLftSmp = ulCrpOff - ulSmpOff;
	usRetCod = pSesEdt->LogAndShf (&ulLftOff, &ulLftSmp, &ulPstSmp, pSesEdt->GetUndLst());

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed
	/////////////////////////////////////////////////////////////////////////
	if (ulRgtSmp) pSesEdt->WrkDspUpd (ulRgtOff + ulRgtSmp, - (long) ulRgtSmp);
	if (ulLftSmp) pSesEdt->WrkDspUpd (ulLftOff + ulLftSmp, - (long) ulLftSmp);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtCop (CSesEdt FAR *pSesEdt, CAudFil FAR *pClpFil,
						DWORD ulSmpOff, DWORD ulSmpCnt, const char *pszJnkVar)
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Write to specified clipboard file
	/////////////////////////////////////////////////////////////////////////
	return (pSesEdt->CopTo_Clp (&ulSmpOff, &ulSmpCnt, pClpFil));
}

extern "C"
WORD FAR PASCAL _export SesEdtPst (CSesEdt FAR *pSesEdt, CAudFil FAR *pSrcFil,
						DWORD ulSmpOff, DWORD ulCutSmp, DWORD ulPstOff, 
						DWORD ulPstSmp,	WORD usAAFAlg, WORD usResAlg, 
						WORD bfRawInh, const char *pszDesStr) 
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// If 0 == ulCutSmp, insert  audio at position ulSmpOff
	// If 0 != ulCutSmp, overlay audio at position ulSmpOff, length ulCutSmp 
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->AudFilRep (&ulSmpOff, &ulCutSmp, TRUE, usAAFAlg, 
		usResAlg, pSrcFil, &ulPstOff, &ulPstSmp, bfRawInh, pszDesStr);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (ulSmpOff + ulCutSmp, ulPstSmp - ulCutSmp);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtEra (CSesEdt FAR *pSesEdt, CAudFil FAR *pRsv001,
						DWORD ulSmpOff, DWORD ulOrgCnt, DWORD ulNewCnt, const char *pszDesStr)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Initialize undo log if requested
	/////////////////////////////////////////////////////////////////////////
	if (NULL != pszDesStr) pSesEdt->GetUndLst()->CreUndEvt (pszDesStr, new CSesSta(pSesEdt));

	/////////////////////////////////////////////////////////////////////////
    // Log any cut area; shift to add/remove space; silence extend
	// Note: CAudFil file access functions round offset, cut & paste count 
	// down to destination format to guarantee correct & full write
	/////////////////////////////////////////////////////////////////////////
	usRetCod = pSesEdt->LogAndShf (&ulSmpOff, &ulOrgCnt, &ulNewCnt, 
		pSesEdt->GetUndLst(), TRUE);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (0L, 0L);
	return (usRetCod);

}

/////////////////////////////////////////////////////////////////////////////
// Working Demo support
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEdtDemLim (DWORD ulRsv001, DWORD ulRsv002)
{
	/////////////////////////////////////////////////////////////////////////
	return (CIFGlo.usDemLim);
}

/////////////////////////////////////////////////////////////////////////////
// Undo/Redo
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEdtUndMax (CSesEdt FAR *pSesEdt, WORD usUndMax)
{
	/////////////////////////////////////////////////////////////////////////
	// Set Undo maximum count
	/////////////////////////////////////////////////////////////////////////
	if (pSesEdt) return (pSesEdt->GetUndLst()->SetUndMax (usUndMax));
	return (-1);
}

extern "C"
WORD FAR PASCAL _export SesEdtUndDes (CSesEdt FAR *pSesEdt, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	if (pSesEdt && pSesEdt->GetUndLst()->GetUndDes (&csWrkStr)) {
		strncpy (szDesStr, csWrkStr, usMaxLen);
		return (TRUE);
	}

	/////////////////////////////////////////////////////////////////////////
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export SesEdtUndPrv (CSesEdt FAR *pSesEdt)
{
	CSesSta	*pSesSta;
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Rerieve undo description and display state; undo file operation
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->GetUndLst()->GetUndDes (NULL, (const CUndSta **) &pSesSta); 
	usRetCod = pSesEdt->GetUndLst()->Un_UndEvt (pSesEdt->GetFilOFS(), 
		pSesEdt->GetCBkPrc(), (DWORD) pSesEdt->GetCBkArg(IDS_POLACTUND));

	/////////////////////////////////////////////////////////////////////////
	// Restore current amplitude display view and selection
	/////////////////////////////////////////////////////////////////////////
	if (pSesSta) pSesSta->UndStaRes (pSesEdt);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtRedDes (CSesEdt FAR *pSesEdt, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	if (pSesEdt && pSesEdt->GetUndLst()->GetRedDes (&csWrkStr)) {
		strncpy (szDesStr, csWrkStr, usMaxLen);
		return (TRUE);
	}

	/////////////////////////////////////////////////////////////////////////
	return (FALSE);
}

extern "C"
WORD FAR PASCAL _export SesEdtRedNxt (CSesEdt FAR *pSesEdt)
{
	CSesSta	*pSesSta;
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Rerieve redo description and display state; redo file operation
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->GetUndLst()->GetRedDes (NULL, (const CUndSta **) &pSesSta); 
	usRetCod = pSesEdt->GetUndLst()->Re_UndEvt (pSesEdt->GetFilOFS(), 
		pSesEdt->GetCBkPrc(), (DWORD) pSesEdt->GetCBkArg(IDS_POLACTUND));

	/////////////////////////////////////////////////////////////////////////
	// Restore current amplitude display view and selection
	/////////////////////////////////////////////////////////////////////////
	if (pSesSta) pSesSta->UndStaRes (pSesEdt);

	/////////////////////////////////////////////////////////////////////////
	return (usRetCod);
}

/////////////////////////////////////////////////////////////////////////////
// Segmented file support
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export SesEdtSegSel (CSesEdt FAR *pSesEdt, WORD usSegQry)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);

	/////////////////////////////////////////////////////////////////////////
	// Query for demo segment limit	if not revert request
	/////////////////////////////////////////////////////////////////////////
	if (usSegQry && (REGDEMKEY == CIFGlo.usRegKey)) {
		static WORD	m_usSegCnt = DEMSEGCNT;
		if (!m_usSegCnt) return (IDS_DEMLIMERR);
		else m_usSegCnt--;
	}

	/////////////////////////////////////////////////////////////////////////
	// Update current segment if not "NUL" (revert) request; load new segment
	/////////////////////////////////////////////////////////////////////////
	if (usSegQry && (usRetCod = pSesEdt->SesFilSegUpd ())) return (usRetCod);
	if (usRetCod = pSesEdt->SesFilSegLod((SEGQRY) usSegQry)) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that view and selection have changed (reset)
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (0L, 0L, TRUE);
	return (usRetCod);

}

extern "C"
WORD FAR PASCAL _export SesEdtSegCre (CSesEdt FAR *pSesEdt)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);
	if (usRetCod = pSesEdt->SesFilSegCre()) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that index may have changed
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (0L, 0L);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtSegDel (CSesEdt FAR *pSesEdt)
{
	WORD	usRetCod;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);
	if (usRetCod = pSesEdt->SesFilSegDel()) return (usRetCod);

	/////////////////////////////////////////////////////////////////////////
	// Notify amplitude display that index may have changed
	/////////////////////////////////////////////////////////////////////////
	pSesEdt->WrkDspUpd (0L, 0L);
	return (usRetCod);
}

extern "C"
WORD FAR PASCAL _export SesEdtSegTxtGet (CSesEdt FAR *pSesEdt, LPSTR szTxtBuf, WORD usMaxLen)
{

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);
	CString csWrkStr = pSesEdt->GetAnoTxt ();
	strncpy (szTxtBuf, csWrkStr, usMaxLen);
	return (0);
}

extern "C"
WORD FAR PASCAL _export SesEdtSegTxtSet (CSesEdt FAR *pSesEdt, LPSTR szTxtBuf)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pSesEdt) return (-1);
	return (pSesEdt->SetAnoTxt (szTxtBuf));
}




