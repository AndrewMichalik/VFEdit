/////////////////////////////////////////////////////////////////////////////
// AmpDsp.cpp : Implementation of the CAmpDsp class
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "audfil.h"						// Audio file support defs
#include "ampchd.h"						// Amplitude display child windows
#include "ampdsp.h"						// Amplitude display window

/////////////////////////////////////////////////////////////////////////////
#define	MSD_2_SPD(f,m)	((DWORD) (f * (m / 1000.)))		// ms/div->smp/div

/////////////////////////////////////////////////////////////////////////////
// CAmpDsp
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAmpDsp, CWnd)
	//{{AFX_MSG_MAP(CAmpDsp)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEACTIVATE()
//	ON_MESSAGE (AUDFILEVT, AudFilEvt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmpDsp creation
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CAmpDsp, CWnd)

CAmpDsp::CAmpDsp()
{
	m_pAmpGph = new CAmpGph;
	m_pAmpXAx = new CAmpXAx;
	m_pAmpYAx = new CAmpYAx;
	m_pAmpSta = new CAmpSta;
	m_pAudFil = NULL;
}
CAmpDsp::~CAmpDsp()
{
	delete m_pAmpGph;
	delete m_pAmpXAx;
	delete m_pAmpYAx;
	delete m_pAmpSta;
	if (AfxIsValidAddress (m_pAudFil, sizeof (*m_pAudFil), FALSE) 
		&& m_pAudFil->IsKindOf(RUNTIME_CLASS(CAudFil))) 
		m_pAudFil->RemAmpDsp (this);
}

/////////////////////////////////////////////////////////////////////////////
// Public funtions
/////////////////////////////////////////////////////////////////////////////
BOOL	CAmpDsp::Create(CAudFil *pAudFil, CWnd* pParentWnd, UINT nChd_ID, 
		const RECT& rIniRec, float flMSpDiv)
{
	const char* pszWndCls;
	RECT		rBndRec;
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	m_pAudFil = pAudFil;

	/////////////////////////////////////////////////////////////////////////
	// Initialize to default settings
	/////////////////////////////////////////////////////////////////////////
	m_adAmpDes.ulSmpOff	= 0L; 	 
	m_adAmpDes.ulDocLen	= m_pAudFil->GetSmpCnt(); 	 
	m_adAmpDes.ulSmpFrq	= m_pAudFil->GetSmpFrq(); 
	m_adAmpDes.flSmppGP	= min (SMPPGPMAX, max (SMPPGPMIN, 
		(float) MSD_2_SPD (m_pAudFil->GetSmpFrq(), flMSpDiv) / PTPMAJDIV));
	m_adAmpDes.usArrLen	= AMPLENDEF;	 
	m_adAmpDes.usGPtCnt	= 0;	 
	m_adAmpDes.usBlkSiz	= (WORD) PCMCapQry (m_pAudFil->GetPCMTyp(), BLKSIZQRY, 0L);	 
	m_adAmpDes.usViwCon	= AMPCONDEF;	 

	m_apAmpPnt.lYAxExt	= PCMCapQry (m_pAudFil->GetPCMTyp(), ATDMAXQRY, 0L);
	m_apAmpPnt.sYAxMax	= + 100;	 
	m_apAmpPnt.sYAxMin	= - 100;	 
	m_apAmpPnt.sYAxInc	=    10;	 

	m_auAmpUsr.amMseOwn = AMPMSENON;
	m_auAmpUsr.ulSelBeg	= 0L;
	m_auAmpUsr.ulSelEnd	= 0L;
	m_auAmpUsr.usAmpMax	= 0;
	m_auAmpUsr.usAmpMin	= 0;
	m_auAmpUsr.ulPosAtP	= 0L;
	m_auAmpUsr.bPosBln  = FALSE;

	/////////////////////////////////////////////////////////////////////////
	// Register & Create Amplitude Parent window
	/////////////////////////////////////////////////////////////////////////
	pszWndCls = AfxRegisterWndClass (0, 
		AfxGetApp()->LoadCursor (IDR_VFEARRPTR), (HBRUSH) GetStockObject (LTGRAY_BRUSH));
	if (!CWnd::Create (pszWndCls, NULL, WS_CHILD | WS_VISIBLE, rIniRec,
		pParentWnd, nChd_ID)) return (FALSE);
	GetClientRect (&rBndRec);
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!m_pAmpSta->Create(this, CAmpDsp::AMPCIDSTA, rBndRec)) return (FALSE);
	if (!m_pAmpXAx->Create(this, CAmpDsp::AMPCIDXAX, rBndRec)) return (FALSE);
	if (!m_pAmpYAx->Create(this, CAmpDsp::AMPCIDYAX, rBndRec)) return (FALSE);
	if (!m_pAmpGph->Create(this, CAmpDsp::AMPCIDGPH, rBndRec)) return (FALSE);

//	/////////////////////////////////////////////////////////////////////////
//	// Update display resolution (inhibit re-paint)
//	/////////////////////////////////////////////////////////////////////////
//	m_pAmpXAx->ChgZAxRes (SB_SCRSMPPMD, MSD_2_SPD (m_adAmpDes.ulSmpFrq, flMSpDiv), TRUE); 

	/////////////////////////////////////////////////////////////////////////
	// Update display
	/////////////////////////////////////////////////////////////////////////
	DspArrUpd ();
	DspArrPnt (&rBndRec);
	pAudFil->AddAmpDsp (this);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);

}

void	CAmpDsp::DspArrUpd ()
{
	DWORD		ulGPtCnt;

	/////////////////////////////////////////////////////////////////////////
	// Initialize document length
	/////////////////////////////////////////////////////////////////////////
	m_adAmpDes.ulDocLen	= m_pAudFil->GetSmpCnt(); 	 

//ajm 9/97: Moved here to update sample offset when length changes & causes 
// scroll bars (and therefore offset) to change.
/////////////////////////////////////////////////////////////////////////
// Update scroll bar on/off (based on document length)
/////////////////////////////////////////////////////////////////////////
AmpXAxScr (m_pAmpXAx->m_hWnd, 0L, &m_adAmpDes.ulSmpOff, &m_adAmpDes);

	/////////////////////////////////////////////////////////////////////////
	// Open the source PCM file
	/////////////////////////////////////////////////////////////////////////
	if (!m_pAudFil->Open(CFile::modeRead)) return;

	/////////////////////////////////////////////////////////////////////////
	// Seek & Initialize ADPCM adaptive values
	/////////////////////////////////////////////////////////////////////////
	m_pAudFil->Seek(m_adAmpDes.ulSmpOff);
	
	/////////////////////////////////////////////////////////////////////////
	// Convert ADPCM into oscillation array
	/////////////////////////////////////////////////////////////////////////
	ulGPtCnt = m_pAudFil->Read ((MXMBLK *) m_mbAmpGph[0], m_adAmpDes.usArrLen, 
		m_adAmpDes.flSmppGP);
 	if (-1L != ulGPtCnt) m_adAmpDes.usGPtCnt = (WORD) ulGPtCnt;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	m_pAudFil->Close();

//	/////////////////////////////////////////////////////////////////////////
//	// Update scroll bar on/off (based on document length)
//	/////////////////////////////////////////////////////////////////////////
//	AmpXAxScr (m_pAmpXAx->m_hWnd, 0L, &m_adAmpDes.ulSmpOff, &m_adAmpDes);

	/////////////////////////////////////////////////////////////////////////
	// Notify parent that contents have changed
	/////////////////////////////////////////////////////////////////////////
	GetParent()->Invalidate (TRUE); 

}

BOOL	CAmpDsp::DspArrPnt (const RECT * prIniRec)
{
	RECT 	rBndRec;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (prIniRec) rBndRec = *prIniRec;
		else GetClientRect (&rBndRec);
	
	/////////////////////////////////////////////////////////////////////////
	// Position self
	/////////////////////////////////////////////////////////////////////////
	rBndRec.bottom -= rBndRec.top;								/* Hgt  */
	rBndRec.right  -= rBndRec.left;								/* Wid  */
	MoveWindow (rBndRec.left, rBndRec.top, rBndRec.right, rBndRec.bottom, TRUE);
	ShowWindow (SW_SHOW);
	GetClientRect (&rBndRec);
	
	/////////////////////////////////////////////////////////////////////////
	// Position children
	/////////////////////////////////////////////////////////////////////////
	AmpStaPos (m_pAmpSta->m_hWnd, &rBndRec);
	AmpXAxPos (m_pAmpXAx->m_hWnd, &rBndRec);
	AmpYAxPos (m_pAmpYAx->m_hWnd, &rBndRec);
	AmpGphPos (m_pAmpGph->m_hWnd, &rBndRec);

	/////////////////////////////////////////////////////////////////////////
	// Force update
	/////////////////////////////////////////////////////////////////////////
	Invalidate (TRUE); 

	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

int		CAmpDsp::OnMouseActivate(CWnd*, UINT, UINT)
{				  
	/////////////////////////////////////////////////////////////////////////
	// Eat mouse click if parent does not have focus (prevent selection reset)
	/////////////////////////////////////////////////////////////////////////
	if (GetFocus () == (this->GetParent())) return MA_ACTIVATE; 
	(this->GetParent())->SetFocus();
	return MA_ACTIVATEANDEAT;			   
	
}

void	CAmpDsp::KeyDwnEvt(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	OnKeyDown(nChar, nRepCnt, nFlags);
}

void	CAmpDsp::TimTicEvt(UINT nIDEvent)
{
	m_pAmpGph->TimTicEvt (nIDEvent);
}

BOOL	CAmpDsp::ChgResEvt (float flMSpDiv)
{
	/////////////////////////////////////////////////////////////////////////
	return (m_pAmpXAx->ChgZAxRes (SB_SCRSMPPMD, MSD_2_SPD (m_adAmpDes.ulSmpFrq, flMSpDiv)));
}

BOOL	CAmpDsp::ChgOffEvt (DWORD ulNewOff)
{
	/////////////////////////////////////////////////////////////////////////
	return (m_pAmpXAx->ChgXAxOff (SB_SCRSMPGTO, ulNewOff));
}

void	CAmpDsp::CarSetEvt (DWORD ulSmpOff, BOOL bfUpdSta)
{
	/////////////////////////////////////////////////////////////////////////
	AmpCarMov (m_pAmpGph->m_hWnd, ulSmpOff, &m_adAmpDes, &m_auAmpUsr);
	if (bfUpdSta) m_pAmpSta->Invalidate (TRUE);
}

BOOL	CAmpDsp::CarGetEvt (DWORD FAR *pulSmpAtP)
{
	/////////////////////////////////////////////////////////////////////////
	*pulSmpAtP = m_auAmpUsr.ulPosAtP;
	return (TRUE);
}

void	CAmpDsp::SelSetEvt (DWORD ulSmpOff, DWORD ulSmpLen)
{
	AmpSelMov (m_pAmpGph->m_hWnd, ulSmpOff, ulSmpLen, &m_adAmpDes, &m_auAmpUsr);

	/////////////////////////////////////////////////////////////////////////
	// Repaint for coloured selection region; update status selection
	/////////////////////////////////////////////////////////////////////////
	m_pAmpGph->Invalidate (TRUE); 
	m_pAmpSta->Invalidate (TRUE);

}

BOOL	CAmpDsp::SelShfEvt (DWORD ulShfPnt, long lShfAmt)
{
	DWORD	ulSmpOff;
	DWORD	ulSmpLen;
	DWORD	ulShfCnt = labs (lShfAmt);

	/////////////////////////////////////////////////////////////////////////
	if (!SelGetEvt (&ulSmpOff, &ulSmpLen)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Right Shift: Shift point appears at new position			  
	// Left  Shift: Shift point appears at new position, ulShfPnt	
	//              could be end of file!							
	/////////////////////////////////////////////////////////////////////////
	if (lShfAmt < 0) {
		// Shift Point to left of selection region?
		if (ulShfPnt <= ulSmpOff) {
			ulSmpOff -= min (ulSmpOff, ulShfCnt);
			SelSetEvt (ulSmpOff, ulSmpLen);
			return (TRUE);
		}
		// Shift Point within selection + effected region?
		else if (ulShfPnt <= (ulSmpOff + ulSmpLen + ulShfCnt)) {
			ulSmpLen -= min (ulSmpLen, ulShfCnt - (ulShfPnt - (ulSmpOff + ulSmpLen)));
			SelSetEvt (ulSmpOff, ulSmpLen);
			return (TRUE);
		}
	}
	if (lShfAmt > 0) {
		// Shift Point to left of selection region?
		if (ulShfPnt <= ulSmpOff) {
			ulSmpOff += ulShfCnt;
			SelSetEvt (ulSmpOff, ulSmpLen);
			return (TRUE);
		}
		// Shift Point within selection region?
		else if (ulShfPnt <= (ulSmpOff + ulSmpLen)) {
			ulSmpLen += ulShfCnt;
			SelSetEvt (ulSmpOff, ulSmpLen);
			return (TRUE);
		}
	}
	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

BOOL	CAmpDsp::SelGetEvt (DWORD FAR *pulSmpOff, DWORD FAR *pulSmpLen)
{
	/////////////////////////////////////////////////////////////////////////
	// If no selection set, do not modify "suggested selection"	pointer vals
	/////////////////////////////////////////////////////////////////////////
	if (m_auAmpUsr.ulSelBeg == m_auAmpUsr.ulSelEnd) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	*pulSmpOff = min (m_auAmpUsr.ulSelBeg, m_auAmpUsr.ulSelEnd);
	*pulSmpLen = max (m_auAmpUsr.ulSelBeg, m_auAmpUsr.ulSelEnd) - *pulSmpOff;

	/////////////////////////////////////////////////////////////////////////
	// Indicate selection region active
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CAmpDsp commands
/////////////////////////////////////////////////////////////////////////////
void CAmpDsp::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_pAmpGph->KeyDwnEvt(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// Public C interface
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export AmpDspOpn (CAmpDsp FAR * FAR *ppAmpDsp, CAudFil FAR *pAudFil, 
						float flMSpDiv, VISWNDHDL hWnd)
{
	RECT		rWrkRec;	   
	CWnd		CParWnd;

	/////////////////////////////////////////////////////////////////////////
	// VB3 hWnd Note: "Because the value of this property can change while
	// a program is running, never store the hWnd value in a variable."
	/////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAudFil) return (-1);
	*ppAmpDsp = new CAmpDsp;	
	
	/////////////////////////////////////////////////////////////////////////
	CParWnd.Attach ((HWND) hWnd);
	CParWnd.GetClientRect (&rWrkRec);										
  	
	/////////////////////////////////////////////////////////////////////////
	//		  Create Waveform Document child/parent window
	/////////////////////////////////////////////////////////////////////////
	BOOL bTmp = (*ppAmpDsp)->Create(pAudFil, &CParWnd, CAmpDsp::AMPCIDDSP, 
		rWrkRec, flMSpDiv);		

	/////////////////////////////////////////////////////////////////////////
	CParWnd.Detach ();	 
	
	return (0);
	   
}

extern "C"
WORD FAR PASCAL _export AmpDspCls (CAmpDsp FAR * FAR *ppAmpDsp)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == *ppAmpDsp) return (-1);
	delete *ppAmpDsp;
	*ppAmpDsp = NULL;

	return (0);
}

extern "C"
WORD FAR PASCAL _export AmpDspPnt (CAmpDsp FAR *pAmpDsp, VISWNDHDL hWnd)
{
	RECT		rWrkRec;

	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (-1);

	/////////////////////////////////////////////////////////////////////////
	GetClientRect ((HWND) hWnd, &rWrkRec);
	InflateRect (&rWrkRec, -2, -2);
	pAmpDsp->DspArrPnt (&rWrkRec);

	return (0);

}

extern "C"
WORD FAR PASCAL _export AmpDspKey (CAmpDsp FAR *pAmpDsp, WORD usChar, WORD usRepCnt, WORD usFlags)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (-1);
	pAmpDsp->KeyDwnEvt(usChar, usRepCnt, usFlags);
	return (0);
}

extern "C"
WORD FAR PASCAL _export AmpDspScr (CAmpDsp FAR *pAmpDsp, DWORD ulSmpPos)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (-1);
	return (pAmpDsp->ChgOffEvt(ulSmpPos));
}

extern "C"
WORD FAR PASCAL _export AmpDspRes (CAmpDsp FAR *pAmpDsp, float flMSpDiv)
{
	/////////////////////////////////////////////////////////////////////////
	if ((NULL == pAmpDsp) || (flMSpDiv <= 0)) return (-1);
	return (pAmpDsp->ChgResEvt(flMSpDiv));
}

extern "C"
WORD FAR PASCAL _export AmpDspTic (CAmpDsp FAR *pAmpDsp, WORD usIDEvent)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (-1);
	pAmpDsp->TimTicEvt(usIDEvent);
	return (0);
}

extern "C"
WORD FAR PASCAL _export AmpDspCarSet (CAmpDsp FAR *pAmpDsp, DWORD ulSmpOff)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (FALSE);
	pAmpDsp->CarSetEvt(ulSmpOff, TRUE);
	return (TRUE);
}

extern "C"
WORD FAR PASCAL _export AmpDspCarGet (CAmpDsp FAR *pAmpDsp, DWORD FAR *pulSmpAtP)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (FALSE);
	return (pAmpDsp->CarGetEvt(pulSmpAtP));
}

extern "C"
WORD FAR PASCAL _export AmpDspSelGet (CAmpDsp FAR *pAmpDsp, DWORD FAR *pulSmpOff,
						DWORD FAR *pulSmpLen)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (FALSE);
	return (pAmpDsp->SelGetEvt(pulSmpOff, pulSmpLen));
}

extern "C"
WORD FAR PASCAL _export AmpDspSelSet (CAmpDsp FAR *pAmpDsp, DWORD ulSmpOff,
						DWORD ulSmpLen)
{
	/////////////////////////////////////////////////////////////////////////
	if (NULL == pAmpDsp) return (FALSE);
	pAmpDsp->SelSetEvt(ulSmpOff, ulSmpLen);
	return (TRUE);
}


