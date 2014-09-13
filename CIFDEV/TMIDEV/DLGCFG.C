/************************************************************************/
/* Dialogic Configuration: DlgCfg.c                     V2.00  06/10/92 */
/* Copyright (c) 1987-1992 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define  NOCOMM                         /* Inhibit certain windows defs */
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\..\tifdll\tiflib\dlglib.h" /* Dialogic D4x stand defs      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "gentmi.h"                     /* Generic TMI definitions      */
#include "tmisup.h"                     /* Generic TMI support defs     */
#include "tmimsg.h"                     /* File I/O support error defs  */
#include "dlgdig.h"                     /* Dialogic TMI definitions     */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/************************************************************************/
#define MPXINPDEF            1          /* Requested Mpx input          */
#define MPXOUTDEF            2          /* Requested Mpx output         */
#define MPXLOCDEF        FALSE          /* Requested Mpx local          */
#define MAXSILDEF            0          /* Max sil allowed during rcrd  */
#define MAXSNDDEF            0          /* Max snd allowed during rcrd  */
#define SILCMPDEF            0          /* Sil compression sensitivity  */
#define AGCMODDEF         TRUE          /* AGC Mode default             */
#define TRMOOHDEF         TRUE          /* Term on/off hook state       */
#define WAICALDEF        FALSE          /* Wait for call                */

/************************************************************************/
/*                  Forward & External References                       */
/************************************************************************/
extern  TMIGLO      TMIGlo;             /* Generic TMI Lib Globals      */

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL TMICfgLod (VISMEMHDL FAR *pmhCfgMem, LPCSTR lpCfgFil, LPCSTR lpSecNam)
{
    DIGCFG FAR *lpDigCfg;    

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpDigCfg = GloAloLck (GMEM_MOVEABLE, pmhCfgMem, 
        sizeof (DIGCFG)))) return ((WORD) -1);
    _fmemset (lpDigCfg, 0, sizeof (*lpDigCfg));

    /********************************************************************/
    /* Check for user specified configuration file and set              */
    /* board parameters accordingly.                                    */
    /********************************************************************/
    lpDigCfg->tdTMIDef.scSysCfg.sVBSwIn = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_VBSWIN, 0);
    lpDigCfg->tdTMIDef.scSysCfg.sVBHwIn = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_VBHWIR, 0);
    lpDigCfg->tdTMIDef.scSysCfg.sMxHwIn = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MXHWIR, 0);
    lpDigCfg->tdTMIDef.scSysCfg.sLinNum = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_LINENO, 0);
    lpDigCfg->tdTMIDef.scSysCfg.sMpxInp = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MPXINP, MPXINPDEF);
    lpDigCfg->tdTMIDef.scSysCfg.sMpxOut = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MPXOUT, MPXOUTDEF);
    lpDigCfg->tdTMIDef.scSysCfg.sMpxLoc = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MPXLOC, MPXLOCDEF);
    lpDigCfg->tdTMIDef.scSysCfg.sTrmOOH = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_TRMOOH, TRMOOHDEF);
    lpDigCfg->tdTMIDef.scSysCfg.sWaiCal = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_WAICAL, WAICALDEF);

    lpDigCfg->tdTMIDef.lcLinCfg.sMaxSil = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MAXSIL, MAXSILDEF);
    lpDigCfg->tdTMIDef.lcLinCfg.sMaxSnd = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_MAXSND, MAXSNDDEF);
    lpDigCfg->tdTMIDef.lcLinCfg.sSilCmp = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_SILCMP, SILCMPDEF);
    lpDigCfg->tdTMIDef.lcLinCfg.sAGCMod = (short) GetPrfLng (lpCfgFil, lpSecNam, PI_AGCMOD, AGCMODDEF);
//lpDigCfg->tdTMIDef.lcLinCfg.dtinit
//lpDigCfg->tdTMIDef.lcLinCfg.dtterm

    /********************************************************************/
    /* Reset & initialize DCB parameters                                */
    /********************************************************************/
    clrdcb  (&(lpDigCfg->dbDlgDCB));

    lpDigCfg->dbDlgDCB.flashchr = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_FLASH_CHAR, 0);
    lpDigCfg->dbDlgDCB.flashtm  = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_FLASH_TIME, 0);
    lpDigCfg->dbDlgDCB.pausetm  = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_PAUSE_TIME, 0);
    lpDigCfg->dbDlgDCB.digrate  = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_DIGRATE,    0);
    lpDigCfg->dbDlgDCB.sch_tm   = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_SCH_TM,     0);
    lpDigCfg->dbDlgDCB.p_bk     = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_P_BK,       0);
    lpDigCfg->dbDlgDCB.p_mk     = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_P_MK,       0);
    lpDigCfg->dbDlgDCB.p_idd    = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_P_IDD,      0);
    lpDigCfg->dbDlgDCB.t_idd    = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_T_IDD,      0);
    lpDigCfg->dbDlgDCB.oh_dly   = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_OH_DLY,     0);
    lpDigCfg->dbDlgDCB.r_on     = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_R_ON,       0);
    lpDigCfg->dbDlgDCB.r_off    = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_R_OFF,      0);
    lpDigCfg->dbDlgDCB.r_ird    = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_R_IRD,      0);
    lpDigCfg->dbDlgDCB.s_bnc    = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_S_BNC,      0);
    lpDigCfg->dbDlgDCB.ttdata   = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_TTDATA,     0);
    lpDigCfg->dbDlgDCB.minpdon  = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_MINPDON,    0);
    lpDigCfg->dbDlgDCB.minpdoff = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_MINPDOFF,   0);
    lpDigCfg->dbDlgDCB.minipd   = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_MINIPD,     0);
    lpDigCfg->dbDlgDCB.minlcoff = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_MINLCOFF,   0);
    lpDigCfg->dbDlgDCB.redge    = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_REDGE,      0);
    lpDigCfg->dbDlgDCB.maxpdoff = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_MAXPDOFF,   0);
																			
    /********************************************************************/
    /********************************************************************/
    clrcpb (&(lpDigCfg->cbDlgCPB));
    lpDigCfg->cbDlgCPB.dtpl_dly = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_DTPL_DLY,   0);
    lpDigCfg->cbDlgCPB.dt_edge  = (byte) GetPrfLng (lpCfgFil, lpSecNam, PI_DT_EDGE,    0);
    lpDigCfg->cbDlgCPB.dtrc_dly = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_DTRC_DLY,   0);
    lpDigCfg->cbDlgCPB.sb_siz   = (word) GetPrfLng (lpCfgFil, lpSecNam, PI_SB_SIZ,     0);
//    /********************************************************************/
//    /* Convert ms to bytes, max = 400 bytes                             */
//    /********************************************************************/
//    cbDlgCPB.sb_siz = (word) min (400L, 
//        (DWORD) lpDigCfg->tdTMIDef.scSysCfg.usCmpTim * ulSmpFrq
//        / 2000L);

    /********************************************************************/
    /********************************************************************/
    lpDigCfg->usCSTInt = (WORD) GetPrfLng (lpCfgFil, lpSecNam, PI_CSTINT, 
        C_LC | C_RING | C_OFFH | C_ONH | C_LCON);      

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhCfgMem);
    return (0);

}

WORD FAR PASCAL TMICfgMod (VISMEMHDL mhCfgMem, WORD usModTyp, DWORD ulArg001)
{
    DIGCFG FAR *lpDigCfg;    
    WORD        usRetCod;

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) return ((WORD) -1);

#if ((defined (DLG))) /**************************************************/
    usRetCod = TRUE;
#endif /*****************************************************************/
#if ((defined (NWV))) /**************************************************/
    #define NWV2BPSEC   4
    if ((lpDigCfg->dbDlgDCB.digrate * NWV2BPSEC) != (WORD) ulArg001) {
        lpDigCfg->dbDlgDCB.digrate = (WORD) (ulArg001 / NWV2BPSEC);
    }
#endif /*****************************************************************/
#if ((defined (RTX))) /**************************************************/
    usRetCod = TRUE;
#endif /*****************************************************************/

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    return (usRetCod);
}

WORD FAR PASCAL TMICfgRel (VISMEMHDL FAR *pmhCfgMem, LPCSTR lpCfgFil, LPCSTR lpSecNam)
{
    DIGCFG FAR *lpDigCfg;    

    /********************************************************************/
    /********************************************************************/
    if (!lpCfgFil || !_fstrlen (lpCfgFil)) {
        *pmhCfgMem = GloAloRel (*pmhCfgMem);
        return (0);
    }
    if (NULL == (lpDigCfg = GloMemLck (*pmhCfgMem))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* If config file is specified, update user specified settings      */
    /********************************************************************/
    WrtPrfLng (lpCfgFil, lpSecNam, PI_VBSWIN, lpDigCfg->tdTMIDef.scSysCfg.sVBSwIn);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_VBHWIR, lpDigCfg->tdTMIDef.scSysCfg.sVBHwIn);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MXHWIR, lpDigCfg->tdTMIDef.scSysCfg.sMxHwIn);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_LINENO, lpDigCfg->tdTMIDef.scSysCfg.sLinNum);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MPXINP, lpDigCfg->tdTMIDef.scSysCfg.sMpxInp);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MPXOUT, lpDigCfg->tdTMIDef.scSysCfg.sMpxOut);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MPXLOC, lpDigCfg->tdTMIDef.scSysCfg.sMpxLoc);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_WAICAL, lpDigCfg->tdTMIDef.scSysCfg.sWaiCal);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_TRMOOH, lpDigCfg->tdTMIDef.scSysCfg.sTrmOOH);

    WrtPrfLng (lpCfgFil, lpSecNam, PI_MAXSIL, lpDigCfg->tdTMIDef.lcLinCfg.sMaxSil);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MAXSND, lpDigCfg->tdTMIDef.lcLinCfg.sMaxSnd);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_SILCMP, lpDigCfg->tdTMIDef.lcLinCfg.sSilCmp);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_AGCMOD, lpDigCfg->tdTMIDef.lcLinCfg.sAGCMod);
//    WrtPrfLng (lpCfgFil, lpSecNam, PI_DIGINI, lpDigCfg->tdTMIDef.lcLinCfg.sDigIni);
//    WrtPrfLng (lpCfgFil, lpSecNam, PI_DIGTRM, lpDigCfg->tdTMIDef.lcLinCfg.sDigTrm);

    /********************************************************************/
    /********************************************************************/
    WrtPrfLng (lpCfgFil, lpSecNam, PI_FLASH_CHAR, lpDigCfg->dbDlgDCB.flashchr);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_FLASH_TIME, lpDigCfg->dbDlgDCB.flashtm);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_PAUSE_TIME, lpDigCfg->dbDlgDCB.pausetm);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_DIGRATE,    lpDigCfg->dbDlgDCB.digrate);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_SCH_TM,     lpDigCfg->dbDlgDCB.sch_tm);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_P_BK,       lpDigCfg->dbDlgDCB.p_bk);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_P_MK,       lpDigCfg->dbDlgDCB.p_mk);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_P_IDD,      lpDigCfg->dbDlgDCB.p_idd);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_T_IDD,      lpDigCfg->dbDlgDCB.t_idd);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_OH_DLY,     lpDigCfg->dbDlgDCB.oh_dly);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_R_ON,       lpDigCfg->dbDlgDCB.r_on);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_R_OFF,      lpDigCfg->dbDlgDCB.r_off);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_R_IRD,      lpDigCfg->dbDlgDCB.r_ird);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_S_BNC,      lpDigCfg->dbDlgDCB.s_bnc);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_TTDATA,     lpDigCfg->dbDlgDCB.ttdata);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MINPDON,    lpDigCfg->dbDlgDCB.minpdon);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MINPDOFF,   lpDigCfg->dbDlgDCB.minpdoff);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MINIPD,     lpDigCfg->dbDlgDCB.minipd);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MINLCOFF,   lpDigCfg->dbDlgDCB.minlcoff);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_REDGE,      lpDigCfg->dbDlgDCB.redge);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_MAXPDOFF,   lpDigCfg->dbDlgDCB.maxpdoff);

    WrtPrfLng (lpCfgFil, lpSecNam, PI_CSTINT, lpDigCfg->usCSTInt);

    /********************************************************************/
    /********************************************************************/
    *pmhCfgMem = GloAloRel (*pmhCfgMem);
    return (0);
}

/************************************************************************/
/*               Create the Config Box Window Procedure                 */
/************************************************************************/
WORD FAR PASCAL TMICfgQry (VISMEMHDL mhCfgMem)
{
    DIGCFG FAR *lpDigCfg;    
    FARPROC     lpPrcAdr;
    int         iRetCod;

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /********************************************************************/
    lpPrcAdr = MakeProcInstance ((FARPROC) CfgEdtBoxPrc, TMIGlo.hLibIns);
    iRetCod = DialogBoxParam (TMIGlo.hLibIns, "SYSCFGBOX", GetParWnd (NULL), 
        (DLGPROC) lpPrcAdr, (DWORD) (LPVOID) &lpDigCfg->tdTMIDef.scSysCfg);
    FreeProcInstance ((FARPROC) lpPrcAdr);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    return (iRetCod);
  
}
  
/************************************************************************/
/*                Configuration Box Edit Procedure                      */
/************************************************************************/
BOOL FAR PASCAL CfgEdtBoxPrc (HWND hWnd, unsigned uMsg, WPARAM wParam,
                LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    TMIDEF  FAR *   lpTMIDef;           /* Inst local data block ptr    */
    BOOL            bfXlt_OK;

    switch (uMsg) {
    case WM_INITDIALOG:
        /****************************************************************/
        /* Store instance specific data pointer                         */
        /****************************************************************/
        if (!SetProp (hWnd, PRPLOW, (HANDLE) LOWORD (lParam)) ||
            !SetProp (hWnd, PRPHGH, (HANDLE) HIWORD (lParam))) {
            EndDialog (hWnd, -1);
            break;
        }
        lpTMIDef = (TMIDEF FAR *) lParam;

        /****************************************************************/
        /****************************************************************/
        CtrDlgBox (NULL, hWnd, NULL, CTR_CTR);

        /****************************************************************/
        SetDlgItemHex (hWnd, DI_VBSWIN, lpTMIDef->scSysCfg.sVBSwIn);
        SetDlgItemHex (hWnd, DI_VBHWIR, lpTMIDef->scSysCfg.sVBHwIn);
        SetDlgItemHex (hWnd, DI_MXHWIR, lpTMIDef->scSysCfg.sMxHwIn);
        SetDlgItemInt (hWnd, DI_LINNUM, lpTMIDef->scSysCfg.sLinNum, FALSE);
        SetDlgItemInt (hWnd, DI_MPXINP, lpTMIDef->scSysCfg.sMpxInp, FALSE);
        SetDlgItemInt (hWnd, DI_MPXOUT, lpTMIDef->scSysCfg.sMpxOut, FALSE);
        CheckDlgButton (hWnd, DI_WAICAL, lpTMIDef->scSysCfg.sWaiCal);

        SetDlgItemInt (hWnd, DI_SILCMP, lpTMIDef->lcLinCfg.sSilCmp, FALSE);
        SetDlgItemInt (hWnd, DI_MAXSIL, lpTMIDef->lcLinCfg.sMaxSil, FALSE);
        SetDlgItemInt (hWnd, DI_MAXSND, lpTMIDef->lcLinCfg.sMaxSnd, FALSE);
//        SetDlgItemInt (hWnd, DI_DIGINI, lpTMIDef->lcLinCfg.sDigIni, FALSE);
//        SetDlgItemInt (hWnd, DI_DIGTRM, lpTMIDef->lcLinCfg.sDigTrm, FALSE);
        CheckDlgButton (hWnd, DI_AGCMOD, lpTMIDef->lcLinCfg.sAGCMod);

        /****************************************************************/
        /* Disable selections if no Multiplexer connected               */
        /****************************************************************/
        if (!lpTMIDef->scSysCfg.sMxHwIn) {
            EnableWindow (GetDlgItem (hWnd, DI_MPXINP), FALSE);
            EnableWindow (GetDlgItem (hWnd, DI_MPXOUT), FALSE);
        }
//Oops! must re-enable if users changes it!

        /************************************************************/
        /* Set focus on 1st edit cntrl, ask Windows not to override */
        /************************************************************/
        SetFocus (GetDlgItem (hWnd, IDOK));
        return (FALSE);
  
    case WM_CTLCOLOR:
      if ((CTLCOLOR_DLG == HIWORD (lParam)) 
        || (CTLCOLOR_STATIC == HIWORD (lParam)) 
        || (CTLCOLOR_BTN == HIWORD (lParam))) { 
          SetBkColor ((HDC) wParam, TMIGlo.ulDBxClr);
          return ((BOOL) TMIGlo.hDBxBsh);
      }
      return (FALSE);

    case WM_COMMAND:
      if (NULL == (lpTMIDef = (TMIDEF FAR *) 
        MAKELONG (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) {
          EndDialog (hWnd, -1);
          break;
      }
      switch(wParam) {
        /****************************************************************/
        /****************************************************************/
        case IDOK:
            lpTMIDef->scSysCfg.sVBSwIn = (short) GetDlgItemHex (hWnd, DI_VBSWIN);
            lpTMIDef->scSysCfg.sVBHwIn = (short) GetDlgItemHex (hWnd, DI_VBHWIR);
            lpTMIDef->scSysCfg.sMxHwIn = (short) GetDlgItemHex (hWnd, DI_MXHWIR);
            lpTMIDef->scSysCfg.sLinNum = GetDlgItemInt (hWnd, DI_LINNUM, &bfXlt_OK, FALSE);        
            lpTMIDef->scSysCfg.sMpxInp = GetDlgItemInt (hWnd, DI_MPXINP, &bfXlt_OK, FALSE);         
            lpTMIDef->scSysCfg.sMpxOut = GetDlgItemInt (hWnd, DI_MPXOUT, &bfXlt_OK, FALSE);         
            lpTMIDef->scSysCfg.sWaiCal = IsDlgButtonChecked (hWnd, DI_WAICAL);
            lpTMIDef->lcLinCfg.sSilCmp = GetDlgItemInt (hWnd, DI_SILCMP, &bfXlt_OK, FALSE);         
            lpTMIDef->lcLinCfg.sMaxSil = GetDlgItemInt (hWnd, DI_MAXSIL, &bfXlt_OK, FALSE);         
            lpTMIDef->lcLinCfg.sMaxSnd = GetDlgItemInt (hWnd, DI_MAXSND, &bfXlt_OK, FALSE);         
//            lpTMIDef->lcLinCfg.sDigIni = GetDlgItemInt (hWnd, DI_DIGINI, &bfXlt_OK, FALSE);         
//            lpTMIDef->lcLinCfg.sDigTrm = GetDlgItemInt (hWnd, DI_DIGTRM, &bfXlt_OK, FALSE);         
            lpTMIDef->lcLinCfg.sAGCMod = IsDlgButtonChecked (hWnd, DI_AGCMOD);
            EndDialog(hWnd, 0);
            return(TRUE);

        case IDCANCEL:
            EndDialog(hWnd, -1);
            return(TRUE);

        default:
            return(FALSE);
      }
      break;

    case WM_DESTROY:
      RemoveProp (hWnd, PRPLOW);
      RemoveProp (hWnd, PRPHGH);
      break;

    default:
        return(FALSE);
    }

    return(FALSE);
}


