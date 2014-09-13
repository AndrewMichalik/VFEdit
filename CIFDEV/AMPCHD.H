/////////////////////////////////////////////////////////////////////////////
// AmpChd.h : Interface of the CAmpDsp child classes
//
/////////////////////////////////////////////////////////////////////////////
class	CAmpDsp;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAmpGph : public CWnd
{
public:
	CAmpGph ();
	BOOL 	Create (CAmpDsp * CAmpDsp, UINT nChd_ID, const RECT& rect);
	void 	KeyDwnEvt (UINT nChar, UINT nRepCnt, UINT nFlags);
	void 	TimTicEvt (UINT nIDEvent);

// Implementation
protected:
	CAmpDsp	*m_pAmpDsp;

	// message handlers
	//{{AFX_MSG(CAmpGph)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAmpXAx : public CWnd
{
public:
	CAmpXAx ();
	BOOL 	Create (CAmpDsp * CAmpDsp, UINT nChd_ID, const RECT& rect);
	BOOL	DrwAmpDsp (const RECT& rIniRec);
	BOOL	ChgXAxOff (UINT nSBCode, DWORD ulNewOff);
	BOOL	ChgZAxRes (UINT nSBCode, DWORD ulSmpCnt, BOOL bfDspInh = FALSE);

// Implementation
protected:
	CAmpDsp	*m_pAmpDsp;

	// message handlers
	//{{AFX_MSG(CAmpXAx)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT, UINT, CScrollBar*);
	afx_msg void OnVScroll(UINT, UINT, CScrollBar*);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAmpYAx : public CWnd
{
public:
	CAmpYAx ();
	BOOL 	Create (CAmpDsp * CAmpDsp, UINT nChd_ID, const RECT& rect);
	BOOL	DrwAmpDsp (const RECT& rIniRec);

// Implementation
protected:
	CAmpDsp	*m_pAmpDsp;

	// message handlers
	//{{AFX_MSG(CAmpYAx)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CAmpSta : public CWnd
{
public:
	CAmpSta ();
	BOOL 	Create (CAmpDsp * CAmpDsp, UINT nChd_ID, const RECT& rect);
	BOOL	DrwAmpDsp (const RECT& rIniRec);

// Implementation
protected:
	CAmpDsp	*m_pAmpDsp;

	// message handlers
	//{{AFX_MSG(CAmpSta)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT, UINT, CScrollBar*);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

