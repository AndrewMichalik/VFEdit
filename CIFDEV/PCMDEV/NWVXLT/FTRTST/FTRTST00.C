WORD    spcflt(float FAR *lpSrcBuf, WORD usSmpCnt, WORD usSecCnt, WORD usFtrLen, 
        float FAR *lpZer, float FAR *lpPol, float FAR *lpHisInp, float FAR *lpHisOut)
{
    WORD usSec, usSmp, ll, usZCo, usPCo, usHIn, usHOu;

    usZCo = usFtrLen + 1;
    usPCo = usFtrLen;
    usHIn = usFtrLen + 1;
    usHOu = usFtrLen;

    /********************************************************************/
    /********************************************************************/
    for (usSec=0; usSec < usSecCnt; usSec++) for (usSmp=0; usSmp < usSmpCnt; usSmp++) {
        lpHisInp[usSec * usHIn] = lpSrcBuf[usSmp];
        lpSrcBuf[usSmp] = lpZer[usSec * usZCo] * lpHisInp[usSec * usHIn];

        for (ll = 1; ll <= usFtrLen; ++ll) {
            lpSrcBuf[usSmp] = lpSrcBuf[usSmp] + lpZer[ll + usSec * usZCo] * lpHisInp[ll + usSec * usHIn]
               - lpPol[ll - 1 + usSec * usPCo] * lpHisOut[ll - 1 + usSec * usHOu];
        }

        if (fabs(lpSrcBuf[usSmp]) > BIG) return (usSec);

        for (ll = usFtrLen; ll >= 2; --ll) {
            lpHisInp[ll + usSec * usHIn] = lpHisInp[ll - 1 + usSec * usHIn];
            lpHisOut[ll - 1 + usSec * usHOu] = lpHisOut[ll - 2 + usSec * usHOu];
        }

        lpHisInp[usSec * usHIn + 1] = lpHisInp[usSec * usHIn];
        lpHisOut[usSec * usHOu] = lpSrcBuf[usSmp];
    }

    /********************************************************************/
    /********************************************************************/
    return (0);
}


