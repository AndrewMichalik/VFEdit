/////////////////////////////////////////////////////////////////////////////
// AudDev.h : interface of the CAudDev classes
//
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
	#include "os_dev\winmem.h"			// Generic memory supp defs
	#include "mcidev\genmci.h" 			// Generic MCI definitions
	#include "tmidev\gentmi.h" 			// Generic TMI definitions
}

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CAudFil;
class	CTmpFil;
class	CAudEff;
class	CEffAAF;
class	CEffRes;
class	CAmpDsp;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const char	RECFILEXT[] = ".REC";		// Record  file extension	   
const char	CHDFILEXT[] = ".CHD";		// Cached  file extension	   
const int	QRYBSTFMT = -1;				// Query  best format indicator
const int	SELBSTFMT =  0;				// Select best format indicator

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CWIOCBk 
{
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CWIOCBk();	
	~CWIOCBk();	
	virtual	WORD		PlaPolIni (CAudFil *pAudFil, DWORD ulSmpOff, DWORD ulSmpCnt, 
							DWORD ulPosVec, DWORD ulLopCnt, PCMTYP usSelPCM, WORD usSelChn, 
							DWORD ulSelFrq, WORD usAAFAlg, WORD usResAlg, 
							CAmpDsp *pAmpDsp, HWND hTimWnd, DWORD ulTimArg);
	virtual	WORD		RecPolIni (CAudFil *pDstFil, DWORD ulSmpOff, DWORD ulSmpCnt, 
							CAudFil *pRecFil, BOOL bfOpnFlg, CAmpDsp *pAmpDsp,
							HWND hTimWnd, DWORD ulTimArg);
	virtual	DWORD		RecLvlChk (LPVOID lpWrkBuf, DWORD ulLvlByt, DWORD ulLvlSmp);
	virtual	DWORD		SmpPosAdj (DWORD ulSmpPos);

	static DWORD CALLBACK EXPORT	PlaPolCBk (MCIPOL usPolReq, LPVOID lpDatBuf,
									DWORD ulBufSiz, WORD usBufAct, DWORD ulSmpPos, 
									DWORD ulCBkArg);
	static DWORD CALLBACK EXPORT	RecPolCBk (MCIPOL usPolReq, LPVOID lpDatBuf,
									DWORD ulBufSiz, WORD usBufAct, DWORD ulSmpPos, 
									DWORD ulCBkArg);

	/////////////////////////////////////////////////////////////////////////
	// The following must be public for extern "C" function usage
	/////////////////////////////////////////////////////////////////////////
	#define		LVLBUFSIZ	8192		// Level meter work buffer size
	#define		LVLMINCNT	   1		// Level meter work buffer count
	#define		LVLMAXCNT	   1		// Level meter work buffer count
	VISMEMHDL	m_hgLvlHdl;				// Level meter buffer handle
	DWORD		m_ulLvlSiz;				// Level meter buffer size
	DWORD		m_ulLvlByt;				// Level meter active byte count

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
protected: 	
	virtual	DWORD		LodMemBuf (LPVOID lpDstBuf, DWORD ulBufSiz);

	typedef enum _WIOCBK {
		WIOCBKBEG,						// Begin poll operation	 
		WIOCBKCNT,						// Continue poll operation 
		WIOCBKPOS,						// Position poll operation 
		WIOCBKEMP,						// Empty poll operation 
		WIOCBKEND						// End poll operation	  
	} WIOCBK;

	CEffInp	*	m_pEffInp;				// Effect: File Input
	CEffAAF	*	m_pEffAAF;				// Effect: anti-aliasing filter
	CEffRes	*	m_pEffRes;				// Effect: resample 
	CEffAtD	*	m_pEffAtD;				// Effect: A to D normalize

	BOOL		m_bfRawMod;				// Raw PCM transfer mode indicator
	DWORD		m_ulPosVec;				// Offset vector sample position
	DWORD		m_ulLopMod;				// Loop sample modulos

	CAmpDsp	*	m_pAmpDsp;				// Audio I/O cursor display
	HWND		m_hTimWnd;				// Audio I/O time callback window
	DWORD 		m_ulTimArg;				// Audio I/O time callback user data

	CAudFil	*	m_pRecFil;				// Rec tempory storage file
	DWORD		m_ulSmpOff;				// Rec destination sample offset
	DWORD		m_ulDstFrq;				// Rec destination frequency
	DWORD		m_ulBytReq;				// Rec bytes remaining

	PCMTYP		m_usPCMTyp;				// Device selected PCM Type
	ITCBLK		m_ibITCBlk[PCMMAXCHN];	// Device ITC block

};

class CAudDev
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
public:
	typedef enum _CTLPRO {
		UNKCTLPRO = 0x0000,				// Audio Device = Unknown
		TMIDIGPRO = 0x1000,				// Audio Device = TMI Digitizer
		MCIMDIPRO = 0x2000,				// Audio Device = MCI MIDI 
		MCIWAVPRO = 0x4000,				// Audio Device = MCI Wave 
		MAXCTLPRO						// Maximum # entries
	} CTLPRO;
	#define	CTLPROTYP(x)	((x) & 0xf000)	// Control protocol type
	#define	CTLPRODIR(x)	((x) & 0x0f00)	// Control protocol direction

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CAudDev(); 
	~CAudDev();
	virtual	BOOL		SelBstFmt (CAudFil *pAudFil, WORD usCtlPro, float flCvtVec);

	/////////////////////////////////////////////////////////////////////////
	// The following must be public for extern "C" function usage
	/////////////////////////////////////////////////////////////////////////
	VISMEMHDL	m_hgWrkHdl;				// Work memory buffer handle
	DWORD		m_ulWrkSiz;				// Work memory buffer size

	WORD		m_usCtlPro;				// Audio device control protocol
	PCMTYP		m_usSelPCM;				// Selected device PCM Type
	WORD		m_usSelChn;				// Selected device channel count
	DWORD 		m_ulSelFrq;				// Selected device sample frequency 
	WORD		m_usSelMsk;				// Selected device encoding mask
	PCMTYP		m_usDefPCM;				// Default device PCM Type
	WORD		m_usDefChn;				// Default device channel count
	DWORD 		m_ulDefFrq;				// Default device sample frequency 

	VISMEMHDL	m_mhSysRes;				// Audio system resource	
	VISMEMHDL	m_mhDevRes;				// Audio device resource	
	WORD		m_usLinNum;				// Audio device line number
	HWND		m_hCBkWnd;				// Audio device event callback

	CString		m_csTmpPfx;				// Temporary file full prefix
	CTmpFil		m_tfRecFil;				// Recorded data file
	CAudFil		m_afRecFil;				// Recorded data file
	CTmpFil		m_tfChdFil;				// Cached   data file

	CWIOCBk	*	m_pWIOCBk;				// Audio I/O callback

protected: 	

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

};


