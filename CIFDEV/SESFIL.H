/////////////////////////////////////////////////////////////////////////////
// SesFil.h : interface of the CSesFil classes
/////////////////////////////////////////////////////////////////////////////
#include "audfil.h"						// Audio file support defs
#include "tmpfil.h"						// Temp file support defs
#include "anotxt.h"						// Annotation text support defs

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CUndLst;

/////////////////////////////////////////////////////////////////////////////
// CSesFil
/////////////////////////////////////////////////////////////////////////////
class CSesFil : public CAudFil
{
public:
	CSesFil ();
	~CSesFil ();
	virtual	WORD		SesFilOpn (CString csFilNam, DWORD ulSegSel, 
							FILFMT FAR *pusFilFmt, PCMTYP FAR *pusPCMTyp, 
							WORD FAR *pusChnCnt, DWORD FAR *pulSmpFrq, 
							CString csTmpDir, HWND hPolWnd, UINT nMsgPrm);
	virtual	WORD		SesFilOpn (CSesFil *pSesSrc);
	virtual	WORD 		SesFilSegLod (SEGQRY usSegQry = SEGSELQRY, DWORD ulSegSel = 0L);
	virtual	WORD 		SesFilSegCre ();
	virtual	WORD 		SesFilSegDel ();
	virtual	WORD 		SesFilSegUpd ();
	virtual	WORD		SesFilSav ();
	virtual BOOL		GetStatus (CFileStatus &rStatus);
	virtual	OFSTRUCT_V*	GetFilOFS ();
	virtual	DWORD		GetSmpCnt ();
	virtual	CString		GetTmpDir () {return (m_csTmpDir);}
	virtual	BOOL 		Is_ModSet (BOOL bfSegReq = FALSE);

virtual	DWORD		GetSegOff ();

	virtual	CString		GetAnoTxt () {return (m_atAnoTxt.GetAnoTxt());} 
	virtual	WORD		SetAnoTxt (CString csAnoTxt) {return (m_atAnoTxt.SetAnoTxt(csAnoTxt));}
	virtual	CUndLst   * GetUndLst () const {return (m_pUndLst);}
	virtual	WORD		CopTo_Clp (DWORD *pulSmpOff, DWORD *pulSmpCnt, 
						CAudFil *pClpFil);
	virtual	WORD		LogAndShf (DWORD *pulSmpOff, DWORD *pulCutSmp, 
						DWORD *pulPstSmp, CUndLst *pUndLst = NULL, 
						BOOL bfSilPst = FALSE);

private: 	
	virtual WORD		IniFilOFS (CString csFilNam,
							FILFMT *pusFilFmt, PCMTYP *pusPCMTyp,
							WORD *pusChnCnt, DWORD *pulSmpFrq, 
							CString csTmpDir, HWND hPolWnd, UINT nMsgPrm);

	CString		m_csTmpDir;				// Temporary file directory
	CTmpFil		m_tfWrkFil;         	// Work File audio data file
	CTmpFil		m_tfSnpFil;				// Snippet audio data file
	CAnoTxt		m_atAnoTxt;				// Annotation text block
	CUndLst	*	m_pUndLst;				// Undo file event list
//	SEGINF		m_siSegInf;				// Work segment info block

};


