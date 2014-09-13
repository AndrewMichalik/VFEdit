/////////////////////////////////////////////////////////////////////////////
// TmpFil.h : Interface of the CTmpFil classes
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
// CTmpFil
/////////////////////////////////////////////////////////////////////////////
class CTmpFil : public CFile
{
public:
	CTmpFil ();
	~CTmpFil ();
//	CTmpFil(const CTmpFil& tf)							// Copy Constructor 
//	{
//		m_ofFilOFS = tf.m_ofFilOFS;
//    	m_ctLstMod = tf.m_ctLstMod;
//		memset (&m_ofFilOFS, 0, sizeof (m_ofFilOFS));	// Remove org reference
//		m_ctLstMod = 0;
//	}
//	const CTmpFil& operator=(const CTmpFil& tf)
//	{
//		m_ofFilOFS = tf.m_ofFilOFS;
//    	m_ctLstMod = tf.m_ctLstMod; 
//		/////////////////////////////////////////////////////////////////////
//		// Remove original reference
//		// Note: m_ctLstMod	will still indicate modification level
//		/////////////////////////////////////////////////////////////////////
//		memset (&tf.m_ofFilOFS, 0, sizeof (m_ofFilOFS));
//    	return (*this);
//	}
	BOOL	operator==(CTmpFil tf)
	{
		return (!stricmp (m_ofFilOFS.szPathName, m_ofFilOFS.szPathName));
	}
	virtual WORD		IniFilOFS (const char* pszFilNam, CFileException* pError = NULL);
	virtual BOOL		Open (UINT nOpenFlags, CFileException* pError = NULL);
	virtual	void		Close () {CFile::Close();}
	virtual	long		Read (void huge *hpBuf, long lCount);
	virtual	long		Write (void huge *hpBuf, long lCount);
	virtual BOOL		Rename (const char *pszNewNam);
	static  CString		GenTmpPfx (CString csTmpDir, CString csTmpHdr);
	virtual	void		SetStatus (const CFileStatus &rStatus); 
	virtual BOOL		GetStatus (CFileStatus &rStatus) const;
	virtual BOOL		GetStatus (CFileStatus *pStatus = NULL) const;
	virtual	OFSTRUCT_V*	GetFilOFS ();
	virtual DWORD		GetLength ();
	virtual	BOOL		Remove ();
	virtual	void		SetModFlg ();
	virtual	void		ClrModFlg ();
	virtual	BOOL 		Is_ModSet ();

protected: 	

private: 	
	OFSTRUCT_V	m_ofFilOFS;				// Full path name, etc
//	CTime		m_ctLstMod;				// Last modification time

};


