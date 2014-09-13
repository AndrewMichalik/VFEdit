/////////////////////////////////////////////////////////////////////////////
// SesEdt.h : interface of the CSesEdt classes
/////////////////////////////////////////////////////////////////////////////
#include "sesfil.h"						// Audio session file support defs
#include "undlst.h"						// Undo file support defs

/////////////////////////////////////////////////////////////////////////////
// CSesEdt
/////////////////////////////////////////////////////////////////////////////
class CSesEdt : public CSesFil
{
public:
	virtual	WORD		AudFilEff (DWORD *pulSmpOff, DWORD *pulSmpCnt, 
						CAudEff *pAudEff, const char *pszDesStr); 
	virtual	WORD		AudFilRep (DWORD *pulSmpOff, DWORD *pulSmpCnt, 
						BOOL bfSizAdj, WORD usAAFAlg, WORD usResAlg, 
						CAudFil *pSrcFil, DWORD *pulPstOff, DWORD *pulPstSmp,
						BOOL bfRawInh, const char *pszDesStr); 
	virtual	WORD		MasUpdBeg (CString csDstNam);
	virtual	WORD		MasUpdAbt ();
	virtual	WORD		MasUpdEnd (BOOL bfBakDel);
	virtual	WORD		WrkDspUpd (DWORD ulSmpOff, long lShfAmt, BOOL bfResFlg = FALSE);

protected: 	
	virtual	WORD		MasBakRem (CString csFilNam);

private: 	
	OFSTRUCT_V			m_ofBakOFS;		// Backup file OFS

};

/////////////////////////////////////////////////////////////////////////////
// CSesSta: Undo event user object
/////////////////////////////////////////////////////////////////////////////
class CSesSta : public CUndSta
{
public:
	CSesSta	(CSesEdt *pSesEdt) {UndStaSav (pSesEdt);}
	virtual	void		UndStaSav (CSesEdt *pSesEdt);
	virtual	void		UndStaRes (CSesEdt *pSesEdt);

private: 	
	/////////////////////////////////////////////////////////////////////////
	BOOL	m_bfModFlg;					// File modified flag
	DWORD	m_ulDocOff;					// Document sample offset
	DWORD	m_ulAtPOff;					// Display at position sample offset
	DWORD	m_ulSelOff;					// Display selection sample offset
	DWORD	m_ulSelLen;					// Display selection sample length

};
