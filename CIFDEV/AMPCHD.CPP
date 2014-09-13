/////////////////////////////////////////////////////////////////////////////
// AmpChd.cpp : Implementation of the CAmpDsp child classes
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "ampdsp.h"						// Amplitude display window
#include "ampchd.h"						// Amplitude display child windows

/////////////////////////////////////////////////////////////////////////////
// CAmpGph
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAmpGph, CWnd)
	//{{AFX_MSG_MAP(CAmpGph)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAmpGph::CAmpGph()
{
	m_hWnd = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Public functions
/////////////////////////////////////////////////////////////////////////////
BOOL	CAmpGph::Create(class CAmpDsp *pCAmpDsp, UINT nChd_ID, const RECT& rIniRec)
{
	const char* pszWndCls;

	/////////////////////////////////////////////////////////////////////////
	// Register & Create Amplitude Graph window
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp = pCAmpDsp;
	pszWndCls = AfxRegisterWndClass (CS_HREDRAW | CS_VREDRAW, 
	AfxGetApp()->LoadCursor (IDR_VFESELMRK), (HBRUSH) GetStockObject (WHITE_BRUSH));
	if (!CWnd::Create (pszWndCls, NULL, WS_CHILD | WS_VISIBLE, rIniRec,
	pCAmpDsp, nChd_ID)) return (FALSE);

	return (TRUE);
}

void	CAmpGph::KeyDwnEvt(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	OnKeyDown(nChar, nRepCnt, nFlags);
}

void	CAmpGph::TimTicEvt(UINT nIDEvent)
{
	if (NULL != m_hWnd) OnTimer (nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// Protected functions
/////////////////////////////////////////////////////////////////////////////
void	CAmpGph::OnPaint()
{
	AmpGphPnt (m_hWnd, &m_pAmpDsp->m_apAmpPnt, &m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr, 
	m_pAmpDsp->m_mbAmpGph[0]);
}

void	CAmpGph::OnTimer(UINT /* wParam */)
{
	CRect		rWrkRec;
	POINT		mpMsePos;
	static	int	nBlnCnt;

	if (++nBlnCnt >= AMPBLNPER) {
		AmpCarBln (m_hWnd, &m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr);
		nBlnCnt = 0;
	}

	/////////////////////////////////////////////////////////////////////////
	// Auto-Scroll
	/////////////////////////////////////////////////////////////////////////
	if (GetCapture () == this) {
		GetClientRect (rWrkRec);
		GetCursorPos (&mpMsePos);
		ScreenToClient (&mpMsePos);
		if (mpMsePos.x <= AMPSCRSEN) OnKeyDown (VK_LEFT, 0, 0);
		else if (mpMsePos.x >= (rWrkRec.right - AMPSCRSEN)) OnKeyDown (VK_RIGHT, 0, 0);
	}

}

void	CAmpGph::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	short	sScrAmt = 0; 				// Default scroll amount

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (0x8000 & GetKeyState (VK_SHIFT)) sScrAmt = +1;
	else if (0x8000 & GetKeyState (VK_CONTROL)) sScrAmt = -1;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (nChar)
	{
		case VK_CLEAR:
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, SB_SCRSMPFIT, 0L);
			break;
		case VK_UP:
			switch (sScrAmt) {
				case -1: sScrAmt = SB_LINEUP; break;
				case  0: sScrAmt = SB_PAGEUP; break;
				case +1: sScrAmt = SB_SCRFUL_UP; break;
			}
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, sScrAmt, 0L);
			break;
		case VK_DOWN:
			switch (sScrAmt) {
				case -1: sScrAmt = SB_LINEDOWN; break;
				case  0: sScrAmt = SB_PAGEDOWN; break;
				case +1: sScrAmt = SB_SCRFULDWN; break;
			}
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, sScrAmt, 0L);
			break;
		case VK_RIGHT:
			switch (sScrAmt) {
				case -1: sScrAmt = SB_LINERIGHT; break;
				case  0: sScrAmt = SB_PAGERIGHT; break;
				case +1: sScrAmt = SB_SCRFULRGT; break;
			}
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_HSCROLL, sScrAmt, 0L);
			break;
		case VK_LEFT:
			switch (sScrAmt) {
				case -1: sScrAmt = SB_LINELEFT;  break;
				case  0: sScrAmt = SB_PAGELEFT;  break;
				case +1: sScrAmt = SB_SCRFULLFT; break;
			}
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_HSCROLL, sScrAmt, 0L);
			break;
// Use page up/down for scrolling channels
//		case VK_NEXT:
//			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, SB_PAGELEFT, 0L);
//			break;
//		case VK_PRIOR:
//			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, SB_PAGERIGHT, 0L);
//			break;
		case VK_HOME:
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_HSCROLL, SB_LEFT, 0L);
			break;
		case VK_END:
			m_pAmpDsp->m_pAmpXAx->PostMessage (WM_HSCROLL, SB_RIGHT, 0L);
			break;
		default:
			break;
	}
}

void	CAmpGph::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rWrkRec;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	SetCapture ();
	GetClientRect (rWrkRec);
	ClientToScreen ((LPPOINT) &rWrkRec.left);
	ClientToScreen ((LPPOINT) &rWrkRec.right);
	ClipCursor ((LPRECT) &rWrkRec);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	AmpMseLDn (m_hWnd, nFlags, point,
		&m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr);
		m_pAmpDsp->m_pAmpSta->Invalidate (TRUE);

}

void	CAmpGph::OnMouseMove(UINT nFlags, CPoint point)
{
	short	sUpdFlg;
	
	/////////////////////////////////////////////////////////////////////////
	// Ignore mouse activity if grandparent does not have focus
	/////////////////////////////////////////////////////////////////////////
	if (GetFocus () != (this->GetParent())->GetParent()) return;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	sUpdFlg = AmpMseMov (m_hWnd, nFlags, point,
		&m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr);
		if (sUpdFlg) m_pAmpDsp->m_pAmpSta->Invalidate (TRUE);

}

void	CAmpGph::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture () != this) return;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	ClipCursor (NULL);
	ReleaseCapture ();
	AmpMseLUp (m_hWnd, nFlags, point,
		&m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr);

	/////////////////////////////////////////////////////////////////////////
	// Repaint for coloured selection region
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp->m_pAmpGph->Invalidate (TRUE); 

}

/////////////////////////////////////////////////////////////////////////////
// CAmpXAx
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAmpXAx, CWnd)
	//{{AFX_MSG_MAP(CAmpXAx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAmpXAx::CAmpXAx()
{
	m_hWnd = NULL;
}

BOOL	CAmpXAx::Create(class CAmpDsp *pCAmpDsp, UINT nChd_ID, const RECT& rIniRec)
{
	const char* pszWndCls;

	/////////////////////////////////////////////////////////////////////////
	// Register & Create Amplitude X-Axis window
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp = pCAmpDsp;
	pszWndCls = AfxRegisterWndClass (CS_HREDRAW | CS_VREDRAW,
	AfxGetApp()->LoadCursor (IDR_VFEARRPTR), (HBRUSH) GetStockObject (LTGRAY_BRUSH));
	if (!CWnd::Create (pszWndCls, NULL, WS_CHILD | WS_VISIBLE, rIniRec, 
	pCAmpDsp, nChd_ID)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Scroll bar may be visible / invisible
	/////////////////////////////////////////////////////////////////////////
	AmpXAxScr (m_hWnd, 0L, &m_pAmpDsp->m_adAmpDes.ulSmpOff, &m_pAmpDsp->m_adAmpDes);

	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

BOOL	CAmpXAx::ChgXAxOff(UINT nSBCode, DWORD ulNewOff)
{
	long	lDocDlt;

	/////////////////////////////////////////////////////////////////////////
	// Return TRUE to indicate NULL request or scroll not at boundary
	// Return FALSE to indicate "at max/min - no change" request (for beep)
	/////////////////////////////////////////////////////////////////////////
	if (!AmpXAxUpd (m_hWnd, SB_SCRSMPGTO, ulNewOff, &lDocDlt, 
		&m_pAmpDsp->m_adAmpDes)) return (TRUE);
	if (!lDocDlt) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Scroll to new position
	/////////////////////////////////////////////////////////////////////////
	AmpXAxScr (m_hWnd, lDocDlt, &m_pAmpDsp->m_adAmpDes.ulSmpOff, &m_pAmpDsp->m_adAmpDes);

	/////////////////////////////////////////////////////////////////////////
	// Scroll state stable; just redraw graphs
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp->DspArrUpd ();
	m_pAmpDsp->m_pAmpXAx->Invalidate (TRUE);
	m_pAmpDsp->m_pAmpGph->Invalidate (TRUE); 

	/////////////////////////////////////////////////////////////////////////
	return (TRUE);

}

BOOL	CAmpXAx::ChgZAxRes(UINT nSBCode, DWORD ulSmpCnt, BOOL bfDspInh)
{
	float	flResFac;
	DWORD	ulCtrSmp;					// Display center sample
	long	lDocDlt;

	/////////////////////////////////////////////////////////////////////////
	// Calculate & save original center point before setting new resolution
	/////////////////////////////////////////////////////////////////////////
	if (SB_SCRSMPFIT == nSBCode) {
		DWORD	ulSelBeg = min (m_pAmpDsp->m_auAmpUsr.ulSelBeg, m_pAmpDsp->m_auAmpUsr.ulSelEnd);
		DWORD	ulSelEnd = max (m_pAmpDsp->m_auAmpUsr.ulSelBeg, m_pAmpDsp->m_auAmpUsr.ulSelEnd);
		DWORD	ulDocLen = m_pAmpDsp->m_adAmpDes.ulDocLen;   
		float	flScrFac = SCRPERPAG ? SCRPERPAG / (float) (SCRPERPAG - 1) : 1;

		/////////////////////////////////////////////////////////////////////
		// Adjust if nothing is currently selected
		/////////////////////////////////////////////////////////////////////
		if (ulSelBeg == ulSelEnd) {
			ulSelBeg = 0L;
			ulSelEnd = ulDocLen;
		}
		/////////////////////////////////////////////////////////////////////
		// Set default sample count & insure selected region is fully visible
		// Adjust for selection region beyond end of document
		/////////////////////////////////////////////////////////////////////
		ulSmpCnt = ulSelEnd - ulSelBeg;
		if (ulSelBeg > ulDocLen) {
			ulSmpCnt = ulSelEnd - ulDocLen;
			ulSmpCnt = (DWORD) (ulSmpCnt * flScrFac);
		}
		else if ((ulSelEnd > ulDocLen) && ((ulDocLen - ulSelBeg) < ulSmpCnt / SCRPERPAG)) {
			// Zoom to allow for last chunk of document plus selected region
			ulSmpCnt += (DWORD) (ulSmpCnt * (flScrFac - 1)) - (ulDocLen - ulSelBeg);
		}
		ulCtrSmp = ulSelBeg + (ulSmpCnt / 2);
	}
	else {  
		DWORD	ulDocLen = m_pAmpDsp->m_adAmpDes.ulDocLen;   
		DWORD	ulVisLen = (DWORD) (m_pAmpDsp->m_adAmpDes.flSmppGP * m_pAmpDsp->m_adAmpDes.usArrLen);
		
		// Check if visible waveform touches right edge     
		// If it does not fill screen, retain current left edge offset
		if (ulDocLen > (m_pAmpDsp->m_adAmpDes.ulSmpOff + ulVisLen))
			ulCtrSmp = m_pAmpDsp->m_adAmpDes.ulSmpOff + (ulVisLen / 2L);
		else {
			ulCtrSmp = m_pAmpDsp->m_adAmpDes.ulSmpOff + (ulDocLen - m_pAmpDsp->m_adAmpDes.ulSmpOff) / 2L;
        }
	}

	/////////////////////////////////////////////////////////////////////////
	// Return TRUE to indicate NULL request or scroll not at boundary
	// Return FALSE to indicate "at max/min - no change" request (for beep)
	/////////////////////////////////////////////////////////////////////////
	if (!AmpZAxUpd (m_hWnd, nSBCode, ulSmpCnt, &flResFac, &m_pAmpDsp->m_adAmpDes))
		return (TRUE); 

	/////////////////////////////////////////////////////////////////////////
	// Calculate ZAx resolution, XAx offset delta
	// If resolution and position unchanged, return false
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp->m_adAmpDes.flSmppGP *= flResFac;
	lDocDlt = (ulCtrSmp - min (ulCtrSmp, (DWORD) ((m_pAmpDsp->m_adAmpDes.flSmppGP * m_pAmpDsp->m_adAmpDes.usArrLen) / 2)))
		 - m_pAmpDsp->m_adAmpDes.ulSmpOff;
	if ((1 == flResFac) && !lDocDlt) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Exit if display update is inhibited
	/////////////////////////////////////////////////////////////////////////
	if (bfDspInh) return (TRUE);

	/////////////////////////////////////////////////////////////////////////
	// Scroll to new centered position
	/////////////////////////////////////////////////////////////////////////
	if (SCREXTUPD & AmpXAxScr (m_hWnd, lDocDlt, &m_pAmpDsp->m_adAmpDes.ulSmpOff, &m_pAmpDsp->m_adAmpDes))
	{
		/////////////////////////////////////////////////////////////////////
		// Scroll bar has appeared / disappeared; redraw whole window
		/////////////////////////////////////////////////////////////////////
		m_pAmpDsp->DspArrUpd ();
		m_pAmpDsp->DspArrPnt ();
	}
	else {
		/////////////////////////////////////////////////////////////////////
		// Scroll state stable; just redraw graphs
		/////////////////////////////////////////////////////////////////////
		m_pAmpDsp->DspArrUpd ();
		m_pAmpDsp->m_pAmpXAx->Invalidate (TRUE);
		m_pAmpDsp->m_pAmpGph->Invalidate (TRUE); 
	}

	return (TRUE);
}

void CAmpXAx::OnPaint()
{
	AmpXAxPnt (m_hWnd, &m_pAmpDsp->m_adAmpDes);
}

void	CAmpXAx::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	POINT	mpMsePos;
	long	lDocDlt;
	
	/////////////////////////////////////////////////////////////////////////
	// Return if not recoginized scroll message
	/////////////////////////////////////////////////////////////////////////
	if (!AmpXAxUpd (m_hWnd, nSBCode, nPos, &lDocDlt, &m_pAmpDsp->m_adAmpDes)) 
		return;

	/////////////////////////////////////////////////////////////////////////
	// Beep if at max / min condition
	/////////////////////////////////////////////////////////////////////////
	if (!lDocDlt) {
		MessageBeep (0);
		return;
	}	

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	AmpXAxScr (m_hWnd, lDocDlt, &m_pAmpDsp->m_adAmpDes.ulSmpOff, 
		&m_pAmpDsp->m_adAmpDes);

	/////////////////////////////////////////////////////////////////////////
	// Track mouse for auto-scroll
	/////////////////////////////////////////////////////////////////////////
	if (GetCapture () == m_pAmpDsp->m_pAmpGph) {
		GetCursorPos (&mpMsePos);
		SetCursorPos (mpMsePos.x, mpMsePos.y);
	}

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp->DspArrUpd ();
	m_pAmpDsp->m_pAmpXAx->Invalidate (TRUE);
	m_pAmpDsp->m_pAmpGph->Invalidate (TRUE); 

}

void	CAmpXAx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ 
	/////////////////////////////////////////////////////////////////////////
	if (!ChgZAxRes (nSBCode, 0L)) MessageBeep(0);
	
	/////////////////////////////////////////////////////////////////////////
	return;

}

/////////////////////////////////////////////////////////////////////////////
// CAmpYAx
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAmpYAx, CWnd)
	//{{AFX_MSG_MAP(CAmpYAx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAmpYAx::CAmpYAx()
{
	m_hWnd = NULL;
}

BOOL	CAmpYAx::Create(class CAmpDsp *pCAmpDsp, UINT nChd_ID, const RECT& rIniRec)
{
	const char* pszWndCls;

	/////////////////////////////////////////////////////////////////////////
	// Register & Create Amplitude Y-Axis window
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp = pCAmpDsp;
	pszWndCls = AfxRegisterWndClass (CS_HREDRAW | CS_VREDRAW,
		AfxGetApp()->LoadCursor (IDR_VFEARRPTR), (HBRUSH) GetStockObject (LTGRAY_BRUSH));
	if (!CWnd::Create (pszWndCls, NULL, WS_CHILD | WS_VISIBLE, rIniRec, 
		pCAmpDsp, nChd_ID)) return (FALSE);

	return (TRUE);
}

void	CAmpYAx::OnPaint()
{
	AmpYAxPnt (m_hWnd, &m_pAmpDsp->m_apAmpPnt);
}

/////////////////////////////////////////////////////////////////////////////
// CAmpSta
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAmpSta, CWnd)
	//{{AFX_MSG_MAP(CAmpSta)
	ON_WM_PAINT()
	ON_WM_VSCROLL()							// Scroll bar attached to status
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAmpSta::CAmpSta()
{
	m_hWnd = NULL;
}

BOOL	CAmpSta::Create(class CAmpDsp *pCAmpDsp, UINT nChd_ID, const RECT& rIniRec)
{
	const char* pszWndCls;

	/////////////////////////////////////////////////////////////////////////
	// Register & Create Amplitude Extents window
	/////////////////////////////////////////////////////////////////////////
	m_pAmpDsp = pCAmpDsp;
	pszWndCls = AfxRegisterWndClass (CS_HREDRAW | CS_VREDRAW,
		AfxGetApp()->LoadCursor (IDR_VFEARRPTR), (HBRUSH) GetStockObject (LTGRAY_BRUSH));
	if (!CWnd::Create (pszWndCls, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL, 
		rIniRec, pCAmpDsp, nChd_ID)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

void	CAmpSta::OnPaint()
{
	AmpStaPnt (m_hWnd, &m_pAmpDsp->m_adAmpDes, &m_pAmpDsp->m_auAmpUsr);
}

void	CAmpSta::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pAmpDsp->m_pAmpXAx->PostMessage (WM_VSCROLL, nSBCode, nPos);
}
