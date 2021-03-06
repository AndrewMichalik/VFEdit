/////////////////////////////////////////////////////////////////////////////
// vfecif.cpp : VFECIF.DLL implementation and initialization code.
// Copyright (c) 1987-1996 Andrew J. Michalik
/////////////////////////////////////////////////////////////////////////////
#include "gencif.h"						// Generic C I/F application defs
#include "vfecif.h"						// VFEdit C I/F application defs

extern "C"
{
	#include "regdev\vfereg.h"			// User Registration defs
	#include "os_dev\winmsg.h"			// User message support

	#include "os_dev\winmem.h"			// Generic memory supp defs
	#include "ampdev\genamp.h"			// Waveform Display defs
	#include "effdev\geneff.h"			// Sound Effects definitions
	#include "fiodev\genfio.h"			// Generic File I/O definitions
	#include "mcidev\genmci.h" 			// Generic MCI definitions
	#include "pcmdev\genpcm.h"			// PCM/APCM conv routine defs
	#include "tmidev\gentmi.h" 			// Generic TMI definitions

	#include <direct.h>					// DOS file/directory operations
}

#include "audfil.h"						// Audio file support defs
#include "tmpfil.h"						// Temp file support defs

/////////////////////////////////////////////////////////////////////////////
//				Global Data Structures Definitions
/////////////////////////////////////////////////////////////////////////////
CIFGLO CIFGlo = {						// C I/F Library Globals		
	"C Interface",						// Library name				
	{'s','r','0','0','5','a','c','0'},	// Operating/Demo Only Key	 
//	{'t','b','7','0','p','7','c','0'},  /* Evaluation Key: 11/01/96 
//	{'s','r','0','0','v','5','c','0'},  /* License Seq Key: S/N 1000        */
//	{'d','b','c','0','d','b','c','0'},  /* Master Key
	{'1','0','0','0'},					// Op/Demo sequence number	 
	{'0','0','0','0'},					// Security check sum			
	REGDEMKEY,							// usRegKey					
	DEMOPNCNT,							// Demo limit remaining
	FALSE,								// Debug errors flag			
	NULL,								// Global instance handle		
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const char	CLPFILPRE[] = "V_AC";		// clipboard file prefix
const char	CLPFILEXT[] = ".CLP";		// clipboard file extension		   

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int WINAPI  CIFDspPrc (HWND, LPCSTR, LPCSTR, UINT);

/////////////////////////////////////////////////////////////////////////////
// Library init
/////////////////////////////////////////////////////////////////////////////
BOOL	CVFECIF::InitInstance()
{
	/////////////////////////////////////////////////////////////////////////
	TRACE ("VFECIF.DLL initializing\n");

	/////////////////////////////////////////////////////////////////////////
	// Initialize support DLL's
	/////////////////////////////////////////////////////////////////////////
	AmpDLLIni (0, 0L, 0L);
	FIODLLIni (0, 0L, 0L);
	MCIDLLIni (0, 0L, 0L);
	PCMDLLIni (0, 0L, (DWORD) (LPVOID) "t2c09p03");
	TMIDLLIni (0, 0L, 0L);

	/////////////////////////////////////////////////////////////////////////
	CIFGlo.hLibIns = AfxGetInstanceHandle();
	SetDialogBkColor();					// grey dialogs in the DLL as well
    MsgDspPrc = CIFDspPrc;				// Re-assignable msg output

	/////////////////////////////////////////////////////////////////////////
	return TRUE;
}

int 	CVFECIF::ExitInstance()
{
	/////////////////////////////////////////////////////////////////////////
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Create instance
/////////////////////////////////////////////////////////////////////////////
CVFECIF	vfecif ("vfecif.dll");

/////////////////////////////////////////////////////////////////////////////
// Message display support
/////////////////////////////////////////////////////////////////////////////
int	FAR PASCAL _export CIFDspPrc (HWND hWnd, LPCSTR lpMsgTxt, LPCSTR lpTtlTxt, UINT uiStyFlg)
{
    return (MessageBox (hWnd, lpMsgTxt, CIFGlo.szLibNam, uiStyFlg));
}
int	CDECL	CIFDspRes (WORD usTypFlg, WORD usMsgSID)
{
	return (MsgDspRes (CIFGlo.hLibIns, usTypFlg, usMsgSID));
}

extern "C"
DWORD FAR PASCAL _export CIFOS_Inf (OSVERSIONINFO FAR *lpVerInf)
{
    OSVERSIONINFO	osVerInf;

	/////////////////////////////////////////////////////////////////////////
	// Copy full info if requested; otherwise, just return platform ID	
	/////////////////////////////////////////////////////////////////////////
	if (NULL == lpVerInf) lpVerInf = &osVerInf;
	FIOOS_Inf (lpVerInf);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (lpVerInf->dwPlatformId);
}

/////////////////////////////////////////////////////////////////////////////
// Public C interface
/////////////////////////////////////////////////////////////////////////////
extern "C"
WORD FAR PASCAL _export	CIFDLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{
	WORD	usCmpCod;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	GlobalCompact (0);

	/////////////////////////////////////////////////////////////////////////
	// If (CIFINIREQ == usReqTyp), check for accelerator key
	/////////////////////////////////////////////////////////////////////////
	if ((CIFSYSINI == usReqTyp) && (!ulPrm002 || !strlen ((LPSTR) ulPrm002))) {
		/////////////////////////////////////////////////////////////////////
		// Check for accelerator key and/or AppKey/UsrKey combo
		/////////////////////////////////////////////////////////////////////
		if (REGDEMKEY == ChkRegKey (CIFGlo.RelKeyArr, CIFGlo.SeqNumArr, &usCmpCod)) {
			switch (usCmpCod) {
				case 0xFFFE:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_INSMEMERR);
					break;
				case 0xFFFD:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_DOSMEMERR);
					break;
				default:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_ACCKEYNON);
			} 
			return ((WORD) -1);
		} 
		/////////////////////////////////////////////////////////////////////
		// Load registration key from physical key [1] or string
		/////////////////////////////////////////////////////////////////////
		if (!usCmpCod) CIFGlo.usRegKey = GetEncKey (CIFGlo.SeqNumArr, 1, &usCmpCod);
 		else CIFGlo.usRegKey = ChkRegKey (CIFGlo.RelKeyArr, CIFGlo.SeqNumArr, &usCmpCod);
	}
	if ((CIFSYSINI == usReqTyp) && ulPrm002 && strlen ((LPSTR) ulPrm002)) {
		CIFGlo.usRegKey = ChkRegKey ((LPSTR) ulPrm002, CIFGlo.SeqNumArr, &usCmpCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// If (0 != usReqTyp), initialize internal structures and DLL's
	/////////////////////////////////////////////////////////////////////////
	if (CIFSUBINI == usReqTyp) {
		AmpDLLIni (usReqTyp, ulPrm001, ulPrm002); 
	}

	/********************************************************************/
	/********************************************************************/
	return (0);

}

extern "C"
WORD FAR PASCAL _export CIFSupVer ()
{
	/********************************************************************/
	/********************************************************************/
	return (CIFVERNUM);
}

extern "C"
WORD FAR PASCAL _export CIFLodStr (WORD usMsgSID, LPSTR szMsgTxt, WORD usMaxLen)
{

    /********************************************************************/
    /* Retrieve a C I/F specific message                              */
    /********************************************************************/
	return (LoadString (CIFGlo.hLibIns, usMsgSID, szMsgTxt, usMaxLen));

}

extern "C"
WORD FAR PASCAL _export CIFSupVerEnu (WORD FAR *pusSupTyp, WORD FAR *pusSupVer, LPSTR szDesStr, WORD usMaxLen)
{
	CString csWrkStr;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	const 	int	CIFDLLSUP = 0;
	const 	int	AMPDLLSUP = 1;
	const 	int	EFFDLLSUP = 2;
	const 	int	FIODLLSUP = 3;
	const 	int	MCIDLLSUP = 4;
	const 	int	PCMDLLSUP = 5;
	const 	int	TMIDLLSUP = 6;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if (!usMaxLen) return (FALSE);

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	switch (*pusSupTyp) {
		case CIFDLLSUP:
			if (!csWrkStr.LoadString(IDS_CIFDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = CIFVERNUM;
		   	break;
		case AMPDLLSUP:
			if (!csWrkStr.LoadString(IDS_AMPDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = AmpSupVer ();
			if (AMPVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		case EFFDLLSUP:
			if (!csWrkStr.LoadString(IDS_EFFDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = EffSupVer ();
			if (EFFVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		case FIODLLSUP:
			if (!csWrkStr.LoadString(IDS_FIODLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = FIOSupVer ();
			if (FIOVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		case MCIDLLSUP:
			if (!csWrkStr.LoadString(IDS_MCIDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = MCISupVer ();
			if (MCIVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		case PCMDLLSUP:
			if (!csWrkStr.LoadString(IDS_PCMDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = PCMSupVer ();
			if (PCMVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		case TMIDLLSUP:
			if (!csWrkStr.LoadString(IDS_TMIDLLSUP)) return (FALSE);
			strncpy (szDesStr, csWrkStr, usMaxLen);
			*pusSupVer = TMISupVer ();
			if (TMIVERNUM != *pusSupVer)
				MsgDspRes (CIFGlo.hLibIns, MB_OK, IDS_MODVERMIS, (LPCSTR) szDesStr);
		   	break;
		default:
			return (FALSE);
	}
	(*pusSupTyp)++;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////
//						Accelerator key support
/////////////////////////////////////////////////////////////////////////////
extern "C"
{
	#define ERR___DEB		0x0002			// Debug error messages flag
	#define KEY___DEB		0x0008			// Debug key flag			
	#define MEM___DEB		0x0020			// Debug memory messages fla
	#define CFG___DEB		0x0080			// Debug config settings fla
	#define INI___DEB		0x0200			// Debug init	settings fla

	#define TBxGlo			CIFGlo
	#define TBXMAXSTR		CIFMAXSTR
	#include "regdev\vfereg.c"				// User Registration code	

	#define _hInst			CIFGlo.hLibIns	
	#include "regdev\kescb.c"				// Registration key code	
}


