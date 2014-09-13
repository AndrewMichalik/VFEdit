''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Global variables shared by all modules
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Global sPrfFilNam       As String       ' Default .INI File name
Global sAppWrkDir       As String       ' Default application working directory
Global dFilTypMDB       As database     ' File Open type database

Global fPrvActFrm       As Form         ' Previously active form
Global lVFEVer_Jr       As Long         ' VFEdit Jr. version

Sub ErrMsgExi (sErrMsg As String)
    If ("" <> sErrMsg) Then MsgBox sErrMsg, MB_ICONEXCLAMATION + MB_OK, frmVFEMDI.Caption
    Unload frmVFEMDI
End Sub

Sub FrmCtrFoc (frmParFrm As Form, frmChdFrm As Form, iCtrFlg As Integer)
    If TypeOf frmParFrm Is frmVFEMDI Then
        ' Center a child form over a parent form.
        FrmCtrMov frmChdFrm, frmParFrm.Left, frmParFrm.Width, frmParFrm.Top, frmParFrm.Height
    Else
        ' Center after Adding in parent position
        FrmCtrMov frmChdFrm, frmVFEMDI.Left + frmParFrm.Left, frmParFrm.Width, frmVFEMDI.Top + frmParFrm.Top, frmParFrm.Height
    End If

    ' Position mouse of control with focus
    If (0 <> iCtrFlg) Then
    End If

End Sub

Sub FrmCtrMov (frmChdFrm As Form, ByVal iParLft As Integer, ByVal iParWid As Integer, ByVal iParTop As Integer, ByVal iParHgt As Integer)
    Dim iLftPos As Integer
    Dim iTopPos As Integer

    ' Get left offset
    iLftPos = iParLft + ((iParWid - frmChdFrm.Width) / 2)
    If (iLftPos + frmChdFrm.Width > screen.Width) Then iLftPos = screen.Width - frmChdFrm.Width
    If (iLftPos < 0) Then iLftPos = 0

    ' Get top offset
    iTopPos = iParTop + ((iParHgt - frmChdFrm.Height) / 2)
    If (iTopPos + frmChdFrm.Height > screen.Height) Then iTopPos = screen.Height - frmChdFrm.Height
    If (iTopPos < 0) Then iTopPos = 0

    ' Center the child form
    frmChdFrm.Move iLftPos, iTopPos

End Sub

Function FrmFunExe (fVFEDoc As Form, ByVal sPrcNam As String, ByVal sInpArg As String)
    ' This is a general purpose procedure used to
    ' communicate between forms
    
    ' Trap no documents or audio bar open
    On Error GoTo FrmFunExeErr
    
    If TypeOf fVFEDoc Is frmAudDoc Then
        fVFEDoc.funInpArg = sInpArg
        fVFEDoc.funPrcNam = sPrcNam
        fVFEDoc.funPrcNam.Refresh
        FrmFunExe = fVFEDoc.funRetVal
    End If
    If TypeOf fVFEDoc Is frmVFEMDI Then
        fVFEDoc.funInpArg = sInpArg
        fVFEDoc.funPrcNam = sPrcNam
        fVFEDoc.funPrcNam.Refresh
        FrmFunExe = fVFEDoc.funRetVal
    End If
    Exit Function

    ' Return null response
FrmFunExeErr:
    On Error GoTo 0
    FrmFunExe = ""
    Exit Function

End Function

Sub FrmModRet (fUnlFrm As Form, ByVal viRetCod As Variant)
    ' This is a modular input / output handler for modal forms
    ' Note that form is hidden, not unloaded. This prevents a possible
    ' loop if this routine is called by the form's unload event
    fUnlFrm.Tag = viRetCod
    fUnlFrm.Hide
End Sub

Function FrmModShw (frmParent As Form, fShwFrm As Form, ByVal vInpVal As Variant, ByVal iCtrFlg As Integer) As Variant
    ' This is a modular input / output handler for modal forms
    ' Note: One quirk is that the tag field is not
    '       available in the Form_Load event

    ' First set form "input"
    fShwFrm.Tag = vInpVal
    
    ' Center and show
    FrmCtrFoc frmParent, fShwFrm, iCtrFlg
    
    fShwFrm.Show modal
    
    ' Return response
    FrmModShw = fShwFrm.Tag
    
    Unload fShwFrm
End Function

Sub FrmUsrDis (fFrm As Form)
    ' Disable input, set mouse to hourglass
    fFrm.Enabled = False
    screen.MousePointer = HourGlass
End Sub

Sub FrmUsrEna (fFrm As Form)
    ' Re-enable input, set mouse to default
    screen.MousePointer = Default
    fFrm.Enabled = True
End Sub

Sub HelpContents ()
  Dim i%
  i = WinHelp(frmVFEMDI.hWnd, app.HelpFile, HELP_CONTENTS, ByVal CLng(0))
End Sub

Sub HelpSearch ()
  Dim i%
  i = WinHelp(frmVFEMDI.hWnd, app.HelpFile, HELP_PARTIALKEY, ByVal "")
End Sub

Function KeyChk_Z_ (KeyAscii As Integer) As Integer
    If (26 = KeyAscii) Then
        KeyAscii = 0
        KeyChk_Z_ = True
        Exit Function
    End If
    KeyChk_Z_ = False
End Function

Function KeyChkCan (KeyAscii As Integer) As Integer
    If (KEY_CANCEL = KeyAscii) Then
        KeyAscii = 0
        KeyChkCan = True
        Exit Function
    End If
    KeyChkCan = False
End Function

Function KeyChkEsc (KeyAscii As Integer) As Integer
    If (KEY_ESCAPE = KeyAscii) Then
        KeyAscii = 0
        KeyChkEsc = True
        Exit Function
    End If
    KeyChkEsc = False
End Function

Function KeyChkSpc (KeyAscii As Integer) As Integer
    If (26 = KeyAscii) Then
        KeyAscii = 0
        KeyChkSpc = True
        Exit Function
    End If
    KeyChkSpc = False
End Function

Sub LngPolPct (frmPolFrm As Form, iPolReq As Integer, sActDes As String, lPctCnt As Long)
    Const SEGFILSTP = 10
    Dim sErrMsg As String
    Dim ii As Integer

    frmVFEMDI.ctlStaLin.Segment = MID_LNGPOLDSP
    frmVFEMDI.ctlStaLin.SegFontBold = True
    frmVFEMDI.ctlStaLin.SegFillColor = &HFFFF&
    frmVFEMDI.ctlStaLin.SegMin = 0
    frmVFEMDI.ctlStaLin.SegMax = 100

    Select Case (iPolReq)
        Case LNGPOLBEG
            frmVFEMDI.ctlStaLin.SegFillValue = 0
            frmVFEMDI.ctlStaLin.SegCaption = sActDes
            ' Disable edit functions for this window
            sErrMsg = FrmFunExe(frmPolFrm, "AudDocBsySet", Str(True))
        Case LNGPOLCNT
            ' Display hourglass; disable form
            screen.MousePointer = 11
            frmVFEMDI.ctlStaLin.SegFillValue = lPctCnt
            frmVFEMDI.ctlStaLin.SegCaption = sActDes & lPctCnt & "%"
        Case LNGPOLEND
            If (frmVFEMDI.ctlStaLin.SegFillValue) Then
                ' Stretch completion graph if non zero
                ii = SEGFILSTP * (frmVFEMDI.ctlStaLin.SegFillValue / SEGFILSTP)
                For ii = ii To 100 Step SEGFILSTP
                    frmVFEMDI.ctlStaLin.SegFillValue = ii
                    frmVFEMDI.ctlStaLin.SegCaption = sActDes & ii & "%"
                Next ii
            End If
            frmVFEMDI.ctlStaLin.SegFillValue = 0
            frmVFEMDI.ctlStaLin.SegCaption = ""
            ' Remove  hourglass; enable form
            screen.MousePointer = 0
            ' Enable edit functions for this window
            sErrMsg = FrmFunExe(frmPolFrm, "AudDocBsySet", Str(False))
    End Select
    
End Sub

Sub LvlPolPct (iPolReq As Integer, sActDes As String, lPctCnt As Long)
    Const SEGFILSTP = 10
    Dim ii As Integer

    frmVFEMDI.ctlStaLin.Segment = MID_LNGPOLDSP
    frmVFEMDI.ctlStaLin.SegFontBold = True
    frmVFEMDI.ctlStaLin.SegFillColor = &HFFFF&
    frmVFEMDI.ctlStaLin.SegMin = 0
    frmVFEMDI.ctlStaLin.SegMax = 100

    Select Case (iPolReq)
        Case LNGPOLBEG
            frmVFEMDI.ctlStaLin.SegFillValue = 0
            frmVFEMDI.ctlStaLin.SegCaption = sActDes
        Case LNGPOLCNT
            frmVFEMDI.ctlStaLin.SegFillValue = lPctCnt
            frmVFEMDI.ctlStaLin.SegCaption = sActDes
        Case LNGPOLEND
            frmVFEMDI.ctlStaLin.SegFillValue = 0
            frmVFEMDI.ctlStaLin.SegCaption = ""
    End Select

End Sub

Sub No_EvtSet (cCtl As Control, iNewVal As Integer)
    Dim iEnaOrg As Integer
    iEnaOrg = cCtl.Enabled
   
   ' Disable to indicate that value was set by internal routine
    cCtl.Enabled = False
    cCtl.Value = iNewVal
    cCtl.Enabled = iEnaOrg
End Sub

Private Function RcnFilIdx (ByVal sFilNam As String) As Integer
    Dim sXfrArg As String
    Dim ii As Integer

    For ii = 1 To RCNFILCNT
        sXfrArg = frmVFEMDI.mnuFRecent(ii).Caption
        If (sFilNam = StrTokStr(sXfrArg, CRLF())) Then
            RcnFilIdx = ii
            Exit Function
        End If
    Next ii
    RcnFilIdx = 0

End Function

Sub RcnFilOpn (index As Integer)
    Dim sXfrArg As String
    Dim sFilNam As String
    Dim sErrMsg As String
    Dim tOpnDoc As VFEDOCTYP
    Dim iRetCod As Integer
    Dim iRd_Onl As Integer
    
    ' Retrieve recent file description
    iRetCod = RcnFilIdx(frmVFEMDI!mnuFRecent(index).Caption)
    If (0 = iRetCod) Then
        MsgBox MSG_BADFILTYP, MB_OK, frmVFEMDI.Caption
        Exit Sub
    End If
    sXfrArg = PrfGetStr(PRF_RCNFILSEC, PRF_RCNFILKEY & iRetCod, "")
    sFilNam = StrTokStr(sXfrArg, Chr$(VFEARGDEL))
    TypStrToDoc sXfrArg, tOpnDoc
    iRd_Onl = Val(StrTokStr(sXfrArg, Chr$(VFEARGDEL)))
    sErrMsg = AudDocOpn(sFilNam, tOpnDoc, iRd_Onl, "")

    ' Write to top and update recent files list.
    If ("" = sErrMsg) Then RcnFilWrt sFilNam, tOpnDoc, iRd_Onl

End Sub

Sub RcnFilUpd ()
    Dim ii, jj
    Dim sXfrArg As String
    Dim sFilNam As String
    
    ' Get recent file strings from .INI file
    For ii = 1 To RCNFILCNT
        sXfrArg = PrfGetStr(PRF_RCNFILSEC, PRF_RCNFILKEY & ii, "")
        sFilNam = StrTokStr(sXfrArg, Chr$(VFEARGDEL))
        If ("" <> sFilNam) Then
            ' Iterate to update the MDI & children recent file menus.
            For jj = 0 To forms.Count - 1
                On Error Resume Next
                forms(jj).mnuFRecent(0).Visible = True
                forms(jj).mnuFRecent(ii).Caption = sFilNam
                forms(jj).mnuFRecent(ii).Visible = True
            Next jj
        End If
    Next ii

    On Error GoTo 0

End Sub

Sub RcnFilWrt (sFilNam, tVFEDoc As VFEDOCTYP, iRd_Onl As Integer)
    Dim ii As Integer
    Dim iPos As Integer
    Dim iRetCod As Integer
    Dim sPrfStr As String
    sPrfStr = String(255, Chr$(STRNULDEL))

    ' Find current file position in list
    iPos = RcnFilIdx(sFilNam)

    ' Choose end of list based upon current list position
    If (0 = iPos) Then
        iPos = RCNFILCNT - 1
    Else
        iPos = iPos - 1
    End If

    ' Copy RecentFile1 to RecentFile2, etc.
    For ii = iPos To 1 Step -1
        sPrfStr = PrfGetStr(PRF_RCNFILSEC, PRF_RCNFILKEY & ii, "")
        If ("" <> sPrfStr) Then
            PrfSetStr PRF_RCNFILSEC, PRF_RCNFILKEY & (ii + 1), sPrfStr
        End If
    Next ii
  
    ' Write sFilNam to first Recent File.
    PrfSetStr PRF_RCNFILSEC, PRF_RCNFILKEY & 1, sFilNam & Chr$(VFEARGDEL) & TypDocToStr(tVFEDoc) & Chr$(VFEARGDEL) & Str(iRd_Onl)
    RcnFilUpd

End Sub

Sub ViwStaClk ()
    frmVFEMDI.ctlStaLin.Visible = Not frmVFEMDI.ctlStaLin.Visible
End Sub

Sub ViwTolClk ()
    frmVFEMDI!picTolBar.Visible = Not frmVFEMDI.picTolBar.Visible
    SetAudBar frmVFEMDI!picTolBar.Visible
End Sub

