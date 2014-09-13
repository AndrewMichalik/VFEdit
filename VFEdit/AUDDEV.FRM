VERSION 2.00
Begin Form frmAudDev 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "Audio Device Select"
   ClientHeight    =   3828
   ClientLeft      =   1380
   ClientTop       =   1632
   ClientWidth     =   5280
   Height          =   4200
   KeyPreview      =   -1  'True
   Left            =   1356
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3828
   ScaleWidth      =   5280
   Top             =   1284
   Width           =   5328
   Begin SSCheck chkCfgQry 
      Caption         =   "&Configure"
      Height          =   372
      Left            =   3960
      TabIndex        =   15
      Top             =   3360
      Visible         =   0   'False
      Width           =   1215
   End
   Begin SSFrame grpDevTyp 
      Caption         =   "Device &Type:"
      ForeColor       =   &H00000000&
      Height          =   795
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3735
      Begin ComboBox cboDevTyp 
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   360
         Width           =   3495
      End
   End
   Begin SSFrame grpBuffer 
      Caption         =   "&Buffer Blocks"
      ForeColor       =   &H00000000&
      Height          =   1035
      Left            =   120
      TabIndex        =   7
      Top             =   2640
      Width           =   3735
      Begin SpinButton spnBlkCnt 
         Height          =   315
         Left            =   3360
         Top             =   600
         Width           =   255
      End
      Begin TextBox edtBlkCnt 
         Height          =   315
         Left            =   2040
         TabIndex        =   11
         Text            =   "4"
         Top             =   600
         Width           =   1335
      End
      Begin SpinButton spnBlkLen 
         Height          =   315
         Left            =   1440
         Top             =   600
         Width           =   255
      End
      Begin TextBox edtBlkLen 
         Height          =   315
         Left            =   120
         TabIndex        =   9
         Text            =   "16"
         Top             =   600
         Width           =   1335
      End
      Begin Label lblBlkCnt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Count:"
         Height          =   255
         Left            =   2040
         TabIndex        =   10
         Top             =   360
         Width           =   1575
      End
      Begin Label lblBlkLen 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Length (Kbytes):"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   1575
      End
   End
   Begin SSFrame grpDatFmt 
      Height          =   1575
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   3735
      Begin ComboBox cboDatFmt 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   120
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   420
         Width           =   3495
      End
      Begin ComboBox cboDatFrq 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   120
         TabIndex        =   6
         Top             =   1140
         Width           =   3495
      End
      Begin Label lblDatFmt 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Data Format:"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   180
         Width           =   3015
      End
      Begin Label lblDatFrq 
         BackColor       =   &H00C0C0C0&
         Caption         =   "&Frequency (Hz):"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   900
         Width           =   2655
      End
   End
   Begin CommandButton cmdHlpBut 
      Caption         =   "Help"
      Height          =   375
      Left            =   3960
      TabIndex        =   14
      Top             =   1620
      Width           =   1215
   End
   Begin CommandButton CmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   3960
      TabIndex        =   12
      Top             =   120
      Width           =   1215
   End
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3960
      TabIndex        =   13
      Top             =   600
      Width           =   1215
   End
End
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Voice Information Systems (1-800-234-VISI) VFEdit Professional Prompt Editor
'                   (c) Copyright Andrew J. Michalik 1987-1999
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Option Explicit

' Device enumerated types
Dim aDevOpnCtlTyp() As VFEDEVTYP

' Data format enumerated types
Dim aDevOpnPCMEnu() As Variant
Dim aDevOpnChnEnu() As Variant
Dim aDevOpnFrqEnu() As Variant

Const UNKCTLPRO = 0                 ' Unknown / best match control protocol
Const DEFBLKLEN = 16                ' Default buffer block length (kilobytes)
Const DEFBLKCNT = 4                 ' Default buffer block count
Const DEFCFGQRY = False             ' Default config query
Const SELBSTFMT = "Best Match"      ' Dev best match selection
Const QRYBSTFMT = -1
Const BUFBLKINC = 4                 ' Buffer block increment
Const BUFBLKMIN = 4                 ' Buffer block Minimum
Const BUFBLKMAX = 128               ' Buffer block maximum
Const BUFBLKFMT = "0"               ' Buffer block display format

Const UNKPCMTYP = 0                 ' Unknown / best match PCM type
Const UNKSMPFRQ = 0                 ' Unknown / best match sample frequency

Sub cboDatFmt_Click ()
    Dim iDevIdx As Integer
    iDevIdx = cboDevTyp.ListIndex
    
    aDevOpnCtlTyp(iDevIdx).iPCMTyp = aDevOpnPCMEnu(cboDatFmt.ListIndex)
    ProSelChnIni
    ProSelFrqIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iPCMTyp, aDevOpnCtlTyp(iDevIdx).iChnCnt, aDevOpnCtlTyp(iDevIdx).lSmpFrq, cboDatFrq
End Sub

Sub cboDevTyp_Click ()
    Dim iDevIdx As Integer
    iDevIdx = cboDevTyp.ListIndex
    ProSelDatIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iPCMTyp, cboDatFmt
    ProSelChnIni
    ProSelFrqIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iPCMTyp, aDevOpnCtlTyp(iDevIdx).iChnCnt, aDevOpnCtlTyp(iDevIdx).lSmpFrq, cboDatFrq
    ProSelLenIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iBlkLen, edtBlkLen
    ProSelCntIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iBlkCnt, edtBlkCnt
    ProSelCfgIni aDevOpnCtlTyp(iDevIdx).iCtlPro, aDevOpnCtlTyp(iDevIdx).iCfgQry, chkCfgQry
End Sub

Sub chkCfgQry_Click (Value As Integer)
    aDevOpnCtlTyp(cboDevTyp.ListIndex).iCfgQry = chkCfgQry.Value
End Sub

Sub cmdCancel_Click ()
    FrmModRet Me, ""
End Sub

Sub cmdHlpBut_Click ()
  SendKeys "{F1}"
End Sub

Sub CmdOK_Click ()
    Dim tDevTyp As VFEDEVTYP
    Dim iRetCod As Integer

    ' Verify valid sample frequency entry
    If (Val(cboDatFrq.Text) <> DevCtlFrqChk(tDevTyp.iCtlPro, Val(cboDatFrq.Text))) Then
        Beep
        cboDatFrq.SetFocus
        cboDatFrq.SelStart = 0
        cboDatFrq.SelLength = Len(cboDatFrq)
        Exit Sub
    End If

    'Set requested frequency
    aDevOpnCtlTyp(cboDevTyp.ListIndex).lSmpFrq = Val(cboDatFrq.Text)
    
    ' Verify valid buffer block entries
    If EdtRngBad(edtBlkLen, BUFBLKMIN, BUFBLKMAX) Then Exit Sub
    If EdtRngBad(edtBlkCnt, BUFBLKMIN, BUFBLKMAX) Then Exit Sub
    
    tDevTyp = aDevOpnCtlTyp(cboDevTyp.ListIndex)
    
    FrmModRet Me, TypDevToStr(tDevTyp)
End Sub

Function DevCtlCfgEnu (ByVal iCtlPro As Integer, aCfgQry() As Variant) As Long
    Dim tDefDev As VFEDEVTYP

    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    If (iCtlPro <> tDefDev.iCtlPro) Then tDefDev.iCfgQry = DEFCFGQRY

    ' Set default configuration query
    DevCtlCfgEnu = tDefDev.iCfgQry

End Function

Function DevCtlCntEnu (ByVal iCtlPro As Integer, aBlkCnt() As Variant) As Long
    Dim tDefDev As VFEDEVTYP

    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    If (iCtlPro <> tDefDev.iCtlPro) Then tDefDev.iBlkCnt = DEFBLKCNT

    ' Set default buffer count
    DevCtlCntEnu = tDefDev.iBlkCnt

End Function

Function DevCtlFrqChk (ByVal iCtlPro As Integer, ByVal lReqFrq As Long) As Long
    ' Check max and Min limits on requested frequency
    ' Permit UNKSMPFRQ (Best match)
    If ((lReqFrq <> UNKSMPFRQ) And (lReqFrq < 1000&)) Then
        DevCtlFrqChk = 1000
        Exit Function
    End If
    
    If (lReqFrq > 64000) Then
        DevCtlFrqChk = 64000
        Exit Function
    End If
    
    DevCtlFrqChk = lReqFrq

End Function

Function DevCtlFrqDef (ByVal iCtlPro As Integer, aSmpFrq() As Variant, ByVal lDefFrq As Long) As Long
    On Error GoTo DevCtlFrqDefErr
    
    'Check and set default sample frequency selection
    If (lDefFrq <= 0) Then          ' Or out of range?
        DevCtlFrqDef = aSmpFrq(0)   ' Best Match
        ' NewVoice hack: Future need default frequency and format selection functions
        If ((16 = iCtlPro) And (16000 = aSmpFrq(0))) Then DevCtlFrqDef = aSmpFrq(UBound(aSmpFrq))
    Else
        DevCtlFrqDef = lDefFrq
    End If
    Exit Function

DevCtlFrqDefErr:
    On Error GoTo 0
    MsgBox WRN_BADDEFVAL, MB_ICONEXCLAMATION, Caption
    DevCtlFrqDef = SMPFRQMin
    Exit Function

End Function

Function DevCtlFrqEnu (ByVal iCtlPro As Integer, ByVal iPCMTyp As Integer, ByVal iChnCnt As Integer, aSmpFrq() As Variant) As Long
    Dim tDefDev As VFEDEVTYP
    Dim lSmpFrq As Long
    Dim iNewIdx As Integer

    ' Initialize for "best match" option
    lSmpFrq = QRYBSTFMT
    
    If AudDevFrqEnu(iCtlPro, iPCMTyp, iChnCnt, lSmpFrq) Then
        ReDim aSmpFrq(0)
        aSmpFrq(0) = lSmpFrq
        iNewIdx = 1
    End If
               
    ' Scan for .DLL recommended frequencies
    lSmpFrq = UNKSMPFRQ
    
    While (AudDevFrqEnu(iCtlPro, iPCMTyp, iChnCnt, lSmpFrq))
        ReDim Preserve aSmpFrq(iNewIdx)
        aSmpFrq(iNewIdx) = lSmpFrq
        iNewIdx = iNewIdx + 1
    Wend

    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    
    If (iCtlPro <> tDefDev.iCtlPro) Then tDefDev.lSmpFrq = UNKSMPFRQ
    
    ' Check and set default frequency selection
    DevCtlFrqEnu = DevCtlFrqDef(iCtlPro, aSmpFrq(), tDefDev.lSmpFrq)
    
End Function

Function DevCtlLenEnu (ByVal iCtlPro As Integer, aBlkLen() As Variant) As Integer
    Dim tDefDev As VFEDEVTYP

    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    
    If (iCtlPro <> tDefDev.iCtlPro) Then tDefDev.iBlkLen = DEFBLKLEN

    ' Set default buffer length
    DevCtlLenEnu = tDefDev.iBlkLen

End Function

Function DevCtlPCMDef (ByVal iCtlPro As Integer, aPCMTyp() As Variant, ByVal iDefPCM As Integer)
    On Error GoTo DevCtlPCMDefErr
    
    'Check and set default PCM type selection
    If ((iDefPCM <= 0) Or (-1 = FndVarIdx(aPCMTyp(), iDefPCM))) Then
        DevCtlPCMDef = aPCMTyp(0)
    Else
        DevCtlPCMDef = iDefPCM
    End If
    Exit Function

DevCtlPCMDefErr:
    On Error GoTo 0
    MsgBox WRN_BADDEFVAL, MB_ICONEXCLAMATION, Caption
    DevCtlPCMDef = UNKPCMTYP
    Exit Function

End Function

Function DevCtlPCMEnu (ByVal iCtlPro As Integer, aPCMTyp() As Variant, sPCMDes() As String) As Integer
    Dim tDefDev As VFEDEVTYP
    Dim sDesStr As String
    Dim iPCMTyp As Integer, iNewIdx As Integer
    sDesStr = String(255, Chr$(STRNULDEL))

    ' Initialize for "best match" option
    iPCMTyp = QRYBSTFMT
    
    If (AudDevPCMEnu(iCtlPro, iPCMTyp, sDesStr, Len(sDesStr))) Then
        ReDim aPCMTyp(0)
        ReDim sPCMDes(0)
        aPCMTyp(0) = iPCMTyp
        sPCMDes(0) = SELBSTFMT
        iNewIdx = 1
    End If
    
    iPCMTyp = UNKPCMTYP

    ' Scan for .DLL supported PCM types
    While (AudDevPCMEnu(iCtlPro, iPCMTyp, sDesStr, Len(sDesStr)))
        ReDim Preserve aPCMTyp(iNewIdx)
        ReDim Preserve sPCMDes(iNewIdx)
        aPCMTyp(iNewIdx) = iPCMTyp
        sPCMDes(iNewIdx) = StrTokStr(sDesStr, Chr$(STRNULDEL))
        iNewIdx = iNewIdx + 1
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend
    
    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    
    If (iCtlPro <> tDefDev.iCtlPro) Then tDefDev.iPCMTyp = UNKPCMTYP

    ' Check and set default PCM type selection
    DevCtlPCMEnu = DevCtlPCMDef(iCtlPro, aPCMTyp(), tDefDev.iPCMTyp)

End Function

Function DevCtlTypDef (tDevTyp() As VFEDEVTYP, ByVal iDefPCM As Integer) As Integer
    On Error GoTo DevCtlTypDefErr
    
    'Check and set default file type selection
    If ((iDefPCM <= 0) Or (-1 = FndDevIdx(tDevTyp(), iDefPCM))) Then
        DevCtlTypDef = tDevTyp(0).iCtlPro
    Else
        DevCtlTypDef = iDefPCM
    End If
    Exit Function

DevCtlTypDefErr:
    On Error GoTo 0
    MsgBox WRN_BADDEFVAL, MB_ICONEXCLAMATION, Caption
    DevCtlTypDef = UNKCTLPRO
    Exit Function

End Function

Function DevCtlTypEnu (tDevTyp() As VFEDEVTYP) As Integer
    Dim tDefDev As VFEDEVTYP
    Dim sDesStr As String
    Dim iCtlPro As Integer
    Dim iNewIdx As Integer
    sDesStr = String(255, Chr$(STRNULDEL))

    ' Scan for .DLL supported devices
    Erase tDevTyp
    While (AudDevCtlEnu(iCtlPro, sDesStr, Len(sDesStr)))
        ReDim Preserve tDevTyp(iNewIdx)
        tDevTyp(iNewIdx).sDevDes = Trim$(StrTokStr(sDesStr, Chr$(STRNULDEL)))
        tDevTyp(iNewIdx).iCtlPro = iCtlPro
        iNewIdx = iNewIdx + 1
        sDesStr = String(255, Chr$(STRNULDEL))
    Wend

    '
    ' Search .Ini file for user defined formats
    '

    ' Fill in default values
    Dim aTmpEnu() As Variant
    Dim sTmpDes() As String
    For iNewIdx = 0 To UBound(tDevTyp)
        tDevTyp(iNewIdx).iPCMTyp = DevCtlPCMEnu(tDevTyp(iNewIdx).iCtlPro, aTmpEnu(), sTmpDes())
        tDevTyp(iNewIdx).iChnCnt = 1
        tDevTyp(iNewIdx).lSmpFrq = DevCtlFrqEnu(tDevTyp(iNewIdx).iCtlPro, tDevTyp(iNewIdx).iPCMTyp, tDevTyp(iNewIdx).iChnCnt, aTmpEnu())
        tDevTyp(iNewIdx).iBlkLen = DevCtlLenEnu(tDevTyp(iNewIdx).iCtlPro, aTmpEnu())
        tDevTyp(iNewIdx).iBlkCnt = DevCtlCntEnu(tDevTyp(iNewIdx).iCtlPro, aTmpEnu())
        tDevTyp(iNewIdx).iCfgQry = DevCtlCfgEnu(tDevTyp(iNewIdx).iCtlPro, aTmpEnu())
    Next iNewIdx

    ' Retrieve default device type from .Ini
    TypStrToDev PrfGetStr(PRF_DEVOPNSEC, PRF_DEVTYPKEY, ""), tDefDev
    
    ' Return default device type selection
    DevCtlTypEnu = DevCtlTypDef(tDevTyp(), tDefDev.iCtlPro)

End Function

Sub edtBlkCnt_Change ()
    aDevOpnCtlTyp(cboDevTyp.ListIndex).iBlkCnt = Val(edtBlkCnt.Text)
End Sub

Sub edtBlkCnt_GotFocus ()
    EdtTxtSel edtBlkCnt
End Sub

Sub edtBlkCnt_KeyDown (KeyCode As Integer, Shift As Integer)
    If (KEY_UP = KeyCode) Then
        spnBlkCnt_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnBlkCnt_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtBlkCnt.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub edtBlkLen_Change ()
    aDevOpnCtlTyp(cboDevTyp.ListIndex).iBlkLen = Val(edtBlkLen.Text)
End Sub

Sub edtBlkLen_GotFocus ()
    EdtTxtSel edtBlkLen
End Sub

Sub edtBlkLen_KeyDown (KeyCode As Integer, Shift As Integer)
    ' Test for arrow key; disable cursor movement if found
    If (KEY_UP = KeyCode) Then
        spnBlkLen_SpinUp
        KeyCode = 0
    End If
    If (KEY_DOWN = KeyCode) Then
        spnBlkLen_SpinDown
        KeyCode = 0
    End If
    If (KEY_HOME = KeyCode) Then
        edtBlkLen.SelStart = 0
        KeyCode = 0
    End If
End Sub

Sub Form_Activate ()
    Dim iDefTyp As Integer
    Dim sInpVar As String
    Dim ii As Integer

    ' Disable input, set mouse to hourglass
    FrmUsrDis Me
    
    ' Yield to complete re-paints
    DoEvents
    
    ' Retrieve input arguments from tag
    sInpVar = tag

    ' Enumerate device type and initialize combo box
    iDefTyp = DevCtlTypEnu(aDevOpnCtlTyp())
    
    cboDevTyp.Clear
    
    For ii = 0 To UBound(aDevOpnCtlTyp)
        cboDevTyp.AddItem (aDevOpnCtlTyp(ii).sDevDes)
    Next ii

    ' Set Device Type list box to default item
    cboDevTyp.ListIndex = FndDevIdx(aDevOpnCtlTyp(), iDefTyp)
    
    ' Re-enable input, set mouse to default
    FrmUsrEna Me
End Sub

Sub Form_KeyPress (KeyAscii As Integer)
    If KeyChkEsc(KeyAscii) Then cmdCancel_Click
End Sub

Sub Form_Load ()
    helpContextID = HLP_DEVSEL
    
    ' Insure that the controls contents are visible
    SafCtlClr Me
End Sub

Sub ProSelCfgIni (ByVal iCtlPro As Integer, ByVal iDefCfg As Integer, cChkBox As Control)
    chkCfgQry.Visible = (0 = AudDevCfgQry(0, iCtlPro, False))
    cChkBox = CChk(iDefCfg)
End Sub

Sub ProSelChnIni ()
  ' Single channel this release...
End Sub

Sub ProSelCntIni (ByVal iCtlPro As Integer, iDefLen As Integer, cEdtBox As TextBox)
    cEdtBox.Text = iDefLen
End Sub

Sub ProSelDatIni (iCtlPro As Integer, iDefPCM As Integer, cCboBox As ComboBox)
    Dim sPCMDes() As String
    Dim iTmp As Integer
    Dim ii As Integer

    cCboBox.Clear
    iTmp = DevCtlPCMEnu(iCtlPro, aDevOpnPCMEnu(), sPCMDes())
    For ii = 0 To UBound(aDevOpnPCMEnu)
        cCboBox.AddItem (sPCMDes(ii))
    Next ii
    cCboBox.ListIndex = FndVarIdx(aDevOpnPCMEnu(), iDefPCM)

End Sub

Sub ProSelFrqIni (ByVal iCtlPro As Integer, ByVal iPCMTyp As Integer, ByVal iChnCnt As Integer, lDefFrq As Long, cCboBox As ComboBox)
    Dim lTmp As Long, iFrqIdx As Integer
    Dim ii As Integer

    cCboBox.Clear
    lTmp = DevCtlFrqEnu(iCtlPro, iPCMTyp, iChnCnt, aDevOpnFrqEnu())
    For ii = 0 To UBound(aDevOpnFrqEnu)
        If (0& <> aDevOpnFrqEnu(ii)) Then
            cCboBox.AddItem (aDevOpnFrqEnu(ii))
        Else cCboBox.AddItem SELBSTFMT
        End If
    Next ii
    
    iFrqIdx = FndVarIdx(aDevOpnFrqEnu(), lDefFrq)
    cCboBox.ListIndex = iFrqIdx
    If (-1 = iFrqIdx) Then cCboBox.Text = lDefFrq

End Sub

Sub ProSelLenIni (ByVal iCtlPro As Integer, ByVal lDefLen As Long, cEdtBox As TextBox)
    cEdtBox.Text = lDefLen
End Sub

Sub spnBlkCnt_SpinDown ()
    EdtBoxSpn edtBlkCnt, -BUFBLKINC, BUFBLKMIN, BUFBLKMAX, BUFBLKFMT
End Sub

Sub spnBlkCnt_SpinUp ()
    EdtBoxSpn edtBlkCnt, BUFBLKINC, BUFBLKMIN, BUFBLKMAX, BUFBLKFMT
End Sub

Sub spnBlkLen_SpinDown ()
    EdtBoxSpn edtBlkLen, -BUFBLKINC, BUFBLKMIN, BUFBLKMAX, BUFBLKFMT
End Sub

Sub spnBlkLen_SpinUp ()
    EdtBoxSpn edtBlkLen, BUFBLKINC, BUFBLKMIN, BUFBLKMAX, BUFBLKFMT
End Sub

