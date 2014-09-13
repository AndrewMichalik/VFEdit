#define	new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// UndEvt.h : interface of the CUndEvt classes
//
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
#if (!defined (FIOVERNUM))
	#include "os_dev\winmem.h"			// Generic memory supp defs
	#include "fiodev\genfio.h"			// Generic File I/O definitions
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Forward references
/////////////////////////////////////////////////////////////////////////////
class	CTmpFil;

/////////////////////////////////////////////////////////////////////////////
// CRepRec
/////////////////////////////////////////////////////////////////////////////
class CRepRec : public CObject
{
public:
	CRepRec () {m_ulOrgPos = m_ulFinLen = m_ulTmpPos = m_ulOrgLen = 0L;}

	/////////////////////////////////////////////////////////////////////////
	CRepRec(const CRepRec& rr)			// Copy Constructor 
	{
		m_ulOrgPos = rr.m_ulOrgPos;
		m_ulFinLen = rr.m_ulFinLen;
		m_ulTmpPos = rr.m_ulTmpPos;
		m_ulOrgLen = rr.m_ulOrgLen;
	}
	const	CRepRec& operator=(const CRepRec& rr) 
	{
		m_ulOrgPos = rr.m_ulOrgPos;
		m_ulFinLen = rr.m_ulFinLen;
		m_ulTmpPos = rr.m_ulTmpPos;
		m_ulOrgLen = rr.m_ulOrgLen;
		return (*this);
	}
	BOOL	operator==(CRepRec rr)
	{
		return ((m_ulOrgPos == rr.m_ulOrgPos) && (m_ulFinLen == rr.m_ulFinLen) &&
				(m_ulTmpPos == rr.m_ulTmpPos) && (m_ulOrgLen == rr.m_ulOrgLen));
	}
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	DWORD		m_ulOrgPos;				// Original byte pos (inclusive)
	DWORD		m_ulFinLen;				// Final byte length
	DWORD		m_ulTmpPos;				// Event data byte pos (inclusive)
	DWORD		m_ulOrgLen;				// Event data byte length

};

/////////////////////////////////////////////////////////////////////////////
// CRepArr
/////////////////////////////////////////////////////////////////////////////
class CRepArr : public CObArray
{
public:
	CRepArr	(CString csFilNam) {m_csFilNam = csFilNam;}
	~CRepArr () {for (int ii=0; ii<GetSize(); ii++) delete GetAt(ii);}

	/////////////////////////////////////////////////////////////////////////
	WORD		Read (LPOFSTRUCT_V pofDstFil, WORD usIdx, FIOPOLPRC fpCBkPrc, 
				DWORD ulCBkArg);
	WORD		Write (LPOFSTRUCT_V pofSrcFil, DWORD ulSrcPos, DWORD ulOrgLen, 
					DWORD ulFinLen, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);	
	CRepArr	  *	Rename (const char* pszFilNam);

	// overloaded operator helpers
	CRepRec	*	operator[](int nIndex) const {return (CRepRec *) GetAt(nIndex);}
	CRepRec	*&	operator[](int nIndex) {return (CRepRec *&) ElementAt(nIndex);}

	/////////////////////////////////////////////////////////////////////////
	CString		m_csFilNam;				// File name
	CTmpFil		m_tfTmpFil;				// Undo file binary data

};

/////////////////////////////////////////////////////////////////////////////
// CUndSta: Undo event user status object
/////////////////////////////////////////////////////////////////////////////
class CUndSta : public CObject
{
	DECLARE_DYNAMIC(CUndSta)
public:
	virtual	void		UndStaSav	() {};
	virtual	void		UndStaRes	() {};
};

/////////////////////////////////////////////////////////////////////////////
// CUndEvt
/////////////////////////////////////////////////////////////////////////////
class CUndEvt : public CObject
{
public:
	/////////////////////////////////////////////////////////////////////////
	CUndEvt	(WORD usSeqNum, CString csTmpPfx, CString csDesStr, CUndSta *pNewSta = NULL);	
	~CUndEvt ();

	WORD		GetSeqNum () {return (m_usSeqNum);}
	CString		GetDesStr () {return (m_csDesStr);}
	CUndSta*	GetUndSta () {return (m_pUndSta);}
	WORD		Do (LPOFSTRUCT_V pofSrcFil, DWORD ulSrcPos, DWORD ulOrgLen, 
				DWORD ulFinLen, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);	
	WORD		Undo (LPOFSTRUCT_V pofDstFil, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);
	WORD		Redo (LPOFSTRUCT_V pofDstFil, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);

private:
	/////////////////////////////////////////////////////////////////////////
	WORD		m_usSeqNum;				// Undo file unique sequence number
	CString		m_csSeqExt;				// Undo file unique sequence string
	CString		m_csTmpPfx;				// Temporary file full prefix
	CString		m_csDesStr;				// Description string
	CUndSta*	m_pUndSta;				// New "DELETE-ABLE" undo state	object

	CRepArr	  *	m_paRepArr;				// Undo file record	array

};

/////////////////////////////////////////////////////////////////////////////
// CUndLst
/////////////////////////////////////////////////////////////////////////////
class CUndLst
{
public:
	#define		UNDMAXDEF	3

	/////////////////////////////////////////////////////////////////////////
	CUndLst ()	{m_vpUndPos = NULL; m_usUndMax = UNDMAXDEF;}
	~CUndLst ()	{ClrUndLst();}

	void		IniTmpPfx (CString csTmpPfx) {m_csTmpPfx = csTmpPfx;}
	WORD		SetUndMax (WORD usUndMax);
	POSITION	CreUndEvt (CString csDesStr, CUndSta *pNewSta = NULL);
	BOOL		GetUndDes (CString *pcsDesStr = NULL, const CUndSta **ppUndSta = NULL);
	BOOL		GetRedDes (CString *pcsDesStr = NULL, const CUndSta **ppUndSta = NULL);
	WORD		LogUndEvt (LPOFSTRUCT_V pofSrcFil, DWORD ulBytOff, DWORD ulCutByt, 
					DWORD ulPstByt, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);	
	WORD		Un_UndEvt (LPOFSTRUCT_V pofDstFil, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);
	WORD		Re_UndEvt (LPOFSTRUCT_V pofDstFil, FIOPOLPRC fpCBkPrc, DWORD ulCBkArg);
	void		DelUndEvt ();
	void		ClrUndLst ();

private:
	/////////////////////////////////////////////////////////////////////////
	BOOL		IsEmpty () const;
	CUndEvt	*	GetAt (POSITION position) const;
	CUndEvt	*	GetHead () const;
	CUndEvt	*	GetTail () const;
	CUndEvt	*	GetNext (POSITION& position) const;
	CUndEvt	*	GetPrev (POSITION& position) const;
	void		RemoveAt (POSITION position);
	void		RemoveHead ();
	void		RemoveTail ();

	/////////////////////////////////////////////////////////////////////////
	CObList		m_olUndLst;				// Undo file object list
	CString		m_csTmpPfx;				// Temporary file full prefix
	WORD		m_usUndMax;				// Maximum undo count
	POSITION	m_vpUndPos;				// Undo list current position
										// NULL == beginning of undo list



};


