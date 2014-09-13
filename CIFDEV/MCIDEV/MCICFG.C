/************************************************************************/
/* MCI Configuration: MCICfg.c                          V2.00  07/10/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "mmsystem.h"                   /* Windows Multi Media defs     */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genmci.h"                     /* Generic MCI definitions      */
#include "mcisup.h"                     /* MCI support definitions      */

#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  MCIGLO  MCIGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
typedef struct _DIGCFG {                /* Digitizer system params      */
    WORD    usLvlInp;                   /* Input volume level           */
    WORD    usLvlOut;                   /* Input volume level           */
} DIGCFG;

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL MCICfgLod (VISMEMHDL FAR *pmhCfgMem, LPCSTR lpCfgFil, LPCSTR lpSecNam)
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
    lpDigCfg->usLvlInp = (WORD) GetPrfLng (lpCfgFil, lpSecNam, PI_LVLINP, 0);
    lpDigCfg->usLvlOut = (WORD) GetPrfLng (lpCfgFil, lpSecNam, PI_LVLOUT, 0);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhCfgMem);
    return (0);

}

WORD FAR PASCAL MCICfgMod (VISMEMHDL mhCfgMem, WORD usModTyp, DWORD ulArg001)
{
    DIGCFG FAR *lpDigCfg;    
    WORD        usRetCod;

    /********************************************************************/
    /********************************************************************/
    if (NULL == (lpDigCfg = GloMemLck (mhCfgMem))) return ((WORD) -1);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    return (usRetCod);
}

WORD FAR PASCAL MCICfgRel (VISMEMHDL FAR *pmhCfgMem, LPCSTR lpCfgFil, LPCSTR lpSecNam)
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
    WrtPrfLng (lpCfgFil, lpSecNam, PI_LVLINP, lpDigCfg->usLvlInp);
    WrtPrfLng (lpCfgFil, lpSecNam, PI_LVLOUT, lpDigCfg->usLvlOut);

    /********************************************************************/
    /********************************************************************/
    *pmhCfgMem = GloAloRel (*pmhCfgMem);
    return (0);
}

/************************************************************************/
/*               Create the Config Box Window Procedure                 */
/************************************************************************/
WORD FAR PASCAL MCICfgQry (VISMEMHDL mhCfgMem)
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
    lpPrcAdr = MakeProcInstance ((FARPROC) CfgEdtBox, MCIGlo.hLibIns);
    iRetCod = DialogBoxParam (MCIGlo.hLibIns, "SYSCFGBOX", GetParWnd (NULL), 
        (DLGPROC) lpPrcAdr, (DWORD) (LPVOID) &lpDigCfg);
    FreeProcInstance ((FARPROC) lpPrcAdr);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (mhCfgMem);
    return (iRetCod);
  
}
  
/************************************************************************/
/*                Configuration Box Edit Procedure                      */
/************************************************************************/
BOOL FAR PASCAL CfgEdtBox (HWND hWnd, unsigned uMsg, WPARAM wParam,
                LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    DIGCFG  FAR *   lpDigCfg;           /* Inst local data block ptr    */
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
        lpDigCfg = (DIGCFG FAR *) lParam;

        /****************************************************************/
        /****************************************************************/
        CtrDlgBox (NULL, hWnd, NULL, CTR_CTR);

        /****************************************************************/
        SetDlgItemInt (hWnd, DI_LVLINP, lpDigCfg->usLvlInp, FALSE);
        SetDlgItemInt (hWnd, DI_LVLOUT, lpDigCfg->usLvlOut, FALSE);

        /************************************************************/
        /* Set focus on 1st edit cntrl, ask Windows not to override */
        /************************************************************/
        SetFocus (GetDlgItem (hWnd, IDOK));
        return (FALSE);
  
    case WM_CTLCOLOR:
      if ((CTLCOLOR_DLG == HIWORD (lParam)) 
        || (CTLCOLOR_STATIC == HIWORD (lParam)) 
        || (CTLCOLOR_BTN == HIWORD (lParam))) { 
          SetBkColor ((HDC) wParam, MCIGlo.ulDBxClr);
          return ((BOOL) MCIGlo.hDBxBsh);
      }
      return (FALSE);

    case WM_COMMAND:
      if (NULL == (lpDigCfg = (DIGCFG FAR *) 
        MAKELONG (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) {
          EndDialog (hWnd, -1);
          break;
      }
      switch(wParam) {
        /****************************************************************/
        /****************************************************************/
        case IDOK:
            lpDigCfg->usLvlInp = GetDlgItemInt (hWnd, DI_LVLINP, &bfXlt_OK, FALSE);
            lpDigCfg->usLvlOut = GetDlgItemInt (hWnd, DI_LVLOUT, &bfXlt_OK, FALSE);
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