/************************************************************************/
/* Dialogic FIO Stubs: DlgStb.c                         V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#include "windows.h"                    /* Windows SDK definitions      */
#include "..\os_dev\winmem.h"           /* Generic memory supp defs     */
#include "genfio.h"                     /* Generic File I/O definitions */

/************************************************************************/
/************************************************************************/
WORD FAR PASCAL IniPL2Hdr (VISMEMHDL FAR *a, ENUPCM b)
                { return (0); }
FIORET          LodPL2Hdr (LPOFSTRUCT_V a, VISMEMHDL FAR *b)
                { return (0); }
FIORET          GetPL2PCM (LPOFSTRUCT_V a, ENUPCM FAR *b)
                { return (0); }
FIORET          LodPL2Vox (LPOFSTRUCT_V a, LPOFSTRUCT_V b, FIOPOLPRC c)
                { return (0); }
FIORET          WrtPL2Fil (LPOFSTRUCT_V a, LPOFSTRUCT_V b, VISMEMHDL c, FIOPOLPRC d) 
                { return (0); }
                    
                    
