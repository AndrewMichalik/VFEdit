/************************************************************************/
/* Amplitude Display Msg Support Defs: FIOMsg.h         V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                  User Display Support Functions                      */
/************************************************************************/
BOOL    MsgCatStr (WORD, char FAR *, WORD);
long    GetPrfLng (LPCSTR, LPCSTR, WORD, long);

HFONT   CreFntFix (HDC, WORD, RECT);
DWORD   ExtFntFix (HWND, WORD, RECT);
RECT    ShdRecBox (HDC, RECT, HPEN, HPEN);
int     ShdRecTxt (HDC, char FAR *, RECT, WORD);
int     ShdRecRec (HDC, RECT, DWORD, DWORD, DWORD, HPEN, HBRUSH);

LPSTR   _fdtorna (double, short, LPSTR);


