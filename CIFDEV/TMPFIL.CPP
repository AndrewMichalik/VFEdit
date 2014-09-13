/////////////////////////////////////////////////////////////////////////////
// TmpFil.cpp : Implementation of the CTmpFil classes
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs

#include "tmpfil.h"						// Temp file support defs

extern "C"
{
	#include "os_dev\winmsg.h"			// User message support
	#include <direct.h>					// DOS file/directory operations
	#include <stdlib.h>					// Misc string/math/error funcs
	#include <dos.h>					// DOS low-level routines
}

/////////////////////////////////////////////////////////////////////////////
//						External References
/////////////////////////////////////////////////////////////////////////////
extern  CIFGLO  CIFGlo;					// C Interface Library Globals

/////////////////////////////////////////////////////////////////////////////
// CTmpFil
/////////////////////////////////////////////////////////////////////////////
CTmpFil::CTmpFil()
{
	memset (&m_ofFilOFS, 0, sizeof (m_ofFilOFS));
//	m_ctLstMod = 0;
}

CTmpFil::~CTmpFil()
{
	Remove();
}

WORD	CTmpFil::IniFilOFS (const char *pszFilNam, CFileException* pError)
{
	
	/////////////////////////////////////////////////////////////////////////
	// IDS_TMPCREERR: "Error creating temporary work file: %1"
	/////////////////////////////////////////////////////////////////////////
	if (HFILE_ERROR == FIOOFSOpn (pszFilNam, &m_ofFilOFS, OF_CREATE | OF_EXIST | OF_READWRITE)) {
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPCREERR, (LPCSTR) pszFilNam);
		// try to recover by creating generated tmp
		// pszFilNam = GenTmpPfx (NULL, NULL);
		// if (HFILE_ERROR == FIOOFSOpn (pszFilNam, &m_ofFilOFS, OF_CREATE | OF_EXIST | OF_READWRITE))
		return (IDS_TMPCREERR);
		// MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPCREREP, (LPCSTR) pszFilNam);
	}
	ClrModFlg ();

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (0);

}

BOOL		CTmpFil::Open (UINT nOpenFlags, CFileException* pError)
{
	return (CFile::Open(m_ofFilOFS.szPathName, nOpenFlags, pError));
}

long		CTmpFil::Read (void huge * hpBuf, long lCount)
{
	return (_hread (m_hFile, hpBuf, lCount));
}

long		CTmpFil::Write (void huge * hpBuf, long lCount)
{
	return (_hwrite (m_hFile, hpBuf, lCount));
}

BOOL	CTmpFil::Rename(const char *pszNewNam)
{
	CString	csFulPth;
	char    szSrcDrv[_MAX_DRIVE], szSrcDir[_MAX_DIR]; 
	char    szSrcNam[_MAX_FNAME], szSrcExt[_MAX_EXT];
	char    szDstDrv[_MAX_DRIVE], szDstDir[_MAX_DIR]; 
	char    szDstNam[_MAX_FNAME], szDstExt[_MAX_EXT];

	/////////////////////////////////////////////////////////////////////////
	if (!strlen (m_ofFilOFS.szPathName)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	// Split names of source and destination files
	// Note: Rename ignores new path specification
	/////////////////////////////////////////////////////////////////////////
	_splitpath (m_ofFilOFS.szPathName, szSrcDrv, szSrcDir, szSrcNam, szSrcExt);
	_splitpath (pszNewNam, szDstDrv, szDstDir, szDstNam, szDstExt);

	/////////////////////////////////////////////////////////////////////////
	TRY 
	{
		CFile::Rename (m_ofFilOFS.szPathName, (CString) szSrcDrv + (CString) szSrcDir + (CString) szDstNam + (CString) szDstExt);
	}
	/////////////////////////////////////////////////////////////////////////
	// IDS_TMPRENERR: "Error renaming temporary work file: %1"
	/////////////////////////////////////////////////////////////////////////
	CATCH (CFileException, e)
	{
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPRENERR, (LPCSTR) m_ofFilOFS.szPathName);
		return (TRUE);
	}
	END_CATCH

	/////////////////////////////////////////////////////////////////////////
	// Re-build full path name
	/////////////////////////////////////////////////////////////////////////
	_makepath (csFulPth.GetBuffer (_MAX_PATH), szSrcDrv, szSrcDir, szDstNam, szDstExt); 
	csFulPth.ReleaseBuffer();

	/////////////////////////////////////////////////////////////////////////
	// Re-open file to reset OFS
	/////////////////////////////////////////////////////////////////////////
	if (HFILE_ERROR == FIOOFSOpn (csFulPth, &m_ofFilOFS, OF_EXIST)) {
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPRENERR, (LPCSTR) m_ofFilOFS.szPathName);
		return (TRUE);
	}

	/////////////////////////////////////////////////////////////////////////
	return (FALSE);

}

CString	CTmpFil::GenTmpPfx (CString csTmpDir, CString csTmpHdr)
{
	char *	pcTmpNam;		 

	/////////////////////////////////////////////////////////////////////////
	// Use current working directory if csTmpDir is empty
	// Insure that directory name in properly terminated
	/////////////////////////////////////////////////////////////////////////
	if (csTmpDir.IsEmpty()) {
		csTmpDir = (pcTmpNam = _getdcwd (0, NULL, _MAX_PATH));
		free (pcTmpNam);
	}		
	/////////////////////////////////////////////////////////////////////////
	// Insure that directory name in properly terminated
	// Keep final slash for current root and drive root directory 
	/////////////////////////////////////////////////////////////////////////
	if ((csTmpDir.Right(1) == "\\") && (csTmpDir.GetLength() > 1)  
	  && (csTmpDir.Right(2) != ":\\")) 
		csTmpDir = csTmpDir.Left(csTmpDir.GetLength() - 1);
	
	/////////////////////////////////////////////////////////////////////////
	// Set full path, prefix and generate unique file name
	// IDS_TMPCREERR: "Error creating temporary work file: %1"
	/////////////////////////////////////////////////////////////////////////
	pcTmpNam = _tempnam (csTmpDir.GetBuffer(_MAX_PATH), csTmpHdr.GetBuffer(_MAX_PATH));
	csTmpDir.ReleaseBuffer();
	csTmpHdr.ReleaseBuffer();
	if (NULL == pcTmpNam) {
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPCREERR, (LPCSTR) (csTmpDir + csTmpHdr));
		return ("");
	}
	csTmpDir = pcTmpNam;
	free (pcTmpNam);

	/////////////////////////////////////////////////////////////////////////
	return (csTmpDir);

}

BOOL		CTmpFil::GetStatus (CFileStatus &rStatus) const
{
	return (CFile::GetStatus (m_ofFilOFS.szPathName, rStatus));
}

BOOL		CTmpFil::GetStatus (CFileStatus *pStatus) const
{
	CFileStatus fsTmpSta;
	if (!pStatus) pStatus = &fsTmpSta;
	return (CFile::GetStatus (m_ofFilOFS.szPathName, *pStatus));
}

void		CTmpFil::SetStatus (const CFileStatus &rStatus) 
{
	TRY 
	{
		CFile::SetStatus (m_ofFilOFS.szPathName, rStatus);
	}
	CATCH (CFileException, e)
	{
		return;
	}
	END_CATCH
}

OFSTRUCT_V*	CTmpFil::GetFilOFS ()
{
	return (&m_ofFilOFS); 
}

DWORD		CTmpFil::GetLength ()
{
	CFileStatus	fsFilSta;
	if (!GetStatus (fsFilSta)) return (0L);
	return ((DWORD) fsFilSta.m_size);
}

BOOL	CTmpFil::Remove()
{
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!strlen (m_ofFilOFS.szPathName)) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	TRY 
	{
		CFile::Remove (m_ofFilOFS.szPathName);
	}
	/////////////////////////////////////////////////////////////////////////
	// IDS_TMPDELERR: "Error deleting temporary work file: %1"
	/////////////////////////////////////////////////////////////////////////
	CATCH (CFileException, e)
	{
		MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_TMPDELERR, (LPCSTR) m_ofFilOFS.szPathName);
		return (TRUE);
	}
	END_CATCH

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	memset (&m_ofFilOFS, 0, sizeof (m_ofFilOFS));
	return (FALSE);

}

void	CTmpFil::SetModFlg () 
{
	CFileStatus	fsFilSta;

// Initialize m_mtime to zero to prevent side effects
if (!GetStatus (fsFilSta)) return;
fsFilSta.m_mtime = 0;

// set archive bit
fsFilSta.m_attribute |= _A_ARCH;
SetStatus (fsFilSta);
return;

}

void	CTmpFil::ClrModFlg ()
{
	CFileStatus	fsFilSta;

// Initialize m_mtime to zero to prevent side effects
if (!GetStatus (fsFilSta)) return;
fsFilSta.m_mtime = 0;

// clear archive bit
fsFilSta.m_attribute &= ~_A_ARCH;
SetStatus (fsFilSta);
return;

	/////////////////////////////////////////////////////////////////////////
	// Warning: Must use file size as well as date since it is possible to 
	// very quickly create a file, then write a small amount of data - all
	// within the 1 second resolution of m_mtime.
	// Future: may need to abandon this method of detection modification!
	/////////////////////////////////////////////////////////////////////////
//	CFileStatus	fsFilSta;
//	m_ctLstMod = GetStatus (fsFilSta) ? fsFilSta.m_mtime : 0;
//	return;
}

BOOL	CTmpFil::Is_ModSet ()
{
	CFileStatus	fsFilSta;
	return (GetStatus (fsFilSta) ? _A_ARCH & fsFilSta.m_attribute : FALSE);

//	return (m_ctLstMod != (GetStatus (fsFilSta) ? fsFilSta.m_mtime : 0));
}


