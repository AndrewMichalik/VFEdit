/////////////////////////////////////////////////////////////////////////////
// EffFrq.h : Interface  of the CAudEff frequency classes
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#define FFTORDDEF	9					// FFT order default

/////////////////////////////////////////////////////////////////////////////
// CFrqEff
// Frequency specific Audio effects stream 
/////////////////////////////////////////////////////////////////////////////
class CFrqEff : public CAudEff
{
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

protected: 	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	static WORD CALLBACK EXPORT	FrqEffCBk (float FAR * FAR *ppflSrcBuf, 
		   						DWORD FAR *lpulDstRsv, DWORD ulBufPts, 
		   						DWORD ulTotPts, DWORD ulHdrPts, DWORD ulCtrPts,
		   						DWORD ulDstRem, LPFFTB lpFFTBlk);
	FFTBLK		m_fbFFTBlk;				// FFT Filter repeated call blk

private: 	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CEffAAF : public CFrqEff
{
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	typedef enum _AAFALG {
		AAFALGUNK = 0,					// Unknown
		AAFALGNON = 1,					// Anti-aliasing off
		AAFALGFST = 2,					// Anti-aliasing fast   (2 IIR int)
		AAFALGNRM = 3,					// Anti-aliasing normal	(2 IIR float)
		AAFALG6II = 4,					// Anti-aliasing normal	(6 IIR int)
		AAFALG6IF = 5,					// Anti-aliasing normal	(6 IIR float)
		AAFALGFFT = 6,					// Anti-aliasing FFT FIR
	} AAFALG;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CEffAAF (DWORD ulLowPas, DWORD ulSmpFrq, AAFALG usAAFAlg);
	~CEffAAF ();

	virtual	CAudEff	*	ExeEffPrc (CAudEff *pAudEff);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
private: 	
	#define AAFPASFAC (float) 0.3		// IIR low-pass pass bnd factor
	#define AAFSTPATT		 40			// IIR low-pass stop bnd atten 
	#define Q2_SECCNT		  2			// IIR low-pass section count  
	#define Q2_SECORD		  1			// IIR low-pass filter length  
	#define Q6_SECCNT		  3			// IIR low-pass section count  
	#define Q6_SECORD		  2			// IIR low-pass filter length  

	BOOL						FtrIIR (DWORD ulLowPas, DWORD ulSmpFrq, 
								AAFALG usAAFAlg);
	BOOL						FtrFFT (DWORD ulLowPas, DWORD ulSmpFrq, 
								AAFALG usAAFAlg);

	TDOFTR		m_tfTDoFtr;				// F2P Filter repeated call blk 
	AAFALG		m_usAAFAlg;				// Anti-aliasing filter type

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CEffDTM : public CFrqEff
{
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	typedef enum _DTMALG {
		DTMALGUNK = 0,					// Unknown
		DTMALGNON = 1,					// DTMF filtering off
		DTMALGFFT = 2,					// DTMF FFT FIR
	} DTMALG;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CEffDTM(DWORD ulSmpFrq, DTMALG usDTMAlg);
	~CEffDTM ();

	virtual	CAudEff	*	ExeEffPrc (CAudEff *pAudEff);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
private: 	
	#define NCHFTRMAX   32
	typedef struct _NCHFTR {			// Notch filter	frequencies
		WORD	usFrqCnt;
		DWORD   ulNchFrq[NCHFTRMAX];
	} NCHFTR;   

	DTMALG		m_usDTMAlg;				// DTMF filter type

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CEffRes : public CFrqEff
{
public:
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	typedef enum _RESALG {
		RESALGUNK = 0,					// Unknown
		RESALGNON = 1,					// Resampling off
		RESALGFST = 2,					// Resampling fast (sample skip)
		RESALGNRM = 3,					// Resampling normal (linear)
		RESALGFFT = 4,					// Resampling FFT
	} RESALG;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CEffRes (DWORD ulSrcFrq, DWORD ulDstFrq, RESALG usResAlg);
	~CEffRes ();

	virtual	CAudEff	*	ExeEffPrc (CAudEff *pAudEff);

	virtual	DWORD		SrcSizEst (DWORD ulDstSmp, DWORD ulSrcFrq);
	virtual	DWORD		DstSizEst (DWORD ulSrcSmp, DWORD ulSrcFrq);
	virtual	float		SmpToMSec (DWORD ulSmpPos);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
private: 	
	DWORD 		m_ulDstFrq;				// Output sample frequency 
	RESALG		m_usResAlg;				// Resampling algorithm
	RESBLK		m_rbResBlk;  			// Int/Dec repeated call block	
	EBSBLK		m_ebEBSFFT;				// FFT resample EBS  

};


