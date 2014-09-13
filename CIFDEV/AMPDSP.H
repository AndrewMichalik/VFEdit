/////////////////////////////////////////////////////////////////////////////
// AmpDsp.h : interface of the CAmpDsp class
//
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
	#include "ampdev\genamp.h"			// Waveform Display defs
}

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CAudFil;
class	CAmpGph;
class	CAmpXAx;
class	CAmpYAx;
class	CAmpSta;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const	int		AMPLENMAX =     512;	// Amplitude disp max length
const	int		AMPLENDEF =     400;	// Amplitude disp def length
const	int		AMPBLNPER =       4;	// Amplitude disp timer period
const	int		AMPSCRSEN =       1;	// Amplitude disp scroll sensitivity
const	int		AMPCHNDEF =       1;	// Amplitude disp def # chan
const	int		AMPCONDEF =      20;	// Amplitude view connected wave res

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAmpDsp : public CWnd
{
	DECLARE_DYNAMIC(CAmpDsp)
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	enum _AMPCID {
		AMPCIDNUL = 0,		   			// Null (0)	unique child ID
		AMPCIDDSP,			   			// Amp parent unique child ID
		AMPCIDGPH,			   			// Amp graph  unique child ID
		AMPCIDSTA,			   			// Amp status unique child ID
		AMPCIDXAX,			   			// XAxis line unique child ID
		AMPCIDYAX,			   			// YAxis line unique child ID
	};
	typedef	enum _AMPRES {
		AMPRESZOM = 0,		   			// Zoom resolution (samp/GP)
		AMPRESLOW,			   			// Low  resolution (samp/GP)
		AMPRESMED,			   			// Med  resolution (samp/GP)
		AMPRESHGH,			   			// High resolution (samp/GP)
		AMPRESLST,
	} AMPRES; 

//	enum _USRMSG {
//		AUDFILEVT = WM_USER,			// Audio File event
//	} USRMSG;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CAmpDsp	();
	~CAmpDsp	();
	BOOL 		Create (CAudFil *m_pAudFil, CWnd *pParentWnd, UINT nChd_ID, 
				const RECT& rect, float flSmppGP);
	void		DspArrUpd ();
	BOOL		DspArrPnt (const RECT *prIniRec = NULL);
	void 		KeyDwnEvt (UINT nChar, UINT nRepCnt, UINT nFlags);
	void 		TimTicEvt (UINT nIDEvent);
	BOOL		ChgResEvt (float flMSpDiv);
	BOOL		ChgOffEvt (DWORD ulNewOff);
	void 		CarSetEvt (DWORD ulSmpOff, BOOL bfUpdSta);
	BOOL		CarGetEvt (DWORD FAR *pulSmpAtP);
	void		SelSetEvt (DWORD ulSmpOff, DWORD ulSmpLen);
	BOOL		SelShfEvt (DWORD ulShfPnt, long lShfAmt);
	BOOL		SelGetEvt (DWORD FAR *pulSmpOff, DWORD FAR *ulSmpLen);
	void		RemAudFil (CAudFil *pAudFil) {m_pAudFil = NULL;}

	friend	class CAmpGph;
	friend 	class CAmpXAx;
	friend	class CAmpYAx;
	friend	class CAmpSta;

// Implementation
protected: 	
	CAudFil	*	m_pAudFil;

	CAmpGph	*	m_pAmpGph;
	CAmpXAx	*	m_pAmpXAx;
	CAmpYAx	*	m_pAmpYAx;
	CAmpSta	*	m_pAmpSta;

	AMPDES		m_adAmpDes;
	AMPPNT		m_apAmpPnt;
	AMPUSR		m_auAmpUsr;

	AMPRES		m_arResSel;
	float		m_flAmpRes[AMPRESLST];

	AMPGPH		m_mbAmpGph[AMPCHNDEF][AMPLENDEF];

	// message handlers
	//{{AFX_MSG(CAmpDsp)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int	OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



