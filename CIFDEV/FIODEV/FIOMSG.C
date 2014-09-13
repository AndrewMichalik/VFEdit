/************************************************************************/
/* File I/O Message Support: FIOMsg.c                   V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "..\os_dev\winmsg.h"           /* User message support         */
#include "genfio.h"                     /* Generic File I/O definitions */
#include "fiosup.h"                     /* File I/O support definitions */
#include "fiomsg.h"                     /* File I/O support error defs  */

#include <stdlib.h>                     /* Misc string/math/error funcs */
#include <string.h>                     /* String manipulation funcs    */

/************************************************************************/
/*                      External References                             */
/************************************************************************/
extern  FIOGLO  FIOGlo;                 /* File I/O Library Globals     */

/************************************************************************/
/************************************************************************/
long    GetPrfLngStr (LPCSTR szPrfNam, LPCSTR szPrfSec, LPSTR szPrfEnt, long lDefVal)
{
    long            lEntVal;
    static  char    szEntVal[FIOMAXSTR];
    static  char *  pcEndChr;

    /********************************************************************/
    /********************************************************************/
    GetPrivateProfileString (szPrfEnt, szPrfEnt, "", szEntVal, 
        FIOMAXSTR, szPrfNam);
    if (szEntVal[0] == '\0') return (lDefVal);
  
    if (_strnicmp (szEntVal, "0x", 2) == 0) {
        pcEndChr = strchr (&szEntVal[2], '\0');
        lEntVal = strtoul (&szEntVal[2], &pcEndChr, 16);
    }
    else lEntVal = atol (szEntVal);

    /********************************************************************/
    /********************************************************************/
    return (lEntVal);

}

long    GetPrfLng (LPCSTR szPrfNam, LPCSTR szPrfSec, WORD usPrfEnt, long lDefVal)
{

    static  char    szPrfEnt[FIOMAXSTR];

    /********************************************************************/
    /********************************************************************/
    if (!MsgLodStr (FIOGlo.hLibIns, usPrfEnt, szPrfEnt, FIOMAXSTR)) return (lDefVal);
    return (GetPrfLngStr (szPrfNam, szPrfSec, szPrfEnt, lDefVal));

}

/************************************************************************/
/************************************************************************/
int FAR PASCAL  FIODspPrc (HWND hWnd, LPCSTR lpMsgTxt, LPCSTR lpTtlTxt, UINT uiStyFlg)
{
    return (MessageBox (hWnd, lpMsgTxt, FIOGlo.szLibNam, uiStyFlg));
}

BOOL FAR PASCAL MsgAskFmtPrc (HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    MSGASKBLK FAR * lpMsgRsp;

    switch (uMsg) {
        case WM_INITDIALOG:
            /************************************************************/
            /* Store instance specific data pointer                     */
            /************************************************************/
            if (!SetProp (hWnd, PRPLOW, (HANDLE) LOWORD (lParam)) ||
                !SetProp (hWnd, PRPHGH, (HANDLE) HIWORD (lParam))) {
                EndDialog (hWnd, -1);
                break;
            }
            lpMsgRsp = (MSGASKBLK FAR *) lParam;

            /************************************************************/
            /************************************************************/
            CtrDlgBox (NULL, hWnd, NULL, CTR_CTR);
            SetWindowText (hWnd, FIOGlo.szLibNam);
            SendDlgItemMessage (hWnd, DI_RSPSTR, EM_LIMITTEXT, WINMAXMSG, 0L);
            SetDlgItemText (hWnd, DI_REQSTR, lpMsgRsp->szMsgTxt);
            SetDlgItemText (hWnd, DI_RSPSTR, lpMsgRsp->szRspTxt);

            /************************************************************/
            /* Set focus on 1st edit cntrl, ask Windows not to override */
            /************************************************************/
            SendDlgItemMessage (hWnd, DI_RSPSTR, EM_SETSEL, 0, MAKELONG (0, 32767));
            SetFocus (GetDlgItem (hWnd, DI_RSPSTR));
            return (FALSE);
  
        case WM_CTLCOLOR:
            if ((CTLCOLOR_DLG == HIWORD (lParam)) 
              || (CTLCOLOR_STATIC == HIWORD (lParam))) { 
                SetBkColor ((HDC) wParam, FIOGlo.ulDBxClr);
                return ((BOOL) FIOGlo.hDBxBsh);
            }
            return (FALSE);

        case WM_COMMAND:
          if (NULL == (lpMsgRsp = (MSGASKBLK FAR *) 
            MAKELONG (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) {
              EndDialog (hWnd, -1);
              break;
          }
          switch(wParam) {
            case IDOK:
                GetDlgItemText (hWnd, DI_RSPSTR, lpMsgRsp->szRspTxt, WINMAXMSG);
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