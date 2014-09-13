''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

Private Sub CtlClrGet (cCtl As Control)
    ' Insure that the controls contents are visible
    On Error GoTo CtlClrGetErr
    Dim iCtl_OK As Integer

    ' Skip if not approved type
    ' Note: "Is TypOf" cannot be nested
    iCtl_OK = False
    If TypeOf cCtl Is TextBox Then iCtl_OK = True
    If TypeOf cCtl Is ListBox Then iCtl_OK = True
    If TypeOf cCtl Is CheckBox Then iCtl_OK = True
    If TypeOf cCtl Is ComboBox Then iCtl_OK = True
    If (Not iCtl_OK) Then Exit Sub
  
    ' Set default background and foreground color
    If (cCtl.ForeColor = cCtl.BackColor) Then cCtl.ForeColor = Not cCtl.BackColor
    cCtl.BackColor = PrfGetStr(PRF_OPTENVSEC, PRF_BAKCLRKEY, cCtl.BackColor)
    cCtl.ForeColor = PrfGetStr(PRF_OPTENVSEC, PRF_FORCLRKEY, cCtl.ForeColor)

    ' Set default font name, size, color
    cCtl.FontName = PrfGetStr(PRF_OPTENVSEC, PRF_FNTNAMKEY, cCtl.FontName)
    cCtl.FontSize = PrfGetStr(PRF_OPTENVSEC, PRF_FNTSIZKEY, cCtl.FontSize)
  
    ' Note: the drop down combobox appears to have a bug where the text is selected
    ' after setting the font name or size
    If TypeOf cCtl Is ComboBox Then If cCtl.Style = 0 Then cCtl.SelText = 0
  
    Exit Sub

CtlClrGetErr:
    Resume Next

End Sub

Sub EdtBoxSpn (cEdtCtl As Control, vInc As Variant, vMin As Variant, vMax As Variant, sFmtStr As String)
    Dim vNewVal As Variant
    vNewVal = Val(cEdtCtl) + vInc

    ' Verify valid edit box range
    If (vNewVal < vMin) Then
        vNewVal = vMin
        Beep
    End If
    If (vNewVal > vMax) Then
        vNewVal = vMax
        Beep
    End If
    
    ' Set new value with formatting
    cEdtCtl = Format$(vNewVal, sFmtStr)
End Sub

Function EdtDirBad (cEdtCtl As Control)
    ' Default to directory OK, exit if test succeeds
    EdtDirBad = False
    If (("" = Trim$(cEdtCtl.Text)) Or (cEdtCtl.Text = SafGetDir(cEdtCtl.Text))) Then Exit Function
    
    ' Highlight and beep
    cEdtCtl.SetFocus
    cEdtCtl.SelStart = 0
    cEdtCtl.SelLength = Len(cEdtCtl)
    EdtDirBad = True
    Beep
End Function

Function EdtRngBad (cEdtCtl As Control, vMin As Variant, vMax As Variant) As Integer
    EdtRngBad = False
    
    ' Force edit box to numeric value and verify valid range
    cEdtCtl = Val(cEdtCtl)
    If (cEdtCtl >= Val(vMin)) And (cEdtCtl <= Val(vMax)) Then Exit Function
    
    ' Highlight and beep
    cEdtCtl.SetFocus
    cEdtCtl.SelStart = 0
    cEdtCtl.SelLength = Len(cEdtCtl)
    EdtRngBad = True
    Beep
End Function

Sub EdtTxtSel (cEdtCtl As Control)
    cEdtCtl.SelStart = 0
    cEdtCtl.SelLength = Len(cEdtCtl)
End Sub

Function FndLstIdx (cLstCtl As Control, iDefVal As Integer)
    Dim ii As Integer
    For ii = 0 To cLstCtl.ListCount
        If (iDefVal = cLstCtl.ItemData(ii)) Then
            FndLstIdx = ii
            Exit Function
        End If
    Next ii
    FndLstIdx = -1

End Function

Function FndVarIdx (aVarTyp() As Variant, ByVal iDefVal As Variant) As Integer
    Dim ii As Integer
    For ii = 0 To VarArrMax(aVarTyp())
        If (iDefVal = aVarTyp(ii)) Then
            FndVarIdx = ii
            Exit Function
        End If
    Next ii
    FndVarIdx = -1

End Function

Sub GetConHlp (f As Form, contextId As Long)
  Dim i%
  i = WinHelp(f.hWnd, app.HelpFile, HELP_CONTEXT, ByVal contextId)
End Sub

Function GetFileVersion (FileToCheck As String) As String
    Dim lpdwHandle As Long
    Dim VersionInfoSize As Long
    Dim lpvdata As String
    Dim VersionInfo As Integer
    Dim lplpBuffer As Long
    Dim lpcb As Integer
    Dim ptrFixed As Integer
    Dim TransString As String
    Dim ptrString As Integer
    Dim fixedstr As String
    Dim stringcopy As Long
    Dim i As Integer
    Dim char As String
    Dim nextchar As String
    Dim TransValue As Long
    Dim TransTable As String

    On Error Resume Next

    VersionInfoSize& = GetFileVersionInfoSize(FileToCheck, lpdwHandle&)
    
    If VersionInfoSize& = 0 Then
        GetFileVersion = MSG_MODVERUNK
        Exit Function
    End If
    
    lpvdata$ = String(VersionInfoSize&, Chr$(STRNULDEL))
    VersionInfo% = GetFileVersionInfo(FileToCheck, lpdwHandle&, VersionInfoSize&, lpvdata$)
    ptrFixed% = VerQueryValue(lpvdata$, "\FILEVERSION", lplpBuffer&, lpcb%)
    
    If ptrFixed% = 0 Then
        ' Take a shot with the hardcoded TransString
        TransString$ = "040904E4"
        ptrString% = VerQueryValue(lpvdata$, "\StringFileInfo\" & TransString$ & "\CompanyName", lplpBuffer&, lpcb%)
        If ptrString% <> 0 Then GoTo GetValues
        ptrFixed% = VerQueryValue(lpvdata$, "\", lplpBuffer&, lpcb%)
        If ptrFixed% = 0 Then
            GetFileVersion = MSG_MODVERUNK
            Exit Function
        Else
            TransString$ = ""
            fixedstr$ = String(lpcb% + 1, Chr(0))
            stringcopy& = lstrcpyn(fixedstr$, lplpBuffer&, lpcb% + 1)
            For i = lpcb% To 1 Step -1
                char$ = Hex(Asc(Mid(fixedstr$, i, 1)))
                If Len(char$) = 1 Then
                    char$ = "0" + char$
                End If
                TransString$ = TransString$ + char$
                If Len(TransString$ & nextchar$) Mod 8 = 0 Then
                    TransString$ = "&H" & TransString$
                    TransValue& = Val(TransString$)
                    TransString$ = ""
                End If
            Next i
        End If
    End If
    
    TransTable$ = String(lpcb% + 1, Chr(0))
    TransString$ = String(0, Chr(0))
    stringcopy& = lstrcpyn(TransTable$, lplpBuffer&, lpcb% + 1)
    
    For i = 1 To lpcb%
        char$ = Hex(Asc(Mid(TransTable$, i, 1)))
        If Len(char$) = 1 Then
            char$ = "0" + char$
        End If
        
        If Len(TransString$ & nextchar$) Mod 4 = 0 Then
            nextchar$ = char$
        Else
            TransString$ = TransString$ + char$ + nextchar$
            nextchar$ = ""
            char$ = ""
        End If
    Next i

GetValues:
    ptrString% = VerQueryValue(lpvdata$, "\StringFileInfo\" & TransString$ & "\FileVersion", lplpBuffer&, lpcb%)
    
    If ptrString% = 1 Then
        TransTable$ = String(lpcb%, Chr(0))
        stringcopy& = lstrcpyn(TransTable$, lplpBuffer&, lpcb% + 1)
        ' GetFileVersion = TransTable$
        GetFileVersion = StrTokStr(TransTable$, Chr$(STRNULDEL))    ' Eliminate null char
    
    Else
        GetFileVersion = MSG_MODVERUNK
    End If
End Function

Function GetLoadedModule (sModFilNam As String) As String
  Dim hInst%, sModPthNam$

  ' Indicate "not loaded" as default
  GetLoadedModule = sModFilNam & MSG_MIDVERNOL
  
  ' get instance handle of module
  hInst = GetModuleHandle(sModFilNam)

  If (hInst > 0) Then
    sModPthNam = Space$(256)
    If (GetModuleFileName(hInst, sModPthNam, Len(sModPthNam)) > 0) Then GetLoadedModule = Trim$(StrTokStr(sModPthNam, Chr$(STRNULDEL)))
  End If
End Function

Private Function GetWinRec (ByVal hWnd As Integer, iLft As Integer, iTop As Integer, iRgt As Integer, iBot As Integer)
    Static rWrkRec As tagRECT

    ' Check for valid window handle
    If (0 = IsWindow(hWnd)) Then
        GetWinRec = False
        Exit Function
    End If

    ' Get window rectangle in screen coordinates
    GetWindowRect hWnd, rWrkRec.Left
    
    ' Convert to twips
    iLft = rWrkRec.Left * Screen.TwipsPerPixelX
    iTop = rWrkRec.Top * Screen.TwipsPerPixelY
    iRgt = rWrkRec.right * Screen.TwipsPerPixelX
    iBot = rWrkRec.bottom * Screen.TwipsPerPixelY

    ' Indicate success
    GetWinRec = True

End Function

Function Max (ByVal vVal1 As Variant, ByVal vVal2 As Variant) As Variant
    Max = vVal1
    If (Val(vVal2) > Val(vVal1)) Then Max = vVal2
End Function

Function Min (ByVal vVal1 As Variant, ByVal vVal2 As Variant) As Variant
    Min = vVal1
    If (Val(vVal2) < Val(vVal1)) Then Min = vVal2
End Function

Function PrfGetDir () As String
    Dim sRetStr As String
    sRetStr = String(255, Chr$(STRNULDEL))

    If (0 <> GetWindowsDirectory(sRetStr, Len(sRetStr))) Then
         PrfGetDir = Trim$(StrTokStr(sRetStr, Chr$(STRNULDEL))) & "\"
    Else PrfGetDir = ""
    End If
End Function

Function PrfGetStr (ByVal sSecNam As String, ByVal sKeyNam As String, ByVal sDefVal As String)
    Dim sRetStr As String
    sRetStr = String(255, Chr$(STRNULDEL))

    If (0 <> GetPrivateProfileString(sSecNam, sKeyNam, sDefVal, sRetStr, Len(sRetStr), sPrfFilNam)) Then
      PrfGetStr = Trim$(StrTokStr(sRetStr, Chr$(STRNULDEL)))
    Else
      PrfGetStr = Trim$(sDefVal)
    End If
End Function

Sub PrfSetStr (ByVal sSecNam As String, ByVal sKeyNam As String, ByVal sDefVal As String)
    Dim iRetCod As Integer

    iRetCod = WritePrivateProfileString(sSecNam, sKeyNam, sDefVal, sPrfFilNam)
End Sub

Function SafActDoc () As Integer
    On Error GoTo SafActDocErr
    SafActDoc = False
    
    ' Verify that there is a currently active audio document
    If TypeOf frmVFEMDI.ActiveForm Is frmAudDoc Then SafActDoc = True
    Exit Function

SafActDocErr:
    On Error GoTo 0
    
    Exit Function
End Function

Sub SafCtlClr (fFrm As Form)
    Dim ii As Integer
    ' Insure that the control contents are visible
    For ii = 0 To fFrm.Controls.Count - 1
        CtlClrGet fFrm.Controls(ii)
    Next ii
End Sub

Sub SafFilDel (sFilNam As String)
    On Error GoTo SafFilDelErr
    
    Kill sFilNam
    
    Exit Sub

SafFilDelErr:
    On Error GoTo 0

    Resume Next
End Sub

Function SafFilExi (ByVal sFilNam As String, iFilAtr As Integer) As Integer
    On Error GoTo SafFilExiErr

    ' Test if file is safe for input; Initialize to bad
    SafFilExi = False

    ' Verify valid directory specification
    iFilAtr = GetAttr_LF(sFilNam)
    If (FILE_ATTRIBUTE_BAD_EX = iFilAtr) Then Exit Function
    
    ' Return success
    SafFilExi = True
    Exit Function

SafFilExiErr:
    On Error GoTo 0
    
    iFilAtr = FILE_ATTRIBUTE_BAD_EX
    
    Resume Next
End Function

Sub SafFocCtl (fActFrm As Form, cActCtl As Control)
    ' Setting the active control on a minimized form causes
    ' a flashing infinite loop
    If (MINIMIZED = fActFrm.WindowState) Then Exit Sub

    ' Set form and control focus
    On Error GoTo SafFocCtlErr
    cActCtl.SetFocus

    Exit Sub

SafFocCtlErr:
    'Do not disable handler
    Resume Next
End Sub

Sub SafFocFrm (fActFrm As Form)
    ' Safely set focus to requested form
    On Error GoTo SafFocFrmMDI
    fActFrm.SetFocus
    Exit Sub

SafFocFrmMDI:
    On Error GoTo SafFocFrmMDIErr
    If (frmVFEMDI.Enabled) Then frmVFEMDI.SetFocus
    Resume Next

SafFocFrmMDIErr:
    Exit Sub

End Sub

Function SafGetDir (ByVal sDirStr As String) As String
    On Error GoTo SafGetDirErr

    Dim iFilAtr As Integer
    
    iFilAtr = 0

    ' Accept null string as valid (.Exe Working) directory
    If ("" = sDirStr) Then sDirStr = sAppWrkDir
    
    ' If not "\" only then add or subtract "\"
    If (Len(sDirStr) > 1) Then
        ' Add full path and "\" if drive specification only
        If (Right(sDirStr, 1) = MSG_FILDRVDEF) Then
            ' Side effect of CurDir$(x) causes drive change; force back to original
            Dim sOrgDir As String
            sOrgDir = CurDir$
            sDirStr = CurDir$(sDirStr)
            ChDrive (sOrgDir)
        End If

        ' Strip "\" by default (any path other than drive root)
        If (Right(sDirStr, 1) = "\") Then sDirStr = Left(sDirStr, Len(sDirStr) - 1)
        
        ' Add full path and "\" if drive specification only
        If (Right(sDirStr, 1) = MSG_FILDRVDEF) Then sDirStr = sDirStr & "\"
    End If
         
    ' Verify valid directory specification
    iFilAtr = GetAttr_LF(sDirStr) And FILE_ATTRIBUTE_DIRECTORY
    
SafGetDirExit:
    On Error GoTo 0
    
    ' If bad directory spec, reset to valid (.Exe Working) directory
    If (0 = (iFilAtr And FILE_ATTRIBUTE_DIRECTORY)) Then sDirStr = sAppWrkDir
    
    ' Add "\" if not already present
    If (Right(sDirStr, 1) <> "\") Then sDirStr = sDirStr & "\"
    
    SafGetDir = sDirStr

    Exit Function

SafGetDirErr:
    ' Beep on directory error - don't bother with message box
    ' MsgBox "[" & Err & "] " & Error, MB_ICONEXCLAMATION, frmVFEMDI.Caption
    ' Future: eliminate beep also?
    Beep
    Resume SafGetDirExit
End Function

Sub SafWndSta (fActFrm As Form, iWndSta)
    ' Set form and control focus
    On Error GoTo SafWndStaErr
    
    fActFrm.WindowState = iWndSta
    
    Exit Sub

SafWndStaErr:
    On Error GoTo 0

    Resume Next
End Sub

Function StrCmpStr (ByVal sInpStr As String, sDelStr) As String
    ' Compress embedded blanks
    Dim ii, iDelLen As Integer
    Dim sRetStr As String

    If ((sInpStr = Null) Or (sDelStr = Null) Or (0 = Len(sDelStr))) Then
        StrCmpStr = sInpStr
        Exit Function
    End If

    iDelLen = Len(sDelStr)
    For ii = 1 To Len(sInpStr) Step iDelLen
        If (sDelStr <> Mid(sInpStr, ii, iDelLen)) Then sRetStr = sRetStr & Mid$(sInpStr, ii, iDelLen)
    Next ii
    StrCmpStr = sRetStr

End Function

Function StrTokStr (sInpStr As String, ByVal sDelStr As String)
    ' Extract a token delimited string
    Dim iCurPos As Integer

    If ((sInpStr = Null) Or (sDelStr = Null) Or (0 = Len(sDelStr))) Then
        StrTokStr = sInpStr
        sInpStr = ""
        Exit Function
    End If

    iCurPos = InStr(sInpStr, sDelStr)
    If (0 = iCurPos) Then
        StrTokStr = sInpStr
        sInpStr = ""
        Exit Function
    End If

    StrTokStr = Left(sInpStr, iCurPos - 1)
    sInpStr = Right(sInpStr, Len(sInpStr) - iCurPos - Len(sDelStr) + 1)

End Function

Private Function VarArrMax (aInpArr() As Variant)
    On Error GoTo IntArrMaxErr
    
    VarArrMax = (UBound(aInpArr))
    
    Exit Function

IntArrMaxErr:
    On Error GoTo 0
    
    VarArrMax = -1
    
    Resume Next
End Function

Sub VerifyModule (sModFulNam$)
  ' Compare the versions of modules in memory to those installed on disk
  Dim hInst As Integer
  Dim sModFilNam As String
  Dim sModPthNam As String
  Dim sVerLod As String
  Dim sVerExp As String
  Dim sVerSav As String

  ' extract module name w/o path
  sModFilNam = sModFulNam

  Do While InStr(sModFilNam, "\") > 0
    sModFilNam = Mid$(sModFilNam, InStr(sModFilNam, "\") + 1)
  Loop

  sModPthNam = GetLoadedModule(sModFilNam)
  sVerLod = GetFileVersion(sModPthNam)   ' loaded
  sVerExp = GetFileVersion(sModFulNam)   ' expected
  sVerSav = PrfGetStr(PRF_MODUSESEC, sModFilNam, "")
  'Debug.Print sModFilNam; ": Exp="; sVerExp; ", loaded="; sVerLod; ", saved="; sVerSav
  
  If (sVerLod <> sVerExp) And (sVerSav <> sVerLod) Then
      FrmCtrMov frmModVer, 0, Screen.Width, 0, Screen.Height

      frmModVer.txtModFnd = LCase(sModPthNam) & MSG_MODVERVER & sVerLod  ' loaded module
      frmModVer.txtModExp = LCase(sModFulNam) & MSG_MODVERVER & sVerExp  ' expected module

      frmModVer.Show MODAL

      If frmModVer.chkSaveInfo Then PrfSetStr PRF_MODUSESEC, sModFilNam, sVerLod
    
      Unload frmModVer
    
      ' Yield to complete re-paints
      DoEvents
  End If

End Sub

