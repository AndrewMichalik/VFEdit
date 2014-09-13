/************************************************************************/
/* Media Control Wave Support: MCIWav.c                 V2.00  07/15/94 */
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
WORD    BufBlkAlo (BUFBLK FAR *, DWORD, VISMEMHDL mhWIORes);
WORD    BufBlkRel (BUFBLK FAR *);

/************************************************************************/
/************************************************************************/
LONG FAR PASCAL MCICBkWin (HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    #define PRPLOW  "PrpLow"
    #define PRPHGH  "PrpHgh"
    LPWAVEHDR       lpWavHdr;
    VISMEMHDL       mhWIOMem;
    WIORES FAR    * lpWIORes;

    /********************************************************************/
    /********************************************************************/
    switch (uMsg) {
        case WM_CREATE:
            /************************************************************/
            /* Store instance specific data pointer                     */
            /************************************************************/
            mhWIOMem = (VISMEMHDL) ((LPCREATESTRUCT) lParam)->lpCreateParams;
            if (!SetProp (hWnd, PRPLOW, (HANDLE) LOWORD (mhWIOMem)) ||
                !SetProp (hWnd, PRPHGH, (HANDLE) HIWORD (mhWIOMem))) {
                EndDialog (hWnd, -1);
                break;
            }
            break;

        case MM_WIM_DATA:
        case MM_WOM_DONE:
            /****************************************************************/
            /* Under HEAVY loading, the wave device can starve everyone.    */
            /* Yield BEFORE sending the next block to force the wave device */
            /* to starve rather than everyone else. One danger in yielding  */
            /* at this point is that lpWIOBlk & lpWavHdr could              */
            /* THEORETICALLY become invalid by an asynchronous process      */
            /* calling MCIWavCls (unlikely).                                */
            /****************************************************************/
            {
                MSG		msg;
                if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessage (&msg);
                }
            }

            /************************************************************/
            /* This message indicates a waveform data block has         */
            /* been played and can be freed. Clean up the preparation   */
            /* done previously on the header.                           */
            /************************************************************/
            lpWavHdr = (LPWAVEHDR) lParam;

            /************************************************************/
            /* Get pointer to wave I/O resource data block.             */
            /************************************************************/
            if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) 
              GloMemLck ((VISMEMHDL) lpWavHdr->dwUser))) {
                break;
            }
            if (NULL != lpWIORes->fpDevPrc) lpWIORes->fpDevPrc (MCIPOLCNT, 
                &lpWIORes->wbWIOBlk, lpWavHdr);
            GloMemUnL ((VISMEMHDL) lpWavHdr->dwUser);
            break;

        case WM_TIMER:
            /************************************************************/
            /* Get pointer to wave I/O resource data block.             */
            /************************************************************/
            if (NULL == (mhWIOMem = (VISMEMHDL) MAKELONG 
                (GetProp (hWnd, PRPLOW), GetProp (hWnd, PRPHGH)))) break;
            if (NULL == (lpWIORes = GloMemLck (mhWIOMem))) break;

            /************************************************************/
            /* Call timer procedure.                                    */
            /************************************************************/
            if (NULL != lpWIORes->fpTimPrc) lpWIORes->fpTimPrc (&lpWIORes->wbWIOBlk);
            GloMemUnL (mhWIOMem);
            break;

    }

    return DefWindowProc (hWnd, uMsg, wParam, lParam);
}

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL MCIWavOpn (MCIPRO usMCIPro, VISMEMHDL FAR *pmhWIORes, 
                VISMEMHDL mhCfgMem, WORD usBlkLen, WORD usBlkCnt, 
                LPSTR szDesStr, WORD usMaxLen)
{
    WIORES FAR *lpWIORes;
    WORD        usi;

    /********************************************************************/
    /********************************************************************/
    if (szDesStr) *szDesStr = '\0';

    /********************************************************************/
    /* Allocate and initialize wave I/O resource data block.            */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloAloLck 
      (GMEM_MOVEABLE | GMEM_SHARE, pmhWIORes, sizeof (*lpWIORes)))) {
        return ((WORD) -1);
    }
    _fmemset (lpWIORes, 0, sizeof (*lpWIORes));

    /********************************************************************/
    /* Allocate & lock all buffered data blocks & headers               */
    /* On failure, release previous blks (ignore failed, already clear) */
    /********************************************************************/
    lpWIORes->wbWIOBlk.ulBufSiz = max (min (usBlkLen, BLKLENMAX), BLKLENMIN) * 1024L;
    lpWIORes->wbWIOBlk.usBufCnt = max (min (usBlkCnt, BLKCNTMAX), BLKCNTMIN);

    for (usi=0; usi<lpWIORes->wbWIOBlk.usBufCnt; usi++) 
        if (BufBlkAlo (&lpWIORes->bbBufBlk[usi], lpWIORes->wbWIOBlk.ulBufSiz, 
        *pmhWIORes)) break;
    if (usi < lpWIORes->wbWIOBlk.usBufCnt) {
        while (usi) BufBlkRel (&lpWIORes->bbBufBlk[usi]);
        *pmhWIORes = GloUnLRel (*pmhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Create the callback window                                       */
    /********************************************************************/
    lpWIORes->hCBkWnd = CreateWindow (
    SI_MCICBKCLS,                           /*  Window class name.      */
    "",                                     /*  Window title.           */
    WS_DISABLED,                            /*  Type of window.         */
    CW_USEDEFAULT,                          /*  x - default location    */
    0,                                      /*  y - default             */
    CW_USEDEFAULT,                          /*  cx - (width)  default   */
    0,                                      /*  cy - (height) default   */
    NULL,                                   /*  No parent for this wind */
    NULL,                                   /*  Use the class menu.     */
    MCIGlo.hLibIns,                         /*  Who created this window */
    (LPSTR) (DWORD) *pmhWIORes              /*  Pass Wav I/O resource   */
    );

    /********************************************************************/
    /********************************************************************/
    if (NULL == lpWIORes->hCBkWnd) {
        MsgDspRes (MCIGlo.hLibIns, 0, SI_MCICRECBK);    
        for (usi=0; usi<lpWIORes->wbWIOBlk.usBufCnt; usi++) 
            BufBlkRel (&lpWIORes->bbBufBlk[usi]);
        *pmhWIORes = GloUnLRel (*pmhWIORes);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Return device description                                        */
    /* Future: Use GetDevNam() to return manufacturer's name            */
    /********************************************************************/
    if (szDesStr) MsgLodStr (MCIGlo.hLibIns, SI_MCIWAVPRO, szDesStr, usMaxLen);

    /********************************************************************/
    /* Extract and set the Device ID (0 to n)                           */
    /********************************************************************/
    lpWIORes->wbWIOBlk.usDev_ID = WAVDEV_ID(usMCIPro);

    /********************************************************************/
    /********************************************************************/
    GloMemUnL (*pmhWIORes);
    return (0);

}

WORD FAR PASCAL MCIWavCls (VISMEMHDL FAR *pmhWIORes) 
{
    WIORES FAR *lpWIORes;
    WORD        usi;

    /********************************************************************/
    /* Get pointer to instance data for waveform callback.              */
    /********************************************************************/
    if ((WIORES FAR *) NULL == (lpWIORes = (WIORES FAR *) GloMemLck (*pmhWIORes))) {
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Destroy the callback window                                      */
    /********************************************************************/
    DestroyWindow (lpWIORes->hCBkWnd);

    /********************************************************************/
    /* Free buffer, header and instance memory                          */
    /********************************************************************/
    for (usi=0; usi<lpWIORes->wbWIOBlk.usBufCnt; usi++) 
        BufBlkRel (&lpWIORes->bbBufBlk[usi]);

    /********************************************************************/
    /********************************************************************/
    *pmhWIORes = GloUnLRel (*pmhWIORes);
    return (0);

}

/************************************************************************/
/************************************************************************/
WORD    BufBlkAlo (BUFBLK FAR *lpBufBlk, DWORD ulBufSiz, VISMEMHDL mhWIORes)
{
    /********************************************************************/
    /* Allocate & lock buffered waveform header memory.                 */
    /********************************************************************/
    if (NULL == (lpBufBlk->lpWavHdr = GloAloLck 
      (GMEM_MOVEABLE | GMEM_SHARE, &lpBufBlk->mhHdrHdl, sizeof (WAVEHDR))))
        return ((WORD) -1);
    _fmemset (lpBufBlk->lpWavHdr, 0, sizeof (WAVEHDR));

    /********************************************************************/
    /* Allocate & lock buffered waveform data memory.                   */
    /********************************************************************/
    if (NULL == (lpBufBlk->lpWavHdr->lpData = GloAloLck 
      (GMEM_MOVEABLE | GMEM_SHARE, &lpBufBlk->mhBufHdl, ulBufSiz))) {
        lpBufBlk->mhHdrHdl= GloUnLRel (lpBufBlk->mhHdrHdl);
        return ((WORD) -1);
    }

    /********************************************************************/
    /* Store wave I/O resource memory handle for callback window.       */
    /********************************************************************/
    lpBufBlk->lpWavHdr->dwUser = (UINT) mhWIORes;

    /********************************************************************/
    /********************************************************************/
    return (0);

}

WORD    BufBlkRel (BUFBLK FAR *lpBufBlk)
{
    lpBufBlk->mhHdrHdl= GloUnLRel (lpBufBlk->mhHdrHdl);
    lpBufBlk->mhBufHdl= GloUnLRel (lpBufBlk->mhBufHdl);
    return (0);
}
