/////////////////////////////////////////////////////////////////////////////
// AnoTxt.h : Interface of the CAnoTxt class
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
#if (!defined (MEMVERNUM))
	#include "os_dev\winmem.h"			// Generic memory supp defs
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CAnoTxt
/////////////////////////////////////////////////////////////////////////////
class CAnoTxt : public CObject
{
public:
	CAnoTxt () 			{m_bfAnoMod = FALSE; m_mhAnoMem = NULL;}
	virtual	VISMEMHDL *	GetAnoHdl () {return (&m_mhAnoMem);}
	virtual	CString		GetAnoTxt () 
	{
		LPSTR	lpAnoTxt;
		if (!(lpAnoTxt = (LPSTR) GloMemLck (m_mhAnoMem))) return ("");
		CString	csAnoTxt = lpAnoTxt;
		GloMemUnL (m_mhAnoMem);
		m_bfAnoMod = FALSE;
		return (csAnoTxt);		
	}
	virtual	WORD		SetAnoTxt (CString csAnoTxt) 
	{
		LPSTR	lpAnoTxt;
		if (!(m_mhAnoMem = GloReAMem (m_mhAnoMem, 
			csAnoTxt.GetLength() + 1))) return (-1);
		if (!(lpAnoTxt = (LPSTR) GloMemLck (m_mhAnoMem))) return (-1);
		strcpy (lpAnoTxt, csAnoTxt);
		GloMemUnL (m_mhAnoMem);
		m_bfAnoMod = TRUE;
		return (0);
	}
	virtual	void		ClrModFlg () {m_bfAnoMod = FALSE;}
	virtual	BOOL 		Is_ModSet () {return (m_bfAnoMod);}

private: 	
	BOOL		m_bfAnoMod;				// Annotation text modification flag
	VISMEMHDL	m_mhAnoMem;				// Annotation text memory handle
};


