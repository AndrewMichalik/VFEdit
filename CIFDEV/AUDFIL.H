/////////////////////////////////////////////////////////////////////////////
// AudFil.h : interface of the CAudFil classes
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
#if (!defined (FIOVERNUM))
	#include "os_dev\winmem.h"			// Generic memory supp defs
	#include "fiodev\genfio.h"			// Generic File I/O definitions
	#include "pcmdev\genpcm.h"			// PCM/APCM conv routine defs
#endif
	#include <float.h>					// Floating data type limits
}

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CAudEff;
class	CAmpDsp;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const int	PCMBLKSIZ =    1024;		// PCM conv mem blk siz
const int	PCMMINCNT =       4;		// PCM conv min mem blk cnt
const int	PCMMAXCNT =      63;		// PCM conv max mem blk cnt
const int 	CBKPOLTHR =	   1000;		// Callback poll time threshold (ms)
const int 	CBKPOLPER =	    500;		// Callback poll time period (ms)

/////////////////////////////////////////////////////////////////////////////
// CFIOCBk
/////////////////////////////////////////////////////////////////////////////
class CFIOCBk
{
public:
	CFIOCBk()			{m_hPolWnd = 0;}
	/////////////////////////////////////////////////////////////////////////
	// Long procedure poll callback functions
	/////////////////////////////////////////////////////////////////////////
	virtual	FIOPOLPRC	GetCBkPrc () {return ((FIOPOLPRC) FIOPolCBk);}
	virtual	CFIOCBk	*	GetCBkArg (WORD usMsgSID) {m_usActDes = usMsgSID; return (this);}
	virtual	WORD		BegCBkPrc (DWORD ulFilPos, WORD usMsgSID = 0)
						{return (FIOPolCBk (FIOPOLBEG, ulFilPos, GetCBkArg(usMsgSID)));}
	virtual	WORD		CntCBkPrc (DWORD ulFilPos, WORD *pusMsgSID = NULL);
	virtual	WORD		EndCBkPrc (DWORD ulFilPos)
						{return (FIOPolCBk (FIOPOLEND, ulFilPos, this));}

	/////////////////////////////////////////////////////////////////////////
	HWND		m_hPolWnd;				// Audio I/O poll callback window
	UINT		m_nMsgPrm;			

protected: 	
	/////////////////////////////////////////////////////////////////////////
	DWORD 		m_ulPolArg;				// Audio I/O poll callback user data
	WORD		m_usActDes;				// Audio I/O poll activity msg ID
	BOOL 		m_bfCntAct;				// Audio I/O poll poll count active
	DWORD 		m_ulTotCnt;				// Audio I/O poll total count
	DWORD 		m_ulLstTim;				// Audio I/O poll last access time
	static WORD CALLBACK EXPORT		FIOPolCBk (FIOPOL usPolReq, DWORD ulFilPos,
									CFIOCBk FAR*lpFIOCBk);
	BOOL							Is_CntAct (DWORD ulFilPos);
	BOOL							Is_PolTim ();

	/////////////////////////////////////////////////////////////////////////
	typedef enum _FIOCBK {
		FIOCBKBEG,						// Begin poll operation
		FIOCBKCNT,						// Continue poll operation
		FIOCBKPOS,						// Position poll operation
		FIOCBKEMP,						// Empty poll operation
		FIOCBKEND						// End poll operation
	} FIOCBK;

};

/////////////////////////////////////////////////////////////////////////////
// CFSECBk
/////////////////////////////////////////////////////////////////////////////
class CFSECBk
{
public:
	CFSECBk(CFIOCBk	*pFIOCBk)	{m_lpFIOCBk = pFIOCBk;}
	/////////////////////////////////////////////////////////////////////////
	// Find Sound Event callback functions
	/////////////////////////////////////////////////////////////////////////
	virtual	FIOPOLPRC	GetCBkPrc () {return ((FIOPOLPRC) FSEPolCBk);}
	virtual	CFSECBk	*	GetCBkArg (WORD usMsgSID) {m_usActDes = usMsgSID; return (this);}

	/////////////////////////////////////////////////////////////////////////
	DWORD		m_ulBegPos;				// Beginning sound byte position
	DWORD		m_ulEndPos;				// Ending sound byte position

protected: 	
	/////////////////////////////////////////////////////////////////////////
	WORD		m_usActDes;				// Audio I/O poll activity msg ID
	DWORD		m_ulTotCnt;				// Total byte count

	CFIOCBk	FAR*m_lpFIOCBk;				// File I/O callback procedure

	static WORD CALLBACK EXPORT		FSEPolCBk (WORD usPolReq, DWORD ulFilPos,
									CFSECBk FAR*lpFSECBk);

};

/////////////////////////////////////////////////////////////////////////////
// CAudFil
/////////////////////////////////////////////////////////////////////////////
class CAudFil : public CFile
{
	DECLARE_DYNAMIC(CAudFil)
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CAudFil ();
	~CAudFil ();

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	virtual WORD		IniFilOFS (CString csFilNam, FILFMT *pusFilFmt = NULL, 
						HWND hPolWnd = NULL, UINT nMsgPrm = 0, 
						CFileException* pError = NULL);
	virtual WORD		IniFilFmt (PCMTYP *pusPCMTyp, WORD *pusChnCnt, 
						DWORD *pulSmpFrq, WORD *pusEncMsk);
	virtual WORD		IniFilFmt (CAudFil *pAudFil);
	virtual	CFIOCBk   * GetFIOCBk () {return (&m_fcFIOCBk);}
	virtual	FIOPOLPRC	GetCBkPrc () {return (m_fcFIOCBk.GetCBkPrc());}
	virtual	DWORD		GetCBkArg (WORD usMsgSID = 0) 
						{return ((DWORD) m_fcFIOCBk.GetCBkArg(usMsgSID));}
	virtual BOOL		GetStatus (CFileStatus &rStatus);
	virtual	OFSTRUCT_V*	GetFilOFS ();
	virtual	MASINF	  *	GetMasInf ();
	virtual	SEGINF	  *	GetSegInf ();
	virtual	FILFMT		GetFilFmt ();
	virtual	PCMTYP		GetPCMTyp ();
	virtual	WORD		GetEncMsk ();
	virtual	WORD		GetChnCnt ();
	virtual	DWORD		GetSmpFrq ();
	virtual	DWORD		GetSmpCnt ();
	virtual	float		SmpToMSec (DWORD ulSmpPos);
	virtual	DWORD		MSecToSmp (float flTimPos);
	virtual	DWORD		SmpSmpLow (DWORD ulSmpCnt);
	virtual	BOOL		Is_FmtCmp (PCMTYP usPCMTyp, WORD usEncMsk, WORD usChnCnt, 
						DWORD ulSmpFrq, float flFrqThr = FLT_MAX);
	virtual	BOOL		Is_FmtCmp (CAudFil *pAudFil, float flFrqThr = FLT_MAX);

	/////////////////////////////////////////////////////////////////////////
	// Display window event notification
	/////////////////////////////////////////////////////////////////////////
	virtual void		AddAmpDsp (CAmpDsp *pAmpDsp) {m_pAmpDsp = pAmpDsp;}
	virtual CAmpDsp	*	AmpDspEnu (CAmpDsp *pAmpDsp = NULL); 
	virtual void		RemAmpDsp (CAmpDsp *pAmpDsp) {m_pAmpDsp = NULL;}

	/////////////////////////////////////////////////////////////////////////
	// File I/O
	/////////////////////////////////////////////////////////////////////////
	virtual	BOOL		Open (UINT nOpenFlags, CFileException* pError = NULL);
	virtual	DWORD		GetSegOff ();
	virtual	LONG		Seek (LONG lSmpOff, UINT nFrom = CFile::begin, DWORD ulGrdSmp = 0L);
	virtual	DWORD		Read (LPBYTE lpDstBuf, DWORD ulBufSiz, DWORD ulSmpCnt, DWORD *pulBytCnt = NULL, BOOL bfRawMod = FALSE);
	virtual	DWORD		Read (MXMBLK *lpMxMArr, WORD usArrLen, float flSmppGP);
	virtual	DWORD		Read (CAudEff *lpAudEff, DWORD ulSmpCnt = -1L);
	virtual	float		Read (DWORD ulSmpCnt, float flNrmLvl, float flNrmExc, 
						float flNrmMax);
	virtual	WORD		Read (DWORD ulSmpCnt, float flFrmTim, float flResTim, 
						float flSndThr, float flAtkRat, float flDcyRat, 
						float flAtkGrd, float flDcyGrd, DWORD ulHghPas, 
						DWORD *pulSndOff, DWORD *pulSndLen);
	virtual	DWORD		Write (LPBYTE lpSrcBuf, DWORD ulSmpCnt, DWORD *pulBytCnt);
	virtual	DWORD		Write (CAudEff *lpAudEff, DWORD ulSmpCnt = -1L);
	virtual	DWORD		Copy (CAudFil *pAudFil, DWORD ulSmpCnt = -1L, CFIOCBk * pFIOCBk = NULL);
	virtual	DWORD		Erase (DWORD ulSmpCnt, BOOL bfRawMod = TRUE);
	virtual	void		Close ();

protected: 	
	/////////////////////////////////////////////////////////////////////////
	// Note: Make private when MSADPCM and multi-channel are ready
	OFSTRUCT_V	m_ofFilOFS;
	/////////////////////////////////////////////////////////////////////////

private: 	
	DWORD		Read (LPBYTE lpDstBuf, DWORD ulBufSiz)
					{return (ulBufSiz ? _hread (m_hFile, lpDstBuf, ulBufSiz) : 0L);}
	DWORD		Write (LPBYTE lpDstBuf, DWORD ulBufSiz)
					{return (ulBufSiz ? _hwrite (m_hFile, lpDstBuf, ulBufSiz) : 0L);}

	MASINF		m_miMasInf;				// Master file info block
	SEGINF		m_siSegInf;				// Work segment info block
	CAmpDsp	  * m_pAmpDsp;				// Amp display update window

	CFIOCBk		m_fcFIOCBk;				// File I/O callback
	VISMEMHDL	m_hgWrkHdl;				// Work memory buffer handle
	DWORD		m_ulWrkSiz;				// Work memory buffer size
	DWORD		m_ulBytRem;				// File byte audio remaining
	ITCBLK		m_ibInpITC[PCMMAXCHN];	// File input ITC block
	ITCBLK		m_ibOutITC[PCMMAXCHN];	// File output ITC block

};
