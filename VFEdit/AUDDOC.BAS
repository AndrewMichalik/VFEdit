''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global pAudClpFil As Long               ' Application clipboard audio

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Audio File (no edit capability) Operations
Declare Function AudFilOpn Lib "vfecif.dll" (ppAudFil As Long, ByVal pszFilNam As String, ByVal usSegSel As Long, usFilFmt As Integer, usPCMTyp As Integer, usChnCnt As Integer, ulSmpFrq As Long, usEncMsk As Integer, ByVal hPolWnd As Long, ByVal ulPolArg As Long) As Integer
Declare Function AudFilCls Lib "vfecif.dll" (ppAudFil As Long) As Integer
Declare Function AudFilTypEnu Lib "vfecif.dll" (usFilFmt As Integer, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudFilPCMEnu Lib "vfecif.dll" (ByVal usFilFmt As Integer, usPCMTyp As Integer, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudFilChnEnu Lib "vfecif.dll" (ByVal usPCMTyp As Integer, usChnCnt As Integer) As Integer
Declare Function AudFilFrqEnu Lib "vfecif.dll" (ByVal usPCMTyp As Integer, ulSmpFrq As Long) As Integer
Declare Function AudFilResEnu Lib "vfecif.dll" (pusResAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudFilAAFEnu Lib "vfecif.dll" (pusAAFAlg As Integer, ByVal szDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function AudFilSmpCnt Lib "vfecif.dll" (ByVal pAudFil As Long) As Long
Declare Function AudFilSmpFrq Lib "vfecif.dll" (ByVal pAudFil As Long) As Long
Declare Function AudFilCmpChk Lib "vfecif.dll" (ByVal pAudFil As Long, ByVal pCmpFil As Long, ByVal flFrqThr As Single) As Integer
Declare Function AudFilMSecToSmp Lib "vfecif.dll" (ByVal pAudFil As Long, ByVal flTimPos As Single) As Long
Declare Function AudFilSmpToMSec Lib "vfecif.dll" (ByVal pAudFil As Long, ByVal ulSmpPos As Long) As Single

' Session File (full edit capability) Operations
Declare Function SesEdtOpn Lib "vfecif.dll" (ppSesEdt As Long, ByVal pszFilNam As String, ByVal usSegSel As Long, usFilFmt As Integer, usPCMTyp As Integer, usChnCnt As Integer, ulSmpFrq As Long, usEncMsk As Integer, ByVal pszTmpDir As String, ByVal hPolWnd As Long, ByVal ulPolArg As Long) As Integer
Declare Function SesEdtRev Lib "vfecif.dll" (ppSesEdt As Long) As Integer
Declare Function SesEdtDes Lib "vfecif.dll" (ByVal pAudFil As Long, ByVal sDesStr As String, ByVal usMaxLen As Integer, ByVal usRsv001 As Integer) As Integer
Declare Function SesEdtFil Lib "vfecif.dll" (ByVal pSesEdt As Long) As Long
Declare Function SesEdtMod Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal usSegReq As Integer) As Integer
Declare Function SesEdtCut Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal sDesStr As String) As Integer
Declare Function SesEdtCrp Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulCrpOff As Long, ByVal ulCrpCnt As Long, ByVal ulSmpCnt As Long, ByVal sDesStr As String) As Integer
Declare Function SesEdtCop Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal sDesStr As String) As Integer
Declare Function SesEdtPst Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal ulPstOff As Long, ByVal ulPstSmp As Long, ByVal usAAFAlg As Integer, ByVal usResAlg As Integer, ByVal bfRawInh As Integer, ByVal sDesStr As String) As Integer
Declare Function SesEdtEra Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal ulOrgCnt As Long, ByVal ulNewCnt As Long, ByVal sDesStr As String) As Integer
Declare Function SesEdtSav Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal pszFilNam As String, ByVal iAutBak As Integer) As Integer
Declare Function SesEdtCls Lib "vfecif.dll" (ppSesEdt As Long) As Integer
Declare Function SesEdtDemLim Lib "vfecif.dll" (ByVal ulRsv001 As Long, ByVal ulRsv002 As Long) As Integer
Declare Function SesEdtUndMax Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal usUndMax As Integer) As Integer
Declare Function SesEdtUndDes Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function SesEdtUndPrv Lib "vfecif.dll" (ByVal pSesEdt As Long) As Integer
Declare Function SesEdtRedDes Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal sDesStr As String, ByVal usMaxLen As Integer) As Integer
Declare Function SesEdtRedNxt Lib "vfecif.dll" (ByVal pSesEdt As Long) As Integer
Declare Function SesEdtSegSel Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal usSelQry As Integer) As Integer
Declare Function SesEdtSegCre Lib "vfecif.dll" (ByVal pSesEdt As Long) As Integer
Declare Function SesEdtSegDel Lib "vfecif.dll" (ByVal pSesEdt As Long) As Integer
Declare Function SesEdtSegTxtGet Lib "vfecif.dll" (ByVal pSesEdt As Long, iTxtArr As Integer, ByVal usBufSiz As Integer) As Integer
Declare Function SesEdtSegTxtSet Lib "vfecif.dll" (ByVal pSesEdt As Long, iTxtArr As Integer) As Integer

Declare Function SesEffChgFrq Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flFrqMul As Single, ByVal usAAFAlg As Integer, ByVal usResAlg As Integer, ByVal sDesStr As String) As Integer
Declare Function SesEffCmpExp Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, lpPrmArr As CMPEXPTYP, ByVal sDesStr As String) As Integer
Declare Function SesEffEchDec Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flDlyTim As Single, ByVal flDec_dB As Single, ByVal sDesStr As String) As Integer
Declare Function SesEffFad_IO Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flFadBeg As Single, ByVal flFadEnd As Single, ByVal usFadAlg As Integer, ByVal sDesStr As String) As Integer
Declare Function SesEffFrqEqu Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal usFFTOrd As Integer, pflEquArr As Single, ByVal usEquBnd As Integer, ByVal flEquGai As Single, ByVal pszDesStr As String) As Integer
Declare Function SesEffMixFil Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal usMixCnt As Integer, pMixFil As Long, pflFdITim As Single, pusMixLvl As Integer, pflFdOTim As Single, ByVal usAAFAlg As Integer, ByVal usResAlg As Integer, ByVal sDesStr As String) As Integer
Declare Function SesEffRedNoi Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flNoiThr As Single, ByVal flAtt_dB As Single, ByVal sDesStr As String) As Integer
Declare Function SesEffTonGen Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal usSigCnt As Integer, pflSigArr As Single, ByVal fTimLen As Single, ByVal pszDesStr As String) As Integer
Declare Function SesEffVolAdj Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flLvl_dB As Single, ByVal sDesStr As String) As Integer

Declare Function SesEffNrmLvl Lib "vfecif.dll" (ByVal pSesEdt As Long, ByVal ulSmpOff As Long, ByVal ulSmpCnt As Long, ByVal flNrmLvl As Single, ByVal flNrmExc As Single, ByVal flNrmMax As Single, flLvl_dB As Single) As Integer
Declare Function SesEffShwFrq Lib "vfecif.dll" (ByVal pAudFil As Long, ByVal ulSmpOff As Long, ByVal usFFTOrd As Integer, ByVal flSumCnt As Single, pusPltArr As Integer, ByVal ulTimPnt As Long, pusCmpCnt As Long) As Integer
Declare Function SesEffSndPos Lib "vfecif.dll" (ByVal pSesEdt As Long, pulSmpOff As Long, pulSmpLen As Long, ByVal flCrpSnd As Single, ByVal flCrpGrd As Single, lpPrmArr As Single) As Integer

Declare Function AmpDspOpn Lib "vfecif.dll" (ppAmpDsp As Long, ByVal pAudFil As Long, ByVal flSmppGP As Single, ByVal hWnd As Long) As Integer
Declare Function AmpDspCls Lib "vfecif.dll" (ppAmpDsp As Long) As Integer
Declare Function AmpDspPnt Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal hWnd As Long) As Integer
Declare Function AmpDspKey Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal usChar As Integer, ByVal usRepCnt As Integer, ByVal usFlags As Integer) As Integer
Declare Function AmpDspRes Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal flMSpDiv As Single) As Integer
Declare Function AmpDspScr Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal ulSmpPos As Long) As Integer
Declare Function AmpDspTic Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal usIDEvent As Integer) As Integer
Declare Function AmpDspCarSet Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal ulSmpOff As Long) As Integer
Declare Function AmpDspCarGet Lib "vfecif.dll" (ByVal pAmpDsp As Long, pulPosAtP As Long) As Integer
Declare Function AmpDspSelGet Lib "vfecif.dll" (ByVal pAmpDsp As Long, pulSelOff As Long, pulSelLen As Long) As Integer
Declare Function AmpDspSelSet Lib "vfecif.dll" (ByVal pAmpDsp As Long, ByVal ulSelOff As Long, ByVal ulSelLen As Long) As Integer

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Dim sFilTypMDB          As String       ' File Open type database name

Function AAFResGet (ByVal sTtlStr As String, ByVal sPrfSec As String, iAAFTyp As Integer, iResTyp As Integer) As Integer
    Dim sRetArg As String
    
    ' Return FALSE to indicate no selection
    AAFResGet = False
    
    ' Get anti-aliasing and resample types
    ' Note: Relies upon consistent use of PRF_AAFTYPKEY and PRF_RESTYPKEY for profile retrieval
    If ("" <> sPrfSec) Then
        iAAFTyp = Val(PrfGetStr(sPrfSec, PRF_AAFTYPKEY, Str$(AAFALGNRM)))
        iResTyp = Val(PrfGetStr(sPrfSec, PRF_RESTYPKEY, Str$(RESALGNRM)))
    End If

    ' Use defaults if algorithms are set to "Unknown" (zero)
    If (0 = iAAFTyp) Then iAAFTyp = AAFALGNRM
    If (0 = iResTyp) Then iResTyp = RESALGNRM

    ' Title string indicates whether to ask user for selection
    If ("" <> sTtlStr) Then
        ' Ask user for filter and resample algorithm settings
        sRetArg = FrmModShw(frmVFEMDI, frmFtrCfg, sTtlStr & Chr$(VFEARGDEL) & Str$(iAAFTyp) & Chr$(VFEARGDEL) & Str$(iResTyp), CTR_MIDMIDNON)
        If ("" = sRetArg) Then Exit Function

        ' Retrieve user response
        iAAFTyp = StrTokStr(sRetArg, Chr$(VFEARGDEL))
        iResTyp = StrTokStr(sRetArg, Chr$(VFEARGDEL))

    End If

    ' Return TRUE to indicate success
    AAFResGet = True

End Function

Sub AudClpCls ()
    Dim iRetCod As Integer
    ' Close clipboard file if currently open
    If (0 <> pAudClpFil) Then iRetCod = SesEdtCls(pAudClpFil)
End Sub

Sub AudClpOpn ()
    Dim iRetCod As Integer
    
    ' Create the global clipboard file
    iRetCod = SesEdtOpn(pAudClpFil, "", 0, 0, 0, 0, 0, 0, SafGetDir(PrfGetStr(PRF_OPTENVSEC, PRF_WRKDIRKEY, WRKDIRDEF)), frmVFEMDI.hWnd, CBK_WNDPOLMSG)

    ' On error, display clipboard open error message
    If (0 <> iRetCod) Then MsgBox MSG_BADCLPOPN, MB_OK, frmVFEMDI.Caption
End Sub

Function AudDocCapFnd (fAudDoc As Form) As String
    ' Trap no documents open
    On Error GoTo AudDocCapFndErr
    
    If TypeOf fAudDoc Is frmAudDoc Then
        If fAudDoc.Caption Like (MSG_FILUNTCAP & "*") Then
            AudDocCapFnd = ""
        Else
            Dim sDocCap As String
            sDocCap = fAudDoc.Caption
            AudDocCapFnd = StrTokStr(sDocCap, Chr$(CAPFILDEL))
        End If
    Else
        AudDocCapFnd = ""
    End If
    Exit Function

    ' Return null response
AudDocCapFndErr:
    On Error GoTo 0
    AudDocCapFnd = ""
    Exit Function

End Function

Function AudDocCnt () As Integer
    Dim ii As Integer
    Dim iDocCnt As Integer

    For ii = 0 To forms.Count - 1
        If TypeOf forms(ii) Is frmAudDoc Then iDocCnt = iDocCnt + 1
    Next ii
    AudDocCnt = iDocCnt

End Function

Private Function AudDocFilFnd (sFilNam As String) As Integer
    Dim ii As Integer
    Dim iDocCnt As Integer

    For ii = 0 To forms.Count - 1
        If TypeOf forms(ii) Is frmAudDoc Then
            If (0 = StrComp(AudDocCapFnd(forms(ii)), sFilNam, 1)) Then
                AudDocFilFnd = ii
                Exit Function
            End If
        End If
    Next ii
    AudDocFilFnd = -1

End Function

Sub AudDocLngPol (frmPolFrm As Form, sDesStr As String, wnd As Integer, msg As Integer, wp As Integer, lp As Long, retval As Long, nodef As Integer)
    Dim usRetCod As Integer

    ' Initialize activity description string; reset cancel request
    If (LNGPOLBEG = wp) Then
        sDesStr = CIFGetStr(CInt(lp), "Working") & " <Ctrl-C to break>" & "... "
        lp = 0
    End If
    
    ' Call poll display procedure
    LngPolPct frmPolFrm, wp, sDesStr, lp
    
    ' Return TRUE to continue processing
    ' Note: VFECIF Ctrl-C will return false
    nodef = True
    retval = True

End Sub

Sub AudDocMDBCls ()
    On Error Resume Next
    
    ' Close database and delete copy
    dFilTypMDB.Close

    SafFilDel sFilTypMDB & MSG_FILTYPEXT
    SafFilDel sFilTypMDB & ".LDB"
End Sub

Sub AudDocMDBOpn ()
    On Error GoTo AudDocMDBOpnErr
    Dim sVFEDocMDB As String
    Dim iFilAtr As Integer

    ' Initialize the full path names for the file type MDB
    ' Check application original directory, working directory, & environment directory
    sVFEDocMDB = SafGetDir(App.Path) & MSG_FILTYPMDB
    If Not SafFilExi(sVFEDocMDB, iFilAtr) Then
        sVFEDocMDB = SafGetDir(WRKDIRDEF) & MSG_FILTYPMDB
        If Not SafFilExi(sVFEDocMDB, iFilAtr) Then sVFEDocMDB = SafGetDir(CurDir$) & MSG_FILTYPMDB
    End If
    sFilTypMDB = SafGetDir(PrfGetStr(PRF_OPTENVSEC, PRF_WRKDIRKEY, WRKDIRDEF)) & MSG_FILTYPPFX & Hex$(GetCurrentTask())
    
    ' Copy & open the file type database
    FileCopy sVFEDocMDB, sFilTypMDB & MSG_FILTYPEXT
    
    Set dFilTypMDB = OpenDatabase(sFilTypMDB & MSG_FILTYPEXT, False, False, "")
    
    ' Enumerate document types
    AudDocTypEnu
    Exit Sub

AudDocMDBOpnErr:
    ' Note: Error$ is reset by "On Error GoTo 0"
    ErrMsgExi (Error$ & CRLF() & sVFEDocMDB & ": " & MSG_BADFILMDB)
    Exit Sub

End Sub

Function AudDocOpn (ByVal sFilNam As String, tOpnDoc As VFEDOCTYP, iRd_Onl As Integer, sSegDes As String) As String
    Dim iRetCod As Integer
    Dim sVFEDoc As String
    
    ' Check if file is already open before referencing form
    If (("" <> sFilNam)) Then
        iRetCod = AudDocFilFnd(sFilNam)
        If (-1 <> iRetCod) Then
            forms(iRetCod).SetFocus
            AudDocOpn = WRN_FILALROPN
            Exit Function
        End If
    End If

    ' Try to create new instance of Audio Document
    On Error GoTo AudDocOpnErr
    Dim fNewDoc As New frmAudDoc

    ' Insure that there are sufficient resources to load form
    Load fNewDoc

    ' Open document
    sVFEDoc = FrmFunExe(fNewDoc, "AudDocLod", sFilNam & Chr$(VFEARGDEL) & TypDocToStr(tOpnDoc) & Chr$(VFEARGDEL) & Str(iRd_Onl) & Chr$(VFEARGDEL) & sSegDes)
    
    ' If failed, unload
    If ("" = sVFEDoc) Then
        ' The document unload will close the pSesEdt object
        Unload fNewDoc
        AudDocOpn = WRN_BADFILOPN
        Exit Function
    End If
    
    ' Update open document returned type (retrieves updated info for headered & segmented files)
    TypStrToDoc sVFEDoc, tOpnDoc

    ' Open successful, update .INI setting
    PrfSetStr PRF_AUDDOCSEC, PRF_DOCTYPKEY, TypDocToSec(tOpnDoc)
    PrfSetStr TypDocToSec(tOpnDoc), PRF_TYPDATKEY, TypDocToDef(tOpnDoc)

    fNewDoc.Show
    AudDocOpn = ""

AudDocOpnExit:
    Exit Function
    
AudDocOpnErr:
    On Error GoTo 0
    ' Warn user that open failed
    MsgBox WRN_INSWINRES, MB_ICONEXCLAMATION, frmVFEMDI.Caption
    AudDocOpn = WRN_INSWINRES
    Resume AudDocOpnExit

End Function

Sub AudDocSesCls (pSesEdt As Long)
    Dim iRetCod As Integer
    iRetCod = SesEdtCls(pSesEdt)
End Sub

Private Sub AudDocTypEnu ()
    'Initialize table tbFilTyp in dFilTypMDB via calls to VFECIF DLL
  
    Dim dsFilTyp As dynaset
    Dim sDesStr As String

    'variables for buffering dsFilType field values
    Dim sDocTyp As String
    Dim iFilFmt As Integer
    Dim sPCMDes As String
    Dim iPCMTyp As Integer
    Dim iChnCnt As Integer      ' Not currently used (always 1)
    Dim lSmpFrq As Long

    Set dsFilTyp = dFilTypMDB.CreateDynaset("SELECT * FROM tbFilTyp")
    
    sDesStr = String(255, Chr$(STRNULDEL))
    'Scan for .DLL supported formats
    Do While (AudFilTypEnu(iFilFmt, sDesStr, Len(sDesStr)))
        sDocTyp = Trim$(StrTokStr(sDesStr, Chr$(NEWLINDEL)))
        sDesStr = String(255, Chr$(STRNULDEL))
        Do While (AudFilPCMEnu(iFilFmt, iPCMTyp, sDesStr, Len(sDesStr)))
            sPCMDes = StrTokStr(sDesStr, Chr$(STRNULDEL))
            sDesStr = String(255, Chr$(STRNULDEL))
            Do While (AudFilFrqEnu(iPCMTyp, lSmpFrq))
                dsFilTyp.AddNew
                dsFilTyp("sDocTyp") = sDocTyp
                dsFilTyp("iFilFmt") = iFilFmt
                dsFilTyp("iPCMTyp") = iPCMTyp
                dsFilTyp("sPCMDes") = sPCMDes
                dsFilTyp("iChnCnt") = 1
                dsFilTyp("lSmpFrq") = lSmpFrq
                dsFilTyp.Update
                sDesStr = String(255, Chr$(STRNULDEL))
            Loop
            ' Currently only support one channel
            ' Generalizing will require parallel update loop over AudFilChnEnu supplied values
        Loop
    Loop
  
    dsFilTyp.Close

End Sub

Function AudDocTypExt (tVFEDoc As VFEDOCTYP) As String
    ' Retrieve default extension for document type
    Dim sExtStr As String

    ' Extract extension(s) from document type description
    sExtStr = tVFEDoc.sDocTyp
    sExtStr = Right(sExtStr, Len(sExtStr) - InStr(sExtStr, "("))
    sExtStr = Left(sExtStr, InStr(sExtStr, ")") - 1)

    ' Check .INI file
    AudDocTypExt = PrfGetStr(TypDocToSec(tVFEDoc), PRF_TYPPATKEY, sExtStr)

End Function

Function AudDocTypFnd (ByVal sDefDoc As String) As String
    ' Get default settings for specified audio document type
    Dim tDefDoc As VFEDOCTYP
    Dim SQLWHERE As String

    ' Parse full or partial document type
    TypStrToDoc sDefDoc, tDefDoc

    ' Check for exact match
    SQLWHERE = "[sDocTyp] = '" & tDefDoc.sDocTyp & "' AND [iFilFmt] = " & tDefDoc.iFilFmt & " AND [sPCMDes] = '" & tDefDoc.sPCMDes & "' AND [iPCMTyp] = " & tDefDoc.iPCMTyp
    If (AudDocTypQry(SQLWHERE, tDefDoc)) Then
        AudDocTypFnd = TypDocToStr(tDefDoc)
        Exit Function
    End If

    ' No exact match, search for valid logical specification without descriptive PCM description
    SQLWHERE = "[sDocTyp] = '" & tDefDoc.sDocTyp & "' AND [iFilFmt] = " & tDefDoc.iFilFmt & " AND [iPCMTyp] = " & tDefDoc.iPCMTyp
    If (AudDocTypQry(SQLWHERE, tDefDoc)) Then
        AudDocTypFnd = TypDocToStr(tDefDoc)
        Exit Function
    End If

    ' No exact match, search for partial match
    SQLWHERE = "[sDocTyp] = '" & tDefDoc.sDocTyp & "' AND [iFilFmt] = " & tDefDoc.iFilFmt
    If (Not AudDocTypQry(SQLWHERE, tDefDoc)) Then
        SQLWHERE = "[sDocTyp] = '" & tDefDoc.sDocTyp & "'"
        If (Not AudDocTypQry(SQLWHERE, tDefDoc)) Then
            ' If no partial match, just use first entry from table
            If (Not AudDocTypQry("TRUE", tDefDoc)) Then
                ' Uh-oh! Database is empty
                MsgBox MSG_ERRFILMDB, MB_ICONEXCLAMATION + MB_OK, frmVFEMDI.Caption
                AudDocTypFnd = ""
                Exit Function
            End If
        End If
    End If
            
    ' Set default return document type
    AudDocTypFnd = TypDocToStr(tDefDoc)
        
    ' Partial (incomplete) match, check .INI file for default settings
    sDefDoc = TypDocToSec(tDefDoc) & Chr$(VFEARGDEL) & PrfGetStr(TypDocToSec(tDefDoc), PRF_TYPDATKEY, TypDocToDef(tDefDoc))
    TypStrToDoc sDefDoc, tDefDoc
        
    ' Test to insure valid .INI settings
    SQLWHERE = "[sDocTyp] = '" & tDefDoc.sDocTyp & "' AND [iFilFmt] = " & tDefDoc.iFilFmt & " AND [sPCMDes] = '" & tDefDoc.sPCMDes & "' AND [iPCMTyp] = " & tDefDoc.iPCMTyp
    If (AudDocTypQry(SQLWHERE, tDefDoc)) Then AudDocTypFnd = TypDocToStr(tDefDoc)
       
End Function

Private Function AudDocTypQry (SQLWHERE As String, tDefDoc As VFEDOCTYP) As Integer
    ' Query database for specified match
    Dim dsFilTyp As dynaset

    ' Build list of available file types
    Set dsFilTyp = dFilTypMDB.CreateDynaset("SELECT * FROM tbFilTyp WHERE " & SQLWHERE)
    
    ' If no match, return NULL
    If dsFilTyp.EOF Then
        dsFilTyp.Close
        AudDocTypQry = False
        Exit Function
    End If

    ' Retrieve default values (a record exists)
    tDefDoc.sDocTyp = dsFilTyp("sDocTyp")
    tDefDoc.iFilFmt = dsFilTyp("iFilFmt")
    tDefDoc.sPCMDes = dsFilTyp("sPCMDes")
    tDefDoc.iPCMTyp = dsFilTyp("iPCMTyp")
    tDefDoc.iChnCnt = dsFilTyp("iChnCnt")
    If ((tDefDoc.lSmpFrq < SMPFRQMIN) Or (tDefDoc.lSmpFrq > SMPFRQMAX)) Then tDefDoc.lSmpFrq = dsFilTyp("lSmpFrq")
    
    ' Close data set
    dsFilTyp.Close

    ' Return valid document type indicator
    AudDocTypQry = True
  
End Function

Function AudDocTypTxt (tVFEDoc As VFEDOCTYP) As String
    ' Describe data
    AudDocTypTxt = tVFEDoc.sPCMDes & " @ " & tVFEDoc.lSmpFrq & " " & MSG_DESFRQ_HZ
End Function

Function FtrAAFNam (iDefAlg As Integer) As String
    Dim iAlgEnu As Integer
    Dim sDesStr As String
    sDesStr = String(255, Chr$(STRNULDEL))
    
    ' Scan for supported anti-aliasing filter algorithms; set default
    iAlgEnu = 0
    While (AudFilAAFEnu(iAlgEnu, sDesStr, Len(sDesStr)))
        If (iAlgEnu = iDefAlg) Then
            FtrAAFNam = StrTokStr(sDesStr, Chr$(STRNULDEL))
            Exit Function
        End If
    Wend
    FtrAAFNam = MSG_DESFMTUNK
   
End Function

Function FtrResNam (iDefAlg As Integer) As String
    Dim iAlgEnu As Integer
    Dim sDesStr As String
    sDesStr = String(255, Chr$(STRNULDEL))
    
    ' Scan for supported anti-aliasing filter algorithms; set default
    iAlgEnu = 0
    While (AudFilResEnu(iAlgEnu, sDesStr, Len(sDesStr)))
        If (iAlgEnu = iDefAlg) Then
            FtrResNam = StrTokStr(sDesStr, Chr$(STRNULDEL))
            Exit Function
        End If
    Wend
    FtrResNam = MSG_DESFMTUNK
   
End Function

Sub AAFResSet (ByVal sPrfSec As String, iAAFTyp As Integer, iResTyp As Integer)
    PrfSetStr sPrfSec, PRF_AAFTYPKEY, Str$(iAAFTyp)
    PrfSetStr sPrfSec, PRF_RESTYPKEY, Str$(iResTyp)
End Sub

