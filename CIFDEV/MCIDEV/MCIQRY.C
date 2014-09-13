/************************************************************************/
/* Media Control Query: MCIQry.c                        V2.00  07/15/94 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "mmsystem.h"                   /* Windows Multi Media defs     */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "..\pcmdev\genpcm.h"           /* PCM/APCM conv routine defs   */
#include "..\effdev\geneff.h"           /* Sound Effects definitions    */
#include "genmci.h"                     /* Generic MCI definitions      */
#include "mcisup.h"                     /* MCI support definitions      */
#include "mciwav.h"                     /* MCI wave definitions         */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  MCIGLO  MCIGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
MCIPRO  FAR PASCAL  MCIWavEnu (MCIPRO usMCIPro, LPSTR szDesStr, WORD usMaxLen)
{
    MCI_SYSINFO_PARMS   siSysInf;
    DWORD               ulWavFmt;

// Dialogic drivers return only one device, making this technique useless. 
//    DWORD               dwDevices;
//    /********************************************************************/
//    /* Any Wave devices available?                                      */
//    /* Note: this returns number listed, not necessarily functional     */
//    /********************************************************************/
//    _fmemset (&siSysInf, 0, sizeof (siSysInf));
//    siSysInf.lpstrReturn = (LPSTR) (DWORD FAR *) &dwDevices;
//    siSysInf.dwRetSize = sizeof (dwDevices);
//    siSysInf.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO;
//    if (mciSendCommand (NULL, MCI_SYSINFO, MCI_SYSINFO_QUANTITY,  
//        (DWORD) (LPVOID) &siSysInf)) return (0);
//    if (dwDevices <= (DWORD) WAVDEV_ID(usMCIPro)) return (0);

    /********************************************************************/
    /* Stop looking if this device has no input or output capabilities. */
    /********************************************************************/
    if (GetDevCap (usMCIPro | MCIPROINP, &ulWavFmt) 
        && GetDevCap (usMCIPro | MCIPROOUT, &ulWavFmt)) return (0);

    /********************************************************************/
    /* Get "aggregate" input/output product name if available           */
    /********************************************************************/
    if (GetDevNam (usMCIPro, szDesStr, usMaxLen)) return (usMCIPro + 1);

    /********************************************************************/
    /* Get "generic" device name if product name not available          */
    /********************************************************************/
    siSysInf.lpstrReturn = szDesStr;
    siSysInf.dwRetSize = usMaxLen;
    siSysInf.dwNumber = WAVDEV_ID(usMCIPro) + 1;
    if (!mciSendCommand (NULL, MCI_SYSINFO, MCI_SYSINFO_NAME,  
        (DWORD) (LPMCI_SYSINFO_PARMS) &siSysInf)) return (usMCIPro + 1);

    /********************************************************************/
    /* Bad device ID; stop looking                                      */
    /********************************************************************/
    return (0);
}

PCMTYP  FAR PASCAL  MCIPCMEnu (MCIPRO usMCIPro, PCMTYP usPCMTyp)
{
    DWORD       ulWavFmt;

    /********************************************************************/
    /********************************************************************/
    if (GetDevCap (usMCIPro, &ulWavFmt)) return (0);

    /********************************************************************/
    /* Check non-standard & standard PCM types                          */
    /********************************************************************/
    if ((usPCMTyp < DLGPCM004) && (
        MCICapQry (usMCIPro, DLGPCM004, 1, 6000L) ||
        MCICapQry (usMCIPro, DLGPCM004, 1, 8000L))) return (DLGPCM004);

    if ((usPCMTyp < DLGPCM008) && (
        MCICapQry (usMCIPro, DLGPCM008, 1, 6000L) ||
        MCICapQry (usMCIPro, DLGPCM008, 1, 8000L))) return (DLGPCM008);

    if ((usPCMTyp < G11PCMF08) && (
        MCICapQry (usMCIPro, G11PCMF08, 1, 6000L) ||
        MCICapQry (usMCIPro, G11PCMF08, 1, 8000L))) return (G11PCMF08);

    if ((usPCMTyp < G11PCMI08) && (
        MCICapQry (usMCIPro, G11PCMI08, 1, 6000L) ||
        MCICapQry (usMCIPro, G11PCMI08, 1, 8000L))) return (G11PCMI08);

    if ((usPCMTyp < MPCPCM008) && (
        (ulWavFmt & WAVE_FORMAT_1M08) ||
        (ulWavFmt & WAVE_FORMAT_1S08) ||
        (ulWavFmt & WAVE_FORMAT_2M08) ||
        (ulWavFmt & WAVE_FORMAT_2S08) ||
        (ulWavFmt & WAVE_FORMAT_4M08) ||
        (ulWavFmt & WAVE_FORMAT_4S08))) return (MPCPCM008);

    if ((usPCMTyp < MPCPCM016) && (
        (ulWavFmt & WAVE_FORMAT_1M16) ||
        (ulWavFmt & WAVE_FORMAT_1S16) ||
        (ulWavFmt & WAVE_FORMAT_2M16) ||
        (ulWavFmt & WAVE_FORMAT_2S16) ||
        (ulWavFmt & WAVE_FORMAT_4M16) ||
        (ulWavFmt & WAVE_FORMAT_4S16))) return (MPCPCM016);

    /********************************************************************/
    /********************************************************************/
    return (0);
}

WORD    FAR PASCAL  MCIChnEnu (MCIPRO usMCIPro, PCMTYP usPCMTyp, WORD usChnCnt)
{
    DWORD       ulWavFmt;

    /********************************************************************/
    /********************************************************************/
    if (GetDevCap (usMCIPro, &ulWavFmt)) return (0);

    /********************************************************************/
    /********************************************************************/
    switch (usPCMTyp) {
        case MPCPCM008:
            if ((usChnCnt < 1) && (
                (ulWavFmt & WAVE_FORMAT_1M08) || 
                (ulWavFmt & WAVE_FORMAT_2M08) || 
                (ulWavFmt & WAVE_FORMAT_4M08))) return (1);
            if ((usChnCnt < 2) && (
                (ulWavFmt & WAVE_FORMAT_1S08) || 
                (ulWavFmt & WAVE_FORMAT_2S08) || 
                (ulWavFmt & WAVE_FORMAT_4S08))) return (2);
            break;
        case MPCPCM016:
            if ((usChnCnt < 1) && (
                (ulWavFmt & WAVE_FORMAT_1M16) || 
                (ulWavFmt & WAVE_FORMAT_2M16) || 
                (ulWavFmt & WAVE_FORMAT_4M16))) return (1);
            if ((usChnCnt < 2) && (
                (ulWavFmt & WAVE_FORMAT_1S16) || 
                (ulWavFmt & WAVE_FORMAT_2S16) || 
                (ulWavFmt & WAVE_FORMAT_4S16))) return (2);
            break;
    }

    /********************************************************************/
    /********************************************************************/
    return (0);
}

DWORD   FAR PASCAL  MCIFrqEnu (MCIPRO usMCIPro, PCMTYP usPCMTyp, 
                    WORD usChnCnt, DWORD ulSmpFrq)
{
    DWORD       ulWavFmt;

    /********************************************************************/
    /********************************************************************/
    if (GetDevCap (usMCIPro, &ulWavFmt)) return (0);

    /********************************************************************/
    /********************************************************************/
    switch (usPCMTyp) {
        case DLGPCM004: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, DLGPCM004, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, DLGPCM004, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (MCICapQry (usMCIPro, DLGPCM004, 1, 11025L))) return (11025L);
            if ((ulSmpFrq < 22050L) && (MCICapQry (usMCIPro, DLGPCM004, 1, 22050L))) return (22050L);
            if ((ulSmpFrq < 44100L) && (MCICapQry (usMCIPro, DLGPCM004, 1, 44100L))) return (44100L);
            break;
        }
        break;
        case DLGPCM008: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, DLGPCM008, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, DLGPCM008, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (MCICapQry (usMCIPro, DLGPCM008, 1, 11025L))) return (11025L);
            if ((ulSmpFrq < 22050L) && (MCICapQry (usMCIPro, DLGPCM008, 1, 22050L))) return (22050L);
            if ((ulSmpFrq < 44100L) && (MCICapQry (usMCIPro, DLGPCM008, 1, 44100L))) return (44100L);
            break;
        }
        break;
        case G11PCMF08: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, G11PCMF08, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, G11PCMF08, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (MCICapQry (usMCIPro, G11PCMF08, 1, 11025L))) return (11025L);
            if ((ulSmpFrq < 22050L) && (MCICapQry (usMCIPro, G11PCMF08, 1, 22050L))) return (22050L);
            if ((ulSmpFrq < 44100L) && (MCICapQry (usMCIPro, G11PCMF08, 1, 44100L))) return (44100L);
            break;
        }
        break;
        case G11PCMI08: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, G11PCMI08, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, G11PCMI08, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (MCICapQry (usMCIPro, G11PCMI08, 1, 11025L))) return (11025L);
            if ((ulSmpFrq < 22050L) && (MCICapQry (usMCIPro, G11PCMI08, 1, 22050L))) return (22050L);
            if ((ulSmpFrq < 44100L) && (MCICapQry (usMCIPro, G11PCMI08, 1, 44100L))) return (44100L);
            break;
        }
        break;
        case MPCPCM008: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, MPCPCM008, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, MPCPCM008, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (ulWavFmt & WAVE_FORMAT_1M08)) return (11025L);
            if ((ulSmpFrq < 22050L) && (ulWavFmt & WAVE_FORMAT_2M08)) return (22050L);
            if ((ulSmpFrq < 44100L) && (ulWavFmt & WAVE_FORMAT_4M08)) return (44100L);
            break;
          case 2: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, MPCPCM008, 2, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, MPCPCM008, 2, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (ulWavFmt & WAVE_FORMAT_1S08)) return (11025L);
            if ((ulSmpFrq < 22050L) && (ulWavFmt & WAVE_FORMAT_2S08)) return (22050L);
            if ((ulSmpFrq < 44100L) && (ulWavFmt & WAVE_FORMAT_4S08)) return (44100L);
            break;
        }                
        break;
        case MPCPCM016: switch (usChnCnt) {
          case 1: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, MPCPCM016, 1, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, MPCPCM016, 1, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (ulWavFmt & WAVE_FORMAT_1M16)) return (11025L);
            if ((ulSmpFrq < 22050L) && (ulWavFmt & WAVE_FORMAT_2M16)) return (22050L);
            if ((ulSmpFrq < 44100L) && (ulWavFmt & WAVE_FORMAT_4M16)) return (44100L);
            break;
          case 2: 
            if ((ulSmpFrq <  6000L) && (MCICapQry (usMCIPro, MPCPCM016, 2, 6000L))) return (6000L);
            if ((ulSmpFrq <  8000L) && (MCICapQry (usMCIPro, MPCPCM016, 2, 8000L))) return (8000L);
            if ((ulSmpFrq < 11025L) && (ulWavFmt & WAVE_FORMAT_1S16)) return (11025L);
            if ((ulSmpFrq < 22050L) && (ulWavFmt & WAVE_FORMAT_2S16)) return (22050L);
            if ((ulSmpFrq < 44100L) && (ulWavFmt & WAVE_FORMAT_4S16)) return (44100L);
            break;
        }                
        break;
    }

    /********************************************************************/
    /********************************************************************/
    return (0L);
}

WORD    FAR PASCAL  MCICapQry (MCIPRO usMCIPro, PCMTYP usPCMTyp, 
                    WORD usChnCnt, DWORD ulSmpFrq)
{
    WAVEFORMATEX    wfWavFmt; 
    WORD            usRetCod;

    /********************************************************************/
    /********************************************************************/
    _fmemset (&wfWavFmt, 0, sizeof wfWavFmt);

    /********************************************************************/
    /********************************************************************/
    switch (usPCMTyp) {
        case DLGPCM004:
            wfWavFmt.wFormatTag = WAVE_FORMAT_DIALOGIC_OKI_ADPCM;
            wfWavFmt.wBitsPerSample = 4;
            wfWavFmt.nBlockAlign = 1;
            break;
        case DLGPCM008: 
        case G11PCMF08: 
            wfWavFmt.wFormatTag = WAVE_FORMAT_MULAW;
            wfWavFmt.wBitsPerSample = 8;
            wfWavFmt.nBlockAlign = 1;
            break;
        case G11PCMI08: 
            wfWavFmt.wFormatTag = WAVE_FORMAT_ALAW;
            wfWavFmt.wBitsPerSample = 8;
            wfWavFmt.nBlockAlign = 1;
            break;
        case MPCPCM008: 
            wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            wfWavFmt.wBitsPerSample = 8;
            wfWavFmt.nBlockAlign = 1;
            break;
        case MPCPCM016: 
            wfWavFmt.wFormatTag = WAVE_FORMAT_PCM;
            wfWavFmt.wBitsPerSample = 16;
            wfWavFmt.nBlockAlign = 2;
            break;
        default:
            return (FALSE);
    }
    wfWavFmt.nChannels = usChnCnt;
    wfWavFmt.nSamplesPerSec = ulSmpFrq;
    wfWavFmt.nAvgBytesPerSec    
        = wfWavFmt.nSamplesPerSec * wfWavFmt.wBitsPerSample / 8L;
    wfWavFmt.cbSize = 0;

    /********************************************************************/
    /* Make sure a waveform output device supports this format.         */
    /********************************************************************/
    switch (WAVDEVDIR (usMCIPro)) {
        case MCIPROINP:
            usRetCod = waveInOpen (NULL, WAVDEV_ID(usMCIPro), 
              (LPWAVEFORMAT) &wfWavFmt, NULL, 0L, WAVE_FORMAT_QUERY);
            return (MMSYSERR_NOERROR == usRetCod);
        case MCIPROOUT:
            usRetCod = waveOutOpen (NULL, WAVDEV_ID(usMCIPro), 
              (LPWAVEFORMAT) &wfWavFmt, NULL, 0L, WAVE_FORMAT_QUERY);
            return (MMSYSERR_NOERROR == usRetCod);
    }

    /********************************************************************/
    /********************************************************************/
    return (FALSE);

}

/************************************************************************/
/************************************************************************/
WORD    GetDevCap (MCIPRO usMCIPro, DWORD FAR *pulWavFmt)
{
    WAVEINCAPS  wcInpCap;
    WAVEOUTCAPS wcOutCap;
    WORD        usRetCod;

    /********************************************************************/
    /********************************************************************/
    switch (WAVDEVDIR (usMCIPro)) {
        case MCIPROINP:
            usRetCod = waveInGetDevCaps  (WAVDEV_ID(usMCIPro), &wcInpCap, sizeof (WAVEINCAPS));  
            break;
        case MCIPROOUT:
            usRetCod = waveOutGetDevCaps (WAVDEV_ID(usMCIPro), &wcOutCap, sizeof (WAVEOUTCAPS));  
            break;
        default:
            return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    *pulWavFmt = usRetCod ? 0L : wcOutCap.dwFormats; 
    return (usRetCod);

}

WORD    GetDevNam (MCIPRO usMCIPro, LPSTR pszDevNam, WORD usMaxLen)
{
    WAVEINCAPS  wcInpCap;
    WAVEOUTCAPS wcOutCap;
    char        szNamInp[MAXPNAMELEN] = {'\0'};
    char        szNamOut[MAXPNAMELEN] = {'\0'}; 
    WORD        usi;

    /********************************************************************/
    /********************************************************************/
	if (!usMaxLen) return (0);
    *pszDevNam = '\0';

    /********************************************************************/
    /* Get input device name                                            */
    /********************************************************************/
    if (0 == waveInGetDevCaps (WAVDEV_ID(usMCIPro), &wcInpCap, sizeof (WAVEINCAPS))) {
        _fstrncpy (szNamInp, wcInpCap.szPname, MAXPNAMELEN);
    }  

    /********************************************************************/
    /* Get output device name                                           */
    /********************************************************************/
    if (0 == waveOutGetDevCaps (WAVDEV_ID(usMCIPro), &wcOutCap, sizeof (WAVEOUTCAPS))) {
        _fstrncpy (szNamOut, wcOutCap.szPname, MAXPNAMELEN);
    }  

    /********************************************************************/
    /* Find simularities; append space at end.                          */
    /********************************************************************/
    for (usi = 0; usi < min (usMaxLen-1, MAXPNAMELEN-1); usi++) {
		if (szNamInp[usi] == szNamOut[usi]) pszDevNam[usi] = szNamOut[usi];	
        else break;
		if ('\0' == pszDevNam[usi]) break;	
	}
	if (' ' != pszDevNam[usi]) pszDevNam[usi++] = ' ';
	pszDevNam[usi]   = '\0';

    /********************************************************************/
    /* Append generic type name                                         */
    /********************************************************************/
    MsgLodStr (MCIGlo.hLibIns, SI_MCIWAVGEN, &pszDevNam[usi], usMaxLen - usi);

    /********************************************************************/
    /********************************************************************/
    return (_fstrlen (pszDevNam));
}
